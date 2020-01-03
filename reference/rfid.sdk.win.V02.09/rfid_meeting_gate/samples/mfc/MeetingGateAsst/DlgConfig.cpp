// DlgConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcdemo1.h"
#include "DlgConfig.h"
#include "gfunctions.h"
#include "rfidlib_reader.h"


// CDlgConfig 对话框

IMPLEMENT_DYNAMIC(CDlgConfig, CDialog)

CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfig::IDD, pParent)
{

}

CDlgConfig::~CDlgConfig()
{
}

void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_cfgIPAddr);
	DDX_Control(pDX, IDC_IPADDRESS3, m_cfgIPMask);
	DDX_Control(pDX, IDC_IPADDRESS2, m_cfgIPGW);
	DDX_Control(pDX, IDC_COMBO14, m_cbbCfgRole);
	DDX_Control(pDX, IDC_COMBO15, m_cbbCfgSyncNumber);
	DDX_Control(pDX, IDC_COMBO16, m_cbbCfgWiegand);
	DDX_Control(pDX, IDC_COMBO17, m_cbbDirectionReverSta);
	DDX_Control(pDX, IDC_COMBO18, m_cbbRFPower);
	DDX_Control(pDX, IDC_COMBO19, m_cbbAFISta);
	DDX_Control(pDX, IDC_EDIT1, m_edtAFIVal);
	DDX_Control(pDX, IDC_COMBO20, m_cbbQuickDisSta);
	DDX_Control(pDX, IDC_COMBO21, m_cbbIrFuncSta);
	DDX_Control(pDX, IDC_COMBO22, m_cbbAntSwitch);
	DDX_Control(pDX, IDC_COMBO23, m_cbbAntCountUsage);
	DDX_Control(pDX, IDC_COMBO24, m_cbbDaiDaKa);

	DDX_Control(pDX, IDC_COMBO25, m_cbbDDKRestrictTime);
	DDX_Control(pDX, IDC_BUTTON14, m_bntReadCfg);
	DDX_Control(pDX, IDC_COMBO26, m_cbbCfgCardFilter);
	DDX_Control(pDX, IDC_BUTTON16, m_bntWrite);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richEdtResult);
	DDX_Control(pDX, IDC_BUTTON15, m_bntCfgReset);
	DDX_Control(pDX,IDC_COMBO27 ,m_cbbStartBlk) ;
	DDX_Control(pDX, IDC_COMBO28 , m_cbbBlkNum) ;
	DDX_Control(pDX,IDC_COMBO29,m_cbbEnableReadBlk) ;
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialog)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlgConfig::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgConfig::OnBnClickedButton3)
	
	ON_BN_CLICKED(IDC_BUTTON15, &CDlgConfig::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CDlgConfig::OnBnClickedButton16)
END_MESSAGE_MAP()


// CDlgConfig 消息处理程序

