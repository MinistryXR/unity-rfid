unit rfidlib_reader;
{
   Only for win32 platform
}
interface
uses Windows;


type
RFIDLIB_EVENTC_CB = procedure(wParam: longword; lParam: longword)  ; stdcall;
PBYTE=^byte  ;


function   RDR_GetLibVersion( buf:pchar ; nSize:longword):longword  ; stdcall ; external 'rfidlib_reader.dll' ;

function RDR_LoadReaderDrivers( path:string):integer ; stdcall ;external 'rfidlib_reader.dll'
function RDR_GetLoadedReaderDriverCount() :longword ; stdcall ;external 'rfidlib_reader.dll'
function RDR_GetLoadedReaderDriverOpt( idx:longword  ; option:string ; valueBuffer:pchar ;var nSize:longword ):integer ; stdcall ;external 'rfidlib_reader.dll'
function  RDR_GetLoadedReaderDriverOptByName( ID:string ; option:string;  valueBuffer:pchar ;var nSize:longword) :integer ; stdcall ;external 'rfidlib_reader.dll'
function  COMPort_Enum():longword ; stdcall ;external 'rfidlib_reader.dll'
function  COMPort_GetEnumItem( idx:longword ; nameBuf:pchar ; nSize:longword ) :integer ; stdcall ;external 'rfidlib_reader.dll'

function  HID_Enum( DevId:string):longword ; stdcall ;external 'rfidlib_reader.dll'
function  HID_GetEnumItem( indx:longword ; infType:byte ; infBuffer:pchar ;var nSize:longword ):integer ; stdcall ;external 'rfidlib_reader.dll'
function  RDR_Open( connStr:string ;var hrOut:longword):integer ; stdcall ;external 'rfidlib_reader.dll'
function  RDR_Close(hr:longword) :integer ; stdcall ;external 'rfidlib_reader.dll'

function   RDR_CreateInvenParamSpecList():longword  ; stdcall ; external 'rfidlib_reader.dll' ;

function   RDR_TagInventory( hr:longword ;AIType:byte;AntennaCoun:byte;AntennaIDs:PBYTE;InvenParamSpecList:longword):integer; stdcall ; external 'rfidlib_reader.dll' ;

function   RDR_GetTagDataReportCount( hr:longword) :longword; stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_GetTagDataReport( hr:longword; seek:byte):longword ;stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_EnableAsyncTagReportOutput(hr:longWord ;AsycType:byte; msg:longword ; hwnd:HWND ;cb:RFIDLIB_EVENTC_CB):integer ;stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_DisableAsyncTagReportOutput( hr:longword):integer ;stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_TagDisconnect( hr:longword; hTag:longword):integer;  stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_GetReaderLastReturnError( hr:longword):integer;  stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_SetAcessAntenna(hr:longword;AntennaID:byte):integer;  stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_OpenRFTransmitter(hr:longword):integer;  stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_CloseRFTransmitter(hr:longword):integer;  stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_SetCommuImmeTimeout(hr:longword):integer;  stdcall ; external 'rfidlib_reader.dll' ;
function   RDR_ResetCommuImmeTimeout(hr:longword):integer;stdcall;external 'rfidlib_reader.dll' ;
function   RDR_GetAntennaInterfaceCount(hr:longword):longword;stdcall ;external 'rfidlib_reader.dll'
function   RDR_GetReaderInfor(hr:longword;infType:Byte;buf:pchar;var nSize :longword) :integer;  stdcall ; external 'rfidlib_reader.dll' ;


function  RDR_CreateSetOutputOperations():longword ; stdcall ;external 'rfidlib_reader.dll'
function  RDR_AddOneOutputOperation( hOperas:longword; outNo:byte ; outMode:byte; outFrequency:longword; outActiveDuration:longword;  outInactiveDuration:longword) :integer;  stdcall ; external 'rfidlib_reader.dll' ;
function  RDR_SetOutput( hr:longword ;outputOpers:longword):integer ; stdcall ;external 'rfidlib_reader.dll'
function  RDR_LoadFactoryDefault(hr:longword ):integer ; stdcall ;external 'rfidlib_reader.dll'
function  RDR_SystemReset(hr:longword ):integer ; stdcall ;external 'rfidlib_reader.dll'
function  RDR_IsSupportInventoryAsyncOutput(hr:longword;var suppported:byte):integer ; stdcall ;external 'rfidlib_reader.dll'

function RDR_ConfigBlockWrite(hr:longword; cfgno :longword ;cfgdata:PBYTE ; nSize:longword ; mask:longword) :integer ; stdcall ;external 'rfidlib_reader.dll'
function RDR_ConfigBlockRead(hr:longword; cfgno:longword ;cfgbuff:PBYTE ; nSize:longword):integer ; stdcall ;external 'rfidlib_reader.dll'
function RDR_ConfigBlockSave(hr:longword; cfgno:longword):integer ; stdcall ;external 'rfidlib_reader.dll'

function RDR_CreateRS485Node( hr:longword;busAddr:longword ;var ohrRS485Node:longword)  :integer ; stdcall ;external 'rfidlib_reader.dll'

function RDR_GetSupportedAirInterfaceProtocol(hr:longword; index:longword ;var AIPType:longword):integer ; stdcall ;external 'rfidlib_reader.dll'

function RDR_DetectNoise(hr:longword; noiseData:PBYTE ;var nSize:longword) :integer ; stdcall ;external 'rfidlib_reader.dll'
function RDR_GetGPICount(hr:longword;var oCount:longword) :integer ; stdcall ;external 'rfidlib_reader.dll'


function  RDR_ExeSpecialControlCmd(hr:longword; cmd:string  ; params:string; result:pchar ; var nSize:longword) :integer ; stdcall ;external 'rfidlib_reader.dll'

function  RDR_GetGPIsStatus(hr:longword ;
									 GPIs:PBYTE  ;
									numToGet:word  ;
									status:PBYTE) :integer ; stdcall ;external 'rfidlib_reader.dll'

function DNODE_Destroy( dn:longword):integer;stdcall;external 'rfidlib_reader.dll'

function Bluetooth_Enum():integer;stdcall;external 'rfidlib_reader.dll'
function Bluetooth_GetEnumItem(idx:integer;infType:integer; nameBuf:pchar; var nSize:longword):integer;stdcall;external 'rfidlib_reader.dll'
function RDR_SetSystemTime(hr:longword;year:longword;month:byte;day:byte;hour:byte;minute:byte;second:byte):integer;stdcall;external 'rfidlib_reader.dll'

function RDR_BuffMode_FetchRecords(hr:longword;flags:longword) :integer;stdcall;external 'rfidlib_reader.dll'

function RDR_ParseTagDataReportRaw(hTagReport:longword;rawBuffer:pbyte; var nSize:longword):integer;stdcall;external 'rfidlib_reader.dll'

function RDR_BuffMode_ClearRecords(hr:longword):integer;stdcall;external 'rfidlib_reader.dll';

implementation

end.
