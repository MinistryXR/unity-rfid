#ifndef __RFIDLIB_AIP_ISO15693_H__
#define __RFIDLIB_AIP_ISO15693_H__


#include "rfidlib.h"

#ifdef __cplusplus
extern "C" {
#endif

DWORD RFIDLIB_API ISO15693_GetLibVersion(LPTSTR buf ,DWORD nSize /* in character */)  ;
/*
*	iso15693 inventory parameters
*/
// inventory need to match the AFI value 
RFID_DN_HANDLE RFIDLIB_API ISO15693_CreateInvenParam(RFID_DN_HANDLE hInvenParamSpecList,
															BYTE AntennaID/* By default set to 0,apply to all antenna */,
															BOOLEAN en_afi,
															BYTE afi,
															BYTE slot_type/*0:default,1: 1slot,16:16 slot */)   ;

err_t RFIDLIB_API ISO15693_SetInvenReadParam(
	RFID_DN_HANDLE hIso15693InvenParam, 
	BOOLEAN readSecSta, 
	DWORD blkAddr,
	DWORD numOfBlks);


/*
* Parse iso15693 tag data 
*/
err_t RFIDLIB_API ISO15693_ParseTagDataReport(RFID_DN_HANDLE hTagReport,
										  DWORD *aip_id,
										  DWORD *tag_id,
										  DWORD* ant_id,
										  BYTE *dsfid,
										  BYTE uid[])  ;

err_t RFIDLIB_API ISO15693_ParseInventoryReadReport(RFID_DN_HANDLE hTagReport,
	BYTE uid[],
	DWORD *numOfBlocks,
	BYTE blkData[],
	DWORD* nSize);


err_t RFIDLIB_API ISO15693_Connect(RFID_READER_HANDLE hr ,
								   DWORD tagType,
							BYTE address_mode,/* in param */ 
							BYTE uid[] ,
							RFID_TAG_HANDLE *ht
							) ;

err_t RFIDLIB_API ISO15693_Reset(RFID_READER_HANDLE hr ,
								 RFID_TAG_HANDLE ht /* Tag handle connected */) ;
err_t RFIDLIB_API ISO15693_ReadSingleBlock(
									RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht, /* Tag handle connected */
									BOOLEAN readSecSta,/* IN: Whether read security status */
								  DWORD blkAddr,/* IN: Block number  */
						BYTE bufBlockDat[], /* OUT: buffer for storing single block data or single block data +sec sta*/
						DWORD nSize /* in:size of the buffer*/,
						DWORD *bytesBlkDatRead)  ;
err_t RFIDLIB_API ISO15693_WriteSingleBlock(
									RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht, /* Tag handle connected */
								   DWORD blkAddr,/* Block number  */
								BYTE newBlkData[] ,
								DWORD bytesToWrite)  ;
err_t RFIDLIB_API ISO15693_ReadMultiBlocks( RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht, /* Tag handle connected */
									BOOLEAN readSecSta ,
									 DWORD blkAddr,/* Block number  */
							DWORD numOfBlksToRead, /* in:Number of blocks to read  */
							DWORD *numOfBlksRead,/* ,out: blocks read */
							BYTE bufBlocks[],/*  buffer for storing block data ,4 * num_of_blks */
							DWORD nSize, /* in:size of the buffer */
							DWORD *bytesBlkDatRead)  ;
err_t RFIDLIB_API ISO15693_WriteMultipleBlocks(RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht, /* Tag handle connected */
									 DWORD blkAddr,
							DWORD numOfBlks, 
							BYTE newBlksData[],
							DWORD bytesToWrite) ;

err_t RFIDLIB_API ISO15693_WriteAFI(RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht, /* Tag handle connected */
								BYTE afi) ;

err_t RFIDLIB_API ISO15693_LockAFI(RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht /* Tag handle connected */) ;
err_t RFIDLIB_API ISO15693_WriteDSFID(RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht, 
									BYTE dsfid)  ;
err_t RFIDLIB_API ISO15693_LockDSFID(RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht)  ;
err_t RFIDLIB_API ISO15693_GetSystemInfo(RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht,
									BYTE uid[],	/* out: tag uid */
											BYTE *dsfid, /* out:DSFID */
											BYTE *afi,  /* out:AFI */
											DWORD *blkSize ,/* out: block size */
											DWORD *numOfBloks, /* out:number of total blocks */
											BYTE *icRef /* out:ic reference */) ;

err_t RFIDLIB_API ISO15693_GetBlockSecStatus(RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht,
										DWORD blkAddr, 
										DWORD numOfBlks,
										BYTE bufBlkSecs[],
										DWORD nSize/* in: size of the buffer */,
										DWORD *bytesSecRead /*out:number of block status byte copied*/ ) ;

err_t RFIDLIB_API ISO15693_LockMultipleBlocks(RFID_READER_HANDLE hr ,
									RFID_TAG_HANDLE ht, /* Tag handle connected */
									 DWORD blkAddr,
							DWORD numOfBlks) ;


err_t RFIDLIB_API NXPICODESLI_EableEAS(RFID_READER_HANDLE hr ,
									   RFID_TAG_HANDLE ht)  ;
err_t RFIDLIB_API NXPICODESLI_DisableEAS(RFID_READER_HANDLE hr ,
										 RFID_TAG_HANDLE ht) ;
err_t RFIDLIB_API NXPICODESLI_LockEAS(RFID_READER_HANDLE hr ,
									  RFID_TAG_HANDLE ht) ;
err_t RFIDLIB_API NXPICODESLI_EASAlarm(RFID_READER_HANDLE hr ,
									   RFID_TAG_HANDLE ht,
									   BYTE EAS_data[],
									   DWORD nSize /* EAS data buffer,32 bytes */,
									   DWORD *bytesWritten);
err_t RFIDLIB_API NXPICODESLI_EASCheck(RFID_READER_HANDLE hr ,
									   RFID_TAG_HANDLE ht,
									   BYTE *EASFlag) ;

err_t RFIDLIB_API NXPICODESLI_GetRandomNum( RFID_READER_HANDLE hr ,
											RFID_TAG_HANDLE ht,
											WORD *random/* 16bits */) ;
err_t RFIDLIB_API NXPICODESLI_SetPassword( RFID_READER_HANDLE hr ,
										   RFID_TAG_HANDLE ht,
										   BYTE pwdNo,/* password adress,Only one password is supported now,the address is 10H */
										   WORD random,
										   DWORD pwd/* 32bits */)  ;

err_t RFIDLIB_API NXPICODESLI_WritePassword(RFID_READER_HANDLE hr ,
											 RFID_TAG_HANDLE ht,
											 BYTE pwdNo,
											 DWORD pwd/* 32bits */)  ;
err_t RFIDLIB_API NXPICODESLI_LockPassword(RFID_READER_HANDLE hr ,
											RFID_TAG_HANDLE ht,
											BYTE pwdNo) ;
err_t	RFIDLIB_API	NXPICODESLI_PasswordProtect(RFID_READER_HANDLE hr ,
												 RFID_TAG_HANDLE ht,
												 BYTE bandType/* EAS=0 or AFI=1 */) ;

err_t RFIDLIB_API NXPICODESLI_EASCheck(RFID_READER_HANDLE hr ,
										RFID_TAG_HANDLE ht,
										BYTE *EASFlag) ;
err_t RFIDLIB_API NXPICODESLI_GetRandomAndSetPassword( RFID_READER_HANDLE hr ,
													   RFID_TAG_HANDLE ht,
													   BYTE pwdNo,/* password adress,Only one password is supported now,the address is 10H */
													   DWORD pwd/* 32bits */)   ;

err_t RFIDLIB_API NXPICODESLI_WriteEASID(RFID_READER_HANDLE hr ,
										 RFID_TAG_HANDLE ht,
										 WORD EASID ) ;

err_t RFIDLIB_API NXPICODESLI_GetNxpSysInfo(RFID_READER_HANDLE hr ,
											RFID_TAG_HANDLE ht,
											BYTE *PPPointer ,
											BYTE *PPConditions ,
											BYTE *lockBits,
											DWORD *featureFlags
											) ;
err_t RFIDLIB_API NXPICODESLI_ReadSignature(RFID_READER_HANDLE hr ,
											RFID_TAG_HANDLE ht,
											BYTE signature[] /* out ,32 bytes */) ;

err_t RFIDLIB_API NXPICODESLI_Enable64BitPwd(RFID_READER_HANDLE hr ,
											 RFID_TAG_HANDLE ht) ;
err_t RFIDLIB_API NXPICODESLI_ProtectPage(RFID_READER_HANDLE hr ,
										  RFID_TAG_HANDLE ht,
										  BYTE PPPointer,
										  BYTE protSta) ;
err_t RFIDLIB_API NXPICODESLI_LockPageProtection(RFID_READER_HANDLE hr ,
												 RFID_TAG_HANDLE ht,
												 BYTE pageAddr) ;
err_t RFIDLIB_API NXPICODESLI_Destroy(RFID_READER_HANDLE hr ,
									  RFID_TAG_HANDLE ht,
									  DWORD pwd) ;
err_t RFIDLIB_API NXPICODESLI_EnblePrivacy(RFID_READER_HANDLE hr ,
										   RFID_TAG_HANDLE ht,
										   DWORD pwd) ;
err_t RFIDLIB_API NXPICODESLI_PresetCounter(RFID_READER_HANDLE hr ,
											RFID_TAG_HANDLE ht,
											WORD initCnt,
											BOOLEAN enReadPwdProtect) ;
err_t RFIDLIB_API NXPICODESLI_IncrementCounter(RFID_READER_HANDLE hr ,
											   RFID_TAG_HANDLE ht) ;




err_t RFIDLIB_API TIHFIPLUS_Write2Blocks(RFID_READER_HANDLE hr ,
										 RFID_TAG_HANDLE ht,
										 DWORD blkAddr,
										 BYTE newTwoBlksData[] /* 2 * 4 */,
										 DWORD bytesToWrite
										 ) ;

err_t RFIDLIB_API TIHFIPLUS_Lock2Blocks(RFID_READER_HANDLE hr ,
										RFID_TAG_HANDLE ht,
										DWORD blkAddr) ;



err_t RFIDLIB_API CIT83128_InitMem(RFID_READER_HANDLE hr , /*in */
								   RFID_TAG_HANDLE ht, /*in */
								   BOOLEAN loseEffect,
								   BYTE blkAddr, /*in */
								   BYTE blkData[] /*in,4bytes */ ) ;

err_t RFIDLIB_API CIT83128_ActAu(RFID_READER_HANDLE hr , /*in */
								 RFID_TAG_HANDLE ht, /*in */
								 DWORD rr /* in */,
								 BYTE token[] /* out */) ;
err_t RFIDLIB_API CIT83128_GetSecPara(RFID_READER_HANDLE hr , /*in */
									  RFID_TAG_HANDLE ht, /*in */
									  BOOLEAN readSecByte, /*in */
									  BYTE secData[]  /*out */ ) ;


err_t RFIDLIB_API STM24LR_WriteSectorPassword(RFID_READER_HANDLE hr,
									RFID_TAG_HANDLE ht,
									BYTE pwdnum,
									DWORD new_pwd);

err_t RFIDLIB_API STM24LR_PresentSectorPassword(RFID_READER_HANDLE hr,
									RFID_TAG_HANDLE ht,
									BYTE pwdnum,
									DWORD pwd);

err_t RFIDLIB_API  STM24LR_LockSector(RFID_READER_HANDLE hr,
									RFID_TAG_HANDLE ht,
									BYTE sector_num,
									BYTE access_type,
									BYTE pwd_num_protect);

err_t RFIDLIB_API  STM24LR_ReadCFG(RFID_READER_HANDLE hr,
									RFID_TAG_HANDLE ht,
									BYTE *cfgby);

err_t RFIDLIB_API  STM24LR_WriteEHCfg(RFID_READER_HANDLE hr,
									RFID_TAG_HANDLE ht,
									BYTE EnergyHarvesting,
									BYTE EHMode);

err_t RFIDLIB_API  STM24LR_WriteDOCfg(RFID_READER_HANDLE hr,
									RFID_TAG_HANDLE ht,
									BYTE cfg_do /* 0: RF busy mode(RF WIP/BUSY pin for RF busy) , 1: RF Write in progress( RF WIP/BUSY pin for) */
									);

err_t RFIDLIB_API  STM24LR_SetRstEHEn(RFID_READER_HANDLE hr,
									RFID_TAG_HANDLE ht,
									BYTE enable
										);

err_t RFIDLIB_API  STM24LR_CheckEHEn(RFID_READER_HANDLE hr,
									RFID_TAG_HANDLE ht,
									BYTE *ctrlreg);


err_t RFIDLIB_API STLRI2k_Kill(RFID_READER_HANDLE hr, /*in */
								RFID_TAG_HANDLE ht, /*in */
									BYTE access, /*value is 0x00 */
									DWORD code);

err_t RFIDLIB_API STLRI2k_WriteKill(RFID_READER_HANDLE hr, /*in */
									RFID_TAG_HANDLE ht, /*in */
									BYTE access, /*value is 0x00 */
									DWORD code);

err_t RFIDLIB_API STLRI2k_LockKill(RFID_READER_HANDLE hr, /*in */
									RFID_TAG_HANDLE ht, /*in */
									BYTE access, /*value is 0x00 */
									BYTE protectSta);


err_t RFIDLIB_API TIHFI_Kill(RFID_READER_HANDLE hr, /*in */ RFID_TAG_HANDLE ht, /*in */ DWORD password);



err_t RFIDLIB_API TIHFI_WriteSingleBlockPwd(RFID_READER_HANDLE hr, /*in */
											RFID_TAG_HANDLE ht, /*in */
											DWORD password,
											BYTE blkAddr,
											BYTE blkData[]  /* 4 bytes block data*/);




err_t RFIDLIB_API ST25DVxx_ReadConfiguration(RFID_READER_HANDLE hr, /*in */
											RFID_TAG_HANDLE ht, /*in */
											BYTE Pointer,
											BYTE *RegisterValue);

err_t RFIDLIB_API ST25DVxx_WriteConfiguration(RFID_READER_HANDLE hr, /*in */
											RFID_TAG_HANDLE ht, /*in */
											BYTE Pointer,
											BYTE RegisterValue);

err_t RFIDLIB_API ST25DVxx_ReadDynamicConfiguration(RFID_READER_HANDLE hr, /*in */
													RFID_TAG_HANDLE ht, /*in */
													BYTE Pointer,
													BYTE *RegisterValue);

err_t RFIDLIB_API ST25DVxx_WriteDynamicConfiguration(RFID_READER_HANDLE hr, /*in */
													RFID_TAG_HANDLE ht, /*in */
													BYTE Pointer,
													BYTE RegisterValue);

err_t RFIDLIB_API ST25DVxx_ManageGPO(RFID_READER_HANDLE hr, /*in */
									RFID_TAG_HANDLE ht, /*in */
									BYTE gpo);

err_t RFIDLIB_API ST25DVxx_WriteMessage(RFID_READER_HANDLE hr, /*in */
										RFID_TAG_HANDLE ht, /*in */
										BYTE* msgData,
										BYTE msgLen);


err_t RFIDLIB_API ST25DVxx_ReadMessageLength(RFID_READER_HANDLE hr, /*in */
											RFID_TAG_HANDLE ht, /*in */
											BYTE* msgLength);
err_t RFIDLIB_API ST25DVxx_ReadMessage(RFID_READER_HANDLE hr, /*in */
										RFID_TAG_HANDLE ht, /*in */
										BYTE Pointer,/*in*/
										BYTE ReadCount,/*in*/
										BYTE *msgBuf,/*out*/
										DWORD *nSize /*in/out*/);

err_t RFIDLIB_API ST25DVxx_WritePassword(RFID_READER_HANDLE hr, /*in */
										RFID_TAG_HANDLE ht, /*in */
										BYTE passwordNum,
										BYTE password[]/*8 bytes*/);

err_t RFIDLIB_API ST25DVxx_PresentPassword(RFID_READER_HANDLE hr, /*in */
										RFID_TAG_HANDLE ht, /*in */
										BYTE passwordNum,
										BYTE password[]/*8 bytes*/);


#ifdef __cplusplus
}
#endif

#endif