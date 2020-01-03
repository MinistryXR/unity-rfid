unit rfidlib_aip_iso15693;

{
  only for WIN32
}

interface
type
PBYTE=^byte  ;

function  ISO15693_GetLibVersion( buf:pchar; nSize:longword):longword;stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function  ISO15693_CreateInvenParam( hInvenParamSpecList:longword ; AntennaID:byte ;en_afi:byte ;afi:byte; slot_type:byte):longword; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function  ISO15693_ParseTagDataReport( hTagReport:longword ; var aip_id:longword ; var tag_id:longword ; var ant_id:longword ; var dsfid:byte ;  uid:PBYTE):integer; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function  ISO15693_Connect( hr :longword ;tagType:longword;address_mode  :byte;uid:PBYTE ;var ht:longword):integer ;stdcall ; external 'rfidlib_aip_iso15693.dll' ;
function  ISO15693_ReadSingleBlock(hr:longword;ht:longword;readSecSta :byte;blkAddr:longword;bufBlockDat:pbyte; nSize :longword;var bytesBlkDatRead:longword)  :integer;stdcall ; external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_WriteSingleBlock(hr:longword ;ht:longword;blkAddr:longword;newBlkData:pbyte;bytesToWrite:longword) :integer ; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_LockBlock(hr:longword  ; ht:longword ;blkAddr  :longword) :integer ; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_ReadMultiBlocks( hr:longword  ; ht:longword ; readSecSta :byte;blkAddr:longword;numOfBlksToRead:longword;	var numOfBlksRead:longword; bufBlocks :pbyte;nSize:longword;var	bytesBlkDatRead:longword) :integer ; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_WriteMultipleBlocks(hr:longword  ;ht:longword ;blkAddr:longword;numOfBlks:longword;newBlksData:pbyte;bytesToWrite:longword):integer ; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_WriteAFI(hr:longword  ;ht:longword ; afi:byte):integer ; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_LockAFI(hr:longword  ;ht:longword ) :integer ; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_WriteDSFID(hr:longword  ;	ht:longword ; dsfid:byte)  :integer ; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_LockDSFID(hr:longword  ;	ht:longword ) :integer ; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_GetSystemInfo(hr:longword  ;	ht:longword ;	uid:pbyte;	var dsfid:byte;						var afi:byte;	var blkSize :longword; var numOfBloks:longword;	var icRef:byte):integer; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_GetBlockSecStatus(hr:longword  ;ht:longword ;blkAddr:longword;numOfBlks:longword;bufBlkSecs:pbyte; nSize:longword;var bytesSecRead:longword) :integer; stdcall ;external 'rfidlib_aip_iso15693.dll' ;
function ISO15693_LockMultipleBlocks(hr:longword ; ht:longword ;blkAddr:longword; numOfBlks:longword) : integer;   stdcall ;external 'rfidlib_aip_iso15693.dll' ;

function NXPICODESLI_EableEAS(hr:longword;ht:longword ):integer; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLI_DisableEAS(hr:longword;ht:longword ):integer; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLI_LockEAS(hr:longword;ht:longword ):integer; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLI_EASCheck(hr:longword;ht:longword ;var EASStatus:byte):integer;   stdcall; external 'rfidlib_aip_iso15693.dll' ;

function NXPICODESLIX_EableEAS(hr:longword;ht:longword ):integer; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLIX_DisableEAS(hr:longword;ht:longword ):integer; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLIX_LockEAS(hr:longword;ht:longword ):integer; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLIX_EASCheck(hr:longword;ht:longword ;var EASStatus:byte):integer;   stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLIX_GetRandomNum(hr:longword;ht:longword ;var random:word):integer ;   stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLIX_SetPassword( hr:longword;ht:longword ; pwdNo:byte; xor_pwd:longword):integer  ;stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLIX_WritePassword(hr:longword;ht:longword ; pwdNo:byte ; pwd:longword):integer  ;stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLIX_LockPassword(hr:longword;ht:longword ; pwdNo:byte):integer  ;stdcall; external 'rfidlib_aip_iso15693.dll' ;
function NXPICODESLIX_PasswordProtect(hr:longword;ht:longword; bandType:byte):integer  ;stdcall; external 'rfidlib_aip_iso15693.dll' ;


function STM24LR16E_UpdatePassword(hr:longword ;ht:longword ;pwdnum: byte;old_pwd:longword; new_pwd:longword) :integer ;stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR16E_AuthPassword(hr:longword ; ht:longword;pwdnum:byte;pwd:longword):integer ;   stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR16E_ActivateSectorSecurity(hr:longword ;ht:longword;  sector_num:byte;  access_type:byte; pwd_num_protect:byte):integer  ; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR16E_ReadCFGByte(hr:longword ;ht:longword;var cfgby:byte  ) :integer;  stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR16E_SetCFGEH(hr:longword ;ht:longword;EnergyHarvesting:byte;EHMode:byte):integer ; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR16E_SetCFGDO(hr:longword ;ht:longword;  cfg_do:byte):integer ; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR16E_SetCtrlRegEHEN(hr:longword ;ht:longword; enable :byte):integer ; stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR16E_ReadCtrlReg(hr:longword ;ht:longword; var ctrlreg:byte):integer ;stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR64_UpdatePassword(hr:longword ;ht:longword ;pwdnum: byte;old_pwd:longword; new_pwd:longword) :integer ;stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR64_AuthPassword(hr:longword ; ht:longword;pwdnum:byte;pwd:longword):integer ;   stdcall; external 'rfidlib_aip_iso15693.dll' ;
function STM24LR64_ActivateSectorSecurity(hr:longword ;ht:longword;  sector_num:byte;  access_type:byte; pwd_num_protect:byte):integer  ; stdcall; external 'rfidlib_aip_iso15693.dll' ;
implementation


end.
