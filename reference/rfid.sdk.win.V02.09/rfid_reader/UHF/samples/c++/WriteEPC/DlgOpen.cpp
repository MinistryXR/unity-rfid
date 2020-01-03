
#include "stdafx.h"
#include "DlgOpen.h"
#include "rfidlib.h"
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
	DDX_Control(pDX, IDC_COMBO_COM, cbb_COMs);
	DDX_Control(pDX, IDC_COMBO_READERTYPE, m_cbbReaderType);
	DDX_Control(pDX, IDC_COMBO_USBOPENTYPE, m_cbbUsbOpenType);
	DDX_Control(pDX, IDC_COMBO_USBSERIAL, m_cbbSerialNum);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipAddrIP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_netPort);
	DDX_Control(pDX, IDC_COMBO_COMMTYPE, m_cbbCommunicationType);
	DDX_Control(pDX, IDC_COMBO_BAUD, cbb_baud);
	DDX_Control(pDX, IDC_COMBO_FRAME, cbb_frame);
}


BEGIN_MESSAGE_MAP(CDlgOpen, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgOpen::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_READERTYPE, &CDlgOpen::OnCbnSelchangeCombo11)
	ON_CBN_SELCHANGE(IDC_COMBO_USBOPENTYPE, &CDlgOpen::OnCbnSelchangeCombo12)
	ON_CBN_SELCHANGE(IDC_COMBO_COMMTYPE, &CDlgOpen::OnCbnSelchangeCombo14)
	ON_BN_CLICKED(IDCANCEL, &CDlgOpen::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgOpen 消息处理程序
BOOL CDlgOpen::OnInitDialog()
{
	CDialog::OnInitDialog();

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
			cbb_COMs.AddString(comname) ;
		}
	}
	if(cbb_COMs.GetCount() > 0) 
	{
		cbb_COMs.SetCurSel(0) ;
	}

	m_cbbCommunicationType.AddString(_T("COM")) ;
	m_cbbCommunicationType.AddString(_T("USB")) ;
	m_cbbCommunicationType.AddString(_T("TCP")) ;
	m_cbbCommunicationType.AddString(_T("Bluetooth")) ;
	m_cbbCommunicationType.SetCurSel( 0) ;
	//cbb_COMs.AddString(_T("COM1")) ;
	//cbb_COMs.AddString(_T("COM2")) ;
	//cbb_COMs.AddString(_T("COM3")) ;
	//cbb_COMs.AddString(_T("COM4")) ;
	//cbb_COMs.AddString(_T("COM5")) ;
	//cbb_COMs.AddString(_T("COM6")) ;
	//cbb_COMs.AddString(_T("COM7")) ;
	//cbb_COMs.AddString(_T("COM8")) ;
	//cbb_COMs.AddString(_T("COM9")) ;
	//

#if 0
	m_cbbReaderType.AddString("ANM200") ;
	m_cbbReaderType.AddString("ANM201") ;
	m_cbbReaderType.AddString("ANRD201") ;
	m_cbbReaderType.AddString("ANRD5112") ;
	m_cbbReaderType.AddString("ANRD120") ;
	m_cbbReaderType.AddString("ANRD242") ;
	m_cbbReaderType.AddString("ANRD100") ;
	m_cbbReaderType.AddString("ANM103R") ;
	m_cbbReaderType.AddString("ANRD501") ;
	m_cbbReaderType.AddString("ANSSR100-TCP") ;
	m_cbbReaderType.AddString("ANSSR100-Serial") ;
	m_cbbReaderType.AddString("ANRD131") ;
	m_cbbReaderType.AddString("ANRD122") ;
	m_cbbReaderType.AddString("ANRD5112-TCP") ;
	m_cbbReaderType.AddString("ANRD120M") ;
	m_cbbReaderType.SetCurSel(0) ;
