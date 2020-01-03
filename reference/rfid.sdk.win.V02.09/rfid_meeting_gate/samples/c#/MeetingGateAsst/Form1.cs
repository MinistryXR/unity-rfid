using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Collections;

namespace csharp_demo
{
   
    public partial class Form1 : Form
    {
        public UIntPtr handle ;
        public ArrayList readerDriverInfoList;
        RFIDLIB.RFID_EVENT_CALLBACK_NEW delegateCBReportGetted;
        RFIDLIB.RFID_EVENT_CALLBACK_NEW delegateCBErrorOcurr;
        RFIDLIB.RFID_EVENT_CALLBACK_NEW delegateCollectExit;
        public Form1()
        {
            InitializeComponent();
            handle =(UIntPtr) 0;

            delegateCBReportGetted = new RFIDLIB.RFID_EVENT_CALLBACK_NEW(OnCBReportGetted);
            delegateCBErrorOcurr = new RFIDLIB.RFID_EVENT_CALLBACK_NEW(OnCBErrorOcurr);
            delegateCollectExit = new RFIDLIB.RFID_EVENT_CALLBACK_NEW(OnCBCollectExit);
            readerDriverInfoList = new ArrayList();

            comboBox6.SelectedIndex = 0;

            comboBox3.SelectedIndex = 1;
            comboBox4.SelectedIndex = 0;
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string str = comboBox2.Text;
            string connstr = "";
            int iret=0;
          
            if (str=="COM")
            {
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + comboBox8.Text + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME + "=" + comboBox1.Text + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + comboBox3.Text + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + comboBox4.Text + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR + "=" + "255";
            }
            else if (str=="TCP/IP")
            {
                string ipAddr;
                ipAddr = textBox3.Text;
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + comboBox8.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_NET + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEIP + "=" + ipAddr + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEPORT + "=" + "6012" + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_LOCALIP + "=" + "";
            }
            else
            {
                MessageBox.Show("Failed");
                return;
            }
            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref handle);
            if (iret == 0)
            {
                checkedListBox1.Items.Clear();
                checkedListBox1.Items.Add("Buzzer on board");
                checkedListBox1.Items.Add("Output port#1");
                checkedListBox1.Items.Add("Output port#2");
                checkedListBox1.Items.Add("Output port#3");
                checkedListBox1.Items.Add("Output port#4");

                textBox1.Enabled = true;
                comboBox6.Enabled = true;
                textBox2.Enabled = true;

                button1.Enabled = false ;
                button2.Enabled = true;
                button3.Enabled = true;
   
                button10.Enabled = true;
                button12.Enabled = true;
                
            }
            else
            {
                MessageBox.Show("Open failed,error:" + iret.ToString());
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_Close(handle);
            if(iret ==0)
            {
                button1.Enabled = true;
                button2.Enabled = false;
                button3.Enabled = false;
            
                button10.Enabled = false;
                button11.Enabled = false;
                button12.Enabled = false;
             
            }
            else 
            {
                MessageBox.Show("Close failed,error:" + iret.ToString());
            }
            handle = (UIntPtr)0;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int iret;
            StringBuilder devInfor = new StringBuilder();
            devInfor.Append('\0', 128);
            UInt32 nSize ;
            nSize =(UInt32) devInfor.Capacity ;
            iret = RFIDLIB.rfidlib_reader.RDR_GetReaderInfor(handle,0, devInfor, ref nSize);
            if (iret == 0)
            {
                MessageBox.Show(devInfor.ToString());
            }
            else
            {
                MessageBox.Show("Failed,error:" + iret.ToString());
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
          
        }

        private void button4_Click(object sender, EventArgs e)
        {
          
        }

        private void button6_Click(object sender, EventArgs e)
        {
         
        }

        private void button8_Click(object sender, EventArgs e)
        {
          
        }

        private void button7_Click(object sender, EventArgs e)
        {
          
        }

        private void button9_Click(object sender, EventArgs e)
        {
           
        }
     
 
        private void button10_Click(object sender, EventArgs e)
        {
            //_shouldStop = false;
            button10.Enabled = false;
            button11.Enabled = true;

            button2.Enabled = false;
            button3.Enabled = false;
         
            button10.Enabled = false;
            button12.Enabled = false;
 
	        /*
	        *  报告获取成功事件
	        *  使用回调函数同步方式返回
	        */
            RFIDLIB.rfidlib_reader.RDR_SetEventHandler(handle, 1, 2, 0, UIntPtr.Zero, delegateCBReportGetted, UIntPtr.Zero);
            /*
            *  获取报告失败事件
            *  使用回调函数同步方式返回
            */
            RFIDLIB.rfidlib_reader.RDR_SetEventHandler(handle, 2, 2, 0, UIntPtr.Zero, delegateCBErrorOcurr, UIntPtr.Zero);
	        /*
	        * 采集线程退出事件
	        * 需要调用MGXXX_StopLoopCollectingBegin 使线程退出，使用回调函数同步方式返回，但在回调函数里面需要使用异步回调。
	        */
            RFIDLIB.rfidlib_reader.RDR_SetEventHandler(handle, 3, 2, 0, UIntPtr.Zero, delegateCollectExit, UIntPtr.Zero);
            RFIDLIB.rfidlib_reader.RDR_BuffMode_StartReportCollection(handle);

        }

        private delegate void delegateLogGetReportError(string err);
        public void LogGetReportError(string err)
        {
            richTextBox1.AppendText(err);
        }


        private delegate void delegateAddNewReport(string uid,string dir,string insteadsta);
        public void AddNewReport(string uid, string dir, string insteadsta)
        {
            ListViewItem lvi = new ListViewItem();
          
            lvi.Text = uid;
            lvi.SubItems.Add(dir);
            lvi.SubItems.Add(insteadsta);
            listView1.Items.Add(lvi);

            string serialnum;
            serialnum = uid.Substring(0, 16);
            if (serialnum == "FFFFFFFFFFFFFFFF")
            {
                // 有人员触发红外检测，但没带卡片，报警
                UIntPtr dnOutputOper = RFIDLIB.rfidlib_reader.RDR_CreateSetOutputOperations();
                if (dnOutputOper != UIntPtr.Zero)
                {
                    //添加输出端口，根据需要修改
                    RFIDLIB.rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper, 1, 3, 1, 1, 1);

                    RFIDLIB.rfidlib_reader.RDR_SetOutput(handle, dnOutputOper);
                    RFIDLIB.rfidlib_reader.DNODE_Destroy(dnOutputOper);
                }
            }
        }


