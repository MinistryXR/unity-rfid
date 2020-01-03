// demo_m24rl64Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"



// Cdemo_m24rl64Dlg 对话框
class Cdemo_m24rl64Dlg : public CDialog
{
	// 构造
public:
	Cdemo_m24rl64Dlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_DEMO_M24RL64_DIALOG };

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
	afx_msg void OnDestroy() ;
	void OnClose() ;
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	void ShowError(INT err)  ;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CTabCtrl m_tab;
	CArray<CDialog *> m_tabDlgs;
	int old_page;
	CComboBox m_cbbAccessAnts;
	CButton m_bntSetAccessAnt;
};
