// DlgInventory.cpp : 实现文件
//

#include "stdafx.h"
#include "rfidlib.h"
#include "demo_m24rl64.h"
#include "DlgInventory.h"
#include "gfunctions.h"
#include "rfidlib_reader.h"
#include "rfidlib_aip_iso15693.h"
#include "rfidlib_aip_iso14443a.h"
#include "rfidlib_aip_iso18000p3m3.h"
#include "dlgadvance.h"


#define WM_INVENOTYR_STOPPED		WM_USER + 1
#define WM_REPORT					WM_USER+2
#define WM_PROTOLOG					WM_USER + 3

typedef void (*CB_TAG_REPORT_HANDLE)(void *cbParam,RFID_READER_HANDLE hreader,DWORD AIPtype,DWORD TagType,DWORD AntId,BYTE uid[],WORD uidlen) ;
void cb_handle_tag_report(void *cbParam,RFID_READER_HANDLE hreader,DWORD AIPtype,DWORD TagType,DWORD AntId,BYTE uid[],WORD uidlen)
{
	CDlgInventory *pdlg ;
	CString tagtypeName ;
	CString AIPName;
	err_t iret;

	// Get air protocol name 
	AIPName.Preallocate(64) ;
	memset(AIPName.GetBuffer(0) ,0x00,AIPName.GetAllocLength());
	DWORD nSize  =AIPName.GetAllocLength() ;
	iret = RDR_GetAIPTypeName(hr,AIPtype,AIPName.GetBuffer(0),&nSize) ;
	if(iret != 0) {
		AIPName=_T("Unknown");
	}
	
	// Get tag type name
	tagtypeName.Preallocate(64) ;
	memset(tagtypeName.GetBuffer(0),0x00,tagtypeName.GetAllocLength());
	nSize =tagtypeName.GetAllocLength() ;
	iret =RDR_GetTagTypeName(hr,AIPtype,TagType,tagtypeName.GetBuffer(0),&nSize) ;
	if(iret !=0) {
		tagtypeName=_T("Unknown") ;
	}
	
	pdlg =(CDlgInventory *)cbParam ;

	TCHAR suid[32] ;
	memset(suid,0,sizeof(suid));
	BytesToHexStr(uid,uidlen,suid) ;	
	CString sAntId ;
	sAntId.Format(_T("%d"),AntId) ;
	INT32 i ;

	//to find uid .
	for( i=0;i<m_taglist.GetCount();i++) {
		if(m_taglist[i].m_uid ==suid && m_taglist[i].m_antNo == AntId) {
			break;
		}
	}

	if(i>=m_taglist.GetCount()) {
		/* it is a new tag ,then add to list */
		CTag newtag;
		newtag.m_counter = 1;
		newtag.m_uid =suid ;
		newtag.m_type = TagType;
		newtag.m_antNo =AntId ;
		newtag.m_AIP =AIPtype  ;
		m_taglist.Add(newtag) ;
		int nRow=pdlg->m_listTagData.InsertItem(m_taglist.GetCount()-1,AIPName);        //插入行
		pdlg->m_listTagData.SetItemText(nRow,1,tagtypeName) ;
		pdlg->m_listTagData.SetItemText(nRow,2,suid) ;
		pdlg->m_listTagData.SetItemText(nRow,3,sAntId) ;
		pdlg->m_listTagData.SetItemText(nRow,4,_T("1"));
	}
	else{
		/* the tag is exist ,then only update found counter */
		m_taglist[i].m_counter++ ;
		if(m_taglist[i].m_counter>=500000)
		{
			m_taglist[i].m_counter = 1;
		}
		CString sc ;
		sc.Format(_T("%d"),m_taglist[i].m_counter) ;
		pdlg->m_listTagData.SetItemText(i,4,sc) ;
	}

	/* update total found */
	CString strTotal;
	strTotal.Format(_T("%d"),m_taglist.GetCount()) ;
	pdlg->m_staTotal.SetWindowText(strTotal) ;

	///* read or write tag */
	//err_t iret;
	//RFID_TAG_HANDLE htag =NULL;
	//if(AIPtype ==RFID_APL_ISO15693_ID ){
	//	/* ISO15693 tag access example code  */
	//	iret = ISO15693_Connect(hreader,TagType,1,uid,&htag) ;
	//	if(iret == 0) {
	//		/* read multiple blocks */
	//		DWORD numOfBlksRead =0;
	//		DWORD bytesDataRead =0 ;
	//		BYTE bufBlocks[64] ;
	//		iret = ISO15693_ReadMultiBlocks(hreader,htag,TRUE,0,4,&numOfBlksRead,bufBlocks,sizeof(bufBlocks),&bytesDataRead) ;
	//		if(iret ==0){
	//			/* read ok */
	//		}
	//		/* other operations */

	//		/* disconnect from tag */
	//		RDR_TagDisconnect(hreader,htag ) ;
	//	}
	//}
	//else if(AIPtype == RFID_APL_ISO14443A_ID){
	//	/* mifare s50 tag access example code */
	//	iret =MFCL_Connect(hreader,0,uid,&htag) ;
	//	if(iret == 0){
	//		BYTE blkData[16] ;
	//		iret = MFCL_ReadBlock(hreader,htag,0,blkData,sizeof(blkData)) ;
	//		if(iret == 0){
	//			/* read block ok */
	//		}
	//		/* disconnect from tag */
	//		RDR_TagDisconnect(hreader,htag ) ;
	//	}

	//}
}

