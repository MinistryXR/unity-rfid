unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls,rfidlib_reader,rfidlib_aip_iso15693,rfidlib_aip_iso14443a, Grids,rfidlib_def,
  CheckLst,UnitInventoryThrd;//, IPEdit;

type
  TForm1 = class(TForm)
    PageControl2: TPageControl;
    TabSheet5: TTabSheet;
    Button5: TButton;
    ListView1: TListView;
    GroupBox1: TGroupBox;
    Button1: TButton;
    Button2: TButton;
    GroupBox2: TGroupBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    Label2: TLabel;
    Edit3: TEdit;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    TabSheet6: TTabSheet;
    Button16: TButton;
    Button17: TButton;
    TabSheet7: TTabSheet;
    Edit2: TEdit;
    Button20: TButton;
    Button18: TButton;
    Button19: TButton;
    Button22: TButton;
    Button21: TButton;
    Button23: TButton;
    Button25: TButton;
    Button24: TButton;
    Label6: TLabel;
    ComboBox2: TComboBox;
    Label7: TLabel;
    ComboBox3: TComboBox;
    GroupBox3: TGroupBox;
    Button13: TButton;
    Button14: TButton;
    Button11: TButton;
    Button10: TButton;
    Button9: TButton;
    Button12: TButton;
    Button15: TButton;
    Button8: TButton;
    Edit1: TEdit;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    ComboBox4: TComboBox;
    Label11: TLabel;
    ComboBox5: TComboBox;
    Button6: TButton;
    Label12: TLabel;
    Edit5: TEdit;
    Label13: TLabel;
    Edit6: TEdit;
    Button7: TButton;
    Label14: TLabel;
    Memo1: TMemo;
    Label15: TLabel;
    Label16: TLabel;
    GroupBox4: TGroupBox;
    Label23: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
    Label27: TLabel;
    Label28: TLabel;
    Label29: TLabel;
    Label30: TLabel;
    ComboBox6: TComboBox;
    GroupBox5: TGroupBox;
    CheckListBox1: TCheckListBox;
    GroupBox6: TGroupBox;
    Button26: TButton;
    Label31: TLabel;
    ComboBox7: TComboBox;
    Button4: TButton;
    GroupBox7: TGroupBox;
    ComboBox1: TComboBox;
    Label1: TLabel;
    GroupBox8: TGroupBox;
    Label32: TLabel;
    ComboBox8: TComboBox;
    Label33: TLabel;
    ComboBox9: TComboBox;
    Label34: TLabel;
    ComboBox10: TComboBox;
    GroupBox9: TGroupBox;
    Label35: TLabel;
    Label36: TLabel;
    Edit4: TEdit;
    Edit7: TEdit;
    Label37: TLabel;
    ComboBox11: TComboBox;
    Label38: TLabel;
    ComboBox12: TComboBox;
    TabSheet1: TTabSheet;
    Label39: TLabel;
    Button3: TButton;
    Button27: TButton;
    Label40: TLabel;
    ComboBox13: TComboBox;
    Label41: TLabel;
    ComboBox14: TComboBox;
    Label42: TLabel;
    Edit9: TEdit;
    Button28: TButton;
    Label43: TLabel;
    Edit10: TEdit;
    Button29: TButton;
    Button30: TButton;
    ComboBox15: TComboBox;
    Label44: TLabel;
    Label45: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button16Click(Sender: TObject);
    procedure Button17Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button11Click(Sender: TObject);
    procedure Button12Click(Sender: TObject);
    procedure Button14Click(Sender: TObject);
    procedure Button15Click(Sender: TObject);
    procedure Button13Click(Sender: TObject);
    procedure Button18Click(Sender: TObject);
    procedure Button19Click(Sender: TObject);
    procedure Button20Click(Sender: TObject);
    procedure Button21Click(Sender: TObject);
    procedure Button22Click(Sender: TObject);
    procedure Button23Click(Sender: TObject);
    procedure Button24Click(Sender: TObject);
    procedure Button25Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure Button26Click(Sender: TObject);
    procedure ComboBox6Change(Sender: TObject);
    procedure ComboBox8Change(Sender: TObject);
    procedure ComboBox10Change(Sender: TObject);
    procedure Button27Click(Sender: TObject);
    procedure Button28Click(Sender: TObject);
    procedure Button29Click(Sender: TObject);
    procedure Button30Click(Sender: TObject);
  private
    { Private declarations }

    procedure  MsgAsyncReport(var   MSG:TMsg);message   WM_ASYNC_REPORT;
    procedure  MsgInventoryFinish(var   MSG:TMsg);message   WM_INVENTORY_FINISH;
  public
    { Public declarations }
    hreader:longword;
    htag:longword;
    htagSLIX:longword;
    htagPlus:longword;
    htagMFCL:longword;
    slix_connected:boolean;
    reader_opened:boolean;
    reader_type:integer;
    invenThrd:TInvenThread;
    invenRuning:boolean;
    procedure AddNewTag(aip_id:longword;tag_id:longword;ant_id:longword;dsfid:byte;uid:array of byte;uidlen:byte) ; 
    procedure ShowError(err:integer) ;
    procedure  SelectCommType(idx:integer) ; 
  end;

