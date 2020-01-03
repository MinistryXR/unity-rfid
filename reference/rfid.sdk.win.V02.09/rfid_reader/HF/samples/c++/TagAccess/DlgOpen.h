#pragma once

#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
// CDlgOpen 对话框
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

class CDlgOpen : public CDialog
{
	DECLARE_DYNAMIC(CDlgOpen)

public:
	CDlgOpen(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOpen();

// 对话框数据
	enum { IDD = IDD_OPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox cbb_COMs;
	afx_msg void OnBnClickedOk();
	CComboBox m_cbbReaderType;
	afx_msg void OnCbnSelchangeCombo11();
public:
	CComboBox m_cbbUsbOpenType;
public:
	afx_msg void OnCbnSelchangeCombo12();
public:
	CComboBox m_cbbSerialNum;
public:
	CIPAddressCtrl m_ipAddrIP;
public:
	CEdit m_netPort;
public:
	CArray<CRdrInfo> m_readerList;
	CComboBox m_cbbCommunicationType;
	afx_msg void OnCbnSelchangeCombo14();
	CComboBox cbb_baud;
	CComboBox cbb_frame;
public:
	afx_msg void OnBnClickedCancel();
};
