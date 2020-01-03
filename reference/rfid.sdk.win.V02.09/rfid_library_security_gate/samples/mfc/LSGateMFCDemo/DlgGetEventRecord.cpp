// DlgGetEventRecord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LSGateMFCDemo.h"
#include "DlgGetEventRecord.h"
#include "LSGateMFCDemoDlg.h"
#include "gfunctions.h"
#include "LSGateMFCDemo.h"
#include "rfidlib_reader.h"

#define WM_THREADEXIT		(WM_USER +1 ) 


// CDlgGetEventRecord �Ի���

IMPLEMENT_DYNAMIC(CDlgGetEventRecord, CDialog)

CDlgGetEventRecord::CDlgGetEventRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGetEventRecord::IDD, pParent)
{

}

CDlgGetEventRecord::~CDlgGetEventRecord()
{
}

void CDlgGetEventRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_bntStart);
	DDX_Control(pDX, IDC_BUTTON2, m_bntStop);
	DDX_Control(pDX, IDC_LIST1, m_listvEventRecord);
	DDX_Control(pDX, IDC_RICHEDIT21, m_reErrorLog);
	DDX_Control(pDX, IDC_STATIC1, m_staCounter);
}


BEGIN_MESSAGE_MAP(CDlgGetEventRecord, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGetEventRecord::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgGetEventRecord::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgGetEventRecord::OnBnClickedButton2)
	ON_MESSAGE(WM_THREADEXIT,OnThreadExit) 
END_MESSAGE_MAP()


// CDlgGetEventRecord ��Ϣ�������

BOOL CDlgGetEventRecord::OnInitDialog()
{
	CDialog::OnInitDialog() ;

	DWORD dwStyle = m_listvEventRecord.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    //dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
    m_listvEventRecord.SetExtendedStyle(dwStyle); //������չ���
	//m_listvEventRecord.InsertColumn( 0, "�¼�����", LVCFMT_LEFT, 100 );//������
	m_listvEventRecord.InsertColumn( 0, _T("Serial Number"), LVCFMT_LEFT, 150 );//������
	m_listvEventRecord.InsertColumn( 1, _T("Direction"), LVCFMT_LEFT, 100 );//������
	m_listvEventRecord.InsertColumn( 2, _T("Time"),LVCFMT_LEFT,80);

	
	m_bntStart.EnableWindow(FALSE) ;
	m_bntStop.EnableWindow(FALSE) ;

	m_counter = 0 ;

	return TRUE ;
}

LRESULT CDlgGetEventRecord::OnThreadExit(WPARAM wparam,LPARAM lparam) 
{
	m_thrdGetReport.Stop() ;
	m_bntStart.EnableWindow(TRUE) ;
	CLSGateMFCDemoDlg *pdlg;
	pdlg = (CLSGateMFCDemoDlg *) theApp.m_pMainWnd ;
	pdlg->OnStopGetEvent() ;
	return 1;
}

void CDlgGetEventRecord::OnReaderOpen() 
{
	m_bntStart.EnableWindow(TRUE) ;
	m_bntStop.EnableWindow(FALSE) ;
}

void CDlgGetEventRecord::OnReaderClose()
{
	m_bntStart.EnableWindow(FALSE) ;
	m_bntStop.EnableWindow(FALSE) ;

}

void CDlgGetEventRecord::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bntStart.EnableWindow(FALSE) ;
	m_bntStop.EnableWindow(TRUE) ;
	
	CLSGateMFCDemoDlg *pdlg;
	pdlg = (CLSGateMFCDemoDlg *) theApp.m_pMainWnd ;
	pdlg->OnStartGetEvent() ;
	m_thrdGetReport.Start(this,ProcGetReports) ;
}
DWORD WINAPI  CDlgGetEventRecord::ProcGetReports(LPVOID lpv)
{
	CDlgGetEventRecord *pT =(CDlgGetEventRecord *)lpv ;
	BYTE flag =0 ;
	while(!pT->m_thrdGetReport.m_exit_flag) 
	{
		int iret = RDR_BuffMode_FetchRecords(hreader ,flag ) ;
		if(iret !=0 ) 
		{
			flag = 0 ;
			CString s;
			s.Format(_T("Failed!error=%d\n"),iret) ;
			pT->LogError(s) ;
		}
		else 
		{
			flag = 1;
			DWORD nCount =RDR_GetTagDataReportCount(hreader) ;
			if(nCount > 0) 
			{
				RFID_DN_HANDLE  hReport = RDR_GetTagDataReport(hreader,RFID_SEEK_FIRST) ;
				while(hReport != NULL)
				{
					BYTE reportBuf[64] ;
					DWORD nSize = sizeof(reportBuf) ;
					iret = RDR_ParseTagDataReportRaw(hReport,reportBuf ,&nSize) ;
					if(iret == 0) 
					{

						//alarm record
						if(nSize < 9) {
						   goto next_report;
						}
						BYTE evntType;
						BYTE direction;
						BYTE time[6] ;
						BYTE dataLen ;

						evntType = reportBuf[0];
						direction = reportBuf[1];
						memcpy(time ,reportBuf + 2,6) ;
						dataLen = reportBuf[8] ;
						nSize -= 9;
						if (nSize < dataLen) goto next_report;


						TCHAR strDatas[128] ;
						memset(strDatas ,0,sizeof(strDatas));
						BytesToHexStr(reportBuf + 9 ,dataLen ,strDatas) ;

						pT->AddNewReport(strDatas ,direction ,time ) ;
					}
next_report:
					hReport = RDR_GetTagDataReport(hreader,RFID_SEEK_NEXT) ;
				}
				pT->m_counter += nCount ; 
				CString str1;
				str1.Format(_T("%d , %d"),pT->m_counter ,nCount) ;
				pT->m_staCounter.SetWindowText(str1) ;
			}
		}
	}
	pT->PostMessage(WM_THREADEXIT,0,0) ;
	return 1;
}

void CDlgGetEventRecord::AddNewReport(/*BYTE eventType,*/CString slData,BYTE dir ,BYTE time[])
{

	CString strDir =_T("NULL") ;
	if(dir== 1) 
	{
		strDir =_T("In") ;
	}
	else if(dir == 2) 
	{
		strDir =_T("Out") ;
	}


	TCHAR strtime[64] ;
	memset(strtime,0,sizeof(strtime));
	BytesToHexStr(time,6,strtime) ;


	int nRow=m_listvEventRecord.InsertItem(m_listvEventRecord.GetItemCount(),slData);        //������
	//m_listvEventRecord.SetItemText(nRow,1,slData) ;
	m_listvEventRecord.SetItemText(nRow,1,strDir) ;
	m_listvEventRecord.SetItemText(nRow,2,strtime) ;
}

void CDlgGetEventRecord::LogError(CString msg)
{
	long  nInsertAfterChar = m_reErrorLog.GetWindowTextLength();
	m_reErrorLog.SetSel(nInsertAfterChar, nInsertAfterChar);
	m_reErrorLog.ReplaceSel(msg, FALSE);
}

void CDlgGetEventRecord::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_listvEventRecord.DeleteAllItems() ;
}

void CDlgGetEventRecord::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bntStop.EnableWindow(FALSE) ;
	m_thrdGetReport.SetExitVar() ;
}
