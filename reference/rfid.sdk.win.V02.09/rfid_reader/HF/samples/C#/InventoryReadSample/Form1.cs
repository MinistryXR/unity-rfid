using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.Collections;

namespace RPANSample
{
    public partial class Form1 : Form
    {
        private UIntPtr hreader = UIntPtr.Zero;
        Thread m_thread = null;
        bool b_threadRun = false;
        public ArrayList readerDriverInfoList;
        public Form1()
        {
            InitializeComponent();

            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
            UInt32 nCount = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();   
            for (UInt32 i = 0; i < nCount; i++)
            {
                StringBuilder strName = new StringBuilder();
                strName.Append('\0', 128);
                UInt32 nSize = (UInt32)strName.Capacity;
                RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(i, RFIDLIB.rfidlib_def.LOADED_RDRDVR_OPT_NAME, strName, ref nSize);
               comboBoxReader.Items.Add(strName.ToString());
            }
            comboBoxReader.SelectedIndex = 0;

            UInt32 nCOMCnt = RFIDLIB.rfidlib_reader.COMPort_Enum();
            for (UInt32 i = 0; i < nCOMCnt; i++)
            {
                StringBuilder comName = new StringBuilder();
                comName.Append('\0', 64);
                RFIDLIB.rfidlib_reader.COMPort_GetEnumItem(i, comName, (UInt32)comName.Capacity);
                comboBoxCOM.Items.Add(comName);
            }

            if (comboBoxCOM.Items.Count > 0)
            {
                comboBoxCOM.SelectedIndex = 0;
            }
          
            comboBoxBaud.SelectedIndex = 1;
            comboBoxFrame.SelectedIndex = 0;

            buttonOpen.Enabled          = true;
            buttonClose.Enabled         = false;
            comboBoxCOM.Enabled         = true;
            comboBoxBaud.Enabled        = true;
            comboBoxFrame.Enabled       = true;
            buttonStartRecord.Enabled   = false;
            buttonStopRecord.Enabled    = false;
            readerDriverInfoList        = new ArrayList();

            comboBoxCOM.SelectedIndex   = comboBoxCOM.Items.Count - 1;
            start_block.SelectedIndex   = 0;
            comboBoxBlockNum.SelectedIndex     = 0;
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            int iret = 0;

            string readerDriverName = comboBoxReader.Text;//"RD5100";
            string connstr = "";

            Int32 idx = comboBoxCOM.SelectedIndex;
            if(idx == -1)
            {
                MessageBox.Show("Open reader failed!");
            }
           
            connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE   + "=" + readerDriverName    + ";" +
                      RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                      RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME  + "=" + comboBoxCOM.Text    + ";" +
                      RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + comboBoxBaud.Text   + ";" +
                      RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + comboBoxFrame.Text  + ";" +
                      RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR  + "=" + "255";

            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("Open reader failed!");
                return;
            }
            UInt32 antennaCount = RFIDLIB.rfidlib_reader.RDR_GetAntennaInterfaceCount(hreader);
            for (int i = 0; i < antennaCount; i++)
            {
                int iAnt;
                iAnt = i + 1;
                checkedListBoxAntennaList.Items.Add("Antenna#" + iAnt.ToString());
            }
            buttonOpen.Enabled          = false;
            buttonClose.Enabled         = true;
            comboBoxCOM.Enabled         = false;
            comboBoxBaud.Enabled        = false;
            comboBoxFrame.Enabled       = false;
            buttonStartRecord.Enabled   = true;
            buttonStopRecord.Enabled    = false;
            comboBoxReader.Enabled = false;
           
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            if (b_threadRun)
            {
                MessageBox.Show("Please stop the thread first!");
                return;
            }
            if (hreader == UIntPtr.Zero)
            {
                return;
            }
            RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            hreader = UIntPtr.Zero;

