// DlgTagIcodesli.cpp : 实现文件
//

#include "stdafx.h"
#include "rfidlib.h"
#include "demo_m24rl64.h"
#include "DlgTagIcodesli.h"
#include "gfunctions.h"
#include "DlgSysInfor.h"
#include "rfidlib_aip_iso15693.h"
#include "rfidlib_reader.h"


// CDlgTagIcodesli 对话框

IMPLEMENT_DYNAMIC(CDlgTagIcodesli, CDialog)

CDlgTagIcodesli::CDlgTagIcodesli(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTagIcodesli::IDD, pParent)
{

}

CDlgTagIcodesli::~CDlgTagIcodesli()
{
}

void CDlgTagIcodesli::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ADDRMODE, m_cbbModes);
	DDX_Control(pDX, IDC_UIDS, m_cbbUIDs);
	DDX_Control(pDX, IDC_NUMBLOCKS, m_cbbBlkNum);
	DDX_Control(pDX, IDC_BLKNO, m_cbbNumBlocks);
	DDX_Control(pDX, IDC_DSFID, m_edtDSFID);
	DDX_Control(pDX, IDC_AFI, m_edtAFI);
	DDX_Control(pDX, IDC_BUTTON13, m_bntConnectTag);
	DDX_Control(pDX, IDC_BUTTON14, m_bntDisconnTag);
	DDX_Control(pDX, IDC_BUTTON16, m_bntGetTagSys);
	DDX_Control(pDX, IDC_BUTTON8, m_bntRSB);
	DDX_Control(pDX, IDC_BUTTON9, m_bntWSB);
	DDX_Control(pDX, IDC_BUTTON10, m_bntRMB);
	DDX_Control(pDX, IDC_BUTTON11, m_bntRSSB);
	DDX_Control(pDX, IDC_BUTTON1, m_bntLockBlk);
	DDX_Control(pDX, IDC_BUTTON4, m_bntWriteDSFID);
	DDX_Control(pDX, IDC_BUTTON5, m_bntLockDSFID);
	DDX_Control(pDX, IDC_BUTTON2, m_bntWriteAFI);
	DDX_Control(pDX, IDC_BUTTON3, m_bntLockAFI);
	DDX_Control(pDX, IDC_ICODESLI_BD, m_editBD);
	DDX_Control(pDX, IDC_BUTTON6, m_bntEanbleEAS);
	DDX_Control(pDX, IDC_BUTTON7, m_bntDisableEAS);
	DDX_Control(pDX, IDC_BUTTON12, m_bntLockEAS);
	DDX_Control(pDX, IDC_BUTTON15, m_bntVerityEAS);
	DDX_Control(pDX, IDC_RICHEDIT21, m_edtEASData);
	DDX_Control(pDX, IDC_BUTTON17, m_bntWMB);
	DDX_Control(pDX, IDC_BUTTON18, m_bntLMB);
}


BEGIN_MESSAGE_MAP(CDlgTagIcodesli, CDialog)
	ON_BN_CLICKED(IDC_BUTTON13, &CDlgTagIcodesli::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlgTagIcodesli::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &CDlgTagIcodesli::OnBnClickedButton16)
	ON_CBN_SELCHANGE(IDC_NUMBLOCKS, &CDlgTagIcodesli::OnCbnSelchangeNumblocks)
	ON_CBN_SELCHANGE(IDC_BLKNO, &CDlgTagIcodesli::OnCbnSelchangeBlkno)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgTagIcodesli::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlgTagIcodesli::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CDlgTagIcodesli::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CDlgTagIcodesli::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTagIcodesli::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgTagIcodesli::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgTagIcodesli::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgTagIcodesli::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgTagIcodesli::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgTagIcodesli::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgTagIcodesli::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON12, &CDlgTagIcodesli::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON15, &CDlgTagIcodesli::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON17, &CDlgTagIcodesli::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CDlgTagIcodesli::OnBnClickedButton18)
END_MESSAGE_MAP()


