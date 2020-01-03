// demo_m24rl64Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "demo_m24rl64.h"
#include "demo_m24rl64Dlg.h"
#include "dlginventory.h"
#include "DlgTagIcodesli.h"
#include "DlgTagTihfiPlus.h"
#include "DlgTagIcodeslix.h"
#include "DlgTagTiHFIStandard.h"
#include "DlgTagM24.h"
#include "DlgTagM24LR16E.h"
#include "TagMb89R118C.h"
#include "DlgTagMFCLS50.h"
#include "DlgTagRF430FRL15x.h"
#include "dlgopen.h"
#include "rfidlib_reader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cdemo_m24rl64Dlg 对话框




Cdemo_m24rl64Dlg::Cdemo_m24rl64Dlg(CWnd* pParent /*=NULL*/)
: CDialog(Cdemo_m24rl64Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cdemo_m24rl64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX,IDC_COMBO11,m_cbbAccessAnts) ;
	DDX_Control(pDX,IDC_BUTTON2,m_bntSetAccessAnt) ;
}

BEGIN_MESSAGE_MAP(Cdemo_m24rl64Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &Cdemo_m24rl64Dlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &Cdemo_m24rl64Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cdemo_m24rl64Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cdemo_m24rl64Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()

void Cdemo_m24rl64Dlg::OnClose()
{
	for(int i =0 ;i<m_tabDlgs.GetCount();i++) {
		if(m_tabDlgs[i]) {
			m_tabDlgs[i]->DestroyWindow() ;
			delete m_tabDlgs[i] ;
		}
	}
	m_tabDlgs.RemoveAll() ;

	RDR_Close(hr) ;
	hr =0 ;
	CDialog::OnClose() ;
}




BOOL Cdemo_m24rl64Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// Show Open dialog 
	CDlgOpen dlg ;
	dlg.DoModal() ;
	if(hr==RFID_HANDLE_NULL){
		//m_tab.EnableWindow(FALSE) ;
		this->EndDialog(0) ;
	}
	/* get supported air interface protocol */
	int index =0 ;
	int iret =0 ;
	DWORD AIType ;
	while(1) {
		CSupportedAIP aip ;
		iret =RDR_GetSupportedAirInterfaceProtocol( hr,index,&AIType) ;
		if(iret != 0) {
			break;
		}
		TCHAR namebuffer[128] ;
		memset(namebuffer,0,sizeof(namebuffer)) ;
		RDR_GetAirInterfaceProtName(hr,AIType,namebuffer ,sizeof(namebuffer)) ;
		aip.m_aip = AIType ;
		aip.m_en = TRUE ;
		aip.m_name.Format(_T("%s") ,namebuffer ) ;
		m_supportedAIP.Add(aip) ;
		index++ ;
	}

	// TODO: 在此添加额外的初始化代码
	TCITEM   item;   
	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Tag Inventory");
	m_tab.InsertItem(0,&item) ;

	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Tag ICODE SLI");
	m_tab.InsertItem(1,&item) ;

	item.mask = TCIF_TEXT;
	item.pszText = _T("Tag ICODE SLIX" );
	m_tab.InsertItem(2,&item) ;

	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Tag Ti-HFI-Plus");
	m_tab.InsertItem(3,&item) ;

	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Tag Ti-HFI-Standard");
	m_tab.InsertItem(4,&item) ;


	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("ST M24LR16E");
	m_tab.InsertItem(5,&item) ;

	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("ST M24LR64");
	m_tab.InsertItem(6,&item) ;


	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("RF430FRL15x");
	m_tab.InsertItem(7,&item) ;

	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Mifare S50");
	m_tab.InsertItem(8,&item) ;

	CDialog *pdlg ;
	pdlg = new CDlgInventory(); 
	pdlg->Create(IDD_INVENTORY,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;


	pdlg = new CDlgTagIcodesli() ;
	pdlg->Create(IDD_TAG_ICODESLI ,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	pdlg = new CDlgTagIcodeslix() ;
	pdlg->Create(IDD_TAG_ICODESLIX ,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	pdlg = new CDlgTagTihfiPlus() ;
	pdlg->Create(IDD_TAG_TIHFI_PLUS,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	//pdlg = new CTagMb89r118c() ;
	//pdlg->Create(IDD_TAG_MB89R118C,&m_tab) ;
	//pdlg->ShowWindow(SW_HIDE) ;
	//m_tabDlgs.Add(pdlg) ;

	pdlg= new CDlgTagTiHFIStandard(); 
	pdlg->Create(IDD_TAG_TIHFI_STANDARD,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;



	pdlg= new DlgTagM24LR16E(); 
	pdlg->Create(IDD_TAG_M24LR16E,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	pdlg= new CDlgTagM24(); 
	pdlg->Create(IDD_TAG_M24RL64,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	pdlg = new CDlgTagRF430FRL15x();
	pdlg->Create(IDD_TAG_RF430FRL15XH,&m_tab);
	pdlg->ShowWindow(SW_HIDE);
	m_tabDlgs.Add(pdlg);

	pdlg = new CDlgTagMFCLS50() ;
	pdlg->Create(IDD_TAG_MFCL_S50,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;



	if(m_tabDlgs.GetCount() > 0) {
		old_page= 0 ;
		RECT rect;
		m_tab.GetClientRect(&rect) ;
		m_tabDlgs[old_page]->SetWindowPos(NULL,10,30,rect.right -20,rect.bottom-40,SWP_SHOWWINDOW);
		m_tab.SetCurSel( 0) ;
	}



	for(int i=0;i<AntennaIFCountOfReader;i++) {
		CString s1;
		s1.Format(_T("Antenna#%d"),i+1 ) ;
		m_cbbAccessAnts.AddString(s1) ;
	}
	m_bntSetAccessAnt.EnableWindow(FALSE) ;
	m_cbbAccessAnts.EnableWindow(FALSE) ;
	if( AntennaIFCountOfReader > 1) {
		m_bntSetAccessAnt.EnableWindow(TRUE) ;
		m_cbbAccessAnts.EnableWindow(TRUE) ;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cdemo_m24rl64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cdemo_m24rl64Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR Cdemo_m24rl64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cdemo_m24rl64Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	RECT rect;
	int idx ;
	m_tab.GetClientRect(&rect) ;
	idx  =m_tab.GetCurSel() ;
	m_tabDlgs[old_page]->ShowWindow(SW_HIDE) ; 
	m_tabDlgs[idx]->SetWindowPos(NULL,10,30,rect.right -20,rect.bottom-40,SWP_SHOWWINDOW);
	m_tabDlgs[idx]->BringWindowToTop() ;

	if(old_page == 0 && idx > 0) {
		((CDlgInventory *)(m_tabDlgs[0]))->OnBnClickedButton2() ;
	}
	if(idx == 1) {

		/* ICODE SLI */
		((CDlgTagIcodesli *)(m_tabDlgs[idx]))->m_cbbUIDs.SetWindowText(_T("")) ;
		while(((CDlgTagIcodesli *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount()> 0)
			((CDlgTagIcodesli *)(m_tabDlgs[idx]))->m_cbbUIDs.DeleteString(0) ;
		for(INT32 i=0;i<m_taglist.GetCount();i++) {
			if(m_taglist[i].m_AIP == RFID_APL_ISO15693_ID) { //m_taglist[i].m_type == RFID_ISO15693_PICC_ICODE_SLI_ID &&
				((CDlgTagIcodesli *)(m_tabDlgs[idx]))->m_cbbUIDs.AddString(m_taglist[i].m_uid) ;
				((CDlgTagIcodesli *)(m_tabDlgs[idx]))->m_cbbUIDs.SetItemData(((CDlgTagIcodesli *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount() -1,m_taglist[i].m_type) ;
			}
		}
	}
	else if(idx == 2) {
		((CDlgTagIcodeslix *)(m_tabDlgs[idx]))->m_cbbUIDs.SetWindowText(_T("")) ;
		while(((CDlgTagIcodeslix *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount()> 0)
			((CDlgTagIcodeslix *)(m_tabDlgs[idx]))->m_cbbUIDs.DeleteString(0) ;
		for(INT32 i=0;i<m_taglist.GetCount();i++) {
			if( m_taglist[i].m_AIP == RFID_APL_ISO15693_ID) { //(m_taglist[i].m_type == RFID_ISO15693_PICC_ICODE_SLIX_ID || (m_taglist[i].m_type == RFID_ISO15693_PICC_ICODE_SLIX2_ID) )&&
				((CDlgTagIcodeslix *)(m_tabDlgs[idx]))->m_cbbUIDs.AddString(m_taglist[i].m_uid) ;
				((CDlgTagIcodeslix *)(m_tabDlgs[idx]))->m_cbbUIDs.SetItemData(((CDlgTagIcodeslix *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount() -1,m_taglist[i].m_type) ;
			}
		}			
	}
	else if(idx == 3) {

		((CDlgTagTihfiPlus *)(m_tabDlgs[idx]))->m_cbbUIDs.SetWindowText(_T("")) ;
		while(((CDlgTagTihfiPlus *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount()> 0)
			((CDlgTagTihfiPlus *)(m_tabDlgs[idx]))->m_cbbUIDs.DeleteString(0) ;
		for(INT32 i=0;i<m_taglist.GetCount();i++) {
			if(m_taglist[i].m_type == RFID_ISO15693_PICC_TI_HFI_PLUS_ID &&
				m_taglist[i].m_AIP == RFID_APL_ISO15693_ID) {
					((CDlgTagTihfiPlus *)(m_tabDlgs[idx]))->m_cbbUIDs.AddString(m_taglist[i].m_uid) ;
			}
		}			
	}
	else if(idx == 4) {
		((CDlgTagTiHFIStandard *)(m_tabDlgs[idx]))->m_cbbUIDs.SetWindowText(_T("")) ;
		while(((CDlgTagTiHFIStandard *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount()> 0)
			((CDlgTagTiHFIStandard *)(m_tabDlgs[idx]))->m_cbbUIDs.DeleteString(0) ;
		for(INT32 i=0;i<m_taglist.GetCount();i++) {
			if(m_taglist[i].m_type == RFID_ISO15693_PICC_TIHFI_STANDARD_ID &&
				m_taglist[i].m_AIP == RFID_APL_ISO15693_ID) {
					((CDlgTagTiHFIStandard *)(m_tabDlgs[idx]))->m_cbbUIDs.AddString(m_taglist[i].m_uid) ;
			}
		}		
	}
	else if(idx == 6) {
		((CDlgTagM24 *)(m_tabDlgs[idx]))->m_cbbUIDs.SetWindowText(_T("")) ;
		while(((CDlgTagM24 *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount()> 0)
			((CDlgTagM24 *)(m_tabDlgs[idx]))->m_cbbUIDs.DeleteString(0) ;
		for(INT32 i=0;i<m_taglist.GetCount();i++) {
			if(m_taglist[i].m_type == RFID_ISO15693_PICC_ST_M24LR64_ID &&
				m_taglist[i].m_AIP == RFID_APL_ISO15693_ID) {
					((CDlgTagM24 *)(m_tabDlgs[idx]))->m_cbbUIDs.AddString(m_taglist[i].m_uid) ;
			}
		}		
	}
	else if(idx == 5) {
		((DlgTagM24LR16E *)(m_tabDlgs[idx]))->m_cbbUIDs.SetWindowText(_T("")) ;
		while(((DlgTagM24LR16E *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount()> 0)
			((DlgTagM24LR16E *)(m_tabDlgs[idx]))->m_cbbUIDs.DeleteString(0) ;
		for(INT32 i=0;i<m_taglist.GetCount();i++) {
			if(m_taglist[i].m_type == RFID_ISO15693_PICC_ST_M24LR16E_ID &&
				m_taglist[i].m_AIP == RFID_APL_ISO15693_ID) {
					((DlgTagM24LR16E *)(m_tabDlgs[idx]))->m_cbbUIDs.AddString(m_taglist[i].m_uid) ;
			}
		}		
	}
	else if (idx==7)
	{
		((CDlgTagRF430FRL15x *)(m_tabDlgs[idx]))->m_cbbUIDs.SetWindowText(_T("")) ;
		while(((CDlgTagRF430FRL15x *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount()> 0)
			((CDlgTagRF430FRL15x *)(m_tabDlgs[idx]))->m_cbbUIDs.DeleteString(0) ;
		for(INT32 i=0;i<m_taglist.GetCount();i++) {
			if(m_taglist[i].m_type == RFID_ISO15693_PICC_RF430FR12XH_ID &&
				m_taglist[i].m_AIP == RFID_APL_ISO15693_ID) {
					((CDlgTagRF430FRL15x *)(m_tabDlgs[idx]))->m_cbbUIDs.AddString(m_taglist[i].m_uid) ;
			}
		}	
	}
	else if(idx ==8) {
		((CDlgTagMFCLS50 *)(m_tabDlgs[idx]))->m_cbbUIDs.SetWindowText(_T("")) ;
		while(((CDlgTagMFCLS50 *)(m_tabDlgs[idx]))->m_cbbUIDs.GetCount()> 0)
			((CDlgTagMFCLS50 *)(m_tabDlgs[idx]))->m_cbbUIDs.DeleteString(0) ;
		for(INT32 i=0;i<m_taglist.GetCount();i++) {
			if(m_taglist[i].m_type == RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID &&
				m_taglist[i].m_AIP == RFID_APL_ISO14443A_ID) {
					((CDlgTagMFCLS50 *)(m_tabDlgs[idx]))->m_cbbUIDs.AddString(m_taglist[i].m_uid) ;
			}
		}		
	}

	old_page = idx ;

}

void Cdemo_m24rl64Dlg::ShowError(INT err) 
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

void Cdemo_m24rl64Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	err_t iret ;
	TCHAR capabilities[128] ;
	memset(capabilities,0,sizeof(capabilities));
	DWORD nSize ;
	nSize = sizeof(capabilities)/sizeof(TCHAR) ;
	iret =RDR_GetReaderInfor(hr,0,capabilities,&nSize) ;
	if(iret != NO_ERR) {
		ShowError(iret) ;
		return;
	}
	MessageBox(capabilities,_T(""),MB_OK) ;
}

void Cdemo_m24rl64Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx ;
	idx =m_cbbAccessAnts.GetCurSel() ;
	if(idx == -1 ) {
		MessageBox(_T("please select access antenna")) ;
		return ;
	}
	err_t iret;
	BYTE accessAnt ;
	accessAnt = idx+ 1;
	iret =RDR_SetAcessAntenna(hr,accessAnt) ;
	if(iret !=  NO_ERR) {
		ShowError(iret) ;
		return;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}
void Cdemo_m24rl64Dlg::OnOK()
{

}

void Cdemo_m24rl64Dlg::OnCancel()
{
	if(InventoryOn) {
		MessageBox(_T("Stop inventory first"),_T(""),MB_OK) ;
		return ;
	}
	CDialog::OnCancel() ;
}
void Cdemo_m24rl64Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR verBuf[64] ;
	memset(verBuf,0,sizeof(verBuf)) ;
	RDR_GetLibVersion(verBuf,sizeof(verBuf) / sizeof(TCHAR)) ;
	MessageBox(verBuf,_T(""),MB_OK) ;
}
