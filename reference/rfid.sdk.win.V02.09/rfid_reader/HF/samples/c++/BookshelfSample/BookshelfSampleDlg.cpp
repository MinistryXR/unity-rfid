// BookshelfSampleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BookshelfSample.h"
#include "BookshelfSampleDlg.h"
#include "gfunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBookshelfSampleDlg 对话框




CBookshelfSampleDlg::CBookshelfSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBookshelfSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hReader = NULL;
	b_threadRunFlg = false;
}

void CBookshelfSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANT, m_cklAntennas);
	DDX_Control(pDX, IDC_LIST_DATA, m_listTagData);
	DDX_Control(pDX, IDC_COMBOTYPE, m_cmb_commType);
	DDX_Control(pDX, IDC_COMBOCOM, m_cmb_comName);
	DDX_Control(pDX, IDC_COMBOBAUD, m_cmb_baud);
	DDX_Control(pDX, IDC_COMBOFRAME, m_cmb_frame);
	DDX_Control(pDX, IDC_EDITADDR, m_edit_ip);
	DDX_Control(pDX, IDC_EDITPORT, m_edit_port);
}

BEGIN_MESSAGE_MAP(CBookshelfSampleDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_INVENTORY, &CBookshelfSampleDlg::OnBnClickedButtonInventory)
	ON_BN_CLICKED(IDC_BUTTONOPEN, &CBookshelfSampleDlg::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTONCLOSE, &CBookshelfSampleDlg::OnBnClickedButtonclose)
	ON_BN_CLICKED(IDC_BUTTON_STOPINVENTORY, &CBookshelfSampleDlg::OnBnClickedButtonStopinventory)
END_MESSAGE_MAP()


// CBookshelfSampleDlg 消息处理程序

BOOL CBookshelfSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	for(int i =0 ;i< 12 ;i++) 
	{
		CString strAnt;
		strAnt.Format(_T("Antenna#%d"),i+1) ;
		m_cklAntennas.AddString(strAnt) ;
	}

	DWORD dwStyle = m_listTagData.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listTagData.SetExtendedStyle(dwStyle); //设置扩展风格
	m_listTagData.InsertColumn( 0, _T("TYPE"), LVCFMT_LEFT, 100 );//插入列
	m_listTagData.InsertColumn( 1, _T("Serial Num"), LVCFMT_LEFT, 150 );//插入列
	m_listTagData.InsertColumn( 2, _T("Antenna"),LVCFMT_LEFT,70);
	m_listTagData.InsertColumn( 3, _T("Found count"),LVCFMT_LEFT,80) ;

	m_cmb_commType.AddString(_T("COM"));
	m_cmb_commType.AddString(_T("Net"));
	m_cmb_commType.SetCurSel(0);

	DWORD nCount = COMPort_Enum();
	for (DWORD j=0;j<nCount;j++)
	{
		TCHAR comNameStr[512];
		memset(comNameStr,'\0',sizeof(comNameStr)/sizeof(TCHAR));
		COMPort_GetEnumItem(j,comNameStr,sizeof(comNameStr)/sizeof(TCHAR));
		m_cmb_comName.AddString(comNameStr);
	}
	if (nCount>0)
	{
		m_cmb_comName.SetCurSel(0);
	}

	m_cmb_baud.AddString(_T("9600"));
	m_cmb_baud.AddString(_T("38400"));
	m_cmb_baud.AddString(_T("57600"));
	m_cmb_baud.AddString(_T("115200"));
	m_cmb_baud.SetCurSel(1);

	m_cmb_frame.AddString(_T("8E1"));
	m_cmb_frame.AddString(_T("8N1"));
	m_cmb_frame.AddString(_T("8O1"));
	m_cmb_frame.SetCurSel(0);

	m_edit_ip.SetWindowText(_T("192.168.0.222"));
	m_edit_port.SetWindowText(_T("9909"));

	RDR_LoadReaderDrivers(_T("\\Drivers"));


	m_cmb_commType.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTONOPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTONCLOSE)->EnableWindow(FALSE);
	m_cmb_comName.EnableWindow(TRUE);
	m_cmb_baud.EnableWindow(TRUE);
	m_cmb_frame.EnableWindow(TRUE);
	m_edit_ip.EnableWindow(TRUE);
	m_edit_port.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_INVENTORY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPINVENTORY)->EnableWindow(FALSE);
	m_listTagData.EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBookshelfSampleDlg::OnPaint()
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
HCURSOR CBookshelfSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBookshelfSampleDlg::OnBnClickedButtonInventory()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTONCLOSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_INVENTORY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPINVENTORY)->EnableWindow(TRUE);
	AfxBeginThread(InventoryThrd,this);
}

