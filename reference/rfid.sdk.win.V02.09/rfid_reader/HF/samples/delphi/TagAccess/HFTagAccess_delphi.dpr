program HFTagAccess_delphi;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  rfidlib_reader in 'rfidlib_reader.pas',
  rfidlib_aip_iso15693 in 'rfidlib_aip_iso15693.pas',
  rfidlib_def in 'rfidlib_def.pas',
  UnitInventoryThrd in 'UnitInventoryThrd.pas',
  rfidlib_aip_iso14443a in 'rfidlib_aip_iso14443a.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
