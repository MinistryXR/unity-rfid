// DlgSysInfor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "demo_m24rl64.h"
#include "DlgSysInfor.h"
#include "gfunctions.h"


// CDlgSysInfor �Ի���

IMPLEMENT_DYNAMIC(CDlgSysInfor, CDialog)

CDlgSysInfor::CDlgSysInfor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSysInfor::IDD, pParent)
{

}

CDlgSysInfor::~CDlgSysInfor()
{
}

void CDlgSysInfor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listSysInfo);
}


BEGIN_MESSAGE_MAP(CDlgSysInfor, CDialog)
END_MESSAGE_MAP()


// CDlgSysInfor ��Ϣ�������

BOOL CDlgSysInfor::OnInitDialog()
{
	CDialog::OnInitDialog();
	DWORD dwStyle = m_listSysInfo.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    //dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
    m_listSysInfo.SetExtendedStyle(dwStyle); //������չ���
	m_listSysInfo.InsertColumn( 0, _T("Name"), LVCFMT_LEFT, 100 );//������
	m_listSysInfo.InsertColumn( 1, _T("Value"), LVCFMT_LEFT, 150 );//������
	m_listSysInfo.InsertItem(0,_T("UID:")) ;
	m_listSysInfo.InsertItem(1,_T("DSFID:")) ;
	m_listSysInfo.InsertItem(2,_T("AFI:")) ;
	m_listSysInfo.InsertItem(3,_T("Block Size:")) ;
	m_listSysInfo.InsertItem(4,_T("Total blocks:")) ;
	m_listSysInfo.InsertItem(5,_T("IC Reference:")) ;	
	TCHAR stmp[64] ;
	memset(stmp,0,sizeof(stmp));
	BytesToHexStr(m_uid,8,stmp)  ;
	m_listSysInfo.SetItemText(0,1,stmp) ;
	memset(stmp,0,sizeof(stmp));
	BytesToHexStr(&m_dsfid,1,stmp) ;
	_tcscat(stmp,_T("H")) ;
	m_listSysInfo.SetItemText(1,1,stmp) ;
	memset(stmp,0,sizeof(stmp)) ;
	BytesToHexStr(&m_afi,1,stmp) ;
	_tcscat(stmp,_T("H")) ;
	m_listSysInfo.SetItemText(2,1,stmp) ;
	memset(stmp,0,sizeof(stmp)) ;
	_itot(m_blocksize,stmp,10) ;
	m_listSysInfo.SetItemText(3,1,stmp) ;
	memset(stmp,0,sizeof(stmp)) ;
	_itot(m_totalnum,stmp,10) ;
	m_listSysInfo.SetItemText(4,1,stmp) ;
	memset(stmp,0,sizeof(stmp)) ;
	BytesToHexStr(&m_icref,1,stmp) ;
	_tcscat(stmp,_T("H")) ;
	m_listSysInfo.SetItemText(5,1,stmp) ;
	return TRUE;
}
