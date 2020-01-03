#pragma once
#include "afxwin.h"
#include "wtlthread.h"
#include "afxcmn.h"


// CDlgGetEventRecord 对话框

class CDlgGetEventRecord : public CDialog
{
	DECLARE_DYNAMIC(CDlgGetEventRecord)

public:
	CDlgGetEventRecord(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgGetEventRecord();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog() ;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton m_bntStart;
	CButton m_bntStop;
	static DWORD WINAPI  ProcGetReports(LPVOID lpv) ;

	WTL::CThread m_thrdGetReport;
	void LogError(CString msg) ;
	CListCtrl m_listvEventRecord;
	CRichEditCtrl m_reErrorLog;
	afx_msg void OnBnClickedButton3();
	void OnReaderOpen() ;
	void OnReaderClose() ; 
	afx_msg void OnBnClickedButton2();
	afx_msg LRESULT OnThreadExit(WPARAM wparam,LPARAM lparam) ;
	void AddNewReport(/*BYTE eventType,*/CString slData,BYTE dir ,BYTE time[]) ;

public:
	CStatic m_staCounter;
	int m_counter;
};
