// LSGateMFCDemoDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CLSGateMFCDemoDlg 对话框
class CLSGateMFCDemoDlg : public CDialog
{
// 构造
public:
	CLSGateMFCDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LSGATEMFCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CArray<CDialog *> m_tabDlgs;
public:
	CTabCtrl m_tab;
	CIPAddressCtrl m_IPAddr;
	CButton m_bntOpen;
	CButton m_bntClose;
	CButton m_bntGetDevInfo;
	afx_msg void OnBnClickedButton1();
	int old_page;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void OnStopGetEvent() ;
	void OnStartGetEvent() ;
};
