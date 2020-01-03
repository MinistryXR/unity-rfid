#pragma once
#include "afxcmn.h"


// CDlgSysInfor 对话框

class CDlgSysInfor : public CDialog
{
	DECLARE_DYNAMIC(CDlgSysInfor)

public:
	CDlgSysInfor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSysInfor();

// 对话框数据
	enum { IDD = IDD_SYSINFO };

	virtual BOOL OnInitDialog(); 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listSysInfo;
	UINT8 m_uid[8] ;
	UINT8 m_dsfid;
	UINT8 m_afi ;
	DWORD m_blocksize ;
	DWORD m_totalnum;
	UINT8 m_icref ;

};
