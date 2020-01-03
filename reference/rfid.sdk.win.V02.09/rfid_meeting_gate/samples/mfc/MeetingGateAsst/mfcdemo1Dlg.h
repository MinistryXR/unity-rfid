// mfcdemo1Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CRdrInfo
{
public:
	CRdrInfo(){}
	virtual ~CRdrInfo() {}
public:
	CString m_name ;
	CString m_productType;
	CString m_Catalog;
	DWORD m_CommTypeSupported;
public:
	CRdrInfo &operator=(const CRdrInfo &Src)
	{
		m_name = Src.m_name ;
		m_productType =Src.m_productType ;
		m_Catalog = Src.m_Catalog ;
		m_CommTypeSupported = Src.m_CommTypeSupported ;
		return *this;
	}
};


// Cmfcdemo1Dlg 对话框
class Cmfcdemo1Dlg : public CDialog
{
// 构造
public:
	Cmfcdemo1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCDEMO1_DIALOG };

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
	//afx_msg void OnCbnSelchangeCmmtype();
	//afx_msg void OnCbnSelchangeDevtype();
	DECLARE_MESSAGE_MAP()

private:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo11();
	afx_msg void OnCbnSelchangeCmmtype();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	
	void ShowError(int iret) ;

private:
	CButton m_bntGetDevInfor;
	CArray<CRdrInfo> m_readerList;
	CTabCtrl m_tab;
	CButton m_bntOpen;
	CButton m_bntClose;
	CComboBox m_cbbCOMMType;
	CComboBox m_cbbComNames;
	CComboBox m_cbbCommunicateType;
	CComboBox m_cbbComBaud;
	CComboBox m_cbbComFrame;
	CIPAddressCtrl m_ipAddr;
	CArray<CDialog *> m_tabDlgs;
	int old_page;
};