/*
* multiple air protocol inventory
*/
err_t rfid_inventory(RFID_READER_HANDLE hreader,
					 BOOLEAN newAI ,
					 BYTE Antennas[],
					 BYTE AntCount ,
					 BOOLEAN enISO15693,
					 BOOLEAN enAFI,
					 BYTE afi,
					 BOOLEAN enISO14443A,
					 BOOLEAN enISO18000p3m3,
					 CB_TAG_REPORT_HANDLE tag_report_handler,
					 void *cbParam,
					 DWORD *tagCount)
{
	err_t iret=0;
	DWORD totalCount;
	RFID_DN_HANDLE dnInvenParamList= RFID_HANDLE_NULL ;
	/*
	*  Add air interface protocol
	*/
	dnInvenParamList = RDR_CreateInvenParamSpecList() ;
	if(dnInvenParamList){
		if(enISO15693){// enable iso15693 inventory
			ISO15693_CreateInvenParam(dnInvenParamList,0,enAFI,afi,0x00) ;
		}
		if(enISO14443A) { // enable iso14443a inentory
			ISO14443A_CreateInvenParam(dnInvenParamList,0) ;
		}
		if(enISO18000p3m3) {// enable iso18000p3m3 inventory
			ISO18000p3m3_CreateInvenParam(dnInvenParamList,0,0,0,ISO18000p6C_Dynamic_Q) ;
		}
	}
	totalCount =0 ;

	//if AntCount =0  ,use default
label_inventory:
	iret = RDR_TagInventory(hreader,newAI,AntCount,Antennas ,dnInvenParamList) ;
	if((iret == NO_ERR ) || (iret  ==  -21)) {
		totalCount+= RDR_GetTagDataReportCount(hreader) ;
		RFID_DN_HANDLE dnhReport = RDR_GetTagDataReport(hreader,RFID_SEEK_FIRST) ;
		while(dnhReport != RFID_HANDLE_NULL) 
		{
			DWORD AIPtype,TagType,AntId ;
			BYTE dsfid;
			BYTE uid[32];
			BYTE uidlen;
			/* Is iso15693 tag ? if parse ok ,process it */
			iret = ISO15693_ParseTagDataReport(dnhReport,&AIPtype,&TagType,&AntId,&dsfid,uid) ;
			if(iret == NO_ERR)
			{
				tag_report_handler( cbParam,hreader,AIPtype , TagType,AntId ,uid ,8) ;
			}
			/* Is iso14443A tag ? if parse ok ,process it */
			iret = ISO14443A_ParseTagDataReport(dnhReport,&AIPtype,&TagType,&AntId,uid,&uidlen) ;
			if(iret  == NO_ERR) {
				tag_report_handler( cbParam,hreader,AIPtype , TagType,AntId ,uid ,uidlen) ;
			}
			/* Is iso18000-3 mode 3 tag ? if parse ok ,process it */
			BYTE tagData[64] ;
			DWORD tagDataLen =sizeof(tagData) ;
			DWORD metaFlags =0 ;
			iret=ISO18000p3m3_ParseTagDataReport(dnhReport ,&AIPtype ,&TagType ,&AntId,&metaFlags,tagData,&tagDataLen) ;
			if(iret == NO_ERR) {
				tag_report_handler( cbParam,hreader,AIPtype , TagType,AntId ,tagData,tagDataLen) ;
			}
			
			dnhReport = RDR_GetTagDataReport(hreader,RFID_SEEK_NEXT) ;
		}
		if(iret == -21) 
		{
			/*Stop trigger ocur at the reader .Maybe there are tags left for reading. */
			newAI=AI_TYPE_CONTINUE;
			goto label_inventory ;
		}

		iret =0 ;
	}
	else {
		/* error occur */
	}
	if(dnInvenParamList) DNODE_Destroy(dnInvenParamList) ;
	if(tagCount) *tagCount= totalCount ;
	return iret;
}

 

