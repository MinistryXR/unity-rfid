// RS485SampleDlg.h : 头文件
//

#pragma once
#include "rfidlib.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "wtlthread.h"

typedef err_t (RFIDLIB_API *READER_CLOSE_API)(RFID_READER_HANDLE hr) ; 


// CRS485SampleDlg 对话框
class CRS485SampleDlg : public CDialog
{
// 构造
public:
	CRS485SampleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RS485SAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose() ;
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT msg_inventory_stopped(WPARAM wp, LPARAM lp) ;
	DECLARE_MESSAGE_MAP()

public:
	RFID_READER_HANDLE m_hr;
	CArray<RFID_READER_HANDLE> m_hRS485 ;
	CArray<DWORD> m_busAddr;
	READER_CLOSE_API reader_close_api ;
	afx_msg void OnBnClickedButton3();
	CListCtrl m_listTagData;
	CRichEditCtrl m_richedtInvnRes;
	CButton m_bntInvenStart;
	CButton m_bntInvenStop;
	WTL::CThread m_thrdInventory;
	WTL::CThread m_thrdStop;
	static DWORD WINAPI proc_inventory(LPVOID lpv) ;
	afx_msg void OnBnClickedButton4();
	static DWORD WINAPI proc_stop_inventory(LPVOID lpv) ;
	void AddNewTag(DWORD busAddr,UINT32 apl_tid,UINT32 picc_tid,UINT32 ant_id,UINT8 dsfid,UINT8 *uid) ;
	BOOLEAN InventoryOn;
	RFID_READER_HANDLE m_curReader;

	void LogInventoryResult(CString msg) ;

	afx_msg void OnBnClickedButton6();
};