var
  Form1: TForm1;

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
procedure  TForm1.ShowError(err:integer) ;
var
ErrReaderReturn:integer;
begin
    if err =-17 {reader return error} then
    begin
        ErrReaderReturn:=RDR_GetReaderLastReturnError(hreader) ;
        showmessage('error code:'+inttostr(err)+','+inttostr(ErrReaderReturn))  ;
    end
    else
    begin
         showmessage('error code:'+inttostr(err))  ;
    end;
end;
procedure  TForm1.MsgAsyncReport(var   MSG:TMsg);
var
iret :integer;
hTagReport:longword;
aip_id:longword;
tag_id:longword;
ant_id:longword;
dsfid:byte;
uid:array[0..10] of byte ;
lstvItem:TListItem;
uidlen :byte;
begin
   hTagReport:=msg.wParam ;
   {try to parse iso15693 tag report}
   iret:=ISO15693_ParseTagDataReport(hTagReport, aip_id, tag_id ,ant_id,dsfid, @uid[0]) ;
   if(iret =0 ) then
   begin
       AddNewTag(  aip_id, tag_id ,ant_id,dsfid,uid,8) ;
   end;

   {try to parse iso14443a tag report }
   iret :=ISO14443A_ParseTagDataReport(hTagReport ,aip_id ,tag_id ,ant_id ,@uid[0],uidlen) ;
   if iret = 0 then
   begin
       AddNewTag(  aip_id, tag_id ,ant_id,0,uid,uidlen) ;
   end ;
end;

procedure TForm1.Button1Click(Sender: TObject);
var
iret :integer ;
idx :integer;
commTypeIdx:integer;
i:integer;
antCount:integer;
usbOpenType:byte;
connstr:string;
begin
     antCount :=0 ;
     idx:= ComboBox6.ItemIndex ;
     if idx = -1 then
     begin
         showmessage('please select reader type') ;
         exit;
     end;
     reader_type:= idx;

     commTypeIdx := ComboBox10.ItemIndex ;

     if  commTypeIdx = -1 then
     begin
         showmessage('please select communication type') ;
          exit;
     end;

     
     CheckListBox1.Items.Clear ;
     ComboBox7.Items.Clear ;

     if commTypeIdx = 0 then    //COM
     begin
                connstr := CONNSTR_NAME_RDTYPE +'='+ ComboBox6.Text + ';'+
                          CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_COM + ';' +
                          CONNSTR_NAME_COMNAME+'=' + ComboBox1.Text + ';'+
                          CONNSTR_NAME_COMBARUD+'='+ComboBox11.Text +';' +
                          CONNSTR_NAME_COMFRAME+'='+ComboBox12.Text +';'+
                          CONNSTR_NAME_BUSADDR+'='+'255' ;
     end
     else if commTypeIdx = 1 then   //USB
     begin
                connstr := CONNSTR_NAME_RDTYPE + '=' + ComboBox6.Text + ';' +
                          CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_USB + ';' +
                          CONNSTR_NAME_HIDADDRMODE+'='+inttostr(ComboBox8.itemIndex) +';' +
                          CONNSTR_NAME_HIDSERNUM + '=' + comboBox9.Text;
     end
     else if commTypeIdx = 2 then  //NET
     begin
                connstr := CONNSTR_NAME_RDTYPE + '=' + ComboBox6.Text + ';' +
                          CONNSTR_NAME_COMMTYPE + '=' + CONNSTR_NAME_COMMTYPE_NET + ';' +
                          CONNSTR_NAME_REMOTEIP + '=' + Edit7.Text + ';' +
                          CONNSTR_NAME_REMOTEPORT + '=' + Edit4.Text  + ';' +
                          CONNSTR_NAME_LOCALIP + '=' + '';
     end;
     iret :=RDR_Open(connstr , hreader) ;
{  // Use old way to open reader driver
     if reader_type =0 then
     begin
         iret:= ANM200_Open(ComboBox1.Text ,38400,'8E1', hreader) ;

     end
     else if reader_type = 1 then
     begin
         iret:= ANM201_Open(ComboBox1.Text ,38400,'8E1', hreader)    ;

     end
     else if  reader_type = 2 then
     begin
         iret :=ANRD201_Open(ComboBox1.Text ,38400,'8E1', hreader) ;

     end
     else if reader_type = 3 then
     begin
         iret :=ANRD5112_Open(ComboBox1.Text ,38400,'8E1', hreader) ;

     end
     else if reader_type = 4 then
     begin
         iret := ANRD242_Open(ComboBox1.Text ,38400,'8E1', hreader) ;

     end
     else if reader_type = 5 then
     begin
        if combobox8.ItemIndex =-1 then
        begin
            ShowMessage('Please select USB open type !') ;
            exit;
        end;
        usbOpenType := combobox8.ItemIndex ;
        iret := ANRD100_Open(usbOpenType,ComboBox9.Text ,hreader) ;
        antCount:=0 ;
     end
     else
     begin
         showmessage('reader type not supported');
         exit;
     end;
}
     if iret = 0 then
     begin
         Button1.Enabled :=false;
         Button4.Enabled :=true;
         Button2.Enabled :=true;
         Button5.Enabled :=true;
         Button16.Enabled :=true;
         //ShowMessage('open ok') ;
         antCount :=RDR_GetAntennaInterfaceCount(hreader) ;
         for i:=0 to antCount-1 do
         begin
              CheckListBox1.Items.Add('Antenna#'+inttostr(i+1)) ;
              ComboBox7.Items.Add('Antenna#'+inttostr(i+1)) ;
         end;
         Button26.Enabled :=false;
         ComboBox7.Enabled :=false;
         CheckListBox1.Enabled := false;
         if antCount > 1 then
         begin
             Button26.Enabled :=true;
             ComboBox7.Enabled :=true;
             CheckListBox1.Enabled := true;
         end;
         reader_opened:=true;
     end
     else
     begin
         ShowMessage('open fail');
     end;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
