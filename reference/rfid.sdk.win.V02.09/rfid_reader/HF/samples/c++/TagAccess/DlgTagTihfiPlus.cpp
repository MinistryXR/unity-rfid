// DlgTagTihfiPlus.cpp : 实现文件
//

#include "stdafx.h"
#include "demo_m24rl64.h"
#include "DlgTagTihfiPlus.h"
#include "gfunctions.h"
#include "DlgSysInfor.h"

#include "rfidlib_reader.h"
#include "rfidlib_aip_iso15693.h"
#include "rfidlib.h"

// CDlgTagTihfiPlus 对话框

IMPLEMENT_DYNAMIC(CDlgTagTihfiPlus, CDialog)

CDlgTagTihfiPlus::CDlgTagTihfiPlus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTagTihfiPlus::IDD, pParent)
{

}

CDlgTagTihfiPlus::~CDlgTagTihfiPlus()
{
}

void CDlgTagTihfiPlus::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_RICHEDIT21, m_editBD);

}


BEGIN_MESSAGE_MAP(CDlgTagTihfiPlus, CDialog)
	ON_BN_CLICKED(IDC_BUTTON13, &CDlgTagTihfiPlus::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlgTagTihfiPlus::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &CDlgTagTihfiPlus::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgTagTihfiPlus::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlgTagTihfiPlus::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CDlgTagTihfiPlus::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CDlgTagTihfiPlus::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTagTihfiPlus::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgTagTihfiPlus::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgTagTihfiPlus::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgTagTihfiPlus::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgTagTihfiPlus::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_NUMBLOCKS, &CDlgTagTihfiPlus::OnBlockAddrSelChange)
	ON_CBN_SELCHANGE(IDC_BLKNO, &CDlgTagTihfiPlus::OnCbnSelchangeBlkno)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgTagTihfiPlus::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgTagTihfiPlus::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON12, &CDlgTagTihfiPlus::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON15, &CDlgTagTihfiPlus::OnBnClickedButton15)
END_MESSAGE_MAP()


// CDlgTagTihfiPlus 消息处理程序
BOOL CDlgTagTihfiPlus::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_cbbModes.AddString(_T("none address")) ;
	m_cbbModes.AddString(_T("address")) ;
	m_cbbModes.AddString(_T("select")) ;
	m_cbbModes.SetCurSel(1) ;
	
	for(int i=0;i<64;i++) {
		CSTR s ;
		s.Format(_T("%03XH"),i) ;
		m_cbbBlkNum.AddString(s) ;
	}
	m_cbbBlkNum.SetCurSel(0) ;

	for(int i=1;i<=64/* read multiple fail if > 15 */;i++) {
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
	m_bntLockBlk.EnableWindow(FALSE) ;

	

	/* Block data edit */
	UINT8 buffer[5] ;
	memset(buffer,0,sizeof(buffer));
	m_editBD.SetData(buffer,sizeof(buffer)) ;
	m_editBD.m_sa =0 ;

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CDlgTagTihfiPlus::OnBnClickedButton13()
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
	UINT8 u[8] ;
	HexStrToBytes(uid,u,NULL) ;
	iret = ISO15693_Connect(hr,RFID_ISO15693_PICC_TI_HFI_PLUS_ID,addrmode,u,&hp);
	if(iret != NO_ERR) {
		//MessageBox("connect tag fail !") ;
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
	m_bntLockBlk.EnableWindow(TRUE) ;


fail:
	return;
}

void CDlgTagTihfiPlus::OnBnClickedButton14()
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
	m_bntLockBlk.EnableWindow(FALSE) ;

}

void CDlgTagTihfiPlus::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	UINT8 uid[8] ;
	UINT8 dsfid;
	UINT8 afi ;
	DWORD blk_size;
	DWORD total_num ;
	UINT8 ic_ref ;
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

void CDlgTagTihfiPlus::OnBnClickedButton8()
{
	BOOLEAN read_ssb ;
	read_ssb = TRUE  ;
	UINT8 block[5] ;
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
	DWORD bytesRead = 0 ;
	iret = ISO15693_ReadSingleBlock(hr,hp,read_ssb,blockno,block,nSize,&bytesRead ) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}
	UpdateData(TRUE);
	m_editBD.SetData (block,bytesRead) ;
	m_editBD.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK);
}

void CDlgTagTihfiPlus::OnBnClickedButton9()
{
	err_t iret;
	UINT8 block[4] ;
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

void CDlgTagTihfiPlus::OnBnClickedButton10()
{
	DWORD blockno ;
	DWORD numOfBlocksToRead;
	DWORD numofBlksRead =0 ;
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
	nSize = sizeof(buffer) ;
	DWORD bytesRead =0 ;
	iret =ISO15693_ReadMultiBlocks(hr,hp,read_ssb,blockno,numOfBlocksToRead,&numofBlksRead,buffer,nSize,&bytesRead) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return;
	}
	UpdateData(TRUE);
	m_editBD.SetData(buffer,bytesRead) ; //UpdateData(buffer ,0,nSize) ;
	m_editBD.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagTihfiPlus::OnBnClickedButton11()
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
	UINT8 buffer[128] ;
	DWORD nSize;
	DWORD bytesRead =0 ;
	nSize = sizeof(buffer) ;
	iret =ISO15693_GetBlockSecStatus(hr,hp,blockno,numOfBlocks,buffer,nSize,&bytesRead) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return;
	}
	UINT8 *blocks ;
	int nlen =bytesRead * 5;
	blocks = new UINT8[nlen] ;
	memset(blocks,0,nlen);
	for(int i=0;i<bytesRead ;i++) {
		blocks[i*5] = buffer[i] ;
	}
	UpdateData(TRUE);
	m_editBD.SetData(blocks ,nlen) ;
	m_editBD.RedrawWindow() ;
}

