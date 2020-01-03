

#include "gFunctions.h"

VOID BytesReverse(UINT8 *buf,UINT32 len ) 
{
	INT32 i;
	UINT8 tmp ;
	for(i = 0;i< len/ 2 ;i++ ) {
		tmp = buf[i] ;
		buf[i] = buf[len-1 -i] ;
		buf[len-1 -i] = tmp ;
	}
}

int ___ttoi(const TCHAR * _str)
{
	int result=0 ;
	int digital=0 ;
	while(*_str)
	{
		if(*_str >=0x30 && *_str <=0x39)
		{
			result=result * 10 + (*_str - 0x30) ;
		}
		_str++ ;
	}

	return result;
}

/*
GUID转成GUID字符串
*/
void GuidToStr(GUID *guid,TCHAR *szStr) 
{
	_stprintf(szStr,
		      _T("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"),
			  guid->Data1,guid->Data2,guid->Data3,guid->Data4[0],
			  guid->Data4[1],guid->Data4[2] ,
			  guid->Data4[3],guid->Data4[4],
			  guid->Data4[5],guid->Data4[6],guid->Data4[7]);
}
/*
字符串的GUID转成GUID变量
*/
int StrToGUID(const TCHAR *cStr,GUID *guid) 
{
	TCHAR firstPart[9],secondPart[5],thirdPart[5],fourthPart[30],fifthPart[13] ;
    int iIndex=0 ;
	int iLen=_tcslen(cStr) ;
	if(iLen!=MAX_STRING_SIZE_GUID) return 0;
	//判断开头和结束
	if(cStr[0]!='{' || cStr[iLen-1]!='}')
	{
		return 0 ;
	}
	//取出第一部分
	memset(firstPart,0,sizeof(firstPart));
	if(SubString(cStr,2,8,firstPart)==false)
	{
		return 0;
	}
	HexStrToBytes(firstPart,(BYTE *)&guid->Data1,NULL) ;
	ReserveBytes((BYTE *)&guid->Data1,4) ;

	//取第二部分
	iIndex=StrSearch(cStr,_T("-"),1) ;
	if(iIndex==-1)
	{
		return 0 ;
	}
	memset(secondPart,0,sizeof(secondPart));
	if(SubString(cStr,iIndex+2,4,secondPart)==false)
	{
		return 0;
	}
	HexStrToBytes(secondPart,(BYTE *)&guid->Data2,NULL) ;
	ReserveBytes((BYTE *)&guid->Data2,2) ;

	//取第三部分
	iIndex=StrSearch(cStr,_T("-"),2) ;
	if(iIndex==-1)
	{
		return 0 ;
	}
	memset(thirdPart,0,sizeof(thirdPart));
	if(SubString(cStr,iIndex+2,4,thirdPart)==false)
	{
		return 0;
	}
	HexStrToBytes(thirdPart,(BYTE *)&guid->Data3,NULL) ;
	ReserveBytes((BYTE *)&guid->Data3,2) ;

	//取第四部分
	iIndex=StrSearch(cStr,_T("-"),3) ;
	if(iIndex==-1)
	{
		return 0 ;
	}
	memset(fourthPart,0,sizeof(fourthPart));
	if(SubString(cStr,iIndex+2,4,fourthPart)==false)
	{
		return 0;
	}

	//取第五部分
	iIndex=StrSearch(cStr,_T("-"),4) ;
	if(iIndex==-1)
	{
		return 0 ;
	}

	memset(fifthPart,0,sizeof(fifthPart));
	if(SubString(cStr,iIndex+2,12,fifthPart)==false)
	{
		return 0;
	}
	_tcscat(fourthPart,fifthPart) ;
	HexStrToBytes(fourthPart,(BYTE *)&guid->Data4,NULL) ;
	//ReserveBytes((BYTE *)guid->Data4,8) ;

	return 1;
}