BOOL CDlgConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cfgIPAddr.SetAddress(192,168,0,222) ;
	m_cfgIPMask.SetAddress(255,255,255,0) ;
	m_cfgIPGW.SetAddress(192,168,0,1) ;

	m_cbbCfgRole.AddString(_T("Master")) ;
	m_cbbCfgRole.AddString(_T("Host#1")) ;
	m_cbbCfgRole.AddString(_T("Host#2")) ;
	m_cbbCfgRole.AddString(_T("Host#3")) ;
	m_cbbCfgRole.AddString(_T("Host#4")) ;
	m_cbbCfgRole.AddString(_T("Host#5")) ;
	m_cbbCfgRole.AddString(_T("Host#6")) ;
	m_cbbCfgRole.AddString(_T("Host#7")) ;
	m_cbbCfgRole.AddString(_T("Host#8")) ;
	m_cbbCfgRole.SetCurSel(0) ;

	m_cbbCfgSyncNumber.AddString(_T("1")) ;
	m_cbbCfgSyncNumber.AddString(_T("2")) ;
	m_cbbCfgSyncNumber.AddString(_T("3")) ;
	m_cbbCfgSyncNumber.AddString(_T("4")) ;
	m_cbbCfgSyncNumber.AddString(_T("5")) ;
	m_cbbCfgSyncNumber.AddString(_T("6")) ;
	m_cbbCfgSyncNumber.AddString(_T("7")) ;
	m_cbbCfgSyncNumber.AddString(_T("8")) ;
	m_cbbCfgSyncNumber.AddString(_T("9")) ;
	m_cbbCfgSyncNumber.SetCurSel(0) ;

	m_cbbCfgWiegand.AddString(_T("Disable"));
	m_cbbCfgWiegand.AddString(_T("Wiegand-26")) ;
	m_cbbCfgWiegand.AddString(_T("Wiegand-34")) ;
	m_cbbCfgWiegand.AddString(_T("Wiegand-66")) ;
	m_cbbCfgWiegand.SetCurSel(0) ;

	m_cbbDirectionReverSta.AddString(_T("Disable")) ;
	m_cbbDirectionReverSta.AddString(_T("Enable")) ;
	m_cbbDirectionReverSta.SetCurSel(0) ;

	m_cbbRFPower.AddString(_T("0.5W")) ;
	m_cbbRFPower.AddString(_T("1.0W")) ;
	m_cbbRFPower.AddString(_T("1.5W")) ;
	m_cbbRFPower.AddString(_T("2.0W")) ;
	m_cbbRFPower.AddString(_T("2.5W")) ;
	m_cbbRFPower.AddString(_T("3.0W")) ;
	m_cbbRFPower.AddString(_T("3.5W")) ;
	m_cbbRFPower.AddString(_T("4.0W")) ;
	m_cbbRFPower.AddString(_T("4.5W")) ;
	m_cbbRFPower.AddString(_T("5.0W")) ;
	m_cbbRFPower.AddString(_T("5.5W")) ;
	m_cbbRFPower.AddString(_T("6.0W")) ;
	m_cbbRFPower.AddString(_T("6.5W")) ;
	m_cbbRFPower.AddString(_T("7.0W")) ;
	m_cbbRFPower.AddString(_T("7.5W")) ;
	m_cbbRFPower.AddString(_T("8.0W")) ;
	m_cbbRFPower.AddString(_T("8.5W")) ;
	m_cbbRFPower.AddString(_T("9.0W")) ;
	m_cbbRFPower.AddString(_T("9.5W")) ;
	m_cbbRFPower.AddString(_T("10W")) ;
	m_cbbRFPower.SetCurSel(0) ;

	m_cbbAFISta.AddString(_T("Disable")) ;
	m_cbbAFISta.AddString(_T("Enable")) ;
	m_cbbAFISta.SetCurSel(0) ;

	m_edtAFIVal.SetWindowText(_T("00")) ;

	m_cbbQuickDisSta.AddString(_T("Disable")) ;
	m_cbbQuickDisSta.AddString(_T("Enable")) ;
	m_cbbQuickDisSta.SetCurSel(0) ;

	m_cbbIrFuncSta.AddString(_T("Disable")) ;
	m_cbbIrFuncSta.AddString(_T("Enable")) ;
	m_cbbIrFuncSta.SetCurSel(0) ;


	m_cbbAntCountUsage.AddString(_T("2 Antenna Interface")) ;
	m_cbbAntCountUsage.AddString(_T("3 Antenna Interface")) ;
	m_cbbAntCountUsage.SetCurSel(0) ;


	m_cbbAntSwitch.AddString(_T("Dual antenna port")) ;
	m_cbbAntSwitch.AddString(_T("Single antenna port")) ;
	m_cbbAntSwitch.AddString(_T("Dual and single antenna port")) ;
	m_cbbAntSwitch.SetCurSel(0) ;
	
	m_cbbDaiDaKa.AddString(_T("Disable")) ;
	m_cbbDaiDaKa.AddString(_T("Enable")) ;
	m_cbbDaiDaKa.SetCurSel(0) ;

	m_cbbCfgCardFilter.AddString(_T("No")) ;
	m_cbbCfgCardFilter.AddString(_T("Yes")) ;
	m_cbbCfgCardFilter.SetCurSel(1) ;

	for(int i =0 ;i<=255;i++) {
		CString str1 ;
		str1.Format(_T("%d"),i) ;
		m_cbbDDKRestrictTime.AddString(str1) ;
	}
	m_cbbDDKRestrictTime.SetCurSel(0) ;

	m_bntWrite.EnableWindow(FALSE) ;
	m_bntReadCfg.EnableWindow(FALSE) ;
	m_bntCfgReset.EnableWindow(FALSE) ;

	for(int i=0 ;i<255;i++) {
		CString s1;
		s1.Format(_T("%d") ,i ) ;
		m_cbbStartBlk.AddString(s1) ;
	}
	m_cbbStartBlk.SetCurSel(0) ;
	m_cbbBlkNum.AddString(_T("1")) ;
	m_cbbBlkNum.AddString(_T("2")) ;
	m_cbbBlkNum.AddString(_T("3")) ;
	m_cbbBlkNum.AddString(_T("4")) ;
	m_cbbBlkNum.SetCurSel(0) ;

	m_cbbEnableReadBlk.AddString(_T("No")) ;
	m_cbbEnableReadBlk.AddString(_T("Yes")) ;
	m_cbbEnableReadBlk.SetCurSel( 0) ;

	firstRead = FALSE ;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CDlgConfig::LogCfgMsg(CString msg) 
{
	m_richEdtResult.SetWindowText(msg) ;
}
void CDlgConfig::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bntReadCfg.EnableWindow(FALSE) ;
	int iret;
	BYTE cfgblock[8] ;
	DWORD m_size = 8;
	LogCfgMsg(_T("Reading....")) ;
	iret  = RDR_ConfigBlockRead(hr,0,cfgblock,m_size)  ;
	if(iret != 0) {
		LogCfgMsg(_T("failed in reading block 0")) ;
		goto exit_func;
	}
	m_cfgIPAddr.SetAddress(cfgblock[0],cfgblock[1],cfgblock[2],cfgblock[3]) ;
	m_cfgIPMask.SetAddress(cfgblock[4] ,cfgblock[5] ,cfgblock[6],cfgblock[7]) ;
	iret  = RDR_ConfigBlockRead(hr,1,cfgblock,m_size)  ;
	if(iret != 0) {
		LogCfgMsg(_T("failed in reading block 1")) ;
		goto exit_func;
	}
	m_cfgIPGW.SetAddress(cfgblock[0],cfgblock[1],cfgblock[2],cfgblock[3]) ;
	iret  = RDR_ConfigBlockRead(hr,2,cfgblock,m_size)  ;
	if(iret != 0) {
		LogCfgMsg(_T("failed in reading block 2")) ;
		goto exit_func;
	}
	//data block
	if(cfgblock[0] >=0 && cfgblock[0]<=1){
		m_cbbEnableReadBlk.SetCurSel(cfgblock[0]) ;
	}
	m_cbbStartBlk.SetCurSel(cfgblock[1]) ;
	if(cfgblock[2] >=1 && cfgblock[2] <=4) {
		m_cbbBlkNum.SetCurSel(cfgblock[2] -1) ;
	}

	//AFI 
	m_cbbAFISta.SetCurSel(-1) ;
	if(cfgblock[3] >= 0  && cfgblock[3] <= 1) {
		m_cbbAFISta.SetCurSel(cfgblock[3]) ;
	}
	TCHAR afivalHex[16];
	memset(afivalHex , 0 ,sizeof(afivalHex));
	BytesToHexStr(&cfgblock[4] ,1 ,afivalHex) ;
	m_edtAFIVal.SetWindowText(afivalHex) ;

	iret  = RDR_ConfigBlockRead(hr,3,cfgblock,m_size)  ;
	if(iret != 0) {
		LogCfgMsg(_T("failed in reading block 3")) ;
		goto exit_func;
	}
	m_cbbIrFuncSta.SetCurSel(-1) ;
	if(cfgblock[0] >= 0 && cfgblock[0] <=1){
		m_cbbIrFuncSta.SetCurSel(cfgblock[0]) ;
	}
	m_cbbCfgCardFilter.SetCurSel(-1) ;
	if(cfgblock[1] >= 0 && cfgblock[1] <= 1) {
		m_cbbCfgCardFilter.SetCurSel(cfgblock[1]) ;
	}
	m_cbbDirectionReverSta.SetCurSel(-1) ;
	if(cfgblock[2] >= 0 && cfgblock[2] <= 1) {
		m_cbbDirectionReverSta.SetCurSel(cfgblock[2]) ;
	}
	m_cbbQuickDisSta.SetCurSel(-1) ;
	if(cfgblock[3] >= 0 && cfgblock[3] <= 1) {
		m_cbbQuickDisSta.SetCurSel(cfgblock[3]) ;
	}	

	m_cbbDaiDaKa.SetCurSel(-1) ;
	if(cfgblock[4] >= 0 && cfgblock[4] <= 1) {
		m_cbbDaiDaKa.SetCurSel(cfgblock[4]) ;
	}
	m_cbbDDKRestrictTime.SetCurSel(cfgblock[5]) ;

	iret  = RDR_ConfigBlockRead(hr,4,cfgblock,m_size)  ;
	if(iret != 0) {
		LogCfgMsg(_T("failed in reading block 4")) ;
		goto exit_func;
	}
	m_cbbCfgWiegand.SetCurSel(-1) ;
	if(cfgblock[0] >= 0 && cfgblock[0] <=3) {
		m_cbbCfgWiegand.SetCurSel(cfgblock[0]) ;
	}

	iret  = RDR_ConfigBlockRead(hr,5,cfgblock,m_size)  ;
	if(iret != 0) {
		LogCfgMsg(_T("failed in reading block 5")) ;
		goto exit_func;
	}
	m_cbbCfgRole.SetCurSel(cfgblock[0]  -1) ;
	m_cbbCfgSyncNumber.SetCurSel(cfgblock[1] -1) ;
	m_cbbAntCountUsage.SetCurSel(-1) ;
	if(cfgblock[3] >=2 && cfgblock[3] <=3) {
		m_cbbAntCountUsage.SetCurSel(cfgblock[3] -2) ;
	}
	m_cbbAntSwitch.SetCurSel(-1) ;
	if(cfgblock[4] >= 0 && cfgblock[4] <= 2) {
		m_cbbAntSwitch.SetCurSel( cfgblock[4] ) ;
	}

	iret  = RDR_ConfigBlockRead(hr,6,cfgblock,m_size)  ;
	if(iret != 0) {
		LogCfgMsg(_T("failed in reading block 6")) ;
		goto exit_func;
	}
	m_cbbRFPower.SetCurSel(cfgblock[0] -1);
	if(!firstRead){
		m_bntWrite.EnableWindow(TRUE) ;
		firstRead = TRUE ;
	}
	LogCfgMsg(_T("Reading Configuration success！")) ;