        private void button11_Click(object sender, EventArgs e)
        {
            button11.Enabled = false;
            RFIDLIB.rfidlib_reader.RDR_BuffMode_StopReportCollectionNoWait(handle);
        }

        private void label14_Click(object sender, EventArgs e)
        {

        }

        private void label13_Click(object sender, EventArgs e)
        {

        }

        private void button12_Click(object sender, EventArgs e)
        {
            int iret = 0;
            Byte outputSel =0 ;
           
            if(textBox1.Text == "" )
            {
                MessageBox.Show("Please input active time!");
                return;
            }
            int idx ;
            idx = comboBox6.SelectedIndex ;
            if(idx == -1)
            {
                MessageBox.Show("Please choose a frequency!");
                return ;
            }
            if(textBox2.Text =="")
            {
                MessageBox.Show("Please input stop time!");
                return ;
            }

            Byte activeDuration  =(Byte)(( int.Parse(textBox1.Text) ) & 0xff) ;
            Byte number =(Byte)(idx+1) ;
            Byte pauseDuration =(Byte)( (int.Parse(textBox2.Text)) & 0xff );
            UIntPtr dnOutputOper = RFIDLIB.rfidlib_reader.RDR_CreateSetOutputOperations();
            for (int i = 0; i < checkedListBox1.Items.Count; i++)
            {
                if (checkedListBox1.GetItemChecked(i))
                {
                    RFIDLIB.rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper,(Byte) (i + 1), 3, number,(UInt32)( activeDuration * 100), (UInt32)(pauseDuration * 100));
                }
            }
            iret = RFIDLIB.rfidlib_reader.RDR_SetOutput(handle, dnOutputOper);
            RFIDLIB.rfidlib_reader.DNODE_Destroy(dnOutputOper);
            if (iret == 0)
            {
                MessageBox.Show("Success");
            }
            else
            {
                MessageBox.Show("Failed,error:" + iret.ToString());
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (button1.Enabled == false)
            {
                MessageBox.Show("Please close device first!");
                button2.Focus();
                e.Cancel = true; 
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            Array.Sort(ports);
            comboBox1.Items.Clear();
            foreach (string s in ports)
            {
                comboBox1.Items.Add(s);
            }

            if(comboBox1.Items.Count > 0) comboBox1.SelectedIndex = 0;

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
                if (driver.m_catalog == RFIDLIB.rfidlib_def.RDRDVR_TYPE_MTGATE) // Only reader we need
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
                comboBox8.Items.Add(drv.m_name);
            }
            if (comboBox8.Items.Count > 0) comboBox8.SelectedIndex = 0;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            listView1.Items.Clear();
        }