#ifdef _WTL_USE_CSTRING
BYTE HexToByte(CSTR hex)
{
	if(hex.GetLength()  != 2 )
		return 0;
	if(!IsHexStr(hex)) {
		return 0;
	}
	BYTE result = 0 ;
	if(hex[0] >='0' && hex[0] <='9') 
		result =(hex[0] - '0') << 4 & 0xf0 ;
	else if(hex[0] >= 'A' && hex[0] <='F') 
		result = (hex[0] - 'A' +0x0A) << 4 & 0xf0 ;
	else if(hex[0] >='a' && hex[0] <='f' ) 
		result = (hex[0] -'a'+0x0a) << 4 & 0xf0 ;
	if(hex[1] >='0' && hex[1] <='9') 
		result |=((hex[1] - '0')  & 0x0f );
	else if(hex[1] >= 'A' && hex[1] <='F') 
		result |=( (hex[1] - 'A' +0x0A)  & 0x0f );
	else if(hex[1] >='a' && hex[1] <='f' ) 
		result |= ((hex[1] -'a'+0x0a) & 0x0f );

	return result;
}

CSTR ByteToHex(BYTE by)
{
	CSTR s2;
	TCHAR c ;
	BYTE t = ((by >> 4 ) & 0x0f) ;
	if(t > 9 )
	{
		c = t - 0x0a + 0x41 ;
		s2.Insert(0,c) ;
	}
	else
	{
		c = t  + 0x30  ;
		s2.Insert(0,c) ;
	}

	t = (by & 0x0f) ;
	if(t > 9 )
	{
		c = t - 0x0a + 0x41 ;
		s2.Insert(1,c) ;
	}
	else
	{
		c = t  + 0x30  ;
		s2.Insert(1,c) ;
	}
 
	return s2;
}
#endif
//
//  函数BytesToHexStr说明
//  转字节数组{0x12,0x22,0x0e} 成字符串 "12220E"
//
void BytesToHexStr(BYTE *bBuffer,int bLen,TCHAR *strBuf) 
{ 
     BYTE l4b,r4b;
	 TCHAR l4c,r4c;
	 int i;
	 for(i=0;i<bLen;i++)
	 {
          r4b=bBuffer[i] & 0x0f ;
          if(r4b>=0 && r4b<=9)  
			  r4c=0x30+r4b ;
		  else
			  r4c=0x41+(r4b-0x0a) ;

		  l4b=(bBuffer[i] & 0xf0) >> 4 ;
          if(l4b>=0 && l4b<=9)  
			  l4c=0x30+l4b ;
		  else
			  l4c=0x41+(l4b-0x0a) ;


		  strBuf[i*2]=l4c ;
		  strBuf[i*2+1]=r4c;

	 }

}
//
//
//
//
TCHAR * BytesToHexSpaceStr(BYTE *bBuffer,int bLen)
{
     BYTE l4b,r4b;
	 TCHAR l4c,r4c;
	 int i;
	 TCHAR *	szBuf=NULL ;
	 int		iszLen=(bLen * 3)-1 +1 ;	//-1最后一个字节没有空格	

	 szBuf=new TCHAR[iszLen] ;

	 if(szBuf==NULL) return NULL;

	 memset(szBuf,0,iszLen);
	 for(i=0;i<bLen;i++)
	 {
          r4b=bBuffer[i] & 0x0f ;
          if(r4b>=0 && r4b<=9)  
			  r4c=0x30+r4b ;
		  else
			  r4c=0x41+(r4b-0x0a) ;

		  l4b=(bBuffer[i] & 0xf0) >> 4 ;
          if(l4b>=0 && l4b<=9)  
			  l4c=0x30+l4b ;
		  else
			  l4c=0x41+(l4b-0x0a) ;


		  szBuf[i*3]=l4c ;
		  szBuf[i*3+1]=r4c;
		  if(i<bLen-1) szBuf[i*3+2]=0x20;	
		  

	 }


	 return szBuf;
}


