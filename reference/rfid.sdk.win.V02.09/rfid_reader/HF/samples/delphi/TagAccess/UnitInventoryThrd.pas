unit UnitInventoryThrd;

interface
uses    Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls,rfidlib_reader,rfidlib_aip_iso15693,rfidlib_aip_iso14443a, Grids,rfidlib_def,
  CheckLst;
const
WM_ASYNC_REPORT = WM_USER+1;
WM_INVENTORY_FINISH = WM_USER + 2;
type
  TInvenThread = class(TThread)
  public
  antennas:array[0..15] of byte;
  antcount:byte;
  hreader:longword ;
  onlyNewTag:boolean;
  checkAFI:byte;
  afiVal:byte;
  stopFlag:boolean;
  formHandle:HWND ;
  ISO15693En:boolean ;
  ISO14443aEn:boolean;
  protected

  procedure Execute; override;

  end;
implementation

procedure TInvenThread.Execute;
var
iret :integer;
hInvenParamList:longword;

nTagCount:longword;
hTagReport:longword;
aip_id:longword;
tag_id:longword;
ant_id:longword;
dsfid:byte;
uid:array[0..7] of byte ;
i:integer;
AIType:byte;


label label_inventory;
begin

{
      hInvenParamList:= RDR_CreateInvenParamSpecList();
      if(   hInvenParamList <>  0) then
      begin
          if ISO15693En  then
          begin
             ISO15693_CreateInvenParam(hInvenParamList, 0,checkAFI,afiVal,0) ;
          end;
          if ISO14443aEn then
          begin
             ISO14443A_CreateInvenParam(  hInvenParamList, 0) ;
          end;
      end;
}
      hInvenParamList:=0 ; //use default parameters

      while( stopFlag = false ) do
      begin
            AIType:= 1;
            if(onlyNewTag ) then
            begin
                AIType:= 2;
            end;
            nTagCount:= 0;
label_inventory:
            iret := RDR_TagInventory(hreader,AIType,antcount,@antennas[0], hInvenParamList) ;
            if((iret = 0) or (iret =-21))  then
            begin
                  nTagCount:=nTagCount+RDR_GetTagDataReportCount(hreader) ;
                  hTagReport :=RDR_GetTagDataReport(hreader,1 ) ;  //seek first
                  while(  hTagReport<> 0) do
                  begin
                           SendMessage(formHandle,WM_ASYNC_REPORT,0,hTagReport) ;
                           hTagReport :=RDR_GetTagDataReport(hreader,2 ) ; //seek next
                  end;


                  if iret = -21 then  // inventory stop trigger occurs ,use  Only new tag inventory to get left tags
                  begin
                      AIType:=2 ; //Only new tag inventory
                      goto label_inventory ;
                  end;
            end
            else
            begin
                //inventory fail
            end;

      end;
      DNODE_Destroy(hInvenParamList) ;
      {
      /*
     *  If API RDR_SetCommuImmeTimeout is called when stop, API RDR_ResetCommuImmeTimeout
     *  must be called too, Otherwise, an error -5 may occurs .
     */
      }
      RDR_ResetCommuImmeTimeout(hreader) ;
      
      PostMessage(formHandle,WM_INVENTORY_FINISH,0,0) ;
end;
end.
