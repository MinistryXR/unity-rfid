using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Threading;

namespace RS485Sample_cs
{
    public partial class MainFrm : Form
    {
        UIntPtr m_hr = UIntPtr.Zero;
        ArrayList m_hRS485 = null;
        ArrayList m_busAddr = null;
        UIntPtr m_curReader = UIntPtr.Zero;
        bool b_inventoryFlg = false;

        public MainFrm()
        {
            InitializeComponent();
            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
            UInt32 nCnt = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();
            for (uint j = 0; j < nCnt; j++)
            {
                UInt32 nSize = 0;
                StringBuilder sName = new StringBuilder();
                sName.Append('\0', 128);
                RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(j, RFIDLIB.rfidlib_def.LOADED_RDRDVR_OPT_NAME, sName, ref nSize);
                cmbDevType.Items.Add(sName);
            }
            if (nCnt > 0)
            {
                cmbDevType.SelectedIndex = 0;
            }


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

            m_hRS485 = new ArrayList();
            m_busAddr = new ArrayList();

            EnableAllCtr(false);

        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            Byte addr = 0;
            for (int i = 0; i < checkedListNode.Items.Count; i++)
            {
                if (checkedListNode.GetItemChecked(i))
                {
                    addr = (Byte)(i+1);
                    break;
                }
             }
             if (addr == 0)
             {
                 MessageBox.Show("Please select the RS485 node first!");
                 return;
            }

            string connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + cmbDevType.Text + ";" +
            RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
            RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME + "=" + cmbComName.Text + ";" +
            RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + cmbBaud.Text + ";" +
            RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + cmbFrame.Text + ";" +
            RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR + "=" + addr;

            UIntPtr hreader = UIntPtr.Zero;
            int iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("Open device failed!err = " + iret);
                return;
            }
            m_hr = hreader;

            for (int i = 0; i < checkedListNode.Items.Count; i++)
            {
                if (checkedListNode.GetItemChecked(i))
                {
                    hreader = UIntPtr.Zero; ;
                    iret = RFIDLIB.rfidlib_reader.RDR_CreateRS485Node(m_hr, (UInt32)i + 1, ref hreader);
                    if (iret == 0)
                    {
                        m_hRS485.Add(hreader);
                        m_busAddr.Add(i + 1);
                    }
                }
            }
            EnableAllCtr(true);
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            if (b_inventoryFlg)
            {
                MessageBox.Show("Please stop inventory first!");
                return;
            }
            if (m_hr.ToUInt64() != 0)
            {
                RFIDLIB.rfidlib_reader.RDR_Close(m_hr);
                m_hr = UIntPtr.Zero;
            }
            for (int j = 0; j < m_hRS485.Count; j++)
            {
                RFIDLIB.rfidlib_reader.RDR_Close((UIntPtr)m_hRS485[j]);
            }
            m_hRS485.Clear();
            m_busAddr.Clear();
            EnableAllCtr(false);
        }

        private void DoInventory()
        {
            int iret;
            byte newAI = RFIDLIB.rfidlib_def.AI_TYPE_NEW;
            UIntPtr dnInvenParamList = UIntPtr.Zero;
            dnInvenParamList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
            if (dnInvenParamList.ToUInt64() != 0)
            {
                RFIDLIB.rfidlib_aip_iso15693.ISO15693_CreateInvenParam(dnInvenParamList, 0, 0, 0, 0x00);
            }
            int idx = 0;
            b_inventoryFlg = true;
            while (b_inventoryFlg)
            {
                m_curReader = (UIntPtr)m_hRS485[idx];
                iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(m_curReader, newAI, 0, null, dnInvenParamList);
                if (iret == 0)
                {
                    UIntPtr dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(m_curReader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST);
                    while (dnhReport.ToUInt64() != 0)
                    {
                        UInt32 AIPtype = 0, TagType = 0, AntId = 0;
                        byte dsfid = 0;
                        byte[] uid = new byte[8];
                        iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseTagDataReport(dnhReport, ref AIPtype, ref TagType, ref AntId, ref dsfid, uid);
                        if (iret == 0)
                        {
                            delegate_tag_report_handle addNewTag = new delegate_tag_report_handle(dele_tag_report_handler);
                            object[] pList = { AIPtype, TagType, AntId, uid, (Byte)8 };
                            Invoke(addNewTag, pList);
                        }
                        dnhReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(m_curReader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT);
                    }

                }
                idx++;
                if (idx >= m_hRS485.Count)
                {
                    idx = 0;
                }
            }
            if (dnInvenParamList.ToUInt64()!=0)
            {
                RFIDLIB.rfidlib_reader.DNODE_Destroy(dnInvenParamList);
            }
            Invoke(new delegateInventoryFinish(InventoryFinish));
        }


