// DlgTagM24LR16E.cpp : 实现文件
//

#include "stdafx.h"
#include "demo_m24rl64.h"
#include "DlgTagM24LR16E.h"
#include "gfunctions.h"
#include "DlgSysInfor.h"

#include "rfidlib_reader.h"
#include "rfidlib_aip_iso15693.h"

// DlgTagM24LR16E 对话框

IMPLEMENT_DYNAMIC(DlgTagM24LR16E, CDialog)

DlgTagM24LR16E::DlgTagM24LR16E(CWnd* pParent /*=NULL*/)
	: CDialog(DlgTagM24LR16E::IDD, pParent)
{

}

DlgTagM24LR16E::~DlgTagM24LR16E()
{
}



// DlgTagM24LR16E 消息处理程序

void DlgTagM24LR16E::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDRMODE, m_cbbModes);
	DDX_Control(pDX, IDC_UIDS, m_cbbUIDs);
	DDX_Control(pDX, IDC_BUTTON13, m_bntConnectTag);
	DDX_Control(pDX, IDC_BUTTON14, m_bntDisconnTag);
	DDX_Control(pDX, IDC_BUTTON16, m_bntGetTagSys);
	DDX_Control(pDX, IDC_BLKNO, m_cbbBlkNum);
	DDX_Control(pDX, IDC_NUMBLOCKS, m_cbbNumBlocks);
	DDX_Control(pDX, IDC_SECTORNUM, m_cbbSectNum);
	DDX_Control(pDX, IDC_ACCESS, m_cbbAccessType);
	DDX_Control(pDX, IDC_PASSNUM_LOCK, m_cbbPassNum);
	DDX_Control(pDX, IDC_PWDNUM_UP, m_cbbPwdNum1);
	DDX_Control(pDX, IDC_NEW_PWD, m_edtNewPwd);
	DDX_Control(pDX, IDC_PWDNUM_AUTH, m_cbbPwdNum2);
	DDX_Control(pDX, IDC_PASSWORD_AUTH, m_edtAuthPwd);
	DDX_Control(pDX, IDC_DSFID, m_edtDSFID);
	DDX_Control(pDX, IDC_AFI, m_edtAFI);
	DDX_Control(pDX, IDC_RICHEDIT21, m_edtBlockData);
	DDX_Control(pDX, IDC_BUTTON8, m_bntRSB);
	DDX_Control(pDX, IDC_BUTTON9, m_bntWSB);
	DDX_Control(pDX, IDC_BUTTON10, m_bntRMB);
	DDX_Control(pDX, IDC_BUTTON11, m_bntRSSB);
	DDX_Control(pDX, IDC_BUTTON15, m_bntLockSect);
	DDX_Control(pDX, IDC_BUTTON5, m_bntUpdatePwd);
	DDX_Control(pDX, IDC_BUTTON12, m_bntAuthPwd);
	DDX_Control(pDX, IDC_BUTTON3, m_bntWriteDSFID);
	DDX_Control(pDX, IDC_BUTTON4, m_bntLockDSFID);
	DDX_Control(pDX, IDC_BUTTON1, m_bntWriteAFI);
	DDX_Control(pDX, IDC_BUTTON2, m_bntLockAFI);
	DDX_Control(pDX, IDC_PWDNUM_AUTH2, m_cbbEnergyHarvesting);
	DDX_Control(pDX, IDC_PWDNUM_AUTH3, m_cbbEHMode);
	DDX_Control(pDX, IDC_PWDNUM_AUTH4, m_cbbWIP);
	DDX_Control(pDX, IDC_PWDNUM_AUTH5, m_cbbEHEN);
	DDX_Control(pDX, IDC_EDIT1, m_edtFIELDON);
	DDX_Control(pDX, IDC_BUTTON18, m_bntSetCfgEH);
	DDX_Control(pDX, IDC_BUTTON19, m_bntSetCfgDO);
	DDX_Control(pDX, IDC_BUTTON20, m_bntReadCfgByte);
	DDX_Control(pDX, IDC_BUTTON22, m_bntSetCtrlRegEHEN);
	DDX_Control(pDX, IDC_BUTTON21, m_bntReadCtrlReg);
	DDX_Control(pDX, IDC_BUTTON26, m_bntWMB);
}


