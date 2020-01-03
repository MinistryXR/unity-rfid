using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Collections;


namespace WindowsApplication2
{
   
    public partial class Form1 : Form
    {
        public UIntPtr hreader;
        public UIntPtr hTag;
        public UIntPtr hTagIcodeslix;
        public UIntPtr hTagTiHFIPlus;
        public Byte enableAFI;
        public Byte AFI;
        public bool EnableISO14443a;
        public Byte onlyNewTag;
        public bool asyncReport;
        public bool _shouldStop;
        public Byte openState;
        public Byte inventoryState;
        public Byte readerType;
        public Byte[] AntennaSel;
        public Byte AntennaSelCount;
        public ArrayList readerDriverInfoList;
        public ArrayList airInterfaceProtList;

        public static INVENTORY.PARAMETERS invenParams= new INVENTORY.PARAMETERS();
        //RFIDLIB.RFIDLIB_EVENT_CALLBACK callbackDelegate;        

        Thread InvenThread;
        public Form1()
        {
            InitializeComponent();
            hreader = (UIntPtr)0;
            hTag = (UIntPtr)0;
            hTagIcodeslix =(UIntPtr) 0 ;
            hTagTiHFIPlus= (UIntPtr) 0 ;

            enableAFI = 0;
            AFI = 0;
            onlyNewTag = 0;
            asyncReport = false;
            //callbackDelegate = new RFIDLIB.RFIDLIB_EVENT_CALLBACK(CallBack);
            openState = 0;
            inventoryState = 0;
            readerType = 0;
            AntennaSel = new byte[16];
            AntennaSelCount = 0;

            //comboBox2.SelectedIndex = 1;
            comboBox8.Items.Add("None addressed");
            comboBox8.Items.Add("Serial number");
            comboBox8.SelectedIndex = 0;
            comboBox8.Enabled = false;
            comboBox9.Enabled = false;

            comboBox14.SelectedIndex = 1;
            comboBox15.SelectedIndex = 0;

            //for (int i=0;i<64;i++)
            //{
            //    comboBox12.Items.Add(i.ToString());
            //}
            //comboBox12.SelectedIndex = 0;

            //comboBox13.Items.Add("Key A");
            //comboBox13.Items.Add("Key B");
            //comboBox13.SelectedIndex = 0;
            //button1.Enabled = true;
            //comboBox11.Enabled = true;
            //button20.Enabled = false;
            //comboBox12.Enabled = false;
            //comboBox13.Enabled = false;
            //textBox7.Enabled = false;
            //textBox8.Enabled = false;
            //textBox9.Enabled = false;
            //button20.Enabled = false;
            //button21.Enabled = false;
            //button22.Enabled = false;
            //button23.Enabled = false;
            //button24.Enabled = false;
            //button25.Enabled = false;
            //button26.Enabled = false;
            //button27.Enabled = false;
            

            readerDriverInfoList = new ArrayList() ;
            airInterfaceProtList = new ArrayList();


            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            StringBuilder drvpath = new StringBuilder();
            drvpath.Append('\0', 128);
            UInt32 ulRet;
            ulRet = RFIDLIB.rfidlib_reader.RDR_GetLibVersion(drvpath, (UInt32)drvpath.Capacity);
            if (ulRet > 0)
            {
                MessageBox.Show(drvpath.ToString());
            }

        }
        //public void CallBack(UIntPtr wparam, UIntPtr lparam)
        //{
        //    int iret;
        //   UInt32 aip_id = 0;
        //   UInt32 tag_id = 0;
        //   UInt32 ant_id = 0;
        //   Byte dsfid = 0;
        //   Byte[] uid = new Byte[8];
        //   iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseTagDataReport(lparam, ref aip_id, ref tag_id, ref ant_id, ref dsfid, uid);
        //   if (iret == 0)
        //   {
        //        /* It is ISO15693 tag data */
        //       object[] pList = { aip_id, tag_id, ant_id, dsfid, uid };
        //       Invoke(new InventoryTagReportEventHandler(AddTag), pList);
        //        //ListViewItem lvi = new ListViewItem();
        //        //lvi.Text = BitConverter.ToString(uid).Replace("-", string.Empty);
        //        //listView1.Items.Add(lvi);
        //   }

