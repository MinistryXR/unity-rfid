#pragma once
#include "afxwin.h"
#include "hexeditctrl.h"
#include "afxcmn.h"

#include "rfidlib.h"


// CDlgTagM24 对话框

class CDlgTagM24 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTagM24)

public:
	CDlgTagM24(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTagM24();

// 对话框数据
	enum { IDD = IDD_TAG_M24RL64 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbbModes;
	CComboBox m_cbbUIDs;
	afx_msg void OnBnClickedButton13();
	RFID_TAG_HANDLE hp ;
	CButton m_bntConnectTag;
	CButton m_bntDisconnTag;
	CButton m_bntGetTagSys;
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton16();
	CComboBox m_cbbBlkNum;
	CComboBox m_cbbNumBlocks;
	CComboBox m_cbbSectNum;
	CComboBox m_cbbAccessType;
	CComboBox m_cbbPassNum;
	CComboBox m_cbbPwdNum1;
	CEdit m_edtNewPwd;
	CEdit m_edtOldPwd;
	CComboBox m_cbbPwdNum2;
	CEdit m_edtAuthPwd;
	CEdit m_edtDSFID;
	CEdit m_edtAFI;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton10();

	CHexEdit m_edtBlockData;
	afx_msg void OnCbnSelchangeBlkno();
	afx_msg void OnCbnSelchangeNumblocks();
	afx_msg void OnBnClickedCheck1();
	CButton m_bntRSB;
	CButton m_bntWSB;
	CButton m_bntRMB;
	CButton m_bntRSSB;
	CButton m_bntLockSect;
	CButton m_bntUpdatePwd;
	CButton m_bntAuthPwd;
	CButton m_bntWriteDSFID;
	CButton m_bntLockDSFID;
	CButton m_bntWriteAFI;
	CButton m_bntLockAFI;

	void ShowError(INT err)  ;
public:
	afx_msg void OnBnClickedButton25();
public:
	afx_msg void OnBnClickedButton6();
public:
	CButton m_bntWriteMultBlocks;
};