// CDlgTagIcodesli 消息处理程序
BOOL CDlgTagIcodesli::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_cbbModes.AddString(_T("none address")) ;
	m_cbbModes.AddString(_T("address")) ;
	m_cbbModes.AddString(_T("select")) ;
	m_cbbModes.SetCurSel(1) ;
	
	for(int i=0;i<28;i++) {
		CSTR s ;
		s.Format(_T("%d"),i) ;
		m_cbbBlkNum.AddString(s) ;
	}
	m_cbbBlkNum.SetCurSel(0) ;
	int maxSupportBlocks = 28 ;
	for(int i=1;i<=maxSupportBlocks/* read multiple fail if > 15 */;i++) {
		CSTR s ;
		s.Format(_T("%d"),i) ;
		m_cbbNumBlocks.AddString(s) ;		
	}
	m_cbbNumBlocks.SetCurSel(0) ;
	
	m_edtDSFID.SetWindowText(_T("00")) ;
	m_edtAFI.SetWindowText(_T("00")) ;
	hp= NULL ;
	m_bntConnectTag.EnableWindow(TRUE) ;
	m_bntDisconnTag.EnableWindow(FALSE) ;
	m_bntGetTagSys.EnableWindow(FALSE) ;
	m_bntRSB.EnableWindow(FALSE) ;
	m_bntWSB.EnableWindow(FALSE) ;
	m_bntRSSB.EnableWindow(FALSE) ;
	m_bntRMB.EnableWindow(FALSE) ;
	m_bntWriteDSFID.EnableWindow(FALSE) ;
	m_bntLockDSFID.EnableWindow(FALSE) ;
	m_bntWriteAFI.EnableWindow(FALSE) ;
	m_bntLockAFI.EnableWindow(FALSE) ;
	m_bntEanbleEAS.EnableWindow(FALSE) ;
	m_bntDisableEAS.EnableWindow(FALSE) ;
	m_bntLockEAS.EnableWindow(FALSE) ;
	m_bntVerityEAS.EnableWindow(FALSE) ;
	m_bntLockBlk.EnableWindow(FALSE) ;
	m_bntWMB.EnableWindow(FALSE) ;
	m_bntLMB.EnableWindow(FALSE) ;

	/* Block data edit */
	BYTE buffer[5] ;
	memset(buffer,0,sizeof(buffer));
	m_editBD.SetData(buffer,sizeof(buffer)) ;
	m_editBD.m_sa =0 ;

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgTagIcodesli::ShowError(INT err) 
{
	CString str ;
	str.Format(_T("error code:%d"),err) ;
	if(err== -17) {
		err_t rdrerr;
		rdrerr= RDR_GetReaderLastReturnError(hr) ;
		str.Format(_T("error code:%d, %04x"),err,rdrerr) ;
	}
	MessageBox(str) ;
}

void CDlgTagIcodesli::OnBnClickedButton13()
{
	INT32 addrmode;
	addrmode = m_cbbModes.GetCurSel() ;
	if(addrmode <0) {
		MessageBox(_T("select address mode! ")) ;
		return ;
	}
	TCHAR uid[32] ;
	memset(uid,0,sizeof(uid));
	m_cbbUIDs.GetWindowText(uid,sizeof(uid)/sizeof(TCHAR)) ;
	if(addrmode != 0) {
		if(uid[0] =='\0') {
			MessageBox(_T("input uid! ")) ;
			return ;			
		}
	}	
	err_t iret;
	BYTE u[8] ;
	HexStrToBytes(uid,u,NULL) ;
	
	//Set tag type
	DWORD tagType = RFID_ISO15693_PICC_ICODE_SLI_ID ;
	if(m_cbbUIDs.GetCurSel() >=0 ){
		/* if selected uid including tag type identified in inventory operation, then use this tag type */
		tagType=m_cbbUIDs.GetItemData(m_cbbUIDs.GetCurSel()) ;
	}

	//Do connection 
	iret = ISO15693_Connect(hr,tagType,addrmode,u,&hp);
	if(iret != NO_ERR) {
		ShowError(iret) ;
		goto fail;
	}
	if(addrmode == 0 ){
		/* 
		* if select none address mode after inventory need to reset the tag first,because the tag is stay quiet now  
		* if the tag is in ready state ,do not need to call reset
		*/
		iret = ISO15693_Reset(hr,hp) ;
		if(iret != 0){
			MessageBox( _T("reset tag fail!"),_T("error"),MB_OK) ;
			RDR_TagDisconnect(hr,hp);
			hp =NULL ;
			return ;
		}
	}


	
	m_bntConnectTag.EnableWindow(FALSE) ;
	m_bntDisconnTag.EnableWindow(TRUE) ;
	m_bntGetTagSys.EnableWindow(TRUE) ;
	m_bntRSB.EnableWindow(TRUE) ;
	m_bntWSB.EnableWindow(TRUE) ;
	m_bntRSSB.EnableWindow(TRUE) ;
	m_bntRMB.EnableWindow(TRUE) ;
	m_bntWriteDSFID.EnableWindow(TRUE) ;
	m_bntLockDSFID.EnableWindow(TRUE) ;
	m_bntWriteAFI.EnableWindow(TRUE) ;
	m_bntLockAFI.EnableWindow(TRUE) ;
	m_bntEanbleEAS.EnableWindow(TRUE) ;
	m_bntDisableEAS.EnableWindow(TRUE) ;
	m_bntLockEAS.EnableWindow(TRUE) ;
	m_bntVerityEAS.EnableWindow(TRUE) ;	
	m_bntLockBlk.EnableWindow(TRUE) ;
	m_bntWMB.EnableWindow(TRUE) ;
	m_bntLMB.EnableWindow(TRUE) ;
fail:
	return ;
}

