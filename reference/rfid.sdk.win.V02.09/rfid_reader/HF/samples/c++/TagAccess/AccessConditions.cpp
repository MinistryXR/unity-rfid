// AccessConditions.cpp : 实现文件
//

#include "stdafx.h"
#include "AccessConditions.h"


// CAccessConditions 对话框

IMPLEMENT_DYNAMIC(CAccessConditions, CDialog)

CAccessConditions::CAccessConditions(CWnd* pParent /*=NULL*/)
	: CDialog(CAccessConditions::IDD, pParent)
{

}

CAccessConditions::~CAccessConditions()
{
}

void CAccessConditions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMBBLOCK0, m_accessBlk0);
	DDX_Control(pDX, IDC_CMBBLOCK1, m_accessBlk1);
	DDX_Control(pDX, IDC_CMBBLOCK2, m_accessBlk2);
	DDX_Control(pDX, IDC_CMBBLOCK3, m_accessBlk3);
	DDX_Control(pDX, IDC_EDITKEYA, m_REdtKeyA);
	DDX_Control(pDX, IDC_EDITKEYB, m_REdtKeyB);
}


BEGIN_MESSAGE_MAP(CAccessConditions, CDialog)
	ON_BN_CLICKED(IDOK, &CAccessConditions::OnBnClickedOk)
END_MESSAGE_MAP()


// CAccessConditions 消息处理程序

BOOL CAccessConditions::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i=0;i<8;i++)
	{
		CString str;
		str.Format(_T("%d"),i);
		m_accessBlk0.AddString(str);
		m_accessBlk1.AddString(str);
		m_accessBlk2.AddString(str);
		m_accessBlk3.AddString(str);
	}
    m_accessBlk0.SetCurSel(0);
	m_accessBlk1.SetCurSel(0);
	m_accessBlk2.SetCurSel(0);
	m_accessBlk3.SetCurSel(0);

	BYTE buffer[16] ;
	m_REdtKeyA.SetOptions(FALSE,TRUE ,FALSE,FALSE) ;
	m_REdtKeyA.m_bpr = 6;
	memset(buffer,0xff,sizeof(buffer)) ;
	m_REdtKeyA.SetData(buffer,6) ;
	m_REdtKeyA.m_sa =0 ;

	m_REdtKeyB.SetOptions(FALSE,TRUE ,FALSE,FALSE) ;
	m_REdtKeyB.m_bpr = 6;
	m_REdtKeyB.SetData(buffer,6) ;
	m_REdtKeyB.m_sa =0 ;

	m_REdtKeyA.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAccessConditions::ComputingAcessBuff(BYTE *block)
{
	//memcpy(block,blkData,16);
	blkData = block;
}
void CAccessConditions::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE blk0AccType;
	BYTE blk1AccType;
	BYTE blk2AccType;
	BYTE trailerAccType;
	int idx;
	idx = m_accessBlk0.GetCurSel();
	if (idx>=0)
	{
		blk0AccType = idx;
	}

	idx = m_accessBlk1.GetCurSel();
	if (idx>=0)
	{
		blk1AccType = idx;
	}

	idx = m_accessBlk2.GetCurSel();
	if (idx>=0)
	{
		blk2AccType = idx;
	}

	idx = m_accessBlk3.GetCurSel();
	if (idx>=0)
	{
		trailerAccType = idx;
	}

	//BYTE buff[16];
	int nret;
	BYTE buffA[6];
	BYTE buffB[6];
	BYTE formattedAccCondi[4];
	m_REdtKeyA.GetData(buffA,0,6);
	m_REdtKeyB.GetData(buffB,0,6);
	nret = MFCL_CreateAccessCondition(blk0AccType,blk1AccType,blk2AccType,trailerAccType,formattedAccCondi);
	if (nret!=NO_ERR)
	{
		AfxMessageBox(_T("操作失败"));
		return;
	}
	memcpy(blkData,buffA,6);
	memcpy(blkData+6,formattedAccCondi,4);
	memcpy(blkData+10,buffB,6);

	OnOK();
}
