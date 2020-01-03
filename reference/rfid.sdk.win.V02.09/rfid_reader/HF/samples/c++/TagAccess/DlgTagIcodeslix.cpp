// DlgTagIcodeslix.cpp : 实现文件
//

#include "stdafx.h"
#include "resource.h"
#include "DlgTagIcodeslix.h"
#include "DlgSysInfor.h"
#include "gfunctions.h"
#include "rfidlib_reader.h"
#include "rfidlib_aip_iso15693.h"


// CDlgTagIcodeslix 对话框



IMPLEMENT_DYNAMIC(CDlgTagIcodeslix, CDialog)

CDlgTagIcodeslix::CDlgTagIcodeslix(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTagIcodeslix::IDD, pParent)
{

}

CDlgTagIcodeslix::~CDlgTagIcodeslix()
{
}

void CDlgTagIcodeslix::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_BUTTON19, m_bntPwdProtect);
	DDX_Control(pDX, IDC_BUTTON17, m_bntSetPwd);
	DDX_Control(pDX, IDC_BUTTON23, m_bntWritePwd);
	DDX_Control(pDX, IDC_BUTTON24, m_bntLockPwd);

	DDX_Control(pDX, IDC_CMBPWDID, m_cbbPwdID);
	DDX_Control(pDX, IDC_EDIT1, m_edtPwd);
	DDX_Control(pDX, IDC_CMBBNDTYPE, m_cbbBandType);
	DDX_Control(pDX, IDC_EDIT3, m_edit_PrivacyPWB);
	DDX_Control(pDX, IDC_CHECK2, m_check_enReadPwdProtect);
	DDX_Control(pDX, IDC_EDIT4, m_edtCounterInitVal);
	DDX_Control(pDX, IDC_EDIT5, m_edit_easid);
	DDX_Control(pDX, IDC_COMBO1, m_cmb_pointer);
	DDX_Control(pDX, IDC_COMBO10, m_cmb_proStaL);
	DDX_Control(pDX, IDC_COMBO11, m_cmb_proStaH);
}


BEGIN_MESSAGE_MAP(CDlgTagIcodeslix, CDialog)
	ON_BN_CLICKED(IDC_BUTTON13, &CDlgTagIcodeslix::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlgTagIcodeslix::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &CDlgTagIcodeslix::OnBnClickedButton16)
	ON_CBN_SELCHANGE(IDC_NUMBLOCKS, &CDlgTagIcodeslix::OnCbnSelchangeNumblocks)
	ON_CBN_SELCHANGE(IDC_BLKNO, &CDlgTagIcodeslix::OnCbnSelchangeBlkno)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlgTagIcodeslix::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlgTagIcodeslix::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CDlgTagIcodeslix::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CDlgTagIcodeslix::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTagIcodeslix::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgTagIcodeslix::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgTagIcodeslix::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgTagIcodeslix::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgTagIcodeslix::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgTagIcodeslix::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlgTagIcodeslix::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON12, &CDlgTagIcodeslix::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON15, &CDlgTagIcodeslix::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON18, &CDlgTagIcodeslix::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CDlgTagIcodeslix::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CDlgTagIcodeslix::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON17, &CDlgTagIcodeslix::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON23, &CDlgTagIcodeslix::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CDlgTagIcodeslix::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON21, &CDlgTagIcodeslix::OnBnClickedButton21)
	ON_CBN_SELCHANGE(IDC_CMBPWDID, &CDlgTagIcodeslix::OnCbnSelchangeCmbpwdid)
	ON_BN_CLICKED(IDC_BUTTON22, &CDlgTagIcodeslix::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON25, &CDlgTagIcodeslix::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &CDlgTagIcodeslix::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, &CDlgTagIcodeslix::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON29, &CDlgTagIcodeslix::OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON28, &CDlgTagIcodeslix::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON30, &CDlgTagIcodeslix::OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON31, &CDlgTagIcodeslix::OnBnClickedButton31)
