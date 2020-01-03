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
            buttonInventory.Enabled = false;
            buttonStopInventory.Enabled = false;

            readerDriverInfoList = new ArrayList();
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            int iret = 0;
            string readerDriverName = "RPAN";
            string connstr = "";
            connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME + "=" + comboBoxCOM.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + comboBoxBaud.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + comboBoxFrame.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR + "=" + "255";

            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("Open reader failed!");
                return;
            }
            buttonOpen.Enabled = false;
            buttonClose.Enabled = true;
            comboBoxCOM.Enabled = false;
            comboBoxBaud.Enabled = false;
            comboBoxFrame.Enabled = false;
            buttonInventory.Enabled = true;
            buttonStopInventory.Enabled = false;
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
            buttonInventory.Enabled = false;
            buttonStopInventory.Enabled = false;
        }

     

        private delegate void delegate_addRecord(string recordData);
        private void addRecord(string recordData)
        {
            dataGridViewRecord.Rows.Add();
            dataGridViewRecord[0, dataGridViewRecord.RowCount - 1].Value = recordData;
        }

        private void buttonStartRecord_Click(object sender, EventArgs e)
        {
            buttonClose.Enabled = false;
            buttonInventory.Enabled = false;
            buttonStopInventory.Enabled = true;

            dataGridViewRecord.Rows.Clear();
            m_thread = new Thread(GetRecordPro);
            m_thread.Start();
        }


        private void GetRecordPro()
        {
            int iret = 0;
            Byte gFlg = 0x00;//
            UIntPtr dnhReport = UIntPtr.Zero;
            b_threadRun = true;
            while (b_threadRun)
            {
                iret = RFIDLIB.rfidlib_reader.RDR_BuffMode_FetchRecords(hreader, gFlg); // send command to device
                if (iret != 0)
                {
                    gFlg = 0x00;  // if fail ,try to get again.
                    continue;
                }

                // Get records from dll buffer memory
                dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST);
                while (dnhReport != UIntPtr.Zero)
                {
                    string strData = "";
                    Byte[] byData = new Byte[32];
                    UInt32 len = (UInt32)byData.Length;
                    if (RFIDLIB.rfidlib_reader.RDR_ParseTagDataReportRaw(dnhReport, byData, ref len) == 0)
                    {
                        if (len > 0)
                        {
                            strData = BitConverter.ToString(byData, 0, (int)len).Replace("-", string.Empty);
                            Invoke(new delegate_addRecord(addRecord), strData);
                        }
                    }
                    dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT);

                }
               gFlg = 0x01;  // if received ok ,get next records from device
               
            }

            Invoke(new delegate_stopThreadPro(stopThreadPro));

            /*
             *  If API RDR_SetCommuImmeTimeout is called when stop, API RDR_ResetCommuImmeTimeout 
             *  must be called too, Otherwise, an error -5 may occurs .
             */
            RFIDLIB.rfidlib_reader.RDR_ResetCommuImmeTimeout(hreader);
        }

        private void buttonStopRecord_Click(object sender, EventArgs e)
        {
            buttonStopInventory.Enabled = false;
            b_threadRun = false ;
            /*
             * Exit the inventory quickly
             */
            RFIDLIB.rfidlib_reader.RDR_SetCommuImmeTimeout(hreader); 

        }

        private delegate void delegate_stopThreadPro();
        private void stopThreadPro()
        {

            buttonClose.Enabled = true;
            buttonInventory.Enabled = true;
            buttonStopInventory.Enabled = false;

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
            for(i=0;i<readerDriverInfoList.Count;i++)
            {
                CReaderDriverInf drv = (CReaderDriverInf)(readerDriverInfoList[(int)i]);
                comboBox1.Items.Add(drv.m_name);
            }
            if (comboBox1.Items.Count > 0) comboBox1.SelectedIndex = 0;
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