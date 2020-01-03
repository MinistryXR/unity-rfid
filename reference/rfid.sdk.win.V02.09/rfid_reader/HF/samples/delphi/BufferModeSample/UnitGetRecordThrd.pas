unit UnitGetRecordThrd;
interface
uses    Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls,rfidlib_reader, Grids,rfidlib_def,
  CheckLst;

const 
WM_GETRECORD_REPORT = WM_USER+1;
WM_THREAD_FINISH = WM_USER + 2;

type
 TGetRecordThread = class(TThread)
  public
  antennas:array[0..15] of byte;
  antcount:byte;
  hreader:longword ;
  onlyNewTag:boolean;
  checkAFI:byte;
  afiVal:byte;
  stopFlag:boolean;
  formHandle:HWND ;

   protected

  procedure Execute; override;
end;
implementation

procedure TGetRecordThread.Execute;
var
iret :integer;
hReport:longword;
gFlg:Byte;

begin
  iret := 0;
  gFlg:=0;
  hReport:=0;
 while(stopFlag = false) do
 begin
    iret := RDR_BuffMode_FetchRecords(hreader, gFlg); // send command to device
     if iret<>0 then
     begin
       Continue;
     end;
     hReport := RDR_GetTagDataReport(hreader, RFID_SEEK_FIRST);
     while hReport<>0 do
     begin
       SendMessage(formHandle,WM_GETRECORD_REPORT,0,hReport) ;
       hReport := RDR_GetTagDataReport(hreader,RFID_SEEK_NEXT);
     end;
     gFlg := 1;
 end;
  SendMessage(formHandle,WM_THREAD_FINISH,0,0) ;
end;

end.
