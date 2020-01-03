using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WindowsApplication2
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
            int i;

            for (i = 0; i < 256; i++)
            {
                cbbSelPointer.Items.Add(i.ToString());
                cbbSelMaskBitsLen.Items.Add(i.ToString());
                cbbReadWordPtr.Items.Add(i.ToString());
                cbbReadWordCnt.Items.Add(i.ToString());
                cbbWriteWordCnt.Items.Add(i.ToString());
                cbbWriteWordPtr.Items.Add(i.ToString());
            }

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

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
        private void button1_Click(object sender, EventArgs e)
        {
            int i ;
            /* select option */
            Form1.invenParams.m_sel.m_enable = ckbSelEnable.Checked;
            Form1.invenParams.m_sel.m_target =(Byte)(cbbSelTarget.SelectedIndex);
            Form1.invenParams.m_sel.m_action =(Byte) cbbSelAction.SelectedIndex  ;
            Form1.invenParams.m_sel.m_memBank = (Byte)cbbSelMemBank.SelectedIndex  ;
            Form1.invenParams.m_sel.m_pointer = (Byte)cbbSelPointer.SelectedIndex;
            Form1.invenParams.m_sel.m_maskBitsLength = (Byte)(cbbSelMaskBitsLen.SelectedIndex );
            Byte[] maskBitBytes= StringToByteArrayFastest(txbSelMaskBits.Text) ;
            Form1.invenParams.m_sel.m_maskBits.Clear();
            for (i = 0; i < maskBitBytes.Length; i++) Form1.invenParams.m_sel.m_maskBits.Add(maskBitBytes[i]);

            /* meta option*/
            Form1.invenParams.m_metaFlags.m_enable=ckbMetaEnable.Checked ;
            Form1.invenParams.m_metaFlags.m_EPC=ckbMetaEPC.Checked  ;
            Form1.invenParams.m_metaFlags.m_frequency =  ckbMetaFrequency.Checked ;
            Form1.invenParams.m_metaFlags.m_readCnt = ckbMetaReadCnt.Checked ;
            Form1.invenParams.m_metaFlags.m_RSSI = ckbMetaRSS.Checked ;
            Form1.invenParams.m_metaFlags.m_tagData = ckbMetaTagData.Checked ;
            Form1.invenParams.m_metaFlags.m_timestamp =ckbMetaTimestamp.Checked ;
            Form1.invenParams.m_metaFlags.m_antennaID = ckbMetaAntennaID.Checked;

            /*inventory read */
            Form1.invenParams.m_read.m_enable= ckbReadEnable.Checked ;
            Form1.invenParams.m_read.m_memBank =(Byte)cbbReadMemBank.SelectedIndex ;
            Form1.invenParams.m_read.m_wordPtr = (Byte)cbbReadWordPtr.SelectedIndex ;
            Form1.invenParams.m_read.m_wordCnt = (Byte)(cbbReadWordCnt.SelectedIndex);

            /*embedded commands---- write*/
            Form1.invenParams.m_write.m_enable = ckbWriteEnable.Checked ;
            Form1.invenParams.m_write.m_memBank =(Byte) cbbWriteMemBank.SelectedIndex  ;
            Form1.invenParams.m_write.m_wordPtr = (Byte)(cbbWriteWordPtr.SelectedIndex ) ;
            Form1.invenParams.m_write.m_wordCnt =(Byte)( cbbWriteWordCnt.SelectedIndex);
            Byte[] writeDataBytes = StringToByteArrayFastest(txbWriteDatas.Text);
            Form1.invenParams.m_write.m_datas.Clear();
            for (i = 0; i < writeDataBytes.Length; i++) Form1.invenParams.m_write.m_datas.Add(writeDataBytes[i]);

            if(txbAccessPwd.Text.Length == 8){
                Byte[] accessPwdBytes = StringToByteArrayFastest(txbAccessPwd.Text);
                Form1.invenParams.m_accessPwd =(UInt32)( accessPwdBytes[0] | (accessPwdBytes[1] << 8 & 0xff00) | (accessPwdBytes[2] << 16 & 0xff0000) | (accessPwdBytes[3] << 24 & 0xff000000));
            }
            /* timeout */
            Form1.invenParams.m_timeout =(UInt32)int.Parse(txbTimeout.Text);

            /* embedded command-----lock */
            Form1.invenParams.m_lock.m_userMemSelected = ckbLockUserMem.Checked ;
            Form1.invenParams.m_lock.m_TIDMemSelected = ckbLockTIDMem.Checked;
            Form1.invenParams.m_lock.m_EPCMemSelected = ckbLockEPCMem.Checked;
            Form1.invenParams.m_lock.m_accessPwdSelected = ckbLockAccessPwd.Checked;
            Form1.invenParams.m_lock.m_killPwdSelected = ckbLockKillPwd.Checked;

            Form1.invenParams.m_lock.m_userMem  = (uint)cbbLockUserMem.SelectedIndex;
            Form1.invenParams.m_lock.m_TIDMem = (uint)cbbLockTIDMem.SelectedIndex;
            Form1.invenParams.m_lock.m_EPCMem = (uint)cbbLockEPCMem.SelectedIndex;
            Form1.invenParams.m_lock.m_accessPwd = (uint)cbbLockAccessPwd.SelectedIndex;
            Form1.invenParams.m_lock.m_killPwd = (uint)cbbLockKillPwd.SelectedIndex;

            Form1.invenParams.m_lock.m_enable = ckbLockEnable.Checked;
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void checkBox8_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void Form2_Load(object sender, EventArgs e)
        {
            /* select option */
            ckbSelEnable.Checked = false;
            if (Form1.invenParams.m_sel.m_enable)
            {
                ckbSelEnable.Checked = true;
            }
            cbbSelTarget.SelectedIndex = Form1.invenParams.m_sel.m_target;
            cbbSelAction.SelectedIndex = Form1.invenParams.m_sel.m_action;
            cbbSelMemBank.SelectedIndex = Form1.invenParams.m_sel.m_memBank;
            cbbSelPointer.SelectedIndex = (int)Form1.invenParams.m_sel.m_pointer;
            cbbSelMaskBitsLen.SelectedIndex = (int)(Form1.invenParams.m_sel.m_maskBitsLength );
            txbSelMaskBits.Text = BitConverter.ToString(Form1.invenParams.m_sel.m_maskBits.ToArray(), 0, Form1.invenParams.m_sel.m_maskBits.Count).Replace("-", string.Empty);


            /* meta option*/
            ckbMetaEnable.Checked = false;
            if (Form1.invenParams.m_metaFlags.m_enable)
            {
                ckbMetaEnable.Checked = true;
            }
            if (Form1.invenParams.m_metaFlags.m_EPC)
            {
                ckbMetaEPC.Checked = true;
            }
            if (Form1.invenParams.m_metaFlags.m_frequency)
            {
                ckbMetaFrequency.Checked = true;
            }
            if (Form1.invenParams.m_metaFlags.m_readCnt)
            {
                ckbMetaReadCnt.Checked = true;
            }
            if (Form1.invenParams.m_metaFlags.m_RSSI)
            {
                ckbMetaRSS.Checked = true;
            }
            if (Form1.invenParams.m_metaFlags.m_tagData)
            {
                ckbMetaTagData.Checked = true;
            }
            if (Form1.invenParams.m_metaFlags.m_timestamp)
            {
                ckbMetaTimestamp.Checked = true;
            }
            if (Form1.invenParams.m_metaFlags.m_antennaID)
            {
                ckbMetaAntennaID.Checked = true;
            }

            /*inventory read */
            if (Form1.invenParams.m_read.m_enable)
            {
                ckbReadEnable.Checked = true;
            }
            cbbReadMemBank.SelectedIndex =(int)Form1.invenParams.m_read.m_memBank ;
            cbbReadWordPtr.SelectedIndex =(int) Form1.invenParams.m_read.m_wordPtr;
            cbbReadWordCnt.SelectedIndex = (int)Form1.invenParams.m_read.m_wordCnt ;

            /*embedded commands---- write*/
            if (Form1.invenParams.m_write.m_enable)
            {
                ckbWriteEnable.Checked = true;
            }
            cbbWriteMemBank.SelectedIndex =(int) Form1.invenParams.m_write.m_memBank;
            cbbWriteWordPtr.SelectedIndex =(int) Form1.invenParams.m_write.m_wordPtr;
            cbbWriteWordCnt.SelectedIndex =(int) Form1.invenParams.m_write.m_wordCnt;
            txbWriteDatas.Text = BitConverter.ToString(Form1.invenParams.m_write.m_datas.ToArray(), 0, Form1.invenParams.m_write.m_datas.Count).Replace("-", string.Empty);

            Byte[] accessPwd = new Byte[4];
            accessPwd[0]= (Byte) (Form1.invenParams.m_accessPwd & 0xff );
            accessPwd[1] = (Byte) (Form1.invenParams.m_accessPwd >> 8 & 0xff);
            accessPwd[2] = (Byte) (Form1.invenParams.m_accessPwd >> 16 & 0xff);
            accessPwd[3] = (Byte)(Form1.invenParams.m_accessPwd >> 24 & 0xff);
            txbAccessPwd.Text = BitConverter.ToString(accessPwd, 0, accessPwd.Length).Replace("-", string.Empty);


            txbTimeout.Text = Form1.invenParams.m_timeout.ToString();

            /* embedded lock */
            ckbLockEnable.Checked = Form1.invenParams.m_lock.m_enable;
            ckbLockUserMem.Checked = Form1.invenParams.m_lock.m_userMemSelected ;
            ckbLockTIDMem.Checked = Form1.invenParams.m_lock.m_TIDMemSelected;
            ckbLockEPCMem.Checked = Form1.invenParams.m_lock.m_EPCMemSelected;
            ckbLockAccessPwd.Checked = Form1.invenParams.m_lock.m_accessPwdSelected;
            ckbLockKillPwd.Checked = Form1.invenParams.m_lock.m_killPwdSelected;

            cbbLockUserMem.SelectedIndex =(int) Form1.invenParams.m_lock.m_userMem;
            cbbLockTIDMem.SelectedIndex = (int)Form1.invenParams.m_lock.m_TIDMem;
            cbbLockEPCMem.SelectedIndex = (int)Form1.invenParams.m_lock.m_EPCMem;
            cbbLockAccessPwd.SelectedIndex = (int)Form1.invenParams.m_lock.m_accessPwd;
            cbbLockKillPwd.SelectedIndex = (int)Form1.invenParams.m_lock.m_killPwd;
        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}