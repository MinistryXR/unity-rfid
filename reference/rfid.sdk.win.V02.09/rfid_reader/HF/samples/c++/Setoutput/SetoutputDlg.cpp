// SetoutputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Setoutput.h"
#include "SetoutputDlg.h"
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


// CSetoutputDlg 对话框




CSetoutputDlg::CSetoutputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetoutputDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hr = NULL;
}

void CSetoutputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_DEVTYPE, m_cmb_devType);
	DDX_Control(pDX, IDC_CMB_COMMUNICATETYPE, m_cmb_communicateType);
	DDX_Control(pDX, IDC_CMB_COMNAME, m_com_name);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_ipaddress_ip);
	DDX_Control(pDX, IDC_EDIT_PORT, m_edit_port);
	DDX_Control(pDX, IDC_CMB_BAUND, m_cmb_baund);
	DDX_Control(pDX, IDC_CMB_FRAME, m_cmb_frame);
	DDX_Control(pDX, IDC_CMB_ACTTIME, m_cmb_activeTime);
	DDX_Control(pDX, IDC_CMB_FREQUENCY, m_cmb_frequecy);
	DDX_Control(pDX, IDC_CMB_STOPTIME, m_cmb_stoptime);
	DDX_Control(pDX, IDC_LIST_OUTPUT, m_list_outPut);
}

BEGIN_MESSAGE_MAP(CSetoutputDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_OPEN, &CSetoutputDlg::OnBnClickedBtnOpen)
	ON_CBN_SELCHANGE(IDC_CMB_COMMUNICATETYPE, &CSetoutputDlg::OnCbnSelchangeCmbCommunicatetype)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CSetoutputDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_SETOUTPUT, &CSetoutputDlg::OnBnClickedBtnSetoutput)
END_MESSAGE_MAP()


// CSetoutputDlg 消息处理程序

