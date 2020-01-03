// DlgControlCommand.cpp : 实现文件
//

#include "stdafx.h"
#include "LSGateMFCDemo.h"
#include "DlgControlCommand.h"
#include "rfidlib_reader.h"


// CDlgControlCommand 对话框

IMPLEMENT_DYNAMIC(CDlgControlCommand, CDialog)

CDlgControlCommand::CDlgControlCommand(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgControlCommand::IDD, pParent)
{

}

CDlgControlCommand::~CDlgControlCommand()
{
}

void CDlgControlCommand::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_bntGetFlow);
	DDX_Control(pDX, IDC_BUTTON4, m_bntClearFlow);
	DDX_Control(pDX, IDC_BUTTON5, m_bntReservedDir);
	DDX_Control(pDX, IDC_STATIC1, m_stacInFlow);
	DDX_Control(pDX, IDC_STATIC2, m_stacOutFlow);
	DDX_Control(pDX, IDC_STATIC3, m_stacSystime);
	DDX_Control(pDX, IDC_BUTTON2, m_bntUpdateTime);
	DDX_Control(pDX, IDC_BUTTON3, m_bntFetchTime);
}


BEGIN_MESSAGE_MAP(CDlgControlCommand, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgControlCommand::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlgControlCommand::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgControlCommand::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgControlCommand::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlgControlCommand::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDlgControlCommand 消息处理程序
BOOL CDlgControlCommand::OnInitDialog() 
{
	CDialog::OnInitDialog() ;
	m_bntGetFlow.EnableWindow(FALSE);
	m_bntClearFlow.EnableWindow(FALSE) ;
	m_bntReservedDir.EnableWindow(FALSE) ;
	m_bntUpdateTime.EnableWindow(FALSE) ;
	m_bntFetchTime.EnableWindow(FALSE) ;

	return TRUE ;
}

void CDlgControlCommand::OnReaderOpen()
{
	m_bntGetFlow.EnableWindow(TRUE);
	m_bntClearFlow.EnableWindow(TRUE) ;
	m_bntReservedDir.EnableWindow(TRUE) ;
	m_bntUpdateTime.EnableWindow(TRUE) ;
	m_bntFetchTime.EnableWindow(TRUE) ;
}

void CDlgControlCommand::OnReaderClose()
{
	m_bntGetFlow.EnableWindow(FALSE);
	m_bntClearFlow.EnableWindow(FALSE) ;
	m_bntReservedDir.EnableWindow(FALSE) ;
	m_bntUpdateTime.EnableWindow(FALSE) ;
	m_bntFetchTime.EnableWindow(FALSE) ;
}

void CDlgControlCommand::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret =0 ;
	DWORD inFlow=0 ,outFlow =0 ;
	//iret =LSG_CmdGetCurrentFlowOfPeople(hreader,&inFlow,&outFlow)   ;
	iret = RDR_GetPassingCounter(hreader,&inFlow,&outFlow)   ;
	if(iret != 0) {
		ShowError(_T("Get flow of people failed"),iret) ;
		return; 
	}
	CString strInFlow,strOutFlow ;
	strInFlow.Format(_T("%d"),inFlow) ;
	m_stacInFlow.SetWindowText(strInFlow) ;
	strOutFlow.Format(_T("%d"),outFlow) ;
	m_stacOutFlow.SetWindowText(strOutFlow) ;

}

void CDlgControlCommand::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret=0 ;
	//iret =  LSG_CmdResetFlowOfPeople(hreader,3) ;
	iret =RDR_ResetPassingCounter(hreader,3) ;
	if(iret != 0) {
		ShowError(_T("reset flow of people failed"),iret)  ;
		return ;
	}
	m_stacInFlow.SetWindowText(_T("0")) ;
	m_stacOutFlow.SetWindowText(_T("0")) ;
}

void CDlgControlCommand::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	SYSTEMTIME systime;
	GetLocalTime(&systime) ;
	iret  =RDR_SetSystemTime(hreader,systime.wYear,systime.wMonth,systime.wDay,systime.wHour,systime.wMinute,systime.wSecond) ;
	if(iret != 0){
		ShowError(_T("Set system time failed!"),iret) ;
		return ;
	}
	MessageBox(_T("Success"),_T("") ,MB_OK) ;
}

void CDlgControlCommand::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	DWORD wYear ;
	BYTE bMonth,bDay,bHour,bMinute,bSecond ;
	iret = RDR_GetSystemTime(hreader,&wYear,&bMonth,&bDay,&bHour,&bMinute,&bSecond ) ;
	if(iret != 0) {
		ShowError(_T("Get system time failed!"),iret) ;
		return ;
	}
	CString str1;
	str1.Format(_T("%d-%d-%d %d:%d:%d"),wYear ,bMonth,bDay,bHour,bMinute,bSecond) ;
	m_stacSystime.SetWindowText(str1) ;
}

void CDlgControlCommand::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret =0  ;
	//iret =LSG_CmdReverseDirection( hreader)  ;
	iret =RDR_ReverseInOutDirection(hreader) ;
	if(iret != 0) {
		ShowError(_T("Failed"),iret) ;
		return ;
	}
	MessageBox(_T("Success"),_T(""),MB_OK) ;
}

void CDlgControlCommand::ShowError(CString msg,int iret) 
{
	CString s1;
	s1.Format(_T("%s,Error Codes=%d"),msg,iret) ;
	MessageBox(s1,_T("Error"),MB_OK) ;
}