exit_func:
	m_bntReadCfg.EnableWindow(TRUE) ;
}

void CDlgConfig::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	
}

void CDlgConfig::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	BYTE cfgblock[8];
	int idx;

	memset(cfgblock,0,sizeof(cfgblock));	
	idx =  m_cbbCfgRole.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select role of synchronization"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[0] =idx + 1;
	idx = m_cbbCfgSyncNumber.GetCurSel() ;
	if(idx == -1 ) {
		MessageBox(_T("Please select number of synchronization"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[1] = idx + 1;

	iret =  RDR_ConfigBlockWrite(hr,5,cfgblock,8,0x03)  ;
	if(iret != 0) {
		MessageBox(_T("Failed in write block 5."),_T(""),MB_OK) ;
		goto exit_func;
	}
	MessageBox(_T("Success"),_T(""),MB_OK) ;
exit_func:
	return;
}

void CDlgConfig::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	int idx;
	BYTE cfgblock[8];
	memset(cfgblock,0,sizeof(cfgblock));
	idx = m_cbbCfgWiegand.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the type of wiegand!"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[0]= idx ;
	iret =  RDR_ConfigBlockWrite(hr,4,cfgblock,8,0x01)  ;
	if(iret != 0) {
		MessageBox(_T("Failed in write block 5."),_T(""),MB_OK) ;
		goto exit_func;
	}
	MessageBox(_T("Success"),_T(""),MB_OK) ;
exit_func:
	return;
}

void CDlgConfig::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	int idx;
	BYTE cfgblock[8];
	memset(cfgblock,0,sizeof(cfgblock));
	idx = m_cbbDirectionReverSta.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please choose the direction status!"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[2]= idx ;
	iret =  RDR_ConfigBlockWrite(hr,3,cfgblock,8,0x04)  ;
	if(iret != 0) {
		MessageBox(_T("Failed in write block 3."),_T(""),MB_OK) ;
		goto exit_func;
	}
	MessageBox(_T("Success"),_T(""),MB_OK) ;
exit_func:
	return;
}

