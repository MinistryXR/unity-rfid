#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CDlgGetReport 对话框

class CDlgGetReport : public CDialog
{
	DECLARE_DYNAMIC(CDlgGetReport)

public:
	CDlgGetReport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgGetReport();

// 对话框数据
	enum { IDD = IDD_DLGGETREPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(); 
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listReports;
public:
	CButton m_bntStart;
public:
	afx_msg void OnBnClickedButton2();
public:
	CButton m_bntStop;
public:
	CButton m_bntClear;
public:
	afx_msg void OnBnClickedButton1();

public:
	afx_msg void OnBnClickedButton3();
	LRESULT OnMsgReportGetted(WPARAM wParam, LPARAM lParam) ;
	LRESULT OnMsgErrorOccur(WPARAM wParam, LPARAM lParam) ;
	LRESULT OnMsgCollectExit(WPARAM wParam, LPARAM lParam) ;
	void addReports(TCHAR uid[],BYTE direction,BYTE time[]);
	CRichEditCtrl m_rchedtErrLog;
	int m_totalGetted;

public:
	CStatic m_staTotal;
};
