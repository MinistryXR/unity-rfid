package RFID;

public class rfidlib_nfc
{
	//static{
	//	System.loadLibrary("jni_rfidlib_nfc");
	//}
	
	public static void LoadLib(String sLibPath, int osType, int arType)
	{
		String libPath = "";
		String osName = "";
		String architecture = "";
		if (osType == rfid_def.VER_LINUX)
		{
			osName = "Linux";
		}
		else if (osType == rfid_def.VER_WINDOWS)
		{
			osName = "Windows";
		}

		if (arType == rfid_def.AR_X86)
		{
			architecture = "x86";
		}
		else if (arType == rfid_def.AR_X64)
		{
			architecture = "x64";
		}

		if (osName.equals("Windows"))
		{
			libPath = String.format("%s/libs/%s/%s/rfidlib_nfc.dll",
					sLibPath, osName, architecture);
			System.load(libPath);
			libPath = String.format("%s/libs/%s/%s/jni_rfidlib_nfc.dll",
					sLibPath, osName, architecture);
			System.load(libPath);
		}
		else if(osName.equals("Linux"))
		{
			//libPath = String.format("%s/libs/%s/%s/librfidlib_aip_iso15693.so",
			//		sLibPath, osName, architecture);
			//System.load(libPath);
		}
	}
	
	public native static long nfc_CreateUriNdef(String sNetAddr, byte UriType);

	public native static int nfc_WriteNdef(long hReader, long hTag, long hNdef, byte IsLock);

	public native static int nfc_ReadNdef(long hReader, long hTag,Long hNdef,Byte NdefType);

	public native static int nfc_ParseNdefByUri(long hNdef, char[] sNetAddr, int NetAddrSize, Byte netType);
}
