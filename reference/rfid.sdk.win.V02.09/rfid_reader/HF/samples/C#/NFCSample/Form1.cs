using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace NFCSample
{
   
    public partial class Form1 : Form
    {
        private UIntPtr hreader = UIntPtr.Zero;
        private UIntPtr htag = UIntPtr.Zero;
        List<tagInfo> inventoryList = new List<tagInfo>();
        public Form1()
        {
            InitializeComponent();
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

            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
            UInt32 nReaderCnt = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();
            for (UInt32 j = 0; j < nReaderCnt; j++)
            {
               
                StringBuilder nameBuffer = new StringBuilder();
                nameBuffer.Append('\0',128);
                UInt32 nameLen =(UInt32) nameBuffer.Length;
                RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(j, RFIDLIB.rfidlib_def.LOADED_RDRDVR_OPT_NAME, nameBuffer, ref nameLen);
                comboBoxReader.Items.Add(nameBuffer.ToString());
            }
            UiControl(false);
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {

            int iret = 0;
            int commTypeIdx = comboBoxType.SelectedIndex;
            if (commTypeIdx < 0)
            {
                MessageBox.Show("Please select the type of communication!");
                return;
            }
            string readerDriverName = comboBoxReader.Text;
            string connstr = "";
            if (commTypeIdx == 0)
            {
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE + "=" + "0" + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=" ;
            }
            else if (commTypeIdx == 1)
            {
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME + "=" + comboBoxCOM.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + comboBoxBaud.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + comboBoxFrame.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR + "=" + "255";
            }
          
            else if (commTypeIdx == 2)
            {
                string ipAddr;
                UInt16 port;
                ipAddr = textBoxAddr.Text;
                port = (UInt16)int.Parse(textBoxPort.Text);
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_NET + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEIP + "=" + ipAddr + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEPORT + "=" + port.ToString() + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_LOCALIP + "=" + "";
            }

            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("Open reader failed!");
                return;
            }
            UiControl(true);
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            if (hreader == UIntPtr.Zero)
            {
                return;
            }
            if (htag != UIntPtr.Zero)
            {
                MessageBox.Show("Please disconnect the tag first!");
                return;
            }
            RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            hreader = UIntPtr.Zero;
            UiControl(false);
        }

        private void UiControl(bool isOpen)
        {
            comboBoxReader.Enabled = !isOpen;
            comboBoxType.Enabled = !isOpen;
            buttonOpen.Enabled = !isOpen;
            buttonClose.Enabled = isOpen;
            comboBoxCOM.Enabled = !isOpen;
            comboBoxBaud.Enabled = !isOpen;
            comboBoxFrame.Enabled = !isOpen;
            textBoxAddr.Enabled = !isOpen;
            textBoxPort.Enabled = !isOpen;
            comboBoxUid.Enabled = isOpen;
            buttonInventory.Enabled = isOpen;
            buttonConnect.Enabled = isOpen;
            tabControl1.Enabled = false;
            buttonDisconnect.Enabled = false;
        }

        private void buttonInventory_Click(object sender, EventArgs e)
        {
            inventoryList.Clear();
            comboBoxUid.Items.Clear();
            int iret = 0;
            UIntPtr dnInvenParamList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
            RFIDLIB.rfidlib_aip_iso15693.ISO15693_CreateInvenParam(dnInvenParamList, (byte)0, (byte)0, (byte)0, (byte)0);
            RFIDLIB.rfidlib_aip_iso14443A.ISO14443A_CreateInvenParam(dnInvenParamList, (byte)0);
            iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, RFIDLIB.rfidlib_def.AI_TYPE_NEW, 0, null, dnInvenParamList);
            if (iret != 0)
            {
                return;
            }

            UIntPtr TagDataReport = UIntPtr.Zero;
            TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST); //first
            while (TagDataReport != UIntPtr.Zero)
            {
                tagInfo tag = new tagInfo();
                UInt32 aip_id = 0;
                UInt32 tag_id = 0;
                UInt32 ant_id = 0;
                Byte dsfid = 0;
                Byte[] uid = new Byte[16];
                byte uidLen = 0;
                string strUid = "";
                iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, ref dsfid, uid);
                if (iret == 0) //ISO15693标签
                {
                    strUid = BitConverter.ToString(uid, 0, 8).Replace("-", string.Empty);
                    tag.uid = strUid;
                    tag.aip_id = aip_id;
                    tag.tag_id = tag_id;
                    inventoryList.Add(tag);
                    goto TagEnd;
                }


                //ISO14443A标签
                iret = RFIDLIB.rfidlib_aip_iso14443A.ISO14443A_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, uid, ref uidLen);
                if (iret == 0)
                {
                    strUid = BitConverter.ToString(uid, 0, uidLen).Replace("-", string.Empty);
                    tag.uid = strUid;
                    tag.aip_id = aip_id;
                    tag.tag_id = tag_id;
                    inventoryList.Add(tag);
                }

            TagEnd:
                TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT); //next
            }

            
            foreach (tagInfo info in inventoryList)
            {
                comboBoxUid.Items.Add(info.uid);
            }

            if (inventoryList.Count > 0)
            {
                comboBoxUid.SelectedIndex = 0;
            }

            if (dnInvenParamList != UIntPtr.Zero)
            {
                RFIDLIB.rfidlib_reader.DNODE_Destroy(dnInvenParamList);
            }
        }

        private void buttonReadUri_Click(object sender, EventArgs e)
        {
            int nret = 0;
            Byte NedfType = 0x00;
            Byte NetType = 0x00;
            UIntPtr Nedf = UIntPtr.Zero;
            StringBuilder addr = new StringBuilder();
            addr.Append('\0', 512);
            nret = RFIDLIB.rfidlib_nfc.nfc_ReadNdef(hreader, htag, ref Nedf, ref NedfType);
            if (nret != 0)
            {
                goto EndExit;
            }

            nret = RFIDLIB.rfidlib_nfc.nfc_ParseNdefByUri(Nedf, addr, (UInt32)addr.Length, ref NetType);
            if (nret != 0)
            {
                goto EndExit;
            }
            textBoxUriAddress.Text = addr.ToString();

        EndExit:
            if (Nedf != UIntPtr.Zero)
            {
                RFIDLIB.rfidlib_reader.DNODE_Destroy(Nedf);
                Nedf = UIntPtr.Zero;
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


        private void buttonConnect_Click(object sender, EventArgs e)
        {
            int idx = comboBoxUid.SelectedIndex;
            int iret = 0;
            if (idx < 0)
            {
                MessageBox.Show("Please select a tag!");
                return;
            }

            if (htag != UIntPtr.Zero)
            {
                RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, htag);
            }

            Byte[] uid = StringToByteArrayFastest(inventoryList[idx].uid);
            if (inventoryList[idx].aip_id == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID)  //15693协议的标签
            {
               
                iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Connect(hreader, inventoryList[idx].tag_id, 1, uid, ref htag);//连接标签
                if (iret != 0)
                {
                    MessageBox.Show("failed!");
                    return;
                }
            }
            else if (inventoryList[idx].aip_id == RFIDLIB.rfidlib_def.RFID_APL_ISO14443A_ID)
            {
                iret = RFIDLIB.rfidlib_aip_iso14443A.NTAG21x_Connect(hreader, uid, ref htag);//连接NTAG21X标签
                if (iret != 0)
                {
                    MessageBox.Show("failed!");
                    return;
                }
            }
            else
            {
                MessageBox.Show("failed!");
                return;
            }

            buttonDisconnect.Enabled = true;
            buttonConnect.Enabled = false;
            tabControl1.Enabled = true;
            buttonInventory.Enabled = false;
            comboBoxUid.Enabled = false;
        }

        private void buttonDisconnect_Click(object sender, EventArgs e)
        {
            if (htag == UIntPtr.Zero)
            {
                return;
            }
            htag = UIntPtr.Zero;
            RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, htag);
            buttonDisconnect.Enabled = false;
            buttonConnect.Enabled = true;
            tabControl1.Enabled = false;
            buttonInventory.Enabled = true;
            comboBoxUid.Enabled = true;
        }

        private void buttonWriteUri_Click(object sender, EventArgs e)
        {
            UIntPtr ndef = RFIDLIB.rfidlib_nfc.nfc_CreateUriNdef(textBoxUriAddress.Text, 0x00);
            Byte IsLock = (Byte)(checkBoxLock.Checked ? 1 : 0);
            int nret = RFIDLIB.rfidlib_nfc.nfc_WriteNdef(hreader, htag, ndef, IsLock);
            if (nret != 0)
            {
                MessageBox.Show("Write uri failed!");
                goto EndExit;
            }
            MessageBox.Show("Write uri successfully!");
        EndExit:
            if (ndef != UIntPtr.Zero)
            {
                RFIDLIB.rfidlib_reader.DNODE_Destroy(ndef);
            }
            
        }
    }


    public class tagInfo
    {
        public string uid;
        public UInt32 aip_id = 0;
        public UInt32 tag_id;
    }

   
}