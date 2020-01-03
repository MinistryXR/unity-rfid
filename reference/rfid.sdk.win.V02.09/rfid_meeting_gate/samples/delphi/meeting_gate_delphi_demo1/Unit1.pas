unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs,StdCtrls, ComCtrls, CheckLst,UnitInventoryThrd,rfidlib_def,rfidlib_reader;

const WM_REPORTGETTED = WM_USER + 1;
const WM_ERROROCURR = WM_USER + 2;
const WM_LOOPEXIT = WM_USER+ 3 ;
type
  TForm1 = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    GroupBox2: TGroupBox;
    Label2: TLabel;
    GroupBox3: TGroupBox;
    Label3: TLabel;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    ListView1: TListView;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Label4: TLabel;
    Memo1: TMemo;
    CheckListBox1: TCheckListBox;
    Label5: TLabel;
    Label6: TLabel;
    ComboBox3: TComboBox;
    Label7: TLabel;
    ComboBox4: TComboBox;
    Label8: TLabel;
    ComboBox5: TComboBox;
    Button7: TButton;
    Label9: TLabel;
    Label10: TLabel;
    IPEdit: TEdit;
    ComboBox1: TComboBox;
    Label11: TLabel;
    ComboBox6: TComboBox;
    ComboBox2: TComboBox;
    Label12: TLabel;
    Label13: TLabel;
    ComboBox7: TComboBox;
    ComboBox8: TComboBox;
    Button8: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure ComboBox6Change(Sender: TObject);
    procedure Button8Click(Sender: TObject);
  private
    { Private declarations }
    procedure OnMsgReportGetted(var msg:TMessage)  ;message WM_REPORTGETTED ;
    procedure OnMsgErrorOcurr(var msg :TMessage); message WM_ERROROCURR ;
    procedure OnMsgLoopExit(var msg:TMessage) ;message WM_LOOPEXIT;
  public
    { Public declarations }
    ThrdStop:TStopGetThread;
  end;

var
  Form1: TForm1;
  hreader:longword;
implementation

{$R *.dfm}


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


function  HexToBytes(szHex:string;buffer:pbyte;bfSize:integer):integer;
var
ilen:integer;
iByte:integer;
i:integer;
szByte:string;
byteHigh,byteLow:char;
hval,lval,val:Byte;
ptmp:pchar;
pbuffer:pbyte;
begin
     result:=0 ;
     pbuffer:=  buffer ;
     szHex:=UpperCase( szHex);
     ilen:=length(szHex);
     if (ilen mod 2) <> 0  then
     begin
         szHex:=szHex +'0' ;
         ilen:=ilen+1;
     end;

     iByte:=ilen div 2 ;
     if iByte > bfSize then iByte:=  bfSize ;

     for i:=0 to iByte-1 do
     begin
         szByte:=copy(szHex,(i * 2)+1,2);
         ptmp:=pchar(szByte);
         byteHigh:=ptmp^ ;
         inc(ptmp);
         byteLow:=ptmp^;
         if ( byte(byteHigh)>=$30)  and (byte(byteHigh)<= $39) then
         begin
             hval:=((Byte(byteHigh)-$30) shl 4) and $f0;

         end
         else if (byte(byteHigh) >= $41 ) and (byte(byteHigh) <=$46)  then
         begin
             hval:=((Byte(byteHigh)-$41 +$0A) shl 4) and $f0;
         end;

         if ( byte(byteLow)>=$30)  and (byte(byteLow)<= $39) then
         begin
             lval:=(Byte(byteLow)-$30)  and $0F;

         end
         else if (byte(byteLow) >= $41 ) and (byte(byteLow) <=$46)  then
         begin
             lval:=(Byte(byteLow)-$41 +$0A) and $0F;
         end;

         val:= hval or lval;

         pbuffer^:=val;

         inc(pbuffer);
     end;


     result:=i+1 ;

end;


procedure TForm1.OnMsgReportGetted(var msg:TMessage)  ;
var
i:integer;
uid:string ;
time:array[0..5] of byte ;
dataLen:byte;
eventType:byte;
direction:byte ;
iret:integer;
strDir :string;
strInstead:string ;
insteadCheckingFlag :byte;
lstitem:TListItem;

