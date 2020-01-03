package RFID;

public class rfidlib_aip_iso14443A
{
	//static
	//{
	//	System.loadLibrary("jni_rfidlib_aip_iso14443A");
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
			libPath = String.format("%s/libs/%s/%s/rfidlib_aip_iso14443A.dll",
					sLibPath, osName, architecture);
			System.load(libPath);
			libPath = String.format("%s/libs/%s/%s/jni_rfidlib_aip_iso14443A.dll",
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

	public native static int ISO14443A_GetLibVersion(char[] buf, int nSize);

	public native static int ISO14443A_ParseTagDataReport(long hTagReport,
			Integer aip_id, Integer tag_id, Integer ant_id, byte[] uid,
			Byte uidlen);

	public native static long ISO14443A_CreateInvenParam(
			long hInvenParamSpecList, byte AntennaID);

	public native static int ULTRALIGHT_Connect(long hr,
			byte[] uid/* 7 bytes */, Long ht);

	public native static int ULTRALIGHT_LockPage(long hr, long ht, byte pageType);

	public native static int ULTRALIGHT_LockBlock(long hr, long ht,
			byte blockType);

	public native static int ULTRALIGHT_ReadMultiplePages(long hr, long ht,
			byte pageStart, byte pageNum, byte[] databuf, Integer nSize);

	public native static int ULTRALIGHT_WriteMultiplePages(long hr, long ht,
			byte pageStart, byte pageNum, byte[] databuf, int bytesToWrite);

	public native static int ULTRALIGHT_Authenticate(long hr, long ht,
			byte[] key /* 16bytes */);

	public native static int ULTRALIGHT_UpdatePassword(long hr, long ht,
			byte[] key);

	public native static int ULTRALIGHT_UpdateAuthConfig(long hr, long ht,
			byte auth0, byte auth1);

	public native static int MFCL_Connect(long hr, byte tagType,
			byte[] uid/* 4 bytes */, Long ht);

	public native static int MFCL_ReadBlock(long hr, long ht, byte blkAddr,
			byte blkData[], int nSize);

	public native static int MFCL_WriteBlock(long hr, long ht, byte blkAddr,
			byte[] blkData/* 16 bytes */);

	public native static int MFCL_Authenticate(long hr, long ht, byte blkAddr,
			byte keyType, byte[] key);

	public native static int MFCL_Increment(long hr, long ht, byte blkAddr,
			int val);

	public native static int MFCL_Decrement(long hr, long ht, byte blkAddr,
			int val);

	public native static int MFCL_Restore(long hr, long ht, byte blkAddr);

	public native static int MFCL_Transfer(long hr, long ht, byte blkAddr);

	public native static int MFCL_FormatValueBlock(long hr, long ht,
			byte blkAddr, int initValue);

	/*
	 * NTAG21x functions
	 */
	public native static int NTAG21x_Connect(long hr, byte uid[] /* 7 bytes */,
			Long ht);

	public native static int NTAG21x_ReadMultiplePages(long hr, long ht,
			int pageStart, int pageNum, byte databuf[], Integer nSize);

	public native static int NTAG21x_WriteMultiplePages(long hr, long ht,
			int pageStart, int pageNum, byte databuf[], int bytesToWrite);

	public native static int NTAG21x_Authenticate(long hr, long ht,
			long pwd, Integer pack);

	public native static int NTAG21x_GetVersion(long hr, long ht, byte ver[] /* out */);

	public native static int NTAG21x_ReadCnt(long hr, long ht, Integer counter /* out */);

	public native static int NTAG21x_ReadSig(long hr, long ht, byte sig[] /* out */);
}
