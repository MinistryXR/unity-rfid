unit UnitInventoryThrd;

interface
uses    Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls,rfidlib_reader;

type
  TStopGetThread = class(TThread)
  public
  formHandle:HWND ;
  hr:longword;
  protected

  procedure Execute; override;

  end;
implementation
uses unit1;

procedure TStopGetThread.Execute;

begin
      RDR_BuffMode_StopReportCollection(hr) ;
      PostMessage(formHandle,WM_LOOPEXIT,0,0) ;
end;
end.