void CDlgConfig::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx;
	BYTE cfgblock[8] ;
	int iret;
	memset(cfgblock,0,sizeof(cfgblock));
	idx = m_cbbRFPower.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please choose the RF power!"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[0]  = idx + 1;
	iret =  RDR_ConfigBlockWrite(hr,6,cfgblock,8,0x01)  ;
	if(iret != 0) {
		MessageBox(_T("Failed in write block 6."),_T(""),MB_OK) ;
		goto exit_func;
	}
	MessageBox(_T("Success"),_T(""),MB_OK) ;
exit_func:
	return ;
}

void CDlgConfig::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码

}

void CDlgConfig::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx;
	int iret;
	BYTE cfgblock[8]  ;
	memset(cfgblock,0,sizeof(cfgblock));
	idx  =m_cbbQuickDisSta.GetCurSel()   ;
	if(idx == -1) {
		MessageBox(_T("Please choose the status"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[3]=idx ;
	iret =  RDR_ConfigBlockWrite(hr,3,cfgblock,8,0x08)  ;
	if(iret != 0) {
		MessageBox(_T("Failed in write block 3."),_T(""),MB_OK) ;
		goto exit_func;
	}
	MessageBox(_T("Success"),_T(""),MB_OK) ;
exit_func:
	return;
}

void CDlgConfig::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx;
	int iret;
	BYTE cfgblock[8] ;

	MessageBox(_T("Success"),_T(""),MB_OK) ;
exit_func:
	return;
}

void CDlgConfig::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx;
	int iret;
	BYTE cfgblock[8] ;

	memset(cfgblock,0,sizeof(cfgblock));
	idx = m_cbbAntSwitch.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please choose the mode"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[4] = idx ;
	iret =  RDR_ConfigBlockWrite(hr,5,cfgblock,8,0x10)  ;
	if(iret != 0) {
		MessageBox(_T("Failed in write block 5."),_T(""),MB_OK) ;
		goto exit_func;
	}
	MessageBox(_T("Success"),_T(""),MB_OK) ;
exit_func:
	return;
}