#endif 
	for(int i=0;i<RDR_GetLoadedReaderDriverCount() ;i++){
		DWORD nSize ;
		CRdrInfo rdrinfo ;
		TCHAR tmp[64] ;
		memset(tmp,0,sizeof(tmp)) ;
		nSize = sizeof(tmp) / sizeof(TCHAR);
		RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_CATALOG) ,tmp, &nSize) ;
		rdrinfo.m_Catalog= tmp ;
		if(rdrinfo.m_Catalog ==_T(RDRDVR_TYPE_READER)){
			memset(tmp,0,sizeof(tmp));
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_NAME) , tmp,&nSize) ;
			rdrinfo.m_name = tmp ;

			memset(tmp,0,sizeof(tmp)) ;
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_ID) ,tmp,&nSize) ;
			rdrinfo.m_productType = tmp ;
			memset(tmp,0,sizeof(tmp)) ;
			nSize = sizeof(tmp) / sizeof(TCHAR);
			RDR_GetLoadedReaderDriverOpt(i,_T(LOADED_RDRDVR_OPT_COMMTYPESUPPORTED) ,tmp,&nSize) ;
			rdrinfo.m_CommTypeSupported = _ttoi(tmp) ; 

			m_readerList.Add(rdrinfo) ;
		}
	}
	for(int i= 0;i<m_readerList.GetCount();i++){
		m_cbbReaderType.AddString(m_readerList[i].m_name) ;
	}
	if(m_cbbReaderType.GetCount()> 0 ){
		m_cbbReaderType.SetCurSel(0) ;
	}

	cbb_baud.AddString(_T("9600"));
	cbb_baud.AddString(_T("19200")) ;
	cbb_baud.AddString(_T("38400"));
	cbb_baud.AddString(_T("57600"));
	cbb_baud.AddString(_T("115200"));
	cbb_baud.SetCurSel(2);

	cbb_frame.AddString(_T("8E1"));
	cbb_frame.AddString(_T("8N1"));
	cbb_frame.AddString(_T("8O1"));
	cbb_frame.SetCurSel(0);
	

	m_cbbUsbOpenType.AddString(_T("None addressed")) ;
	m_cbbUsbOpenType.AddString(_T("Serial number")) ;
	m_cbbUsbOpenType.SetCurSel(0) ;

	m_ipAddrIP.SetAddress(192,168,0,222) ;
	m_netPort.SetWindowText(_T("9909")) ;

	m_cbbUsbOpenType.EnableWindow(FALSE) ;
	m_cbbSerialNum.EnableWindow(FALSE) ;
	m_ipAddrIP.EnableWindow(FALSE) ;
	m_netPort.EnableWindow(FALSE) ;
	return TRUE;  
}
void CDlgOpen::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/* open rfid reader */
	int idx ;
	int idxCommType ;
	err_t iret= NO_ERR;
	idx = m_cbbReaderType.GetCurSel() ;
	if(idx == -1 )
	{
		MessageBox(_T("Select reader type please"),_T(""),MB_OK) ;
		return ;
	}
	idxCommType = m_cbbCommunicationType.GetCurSel() ;
	if(idxCommType == -1){
		MessageBox(_T("Select communication type please"),_T(""),MB_OK) ;
		return ;	
	}
	TCHAR com[64] ;
	memset(com,0,sizeof(com)) ;
	cbb_COMs.GetWindowText(com,sizeof(com) / sizeof(TCHAR)) ;

	int usbOpenType = m_cbbUsbOpenType.GetCurSel() ;
	TCHAR usbSerialNum[64] ;
	memset(usbSerialNum,0,sizeof(usbSerialNum)) ;
	m_cbbSerialNum.GetWindowText(usbSerialNum,sizeof(usbSerialNum)/sizeof(TCHAR)) ;

	BYTE ip_b1,ip_b2,ip_b3,ip_b4;
	m_ipAddrIP.GetAddress(ip_b1,ip_b2,ip_b3,ip_b4) ;
	WORD port ;
	TCHAR portbuf[32] ;
	memset(portbuf,0,sizeof(portbuf)) ;
	m_netPort.GetWindowText(portbuf,sizeof(portbuf)) ;
	port =_ttoi(portbuf) ;
	CString ipStr;
	ipStr.Format(_T("%d.%d.%d.%d"),ip_b1,ip_b2,ip_b3,ip_b4) ;

	if(usbOpenType == -1) {
		MessageBox(_T("Please select USB open type!")) ;
		return ;
	}

	CString connstr ;
	CString sBaud,sFrame;
	switch(idxCommType){
		case 0: //COM
			cbb_baud.GetWindowText(sBaud);
			cbb_frame.GetWindowText(sFrame);
			connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%s;%s=%s;%s=%s"),_T(CONNSTR_NAME_RDTYPE) ,m_readerList[idx].m_name ,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_COM) ,_T(CONNSTR_NAME_COMNAME),com,_T(CONNSTR_NAME_COMBARUD) ,sBaud, _T(CONNSTR_NAME_COMFRAME),sFrame, _T(CONNSTR_NAME_BUSADDR),_T("255")) ;
			break;
		case 1: //USB 
			connstr.Format(_T("%s=%s;%s=%s;%s=%d;%s=%s"),_T(CONNSTR_NAME_RDTYPE) ,m_readerList[idx].m_name,_T(CONNSTR_NAME_COMMTYPE) ,_T(CONNSTR_NAME_COMMTYPE_USB) ,_T(CONNSTR_NAME_HIDADDRMODE) ,usbOpenType ,_T(CONNSTR_NAME_HIDSERNUM),usbSerialNum) ;
			break;
		case 2: //TCP
			connstr.Format(_T("%s=%s;%s=%s;%s=%s;%s=%d;%s=%s") ,_T(CONNSTR_NAME_RDTYPE),m_readerList[idx].m_name ,_T(CONNSTR_NAME_COMMTYPE),_T(CONNSTR_NAME_COMMTYPE_NET),_T(CONNSTR_NAME_REMOTEIP),ipStr ,_T(CONNSTR_NAME_REMOTEPORT) ,port,_T(CONNSTR_NAME_LOCALIP),_T("")) ;
			break;
	}
	//MessageBox(connstr,"",MB_OK) ;
	iret = RDR_Open(connstr,&hr) ;


	//
	//
	if(iret != NO_ERR) {
		//reader_close_api =NULL ;
		MessageBox(_T("open reader fail"),_T(""),MB_OK) ;
		return ;
	}
	AntennaIFCountOfReader = RDR_GetAntennaInterfaceCount(hr) ;
	OnOK();
}

