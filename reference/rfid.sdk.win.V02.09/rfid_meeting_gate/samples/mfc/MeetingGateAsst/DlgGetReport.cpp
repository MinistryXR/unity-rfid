// DlgGetReport.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcdemo1.h"
#include "DlgGetReport.h"
#include "rfidlib.h"
#include "wtlthread.h"
#include "rfidlib_reader.h"
#include "gfunctions.h"


#define WM_REPORTGETTED			(WM_USER + 1)
#define WM_RUNERROR				(WM_USER+2)
#define WM_COLLECTION_EXT		(WM_USER +3 )


// CDlgGetReport 对话框

IMPLEMENT_DYNAMIC(CDlgGetReport, CDialog)

CDlgGetReport::CDlgGetReport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetReport::IDD, pParent)
{

}

CDlgGetReport::~CDlgGetReport()
{
}

void CDlgGetReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listReports);
	DDX_Control(pDX, IDC_BUTTON1, m_bntStart);
	DDX_Control(pDX, IDC_BUTTON2, m_bntStop);
	DDX_Control(pDX, IDC_BUTTON3, m_bntClear);
	DDX_Control(pDX, IDC_RICHEDIT21, m_rchedtErrLog);
	DDX_Control(pDX, IDC_STATIC1, m_staTotal);
}


BEGIN_MESSAGE_MAP(CDlgGetReport, CDialog)
	ON_MESSAGE(WM_REPORTGETTED,OnMsgReportGetted) 
	ON_MESSAGE(WM_RUNERROR ,OnMsgErrorOccur) 
	ON_MESSAGE(WM_COLLECTION_EXT ,OnMsgCollectExit) 
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgGetReport::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGetReport::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgGetReport::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDlgGetReport 消息处理程序
BOOL CDlgGetReport::OnInitDialog()
{
	CDialog::OnInitDialog() ;
	
	DWORD dwStyle = m_listReports.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
    m_listReports.SetExtendedStyle(dwStyle); //设置扩展风格
	m_listReports.InsertColumn( 0, _T("Serial number"), LVCFMT_LEFT, 150 );//插入列
	m_listReports.InsertColumn( 1, _T("Directions"), LVCFMT_LEFT, 100 );//插入列
	m_listReports.InsertColumn( 2, _T("Instead state"), LVCFMT_LEFT, 100 );//插入列


	m_bntStart.EnableWindow(FALSE) ;
	m_bntStop.EnableWindow(FALSE) ;
	m_bntClear.EnableWindow(FALSE) ;

	m_totalGetted =0 ;

	return TRUE ;
}

void CDlgGetReport::addReports(TCHAR uid[],BYTE direction,BYTE time[])
{
	CString strDir ;
	CString strInstead ;
	//int reccount=0;
	BYTE  insteadCheckingFlag ;
	insteadCheckingFlag= (direction >> 7 ) & 0x01;
	direction= direction & 0x7f;
	switch(direction) 
	{
	case 0:
		strDir = _T("No direction") ;
		break;
	case 1:
		strDir = _T("In") ;
		break;
	case 2:
		strDir =_T("Out") ;
		break;
	default:
		strDir =_T("Error value") ;

	}
	if(insteadCheckingFlag) 
	{
		strInstead=_T("Yes");
	}

	int nRow=m_listReports.InsertItem(m_listReports.GetItemCount(),uid);        //插入行
	m_listReports.SetItemText(nRow,1,strDir) ;
	m_listReports.SetItemText(nRow,2,strInstead) ;

	//m_totalGetted++ ;
	//reccount++ ;

	/*CString s ;
	s.Format("%d , %d" ,m_totalGetted ,reccount ) ;
	this->m_staTotal.SetWindowText(s) ;*/
}

