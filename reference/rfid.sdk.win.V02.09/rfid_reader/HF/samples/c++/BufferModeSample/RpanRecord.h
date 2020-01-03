#pragma once
#include "rfidlib_reader.h"
//#include "rfidlib_drv_rpan.h"

typedef err_t (RFIDLIB_API *P_ANRPAN_SetSysTime)(RFID_READER_HANDLE hr,WORD year,BYTE month,BYTE day,BYTE hour,BYTE min,BYTE sec);
typedef err_t (RFIDLIB_API *P_ANRPAN_ParseRecord)(RFID_READER_HANDLE hr,RFID_DN_HANDLE hReport,BYTE* buffer,int *len);
typedef err_t (RFIDLIB_API *P_ANRPAN_GetRecord)(RFID_READER_HANDLE hr,BYTE flg);
typedef err_t (RFIDLIB_API *P_ANRPAN_ClearRecord)(RFID_READER_HANDLE hr);

class CRpanRecord
{
public:
	CRpanRecord(void);
	~CRpanRecord(void);
	 bool  init(CString path);

	 err_t ANRPAN_SetSysTime(RFID_READER_HANDLE hr,WORD year,BYTE month,BYTE day,BYTE hour,BYTE min,BYTE sec);
	 err_t ANRPAN_ParseRecord(RFID_READER_HANDLE hr,RFID_DN_HANDLE hReport,BYTE* buffer,int *len);
	 err_t ANRPAN_GetRecord(RFID_READER_HANDLE hr,BYTE flg);
	 err_t ANRPAN_ClearRecord(RFID_READER_HANDLE hr);

private:
	P_ANRPAN_SetSysTime API_ANRPAN_SetSysTime;
    P_ANRPAN_ParseRecord API_ANRPAN_ParseRecord;
	P_ANRPAN_GetRecord API_ANRPAN_GetRecord;
	P_ANRPAN_ClearRecord API_ANRPAN_ClearRecord;
	HINSTANCE hDll; //DLL¾ä±ú 
};
