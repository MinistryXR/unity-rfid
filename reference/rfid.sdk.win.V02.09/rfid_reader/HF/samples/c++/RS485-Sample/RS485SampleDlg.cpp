// RS485SampleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RS485Sample.h"
#include "RS485SampleDlg.h"
#include "gfunctions.h"
#include "rfidlib_reader.h"
#include "rfidlib_aip_iso15693.h"
#include "dlgopen.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_INVENOTYR_STOPPED   (WM_USER +1 )

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


// CRS485SampleDlg 对话框




CRS485SampleDlg::CRS485SampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRS485SampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRS485SampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listTagData);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richedtInvnRes);
	DDX_Control(pDX, IDC_BUTTON3, m_bntInvenStart);
	DDX_Control(pDX, IDC_BUTTON4, m_bntInvenStop);
}

BEGIN_MESSAGE_MAP(CRS485SampleDlg, CDialog)
	ON_MESSAGE(WM_INVENOTYR_STOPPED,msg_inventory_stopped)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CRS485SampleDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CRS485SampleDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CRS485SampleDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CRS485SampleDlg 消息处理程序

BOOL CRS485SampleDlg::OnInitDialog()
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
	this->m_hr = NULL ;
	CDlgOpen dlg ;
	dlg.m_pParent = this ;
	dlg.DoModal() ;
	if(this->m_hr ==RFID_HANDLE_NULL){
		//m_tab.EnableWindow(FALSE) ;
		this->EndDialog(0) ;
	}

	DWORD dwStyle = m_listTagData.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
    m_listTagData.SetExtendedStyle(dwStyle); //设置扩展风格
	m_listTagData.InsertColumn(0,_T("Reader Addr"),LVCFMT_LEFT,100) ;
	m_listTagData.InsertColumn( 1, _T("TYPE"), LVCFMT_LEFT, 100 );//插入列
	m_listTagData.InsertColumn( 2, _T("Serial Num"), LVCFMT_LEFT, 150 );//插入列
	m_listTagData.InsertColumn( 3, _T("DSFID"), LVCFMT_LEFT, 100 );//插入列
	m_listTagData.InsertColumn( 4, _T("Antenna"),LVCFMT_LEFT,80);
	m_listTagData.InsertColumn( 5, _T("Found count"),LVCFMT_LEFT,100) ;

	InventoryOn = FALSE  ;
	m_curReader =NULL ;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRS485SampleDlg::OnClose()
{
	// Close RS485 Nodes first
	for(int i=0 ;i<this->m_hRS485.GetCount();i++) {
		if(this->m_hRS485[i] != NULL) {
			if(reader_close_api) reader_close_api(this->m_hRS485[i]);
			this->m_hRS485[i]= NULL ;
		}
	}
	// Close base reader 
	if(reader_close_api && m_hr ) {
		reader_close_api(m_hr) ;
	}
	m_hr =0 ;
	CDialog::OnClose() ;
}


void CRS485SampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRS485SampleDlg::OnPaint()
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
HCURSOR CRS485SampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRS485SampleDlg::OnBnClickedButton3()
{
	m_taglist.RemoveAll();
	m_listTagData.DeleteAllItems();

	m_thrdInventory.Start(this,proc_inventory) ;
	m_bntInvenStart.EnableWindow(FALSE) ;
	m_bntInvenStop.EnableWindow(TRUE) ;
	m_richedtInvnRes.SetWindowText(_T("")) ;
	InventoryOn = TRUE;
}

LRESULT CRS485SampleDlg::msg_inventory_stopped(WPARAM wp, LPARAM lp)
{
	m_thrdStop.SetExitVar() ;
	m_thrdStop.Stop() ;
	m_bntInvenStart.EnableWindow(TRUE) ;
	m_bntInvenStop.EnableWindow(FALSE) ;

	InventoryOn=FALSE;
	
	return  0 ;
}

DWORD WINAPI CRS485SampleDlg::proc_inventory(LPVOID lpv)
{
	err_t iret;
	CRS485SampleDlg *pT = (CRS485SampleDlg *)lpv;
	BYTE newAI= AI_TYPE_NEW ;
	

	RFID_DN_HANDLE dnInvenParamList= RFID_HANDLE_NULL ;
	dnInvenParamList = RDR_CreateInvenParamSpecList() ;
	if(dnInvenParamList){
		ISO15693_CreateInvenParam(dnInvenParamList,0,0,0,0x00) ;
	}
	int idx = 0 ;
	while(!pT->m_thrdInventory.m_exit_flag) {
		//if AntCount =0  ,use default
		pT->m_curReader = pT->m_hRS485[idx] ;
		iret = RDR_TagInventory(pT->m_curReader ,newAI,0,NULL ,dnInvenParamList) ;
		if(iret == NO_ERR) {

			RFID_DN_HANDLE dnhReport = RDR_GetTagDataReport(pT->m_curReader ,RFID_SEEK_FIRST) ;
			while(dnhReport != RFID_HANDLE_NULL) 
			{
				DWORD AIPtype,TagType,AntId ;
				BYTE dsfid;
				BYTE uid[8];
				iret = ISO15693_ParseTagDataReport(dnhReport,&AIPtype,&TagType,&AntId,&dsfid,uid) ;
				if(iret == NO_ERR)
				{
					pT->AddNewTag(pT->m_busAddr[idx] ,AIPtype,TagType,AntId,dsfid,uid) ;
				}
				dnhReport = RDR_GetTagDataReport(pT->m_curReader ,RFID_SEEK_NEXT) ;
			}

		}
		else {
			
				if(iret == -17) {// error from reader
					err_t rdr_err= RDR_GetReaderLastReturnError(pT->m_curReader ) ;
					CString stmp;
					stmp.Format(_T("reader(%d) Inventory fail:%d,%d\n"),pT->m_busAddr[idx],iret,rdr_err) ;
					pT->LogInventoryResult(stmp) ;
				}
				else {
					CString stmp;
					stmp.Format(_T("reader(%d) Inventory fail:%d\n"),pT->m_busAddr[idx],iret) ;
					pT->LogInventoryResult(stmp) ;
				}
		}
		idx++ ;
		if(idx >= pT->m_hRS485.GetCount()){
			idx =0 ;
		}
	}
	if(dnInvenParamList) DNODE_Destroy(dnInvenParamList) ;

	return 1;

}

