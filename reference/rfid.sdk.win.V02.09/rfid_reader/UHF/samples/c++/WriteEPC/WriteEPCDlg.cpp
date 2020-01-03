// WriteEPCDlg.cpp : ʵ���ļ�
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


// CWriteEPCDlg �Ի���

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


// CWriteEPCDlg ��Ϣ�������

BOOL CWriteEPCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWriteEPCDlg::OnPaint()
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
HCURSOR CWriteEPCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWriteEPCDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
// TODO: �ڴ���ӿؼ�֪ͨ����������
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