END_MESSAGE_MAP()


// CDlgTagIcodeslix 消息处理程序
BOOL CDlgTagIcodeslix::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_cbbModes.AddString(_T("none address")) ;
	m_cbbModes.AddString(_T("address")) ;
	m_cbbModes.AddString(_T("select")) ;
	m_cbbModes.SetCurSel(1) ;
	
	m_maxBlockCount =80 ;
	for(int i=0;i<m_maxBlockCount;i++) {
		CSTR s ;
		s.Format(_T("%d"),i) ;
		m_cbbBlkNum.AddString(s) ;
		m_cmb_pointer.AddString(s);
	}
	m_cbbBlkNum.SetCurSel(0) ;
	m_cmb_pointer.SetCurSel(0) ;
	int maxSupportBlocks = 32 ;
	for(int i=1;i<=maxSupportBlocks;i++) {
		CSTR s ;
		s.Format(_T("%d"),i) ;
		m_cbbNumBlocks.AddString(s) ;		
	}
	m_cbbNumBlocks.SetCurSel(0) ;
	
	m_edtDSFID.SetWindowText(_T("00")) ;
	m_edtAFI.SetWindowText(_T("00")) ;


	m_cbbBandType.AddString(_T("EAS")) ;
	m_cbbBandType.AddString(_T("AFI")) ;
	m_cbbBandType.SetCurSel(0) ;

	m_edtPwd.SetWindowText(_T("00000000")) ;
	m_cbbPwdID.AddString(_T("Read"));
	m_cbbPwdID.AddString(_T("Write"));
	m_cbbPwdID.AddString(_T("Privacy"));
	m_cbbPwdID.AddString(_T("Destroy"));
	m_cbbPwdID.AddString(_T("EAS/AFI"));
	m_cbbPwdID.SetCurSel(0) ;

	m_edit_PrivacyPWB.SetWindowText(_T("0F0F0F0F")) ;


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

	m_bntPwdProtect.EnableWindow(FALSE) ;
	m_bntSetPwd.EnableWindow(FALSE) ;
	m_bntWritePwd.EnableWindow(FALSE) ;
	m_bntLockPwd.EnableWindow(FALSE) ;
	m_cbbPwdID.EnableWindow(FALSE) ;
	m_edtPwd.EnableWindow(FALSE) ;
	m_cbbBandType.EnableWindow(FALSE) ;

	m_edit_easid.SetWindowText(_T("0000")) ;
	m_edtCounterInitVal.SetWindowText(_T("0")) ;
	

	/* Block data edit */
	BYTE buffer[5] ;
	memset(buffer,0,sizeof(buffer));
	m_editBD.SetData(buffer,sizeof(buffer)) ;
	m_editBD.m_sa =0 ;


	m_cmb_proStaL.AddString(_T("Public"));
	m_cmb_proStaH.AddString(_T("Public")) ;
	m_cmb_proStaL.AddString(_T("RW protected by the R password"));
	m_cmb_proStaH.AddString(_T("RW protected by the R password")) ;
	m_cmb_proStaL.AddString(_T("W protected by the W password"));
	m_cmb_proStaH.AddString(_T("W protected by the W password")) ;
	m_cmb_proStaL.AddString(_T("R protected by the R password and W protected by the RW password"));
	m_cmb_proStaH.AddString(_T("R protected by the R password and W protected by the RW password")) ;

	m_cmb_proStaL.SetCurSel(0) ;
	m_cmb_proStaH.SetCurSel(0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CDlgTagIcodeslix::ShowError(INT err) 
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

void CDlgTagIcodeslix::OnBnClickedButton13()
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

	//Set UID
	BYTE u[8] ;
	HexStrToBytes(uid,u,NULL) ;

	//Set tag type
	DWORD tagType = RFID_ISO15693_PICC_ICODE_SLIX_ID ;
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
		//iret = ISO15693_Reset(hr,hp) ;
		//if(iret != 0){
		//	MessageBox( _T("reset tag fail!"),_T("error"),MB_OK) ;
		//	RDR_TagDisconnect(hr,hp);
		//	hp =NULL ;
		//	return ;
		//}
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
	m_bntPwdProtect.EnableWindow(TRUE) ;
	m_bntSetPwd.EnableWindow(TRUE) ;
	m_bntWritePwd.EnableWindow(TRUE) ;
	m_bntLockPwd.EnableWindow(TRUE) ;
	m_cbbPwdID.EnableWindow(TRUE) ;
	m_edtPwd.EnableWindow(TRUE) ;
	m_cbbBandType.EnableWindow(TRUE) ;
fail:
	return ;
}

