#pragma once
#include "afxcmn.h"


// CDlgSysInfor �Ի���

class CDlgSysInfor : public CDialog
{
	DECLARE_DYNAMIC(CDlgSysInfor)

public:
	CDlgSysInfor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSysInfor();

// �Ի�������
	enum { IDD = IDD_SYSINFO };

	virtual BOOL OnInitDialog(); 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
