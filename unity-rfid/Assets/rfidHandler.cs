using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;


public class rfidHandler : MonoBehaviour
{
    [DllImport("rfidlib_reader")]
    public static extern int RDR_Open(string connStr, ref UIntPtr hrOut);

    [DllImport("rfidlib_reader")]
    public static extern int RDR_Close(UIntPtr hr);

    [DllImport("rfidlib_reader")]
    public static extern int RDR_LoadReaderDrivers(string drvpath);

    [DllImport("rfidlib_reader")]
    public static extern UInt32 RDR_GetLoadedReaderDriverCount();

    [DllImport("rfidlib_reader")]
    public static extern UIntPtr RDR_CreateInvenParamSpecList();

    [DllImport("rfidlib_reader")]
    public static extern int RDR_TagInventory(UIntPtr hr, Byte AIType, Byte AntennaCoun, Byte[] AntennaIDs, UIntPtr InvenParamSpecList);

    [DllImport("rfidlib_reader")]
    public static extern UIntPtr RDR_GetTagDataReport(UIntPtr hr, Byte seek);

    [DllImport("rfidlib_reader")]
    public static extern UInt32 RDR_GetTagDataReportCount(UIntPtr hr);

    [DllImport("rfidlib_aip_iso14443A")]
    public static extern UIntPtr ISO14443A_CreateInvenParam(UIntPtr hInvenParamSpecList,Byte AntennaID);

    [DllImport("rfidlib_aip_iso14443A")]
    public static extern int ISO14443A_ParseTagDataReport(UIntPtr hTagReport, ref UInt32 aip_id, ref UInt32 tag_id, ref UInt32 ant_id, Byte[] uid, ref Byte uidlen);

    UIntPtr hreader;

    // Start is called before the first frame update
    void Start()
    {
        RDR_LoadReaderDrivers("D:/Projects/RFID_test/Drivers");
        uint count = RDR_GetLoadedReaderDriverCount();
        Debug.Log("Loaded " + count + " drivers");
        hreader = (UIntPtr)0;
    }

    // Update is called once per frame
    void Update()
    {
        Byte AIType = 1;
        int iCount = 0;
        byte AntennaSelCount = (Byte)iCount;
        byte[] AntennaSel = new byte[16];

        UIntPtr InvenParamSpecList = UIntPtr.Zero;
        InvenParamSpecList = RDR_CreateInvenParamSpecList();
        if (InvenParamSpecList.ToUInt64() != 0)
        {
            ISO14443A_CreateInvenParam(InvenParamSpecList, 0);
        }
       
        int iret = RDR_TagInventory(hreader, AIType, AntennaSelCount, AntennaSel, InvenParamSpecList);
        if (iret == 0 || iret == -21)
        {
            RDR_GetTagDataReportCount(hreader);

            UIntPtr TagDataReport;
            TagDataReport = (UIntPtr)0;
            TagDataReport = RDR_GetTagDataReport(hreader, 1); //first

            while (TagDataReport.ToUInt64() > 0)
            {
                UInt32 aip_id = 0;
                UInt32 tag_id = 0;
                UInt32 ant_id = 0;
                Byte dsfid = 0;
                Byte uidlen = 0;
                Byte[] uid = new Byte[16];

                iret = ISO14443A_ParseTagDataReport(TagDataReport, ref aip_id, ref tag_id, ref ant_id, uid, ref uidlen);
                if (iret == 0)
                {
                    object[] pList = { aip_id, tag_id, ant_id, uid, (int)uidlen };
                    string strUid = BitConverter.ToString(uid, 0, (int)uidlen).Replace("-", string.Empty);
                    Debug.Log(strUid);
                }

                TagDataReport = RDR_GetTagDataReport(hreader, 2);
            }
        }
    }

    public void connect()
    {
        string connstr = "RDType=RL8000;CommType=USB;AddrMode=1;SerNum=09703400DC";
        //UIntPtr hreader = (UIntPtr)0; 
        int iret = RDR_Open(connstr, ref hreader);
        if (iret != 0) Debug.Log("Failed to open reader");
        else Debug.Log("Opened reader");
    }


    public void stop()
    {
        int iret = 0;
        iret = RDR_Close(hreader);
        if (iret == 0)
        {
            hreader = (UIntPtr)0;
            Debug.Log("Closed reader");
        }
        else
        {
            Debug.Log("Fail to close");
        }

    }
}
