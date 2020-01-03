using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SetOutput_cs
{
    public partial class Form1 : Form
    {
        UIntPtr hreader = UIntPtr.Zero;
        public Form1()
        {
            InitializeComponent();

            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
            UInt32 nCnt = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();
            for (UInt32 j = 0; j < nCnt; j++)
            {
                UInt32 nSize = 0;
                StringBuilder sName = new StringBuilder();
                sName.Append('\0',128);
                RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(j, RFIDLIB.rfidlib_def.LOADED_RDRDVR_OPT_NAME, sName,ref nSize);
                cmbDevType.Items.Add(sName);
            }
            if (nCnt > 0)
            {
                cmbDevType.SelectedIndex = 0;
            }
            cmbCommuncateType.Items.Add("USB");
            cmbCommuncateType.Items.Add("COM");
            cmbCommuncateType.Items.Add("NET");
            cmbCommuncateType.SelectedIndex = 0;

            UInt32 comNum = RFIDLIB.rfidlib_reader.COMPort_Enum();
            for (UInt32 j = 0; j < comNum; j++)
            {
                UInt32 nSize = 0;
                StringBuilder comName = new StringBuilder();
                comName.Append('\0', 128);
                RFIDLIB.rfidlib_reader.COMPort_GetEnumItem(j, comName, nSize);
                cmbComName.Items.Add(comName.ToString());
            }
            if (comNum > 0)
            {
                cmbComName.SelectedIndex = 0;
            }

            cmbBaud.SelectedIndex = 1;
            cmbFrame.SelectedIndex = 0;

            for (int j = 1; j <= 255; j++)
            {
                cmbFrequency.Items.Add(j.ToString());
            }
            cmbFrequency.SelectedIndex = 0;
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (cmbDevType.SelectedIndex == -1)
            {
                MessageBox.Show("select reader driver type");
                return;
            }
            if (cmbCommuncateType.SelectedIndex == -1)
            {
                MessageBox.Show("select communication type");
                return;
            }

            int iret = 0;

            // Use new way to open reader driver
            int commTypeIdx = cmbCommuncateType.SelectedIndex;
            string readerDriverName = cmbDevType.Text;
            string connstr = "";
            if (commTypeIdx == 0)
            {
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE + "=" + 0 + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=";
               
            }
            else if (commTypeIdx == 1)
            {
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME + "=" + cmbComName.Text + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + cmbBaud.Text + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + cmbFrame.Text + ";" +
                         RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR + "=" + "255";
            }
            else if (commTypeIdx == 2)
            {
                string ipAddr = textIp.Text;
                UInt16 port;
                ipAddr = textIp.Text;
                port = (UInt16)int.Parse(textPort.Text);
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_NET + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEIP + "=" + ipAddr + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEPORT + "=" + port.ToString() + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_LOCALIP + "=" + "";
            }

            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("Open device failed!");
                return;
            }
            LoadOutputName();
            EnableAllCtr(true);
        }

        private void EnableAllCtr(bool isOpen)
        {
            cmbDevType.Enabled = !isOpen;
            cmbCommuncateType.Enabled = !isOpen;
            cmbComName.Enabled = !isOpen;
            cmbBaud.Enabled = !isOpen;
            cmbFrame.Enabled = !isOpen;
            textIp.Enabled = !isOpen;
            textPort.Enabled = !isOpen;
            btnClose.Enabled = isOpen;
            btnOpen.Enabled = !isOpen;
            textActTime.Enabled = isOpen;
            cmbFrequency.Enabled = isOpen;
            textStopTime.Enabled = isOpen;
            btnSetOutput.Enabled = isOpen;
        }


        private void EnableAllCtr(int communicateType)
        {
            switch (communicateType)
            {
                case 0:
                    cmbComName.Enabled = false;
                    cmbBaud.Enabled = false;
                    cmbFrame.Enabled = false;
                    textIp.Enabled = false;
                    textPort.Enabled = false;
                    break;
                case 1:
                    cmbComName.Enabled = true;
                    cmbBaud.Enabled = true;
                    cmbFrame.Enabled = true;
                    textIp.Enabled = false;
                    textPort.Enabled = false;
                    break;
                case 2:
                    cmbComName.Enabled = false;
                    cmbBaud.Enabled = false;
                    cmbFrame.Enabled = false;
                    textIp.Enabled = true;
                    textPort.Enabled = true;
                    break;
                default: break;
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            int iret = RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            if (iret == 0)
            {
                EnableAllCtr(false);
                EnableAllCtr(cmbCommuncateType.SelectedIndex);
                checkedListOutput.Items.Clear();
                hreader = UIntPtr.Zero;
            }
        }

       

        private void cmbCommuncateType_SelectedIndexChanged(object sender, EventArgs e)
        {
            EnableAllCtr(cmbCommuncateType.SelectedIndex);
        }

        private void LoadOutputName()
        {
            byte nCnt = 0;
            checkedListOutput.Items.Clear();
            int iret = RFIDLIB.rfidlib_reader.RDR_GetOutputCount(hreader,ref nCnt);
            for (int j = 0; j < nCnt; j++)
            {
                StringBuilder sName = new StringBuilder();
                uint nsize = 0;
                sName.Append('\0', 128);
                iret = RFIDLIB.rfidlib_reader.RDR_GetOutputName(hreader, (byte)(j + 1), sName, ref nsize);
                if (iret != 0)
                {
                    continue;
                }
                checkedListOutput.Items.Add(sName);
                checkedListOutput.SetItemChecked(j, true);
            }

        }

        private void btnSetOutput_Click(object sender, EventArgs e)
        {
            int iret = 0;
            Byte outputSel = 0;

            if (textActTime.Text == "")
            {
                MessageBox.Show("Please input active time!");
                return;
            }
            int idx;
            idx = cmbFrequency.SelectedIndex;
            if (idx == -1)
            {
                MessageBox.Show("Please choose a frequency!");
                return;
            }
            if (textStopTime.Text == "")
            {
                MessageBox.Show("Please input stop time!");
                return;
            }

            Byte activeDuration = (Byte)((int.Parse(textActTime.Text)) & 0xff);
            Byte number = (Byte)(idx + 1);
            Byte pauseDuration = (Byte)((int.Parse(textStopTime.Text)) & 0xff);
            UIntPtr dnOutputOper = RFIDLIB.rfidlib_reader.RDR_CreateSetOutputOperations();
            for (int i = 0; i < checkedListOutput.Items.Count; i++)
            {
                if (checkedListOutput.GetItemChecked(i))
                {
                    RFIDLIB.rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper, (Byte)(i + 1), 3, number,(UInt32)( activeDuration*100),(UInt32)( pauseDuration*100));
                }
            }
            iret = RFIDLIB.rfidlib_reader.RDR_SetOutput(hreader, dnOutputOper);
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

        private void Form1_Load(object sender, EventArgs e)
        {

        }

    }
}