#pragma once
#include "afxwin.h"


// CDlgControlCommand �Ի���

class CDlgControlCommand : public CDialog
{
	DECLARE_DYNAMIC(CDlgControlCommand)

public:
	CDlgControlCommand(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgControlCommand();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog() ;
	DECLARE_MESSAGE_MAP()
public:
	CButton m_bntGetFlow;
	CButton m_bntClearFlow;
	CButton m_bntReservedDir;
	afx_msg void OnBnClickedButton1();
	CStatic m_stacInFlow;
	CStatic m_stacOutFlow;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CStatic m_stacSystime;
	CButton m_bntUpdateTime;
	CButton m_bntFetchTime;

	void OnReaderOpen() ;
	void OnReaderClose() ;
	afx_msg void OnBnClickedButton5();
	void ShowError(CString msg,int iret)  ;
};
