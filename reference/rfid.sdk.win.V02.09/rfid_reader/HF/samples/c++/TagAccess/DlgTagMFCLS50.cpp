// DlgTagMFCLS50.cpp : 实现文件
//

#include "stdafx.h"
#include "rfidlib.h"
#include "rfidlib_aip_iso14443a.h"
#include "DlgTagMFCLS50.h"

#include "gfunctions.h"
#include "rfidlib_reader.h"



// CDlgTagMFCLS50 对话框

IMPLEMENT_DYNAMIC(CDlgTagMFCLS50, CDialog)

CDlgTagMFCLS50::CDlgTagMFCLS50(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTagMFCLS50::IDD, pParent)
{

}

CDlgTagMFCLS50::~CDlgTagMFCLS50()
{
}

void CDlgTagMFCLS50::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UIDS, m_cbbUIDs);
	DDX_Control(pDX, IDC_UIDS2, m_cbbKeyType);
	DDX_Control(pDX, IDC_BUTTON13, m_bntConnect);
	DDX_Control(pDX, IDC_BUTTON14, m_bntDisconnect);
	DDX_Control(pDX, IDC_BUTTON6, m_bntAuthenticate);
	DDX_Control(pDX, IDC_BUTTON1, m_bntReadBlock);
	DDX_Control(pDX, IDC_BUTTON2, m_bntWriteBlock);
	DDX_Control(pDX, IDC_BUTTON3, m_bntIncrement);
	DDX_Control(pDX, IDC_BUTTON5, m_bntDecrement);
	DDX_Control(pDX, IDC_BUTTON4, m_bntRestore);
	DDX_Control(pDX, IDC_BUTTON27, m_bntFormatValueBlock);
	DDX_Control(pDX, IDC_UIDS3, m_blkAddr);
	DDX_Control(pDX, IDC_ICODESLI_BD, m_editDB);
	DDX_Control(pDX, IDC_ICODESLI_BD2, m_REdtKey);
	DDX_Control(pDX, IDC_EDIT2, m_edtValue);
}


BEGIN_MESSAGE_MAP(CDlgTagMFCLS50, CDialog)
	ON_BN_CLICKED(IDC_BUTTON13, &CDlgTagMFCLS50::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlgTagMFCLS50::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgTagMFCLS50::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlgTagMFCLS50::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgTagMFCLS50::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON27, &CDlgTagMFCLS50::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgTagMFCLS50::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgTagMFCLS50::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON12, &CDlgTagMFCLS50::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgTagMFCLS50::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_UIDS3, &CDlgTagMFCLS50::OnCbnSelchangeUids3)
END_MESSAGE_MAP()


// CDlgTagMFCLS50 消息处理程序
BOOL CDlgTagMFCLS50::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	hp = NULL ;
	m_bntConnect.EnableWindow(TRUE) ;
	m_bntDisconnect.EnableWindow(FALSE) ;
	m_bntAuthenticate.EnableWindow(FALSE) ;
	m_bntReadBlock.EnableWindow(FALSE) ;
	m_bntWriteBlock.EnableWindow(FALSE) ;
	m_bntRestore.EnableWindow(FALSE) ;
	m_bntIncrement.EnableWindow(FALSE) ;
	m_bntDecrement.EnableWindow(FALSE) ;
	m_bntFormatValueBlock.EnableWindow(FALSE) ;

	for(int i=0;i<64;i++) {
		CString strAddr;
		strAddr.Format(_T("%d") , i) ;
		m_blkAddr.AddString(strAddr) ;
	}
	if(m_blkAddr.GetCount() > 0)m_blkAddr.SetCurSel( 0) ;
	
	m_cbbKeyType.AddString(_T("KeyA")) ;
	m_cbbKeyType.AddString(_T("KeyB")) ;
	m_cbbKeyType.SetCurSel(0) ;
	

	BYTE buffer[16] ;
	m_REdtKey.SetOptions(FALSE,TRUE ,FALSE,FALSE) ;
	m_REdtKey.m_bpr = 6;
	memset(buffer,0xff,sizeof(buffer)) ;
	m_REdtKey.SetData(buffer,6) ;
	m_REdtKey.m_sa =0 ;

	
	memset(buffer,0,sizeof(buffer));
	m_editDB.SetOptions(FALSE ,TRUE ,TRUE ,FALSE ) ;
	m_editDB.m_bpr = 16;
	m_editDB.SetData(buffer,sizeof(buffer)) ;
	m_editDB.m_sa =0 ;

	m_edtValue.SetWindowText(_T("0")) ;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgTagMFCLS50::ShowError(INT err) 
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