iret :integer;
uid:array[0..9] of byte;
begin


     if ComboBox15.ItemIndex=-1 then
     begin
         ShowMessage('select UID ,please') ;
         exit;
     end;

     HexToBytes(ComboBox15.Text  ,@uid[0],sizeof(uid)) ;
     iret:= MFCL_Connect(hreader,0,@uid[0],htagMFCL) ;
     if(iret = 0) then
     begin
         //showmessage('ok') ;
     
          Button3.Enabled :=false;
          Button27.Enabled :=true;
     end
     else
     begin
         ShowError(iret);
     end;

end;

procedure TForm1.Button2Click(Sender: TObject);
var
iret :integer;
i:integer;
begin

     iret:= RDR_Close(hreader) ;
     {  // use old way to close reader driver
     if reader_type =0 then
        iret :=  ANM200_Close(hreader)
     else if reader_type = 1 then
        iret:=ANM201_Close(hreader)
     else if reader_type= 2 then
        iret:=ANRD201_Close(hreader)
     else if reader_type = 3 then
        iret :=ANRD5112_Close(hreader)
     else if reader_type = 4 then
        iret :=ANRD242_Close(hreader)

     else if reader_type = 5 then
        iret := ANRD100_Close(hreader)
     else
     begin
         showmessage('reader type not supported ') ;
         exit;
     end;
     }
     if iret = 0 then
     begin
          //ShowMessage('ok');
         Button1.Enabled :=true;
         Button4.Enabled :=false;
         Button2.Enabled :=false;
         Button5.Enabled :=false;
         Button16.Enabled :=false;
         reader_opened:=false;
         hreader :=0 ;
     end
     else
     begin
          ShowMessage('fail');
     end;
end;

procedure TForm1.Button4Click(Sender: TObject);
var

infoBuf:array[0..128] of char ;
iret :integer;
nSize:longword ;
begin
     nSize := sizeof(infoBuf) ;
     ZeroMemory(@infoBuf[0],nSize) ;
     //iret := ANRDXX_GetCapabilities(hreader,infoBuf,nSize) ;
     iret :=RDR_GetReaderInfor(hreader,0, infoBuf,nSize) ;
     if(iret = 0) then
     begin
          ShowMessage( infoBuf);
     end
     else
     begin
          ShowMessage('fail') ;
     end;

end;
procedure  TForm1.MsgInventoryFinish(var   MSG:TMsg);
begin
     invenThrd.WaitFor ;
     invenThrd.Destroy() ;
     Button5.Caption :='Start Inventory' ;
     Button5.Enabled :=true;

     Button2.Enabled :=true;
     Button4.Enabled :=true;
     Button16.Enabled :=true;
     Button18.Enabled :=true;
     invenRuning:=false;
end;

