#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "hexeditctrl.h"

// CDlgTagIcodesli 对话框

class CDlgTagIcodesli : public CDialog
{
	DECLARE_DYNAMIC(CDlgTagIcodesli)

public:
	CDlgTagIcodesli(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTagIcodesli();

// 对话框数据
	enum { IDD = IDD_TAG_ICODESLI };

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
	CButton m_bntEanbleEAS;
	CButton m_bntDisableEAS;
	CButton m_bntLockEAS;
	CButton m_bntVerityEAS;
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnCbnSelchangeNumblocks();
	afx_msg void OnCbnSelchangeBlkno();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton15();
	CRichEditCtrl m_edtEASData;
public:
	void ShowError(INT err) ;
public:
	afx_msg void OnBnClickedButton17();
public:
	afx_msg void OnBnClickedButton18();
public:
	CButton m_bntWMB;
public:
	CButton m_bntLMB;

	void OnBlockAddrSelChange();
};
