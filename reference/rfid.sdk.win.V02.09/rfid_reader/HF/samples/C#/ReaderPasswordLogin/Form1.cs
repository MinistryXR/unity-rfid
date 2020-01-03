using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace ReaderPasswordLogin
{
    public partial class Form1 : Form
    {
        public class CReaderDriverInf
        {
            public string m_catalog;
            public string m_name;
            public string m_productType;
            public UInt32 m_commTypeSupported;
        }
        public Byte readerType;
        public UIntPtr hreader;
        public ArrayList readerDriverInfoList;
        public List<String> m_blueAddrList = new List<string>();
        public Form1()
        {
            InitializeComponent();
            readerDriverInfoList = new ArrayList();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
            /* Load all reader driver dll, like "rfidlib_ANRD201.dll" */
            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
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

            for (i = 0; i < readerDriverInfoList.Count; i++)
            {
                CReaderDriverInf drv = (CReaderDriverInf)(readerDriverInfoList[(int)i]);
                comboBox6.Items.Add(drv.m_name);
            }
            if (comboBox6.Items.Count > 0) comboBox6.SelectedIndex = 0;

            /* enum PC serial ports */
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

            button1.Enabled = false;
            button2.Enabled = false;
            button3.Enabled = false;
            button4.Enabled = false;

            comboBox8.Items.Add("None addressed");
            comboBox8.Items.Add("Serial number");
            comboBox8.SelectedIndex = 0;

            comboBox14.SelectedIndex = 2;
            comboBox15.SelectedIndex = 0;


        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (comboBox6.SelectedIndex == -1)
            {
                MessageBox.Show("select reader driver type");
                return;
            }
            if (comboBox10.SelectedIndex == -1)
            {
                MessageBox.Show("select communication type");
                return;
            }
            Byte usbOpenType = 0;
            usbOpenType = (Byte)comboBox8.SelectedIndex;


            readerType = (Byte)comboBox6.SelectedIndex;

            int iret = 0;
 

            // Use new way to open reader driver
            int commTypeIdx = comboBox10.SelectedIndex;
            string readerDriverName = ((CReaderDriverInf)(readerDriverInfoList[readerType])).m_name;
            string connstr = "";
            if (commTypeIdx == 0)
            {  //Serial
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME + "=" + comboBox1.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + comboBox14.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + comboBox15.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR + "=" + "255";
            }
            else if (commTypeIdx == 1)
            { //USBHID
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE + "=" + usbOpenType.ToString() + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=" + comboBox9.Text;
            }
            else if (commTypeIdx == 2)
            { //TCP
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
            else if (commTypeIdx == 3)//BlueTooth
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

            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("fail");
              
                button2.Enabled = true;
            }
            else
            {

                //MessageBox.Show("ok");
                button6.Enabled = false;
      
                button3.Enabled = true;
                button4.Enabled = true;
                button5.Enabled = true;

                button1.Enabled = true;
                button2.Enabled = true;
                button3.Enabled = true;
                button4.Enabled = true;

            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            int iret = 0;

            iret = RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            if (iret == 0)
            {
                hreader = (UIntPtr)0;
                //MessageBox.Show("ok");

                button3.Enabled = false;
                button4.Enabled = false;
                button5.Enabled = false;



                button1.Enabled = false;
                button2.Enabled = false;
                button3.Enabled = false;
                button4.Enabled = false;
                button6.Enabled = true;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int iret;

            byte[] pwd = StringToByteArrayFastest(textBox1.Text );
            if (pwd.Length != 8)
            {
                MessageBox.Show("password format invalid");
                return;
            }

            iret = RFIDLIB.rfidlib_reader.RDR_Login(hreader, pwd);
            if (iret == 0)
            {
                MessageBox.Show("ok ");
            }
            else
            {
                MessageBox.Show("fail ");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int iret;

            byte[] pwd = StringToByteArrayFastest(textBox1.Text);
            if (pwd.Length != 8)
            {
                MessageBox.Show("password format invalid");
                return;
            }

            iret = RFIDLIB.rfidlib_reader.RDR_EnablePasswordLogin(hreader, pwd,1);
            if (iret == 0)
            {
                MessageBox.Show("ok ");
            }
            else
            {
                MessageBox.Show("fail ");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int iret;

            byte[] pwd = StringToByteArrayFastest(textBox1.Text);
            if (pwd.Length != 8)
            {
                MessageBox.Show("password format invalid");
                return;
            }

            iret = RFIDLIB.rfidlib_reader.RDR_EnablePasswordLogin(hreader, pwd, 0);
            if (iret == 0)
            {
                MessageBox.Show("ok ");
            }
            else
            {
                MessageBox.Show("fail ");
            }
        }
        public static byte[] StringToByteArrayFastest(string hex)
        {
            if (hex.Length % 2 == 1)
                throw new Exception("The binary key cannot have an odd number of digits");

            int len = hex.Length >> 1;
            byte[] arr = new byte[len];

            for (int i = 0; i < len; ++i)
            {
                arr[i] = (byte)((GetHexVal(hex[i << 1]) << 4) + (GetHexVal(hex[(i << 1) + 1])));
            }

            return arr;
        }

        public static int GetHexVal(char hex)
        {
            int val = (int)hex;
            //For uppercase A-F letters:
            // return val - (val < 58 ? 48 : 55);
            //For lowercase a-f letters:
            //return val - (val < 58 ? 48 : 87);
            //Or the two combined, but a bit slower:
            return val - (val < 58 ? 48 : (val < 97 ? 55 : 87));
        }
        private void button4_Click(object sender, EventArgs e)
        {
            int iret;

            byte[] pwd = StringToByteArrayFastest(textBox1.Text);
            if (pwd.Length != 8)
            {
                MessageBox.Show("password format invalid");
                return;
            }

            byte[] newPwd = StringToByteArrayFastest(textBox2.Text);
            if (newPwd.Length != 8)
            {
                MessageBox.Show("password format invalid");
                return;
            }

            iret = RFIDLIB.rfidlib_reader.RDR_UpdateLoginPassword(hreader, pwd, newPwd);
            if (iret == 0)
            {
                MessageBox.Show("ok ");
            }
            else
            {
                MessageBox.Show("fail ");
            }
        }

        private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
        {
            CReaderDriverInf driver = (CReaderDriverInf)readerDriverInfoList[comboBox6.SelectedIndex];

            if ((driver.m_commTypeSupported & RFIDLIB.rfidlib_def.COMMTYPE_USB_EN) > 0)
            {
                comboBox9.Items.Clear();
                UInt32 nCount = RFIDLIB.rfidlib_reader.HID_Enum(driver.m_name);
                int iret;
                int i;
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
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            int iret;
            StringBuilder devInfor = new StringBuilder();
            devInfor.Append('\0', 128);
            UInt32 nSize;
            nSize = (UInt32)devInfor.Capacity;
            iret = RFIDLIB.rfidlib_reader.RDR_GetReaderInfor(hreader, 0, devInfor, ref nSize);
            if (iret == 0)
            {
                MessageBox.Show(devInfor.ToString());
            }
            else
            {
                MessageBox.Show("fail");
            }
        }
    }
}