void CRS485SampleDlg::LogInventoryResult(CString msg)
{
	long  nInsertAfterChar = m_richedtInvnRes.GetWindowTextLength();
	m_richedtInvnRes.SetSel(nInsertAfterChar, nInsertAfterChar);
	m_richedtInvnRes.ReplaceSel(msg, FALSE);
}
void CRS485SampleDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!InventoryOn) 
		return ;
	m_bntInvenStop.EnableWindow(FALSE) ;
	m_thrdStop.Start(this,proc_stop_inventory) ;
}


DWORD WINAPI CRS485SampleDlg::proc_stop_inventory(LPVOID lpv)
{
	CRS485SampleDlg *pT ;
	pT = (CRS485SampleDlg *)lpv ;
	pT->m_thrdInventory.SetStopTimeout(50000);//多标签时需要等待长时间, RDR_TagInventory的超时是30秒	
	for(int i=0;i<pT->m_hRS485.GetCount();i++) {
		RDR_SetCommuImmeTimeout(pT->m_hRS485[i]) ; 
	}
	pT->m_thrdInventory.SetExitVar() ;
	pT->m_thrdInventory.Stop() ;
	for(int i=0;i<pT->m_hRS485.GetCount();i++) {
		RDR_ResetCommuImmeTimeout(pT->m_hRS485[i]) ; 
	}
	pT->PostMessage(WM_INVENOTYR_STOPPED,0,0) ;
	return 1;
}


void CRS485SampleDlg::AddNewTag(DWORD busAddr,UINT32 apl_tid,UINT32 picc_tid,UINT32 ant_id,UINT8 dsfid,UINT8 *uid)
{
	CString tagtype ;
	if(picc_tid == RFID_ISO15693_PICC_ICODE_SLI_ID ){
		tagtype =_T("NXP ICODE SLI") ;
	}
	else if(picc_tid ==RFID_ISO15693_PICC_TI_HFI_PLUS_ID) {
		tagtype = _T("Ti HF-I Plus") ;
	}
	else if(picc_tid == RFID_ISO15693_PICC_FUJ_MB89R118C_ID) {
		tagtype =_T("Fujitsu MB89R118C") ;
	}
	else if(picc_tid == RFID_ISO15693_PICC_ST_M24LR64_ID) {
		tagtype =_T("ST M24LR64") ;
	}
	else if(picc_tid == RFID_ISO15693_PICC_ST_M24LR16E_ID) {
		tagtype =_T("ST M24LR16E") ;
	}
	else if(picc_tid== RFID_ISO15693_PICC_ICODE_SLIX_ID) {
		tagtype=_T("NXP ICODE SLIX") ;
	}
	else if(picc_tid== RFID_ISO15693_PICC_TIHFI_STANDARD_ID){
		tagtype=_T("Ti HF-I Standard") ;
	}
	else if(picc_tid == RFID_ISO15693_PICC_TIHFI_PRO_ID) {
		tagtype=_T("Ti HF-I Pro") ;
	}
	else {
		tagtype  =_T("Unknown Tag") ;
	}
	TCHAR suid[32] ;
	memset(suid,0,sizeof(suid));
	BytesToHexStr(uid,8,suid) ;	
	TCHAR sdsfid[8] ;
	memset(sdsfid,0,sizeof(sdsfid));
	BytesToHexStr(&dsfid,1,sdsfid) ;
	CString sAntId ;
	sAntId.Format(_T("%d"),ant_id) ;
	INT32 i ;
	for( i=0;i<m_taglist.GetCount();i++) {
		if(m_taglist[i].m_uid ==suid && m_taglist[i].m_antNo == ant_id && m_taglist[i].m_readerAddr == busAddr) {
			break;
		}
	}
	if(i>=m_taglist.GetCount()) {
		CTag newtag;
		newtag.m_counter = 1;
		newtag.m_uid =suid ;
		newtag.m_type = picc_tid;
		newtag.m_antNo =ant_id ;
		newtag.m_readerAddr = busAddr;
		m_taglist.Add(newtag) ;
		CString str1 ;
		str1.Format(_T("%d") ,busAddr) ;
		int nRow=m_listTagData.InsertItem(m_taglist.GetCount()-1,str1);        //插入行
		m_listTagData.SetItemText(nRow,1,tagtype) ;
		m_listTagData.SetItemText(nRow,2,suid) ;
		m_listTagData.SetItemText(nRow,3,sdsfid) ;
		m_listTagData.SetItemText(nRow,4,sAntId) ;
		m_listTagData.SetItemText(nRow,5,_T("1"));
	}
	else{
		m_taglist[i].m_counter++ ;
		if(m_taglist[i].m_counter>=500000)
		{
			m_taglist[i].m_counter = 1;
		}
		CString sc ;
		sc.Format(_T("%d"),m_taglist[i].m_counter) ;
		m_listTagData.SetItemText(i,5,sc) ;
	}
	//m_listTagData.SetItemText(nRow,1,);  //设置数据
	//m_listTagData.

}
void CRS485SampleDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_taglist.RemoveAll();
	m_listTagData.DeleteAllItems();

}
