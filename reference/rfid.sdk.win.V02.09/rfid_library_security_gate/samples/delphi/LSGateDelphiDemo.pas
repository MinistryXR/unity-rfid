unit LSGateDelphiDemo;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Mask, ComCtrls, Grids,rfidlib_def,rfidlib_reader,ThManage;


type
  TMainForm = class(TForm)
    NetworkGroup: TGroupBox;
    IPLabel: TLabel;
    IPMaskEdit: TMaskEdit;
    OpenBtn: TButton;
    CloseBtn: TButton;
    GetDevInfoBtn: TButton;
    MainPageCtrl: TPageControl;
    CommandPage: TTabSheet;
    EventRecordPage: TTabSheet;
    PeopleFlowGroup: TGroupBox;
    GetPeopleFlowBtn: TButton;
    ClearPeopleFlowBtn: TButton;
    PeopleFlowIn: TLabel;
    PeopleFlowOut: TLabel;
    PeopleFlowInNum: TLabel;
    PeopleFlowOutNum: TLabel;
    ReverseDirectionBtn: TButton;
    SystemTimeGroup: TGroupBox;
    SetSystemTimeBtn: TButton;
    GetSystemTimeBtn: TButton;
    CurrentSystemTimeLabel: TLabel;
    EventRecordListLabel: TLabel;
    RecordList: TListView;
    EventRecordStartBtn: TButton;
    EventRecordStopBtn: TButton;
    EventRecordClearBtn: TButton;
    EventRecordErrorLabel: TLabel;
    EventRecordCountLabel: TLabel;
    EventRecordMemo: TMemo;
    procedure FormCreate(Sender: TObject);
    procedure OpenBtnClick(Sender: TObject);
    procedure CloseBtnClick(Sender: TObject);
    procedure GetDevInfoBtnClick(Sender: TObject);
    procedure GetPeopleFlowBtnClick(Sender: TObject);
    procedure ClearPeopleFlowBtnClick(Sender: TObject);
    procedure SetSystemTimeBtnClick(Sender: TObject);
    procedure GetSystemTimeBtnClick(Sender: TObject);
    procedure ReverseDirectionBtnClick(Sender: TObject);
    procedure EventRecordStartBtnClick(Sender: TObject);
    procedure EventRecordStopBtnClick(Sender: TObject);
    procedure EventRecordClearBtnClick(Sender: TObject);


  private



    procedure CommandTabRanderOpen();
    procedure CommandTabRanderClose();
    procedure EventRecordTabRanderOpen();
    procedure EventRecordTabRanderClose();

    procedure ShowError(msg:string;iret:integer);
    procedure StartGetEvent();

    function ManageStartThread:Boolean;  //线程开启操作

    procedure MsgLogError(var MSG:TMsg);message WM_LOGERROR_MSG;
    procedure MsgCountNum(var MSG:TMsg);message WM_COUNTNUM_MSG;
    procedure MsgThreadExit(var MSG:TMsg);message WM_THREADEXIT_MSG;
    procedure MsgReportData(var MSG:TMsg);message WM_REPORTDATA_MSG;

  public
      hreader:longword;
      inventTh:TInventThread;
      invenRuning:boolean;
      m_counter:integer;
  end;



var
  MainForm: TMainForm;

implementation

{$R *.dfm}


// *** 显示错误函数 ***********************************
procedure TMainForm.ShowError(msg:string;iret:integer);
begin
   msg := msg + ',Error Codes=';
   msg := msg + IntToStr(iret);
   showmessage(msg);
end;




procedure TMainForm.FormCreate(Sender: TObject);
var
  i:integer;