            buttonOpen.Enabled          = true;
            buttonClose.Enabled         = false;
            comboBoxCOM.Enabled         = true;
            comboBoxBaud.Enabled        = true;
            comboBoxFrame.Enabled       = true;
            buttonStartRecord.Enabled   = false;
            buttonStopRecord.Enabled    = false;
            comboBoxReader.Enabled = true;
            checkedListBoxAntennaList.Items.Clear();
        }

        private delegate void delegate_addRecord(string uid, string recordData);
        private void addRecord(string uid, string recordData)
        {
            dataGridViewRecord.Rows.Add();
            dataGridViewRecord[0, dataGridViewRecord.RowCount - 1].Value = uid;
            dataGridViewRecord[1, dataGridViewRecord.RowCount - 1].Value = recordData;
        }

        private void buttonStartRecord_Click(object sender, EventArgs e)
        {
            buttonClose.Enabled         = false;
            buttonStartRecord.Enabled   = false;
            buttonStopRecord.Enabled    = true;
            buttonOpen.Enabled = false;
            checkedListBoxAntennaList.Enabled = false;
            start_block.Enabled = false;
            comboBoxBlockNum.Enabled = false;
            checkBoxReadSecureSta.Enabled = false;
            dataGridViewRecord.Rows.Clear();
            m_thread = new Thread(InventoryProc);
            m_thread.Start();
        }