BOOL CSetoutputDlg::OnInitDialog()
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
	RDR_LoadReaderDrivers(_T("\\Drivers"));
	DWORD devCnt = RDR_GetLoadedReaderDriverCount();
	for(int i=0;i<(int)devCnt;i++)
	{
		DWORD nSize ;
		TCHAR tmp[64] ;
		CString sDevName;
		memset(tmp,0,sizeof(tmp)) ;
		nSize = sizeof(tmp) / sizeof(TCHAR);
		memset(tmp,0,sizeof(tmp));
		nSize = sizeof(tmp) / sizeof(TCHAR);
		RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_NAME) , tmp,&nSize);
		sDevName.Format(_T("%s"),tmp);
		m_cmb_devType.AddString(sDevName);
	}

	if (devCnt)
	{
		m_cmb_devType.SetCurSel(0);
	}

	m_cmb_communicateType.AddString(_T("USB"));
	m_cmb_communicateType.AddString(_T("COM"));
	m_cmb_communicateType.AddString(_T("NET"));
	m_cmb_communicateType.SetCurSel(0);

	DWORD comNum = COMPort_Enum();
	for (int j=0;j<(int)comNum;j++)
	{
		TCHAR ComBuffer[64];
		CString sComName;
		memset(ComBuffer,0,sizeof(ComBuffer));
		COMPort_GetEnumItem(j,ComBuffer,sizeof(ComBuffer)/sizeof(TCHAR));
		sComName.Format(_T("%s"),ComBuffer);
		m_com_name.AddString(sComName);
	}
	if (comNum>0)
	{
		m_com_name.SetCurSel(0);
	}
	m_cmb_baund.AddString(_T("9600"));
	m_cmb_baund.AddString(_T("38400"));
	m_cmb_baund.AddString(_T("57600"));
    m_cmb_baund.AddString(_T("115200"));
	m_cmb_baund.SetCurSel(1);

	m_cmb_frame.AddString(_T("8E1"));
	m_cmb_frame.AddString(_T("8N1"));
	m_cmb_frame.AddString(_T("8O1"));
	m_cmb_frame.SetCurSel(0);


	m_ipaddress_ip.SetAddress(192,168,0,222);
	m_edit_port.SetWindowText(_T("9909"));

	for (int j=1;j<=255;j++)
	{
		CString str;
		str.Format(_T("%d"),j);
		m_cmb_activeTime.AddString(str);
		m_cmb_frequecy.AddString(str);
		m_cmb_stoptime.AddString(str);
	}
	m_cmb_activeTime.SetCurSel(0);
	m_cmb_frequecy.SetCurSel(0);
	m_cmb_stoptime.SetCurSel(0);

	EnableAllCtr(FALSE);
	OnCbnSelchangeCmbCommunicatetype();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSetoutputDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSetoutputDlg::OnPaint()
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
HCURSOR CSetoutputDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSetoutputDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString connstr ;
	CString sDevName;
	CString sCom,sBaud,sFrame;
	CString sIp,sPort;
	BYTE m_ip[4];
	unsigned short m_port;
	m_cmb_devType.GetWindowText(sDevName);
	m_com_name.GetWindowText(sCom);
	m_cmb_baund.GetWindowText(sBaud);
	m_cmb_frame.GetWindowText(sFrame);
	m_ipaddress_ip.GetAddress(m_ip[0],m_ip[1],m_ip[2],m_ip[3]);
	sIp.Format(_T("%d.%d.%d.%d"),m_ip[0],m_ip[1],m_ip[2],m_ip[3]);
	m_edit_port.GetWindowText(sPort);
	m_port = _ttoi(sPort);
	switch(m_cmb_communicateType.GetCurSel())
	{
	case 0: //USB 
		connstr.Format(_T("%s=%s;%s=%s;%s=%d;%s=%s"),_T(CONNSTR_NAME_RDTYPE) ,sDevName,_T(CONNSTR_NAME_COMMTYPE) ,_T(CONNSTR_NAME_COMMTYPE_USB) ,_T(CONNSTR_NAME_HIDADDRMODE) ,0 ,_T(CONNSTR_NAME_HIDSERNUM),"") ;
		break;

	case 1: //COM
		connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s;%s=%s;%s=%s"),_T(CONNSTR_NAME_RDTYPE) ,sDevName,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_COM) ,_T(CONNSTR_NAME_COMNAME),sCom,_T(CONNSTR_NAME_COMBARUD) ,sBaud, _T(CONNSTR_NAME_COMFRAME),sFrame, _T(CONNSTR_NAME_BUSADDR),_T("255")) ;
		break;

	case 2: //TCP
		connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%d;%s=%s") ,_T(CONNSTR_NAME_RDTYPE),sDevName,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_NET),_T(CONNSTR_NAME_REMOTEIP),sIp ,_T(CONNSTR_NAME_REMOTEPORT) ,m_port,_T(CONNSTR_NAME_LOCALIP),_T("")) ;
		break;
	}

	err_t iret  = RDR_Open(connstr,&hr) ;
	if(iret != NO_ERR) {
		MessageBox(_T("open reader fail"),_T(""),MB_OK) ;
		return ;
	}
	ListOutput();
	EnableAllCtr(TRUE);
}

void CSetoutputDlg::OnCbnSelchangeCmbCommunicatetype()
{
	// TODO: 在此添加控件通知处理程序代码
	switch(m_cmb_communicateType.GetCurSel())
	{
	case 0:
		m_com_name.EnableWindow(FALSE);
		m_cmb_baund.EnableWindow(FALSE);
		m_cmb_frame.EnableWindow(FALSE);
		m_ipaddress_ip.EnableWindow(FALSE);
		m_edit_port.EnableWindow(FALSE);
		break;
	case 1:
		m_com_name.EnableWindow(TRUE);
		m_cmb_baund.EnableWindow(TRUE);
		m_cmb_frame.EnableWindow(TRUE);
		m_ipaddress_ip.EnableWindow(FALSE);
		m_edit_port.EnableWindow(FALSE);
		break;
	case 2:
		m_com_name.EnableWindow(FALSE);
		m_cmb_baund.EnableWindow(FALSE);
		m_cmb_frame.EnableWindow(FALSE);
		m_ipaddress_ip.EnableWindow(TRUE);
		m_edit_port.EnableWindow(TRUE);
		break;
	default:
		break;
	}
}


