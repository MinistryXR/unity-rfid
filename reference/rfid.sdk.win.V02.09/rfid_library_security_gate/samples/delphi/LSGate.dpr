program LSGate;

uses
  Forms,
  LSGateDelphiDemo in 'LSGateDelphiDemo.pas' {MainForm},
  rfidlib_def in 'rfidlib_def.pas',
  rfidlib_reader in 'rfidlib_reader.pas',
  ThManage in 'ThManage.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.