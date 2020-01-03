// DlgControl.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcdemo1.h"
#include "DlgControl.h"
#include "rfidlib_reader.h"


// CDlgControl 对话框

IMPLEMENT_DYNAMIC(CDlgControl, CDialog)

CDlgControl::CDlgControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgControl::IDD, pParent)
{

}

CDlgControl::~CDlgControl()
{
}

void CDlgControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listOutputs);
	DDX_Control(pDX, IDC_COMBO21, m_cbbCtrlActiveTime);
	DDX_Control(pDX, IDC_COMBO22, m_cbbCtrlFrequence);
	DDX_Control(pDX, IDC_COMBO23, m_cbbCtrlDeactiveTime);
	DDX_Control(pDX, IDC_BUTTON1, m_bntCtrlOutput);
}


BEGIN_MESSAGE_MAP(CDlgControl, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgControl::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgControl 消息处理程序
BOOL CDlgControl::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_listOutputs.AddString(_T("Buzzer on board")) ;
	m_listOutputs.AddString(_T("Port#1")) ;
	m_listOutputs.AddString(_T("Port#2")) ;
	m_listOutputs.AddString(_T("Port#3")) ;
	m_listOutputs.AddString(_T("Port#4")) ;

	for(int i=1;i<=255;i++) {
		CString str1;
		str1.Format(_T("%d") ,i ) ;
		m_cbbCtrlActiveTime.AddString(str1) ;
		m_cbbCtrlDeactiveTime.AddString(str1) ;
		m_cbbCtrlFrequence.AddString(str1) ;
	}
	m_cbbCtrlActiveTime.SetCurSel(0) ;
	m_cbbCtrlDeactiveTime.SetCurSel(0) ;
	m_cbbCtrlFrequence.SetCurSel(0) ;

	m_bntCtrlOutput.EnableWindow(FALSE) ;
	return TRUE ;
}
void CDlgControl::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
#if 0
	int iret;
	int i ;
	BYTE outputSel  =0 ;
	BYTE activeTime,frequency,deactiveTime ;
	for(i=0 ;i<m_listOutputs.GetCount();i++) {
		if(m_listOutputs.GetCheck(i) ) {
			outputSel|=(0x01 << i ) ;
		}
	}
	if(outputSel == 0) {
		MessageBox("请选择输出端口","",MB_OK) ;
		return ;
	}
	int idx;
	idx =m_cbbCtrlActiveTime.GetCurSel() ;
	if(idx == -1) {
		MessageBox("请选择激活时间","",MB_OK) ;
		return ;
	}
	activeTime = idx + 1;
	idx = m_cbbCtrlFrequence.GetCurSel() ;
	if(idx == -1) {
		MessageBox("请选择输出频率","",MB_OK) ;
		return ;
	}
	frequency = idx + 1;
	idx = m_cbbCtrlDeactiveTime.GetCurSel() ;
	if(idx == -1) {
		MessageBox("请选择停止时间","",MB_OK) ;
		return ;
	}
	deactiveTime = idx + 1;
	iret  =MGXXX_SetOutputPort(hr,outputSel,activeTime,frequency,deactiveTime);
	if(iret != 0) {
		CString str1;
		str1.Format("输出失败,错误:%d" ,iret) ;
		MessageBox(str1,"",MB_OK) ;
		return ;
	}
	MessageBox("成功","",MB_OK) ;
#endif
	int iret;
	BYTE activeTime,frequency,deactiveTime ;
	RFID_DN_HANDLE dnOutputOper;
	dnOutputOper = RDR_CreateSetOutputOperations() ;
	for(int i=0 ;i<m_listOutputs.GetCount();i++) 
	{
		if(m_listOutputs.GetCheck(i)==FALSE) 
		{
			continue;
		}

		int idx;
		idx =m_cbbCtrlActiveTime.GetCurSel() ;
		if(idx == -1) 
		{
			MessageBox(_T("Please select the Activation time."),_T(""),MB_OK) ;
			return ;
		}
		activeTime = idx + 1;
		idx = m_cbbCtrlFrequence.GetCurSel() ;
		if(idx == -1) 
		{
			MessageBox(_T("Please select the Frequency."),_T(""),MB_OK) ;
			return ;
		}
		frequency = idx + 1;
		idx = m_cbbCtrlDeactiveTime.GetCurSel() ;
		if(idx == -1) 
		{
			MessageBox(_T("Please select the stop time."),_T(""),MB_OK) ;
			return ;
		}
		deactiveTime = idx + 1;

		iret = RDR_AddOneOutputOperation(dnOutputOper,i+1,3,frequency,activeTime * 100,deactiveTime * 100);
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
