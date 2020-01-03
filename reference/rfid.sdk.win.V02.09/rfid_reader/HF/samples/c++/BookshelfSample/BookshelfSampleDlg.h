// BookshelfSampleDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "rfidlib.h"
#include "rfidlib_reader.h"
#include "rfidlib_AIP_ISO15693.h"


class CTag
{
public:
	CString m_uid ;
	INT32 m_counter;
	INT32 m_type ;
	INT32 m_antNo ;
	INT32 m_AIP ; 
public:
	CTag &operator=(const CTag &src ) 
	{
		m_uid = src.m_uid ;
		m_counter= src.m_counter;
		m_type = src.m_type;
		m_antNo = src.m_antNo ;
		m_AIP = src.m_AIP;
		return *this;
	}
} ;




// CBookshelfSampleDlg 对话框
class CBookshelfSampleDlg : public CDialog
{
// 构造
public:
	CBookshelfSampleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BOOKSHELFSAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnBnClickedButtonInventory();
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtonclose();
	static UINT InventoryThrd(void *lp);
	void AddTagToList(DWORD AIPtype,DWORD TagType,DWORD AntId,BYTE uid[],WORD uidlen);
	CCheckListBox m_cklAntennas; 
	CListCtrl m_listTagData;
	CComboBox m_cmb_commType;
	CComboBox m_cmb_comName;
	CComboBox m_cmb_baud;
	CComboBox m_cmb_frame;
	CEdit m_edit_ip;
	CEdit m_edit_port;
	RFID_READER_HANDLE hReader;
	bool b_threadRunFlg;
	CArray<CTag>  m_taglist;
public:
	afx_msg void OnBnClickedButtonStopinventory();
};