BEGIN_MESSAGE_MAP(DlgTagM24LR16E, CDialog)
	ON_BN_CLICKED(IDC_BUTTON13, &DlgTagM24LR16E::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &DlgTagM24LR16E::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON16, &DlgTagM24LR16E::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON3, &DlgTagM24LR16E::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &DlgTagM24LR16E::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &DlgTagM24LR16E::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &DlgTagM24LR16E::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON12, &DlgTagM24LR16E::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON5, &DlgTagM24LR16E::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON9, &DlgTagM24LR16E::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &DlgTagM24LR16E::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON11, &DlgTagM24LR16E::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON15, &DlgTagM24LR16E::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON10, &DlgTagM24LR16E::OnBnClickedButton10)
	ON_CBN_SELCHANGE(IDC_BLKNO, &DlgTagM24LR16E::OnCbnSelchangeBlkno)
	ON_CBN_SELCHANGE(IDC_NUMBLOCKS, &DlgTagM24LR16E::OnCbnSelchangeNumblocks)
	ON_BN_CLICKED(IDC_CHECK1, &DlgTagM24LR16E::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON20, &DlgTagM24LR16E::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON18, &DlgTagM24LR16E::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &DlgTagM24LR16E::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON22, &DlgTagM24LR16E::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON21, &DlgTagM24LR16E::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON26, &DlgTagM24LR16E::OnBnClickedButton26)
END_MESSAGE_MAP()