// CDlgInventory 对话框

IMPLEMENT_DYNAMIC(CDlgInventory, CDialog)

CDlgInventory::CDlgInventory(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInventory::IDD, pParent)
{

}

CDlgInventory::~CDlgInventory()
{
}

void CDlgInventory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listTagData);
	DDX_Control(pDX, IDC_BUTTON1, m_bntInvenStart);
	DDX_Control(pDX, IDC_BUTTON2, m_bntInvenStop);
	DDX_Control(pDX, IDC_BUTTON3, m_bntAdvance);
	DDX_Control(pDX, IDC_STATIC1, m_staTotal);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richedtInvnRes);
	DDX_Control(pDX, IDC_STATIC_INVENCOUNT, m_labInvenCounter);
	DDX_Control(pDX, IDC_CHECK2, m_ckbBeep);
}


BEGIN_MESSAGE_MAP(CDlgInventory, CDialog)
	ON_MESSAGE(WM_INVENOTYR_STOPPED,msg_inventory_stopped)
	ON_MESSAGE(WM_SIZE ,OnSize)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInventory::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgInventory::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgInventory::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgInventory::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDlgInventory 消息处理程序

BOOL CDlgInventory::OnInitDialog()
{
	CDialog::OnInitDialog();
	DWORD dwStyle = m_listTagData.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
    m_listTagData.SetExtendedStyle(dwStyle); //设置扩展风格
	m_listTagData.InsertColumn(0,_T("Standard"),LVCFMT_LEFT,70) ;
	m_listTagData.InsertColumn( 1, _T("Tag Type"), LVCFMT_LEFT, 120 );//插入列
	m_listTagData.InsertColumn( 2, _T("Serial Num"), LVCFMT_LEFT, 150 );//插入列
	m_listTagData.InsertColumn( 3, _T("Antenna"),LVCFMT_LEFT,80);
	m_listTagData.InsertColumn( 4, _T("Found count"),LVCFMT_LEFT,100) ;

	m_bntInvenStop.EnableWindow(FALSE) ;
	m_bntAdvance.EnableWindow(TRUE) ;

	m_only_new_tag =FALSE;
	m_AFI_match =FALSE;
	m_AFI_val = 0x00 ;
	m_slottype =0 ;


#if 0
	m_dlgTotal.Create(IDD_TOTAL,this) ;
	m_dlgTotal.SetWindowPos(NULL,0,0,50,50,0) ;
	m_dlgTotal.ShowWindow(SW_SHOW) ;
	m_dlgTotal.BringWindowToTop() ;
#endif
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

LRESULT CDlgInventory::OnSize(WPARAM wp, LPARAM lp)
{
	return  0 ;
}

LRESULT CDlgInventory::msg_inventory_stopped(WPARAM wp, LPARAM lp)
{
	m_thrdInventory.Stop() ;
	m_bntInvenStart.EnableWindow(TRUE) ;
	m_bntInvenStop.EnableWindow(FALSE) ;
	m_bntAdvance.EnableWindow(TRUE) ;
	InventoryOn=FALSE;
	
	return  0 ;
}


void CDlgInventory::OnBnClickedButton1()
{
	m_readCount =0 ;
	m_taglist.RemoveAll() ;
	m_staTotal.SetWindowText(_T("0")) ;
	m_labInvenCounter.SetWindowText(_T("0")) ;
	m_listTagData.DeleteAllItems() ;
	m_thrdInventory.Start(this,proc_inventory) ;
	m_bntInvenStart.EnableWindow(FALSE) ;
	m_bntInvenStop.EnableWindow(TRUE) ;
	m_bntAdvance.EnableWindow(FALSE) ;
	m_richedtInvnRes.SetWindowText(_T("")) ;
	InventoryOn = TRUE;
}
void CDlgInventory::LogInventoryResult(CString msg)
{
	long  nInsertAfterChar = m_richedtInvnRes.GetWindowTextLength();
	m_richedtInvnRes.SetSel(nInsertAfterChar, nInsertAfterChar);
	m_richedtInvnRes.ReplaceSel(msg, FALSE);
}



DWORD WINAPI CDlgInventory::proc_inventory(LPVOID lpv)
{
	err_t iret;
	BYTE Antennas[64];
	BYTE AntCount =0 ;
	DWORD PrevTotalCount ;
	DWORD totalCount  ;
	CDlgInventory *pT = (CDlgInventory *)lpv;
	BYTE newAI= AI_TYPE_NEW ;

	/* Is only read new tag ? */
	if(pT->m_only_new_tag){
		newAI=AI_TYPE_CONTINUE;
	}
	/* antenna selection */
	if(AntennaSelected > 0) {
		for(int i =0;i<32;i++) {
			if((AntennaSelected & (0x01 << i)) >0 ) {
				Antennas[AntCount]= i+ 1;
				AntCount++ ;
			}
		}
	}
	/*
	*  enable air interface protocol
	*/
	BOOLEAN enISO15693 ,enISO14443a,enISO18000p3m3;
	enISO15693 = enISO14443a =enISO18000p3m3=FALSE ;
	for(int i =0 ;i<m_supportedAIP.GetCount();i++){
		if(m_supportedAIP[i].m_en){
			if(m_supportedAIP[i].m_aip == RFID_APL_ISO15693_ID){
				enISO15693 =TRUE ;
			}
			else if(m_supportedAIP[i].m_aip == RFID_APL_ISO14443A_ID) {
				enISO14443a =TRUE ;
			}
			else if(m_supportedAIP[i].m_aip ==RFID_APL_ISO18000P3M3){
				enISO18000p3m3 = TRUE ;
			}
			//else if (m_supportedAIP[i].m_aip==RFID_APL_EPCGEN2_ID)
			//{
			//	enISO180006C = TRUE;
			//}
		}
	}

	totalCount =0 ;
	PrevTotalCount =0 ;
	while(!pT->m_thrdInventory.m_exit_flag) {
		//if AntCount =0  ,use default
		iret = rfid_inventory(hr,newAI,Antennas,AntCount ,enISO15693 ,pT->m_AFI_match,pT->m_AFI_val ,enISO14443a,enISO18000p3m3 ,cb_handle_tag_report,pT ,&totalCount) ;
		if(iret == NO_ERR) {
			pT->m_readCount++ ;
			CString strReadCount;
			strReadCount.Format(_T("%d"),pT->m_readCount) ;
			pT->m_labInvenCounter.SetWindowText(strReadCount) ;

			if(totalCount > 0)
			{
				if(pT->m_ckbBeep.GetCheck()) {
					Beep(700,100) ;
				}
			}

			if(PrevTotalCount != totalCount) { // tag count changed 
				CString stmp;
				stmp.Format(_T("Report count changed from:%d to %d\n"),PrevTotalCount,totalCount) ;
				pT->LogInventoryResult(stmp) ;		 
			}
			PrevTotalCount = totalCount ;
			totalCount =0 ;

			newAI=AI_TYPE_NEW;
			if(pT->m_only_new_tag){
				newAI=AI_TYPE_CONTINUE;
			}
		}
		else {
				totalCount =0 ;
				if(iret == -17) {// error from reader
					err_t rdr_err= RDR_GetReaderLastReturnError(hr) ;
					CString stmp;
					stmp.Format(_T("Inventory fail:%d,%d\n"),iret,rdr_err) ;
					pT->LogInventoryResult(stmp) ;
				}
				else {
					CString stmp;
					stmp.Format(_T("Inventory fail:%d\n"),iret) ;
					pT->LogInventoryResult(stmp) ;
				}
				//inventory error
				newAI=AI_TYPE_NEW;
				if(pT->m_only_new_tag){
					newAI=AI_TYPE_CONTINUE;
				}
		}
	}
	/*
	*  If API RDR_SetCommuImmeTimeout is called when stop, API RDR_ResetCommuImmeTimeout 
	*  must be called too, Otherwise, an error -5 may occurs .
	*/
	RDR_ResetCommuImmeTimeout(hr) ;
	pT->PostMessage(WM_INVENOTYR_STOPPED,0,0) ;
	return 1;

}
//
//
//DWORD WINAPI CDlgInventory::proc_inventory(LPVOID lpv)
//{
//	err_t iret;
//	BYTE Antennas[64];
//	BYTE AntCount =0 ;
//	DWORD PrevTotalCount ;
//	DWORD totalCount  ;
//	CDlgInventory *pT = (CDlgInventory *)lpv;
//	BYTE newAI= AI_TYPE_NEW ;
//	if(pT->m_only_new_tag){
//		newAI=AI_TYPE_CONTINUE;
//	}
//	if(AntennaSelected > 0) {
//		for(int i =0;i<32;i++) {
//			if((AntennaSelected & (0x01 << i)) >0 ) {
//				Antennas[AntCount]= i+ 1;
//				AntCount++ ;
//			}
//		}
//	}
//	// Enable Async report output 
//	if(pT->m_enAsyncOutput) {
//		RDR_EnableAsyncTagReportOutput(hr,RFID_EVTMED_USE_MSG,WM_REPORT,pT->m_hWnd,NULL) ;
//	}
//	else {
//		RDR_DisableAsyncTagReportOutput(hr) ;
//	}
//	/*
//	*  Add air interface protocol
//	*/
//	RFID_DN_HANDLE dnInvenParamList= RFID_HANDLE_NULL ;
//	dnInvenParamList = RDR_CreateInvenParamSpecList() ;
//	if(dnInvenParamList){
//		for(int i =0 ;i<m_supportedAIP.GetCount();i++){
//			if(m_supportedAIP[i].m_en){
//				if(m_supportedAIP[i].m_aip == RFID_APL_ISO15693_ID){
//					ISO15693_CreateInvenParam(dnInvenParamList,0,pT->m_AFI_match,pT->m_AFI_val,0x00) ;
//				}
//				else if(m_supportedAIP[i].m_aip == RFID_APL_ISO14443A_ID) {
//					ISO14443A_CreateInvenParam(dnInvenParamList,0) ;
//				}
//			}
//		}
//	}
//
//	totalCount =0 ;
//	PrevTotalCount =0 ;
//	while(!pT->m_thrdInventory.m_exit_flag) {
//		//if AntCount =0  ,use default
//		iret = RDR_TagInventory(hr,newAI,AntCount,Antennas ,dnInvenParamList) ;
//		if(iret == NO_ERR) {
//			pT->m_readCount++ ;
//			CString strReadCount;
//			strReadCount.Format("%d",pT->m_readCount) ;
//			pT->m_labInvenCounter.SetWindowText(strReadCount) ;
//
//			DWORD currentCount =  RDR_GetTagDataReportCount(hr) ;
//			if(currentCount > 0)
//			{
//				if(pT->m_ckbBeep.GetCheck()) {
//					Beep(700,100) ;
//				}
//			}
//			
//			totalCount+=currentCount ;
//			if(PrevTotalCount != totalCount) { // tag count changed 
//				CString stmp;
//				stmp.Format("Report count changed from:%d to %d\n",PrevTotalCount,totalCount) ;
//				pT->LogInventoryResult(stmp) ;		 
//			}
//			PrevTotalCount = totalCount ;
//			totalCount =0 ;
//
//			newAI=AI_TYPE_NEW;
//			if(pT->m_only_new_tag){
//				newAI=AI_TYPE_CONTINUE;
//			}
//			if(!pT->m_enAsyncOutput) {//Is not async output 
//
//				RFID_DN_HANDLE dnhReport = RDR_GetTagDataReport(hr,RFID_SEEK_FIRST) ;
//				while(dnhReport != RFID_HANDLE_NULL) 
//				{
//					DWORD AIPtype,TagType,AntId ;
//					BYTE dsfid;
//					BYTE uid[8];
//					BYTE uidlen;
//					iret = ISO15693_ParseTagDataReport(dnhReport,&AIPtype,&TagType,&AntId,&dsfid,uid) ;
//					if(iret == NO_ERR)
//					{
//						pT->AddNewTag(AIPtype,TagType,AntId,dsfid,uid) ;
//					}
//					iret = ISO14443A_ParseTagDataReport(dnhReport,&AIPtype,&TagType,&AntId,uid,&uidlen) ;
//					if(iret  == NO_ERR) {
//						pT->AddNewISO14443ATag(AIPtype,TagType,AntId , uid,uidlen) ;
//					}
//					dnhReport = RDR_GetTagDataReport(hr,RFID_SEEK_NEXT) ;
//				}
//			}
//		}
//		else {
//			if(iret == -21) //Stop trigger ocur at the reader .Maybe there are tags left for reading.
//			{
//				totalCount+= RDR_GetTagDataReportCount(hr) ;
//				if(!pT->m_enAsyncOutput) {//Is not async output 
//
//					RFID_DN_HANDLE dnhReport = RDR_GetTagDataReport(hr,RFID_SEEK_FIRST) ;
//					while(dnhReport != RFID_HANDLE_NULL) 
//					{
//						DWORD APItype,TagType,AntId ;
//						BYTE dsfid;
//						BYTE uid[8];
//						iret = ISO15693_ParseTagDataReport(dnhReport,&APItype,&TagType,&AntId,&dsfid,uid) ;
//						if(iret == NO_ERR)
//						{
//							pT->AddNewTag(APItype,TagType,AntId,dsfid,uid) ;
//						}
//						dnhReport = RDR_GetTagDataReport(hr,RFID_SEEK_NEXT) ;
//					}
//				}
//				newAI=AI_TYPE_CONTINUE;
//			}
//			else {
//				totalCount =0 ;
//				if(iret == -17) {// error from reader
//					err_t rdr_err= RDR_GetReaderLastReturnError(hr) ;
//					CString stmp;
//					stmp.Format("Inventory fail:%d,%d\n",iret,rdr_err) ;
//					pT->LogInventoryResult(stmp) ;
//				}
//				else {
//					CString stmp;
//					stmp.Format("Inventory fail:%d\n",iret) ;
//					pT->LogInventoryResult(stmp) ;
//				}
//				//inventory error
//				newAI=AI_TYPE_NEW;
//			}
//		}
//	}
//	if(dnInvenParamList) DNODE_Destroy(dnInvenParamList) ;
//    /*
//     *  If API RDR_SetCommuImmeTimeout is called when stop, API RDR_ResetCommuImmeTimeout 
//     *  must be called too, Otherwise, an error -5 may occurs .
//     */
//	RDR_ResetCommuImmeTimeout(hr) ;
//	pT->PostMessage(WM_INVENOTYR_STOPPED,0,0) ;
//	return 1;
//
//}


void CDlgInventory::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!InventoryOn) 
		return ;
	m_bntInvenStop.EnableWindow(FALSE) ;
	RDR_SetCommuImmeTimeout(hr) ; // 尝试让RDR_TagInventory马上超时退出 ，与RDR_ResetCommuImmeTimeout配对使用
	m_thrdInventory.SetStopTimeout(50000);//多标签时需要等待长时间, RDR_TagInventory的超时是30秒
	m_thrdInventory.SetExitVar() ;
}

