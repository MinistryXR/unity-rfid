unit BufferModeSample;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls,rfidlib_reader, Grids,rfidlib_def,
  CheckLst ,UnitGetRecordThrd;//, IPEdit;

type
  TForm1 = class(TForm)
    ComboBoxReader: TComboBox;
    ButtonOpen: TButton;
    ButtonClose: TButton;
    buttonSetTime: TButton;
    GroupBox1: TGroupBox;
    StaticText1: TStaticText;
    StaticText2: TStaticText;
    ComboBoxInterface: TComboBox;
    GroupBox2: TGroupBox;
    StaticText3: TStaticText;
    ComboBoxCOMName: TComboBox;
    StaticText4: TStaticText;
    ComboBoxBaud: TComboBox;
    ComboBoxFrame: TComboBox;
    StaticText5: TStaticText;
    GroupBox3: TGroupBox;
    StaticText6: TStaticText;
    StaticText7: TStaticText;
    EditIP: TEdit;
    EditPort: TEdit;
    GroupBox4: TGroupBox;
    StaticText8: TStaticText;
    ComboBoxBluetoothName: TComboBox;
    StaticText9: TStaticText;
    EditBluetoothAddr: TEdit;
    ListView1: TListView;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    procedure ButtonOpenClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure buttonSetTimeClick(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure ButtonCloseClick(Sender: TObject);
    procedure ComboBoxBluetoothNameChange(Sender: TObject);
  private
    { Private declarations }
    procedure  MsgGetReport(var   MSG:TMsg);message   WM_GETRECORD_REPORT;
    procedure  MsgThreadFinish(var   MSG:TMsg);message   WM_THREAD_FINISH;
    procedure AddRecord(data:array of byte;len:Integer);
  public
    { Public declarations }
    hreader:longword;
    reader_opened:boolean;
    threadRuning:boolean;
    reader_type:integer;
    invenRuning:boolean;
    invenThrd:TGetRecordThread;
  end;

var
  Form1: TForm1;

implementation


function BytesToHex(buffer:Pbyte;nLen:integer):string;
var
i:integer;
ptmp:pbyte;

begin
      result:='' ;
      ptmp:=buffer;
      for i:=0 to   nLen-1 do
      begin
            result:=result+inttohex(ptmp^,2) ;

            inc(ptmp) ;

      end;

end;

{$R *.dfm}

//获取记录
procedure  TForm1.MsgGetReport(var   MSG:TMsg);
var
  iret:Integer;
  hReport:LongWord ;
  byData:array[0..32] of Byte;
  byLen:LongWord;
  strData:string;
begin
  hReport:=msg.wParam ;
  byLen:=32;
  iret:= RDR_ParseTagDataReportRaw(hReport, @byData[0],byLen);
  if iret=0  then
  begin
    AddRecord(byData,byLen);
  end;

end;

//线程结束
procedure  TForm1.MsgThreadFinish(var   MSG:TMsg);
begin
  Button1.Enabled := True;
  Button2.Enabled:=False;
  Button3.Enabled:=True;
  invenRuning:=False;
end;

procedure TForm1.ButtonOpenClick(Sender: TObject);
var
iret :integer ;
idx :integer;
commTypeIdx:integer;
i:integer;
antCount:integer;
usbOpenType:byte;
connstr:string;
begin
  idx:= ComboBoxReader.ItemIndex ;
     if idx = -1 then
     begin
         showmessage('please select reader type') ;
         exit;
     end;

     commTypeIdx := ComboBoxInterface.ItemIndex ;
     if  commTypeIdx = -1 then
     begin
         showmessage('please select communication type') ;
         exit;
     end;

     if commTypeIdx = 0 then   //USB
     begin
                connstr := CONNSTR_NAME_RDTYPE + '=' + ComboBoxReader.Text + ';' +
                          CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_USB + ';' +
                          CONNSTR_NAME_HIDADDRMODE+'='+'0' +';' +
                          CONNSTR_NAME_HIDSERNUM + '=' ;
     end
     else if commTypeIdx = 1 then    //COM
     begin
                connstr := CONNSTR_NAME_RDTYPE +'='+ ComboBoxReader.Text + ';'+
                          CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_COM + ';' +
                          CONNSTR_NAME_COMNAME+'=' + ComboBoxCOMName.Text + ';'+
                          CONNSTR_NAME_COMBARUD+'='+ComboBoxBaud.Text +';' +
                          CONNSTR_NAME_COMFRAME+'='+ComboBoxFrame.Text +';'+
                          CONNSTR_NAME_BUSADDR+'='+'255' ;
     end

     else if commTypeIdx = 2 then  //NET
     begin
                connstr := CONNSTR_NAME_RDTYPE + '=' + ComboBoxReader.Text + ';' +
                          CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_NET + ';' +
                          CONNSTR_NAME_REMOTEIP + '=' + EditIP.Text + ';' +
                          CONNSTR_NAME_REMOTEPORT + '=' + EditBluetoothAddr.Text  + ';' +
                          CONNSTR_NAME_LOCALIP + '=' + '';
     end

     else if  commTypeIdx = 3 then    //BLUETOOTH
     begin
       connstr:= CONNSTR_NAME_RDTYPE + '=' + ComboBoxReader.Text + ';' +
                        CONNSTR_NAME_COMMTYPE + '=' + 'BLUETOOTH' + ';' +
                        'Addr' + '=' + EditBluetoothAddr.Text;
     end;

     iret :=RDR_Open(connstr , hreader) ;
     if iret<>0 then
     begin
         showmessage('Failed to open the reader.') ;
         exit;
     end;

     ButtonOpen.Enabled := False;
     ButtonClose.Enabled:=True;
     buttonSetTime.Enabled:=True;
     ComboBoxCOMName.Enabled:=False;
     ComboBoxBaud.Enabled:=False;
     ComboBoxFrame.Enabled:=False;
     EditIP.Enabled:=False;
     EditPort.Enabled:=False;
     ComboBoxBluetoothName.Enabled:=False;
     EditBluetoothAddr.Enabled:=False;
     Button1.Enabled:=True;
     Button2.Enabled:=False;
     Button2.Enabled:=False;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
driverCnt:longword;
portCnt:longword;
bluetoothCnt:longword;
i:integer;
iret:integer;
nSize :longword;
optBuf:array[0..63] of char;
portBuf:array[0..31] of char;
bluetoothBuf:array[0..32] of char;
bluetoothAddr:array[0..32] of char;
begin
       reader_opened:=false;
       reader_type :=-1;
       threadRuning :=false;
       RDR_LoadReaderDrivers('\Drivers') ;
       ComboBoxReader.Items.Add('RPAN') ;
       {
       driverCnt:=RDR_GetLoadedReaderDriverCount() ;
       for i:=0 to driverCnt-1 do
       begin
            ZeroMemory(@optBuf[0],sizeof(optBuf));
            nSize:=sizeof(optBuf) ;
            iret:=RDR_GetLoadedReaderDriverOpt(i,LOADED_RDRDVR_OPT_CATALOG ,@optBuf[0],nSize) ;
            if iret = 0 then
            begin
                if optBuf = RDRDVR_TYPE_READER then // we only need reader driver
                begin
                     ZeroMemory(@optBuf[0],sizeof(optBuf));
                     nSize:=sizeof(optBuf) ;
                     iret:=RDR_GetLoadedReaderDriverOpt(i,LOADED_RDRDVR_OPT_NAME ,@optBuf[0],nSize) ;
                     if iret = 0 then
                     begin
                          ComboBoxReader.Items.Add(optBuf) ;
                     end;

                end;
            end;
       end;}

       bluetoothCnt := Bluetooth_Enum();
       for i:=0 to  bluetoothCnt-1 do
       begin
        nSize:=  sizeof(bluetoothBuf);
        ZeroMemory(@bluetoothBuf[0],nSize);
        iret :=Bluetooth_GetEnumItem(i,1,bluetoothBuf ,nSize) ;
        if iret = 0 then
        begin
        ComboBoxBluetoothName.Items.Add(bluetoothBuf) ;
        end;
        if bluetoothCnt>0 then
        begin
        ComboBoxBluetoothName.ItemIndex:=0;   //bluetoothAddr
        nSize:= sizeof(bluetoothAddr);
        ZeroMemory(@bluetoothAddr[0],sizeof(bluetoothAddr));
        iret :=Bluetooth_GetEnumItem(0,2,bluetoothAddr ,nSize) ;
        EditBluetoothAddr.Text :=   bluetoothAddr;
        end;
       end;

       portCnt := COMPort_Enum() ;
       for i:=0 to portCnt-1 do
       begin
            ZeroMemory(@portBuf[0],sizeof(portBuf));
            iret :=COMPort_GetEnumItem(i,portBuf , sizeof(portBuf)) ;
            if iret = 0 then
            begin
                 ComboBoxCOMName.Items.Add(portBuf) ;
            end;
       end;
       if(ComboBoxCOMName.Items.Count > 0) then ComboBoxCOMName.ItemIndex:=0 ;
       if ComboBoxReader.Items.Count > 0 then ComboBoxReader.ItemIndex:= 0 ;

       ComboBoxBaud.Items.Add('9600');
       ComboBoxBaud.Items.Add('38400');
       ComboBoxBaud.Items.Add('57600');
       ComboBoxBaud.Items.Add('115200');
       ComboBoxBaud.ItemIndex:=1;

       ComboBoxFrame.Items.Add('8E1');
       ComboBoxFrame.Items.Add('8N1');
       ComboBoxFrame.Items.Add('8O1');
       ComboBoxFrame.ItemIndex:=0;

       ComboBoxInterface.Items.Add('USB');
       ComboBoxInterface.Items.Add('COM');
       ComboBoxInterface.Items.Add('Net');
       ComboBoxInterface.ItemIndex:=0;
       ComboBoxInterface.Items.Add('Bluetooth');
end;



procedure TForm1.Button1Click(Sender: TObject);
var
ID: THandle;
begin
   Button1.Enabled:=False;
   Button2.Enabled:=True;
   Button3.Enabled:=False;
   ListView1.Items.Clear ;
   invenThrd := TGetRecordThread.Create(true);
   invenThrd.stopFlag := false;
   invenThrd.formHandle:= self.Handle ;
   invenThrd.hreader:=hreader;
   invenThrd.Resume ;
   invenRuning:= true;

end;



 procedure  TForm1.AddRecord(data:array of byte;len:Integer);
 var
 lstvItem:TListItem;
 strData:string;
 begin
    lstvItem:=ListView1.Items.Add ;
    strData :=  BytesToHex(@data[0],len);
    lstvItem.Caption:=strData;
 end;

procedure TForm1.buttonSetTimeClick(Sender: TObject);
var
dTime:TsystemTime;
iret:Integer;
begin
  getlocaltime(dTime)     ;
  iret:=RDR_SetSystemTime(hreader,dTime.wYear,dTime.wMonth,dTime.wDay,dTime.wHour,dTime.wMinute,dTime.wSecond);
  if iret=0 then
  begin
     showmessage('Set system time successfully.') ;
  end;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
invenThrd.stopFlag:= true;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
  iret:Integer;
begin
  iret := RDR_BuffMode_ClearRecords(hreader);
  if iret=0 then
  begin
    ListView1.Items.Clear ;
    showmessage('Clear the record successfully.') ;
  end
  else
  begin
    showmessage('Failed to clear the record') ;
  end;

end;

procedure TForm1.ButtonCloseClick(Sender: TObject);
begin
  if  invenRuning then
  begin
    showmessage('Please stop the thread of getting the report.') ;
    exit;

  end;
  if hreader<>0 then
  begin
    RDR_Close(hreader)   ;
    hreader:=0;
  end;
   ButtonOpen.Enabled := True;
   ButtonClose.Enabled:=False;
     buttonSetTime.Enabled:=False;
     ComboBoxCOMName.Enabled:=True;
     ComboBoxBaud.Enabled:=True;
     ComboBoxFrame.Enabled:=True;
     EditIP.Enabled:=True;
     EditPort.Enabled:=True;
     ComboBoxBluetoothName.Enabled:=True;
     EditBluetoothAddr.Enabled:=True;
     Button1.Enabled:=False;
     Button2.Enabled:=False;
     Button2.Enabled:=False;
end;

procedure TForm1.ComboBoxBluetoothNameChange(Sender: TObject);
var
  iret:Integer;
  idx:Integer;
  nSize:LongWord;
  bluetoothBuf:array[0..32] of char;
  bluetoothAddr:array[0..32] of char;
begin
  idx:=ComboBoxBluetoothName.ItemIndex;
  if (idx=-1) then
  begin
   exit;
  end;
  nSize :=  sizeof(bluetoothBuf);
  ZeroMemory(@bluetoothBuf[0],nSize);
  iret := Bluetooth_GetEnumItem(idx,2,bluetoothBuf ,nSize);
  if iret=0 then
  begin
  EditBluetoothAddr.Text :=  bluetoothBuf;
  end;
end;

end.

