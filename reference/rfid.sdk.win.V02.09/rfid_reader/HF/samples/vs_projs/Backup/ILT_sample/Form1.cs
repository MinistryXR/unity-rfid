using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ILT_sample
{
    public partial class Form1 : Form
    {
        public UIntPtr hreader;
        public UIntPtr hTag;
        public Boolean _shouldStop;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {   
            string connstr ;
            int iret;
            connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=RL8000;" +
                      RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" +
                      RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE + "=0;" +
                      RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=";
         

            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("fail");
            }
            else
            {
                bntOpen.Enabled = false;
                bntClose.Enabled = true;

                bntInventory.Enabled = true;
                bntConnect.Enabled = true;
                bntDisconnect.Enabled = false;
          
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int iret = 0;

            if (bntDisconnect.Enabled == true)
            {
                MessageBox.Show("Disconnect first please");
                return;
            }

            iret = RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            if (iret == 0)
            {
                hreader = (UIntPtr)0;
                bntOpen.Enabled = true;
                bntClose.Enabled = false;
                hreader = UIntPtr.Zero;
                //MessageBox.Show("ok");

                bntInventory.Enabled = false;
                bntConnect.Enabled = false;
                bntDisconnect.Enabled = false;
                bntRead.Enabled = false;
                bntWrite.Enabled = false;
                bntLock.Enabled = false;
              
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int iret;

            UInt32 startWord =(UInt32) cmbStartWord.SelectedIndex;
            Byte wordCnt;
            Byte memBank = (Byte)cmbMemBank.SelectedIndex;
            Byte[] tagData = StringToByteArrayFastest(txbData.Text);
            wordCnt = (Byte)((tagData.Length + 1) / 2);
            if (wordCnt == 0)
            {
                MessageBox.Show("input data please ");
                return;
            }
            iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_Write(hreader, hTag, memBank, startWord, wordCnt, tagData,(UInt32) tagData.Length);
            if (iret == 0)
            {
                MessageBox.Show("write ok");
            }
            else
            {
                MessageBox.Show("write fail");
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

        }

        private void button5_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
            hTag = UIntPtr.Zero;
            hreader =UIntPtr.Zero ;

            int i;
            for (i = 0; i < 256; i++)
            {
                cmbStartWord.Items.Add(i.ToString());
            }
            cmbStartWord.SelectedIndex = 0;
            for (i = 1; i < 256; i++) cmbWordCnt.Items.Add(i.ToString());
            cmbWordCnt.SelectedIndex = 0;

            cmbMemBank.SelectedIndex = 1;

            cmbUser.SelectedIndex = 0;
            cmbTID.SelectedIndex = 0;
            cmbEPC.SelectedIndex = 0;
            cmbAccessPwd.SelectedIndex = 0;
            cmbKillPwd.SelectedIndex = 0;

            bntInventory.Enabled = false;
            bntConnect.Enabled = false;
            bntDisconnect.Enabled = false;

            bntRead.Enabled = false;
            bntWrite.Enabled = false;
            bntLock.Enabled = false;

            for (i = 0; i <= 31; i++)
            {
                cmbEPCLen.Items.Add(i.ToString());
            }
            cmbEPCLen.SelectedIndex = 6;
        }

        private void button1_Click_1(object sender, EventArgs e)
        {

            int iret;
            bntInventory.Enabled = false;
            lstbTagFound.Items.Clear();
            cmbTagsFound.Items.Clear();
            cmbTagsFound.Text = "";

            Byte[] AntennaSel = new Byte[16];
            UIntPtr InvenParamSpecList = UIntPtr.Zero;
            InvenParamSpecList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
            if (InvenParamSpecList.ToUInt64() != 0)
            {

                RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_CreateInvenParam(InvenParamSpecList, 0, 0, 0, RFIDLIB.rfidlib_def.ISO18000p6C_Dynamic_Q);
            }
            iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, 1, 0, AntennaSel, InvenParamSpecList);
            if (iret == 0 || iret == -21)
            {
                UIntPtr TagDataReport;
                TagDataReport = (UIntPtr)0;
                TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST); //first
                while (TagDataReport.ToUInt64() > 0)
                {
                    UInt32 aip_id = 0;
                    UInt32 tag_id = 0;
                    UInt32 ant_id = 0;
                    UInt32 metaFlags = 0;
                    Byte[] tagData = new Byte[32];
                    UInt32 tagDataLen = (UInt32)tagData.Length;
                    iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, ref metaFlags, tagData, ref tagDataLen);
                    if (iret == 0)
                    {
                        string epcStr = BitConverter.ToString(tagData, 0, (int)tagDataLen).Replace("-", string.Empty);
                        lstbTagFound.Items.Add(epcStr);
                        cmbTagsFound.Items.Add(epcStr);
                      
                    }

                    /* Get Next report from buffer */
                    TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT); //next
                }
            }
        exit_write:
            if (InvenParamSpecList.ToUInt64() != 0) RFIDLIB.rfidlib_reader.DNODE_Destroy(InvenParamSpecList);

            labTotal.Text = "Tags Found: " + lstbTagFound.Items.Count.ToString();
            bntInventory.Enabled = true;
            if (cmbTagsFound.Items.Count > 0) cmbTagsFound.SelectedIndex = 0;
        }
   
        private void button1_Click_2(object sender, EventArgs e)
        {
            int iret;
            if(cmbTagsFound.Text =="" ){
                MessageBox.Show("select epc please") ;
                return ;
            }
            Byte[] epc=StringToByteArrayFastest(cmbTagsFound.Text ) ;
            Byte setPwd =0 ;
            if (ckbSetPwd.Checked)
            {
                setPwd = 1;
            }
            Byte[] byPwd = StringToByteArrayFastest(txbPwd.Text);
            if (byPwd.Length != 4)
            {
                MessageBox.Show("Length of the password is wrong");
                return;
            }
            UInt32 password=(UInt32)(byPwd[0] & 0xff |(byPwd[1] << 8 & 0xff00) | (byPwd[2] << 16 & 0xff0000 ) | (byPwd[3] << 24 & 0xff000000) );

            UInt32 epcBitsLen =(UInt32)( epc.Length * 8);
            iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_Connect(hreader, 0, epc, epcBitsLen, setPwd, password, ref hTag);
            if (iret == 0)
            {
                bntConnect.Enabled = false;
                bntDisconnect.Enabled = true;
                bntRead.Enabled = true;
                bntWrite.Enabled = true;
                bntLock.Enabled = true;
                bntInventory.Enabled = false;
            }
            else
            {
                MessageBox.Show("connect fail");
            }

        }

        private void bntDisconnect_Click(object sender, EventArgs e)
        {
            RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
            hTag = UIntPtr.Zero;

            bntConnect.Enabled = true;
            bntDisconnect.Enabled = false;

            bntRead.Enabled = false;
            bntWrite.Enabled = false;
            bntLock.Enabled = false;
            bntInventory.Enabled = true;
        }

        private void bntRead_Click(object sender, EventArgs e)
        {
            int iret;
            UInt32 startWord = (UInt32)cmbStartWord.SelectedIndex;
            Byte memBank = (Byte)cmbMemBank.SelectedIndex;
            Byte wordCnt = (Byte)(cmbWordCnt.SelectedIndex + 1);
            Byte[] wordBuffer = new Byte[wordCnt * 2 +10];
            UInt32 nRead =(UInt32)( wordBuffer.Length);
            iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_Read(hreader, hTag, memBank, startWord, wordCnt, wordBuffer, ref nRead);
            if (iret == 0)
            {
                txbData.Text = BitConverter.ToString(wordBuffer, 0, (int)nRead).Replace("-", string.Empty);
            }
            else
            {
                MessageBox.Show("read fail");
            }
        }

        private void bntLock_Click(object sender, EventArgs e)
        {
            UInt16 mask, action,temp;
            mask = action = 0;
            if (ckbUser.Checked)
            {
                temp = (UInt16)cmbUser.SelectedIndex ;
                mask |= 0x03;
                action |= (UInt16)(temp);
            }
            if (ckbTID.Checked)
            {
                temp = (UInt16)cmbTID.SelectedIndex;
                mask |= (0x03 << 2);
                action |= (UInt16)(temp << 2);
            }
            if (ckbEPC.Checked)
            {
                temp = (UInt16)cmbEPC.SelectedIndex;
                mask |= (0x03 << 4 & 0x30);
                action |= (UInt16)(temp << 4);
            }
            if (ckbAccessPwd.Checked)
            {
                temp = (UInt16)cmbAccessPwd.SelectedIndex;
                mask |= (0x03 << 6);
                action |= (UInt16)(temp << 6);
            }
            if (ckbKillPwd.Checked)
            {
                temp = (UInt16)cmbKillPwd.SelectedIndex;
                mask |= (0x03 << 8);
                action |= (UInt16)(temp << 8);
            }

            int iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_Lock(hreader, hTag, mask, action);
            if (iret == 0)
            {
                MessageBox.Show("lock ok");
            }
            else
            {
                MessageBox.Show("lock fail");
            }
        }

        private void button1_Click_3(object sender, EventArgs e)
        {
            int iret;

            Byte[] byPwd = StringToByteArrayFastest(txbKillPwd.Text);
            if (byPwd.Length != 4)
            {
                MessageBox.Show("Length of the password is wrong");
                return;
            }
            UInt32 password = (UInt32)(byPwd[0] & 0xff | (byPwd[1] << 8 & 0xff00) | (byPwd[2] << 16 & 0xff0000) | (byPwd[3] << 24 & 0xff000000));

            Byte recomm = 0;
            if (ckbRecomLSB.Checked)
            {
                recomm |= 0x01;
            }
            if (ckbRecomLSB2.Checked)
            {
                recomm |= 0x02;
            }
            if (ckbRecomLSB3.Checked)
            {
                recomm |= 0x04;
            }
            iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_Kill(hreader, hTag, password, recomm);
            if (iret == 0)
            {
                MessageBox.Show("Kill ok");
            }
            else
            {
                MessageBox.Show("Kill fail");
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            int iret;
            UInt16 pc =0 ;
            iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_ReadPC(hreader, hTag, ref pc);
            if (iret != 0)
            {
                MessageBox.Show("read PC fail");
            }
            else
            {
                int epclen = (pc>>3) & 0x1f;
                cmbEPCLen.SelectedIndex = epclen;
            }
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            int iret;
            if (cmbEPCLen.SelectedIndex == -1)
            {
                MessageBox.Show("select EPC length please");
                return;
            }
            UInt16 pc = 0;
            UInt16 epclen = (UInt16) cmbEPCLen.SelectedIndex ;
            pc = (UInt16)(epclen << 3 & 0x00f8);
            iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_WritePC(hreader, hTag, 0xf8, pc);
            if (iret == 0)
            {
                MessageBox.Show("Write ok");
            }
            else
            {
                MessageBox.Show("Write fail");
            }
        }
    }
}


