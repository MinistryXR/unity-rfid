// DlgTotal.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgTotal.h"


// CDlgTotal �Ի���

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


// CDlgTotal ��Ϣ�������
BOOL CDlgTotal::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE

}