void CDlgConfig::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx;
	int iret;
	BYTE cfgblock[8] ;

	memset(cfgblock,0,sizeof(cfgblock));
	idx = m_cbbAntCountUsage.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the number of antenna interface"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[3] =idx+ 2;
	iret =  RDR_ConfigBlockWrite(hr,5,cfgblock,8,0x08)  ;
	if(iret != 0) {
		MessageBox(_T("Failed in write block 5."),_T(""),MB_OK) ;
		goto exit_func;
	}
	MessageBox(_T("Success"),_T(""),MB_OK) ;	
exit_func:
	return;
}

void CDlgConfig::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	int idx;
	int iret;
	BYTE cfgblock[8] ;

	memset(cfgblock,0,sizeof(cfgblock));

	MessageBox(_T("Success"),_T(""),MB_OK) ;	
exit_func:
	return ;
}

void CDlgConfig::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret; 
	if(MessageBox(_T("Sure to restore the factory settings？"),_T("warning"),MB_YESNO) == IDNO) {
		return;
	}
	LogCfgMsg(_T("Recovering....")) ;
	iret =RDR_LoadFactoryDefault(hr) ;
	if(iret != 0) {
		LogCfgMsg(_T("Load failed!")) ;
		return ;
	}
	LogCfgMsg(_T("Success")) ;
}