void CBookshelfSampleDlg::OnBnClickedButtonopen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString connstr ;
	CString sBaud,sFrame;
	CString sComName;
	CString ipStr,portStr;
	err_t iret;

	switch(m_cmb_commType.GetCurSel())
	{
	case 0: //COM
		m_cmb_comName.GetWindowText(sComName);
		m_cmb_baud.GetWindowText(sBaud);
		m_cmb_frame.GetWindowText(sFrame);
		connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s;%s=%s;%s=%s"),_T(CONNSTR_NAME_RDTYPE) ,_T("SSR100") ,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_COM) ,_T(CONNSTR_NAME_COMNAME),sComName,_T(CONNSTR_NAME_COMBARUD) ,sBaud, _T(CONNSTR_NAME_COMFRAME),sFrame, _T(CONNSTR_NAME_BUSADDR),_T("255")) ;
		break;	
	case 1: //TCP
		m_edit_ip.GetWindowText(ipStr);
		m_edit_port.GetWindowText(portStr);
		connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s;%s=%s") ,_T(CONNSTR_NAME_RDTYPE),_T("SSR100") ,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_NET),_T(CONNSTR_NAME_REMOTEIP),ipStr ,_T(CONNSTR_NAME_REMOTEPORT) ,portStr,_T(CONNSTR_NAME_LOCALIP),_T("")) ;
		break;
	default:
		return;
	}
	iret = RDR_Open(connstr,&hReader) ;
	if (iret!=0)
	{
		AfxMessageBox(_T("Failed to open reader!"));
		return;
	}

	m_cmb_commType.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONOPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONCLOSE)->EnableWindow(TRUE);
	m_cmb_comName.EnableWindow(FALSE);
	m_cmb_baud.EnableWindow(FALSE);
	m_cmb_frame.EnableWindow(FALSE);
	m_edit_ip.EnableWindow(FALSE);
	m_edit_port.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_INVENTORY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOPINVENTORY)->EnableWindow(FALSE);
	m_listTagData.EnableWindow(TRUE);
}

void CBookshelfSampleDlg::OnBnClickedButtonclose()
{
	// TODO: 在此添加控件通知处理程序代码
	if (hReader==NULL)
	{
		return;
	}
	if (b_threadRunFlg)
	{
		AfxMessageBox(_T("Please stop the thread first!"));
		return;
	}
	RDR_Close(hReader);
	hReader = NULL;

	m_cmb_commType.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTONOPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTONCLOSE)->EnableWindow(FALSE);
	m_cmb_comName.EnableWindow(TRUE);
	m_cmb_baud.EnableWindow(TRUE);
	m_cmb_frame.EnableWindow(TRUE);
	m_edit_ip.EnableWindow(TRUE);
	m_edit_port.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_INVENTORY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOPINVENTORY)->EnableWindow(FALSE);
	m_listTagData.EnableWindow(FALSE);
}



UINT CBookshelfSampleDlg::InventoryThrd(void *lp)
 {
	 CBookshelfSampleDlg *pt = (CBookshelfSampleDlg*)lp;
	 err_t iret;
	 BYTE newAI= AI_TYPE_NEW ;
	 RFID_DN_HANDLE dnhReport = RFID_HANDLE_NULL;
	 RFID_DN_HANDLE dnInvenParamList= RFID_HANDLE_NULL ;	
	 DWORD AIPtype=0,TagType=0,AntId=0 ;
	 BYTE dsfid = 0;
	 BYTE byUid[16] = {0x00};
	 BYTE AntCount =0 ;//天线数量
	 BYTE Antennas[64];//天线列表
	 pt->b_threadRunFlg = true;
	 memset(Antennas,0x00,sizeof(Antennas));

	 //盘点的天线号
	 for (int j=0;j<pt->m_cklAntennas.GetCount();j++)
	 {
		 if (pt->m_cklAntennas.GetCheck(j)) 
		 {
			 AntCount++;
			 Antennas[j] = j+1;
		 }
	 }
	 if (AntCount<=0)
	 {
		 AfxMessageBox(_T("Please select the antennas first!"));
		 goto End;
	 }

	 pt->m_listTagData.DeleteAllItems();
	 pt->m_taglist.RemoveAll();

	 dnInvenParamList = RDR_CreateInvenParamSpecList() ;
	 if (dnInvenParamList!=NULL)
	 {
		 ISO15693_CreateInvenParam(dnInvenParamList,0,0,0,0);
	 }

	 while(pt->b_threadRunFlg)
	 {
		 iret = RDR_TagInventory(pt->hReader,newAI,AntCount,Antennas,dnInvenParamList) ;  //OKOK
		 if (iret!=NO_ERR)
		 {
			 continue;
		 }
		 dnhReport = RDR_GetTagDataReport(pt->hReader,RFID_SEEK_FIRST) ;	
		 while(dnhReport)
		 {
			 iret = ISO15693_ParseTagDataReport(dnhReport,&AIPtype,&TagType,&AntId,&dsfid,byUid) ;
			 if (iret==NO_ERR)
			 {
				  pt->AddTagToList(AIPtype,TagType,AntId,byUid,8);
			 }
			 dnhReport = RDR_GetTagDataReport(pt->hReader,RFID_SEEK_NEXT) ;	
		 }
	 }

End:
	 if (dnInvenParamList!=NULL)
	 {
		 DNODE_Destroy(dnInvenParamList);
	 }
	 RDR_ResetCommuImmeTimeout(pt->hReader);

	 pt->GetDlgItem(IDC_BUTTONCLOSE)->EnableWindow(TRUE);
	 pt->GetDlgItem(IDC_BUTTON_INVENTORY)->EnableWindow(TRUE);
	 pt->GetDlgItem(IDC_BUTTON_STOPINVENTORY)->EnableWindow(FALSE);
	 pt->EnableWindow(TRUE);

	 
	 pt->b_threadRunFlg = false;
	 return TRUE;
 }

