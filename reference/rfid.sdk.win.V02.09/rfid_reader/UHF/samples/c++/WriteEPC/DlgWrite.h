#pragma once
#include "afxwin.h"


// CDlgWrite 对话框

class CDlgWrite : public CDialog
{
	DECLARE_DYNAMIC(CDlgWrite)

public:
	CDlgWrite(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWrite();

// 对话框数据
	enum { IDD = IDD_WRITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbEPCs;
public:
	CComboBox m_cmbStartWord;
public:
	CComboBox m_cmbWordCnt;
public:
	CEdit m_edtAccessPwd;
public:
	afx_msg void OnBnClickedButton1();
	BOOL  OnInitDialog() ;
	BOOLEAN EPC_Write(BYTE oldEPC[],int oldEPCLen, int wordStart, int wordCnt, BYTE data[],int dlen,DWORD accessPwd) ;
public:
	CEdit m_editEPCToWrite;
};
