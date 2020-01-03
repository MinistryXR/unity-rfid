unit rfidlib_aip_iso14443a;

{
  only for WIN32
}

interface
type
PBYTE=^byte  ;

function  ISO14443A_GetLibVersion( buf:pchar; nSize:longword):longword;stdcall ;external 'rfidlib_aip_iso14443a.dll' ;
function  ISO14443A_CreateInvenParam( hInvenParamSpecList:longword ; AntennaID:byte):longword; stdcall ;external 'rfidlib_aip_iso14443a.dll' ;
function  ISO14443A_ParseTagDataReport( hTagReport:longword ; var aip_id:longword ; var tag_id:longword ; var ant_id:longword ;  uid:PBYTE; var uidlen:byte ):integer; stdcall ;external 'rfidlib_aip_iso14443a.dll' ;

function MFCL_Connect( hr :longword ;tagType:byte;uid:PBYTE ;var ht:longword):integer ;stdcall ; external 'rfidlib_aip_iso14443a.dll' ;
function MFCL_Authenticate(hr:longword;ht:longword;blkAddr:Byte ; keyType:Byte ;key:PBYTE)  :integer;stdcall ; external 'rfidlib_aip_iso14443a.dll' ;
function MFCL_ReadBlock(hr:longword ;ht:longword; blkAddr:Byte ;blkData:PBYTE ; nSize:longword) :integer ; stdcall ;external 'rfidlib_aip_iso14443a.dll' ;
function MFCL_WriteBlock(hr:longword  ; ht:longword ;blkAddr:Byte ;blkData:PBYTE) :integer ; stdcall ;external 'rfidlib_aip_iso14443a.dll' ;


implementation


end.