void CDlgTagMFCLS50::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR uid[32] ;
	memset(uid,0,sizeof(uid));
	m_cbbUIDs.GetWindowText(uid,sizeof(uid)/sizeof(TCHAR)) ;	
	err_t iret;
	BYTE u[8] ;
	HexStrToBytes(uid,u,NULL) ;
	iret = MFCL_Connect(hr,0,u,&hp);
	if(iret != NO_ERR) {
		ShowError(iret) ;
		goto fail;
	}
	m_bntConnect.EnableWindow(FALSE) ;
	m_bntDisconnect.EnableWindow(TRUE) ;
	m_bntAuthenticate.EnableWindow(TRUE) ;
	m_bntReadBlock.EnableWindow(TRUE) ;
	m_bntWriteBlock.EnableWindow(TRUE) ;
	m_bntRestore.EnableWindow(TRUE) ;
	m_bntIncrement.EnableWindow(TRUE) ;
	m_bntDecrement.EnableWindow(TRUE) ;
	m_bntFormatValueBlock.EnableWindow(TRUE) ;

	
fail:
	return ;
}

void CDlgTagMFCLS50::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	RDR_TagDisconnect(hr,hp) ;
	m_bntConnect.EnableWindow(TRUE) ;
	m_bntDisconnect.EnableWindow(FALSE) ;
	m_bntAuthenticate.EnableWindow(FALSE) ;
	m_bntReadBlock.EnableWindow(FALSE) ;
	m_bntWriteBlock.EnableWindow(FALSE) ;
	m_bntRestore.EnableWindow(FALSE) ;
	m_bntIncrement.EnableWindow(FALSE) ;
	m_bntDecrement.EnableWindow(FALSE) ;
	m_bntFormatValueBlock.EnableWindow(FALSE) ;
}

void CDlgTagMFCLS50::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	int idx;
	BYTE blkAddr;
	BYTE blkData[16] ;

	idx  = m_blkAddr.GetCurSel() ;
	if(idx ==-1) {
		MessageBox(_T("select block address "),_T("") ,MB_OK) ;
		return ;
	}
	blkAddr = idx & 0xff;

	iret = MFCL_ReadBlock(hr,hp,blkAddr ,blkData ,sizeof(blkData)) ;
	if(iret != 0) {
		ShowError(iret) ;
		return ;
	}
	UpdateData(TRUE);
	m_editDB.SetData(blkData,16) ;
	m_editDB.RedrawWindow() ;
}

void CDlgTagMFCLS50::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	int idx ;
	BYTE blkAddr;
	BYTE keyType ;
	BYTE key[6] ;
	idx  = m_blkAddr.GetCurSel() ;
	if(idx ==-1) {
		MessageBox(_T("select block address "),_T("") ,MB_OK) ;
		return ;
	}
	blkAddr = idx  & 0xff ;
	idx = m_cbbKeyType.GetCurSel() ;
	if(idx == -1 ){
		MessageBox(_T("select key type ,please"),_T("") ,MB_OK) ;
		return  ;
	}
	keyType = idx & 0xff ; //0: KEY A ,1:KEY B
	m_REdtKey.GetData(key ,0,6 ) ;
	iret = MFCL_Authenticate(hr,hp ,blkAddr ,keyType ,key) ;
	if(iret !=0) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok") ,_T(""),MB_OK) ;
}

