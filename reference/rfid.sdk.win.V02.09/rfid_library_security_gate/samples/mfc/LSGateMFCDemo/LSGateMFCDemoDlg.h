// LSGateMFCDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CLSGateMFCDemoDlg �Ի���
class CLSGateMFCDemoDlg : public CDialog
{
// ����
public:
	CLSGateMFCDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LSGATEMFCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CArray<CDialog *> m_tabDlgs;
public:
	CTabCtrl m_tab;
	CIPAddressCtrl m_IPAddr;
	CButton m_bntOpen;
	CButton m_bntClose;
	CButton m_bntGetDevInfo;
	afx_msg void OnBnClickedButton1();
	int old_page;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void OnStopGetEvent() ;
	void OnStartGetEvent() ;
};