// DlgTagM24LR16E 消息处理程序
BOOL DlgTagM24LR16E::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_cbbModes.AddString(_T("none address")) ;
	m_cbbModes.AddString(_T("address")) ;
	m_cbbModes.AddString(_T("select")) ;
	m_cbbModes.SetCurSel(1) ;
	
	for(int i=0;i<0x200;i++) {
		CSTR s ;
		s.Format(_T("%03XH"),i) ;
		m_cbbBlkNum.AddString(s) ;
	}
	m_cbbBlkNum.SetCurSel(0) ;
	for(int i=1;i<=0x200;i++) {
		CSTR s ;
		s.Format(_T("%d"),i) ;
		m_cbbNumBlocks.AddString(s) ;		
	}
	m_cbbNumBlocks.SetCurSel(0) ;
	for(int i=0;i< 16;i++){
		CSTR s ;
		s.Format(_T("%d"),i) ;
		m_cbbSectNum.AddString(s) ;			
	}
	m_cbbSectNum.SetCurSel(0) ;
	for(int i=1;i<=3;i++) {
		CSTR s ;
		s.Format(_T("password#%d"),i) ;
		m_cbbPassNum.AddString(s) ;
		m_cbbPwdNum1.AddString(s) ;		
		m_cbbPwdNum2.AddString(s) ;
	}
	m_cbbPassNum.SetCurSel(0) ;
	m_cbbPwdNum1.SetCurSel(0) ;
	m_cbbPwdNum2.SetCurSel(0) ;

	m_cbbAccessType.AddString(_T("R_RW")) ;  
	m_cbbAccessType.AddString(_T("RW_RW")) ;
	m_cbbAccessType.AddString(_T("NO_RW")) ;
	m_cbbAccessType.AddString(_T("NO_R")) ;
	m_cbbAccessType.SetCurSel(0) ;

	m_edtNewPwd.SetWindowText(_T("00000000")) ;
	m_edtAuthPwd.SetWindowText(_T("00000000")) ;
	m_edtDSFID.SetWindowText(_T("00")) ;
	m_edtAFI.SetWindowText(_T("00")) ;
	m_cbbEnergyHarvesting.AddString(_T("power level:0")) ;
	m_cbbEnergyHarvesting.AddString(_T("power level:1")) ;
	m_cbbEnergyHarvesting.AddString(_T("power level:2")) ;
	m_cbbEnergyHarvesting.AddString(_T("power level:3")) ;

	m_cbbEHMode.AddString(_T("EH enable after power-up")) ;
	m_cbbEHMode.AddString(_T("EH disable after power-up")) ;

	m_cbbWIP.AddString(_T("RF busy mode")) ;
	m_cbbWIP.AddString(_T("RF Write in progress")) ;

	m_cbbEHEN.AddString(_T("EH diable")) ;
	m_cbbEHEN.AddString(_T("EH enable")) ;

	m_edtFIELDON.EnableWindow(FALSE) ;

	hp= NULL ;
	m_bntConnectTag.EnableWindow(TRUE) ;
	m_bntDisconnTag.EnableWindow(FALSE) ;
	m_bntGetTagSys.EnableWindow(FALSE) ;
	m_bntRSB.EnableWindow(FALSE) ;
	m_bntWSB.EnableWindow(FALSE) ;
	m_bntRSSB.EnableWindow(FALSE) ;
	m_bntLockSect.EnableWindow(FALSE) ;
	m_bntUpdatePwd.EnableWindow(FALSE) ;
	m_bntAuthPwd.EnableWindow(FALSE) ;
	m_bntWriteDSFID.EnableWindow(FALSE) ;
	m_bntLockDSFID.EnableWindow(FALSE) ;
	m_bntWriteAFI.EnableWindow(FALSE) ;
	m_bntLockAFI.EnableWindow(FALSE) ;
	m_bntRMB.EnableWindow(FALSE) ;
	m_bntSetCfgEH.EnableWindow(FALSE) ;
	m_bntSetCfgDO.EnableWindow(FALSE) ;
	m_bntReadCfgByte.EnableWindow(FALSE) ;
	m_bntSetCtrlRegEHEN.EnableWindow(FALSE) ;
	m_bntReadCtrlReg.EnableWindow(FALSE) ;
	m_bntWMB.EnableWindow(FALSE) ;
	/* Block data edit */
	UINT8 buffer[5] ;
	memset(buffer,0,sizeof(buffer));
	m_edtBlockData.SetData(buffer,sizeof(buffer)) ;
	m_edtBlockData.m_sa =0 ;

	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void DlgTagM24LR16E::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
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
	iret = ISO15693_Connect(hr,RFID_ISO15693_PICC_ST_M24LR16E_ID,addrmode,u,&hp);
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
			MessageBox(_T( "reset tag fail!"),_T("error"),MB_OK) ;
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
	m_bntLockSect.EnableWindow(TRUE) ;
	m_bntUpdatePwd.EnableWindow(TRUE) ;
	m_bntAuthPwd.EnableWindow(TRUE) ;
	m_bntWriteDSFID.EnableWindow(TRUE) ;
	m_bntLockDSFID.EnableWindow(TRUE) ;
	m_bntWriteAFI.EnableWindow(TRUE) ;
	m_bntLockAFI.EnableWindow(TRUE) ;
	m_bntRMB.EnableWindow(TRUE) ;
	m_bntSetCfgEH.EnableWindow(TRUE) ;
	m_bntSetCfgDO.EnableWindow(TRUE) ;
	m_bntReadCfgByte.EnableWindow(TRUE) ;
	m_bntSetCtrlRegEHEN.EnableWindow(TRUE) ;
	m_bntReadCtrlReg.EnableWindow(TRUE) ;
	m_bntWMB.EnableWindow(TRUE);
fail:
	return;
}

void DlgTagM24LR16E::ShowError(INT err) 
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

