#pragma once
#include "afxwin.h"


// CDlgWrite �Ի���

class CDlgWrite : public CDialog
{
	DECLARE_DYNAMIC(CDlgWrite)

public:
	CDlgWrite(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWrite();

// �Ի�������
	enum { IDD = IDD_WRITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
