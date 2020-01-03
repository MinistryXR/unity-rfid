unit rfidlib_G101;

interface
function   MG101_GetLibVersion( buf:pchar ; nSize:longword):longword  ;stdcall ;external 'rfidlib_G101.dll' ;
function   MG101_Open( comname:string  ; baud : longword ; frame:string ;var o_hr:longword):integer ;stdcall; external 'rfidlib_G101.dll' ;

implementation

end.