void DlgTagM24LR16E::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	RDR_TagDisconnect(hr,hp) ;
	m_bntConnectTag.EnableWindow(TRUE) ;
	m_bntDisconnTag.EnableWindow(FALSE) ;
	m_bntGetTagSys.EnableWindow(FALSE) ;
	m_bntRSB.EnableWindow(FALSE) ;
	m_bntWSB.EnableWindow(FALSE) ;
	m_bntRSSB.EnableWindow(FALSE) ;
	m_bntLockSect.EnableWindow(FALSE) ;
	m_bntUpdatePwd.EnableWindow(FALSE) ;
	m_bntAuthPwd.EnableWindow(FALSE) ;
	m_bntWriteDSFID.EnableWindow(FALSE) ;
	m_bntLockDSFID.EnableWindow(FALSE) ;
	m_bntWriteAFI.EnableWindow(FALSE) ;
	m_bntLockAFI.EnableWindow(FALSE) ;
	m_bntRMB.EnableWindow(FALSE) ;
	m_bntSetCfgEH.EnableWindow(FALSE) ;
	m_bntSetCfgDO.EnableWindow(FALSE) ;
	m_bntReadCfgByte.EnableWindow(FALSE) ;
	m_bntSetCtrlRegEHEN.EnableWindow(FALSE) ;
	m_bntReadCtrlReg.EnableWindow(FALSE) ;
	m_bntWMB.EnableWindow(FALSE) ;
}

void DlgTagM24LR16E::OnBnClickedButton16()
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

void DlgTagM24LR16E::OnBnClickedButton3()
{
	err_t iret;
    TCHAR dsfid[16] ;
	memset(dsfid,0,sizeof(dsfid));
	m_edtDSFID.GetWindowText(dsfid,sizeof(dsfid)/sizeof(TCHAR));
	BYTE v ;
	HexStrToBytes(dsfid,&v,NULL) ;
	iret = ISO15693_WriteDSFID(hr,hp,v) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void DlgTagM24LR16E::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	BYTE v ;
    TCHAR afi[16] ;
	memset(afi,0,sizeof(afi));
	m_edtAFI.GetWindowText(afi,sizeof(afi)/sizeof(TCHAR));
	
	HexStrToBytes(afi,&v,NULL) ;
	iret = ISO15693_WriteAFI(hr,hp,v) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
	}
	else {
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
}

void DlgTagM24LR16E::OnBnClickedButton4()
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

void DlgTagM24LR16E::OnBnClickedButton2()
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

void DlgTagM24LR16E::OnBnClickedButton12()
{
	err_t iret;
	DWORD uiPwd ;
	BYTE pwdno;
	UINT8 byPwd[4];
	TCHAR sPwd[32];
	memset(sPwd,0,sizeof(sPwd));
	m_edtAuthPwd.GetWindowText(sPwd,sizeof(sPwd)/sizeof(TCHAR));
	HexStrToBytes(sPwd,byPwd,NULL) ;
	//memcpy(&uiPwd,byPwd,4) ; 
	uiPwd = (byPwd[0] & 0xff) | (byPwd[1] << 8 & 0xff00) | (byPwd[2] << 16 & 0xff0000) | (byPwd[3] << 24 & 0xff000000) ;
	int idx = m_cbbPwdNum2.GetCurSel() ;
	if(idx < 0) {
		MessageBox(_T("select password")) ;
		return ;
	}
	pwdno = idx + 1;
	iret =STM24LR_PresentSectorPassword(hr,hp,pwdno,uiPwd) ;
	if(iret !=NO_ERR) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok")) ;

}