procedure TForm1.AddNewTag(aip_id:longword;tag_id:longword;ant_id:longword;dsfid:byte;uid:array of byte;uidlen:byte) ;
var
lstvItem:TListItem;
tagType:string;
struid:string;
strDSFID:string;
i:integer;
tagFound:boolean;
begin

    if aip_id = RFID_APL_ISO15693_ID then
    begin
          if tag_id =RFID_ISO15693_PICC_ICODE_SLI_ID then
             tagtype := 'NXP ICODE SLI'
          else if tag_id = RFID_ISO15693_PICC_TI_HFI_PLUS_ID then
             tagtype:= 'Tag-it HF-I plus'
          else if tag_id = RFID_ISO15693_PICC_FUJ_MB89R118C_ID then
              tagtype:='Fujitsu MB89R118C'
          else if  tag_id= RFID_ISO15693_PICC_ST_M24LR64_ID then
              tagtype:='ST M24LR64'
          else if tag_id = RFID_ISO15693_PICC_ST_M24LR16E_ID then
              tagtype := 'ST M24LR16E'
          else if tag_id = RFID_ISO15693_PICC_ICODE_SLIX_ID then
              tagtype := 'NXP ICODE SLIX'
          else if tag_id = RFID_ISO15693_PICC_TIHFI_STANDARD_ID then
              tagtype :='Tag-it HF-I Standard'
          else if tag_id= RFID_ISO15693_PICC_TIHFI_PRO_ID then
              tagtype := 'Tag-it HF-I Pro'
          else
              tagtype:='Unknown tag';
    end
    else if aip_id = RFID_APL_ISO14443A_ID then
    begin
          if tag_id =RFID_ISO14443A_PICC_NXP_ULTRALIGHT_ID then
             tagtype := 'Mifare ultralight'
          else if tag_id = RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID then
             tagtype:= 'Mifare S50'
          else if tag_id = RFID_ISO14443A_PICC_NXP_MIFARE_S70_ID then
              tagtype:='Mifare S70'
          else
              tagtype:='Unknown tag';
    end
    else
    begin
         tagtype:='Unknown tag';
    end ;

    tagFound:=false;
    struid:=BytesToHex(@uid[0], uidlen) ;
    strDSFID:= BytesToHex(@dsfid,1) ;
    for i:=0 to ListView1.Items.Count-1 do
    begin
        if(  ListView1.Items[i].SubItems[0] =  struid ) then
        begin
              tagFound:=true;
              break;
        end ;
    end;
    if( not tagFound)  then
    begin
    lstvItem:=ListView1.Items.Add ;
    lstvItem.Caption := tagtype;
    lstvItem.SubItems.Add(struid) ;
    lstvItem.SubItems.Add(strDSFID) ;
    lstvItem.SubItems.Add(inttostr(ant_id)) ;
    lstvItem.SubItems.Add('1');

    if aip_id = RFID_APL_ISO15693_ID then
    begin
       ComboBox3.Items.Add(struid) ;
    end
    else if aip_id = RFID_APL_ISO14443A_ID then
    begin
        ComboBox15.Items.Add(struid);
    end;


    end
    else
    begin
    ListView1.Items[i].SubItems[3]:=inttostr( strtoint(ListView1.Items[i].SubItems[3]) + 1) ;
    end;

    
    Label5.Caption := inttostr(ListView1.Items.Count) ;
end;

procedure TForm1.Button5Click(Sender: TObject);
var
iret :integer;

AsyncOutput:boolean;
AIType :byte;
AFIEnabled:byte;
afi:byte;
i:integer;

label label_inventory;
begin
      if not invenRuning then
      begin
          ListView1.Items.Clear ;
          ComboBox3.Items.Clear ;
          ComboBox15.Items.Clear ;
          Label5.Caption :='0' ;
          invenThrd := TInvenThread.Create(true);
          {
          invenThrd.ISO15693En :=ckbISO15693En.Checked ;
          invenThrd.ISO14443aEn := ckbISO14443aEn.Checked;
          }
          invenThrd.stopFlag := false;
          invenThrd.antcount := 0;
          for i:= 0 to CheckListBox1.Items.Count -1 do
          begin
              if(CheckListBox1.Checked[i]) then
              begin
                   invenThrd.antennas[invenThrd.antcount]:= i+ 1;
                   invenThrd.antcount:= invenThrd.antcount+1;
              end;
          end;
          invenThrd.hreader :=hreader;
          invenThrd.onlyNewTag :=CheckBox2.Checked;
          invenThrd.checkAFI:= 0 ;
          if CheckBox3.Checked  then
          begin
             invenThrd.checkAFI:= 1 ;
          end;
          HexToBytes(Edit3.Text ,@invenThrd.afiVal,1)  ;
          invenThrd.formHandle:= self.Handle ;
          invenThrd.Resume ;
          invenRuning:= true;
          Button5.Caption := 'Stop Inventory' ;
          Button2.Enabled :=false;
          Button4.Enabled :=false;
          Button16.Enabled :=false;
          Button18.Enabled :=false;
      end
      else
      begin
          Button5.Enabled :=false;
          invenThrd.stopFlag:= true;

          //RDR_TagInventory exit Immediately
          RDR_SetCommuImmeTimeout(hreader);  
      end;
end;
procedure report_callback(wparam:longword;lparam:longword); stdcall;
begin
    Showmessage('callbac') ;
