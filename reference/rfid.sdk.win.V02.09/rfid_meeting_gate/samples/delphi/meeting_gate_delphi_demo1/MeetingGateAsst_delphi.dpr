program MeetingGateAsst_delphi;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  UnitInventoryThrd in 'UnitInventoryThrd.pas',
  rfidlib_reader in 'rfidlib_reader.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
