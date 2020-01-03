#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "rfidlib_aip_iso14443a.h"
#include "hexeditctrl.h"


// CAccessConditions 对话框

class CAccessConditions : public CDialog
{
	DECLARE_DYNAMIC(CAccessConditions)

public:
	CAccessConditions(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccessConditions();

// 对话框数据
	enum { IDD = IDD_ACCESS_CONDITIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void ComputingAcessBuff(BYTE *block);

private:
	CComboBox m_accessBlk0;
	CComboBox m_accessBlk1;
	CComboBox m_accessBlk2;
	CComboBox m_accessBlk3;
	CHexEdit m_REdtKeyA;
	CHexEdit m_REdtKeyB;
	BYTE *blkData;
	virtual BOOL OnInitDialog();
	//CEdit MTE;
	afx_msg void OnBnClickedOk();
};
