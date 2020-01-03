package RFID;

public class rfidlib_LSGate {
	//static{
	//	System.loadLibrary("jni_rfidlib_LSGate");
	//}
	static String osName = "";
	public static void LoadLib(String sLibPath, int osType, int arType)
	{
		String libPath = "";
		
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
			libPath = String.format("%s/libs/%s/%s/rfidlib_LSGate.dll",
					sLibPath, osName, architecture);
			System.load(libPath);
			libPath = String.format("%s/libs/%s/%s/jni_rfidlib_LSGate.dll",
					sLibPath, osName, architecture);
			System.load(libPath);
			
			//libPath = String.format("%s/libs/%s/%s/Drivers",
			//		sLibPath, osName, architecture);
			//RDR_LoadReaderDrivers(libPath);
		}
		else if (osName.equals("Linux"))
		{
		}
	}
	public native static int LSG_GetLibVersion(char[] buf ,int nSize /* in character */)  ;
	public native static int LSG_CmdGetReports(long hr ,byte Flag,byte recordsToGet) ;
	public native static int LSG_CmdGetSystemTime(long hr,Integer year,Byte month,Byte day ,Byte hour,Byte minute,Byte second);
	public native static int LSG_CmdSetSystemTime(long hr,int year,byte month,byte day ,byte hour,byte minute,byte second) ;
	public native static int LSG_CmdResetFlowOfPeople(long hr,byte flag) ;
	public native static int LSG_CmdGetCurrentFlowOfPeople(long hr,Integer inFlow,Integer outFlow);
	public native static int LSG_CmdReverseDirection(long hr);
	public native static int LSG_ParseSCEventData(long hReport ,char[] slData,Integer nSize,Byte dir ,byte[] time) ;
}
