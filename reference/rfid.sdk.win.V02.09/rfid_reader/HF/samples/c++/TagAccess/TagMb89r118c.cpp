// TagMb89r118c.cpp : 实现文件
//

#include "stdafx.h"
#include "Resource.h"
#include "TagMb89r118c.h"
#include "rfidlib_aip_iso15693.h"
#include "DlgSysInfor.h"
#include "gfunctions.h"
#include "rfidlib_reader.h"


// CTagMb89r118c 对话框

IMPLEMENT_DYNAMIC(CTagMb89r118c, CDialog)

CTagMb89r118c::CTagMb89r118c(CWnd* pParent /*=NULL*/)
	: CDialog(CTagMb89r118c::IDD, pParent)
{

}

CTagMb89r118c::~CTagMb89r118c()
{
}

void CTagMb89r118c::DoDataExchange(CDataExchange* pDX)
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

	DDX_Control(pDX, IDC_BUTTON6, m_bntEanbleEAS);

	DDX_Control(pDX, IDC_BUTTON15, m_bntVerityEAS);

	DDX_Control(pDX, IDC_ICODESLI_BD, m_editBD);
	DDX_Control(pDX, IDC_BUTTON17, m_bntWriteMultiBlks);
	DDX_Control(pDX, IDC_EASFLAG, m_cbbEASFlag);
	DDX_Control(pDX, IDC_RICHEDIT21, m_edtEASData);
}


BEGIN_MESSAGE_MAP(CTagMb89r118c, CDialog)
	ON_BN_CLICKED(IDC_BUTTON13, &CTagMb89r118c::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CTagMb89r118c::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &CTagMb89r118c::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON8, &CTagMb89r118c::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTagMb89r118c::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CTagMb89r118c::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CTagMb89r118c::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON1, &CTagMb89r118c::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_NUMBLOCKS, &CTagMb89r118c::OnCbnSelchangeNumblocks)
	ON_CBN_SELCHANGE(IDC_BLKNO, &CTagMb89r118c::OnCbnSelchangeBlkno)
	ON_BN_CLICKED(IDC_BUTTON17, &CTagMb89r118c::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON4, &CTagMb89r118c::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTagMb89r118c::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CTagMb89r118c::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTagMb89r118c::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CTagMb89r118c::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON15, &CTagMb89r118c::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON12, &CTagMb89r118c::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_CHECK2, &CTagMb89r118c::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON24, &CTagMb89r118c::OnBnClickedButton24)
END_MESSAGE_MAP()


// CTagMb89r118c 消息处理程序
BOOL CTagMb89r118c::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_cbbModes.AddString(_T("none address")) ;
	m_cbbModes.AddString(_T("address")) ;
	m_cbbModes.AddString(_T("select")) ;
	m_cbbModes.SetCurSel(1) ;
	
	for(int i=0;i<0xFA;i++) {
		CSTR s ;
		s.Format(_T("%03XH"),i) ;
		m_cbbBlkNum.AddString(s) ;
	}
	m_cbbBlkNum.SetCurSel(0) ;

	for(int i=1;i<=0xFA /* the RAM of the reader is small */;i++) {
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
	m_bntVerityEAS.EnableWindow(FALSE) ;
	m_bntLockBlk.EnableWindow(FALSE) ;
	m_bntWriteMultiBlks.EnableWindow(FALSE) ;


	m_cbbEASFlag.AddString(_T("disable")) ;
	m_cbbEASFlag.AddString(_T("enable")) ;
	m_cbbEASFlag.SetCurSel(0) ;
	

	/* Block data edit */
	BYTE buffer[9] ;
	memset(buffer,0,sizeof(buffer));
	m_editBD.m_bpr = 9;
	m_editBD.SetData(buffer,sizeof(buffer)) ;
	m_editBD.m_sa =0 ;

	use_fast_cmd = FALSE;

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CTagMb89r118c::OnBnClickedButton13()
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
	iret = ISO15693_Connect(hr,RFID_ISO15693_PICC_FUJ_MB89R118C_ID,addrmode,u,&hp);
	if(iret != NO_ERR) {
		MessageBox(_T("connect tag fail !")) ;
		goto fail;
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
	m_bntVerityEAS.EnableWindow(TRUE) ;	
	m_bntLockBlk.EnableWindow(TRUE) ;
	m_bntWriteMultiBlks.EnableWindow(TRUE) ;
	m_cbbModes.EnableWindow(FALSE) ;
	m_cbbUIDs.EnableWindow(FALSE) ;

fail:
	return ;
}

void CTagMb89r118c::OnBnClickedButton14()
{
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
	m_bntVerityEAS.EnableWindow(FALSE) ;	
	m_bntLockBlk.EnableWindow(FALSE) ;
	m_bntWriteMultiBlks.EnableWindow(FALSE) ;
	m_cbbModes.EnableWindow(TRUE) ;
	m_cbbUIDs.EnableWindow(TRUE) ;

}

void CTagMb89r118c::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	BYTE uid[8] ;
	BYTE dsfid;
	BYTE afi ;
	DWORD blk_size,total_num ;

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

void CTagMb89r118c::OnBnClickedButton8()
{
BOOLEAN read_ssb ;
	read_ssb = TRUE ;
	BYTE block[9] ;
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
	DWORD BytesRead =0 ;
	iret = ISO15693_ReadSingleBlock(hr,hp,read_ssb,blockno,block,nSize ,&BytesRead) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}
	UpdateData(TRUE);
	m_editBD.SetData(block,BytesRead) ;
	m_editBD.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK);
}