void CDlgTagIcodeslix::OnBnClickedButton14()
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
	m_bntPwdProtect.EnableWindow(FALSE) ;
	m_bntSetPwd.EnableWindow(FALSE) ;
	m_bntWritePwd.EnableWindow(FALSE) ;
	m_bntLockPwd.EnableWindow(FALSE) ;
	m_cbbPwdID.EnableWindow(FALSE) ;
	m_edtPwd.EnableWindow(FALSE) ;
	m_cbbBandType.EnableWindow(FALSE) ;
}

void CDlgTagIcodeslix::OnBnClickedButton16()
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
void CDlgTagIcodeslix::OnBlockAddrSelChange()
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
void CDlgTagIcodeslix::OnCbnSelchangeNumblocks()
{

	int leftNum = m_maxBlockCount -m_cbbBlkNum.GetCurSel();
	while(m_cbbNumBlocks.GetCount() > 0) {
		m_cbbNumBlocks.DeleteString(0) ;
	}
	for(int i= 1;i<=leftNum;i++ ) {
		CString str1;
		str1.Format(_T("%d") ,i) ;
		m_cbbNumBlocks.AddString(str1) ;
	}
	m_cbbNumBlocks.SetCurSel(0) ;

	OnBlockAddrSelChange();
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
	read_ssb = TRUE;
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

void CDlgTagIcodeslix::OnCbnSelchangeBlkno()
{
	OnBlockAddrSelChange() ;
}

void CDlgTagIcodeslix::OnBnClickedButton8()
{
	BOOLEAN read_ssb ;
	read_ssb = TRUE;
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
	DWORD bytesBlkDatRead =0  ;
	iret = ISO15693_ReadSingleBlock(hr,hp,read_ssb,blockno,block,nSize, &bytesBlkDatRead) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}
	UpdateData(TRUE);
	m_editBD.SetData(block,bytesBlkDatRead) ;
	m_editBD.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK);

}

void CDlgTagIcodeslix::OnBnClickedButton9()
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

