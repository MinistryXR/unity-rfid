#pragma once
#include "resource.h"
#include "afxwin.h"
#include "hexeditctrl.h"

// CDlgTagTiHFIStandard 对话框

class CDlgTagTiHFIStandard : public CDialog
{
	DECLARE_DYNAMIC(CDlgTagTiHFIStandard)

public:
	CDlgTagTiHFIStandard(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTagTiHFIStandard();

// 对话框数据
	enum { IDD = IDD_TAG_TIHFI_STANDARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(); 
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbbModes;
public:
	CComboBox m_cbbBlkNum;
public:
	CComboBox m_cbbUIDs;
public:
	afx_msg void OnBnClickedButton13();
public:

	CHexEdit m_editBD ;
public:
	afx_msg void OnBnClickedButton8();
public:
	afx_msg void OnBnClickedButton9();
public:
	afx_msg void OnBnClickedButton1();
public:


	void ShowError(INT err)  ;
	RFID_TAG_HANDLE hp ; 
public:
	CButton m_bntConnect;
public:
	CButton m_bntDisconnect;
public:
	CButton m_bntReadSingle;
public:
	CButton m_bntWriteSingle;
public:
	CButton m_bntLockBlock;
public:
	afx_msg void OnBnClickedButton14();
public:
	afx_msg void OnBnClickedButton2();
public:
	CComboBox m_cbbNumBlocks;
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton4();
public:
	afx_msg void OnCbnSelchangeNumblocks();


public:
	afx_msg void OnCbnSelchangeNumblocks2();
	void OnSelchangeNumblocks() ;
};