void CDlgOpen::OnCbnSelchangeCombo11()
{
	int idx ;
	idx = m_cbbReaderType.GetCurSel() ;
	if(idx  == -1) return ;
	if((m_readerList[idx].m_CommTypeSupported & COMMTYPE_USB_EN) > 0) {
		while(m_cbbSerialNum.GetCount()> 0) m_cbbSerialNum.DeleteString(0) ;
		err_t iret;
		DWORD nCount ;
		nCount =HID_Enum(m_readerList[idx].m_name) ;
		for(int i=0;i<nCount;i++) {
			TCHAR sernum[64] ;
			memset(sernum,0,sizeof(sernum));
			DWORD nSize = sizeof(sernum)/sizeof(TCHAR) ; // in character
			iret = HID_GetEnumItem(i,HID_ENUM_INF_TYPE_SERIALNUM,sernum,&nSize) ;
			if(iret == NO_ERR) {
				m_cbbSerialNum.AddString(sernum) ;
			}
		}

	} 

}

void CDlgOpen::OnCbnSelchangeCombo12()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx;
	idx =m_cbbUsbOpenType.GetCurSel() ;
	if(idx  == 0) {
		m_cbbSerialNum.EnableWindow(FALSE) ;
	}
	else {
		m_cbbSerialNum.EnableWindow(TRUE);
	}	
}

void CDlgOpen::OnCbnSelchangeCombo14()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	int idx ;
	idx = m_cbbReaderType.GetCurSel() ;
	if(idx == -1) return ;
	int CommTypeIdx ;
	CommTypeIdx = m_cbbCommunicationType.GetCurSel() ;

	cbb_COMs.EnableWindow(FALSE) ;
	cbb_baud.EnableWindow(FALSE);
	cbb_frame.EnableWindow(FALSE);
	m_ipAddrIP.EnableWindow(FALSE) ;
	m_netPort.EnableWindow(FALSE) ;
	m_cbbUsbOpenType.EnableWindow(FALSE) ;
	//m_cbbUsbOpenType.SetCurSel(0) ;
	m_cbbSerialNum.EnableWindow(FALSE) ;
	if(CommTypeIdx== 0){
		cbb_COMs.EnableWindow(TRUE) ;
		cbb_baud.EnableWindow(TRUE);
		cbb_frame.EnableWindow(TRUE);
	}
	else if(CommTypeIdx ==1) {
		m_cbbUsbOpenType.EnableWindow(TRUE) ;
		m_cbbUsbOpenType.SetCurSel(0) ;
		m_cbbSerialNum.EnableWindow(FALSE) ;
	}
	else if(CommTypeIdx ==2){
		m_ipAddrIP.EnableWindow(TRUE) ;
		m_netPort.EnableWindow(TRUE) ;
	}
	
}

void CDlgOpen::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
