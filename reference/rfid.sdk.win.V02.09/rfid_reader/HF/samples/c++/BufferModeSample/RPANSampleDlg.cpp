// RPANSampleDlg.cpp : 实现文件
//

#include "stdafx.h"

#include "RPANSample.h"
#include "RPANSampleDlg.h"
#include "gfunctions.h"
#include "rfidlib_reader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRPANSampleDlg 对话框




CRPANSampleDlg::CRPANSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRPANSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hReader = NULL;
	b_threadRun = false;
}

void CRPANSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOTYPE, m_cmb_type);
	DDX_Control(pDX, IDC_COMBOCOM, m_cmb_comName);
	DDX_Control(pDX, IDC_COMBOBAUD, m_cmb_baud);
	DDX_Control(pDX, IDC_COMBOFRAME, m_cmb_frame);
	DDX_Control(pDX, IDC_EDITADDR, m_edit_addr);
	DDX_Control(pDX, IDC_EDITPORT, m_edit_port);
	DDX_Control(pDX, IDC_LIST_DATA, m_listTagData);
	DDX_Control(pDX, IDC_CMB_BLUETOOTHNAME, m_cmb_bluetoothName);
}

BEGIN_MESSAGE_MAP(CRPANSampleDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTONOPEN, &CRPANSampleDlg::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTONCLOSE, &CRPANSampleDlg::OnBnClickedButtonclose)
	ON_BN_CLICKED(IDC_BUTTONSETTIME, &CRPANSampleDlg::OnBnClickedButtonsettime)
	ON_BN_CLICKED(IDC_BUTTON_CLEARRECORD, &CRPANSampleDlg::OnBnClickedButtonClearrecord)
	ON_BN_CLICKED(IDC_BUTTON_START, &CRPANSampleDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CRPANSampleDlg::OnBnClickedButtonStop)
	ON_CBN_SELCHANGE(IDC_CMB_BLUETOOTHNAME, &CRPANSampleDlg::OnCbnSelchangeCmbBluetoothname)
END_MESSAGE_MAP()


// CRPANSampleDlg 消息处理程序

