// mfcdemo1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcdemo1.h"
#include "mfcdemo1Dlg.h"
#include "DlgConfig.h"
#include "DlgGetReport.h"
#include "DlgControl.h"
#include "rfidlib.h"
#include "rfidlib_G101.h"
#include "rfidlib_G302.h"
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


// Cmfcdemo1Dlg 对话框




Cmfcdemo1Dlg::Cmfcdemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cmfcdemo1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfcdemo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_COMBO11, m_cbbCOMMType);
	DDX_Control(pDX, IDC_COMBO13, m_cbbComNames);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipAddr);
	DDX_Control(pDX, IDC_BUTTON1, m_bntOpen);
	DDX_Control(pDX, IDC_BUTTON2, m_bntClose);
	DDX_Control(pDX, IDC_BUTTON3, m_bntGetDevInfor);
	DDX_Control(pDX, IDC_CMBCMMTYPE,m_cbbCommunicateType);
	DDX_Control(pDX, IDC_COMBO2,m_cbbComBaud);
	DDX_Control(pDX, IDC_COMBO3,m_cbbComFrame);
}

BEGIN_MESSAGE_MAP(Cmfcdemo1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &Cmfcdemo1Dlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &Cmfcdemo1Dlg::OnTcnSelchangeTab1)
	ON_CBN_SELCHANGE(IDC_COMBO11, &Cmfcdemo1Dlg::OnCbnSelchangeCombo11)
	ON_BN_CLICKED(IDC_BUTTON2, &Cmfcdemo1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cmfcdemo1Dlg::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_CMBCMMTYPE,OnCbnSelchangeCmmtype)
	//ON_CBN_SELCHANGE(IDC_COMBO11, OnCbnSelchangeDevtype)
END_MESSAGE_MAP()


// Cmfcdemo1Dlg 消息处理程序

