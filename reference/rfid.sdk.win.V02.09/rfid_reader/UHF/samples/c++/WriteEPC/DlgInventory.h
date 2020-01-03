#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "wtlthread.h"

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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	LRESULT msg_inventory_stopped(WPARAM wp, LPARAM lp) ;
	BOOL OnInitDialog() ;
public:
	CListCtrl m_listTagData;
public:
	CStatic m_staTotal;
	WTL::CThread m_thrdInventory;
	int m_readCount ;

	static DWORD WINAPI proc_inventory(LPVOID lpv);
public:
	CButton m_bntInvenStart;
public:
	CButton m_bntInvenStop;
public:
	CRichEditCtrl m_richedtInvnRes;

	BOOLEAN InventoryOn;
public:
	int tag_inventory(BYTE AIType,DWORD *nTagCount ) ;
	void LogInventoryResult(CString msg) ;
public:
	afx_msg void OnBnClickedButton2();
	void handle_tag_report(DWORD AIPType, DWORD tagType, DWORD antID, DWORD metaFlags, BYTE* tagData, DWORD datlen, CSTR writeOper, CSTR lockOper) ;
public:
	CEdit m_editTimeout;
	int m_invenTimeout;
};