end;

procedure TForm1.Button6Click(Sender: TObject);
var
iret:integer;
secBuffer:array[0..63]of byte;
nSize:longword;
bytesRead:longword;
blkNum:longword;
startBlock:longword;
idx :integer;
begin
     idx :=ComboBox4.ItemIndex ;
     if idx = -1 then
     begin
         ShowMessage('select block address ,please') ;
         exit;
     end; 
     startBlock:=idx  ;
     idx:=ComboBox5.ItemIndex ;
     if idx = -1 then
     begin
         ShowMessage('select number of blocks to read ,please') ;
         exit;
     end;
     blkNum:=idx+1;
     nSize:= sizeof(secBuffer);
     bytesRead:= 0 ;
     iret := ISO15693_GetBlockSecStatus(hreader,htagSLIX,startBlock,blkNum,@secBuffer[0], nSize,bytesRead );
     if iret = 0 then
     begin
           edit1.Text :=BytesToHex(@secBuffer[0], bytesRead);
     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button7Click(Sender: TObject);
var
dsfid:byte;
iret:integer;
begin
    HexToBytes( Edit6.Text ,@dsfid,1) ;
    iret:=ISO15693_WriteDSFID(hreader,htagSLIX,  dsfid) ;
    if iret = 0 then
    begin
        showmessage('ok') ;
    end
    else
    begin
        ShowError(iret);
    end;
end;

procedure TForm1.Button8Click(Sender: TObject);
var
iret :integer;
block:array[0..4] of byte;     //5 bytes
nSize:longword;
bytesRead:longword;
startBlock:longword;
numOfBlks: longword;

idx :integer;
begin
     idx :=ComboBox4.ItemIndex ;
     if idx = -1 then
     begin
         ShowMessage('select block address ,please') ;
         exit;
     end;
     startBlock:=idx  ;

     idx :=ComboBox5.ItemIndex;
     if idx = -1 then
     begin
         ShowMessage('select block address ,please') ;
         exit;
     end;
     numOfBlks :=idx+1;

     nSize:=sizeof(block) ;

     iret:=ISO15693_LockMultipleBlocks(hreader,htagSLIX,startBlock,numOfBlks) ;
     if(iret =0) then
     begin
        ShowMessage('Lock Multi blocks successfully') ;
     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button16Click(Sender: TObject);
var
iret :integer;
uid:array[0..7] of byte;
addrMode:byte;
idx :integer;
begin
     idx:= ComboBox2.ItemIndex ;
     if idx = -1 then
     begin
         ShowMessage('select address mode ,please') ;
         exit;
     end;
     addrMode:= idx;
     if addrMode =1 then    // Addressed mode
     begin
         if ComboBox3.ItemIndex=-1 then
         begin
             ShowMessage('select UID ,please') ;
             exit;
         end;
     end;
     HexToBytes(ComboBox3.Text  ,@uid[0],8) ;
     iret:= ISO15693_Connect(hreader,RFID_ISO15693_PICC_ICODE_SLIX_ID,1,@uid[0],htagSLIX) ;
     if(iret = 0) then
     begin
         //showmessage('ok') ;
          Button16.Enabled :=false;
          Button17.Enabled :=true;
          Button8.Enabled :=true;
          Button9.Enabled :=true;
          Button12.Enabled :=true;
          Button7.Enabled :=true;
          Button14.Enabled :=true;
          Button15.Enabled :=true;
          Button13.Enabled :=true;
          Button10.Enabled :=true;
          Button6.Enabled :=true;
          Button11.Enabled :=true;

          slix_connected:=true;
     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button17Click(Sender: TObject);
var
iret :integer;
begin
     iret:= RDR_TagDisconnect(hreader,htagSLIX) ;
     if(iret= 0) then
     begin
          Button16.Enabled :=true;
          Button17.Enabled :=false;
          Button8.Enabled :=false;
          Button9.Enabled :=false;
          Button12.Enabled :=false;
          Button7.Enabled :=false;
          Button14.Enabled :=false;
          Button15.Enabled :=false;
          Button13.Enabled :=false;
          Button10.Enabled :=false;
          Button6.Enabled :=false;
          Button11.Enabled :=false;
          htagSLIX:=0 ;
          slix_connected:=false;
     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button10Click(Sender: TObject);
