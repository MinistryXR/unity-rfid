unit ThManage;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls,rfidlib_reader, Grids,rfidlib_def,
  CheckLst;

const
  DEFAULT_STOP_TIMEOUT = 10000;
  RFID_SEEK_FIRST = 1;
  RFID_SEEK_NEXT = 2;
  WM_LOGERROR_MSG = WM_USER+1;
  WM_COUNTNUM_MSG = WM_USER+2;
  WM_THREADEXIT_MSG = WM_USER+3;
  WM_REPORTDATA_MSG = WM_USER+4;



type
  TInventThread = class(TThread)

  public
    m_exit_flag:Boolean;   //�߳��˳���־
    m_exit_event:THandle;   //�¼����
    m_stop_timeout:integer; //�ȴ�ʱ��
    m_ThreadStarted:Boolean;   //�ж��߳��Ƿ��Ѿ�����
    m_hThread:THandle;   //�߳̾��
    m_pdwThreadId:integer; //�̺߳�
    hreader:longword;
    formHandle:HWND;


    function stop():Boolean;
    procedure SetExitVar();

  protected
    procedure Execute;override;



  end;

  type
      myData = ^TDATA;
      TDATA = record
      strData:String;
      direction:Byte;
      time:String;

  end;



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
// *** �߳̽��� ****************************************************
function TInventThread.stop():Boolean;
var
  dwRes:integer;
begin
  if m_ThreadStarted = false then
    Result := true;

  if not m_hThread = null then
    begin
        m_exit_flag := true;
        dwRes := WaitForSingleObject(m_hThread,m_stop_timeout);
        case dwRes of
           WAIT_OBJECT_0:begin
           end;
           WAIT_TIMEOUT:begin
               TerminateThread(m_hThread,0);
           end;
           else begin
           end;
         end;

         CloseHandle(m_hThread);
         m_hThread := null;
         m_pdwThreadId := 0;
    end;

    m_ThreadStarted := false;
    Result := true;
end;

procedure TInventThread.Execute;
var
  flag:Byte;
  iret:integer;
  nCount:integer;
  hTagReport:longword;
  infoBuf:array[0..64] of byte ;
  nSize:longword;
  evntType:Byte;
  direction:Byte;
  time:array[0..6] of Byte;
  dataLen:Byte;
  datout:String;
  datastrout:String;
  data:myData;
  label next_report;

begin
      //�̺߳���ִ����
      flag := 0;
      while (m_exit_flag = false) do
        begin
           iret := RDR_BuffMode_FetchRecords(hreader,flag);
           if iret <> 0 then
              begin
                 flag := 0;
                 //��ϵͳ��¼
                 SendMessage(formHandle,WM_LOGERROR_MSG,0,iret) ;
              end
           else
              begin
                  flag := 1;
                  nCount :=  RDR_GetTagDataReportCount(hreader);
                  if nCount > 0 then
                    begin
                       hTagReport :=  RDR_GetTagDataReport(hreader,RFID_SEEK_FIRST);
                       while (hTagReport <> 0) do
                          begin
                            nSize :=  sizeof(infoBuf);
                            iret := RDR_ParseTagDataReportRaw(hTagReport,@infoBuf[0],nSize);
                            if iret = 0 then
                              begin
                                if nSize < 9 then
                                  begin
                                       goto next_report;
                                  end;

                                evntType := infoBuf[0];
                                direction := infoBuf[1];
                                CopyMemory(@time[0],@infoBuf[2],6);
                                dataLen := infoBuf[8];
                                nSize := nSize - 9;
                                if nSize < dataLen then
                                  begin
                                      goto next_report;
                                  end;

                                  //ZeroMemory(@strDatas[0],sizeof(strDatas));
                                  datout := BytesToHex(@infoBuf[9],dataLen);


                                  //����Ҫ����Ϣ���ݸ�����壬���ڼ�¼��listview��
                                  datastrout := BytesToHex(@time[0],6);
                                  new(data);
                                  data.strData := datout;
                                  data.direction := direction;
                                  data.time := datastrout;

                                   SendMessage(formHandle,WM_REPORTDATA_MSG,0,lparam(data));
                              end;

                            next_report:
                            hTagReport := RDR_GetTagDataReport(hreader,RFID_SEEK_NEXT) ;
                          end;
                          //������ͳ��
                          SendMessage(formHandle,WM_COUNTNUM_MSG,0,nCount);
                    end;
              end;
        end;
   //�߳̽���
   PostMessage(formHandle,WM_THREADEXIT_MSG,0,0);

end;



procedure TInventThread.SetExitVar();
begin
    m_exit_flag := true;
    SetEvent(m_exit_event);
end;



end.