void CDlgTagIcodesli::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	RDR_TagDisconnect(hr,hp) ;
	m_bntConnectTag.EnableWindow(TRUE) ;
	m_bntDisconnTag.EnableWindow(FALSE) ;
	m_bntGetTagSys.EnableWindow(FALSE) ;
	m_bntRSB.EnableWindow(FALSE) ;
	m_bntWSB.EnableWindow(FALSE) ;
	m_bntRSSB.EnableWindow(FALSE) ;
	m_bntWriteDSFID.EnableWindow(FALSE) ;
	m_bntLockDSFID.EnableWindow(FALSE) ;
	m_bntWriteAFI.EnableWindow(FALSE) ;
	m_bntLockAFI.EnableWindow(FALSE) ;
	m_bntRMB.EnableWindow(FALSE) ;
	m_bntEanbleEAS.EnableWindow(FALSE) ;
	m_bntDisableEAS.EnableWindow(FALSE) ;
	m_bntLockEAS.EnableWindow(FALSE) ;
	m_bntVerityEAS.EnableWindow(FALSE) ;	
	m_bntLockBlk.EnableWindow(FALSE) ;
	m_bntWMB.EnableWindow(FALSE) ;
	m_bntLMB.EnableWindow(FALSE) ;
}

void CDlgTagIcodesli::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	BYTE uid[8] ;
	BYTE dsfid;
	BYTE afi ;
	DWORD blk_size;
	DWORD total_num ;
	BYTE ic_ref ;
	iret =  ISO15693_GetSystemInfo(hr,hp,uid,&dsfid,&afi,&blk_size,&total_num,&ic_ref ) ;
	if(iret != NO_ERR) {
		//MessageBox("get system infor fail","",MB_OK) ;
		ShowError(iret) ;
		return  ;
	}
	CDlgSysInfor dlg ;
	memcpy(dlg.m_uid,uid,8) ;
	dlg.m_dsfid = dsfid ;
	dlg.m_afi = afi ;
	dlg.m_blocksize = blk_size;
	dlg.m_totalnum = total_num ;
	dlg.m_icref =  ic_ref ;
	dlg.DoModal() ;	
}
void CDlgTagIcodesli::OnBlockAddrSelChange()
{
	int idx ;
	int block_no,num_blocks,block_size;
	BOOLEAN read_ssb ;
	block_size = 4;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		return;
	}
	block_no = idx;
	
	idx = m_cbbNumBlocks.GetCurSel() ;
	if(idx < 0) {
		num_blocks = 1;
	}
	else{
		num_blocks =idx + 1;
	}
	read_ssb =TRUE ;  // read block secure flag
	if(read_ssb)
		block_size++ ;
	
	UpdateData(TRUE);
	BYTE *buf ;
	buf = new BYTE[num_blocks * block_size ] ;
	memset(buf,0,num_blocks * block_size) ;
	m_editBD.m_sa =block_no ;
	m_editBD.m_bpr =block_size ;
	m_editBD.SetData(buf,num_blocks * block_size) ;
	m_editBD.RedrawWindow();
	delete[] buf;
}
void CDlgTagIcodesli::OnCbnSelchangeNumblocks()
{

	

	int leftNum = 28 -m_cbbBlkNum.GetCurSel();
	while(m_cbbNumBlocks.GetCount() > 0) {
		m_cbbNumBlocks.DeleteString(0) ;
	}
	for(int i= 1;i<=leftNum;i++ ) {
		CString str1;
		str1.Format(_T("%d") ,i) ;
		m_cbbNumBlocks.AddString(str1) ;
	}
	m_cbbNumBlocks.SetCurSel(0) ;

	OnBlockAddrSelChange() ;
}