begin
   IPMaskEdit.Text := '192.168.0.222';    //设置初始的IP地址
   CloseBtn.Enabled := false;  //初始时将close按钮设置不可用
   GetDevInfoBtn.Enabled := false;  //初始时将GetDevInfoBtn按钮设置为不可用
   GetPeopleFlowBtn.Enabled := false; //初始时将GetPeopleFlowBtn按钮设置为不可用
   ClearPeopleFlowBtn.Enabled := false;  //初始时将ClearPeopleFlowBtn按钮设置为不可用
   ReverseDirectionBtn.Enabled := false;  //初始时将ReverseDirectionBtn设置为不可用
   SetSystemTimeBtn.Enabled := false;  //初始时将SetSystemTimeBtn设置为不可用
   GetSystemTimeBtn.Enabled := false;  //初始时将GetSystemTimeBtn设置为不可用
   CurrentSystemTimeLabel.Caption := '2017-03-08';   //初始时将CurrentSysteTimeLabel设置日期

   //*** 设置RecordList列表 ****************************************
   RecordList.Clear;
   RecordList.Columns.Clear;
   RecordList.Columns.Add;
   RecordList.Columns.Add;
   RecordList.Columns.Add;
   RecordList.Columns.Items[0].Caption := 'Serial Number';
   RecordList.Columns.Items[0].Width := 150;
   RecordList.Columns.Items[1].Caption := 'Direction';
   RecordList.Columns.Items[1].Width := 100;
   RecordList.Columns.Items[2].Caption := 'Time';
   RecordList.Columns.Items[2].Width := 100;
   RecordList.ViewStyle := vsreport;
   RecordList.GridLines := true;

   //*** 设置RecordList列表 ****************************************


   EventRecordStartBtn.Enabled := false;   //初始时将EventRecordStartBtn设置为不可用
   EventRecordStopBtn.Enabled := false;   //初始时将EventRecordStopBtn设置为不可用
   EventRecordMemo.Lines.Clear;

   RDR_LoadReaderDrivers('\Drivers');


   invenRuning := false;   //设置线程启动标志为false

   m_counter := 0;

end;

procedure  TMainForm.MsgLogError(var MSG:TMsg);
var
  msgstr:String;
begin
  //获取消息信息
  msgstr := 'Failed!error=' + IntToStr(MSG.wParam) + #13#10;
  //追加到编辑框里    EventRecordMemo
  EventRecordMemo.Text := EventRecordMemo.Text + msgstr;
  //Memo1->Text = Memo1->Text +Str ;

  //long  nInsertAfterChar = m_reErrorLog.GetWindowTextLength();
	//m_reErrorLog.SetSel(nInsertAfterChar, nInsertAfterChar);
	//m_reErrorLog.ReplaceSel(msg, FALSE);
end;

procedure TMainForm.MsgCountNum(var MSG:TMsg);
var
  nCount:integer;
  str:String;
begin
     nCount := MSG.wParam;
     m_counter := m_counter+nCount;
     str := IntToStr(m_counter) + ',' + IntToStr(nCount);
     EventRecordCountLabel.Caption := str;
end;


procedure TMainForm.MsgThreadExit(var MSG:TMsg);
begin
      //线程结束
      inventTh.stop();
      EventRecordStartBtn.Enabled := true; //可用

      OpenBtn.Enabled := false;  //不可用
      CloseBtn.Enabled := true;  //可用
      GetDevInfoBtn.Enabled := true; //可用

      CommandTabRanderOpen();
end;

procedure TMainForm.MsgReportData(var MSG:TMsg);
var
  data:myData;
  str:String;
  strData:String;
  time:String;
  addr:integer;
begin
    addr := MSG.LParam;
    data := myData(MSG.WParam);
    str := 'NULL';
    if  data.direction = 1 then
      begin
          str := 'In';
      end;

    if data.direction = 2 then
      begin
          str := 'Out';
      end;


    //向列表中追加数据
    strData := data.strData;
    time := data.time;
    with RecordList.Items.Add do
      begin
          caption := strData;
          subitems.Add(str);
          subitems.Add(time);
      end;


end;

function Trimplace(str:string):string;
 var
     tmp:string;
     p:Integer;
 begin
     tmp:=Trim(str);
     while Pos(' ',tmp) > 0 do
     begin
         p :=  Pos(' ',tmp);
         tmp := Copy(tmp,1,p-1)+Copy(tmp,p+1,Length(tmp)-p);
     end;   
     Result := tmp;
 end;

//*** 判断是否是有效的IP地址 ***************************************
function IsValidIP(strIP: string): Boolean;
var
  i, PartCount {用多少段,以点号分开}: Integer;
  Part: string;
begin
  PartCount := 0;
  while strIP <> '' do
  begin
    i := Pos('.', strIP);
    if i = 0 then
    begin
      Part := strIP;
      strIP := '';
    end
    else
    begin
      Part := Copy(strIP, 1, i - 1);
      Part := Trimplace(Part);
      Delete(strIP, 1, i);
    end;
    //IP分段必须是[0,255]的整数
    if not TryStrToInt(Part, i) or (i < 0) or (i > 255) then
    begin
      Result := False;
      Exit;
    end;
    Inc(PartCount);
  end;
  Result := PartCount = 4; //必须要有4段