//
//  函数HexStrToBytes说明
//  转字符串"12220E" 字节数组{0x12,0x22,0x0e}
//
bool HexStrToBytes(const TCHAR *strBuf,BYTE *byBuf,int *byLen)
{
     int                      slen=0 ;
	 int                      byteCount;
	 int                      index=0 ;
	 BYTE                     btmp ;
	 int                      val;
	 int                      itmp =0;

	 slen=_tcslen(strBuf) ;	 
	 if(slen<2)              return false;
	 //不是2的倍数
	 if((slen % 2)!=0)       return false;

	 byteCount=slen / 2 ;
	 itmp=byteCount ;
	 //全部转大写
	 //CharToUpper(strBuf) ;
	 while(byteCount)
	 {
          btmp=0 ;
          val=CharToInt(strBuf[index]) ;
		  if(val==-1)  return false;
          btmp=(val << 4) & 0xf0;
          
          val=CharToInt(strBuf[index+1]) ;
		  if(val==-1)  return false;

		  btmp=btmp | (val & 0x0f) ;

		  byBuf[itmp-byteCount] =btmp;
          
		  index=index+2;

		  byteCount-- ;
	 }
     
	 if(byLen!=NULL) *byLen=itmp ;
	 
     return true;
}



//
//  函数CharToInt说明
//  转字符成数值
//
int CharToInt(TCHAR val)
{
     int ret=-1;
	 if(val>='0' && val <='9') 
	 {
         ret=val-0x30 ;
	 }
	 if(val>='A'  && val<='F')
	 {
         ret=val-'A'+ 0x0a;
	 }
	 if(val>='a' && val<='f')
	 {
         ret=val-'a'+0x0a ;
	 }

	 return ret;

}

//
//  函数CharToUpper说明
//  小写字母转大写字母 'a'->'A'
//
void CharToUpper(TCHAR *strBuffer)  //Warning :the buffer is not the const string .
{
  int sLen ;

  sLen=_tcslen(strBuffer) ;
  int i;
  for(i=0 ;i<sLen ;i++)
  {
       if(strBuffer[i] >='a' && strBuffer[i]<='z') strBuffer[i]=strBuffer[i]-'a' +'A' ;
   
  }
}
//
//  函数BytesCmp说明
//  两个字节数组进行比较
//
bool BytesCmp(BYTE *Buf1,BYTE *Buf2,int len) 
{
  int i;
  bool ret=true;
  for(i=0;i<len;i++)
  {
       if(Buf1[i] != Buf2[i]) 
	   {
           ret=false;
		   break;

	   }
   

  }


  return ret;


}
//
//  函数ReserveBytes说明
//  倒排序{0x12,0x22,0x0e}->{0x0e,0x22,0x12}
//
bool ReserveBytes(BYTE *bBuf,int bLen)
{
  int i;
  int half ;
  BYTE tmpStart,tmpEnd;
  half=bLen / 2 ;
  for(i=0;i<half ;i++)
  {
     tmpStart=bBuf[i] ;
     tmpEnd=bBuf[bLen-1-i] ;
	 bBuf[i]= tmpEnd;
     bBuf[bLen-1-i]=tmpStart ;

  }

  return true;

}
//
//  函数IsZeroBytes说明
//  判断字节数组的里面的所有数组的字节是否为0x00
//  参数cmpVal：是比较的值
bool IsBytesInSameValue(BYTE *bBuf,int bLen,BYTE cmpVal)
{

   int i;
   for(i=0;i<bLen;i++) if(bBuf[i]!= cmpVal) return false;

   return true;
}