void CDlgTagMFCLS50::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret;
	BYTE block[16] ;
	BYTE blkAddr;
	int idx;
	idx  = m_blkAddr.GetCurSel() ;
	if(idx ==-1) 
	{
		MessageBox(_T("select block address "),_T("") ,MB_OK) ;
		return ;
	}
	/*if (idx==3)
	{
		CAccessConditions dlg;
		dlg.ComputingAcessBuff(block);
		if (dlg.DoModal()!=IDOK)
		{
			return;
		}
		m_editDB.SetData(block,16);
	}*/
	blkAddr = idx & 0xff ;
	m_editDB.GetData(block,0,16) ;
	iret = MFCL_WriteBlock(hr,hp,blkAddr , block ) ;
	if(iret != NO_ERR) 
	{
		//MessageBox("fail","",MB_OK) ;
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagMFCLS50::OnBnClickedButton27()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	BYTE blkAddr;
	int idx;
	DWORD value ;
	idx  = m_blkAddr.GetCurSel() ;
	if(idx ==-1) {
		MessageBox(_T("select block address "),_T("") ,MB_OK) ;
		return ;
	}
	blkAddr = idx & 0xff;
	CString strval ;
	m_edtValue.GetWindowText(strval) ;
	value =_ttoi(strval ) ;

	iret = MFCL_FormatValueBlock(hr,hp ,blkAddr,value) ;
	if(iret != 0){
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagMFCLS50::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	BYTE blkAddr;
	int idx;
	DWORD value ;

	idx  = m_blkAddr.GetCurSel() ;
	if(idx ==-1) {
		MessageBox(_T("select block address "),_T("") ,MB_OK) ;
		return ;
	}
	blkAddr = idx & 0xff;

	CString strval ;
	m_edtValue.GetWindowText(strval) ;
	value =_ttoi(strval ) ;

	iret = MFCL_Increment(hr,hp,blkAddr ,value ) ;
	if(iret != 0) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;

}

void CDlgTagMFCLS50::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	BYTE blkAddr;
	int idx;
	DWORD value ;
	idx  = m_blkAddr.GetCurSel() ;
	if(idx ==-1) {
		MessageBox(_T("select block address "),_T("") ,MB_OK) ;
		return ;
	}
	blkAddr = idx & 0xff;

	CString strval ;
	m_edtValue.GetWindowText(strval) ;
	value =_ttoi(strval ) ;

	iret = MFCL_Decrement(hr,hp,blkAddr ,value ) ;
	if(iret != 0) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagMFCLS50::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	BYTE blkAddr;
	int idx;
	DWORD value ;
	idx  = m_blkAddr.GetCurSel() ;
	if(idx ==-1) {
		MessageBox(_T("select block address "),_T("") ,MB_OK) ;
		return ;
	}
	blkAddr = idx & 0xff;

	iret = MFCL_Transfer(hr,hp,blkAddr ) ;
	if(iret != 0) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagMFCLS50::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	BYTE blkAddr;
	int idx;
	DWORD value ;

	idx  = m_blkAddr.GetCurSel() ;
	if(idx ==-1) {
		MessageBox(_T("select block address "),_T("") ,MB_OK) ;
		return ;
	}
	blkAddr = idx & 0xff;
	iret = MFCL_Restore(hr,hp,blkAddr) ;
	if(iret != 0) {
		ShowError(iret) ;
		return ;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagMFCLS50::OnCbnSelchangeUids3()
{
	// TODO: 在此添加控件通知处理程序代码
	/*int idx = m_blkAddr.GetCurSel();
	if (idx!=3)
	{
		m_editDB.EnableWindow(TRUE);
		return;
	}
	m_editDB.EnableWindow(FALSE);*/
}
