// DlgTagTiHFIStandard.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgTagTiHFIStandard.h"
#include "rfidlib_reader.h"
#include "rfidlib_aip_iso15693.h"
#include "gfunctions.h"


// CDlgTagTiHFIStandard 对话框

IMPLEMENT_DYNAMIC(CDlgTagTiHFIStandard, CDialog)

CDlgTagTiHFIStandard::CDlgTagTiHFIStandard(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTagTiHFIStandard::IDD, pParent)
{

}

CDlgTagTiHFIStandard::~CDlgTagTiHFIStandard()
{
}

void CDlgTagTiHFIStandard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDRMODE, m_cbbModes);
	DDX_Control(pDX, IDC_NUMBLOCKS, m_cbbBlkNum);
	DDX_Control(pDX, IDC_UIDS, m_cbbUIDs);

	DDX_Control(pDX,IDC_BLOCKDATA,m_editBD) ;

	DDX_Control(pDX, IDC_BUTTON13, m_bntConnect);
	DDX_Control(pDX, IDC_BUTTON14, m_bntDisconnect);
	DDX_Control(pDX, IDC_BUTTON8, m_bntReadSingle);
	DDX_Control(pDX, IDC_BUTTON9, m_bntWriteSingle);
	DDX_Control(pDX, IDC_BUTTON1, m_bntLockBlock);
	DDX_Control(pDX, IDC_NUMBLOCKS2, m_cbbNumBlocks);
}


BEGIN_MESSAGE_MAP(CDlgTagTiHFIStandard, CDialog)
	ON_BN_CLICKED(IDC_BUTTON13, &CDlgTagTiHFIStandard::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgTagTiHFIStandard::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlgTagTiHFIStandard::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTagTiHFIStandard::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlgTagTiHFIStandard::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgTagTiHFIStandard::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgTagTiHFIStandard::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgTagTiHFIStandard::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_NUMBLOCKS, &CDlgTagTiHFIStandard::OnCbnSelchangeNumblocks)
	ON_CBN_SELCHANGE(IDC_NUMBLOCKS2, &CDlgTagTiHFIStandard::OnCbnSelchangeNumblocks2)
END_MESSAGE_MAP()


// CDlgTagTiHFIStandard 消息处理程序

// CDlgTagTihfiPlus 消息处理程序
BOOL CDlgTagTiHFIStandard::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_cbbModes.AddString(_T("none address")) ;
	m_cbbModes.AddString(_T("address")) ;
	m_cbbModes.AddString(_T("select")) ;
	m_cbbModes.SetCurSel(1) ;
	/* 0x0-0x7 user blocks, 0x8-0x9 Serial number, 0x0A AFI */
	for(int i=0;i<= 0x0A;i++) {
		CSTR s ;
		s.Format(_T("%02XH"),i) ;
		m_cbbBlkNum.AddString(s) ;
	}
	m_cbbBlkNum.SetCurSel(0) ;
	for(int i = 1;i<=11;i++ ) {
		CSTR s ;
		s.Format(_T("%d"),i) ;
		m_cbbNumBlocks.AddString(s) ;
	}
	m_cbbNumBlocks.SetCurSel(0) ;


	m_bntConnect.EnableWindow(TRUE) ;
	m_bntDisconnect.EnableWindow(FALSE) ;
	m_bntReadSingle.EnableWindow(FALSE) ;
	m_bntWriteSingle.EnableWindow(FALSE) ;
	m_bntLockBlock.EnableWindow(FALSE) ;

	/* Block data edit */
	UINT8 buffer[5] ;
	memset(buffer,0,sizeof(buffer));
	m_editBD.SetData(buffer,sizeof(buffer)) ;
	m_editBD.m_sa =0 ;
	hp = NULL ;
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CDlgTagTiHFIStandard::OnBnClickedButton13()
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
	iret = ISO15693_Connect(hr,RFID_ISO15693_PICC_TIHFI_STANDARD_ID,addrmode,u,&hp);
	if(iret != NO_ERR) {
		//MessageBox("connect tag fail !") ;
		ShowError(iret) ;
		goto fail;
	}
	m_bntConnect.EnableWindow(FALSE) ;
	m_bntDisconnect.EnableWindow(TRUE) ;
	m_bntReadSingle.EnableWindow(TRUE) ;
	m_bntWriteSingle.EnableWindow(TRUE) ;
	m_bntLockBlock.EnableWindow(TRUE) ;


fail:
	return;
}

void CDlgTagTiHFIStandard::OnBnClickedButton8()
{
	BOOLEAN read_ssb ;
	read_ssb =TRUE ;
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

void CDlgTagTiHFIStandard::OnBnClickedButton9()
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

void CDlgTagTiHFIStandard::OnBnClickedButton1()
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


void CDlgTagTiHFIStandard::ShowError(INT err) 
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
void CDlgTagTiHFIStandard::OnBnClickedButton14()
{
// TODO: 在此添加控件通知处理程序代码
	RDR_TagDisconnect(hr,hp) ;
	hp = NULL ;
	m_bntConnect.EnableWindow(TRUE) ;
	m_bntDisconnect.EnableWindow(FALSE) ;
	m_bntReadSingle.EnableWindow(FALSE) ;
	m_bntWriteSingle.EnableWindow(FALSE) ;
	m_bntLockBlock.EnableWindow(FALSE) ;

}

void CDlgTagTiHFIStandard::OnBnClickedButton2()
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

void CDlgTagTiHFIStandard::OnBnClickedButton3()
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

void CDlgTagTiHFIStandard::OnBnClickedButton4()
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

void CDlgTagTiHFIStandard::OnCbnSelchangeNumblocks()
{
	int leftNum = 11 -m_cbbBlkNum.GetCurSel();
	while(m_cbbNumBlocks.GetCount() > 0) {
		m_cbbNumBlocks.DeleteString(0) ;
	}
	for(int i= 1;i<=leftNum;i++ ) {
		CString str1;
		str1.Format(_T("%d") ,i) ;
		m_cbbNumBlocks.AddString(str1) ;
	}
	m_cbbNumBlocks.SetCurSel(0) ;

	OnSelchangeNumblocks();
}



void CDlgTagTiHFIStandard::OnSelchangeNumblocks()
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
void CDlgTagTiHFIStandard::OnCbnSelchangeNumblocks2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnSelchangeNumblocks() ;
}
