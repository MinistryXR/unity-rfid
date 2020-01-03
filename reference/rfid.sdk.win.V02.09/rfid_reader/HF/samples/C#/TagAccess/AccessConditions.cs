using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Collections;
using RFIDLIB;

namespace WindowsApplication2
{
    public partial class AccessConditions : Form
    {
        //private byte []blkBuff;
        Form1 dlg;
        public AccessConditions(Form cwnd)
        {
            InitializeComponent();
           // blkBuff = new byte [16];
            for (int i=0;i<=7;i++)
            {
                string str = i.ToString();
                comboBox1.Items.Add(str);
                comboBox2.Items.Add(str);
                comboBox3.Items.Add(str);
                comboBox4.Items.Add(str);
            }
            byte[] buff = new byte[16];
            //byte[] keyA = new byte[6];
            //byte[] keyB = new byte[6];
            byte[] accessBuff = new byte[4];
            byte blk0AccType = 0;
            byte blk1AccType = 0;
            byte blk2AccType = 0;
            byte trailerAccType = 0;
            dlg = (Form1)cwnd;
            dlg.getAccessVal(ref buff);
           /* for (int i = 0; i < 6; i++)
            {
                keyA[i] = buff[i];
                keyB[i] = buff[10 + i];
            }*/
            for (int j = 0; j < 4; j++)
            {
                accessBuff[j] = buff[6 + j];
            }
           // textBox1.Text = BitConverter.ToString(keyA, 0, 6).Replace("-", string.Empty);
           // textBox2.Text = BitConverter.ToString(keyB, 0, 6).Replace("-", string.Empty);
            RFIDLIB.rfidlib_aip_iso14443A.MFCL_ParseAccessCondi(accessBuff, ref blk0AccType, ref blk1AccType, ref blk2AccType, ref trailerAccType);

            comboBox1.SelectedIndex = blk0AccType;
            comboBox2.SelectedIndex = blk1AccType;
            comboBox3.SelectedIndex = blk2AccType;
            comboBox4.SelectedIndex = trailerAccType;


        }
     
        public int CreateKeyBuff(byte[] buff)
        {
            int nret;
            byte[] formattedAccCondi = new byte[6];
            byte blk0AccType, blk1AccType, blk2AccType, trailerAccType;

            blk0AccType = (byte)comboBox1.SelectedIndex;
            blk1AccType = (byte)comboBox2.SelectedIndex;
            blk2AccType = (byte)comboBox3.SelectedIndex;
            trailerAccType =(byte) comboBox4.SelectedIndex;

            if (blk0AccType < 0 || blk1AccType < 0 || blk2AccType<0 || trailerAccType<0)
            {
                MessageBox.Show("请选择读取权限");
                return 1;
            }
            byte[] keyA = StringToByteArrayFastest(textBox1.Text);
            byte[] keyB = StringToByteArrayFastest(textBox2.Text);
            nret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_CreateAccessCondition(blk0AccType, blk1AccType, blk2AccType, 
                trailerAccType, formattedAccCondi);

            if (nret!=0)
            {
                MessageBox.Show("操作出错");
                return 1;
            }
            for (int k = 0; k < 6;k++ )
            {
                buff[k] = keyA[k];
                buff[k + 10] = keyB[k];
            }
            for (int k = 0; k < 4;k++ )
            {
                buff[k + 6] = formattedAccCondi[k];
            }
            return 0;
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
            //return val - (val < 58 ? 48 : 55);
            //For lowercase a-f letters:
            //return val - (val < 58 ? 48 : 87);
            //Or the two combined, but a bit slower:
            return val - (val < 58 ? 48 : (val < 97 ? 55 : 87));
        }

        private void button1_Click(object sender, EventArgs e)
        {
           // Form1 dlg = (Form1)this.ParentForm;
            if (dlg==null)
            {
                return;
            }
            byte[]buff = new byte[30];
            CreateKeyBuff(buff);
            dlg.setAccessConditionBuff(buff);
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void AccessConditions_Load(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            AccessTypeBlkBlock dlg = new AccessTypeBlkBlock();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                int idx = dlg.getSelectIndex();
                if (idx >= 0)
                {
                    comboBox1.SelectedIndex = idx;
                }
            }
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            AccessTypeBlkBlock dlg = new AccessTypeBlkBlock();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                int idx = dlg.getSelectIndex();
                if (idx >= 0)
                {
                    comboBox2.SelectedIndex = idx;
                }
            }
            
        }

        private void button5_Click(object sender, EventArgs e)
        {
            AccessTypeBlkBlock dlg = new AccessTypeBlkBlock();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                int idx = dlg.getSelectIndex();
                if (idx >= 0)
                {
                    comboBox3.SelectedIndex = idx;
                }
            }
        
        }

        private void button6_Click(object sender, EventArgs e)
        {
            AccessTypeTailBlock dlg = new AccessTypeTailBlock();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                int idx = dlg.getSelectIndex();
                if (idx >= 0)
                {
                    comboBox4.SelectedIndex = idx;
                }
            }
           
        }
    }
}