void CTagMb89r118c::OnBnClickedButton9()
{
// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	BYTE block[8] ;
	DWORD blockno ;
	INT32 idx;
	m_editBD.GetData(block,1,8) ;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	iret = ISO15693_WriteSingleBlock(hr,hp,blockno,block,8) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CTagMb89r118c::OnBnClickedButton10()
{

	DWORD blockAddr;
	DWORD numOfBlockToRead;
	DWORD numOfBlocks;
	DWORD bytesRead;
	BOOLEAN read_ssb ;
	read_ssb =TRUE ;
	INT32 idx;
	idx = m_cbbModes.GetCurSel() ;
	if( idx != 1) {
		MessageBox(_T("Only support address mode")) ;
		return ;
	}
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockAddr = idx;
	
	idx = m_cbbNumBlocks.GetCurSel() ;
	if(idx< 0) {
		MessageBox(_T("select number of blocks"),_T(""),MB_OK) ;
		return ;
	}
	numOfBlockToRead = idx+1 ;
	err_t iret;
	BYTE buffer[256*8] ;

	numOfBlocks =0 ;
	bytesRead =0 ;
	/* reader RAM is not too large ,exceed 200 blocks ,the reader will return error  */
	iret =ISO15693_ReadMultiBlocks(hr,hp,read_ssb,blockAddr,numOfBlockToRead,&numOfBlocks,buffer,sizeof(buffer),&bytesRead) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return;
	}

	UpdateData(TRUE);
	m_editBD.SetData(buffer ,bytesRead) ;
	m_editBD.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CTagMb89r118c::OnBnClickedButton11()
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
	if((blockno % 8) != 0) {
		MessageBox(_T("The first block number specified in this request must be a multiple of 8"));
		return ;
	}
	
	idx = m_cbbNumBlocks.GetCurSel() ;
	if(idx< 0) {
		MessageBox(_T("select number of blocks"),_T(""),MB_OK) ;
		return ;
	}
	numOfBlocks = idx +1 ;
	if(numOfBlocks > 64) {
		MessageBox(_T("Up to 64 blocks of data can be read for one request.")) ;
		return ;
	}
	err_t iret;
	BYTE buffer[128] ;
	DWORD nSize;
	nSize = sizeof(buffer) ;
	DWORD BytesRead =0 ;
	iret =ISO15693_GetBlockSecStatus(hr,hp,blockno,numOfBlocks,buffer,nSize,&BytesRead) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return;
	}
	BYTE *blocks ;
	int nlen =BytesRead * 9;
	blocks = new BYTE[nlen] ;
	memset(blocks,0,nlen);
	for(int i=0;i<BytesRead ;i++) {
		blocks[i*9] = buffer[i] ;
	}
	UpdateData(TRUE);
	m_editBD.SetData(blocks ,nlen) ;
	m_editBD.RedrawWindow() ;
}

void CTagMb89r118c::OnBnClickedButton1()
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

