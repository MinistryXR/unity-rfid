#include "StdAfx.h"
#include "RpanRecord.h"

CRpanRecord::CRpanRecord(void)
{
	hDll = NULL;
	API_ANRPAN_SetSysTime = NULL;
	API_ANRPAN_ParseRecord = NULL;
	API_ANRPAN_GetRecord = NULL;
	API_ANRPAN_ClearRecord = NULL;
}

CRpanRecord::~CRpanRecord(void)
{
	if(hDll)
	{
		 FreeLibrary(hDll); 
	}
}


bool  CRpanRecord::init(CString path)
{
	/*CString dllPath ;
	if (path==_T(""))
	{
		dllPath = _T("rfidlib_drv_rpan.dll");
	}
	else
	{
		dllPath = _T(".") +path + _T("\\rfidlib_drv_rpan.dll");
	}*/

	hDll = LoadLibrary(path); 
	if (hDll==NULL)
	{
		return false;
	}

	API_ANRPAN_SetSysTime = (P_ANRPAN_SetSysTime)GetProcAddress(hDll,"ANRPAN_SetSysTime");
	API_ANRPAN_ParseRecord = (P_ANRPAN_ParseRecord)GetProcAddress(hDll,"ANRPAN_ParseRecord");
	API_ANRPAN_GetRecord = (P_ANRPAN_GetRecord)GetProcAddress(hDll,"ANRPAN_GetRecord");
	API_ANRPAN_ClearRecord = (P_ANRPAN_ClearRecord)GetProcAddress(hDll,"ANRPAN_ClearRecord");
	return true;
}

err_t CRpanRecord::ANRPAN_ParseRecord(RFID_READER_HANDLE hr,RFID_DN_HANDLE hReport,BYTE* buffer,int *len)
{
	return API_ANRPAN_ParseRecord(hr,hReport,buffer,len);
}

err_t CRpanRecord::ANRPAN_GetRecord(RFID_READER_HANDLE hr,BYTE flg)
{
	return API_ANRPAN_GetRecord(hr,flg);
}

err_t CRpanRecord::ANRPAN_ClearRecord(RFID_READER_HANDLE hr)
{
	return API_ANRPAN_ClearRecord(hr);
}

err_t CRpanRecord::ANRPAN_SetSysTime(RFID_READER_HANDLE hr,WORD year,BYTE month,BYTE day,BYTE hour,BYTE min,BYTE sec)
{
	return API_ANRPAN_SetSysTime(hr,year,month,day,hour,min,sec);
}