// DlgOpen.cpp : 实现文件
//

#include "stdafx.h"
#include "RS485Sample.h"
#include "DlgOpen.h"
#include "rfidlib.h"
#include "rfidlib_ANRD201.h"
#include "rfidlib_reader.h"
#include "rfidlib_reader.h"


// CDlgOpen 对话框

IMPLEMENT_DYNAMIC(CDlgOpen, CDialog)

CDlgOpen::CDlgOpen(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOpen::IDD, pParent)
{

}

CDlgOpen::~CDlgOpen()
{
}

void CDlgOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbReaders);
	DDX_Control(pDX, IDC_COMBO1, m_cbbCOMs);
	DDX_Control(pDX, IDC_CMBREADERTYPE, m_cbbReaderType);
}


BEGIN_MESSAGE_MAP(CDlgOpen, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgOpen::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgOpen 消息处理程序
BOOL CDlgOpen::OnInitDialog()
{
	CDialog::OnInitDialog() ;

	for(DWORD i=0;i<RDR_GetLoadedReaderDriverCount() ;i++)
	{
		DWORD nSize ;
		CRdrInfo rdrinfo ;
		TCHAR tmp[64] ;
		memset(tmp,0,sizeof(tmp)) ;
		nSize = sizeof(tmp) / sizeof(TCHAR);
		RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_CATALOG),tmp, &nSize) ;
		rdrinfo.m_Catalog= tmp ;
		if(rdrinfo.m_Catalog ==_T(RDRDVR_TYPE_READER))
		{
			memset(tmp,0,sizeof(tmp)) ;
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_COMMTYPESUPPORTED),tmp,&nSize) ;
			rdrinfo.m_CommTypeSupported = _ttoi(tmp) ; 
			if(COMMTYPE_COM_EN!=(rdrinfo.m_CommTypeSupported&0x01))//不支持串口
			{
				continue;
			}

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
		m_cbbReaderType.AddString(m_readerList[i].m_name) ;
	}
	if(m_cbbReaderType.GetCount()> 0 ){
		m_cbbReaderType.SetCurSel(0) ;
	}

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
			m_cbbCOMs.AddString(comname) ;
		}
	}
	m_cbbCOMs.SetCurSel(0) ;

	m_listbReaders.AddString(_T("RS485 Node#1")) ;
	m_listbReaders.AddString(_T("RS485 Node#2")) ;
	m_listbReaders.AddString(_T("RS485 Node#3")) ;
	m_listbReaders.AddString(_T("RS485 Node#4")) ;
	m_listbReaders.AddString(_T("RS485 Node#5")) ;
	m_listbReaders.AddString(_T("RS485 Node#6")) ;
	m_listbReaders.AddString(_T("RS485 Node#7")) ;
	m_listbReaders.AddString(_T("RS485 Node#8")) ;
	m_listbReaders.AddString(_T("RS485 Node#9")) ;
	m_listbReaders.AddString(_T("RS485 Node#10")) ;
	return TRUE ;
}

void CDlgOpen::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/* open rfid reader */
#if 0
	int iret;
	RFID_READER_HANDLE hr;
	TCHAR com[64] ;
	memset(com,0,sizeof(com)) ;
	m_cbbCOMs.GetWindowText(com,sizeof(com) / sizeof(TCHAR)) ;
	int  i ;
	for( i=0;i<m_listbReaders.GetCount();i++ ) {
		if(m_listbReaders.GetCheck(i) ) {
			break;
		}
	}
	if(i >= m_listbReaders.GetCount()) {
		MessageBox("select reader please !","",MB_OK) ;
		return ;
	}

	m_pParent->reader_close_api = ANRD201_Close ;
	iret = ANRD201_Open(com,38400,"8E1",&hr) ;
	if(iret != NO_ERR) {
		m_pParent->reader_close_api =NULL ;
		MessageBox("open reader fail","",MB_OK) ;
		return ;
	}
	m_pParent->m_hr = hr ;
	//create RS485 reader .
	for(int i=0;i<m_listbReaders.GetCount();i++ ) {
		if(m_listbReaders.GetCheck(i) ) {
			hr =0 ;
			iret = RDR_CreateRS485Node(m_pParent->m_hr ,i+1,&hr) ;
			if(iret  == 0) {
				m_pParent->m_hRS485.Add(hr) ;
				m_pParent->m_busAddr.Add(i+1) ;
			}
		}
	}
	OnOK();
#endif

	int iret;
	RFID_READER_HANDLE hr;
	TCHAR com[64] ;
	memset(com,0,sizeof(com)) ;
	m_cbbCOMs.GetWindowText(com,sizeof(com) / sizeof(TCHAR)) ;
	int  i ;
	for( i=0;i<m_listbReaders.GetCount();i++ ) 
	{
		if(m_listbReaders.GetCheck(i) ) 
		{
			break;
		}
	}
	if(i >= m_listbReaders.GetCount()) 
	{
		MessageBox(_T("select reader please !"),_T(""),MB_OK) ;
		return ;
	}

	m_pParent->reader_close_api = RDR_Close ;

	CString connstr;
	int idx = m_cbbReaderType.GetCurSel();
	connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s;%s=%s;%s=%d"),_T(CONNSTR_NAME_RDTYPE),m_readerList[idx].m_name ,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_COM),_T(CONNSTR_NAME_COMNAME),com,_T(CONNSTR_NAME_COMBARUD),_T("38400"),_T(CONNSTR_NAME_COMFRAME),_T("8E1"),_T(CONNSTR_NAME_BUSADDR),i+1);
	iret = RDR_Open(connstr,&hr) ;

	if(iret != NO_ERR) 
	{
		m_pParent->reader_close_api =NULL ;
		MessageBox(_T("open reader fail"),_T(""),MB_OK) ;
		return ;
	}
	m_pParent->m_hr = hr ;
	for(int i=0;i<m_listbReaders.GetCount();i++ ) 
	{
		if(m_listbReaders.GetCheck(i) ) 
		{
			hr =0 ;
			iret = RDR_CreateRS485Node(m_pParent->m_hr ,i+1,&hr) ;
			if(iret  == 0) 
			{
				m_pParent->m_hRS485.Add(hr) ;
				m_pParent->m_busAddr.Add(i+1) ;
			}
		}
	}
	OnOK();
}