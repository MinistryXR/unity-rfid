#pragma once
#include "afxwin.h"
#include "RS485SampleDlg.h"

// CDlgOpen �Ի���
class CRdrInfo
{
public:
	CRdrInfo(){}
	virtual ~CRdrInfo() {}
public:
	CString m_name ;
	CString m_productType;
	CString m_Catalog;
	DWORD m_CommTypeSupported;
public:
	CRdrInfo &operator=(const CRdrInfo &Src)
	{
		m_name = Src.m_name ;
		m_productType =Src.m_productType ;
		m_Catalog = Src.m_Catalog ;
		m_CommTypeSupported = Src.m_CommTypeSupported ;
		return *this;
	}
};

class CDlgOpen : public CDialog
{
	DECLARE_DYNAMIC(CDlgOpen)

public:
	CDlgOpen(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOpen();
// �Ի�������
	enum { IDD = IDD_OPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CRS485SampleDlg *m_pParent;

private:
	afx_msg void OnBnClickedOk();
	CCheckListBox m_listbReaders;
	CComboBox m_cbbCOMs;
	CArray<CRdrInfo> m_readerList;
	CComboBox m_cbbReaderType;
};