void CDlgConfig::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	int iret;
	int idx;
	BYTE cfgblock[8];
	LogCfgMsg(_T("Writing....")) ;
	/* 第0块*/
	BYTE ip1,ip2,ip3,ip4;
	memset(cfgblock,0,sizeof(cfgblock));
	m_cfgIPAddr.GetAddress(ip1,ip2,ip3,ip4) ;
	cfgblock[0] = ip1 ;
	cfgblock[1] = ip2 ;
	cfgblock[2] = ip3;
	cfgblock[3] = ip4 ;
	m_cfgIPMask.GetAddress(ip1,ip2,ip3,ip4) ;
	cfgblock[4] = ip1 ;
	cfgblock[5] = ip2 ;
	cfgblock[6] = ip3 ;
	cfgblock[7] = ip4;
	
	iret =RDR_ConfigBlockWrite(hr,0,cfgblock,8,0xff)  ;
	if(iret != 0) {
		LogCfgMsg(_T("Failed in write block 0.")) ;
		goto exit_func;
	}
	/* 第1块*/
	memset(cfgblock,0,sizeof(cfgblock));
	m_cfgIPGW.GetAddress(ip1,ip2,ip3,ip4) ;
	cfgblock[0] = ip1 ;
	cfgblock[1] = ip2 ;
	cfgblock[2] = ip3;
	cfgblock[3] = ip4 ;
	iret =RDR_ConfigBlockWrite(hr,1,cfgblock,8,0x0f)  ;
	if(iret != 0) {
		LogCfgMsg(_T("Failed in write block 1.")) ;
		goto exit_func;
	}
	/* 第2块*/
	memset(cfgblock,0,sizeof(cfgblock));
	//data block
	if(m_cbbEnableReadBlk.GetCurSel() != -1)cfgblock[0] =m_cbbEnableReadBlk.GetCurSel() ;
	if(m_cbbStartBlk.GetCurSel() != -1 ) cfgblock[1] =m_cbbStartBlk.GetCurSel()  ;
	if(m_cbbBlkNum.GetCurSel()!= -1)cfgblock[2] =  m_cbbBlkNum.GetCurSel() + 1;
	idx = m_cbbAFISta.GetCurSel() ;
	if(idx  == -1) {
		MessageBox(_T("Please select the state!"),_T(""),MB_OK) ;
		goto exit_func;
	}
	
	BYTE afival = 0 ;
	cfgblock[3] = idx; 
	TCHAR afiValHex[3] ;
	memset(afiValHex , 0 ,sizeof(afiValHex));
	m_edtAFIVal.GetWindowText(afiValHex ,sizeof(afiValHex) / sizeof(TCHAR)) ;
	HexStrToBytes(afiValHex,&afival,NULL) ;
	
	cfgblock[4] =afival ;
	iret =  RDR_ConfigBlockWrite(hr,2,cfgblock,8,0x1f)  ;
	if(iret != 0) {
		LogCfgMsg(_T("Failed in write block 2")) ;
		goto exit_func;
	}
	/* 第3块*/
	memset(cfgblock,0,sizeof(cfgblock));
	idx =m_cbbIrFuncSta.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the state"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[0] = idx; 
	idx = m_cbbCfgCardFilter.GetCurSel() ;
	if(idx == -1 ) {
		MessageBox(_T("Please select the state"),_T(""),MB_OK) ;
		goto exit_func;	

	}
	cfgblock[1] = idx ; 

	idx = m_cbbDirectionReverSta.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the state"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[2]= idx ;

	idx  =m_cbbQuickDisSta.GetCurSel()   ;
	if(idx == -1) {
		MessageBox(_T("Please select the state"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[3]=idx ;

	iret =  RDR_ConfigBlockWrite(hr,3,cfgblock,8,0x03)  ;
	if(iret != 0) {
		LogCfgMsg(_T("Failed in write block 3" )) ;
		goto exit_func;
	}


	idx = m_cbbDaiDaKa.GetCurSel() ;
	if(idx == -1 ) {
		MessageBox(_T("Please select the state"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[4] = idx ; 
	cfgblock[5] = m_cbbDDKRestrictTime.GetCurSel() ;


	iret =  RDR_ConfigBlockWrite(hr,3,cfgblock,8,0x3f)  ;
	if(iret != 0) {
		LogCfgMsg(_T("Failed in write block 3")) ;
		goto exit_func;
	}
	/* 第4块 */
	memset(cfgblock,0,sizeof(cfgblock));
	idx = m_cbbCfgWiegand.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the type of wiegand"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[0]= idx ;
	iret =  RDR_ConfigBlockWrite(hr,4,cfgblock,8,0x01)  ;
	if(iret != 0) {
		LogCfgMsg(_T("Failed in write block 5" )) ;
		goto exit_func;
	}

	/*第5块*/
	memset(cfgblock,0,sizeof(cfgblock));	
	idx =  m_cbbCfgRole.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the role!"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[0] =idx + 1;
	idx = m_cbbCfgSyncNumber.GetCurSel() ;
	if(idx == -1 ) {
		MessageBox(_T("Please select number of synchronizations!"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[1] = idx + 1;

	idx = m_cbbAntSwitch.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the  switching mode"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[4] = idx ;

	idx = m_cbbAntCountUsage.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the number of antenna interface"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[3] =idx+ 2;
	iret =  RDR_ConfigBlockWrite(hr,5,cfgblock,8,0x1f)  ;
	if(iret != 0) {
		LogCfgMsg(_T("Failed in write block 5" )) ;
		goto exit_func;
	}

	/*第6块*/
	memset(cfgblock,0,sizeof(cfgblock));
	idx = m_cbbRFPower.GetCurSel() ;
	if(idx == -1) {
		MessageBox(_T("Please select the RF power"),_T(""),MB_OK) ;
		goto exit_func;
	}
	cfgblock[0]  = idx + 1;
	iret =  RDR_ConfigBlockWrite(hr,6,cfgblock,8,0x01)  ;
	if(iret != 0) {
		LogCfgMsg(_T("Failed in write block 6" )) ;
		goto exit_func;
	}
	LogCfgMsg(_T("Write Configuration success" )) ;

exit_func:
	return ;
}
