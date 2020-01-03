using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace LSG_Csharp_demo
{
    public partial class Form1 : Form
    {
        public UIntPtr hreader;
        Thread thrdGetEvent;
        int exit_flag;
        public Form1()
        {
            InitializeComponent();

            hreader = UIntPtr.Zero;
            
        }


        private void button2_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            if (iret != 0)
            {
                MessageBox.Show("Failure to close device,error:"+iret.ToString());
                return;
            }
            button1.Enabled = true ;
            button2.Enabled = false;
            button3.Enabled = false;
            button4.Enabled = false;
            button5.Enabled = false;
            button6.Enabled = false;
            button7.Enabled = false;
            button8.Enabled = false;
            button9.Enabled = false;
            button10.Enabled = false;
            button11.Enabled = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");

            button1.Enabled = true;
            button2.Enabled = false;
            button3.Enabled = false;
            button4.Enabled = false;
            button5.Enabled = false;
            button6.Enabled = false;
            button7.Enabled = false;
            button8.Enabled = false;
            button9.Enabled = false;
            button10.Enabled = false;
            button11.Enabled = false;

        
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int iret;
            StringBuilder sbDevInfBu= new StringBuilder() ;
            sbDevInfBu.Append('\0',128) ;
            UInt32 nSize =(UInt32) sbDevInfBu.Capacity  ;
            iret = RFIDLIB.rfidlib_reader.RDR_GetReaderInfor(hreader,0, sbDevInfBu, ref nSize);
            if (iret != 0)
            {
                MessageBox.Show("Failure to get device information,error:"+iret.ToString());
                return;
            }
            MessageBox.Show(sbDevInfBu.ToString());
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int iret=0;
            UInt32 inFlow, outFlow;
            inFlow = outFlow = 0;
            //iret = RFIDLIB.rfidlib_LSGate.LSG_CmdGetCurrentFlowOfPeople(hreader,ref inFlow, ref outFlow);
            iret = RFIDLIB.rfidlib_reader.RDR_GetPassingCounter(hreader, ref inFlow, ref outFlow);
            if (iret != 0)
            {
                MessageBox.Show("Failure to get flow of people,error:"+iret.ToString());
                return;
            }
            label2.Text = inFlow.ToString();
            label3.Text = outFlow.ToString();

        }

        private void button5_Click(object sender, EventArgs e)
        {
            int iret=0;
            iret = RFIDLIB.rfidlib_reader.RDR_ResetPassingCounter(hreader, 3);
            if (iret != 0)
            {
                MessageBox.Show("Failure to reset flow of people,error:"+iret.ToString());
                return;
            }
            label2.Text = "0";
            label3.Text = "0";
        }

        private void button8_Click(object sender, EventArgs e)
        {
            int iret=0;
            //iret = RFIDLIB.rfidlib_LSGate.LSG_CmdReverseDirection(hreader);
            iret = RFIDLIB.rfidlib_reader.RDR_ReverseInOutDirection(hreader);
            if (iret != 0)
            {
                MessageBox.Show("Failure to reverse direction,error:"+iret.ToString());
                return;
            }
            MessageBox.Show("Success");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            int iret;
            UInt32 year;
            Byte month, day, hour, minute, second;
            year = 0;
            month = day = hour = minute = second = 0;
            iret = RFIDLIB.rfidlib_reader.RDR_GetSystemTime(hreader, ref year, ref month, ref day,ref hour,ref minute, ref second);
            if (iret != 0)
            {
                MessageBox.Show("Failure to get system time,error:"+iret.ToString());
                return;
            }
            string stime;
            stime = year.ToString() + "-" + month.ToString() + "-" + day.ToString() + " " + hour.ToString() + ":" + minute.ToString() + ":" + second.ToString();
            label6.Text = stime;

        }

        private void button7_Click(object sender, EventArgs e)
        {
            int iret;
            UInt32 year;
            Byte month, day, hour, minute, second;
            year =(UInt32) DateTime.Now.Year ;
            month =(Byte) DateTime.Now.Month ;
            day = (Byte)DateTime.Now.Day;
            hour = (Byte)DateTime.Now.Hour;
            minute = (Byte)DateTime.Now.Minute;
            second = (Byte)DateTime.Now.Second;

            iret = RFIDLIB.rfidlib_reader.RDR_SetSystemTime(hreader, year,month,day,hour,minute,second);
            if (iret != 0)
            {
                MessageBox.Show("Failure to set system time,error:"+iret.ToString());
                return;
            }
            MessageBox.Show("Success");
        }
        private delegate void delegateGetEventFinishCallback();
        public void GetEventFinishCallback()
        {
            button9.Enabled = true;
        }
        private delegate void delegateLogError(int ierr) ;
        public void LogError(int ierr)
        {
            string s;
            s = "error:" + ierr.ToString() + "\n";
            richTextBox1.AppendText(s);
        }
        private delegate void delegateEventHandler(/*Byte eventType, */String carddata, Byte dir, Byte[] time);
        public void AddReport(/*Byte eventType, */String carddata, Byte dir, Byte[] time)
        {
            ListViewItem lvi = new ListViewItem();
            String strDir = "null";
            if (dir == 1)
                strDir = "in";
            else if (dir == 2)
                strDir = "out";
            
            String strtime = BitConverter.ToString(time).Replace("-", string.Empty);
            lvi.Text = carddata;
            lvi.SubItems.Add(strDir);
            lvi.SubItems.Add(strtime);
            listView1.Items.Add(lvi);
        }
       
        public void ProcGetEvents()
        {
            int iret;
            Byte flag = 0;
            while (exit_flag == 0)
            {
                iret = RFIDLIB.rfidlib_reader.RDR_BuffMode_FetchRecords(hreader, flag);
                //iret = RFIDLIB.rfidlib_LSGate.LSG_CmdGetReports(hreader, flag, 10);
                if (iret == 0)
                {
                    UInt32 nCount;
                    nCount = RFIDLIB.rfidlib_reader.RDR_GetTagDataReportCount(hreader);
                    if (nCount > 0)
                    {
                        UIntPtr hReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST);
                        while (hReport != UIntPtr.Zero)
                        {
                            Byte[] reportBuf = new Byte[64];
                            UInt32 nSize = (UInt32)reportBuf.Length ;
                            iret = RFIDLIB.rfidlib_reader.RDR_ParseTagDataReportRaw(hReport, reportBuf, ref nSize);
                           //iret = RFIDLIB.rfidlib_LSGate.LSG_ParseSCEventData(hReport, slData, nSize, ref dir, time);
                           if (iret == 0)
                           {
                               if(nSize < 9) {
                                   goto next_report;
                               }
                               Byte evntType;
                               Byte direction;
                               Byte[] time=new Byte[6] ;
                               Byte dataLen ;

                               evntType = reportBuf[0];
                               direction = reportBuf[1];
                               for(int i=0;i<6;i++ ) {
                                   time[i] = reportBuf[2+i] ;
                               }
                               dataLen = reportBuf[8] ;
                               nSize -= 9;
                               if (nSize < dataLen) goto next_report;

                               String strData = BitConverter.ToString(reportBuf, 9, (int)dataLen).Replace("-", string.Empty);
                               object[] pList = { strData, direction, time };
                               Invoke(new delegateEventHandler(AddReport), pList);
                           }
                        next_report:
                           hReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT);
                        }
                        flag = 1;
                    }

                }
                else
                {
                    // error 
                    //{
                    object[] pList = { iret };
                    Invoke(new delegateLogError(LogError), pList);
                    // }
                }
            }
            {
                object[] pList = { };
                Invoke(new delegateGetEventFinishCallback(GetEventFinishCallback), pList);
            }
        }
        private void button9_Click(object sender, EventArgs e)
        {
            exit_flag = 0;
            thrdGetEvent = new Thread(ProcGetEvents);
            thrdGetEvent.Start();
            button9.Enabled = false;
            button10.Enabled = true;
        }

        private void button11_Click(object sender, EventArgs e)
        {

        }

        private void button10_Click(object sender, EventArgs e)
        {
            exit_flag = 1;

            button10.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int iret;
            string connstr = "RDType=LSG405;CommType=NET;RemoteIP=" + textBox1.Text + ";RemotePort=6012;LocalIP=";
            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("Failure to open device,error:"+iret.ToString());
                return;
            }
            button1.Enabled = false;
            button2.Enabled = true;
            button3.Enabled = true;
            button4.Enabled = true;
            button5.Enabled = true;
            button6.Enabled = true;
            button7.Enabled = true;
            button8.Enabled = true;
            button9.Enabled = true;
            button10.Enabled = true;
            button11.Enabled = true;
        }
    }
}