void CDlgTagIcodeslix::OnBnClickedButton10()
{
	DWORD blockno ;
	DWORD numOfBlocksToRead;
	DWORD numOfBlocksRead =0;
	BOOLEAN read_ssb ;
	read_ssb = TRUE ;
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
	DWORD bytesRead = 0 ;
	iret =ISO15693_ReadMultiBlocks(hr,hp,read_ssb,blockno,numOfBlocksToRead,&numOfBlocksRead,buffer,nSize,&bytesRead) ;
	if(iret != NO_ERR) {
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return;
	}
	UpdateData(TRUE);
	m_editBD.SetData(buffer ,bytesRead) ;
	m_editBD.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodeslix::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD blockno,numOfBlocksToRead ;
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
	numOfBlocksToRead = idx +1 ;
	err_t iret;
	BYTE buffer[128] ;
	DWORD nSize;
	nSize = sizeof(buffer) ;
	DWORD bytesRead =0 ;
	iret =ISO15693_GetBlockSecStatus(hr,hp,blockno,numOfBlocksToRead,buffer,nSize,&bytesRead) ;
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

void CDlgTagIcodeslix::OnBnClickedButton1()
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

void CDlgTagIcodeslix::OnBnClickedButton4()
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

void CDlgTagIcodeslix::OnBnClickedButton2()
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

void CDlgTagIcodeslix::OnBnClickedButton5()
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

void CDlgTagIcodeslix::OnBnClickedButton3()
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

void CDlgTagIcodeslix::OnBnClickedButton6()
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

void CDlgTagIcodeslix::OnBnClickedButton7()
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

void CDlgTagIcodeslix::OnBnClickedButton12()
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

void CDlgTagIcodeslix::OnBnClickedButton15()
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

void CDlgTagIcodeslix::OnBnClickedButton18()
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

void CDlgTagIcodeslix::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	int idx;
	BYTE bandType ;
	idx =m_cbbBandType.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("select AFI or EAS,please"),_T(""),MB_OK) ;
		return ;
	}
	bandType= idx;
	iret = NXPICODESLI_PasswordProtect(hr,hp,bandType);
	if(iret != 0) {
		ShowError(iret) ;
		return;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodeslix::OnBnClickedButton20()
{
	BYTE signature[32]={0};
	err_t iret = NXPICODESLI_ReadSignature(hr,hp,signature);
	if (iret!=NO_ERR)
	{
		ShowError(iret) ;
	}
	else
	{
		TCHAR sTmp[128] = {0x00};
		memset(sTmp,'\0',sizeof(sTmp));
		BytesToHexStr(signature,32,sTmp);
		MessageBox(sTmp,_T(""));
	}
}

DWORD htole32(DWORD val) 
{
	val = ((val >> 16) & 0xffff) | ((val << 16) & 0xffff0000) ;
	val = ((val >> 8) & 0x00ff00ff) | ((val << 8) & 0xff00ff00)  ;
	return val;
}
void CDlgTagIcodeslix::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	//int iret ;
	//TCHAR passwordStr[9] ;
	//BYTE passwordBytes[4] ;
	//BYTE pwdID; 
	//int idx;
	//idx = m_cbbModes.GetCurSel() ;
	//if(idx == 0) {
	//	MessageBox(_T("Only support addressed mode and select mode!")) ;
	//	return ;
	//}
	//idx =m_cbbPwdID.GetCurSel()  ;
	//if(idx ==-1) {
	//	MessageBox(_T("select password id,please")) ;
	//	return ;
	//}
	//BYTE pwbNo = 0;
	//switch(m_cmb_pwbType.GetCurSel())
	//{
	//case 0:pwbNo = 0x01;break;
	//case 1:pwbNo = 0x02;break;
	//case 2:pwbNo = 0x04;break;
	//case 3:pwbNo = 0x08;break;
	//case 4:pwbNo = 0x10;break;
	//default:return;
	//}
	//m_edtPwd.GetWindowText(passwordStr ,sizeof(passwordStr) / sizeof(TCHAR)) ;
	//HexStrToBytes(passwordStr, passwordBytes,NULL) ;
	//DWORD  password =passwordBytes[0] & 0xff | (passwordBytes[1] << 8 & 0xff00) | (passwordBytes[2] << 16 & 0xff0000) | (passwordBytes[3] <<24 & 0xff000000)  ;
	//iret = NXPICODESLI_GetRandomAndSetPassword(hr,hp,pwdID ,password) ;
	//if(iret != 0) {
	//	ShowError(iret) ;
	//	return;
	//}
	//MessageBox(_T("ok"),_T(""),MB_OK) ;


	WORD random=0;
	CString ss;
	m_edtPwd.GetWindowText(ss);
	DWORD pwb = _tcstoul(ss,NULL,16);
	pwb = htole32(pwb);
	BYTE pwbNo = 0;
	switch(m_cbbPwdID.GetCurSel())
	{
	case 0:pwbNo = 0x01;break;
	case 1:pwbNo = 0x02;break;
	case 2:pwbNo = 0x04;break;
	case 3:pwbNo = 0x08;break;
	case 4:pwbNo = 0x10;break;
	default:return;
	}
	err_t iret;
	iret =NXPICODESLI_GetRandomAndSetPassword(hr,hp,pwbNo ,pwb) ;
	if(iret != 0) {
		ShowError(iret) ;
		return;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodeslix::OnBnClickedButton23()
{
	// TODO: 在此添加控件通知处理程序代码
	//int idx;
	//int iret;
	//BYTE pwdID; 
	//idx = m_cbbModes.GetCurSel() ;
	//if(idx == 0) {
	//	MessageBox(_T("Only support addressed mode and select mode!")) ;
	//	return ;
	//}
	//idx =m_cbbPwdID.GetCurSel()  ;
	//if(idx ==-1) {
	//	MessageBox(_T("select password id,please")) ;
	//	return ;
	//}
	//pwdID = 0x10 ;
	//TCHAR pwdStr[9] ;
	//memset(pwdStr,0,sizeof(pwdStr)) ;
	//m_edtPwd.GetWindowText(pwdStr,sizeof(pwdStr) / sizeof(TCHAR)) ;
	//BYTE pwdBytes[4];
	//HexStrToBytes(pwdStr,pwdBytes ,NULL) ;
	//DWORD pwd  =(pwdBytes[0] & 0xff) | (pwdBytes[1] << 8 & 0xff00) | (pwdBytes[2] << 16 & 0xff0000) | (pwdBytes[3] << 24 & 0xff000000) ;
	//iret  = NXPICODESLI_WritePassword(hr,hp,pwdID,pwd) ;
	//if(iret != 0) {
	//	ShowError(iret) ;
	//	return;
	//}
	//MessageBox(_T("ok"),_T(""),MB_OK) ;

	CString ss;
	m_edtPwd.GetWindowText(ss);
	DWORD pwb = _tcstoul(ss,NULL,16);
	pwb = htole32(pwb);
	BYTE pwbNo = 0;
	switch(m_cbbPwdID.GetCurSel())
	{
	case 0:pwbNo = 0x01;break;
	case 1:pwbNo = 0x02;break;
	case 2:pwbNo = 0x04;break;
	case 3:pwbNo = 0x08;break;
	case 4:pwbNo = 0x10;break;
	default:return;
	}
	err_t iret  = NXPICODESLI_WritePassword(hr,hp,pwbNo,pwb) ;
	if(iret != 0) {
		ShowError(iret) ;
		return;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodeslix::OnBnClickedButton24()
{
	// TODO: 在此添加控件通知处理程序代码
	//int iret;
	//BYTE pwdid ;
	//int idx;
	//DWORD dwPwd = 0 ;
	//idx =m_cbbPwdID.GetCurSel()  ;
	//if(idx ==-1) {
	//	MessageBox(_T("select password id,please")) ;
	//	return ;
	//}
	//pwdid = 0x10 ;

	//iret = NXPICODESLI_LockPassword(hr,hp,pwdid) ;
	//if(iret !=NO_ERR) {
	//	ShowError(iret) ;
	//	return;
	//}
	//MessageBox(_T("ok"),_T(""),MB_OK) ;


	int idx = m_cbbPwdID.GetCurSel();
	BYTE pwbNo = 0;
	switch(idx)
	{
	case 0:pwbNo = 0x01;break;
	case 1:pwbNo = 0x02;break;
	case 2:pwbNo = 0x04;break;
	case 3:pwbNo = 0x08;break;
	case 4:pwbNo = 0x10;break;
	}
	err_t iret = NXPICODESLI_LockPassword(hr,hp,pwbNo);
	if(iret !=NO_ERR) {
		ShowError(iret) ;
		return;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagIcodeslix::OnBnClickedButton21()
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

void CDlgTagIcodeslix::OnCbnSelchangeCmbpwdid()
{
	// TODO: 在此添加控件通知处理程序代码
	int pwdType = m_cbbPwdID.GetCurSel()  ;
	if((pwdType== 0)|| (pwdType== 1)||(pwdType== 4)) {
		m_edtPwd.SetWindowText(_T("00000000")) ;
	}
	else {
		m_edtPwd.SetWindowText(_T("0F0F0F0F")) ;
	}
}

void CDlgTagIcodeslix::OnBnClickedButton22()
{
	err_t iret = NXPICODESLI_Enable64BitPwd(hr,hp);
	if (iret!=NO_ERR)
	{
		ShowError(iret);
	}
	else{
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodeslix::OnBnClickedButton25()
{
	CString ss;
	m_edit_PrivacyPWB.GetWindowText(ss);
	DWORD pwb = _tcstoul(ss,NULL,16);
	pwb = htole32(pwb);
	err_t iret = NXPICODESLI_EnblePrivacy(hr,hp,pwb);
	if (iret!=NO_ERR)
	{
		ShowError(iret);
	}
	else{
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodeslix::OnBnClickedButton26()
{
	CString ss;
	m_edit_PrivacyPWB.GetWindowText(ss);
	DWORD pwb = _tcstoul(ss,NULL,16);
	pwb = htole32(pwb);
	err_t iret = NXPICODESLI_Destroy(hr,hp,pwb);
	if (iret!=NO_ERR)
	{
		ShowError(iret);
	}
	else{
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodeslix::OnBnClickedButton27()
{
	CString ss;
	m_edtCounterInitVal.GetWindowText(ss);
	WORD initCnt = (WORD)_tcstoul(ss,NULL,10);
	BOOLEAN enReadPwdProtect = FALSE;
	if(m_check_enReadPwdProtect.GetCheck())
	{
		enReadPwdProtect = TRUE;
	}
	err_t iret = NXPICODESLI_PresetCounter(hr,hp,initCnt,enReadPwdProtect);
	if (iret!=NO_ERR)
	{
		ShowError(iret);
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodeslix::OnBnClickedButton29()
{
	CString ss;
	
	m_edit_easid.GetWindowText(ss);
	WORD easid = (WORD)_tcstoul(ss,NULL,16);
	easid = htole32(easid);
	err_t iret = NXPICODESLI_WriteEASID(hr,hp,easid);
	if (iret!=NO_ERR)
	{
		ShowError(iret);
	}
	else{
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodeslix::OnBnClickedButton28()
{
	err_t iret = NXPICODESLI_IncrementCounter(hr,hp);
	if (iret!=NO_ERR)
	{
		ShowError(iret);
	}
	else{
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodeslix::OnBnClickedButton30()
{
	int PPPointer = m_cmb_pointer.GetCurSel();
	if(PPPointer == -1) {
		MessageBox(_T("Please select block address"),_T(""),MB_OK) ;
		return ;
	}
	BYTE protSta = 0;
	switch(m_cmb_proStaL.GetCurSel())
	{
	case 0:
		protSta |= 0x00;
		break;
	case 1:
		protSta |= 0x01;
		break;
	case 2:
		protSta |= 0x02;
		break;
	case 3:
		protSta |= 0x03;
		break;
	default:return;
	}

	switch(m_cmb_proStaH.GetCurSel())
	{
	case 0:
		protSta|= 0x00;
		break;
	case 1:
		protSta|=0x10;
		break;
	case 2:
		protSta|=0x20;
		break;
	case 3:
		protSta|=0x30;
		break;
	default:return;
	}

	err_t iret = NXPICODESLI_ProtectPage(hr,hp,PPPointer,protSta);
	if (iret!=NO_ERR)
	{
		ShowError(iret);
	}
	else{
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void CDlgTagIcodeslix::OnBnClickedButton31()
{
	int PPPointer = m_cmb_pointer.GetCurSel();
	err_t iret = NXPICODESLI_LockPageProtection(hr,hp,PPPointer);
	if (iret!=NO_ERR)
	{
		ShowError(iret);
	}
	else{
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}