void DlgTagM24LR16E::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	DWORD uiPwdNew;
	BYTE pwdno;
	BYTE byPwdNew[4];
	TCHAR sPwdNew[32];
	memset(sPwdNew,0,sizeof(sPwdNew));
	m_edtNewPwd.GetWindowText(sPwdNew,sizeof(sPwdNew)/sizeof(TCHAR));
	HexStrToBytes(sPwdNew,byPwdNew,NULL) ;
	//memcpy(&uiPwdNew,byPwdNew,4) ;
	//memcpy(&uiPwdOld,byPwdOld,4) ;
	uiPwdNew = (byPwdNew[0] & 0xff) | (byPwdNew[1] << 8 & 0xff00) | (byPwdNew[2] << 16 & 0xff0000) | (byPwdNew[3] << 24 & 0xff000000) ;
	
	int idx = m_cbbPwdNum1.GetCurSel() ;
	if(idx < 0) {
		MessageBox(_T("select password")) ;
		return ;
	}
	pwdno = idx +1;
	iret =STM24LR_WriteSectorPassword(hr,hp,pwdno,uiPwdNew) ;
	if(iret !=NO_ERR) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok")) ;
}

void DlgTagM24LR16E::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	UINT8 block[4] ;
	DWORD blockno ;
	INT32 idx;
	m_edtBlockData.GetData(block,1,4) ;
	idx = m_cbbBlkNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	blockno = idx;
	iret = ISO15693_WriteSingleBlock(hr,hp,blockno,block,4) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;

}

void DlgTagM24LR16E::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOLEAN read_ssb ;
	read_ssb = TRUE ;
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
	DWORD bytesRead =0 ;
	iret = ISO15693_ReadSingleBlock(hr,hp,read_ssb,blockno,block,sizeof(block), &bytesRead) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return ;
	}
	UpdateData(TRUE);
	m_edtBlockData.SetData(block ,bytesRead) ;
	m_edtBlockData.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK);

}

void DlgTagM24LR16E::OnBnClickedButton11()
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
	DWORD bytesRead =0 ;
	iret =ISO15693_GetBlockSecStatus(hr,hp,blockno,numOfBlocks,buffer,sizeof(buffer),&bytesRead) ;
	if(iret != NO_ERR) {
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
	m_edtBlockData.SetData(blocks ,nlen) ;
	m_edtBlockData.RedrawWindow() ;

}

void DlgTagM24LR16E::OnBnClickedButton15()
{
	BYTE sectornum,pwdnum,accesstype ;
	INT32 idx;
	idx = m_cbbSectNum.GetCurSel() ;
	if(idx < 0) {
		MessageBox(_T("select sector number"),_T(""),MB_OK) ;
		return ;
	}
	sectornum = idx;
	idx =m_cbbAccessType.GetCurSel() ;
	if(idx <0 ){
		MessageBox(_T("select access type"),_T(""),MB_OK) ;
		return ;
	}
	accesstype=  idx;
	idx = m_cbbPassNum.GetCurSel();
	if(idx < 0) {
		MessageBox(_T("select password num"),_T(""),MB_OK) ;
		return ;
	}
	pwdnum =idx + 1;
	err_t iret ;
	iret =STM24LR_LockSector(hr,hp,sectornum,accesstype,pwdnum) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK);

}

void DlgTagM24LR16E::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD blockno ;
	DWORD numOfBlocks;
	DWORD numOfBlocksRead ;
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
	numOfBlocks = idx+1 ;
	err_t iret;
	UINT8  *buffer ;
	buffer  = new BYTE[numOfBlocks * 5] ;
	if(!buffer) {
		MessageBox(_T("Memory allocate fail"),_T(""),MB_OK) ;
		return ;
	}
	DWORD bytesRead = 0;
	numOfBlocksRead =0 ;
	iret =ISO15693_ReadMultiBlocks(hr,hp,read_ssb,blockno,numOfBlocks,&numOfBlocksRead,buffer,numOfBlocks * 5,&bytesRead) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
		if(buffer) delete[]  buffer ;
		return;
	}
	UpdateData(TRUE);
	m_edtBlockData.SetData(buffer ,bytesRead) ;
	m_edtBlockData.RedrawWindow() ;
	MessageBox(_T("ok"),_T(""),MB_OK) ;
	if(buffer) delete[]  buffer ;
}

