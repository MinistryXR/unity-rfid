#pragma once

#include "resource.h"
// CDlgTotal �Ի���

class CDlgTotal : public CDialog
{
	DECLARE_DYNAMIC(CDlgTotal)

public:
	CDlgTotal(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTotal();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