BOOL Cmfcdemo1Dlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	hr = 0 ; 
TCITEM   item;   
	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Device Configuration");
	m_tab.InsertItem(0,&item) ;
	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Get report");
	m_tab.InsertItem(1,&item) ;
	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Set output");
	m_tab.InsertItem(2,&item) ;

	CDialog *pdlg ;
	pdlg = new CDlgConfig(); 
	pdlg->Create(IDD_DLGCFG,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	pdlg = new CDlgGetReport() ;
	pdlg->Create(IDD_DLGGETREPORT ,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	pdlg = new CDlgControl() ;
	pdlg->Create(IDD_DLGCONTROL ,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	old_page= 0 ;
	RECT rect;
	m_tab.GetClientRect(&rect) ;
	m_tabDlgs[old_page]->SetWindowPos(NULL,10,30,rect.right -20,rect.bottom-40,SWP_SHOWWINDOW);
	m_tab.SetCurSel( 0) ;

	RDR_LoadReaderDrivers(_T("\\Drivers")) ;
	for(DWORD i=0;i<RDR_GetLoadedReaderDriverCount() ;i++)
	{
		DWORD nSize ;
		CRdrInfo rdrinfo ;
		TCHAR tmp[64] ;
		memset(tmp,0,sizeof(tmp)) ;
		nSize = sizeof(tmp) / sizeof(TCHAR);
		RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_CATALOG),tmp, &nSize) ;
		rdrinfo.m_Catalog= tmp ;
		if(rdrinfo.m_Catalog ==_T(RDRDVR_TYPE_MTGATE))
		{
			memset(tmp,0,sizeof(tmp)) ;
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_COMMTYPESUPPORTED),tmp,&nSize) ;
			rdrinfo.m_CommTypeSupported = _ttoi(tmp) ; 

			memset(tmp,0,sizeof(tmp));
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_NAME), tmp,&nSize) ;
			rdrinfo.m_name = tmp ;

			memset(tmp,0,sizeof(tmp)) ;
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_ID),tmp,&nSize) ;
			rdrinfo.m_productType = tmp ;

			m_readerList.Add(rdrinfo) ;
		}
	}

	for(int i= 0;i<m_readerList.GetCount();i++)
	{
		m_cbbCOMMType.AddString(m_readerList[i].m_name) ;
	}
	m_cbbCOMMType.SetCurSel(0) ;

	DWORD COMCount ;
	COMCount = COMPort_Enum() ;
	int iret;
	for(int i =0;i<COMCount ;i++)
	{
		TCHAR comname[64] ;
		memset(comname,0,sizeof(comname)) ;
		iret =  COMPort_GetEnumItem(i,comname,sizeof(comname)/ sizeof(TCHAR)) ;
		if(iret == 0)
		{
			m_cbbComNames.AddString(comname) ;
		}
	}
	if (COMCount>0)
	{
		m_cbbComNames.SetCurSel(0) ;
	}
	

	m_ipAddr.SetAddress(192,168,0,222) ;
	m_ipAddr.EnableWindow(FALSE) ;

	m_bntOpen.EnableWindow(TRUE) ;
	m_bntClose.EnableWindow(FALSE) ;
	m_bntGetDevInfor.EnableWindow(FALSE) ;

	m_cbbComBaud.AddString(_T("9600"));
	m_cbbComBaud.AddString(_T("38400"));
	m_cbbComBaud.AddString(_T("57600"));
	m_cbbComBaud.AddString(_T("115200"));
	m_cbbComBaud.SetCurSel(1);

	m_cbbComFrame.AddString(_T("8E1"));
	m_cbbComFrame.AddString(_T("8N1"));
	m_cbbComFrame.AddString(_T("8O1"));
	m_cbbComFrame.SetCurSel(0);

	OnCbnSelchangeCombo11();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cmfcdemo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cmfcdemo1Dlg::OnPaint()
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
HCURSOR Cmfcdemo1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cmfcdemo1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
    CString str;
	INT32 iret = 1;
	CString connstr ;
	m_cbbCommunicateType.GetWindowText(str);
	TCHAR com[64] ;
	int idx = m_cbbCOMMType.GetCurSel() ;
	memset(com,0,sizeof(com)) ;
	m_cbbComNames.GetWindowText(com,sizeof(com) / sizeof(TCHAR)) ;
	if (str==_T("COM"))
	{
		CString sBaud,sFrame;
		m_cbbComBaud.GetWindowText(sBaud);
		m_cbbComFrame.GetWindowText(sFrame);
		connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s;%s=%s;%s=%s"),_T(CONNSTR_NAME_RDTYPE),m_readerList[idx].m_name,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_COM) ,_T(CONNSTR_NAME_COMNAME),com,_T(CONNSTR_NAME_COMBARUD) ,sBaud, _T(CONNSTR_NAME_COMFRAME),sFrame , _T(CONNSTR_NAME_BUSADDR),_T("255")) ;
		iret = RDR_Open(connstr,&hr) ;//RDR_Open
	}
	else if (str==_T("TCP/IP"))
	{
		BYTE ip_b1,ip_b2,ip_b3,ip_b4;
		m_ipAddr.GetAddress(ip_b1,ip_b2,ip_b3,ip_b4) ;
		WORD port = 6012;
		CString ipStr;
		ipStr.Format(_T("%d.%d.%d.%d"),ip_b1,ip_b2,ip_b3,ip_b4) ;
		connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%d;%s=%s") ,_T(CONNSTR_NAME_RDTYPE),m_readerList[idx].m_name,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_NET),_T(CONNSTR_NAME_REMOTEIP),ipStr ,_T(CONNSTR_NAME_REMOTEPORT),port,_T(CONNSTR_NAME_LOCALIP),_T("")) ;
		iret = RDR_Open(connstr,&hr) ;
	}
	else
	{
		MessageBox(_T("Please select the type of communication!"),_T(""),MB_OK) ;
		return ;
	}
	//iret = 0;
	if(iret != 0) 
	{
		ShowError(iret ) ;
		return ;
	}

	CDlgControl  *pdlg  = (CDlgControl  *)m_tabDlgs[2] ;
	if(pdlg) 
	{
		while(pdlg->m_listOutputs.GetCount() > 0) 
		{
			pdlg->m_listOutputs.DeleteString(0) ;
		}
		pdlg->m_listOutputs.AddString(_T("Buzzer on board")) ;
		pdlg->m_listOutputs.AddString(_T("Output#1")) ;
		pdlg->m_listOutputs.AddString(_T("Output#2")) ;
		pdlg->m_listOutputs.AddString(_T("Output#3")) ;
		pdlg->m_listOutputs.AddString(_T("Output#4")) ;

		pdlg->m_cbbCtrlActiveTime.EnableWindow(TRUE) ;
		pdlg->m_cbbCtrlFrequence.EnableWindow(TRUE) ;
		pdlg->m_cbbCtrlDeactiveTime.EnableWindow(TRUE) ;
	}
	CDlgConfig  *pdlg2  = (CDlgConfig  *)m_tabDlgs[0] ;
	pdlg2->m_bntWrite.EnableWindow(FALSE) ;
	pdlg2->m_bntReadCfg.EnableWindow(TRUE) ;
	pdlg2->m_bntCfgReset.EnableWindow(TRUE) ;
	pdlg2->m_cfgIPAddr.EnableWindow(TRUE) ;
	pdlg2->m_cfgIPMask.EnableWindow(TRUE) ;
	pdlg2->m_cfgIPGW.EnableWindow(TRUE) ;
	pdlg2->m_cbbCfgRole.EnableWindow(TRUE) ;
	pdlg2->m_cbbCfgSyncNumber.EnableWindow(TRUE) ;
	pdlg2->m_cbbCfgWiegand.EnableWindow(TRUE) ;
	pdlg2->m_cbbDirectionReverSta.EnableWindow(TRUE) ;
	pdlg2->m_cbbRFPower.EnableWindow(TRUE) ;
	pdlg2->m_cbbAFISta.EnableWindow(TRUE) ;
	pdlg2->m_edtAFIVal.EnableWindow(TRUE) ;
	pdlg2->m_cbbQuickDisSta.EnableWindow(TRUE) ;
	pdlg2->m_cbbIrFuncSta.EnableWindow(TRUE) ;
	pdlg2->m_cbbAntSwitch.EnableWindow(TRUE) ;
	pdlg2->m_cbbAntCountUsage.EnableWindow(TRUE) ;
	pdlg2->m_cbbDaiDaKa.EnableWindow(TRUE) ;
	pdlg2->m_cbbDDKRestrictTime.EnableWindow(TRUE) ;
	pdlg2->m_cbbCfgCardFilter.EnableWindow(TRUE) ;
	m_bntOpen.EnableWindow(FALSE) ;
	m_bntClose.EnableWindow(TRUE) ;

	CDlgGetReport *pdlgReport  ;
	pdlgReport = (CDlgGetReport *)m_tabDlgs[1] ;
	pdlgReport->m_bntStart.EnableWindow(TRUE) ;
	pdlgReport->m_bntClear.EnableWindow(TRUE) ;

	CDlgControl *pDlgCtrl ;
	pDlgCtrl = (CDlgControl *) m_tabDlgs[2] ;
	pDlgCtrl->m_bntCtrlOutput.EnableWindow(TRUE) ;

	m_bntGetDevInfor.EnableWindow(TRUE) ;
	
}

