#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "hexeditctrl.h"
#include "rfidlib.h"

// CDlgTagTihfiPlus 对话框

class CDlgTagTihfiPlus : public CDialog
{
	DECLARE_DYNAMIC(CDlgTagTihfiPlus)

public:
	CDlgTagTihfiPlus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTagTihfiPlus();

// 对话框数据
	enum { IDD = IDD_TAG_TIHFI_PLUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(); 
	DECLARE_MESSAGE_MAP()
public:
	RFID_TAG_HANDLE hp ;
	CComboBox m_cbbModes;
	CComboBox m_cbbUIDs;
	CComboBox m_cbbBlkNum;
	CComboBox m_cbbNumBlocks;
	CEdit m_edtDSFID;
	CEdit m_edtAFI;
	CButton m_bntConnectTag;
	CButton m_bntDisconnTag;
	CButton m_bntGetTagSys;
	CButton m_bntRSB;
	CButton m_bntWSB;
	CButton m_bntRMB;
	CButton m_bntRSSB;
	CButton m_bntLockBlk;
	CButton m_bntWriteDSFID;
	CButton m_bntLockDSFID;
	CButton m_bntWriteAFI;
	CButton m_bntLockAFI;

	CHexEdit m_editBD;

	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeNumblocks();
	afx_msg void OnCbnSelchangeBlkno();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	void ShowError(INT err) ;
public:
	afx_msg void OnBnClickedButton12();
public:
	afx_msg void OnBnClickedButton15();
	void OnBlockAddrSelChange() ;
};