var
iret :integer;
block:array[0..31] of byte;
nSize:longword;
blkNumToRead:longword;
blkNumRead:longword;
startBlock:byte;
bytesRead:longword;
idx :integer;
begin
     idx :=ComboBox4.ItemIndex ;
     if idx = -1 then
     begin
         ShowMessage('select block address ,please') ;
         exit;
     end; 
     startBlock:=idx  ;
     idx:=ComboBox5.ItemIndex ;
     if idx = -1 then
     begin
         ShowMessage('select number of blocks to read ,please') ;
         exit;
     end;
     blkNumToRead:=idx+1;
     nSize:=sizeof(block) ;
     blkNumRead :=0 ;
     iret:= ISO15693_ReadMultiBlocks(hreader,htagSLIX,0,startBlock,blkNumToRead,blkNumRead,@block[0], nSize,bytesRead) ;
     if(iret =0) then
     begin
          edit1.Text :=BytesToHex(@block[0],bytesRead) ;
     end
     else
     begin
        ShowError(iret);
     end;

end;

procedure TForm1.Button9Click(Sender: TObject);
var
iret :integer;
db:array[0..31] of byte;
startBlock:longword;
numOfBlks:longword;
idx :integer;
begin
     idx :=ComboBox4.ItemIndex ;
     if idx = -1 then
     begin
         ShowMessage('select block address ,please') ;
         exit;
     end; 
     startBlock:=idx  ;
     numOfBlks := ComboBox5.ItemIndex+1 ;
     //db[0]:=$aa;
     //db[1]:=$bb;
     //db[2]:=$cc;
     //db[3]:=$dd;
     HexToBytes(Edit1.Text ,@db[0],sizeof(db)) ;
    //iret:= ISO15693_WriteSingleBlock(hreader,htagSLIX,startBlock,@db[0]{4 bytes data},4) ;
    iret:=ISO15693_WriteMultipleBlocks(hreader,htagSLIX,startBlock,numOfBlks,@db[0],4*numOfBlks);
    if(iret =0) then
    begin
          ShowMessage('ok') ;
    end
    else
    begin
          ShowError(iret);
    end;
end;

procedure TForm1.Button11Click(Sender: TObject);
var
iret :integer;
uid:array[0..7] of byte;
dsfid,afi,icref:byte;
blkSize,blkNum:longword;
begin
    dsfid:=0 ;
    afi:=0 ;
    blkSize:=0 ;
    blkNum:=0 ;
    icref:= 0;
    iret:= ISO15693_GetSystemInfo(hreader,htagSLIX,@uid[0], dsfid, afi ,blkSize ,blkNum, icref) ;
    if iret = 0 then
    begin
         ShowMessage('ok') ;
         Label24.Caption :=BytesToHex(@uid[0],8) ;
         Label25.Caption := BytesToHex(@afi,1)+'h' ;
         Label26.Caption := BytesToHex(@dsfid,1)+'h' ;
         Label27.Caption := inttostr(blkSize);
         Label28.Caption :=inttostr( blkNum) ;
         Label29.Caption := BytesToHex(@icref,1)+'h' ;

    end
    else
    begin
         ShowError(iret);
    end;
end;

procedure TForm1.Button12Click(Sender: TObject);
var
iret :integer;
afi:byte;
begin
    HexToBytes(Edit5.Text ,@afi,1) ;
    iret:= ISO15693_WriteAFI(hreader,htagSLIX,afi) ;
    if iret = 0 then
    begin
         ShowMessage('ok') ;
    end
    else
    begin
        ShowError(iret);
    end;
end;

procedure TForm1.Button14Click(Sender: TObject);
var
iret :integer;
begin
    iret:=NXPICODESLIX_EableEAS(hreader,htagSLIX) ;
    if(iret =0) then
    begin
         showmessage('ok') ;
    end
    else
    begin
        ShowError(iret);
    end; 
end;

procedure TForm1.Button15Click(Sender: TObject);
var
iret:integer;
begin
     iret:= NXPICODESLIX_DisableEAS(hreader,htagSLIX) ;
     if(iret =0 ) then
     begin
          showmessage('ok') ;
     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button13Click(Sender: TObject);
var
iret:integer;
EASStatus:byte;
begin
 
     Memo1.Lines.Text :='' ;
     iret:=NXPICODESLIX_EASCheck(hreader,htagSLIX,EASStatus ) ;
     if(iret=0) then
     begin
          if(EASStatus =0) then
          begin
             Memo1.Lines.Text :='EAS is closed' ;
          end
          else
          begin
             Memo1.Lines.Text :='EAS is open' ;
          end;

     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button18Click(Sender: TObject);
var
iret :integer;
uid:array[0..7] of byte;
begin
     if( ListView1.Selected = nil) then
     begin
         showmessage('select uid');
         exit ;
     end;
     HexToBytes( ListView1.Selected.SubItems[0] ,@uid[0],8) ;
     iret:= ISO15693_Connect(hreader,RFID_ISO15693_PICC_TI_HFI_PLUS_ID,1,@uid[0],htagPlus) ;
     if(iret = 0) then
     begin
         showmessage('ok') ;
     end
     else
     begin
          ShowError(iret);
     end;

end;

