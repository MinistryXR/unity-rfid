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

        Thread InvenThread;
        public Form1()
        {
            InitializeComponent();
            hreader = (UIntPtr)0;


        }


        public Boolean tag_inventory(ref string suid)
        {

            Boolean found = false;
            int iret;
            Byte[] AntennaSel = new Byte[1];
            iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, 1, 0, AntennaSel, UIntPtr.Zero);
            if (iret == 0)
            {

                UIntPtr TagDataReport;
                TagDataReport = (UIntPtr)0;
                TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST); //first
                if (TagDataReport != UIntPtr.Zero)
                {
                    UInt32 aip_id = 0;
                    UInt32 tag_id = 0;
                    UInt32 ant_id = 0;
                    Byte dsfid = 0;
                    Byte uidlen = 0;
                    Byte[] uid = new Byte[16];

                    RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, ref dsfid, uid);

                    suid = BitConverter.ToString(uid, 0, (int)8).Replace("-", string.Empty);
                    found = true;
                }

            }

            return found;
        }
    
       
        private void button2_Click(object sender, EventArgs e)
        {

            int iret;
            /*
             * Try to open communcation layer for specified reader 
             */

            string readerDriverName ="RD100" ;
            string connstr ="";

            // Build USBHID communication connection string
            connstr = RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=" + readerDriverName + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE+"=0;" +
                          RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=";
          
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
            }
            else
            {
                button2.Enabled = false;
                button3.Enabled = true;
                button1.Enabled = true;

            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int iret;
            iret = RFIDLIB.rfidlib_reader.RDR_Close(hreader);
            if (iret == 0)
            {
                hreader = (UIntPtr)0;

                button2.Enabled = true;
                button3.Enabled = false;
                button1.Enabled = false;
            }
            else
            {
                MessageBox.Show("fail");
            }
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
     
   

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {

        }



        private void Form1_Load(object sender, EventArgs e)
        {
            /* 
             *  Call required, when application load ,this API just only need to load once
             *  Load all reader driver dll from drivers directory, like "rfidlib_ANRD201.dll"  
             */
            RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\\Drivers");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string uid;
            uid = "";
            if (tag_inventory(ref uid))
            {
                textBox1.Text = uid;
            }
            else
            {
                MessageBox.Show("tag not found");
            }
        }


    }
 
}