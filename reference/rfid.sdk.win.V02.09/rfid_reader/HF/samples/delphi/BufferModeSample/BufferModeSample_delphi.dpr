program BufferModeSample_delphi;

uses
  Forms,
  BufferModeSample in 'BufferModeSample.pas' {Form1},
  UnitGetRecordThrd in 'UnitGetRecordThrd.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
