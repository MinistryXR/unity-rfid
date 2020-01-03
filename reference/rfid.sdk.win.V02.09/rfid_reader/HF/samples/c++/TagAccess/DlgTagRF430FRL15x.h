#pragma once
#include "resource.h"
#include "afxwin.h"

// CDlgTagRF430FRL15x 对话框

class CDlgTagRF430FRL15x : public CDialog
{
	DECLARE_DYNAMIC(CDlgTagRF430FRL15x)

public:
	CDlgTagRF430FRL15x(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTagRF430FRL15x();

// 对话框数据
	enum { IDD = IDD_TAG_RF430FRL15XH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	virtual BOOL OnInitDialog();
	CComboBox m_cbbUIDs;
private:
	CComboBox m_cbbModes;
	CComboBox m_cbbBlkAddr;
	CComboBox m_cbbBlkNum;
	RFID_TAG_HANDLE hp ;
public:
	void CDlgTagRF430FRL15x::ShowError(INT err) ;
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonReadblks();
private:
	CButton m_check_ssb;
public:
	afx_msg void OnBnClickedButtonReadblk();
	afx_msg void OnBnClickedButtonWriteblk();
	afx_msg void OnBnClickedButtonGettaginfor();
	afx_msg void OnBnClickedButtonWriteblks();
};