procedure TForm1.Button19Click(Sender: TObject);
var
iret :integer;
begin
     iret:= RDR_TagDisconnect(hreader,htagPlus) ;
     if(iret= 0) then
     begin
         showmessage('ok') ;
         htagPlus:=0 ;
     end
     else
     begin
         ShowError(iret);
     end;

end;

procedure TForm1.Button20Click(Sender: TObject);
var
iret :integer;
block:array[0..4] of byte;
nSize:longword;
bytesRead:longword;
blockToRead:longword;
begin
     blockToRead:=0 ;
     nSize:=sizeof(block) ;
     iret:= ISO15693_ReadSingleBlock(hreader,htagPlus,1,blockToRead,@block[0], nSize,bytesRead) ;
     if(iret =0) then
     begin
          edit2.Text :=BytesToHex(@block[0],nSize) ;
     end
     else
     begin
         ShowError(iret);
     end;

end;

procedure TForm1.Button21Click(Sender: TObject);
var
iret :integer;
block:array[0..31] of byte;
nSize:longword;
blkNumToRead:longword;
blkNumRead:longword;
bytesRead:longword;
begin
     nSize:=sizeof(block) ;
     blkNumToRead:=2;
     blkNumRead:= 0;
     iret:= ISO15693_ReadMultiBlocks(hreader,htagPlus,1,0,blkNumToRead,blkNumRead,@block[0], nSize,bytesRead) ;
     if(iret =0) then
     begin
          edit2.Text :=BytesToHex(@block[0],bytesRead) ;
     end
     else
     begin
          ShowError(iret);
     end;

end;

procedure TForm1.Button22Click(Sender: TObject);
var
iret :integer;
db:array[0..7] of byte;
begin
    db[0]:=$11;
    db[1]:=$22;
    db[2]:=$33;
    db[3]:=$44;
    iret:= ISO15693_WriteSingleBlock(hreader,htagPlus,0,@db[0],4) ;
    if(iret =0) then
    begin
          ShowMessage('ok') ;
    end
    else
    begin
           ShowError(iret);
    end;

end;

procedure TForm1.Button23Click(Sender: TObject);
var
iret :integer;
uid:array[0..7] of byte;
dsfid,afi,icref:byte;
blkSize,blkNum:longword;
begin
    dsfid:=0 ;
    afi:=0 ;
    blkSize:=0 ;
    blkNum:=0 ;
    icref:= 0;
    iret:= ISO15693_GetSystemInfo(hreader,htagPlus,@uid[0], dsfid, afi ,blkSize ,blkNum, icref) ;
    if iret = 0 then
    begin
         ShowMessage('ok') ;
    end
    else
    begin
          ShowError(iret);
    end;

end;

procedure TForm1.Button24Click(Sender: TObject);
var
iret:integer;
dbtwo:array[0..15] of byte;
begin

end;

procedure TForm1.Button25Click(Sender: TObject);
var
iret:integer;
begin

end;

procedure TForm1.SelectCommType(idx:integer) ;
begin
     if idx =0 then
     begin
         ComboBox1.Enabled :=true;
         Edit7.Enabled :=false;
         Edit4.Enabled :=false;
         ComboBox8.Enabled :=false;
         ComboBox9.Enabled :=false;
     end
     else if idx = 1 then
     begin
         ComboBox1.Enabled :=false;
         Edit7.Enabled :=false;
         Edit4.Enabled :=false;
         ComboBox8.Enabled :=true;
         ComboBox9.Enabled :=true;
     end
     else if idx = 2 then
     begin
         ComboBox1.Enabled :=false;
         Edit7.Enabled :=true;
         Edit4.Enabled :=true;
         ComboBox8.Enabled :=false;
         ComboBox9.Enabled :=false;
     end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
driverCnt:longword;
portCnt:longword;
i:integer;
iret:integer;
nSize :longword;
optBuf:array[0..63] of char;
portBuf:array[0..31] of char;
begin
       slix_connected:=false;
       reader_opened:=false;
       reader_type :=-1;
       invenRuning :=false;

       // Load all reader driver
       RDR_LoadReaderDrivers('\Drivers') ;
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
                          ComboBox6.Items.Add(optBuf) ;
                     end;
                     
                end;
            end;
       end;

       portCnt := COMPort_Enum() ;
       for i:=0 to portCnt-1 do
       begin
            ZeroMemory(@portBuf[0],sizeof(portBuf));
            iret :=COMPort_GetEnumItem(i,portBuf , sizeof(portBuf)) ;
            if iret = 0 then
            begin
                 ComboBox1.Items.Add(portBuf) ;
            end;
       end;
       if(ComboBox1.Items.Count > 0) then ComboBox1.ItemIndex:=0 ;
       if ComboBox6.Items.Count > 0 then ComboBox6.ItemIndex:= 0 ;
       ComboBox10.ItemIndex:=0 ;
       SelectCommType(ComboBox10.ItemIndex) ;

       ComboBox11.Items.Add('9600');
       ComboBox11.Items.Add('38400');
       ComboBox11.Items.Add('57600');
       ComboBox11.Items.Add('115200');
       ComboBox11.ItemIndex:=1;

       ComboBox12.Items.Add('8E1');
       ComboBox12.Items.Add('8N1');
       ComboBox12.Items.Add('8O1');
       ComboBox12.ItemIndex:=0;

       htag:=0 ;
       htagSLIX:=0 ;
       htagMFCL :=0 ;
       htagPlus:=0 ;