buffer:array[0..63] of byte;
dnhReport:longword;
nSize:longword;
begin
     dnhReport :=RDR_GetTagDataReport(hreader,RFID_SEEK_FIRST);
     while dnhReport<>0 do
     begin
       ZeroMemory(@buffer[0],sizeof(buffer)) ;
       nSize:= sizeof(buffer);
       iret :=RDR_ParseTagDataReportRaw(dnhReport,@buffer[0],nSize);
       if (iret = 0 ) then
       begin
           if nSize >= 9 then
           begin
              eventType := buffer[0];
              direction := buffer[1];
              for i:=0 to 5 do
              begin
                  time[i]:=buffer[2+ i] ;
              end;
              dataLen :=buffer[8] ;
              nSize := nSize -9 ;
              if nSize >= dataLen then
              begin
 			            direction:= direction and $7f;
                  if(direction =0) then
					        strDir := 'None'
		    	        else if(direction = 1) then
					          strDir := 'In'
                  else if(direction = 2) then
                    strDir :='Out'
                  else
                    strDir :='Error';

                  uid:=BytesToHex(@buffer[9],dataLen) ;
                  lstitem := ListView1.Items.Add ;
                  lstitem.Caption := uid;
                  lstitem.SubItems.Add(strDir) ;
              end;
           end;

           

		  end;
      dnhReport :=RDR_GetTagDataReport(hreader,RFID_SEEK_NEXT);
    end;
end;

procedure TForm1.OnMsgErrorOcurr(var msg :TMessage);
var
err:integer;
str :string;
begin
   err := msg.LParam ;
	 str:='Error:' + inttostr(err) ;
   memo1.Lines.Add(str) ;
end;

procedure TForm1.OnMsgLoopExit(var msg:TMessage) ;
begin
    RDR_BuffMode_StopReportCollection(hreader) ;
    
    Button4.Enabled := true;
    Button5.Enabled := false;
    Button2.Enabled := true;
    Button3.Enabled :=true;
    Button7.Enabled :=true;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
i:integer;
driverCnt:longword;
optBuf:array[0..63] of char;
nSize :longword;
iret:integer;
comCnt:longword ;
comName:array[0..128] of char;
begin
    for i:=1 to 255 do
    begin
         ComboBox3.Items.Add(inttostr(i) ) ;
         ComboBox4.Items.Add(inttostr(i) ) ;
         ComboBox5.Items.Add(inttostr(i)) ;
    end;
    ComboBox3.ItemIndex :=0 ;
    ComboBox4.ItemIndex :=0 ;
    ComboBox5.ItemIndex:= 0;

    ComboBox6.Items.Add('COM');
    ComboBox6.Items.Add('NET');
    ComboBox6.ItemIndex := 0;

    CheckListBox1.Items.Clear();
    CheckListBox1.Items.Add('���Ϸ�����');
    CheckListBox1.Items.Add('����˿�#1');
    CheckListBox1.Items.Add('����˿�#2');
    CheckListBox1.Items.Add('����˿�#3');
    CheckListBox1.Items.Add('����˿�#4');

    comCnt := COMPort_Enum();
    for i:=0 to comCnt-1 do
    begin
      ZeroMemory(@comName[0],sizeof(comName));
       nSize:=sizeof(comName) ;
       COMPort_GetEnumItem(i,comName,nSize);
       ComboBox2.Items.Add(comName) ;
    end;

    if comCnt>0 then
    begin
      ComboBox2.ItemIndex := 0;
    end;

    ComboBox7.Items.Add('9600');
    ComboBox7.Items.Add('38400');
    ComboBox7.Items.Add('57600');
    ComboBox7.Items.Add('115200');
    ComboBox7.ItemIndex := 1;

    ComboBox8.Items.Add('8E1');
    ComboBox8.Items.Add('8N1');
    ComboBox8.Items.Add('8O1');
    ComboBox8.ItemIndex := 0;

    ComboBox2.Enabled:=true;
   ComboBox7.Enabled:=true;
   ComboBox8.Enabled:=true;
   IPEdit.Enabled:=false;

    Memo1.Lines.Clear ;
    RDR_LoadReaderDrivers('.\Drivers') ;
    driverCnt:=RDR_GetLoadedReaderDriverCount() ;
    for i:=0 to driverCnt-1 do
       begin
            ZeroMemory(@optBuf[0],sizeof(optBuf));
            nSize:=sizeof(optBuf) ;
            iret:=RDR_GetLoadedReaderDriverOpt(i,LOADED_RDRDVR_OPT_CATALOG ,@optBuf[0],nSize) ;
            if iret = 0 then
            begin
                if optBuf = RDRDVR_TYPE_MTGATE then
                begin
                     ZeroMemory(@optBuf[0],sizeof(optBuf));
                     nSize:=sizeof(optBuf) ;
                     iret:=RDR_GetLoadedReaderDriverOpt(i,LOADED_RDRDVR_OPT_NAME ,@optBuf[0],nSize) ;
                     if iret = 0 then
                     begin
                          ComboBox1.Items.Add(optBuf) ;
                     end;
                     
                end;
            end;
       end;

       if driverCnt > 0 then
       begin
         ComboBox1.ItemIndex := 0;
       end



