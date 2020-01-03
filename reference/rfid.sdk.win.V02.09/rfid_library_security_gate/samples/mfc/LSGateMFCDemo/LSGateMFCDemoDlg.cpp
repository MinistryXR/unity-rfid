// LSGateMFCDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LSGateMFCDemo.h"
#include "LSGateMFCDemoDlg.h"
#include "DlgControlCommand.h"
#include "DlgGetEventRecord.h"
#include "rfidlib.h"
#include "rfidlib_reader.h"

#include "BaseTsd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLSGateMFCDemoDlg �Ի���




CLSGateMFCDemoDlg::CLSGateMFCDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLSGateMFCDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLSGateMFCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPAddr);
	DDX_Control(pDX, IDC_BUTTON1, m_bntOpen);
	DDX_Control(pDX, IDC_BUTTON2, m_bntClose);
	DDX_Control(pDX, IDC_BUTTON3, m_bntGetDevInfo);
}

BEGIN_MESSAGE_MAP(CLSGateMFCDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CLSGateMFCDemoDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CLSGateMFCDemoDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLSGateMFCDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLSGateMFCDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CLSGateMFCDemoDlg ��Ϣ�������

BOOL CLSGateMFCDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	TCITEM   item;   
	item.mask  =   TCIF_TEXT;   
	item.pszText  = _T("Command");
	m_tab.InsertItem(0,&item) ;

	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Event Record");
	m_tab.InsertItem(1,&item) ;

	


	CDialog *pdlg ;
	pdlg = new CDlgControlCommand(); 
	pdlg->Create(IDD_DIALOG1,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;


	pdlg = new CDlgGetEventRecord() ;
	pdlg->Create(IDD_DIALOG2 ,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;

	if(m_tabDlgs.GetCount() > 0) {
		old_page= 0 ;
		RECT rect;
		m_tab.GetClientRect(&rect) ;
		m_tabDlgs[old_page]->SetWindowPos(NULL,10,30,rect.right -20,rect.bottom-40,SWP_SHOWWINDOW);
		m_tab.SetCurSel( 0) ;
	}

	m_IPAddr.SetAddress(192,168,0,222) ;
	m_bntOpen.EnableWindow(TRUE) ;
	m_bntClose.EnableWindow(FALSE) ;
	m_bntGetDevInfo.EnableWindow(FALSE) ;


	RDR_LoadReaderDrivers(_T("\\Drivers"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLSGateMFCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLSGateMFCDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CLSGateMFCDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLSGateMFCDemoDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BYTE ip1,ip2,ip3,ip4;
	m_IPAddr.GetAddress(ip1 ,ip2,ip3,ip4);
	int iret;
	CString ipstr;
	ipstr.Format(_T("%d.%d.%d.%d"),ip1,ip2,ip3,ip4) ;

	CString connstr;
	connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%d;%s=%s") ,_T(CONNSTR_NAME_RDTYPE) ,_T("LSG405"),_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_NET),_T(CONNSTR_NAME_REMOTEIP),ipstr,_T(CONNSTR_NAME_REMOTEPORT) ,6012,_T(CONNSTR_NAME_LOCALIP),_T("")) ;


	iret = RDR_Open(connstr,&hreader);
	/*iret =LSG_Open(ipstr,6012,&hreader);*/
	if(iret != 0) 
	{
		MessageBox(_T("Open failed!"),_T(""),MB_OK) ;
		return ;
	}
	m_bntOpen.EnableWindow(FALSE) ;
	m_bntClose.EnableWindow(TRUE) ;
	m_bntGetDevInfo.EnableWindow(TRUE) ;

	CDlgControlCommand *pDlgCmd ;
	pDlgCmd =(CDlgControlCommand *)m_tabDlgs[0]  ;
	pDlgCmd->OnReaderOpen() ;
	CDlgGetEventRecord *pDlgGetEvent;
	pDlgGetEvent = (CDlgGetEventRecord *)m_tabDlgs[1] ;
	pDlgGetEvent->OnReaderOpen() ;

}

void CLSGateMFCDemoDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

void CLSGateMFCDemoDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iret;
	iret = RDR_Close(hreader) ;
	if(iret!=0) {
		MessageBox(_T("Close failed!"),_T(""),MB_OK) ;
		return ;
	}
	m_bntOpen.EnableWindow(TRUE) ;
	m_bntClose.EnableWindow(FALSE) ;
	m_bntGetDevInfo.EnableWindow(FALSE) ;

	CDlgControlCommand *pDlgCmd ;
	pDlgCmd =(CDlgControlCommand *)m_tabDlgs[0]  ;
	pDlgCmd->OnReaderClose() ;
	CDlgGetEventRecord *pDlgGetEvent;
	pDlgGetEvent = (CDlgGetEventRecord *)m_tabDlgs[1] ;
	pDlgGetEvent->OnReaderClose() ;
}

void CLSGateMFCDemoDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iret;
	TCHAR infBuff[64] ;
	memset(infBuff ,'\0', sizeof(infBuff));
	DWORD nLen ;
	nLen =  sizeof(infBuff)  / sizeof(TCHAR);
	iret = RDR_GetReaderInfor(hreader,0,infBuff,&nLen) ;
	if(iret != 0) {
		MessageBox(_T("Get device information failed!"),_T(""),MB_OK) ;
		return ;
	}
	MessageBox(infBuff ,_T(""),MB_OK) ;
}


void CLSGateMFCDemoDlg::OnStopGetEvent()
{
	m_bntOpen.EnableWindow(FALSE) ;
	m_bntClose.EnableWindow(TRUE) ;
	m_bntGetDevInfo.EnableWindow(TRUE) ;

	CDlgControlCommand *pDlgCmd ;
	pDlgCmd =(CDlgControlCommand *)m_tabDlgs[0]  ;
	pDlgCmd->OnReaderOpen() ;
}

void CLSGateMFCDemoDlg::OnStartGetEvent()
{
	m_bntOpen.EnableWindow(FALSE) ;
	m_bntClose.EnableWindow(FALSE) ;
	m_bntGetDevInfo.EnableWindow(FALSE) ;

	CDlgControlCommand *pDlgCmd ;
	pDlgCmd =(CDlgControlCommand *)m_tabDlgs[0]  ;
	pDlgCmd->OnReaderClose() ;
	
}