void CTagMb89r118c::OnCbnSelchangeNumblocks()
{

	int leftNum = 0xFA -m_cbbBlkNum.GetCurSel();
	while(m_cbbNumBlocks.GetCount() > 0) {
		m_cbbNumBlocks.DeleteString(0) ;
	}
	for(int i= 1;i<=leftNum;i++ ) {
		CString str1;
		str1.Format(_T("%d") ,i) ;
		m_cbbNumBlocks.AddString(str1) ;
	}
	m_cbbNumBlocks.SetCurSel(0) ;

	OnBlockAddrChanged();

#if 0
	int idx ;
	int block_no,num_blocks,block_size;
	BOOLEAN read_ssb ;
	block_size = 8;
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
	read_ssb = TRUE ;
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

void CTagMb89r118c::OnCbnSelchangeBlkno()
{
	OnBlockAddrChanged()  ;
}


void CTagMb89r118c::OnBlockAddrChanged()
{
	int idx ;
	int block_no,num_blocks,block_size;
	BOOLEAN read_ssb ;
	block_size = 8;
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

void CTagMb89r118c::OnBnClickedButton17()
{
// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	BYTE *pblock ;
	DWORD blockno ;
	DWORD numOfBlockToWrite;
	INT32 idx;
	
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	/* get number of blocks to write */
	idx = m_cbbNumBlocks.GetCurSel()  ;
	if(idx < 0) {
		MessageBox(_T("Select number of blocks"),_T(""),MB_OK) ;
		return ;
	}	
	numOfBlockToWrite =idx + 1;

	pblock = new BYTE[ 8 * numOfBlockToWrite ] ;
	if(!pblock) {
		MessageBox(_T("Memory allocate fail!"),_T(""),MB_OK) ;
		return ;
	}
	idx =1 ;
	for(int i=0;i<numOfBlockToWrite;i++) {
		m_editBD.GetData(pblock+ i * 8,idx,8) ;
		idx +=(8 + 1);
	}
	iret = ISO15693_WriteMultipleBlocks(hr,hp,blockno,numOfBlockToWrite,pblock,numOfBlockToWrite * 8) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		if(pblock) delete[] pblock;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
	if(pblock) delete[] pblock;

}

void CTagMb89r118c::OnBnClickedButton4()
{
	err_t iret;
    TCHAR afi[16] ;
	memset(afi,0,sizeof(afi));
	m_edtDSFID.GetWindowText(afi,sizeof(afi)/sizeof(TCHAR));
	BYTE v ;
	HexStrToBytes(afi,&v,NULL) ;
	iret = ISO15693_WriteDSFID(hr,hp,v) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CTagMb89r118c::OnBnClickedButton5()
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

void CTagMb89r118c::OnBnClickedButton2()
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

void CTagMb89r118c::OnBnClickedButton3()
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

void CTagMb89r118c::OnBnClickedButton6()
{
	int idx; 
	err_t iret;
	idx = m_cbbModes.GetCurSel() ;
	if( idx != 1) {
		MessageBox(_T("Only support address mode")) ;
		return ;
	}

	idx =  m_cbbEASFlag.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select EAS flag "),_T(""),MB_OK) ;
		return ;
	}
	BYTE EASFlag ;
	EASFlag = idx;  /* 0:disable,1:enable */
	//iret = FUJMB89R118C_WriteEAS(hr,hp,EASFlag) ;
	iret= -1;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}


void CTagMb89r118c::ShowError(INT err) 
{
	CString str ;
	str.Format(_T("error code:%d"),err) ;
	if(err== -17) {
		err_t rdrerr;
		rdrerr= RDR_GetReaderLastReturnError(hr) ;
		str.Format(_T("error code:%d, %d"),err,rdrerr) ;
	}
	MessageBox(str) ;
}
void CTagMb89r118c::OnBnClickedButton15()
{
	BYTE buffer[16] ;
	DWORD nSize;
	err_t iret;
	int idx;
	idx = m_cbbModes.GetCurSel() ;
	if( idx == 1) {
		MessageBox(_T("Only support none address mode and select mode")) ;
		return ;
	}
	nSize = sizeof(buffer) ;
	DWORD BytesRead =0 ;
	m_edtEASData.SetWindowText(_T("")) ;
	//iret = FUJMB89R118C_DetectEAS(hr,hp,buffer,nSize,&BytesRead) ;
	iret =-1;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}
	TCHAR str[128] ;
	memset(str,0,sizeof(str));
	BytesToHexStr(buffer,BytesRead,str) ;
	m_edtEASData.SetWindowText(str) ;
}

void CTagMb89r118c::OnBnClickedButton12()
{
//
//	BYTE blockAddr;
//	BYTE numOfBlocks;
//	BOOLEAN read_ssb ;
//	read_ssb = TRUE ;
//	INT32 idx;
//	idx = m_cbbModes.GetCurSel() ;
//	if( idx != 1) {
//		MessageBox(_T("Only support address mode")) ;
//		return ;
//	}
//	idx = m_cbbBlkNum.GetCurSel();
//	if(idx < 0) {
//		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
//		return ;
//	}
//	blockAddr = idx;
//	
//	idx = m_cbbNumBlocks.GetCurSel() ;
//	if(idx< 0) {
//		MessageBox(_T("select number of blocks"),_T(""),MB_OK) ;
//		return ;
//	}
//	numOfBlocks = idx+1 ;
//	err_t iret;
//	BYTE buffer[256*8] ;
//	DWORD nSize;
//	nSize = sizeof(buffer) ;
//	/* reader RAM is not too large ,exceed 200 blocks ,the reader will return error  */
//	iret =FUJMB89R118C_ReadMultiBlksUnlimited(hr,hp,read_ssb,blockAddr,&numOfBlocks,buffer,&nSize) ;
//	if(iret != NO_ERR) {
//		ShowError(iret) ;
//		return;
//	}
//#if 0
//	CString str1;
//	int index = 0;
//	while((nSize-index) > 0) {
//		if((nSize-index)  >=9) {
//			char str[2048] ;
//			memset(str,0,sizeof(str));
//			BytesToHexStr(buffer+index,9,str);	
//			CString str2;
//			str2.Format("%s\n",str);
//			str1 +=str2;
//		}
//		index+=9 ;
//	}
//	MessageBox(str1,"",MB_OK) ;
//#endif
//	UpdateData(TRUE);
//	m_editBD.SetData(buffer ,nSize) ;
//	m_editBD.RedrawWindow() ;
//	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CTagMb89r118c::OnBnClickedCheck2()
{
	


}

void CTagMb89r118c::OnBnClickedButton24()
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