end;

procedure TMainForm.OpenBtnClick(Sender: TObject);
var
   IpResultBoolean:boolean;
   connstr:string;
   ipstr:string;
   iret:integer;
begin

// *** open 代码部分 ***********************************************
    //*** 首先判断 ip 地址的正确性
    ipstr := IPMaskEdit.Text;
    ipstr := Trimplace(ipstr);
    IpResultBoolean := IsValidIP(ipstr);

    if IpResultBoolean = false then
       begin
       showmessage('IP地址不正确');
       Exit;
       end;

    //*** 执行其他的逻辑代码 **************

    connstr := CONNSTR_NAME_RDTYPE + '=' + 'LSG405' + ';' +
               CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_NET + ';' +
               CONNSTR_NAME_REMOTEIP + '=' + ipstr + ';' +
               CONNSTR_NAME_REMOTEPORT +  '=' + '6012' + ';' +
               CONNSTR_NAME_LOCALIP + '=' + '';
    iret := RDR_Open(connstr,hreader);
    if iret <> 0 then
       begin
       showmessage('Open failed !');
       Exit;
       end;


    OpenBtn.Enabled := false;  //设为不可用
    CloseBtn.Enabled := true;  //设为可用
    GetDevInfoBtn.Enabled := true;  //设为可用

    //*** 针对Tab所做的操作 ***************
    CommandTabRanderOpen();
    EventRecordTabRanderOpen();

// *** open 代码部分 ***********************************************
end;



// *** 指定CommandTab的某些按钮的可用性 ****************************
procedure TMainForm.CommandTabRanderOpen();
begin
   GetPeopleFlowBtn.Enabled := true;  //可用
   ClearPeopleFlowBtn.Enabled := true; //可用
   SetSystemTimeBtn.Enabled := true;  //可用
   GetSystemTimeBtn.Enabled := true;  //可用
   ReverseDirectionBtn.Enabled := true;  //可用

end;

procedure TMainForm.CommandTabRanderClose();
begin
   GetPeopleFlowBtn.Enabled := false;  //不可用
   ClearPeopleFlowBtn.Enabled := false; //不可用
   SetSystemTimeBtn.Enabled := false;  //不可用
   GetSystemTimeBtn.Enabled := false;  //不可用
   ReverseDirectionBtn.Enabled := false;  //不可用
end;

// *** 指定CommandTab的某些按钮的可用性 ****************************

// *** 指定EventRecordTab的某些按钮的可用性 ***********************
procedure TMainForm.EventRecordTabRanderOpen();
begin
     EventRecordStartBtn.Enabled := true;  //可用
     EventRecordStopBtn.Enabled := false;  //不可用
end;

procedure TMainForm.EventRecordTabRanderClose();
begin
     EventRecordStartBtn.Enabled := false;  //不可用
     EventRecordStopBtn.Enabled := false;  //不可用
end;

// *** 指定EventRecordTab的某些按钮的可用性 ***********************


procedure TMainForm.CloseBtnClick(Sender: TObject);
var
  iret:integer;
begin
  iret := RDR_Close(hreader);
  if iret <> 0 then
     begin
       showmessage('Close failed!');
       Exit;
     end;

  OpenBtn.Enabled := true;  //可用
  CloseBtn.Enabled := false;  //不可用
  GetDevInfoBtn.Enabled := false; //不可用
  EventRecordStartBtn.Enabled := false;  //不可用
  
  CommandTabRanderClose();
  
end;

procedure TMainForm.GetDevInfoBtnClick(Sender: TObject);
var

infoBuf:array[0..128] of char ;
iret :integer;
nSize:longword ;
begin
     nSize := sizeof(infoBuf) ;
     ZeroMemory(@infoBuf[0],nSize) ;
     iret :=RDR_GetReaderInfor(hreader,0, infoBuf,nSize) ;
     if(iret = 0) then
     begin
          ShowMessage( infoBuf);
     end
     else
     begin
          ShowMessage('Get device information failed!') ;
     end;

end;

procedure TMainForm.GetPeopleFlowBtnClick(Sender: TObject);
var
  iret:integer;
  inFlow:longword;
  outFlow:longword;
