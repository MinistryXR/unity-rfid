#pragma once
#include "afxwin.h"
#include "hexeditctrl.h"
#include "afxcmn.h"

// CTagMb89r118c 对话框

class CTagMb89r118c : public CDialog
{
	DECLARE_DYNAMIC(CTagMb89r118c)

public:
	CTagMb89r118c(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTagMb89r118c();

// 对话框数据
	enum { IDD = IDD_TAG_MB89R118C };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog(); 
	DECLARE_MESSAGE_MAP()
public:
	RFID_TAG_HANDLE hp ;
public:
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
private:
	CButton m_bntLockDSFID;
public:
	CButton m_bntWriteAFI;
	CButton m_bntLockAFI;
	CButton m_bntEanbleEAS;

	CButton m_bntVerityEAS;
	CHexEdit m_editBD;
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeNumblocks();
	afx_msg void OnCbnSelchangeBlkno();
	CButton m_bntWriteMultiBlks;
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton15();
	CComboBox m_cbbEASFlag;
	CRichEditCtrl m_edtEASData;
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedCheck2();


	BOOL use_fast_cmd; 
	void ShowError(INT err) ;
public:
	afx_msg void OnBnClickedButton24();

	void OnBlockAddrChanged() ;
};