BOOL CRPANSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	DWORD dwStyle = m_listTagData.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listTagData.SetExtendedStyle(dwStyle); //设置扩展风格
	m_listTagData.InsertColumn( 0, _T("Record"), LVCFMT_LEFT, 420 );//插入列



	m_cmb_type.AddString(_T("USB"));
	m_cmb_type.AddString(_T("COM"));
	m_cmb_type.AddString(_T("NET"));
	m_cmb_type.AddString(_T("BLUETOOTH"));
	m_cmb_type.SetCurSel(0);

	m_cmb_baud.AddString(_T("9600"));
	m_cmb_baud.AddString(_T("38400"));
	m_cmb_baud.AddString(_T("57600"));
	m_cmb_baud.AddString(_T("115200"));
	m_cmb_baud.SetCurSel(1);

	m_cmb_frame.AddString(_T("8E1"));
	m_cmb_frame.AddString(_T("8N1"));
	m_cmb_frame.AddString(_T("8O1"));
	m_cmb_frame.SetCurSel(0);

	DWORD nComCnt = COMPort_Enum();
	for (DWORD j=0;j<nComCnt;j++)
	{
		TCHAR comName[128];
		memset(comName,0x00,sizeof(comName));
		COMPort_GetEnumItem(j,comName,sizeof(comName)/sizeof(TCHAR));
		m_cmb_comName.AddString(comName);
	}
	if (nComCnt>0)
	{
		m_cmb_comName.SetCurSel(0);
	}

	m_edit_addr.SetWindowText(_T("192.168.0.222"));
	m_edit_port.SetWindowText(_T("9909"));

	DWORD blueCnt = Bluetooth_Enum();
	for (DWORD j=0;j<blueCnt;j++)
	{
		TCHAR nameBuffer[256];
		TCHAR addrBuffer[256];
		memset(nameBuffer,0x00,sizeof(nameBuffer));
		memset(addrBuffer,0x00,sizeof(addrBuffer));
		DWORD nameBufferSize = sizeof(nameBuffer)/sizeof(TCHAR);
		DWORD addrBufferSize = sizeof(addrBuffer)/sizeof(TCHAR);
		Bluetooth_GetEnumItem(j,1,nameBuffer,&nameBufferSize);
		Bluetooth_GetEnumItem(j,2,addrBuffer,&addrBufferSize);
		m_cmb_bluetoothName.AddString(nameBuffer);
		blueAddrList.push_back(addrBuffer);
	}
	if (blueAddrList.size())
	{
		m_cmb_bluetoothName.SetCurSel(0);
		GetDlgItem(IDC_EDIT_BLUETOOTHADDR)->SetWindowText(blueAddrList[0]);
	}


	GetDlgItem(IDC_BUTTONOPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTONCLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONSETTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLEARRECORD)->EnableWindow(FALSE);
	m_cmb_type.EnableWindow(TRUE);
	m_cmb_comName.EnableWindow(TRUE);
	m_cmb_baud.EnableWindow(TRUE);
	m_cmb_frame.EnableWindow(TRUE);
	m_edit_addr.EnableWindow(TRUE);
	m_edit_port.EnableWindow(TRUE);

	RDR_LoadReaderDrivers(_T("\\Drivers"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRPANSampleDlg::OnPaint()
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
HCURSOR CRPANSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRPANSampleDlg::OnBnClickedButtonopen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString connstr ;
	CString sBaud,sFrame;
	CString sComName;
	CString ipStr,portStr;
	CString bluetoothAddr;
	err_t iret;
	
	switch(m_cmb_type.GetCurSel())
	{
		case 0: //USB 
			connstr.Format(_T("%s=%s;%s=%s;%s=%d;%s=%s"),_T(CONNSTR_NAME_RDTYPE) ,_T("RPAN"),_T(CONNSTR_NAME_COMMTYPE) ,_T(CONNSTR_NAME_COMMTYPE_USB) ,_T(CONNSTR_NAME_HIDADDRMODE) ,0 ,_T(CONNSTR_NAME_HIDSERNUM),_T("")) ;
			break;
		case 1: //COM
			m_cmb_comName.GetWindowText(sComName);
			m_cmb_baud.GetWindowText(sBaud);
			m_cmb_frame.GetWindowText(sFrame);
			connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s;%s=%s;%s=%s"),_T(CONNSTR_NAME_RDTYPE) ,_T("RPAN") ,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_COM) ,_T(CONNSTR_NAME_COMNAME),sComName,_T(CONNSTR_NAME_COMBARUD) ,sBaud, _T(CONNSTR_NAME_COMFRAME),sFrame, _T(CONNSTR_NAME_BUSADDR),_T("255")) ;
			break;	
		case 2: //TCP
			m_edit_addr.GetWindowText(ipStr);
			m_edit_port.GetWindowText(portStr);
			connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s;%s=%s") ,_T(CONNSTR_NAME_RDTYPE),_T("RPAN") ,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_NET),_T(CONNSTR_NAME_REMOTEIP),ipStr ,_T(CONNSTR_NAME_REMOTEPORT) ,portStr,_T(CONNSTR_NAME_LOCALIP),_T("")) ;
			break;
		case 3://BLUETOOTH
			GetDlgItem(IDC_EDIT_BLUETOOTHADDR)->GetWindowText(bluetoothAddr);
			if (bluetoothAddr==_T(""))
			{
				MessageBox(_T("The address of the bluetooth can not be null!"));
				return;
			}
			connstr.Format(_T("%s=%s;%s=%s;%s=%s") ,_T(CONNSTR_NAME_RDTYPE),_T("RPAN") ,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_BLUETOOTH),_T(CONNSTR_NAME_BLUETOOTH_SERNUM),bluetoothAddr) ;
			break;

	}
	iret = RDR_Open(connstr,&hReader) ;
	if (iret!=0)
	{
		AfxMessageBox(_T("Failed to open reader!"));
		return;
	}

	GetDlgItem(IDC_BUTTONOPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONCLOSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTONSETTIME)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLEARRECORD)->EnableWindow(TRUE);
	m_cmb_type.EnableWindow(FALSE);
	m_cmb_comName.EnableWindow(FALSE);
	m_cmb_baud.EnableWindow(FALSE);
	m_cmb_frame.EnableWindow(FALSE);
	m_edit_addr.EnableWindow(FALSE);
	m_edit_port.EnableWindow(FALSE);
	
}