end;

procedure TForm1.Button1Click(Sender: TObject);
var
idx :integer;
iret :integer;
connstr : string  ;
begin
    idx := ComboBox6.ItemIndex;
    if (idx = -1) then
    begin
    ShowMessage('Please select COMM type');
    exit;
    end;

    if (idx = 0) then
    begin
    connstr := CONNSTR_NAME_RDTYPE +'='+ ComboBox1.Text + ';'+
                          CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_COM + ';' +
                          CONNSTR_NAME_COMNAME+'=' + ComboBox2.Text + ';'+
                          CONNSTR_NAME_COMBARUD+'='+ComboBox7.Text +';' +
                          CONNSTR_NAME_COMFRAME+'='+ComboBox8.Text +';'+
                          CONNSTR_NAME_BUSADDR+'='+'255' ;
    end
    else if(idx = 1) then
    begin
    connstr := CONNSTR_NAME_RDTYPE + '=' + ComboBox1.Text + ';' +
                          CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_NET + ';' +
                          CONNSTR_NAME_REMOTEIP + '=' + IPEdit.Text + ';' +
                          CONNSTR_NAME_REMOTEPORT + '=' + '6012'  + ';' +
                          CONNSTR_NAME_LOCALIP + '=' + '';
    end;
    iret := RDR_Open(connstr,hreader);
    if (iret = 0)  then
    begin
      Button1.Enabled := false ;
      button2.Enabled := true;
      button3.Enabled := true;
      Button4.Enabled  :=true;
      button7.Enabled := true;
      Button8.Enabled :=true ;
    end
    else
    begin
        ShowMessage('open fail');
    end;
            {idx := ComboBox1.ItemIndex;
            if (idx = -1) then
            begin
                ShowMessage('��ѡ��ͨ�Žӿ�����');
                exit;
            end;
            if (idx = 0)  then
            begin
                iret :=MG101_Open(ComboBox2.Text, 38400, '8E1',  hreader);
                CheckListBox1.Items.Clear() ;
                CheckListBox1.Items.Add('����˿�#1');
                CheckListBox1.Items.Add('����˿�#2');
                CheckListBox1.Items.Add('����˿�#3');
                CheckListBox1.Items.Add('����˿�#4');
                CheckListBox1.Items.Add('����˿�#5');
                CheckListBox1.Items.Add('����˿�#6');
                CheckListBox1.Items.Add('����˿�#7');
                CheckListBox1.Items.Add('���Ϸ�����');

                ComboBox3.Enabled := false;
                ComboBox4.Enabled := false;
                ComboBox5.Enabled := false;

            end
            else if (idx = 1)  then
            begin

                iret :=MG302_SerOpen(ComboBox2.Text, 38400, '8E1',  hreader);
                CheckListBox1.Items.Clear();
                CheckListBox1.Items.Add('���Ϸ�����');
                CheckListBox1.Items.Add('����˿�#1');
                CheckListBox1.Items.Add('����˿�#2');
                CheckListBox1.Items.Add('����˿�#3');
                CheckListBox1.Items.Add('����˿�#4');

                ComboBox3.Enabled := true;
                ComboBox4.Enabled := true;
                ComboBox5.Enabled := true;
            end
            else if (idx = 2)   then
            begin
                iret := MG302_EthOpen(IPEdit.Text, 6012, hreader);
                CheckListBox1.Items.Clear();
                CheckListBox1.Items.Add('���Ϸ�����');
                CheckListBox1.Items.Add('����˿�#1');
                CheckListBox1.Items.Add('����˿�#2');
                CheckListBox1.Items.Add('����˿�#3');
                CheckListBox1.Items.Add('����˿�#4');

                ComboBox3.Enabled := true;
                ComboBox4.Enabled := true;
                ComboBox5.Enabled := true;
            end
            else
            begin
                ShowMessage('�����ǩ��������');
                exit;
            end;
            
            if (iret = 0)  then
            begin
                Button1.Enabled := false ;
                button2.Enabled := true;
                button3.Enabled := true;
                Button4.Enabled  :=true;


                button7.Enabled := true;

              
                
            end
            else
            begin
                Showmessage('��ʧ��,����:' + inttostr(iret));
            end; }
end;

procedure TForm1.Button2Click(Sender: TObject);
var
iret :integer;
begin

            iret := RDR_Close(hreader);
            if(iret =0)  then
            begin
                button1.Enabled := true;
                button2.Enabled := false;
                button3.Enabled := false;

                button4.Enabled := false;
                button5.Enabled := false;
                button6.Enabled := false;
                button7.Enabled := false;
                Button8.Enabled :=false;
            end
            else
            begin
                Showmessage('error:' + inttostr(iret));
            end;
            hreader:= 0 ;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