        private void InventoryProc()
        {
            int iret                        = 0;
            UIntPtr dnhReport               = UIntPtr.Zero;
            b_threadRun                     = true;
            byte AIType                     = RFIDLIB.rfidlib_def.AI_TYPE_NEW;
            Byte IsReadSecureStatusBytes = 0;
            UInt32 StartAddr                = 0;
            UInt32 NumOfToReadBlocks             = 0;
            Byte[] AntennaSel=new Byte[64];
            Byte AntennaSelCount = 0;

            this.Invoke((EventHandler)(delegate
            {
                for (int i = 0; i < checkedListBoxAntennaList.Items.Count; i++)
                {
                    if (checkedListBoxAntennaList.GetItemChecked(i))
                    {
                        AntennaSel[AntennaSelCount] = (Byte)(i + 1);
                        AntennaSelCount++;
                    }
                }
                IsReadSecureStatusBytes =(Byte) (checkBoxReadSecureSta.Checked?1:0);
                StartAddr = (UInt32)start_block.SelectedIndex;
                NumOfToReadBlocks = (UInt32)comboBoxBlockNum.SelectedIndex + 1;
            }));

            UIntPtr m_hInvenParamSpecList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
            if (UIntPtr.Zero == m_hInvenParamSpecList)
            {
                return;
            }
            UIntPtr hIso15693InvenParam = RFIDLIB.rfidlib_aip_iso15693.ISO15693_CreateInvenParam(m_hInvenParamSpecList, 0, 0, 0, 0);
            if (UIntPtr.Zero == hIso15693InvenParam)
            {
                return;
            }

            RFIDLIB.rfidlib_aip_iso15693.ISO15693_SetInvenReadParam(hIso15693InvenParam, IsReadSecureStatusBytes, StartAddr, NumOfToReadBlocks);
            while (b_threadRun)
            {
                iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, AIType, AntennaSelCount, AntennaSel, m_hInvenParamSpecList);
                if (iret == 0)
                {
                    dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST);
                    while (dnhReport != UIntPtr.Zero)
                    {
                        Byte[] uid = new Byte[64];
                        Byte[] Data = new Byte[40];
                        UInt32 NumOfBlocks = 8;
                        UInt32 nSize = (UInt32)Data.Length;
                        iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseInventoryReadReport(dnhReport, uid, ref NumOfBlocks, Data, ref nSize);
                        if (0 == iret)
                        {
                            String strData  = "";
                            String strUID   = "";
                            strData = BitConverter.ToString(Data, 0, (int)nSize).Replace("-", string.Empty);
                            strUID  = BitConverter.ToString(uid, 0, 8).Replace("-", string.Empty);
                            this.Invoke((EventHandler)(delegate
                            {
                                bool bTagFind = false;
                                for (int j = 0; j < dataGridViewRecord.RowCount; j++)
                                {
                                    if (dataGridViewRecord[0, j].Value.ToString() == strUID)
                                    {
                                        int tagCnt = int.Parse(dataGridViewRecord[2, j].Value.ToString());
                                        tagCnt++;
                                        dataGridViewRecord[2, j].Value = tagCnt.ToString();
                                        bTagFind = true;
                                        break;
                                    }
                                }
                                if (!bTagFind)
                                {
                                    dataGridViewRecord.Rows.Add();
                                    dataGridViewRecord[0, dataGridViewRecord.RowCount - 1].Value = strUID;
                                    dataGridViewRecord[1, dataGridViewRecord.RowCount - 1].Value = strData;
                                    dataGridViewRecord[2, dataGridViewRecord.RowCount - 1].Value = "0";
                                }
                            }));
                        }
                        dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT);
                    }
                }
            }

            this.Invoke((EventHandler)(delegate
            {
                buttonClose.Enabled = true;
                buttonStartRecord.Enabled = true;
                buttonStopRecord.Enabled = false;
                buttonClose.Enabled = true;
                checkedListBoxAntennaList.Enabled = true;
                start_block.Enabled = true;
                comboBoxBlockNum.Enabled = true;
                checkBoxReadSecureSta.Enabled = true;
            }));
            RFIDLIB.rfidlib_reader.RDR_ResetCommuImmeTimeout(hreader);
            RFIDLIB.rfidlib_reader.DNODE_Destroy(m_hInvenParamSpecList);
        }

        private void buttonStopRecord_Click(object sender, EventArgs e)
        {
            RFIDLIB.rfidlib_reader.RDR_SetCommuImmeTimeout(hreader); 
            buttonStopRecord.Enabled    = false;
            b_threadRun                 = false ;
            start_block.Enabled = true;
            comboBoxBlockNum.Enabled   = true;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            UInt32 nCount;
            nCount = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();
            uint i;
            for( i=0;i<nCount;i++)
            {
                UInt32 nSize;
                CReaderDriverInf driver = new CReaderDriverInf();
                StringBuilder strCatalog = new StringBuilder();
                strCatalog.Append('\0', 64);
                
                nSize = (UInt32)strCatalog.Capacity;
                RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(i, RFIDLIB.rfidlib_def.LOADED_RDRDVR_OPT_CATALOG, strCatalog, ref nSize);
                driver.m_catalog = strCatalog.ToString();
                if (driver.m_catalog == RFIDLIB.rfidlib_def.RDRDVR_TYPE_READER) // Only reader we need
                {
                    StringBuilder strName = new StringBuilder();
                    strName.Append('\0', 64);
                    nSize = (UInt32)strName.Capacity;
                    RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(i, RFIDLIB.rfidlib_def.LOADED_RDRDVR_OPT_NAME, strName, ref nSize);
                    driver.m_name = strName.ToString();

                    StringBuilder strProductType = new StringBuilder();
                    strProductType.Append('\0', 64);
                    nSize = (UInt32)strProductType.Capacity;
                    RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(i, RFIDLIB.rfidlib_def.LOADED_RDRDVR_OPT_ID, strProductType, ref nSize);
                    driver.m_productType = strProductType.ToString();

                    StringBuilder strCommSupported = new StringBuilder();
                    strCommSupported.Append('\0', 64);
                    nSize = (UInt32)strCommSupported.Capacity;
                    RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(i, RFIDLIB.rfidlib_def.LOADED_RDRDVR_OPT_COMMTYPESUPPORTED, strCommSupported, ref nSize);
                    driver.m_commTypeSupported = (UInt32)int.Parse(strCommSupported.ToString());

                    readerDriverInfoList.Add(driver);

                    comboBoxReader.Items.Add(driver.m_name);
                }

            }
        }
    }

    public class CReaderDriverInf
    {
        public string m_catalog;
        public string m_name;
        public string m_productType;
        public UInt32 m_commTypeSupported;
    }
}