void CDlgTagIcodesli::OnCbnSelchangeBlkno()
{
	OnBlockAddrSelChange() ;
}

void CDlgTagIcodesli::OnBnClickedButton8()
{
	BOOLEAN read_ssb ;
	read_ssb =TRUE;
	BYTE block[5] ;
	DWORD blockno ;
	INT32 idx;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	memset(block,0,sizeof(block)) ;
	err_t iret;
	DWORD nSize = sizeof(block) ;
	DWORD bytesRead  =0 ;
	iret = ISO15693_ReadSingleBlock(hr,hp,read_ssb,blockno,block,nSize,&bytesRead ) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}

	UpdateData(TRUE);
	m_editBD.SetData(block,bytesRead) ;
	m_editBD.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK);

}

void CDlgTagIcodesli::OnBnClickedButton9()
{
// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	BYTE block[4] ;
	DWORD blockno ;
	INT32 idx;
	m_editBD.GetData(block,1,4) ;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	iret = ISO15693_WriteSingleBlock(hr,hp,blockno,block,4) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodesli::OnBnClickedButton10()
{
	DWORD blockno ;
	DWORD numOfBlocksToRead;
	DWORD numOfBlksRead=0 ;
	BOOLEAN read_ssb ;
	read_ssb = TRUE;
	INT32 idx;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	
	idx = m_cbbNumBlocks.GetCurSel() ;
	if(idx< 0) {
		MessageBox(_T("select number of blocks"),_T(""),MB_OK) ;
		return ;
	}
	numOfBlocksToRead = idx+1 ;
	err_t iret;
	BYTE buffer[128*5] ;
	DWORD nSize;
	DWORD bytesBlkDatRead =0 ;
	nSize = sizeof(buffer) ;
	iret =ISO15693_ReadMultiBlocks(hr,hp,read_ssb,blockno,numOfBlocksToRead,&numOfBlksRead,buffer,nSize,&bytesBlkDatRead) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return;
	}
	UpdateData(TRUE);
	m_editBD.SetData(buffer ,bytesBlkDatRead) ;
	m_editBD.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodesli::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD blockno,numOfBlocks ;
	INT32 idx;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	
	idx = m_cbbNumBlocks.GetCurSel() ;
	if(idx< 0) {
		MessageBox(_T("select number of blocks"),_T(""),MB_OK) ;
		return ;
	}
	numOfBlocks = idx +1 ;
	err_t iret;
	BYTE buffer[128] ;
	DWORD nSize;
	DWORD bytesRead =0 ;
	nSize = sizeof(buffer) ;
	iret =ISO15693_GetBlockSecStatus(hr,hp,blockno,numOfBlocks,buffer,nSize,&bytesRead) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return;
	}
	BYTE *blocks ;
	int nlen =bytesRead * 5;
	blocks = new BYTE[nlen] ;
	memset(blocks,0,nlen);
	for(int i=0;i<bytesRead ;i++) {
		blocks[i*5] = buffer[i] ;
	}
	UpdateData(TRUE);
	m_editBD.SetData(blocks ,nlen) ;
	m_editBD.RedrawWindow() ;
}

