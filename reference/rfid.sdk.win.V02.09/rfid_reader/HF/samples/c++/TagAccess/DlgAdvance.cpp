// DlgAdvance.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgAdvance.h"
#include "gfunctions.h"


// CDlgAdvance �Ի���

IMPLEMENT_DYNAMIC(CDlgAdvance, CDialog)

CDlgAdvance::CDlgAdvance(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAdvance::IDD, pParent)
{

}

CDlgAdvance::~CDlgAdvance()
{
}

void CDlgAdvance::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_chkOnlyNewTag);
	DDX_Control(pDX, IDC_CHECK2, m_chkAFIMatch);
	DDX_Control(pDX, IDC_EDIT1, m_edtAFIval);
	DDX_Control(pDX, IDC_LIST1,m_cklAntennas);
	DDX_Control(pDX,IDC_LIST2,m_cklAirProtocl) ;

}


BEGIN_MESSAGE_MAP(CDlgAdvance, CDialog)
	ON_BN_CLICKED(IDC_CHECK2, &CDlgAdvance::OnBnClickedCheck2)
	ON_BN_CLICKED(IDOK, &CDlgAdvance::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK3, &CDlgAdvance::OnBnClickedCheck3)
	ON_BN_CLICKED(IDCANCEL, &CDlgAdvance::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgAdvance ��Ϣ�������
BOOL CDlgAdvance::OnInitDialog()
{
	int i; 
	CDialog::OnInitDialog();

	m_chkOnlyNewTag.SetCheck(m_only_new_tag) ;
	m_chkAFIMatch.SetCheck(m_AFI_match) ;
	m_edtAFIval.EnableWindow(m_AFI_match) ;
	CString s;
	s.Format(_T("%02X") ,m_AFI_val) ;
	m_edtAFIval.SetWindowText(s) ;

	
	for(int i =0 ;i< AntennaIFCountOfReader ;i++) {
		CString strAnt;
		strAnt.Format(_T("Antenna#%d"),i+1) ;
		m_cklAntennas.AddString(strAnt) ;
	}
	if(AntennaIFCountOfReader<=1 ) {
		m_cklAntennas.EnableWindow(FALSE) ;
	}
	else {
		m_cklAntennas.EnableWindow(TRUE ) ;
	}
	for(i=0;i<AntennaIFCountOfReader;i++) {
		if((AntennaSelected  & (0x01 << i)) > 0) { 
			m_cklAntennas.SetCheck(i,TRUE) ;
		}
	}
	if(m_cklAirProtocl.GetCount() == 0){
		for( i=0;i<m_supportedAIP.GetCount() ;i++) {
			m_cklAirProtocl.AddString(m_supportedAIP[i].m_name) ;
			if(m_supportedAIP[i].m_en){
				m_cklAirProtocl.SetCheck(i,TRUE ) ;
			}
			else {
				m_cklAirProtocl.SetCheck(i,FALSE ) ;
			}
		}
	}
	if(m_cklAirProtocl.GetCount() ==1) {
		m_cklAirProtocl.EnableWindow(FALSE) ;
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
void CDlgAdvance::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_chkAFIMatch.GetCheck()) {
		m_edtAFIval.EnableWindow(TRUE) ;
	}
	else {
		m_edtAFIval.EnableWindow(FALSE) ;
	}
}

void CDlgAdvance::OnBnClickedOk()
{
	int i;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_only_new_tag = m_chkOnlyNewTag.GetCheck() ;
	m_AFI_match =m_chkAFIMatch.GetCheck() ;
	TCHAR afival[16];
	memset(afival,0,sizeof(afival));
	m_edtAFIval.GetWindowText(afival,sizeof(afival)/sizeof(TCHAR));
	BYTE afi[20];
	HexStrToBytes(afival,afi,NULL) ;
	m_AFI_val = afi[0];

	AntennaSelected =0;
	for(i=0;i<m_cklAntennas.GetCount();i++) {
		if(m_cklAntennas.GetCheck(i) ) {
			AntennaSelected |= (0x01 << i ) ;
		}
	}
	for(i=0;i<m_cklAirProtocl.GetCount();i++){
		m_supportedAIP[i].m_en =m_cklAirProtocl.GetCheck(i) ;
	}

	OnOK();
}

void CDlgAdvance::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgAdvance::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
