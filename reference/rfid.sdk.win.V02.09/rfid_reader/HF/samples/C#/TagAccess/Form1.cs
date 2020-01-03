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
        public Byte onlyNewTag;
        public bool _shouldStop;
        public Byte openState;
        public Byte inventoryState;
        public Byte readerType;
        public Byte[] AntennaSel;
        public Byte AntennaSelCount;
        public ArrayList readerDriverInfoList;
        public ArrayList airInterfaceProtList;
        public List<String> m_blueAddrList = new List<string>();     

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
            openState = 0;
            inventoryState = 0;
            readerType = 0;
            AntennaSel = new byte[16];
            AntennaSelCount = 0;

            comboBox2.SelectedIndex = 1;
            comboBox8.Items.Add("None addressed");
            comboBox8.Items.Add("Serial number");
            comboBox8.SelectedIndex = 0;
            comboBox8.Enabled = false;
            comboBox9.Enabled = false;

            comboBox14.SelectedIndex = 1;
            comboBox15.SelectedIndex = 0;

            for (int i=0;i<64;i++)
            {
                comboBox12.Items.Add(i.ToString());
            }
            comboBox12.SelectedIndex = 0;

            comboBox13.Items.Add("Key A");
            comboBox13.Items.Add("Key B");
            comboBox13.SelectedIndex = 0;
            button1.Enabled = true;
            comboBox11.Enabled = true;
            button20.Enabled = false;
            comboBox12.Enabled = false;
            comboBox13.Enabled = false;
            textBox7.Enabled = false;
            textBox8.Enabled = false;
            textBox9.Enabled = false;
            button20.Enabled = false;
            button21.Enabled = false;
            button22.Enabled = false;
            button23.Enabled = false;
            button24.Enabled = false;
            button25.Enabled = false;
            button26.Enabled = false;
            button27.Enabled = false;
            

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
        private delegate void delegateInventoryFinishCallback();
        public void InventoryFinishCallback()
        {
            button5.Enabled = true;
            button6.Enabled = false;
            button3.Enabled = true;
            inventoryState = 0;
        }
     
        public delegate void delegate_tag_report_handle(UInt32 AIPType, UInt32 tagType, UInt32 antID, Byte[] uid, int uidlen);
        public void dele_tag_report_handler(UInt32 AIPType, UInt32 tagType, UInt32 antID, Byte[] uid, int uidlen)
        {
            
            String strUid;

            int iret;
            String strAIPName ,strTagTypeName;
            StringBuilder sbAIPName = new StringBuilder();
            sbAIPName.Append('\0', 128);
            UInt32 nSize = (UInt32)sbAIPName.Capacity;
            iret =RFIDLIB.rfidlib_reader.RDR_GetAIPTypeName(hreader, AIPType, sbAIPName, ref nSize);
            if (iret != 0)
            {
                strAIPName ="Unknown" ;
            }
            else {
               strAIPName =      sbAIPName.ToString() ;
            }

            StringBuilder sbTagName = new StringBuilder() ;
            sbTagName.Append('\0', 128);
            nSize =(UInt32) sbTagName.Capacity;
            iret = RFIDLIB.rfidlib_reader.RDR_GetTagTypeName(hreader, AIPType,tagType ,sbTagName, ref nSize);
            if (iret != 0)
            {
                strTagTypeName = "Unknown";
            }
            else
            {
                strTagTypeName = sbTagName.ToString();
            }

            strUid = BitConverter.ToString(uid, 0, (int)uidlen).Replace("-", string.Empty);

     
            bool found = false;
            int i;
            for (i = 0; i < listView1.Items.Count; i++)
            {
                if (listView1.Items[i].SubItems[2].Text == strUid && listView1.Items[i].SubItems[4].Text == antID.ToString())
                {
                    found = true;
                    break;
                }

            }
            if (!found)
            {
                MessageBox.Show("found " + strUid);
                ListViewItem lvi = new ListViewItem();
                lvi.Text = strAIPName;
                lvi.SubItems.Add(strTagTypeName);
                lvi.SubItems.Add(strUid);
                lvi.SubItems.Add("1");
                lvi.SubItems.Add(antID.ToString());
                listView1.Items.Add(lvi);

                tagInfo ti = new tagInfo(strUid, tagType);
                comboBox3.Items.Add(ti);
                comboBox11.Items.Add(ti);
                comboBox16.Items.Add(ti);
                comboBox29.Items.Add(ti);
                comboBox38.Items.Add(ti);
                comboBox42.Items.Add(ti);
                
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

            /* you can try to read or write tag below */
            //int iret ;
            //UIntPtr hTag = UIntPtr.Zero ;
            //if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID){
            //     /* iso15693 example to read multiple blocks here */
            //    iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Connect(hreader, tagType, 1, uid, ref hTag);
            //    if(iret == 0){
            //        UInt32 numOfBlksRead ;
            //        UInt32 bytesRead;
            //        Byte[] bufBlocks = new Byte[64];
            //        numOfBlksRead = bytesRead =0 ;
            //        iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ReadMultiBlocks(hreader, hTag, 1, 0, 4, ref numOfBlksRead, bufBlocks,(UInt32) bufBlocks.GetLength(0), ref bytesRead);
            //        if(iret == 0){
            //            /* read multiple blocks ok */
            //        }

            //        RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
            //    }
            //}
            //else if (AIPType == RFIDLIB.rfidlib_def.RFID_APL_ISO14443A_ID && tagType == RFIDLIB.rfidlib_def.RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID)
            //{
            //    /* iso14443a mifare s50 read block example here */
            //    iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_Connect(hreader, 0/* 0:s50,1:s70*/, uid, ref hTag);
            //    if(iret == 0){
            //        Byte[] block = new Byte[16] ;
            //        iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_ReadBlock(hreader,hTag,0,block,(UInt32)block.GetLength(0)) ;
            //        if(iret == 0) {
            //            /* read block ok*/
            //        }
            //        RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
            //    }
            //}

        }
        public int tag_inventory(
                               Byte AIType,
                                 Byte AntennaSelCount,
                                 Byte[] AntennaSel,
                                bool enable15693,
                                bool enable14443A,
                                bool enable18000p3m3,
                                  Byte enableAFI,
                                 Byte afiVal,
                                delegate_tag_report_handle tagReportHandler,
                                 ref UInt32 nTagCount)
        {

            int iret;
            UIntPtr InvenParamSpecList = UIntPtr.Zero;
            InvenParamSpecList = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList();
            if (InvenParamSpecList.ToUInt64() != 0)
            {
                if (enable15693 == true)
                {
                    RFIDLIB.rfidlib_aip_iso15693.ISO15693_CreateInvenParam(InvenParamSpecList, 0, 0, 0, 0);
                }
                if (enable14443A == true)
                {
                    RFIDLIB.rfidlib_aip_iso14443A.ISO14443A_CreateInvenParam(InvenParamSpecList, 0);
                }
                if (enable18000p3m3)
                {
                    RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_CreateInvenParam(InvenParamSpecList, 0, 0, 0, RFIDLIB.rfidlib_def.ISO18000p6C_Dynamic_Q);
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
                    Byte dsfid = 0;
                    Byte uidlen = 0;
                    Byte[] uid = new Byte[16];

                    /* Parse iso15693 tag report */
                    if (enable15693 == true)
                    {
                        iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, ref dsfid, uid);
                        if (iret == 0)
                        {
                            uidlen = 8;
                            object[] pList = { aip_id, tag_id, ant_id, uid, (int)uidlen };
                            Invoke(tagReportHandler, pList);
                            //tagReportHandler(hreader, aip_id, tag_id, ant_id, uid ,8);
                        }
                    }

                    /* Parse Iso14443A tag report */
                    if (enable14443A == true)
                    {
                        iret = RFIDLIB.rfidlib_aip_iso14443A.ISO14443A_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, uid, ref uidlen);
                        if (iret == 0)
                        {
                            object[] pList = { aip_id, tag_id, ant_id, uid, (int)uidlen };
                            Invoke(tagReportHandler, pList);
                            //tagReportHandler(hreader, aip_id, tag_id, ant_id, uid, uidlen);
                        }
                    }

                    /* Parse Iso18000-3 mode 3  tag report */
                    if (enable18000p3m3)
                    {
                        UInt32 metaFlags = 0;
                        Byte[] tagData = new Byte[32];
                        UInt32 tagDataLen = (UInt32)tagData.Length;
                        iret = RFIDLIB.rfidlib_aip_iso18000p3m3.ISO18000p3m3_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, ref metaFlags, tagData, ref tagDataLen);
                        if (iret == 0)
                        {
                            object[] pList = { aip_id, tag_id, ant_id, tagData, (int)tagDataLen };
                            Invoke(tagReportHandler, pList);
                        }
                    }

                    /* Get Next report from buffer */
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
            Boolean enISO15693, enISO14443a, enISO18000p3m3;
            delegate_tag_report_handle cbTagReportHandle; 

            cbTagReportHandle = new delegate_tag_report_handle(dele_tag_report_handler) ;
            enISO15693 = enISO14443a = enISO18000p3m3 = false;
            /* check air protocol */
            for(int i = 0; i < airInterfaceProtList.Count; i++)
            {
                CSupportedAirProtocol aip;
                aip = (CSupportedAirProtocol)airInterfaceProtList[i];
                if (aip.m_en)
                {
                    if(aip.m_ID == RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID) {
                        //create ISO15693 inventory parameter  
                        enISO15693 =true;
                    }
                    else if (aip.m_ID == RFIDLIB.rfidlib_def.RFID_APL_ISO14443A_ID)
                    {
                        //create ISO14443A inventory parameter  
                        enISO14443a =true;
                    }
                    else if (aip.m_ID == RFIDLIB.rfidlib_def.RFID_APL_ISO18000P3M3)
                    {
                        enISO18000p3m3 = true;
                    }
                }
            }
            int iret;
            Byte AIType = RFIDLIB.rfidlib_def.AI_TYPE_NEW;
            if (onlyNewTag == 1)
            {
                AIType = RFIDLIB.rfidlib_def.AI_TYPE_CONTINUE;  //only new tag inventory 
            }
            while (!_shouldStop)
            {

                UInt32 nTagCount =0 ;
                iret = tag_inventory( AIType, AntennaSelCount, AntennaSel, enISO15693, enISO14443a,enISO18000p3m3, enableAFI, AFI, cbTagReportHandle, ref nTagCount);
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
            checkedListBox1.Items.Clear();
            comboBox7.Items.Clear();
            button19.Enabled = false;
            button2.Enabled = false;

            /*
             * Try to open communcation layer for specified reader 
             */
            int commTypeIdx = comboBox10.SelectedIndex;
            string readerDriverName = ((CReaderDriverInf)(readerDriverInfoList[readerType])).m_name;
            string connstr ="";
            // Build serial communication connection string
            if (commTypeIdx == 0){  
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE +"="+ readerDriverName + ";"+
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME+"=" + comboBox1.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + comboBox14.Text + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + comboBox15.Text + ";" + 
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR+"="+"255" ;
            }
            // Build USBHID communication connection string
            else if (commTypeIdx == 1){
                connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE+"="+usbOpenType.ToString() +";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=" + comboBox9.Text;
                MessageBox.Show(connstr);
            }
            // Build network communication connection string
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
            // Build blueTooth communication connection string
            else if (commTypeIdx == 3)
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
            // Call required to open reader driver
            iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, ref hreader);
            if (iret != 0)
            {
                /*
                 *  Open fail:
                 *  if you Encounter this error ,make sure you has called the API "RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers")" 
                 *  when application load
                 */
                MessageBox.Show("fail");
                checkedListBox1.Enabled = true;
                button2.Enabled = true;
            }
            else
            {
                /*
                 * Open Ok and try to get some information from driver ,and assign value to the correspondding control 
                 */

                // this API is not required in your own application
                // Get antenna count
                antennaCount = RFIDLIB.rfidlib_reader.RDR_GetAntennaInterfaceCount(hreader);
                int i;
                for (i = 0; i < antennaCount; i++)
                {
                    int iAnt ;
                    iAnt = i+ 1;

                    checkedListBox1.Items.Add("Antenna#" + iAnt.ToString() );
                    comboBox7.Items.Add("Antenna#" + iAnt.ToString());
                }
                button19.Enabled = false;
                checkedListBox1.Enabled = false;
                comboBox7.Enabled = false;
                if (antennaCount > 1)
                {
                    button19.Enabled = true;
                    checkedListBox1.Enabled = true;
                    comboBox7.Enabled = true;
                }
          
                if (antennaCount > 1)
                {
                    checkedListBox1.Enabled = true;
                }

                
                // this API is not required in your own application
                // To get supported air protocol interface of the reader ,such as ISO15693 ,ISO14443a....
                checkedListBox2.Items.Clear();
                UInt32 index = 0;
   
                UInt32 AIType;
                while (true)
                {
                    AIType = 0;
                    iret = RFIDLIB.rfidlib_reader.RDR_GetSupportedAirInterfaceProtocol(hreader, index, ref AIType);
                    if (iret != 0)
                    {
                        break;
                    }
                    StringBuilder namebuf = new StringBuilder();
                    namebuf.Append('\0', 128);
                    RFIDLIB.rfidlib_reader.RDR_GetAirInterfaceProtName(hreader, AIType, namebuf,(UInt32) namebuf.Capacity);

                    CSupportedAirProtocol aip = new CSupportedAirProtocol();
                    aip.m_ID = AIType;
                    aip.m_name = namebuf.ToString();
                    aip.m_en = true;
                    airInterfaceProtList.Add(aip);

                    checkedListBox2.Items.Add(aip.m_name, true);
                    
                    index++;
                }

                /*
                 * Enable controls
                 */
                button2.Enabled = false;
                button3.Enabled = true;
                button4.Enabled = true;
                button5.Enabled = true;
                button7.Enabled = true;
                button30.Enabled = true;

                //ST M24LR page 
                button61.Enabled = true;
                button58.Enabled = true;
                button61.Enabled = true;
                button59.Enabled = true;

                //ST LRI2k page
                bntLRI2kConn.Enabled = true;
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
           /*
            *  Close reader driver ,this API is required
            */
           iret = RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            if (iret == 0)
            {
                hreader = (UIntPtr)0;
                //MessageBox.Show("ok");
                button2.Enabled = true;
                button3.Enabled = false;
                button4.Enabled = false;
                button5.Enabled = false;
                button7.Enabled = false;

                openState = 0;
                checkedListBox1.Enabled = true;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            _shouldStop = false;
            listView1.Items.Clear();
            comboBox3.Items.Clear();
            comboBox11.Items.Clear();
            comboBox16.Items.Clear();
            comboBox29.Items.Clear();
            comboBox38.Items.Clear();
            comboBox42.Items.Clear();
            // AFI
            if (checkBox3.Checked)
            {
                enableAFI = 1;
                Byte[] afi;
                afi = StringToByteArrayFastest(textBox3.Text);
                AFI = afi[0];
            }
            else
            {
                enableAFI = 0;
            }
            //Only new tag
            if (checkBox2.Checked)
            {
               onlyNewTag = 1;
            }
            else
            {
                onlyNewTag = 0;
            }

            // antenna selection
            int iCount = 0;
            for (int i = 0; i < checkedListBox1.Items.Count; i++)
            {
                if (checkedListBox1.GetItemChecked(i))
                {
                    AntennaSel[iCount] = (Byte)(i + 1);
                    iCount++;
                }
            }
            AntennaSelCount = (Byte)iCount;
            /*
             *  air interface protocol
             */
            for (int i = 0; i < checkedListBox2.Items.Count; i++)
            {
                CSupportedAirProtocol aip;
                aip = (CSupportedAirProtocol)airInterfaceProtList[i];
                if(checkedListBox2.GetItemChecked(i)){
                    aip.m_en = true;
                }
                else {
                    aip.m_en = false;
                }
            }



            /*
             * Start the thread to inventory tags 
             */
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

        private void button7_Click(object sender, EventArgs e)
        {
 
            int iret;
            string suid ;
            int idx;
            if (hTag !=UIntPtr.Zero)
            {
                MessageBox.Show("please disconnect tag first");
                return;
            }
            idx = comboBox2.SelectedIndex;
            if (idx == -1)
            {
                MessageBox.Show("please select address mode");
                return;
            }
            if (idx == 1 || idx == 2) // Addressed and select need uid 
            {
                if (comboBox3.Text == "")
                {
                    MessageBox.Show("please input a uid");
                    return;
                }
            }

            // set uid
            suid = comboBox3.Text;
            byte[] uid = StringToByteArrayFastest(suid);

            //set tag type default is NXP icode sli 
            UInt32 tagType =RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_ICODE_SLI_ID ; 
            if(comboBox3.SelectedIndex != -1) {
                // if we get the tag type from inventory ,then input the identified tag type 
               tagType = (comboBox3.SelectedItem as tagInfo).m_tagType ;
            }

            // set address mode 
            Byte addrMode = (Byte)idx;

            // do connection
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Connect(hreader, tagType, addrMode, uid, ref hTag);
            if (iret == 0)
            {
                /* 
                * if select none address mode after inventory need to reset the tag first,because the tag is stay quiet now  
                * if the tag is in ready state ,do not need to call reset
                */
                if (addrMode == 0) {
                    iret= RFIDLIB.rfidlib_aip_iso15693.ISO15693_Reset(hreader, hTag);
                    if(iret != 0) {
                        MessageBox.Show("reset tag fail");
                        RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
                        hTag = UIntPtr.Zero;
                        return;
                    }
                }
                /* connect ok */
                button7.Enabled = false;
                button8.Enabled = true;
                button9.Enabled = true;
                button11.Enabled = true;
                button10.Enabled = true;
                button12.Enabled = true;
                button18.Enabled = true;
                button13.Enabled = true;
                button15.Enabled = true;
                button16.Enabled = true;
                button17.Enabled = true;
                button14.Enabled = true;

                button73.Enabled  = true;
                button74.Enabled =true;
                button76.Enabled =true;
                button75.Enabled =true;
                button77.Enabled =true;
                button78.Enabled =true;
                button79.Enabled = true;

            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {

            int iret;

            // do disconnection
            iret = RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader,hTag);
            if (iret == 0)
            {
                hTag = (UIntPtr)0;
                button7.Enabled = true;
                button8.Enabled = false;
                button9.Enabled = false;
                button11.Enabled = false;
                button10.Enabled = false;
                button12.Enabled = false;
                button18.Enabled = false;
                button13.Enabled = false;
                button15.Enabled = false;
                button16.Enabled = false;
                button17.Enabled = false;
                button14.Enabled = false;

                button73.Enabled = false;
                button74.Enabled = false;
                button76.Enabled = false;
                button75.Enabled = false;
                button77.Enabled = false;
                button78.Enabled = false;
                button79.Enabled = false;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blkAddr;
            UInt32 numOfBlks;
            idx = comboBox4.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blkAddr = (UInt32)idx;
            idx = comboBox5.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            numOfBlks = (UInt32)(idx + 1);
            byte[] newBlksData = StringToByteArrayFastest(textBox1.Text);

            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteMultipleBlocks(hreader, hTag, blkAddr, numOfBlks, newBlksData, (uint)newBlksData.Length);
            if (iret == 0)
            {
                MessageBox.Show("ok !");
            }
            else
            {
                MessageBox.Show("failed!err = " + iret);
            }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blkAddr;
            UInt32 numOfBlks;
            idx = comboBox4.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blkAddr = (UInt32)idx;
            idx = comboBox5.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            numOfBlks = (UInt32)(idx + 1);

            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_LockMultipleBlocks(hreader, hTag, blkAddr, numOfBlks);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button11_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            UInt32 blocksRead = 0;
            idx = comboBox4.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blockAddr = (UInt32)idx;
            idx = comboBox5.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            blockToRead = (UInt32)(idx + 1);
            UInt32 nSize;
            Byte[] BlockBuffer= new Byte[40] ;
    
            nSize = (UInt32)BlockBuffer.GetLength(0);
            UInt32 bytesRead = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ReadMultiBlocks(hreader, hTag, 0, blockAddr, blockToRead, ref blocksRead, BlockBuffer, nSize, ref bytesRead);
            if (iret == 0)
            {
                //blocksRead: blocks read 
                textBox1.Text = BitConverter.ToString(BlockBuffer, 0, (int)bytesRead).Replace("-", string.Empty);
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }

        }

        private void button12_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            idx = comboBox4.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blockAddr = (UInt32)idx;
            idx = comboBox5.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            blockToRead = (UInt32)(idx + 1);
            Byte[] buffer = new Byte[blockToRead];
            UInt32 nSize = (UInt32)buffer.GetLength(0);
            UInt32 bytesRead = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_GetBlockSecStatus(hreader, hTag, blockAddr, blockToRead, buffer, nSize, ref bytesRead);
            if (iret == 0)
            {
                textBox1.Text = BitConverter.ToString(buffer).Replace("-", string.Empty);
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
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
        private void button14_Click(object sender, EventArgs e)
        {
            int iret;
            Byte[] uid= new Byte[8] ;
            Byte dsfid, afi, icref;
            UInt32 blkSize ,blkNum;
            dsfid =afi =  icref =0 ;
            blkSize = blkNum = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_GetSystemInfo(hreader,hTag, uid, ref dsfid, ref afi, ref blkSize, ref blkNum, ref icref);
            if (iret == 0)
            {
                label15.Text = BitConverter.ToString(uid).Replace("-", string.Empty);
                label21.Text = ByteToHex(afi)+"H" ;
                label22.Text = ByteToHex(dsfid) + "H";
                label23.Text = ByteToHex((Byte)(blkSize & 0xff)) + "H";
                label24.Text = ByteToHex((Byte)(blkNum & 0xff)) + "H";
                label25.Text = ByteToHex(icref) + "H";
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button15_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_EableEAS(hreader, hTag);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button16_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_DisableEAS(hreader, hTag);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button17_Click(object sender, EventArgs e)
        {
            int iret;
            Byte EASStatus;
            EASStatus = 0;
            richTextBox1.Text = "";
            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_EASCheck(hreader, hTag, ref EASStatus);
            if (iret == 0)
            {
                if (EASStatus ==0){
                    richTextBox1.Text = "EAS is closed";
                }
                else {
                    richTextBox1.Text = "EAS is open";
                }
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button26_Click(object sender, EventArgs e)
        {

        }

        private void button18_Click(object sender, EventArgs e)
        {
/*
            int iret;
            Byte[] blockbuf = new Byte[5];
            UInt32 nSize = (UInt32)blockbuf.GetLength(0);
            iret = RFIDLIB.rfidlib_tag_nxp_icodeslix.NXPICODESLIX_ReadSingleBlock(hTagIcodeslix, 1, 0, blockbuf, ref nSize);
            if (iret == 0)
            {
                textBox2.Text = BitConverter.ToString(blockbuf).Replace("-", string.Empty);
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
*/
        }

        private void button19_Click(object sender, EventArgs e)
        {
         
        }

        private void button20_Click(object sender, EventArgs e)
        {
            /*
            int iret;
            Byte blockToRead;
            UInt32 nSize;
            Byte[] BlockBuffer = new Byte[20];
            blockToRead = 2;
            nSize = (UInt32)BlockBuffer.GetLength(0);
            iret = RFIDLIB.rfidlib_tag_nxp_icodeslix.NXPICODESLIX_ReadMultiBlocks(hTagIcodeslix, 1, 0, ref blockToRead, BlockBuffer, ref nSize);
            if (iret == 0)
            {
                textBox2.Text = BitConverter.ToString(BlockBuffer, 0, 10).Replace("-", string.Empty);
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
            */
        }

        private void button22_Click(object sender, EventArgs e)
        {

        }

        private void button23_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_EableEAS(hreader,hTagIcodeslix);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button24_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_DisableEAS(hreader, hTagIcodeslix);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button25_Click(object sender, EventArgs e)
        {
            /*
            int iret;
            Byte[] EAS_data = new Byte[64];
            UInt32 nSize = (UInt32)EAS_data.GetLength(0);
            iret = RFIDLIB.rfidlib_tag_nxp_icodeslix.NXPICODESLIX_EASAlarm(hTagIcodeslix, EAS_data, ref nSize);
            if (iret == 0)
            {
                textBox2.Text = BitConverter.ToString(EAS_data, 0, 32).Replace("-", string.Empty);
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
             */
        }

        private void button30_Click(object sender, EventArgs e)
        {
 
        }

        private void button31_Click(object sender, EventArgs e)
        {

        }

        private void button29_Click(object sender, EventArgs e)
        {

        }

        private void button27_Click(object sender, EventArgs e)
        {

        }

        private void button32_Click(object sender, EventArgs e)
        {
    
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void listView1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

        private void button6_Click_1(object sender, EventArgs e)
        {
            button6_Click(sender, e);
        }

        private void button5_Click_1(object sender, EventArgs e)
        {
            button5_Click(sender, e);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button13_Click(object sender, EventArgs e)
        {
            int iret;
            byte[] dsfid = StringToByteArrayFastest(textBox4.Text);
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteDSFID(hreader,hTag, dsfid[0]);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void tabPage3_Click(object sender, EventArgs e)
        {

        }

        private void tabPage4_Click(object sender, EventArgs e)
        {

        }

        private void button33_Click(object sender, EventArgs e)
        {

        }

        private void button21_Click(object sender, EventArgs e)
        {

        }

        private void button34_Click(object sender, EventArgs e)
        {

        }

        private void button28_Click(object sender, EventArgs e)
        {

        }

        private void tabPage2_Click(object sender, EventArgs e)
        {

        }

        private void button26_Click1(object sender, EventArgs e)
        {

        }

        private void button35_Click(object sender, EventArgs e)
        {

        }

        private void button36_Click(object sender, EventArgs e)
        {

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button6_Click_2(object sender, EventArgs e)
        {
            button6.Enabled = false;
            _shouldStop = true;
            /*
             * Exit the inventory quickly
             */
            RFIDLIB.rfidlib_reader.RDR_SetCommuImmeTimeout(hreader);

            if (comboBox3.Items.Count > 0) comboBox3.SelectedIndex = 0;
            if (comboBox11.Items.Count > 0) comboBox11.SelectedIndex = 0;
            if (comboBox16.Items.Count > 0) comboBox16.SelectedIndex = 0;
            if (comboBox29.Items.Count > 0) comboBox29.SelectedIndex = 0;
            if (comboBox42.Items.Count > 0) comboBox42.SelectedIndex = 0;
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

        private void button18_Click_1(object sender, EventArgs e)
        {
            int iret;
            byte[] afi = StringToByteArrayFastest(textBox2.Text );
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteAFI(hreader,hTag, afi[0]);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
 
            comboBox1.SelectedIndex = 0;
            /* 
             *  Call required, when application load ,this API just only need to load once
             *  Load all reader driver dll from drivers directory, like "rfidlib_ANRD201.dll"  
             */
            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
            

            /*
             * Not call required,it can be Omitted in your own appliation
             * enum and show loaded reader driver 
             */
            UInt32 nCount;
            nCount = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount();
            MessageBox.Show("Loaded " + nCount + " drivers");
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


            /* 
             * Not call required,it can be Omitted in your own appliation
             * enum PC serial ports 
             */
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


            /*
             * Not call required,it can be Omitted in your own appliation
             * enum matched bluetooth 
             */
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


            /*
             * Control initialization
             */
            for ( i = 0; i < 512; i++)
            {
                comboBox32.Items.Add(i.ToString());
                int k =(int)( i + 1);
                comboBox31.Items.Add(k.ToString());
            }
            comboBox32.SelectedIndex = 0;
            comboBox31.SelectedIndex = 0;
    
            comboBox5.SelectedIndex = 0;
            comboBox30.SelectedIndex = 1;
            comboBox33.SelectedIndex = 0;
            comboBox37.SelectedIndex =0 ;
            comboBox34.SelectedIndex =0 ;
            comboBox35.SelectedIndex =0 ;
            comboBox36.SelectedIndex = 0;

            comboBox17.SelectedIndex = 1;
            comboBox30.SelectedIndex = 1;
            comboBox39.SelectedIndex = 1;
            comboBox41.SelectedIndex = 0;
            comboBox40.SelectedIndex = 0;

            comboBox44.SelectedIndex = 0;
            comboBox43.SelectedIndex = 0;


            comboBox45.Items.Add("Read");
            comboBox45.Items.Add("Write");
            comboBox45.Items.Add("Private");
            comboBox45.Items.Add("Destroy");
            comboBox45.Items.Add("EAS/AFI");
            comboBox45.SelectedIndex = 0;

            comboBox46.Items.Add("EAS");
            comboBox46.Items.Add("AFI");
            comboBox46.SelectedIndex = 0;

            int icodesliMaxBlockCnt = 80;
            for ( i = 0; i < icodesliMaxBlockCnt; i++)
            {
                comboBox4.Items.Add(i.ToString());
                comboBox47.Items.Add(i.ToString());
            }
            comboBox4.SelectedIndex = 0;
            comboBox47.SelectedIndex = 0;

            comboBox48.Items.Add("Public");
            comboBox49.Items.Add("Public");
            comboBox48.Items.Add("RW protected by the R password");
            comboBox49.Items.Add("RW protected by the R password");
            comboBox48.Items.Add("W protected by the W password");
            comboBox49.Items.Add("W protected by the W password");
            comboBox48.Items.Add("R protected by the R password and W protected by the RW password");
            comboBox49.Items.Add("R protected by the R password and W protected by the RW password");
            comboBox48.SelectedIndex = 0;
            comboBox49.SelectedIndex = 0;


        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button19_Click_1(object sender, EventArgs e)
        {
            /*
             *  if connected a reader with multiple antenna , we should call RDR_SetAccessAntenna to select 
             *  antenna which the tags located  for reading/writing tag memory after inventory .
             */
            int idx;
 
            idx = comboBox7.SelectedIndex;
            if (idx == -1)
            {
                MessageBox.Show("Please select access antenna !");
                return;
            }
            Byte accessAnt ;
            accessAnt = (Byte)(idx + 1);
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_SetAcessAntenna(hreader, accessAnt);
            if (iret != 0)
            {
                MessageBox.Show("fail");
                return;
            }
            MessageBox.Show("ok");
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
            /*
             * Try to get  serial number and type from device
             */
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

        private void button1_Click_1(object sender, EventArgs e)
        {
            int iret;
            string suid;
            if (hTag != UIntPtr.Zero)
            {
                MessageBox.Show("please disconnect tag first");
                return;
            }
            if (comboBox11.Text == "")
            {
                MessageBox.Show("please input a uid");
                return;
            }
            suid = comboBox11.Text;
            byte[] uid = StringToByteArrayFastest(suid);
            iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_Connect(hreader, 0, uid, ref hTag);
            if (iret==0)
            {
                button1.Enabled = false;
                comboBox11.Enabled = false;
                button20.Enabled = true;
                comboBox12.Enabled = true;
                comboBox13.Enabled = true;
                textBox7.Enabled = true;
                textBox8.Enabled = true;
                textBox9.Enabled = true;
                button20.Enabled = true;
                button21.Enabled = true;
                button22.Enabled = true;
                button23.Enabled = true;
                button24.Enabled = true;
                button25.Enabled = true;
                button26.Enabled = true;
                button27.Enabled = true;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button20_Click_1(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
            if (iret==0)
            {
                hTag = (UIntPtr)0;
                button1.Enabled = true;
                comboBox11.Enabled = true;
                button20.Enabled = false;
                comboBox12.Enabled = false;
                comboBox13.Enabled = false;
                textBox7.Enabled = false;
                textBox8.Enabled = false;
                textBox9.Enabled = false;
                button20.Enabled = false;
                button21.Enabled = false;
                button22.Enabled = false;
                button23.Enabled = false;
                button24.Enabled = false;
                button25.Enabled = false;
                button26.Enabled = false;
                button27.Enabled = false;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button21_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            idx = comboBox12.SelectedIndex;
            if (idx<0)
            {
                MessageBox.Show("Please select block address");
                return;
            }
            byte blkAddr =(byte) idx;//(byte)comboBox12.SelectedIndex;

            idx = comboBox13.SelectedIndex;
            if (idx<0)
            {
                MessageBox.Show("Please select key type");
                return;
            }
            byte keyType = (byte)idx;
            byte[] key = StringToByteArrayFastest(textBox7.Text);

            iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_Authenticate(hreader, hTag, blkAddr, keyType, key);
            if (iret==0)
            {
                MessageBox.Show("OK");
            }
            else
            {
                MessageBox.Show("Fail");
            }
        }

        private void button22_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            byte blkAddr;
            byte[]blkData = new byte[16];

            idx = comboBox12.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("Please select block address");
                return;
            }
            blkAddr = (byte)idx;
            iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_ReadBlock(hreader, hTag, blkAddr, blkData, 16);
            if (iret==0)
            {
                textBox8.Text = BitConverter.ToString(blkData, 0, 16).Replace("-", string.Empty);
                MessageBox.Show("OK");
                button23.Enabled = true;
                button28.Enabled = true;
            }
            else
            {
                MessageBox.Show("Fail");
            }
        }

        private void button23_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            byte blkAddr;

            idx = comboBox12.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("Please select block address");
                return;
            }
            blkAddr = (byte)idx;
            byte[] blkData = StringToByteArrayFastest(textBox8.Text);
            iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_WriteBlock(hreader, hTag, blkAddr, blkData);
            if (iret==0)
            {
                MessageBox.Show("OK");
            }
            else
            {
                MessageBox.Show("Fail");
            }
        }

        private void button24_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            byte blkAddr;
            UInt32 val = UInt32.Parse(textBox9.Text);
            idx = comboBox12.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("Please select block address");
                return;
            }
            blkAddr = (byte)idx;
            iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_FormatValueBlock(hreader, hTag, blkAddr, val);
            if (iret==0)
            {
                MessageBox.Show("OK");
            }
            else
            {
                MessageBox.Show("Fail");
            }
        }

        private void button25_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            byte blkAddr;
            UInt32 val = UInt32.Parse(textBox9.Text);
            idx = comboBox12.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("Please select block address");
                return;
            }
            blkAddr = (byte)idx;
            iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_Increment(hreader, hTag, blkAddr, val);
            if (iret == 0)
            {
                MessageBox.Show("OK");
            }
            else
            {
                MessageBox.Show("Fail");
            }
        }

        private void button26_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            byte blkAddr;
            UInt32 val = UInt32.Parse(textBox9.Text);
            idx = comboBox12.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("Please select block address");
                return;
            }
            blkAddr = (byte)idx;
            iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_Decrement(hreader, hTag, blkAddr, val);
            if (iret == 0)
            {
                MessageBox.Show("OK");
            }
            else
            {
                MessageBox.Show("Fail");
            }
        }

        private void button27_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            byte blkAddr;
            idx = comboBox12.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("Please select block address");
                return;
            }
            blkAddr = (byte)idx;
            iret = RFIDLIB.rfidlib_aip_iso14443A.MFCL_Restore(hreader, hTag, blkAddr);
            if (iret == 0)
            {
                MessageBox.Show("OK");
            }
            else
            {
                MessageBox.Show("Fail");
            }
        }

        private void comboBox12_SelectedIndexChanged(object sender, EventArgs e)
        {
            int idx;
            byte blkAddr;
            idx = comboBox12.SelectedIndex;
            blkAddr = (byte)idx;
            if (RFIDLIB.rfidlib_aip_iso14443A.MFCL_IsTailerBlock(blkAddr) == 1)
            {
                textBox8.Enabled = false;
                button23.Enabled = false;
                button28.Enabled = false;
            }
            else
            {
                textBox8.Enabled = true;
                button23.Enabled = true;
                button28.Enabled = false;
            }
        }

        private void button28_Click_1(object sender, EventArgs e)
        {
            //int iret;
            int idx;
            byte blkAddr;

            idx = comboBox12.SelectedIndex;
            blkAddr = (byte)idx;
            if (RFIDLIB.rfidlib_aip_iso14443A.MFCL_IsTailerBlock(blkAddr) == 1)
            //if (blkAddr == 3)
            {
                byte[] block = new byte[16];
                AccessConditions dlg = new AccessConditions(this);
                //dlg.setPareWnd(this);
                dlg.ShowDialog();
                
            }
        }

        public void setAccessConditionBuff(byte[] buff)
        {
            textBox8.Text = BitConverter.ToString(buff, 0, 16).Replace("-", string.Empty);
        }

        public void getAccessVal(ref byte[]accessBuff)
        {
            accessBuff = StringToByteArrayFastest(textBox8.Text);
        }

        private void groupBox9_Enter(object sender, EventArgs e)
        {

        }

        private void button30_Click_1(object sender, EventArgs e)
        {
            int iret;
            string suid;
            int idx;
            if (hTag != UIntPtr.Zero)
            {
                MessageBox.Show("please disconnect tag first");
                return;
            }
            idx = comboBox17.SelectedIndex;
            if (idx == -1)
            {
                MessageBox.Show("please select address mode");
                return;
            }
            if (idx == 1 || idx == 2) // Addressed and select need uid 
            {
                if (comboBox16.Text == "")
                {
                    MessageBox.Show("please input a uid");
                    return;
                }
            }
            suid = comboBox16.Text;
            byte[] uid = StringToByteArrayFastest(suid);
            Byte addrMode = (Byte)idx;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Connect(hreader, RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_CIT83128_ID, addrMode, uid, ref hTag);
            if (iret == 0)
            {
                /* 
                * if select none address mode after inventory need to reset the tag first,because the tag is stay quiet now  
                * if the tag is in ready state ,do not need to call reset
                */
                if (addrMode == 0)
                {
                    iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Reset(hreader, hTag);
                    if (iret != 0)
                    {
                        MessageBox.Show("reset tag fail");
                        RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
                        hTag = UIntPtr.Zero;
                        return;
                    }
                }
                /* connect ok */
                button29.Enabled = true;
                button30.Enabled = false;

                comboBox18.SelectedIndex = 0;
                comboBox19.SelectedIndex = 0;
                comboBox20.SelectedIndex = 0;

            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button29_Click_1(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
            if (iret == 0)
            {
                hTag = (UIntPtr)0;
                //MessageBox.Show("ok");
                button29.Enabled = false;
                button30.Enabled = true;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button31_Click_1(object sender, EventArgs e)
        {
            int iret;
            Byte[] BlockBuffer= new Byte[5] ;
            Byte bReadSecByte;
            bReadSecByte = 1;
            iret = RFIDLIB.rfidlib_aip_iso15693.CIT83128_GetSecPara(hreader, hTag,
                                                                    bReadSecByte,/* read secure byte or not */
                                                                    BlockBuffer /* block data */
                                                                    );
            if (iret != 0)
            {
                if (iret == -17)
                {
                    iret = RFIDLIB.rfidlib_reader.RDR_GetReaderLastReturnError(hreader);
                    MessageBox.Show("reader return err:"+ iret.ToString());
                }
                else
                {
                    MessageBox.Show("fail");
                }
            }
            else
            {
                MessageBox.Show("ok");
            }
        }

        private void button32_Click_1(object sender, EventArgs e)
        {
            int iret;
            UInt32 rr;
            rr =(UInt32) int.Parse(textBox27.Text );
            Byte[] token = new Byte[8];
            iret = RFIDLIB.rfidlib_aip_iso15693.CIT83128_ActAu(hreader, hTag, rr, token);
            if (iret != 0)
            {
                if (iret == -17)
                {
                    iret = RFIDLIB.rfidlib_reader.RDR_GetReaderLastReturnError(hreader);
                    MessageBox.Show("reader return err:" + iret.ToString());
                }
                else
                {
                    MessageBox.Show("fail");
                }
            }
            else
            {
                textBox28.Text = BitConverter.ToString(token, 0,8).Replace("-", string.Empty); 
                MessageBox.Show("ok");
            }
        }

        private void button33_Click_1(object sender, EventArgs e)
        {
            int iret;
            Byte loseEffect;
            Byte blkAdr;
            
            loseEffect =(Byte) comboBox18.SelectedIndex;
            blkAdr = 0;
            blkAdr = (Byte)comboBox19.SelectedIndex;
            Byte blkNum =(Byte)(comboBox20.SelectedIndex + 1);
            Byte[] blkData = new Byte[4 * blkNum];
            iret = RFIDLIB.rfidlib_aip_iso15693.CIT83128_InitMem(hreader, hTag, loseEffect, blkAdr, blkNum, blkData);
            if (iret != 0)
            {
                if (iret == -17)
                {
                    iret = RFIDLIB.rfidlib_reader.RDR_GetReaderLastReturnError(hreader);
                    MessageBox.Show("reader return err:" + iret.ToString());
                }
                else
                {
                    MessageBox.Show("fail");
                }
            }
            else
            {
                MessageBox.Show("ok");
            }
        }

        private void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void cbbBluetoothName_SelectedIndexChanged(object sender, EventArgs e)
        {
            txbBluetoothSN.Text = m_blueAddrList[cbbBluetoothName.SelectedIndex];
        }

        private void button61_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            UInt32 blocksRead = 0;
            idx = comboBox32.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blockAddr = (UInt32)idx;
            idx = comboBox31.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            blockToRead = (UInt32)(idx + 1);
            UInt32 nSize;
            Byte[] BlockBuffer = new Byte[40];

            nSize = (UInt32)BlockBuffer.GetLength(0);
            UInt32 bytesRead = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ReadMultiBlocks(hreader, hTag, 0, blockAddr, blockToRead, ref blocksRead, BlockBuffer, nSize, ref bytesRead);
            if (iret == 0)
            {
                //blocksRead: blocks read 
                textBox18.Text = BitConverter.ToString(BlockBuffer, 0, (int)bytesRead).Replace("-", string.Empty);
                
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button59_Click(object sender, EventArgs e)
        {
            int iret;
            string suid;
            int idx;
            if (hTag != UIntPtr.Zero)
            {
                MessageBox.Show("please disconnect tag first");
                return;
            }
            idx = comboBox30.SelectedIndex;
            if (idx == -1)
            {
                MessageBox.Show("please select address mode");
                return;
            }
            if (idx == 1 || idx == 2) // Addressed and select need uid 
            {
                if (comboBox29.Text == "")
                {
                    MessageBox.Show("please input a uid");
                    return;
                }
            }
            suid = comboBox29.Text;
            byte[] uid = StringToByteArrayFastest(suid);
            Byte addrMode = (Byte)idx;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Connect(hreader, RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_ST_M24LR64_ID, addrMode, uid, ref hTag);
            if (iret == 0)
            {
                /* 
                * if select none address mode after inventory need to reset the tag first,because the tag is stay quiet now  
                * if the tag is in ready state ,do not need to call reset
                */
                if (addrMode == 0)
                {
                    iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Reset(hreader, hTag);
                    if (iret != 0)
                    {
                        MessageBox.Show("reset tag fail");
                        RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
                        hTag = UIntPtr.Zero;
                        return;
                    }
                }
                /* connect ok */
                //MessageBox.Show("ok");
                button59.Enabled = false;
                button58.Enabled = true;
                button69.Enabled = true;
                button61.Enabled = true;
                button67.Enabled = true;
                button60.Enabled = true;
                button63.Enabled = true;
                button64.Enabled = true;
                button66.Enabled = true;

            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button58_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
            if (iret == 0)
            {
                hTag = (UIntPtr)0;
             
            }
            else
            {
                MessageBox.Show("fail");
            }
            button59.Enabled = true;
            button58.Enabled = false;
            button69.Enabled = false;
            button61.Enabled = false;
            button67.Enabled = false;
            button60.Enabled = false;
            button63.Enabled = false;
            button64.Enabled = false;
            button66.Enabled = false;
        }

        private void button67_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            idx = comboBox32.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blockAddr = (UInt32)idx;
            idx = comboBox31.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            blockToRead = (UInt32)(idx + 1);
            Byte[] buffer = new Byte[blockToRead];
            UInt32 nSize = (UInt32)buffer.GetLength(0);
            UInt32 bytesRead = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_GetBlockSecStatus(hreader, hTag, blockAddr, blockToRead, buffer, nSize, ref bytesRead);
            if (iret == 0)
            {
                textBox18.Text = BitConverter.ToString(buffer).Replace("-", string.Empty);
    
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button69_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blkAddr;
            UInt32 numOfBlks;
            idx = comboBox32.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blkAddr = (UInt32)idx;
            idx = comboBox31.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            numOfBlks = (UInt32)(idx + 1);
            byte[] newBlksData = StringToByteArrayFastest(textBox18.Text);

            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteMultipleBlocks(hreader, hTag, blkAddr, numOfBlks, newBlksData, (uint)newBlksData.Length);
            if (iret == 0)
            {
                MessageBox.Show("Write ok!");
            }
            else
            {
                MessageBox.Show("Write failed!err = " + iret);
            }
        }

        private void button60_Click(object sender, EventArgs e)
        {
            int iret;
            byte[] afi = StringToByteArrayFastest(textBox17.Text);
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteAFI(hreader, hTag, afi[0]);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button66_Click(object sender, EventArgs e)
        {
            int iret;
            byte[] dsfid = StringToByteArrayFastest(textBox16.Text);
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteDSFID(hreader, hTag, dsfid[0]);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button62_Click(object sender, EventArgs e)
        {
            int iret;
            int pwdIdx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            UInt32 blocksRead = 0;
            pwdIdx = comboBox32.SelectedIndex;
            if (pwdIdx < 0)
            {
                MessageBox.Show("please select password number");
                return;
            }
            if (textBox19.Text.Length != 8)
            {
                MessageBox.Show("Invalid password format");
                return;
            }
            byte[] pwd = StringToByteArrayFastest(textBox19.Text);
            UInt32 uPwd =(UInt32)( (pwd[0] & 0xff) | (pwd[1] << 8 & 0xff00) | (pwd[2] << 16 & 0xff0000) | (pwd[3] << 24 & 0xff000000) );

            iret = RFIDLIB.rfidlib_aip_iso15693.STM24LR_PresentSectorPassword(hreader, hTag,(Byte)( pwdIdx + 1), uPwd);
            if (iret == 0)
            {
                MessageBox.Show("write pwd ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button63_Click(object sender, EventArgs e)
        {
            int iret;
            int pwdIdx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            UInt32 blocksRead = 0;
            pwdIdx = comboBox37.SelectedIndex;
            if (pwdIdx < 0)
            {
                MessageBox.Show("please select password number");
                return;
            }
            if (textBox20.Text.Length != 8)
            {
                MessageBox.Show("Invalid password format");
                return;
            }
            byte[] pwd = StringToByteArrayFastest(textBox20.Text);
            UInt32 uPwd = (UInt32)((pwd[0] & 0xff) | (pwd[1] << 8 & 0xff00) | (pwd[2] << 16 & 0xff0000) | (pwd[3] << 24 & 0xff000000));

            iret = RFIDLIB.rfidlib_aip_iso15693.STM24LR_WriteSectorPassword(hreader, hTag, (Byte)(pwdIdx + 1), uPwd);
            if (iret == 0)
            {
                MessageBox.Show("present pwd ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button64_Click(object sender, EventArgs e)
        {
            int iret;
            int sectorIdx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            UInt32 blocksRead = 0;
            sectorIdx = comboBox34.SelectedIndex;
            if (sectorIdx < 0)
            {
                MessageBox.Show("please select sector number");
                return;
            }
            int pwdIdx;
            pwdIdx = comboBox35.SelectedIndex;
            if (pwdIdx < 0)
            {
                MessageBox.Show("please select password number");
                return;
            }
            int accessIdx;
            accessIdx = comboBox36.SelectedIndex;
            if (accessIdx < 0)
            {
                MessageBox.Show("please select access");
                return;
            }

            iret = RFIDLIB.rfidlib_aip_iso15693.STM24LR_LockSector(hreader, hTag, (Byte)sectorIdx, (Byte)accessIdx, (Byte)(pwdIdx + 1));
            if (iret == 0)
            {
                MessageBox.Show("present pwd ok");
            }
            else
            {
                MessageBox.Show("fail");
            }

          
        }

        private void button68_Click(object sender, EventArgs e)
        {
            int iret;
            string suid;
            int idx;
            if (hTag != UIntPtr.Zero)
            {
                MessageBox.Show("please disconnect tag first");
                return;
            }
            idx = comboBox39.SelectedIndex;
            if (idx == -1)
            {
                MessageBox.Show("please select address mode");
                return;
            }
            if (idx == 1 || idx == 2) // Addressed and select need uid 
            {
                if (comboBox38.Text == "")
                {
                    MessageBox.Show("please input a uid");
                    return;
                }
            }
            suid = comboBox38.Text;
            byte[] uid = StringToByteArrayFastest(suid);
            Byte addrMode = (Byte)idx;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Connect(hreader, RFIDLIB.rfidlib_def.RFID_ISO15693_PICC_ST_LRI2k_ID, addrMode, uid, ref hTag);
            if (iret == 0)
            {
                /* 
                * if select none address mode after inventory need to reset the tag first,because the tag is stay quiet now  
                * if the tag is in ready state ,do not need to call reset
                */
                if (addrMode == 0)
                {
                    iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Reset(hreader, hTag);
                    if (iret != 0)
                    {
                        MessageBox.Show("reset tag fail");
                        RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
                        hTag = UIntPtr.Zero;
                        return;
                    }
                }
                /* connect ok */
                //MessageBox.Show("ok");
                bntLRI2kConn.Enabled = false;
                bntLRI2kDis.Enabled = true;
                bntLRI2kReadMul.Enabled = true;
                bntLRI2kGetBSS.Enabled = true;
                bntLRI2kGetSysInf.Enabled = true;
                bntLRI2kKill.Enabled = true;
                BntLRI2kLockKill.Enabled = true;
                bntLRI2kWrieAFI.Enabled = true;
                bntLRI2kWriteDSFID.Enabled = true;
                bntLRI2kWriteKill.Enabled = true;
                bntLRI2kWriteMul.Enabled = true;
                bntLRI2kLockMul.Enabled = true;

            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button65_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
            if (iret == 0)
            {
                hTag = (UIntPtr)0;
                //MessageBox.Show("ok");
                bntLRI2kConn.Enabled = true;
                bntLRI2kDis.Enabled = false;
                bntLRI2kReadMul.Enabled = false;
                bntLRI2kGetBSS.Enabled = false;
                bntLRI2kGetSysInf.Enabled = false;
                bntLRI2kKill.Enabled = false;
                BntLRI2kLockKill.Enabled = false;
                bntLRI2kWrieAFI.Enabled = false;
                bntLRI2kWriteDSFID.Enabled = false;
                bntLRI2kWriteKill.Enabled = false;
                bntLRI2kWriteMul.Enabled = false;
                bntLRI2kLockMul.Enabled = false;
               
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button71_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            UInt32 blocksRead = 0;
            idx = comboBox41.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blockAddr = (UInt32)idx;
            idx = comboBox40.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            blockToRead = (UInt32)(idx + 1);
            UInt32 nSize;
            Byte[] BlockBuffer = new Byte[40];

            nSize = (UInt32)BlockBuffer.GetLength(0);
            UInt32 bytesRead = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ReadMultiBlocks(hreader, hTag, 0, blockAddr, blockToRead, ref blocksRead, BlockBuffer, nSize, ref bytesRead);
            if (iret == 0)
            {
                //blocksRead: blocks read 
                textBox23.Text = BitConverter.ToString(BlockBuffer, 0, (int)bytesRead).Replace("-", string.Empty);
            
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button77_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            idx = comboBox41.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blockAddr = (UInt32)idx;
            idx = comboBox40.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            blockToRead = (UInt32)(idx + 1);
            Byte[] buffer = new Byte[blockToRead];
            UInt32 nSize = (UInt32)buffer.GetLength(0);
            UInt32 bytesRead = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_GetBlockSecStatus(hreader, hTag, blockAddr, blockToRead, buffer, nSize, ref bytesRead);
            if (iret == 0)
            {
                textBox23.Text = BitConverter.ToString(buffer).Replace("-", string.Empty);
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button78_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blkAddr;
            UInt32 numOfBlks;
            idx = comboBox41.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blkAddr = (UInt32)idx;
            idx = comboBox40.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            numOfBlks = (UInt32)(idx + 1);

            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_LockMultipleBlocks(hreader, hTag, blkAddr, numOfBlks);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button79_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blkAddr;
            UInt32 numOfBlks;
            idx = comboBox41.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blkAddr = (UInt32)idx;
            idx = comboBox40.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            numOfBlks = (UInt32)(idx + 1);
            byte[] newBlksData = StringToByteArrayFastest(textBox23.Text);

            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteMultipleBlocks(hreader, hTag, blkAddr, numOfBlks, newBlksData, (uint)newBlksData.Length);
            if (iret == 0)
            {
                MessageBox.Show("Write ok!");
            }
            else
            {
                MessageBox.Show("Write failed!err = " + iret);
            }
        }

        private void button70_Click(object sender, EventArgs e)
        {
            int iret;
            byte[] afi = StringToByteArrayFastest(textBox22.Text);
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteAFI(hreader, hTag, afi[0]);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button76_Click(object sender, EventArgs e)
        {
            int iret;
            byte[] dsfid = StringToByteArrayFastest(textBox21.Text);
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_WriteDSFID(hreader, hTag, dsfid[0]);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button75_Click(object sender, EventArgs e)
        {
            int iret;
            Byte[] uid = new Byte[8];
            Byte dsfid, afi, icref;
            UInt32 blkSize, blkNum;
            dsfid = afi = icref = 0;
            blkSize = blkNum = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_GetSystemInfo(hreader, hTag, uid, ref dsfid, ref afi, ref blkSize, ref blkNum, ref icref);
            if (iret == 0)
            {
                label15.Text = BitConverter.ToString(uid).Replace("-", string.Empty);
                label21.Text = ByteToHex(afi) + "H";
                label22.Text = ByteToHex(dsfid) + "H";
                label23.Text = ByteToHex((Byte)(blkSize & 0xff)) + "H";
                label24.Text = ByteToHex((Byte)(blkNum & 0xff)) + "H";
                label25.Text = ByteToHex(icref) + "H";
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void bntLRI2kGetSysInf_Click(object sender, EventArgs e)
        {
            int iret;
            Byte[] uid = new Byte[8];
            Byte dsfid, afi, icref;
            UInt32 blkSize, blkNum;
            dsfid = afi = icref = 0;
            blkSize = blkNum = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_GetSystemInfo(hreader, hTag, uid, ref dsfid, ref afi, ref blkSize, ref blkNum, ref icref);
            if (iret == 0)
            {
                
                
                labLRI2kInfUID.Text = BitConverter.ToString(uid).Replace("-", string.Empty);
                labLRI2kInfAFI.Text = ByteToHex(afi) + "H";
                labLRI2kInfDSFID.Text = ByteToHex(dsfid) + "H";
                labLRI2kInfBlkSize.Text = ByteToHex((Byte)(blkSize & 0xff)) + "H";
                labLRI2kInfBlkNum.Text = ByteToHex((Byte)(blkNum & 0xff)) + "H";
                labLRI2kInfICRef.Text = ByteToHex(icref) + "H";
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void bntLRI2kWriteKill_Click(object sender, EventArgs e)
        {
            int iret;


            if (textBox24.Text.Length != 8)
            {
                MessageBox.Show("Invalid kill code format");
                return;
            }
            byte[] byKillCode = StringToByteArrayFastest(textBox24.Text);
            UInt32 uKillCode = (UInt32)((byKillCode[0] & 0xff) | (byKillCode[1] << 8 & 0xff00) | (byKillCode[2] << 16 & 0xff0000) | (byKillCode[3] << 24 & 0xff000000));

            iret = RFIDLIB.rfidlib_aip_iso15693.STLRI2k_WriteKill(hreader, hTag, 0x00, uKillCode);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                if (iret == -17)
                {
                    int lastErr = RFIDLIB.rfidlib_reader.RDR_GetReaderLastReturnError(hreader);
                    MessageBox.Show("Write failed! reader err = " + lastErr.ToString());
                }
                else
                {
                    MessageBox.Show("Write failed!err = " + iret.ToString());
                }
               
            }
        }

        private void bntLRI2kKill_Click(object sender, EventArgs e)
        {
            int iret;
            int pwdIdx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            UInt32 blocksRead = 0;

            if (textBox24.Text.Length != 8)
            {
                MessageBox.Show("Invalid kill code format");
                return;
            }
            byte[] byKillCode = StringToByteArrayFastest(textBox24.Text);
            UInt32 uKillCode = (UInt32)((byKillCode[0] & 0xff) | (byKillCode[1] << 8 & 0xff00) | (byKillCode[2] << 16 & 0xff0000) | (byKillCode[3] << 24 & 0xff000000));

            iret = RFIDLIB.rfidlib_aip_iso15693.STLRI2k_Kill(hreader, hTag, 0x00, uKillCode);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void BntLRI2kLockKill_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_aip_iso15693.STLRI2k_LockKill(hreader, hTag, 0x00, 0x01);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button68_Click_1(object sender, EventArgs e)
        {
            int iret;
            string suid;
            if (hTag != UIntPtr.Zero)
            {
                MessageBox.Show("please disconnect tag first");
                return;
            }
            if (comboBox42.Text == "")
            {
                MessageBox.Show("please input a uid");
                return;
            }
            suid = comboBox42.Text;
            byte[] uid = StringToByteArrayFastest(suid);
            iret = RFIDLIB.rfidlib_aip_iso14443A.ULTRALIGHT_Connect(hreader,uid, ref hTag);
            if (iret == 0)
            {
                button68.Enabled = false;
                button65.Enabled = true;
                button70.Enabled = true;
                button71.Enabled = true;
               
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button70_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 pageAddr;
            UInt32 pagesToRead;
    
            idx = comboBox44.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            pageAddr = (UInt32)idx;
            idx = comboBox43.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            pagesToRead = (UInt32)(idx + 1);
            UInt32 nSize;
            Byte[] PagesBuffer = new Byte[256];

            nSize = (UInt32)PagesBuffer.GetLength(0);

            iret = RFIDLIB.rfidlib_aip_iso14443A.ULTRALIGHT_ReadMultiplePages(hreader, hTag, pageAddr, pagesToRead, PagesBuffer, ref nSize);
            if (iret == 0)
            {
                //blocksRead: blocks read 
                textBox25.Text = BitConverter.ToString(PagesBuffer, 0, (int)nSize).Replace("-", string.Empty);
                //MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button65_Click_1(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, hTag);
            if (iret == 0)
            {
                hTag = (UIntPtr)0;
                button68.Enabled = true;
                button65.Enabled = false;
                button70.Enabled = false;
                button71.Enabled = false;
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button71_Click_1(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 pageAddr;
            UInt32 pagesToWrite;
            idx = comboBox44.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            pageAddr = (UInt32)idx;
            idx = comboBox43.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select number of blocks");
                return;
            }
            pagesToWrite = (UInt32)(idx + 1);
            byte[] newBlksData = StringToByteArrayFastest(textBox25.Text);

            iret = RFIDLIB.rfidlib_aip_iso14443A.ULTRALIGHT_WriteMultiplePages(hreader, hTag, pageAddr, pagesToWrite, newBlksData, (uint)newBlksData.Length);
            if (iret == 0)
            {
                MessageBox.Show("Write ok!");
            }
            else
            {
                MessageBox.Show("Write failed!err = " + iret);
            }
        }

        private void tabPage7_Click(object sender, EventArgs e)
        {

        }

        private void button72_Click(object sender, EventArgs e)
        {
            int iret;
            int idx;
            UInt32 blockAddr;
            UInt32 blockToRead;
            UInt32 blocksRead = 0;
            idx = comboBox4.SelectedIndex;
            if (idx < 0)
            {
                MessageBox.Show("please select block address");
                return;
            }
            blockAddr = (UInt32)idx;
         
            UInt32 nSize;
            Byte[] BlockBuffer = new Byte[16];

            nSize = (UInt32)BlockBuffer.GetLength(0);
            UInt32 bytesRead = 0;
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ReadSingleBlock(hreader, hTag, 0, blockAddr, BlockBuffer, nSize, ref bytesRead);
            if (iret == 0)
            {
                //blocksRead: blocks read 
                textBox1.Text = BitConverter.ToString(BlockBuffer, 0, (int)bytesRead).Replace("-", string.Empty);
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button73_Click(object sender, EventArgs e)
        {
            int iret;
            byte pwdId;
            UInt32 pwd;
            if (comboBox45.SelectedIndex == -1)
            {
                MessageBox.Show("Please select password ID");
                return;
            }
            switch (comboBox45.SelectedIndex)
            {
                case 0: pwdId = 0x01; break;
                case 1: pwdId = 0x02; break;
                case 2: pwdId = 0x04; break;
                case 3: pwdId = 0x08; break;
                case 4: pwdId = 0x10; break;
                default: 
                {
                    MessageBox.Show("Invalid password ID") ;
                    return ;
                }
            }

            byte[] byPwd = StringToByteArrayFastest(textBox26.Text );
            if (byPwd.Length != 4)
            {
                MessageBox.Show("Please input valid password");
                return;
            }
            pwd = (UInt32)((byPwd[0] & 0xff) | (byPwd[1] << 8 & 0xff00) | (byPwd[2] << 16 & 0xff0000) | (byPwd[3] << 24 & 0xff000000));

            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_GetRandomAndSetPassword(hreader, hTag, pwdId, pwd);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button74_Click(object sender, EventArgs e)
        {
            int iret;
            byte pwdId;
            UInt32 pwd;
            if (comboBox45.SelectedIndex == -1)
            {
                MessageBox.Show("Please select password ID");
                return;
            }
            switch (comboBox45.SelectedIndex)
            {
                case 0: pwdId = 0x01; break;
                case 1: pwdId = 0x02; break;
                case 2: pwdId = 0x04; break;
                case 3: pwdId = 0x08; break;
                case 4: pwdId = 0x10; break;
                default:
                    {
                        MessageBox.Show("Invalid password ID");
                        return;
                    }
            }
            byte[] byPwd = StringToByteArrayFastest(textBox26.Text);
            if (byPwd.Length != 4)
            {
                MessageBox.Show("Please input valid password");
                return;
            }
            pwd = (UInt32)((byPwd[0] & 0xff) | (byPwd[1] << 8 & 0xff00) | (byPwd[2] << 16 & 0xff0000) | (byPwd[3] << 24 & 0xff000000));

            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_WritePassword(hreader, hTag, pwdId, pwd);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
            
        }

        private void button76_Click_1(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_Enable64BitPwd(hreader, hTag);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button75_Click_1(object sender, EventArgs e)
        {
            int iret;
            byte pwdId;
            UInt32 pwd;
            if (comboBox45.SelectedIndex == -1)
            {
                MessageBox.Show("Please select password ID");
                return;
            }
            switch (comboBox45.SelectedIndex)
            {
                case 0: pwdId = 0x01; break;
                case 1: pwdId = 0x02; break;
                case 2: pwdId = 0x04; break;
                case 3: pwdId = 0x08; break;
                case 4: pwdId = 0x10; break;
                default:
                    {
                        MessageBox.Show("Invalid password ID");
                        return;
                    }
            }
            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_LockPassword(hreader, hTag, pwdId);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void groupBox25_Enter(object sender, EventArgs e)
        {

        }

        private void button77_Click_1(object sender, EventArgs e)
        {
            int iret;
            if(comboBox46.SelectedIndex == -1) {
                MessageBox.Show("Please protection bank type") ;
                return ;
            }
            Byte bandType;
            /*
             * Band type:
             * 0:EAS,1:AFI
             */
            bandType = (Byte)comboBox46.SelectedIndex  ;

            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_PasswordProtect(hreader, hTag, bandType);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button78_Click_1(object sender, EventArgs e)
        {
            int iret;
            if(comboBox47.SelectedIndex == -1) 
            {
                MessageBox.Show("Please select block address") ;
                return ;
            }
            Byte PPPointer = (Byte)comboBox47.SelectedIndex;
            Byte HPSta, LPSta;
            if (comboBox48.SelectedIndex == -1)
            {
                MessageBox.Show("Please select Low page status");
                return;
            }
            if (comboBox49.SelectedIndex == -1)
            {
                MessageBox.Show("Please select High page status");
                return;
            }
            LPSta = (Byte)comboBox48.SelectedIndex;
            HPSta = (Byte)comboBox49.SelectedIndex;
            Byte PageSta;
            PageSta =(Byte)( (LPSta & 0x0f) | (HPSta << 4 & 0xf0) );

            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_ProtectPage(hreader, hTag, PPPointer, PageSta);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void button79_Click_1(object sender, EventArgs e)
        {
            int iret;
            if (comboBox47.SelectedIndex == -1)
            {
                MessageBox.Show("Please select block address");
                return;
            }
            Byte PPPointer = (Byte)comboBox47.SelectedIndex;
          

            iret = RFIDLIB.rfidlib_aip_iso15693.NXPICODESLI_LockPageProtection(hreader, hTag, PPPointer);
            if (iret == 0)
            {
                MessageBox.Show("ok");
            }
            else
            {
                MessageBox.Show("fail");
            }
        }

        private void comboBox45_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch(comboBox45.SelectedIndex) {
                case 0:
                case 1:
                case 4:
                textBox26.Text ="00000000" ;
                break;
                case 2:
                case 3:
                textBox26.Text ="0F0F0F0F" ;
                break;

            }
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

    public class tagInfo
    {
        public string m_uid;
        public UInt32 m_tagType;
        public tagInfo(string uid, UInt32 tagType)
        {
            m_uid = uid;
            m_tagType = tagType;
        }
        public override string ToString()
        {
            return m_uid.ToString();
        }

    }
  
    public class CSupportedAirProtocol
    {
        public UInt32 m_ID;
        public string m_name;
        public Boolean m_en;
    }
}