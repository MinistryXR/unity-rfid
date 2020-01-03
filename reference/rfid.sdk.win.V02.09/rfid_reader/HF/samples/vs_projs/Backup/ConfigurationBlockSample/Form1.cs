using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace ConfigurationBlockSample
{
    public partial class Form1 : Form
    {
        public UIntPtr hreader;
        public ArrayList readerDriverInfoList;
        public List<String> m_blueAddrList = new List<string>();
        public Form1()
        {
            InitializeComponent();
            hreader = (UIntPtr)0;
            readerDriverInfoList = new ArrayList();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //if (comboBox6.SelectedIndex == -1)
            //{
            //    MessageBox.Show("select reader driver type");
            //    return;
            //}
            if (comboBox10.SelectedIndex == -1)
            {
                MessageBox.Show("select communication type");
                return;
            }
            Byte usbOpenType = 0;
            usbOpenType = (Byte)comboBox8.SelectedIndex;


            //readerType = (Byte)comboBox6.SelectedIndex;

            int iret = 0;

            /*
             * Try to open communcation layer for specified reader 
             */
            int commTypeIdx = comboBox10.SelectedIndex;
            string readerDriverName = "M201";//((CReaderDriverInf)(readerDriverInfoList[readerType])).m_name;
            string connstr = "";
            // Build serial communication connection string
            if (commTypeIdx == 0)
            {
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME + "=" + comboBox1.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + comboBox14.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + comboBox15.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR + "=" + "255";
            }
            // Build USBHID communication connection string
            else if (commTypeIdx == 1)
            {
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE + "=" + usbOpenType.ToString() + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=" + comboBox9.Text;
            }
            // Build network communication connection string
            else if (commTypeIdx == 2)
            {
                string ipAddr;
                UInt16 port;
                ipAddr = textBox5.Text;
                port = (UInt16)int.Parse(textBox6.Text);
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_NET + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEIP + "=" + ipAddr + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEPORT + "=" + port.ToString() + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_LOCALIP + "=" + "";
            }
            // Build blueTooth communication connection string
            else if (commTypeIdx == 3)
            {
                if (txbBluetoothSN.Text == "")
                {
                    MessageBox.Show("The address of the bluetooth can not be null!");
                    return;
                }
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_BLUETOOTH + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_BLUETOOTH_SN + "=" + txbBluetoothSN.Text;
            }
            // Call required to open reader driver
            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                /*
                 *  Open fail:
                 *  if you Encounter this error ,make sure you has called the API "RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers")" 
                 *  when application load
                 */
                MessageBox.Show("fail");

            }
            else
            {
                button2.Enabled = false;
                button3.Enabled = true;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int iret = 0;

            /*
             *  Close reader driver ,this API is required
             */
            iret = RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            if (iret == 0)
            {
                hreader = (UIntPtr)0;
                button2.Enabled = true;
                button3.Enabled = false;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
            /* 
             *  Call required, when application load ,this API just only need to load once
             *  Load all reader driver dll from drivers directory, like "rfidlib_ANRD201.dll"  
             */
            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");

            /*
             * Not call required,it can be Omitted in your own appliation
             * enum and show loaded reader driver 
             */
            UInt32 nCount;
            nCount = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();
            uint i;
            for (i = 0; i < nCount; i++)
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
                }

            }
            //for (i = 0; i < readerDriverInfoList.Count; i++)
            //{
            //    CReaderDriverInf drv = (CReaderDriverInf)(readerDriverInfoList[(int)i]);
            //    comboBox6.Items.Add(drv.m_name);
            //}
            //if (comboBox6.Items.Count > 0) comboBox6.SelectedIndex = 0;


            /* 
             * Not call required,it can be Omitted in your own appliation
             * enum PC serial ports 
             */
            comboBox1.Items.Clear();
            UInt32 nCOMCnt = RFIDLIB.rfidlib_reader.COMPort_Enum();
            for (i = 0; i < nCOMCnt; i++)
            {
                StringBuilder comName = new StringBuilder();
                comName.Append('\0', 64);
                RFIDLIB.rfidlib_reader.COMPort_GetEnumItem(i, comName, (UInt32)comName.Capacity);
                comboBox1.Items.Add(comName);
            }
            if (comboBox1.Items.Count > 0) comboBox1.SelectedIndex = 0;
            comboBox1.Enabled = true;
            comboBox10.SelectedIndex = 0;


            /*
             * Not call required,it can be Omitted in your own appliation
             * enum matched bluetooth 
             */
            UInt32 nBluetooth = RFIDLIB.rfidlib_reader.Bluetooth_Enum();
            for (UInt32 j = 0; j < nBluetooth; j++)
            {
                StringBuilder nameBuf = new StringBuilder();
                StringBuilder addrBuf = new StringBuilder();
                UInt32 nSize = 256;
                nameBuf.Append('\0', (int)nSize);
                addrBuf.Append('\0', (int)nSize);
                RFIDLIB.rfidlib_reader.Bluetooth_GetEnumItem(j, 1, nameBuf, ref nSize);
                nSize = 256;
                RFIDLIB.rfidlib_reader.Bluetooth_GetEnumItem(j, 2, addrBuf, ref nSize);
                cbbBluetoothName.Items.Add(nameBuf);
                m_blueAddrList.Add(addrBuf.ToString());
            }
            if (cbbBluetoothName.Items.Count > 0)
            {
                cbbBluetoothName.SelectedIndex = 0;
            }
            int iret;
            nCount = RFIDLIB.rfidlib_reader.HID_Enum("M201");
            for (i = 0; i < nCount; i++)
            {
                StringBuilder sernum = new StringBuilder();
                sernum.Append('\0', 64);
                UInt32 nSize;
                nSize = (UInt32)sernum.Capacity;
                iret = RFIDLIB.rfidlib_reader.HID_GetEnumItem((UInt32)i, RFIDLIB.rfidlib_def.HID_ENUM_INF_TYPE_SERIALNUM, sernum, ref nSize);
                if (iret == 0)
                {
                    comboBox9.Items.Add(sernum.ToString());
                }
            }
            comboBox2.SelectedIndex = 0;
            comboBox8.Items.Add("None addressed");
            comboBox8.Items.Add("Serial number");
            comboBox8.SelectedIndex = 0;

        }

        private void button1_Click(object sender, EventArgs e)
        {
	        int iret ;
            Byte[] cfgblk = new byte[8];
	        Byte rfpower  ;

            iret = RFIDLIB.rfidlib_reader.RDR_ConfigBlockRead(hreader, 1, cfgblk, 8);
	        if(iret != 0) {
                MessageBox.Show("read fail");
                return;
	        }
	        rfpower =cfgblk[0] ;

            if (rfpower < comboBox2.Items.Count)
            {
                comboBox2.SelectedIndex = rfpower;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int iret;
            byte powerVal;
            byte[] cfgblk = new byte[8];
            if (comboBox2.SelectedIndex == -1)
            {
	            MessageBox.Show("select rf power please") ;
	            return ;
            }
            powerVal = (byte)comboBox2.SelectedIndex;
       
            iret= RFIDLIB.rfidlib_reader.RDR_ConfigBlockRead(hreader,1,cfgblk,8) ;
            if(iret != 0) {
                MessageBox.Show("read fail");
	            return ;
            }
            cfgblk[0]= powerVal ;
            iret = RFIDLIB.rfidlib_reader.RDR_ConfigBlockWrite(hreader, 1, cfgblk, 8, 0);
            if(iret != 0)
            {
                MessageBox.Show("write fail");
	            return ;
            }
            MessageBox.Show("write ok");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_ConfigBlockSave(hreader, 1);
            if (iret != 0)
            {
                MessageBox.Show("save fail");
                return;
            }
            MessageBox.Show("Save ok");
        }

        private void groupBox4_Enter(object sender, EventArgs e)
        {

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