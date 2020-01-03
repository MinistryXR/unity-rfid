#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDlgConfig 对话框

class CDlgConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgConfig)

public:
	CDlgConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgConfig();

// 对话框数据
	enum { IDD = IDD_DLGCFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog() ;
	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_cfgIPAddr;
public:
	CIPAddressCtrl m_cfgIPMask;
public:
	CIPAddressCtrl m_cfgIPGW;
public:
	CComboBox m_cbbCfgRole;
public:
	CComboBox m_cbbCfgSyncNumber;
public:
	CComboBox m_cbbCfgWiegand;
public:
	CComboBox m_cbbDirectionReverSta;
public:
	CComboBox m_cbbRFPower;
public:
	CComboBox m_cbbAFISta;
public:
	CEdit m_edtAFIVal;
public:
	CComboBox m_cbbQuickDisSta;
public:
	CComboBox m_cbbIrFuncSta;
public:
	CComboBox m_cbbAntSwitch;
public:
	CComboBox m_cbbAntCountUsage;
public:
	CComboBox m_cbbDaiDaKa;

public:
	CComboBox m_cbbDDKRestrictTime;
public:
	afx_msg void OnBnClickedButton14();
public:
	CButton m_bntReadCfg;
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton8();
public:
	afx_msg void OnBnClickedButton9();
public:
	afx_msg void OnBnClickedButton4();
public:
	afx_msg void OnBnClickedButton7();
public:
	afx_msg void OnBnClickedButton13();
public:
	afx_msg void OnBnClickedButton6();
public:
	afx_msg void OnBnClickedButton5();
public:
	afx_msg void OnBnClickedButton12();
public:
	afx_msg void OnBnClickedButton11();
public:
	afx_msg void OnBnClickedButton10();
public:
	afx_msg void OnBnClickedButton15();
public:
	CComboBox m_cbbCfgCardFilter;
public:
	afx_msg void OnBnClickedButton16();
public:
	CButton m_bntWrite;

	BOOLEAN firstRead;
public:
	CRichEditCtrl m_richEdtResult;

	void LogCfgMsg(CString msg)  ;
public:
	CButton m_bntCfgReset;
	CComboBox m_cbbStartBlk; 
	CComboBox m_cbbBlkNum ;
	CComboBox m_cbbEnableReadBlk ;
};