        private delegate void delegate_tag_report_handle(UInt32 AIPType, UInt32 tagType, UInt32 antID, Byte[] uid, Byte uidlen);
        private void dele_tag_report_handler(UInt32 AIPType, UInt32 tagType, UInt32 antID, Byte[] uid, Byte uidlen)
        {

            String tagtypeName;
            String strUid;
            strUid = BitConverter.ToString(uid, 0, (int)uidlen).Replace("-", string.Empty);
            if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_ICODE_SLI_ID)
            {
                tagtypeName = "NXP ICODE SLI";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_TI_HFI_PLUS_ID)
            {
                tagtypeName = "Ti HF-I Plus";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_ST_M24LRXX_ID)
            {
                tagtypeName = "ST M24LRxx";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_FUJ_MB89R118C_ID)
            {
                tagtypeName = "Fujitsu MB89R118C";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_ST_M24LR64_ID)
            {
                tagtypeName = "ST M24LR64";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_ST_M24LR16E_ID)
            {
                tagtypeName = "ST M24LR16E";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_ICODE_SLIX_ID)
            {
                tagtypeName = "NXP ICODE SLIX";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_TIHFI_STANDARD_ID)
            {
                tagtypeName = "Ti HF-I Standard";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_TIHFI_PRO_ID)
            {
                tagtypeName = "Ti HF-I Pro";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO14443A_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO14443A_PICC_NXP_ULTRALIGHT_ID)
            {
                tagtypeName = "NXP Mifare Ultralight";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO14443A_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID)
            {
                tagtypeName = "NXP Mifare S50";
            }
            else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO14443A_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO14443A_PICC_NXP_MIFARE_S70_ID)
            {
                tagtypeName = "NXP Mifare S70";
            }
            else
            {
                tagtypeName = "Unknown Tag";
            }
            bool found = false;
            int i;
            for (i = 0; i < listViewInventory.Items.Count; i++)
            {
                if (listViewInventory.Items[i].SubItems[1].Text == strUid && listViewInventory.Items[i].SubItems[3].Text == antID.ToString())
                {
                    found = true;
                    break;
                }

            }
            if (!found)
            {
                ListViewItem lvi = new ListViewItem();
                lvi.Text = tagtypeName;
                lvi.SubItems.Add(strUid);
                lvi.SubItems.Add("1");
                lvi.SubItems.Add(antID.ToString());
                listViewInventory.Items.Add(lvi);
            }
            else
            {
                String strCounter = listViewInventory.Items[i].SubItems[2].Text;
                int counter;
                counter = int.Parse(strCounter);
                counter++;
                if (counter >= 100000)
                {
                    counter = 1;
                }
                listViewInventory.Items[i].SubItems[2].Text = counter.ToString();
            }
        }

        private delegate void delegateInventoryFinish();
        private void InventoryFinish()
        {
            btnStart.Enabled = true;
            btnStop.Enabled = false;
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            listViewInventory.Items.Clear();
            Thread m_inventoryThrd = new Thread(DoInventory);
            btnStart.Enabled = false;
            btnStop.Enabled = true;
            m_inventoryThrd.Start();
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            b_inventoryFlg = false;
        }

        private void EnableAllCtr(bool isOpen)
        {
            cmbDevType.Enabled = !isOpen;
            cmbComName.Enabled = !isOpen;
            cmbBaud.Enabled = !isOpen;
            cmbFrame.Enabled = !isOpen;
            checkedListNode.Enabled = !isOpen;
            btnOpen.Enabled = !isOpen;
            btnClose.Enabled = isOpen;
            btnStart.Enabled = isOpen;
            btnStop.Enabled = false;
        }

        private void MainFrm_Load(object sender, EventArgs e)
        {

        }
    }
}