        //}
        private delegate void delegateInventoryFinishCallback();
        public void InventoryFinishCallback()
        {
            button5.Enabled = true;
            button6.Enabled = false;
            button3.Enabled = true;
            inventoryState = 0;
        }
        private delegate void InventoryTagReportEventHandler(  UInt32 aip_id,UInt32 tag_id ,UInt32 ant_id, Byte dsfid , Byte[] uid) ;
        public void AddTagISO14443A(UInt32 aip_id, UInt32 tag_id, UInt32 ant_id, Byte uidlen, Byte[] uid)
        {
            ListViewItem lvi = new ListViewItem();
            String tagtype;
            String strUid;
            strUid = BitConverter.ToString(uid, 0, uidlen).Replace("-", string.Empty);
            switch (tag_id)
            {
                case 1:
                    tagtype = "NXP Mifare Ultralight";
                    break;
                case 2:
                    tagtype = "NXP Mifare S50";
                    break;
                case 3:
                    tagtype = "NXP Mifare S70";
                    break;
                default:
                    tagtype = "Unknown tag";
                    break;
            }
            bool found = false;
            int i;
            for (i = 0; i < listView1.Items.Count; i++)
            {
                if (listView1.Items[i].SubItems[2].Text == strUid)
                {
                    found = true;
                    break;
                }

            }
            if (!found)
            {

                lvi.Text = tagtype;
                lvi.SubItems.Add("");
                lvi.SubItems.Add(strUid);
                lvi.SubItems.Add("1");
                listView1.Items.Add(lvi);
                comboBox1.Items.Add(strUid);
                if (tagtype=="NXP Mifare S50")
                {
                    //comboBox11.Items.Add(strUid);
                }

            }
            else
            {
                String strCounter = listView1.Items[i].SubItems[3].Text;
                int counter;
                counter = int.Parse(strCounter);
                counter++;
                if (counter >= 100000)
                {
                    counter = 1;
                }
                listView1.Items[i].SubItems[3].Text = counter.ToString();
            }
            label13.Text = listView1.Items.Count.ToString();
        }
        public void AddTag(UInt32 aip_id, UInt32 tag_id, UInt32 ant_id, Byte dsfid, Byte[] uid)
        {
            ListViewItem lvi = new ListViewItem();
            String tagtype;
            String strUid;
            strUid = BitConverter.ToString(uid,0,8).Replace("-", string.Empty);
            switch (tag_id)
            {
                case 1:
                    tagtype = "NXP ICODE SLI" ;
                    break;
                case 2:
                    tagtype= "Tag-it HF-I plus" ;
                    break;
                case 4:
                    tagtype="Fujitsu MB89R118C";
                    break;
                case 5:
                    tagtype="ST M24LR64" ;
                    break;
                case 6:
                    tagtype = "ST M24LR16E";
                    break;
                case 7:
                    tagtype = "NXP ICODE SLIX";
                    break;
                case 8:
                    tagtype = "Tag-it HF-I Standard";
                    break;
                case 9:
                    tagtype = "Tag-it HF-I Pro";
                    break;
                default:
                    tagtype = "Unknown tag";
                    break;
            }
            bool found = false;
            int i;
            for (i = 0; i < listView1.Items.Count; i++)
            {
                if (listView1.Items[i].SubItems[2].Text == strUid && listView1.Items[i].SubItems[4].Text == ant_id.ToString())
                {
                    found = true;
                    break;
                }

            }
            if (!found)
            {
                Byte[] baDsfid = new Byte[1];
                baDsfid[0] = dsfid;
                lvi.Text = tagtype;
                lvi.SubItems.Add(BitConverter.ToString(baDsfid).Replace("-", string.Empty));
                lvi.SubItems.Add(strUid);
                lvi.SubItems.Add("1");
                lvi.SubItems.Add(ant_id.ToString());
                listView1.Items.Add(lvi);
                //comboBox3.Items.Add(strUid);
            }
            else
            {
                String strCounter = listView1.Items[i].SubItems[3].Text;
                int counter;
                counter = int.Parse(strCounter);
                counter++;
                if (counter >= 100000)
                {
                    counter = 1;
                }
                listView1.Items[i].SubItems[3].Text = counter.ToString();
            }
            label13.Text = listView1.Items.Count.ToString();
        }
        public delegate void delegate_tag_report_handle(UInt32 AIPType, UInt32 tagType, UInt32 antID, UInt32 metaFlags, Byte[] tagData, UInt32 datlen, String writeOper,String lockOper);
        public void dele_tag_report_handler(UInt32 AIPType, UInt32 tagType, UInt32 antID, UInt32 metaFlags, Byte[] tagData, UInt32 datlen, String writeOper, String lockOper)
        {
            UInt16 epcBitsLen = 0;
            int idx = 0;
            List<Byte> epc;
            List<Byte> readData;
            int i;
            String strAntId;
            UInt32 timestamp;
            UInt32 frequency;
            Byte rssi;
            Byte readCnt;

            strAntId = antID.ToString() ;


            epc = new List<byte>();
            readData = new List<byte>();
            timestamp = 0;
            frequency = 0;
            rssi = 0;
            readCnt = 0;
            if (metaFlags == 0) metaFlags |= RFIDLIB.rfidlib_def.ISO18000p6C_META_BIT_MASK_EPC;
            if ((metaFlags & RFIDLIB.rfidlib_def.ISO18000p6C_META_BIT_MASK_EPC) > 0)
            {
                if (datlen < 2)
                {
                    //error data size 
                    return;
                }

                epcBitsLen = (UInt16)(tagData[idx] | (tagData[idx+1] << 8));
                idx += 2;
                int epcBytes = ((epcBitsLen + 7) / 8);
                if ((datlen - idx) < epcBytes)
                {
                    // error data size 
                    return;
                }
                for (i = 0; i < epcBytes; i++) epc.Add(tagData[idx + i]);
                idx += epcBytes;
            }
            if ((metaFlags & RFIDLIB.rfidlib_def.ISO18000P6C_META_BIT_MASK_TIMESTAMP) > 0)
            {
                if ((datlen - idx) < 4)
                {
                    //error data size 
                    return;
                }
                timestamp = (UInt32)(tagData[idx] | (tagData[idx + 1] << 8 & 0xff00) | (tagData[idx + 2] << 16 & 0xff0000) | (tagData[idx + 3] << 24 & 0xff000000));
                idx += 4;
            }
            if ((metaFlags & RFIDLIB.rfidlib_def.ISO18000P6C_META_BIT_MASK_FREQUENCY) > 0)
            {
                if ((datlen - idx) < 4)
                {
                    //error data size 
                    return;
                }
                frequency = (UInt32)(tagData[idx] | (tagData[idx + 1] << 8 & 0xff00) | (tagData[idx + 2] << 16 & 0xff0000) | (tagData[idx + 3] << 24 & 0xff000000));
                idx += 4;
            }
            if ((metaFlags & RFIDLIB.rfidlib_def.ISO18000p6C_META_BIT_MASK_RSSI) > 0)
            {
                if ((datlen - idx) < 1)
                {
                    //error data size 
                    return;
                }
                rssi = tagData[idx];
                idx += 1;
            }
            if ((metaFlags & RFIDLIB.rfidlib_def.ISO18000P6C_META_BIT_MASK_READCOUNT) > 0)
            {
                if ((datlen - idx) < 1)
                {
                    //error data size 
                    return;
                }
                readCnt = tagData[idx];
                idx += 1;
            }
            if ((metaFlags & RFIDLIB.rfidlib_def.ISO18000P6C_META_BIT_MASK_TAGDATA) > 0)
            {
                for (i = idx; i < datlen; i++) readData.Add(tagData[i]);
            }

            String strEPC = BitConverter.ToString(epc.ToArray(), 0, epc.Count).Replace("-", string.Empty);
            String strUid = BitConverter.ToString(readData.ToArray(), 0, readData.Count).Replace("-", string.Empty);

            bool found = false;
            for (i = 0; i < listView1.Items.Count; i++)
            {
                if (listView1.Items[i].SubItems[1].Text == strUid && listView1.Items[i].SubItems[2].Text == strAntId)
                {
                    found = true;
                    break;
                }

            }
            if (!found)
            {
                ListViewItem lvi = new ListViewItem();
                lvi.Text = "1";
                lvi.SubItems.Add(strEPC);
                lvi.SubItems.Add(strUid);
                lvi.SubItems.Add(strAntId);
                Byte[] byTimestamp = new Byte[3]  ;
                byTimestamp[0] =(Byte)(timestamp>> 16 & 0xff);
                byTimestamp[1] =(Byte)(timestamp>> 8 & 0xff);
                byTimestamp[2] =(Byte)(timestamp & 0xff );
                lvi.SubItems.Add(BitConverter.ToString(byTimestamp, 0, byTimestamp.Length).Replace("-", string.Empty));

                frequency = frequency / 1000;
                lvi.SubItems.Add(frequency.ToString());
                lvi.SubItems.Add(rssi.ToString());
                lvi.SubItems.Add(readCnt.ToString());
                lvi.SubItems.Add(writeOper);
                lvi.SubItems.Add(lockOper);

                listView1.Items.Add(lvi);

            }
            else
            {
                String strCounter = listView1.Items[i].SubItems[0].Text;
                int counter;
                counter = int.Parse(strCounter);
                counter++;
                if (counter >= 100000)
                {
                    counter = 1;
                }
                listView1.Items[i].SubItems[0].Text = counter.ToString();

                Byte[] byTimestamp = new Byte[3];
                byTimestamp[0] = (Byte)(timestamp >> 16 & 0xff);
                byTimestamp[1] =(Byte)( timestamp >> 8 & 0xff);
                byTimestamp[2] = (Byte)(timestamp & 0xff);
                listView1.Items[i].SubItems[3].Text=BitConverter.ToString(byTimestamp, 0, byTimestamp.Length).Replace("-", string.Empty);

                frequency = frequency / 1000;
                listView1.Items[i].SubItems[4].Text=frequency.ToString();
                listView1.Items[i].SubItems[5].Text=rssi.ToString();
                listView1.Items[i].SubItems[6].Text =readCnt.ToString();
                listView1.Items[i].SubItems[7].Text = writeOper;
                listView1.Items[i].SubItems[8].Text = lockOper;

            }
            label13.Text = listView1.Items.Count.ToString();

        }
        public int tag_inventory(
                                Byte AIType,
                                 Byte AntennaSelCount,
                                 Byte[] AntennaSel,
                                delegate_tag_report_handle tagReportHandler,
                                 ref UInt32 nTagCount )
        {

            int iret;
            UIntPtr InvenParamSpecList = UIntPtr.Zero;
            InvenParamSpecList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
            if (InvenParamSpecList.ToUInt64() != 0)
            {
                /* set timeout */
                RFIDLIB.rfidlib_reader.RDR_SetInvenStopTrigger(InvenParamSpecList,RFIDLIB.rfidlib_def. INVEN_STOP_TRIGGER_TYPE_TIMEOUT, invenParams.m_timeout, 0);
                /* create ISO18000p6C air protocol inventory parameters */
                UIntPtr  AIPIso18000p6c = RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_CreateInvenParam(InvenParamSpecList, 0, 0, RFIDLIB.rfidlib_def.ISO18000p6C_S0, RFIDLIB.rfidlib_def.ISO18000p6C_TARGET_A, RFIDLIB.rfidlib_def.ISO18000p6C_Dynamic_Q);
                if(AIPIso18000p6c.ToUInt64() != 0) {
                    //set selection parameters
                    if (invenParams.m_sel.m_enable)
                    {
                        Byte[] maskBits = invenParams.m_sel.m_maskBits.ToArray();
                        RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_SetInvenSelectParam(AIPIso18000p6c, invenParams.m_sel.m_target, invenParams.m_sel.m_action, invenParams.m_sel.m_memBank, invenParams.m_sel.m_pointer, maskBits, invenParams.m_sel.m_maskBitsLength, 0);

                    }
                    // set inventory read parameters
                    if(invenParams.m_read.m_enable) {
                        RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_SetInvenReadParam(AIPIso18000p6c ,invenParams.m_read.m_memBank,invenParams.m_read.m_wordPtr,(Byte)invenParams.m_read.m_wordCnt) ;
                    }

                    // Add Embedded commands
                    if(invenParams.m_write.m_enable) {
                        Byte[] writeDatas = invenParams.m_write.m_datas.ToArray() ;
             
                        RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_CreateTAWrite(AIPIso18000p6c, invenParams.m_write.m_memBank, invenParams.m_write.m_wordPtr, invenParams.m_write.m_wordCnt, writeDatas, (UInt32)writeDatas.Length); 
                    }

                    if (invenParams.m_lock.m_enable)
                    {
                        UInt16 mask ,action ;
                        mask = action = 0 ;
                        if (invenParams.m_lock.m_userMemSelected)
                        {
                            mask |= 0x03;
                            action |=(UInt16)( invenParams.m_lock.m_userMem);
                        }
                        if (invenParams.m_lock.m_TIDMemSelected)
                        {
                            mask |= (0x03 << 2);
                            action |= (UInt16)(invenParams.m_lock.m_TIDMem << 2);
                        }
                        if (invenParams.m_lock.m_EPCMemSelected)
                        {
                            mask |= (0x03 << 4);
                            action |= (UInt16)(invenParams.m_lock.m_EPCMem << 4);
                        }
                        if (invenParams.m_lock.m_accessPwdSelected)
                        {
                            mask|=(0x03 << 6) ;
                            action |= (UInt16)(invenParams.m_lock.m_accessPwd << 6);
                        }
                        if (invenParams.m_lock.m_killPwdSelected)
                        {
                            mask |= (0x03 << 8);
                            action |= (UInt16)(invenParams.m_lock.m_killPwd << 8);
                        }
                        
                        RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_CreateTALock(AIPIso18000p6c,mask,action) ;
                    }
                    // set meta flags 
                    if (invenParams.m_metaFlags.m_enable)
                    {
                        UInt32 metaFlags=0 ;
                        if (invenParams.m_metaFlags.m_EPC)
                        {
                            metaFlags |= RFIDLIB.rfidlib_def.ISO18000p6C_META_BIT_MASK_EPC;
                        }
                        if (invenParams.m_metaFlags.m_timestamp)
                        {
                            metaFlags |= RFIDLIB.rfidlib_def.ISO18000P6C_META_BIT_MASK_TIMESTAMP;
                        }
                        if(invenParams.m_metaFlags.m_frequency ) {
                            metaFlags |= RFIDLIB.rfidlib_def.ISO18000P6C_META_BIT_MASK_FREQUENCY;
                        }
                        if(invenParams.m_metaFlags.m_RSSI) {
                            metaFlags |= RFIDLIB.rfidlib_def.ISO18000p6C_META_BIT_MASK_RSSI;
                        }
                        if(invenParams.m_metaFlags.m_readCnt ) {
                            metaFlags |= RFIDLIB.rfidlib_def.ISO18000P6C_META_BIT_MASK_READCOUNT;    
                        }
                        if(invenParams.m_metaFlags.m_tagData) {
                            metaFlags |= RFIDLIB.rfidlib_def.ISO18000P6C_META_BIT_MASK_TAGDATA;
                        }
                        RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_SetInvenMetaDataFlags(AIPIso18000p6c ,metaFlags);
                    }
                    // set access password
                    if (invenParams.m_read.m_enable || invenParams.m_write.m_enable || invenParams.m_lock.m_enable)
                    {
                        RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_SetInvenAccessPassword(AIPIso18000p6c ,invenParams.m_accessPwd);
                    }
                }

            }
            nTagCount = 0;
        LABEL_TAG_INVENTORY:
            iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, AIType, AntennaSelCount, AntennaSel, InvenParamSpecList);
            if (iret == 0 || iret == -21)
            {
                nTagCount += RFIDLIB.rfidlib_reader.RDR_GetTagDataReportCount(hreader);
                UIntPtr TagDataReport;
                TagDataReport = (UIntPtr)0;
                TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST); //first
                while (TagDataReport.ToUInt64() > 0)
                {
                    UInt32 aip_id = 0;
                    UInt32 tag_id = 0;
                    UInt32 ant_id = 0;
                    Byte[] tagData = new Byte[256];
                    UInt32 nSize =(UInt32)tagData.Length ;
                    UInt32 metaFlags = 0;

                    iret = RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_ParseTagReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, ref metaFlags, tagData, ref nSize);
                    if (iret == 0)
                    {
                        String writeOper = "";
                        String lockOper = "";
                        if (invenParams.m_write.m_enable)
                        {
                            iret = RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_CheckTAWriteResult(TagDataReport);
                            if (iret != 0)
                            {
                                writeOper = "fail";
                            }
                            else
                            {
                                writeOper = "success";

                            }
                        }
                        if(invenParams.m_lock.m_enable)
                        {
                            iret = RFIDLIB.rfidlib_aip_iso18000p6C.ISO18000p6C_CheckTALockResult(TagDataReport);
                            if (iret != 0)
                            {
                                lockOper = "fail";
                            }
                            else
                            {
                                lockOper = "success";
                            }
                        }
                        object[] pList = { aip_id, tag_id, ant_id, metaFlags, tagData, nSize, writeOper, lockOper };
                        Invoke(tagReportHandler, pList);
                    }

