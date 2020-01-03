// DlgTotal.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgTotal.h"


// CDlgTotal 对话框

IMPLEMENT_DYNAMIC(CDlgTotal, CDialog)

CDlgTotal::CDlgTotal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTotal::IDD, pParent)
{

}

CDlgTotal::~CDlgTotal()
{
}

void CDlgTotal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTotal, CDialog)
END_MESSAGE_MAP()


// CDlgTotal 消息处理程序
BOOL CDlgTotal::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE

}