void CDlgTagIcodesli::OnBnClickedButton1()
{
	//err_t iret ;
	//DWORD blockno ;
	//INT32 idx;
	//idx = m_cbbBlkNum.GetCurSel();
	//if(idx < 0) {
	//	MessageBox(_T("Select block no"),_T(""),MB_OK) ;
	//	return ;
	//}
	//blockno = idx;
	//iret = ISO15693_LockBlock(hr,hp,blockno) ;
	//if(iret != NO_ERR) {
	//	//MessageBox("fail","",MB_OK) ;
	//	ShowError(iret) ;
	//	return;
	//}
	//MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodesli::OnBnClickedButton4()
{
	err_t iret;
    TCHAR dsfid[16] ;
	memset(dsfid,0,sizeof(dsfid));
	m_edtDSFID.GetWindowText(dsfid,sizeof(dsfid)/sizeof(TCHAR));
	BYTE v ;
	HexStrToBytes(dsfid,&v,NULL) ;
	iret = ISO15693_WriteDSFID(hr,hp,v) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodesli::OnBnClickedButton2()
{
	err_t iret;
    TCHAR afi[16] ;
	memset(afi,0,sizeof(afi));
	m_edtAFI.GetWindowText(afi,sizeof(afi)/sizeof(TCHAR));
	BYTE v ;
	HexStrToBytes(afi,&v,NULL) ;
	iret = ISO15693_WriteAFI(hr,hp,v) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodesli::OnBnClickedButton5()
{
	err_t iret;
	iret = ISO15693_LockDSFID(hr,hp) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodesli::OnBnClickedButton3()
{
	err_t iret;
	iret = ISO15693_LockAFI(hr,hp) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodesli::OnBnClickedButton6()
{
	// Enable EAS
	err_t iret;
	iret = NXPICODESLI_EableEAS(hr,hp) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodesli::OnBnClickedButton7()
{
	// Disable EAS
	err_t iret;
	iret = NXPICODESLI_DisableEAS(hr,hp) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodesli::OnBnClickedButton12()
{
	// Lock EAS
	err_t iret;
	iret = NXPICODESLI_LockEAS(hr,hp) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodesli::OnBnClickedButton15()
{
	// Verify EAS
	err_t iret;
	BYTE EASStatus ;
	m_edtEASData.SetWindowText(_T("")) ;
	EASStatus =0 ;
	iret =NXPICODESLI_EASCheck(hr,hp,&EASStatus) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return;
	}
	if(EASStatus) {
		/* EAS function is open */
		m_edtEASData.SetWindowText(_T("EAS open")) ;
	}
	else {
		/* EAS function is closed */
		m_edtEASData.SetWindowText(_T("EAS closed")) ;
	}
}

void CDlgTagIcodesli::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码

	int iret;
	DWORD blockno ;
	DWORD numOfBlocksToWrite;
	BOOLEAN read_ssb ;
	read_ssb = TRUE;
	INT32 idx;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	
	idx = m_cbbNumBlocks.GetCurSel() ;
	if(idx< 0) {
		MessageBox(_T("select number of blocks"),_T(""),MB_OK) ;
		return ;
	}
	numOfBlocksToWrite = idx+1 ;

	BYTE *blocksdata ;
	blocksdata = new BYTE[numOfBlocksToWrite * 4] ;
	if(!blocksdata) {
		MessageBox(_T("Memory allocate fail!"),_T(""),MB_OK) ;
		return ;
	}
	for(int i =0 ;i<numOfBlocksToWrite;i++) {
		m_editBD.GetData(blocksdata + i*4,i*5 + 1,4) ;
	}
	
	iret = ISO15693_WriteMultipleBlocks(hr,hp,blockno,numOfBlocksToWrite,blocksdata,numOfBlocksToWrite * 4) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		if(blocksdata) delete[] blocksdata;
		ShowError(iret) ;
		return ;
	}
	if(blocksdata) delete[] blocksdata;
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodesli::OnBnClickedButton18()
{
	int iret;
	DWORD blockno ;
	DWORD numOfBlocksToLock;
	BOOLEAN read_ssb ;
	read_ssb = TRUE;
	INT32 idx;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	
	idx = m_cbbNumBlocks.GetCurSel() ;
	if(idx< 0) {
		MessageBox(_T("select number of blocks"),_T(""),MB_OK) ;
		return ;
	}
	numOfBlocksToLock = idx+1 ;

	iret =ISO15693_LockMultipleBlocks(hr,hp,blockno,numOfBlocksToLock) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}