end;

procedure TForm1.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
     if reader_opened then
     begin
           Showmessage('close reader before exit') ;
           CanClose:= false;
           exit;
     end;
end;

procedure TForm1.Button26Click(Sender: TObject);
var
accessAnt:byte;
iret :integer;
begin
     if ComboBox7.ItemIndex = -1 then
     begin
         ShowMessage('Please select access antenna number!') ;
         exit ;
     end;
     accessAnt := ComboBox7.ItemIndex+1 ;
     iret := RDR_SetAcessAntenna(hreader,accessAnt) ;
     if( iret <> 0) then
     begin
          ShowError(iret);
          exit;
     end;
     ShowMessage('ok') ;
end;

procedure TForm1.ComboBox6Change(Sender: TObject);
var
nCount:longword;
i:integer;

iret :integer;
sernum:array[0..63] of char;
nSize:longword;
begin
      ComboBox9.Items.Clear;
      nCount:= HID_Enum(ComBoBox6.Text );
      for i:=0 to nCount -1 do
      begin
         ZeroMemory(@sernum[0],sizeof(sernum));
         nSize :=sizeof(sernum) ;
         iret := HID_GetEnumItem(i,HID_ENUM_INF_TYPE_SERIALNUM ,sernum  ,nSize) ;
         if iret= 0 then
         begin
              ComboBox9.Items.Add(sernum) ;
         end;
      end;
end;

procedure TForm1.ComboBox8Change(Sender: TObject);
begin
       if   ComboBox8.ItemIndex =0 then
       begin
             ComboBox9.Enabled := false;
       end
       else
       begin
             ComboBox9.Enabled := true;
       end;
end;

procedure TForm1.ComboBox10Change(Sender: TObject);
begin
      SelectCommType(ComboBox10.ItemIndex ) ;
end;

procedure TForm1.Button27Click(Sender: TObject);
var
iret:integer;
begin
    iret:= RDR_TagDisconnect(hreader,htagMFCL) ;
     if(iret= 0) then
     begin
          htagMFCL:=0 ;
          Button3.Enabled :=true;
          Button27.Enabled :=false;
     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button28Click(Sender: TObject);
var
blockAddr:Byte ;
keytype :byte;
iret :integer;
key:array[0..31] of byte;
begin
     if ComboBox13.ItemIndex =-1 then
     begin
          showmessage('please select block address') ;
          exit ;
     end ;
     blockAddr := ComboBox13.ItemIndex ;
     if ComboBox14.ItemIndex  =-1 then
     begin
          showmessage('please select key type') ;
          exit ;
     end;
     keytype :=ComboBox14.ItemIndex ;

     HexToBytes(Edit9.Text ,@key[0],sizeof(key)) ;

     iret :=MFCL_Authenticate(hreader,htagMFCL,blockAddr,keytype ,@key[0])   ;
     if iret =0 then
     begin
         showmessage('ok') ;
     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button29Click(Sender: TObject);
var
iret:integer;
blockAddr:Byte ;
blkBuf:array[0..16] of byte;
begin
     if ComboBox13.ItemIndex =-1 then
     begin
          showmessage('please select block address') ;
          exit ;
     end ;
     blockAddr := ComboBox13.ItemIndex ;
     iret :=MFCL_ReadBlock(hreader, htagMFCL ,blockAddr,@blkBuf[0] ,sizeof(blkBuf)) ;
     if iret =0 then
     begin
         Edit10.Text :=BytesToHex(@blkBuf[0],16) ;
     end
     else
     begin
         ShowError(iret);
     end;
end;

procedure TForm1.Button30Click(Sender: TObject);
var
iret:integer;
blockAddr:Byte ;
blkBuf:array[0..16] of byte;
begin
     if ComboBox13.ItemIndex =-1 then
     begin
          showmessage('please select block address') ;
          exit ;
     end ;
     blockAddr := ComboBox13.ItemIndex ;

     HexToBytes(Edit10.Text ,@blkBuf[0],sizeof(blkBuf)) ;
     iret :=MFCL_WriteBlock(hreader, htagMFCL ,blockAddr,@blkBuf[0]) ;
     if iret =0 then
     begin
         ShowMessage('ok') ;
     end
     else
     begin
         ShowError(iret);
     end;
end;

end.