void CBookshelfSampleDlg::AddTagToList(DWORD AIPtype,DWORD TagType,DWORD AntId,BYTE uid[],WORD uidlen)
{
	CString tagtypeName ;

	/* identify tag type */
	if(AIPtype ==RFID_APL_ISO15693_ID  && TagType == RFID_ISO15693_PICC_ICODE_SLI_ID ){
		tagtypeName =_T("NXP ICODE SLI") ;
	}
	else if(AIPtype ==RFID_APL_ISO15693_ID  && TagType ==RFID_ISO15693_PICC_TI_HFI_PLUS_ID) {
		tagtypeName = _T("Ti HF-I Plus") ;
	}

	else if(AIPtype ==RFID_APL_ISO15693_ID  && TagType == RFID_ISO15693_PICC_FUJ_MB89R118C_ID) {
		tagtypeName = _T("Fujitsu MB89R118C");
	}
	else if(AIPtype ==RFID_APL_ISO15693_ID  && TagType == RFID_ISO15693_PICC_ST_M24LR64_ID) {
		tagtypeName = _T("ST M24LR64") ;
	}
	else if(AIPtype ==RFID_APL_ISO15693_ID  && TagType == RFID_ISO15693_PICC_ST_M24LR16E_ID) {
		tagtypeName = _T("ST M24LR16E") ;
	}
	else if(AIPtype ==RFID_APL_ISO15693_ID  && TagType== RFID_ISO15693_PICC_ICODE_SLIX_ID) {
		tagtypeName= _T("NXP ICODE SLIX") ;
	}
	else if(AIPtype ==RFID_APL_ISO15693_ID  && TagType== RFID_ISO15693_PICC_TIHFI_STANDARD_ID){
		tagtypeName=_T("Ti HF-I Standard") ;
	}
	else if(AIPtype ==RFID_APL_ISO15693_ID  && TagType == RFID_ISO15693_PICC_TIHFI_PRO_ID) {
		tagtypeName=_T("Ti HF-I Pro") ;
	}
	else if(AIPtype == RFID_APL_ISO14443A_ID && TagType == RFID_ISO14443A_PICC_NXP_ULTRALIGHT_ID){
		tagtypeName =_T("NXP Mifare Ultralight") ;
	}
	else if(AIPtype ==RFID_APL_ISO14443A_ID &&  TagType ==RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID ){
		tagtypeName =_T("NXP Mifare S50") ;
	}
	else if(AIPtype == RFID_APL_ISO14443A_ID && TagType==RFID_ISO14443A_PICC_NXP_MIFARE_S70_ID){
		tagtypeName =_T("NXP Mifare S70") ;
	}
	else {
		tagtypeName  =_T("Unknown Tag") ;
	}

	TCHAR suid[32] ;
	memset(suid,0,sizeof(suid));
	BytesToHexStr(uid,uidlen,suid) ;	
	CString sAntId ;
	sAntId.Format(_T("%d"),AntId) ;
	INT32 i ;
	for( i=0;i<m_taglist.GetCount();i++) {
		if(m_taglist[i].m_uid ==suid && m_taglist[i].m_antNo == AntId) {
			break;
		}
	}
	if(i>=m_taglist.GetCount()) {
		CTag newtag;
		newtag.m_counter = 1;
		newtag.m_uid =suid ;
		newtag.m_type = TagType;
		newtag.m_antNo =AntId ;
		newtag.m_AIP =AIPtype  ;
		m_taglist.Add(newtag) ;
		int nRow=m_listTagData.InsertItem((int)m_taglist.GetCount()-1,tagtypeName);        //插入行
		m_listTagData.SetItemText(nRow,1,suid) ;
		m_listTagData.SetItemText(nRow,2,sAntId) ;
		m_listTagData.SetItemText(nRow,3,_T("1"));
	}
	else{
		m_taglist[i].m_counter++ ;
		if(m_taglist[i].m_counter>=500000)
		{
			m_taglist[i].m_counter = 1;
		}
		CString sc ;
		sc.Format(_T("%d"),m_taglist[i].m_counter) ;
		m_listTagData.SetItemText(i,3,sc) ;
	}
}
void CBookshelfSampleDlg::OnBnClickedButtonStopinventory()
{
	// TODO: 在此添加控件通知处理程序代码
	if (b_threadRunFlg)
	{
		EnableWindow(FALSE);
		RDR_SetCommuImmeTimeout(hReader);
		b_threadRunFlg = false;
	}
}