void CDlgTagTihfiPlus::OnBnClickedButton1()
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
	//iret =ISO15693_LockBlock(hr,hp,blockno) ;
	//if(iret != NO_ERR) {
	//	//MessageBox("fail","",MB_OK) ;
	//	ShowError(iret) ;
	//	return;
	//}
	//MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagTihfiPlus::OnBnClickedButton4()
{
	err_t iret;
    TCHAR afi[16] ;
	memset(afi,0,sizeof(afi));
	m_edtDSFID.GetWindowText(afi,sizeof(afi)/sizeof(TCHAR));
	UINT8 v ;
	HexStrToBytes(afi,&v,NULL) ;
	iret =ISO15693_WriteDSFID(hr,hp,v) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagTihfiPlus::OnBnClickedButton5()
{
err_t iret;
	iret = ISO15693_LockDSFID(hr,hp) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagTihfiPlus::OnBnClickedButton2()
{
	err_t iret;
    TCHAR afi[16] ;
	memset(afi,0,sizeof(afi));
	m_edtAFI.GetWindowText(afi,sizeof(afi)/sizeof(TCHAR));
	UINT8 v ;
	HexStrToBytes(afi,&v,NULL) ;
	iret = ISO15693_WriteAFI(hr,hp,v) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagTihfiPlus::OnBnClickedButton3()
{
	err_t iret;
	iret = ISO15693_LockAFI(hr,hp) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}
void CDlgTagTihfiPlus::OnBlockAddrSelChange()
{
	int leftNum = 64 -m_cbbBlkNum.GetCurSel();
	while(m_cbbNumBlocks.GetCount() > 0) {
		m_cbbNumBlocks.DeleteString(0) ;
	}
	for(int i= 1;i<=leftNum;i++ ) {
		CString str1;
		str1.Format(_T("%d") ,i) ;
		m_cbbNumBlocks.AddString(str1) ;
	}
	m_cbbNumBlocks.SetCurSel(0) ;

	OnCbnSelchangeNumblocks();
#if 0
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
#endif
}

void CDlgTagTihfiPlus::OnCbnSelchangeNumblocks()
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
	read_ssb =TRUE ;
	if(read_ssb)
		block_size++ ;
	
	UpdateData(TRUE);
	UINT8 *buf ;
	buf = new UINT8[num_blocks * block_size ] ;
	memset(buf,0,num_blocks * block_size) ;
	m_editBD.m_sa =block_no ;
	m_editBD.m_bpr =block_size ;
	m_editBD.SetData(buf,num_blocks * block_size) ;
	m_editBD.RedrawWindow();
	delete[] buf;

}

void CDlgTagTihfiPlus::OnCbnSelchangeBlkno()
{
   OnCbnSelchangeNumblocks() ;
}

void CDlgTagTihfiPlus::OnBnClickedButton6()
{
	//err_t iret;
	//UINT8 block[8] ;
	//DWORD blockno ;
	//UINT8 num ;
	//INT32 idx;
	//
	//
	//idx = m_cbbBlkNum.GetCurSel();
	//if(idx < 0) {
	//	MessageBox(_T("Select block no"),_T(""),MB_OK) ;
	//	return ;
	//}
	//blockno = idx;
	//if((blockno & 0x01) > 0) {
	//	MessageBox(_T("Only support even address!")) ;
	//	return;
	//}
	//if(m_editBD.m_length < (m_editBD.m_bpr * 2) ) {
	//	MessageBox(_T("input 2 blocks data")) ;
	//	return;		
	//}
	//m_editBD.GetData(block,1,4) ;
	//m_editBD.GetData(block+4,6,4) ;
	//iret = TIHFIPLUS_Write2Blocks(hr,hp,blockno,block,8) ;
	//if(iret != NO_ERR) {
	//	//MessageBox("fail","",MB_OK) ;
	//	ShowError(iret) ;
	//	return ;
	//}
	//MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagTihfiPlus::OnBnClickedButton7()
{
	//err_t iret;
	//DWORD blockno ;
	//UINT8 num ;
	//INT32 idx;
	//
	//
	//idx = m_cbbBlkNum.GetCurSel();
	//if(idx < 0) {
	//	MessageBox(_T("Select block no"),_T(""),MB_OK) ;
	//	return ;
	//}
	//blockno = idx;
	//if((blockno & 0x01) > 0) {
	//	MessageBox(_T("Only support even address!")) ;
	//	return;
	//}
	//iret = TIHFIPLUS_Lock2Blocks(hr,hp,blockno) ;
	//if(iret != NO_ERR) {
	//	//MessageBox("fail","",MB_OK) ;
	//	ShowError(iret) ;
	//	return ;
	//}
	//MessageBox(_T("ok"),_T(""),MB_OK) ;
}


void CDlgTagTihfiPlus::ShowError(INT err) 
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

void CDlgTagTihfiPlus::OnBnClickedButton12()
{

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
		ShowError(iret) ;
		if(blocksdata) delete[] blocksdata;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
	if(blocksdata) delete[] blocksdata;
}

void CDlgTagTihfiPlus::OnBnClickedButton15()
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
