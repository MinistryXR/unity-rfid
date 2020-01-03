// WriteEPCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WriteEPC.h"
#include "WriteEPCDlg.h"
#include "DlgOpen.h"
#include "DlgInventory.h"
#include "DlgWrite.h"
#include "rfidlib_reader.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWriteEPCDlg 对话框

void CWriteEPCDlg::ShowError(INT err) 
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


CWriteEPCDlg::CWriteEPCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteEPCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWriteEPCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CWriteEPCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CWriteEPCDlg::OnBnClickedButton1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CWriteEPCDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CWriteEPCDlg 消息处理程序

BOOL CWriteEPCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// Show Open dialog 
	CDlgOpen dlg ;
	dlg.DoModal() ;
	if(hr==RFID_HANDLE_NULL){
		//m_tab.EnableWindow(FALSE) ;
		this->EndDialog(0) ;
		return true;
	}


TCITEM   item;   
	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Tag Inventory");
	m_tab.InsertItem(0,&item) ;

	item.mask  =   TCIF_TEXT;   
	item.pszText  =_T("Write operation");
	m_tab.InsertItem(1,&item) ;

	

	CDialog *pdlg ;
	pdlg = new CDlgInventory(); 
	pdlg->Create(IDD_INVENTORY,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;


	pdlg = new CDlgWrite() ;
	pdlg->Create(IDD_WRITE ,&m_tab) ;
	pdlg->ShowWindow(SW_HIDE) ;
	m_tabDlgs.Add(pdlg) ;


	if(m_tabDlgs.GetCount() > 0) {
		old_page= 0 ;
		RECT rect;
		m_tab.GetClientRect(&rect) ;
		m_tabDlgs[old_page]->SetWindowPos(NULL,10,30,rect.right -20,rect.bottom-40,SWP_SHOWWINDOW);
		m_tab.SetCurSel( 0) ;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWriteEPCDlg::OnPaint()
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
HCURSOR CWriteEPCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWriteEPCDlg::OnBnClickedButton1()
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

void CWriteEPCDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	RECT rect;
	int idx ;
	m_tab.GetClientRect(&rect) ;
	idx  =m_tab.GetCurSel() ;
	m_tabDlgs[old_page]->ShowWindow(SW_HIDE) ; 
	m_tabDlgs[idx]->SetWindowPos(NULL,10,30,rect.right -20,rect.bottom-40,SWP_SHOWWINDOW);
	m_tabDlgs[idx]->BringWindowToTop() ;

	if(idx ==1) {
		CDlgWrite *pDlgWrite;
		pDlgWrite = (CDlgWrite *)m_tabDlgs[idx] ;
		while(pDlgWrite->m_cmbEPCs.GetCount()> 0)
			pDlgWrite->m_cmbEPCs.DeleteString(0) ;
		for(int i=0;i<m_taglist.GetCount();i++) {
			pDlgWrite->m_cmbEPCs.AddString(m_taglist[i].m_uid) ;
		}

		if(pDlgWrite->m_cmbEPCs.GetCount() > 0) {
			pDlgWrite->m_cmbEPCs.SetCurSel(0) ;
		}
	}

	
	old_page = idx ;
}
