using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace RFIDLIB
{
    class rfidlib_nfc
    {
#if UNICODE
        [DllImport("rfidlib_nfc.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern UIntPtr nfc_CreateUriNdef(string sNetAddr, Byte UriType);

        [DllImport("rfidlib_nfc.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int nfc_WriteNdef(UIntPtr hReader, UIntPtr hTag, UIntPtr hNdef, Byte IsLock);

        [DllImport("rfidlib_nfc.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int nfc_ReadNdef(UIntPtr hReader, UIntPtr hTag, ref UIntPtr hNdef, ref Byte NdefType);

        [DllImport("rfidlib_nfc.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int nfc_ParseNdefByUri(UIntPtr hNdef, StringBuilder sNetAddr, UInt32 NetAddrSize, ref Byte netType);

#else
        [DllImport("rfidlib_nfc.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern UIntPtr nfc_CreateUriNdef(string sNetAddr, Byte UriType);

        [DllImport("rfidlib_nfc.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int nfc_WriteNdef(UIntPtr hReader, UIntPtr hTag, UIntPtr hNdef, Byte IsLock);

        [DllImport("rfidlib_nfc.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int nfc_ReadNdef(UIntPtr hReader, UIntPtr hTag, ref UIntPtr hNdef, ref Byte NdefType);

        [DllImport("rfidlib_nfc.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int nfc_ParseNdefByUri(UIntPtr hNdef, StringBuilder sNetAddr, UInt32 NetAddrSize, ref Byte netType);

#endif

    }
}
