using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace RFIDLIB
{
    public class rfidlib_drv_rpan
    {
#if UNICODE
        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern UInt32 ANRPAN_GetLibVersion(StringBuilder buf, UInt32 nSize /* in character */);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_SerialOpen(string comname, UInt32 baud, string frame, ref UIntPtr o_hr /* out parameter */);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_HidOpen(Byte AddrMode, string DeviceIdentifyStr, ref UIntPtr o_hr /* out parameter */);


        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_TCPOpen(string readerIPAddr, UInt16 remotePort, string localIPToBind, ref UIntPtr o_hr /* out parameter */);


        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_Close(UIntPtr hr);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_SetSysTime(UIntPtr hr, UInt16 year, Byte month, Byte day, Byte hour, Byte min, Byte sec);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_ParseRecord(UIntPtr hr, UIntPtr hReport, Byte[] buffer, ref int len);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_GetRecord(UIntPtr hr, Byte flg);


        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_ClearRecord(UIntPtr hr);
#else
        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern UInt32 ANRPAN_GetLibVersion(StringBuilder buf, UInt32 nSize /* in character */);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_SerialOpen(string comname, UInt32 baud, string frame, ref UIntPtr o_hr /* out parameter */);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_HidOpen(Byte AddrMode, string DeviceIdentifyStr, ref UIntPtr o_hr /* out parameter */);


        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_TCPOpen(string readerIPAddr, UInt16 remotePort, string localIPToBind, ref UIntPtr o_hr /* out parameter */);


        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_Close(UIntPtr hr);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_SetSysTime(UIntPtr hr, UInt16 year, Byte month, Byte day, Byte hour, Byte min, Byte sec);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_ParseRecord(UIntPtr hr, UIntPtr hReport, Byte[] buffer, ref int len);

        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_GetRecord(UIntPtr hr, Byte flg);


        [DllImport(".\\Drivers\\rfidlib_drv_rpan.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int ANRPAN_ClearRecord(UIntPtr hr);
#endif

    }
}
