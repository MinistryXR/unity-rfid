// WriteEPCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CWriteEPCDlg �Ի���
class CWriteEPCDlg : public CDialog
{
// ����
public:
	CWriteEPCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WRITEEPC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void ShowError(INT err)  ;
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CTabCtrl m_tab;
	CArray<CDialog *> m_tabDlgs;
	int old_page;
};