void DlgTagM24LR16E::OnCbnSelchangeBlkno()
{
	int idx ;
	int block_no,num_blocks,block_size;
	BOOL read_ssb ;
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
	UINT8 *buf ;
	buf = new UINT8[num_blocks * block_size ] ;
	memset(buf,0,num_blocks * block_size) ;
	m_edtBlockData.m_sa =block_no ;
	m_edtBlockData.m_bpr =block_size ;
	m_edtBlockData.SetData(buf,num_blocks * block_size) ;
	m_edtBlockData.RedrawWindow();
	delete[] buf;
}

void DlgTagM24LR16E::OnCbnSelchangeNumblocks()
{
	OnCbnSelchangeBlkno();
}

void DlgTagM24LR16E::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCbnSelchangeBlkno();
}

void DlgTagM24LR16E::OnBnClickedButton20()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	BYTE cfgbyte;
	iret = STM24LR_ReadCFG(hr,hp,&cfgbyte) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return ;		
	}
	UINT8 energy_harvesting_level ;
	UINT8 cfg_EH_mode ;
	UINT8 cfg_DO;

	energy_harvesting_level = cfgbyte & 0x03;
	cfg_EH_mode = (cfgbyte >> 2 ) & 0x01 ;
	cfg_DO = (cfgbyte >> 3 ) & 0x01;
	m_cbbEnergyHarvesting.SetCurSel(energy_harvesting_level) ;
	m_cbbEHMode.SetCurSel(cfg_EH_mode) ;
	m_cbbWIP.SetCurSel(cfg_DO) ;
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void DlgTagM24LR16E::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	INT32 idx ;
	BYTE energy_harvesting ;
	BYTE eh_mode;
	idx = m_cbbEnergyHarvesting.GetCurSel() ;
	if(idx < 0) {
		MessageBox(_T("select energy harvesting level"),_T(""),MB_OK) ;
		return ;
	}
	energy_harvesting = idx ;
	idx = m_cbbEHMode.GetCurSel() ;
	if(idx <  0) {
		MessageBox(_T("select EH mode "),_T("") ,MB_OK) ;
		return ;
	}
	eh_mode  = idx ;
	iret =STM24LR_WriteEHCfg(hr,hp,energy_harvesting , eh_mode) ; 
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void DlgTagM24LR16E::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	INT32 idx ;
	BYTE do_mode ;
	idx = m_cbbWIP.GetCurSel() ;
	if(idx < 0) {
		MessageBox(_T("select DO mode"),_T(""),MB_OK) ;
		return ;
	}
	do_mode = idx ;
	iret =STM24LR_WriteDOCfg(hr,hp,do_mode) ; 
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void DlgTagM24LR16E::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	INT32 idx ;
	BYTE eh_en ;
	idx = m_cbbEHEN.GetCurSel() ;
	if(idx < 0) {
		MessageBox(_T("select EH enable/disable"),_T(""),MB_OK) ;
		return ;
	}
	eh_en = idx ;

	iret =STM24LR_SetRstEHEn(hr,hp,eh_en) ; 
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void DlgTagM24LR16E::OnBnClickedButton21()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	BYTE ctrlreg;
	iret = STM24LR_CheckEHEn(hr,hp,&ctrlreg) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return ;		
	}
	UINT8 EH_en ;
	UINT8 FIELD_ON ;

	EH_en = ctrlreg & 0x01;
	FIELD_ON= ctrlreg >> 1 & 0x01;

	m_cbbEHEN.SetCurSel(EH_en) ;
	TCHAR str[64] ;
	memset(str,0,sizeof(str)) ;
	_itot(FIELD_ON,str,10) ;
	m_edtFIELDON.SetWindowText(str) ;
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}


void DlgTagM24LR16E::OnBnClickedButton26()
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
		m_edtBlockData.GetData(blocksdata + i*4,i*5 + 1,4) ;
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
