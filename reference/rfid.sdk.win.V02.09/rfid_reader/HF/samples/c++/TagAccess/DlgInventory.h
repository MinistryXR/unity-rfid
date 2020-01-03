#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "wtlthread.h"
#include "DlgTotal.h"

// CDlgInventory 对话框



class CDlgInventory : public CDialog
{
	DECLARE_DYNAMIC(CDlgInventory)

public:
	CDlgInventory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInventory();

// 对话框数据
	enum { IDD = IDD_INVENTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_listTagData;
	WTL::CThread m_thrdInventory;

	afx_msg void OnBnClickedButton1();
	CButton m_bntInvenStart;
	CButton m_bntInvenStop;
	LRESULT msg_inventory_stopped(WPARAM wp, LPARAM lp) ;
	LRESULT OnAsyncReport(WPARAM wp, LPARAM lp)  ;
	static DWORD WINAPI proc_inventory(LPVOID lpv) ;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	/* inventory options */
	BOOL m_only_new_tag;
	BOOL m_AFI_match ;
	BYTE m_AFI_val;
	UINT m_slottype;
	CButton m_bntAdvance;
	CStatic m_staTotal;
	CDlgTotal m_dlgTotal;
	LRESULT OnSize(WPARAM wp, LPARAM lp) ;
	afx_msg void OnBnClickedButton4();
	BOOL m_enAsyncOutput;
public:
	CRichEditCtrl m_richedtInvnRes;

	int m_readCount ;

	void LogInventoryResult(CString msg) ;
public:
	CStatic m_labInvenCounter;
public:
	CButton m_ckbBeep;
};
