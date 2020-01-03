package RFID;

public class rfidlib_reader
{
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
			libPath = String.format("%s/libs/%s/%s/rfidlib_reader.dll",
					sLibPath, osName, architecture);
			System.load(libPath);
			libPath = String.format("%s/libs/%s/%s/jni_rfidlib_reader.dll",
					sLibPath, osName, architecture);
			System.load(libPath);
			
			libPath = String.format("%s/libs/%s/%s/Drivers",
					sLibPath, osName, architecture);
			RDR_LoadReaderDrivers(libPath);
		}
		else if (osName.equals("Linux"))
		{
			libPath = String.format("%s/libs/%s/%s/librfidlib_reader.so",
						sLibPath, osName, architecture);
			System.load(libPath);
		}
	}
	
	
	public static String COMPort_GetEnumItem(int idx)
	{
		char nameBuf[] = new char[512];
		Integer nSize = new Integer(0);
		rfidlib_reader.COMPort_GetEnumItem(idx, nameBuf, nSize);
		
		if(osName.equals("Linux"))
		{
			char tmp[] = new char[255];
			for(int j=0;j<nSize;j++)
			{
				if(j%2==0)
				{
					tmp[j/2] = nameBuf[j];
				}
			}
			return String.copyValueOf(tmp, 0, nSize/2);
		}
		else if(osName.equals("Windows"))
		{
			return String.copyValueOf(nameBuf, 0, nSize);
		}
		return "";
	}
	
	public static int RDR_GetReaderInfor(long hr,StringBuilder str)
	{
		char[] buffer = new char[255];
		Integer nSize = new Integer(buffer.length);
		int iret = rfidlib_reader.RDR_GetReaderInfor(hr, (byte) 1,
				buffer, nSize);
		if(iret!=0)
		{
			return iret;
		}
		
		if(osName.equals("Linux"))
		{
			char tmp[] = new char[255];
			for(int j=0;j<nSize;j++)
			{
				if(j%2==0)
				{
					tmp[j/2] = buffer[j];
				}
			}
			str.append( String.copyValueOf(tmp, 0, nSize/2));
		}
		else if(osName.equals("Windows"))
		{
			str.append( String.copyValueOf(buffer, 0, nSize/2));
		}
		else
		{
			return -1;
		}
		return iret;
	}

	public native static int RDR_GetLibVersion(char[] buffer, int nSize);

	public native static int RDR_LoadReaderDrivers(String path);

	public native static int RDR_GetLoadedReaderDriverCount();

	public native static int RDR_GetLoadedReaderDriverOpt(int idx,
			String option, char[] valueBuffer, Integer nSize/** out **/
	);

	public native static int RDR_GetLoadedReaderDriverOptByName(String ID,
			String option, char[] valueBuffer, Integer nSize/*** out **/
	);

	public native static int HID_Enum(String DevId);

	public native static int HID_GetEnumItem(int indx, byte infType,
			char[] infBuffer, Integer nSize/** out **/
	);

	public native static int COMPort_Enum();

	public native static int COMPort_GetEnumItem(int idx, char[] nameBuf,
			Integer nSize/* out */);

	public native static int RDR_Open(String connStr, Long hrOut/* out */);

	public native static int RDR_Close(long hr);

	public native static long RDR_CreateInvenParamSpecList();

	public native static int RDR_TagInventory(long hr, byte AIType,
			byte AntennaCount, byte[] AntennaIDs, long InvenParamSpecList);

	public native static int RDR_GetTagDataReportCount(long hr);

	public native static long RDR_GetTagDataReport(long hr, byte seek);

	public native static int RDR_TagConnect(long hr, int ConnParms, Integer hTag/* out */);

	public native static int RDR_TagDisconnect(long hr, long hTag);

	public native static int RDR_DisconnectAllTags(long hr);

	public native static int RDR_GetReaderLastReturnError(long hr);

	public native static int RDR_SetAcessAntenna(long hr, byte AntennaID);

	public native static int RDR_OpenRFTransmitter(long hr);

	public native static int RDR_CloseRFTransmitter(long hr);

	public native static int RDR_SetCommuImmeTimeout(long hr);

	public native static int RDR_ResetCommuImmeTimeout(long hr);

	public native static int RDR_GetAntennaInterfaceCount(long hr);

	public native static int RDR_GetOutputCount(long hr, Byte nCount);

	public native static int RDR_GetOutputName(long hr, byte idxOut,
			char[] bufName, Integer nSize);

	public native static long RDR_CreateSetOutputOperations();

	public native static int RDR_AddOneOutputOperation(long hOperas,
			byte outNo, byte outMode, int outFrequency, int outActiveDuration,
			int outInactiveDuration);

	public native static int RDR_SetOutput(long hr, long outputOpers);

	public native static int RDR_LoadFactoryDefault(long hr);

	public native static long RDR_CreateSetGetConfigItemList();

	public native static int RDR_SystemReset(long hr);

	public native static int RDR_IsSupportInventoryAsyncOutput(long hr,
			Boolean suppported);

	public native static int RDR_GetReaderInfor(long hr, byte Type,
			char[] buffer, Integer nSize);

	public native static int RDR_ConfigBlockWrite(long hr, int cfgno,
			byte[] cfgdata, int nSize, int mask);

	public native static int RDR_ConfigBlockRead(long hr, int cfgno,
			byte[] cfgbuff, int nSize);

	public native static int RDR_ConfigBlockSave(long hr, int cfgno);

	public native static int RDR_CreateRS485Node(long hr, int busAddr,
			Integer ohrRS485Node);

	public native static int RDR_GetSupportedAirInterfaceProtocol(long hr,
			int index, Integer AIPType);

	public native static int RDR_GetGPICount(long hr, Integer oCount);

	public native static int RDR_LoadAuthKey(long hr, byte storeType,
			byte keyType, byte[] key, int keylen);

	public native static int RDR_SelectAuthKey(long hr, byte keyType);

	public native static int RDR_SafeAuthencate(long hr, int hTag, int params);

	public native static int RDR_ResetRF(long hr);

	public native static int DNODE_Destroy(long hr);
}