//
//  函数dwToIpv4Str说明
//  转ip地址成字符串
//
void dwToIpv4Str(DWORD ipaddr,TCHAR *ipStr) 
{
    BYTE *tmp ;
	tmp=(BYTE *)&ipaddr  ;
	_stprintf(ipStr,_T("%d.%d.%d.%d"),*tmp,*(tmp+1),*(tmp+2),*(tmp+3) ) ;

}
//
//  函数ReserveWord说明
//  倒换Word
//
void ReserveWord(WORD *dwVal) 
{
 
	*dwVal=((*dwVal >> 8 ) & 0x00ff ) | ((*dwVal << 8 ) & 0xff00 );

}
//
//  函数WriteMsgToFile说明
//  写消息到文件
//
bool WriteMsgToFile(TCHAR *fileName, TCHAR *recBuf, DWORD dwDataLen, bool pWriteSource)
{
  TCHAR strBuf[3005]={0} ;
  TCHAR timeStr[50]={0} ;
  int writeLen=dwDataLen;
  DWORD fileWritten;
  SYSTEMTIME sysTime ;
  if(! pWriteSource)  
  {
     
	 TCHAR toBuf[10] ;	 
	 int i;
	 int tmpLen ;
	 if(dwDataLen>500)  tmpLen=500; else tmpLen= dwDataLen;
	 memset(strBuf,0x0,sizeof(strBuf)) ;
	 for(i=0 ;i<tmpLen ;i++)
	 {
		_itot(recBuf[i],toBuf,16) ;
        _tcscat(strBuf,toBuf);
		_tcscat(strBuf,_T(" "));
	 }
     writeLen=_tcslen(strBuf) ;
  }
  else
  {
	  if(dwDataLen>1000)  writeLen=1000 ;
	  CopyMemory(strBuf,recBuf,writeLen);
  }
  /*
  GetSystemTime( &sysTime) ;
  SysTimeTostr(sysTime,timeStr) ;  
  strcat(strBuf,"    ") ;
  strcat(strBuf,timeStr) ;*/

  HANDLE hFile;
  hFile=CreateFile(fileName,GENERIC_WRITE | GENERIC_READ,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL ,0) ;
  if(hFile==INVALID_HANDLE_VALUE) return false;
  try
  {
      if(hFile!=INVALID_HANDLE_VALUE)
	  {
        SetFilePointer( hFile,GetFileSize(hFile,NULL),NULL,FILE_BEGIN) ;
        strBuf[writeLen]=0x0d ;
	    strBuf[writeLen+1]=0x0a;
	    writeLen=writeLen+2;
        WriteFile(hFile,strBuf,writeLen,&fileWritten,NULL);

	    CloseHandle(hFile) ;
	  }
  }
  catch(...)
  {
    return false;
  }
  return true;
}

//
//
//
int BytesSearch(BYTE *source,int slen,BYTE *sub,int sublen,int count)
{
  int i=0 ;

  while(i<slen) 
  {

	  if(memcmp(source+i,sub,sublen)==0)
	  {
          if(count==1)
		  {
              return  i;
		  }
		  else
		  {
              count-- ;
			  i=i+sublen ;
			  continue;
		  }
	  }

	  i++ ;

    
  }

  return -1;
}

//
//  函数StrSearch说明
//  字符串查找
//  函数返回是字符在字符串的index
//
int StrSearch( const TCHAR *strSource,const TCHAR *subStr,int count)
{
  
  if(count<=0) return -1;
  if((strSource==NULL) || (subStr==NULL)) return -1 ;
  int subLen=_tcslen(subStr) ;
  int scrLen=_tcslen(strSource) ;
  int i;
  i=0 ;

  while(i<scrLen) 
  {

	  if(memcmp(strSource+i,subStr,subLen * sizeof(TCHAR))==0)
	  {
          if(count==1)
		  {
              return  i;
		  }
		  else
		  {
              count-- ;
			  i=i+subLen ;
			  continue;
		  }
	  }

	  i++ ;

    
  }

  return -1;
}
//
//  函数SubString说明
//  取子字符串
//  iStart 从1开始
bool SubString(const TCHAR *Source,int iStart,int len,TCHAR *Sub)
{
     if(Source==NULL)                      return false;
	 int sLen =_tcslen(Source);
	 if(sLen==0)                          return false;
	 if(iStart>sLen)                      return false;
	 if(len<=0) len=sLen-iStart+1 ;
     if(sLen<(iStart+len-1)) len=sLen-iStart+1 ;

	 memcpy(Sub,Source+(iStart-1),len * sizeof(TCHAR)) ;
      
     return true;
}

bool isDigitalStr(const TCHAR *str)
{
   	
  int slen=0 ;
  int i;
  bool wr ;
  slen=_tcslen(str) ;
  for(i=0;i<slen;i++)
  {
    if(str[i]<0x30 || str[i]>0x39)
    {
      break;	
    }	
  	
  }	
  if(i==slen) return true;
  else return false;
  
	
}
bool IsHexStr(const TCHAR *str)
{
    int slen=_tcslen(str) ;
    while(slen)
    {
      if((str[slen-1]>=0x30 && str[slen-1]<=0x39) || (str[slen-1]>='A' && str[slen-1]<='F') )
        slen-- ;
      else
        return false;
    }

    return true;

}