LRESULT CDlgGetReport::OnMsgReportGetted(WPARAM wParam, LPARAM lParam)
{
	int iret;
	int reccount  =0 ;
	
	RFID_DN_HANDLE dnhReport = RDR_GetTagDataReport(hr,RFID_SEEK_FIRST);
	while (dnhReport!=RFID_HANDLE_NULL)
	{
		//memset(uid,0,sizeof(uid)) ;
		//iret = MGXXX_ParseIOReportData(hr,dnhReport,uid,nSize ,&direction,time) ;
		BYTE reportBuffer[64] ;
		DWORD nSize = sizeof(reportBuffer);
		iret = RDR_ParseTagDataReportRaw(dnhReport ,reportBuffer,&nSize) ;
		if (iret==NO_ERR)
		{
           if (nSize < 9) goto next_report;
           BYTE eventType;
           BYTE direction;
           BYTE  time[6];
           BYTE dataLen;

           eventType = reportBuffer[0];
           direction = reportBuffer[1];
		   memcpy(time ,reportBuffer + 2,6);
           dataLen = reportBuffer[8];

           nSize -= 9;
           if (nSize < dataLen) goto next_report;

		   TCHAR strDatas[128] ;
		   memset(strDatas ,0,sizeof(strDatas));
		   BytesToHexStr(reportBuffer + 9 ,dataLen ,strDatas) ;
                
			addReports(strDatas,direction,time);
			m_totalGetted++ ;
			reccount++ ;
		}
next_report:
		dnhReport = RDR_GetTagDataReport(hr,RFID_SEEK_NEXT);
	}

	CString s ;
	s.Format(_T("%d , %d") ,m_totalGetted ,reccount ) ;
	this->m_staTotal.SetWindowText(s) ;
	return  0 ;
}

LRESULT CDlgGetReport::OnMsgErrorOccur(WPARAM wParam, LPARAM lParam)
{
	int err = lParam ;
	CString errstr ;
	errstr.Format(_T("Error Codes:%d \n") , err) ;
	long  nInsertAfterChar = m_rchedtErrLog.GetWindowTextLength();
	m_rchedtErrLog.SetSel(nInsertAfterChar, nInsertAfterChar);
	m_rchedtErrLog.ReplaceSel(errstr, FALSE);
	return  0;
}

LRESULT CDlgGetReport::OnMsgCollectExit(WPARAM wParam, LPARAM lParam)
{
	RDR_BuffMode_StopReportCollection(hr) ;
	m_bntStart.EnableWindow(TRUE) ;
	return  0 ;
}


void CDlgGetReport::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bntStop.EnableWindow(FALSE) ;
	RDR_BuffMode_StopReportCollectionNoWait(hr) ;
}

void CDlgGetReport::OnBnClickedButton1()
{
	
	m_bntStart.EnableWindow(FALSE) ;
	m_bntStop.EnableWindow(TRUE) ;

	//RDR_SetEventHandler()

	/*
	*  报告获取成功事件
	*  使用SendMessage同步消息方式返回
	*/
	RDR_SetEventHandler(hr,RFIDLIB_EVNT_GETBUF_REPORT_FOUND,RFID_EVTMED_USE_MSG,WM_REPORTGETTED,this->m_hWnd,NULL,NULL) ;
	/*
	*  获取报告失败事件
	*  使用SendMessage同步消息方式返回
	*/
	RDR_SetEventHandler(hr,RFIDLIB_EVNT_GETBUF_ERROR ,RFID_EVTMED_USE_MSG ,WM_RUNERROR,this->m_hWnd,NULL,NULL) ;
	/*
	* 采集线程退出事件
	* 需要调用MGXXX_StopLoopCollectingBegin 使线程退出，使用PostMessage异步消息的方式返回
	*/
	RDR_SetEventHandler(hr,RFIDLIB_EVNT_GETBUF_EXIT ,RFID_EVTMED_USE_POSTMSG ,WM_COLLECTION_EXT,this->m_hWnd,NULL,NULL) ;
	
	RDR_BuffMode_StartReportCollection(hr) ;
}


void CDlgGetReport::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listReports.DeleteAllItems() ;
}