iret:integer;
devInfor:array[0..63] of char ;
nSize :longword;
begin
            ZeroMemory(@devInfor[0],sizeof(devInfor));

            nSize :=sizeof(devInfor) ;
            iret := RDR_GetReaderInfor(hreader,0, devInfor,nSize);
            if (iret = 0) then 
            begin
                ShowMessage(devInfor);
            end
            else
            begin
                ShowMessage('error:' + inttostr(iret) );
            end;
end;

procedure TForm1.ComboBox1Change(Sender: TObject);
begin
      if combobox1.ItemIndex = 0 then
      begin
           ComboBox2.Enabled :=true;
           IPEdit.Enabled :=false;
      end
      else if   combobox1.ItemIndex = 1 then
      begin
           ComboBox2.Enabled :=true;
           IPEdit.Enabled :=false;
      end
      else if  combobox1.ItemIndex = 2 then
      begin
           ComboBox2.Enabled :=false;
           IPEdit.Enabled :=true;
      end;
end;

procedure TForm1.Button7Click(Sender: TObject);
var
iret:integer;
outputSel:byte;
activeTime:byte;
frequency:byte;
pausetime:byte;
i:integer;
idx:integer;
dnOutputOper:longword;
begin
            outputSel:= 0 ;
            idx:= ComboBox3.itemindex ;
            if(  idx= -1 ) then
            begin
                ShowMessage('Please select Active time');
                exit;
            end ;
            activeTime:= idx + 1;

            idx := ComboBox4.ItemIndex ;
            if(idx = -1) then
            begin
                ShowMessage('Please select frequency') ;
                exit;
            end;
            frequency:= idx +1 ;

            idx:= ComboBox5.ItemIndex ;
            if(idx = -1)  then
            begin
                ShowMessage('Please select stop time') ;
                exit;
            end;
            pausetime:=idx + 1;

            dnOutputOper := RDR_CreateSetOutputOperations();
            if(dnOutputOper=0) then
            begin
            exit;
            end;

            for i:=0  to CheckListBox1.Items.Count-1 do
            begin
                if(CheckListBox1.Checked[i])  then
                begin
                    outputSel :=(outputSel or ($01 shl i));
                    RDR_AddOneOutputOperation(dnOutputOper,i+1,3, frequency,activeTime*100,pausetime*100);
                end;
            end;
            if(outputSel = 0) then
            begin
                ShowMessage('select output port') ;
                exit;
            end;

            iret := RDR_SetOutput(hreader,dnOutputOper);
            DNODE_Destroy( dnOutputOper);
            if (iret = 0) then
            begin
                ShowMessage('ok');
            end
            else
            begin
                ShowMessage('error:' + inttostr(iret) );
            end;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin

            Button4.Enabled := false;
            Button5.Enabled := true;
            Button2.Enabled := false;
            Button3.Enabled :=false;
            Button7.Enabled :=false;
            RDR_SetEventHandler(hreader, 1, 1 {use send message}, WM_REPORTGETTED, self.Handle, nil,nil);
            RDR_SetEventHandler(hreader, 2, 1 {use send message}, WM_ERROROCURR,  self.Handle, nil,nil);
            RDR_SetEventHandler(hreader, 3, 3 {use Post message}, WM_LOOPEXIT,  self.Handle, nil,nil);
            RDR_BuffMode_StartReportCollection(hreader);

end;

procedure TForm1.Button5Click(Sender: TObject);
begin
	Button5.Enabled:= false;
  RDR_BuffMode_StopReportCollectionNoWait(hreader) ;
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
     ListView1.Items.Clear ;
end;


procedure TForm1.ComboBox6Change(Sender: TObject);
var
idx:integer;

begin
   idx := ComboBox6.ItemIndex;
   if(idx=0) then
   begin
   ComboBox2.Enabled:=true;
   ComboBox7.Enabled:=true;
   ComboBox8.Enabled:=true;
   IPEdit.Enabled:=false;
   end
   else if(idx = 1)  then
   begin
   ComboBox2.Enabled:=false;
   ComboBox7.Enabled:=false;
   ComboBox8.Enabled:=false;
   IPEdit.Enabled:=true;
   end;
end;

procedure TForm1.Button8Click(Sender: TObject);
var
iret :integer;
begin
    iret :=RDR_BuffMode_ClearRecords(hreader) ;
    if (iret = 0) then 
    begin
        ShowMessage('Clear OK') ;
    end
    else
    begin
        ShowMessage('Error:' + inttostr(iret) );
    end;
end;

end.