/*
           if (txbEPC.Text == "")
            {
                MessageBox.Show("input new epc please");
                return;
            }
            int iret;
            Byte[] AntennaSel = new Byte[16];
            UIntPtr InvenParamSpecList = UIntPtr.Zero;
            InvenParamSpecList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
            if (InvenParamSpecList.ToUInt64() != 0)
            {
                RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_CreateInvenParam(InvenParamSpecList, 0, 0, 0, 4);
            }
            iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, 1, 0, AntennaSel, InvenParamSpecList);
            if (iret == 0)
            {

                if (RFIDLIB.rfidlib_reader.RDR_GetTagDataReportCount(hreader) == 0)
                {
                    MessageBox.Show("No tag found!");
                    goto exit_write;
                }
                UIntPtr TagDataReport;
                TagDataReport = (UIntPtr)0;
                TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST); //first
                while (TagDataReport.ToUInt64() > 0)
                {
                    UInt32 aip_id = 0;
                    UInt32 tag_id = 0;
                    UInt32 ant_id = 0;
                    UInt32 metaFlags = 0;
                    Byte[] tagData = new Byte[32];
                    UInt32 tagDataLen = (UInt32)tagData.Length;
                    iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, ref metaFlags, tagData, ref tagDataLen);
                    if (iret == 0)
                    {
                        string epcStr = BitConverter.ToString(tagData, 0, (int)tagDataLen).Replace("-", string.Empty);
                        //object[] pList = { aip_id, tag_id, ant_id, tagData, tagDataLen };
                        //Invoke(tagReportHandler, pList);
                        UIntPtr hTag = UIntPtr.Zero;
                        UInt32 epcBitsLen = tagDataLen * 8;
                        iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_Connect(hreader, 0, tagData, epcBitsLen,1 ,0, ref hTag);
                        if (iret == 0)
                        {
                            
                            byte[] epcDatas = StringToByteArrayFastest(txbEPC.Text);
                            int bytesToWrite = epcDatas.Length;
                            if (bytesToWrite > tagDataLen) bytesToWrite = (int)tagDataLen;
                            for (int i = 0; i < bytesToWrite; i++) tagData[i] = epcDatas[i];

                            Byte wordCnt = (Byte)(tagDataLen / 2);

                            iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_Write(hreader, hTag, 1, 0, wordCnt, tagData, tagDataLen);
                            if (iret == 0)
                            {
                                rtbLog.AppendText(epcStr + " write ok \n");
                            }
                            else
                            {
                                rtbLog.AppendText(epcStr + " write fail \n");
                            }

                            RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
                        }
                        else
                        {
                            rtbLog.AppendText(epcStr +" connect fail \n");
                        }
                    }

                    
                    TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT); //next
                }
            }
            exit_write:
            if (InvenParamSpecList.ToUInt64() != 0) RFIDLIB.rfidlib_reader.DNODE_Destroy(InvenParamSpecList);



*/