                    TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT); //next
                }
                if (iret == -21) // stop trigger occur,need to inventory left tags
                {
                    AIType = RFIDLIB.rfidlib_def.AI_TYPE_CONTINUE;//use only-new-tag inventory 
                    goto LABEL_TAG_INVENTORY;
                }
                iret = 0;
            }
            if (InvenParamSpecList.ToUInt64() != 0) RFIDLIB.rfidlib_reader.DNODE_Destroy(InvenParamSpecList);
            return iret;
        }
        public void DoInventory()
        {
            delegate_tag_report_handle cbTagReportHandle; 

            cbTagReportHandle = new delegate_tag_report_handle(dele_tag_report_handler) ;

            int iret;
            Byte AIType = RFIDLIB.rfidlib_def.AI_TYPE_NEW;
            if (onlyNewTag == 1)
            {
                AIType = RFIDLIB.rfidlib_def.AI_TYPE_CONTINUE;  //only new tag inventory 
            }
            while (!_shouldStop)
            {

                UInt32 nTagCount =0 ;
                iret = tag_inventory( AIType, 0, AntennaSel, cbTagReportHandle, ref nTagCount);
                if (iret == 0)
                {
                    // inventory ok

                }
                else {
                    // inventory error 
                }
                AIType =  RFIDLIB.rfidlib_def.AI_TYPE_NEW;
                if (onlyNewTag == 1)
                {
                    AIType = RFIDLIB.rfidlib_def.AI_TYPE_CONTINUE;  //only new tag inventory 
                }
            }
            object[] pFinishList = { };
            Invoke(new delegateInventoryFinishCallback(InventoryFinishCallback), pFinishList);

            /*
             *  If API RDR_SetCommuImmeTimeout is called when stop, API RDR_ResetCommuImmeTimeout 
             *  must be called too, Otherwise, an error -5 may occurs .
             */
            RFIDLIB.rfidlib_reader.RDR_ResetCommuImmeTimeout(hreader);

        }
        //public void DoInventory()
        //{

        //    UIntPtr InvenParamSpecList;
        //    InvenParamSpecList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
        //    if (InvenParamSpecList.ToUInt64() != 0)
        //    {
        //        for(int i = 0; i < airInterfaceProtList.Count; i++)
        //        {
        //            CSupportedAirProtocol aip;
        //            aip = (CSupportedAirProtocol)airInterfaceProtList[i];
        //            if (aip.m_en)
        //            {
        //                if(aip.m_ID == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID) {
        //                    //create ISO15693 inventory parameter  
        //                    RFIDLIB.rfidlib_aip_iso15693.ISO15693_CreateInvenParam(InvenParamSpecList, 0, enableAFI, AFI, 0);
        //                }
        //                else if (aip.m_ID == RFIDLIB.rfidlib_def.RFID_APL_ISO14443A_ID)
        //                {
        //                    //create ISO14443A inventory parameter  
        //                    RFIDLIB.rfidlib_aip_iso14443A.ISO14443A_CreateInvenParam(InvenParamSpecList, 0 /* apply to all antenna */);
        //                }
        //            }
        //        }
        //    }
        //    int iret;
        //    Byte AIType = 1;
        //    while (!_shouldStop)
        //    {
        //        if (onlyNewTag == 1)
        //        {
        //            AIType = 2;  //only new tag inventory 
        //        }

        //    DO_INVENTORY_LABEL:
        //        iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, AIType, AntennaSelCount, AntennaSel, InvenParamSpecList);
        //        if (iret == 0 || iret == -21)
        //        {

        //            // inventory ok 
        //            UInt32 nTagCount = RFIDLIB.rfidlib_reader.RDR_GetTagDataReportCount(hreader);
        //            if (asyncReport == false)
        //            {
        //                UIntPtr TagDataReport;
        //                TagDataReport = (UIntPtr)0;
        //                TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, 1); //first
        //                while (TagDataReport.ToUInt64() > 0)
        //                {
        //                    UInt32 aip_id = 0;
        //                    UInt32 tag_id = 0;
        //                    UInt32 ant_id = 0;
        //                    Byte dsfid = 0;
        //                    Byte uidlen =0 ;
        //                    Byte[] uid = new Byte[16];
        //                    iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, ref dsfid, uid);
        //                    if (iret == 0)
        //                    {
        //                        // It is ISO15693 tag data 
        //                        object[] pList = { aip_id,tag_id,ant_id,dsfid,uid };
        //                        Invoke(new InventoryTagReportEventHandler(AddTag), pList);
        //                    }
        //                    iret = RFIDLIB.rfidlib_aip_iso14443A.ISO14443A_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, uid, ref uidlen);
        //                    if(iret == 0){
        //                        // It is ISO15693 tag data 
        //                        object[] pList = { aip_id, tag_id, ant_id, uidlen, uid };
        //                        Invoke(new InventoryTagReportEventHandler(AddTagISO14443A), pList);
        //                    }
        //                    TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, 2); //next
        //                }
        //            }
        //            if (iret == -21) // stop trigger occur,need to inventory left tags
        //            {
        //                AIType = 2;//use only-new-tag inventory 
        //                goto DO_INVENTORY_LABEL;
        //            }

        //        }


        //    }
        //    /*
        //     * NOTE: release the InvenParamSpecList here
        //     */
        //    RFIDLIB.rfidlib_data_node.DNODE_Destroy(InvenParamSpecList);
        //    object[] pFinishList = { };
        //    Invoke(new delegateInventoryFinishCallback(InventoryFinishCallback), pFinishList);

        //    /*
        //     *  If API RDR_SetCommuImmeTimeout is called when stop, API RDR_ResetCommuImmeTimeout 
        //     *  must be called too, Otherwise, an error -5 may occurs .
        //     */
        //    RFIDLIB.rfidlib_reader.RDR_ResetCommuImmeTimeout(hreader);

        //}
        private void button2_Click(object sender, EventArgs e)
        {
            if (comboBox6.SelectedIndex == -1)
            {
                MessageBox.Show("select reader driver type");
                return;
            }
            if(comboBox10.SelectedIndex == -1){
                MessageBox.Show("select communication type");
                return;
            }
            Byte usbOpenType = 0;
            usbOpenType =(Byte) comboBox8.SelectedIndex ;

            
            readerType = (Byte)comboBox6.SelectedIndex;

            int iret =0;
            UInt32 antennaCount = 0;
            button2.Enabled = false;

            // Use new way to open reader driver
            int commTypeIdx = comboBox10.SelectedIndex;
            string readerDriverName = ((CReaderDriverInf)(readerDriverInfoList[readerType])).m_name;
            string connstr ="";
            if (commTypeIdx == 0){
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE +"="+ readerDriverName + ";"+
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME+"=" + comboBox1.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + comboBox14.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + comboBox15.Text + ";" + 
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR+"="+"255" ;
            }
            else if (commTypeIdx == 1){
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE+"="+usbOpenType.ToString() +";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=" + comboBox9.Text;
            }
            else if(commTypeIdx == 2){
                string ipAddr;
                UInt16 port;
                ipAddr = textBox5.Text;
                port =(UInt16) int.Parse(textBox6.Text);
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_NET + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEIP + "=" + ipAddr + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEPORT + "=" + port.ToString() + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_LOCALIP + "=" + "";
            }

            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                MessageBox.Show("fail");
                button2.Enabled = true;
            }
            else
            {
                //antennaCount = RFIDLIB.rfidlib_reader.RDR_GetAntennaInterfaceCount(hreader);

                //MessageBox.Show("ok");
                button2.Enabled = false;
                button3.Enabled = true;
                button4.Enabled = true;
                button5.Enabled = true;
                button1.Enabled = true;
                //button7.Enabled = true;
                //button30.Enabled = true;

             


                UInt32 index = 0;
   
                //UInt32 AIType;
                //while (true)
                //{
                //    AIType = 0;
                //    iret = RFIDLIB.rfidlib_reader.RDR_GetSupportedAirInterfaceProtocol(hreader, index, ref AIType);
                //    if (iret != 0)
                //    {
                //        break;
                //    }
                //    StringBuilder namebuf = new StringBuilder();
                //    namebuf.Append('\0', 128);
                //    RFIDLIB.rfidlib_reader.RDR_GetAirInterfaceProtName(hreader, AIType, namebuf,(UInt32) namebuf.Capacity);

                //    CSupportedAirProtocol aip = new CSupportedAirProtocol();
                //    aip.m_ID = AIType;
                //    aip.m_name = namebuf.ToString();
                //    aip.m_en = true;
                //    airInterfaceProtList.Add(aip);

                    
                //    index++;
                //}

                openState = 1;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int iret=0;
            if (hTag != (UIntPtr) 0)
            {
                MessageBox.Show("disconnect from tag first!");
                return;
            }

           iret = RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            if (iret == 0)
            {
                hreader = (UIntPtr)0;
                //MessageBox.Show("ok");
                button2.Enabled = true;
                button3.Enabled = false;
                button4.Enabled = false;
                button5.Enabled = false;
                //button7.Enabled = false;

                openState = 0;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {

        }
        public const Byte  TX_ANT=0;
        public const Byte  RX_ANT = 1;
        private void button5_Click(object sender, EventArgs e)
        {
            _shouldStop = false;
            listView1.Items.Clear();

            onlyNewTag = 0;


            InvenThread = new Thread(DoInventory);
            InvenThread.Start();
            button5.Enabled = false ;
            button6.Enabled = true;
            button3.Enabled = false;

            inventoryState = 1;
            return;
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
  

        private void button6_Click(object sender, EventArgs e)
        {
            
           
        }
        public static byte[] StringToByteArrayFastest(string hex)
        {
            if (hex.Length % 2 == 1)
                throw new Exception("The binary key cannot have an odd number of digits");

            int len = hex.Length >> 1 ;
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


      


        String ByteToHex(Byte val)
        {
            Char[] chs = new Char[2];
            Byte left, right;
            left =(Byte)( val >> 4 & 0x0f);
            right =(Byte) ( val & 0x0f);
            if (left >= 0 && left <= 9)
            {
                chs[0] = (Char)('0' + left);
            }
            else
            {
                chs[0] = (Char)('A' + (left - 10));
            }
            if (right >= 0 && right <= 9)
            {
                chs[1] = (Char)('0' + right);
            }
            else
            {
                chs[1] = (Char)('A' + (right - 10));
            }

            String hex=new string(chs);
            return hex ;
        }


        private void button6_Click_1(object sender, EventArgs e)
        {
            button6_Click(sender, e);
        }

        private void button5_Click_1(object sender, EventArgs e)
        {
            button5_Click(sender, e);
        }


      
        private void button6_Click_2(object sender, EventArgs e)
        {
            button6.Enabled = false;
            _shouldStop = true;
            /*
             * Exit the inventory quickly
             */
            RFIDLIB.rfidlib_reader.RDR_SetCommuImmeTimeout(hreader); 

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (inventoryState> 0)
            {
                MessageBox.Show("stop inventory first!");
                e.Cancel = true;
                return;
            }
            if (openState > 0)
            {
                MessageBox.Show("close reader driver first!");
                e.Cancel = true;
            }
        }


        private void Form1_Load(object sender, EventArgs e)
        {
 
            comboBox1.SelectedIndex = 0;
            /* Load all reader driver dll, like "rfidlib_ANRD201.dll" */ 
            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
            /* enum and show loaded reader driver */
            UInt32 nCount;
            nCount = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();
            uint i;
            for( i=0;i<nCount;i++){
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

            for(i=0;i<readerDriverInfoList.Count;i++)
            {
                CReaderDriverInf drv = (CReaderDriverInf)(readerDriverInfoList[(int)i]);
                comboBox6.Items.Add(drv.m_name);
            }
            if (comboBox6.Items.Count > 0) comboBox6.SelectedIndex = 0;

            /* enum PC serial ports */
            comboBox1.Items.Clear();
            UInt32 nCOMCnt = RFIDLIB.rfidlib_reader.COMPort_Enum();
            for ( i = 0; i < nCOMCnt; i++)
            {
                StringBuilder comName = new StringBuilder();
                comName.Append('\0', 64);
                RFIDLIB.rfidlib_reader.COMPort_GetEnumItem(i, comName, (UInt32)comName.Capacity);
                comboBox1.Items.Add(comName);
            }
            if (comboBox1.Items.Count > 0) comboBox1.SelectedIndex = 0;
            comboBox1.Enabled = true;
            comboBox10.SelectedIndex = 0;

            
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button19_Click_1(object sender, EventArgs e)
        {
         
        }

        private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
        {
            CReaderDriverInf driver = (CReaderDriverInf)readerDriverInfoList[comboBox6.SelectedIndex];

            if((driver.m_commTypeSupported & RFIDLIB.rfidlib_def.COMMTYPE_USB_EN) > 0){
                comboBox9.Items.Clear();
                UInt32 nCount = RFIDLIB.rfidlib_reader.HID_Enum(driver.m_name);
                int iret;
                int i;
                for ( i = 0; i < nCount; i++)
                {
                    StringBuilder sernum = new StringBuilder();
                    sernum.Append('\0', 64);
                    UInt32 nSize;
                    nSize = (UInt32)sernum.Capacity;
                    iret = RFIDLIB.rfidlib_reader.HID_GetEnumItem((UInt32)i, RFIDLIB.rfidlib_def.HID_ENUM_INF_TYPE_SERIALNUM, sernum,ref nSize);
                    if (iret == 0)
                    {
                        comboBox9.Items.Add(sernum.ToString());
                    }
                }
            }
        }

        private void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox8.SelectedIndex == 0)
            {
                comboBox9.Enabled = false;
            }
            else
            {
                comboBox9.Enabled = true;
            }
        }

        private void button4_Click_1(object sender, EventArgs e)
        {
            int iret;
            StringBuilder devInfor = new StringBuilder();
            devInfor.Append('\0', 128);
            UInt32 nSize ;
            nSize =(UInt32) devInfor.Capacity ;
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

        private void comboBox10_SelectedIndexChanged(object sender, EventArgs e)
        {
            comboBox1.Enabled = false;
            comboBox8.Enabled = false;
            comboBox9.Enabled = false;
            textBox5.Enabled = false;
            textBox6.Enabled = false;
            comboBox14.Enabled = false;
            comboBox15.Enabled = false;
            if (comboBox10.SelectedIndex == 0)
            {
                comboBox1.Enabled = true;
                comboBox14.Enabled = true;
                comboBox15.Enabled = true;
            }
            else if(comboBox10.SelectedIndex == 1){
                comboBox8.Enabled = true;
                comboBox9.Enabled = true;
            }
            else if(comboBox10.SelectedIndex == 2){
                textBox5.Enabled = true;
                textBox6.Enabled = true;
            }
        }

        



      



        private void button1_Click_2(object sender, EventArgs e)
        {
            Form2 frm;
            frm = new Form2();
            frm.ShowDialog();
        }

        private void listView1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }
    }
  
    public class TagReportEvent:Object 
    {
        public UInt32 aipType;
        public UInt32 tagType;
        public UInt32 antID;
        public Byte dsfid;
        public Byte[] uid;
        TagReportEvent()
        {
            aipType = 0;
            tagType = 0;
            antID = 0;
            dsfid = 0;
            uid = new Byte[8] ;
        }

    }
    public class CReaderDriverInf
    {
        public string m_catalog;
        public string m_name;
        public string m_productType;
        public UInt32  m_commTypeSupported;
    } 
    public class CSupportedAirProtocol
    {
        public UInt32 m_ID;
        public string m_name;
        public Boolean m_en;
    }
}