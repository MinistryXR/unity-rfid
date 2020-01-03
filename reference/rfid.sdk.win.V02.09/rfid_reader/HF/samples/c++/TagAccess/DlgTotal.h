#pragma once

#include "resource.h"
// CDlgTotal 对话框

class CDlgTotal : public CDialog
{
	DECLARE_DYNAMIC(CDlgTotal)

public:
	CDlgTotal(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTotal();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