        private void button14_Click(object sender, EventArgs e)
        {

        }

        private void button15_Click(object sender, EventArgs e)
        {
          
        }

        private void button16_Click(object sender, EventArgs e)
        {
           
        }

        private void tabPage3_Click(object sender, EventArgs e)
        {

        }

        private void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
        {
            comboBox2.Items.Clear();
            UInt32 m_commTypeSupported = ((CReaderDriverInf)(readerDriverInfoList[comboBox8.SelectedIndex])).m_commTypeSupported;
            if ((m_commTypeSupported & RFIDLIB.rfidlib_def.COMMTYPE_COM_EN) > 0)
            {
                comboBox2.Items.Add("COM");
            }
            if ((m_commTypeSupported & RFIDLIB.rfidlib_def.COMMTYPE_NET_EN) > 0)
            {
                comboBox2.Items.Add("TCP/IP");
            }
            comboBox2.SelectedIndex = 0;

        }

        private void button18_Click(object sender, EventArgs e)
        {
        
        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void button17_Click(object sender, EventArgs e)
        {
         
        }

        private void button14_Click_1(object sender, EventArgs e)
        {
          
        }

        private void label28_Click(object sender, EventArgs e)
        {

        }

        private void button19_Click(object sender, EventArgs e)
        {
          

        }

        private void button20_Click(object sender, EventArgs e)
        {
          
        }

        private void button23_Click(object sender, EventArgs e)
        {
          

        }

        private void button24_Click(object sender, EventArgs e)
        {
           
        }

        private void button21_Click(object sender, EventArgs e)
        {
          
        }

        private void button22_Click(object sender, EventArgs e)
        {
         
        }

        private void button25_Click(object sender, EventArgs e)
        {
         
        }

        private void groupBox11_Enter(object sender, EventArgs e)
        {

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
            return val - (val < 58 ? 48 : 55);
            //For lowercase a-f letters:
            //return val - (val < 58 ? 48 : 87);
            //Or the two combined, but a bit slower:
            //return val - (val < 58 ? 48 : (val < 97 ? 55 : 87));
        }
        private void button26_Click(object sender, EventArgs e)
        {
           
        }

        private void button27_Click(object sender, EventArgs e)
        {
       
        }

        private void button29_Click(object sender, EventArgs e)
        {
          
        }

        private void button28_Click(object sender, EventArgs e)
        {
            
        }

        private void button30_Click(object sender, EventArgs e)
        {
           
        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private delegate void delegateAsyncCollectExit();
        public void OnAsyncCollectExit()
        {
            /* 等待采集线程退出 */
            RFIDLIB.rfidlib_reader.RDR_BuffMode_StopReportCollection(handle);
        }
        private void AsyncCollectExitMethodCompleted(IAsyncResult asyncResult)
        {

            object[] pList = { };
            Invoke(new delegateInventoryFinishCallback(StopFinishCallback), pList);
        }
        public void OnCBCollectExit(UIntPtr inParam, UIntPtr wparam, UIntPtr lparam)
        {
            //使用异步回调
            delegateAsyncCollectExit cb = OnAsyncCollectExit;
            IAsyncResult asyncResult = cb.BeginInvoke(AsyncCollectExitMethodCompleted, cb);
        }
        public void OnCBErrorOcurr(UIntPtr inParam, UIntPtr wparam, UIntPtr lparam)
        {
            string str1;

            if (UIntPtr.Size == 4)
            {
                //32 bit
                int err = (int)lparam;
                str1 = "Get report failed:" + err.ToString() + "\n";
            }
            else
            {
                //64 bit
                long err = (long)lparam;
                str1 = "Get report failed:" + err.ToString() + "\n";
            }
            object[] logList = { str1 };
            Invoke(new delegateLogGetReportError(LogGetReportError), logList);

        }
        public void OnCBReportGetted(UIntPtr inParam, UIntPtr wparam, UIntPtr lparam)
        {
            int iret=0;
            UIntPtr dnhReport;
            dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(handle, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST);
            while (dnhReport !=UIntPtr.Zero)
            {
                string insteadsta;
                string strdir;
                //StringBuilder uid = new StringBuilder();
                //UInt32 nSize;
                //byte direction = 0;
                //byte[] time = new byte[6];
                //uid.Append('\0', 128);
                //nSize = (UInt32)uid.Capacity  ;
                //iret = RFIDLIB.rfidlib_Gxxx.MGXXX_ParseIOReportData(handle, dnhReport, uid, nSize, ref direction, time);
                Byte[] reportBuffer = new Byte[64] ;
                UInt32  nSize  =(UInt32) reportBuffer.Length  ;
                iret = RFIDLIB.rfidlib_reader.RDR_ParseTagDataReportRaw(dnhReport, reportBuffer, ref nSize);
                if (iret == 0)
                {
                    if (nSize < 9) goto next_report;
                    Byte eventType;
                    Byte direction;
                    Byte[] time = new Byte[6];
                    Byte dataLen;

                    eventType = reportBuffer[0];
                    direction = reportBuffer[1];
                    for (int i = 0; i < 6; i++)
                    {
                        time[i] = reportBuffer[2 + i];
                    }
                    dataLen = reportBuffer[8];

                    nSize -= 9;
                    if (nSize < dataLen) goto next_report;
 
                    //Byte[] datas = new Byte[dataLen];
                    //for (int i = 0; i < dataLen; i++)
                    //{
                    //    datas
                    //}
                    //reportBuffer.CopyTo(datas, 9);

                    String strData = BitConverter.ToString(reportBuffer, 9, (int)dataLen).Replace("-", string.Empty);

                    insteadsta = "";
                    Byte insteedCheckingFlag = (Byte)(direction >> 7 & 0x01);
                    if (insteedCheckingFlag > 0)
                    {
                        insteadsta = "Yes";
                    }
                    direction = (Byte)(direction & 0x7F);
                    strdir = "Wrong direction";
                    switch (direction)
                    {
                        case 0:
                            strdir = "NULL";
                            break;
                        case 1:
                            strdir = "In";
                            break;
                        case 2:
                            strdir = "Out";
                            break;
                    }

                    object[] pList1 = { strData, strdir, insteadsta };
                    Invoke(new delegateAddNewReport(AddNewReport), pList1);
                }
            next_report:
                dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(handle, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT);
            }
        }
        private delegate void delegateInventoryFinishCallback();
        public void StopFinishCallback()
        {
            button11.Enabled = false;
            button10.Enabled = true;
            button2.Enabled = true;
            button3.Enabled = true;

            button10.Enabled = true;
            button12.Enabled = true;
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string str = comboBox2.Text;
            if (str=="COM")
            {
                comboBox1.Enabled = true;
                textBox3.Enabled = false;
                comboBox3.Enabled = true;
                comboBox4.Enabled = true;
            }
            else if (str=="TCP/IP")
            {
                comboBox1.Enabled = false;
                textBox3.Enabled = true;
                comboBox3.Enabled = false;
                comboBox4.Enabled = false;
            }
            else
            {

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