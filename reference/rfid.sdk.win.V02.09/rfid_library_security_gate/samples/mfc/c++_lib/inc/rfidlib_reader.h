#ifndef __RFIDLIB_READER_H__
#define __RFIDLIB_READER_H__


#include "rfidlib.h"

#ifdef __cplusplus
extern "C" {
#endif


 
/************************************functions not opened for application*******************************/
RFID_DN_HANDLE RFIDLIB_API RDR_CreateAccessNoneParamRequest(DWORD accessCode) ; // use

err_t RFIDLIB_API RDR_GetCapabilities(RFID_READER_HANDLE hr, 
									  BYTE Type ,
									  RFID_DN_HANDLE pCapabilityData /* out */
									  ) ;
err_t RFIDLIB_API RDR_SetConfig(RFID_READER_HANDLE hr,
								RFID_DN_HANDLE  CfgItemSettingData /* Input,Node name is item name */
								) ;
err_t RFIDLIB_API RDR_GetConfig(RFID_READER_HANDLE hr,
								RFID_DN_HANDLE pCfgItemGettedData /*Output ,Node name is item name*/
								) ;
err_t RFIDLIB_API RDR_EnableAsyncTagReportOutput(RFID_READER_HANDLE hr,BYTE type,WIN_MSG_t msg ,HWND hwnd,RFID_EVENT_CALLBACK cb) ;
err_t RFIDLIB_API RDR_DisableAsyncTagReportOutput(RFID_READER_HANDLE hr);
err_t RFIDLIB_API RDR_IsSupportInventoryAsyncOutput(RFID_READER_HANDLE hr, BOOLEAN *suppported);
RFID_DN_HANDLE RFIDLIB_API RDR_CreateSetGetConfigItemList();

/*********************************functions opened*****************************************************/

/*
* get lib version
*/
DWORD RFIDLIB_API RDR_GetLibVersion(LPTSTR buf ,DWORD nSize /* in character */)  ;
/*
* load device drivers
*/
err_t RFIDLIB_API RDR_LoadReaderDrivers(LPCTSTR path) ;
/*
* get loaded device driver count
*/
DWORD RFIDLIB_API RDR_GetLoadedReaderDriverCount() ;
/*
*get loaded device driver option
*/
err_t RFIDLIB_API RDR_GetLoadedReaderDriverOpt(DWORD idx ,LPCTSTR option ,LPTSTR valueBuffer,DWORD *nSize );
/*
*get loaded device driver option by name 
*/
err_t RFIDLIB_API RDR_GetLoadedReaderDriverOptByName(LPCTSTR ID ,LPCTSTR option ,LPTSTR valueBuffer,DWORD *nSize) ;

DWORD RFIDLIB_API HID_Enum(LPCTSTR DevId)  ;
err_t RFIDLIB_API HID_GetEnumItem(DWORD indx ,BYTE infType,LPTSTR infBuffer,DWORD *nSize ) ;
DWORD RFIDLIB_API COMPort_Enum(void) ;
err_t RFIDLIB_API COMPort_GetEnumItem(DWORD idx,LPTSTR nameBuf,DWORD nSize ) ;
err_t RFIDLIB_API RDR_Open(LPCTSTR connStr ,RFID_READER_HANDLE *hrOut) ;
err_t RFIDLIB_API RDR_Close(RFID_READER_HANDLE hr)  ;
/*
*create inventory parameter list node
*/
RFID_DN_HANDLE RFIDLIB_API RDR_CreateInvenParamSpecList()  ;  
/*
*inventory,support multiple air protocol ,embedded commands
*/
err_t RFIDLIB_API RDR_TagInventory(RFID_READER_HANDLE hr,
									 BYTE AIType,
									BYTE AntennaCount,
									 BYTE AntennaIDs[] ,
								 RFID_DN_HANDLE InvenParamSpecList) ;
/*
*get tag data report count
*/
DWORD RFIDLIB_API RDR_GetTagDataReportCount(RFID_READER_HANDLE hr) ;
/*
*get tag data report
*/
RFID_DN_HANDLE	RFIDLIB_API RDR_GetTagDataReport(RFID_READER_HANDLE hr , BYTE seek) ;
/*
*connect tag
*/
err_t RFIDLIB_API RDR_TagConnect(RFID_READER_HANDLE hr,
							RFID_DN_HANDLE ConnParms,   /* Connect parameters,inclue AIP id and tag id */
							RFID_TAG_HANDLE *hTag   /* Return handle of the connected picc */
							) ;
/*
*access tag  
*/
err_t RFIDLIB_API RDR_TagAccess(RFID_READER_HANDLE hr,
								RFID_TAG_HANDLE hTag,		/* the handle of connected picc */
								RFID_DN_HANDLE tagAccess 
								)  ;
/*
*disconnect tag
*/
err_t RFIDLIB_API RDR_TagDisconnect(RFID_READER_HANDLE hr,
									 RFID_TAG_HANDLE hTag)  ;
/*
*disconnect all connected tags
*/
err_t RFIDLIB_API RDR_DisconnectAllTags(RFID_READER_HANDLE hr)  ;
/*
*get reader last return error 
*/
err_t RFIDLIB_API RDR_GetReaderLastReturnError(RFID_READER_HANDLE hr)  ;

err_t RFIDLIB_API RDR_SetAcessAntenna(RFID_READER_HANDLE hr ,BYTE AntennaID) ;

err_t RFIDLIB_API RDR_OpenRFTransmitter(RFID_READER_HANDLE hr) ;

err_t RFIDLIB_API RDR_CloseRFTransmitter(RFID_READER_HANDLE hr) ;

err_t RFIDLIB_API RDR_SetCommuImmeTimeout(RFID_READER_HANDLE hr) ;
err_t RFIDLIB_API RDR_ResetCommuImmeTimeout(RFID_READER_HANDLE hr) ;

DWORD RFIDLIB_API RDR_GetAntennaInterfaceCount(RFID_READER_HANDLE hr)  ;

err_t RFIDLIB_API RDR_GetOutputCount(RFID_READER_HANDLE hr,BYTE *nCount) ;

err_t RFIDLIB_API RDR_GetOutputName(RFID_READER_HANDLE hr,BYTE idxOut,LPTSTR bufName ,DWORD *nSize)  ;

RFID_DN_HANDLE RFIDLIB_API RDR_CreateSetOutputOperations() ;

/*
* outMode:
  0: No change 
  1: On 
  2: Off
  3: flash
*/
err_t RFIDLIB_API RDR_AddOneOutputOperation(RFID_DN_HANDLE hOperas,BYTE outNo,BYTE outMode,DWORD outFrequency,DWORD outActiveDuration ,DWORD outInactiveDuration) ;

err_t RFIDLIB_API RDR_SetOutput(RFID_READER_HANDLE hr ,RFID_DN_HANDLE outputOpers /* output operations */) ;

err_t RFIDLIB_API RDR_LoadFactoryDefault(RFID_READER_HANDLE hr) ;




err_t RFIDLIB_API RDR_SystemReset(RFID_READER_HANDLE hr) ;


err_t RFIDLIB_API RDR_GetReaderInfor(RFID_READER_HANDLE hr,
									 BYTE Type ,
									 LPTSTR buffer,
									 DWORD *nSize) ;

err_t RFIDLIB_API RDR_ConfigBlockWrite(RFID_READER_HANDLE hr,DWORD cfgno ,BYTE cfgdata[],DWORD nSize,DWORD mask) ;
err_t RFIDLIB_API RDR_ConfigBlockRead(RFID_READER_HANDLE hr,DWORD cfgno,BYTE cfgbuff[],DWORD nSize)  ;
err_t RFIDLIB_API RDR_ConfigBlockSave(RFID_READER_HANDLE hr,DWORD cfgno) ;

err_t RFIDLIB_API RDR_CreateRS485Node( RFID_READER_HANDLE hr ,DWORD busAddr,RFID_READER_HANDLE *ohrRS485Node)  ;

err_t RFIDLIB_API RDR_GetSupportedAirInterfaceProtocol(RFID_READER_HANDLE hr ,DWORD index,DWORD *AIPType) ;

err_t RFIDLIB_API RDR_DetectNoise(RFID_READER_HANDLE hr ,BYTE noiseData[] ,DWORD *nSize)  ;

err_t RFIDLIB_API RDR_EnableProtocolLog(RFID_READER_HANDLE hr,BYTE methType,WIN_MSG_t msg ,HWND hwnd,RFID_EVENT_CALLBACK_NEW cb,void *param) ;
err_t RFIDLIB_API RDR_DisalbeProtocolLog(RFID_READER_HANDLE hr) ;
err_t RFIDLIB_API RDR_GetGPICount(RFID_READER_HANDLE hr,DWORD *oCount)  ;

err_t RFIDLIB_API RDR_ExeSpecialControlCmd(RFID_READER_HANDLE hr,LPCTSTR cmd ,LPCTSTR params,LPTSTR result,DWORD *nSize) ;

err_t RFIDLIB_API RDR_GetGPIsStatus(RFID_READER_HANDLE hr/* in */ ,
									BYTE GPIs[]/* in */  ,
									WORD number /* in */ ,
									BYTE status[] /* out */) ;

err_t RFIDLIB_API RDR_SetEventHandler(RFID_READER_HANDLE hr,BYTE eventType,BYTE methType,UINT msg ,HWND hwnd,RFID_EVENT_CALLBACK_NEW cb,VOID *param)  ;
err_t RFIDLIB_API RDR_GetAirInterfaceProtName(RFID_READER_HANDLE hr ,DWORD AIPType ,LPTSTR namebuf,DWORD nSize )  ;
err_t RFIDLIB_API RDR_LoadAuthKey(RFID_READER_HANDLE hr ,BYTE storeType,BYTE keyType ,BYTE key[] ,WORD keylen) ;
err_t RFIDLIB_API RDR_SelectAuthKey(RFID_READER_HANDLE hr ,BYTE keyType) ;
err_t RFIDLIB_API RDR_CommandTransceive(RFID_READER_HANDLE hr,DWORD cmd ,BYTE *prmDataSnd ,DWORD bytesToSnd ,BYTE *prmDataRecv,DWORD *bytesRecv,DWORD timeout) ;
err_t RFIDLIB_API RDR_StartBootLoader(RFID_READER_HANDLE hr) ;
err_t RFIDLIB_API RDR_UpdateHardSerialNum(RFID_READER_HANDLE hr ,BYTE sernum[] ,WORD length) ;
err_t RFIDLIB_API RDR_ResetRF(RFID_READER_HANDLE hr ) ;

err_t RFIDLIB_API DNODE_Destroy(RFID_DN_HANDLE dn) ; 

err_t RFIDLIB_API RDR_SetInvenStopTrigger(RFID_DN_HANDLE hInvenParams,BYTE stopTriggerType,DWORD maxTimeout,DWORD triggerValue)  ;

err_t RFIDLIB_API RDR_IsSupportEmbeddedTagAccess(RFID_READER_HANDLE hr,BOOLEAN *isSupported);

DWORD RFIDLIB_API Bluetooth_Enum();
err_t RFIDLIB_API Bluetooth_GetEnumItem(DWORD idx ,BYTE infType,LPTSTR nameBuf,DWORD *nSize );

/*
* 标示在关闭之前停止所有通行操作 ， 通信连接有可能会中断
*/
err_t RFIDLIB_API RDR_SetStopCommBeforeClose(RFID_READER_HANDLE hr) ;


err_t  RFIDLIB_API RDR_GetSystemTime(RFID_READER_HANDLE hr ,DWORD *year,BYTE *month,BYTE *day ,BYTE *hour,BYTE *minute,BYTE *second)  ;
err_t  RFIDLIB_API RDR_SetSystemTime(RFID_READER_HANDLE hr ,DWORD year,BYTE month,BYTE day ,BYTE hour,BYTE minute,BYTE second)  ;
err_t RFIDLIB_API RDR_BuffMode_FetchRecords(RFID_READER_HANDLE hr ,DWORD flags)  ;
err_t RFIDLIB_API RDR_BuffMode_ClearRecords(RFID_READER_HANDLE hr ) ;
err_t RFIDLIB_API RDR_BuffMode_FlashEmpty(RFID_READER_HANDLE hr ) ;

 
err_t  RFIDLIB_API RDR_StartRO(RFID_READER_HANDLE hr ,DWORD ROSepcID) ;
err_t  RFIDLIB_API RDR_StopRO(RFID_READER_HANDLE hr ,DWORD ROSepcID) ;

err_t  RFIDLIB_API RDR_ParseTagDataReportRaw(RFID_DN_HANDLE hTagReport,BYTE rawBuffer[],DWORD *nSize) ;
err_t  RFIDLIB_API  RDR_BuffMode_StartReportCollection(RFID_READER_HANDLE hr)  ;
err_t  RFIDLIB_API  RDR_BuffMode_StopReportCollection(RFID_READER_HANDLE hr)  ;
err_t  RFIDLIB_API  RDR_BuffMode_StopReportCollectionNoWait(RFID_READER_HANDLE hr) ;
err_t  RFIDLIB_API RDR_ResetPassingCounter(RFID_READER_HANDLE hr , DWORD flag)  ;
err_t  RFIDLIB_API RDR_GetPassingCounter(RFID_READER_HANDLE hr ,DWORD *inFlow,DWORD *outFlow)  ;
err_t  RFIDLIB_API RDR_ReverseInOutDirection(RFID_READER_HANDLE hr )  ;
err_t  RFIDLIB_API RDR_Login(RFID_READER_HANDLE hr, BYTE pwd[]);
err_t  RFIDLIB_API RDR_EnablePasswordLogin(RFID_READER_HANDLE hr, BYTE pwd[], BOOLEAN enable);
err_t  RFIDLIB_API RDR_UpdateLoginPassword(RFID_READER_HANDLE hr, BYTE pwd[], BYTE newPwd[]);
err_t  RFIDLIB_API RDR_GetAIPTypeName(RFID_READER_HANDLE hr, DWORD AIP_ID, LPTSTR nameBuf, DWORD *nSize);
err_t  RFIDLIB_API RDR_GetTagTypeName(RFID_READER_HANDLE hr, DWORD AIP_ID, DWORD TAG_ID, LPTSTR nameBuf, DWORD *nSize);
err_t  RFIDLIB_API RDR_ResetTagFilterCounter(RFID_READER_HANDLE hr);

err_t RFIDLIB_API RDR_ModuleStartBootLoader(RFID_READER_HANDLE hr, LPCTSTR sDevId);
err_t RFIDLIB_API RDR_ModuleStopMBootLoader(RFID_READER_HANDLE hr);
err_t RFIDLIB_API RDR_ModuleTransferData(RFID_READER_HANDLE hr,DWORD timeout,BYTE transferData[], DWORD nTransferData, BYTE dataBack[], DWORD *nDataBackSize);

err_t RFIDLIB_API RDR_ResetBackupAntenna(RFID_READER_HANDLE hr);

#ifdef __cplusplus
}
#endif




#endif

