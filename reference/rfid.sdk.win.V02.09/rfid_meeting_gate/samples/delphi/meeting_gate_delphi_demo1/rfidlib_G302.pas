unit rfidlib_G302;

interface

function   MG302_GetLibVersion( buf:pchar ; nSize:longword):longword  ;stdcall ;external 'rfidlib_G302.dll' ;
function   MG302_EthOpen( ipAddr:string; port:word ;var o_hr:longword):integer ; stdcall ;external 'rfidlib_G302.dll' ;
function   MG302_SerOpen( comname:string  ; baud : longword ; frame:string ;var o_hr:longword):integer;stdcall; external 'rfidlib_G302.dll' ;


implementation

end.