begin
  iret := RDR_GetPassingCounter(hreader,inFlow,outFlow);
  if iret <> 0 then
    begin
        ShowError('Get flow of people failed',iret);
        Exit;
    end;

   PeopleFlowInNum.Caption := IntToStr(inFlow);
   PeopleFlowOutNum.Caption := IntToStr(outFlow);

end;

procedure TMainForm.ClearPeopleFlowBtnClick(Sender: TObject);
var
  iret:integer;
begin
  iret := RDR_ResetPassingCounter(hreader,3);
  if iret <> 0 then
    begin
        ShowError('reset flow of people failed',iret);
        Exit;
    end;

   PeopleFlowInNum.Caption := '0';
   PeopleFlowOutNum.Caption := '0';

end;

procedure TMainForm.SetSystemTimeBtnClick(Sender: TObject);
var
  iret:integer;
  Present:TDateTime;
  Year,Month,Day:Word;
  Hour,Min,Sec,MSec:Word;
begin
  // 获取本地时间
  Present := Now;
  DecodeDate(Present,Year,Month,Day);
  DecodeTime(Present,Hour,Min,Sec,MSec);
  iret := RDR_SetSystemTime(hreader,Year,Month,Day,Hour,Min,Sec);
  if iret <> 0 then
    begin
        ShowError('Set system time failed!',iret);
        Exit;
    end;

   showmessage('Success');
end;

procedure TMainForm.GetSystemTimeBtnClick(Sender: TObject);
var
  iret:integer;
  wYear:longword;
  bMonth,bDay,bHour,bMinute,bSecond:Byte;
  connstr:string;
begin
  iret := RDR_GetSystemTime(hreader,wYear,bMonth,bDay,bHour,bMinute,bSecond);
  if iret <> 0 then
    begin
        ShowError('Get system time failed!',iret);
        Exit;
    end;

    connstr :=  IntToStr(wYear) + '-' + IntToStr(bMonth) + '-' + IntToStr(bDay) + ' ' + IntToStr(bHour) + ':' + IntToStr(bMinute) + ':' + IntToStr(bSecond);
    CurrentSystemTimeLabel.Caption := connstr;

end;

procedure TMainForm.ReverseDirectionBtnClick(Sender: TObject);
var
  iret:integer;
begin
  iret := RDR_ReverseInOutDirection(hreader);
  if iret <> 0 then
    begin
        ShowError('Failed',iret);
        Exit;
    end;

    showmessage('Success');

end;

// *** 线程函数 ***********************************************
function ProcGetReports():integer;
begin


end;

// *** 线程函数 ***********************************************


procedure TMainForm.EventRecordStartBtnClick(Sender: TObject);

begin
    EventRecordStartBtn.Enabled := false;
    EventRecordStopBtn.Enabled := true;
    StartGetEvent();

     ManageStartThread();
end;

function TMainForm.ManageStartThread:Boolean;  //线程开启操作
begin
     if not invenRuning then  //表示invenRuning = false
        begin
             inventTh := TInventThread.Create(true); //创建线程并挂起，所谓的构造函数
             inventTh.m_stop_timeout := DEFAULT_STOP_TIMEOUT;  //设置超时时间
             inventTh.m_ThreadStarted := true;  //设置线程启动标志为true
             inventTh.m_exit_event := CreateEvent(nil,true,false,nil);
             inventTh.m_hThread := 0;
             inventTh.m_pdwThreadId := 0;
             inventTh.m_ThreadStarted := false;
             inventTh.hreader := hreader;
             inventTh.formHandle:= self.Handle ;

             inventTh.Resume;   //唤醒线程

        end
     else
        begin
             inventTh.m_ThreadStarted := false;
        end;

end;

procedure TMainForm.StartGetEvent();
begin
    OpenBtn.Enabled := false;  //不可用
    CloseBtn.Enabled := false;  //不可用
    GetDevInfoBtn.Enabled := false;  //不可用

    CommandTabRanderClose();
end;







procedure TMainForm.EventRecordStopBtnClick(Sender: TObject);
begin
       EventRecordStopBtn.Enabled := false;  //不可用
       inventTh.SetExitVar();
end;

procedure TMainForm.EventRecordClearBtnClick(Sender: TObject);
begin
    //将列表控件所有内容进行删除
    RecordList.Items.Clear;
end;

end.