//判断字符串里，是否都是汉字
bool IsCharacterStr(const TCHAR *chStr)
{
      int slen=_tcslen(chStr) ;
      int i;
      for(i=0;i<slen;i++)
      {
          if(chStr[i] >=  0x80) return false;
      }


      return true;


}

void ExtractFilePath(TCHAR *fileName,TCHAR *filePath,int bufSize) 
{
	int		i=0 ;
	int		pos=-1 ;

	if((fileName == NULL ) || (filePath == NULL ) || (bufSize == 0)  ) return ;
	while( *(fileName+i)) 
	{
		if(*(fileName+i) == '\\') pos =  i ;

		i++ ;
	}

	if(pos >  (bufSize -1)) pos=bufSize -1 ;

	_tcsncpy(filePath,fileName,pos) ;


}

int Cal_DWORD_CharCount(DWORD dwValue) 
{
	int		count=0 ;
	DWORD	dwVal=dwValue ;

	if(dwVal==0) return 1;
	
	while(dwVal>0)
	{
		count++;
		dwVal=dwVal / 10;
	}

	return count;
}

int	 ReserveString(TCHAR *str) 
{
	if(str == NULL ) return  0;
	int ilen=_tcslen(str) ;
	if(ilen <=0 ) return  0;
	TCHAR tmp ;
	for(int i=0;i<(ilen / 2) ;i++)
	{
		tmp=str[i] ;
		str[i]=str[ilen-1-i] ;
		str[ilen-1-i] =tmp ;
	}

	return 1;
}

int ReserveHexString(TCHAR *str) 
{
	if(str == NULL ) return  0;
	int ilen=_tcslen(str) ;
	if((ilen <=0) ||  (ilen % 2 >0)) return  0;
	TCHAR tmp[3] ;
	for(int i=0;i<(ilen / 4) ;i++)
	{
		memset(tmp,0,sizeof(tmp));
		_tcsncpy(tmp,&str[i*2],2) ;
		_tcsncpy(&str[i*2],&str[(ilen-1-1) - i*2],2) ;	
		_tcsncpy(&str[(ilen-1-1) - i*2],tmp,2) ;		
	}

	return 1;
}

//the function return the buffer include the full path string . free the return buffer if no longer use.
TCHAR *GetModuleFileName_ext()
{
	int	nCount= 256;
	TCHAR *szbuf=(TCHAR *)realloc(NULL,nCount * sizeof(TCHAR)) ;
	
	int nLen ;

	if(szbuf )
	{
		memset(szbuf,0,nCount * sizeof(TCHAR));
		nLen=GetModuleFileName(NULL,szbuf,nCount) ;
		if (nLen < nCount)
		{
			return szbuf;
		}
		TCHAR *sztmp=NULL ;
		do
		{
			nCount +=256 ;
			sztmp=(TCHAR *)realloc(szbuf,nCount * sizeof(TCHAR));
			if(sztmp==NULL)
			{
				free(szbuf) ;
				return NULL ;
			}
			szbuf=sztmp ;
			memset(szbuf,0,nCount * sizeof(TCHAR));
			nLen=GetModuleFileName(NULL,szbuf,nCount) ;

			
		}while(nLen >= nCount);
		
		
	}

	return szbuf;
}


wchar_t * ANSIToUnicode( const char* str )
{
     int textlen ;
     wchar_t * result;
     textlen = MultiByteToWideChar( CP_ACP, 0, str,-1, NULL,0 );
     result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t));
     memset(result,0,(textlen+1)*sizeof(wchar_t));
     MultiByteToWideChar(CP_ACP, 0,str,-1,(LPWSTR)result,textlen );
     return result;
}

char * UnicodeToANSI( const wchar_t* str )
{
     char* result;
     int textlen;
     textlen = WideCharToMultiByte( CP_ACP, 0, str, -1, NULL, 0, NULL, NULL );
     result =(char *)malloc((textlen+1)*sizeof(char));
     memset( result, 0, sizeof(char) * ( textlen + 1 ) );
     WideCharToMultiByte( CP_ACP, 0, str, -1, result, textlen, NULL, NULL );
     return result;
}



