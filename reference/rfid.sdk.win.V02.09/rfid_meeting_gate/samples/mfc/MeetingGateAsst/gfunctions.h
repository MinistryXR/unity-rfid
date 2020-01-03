#ifndef MY_GFUNCTIONS_H 
#define MY_GFUNCTIONS_H

#include "windows.h"
#include "tchar.h"
#include "stdio.h"
#ifdef _WTL_USE_CSTRING
#include "atlbase.h"
#include "atlapp.h"
#include "atlmisc.h"
#endif

#define	MAX_STRING_SIZE_GUID							38

bool HexStrToBytes(const TCHAR *strBuf,BYTE *byBuf,int *byLen) ;
int  CharToInt(TCHAR val)  ;
void CharToUpper(TCHAR *strBuffer);
bool BytesCmp(BYTE *Buf1,BYTE *Buf2,int len)  ;
bool ReserveBytes(BYTE *bBuf,int bLen)  ;
bool IsBytesInSameValue(BYTE *bBuf,int bLen,BYTE cmpVal)  ;
void dwToIpv4Str(DWORD ipaddr,TCHAR *ipStr)  ;
void BytesToHexStr(BYTE *bBuffer,int bLen,TCHAR *strBuf)  ;
bool WriteMsgToFile(TCHAR *fileName, TCHAR *recBuf, DWORD dwDataLen, bool pWriteSource) ;
void ReserveWord(WORD *dwVal) ;
int  StrSearch( const TCHAR *strSource,const TCHAR *subStr,int count) ;
bool SubString(const TCHAR *Source,int iStart,int len,TCHAR *Sub) ;
int	 ReserveString(TCHAR *str) ;
bool isDigitalStr(const TCHAR *str) ;
bool IsHexStr(const TCHAR *str) ;
bool IsCharacterStr(const TCHAR *chStr) ;
int StrToGUID(const TCHAR *cStr,GUID *guid)  ;
void GuidToStr(GUID *guid,TCHAR *szStr)  ;
void ExtractFilePath(TCHAR *fileName,TCHAR *filePath,int bufSize)  ;
int Cal_DWORD_CharCount(DWORD dwValue) ;
TCHAR * BytesToHexSpaceStr(BYTE *bBuffer,int bLen)  ;
int BytesSearch(BYTE *source,int slen,BYTE *sub,int sublen,int count) ;
int	 ReserveString(TCHAR *str)  ;
int	 ReserveHexString(TCHAR *str)  ;
int ___ttoi(const TCHAR * _str) ;
TCHAR *GetModuleFileName_ext() ;
TCHAR *GetPrivateProfileString_ext(TCHAR *lpAppName,TCHAR * lpKeyName,TCHAR * lpDefault,TCHAR *lpFileName)	 ;
TCHAR *GetPrivateProfileString_ext2(TCHAR *lpAppName,TCHAR * lpKeyName,TCHAR * lpDefault,TCHAR *lpFileName)		;
char * UnicodeToANSI( const wchar_t* str ) ;
wchar_t * ANSIToUnicode( const char* str );

#ifdef _WTL_USE_CSTRING
CSTR ByteToHex(BYTE by);
BYTE HexToByte(CSTR hex) ;
#endif

void BytesReverse(UINT8 *buf,UINT32 len )  ;
#endif
