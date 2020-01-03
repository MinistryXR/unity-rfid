#pragma once
#include "afxwin.h"


// CDlgControl 对话框

class CDlgControl : public CDialog
{
	DECLARE_DYNAMIC(CDlgControl)

public:
	CDlgControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgControl();

// 对话框数据
	enum { IDD = IDD_DLGCONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog() ;
	DECLARE_MESSAGE_MAP()
public:
	CCheckListBox m_listOutputs;
public:
	CComboBox m_cbbCtrlActiveTime;
public:
	CComboBox m_cbbCtrlFrequence;
public:
	CComboBox m_cbbCtrlDeactiveTime;
public:
	afx_msg void OnBnClickedButton1();
public:
	CButton m_bntCtrlOutput;
};