#if !defined(WINCE)
TCHAR *GetPrivateProfileString_ext(TCHAR *lpAppName,TCHAR * lpKeyName,TCHAR * lpDefault,TCHAR *lpFileName)			
{
	int	nCount= 128;
	TCHAR *szbuf=NULL ;
	TCHAR *ptmp=NULL ;
	int iret;
	
	while(1)
	{
		ptmp= (TCHAR *)realloc(szbuf,nCount * sizeof(TCHAR)) ;
		if(ptmp == NULL)
		{
			if(szbuf != NULL)free(szbuf) ;
			szbuf=NULL ;
			break;
		}
		szbuf=ptmp ;
		memset(szbuf,0,nCount * sizeof(TCHAR )) ;

		iret=GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,szbuf,nCount,lpFileName);
		if(iret< (nCount-1)) break;

		nCount+=128 ;
	}

	return szbuf;
}

TCHAR *GetPrivateProfileString_ext2(TCHAR *lpAppName,TCHAR * lpKeyName,TCHAR * lpDefault,TCHAR *lpFileName)			
{
	int	nCount= 128;
	TCHAR *szbuf=NULL ;
	int iret;
	
	while(1)
	{
		if(szbuf ) delete[] szbuf ;
		szbuf=new TCHAR[nCount] ;
		memset(szbuf,0,nCount * sizeof(TCHAR )) ;
		iret=GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,szbuf,nCount,lpFileName);
		if(iret< (nCount-1)) break;

		nCount+=128 ;
	}

	return szbuf;
}




char* ConvertMoney(char* dest,char* src )  
{  
static const char *numberchar[] = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};  
static const char *unitchar[] =  
{  
"整", "分", "角", "圆", // 0 - 3  
"拾", "佰", "仟", "万", // 4 - 7  
"拾", "佰", "仟", "亿", // 8 - 11  
"拾", "佰", "仟", "兆", // 12 - 15  
"拾", "佰", "仟", "京" // 16 - 19  
};  
dest[0] = '\0';  
//编译的二进制码  
char code[128];  
int clen = 0;  
int cunit= 2; //初始化为角  
int ndot = 0;  
int ndec = 0;  
//第一遍编译  
for(;*src != '\0' ;++src)  
{  
if( *src >= '0' && *src<= '9') { code[clen++] = *src- '0'; if(!ndot) ++cunit; else if(ndot) ++ndec; } else if(*src == '.') { code[clen++] = -1; ++ndot; } else { return dest; } } if(ndot >1 || ndec > 2 || cunit >19 || clen == 0)  
{  
return dest;  
}  
  
//第二遍编译  
int nzero = 0;  
int nvalid = 0;  
char *p= dest;  
for(int n = 0;n< clen;++n)  
{  
if(code[n] == 0)  
{  
//对于基点单位要输出  
if(nvalid && (nzero <3 && cunit %4 == 3) ) { strncpy(p,unitchar[cunit],2); p+=2; } ++nzero; --cunit; } else if(code[n] != -1) { //在输入有效数据时，输出0 if(nvalid && nzero > 0)  
{  
strncpy(p,numberchar[0],2);  
p+=2;  
}  
nzero = 0;  
  
//输出有效数据  
strncpy(p,numberchar[code[n]],2);  
p+=2;  
strncpy(p,unitchar[cunit--],2);  
p+=2;  
  
//有效位增加  
++nvalid;  
}  
else  
{  
//这个时候可以输出"园"  
if(nzero>3)  
{  
strncpy(p,unitchar[3],2);  
p+=2;  
}  
nzero = 0;  
}  
}  
//如果没有有效数据，全部是0，则补一个0  
if(nvalid == 0 && nzero> 0)  
{  
strncpy(p,numberchar[0],2);  
p+=2;  
}  
  
//输出单位“圆”  
if(nvalid == 0 || nzero>3)  
{  
strncpy(p,unitchar[3],2);  
p+=2;  
}  
  
//判断是否需要输出“整”  
//如果小数位0，结尾是2个0，或者结尾是一个0但是只有一个小数  
if(ndec == 0 || nzero == 2 || ( nzero == 1 && ndec == 1) )  
{  
strncpy(p,unitchar[0],2);  
p+=2;  
}  
  
*p = '\0';  
return dest;  
} 
#endif