//
//void CDlgInventory::AddNewTag(UINT32 apl_tid,UINT32 picc_tid,UINT32 ant_id,UINT8 dsfid,UINT8 *uid)
//{
//	CString tagtype ;
//	if(picc_tid == RFID_ISO15693_PICC_ICODE_SLI_ID ){
//		tagtype ="NXP ICODE SLI" ;
//	}
//	else if(picc_tid ==RFID_ISO15693_PICC_TI_HFI_PLUS_ID) {
//		tagtype = "Ti HF-I Plus" ;
//	}
//	else if(picc_tid ==RFID_ISO15693_PICC_ST_M24LRXX_ID ) {
//		tagtype ="ST M24LRxx" ;
//	}
//	else if(picc_tid == RFID_ISO15693_PICC_FUJ_MB89R118C_ID) {
//		tagtype ="Fujitsu MB89R118C" ;
//	}
//	else if(picc_tid == RFID_ISO15693_PICC_ST_M24LR64_ID) {
//		tagtype ="ST M24LR64" ;
//	}
//	else if(picc_tid == RFID_ISO15693_PICC_ST_M24LR16E_ID) {
//		tagtype ="ST M24LR16E" ;
//	}
//	else if(picc_tid== RFID_ISO15693_PICC_ICODE_SLIX_ID) {
//		tagtype="NXP ICODE SLIX" ;
//	}
//	else if(picc_tid== RFID_ISO15693_PICC_TIHFI_STANDARD_ID){
//		tagtype="Ti HF-I Standard" ;
//	}
//	else if(picc_tid == RFID_ISO15693_PICC_TIHFI_PRO_ID) {
//		tagtype="Ti HF-I Pro" ;
//	}
//	else {
//		tagtype  ="Unknown Tag" ;
//	}
//	TCHAR suid[32] ;
//	memset(suid,0,sizeof(suid));
//	BytesToHexStr(uid,8,suid) ;	
//	TCHAR sdsfid[8] ;
//	memset(sdsfid,0,sizeof(sdsfid));
//	BytesToHexStr(&dsfid,1,sdsfid) ;
//	CString sAntId ;
//	sAntId.Format("%d",ant_id) ;
//	INT32 i ;
//	for( i=0;i<m_taglist.GetCount();i++) {
//		if(m_taglist[i].m_uid ==suid && m_taglist[i].m_antNo == ant_id) {
//			break;
//		}
//	}
//	if(i>=m_taglist.GetCount()) {
//		CTag newtag;
//		newtag.m_counter = 1;
//		newtag.m_uid =suid ;
//		newtag.m_type = picc_tid;
//		newtag.m_antNo =ant_id ;
//		newtag.m_AIP =apl_tid  ;
//		m_taglist.Add(newtag) ;
//		int nRow=m_listTagData.InsertItem(m_taglist.GetCount()-1,tagtype);        //插入行
//		m_listTagData.SetItemText(nRow,1,suid) ;
//		m_listTagData.SetItemText(nRow,2,sdsfid) ;
//		m_listTagData.SetItemText(nRow,3,sAntId) ;
//		m_listTagData.SetItemText(nRow,4,"1");
//	}
//	else{
//		m_taglist[i].m_counter++ ;
//		if(m_taglist[i].m_counter>=500000)
//		{
//			m_taglist[i].m_counter = 1;
//		}
//		CSTR sc ;
//		sc.Format("%d",m_taglist[i].m_counter) ;
//		m_listTagData.SetItemText(i,4,sc) ;
//	}
//
//	CString strTotal;
//	strTotal.Format("%d",m_taglist.GetCount()) ;
//	m_staTotal.SetWindowText(strTotal) ;
//	//m_listTagData.SetItemText(nRow,1,);  //设置数据
//	//m_listTagData.
//
//}
//
//void CDlgInventory::AddNewISO14443ATag(UINT32 apl_tid,UINT32 picc_tid,UINT32 ant_id,UINT8 *uid,UINT8 uidlen)
//{
//	CString tagtype ;
//	switch(picc_tid) {
//		case RFID_ISO14443A_PICC_NXP_ULTRALIGHT_ID:
//			tagtype ="NXP Mifare Ultralight" ;
//			break;
//		case RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID:
//			tagtype ="NXP Mifare S50" ;
//			break;
//		case RFID_ISO14443A_PICC_NXP_MIFARE_S70_ID:
//			tagtype ="NXP Mifare S70" ;
//			break;
//		default:
//			tagtype ="unknown tag" ;
//
//	}
//	TCHAR suid[32] ;
//	memset(suid,0,sizeof(suid));
//	BytesToHexStr(uid,uidlen,suid) ;	
//	CString sAntId ;
//	sAntId.Format("%d",ant_id) ;
//	INT32 i ;
//	for( i=0;i<m_taglist.GetCount();i++) {
//		if(m_taglist[i].m_uid ==suid && m_taglist[i].m_antNo == ant_id) {
//			break;
//		}
//	}
//	if(i>=m_taglist.GetCount()) {
//		CTag newtag;
//		newtag.m_counter = 1;
//		newtag.m_uid =suid ;
//		newtag.m_type = picc_tid;
//		newtag.m_antNo =ant_id ;
//		newtag.m_AIP =apl_tid  ;
//		m_taglist.Add(newtag) ;
//		int nRow=m_listTagData.InsertItem(m_taglist.GetCount()-1,tagtype);        //插入行
//		m_listTagData.SetItemText(nRow,1,suid) ;
//		m_listTagData.SetItemText(nRow,2,"") ;
//		m_listTagData.SetItemText(nRow,3,sAntId) ;
//		m_listTagData.SetItemText(nRow,4,"1");
//	}
//	else{
//		m_taglist[i].m_counter++ ;
//		if(m_taglist[i].m_counter>=500000)
//		{
//			m_taglist[i].m_counter = 1;
//		}
//		CSTR sc ;
//		sc.Format("%d",m_taglist[i].m_counter) ;
//		m_listTagData.SetItemText(i,4,sc) ;
//	}
//
//	CString strTotal;
//	strTotal.Format("%d",m_taglist.GetCount()) ;
//	m_staTotal.SetWindowText(strTotal) ;
//	//m_listTagData.SetItemText(nRow,1,);  //设置数据
//	//m_listTagData.
//
//}
void CDlgInventory::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgAdvance dlg ;
	dlg.m_only_new_tag= m_only_new_tag;
	dlg.m_AFI_match = m_AFI_match;
	dlg.m_AFI_val =m_AFI_val;
	dlg.m_slottype = m_slottype;
	dlg.DoModal();
	m_only_new_tag = dlg.m_only_new_tag ;
	m_AFI_match = dlg.m_AFI_match ;
	m_AFI_val = dlg.m_AFI_val;
	m_slottype = dlg.m_slottype;
	  
}

void CDlgInventory::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_taglist.RemoveAll() ;
	m_staTotal.SetWindowText(_T("0")) ;
	m_listTagData.DeleteAllItems() ;
}