UINT CRPANSampleDlg::GetRecordPro(void *lp)
{
	CRPANSampleDlg *pt = (CRPANSampleDlg*)lp;
	pt->b_threadRun = true;
	pt->m_listTagData.DeleteAllItems();
	BYTE gFlg = 0x00;
	RFID_DN_HANDLE dnhReport = NULL;
	err_t nret;
	while(pt->b_threadRun)
	{
		nret = RDR_BuffMode_FetchRecords(pt->hReader,gFlg);
		if (nret!=NO_ERR)
		{
			gFlg = 0x00;
			continue;
		}
		dnhReport = RDR_GetTagDataReport(pt->hReader,RFID_SEEK_FIRST) ;		
		gFlg = 0x01;//以后采集标志位为0x01
		while(dnhReport!=NULL)
		{
			BYTE byData[512] = {0x00};
			TCHAR sData[1024]={0x00};
			memset(sData,'\0',sizeof(sData));
			DWORD len = sizeof(byData);
			RDR_ParseTagDataReportRaw(dnhReport,byData,&len);
			BytesToHexStr(byData,len,sData);
			int nRow=pt->m_listTagData.InsertItem(pt->m_listTagData.GetItemCount(),sData);        //插入行
			//vDataList.push_back(sData);
			dnhReport = RDR_GetTagDataReport(pt->hReader,RFID_SEEK_NEXT) ;	
		}
	}
	pt->GetDlgItem(IDC_BUTTONSETTIME)->EnableWindow(TRUE);
	pt->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	pt->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	pt->GetDlgItem(IDC_BUTTON_CLEARRECORD)->EnableWindow(TRUE);
	pt->EnableWindow(TRUE);
	return TRUE;
}
void CRPANSampleDlg::OnBnClickedButtonclose()
{
	// TODO: 在此添加控件通知处理程序代码
	if (b_threadRun)
	{
		AfxMessageBox(_T("Please stop the thread first!"));
		return;
	}
	if (hReader==NULL)
	{
		return;
	}
	RDR_Close(hReader);
	hReader = NULL;
	GetDlgItem(IDC_BUTTONOPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTONCLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONSETTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLEARRECORD)->EnableWindow(FALSE);
	m_cmb_type.EnableWindow(TRUE);
	m_cmb_comName.EnableWindow(TRUE);
	m_cmb_baud.EnableWindow(TRUE);
	m_cmb_frame.EnableWindow(TRUE);
	m_edit_addr.EnableWindow(TRUE);
	m_edit_port.EnableWindow(TRUE);
}

void CRPANSampleDlg::OnBnClickedButtonsettime()
{
	// TODO: 在此添加控件通知处理程序代码
	 CTime t = CTime::GetCurrentTime();

	err_t iret = RDR_SetSystemTime(hReader,(DWORD)t.GetYear(),(BYTE)t.GetMonth(),(BYTE)t.GetDay(),(BYTE)t.GetHour(),(BYTE)t.GetMinute(),(BYTE)t.GetSecond());
	if (iret==0)
	{
		AfxMessageBox(_T("Set the time successfully"));
	}
	else
	{
		AfxMessageBox(_T("Failed to set the time!"));
	}
}

void CRPANSampleDlg::OnBnClickedButtonClearrecord()
{
	//m_listTagData.InsertItem(m_listTagData.GetItemCount(),_T("1235"));        //插入行
	// TODO: 在此添加控件通知处理程序代码
	err_t iret = RDR_BuffMode_ClearRecords(hReader);
	if (iret==0)
	{
		AfxMessageBox(_T("Clear record successfully!"));
	}
	else
	{
		AfxMessageBox(_T("Failed to clear record!"));
	}
}

void CRPANSampleDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTONSETTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLEARRECORD)->EnableWindow(FALSE);
	AfxBeginThread(GetRecordPro,this);
}

void CRPANSampleDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if (b_threadRun)
	{
		EnableWindow(FALSE);
		b_threadRun = false;
	}
}

void CRPANSampleDlg::OnCbnSelchangeCmbBluetoothname()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sAddr;
	int idx = m_cmb_bluetoothName.GetCurSel();
	if (idx>=0)
	{
		sAddr = blueAddrList[idx];
		GetDlgItem(IDC_EDIT_BLUETOOTHADDR)->SetWindowText(sAddr);
	}
}
