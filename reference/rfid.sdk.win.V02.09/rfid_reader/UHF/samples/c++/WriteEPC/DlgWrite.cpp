// DlgWrite.cpp : 实现文件
//

#include "stdafx.h"
#include "WriteEPC.h"
#include "DlgWrite.h"
#include "gfunctions.h"
#include "rfidlib_reader.h"
#include "rfidlib_aip_iso18000p6c.h"


// CDlgWrite 对话框

IMPLEMENT_DYNAMIC(CDlgWrite, CDialog)

CDlgWrite::CDlgWrite(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWrite::IDD, pParent)
{

}

CDlgWrite::~CDlgWrite()
{
}

void CDlgWrite::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cmbEPCs);
	DDX_Control(pDX, IDC_COMBO2, m_cmbStartWord);
	DDX_Control(pDX, IDC_COMBO3, m_cmbWordCnt);
	DDX_Control(pDX, IDC_EDIT2, m_edtAccessPwd);
	DDX_Control(pDX, IDC_EDIT1, m_editEPCToWrite);
}


BEGIN_MESSAGE_MAP(CDlgWrite, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgWrite::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgWrite 消息处理程序

BOOL CDlgWrite::OnInitDialog()
{
	int i ;
	CDialog::OnInitDialog();
	for(i =0 ;i<12;i++ ) {
		CSTR s ;
		s.Format(_T("%d") ,i+2) ;
		m_cmbStartWord.AddString(s) ;
		s.Format(_T("%d"),i+1) ;
		m_cmbWordCnt.AddString(s) ;
	}
	m_cmbStartWord.SetCurSel(0) ;
	m_cmbWordCnt.SetCurSel(0) ;
	m_edtAccessPwd.SetWindowText(_T("00000000")) ;
	m_editEPCToWrite.SetWindowText(_T("0000")) ;
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgWrite::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR epcStr[64] ;
	memset(epcStr,0,sizeof(epcStr)) ;
	m_cmbEPCs.GetWindowText(epcStr ,sizeof(epcStr) / sizeof(TCHAR)) ;
	if(m_cmbEPCs.GetWindowTextLength() == 0) {
		MessageBox(_T("Input EPC code ,please"),_T(""),MB_OK) ;
		return ;
	}
	if(m_cmbStartWord.GetCurSel() == -1) {
		MessageBox(_T("Select start word,please"),_T(""),MB_OK) ;
		return ;
	}
	if(m_cmbWordCnt.GetCurSel() ==-1) {
		MessageBox(_T("Select word count,please"),_T("") ,MB_OK) ;
		return ;
	}

	TCHAR dataStr[64] ;
	memset(dataStr,0,sizeof(dataStr)) ;
	m_editEPCToWrite.GetWindowText(dataStr,sizeof(dataStr)/sizeof(TCHAR)) ;
	if(m_editEPCToWrite.GetWindowTextLength() == 0) {
		MessageBox(_T("Input new EPC data ,please"),_T(""),MB_OK) ;
		return ;
	}


	BYTE epcByBuf[64] ;
	int epcByLen;
	HexStrToBytes(epcStr,epcByBuf,&epcByLen) ;

	BYTE dataByBuf[64] ;
	int dataByLen ;
	HexStrToBytes(dataStr, dataByBuf ,&dataByLen) ; 

	if(m_edtAccessPwd.GetWindowTextLength() != 8) {
		MessageBox(_T("Wrong access password"),_T(""),MB_OK) ;
		return ;
	}
	TCHAR strAccsPwd[64] ;
	memset(strAccsPwd,0,sizeof(strAccsPwd)) ;
	m_edtAccessPwd.GetWindowText(strAccsPwd ,sizeof(strAccsPwd) / sizeof(TCHAR)) ;
	BYTE accsPwdByBuf[4] ;
	int accsPwdByLen;
	HexStrToBytes(strAccsPwd, accsPwdByBuf ,&accsPwdByLen) ; 

    DWORD accessPwd = (accsPwdByBuf[0] | (accsPwdByBuf[1] << 8 & 0xff00) | (accsPwdByBuf[2] << 16 & 0xff0000) | (accsPwdByBuf[3] << 24 & 0xff000000));


    int WordCnt;
    int WordPointer;
    BOOLEAN iret;

	WordCnt = m_cmbWordCnt.GetCurSel()+1;
    WordPointer = m_cmbStartWord.GetCurSel() + 2;
    iret = EPC_Write(epcByBuf,epcByLen,WordPointer,WordCnt,dataByBuf ,dataByLen ,accessPwd );
    if (iret)
    {
        MessageBox(_T("write ok") ,_T(""),MB_OK);
    }
    else
    {
        MessageBox(_T("write fail"),_T(""),MB_OK);
    }
}



BOOLEAN CDlgWrite::EPC_Write(BYTE oldEPC[],int oldEPCLen, int wordStart, int wordCnt, BYTE data[],int dlen,DWORD accessPwd)
{
    int iret;
    BOOLEAN result;
    RFID_DN_HANDLE InvenParamSpecList =NULL;

    result = FALSE;
    /*1. inventory parameters setting */
    InvenParamSpecList = RDR_CreateInvenParamSpecList();
    if (InvenParamSpecList)
    {
        /* set timeout */
        RDR_SetInvenStopTrigger(InvenParamSpecList, INVEN_STOP_TRIGGER_TYPE_TIMEOUT,200, 0);
        /* create ISO18000p6C air protocol inventory parameters */
        RFID_DN_HANDLE AIPIso18000p6c = ISO18000p6C_CreateInvenParam(InvenParamSpecList, 0, 0, ISO18000p6C_S0,ISO18000p6C_TARGET_A, ISO18000p6C_Dynamic_Q);
        if (AIPIso18000p6c)
        {
            //set selection parameters,select total EPC bits
            ISO18000p6C_SetInvenSelectParam(AIPIso18000p6c, ISO18000p6C_SELECT_TARGET_INV_SL, 0x00/* assert SL */,ISO18000p6C_MEM_BANK_EPC, 0, oldEPC,(oldEPCLen * 8), 0);

            // Add Embedded commands
            ISO18000p6C_CreateTAWrite(AIPIso18000p6c,ISO18000p6C_MEM_BANK_EPC, wordStart,wordCnt, data, dlen);
          
            // set access password
            ISO18000p6C_SetInvenAccessPassword(AIPIso18000p6c, accessPwd);
        }

    }
    /*2. inventory tags */
    iret =RDR_TagInventory(hr, AI_TYPE_NEW, 0, NULL, InvenParamSpecList);
    if (iret == 0 || iret == -21)
    {
        RFID_DN_HANDLE TagDataReport;
        TagDataReport = NULL;
        TagDataReport = RDR_GetTagDataReport(hr, RFID_SEEK_FIRST); //first
        if(TagDataReport)
        {
            DWORD aip_id = 0;
            DWORD tag_id = 0;
            DWORD ant_id = 0;
            BYTE tagData[256];
            DWORD nSize = sizeof(tagData);
            DWORD metaFlags = 0;

            iret = ISO18000p6C_ParseTagReport(TagDataReport, &aip_id, &tag_id, &ant_id, &metaFlags, tagData, &nSize);
            if (iret == 0)
            {
                iret = ISO18000p6C_CheckTAWriteResult(TagDataReport);
                if (iret == 0)
                {
                    result = TRUE;
                }
            }
        }
    }
    /*3. destory inventory parameter */
    if (InvenParamSpecList) DNODE_Destroy(InvenParamSpecList);
    return result;


}