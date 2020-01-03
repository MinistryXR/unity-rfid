#pragma once
#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"
#include "hexeditctrl.h"
#include "AccessConditions.h"



// CDlgTagMFCLS50 对话框

class CDlgTagMFCLS50 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTagMFCLS50)

public:
	CDlgTagMFCLS50(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTagMFCLS50();

// 对话框数据
	enum { IDD = IDD_TAG_MFCL_S50 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(); 
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbbUIDs;
	CComboBox m_cbbKeyType;
	afx_msg void OnBnClickedButton13();
	void ShowError(INT err)  ;
	CButton m_bntConnect;
	CButton m_bntDisconnect;
	CButton m_bntAuthenticate;
	CButton m_bntReadBlock;
	CButton m_bntWriteBlock;
	CButton m_bntIncrement;
	CButton m_bntDecrement;
	CButton m_bntRestore;
	CButton m_bntFormatValueBlock;
	afx_msg void OnBnClickedButton14();

	RFID_TAG_HANDLE hp ;
	CComboBox m_blkAddr;
	CHexEdit m_editDB;
	afx_msg void OnBnClickedButton1();
	CHexEdit m_REdtKey;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton2();
	CEdit m_edtValue;
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton4();

public:
	afx_msg void OnCbnSelchangeUids3();
};
