unit rfidlib_Gxxx;

interface


const  MGXXX_EVNT_REPORTOUT	 =1	 ;				//report event output
const  MGXXX_EVNT_ERROROUT	 =				2	 ;				//error event output
const  MGXXX_EVNT_COLLEXIT	 =				3   ;                //collecting exit event output


type
PBYTE=^byte  ;
RFIDLIB_EVENTC_CB = procedure(inParam:longword;wParam: longword; lParam: longword)  ; stdcall;

function   MGXXX_GetLibVersion( buf:pchar ; nSize:longword):longword  ;stdcall ;external 'rfidlib_Gxxx.dll' ;
function   MG1XX_Open( comname:string  ; baud : longword ; frame:string ;var o_hr:longword):integer ;stdcall; external 'rfidlib_Gxxx.dll' ;
function   MG3XX_OpenLAN( ipAddr:string; port:word ;var o_hr:longword):integer ; stdcall ;external 'rfidlib_Gxxx.dll' ;
function   MG3XX_OpenSerial( comname:string  ; baud : longword ; frame:string ;var o_hr:longword):integer;stdcall; external 'rfidlib_Gxxx.dll' ;
function   MGXXX_Close( hr:longword):integer ;stdcall external 'rfidlib_Gxxx.dll' ;
function   MGXXX_GetDeviceInfor( hr :longword ; infBuf:pchar ;var nSize:longword):integer ;stdcall ;external 'rfidlib_Gxxx.dll'
function   MGXXX_WriteCfgBlock(hr :longword ; cfgNo:byte ;cfgdata:PBYTE ; mask:Byte):integer;stdcall ;external 'rfidlib_Gxxx.dll' ;
function   MGXXX_ReadCfgBlock(hr :longword ; cfgNo:byte ; cfgdata:PBYTE ):integer ; stdcall ;external 'rfidlib_Gxxx.dll' ;
function   MGXXX_SaveCfgBlock(hr :longword ; cfgNo:Byte):integer;stdcall  ;external 'rfidlib_Gxxx.h' ;
function   MGXXX_SetOutputPort(hr :longword ; GPIOOutSel:Byte ; activeTime:byte ; frequency:byte ; pauseTime:Byte):integer; stdcall; external 'rfidlib_Gxxx.dll' ;
function   MGXXX_LoadFactoryDefault(hr :longword ):integer; stdcall ;external 'rfidlib_Gxxx.dll' ;
function   MGXXX_GetReports(hr :longword  ; Flag:byte):integer;stdcall; external 'rfidlib_Gxxx.dll' ;
function   MGXXX_ReportStoredMoveFirst(hr :longword ):integer ;stdcall ;external 'rfidlib_Gxxx.dll' ;
function   MGXXX_GetNumOfReportStored(hr :longword ) :longword;stdcall ;external 'rfidlib_Gxxx.dll' ;
function   MGXXX_GetReportStored(hr :longword  ; uid:pchar ; nSize:longword ;var dir :byte;  time:PBYTE):integer; stdcall  ;external 'rfidlib_Gxxx.dll' ;
function   MGXXX_GetLastReaderReturnErr(hr :longword  ):integer  ;stdcall ;external 'rfidlib_Gxxx.dll' ;
function   MGXXX_GetNoiseLevel(hr :longword ; noisebuf:PBYTE ;var nSize:longword) :integer;stdcall ;external 'rfidlib_Gxxx.dll' ;

function MGXXX_SetEventHandler(hr :longword ; eventType:Byte ; methType:byte ; msg :longword ; hwnd:longword ; cb:RFIDLIB_EVENTC_CB ; param:Pointer):integer;stdcall ;external 'rfidlib_Gxxx.dll' ;
function MGXXX_RunLoopCollecting(hr :longword  )  :integer;stdcall ;external 'rfidlib_Gxxx.dll' ;
function MGXXX_StopLoopCollecting(hr :longword  ) :integer;stdcall ;external 'rfidlib_Gxxx.dll' ;
function MGXXX_StopLoopCollectingBegin(hr :longword  ) :integer;stdcall ;external 'rfidlib_Gxxx.dll' ;
function MGXXX_StopLoopCollectingEnd(hr :longword  ) :integer;stdcall ;external 'rfidlib_Gxxx.dll' ;

function MGXXX_ParseIOReportData(hr:longword;hreport:longword;uid:pchar;nSize:longword;var dir:byte;time:PBYTE):integer;stdcall ;external 'rfidlib_Gxxx.dll' ;

function MGXXX_ClearBuffer(hr:longword):integer;stdcall ;external 'rfidlib_Gxxx.dll' ;

implementation

end.
