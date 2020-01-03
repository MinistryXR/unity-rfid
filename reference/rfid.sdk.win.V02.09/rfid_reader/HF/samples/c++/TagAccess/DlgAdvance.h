#pragma once


// CDlgAdvance �Ի���
#include "resource.h"
#include "afxwin.h"
class CDlgAdvance : public CDialog
{
	DECLARE_DYNAMIC(CDlgAdvance)

public:
	CDlgAdvance(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAdvance();

// �Ի�������
	enum { IDD = IDD_ADVANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkOnlyNewTag;
	CButton m_chkAFIMatch;
	CEdit m_edtAFIval;
	BOOLEAN m_only_new_tag;
	UINT m_slottype ;
	BOOLEAN m_AFI_match ;
	BYTE m_AFI_val;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedOk();
	CCheckListBox m_cklAntennas; 
	CCheckListBox m_cklAirProtocl;
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCancel();
};
