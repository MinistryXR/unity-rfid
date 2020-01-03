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
        List<String> m_blueAddrList = new List<string>();
        public ArrayList readerDriverInfoList;
        public Form1()
        {
            InitializeComponent();

            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");

            //string[] strCom = SerialPort.GetPortNames();
            //foreach (string s in strCom)
            //{
            //    comboBoxCOM.Items.Add(s);
            //}
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

            //枚举已经配对的蓝牙设备
            UInt32 nBluetooth = RFIDLIB.rfidlib_reader.Bluetooth_Enum();
            for (UInt32 j = 0; j < nBluetooth; j++)
            {
                StringBuilder nameBuf = new StringBuilder();
                StringBuilder addrBuf = new StringBuilder();
                UInt32 nSize = 256;
                nameBuf.Append('\0', (int)nSize);
                addrBuf.Append('\0',(int) nSize);
                RFIDLIB.rfidlib_reader.Bluetooth_GetEnumItem(j, 1, nameBuf, ref nSize);
                nSize = 256;
                RFIDLIB.rfidlib_reader.Bluetooth_GetEnumItem(j, 2, addrBuf, ref nSize);
               
                m_blueAddrList.Add(addrBuf.ToString());
            }

            buttonOpen.Enabled = true;
            buttonClose.Enabled = false;
            comboBoxCOM.Enabled = true;
            comboBoxBaud.Enabled = true;
            comboBoxFrame.Enabled = true;
            buttonStartRecord.Enabled = false;
            buttonStopRecord.Enabled = false;
            buttonClearRecord.Enabled = false;

            readerDriverInfoList = new ArrayList();

            comboBoxCOM.SelectedIndex = comboBoxCOM.Items.Count - 1;
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            int iret = 0;

            string readerDriverName = "RD5100";
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

            buttonOpen.Enabled          = false;
            buttonClose.Enabled         = true;
            comboBoxCOM.Enabled         = false;
            comboBoxBaud.Enabled        = false;
            comboBoxFrame.Enabled       = false;
            buttonStartRecord.Enabled   = true;
            buttonStopRecord.Enabled    = false;
            buttonClearRecord.Enabled   = true;
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

            buttonOpen.Enabled = true;
            buttonClose.Enabled = false;
            comboBoxCOM.Enabled = true;
            comboBoxBaud.Enabled = true;
            comboBoxFrame.Enabled = true;
            buttonStartRecord.Enabled = false;
            buttonStopRecord.Enabled = false;
            buttonClearRecord.Enabled = false;
        }

        private void buttonSetTime_Click(object sender, EventArgs e)
        {
            DateTime curTime = DateTime.Now;
            int iret = RFIDLIB.rfidlib_reader.RDR_SetSystemTime(hreader, (UInt32)curTime.Year, (Byte)curTime.Month, (Byte)curTime.Day, (Byte)curTime.Hour, (Byte)curTime.Minute, (Byte)curTime.Second);
            if (iret == 0)
            {
                MessageBox.Show("Set system'time successfully!");
            }
            else
            {
                MessageBox.Show("Failure to set system'time!");
            }
        }

        private void buttonClearRecord_Click(object sender, EventArgs e)
        {
            int iret = RFIDLIB.rfidlib_reader.RDR_BuffMode_ClearRecords(hreader);
            if (iret == 0)
            {
                MessageBox.Show("Clear record successfully!");
            }
            else
            {
                MessageBox.Show("Failure to clear record!");
            }
        }

        private delegate void delegate_addRecord(string recordData);
        private void addRecord(string recordData)
        {
            dataGridViewRecord.Rows.Add();
            dataGridViewRecord[0, dataGridViewRecord.RowCount - 1].Value = recordData;
        }

        private void buttonStartRecord_Click(object sender, EventArgs e)
        {
            buttonClose.Enabled         = false;
            buttonStartRecord.Enabled   = false;
            buttonClearRecord.Enabled   = false;
            buttonStopRecord.Enabled    = true;

            dataGridViewRecord.Rows.Clear();
            m_thread = new Thread(GetRecordPro);
            m_thread.Start();
        }


        private void GetRecordPro()
        {
            int iret            = 0;
            UIntPtr dnhReport   = UIntPtr.Zero;
            b_threadRun         = true;
            byte AIType         = RFIDLIB.rfidlib_def.AI_TYPE_NEW;
            byte[] AntID        = new byte[16];

            UIntPtr m_hInvenParamSpecList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
            if (UIntPtr.Zero == m_hInvenParamSpecList) return;

            UIntPtr hIso15693InvenParam = RFIDLIB.rfidlib_aip_iso15693.ISO15693_CreateInvenParam(m_hInvenParamSpecList, 0, 0, 0, 0);
            if (UIntPtr.Zero == hIso15693InvenParam) return;

            RFIDLIB.rfidlib_aip_iso15693.ISO15693_SetInvenReadParam(hIso15693InvenParam, 0, 0, 8);

            while (b_threadRun)
            {
LABEL_TAG_INVENTORY:
                iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, AIType, 0, AntID, m_hInvenParamSpecList);
                if (iret == 0 || iret == -21)
                {
                    // Get records from dll buffer memory
                    dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST);
                    while (dnhReport != UIntPtr.Zero)
                    {
                        Byte[] uid          = new Byte[64];
                        Byte[] Data         = new Byte[40];
                        UInt32 NumOfBlocks  = 8;
                        UInt32 Size         = (UInt32)Data.Length;

                        iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseInventoryReadReport(dnhReport, uid, ref NumOfBlocks, Data, ref Size);

                        if (0 == iret)
                        {
                            //if (len > 0)
                           // {
                           //     strData = BitConverter.ToString(byData, 0, (int)len).Replace("-", string.Empty);
                           //     Invoke(new delegate_addRecord(addRecord), strData);
                           // }
                        }
                        dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT);
                    }
                }

                if (iret == -21) // stop trigger occur,need to inventory left tags
                {
                    AIType = RFIDLIB.rfidlib_def.AI_TYPE_CONTINUE;//use only-new-tag inventory 
                    goto LABEL_TAG_INVENTORY;
                }
            }
            Invoke(new delegate_stopThreadPro(stopThreadPro));

            /*
             *  If API RDR_SetCommuImmeTimeout is called when stop, API RDR_ResetCommuImmeTimeout 
             *  must be called too, Otherwise, an error -5 may occurs .
             */
            RFIDLIB.rfidlib_reader.RDR_ResetCommuImmeTimeout(hreader);

            RFIDLIB.rfidlib_reader.DNODE_Destroy(m_hInvenParamSpecList);
        }

        private void buttonStopRecord_Click(object sender, EventArgs e)
        {
            buttonStopRecord.Enabled    = false;
            b_threadRun                 = false ;
            /*
             * Exit the inventory quickly
             */
            RFIDLIB.rfidlib_reader.RDR_SetCommuImmeTimeout(hreader); 

        }

        private delegate void delegate_stopThreadPro();
        private void stopThreadPro()
        {

            buttonClose.Enabled         = true;
            buttonStartRecord.Enabled   = true;
            buttonClearRecord.Enabled   = true;
            buttonStopRecord.Enabled    = false;

         }

        private void Form1_Load(object sender, EventArgs e)
        {
            UInt32 nCount;
            nCount = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();
            uint i;
            for( i=0;i<nCount;i++){
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