void Cmfcdemo1Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
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

	old_page = idx;
}

void Cmfcdemo1Dlg::OnCbnSelchangeCombo11()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx;
	idx = m_cbbCOMMType.GetCurSel() ;

	m_cbbCommunicateType.ResetContent();
	//TRACE0("=====%d\n",m_readerList[idx].m_CommTypeSupported);
	if((m_readerList[idx].m_CommTypeSupported&COMMTYPE_COM_EN)>0)//支持串口
	{
		m_cbbCommunicateType.AddString(_T("COM"));
	}
	if ((m_readerList[idx].m_CommTypeSupported&COMMTYPE_NET_EN)>0)//
	{
		m_cbbCommunicateType.AddString(_T("TCP/IP"));
	}
	m_cbbCommunicateType.SetCurSel(0);
	OnCbnSelchangeCmmtype();
}

void Cmfcdemo1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int iret;
	if (hr!=NULL)
	{
		iret =  RDR_Close(hr) ;
		hr = 0 ;
	}
	
	m_bntOpen.EnableWindow(TRUE) ;
	m_bntClose.EnableWindow(FALSE) ;
	m_bntGetDevInfor.EnableWindow(FALSE) ;

	CDlgConfig *pdlgCfg  = (CDlgConfig *)m_tabDlgs[0] ;
	pdlgCfg->m_bntReadCfg.EnableWindow(FALSE) ;
	pdlgCfg->m_bntCfgReset.EnableWindow(FALSE) ;
	pdlgCfg->m_bntWrite.EnableWindow(FALSE) ;

	CDlgGetReport *pdlgReport  ;
	pdlgReport = (CDlgGetReport *)m_tabDlgs[1] ;
	pdlgReport->m_bntStart.EnableWindow(FALSE) ;
	pdlgReport->m_bntClear.EnableWindow(FALSE) ;

	CDlgControl *pDlgCtrl ;
	pDlgCtrl = (CDlgControl *) m_tabDlgs[2] ;
	pDlgCtrl->m_bntCtrlOutput.EnableWindow(FALSE) ;

}
void Cmfcdemo1Dlg::ShowError(int iret) 
{
	CString str;
	str.Format(_T("Error:%d"),iret) ;
	MessageBox(str,_T(""),MB_OK) ;
}

void Cmfcdemo1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	TCHAR devInfBuf[64] ;
	memset(devInfBuf ,0 ,sizeof(devInfBuf));
	DWORD nsize = sizeof(devInfBuf) / sizeof(TCHAR) ; //字符数量
	iret = RDR_GetReaderInfor(hr ,0,devInfBuf , &nsize) ;
	if(iret != 0) {
		ShowError(iret) ;
		return;
	}
	MessageBox(devInfBuf,_T(""),MB_OK) ;
}



void Cmfcdemo1Dlg::OnCbnSelchangeCmmtype()
{
	CString str;
	m_cbbCommunicateType.GetWindowText(str);
	if (str==_T("COM"))
	{
		m_cbbComNames.EnableWindow(TRUE) ;
		m_ipAddr.EnableWindow(FALSE) ;
	}
	else if (str==_T("TCP/IP"))
	{
		m_cbbComNames.EnableWindow(FALSE) ;
		m_ipAddr.EnableWindow(TRUE) ;
	}
}