void CSetoutputDlg::EnableAllCtr(BOOL isOpen)
{
	m_cmb_devType.EnableWindow(!isOpen);
	m_cmb_communicateType.EnableWindow(!isOpen);
	m_com_name.EnableWindow(!isOpen);
	m_ipaddress_ip.EnableWindow(!isOpen);
	m_edit_port.EnableWindow(!isOpen);
	m_cmb_baund.EnableWindow(!isOpen);
	m_cmb_frame.EnableWindow(!isOpen);	
	m_cmb_activeTime.EnableWindow(isOpen);
	m_cmb_frequecy.EnableWindow(isOpen);
	m_cmb_stoptime.EnableWindow(isOpen);
	GetDlgItem(IDC_BTN_OPEN)->EnableWindow(!isOpen);
	GetDlgItem(IDC_BTN_CLOSE)->EnableWindow(isOpen);
	GetDlgItem(IDC_BTN_SETOUTPUT)->EnableWindow(isOpen);
}
void CSetoutputDlg::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	if (hr!=NULL)
	{
		RDR_Close(hr);
		hr = NULL;
		EnableAllCtr(FALSE);
		OnCbnSelchangeCmbCommunicatetype();
	}
	
}


void CSetoutputDlg::ListOutput()
{
	m_list_outPut.ResetContent();
	BYTE nCount=0;
	err_t nret = RDR_GetOutputCount(hr,&nCount);
	if (nret!=NO_ERR)
	{
		return;
	}
	for (BYTE j=0;j<nCount;j++)
	{
		TCHAR sTmp[128];
		DWORD nSize = 0;
		memset(sTmp,0,sizeof(sTmp));
		if(RDR_GetOutputName(hr,j+1,sTmp ,&nSize)!=NO_ERR)
		{
			continue;
		}
		m_list_outPut.AddString(sTmp);
		m_list_outPut.SetCheck(j,TRUE);
	}
	
}
void CSetoutputDlg::OnBnClickedBtnSetoutput()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	BYTE activeTime,frequency,deactiveTime ;
	RFID_DN_HANDLE dnOutputOper;
	dnOutputOper = RDR_CreateSetOutputOperations() ;
	for(int i=0 ;i<m_list_outPut.GetCount();i++) 
	{
		if(m_list_outPut.GetCheck(i)==FALSE) 
		{
			continue;
		}

		int idx;
		idx =m_cmb_activeTime.GetCurSel();
		if(idx == -1) 
		{
			MessageBox(_T("Please select the Activation time."),_T(""),MB_OK) ;
			return ;
		}
		activeTime = idx + 1;
		idx = m_cmb_frequecy.GetCurSel() ;
		if(idx == -1) 
		{
			MessageBox(_T("Please select the Frequency."),_T(""),MB_OK) ;
			return ;
		}
		frequency = idx + 1;
		idx = m_cmb_stoptime.GetCurSel() ;
		if(idx == -1) 
		{
			MessageBox(_T("Please select the stop time."),_T(""),MB_OK) ;
			return ;
		}
		deactiveTime = idx + 1;

		iret = RDR_AddOneOutputOperation(dnOutputOper,i+1,3,frequency,activeTime*100,deactiveTime*100);
		if (iret!=NO_ERR)
		{

			MessageBox(_T("Failure to set output."),_T(""),MB_OK) ;
			return ;
		}
	}
	iret = RDR_SetOutput(hr,dnOutputOper);
	DNODE_Destroy(dnOutputOper);
	if (iret!=NO_ERR)
	{
		CString str;
		str.Format(_T("Failure to set output,error:%d") ,iret);
		MessageBox(str,_T(""),MB_OK) ;
	}
	else
	{
		CString str;
		str.Format(_T("Set output successfully"));
		MessageBox(str,_T(""),MB_OK) ;
	}
}
