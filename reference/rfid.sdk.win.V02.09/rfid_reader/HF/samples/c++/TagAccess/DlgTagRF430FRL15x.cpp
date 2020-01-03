// DlgTagRF430FRL15x.cpp : 实现文件
//

#include "stdafx.h"
#include <stdlib.h>
#include "DlgTagRF430FRL15x.h"
#include "gfunctions.h"
#include "rfidlib_reader.h"
#include "rfidlib_aip_iso15693.h"
#include "DlgSysInfor.h"

// CDlgTagRF430FRL15x 对话框

IMPLEMENT_DYNAMIC(CDlgTagRF430FRL15x, CDialog)

CDlgTagRF430FRL15x::CDlgTagRF430FRL15x(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTagRF430FRL15x::IDD, pParent)
{
	hp = NULL;
}

CDlgTagRF430FRL15x::~CDlgTagRF430FRL15x()
{
}

void CDlgTagRF430FRL15x::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UIDS, m_cbbUIDs);
	DDX_Control(pDX, IDC_ADDRMODE, m_cbbModes);
	DDX_Control(pDX, IDC_BLOCKADDR, m_cbbBlkAddr);
	DDX_Control(pDX, IDC_BLOCKNUM, m_cbbBlkNum);
	DDX_Control(pDX, IDC_CHECK_SECURITY, m_check_ssb);
}


BEGIN_MESSAGE_MAP(CDlgTagRF430FRL15x, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CDlgTagRF430FRL15x::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CDlgTagRF430FRL15x::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_READBLKS, &CDlgTagRF430FRL15x::OnBnClickedButtonReadblks)
	ON_BN_CLICKED(IDC_BUTTON_READBLK, &CDlgTagRF430FRL15x::OnBnClickedButtonReadblk)
	ON_BN_CLICKED(IDC_BUTTON_WRITEBLK, &CDlgTagRF430FRL15x::OnBnClickedButtonWriteblk)
	ON_BN_CLICKED(IDC_BUTTON_GETTAGINFOR, &CDlgTagRF430FRL15x::OnBnClickedButtonGettaginfor)
	ON_BN_CLICKED(IDC_BUTTON_WRITEBLKS, &CDlgTagRF430FRL15x::OnBnClickedButtonWriteblks)
END_MESSAGE_MAP()


// CDlgTagRF430FRL15x 消息处理程序


BOOL CDlgTagRF430FRL15x::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cbbModes.AddString(_T("none address")) ;
	m_cbbModes.AddString(_T("address")) ;
	m_cbbModes.SetCurSel(1) ;

	for (int j=0;j<256;j++)
	{
		CString s;
		s.Format(_T("%d"),j);
		m_cbbBlkAddr.AddString(s);
	}
	m_cbbBlkAddr.SetCurSel(0);

	for (int j=1;j<=4;j++)
	{
		CString s;
		s.Format(_T("%d"),j);
		m_cbbBlkNum.AddString(s);
	}
	m_cbbBlkNum.SetCurSel(0);

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GETTAGINFOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_BLKDATA)->EnableWindow(FALSE);
	m_cbbBlkAddr.EnableWindow(FALSE);
	m_cbbBlkNum.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_READBLK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WRITEBLK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOCKBLK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_READBLKS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WRITEBLKS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOCKBLKS)->EnableWindow(FALSE);


	return TRUE;
}


void CDlgTagRF430FRL15x::OnBnClickedButtonConnect()
{
	INT32 addrmode;
	addrmode = m_cbbModes.GetCurSel() ;
	if(addrmode <0) {
		MessageBox(_T("select address mode! ")) ;
		return ;
	}
	TCHAR uid[32] ;
	memset(uid,0,sizeof(uid));
	m_cbbUIDs.GetWindowText(uid,sizeof(uid)/sizeof(TCHAR)) ;
	if(addrmode != 0) {
		if(uid[0] =='\0') {
			MessageBox(_T("input uid! ")) ;
			return ;			
		}
	}	
	err_t iret;
	BYTE u[8] ;
	HexStrToBytes(uid,u,NULL) ;

	//Set tag type
	DWORD tagType = RFID_ISO15693_PICC_RF430FR12XH_ID ;
	iret = ISO15693_Connect(hr,tagType,addrmode,u,&hp);
	if(iret != NO_ERR) 
	{
		goto fail;
	}

	m_cbbModes.EnableWindow(FALSE);
	m_cbbUIDs.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_GETTAGINFOR)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_BLKDATA)->EnableWindow(TRUE);
	m_cbbBlkAddr.EnableWindow(TRUE);
	m_cbbBlkNum.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_READBLK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_WRITEBLK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOCKBLK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_READBLKS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_WRITEBLKS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LOCKBLKS)->EnableWindow(TRUE);
fail:
	return;
}


void CDlgTagRF430FRL15x::OnBnClickedButtonDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	RDR_TagDisconnect(hr,hp) ;
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_GETTAGINFOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_BLKDATA)->EnableWindow(FALSE);
	m_cbbBlkAddr.EnableWindow(FALSE);
	m_cbbBlkNum.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_READBLK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WRITEBLK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOCKBLK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_READBLKS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_WRITEBLKS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LOCKBLKS)->EnableWindow(FALSE);
	m_cbbUIDs.EnableWindow(TRUE);
	m_cbbModes.EnableWindow(TRUE);
}


void CDlgTagRF430FRL15x::ShowError(INT err) 
{
	CString str ;
	str.Format(_T("error code:%d"),err) ;
	if(err== -17) {
		err_t rdrerr;
		rdrerr= RDR_GetReaderLastReturnError(hr) ;
		str.Format(_T("error code:%d, %04x"),err,rdrerr) ;
	}
	MessageBox(str) ;
}



void CDlgTagRF430FRL15x::OnBnClickedButtonReadblks()
{
	DWORD blockno ;
	DWORD numOfBlocksToRead;
	DWORD numOfBlocksRead =0;
	BOOLEAN read_ssb ;
	CString strNo;
	CString strNum;
	read_ssb = m_check_ssb.GetCheck()?TRUE:FALSE ;
	
	m_cbbBlkAddr.GetWindowText(strNo);
	blockno = _tstoi(strNo);

	m_cbbBlkNum.GetWindowText(strNum);
	numOfBlocksToRead = _tstoi(strNum) ;
	err_t iret;
	BYTE buffer[64*9] ;
	TCHAR strBuf[128*9];
	DWORD nSize;
	nSize = sizeof(buffer) ;
	DWORD bytesRead = 0 ;
	memset(strBuf,0x00,sizeof(strBuf));
	iret =ISO15693_ReadMultiBlocks(hr,hp,read_ssb,blockno,numOfBlocksToRead,&numOfBlocksRead,buffer,nSize,&bytesRead) ;
	if(iret != NO_ERR) 
	{
		ShowError(iret) ;
		return;
	}
	BytesToHexStr(buffer,bytesRead,strBuf) ;
	GetDlgItem(IDC_EDIT_BLKDATA)->SetWindowText(strBuf);
	MessageBox(_T("ok"),_T(""),MB_OK) ;
	
}

void CDlgTagRF430FRL15x::OnBnClickedButtonReadblk()
{
	DWORD blockno ;
	DWORD numOfBlocksToRead;
	DWORD numOfBlocksRead =0;
	BOOLEAN read_ssb ;
	CString strNo;
	read_ssb = m_check_ssb.GetCheck()?TRUE:FALSE ;
	m_cbbBlkAddr.GetWindowText(strNo);
	blockno = _tstoi(strNo);
	err_t iret;
	BYTE buffer[9] ;
	TCHAR strBuf[20];
	DWORD nSize;
	nSize = sizeof(buffer) ;
	DWORD bytesRead = 0 ;
	memset(strBuf,0x00,sizeof(strBuf));
	iret = ISO15693_ReadSingleBlock( hr , hp,read_ssb,blockno,buffer,nSize,&bytesRead)  ;
	if(iret != NO_ERR) 
	{
		ShowError(iret) ;
		return;
	}
	BytesToHexStr(buffer,bytesRead,strBuf) ;
	GetDlgItem(IDC_EDIT_BLKDATA)->SetWindowText(strBuf);
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}

void CDlgTagRF430FRL15x::OnBnClickedButtonWriteblk()
{
	DWORD blockno ;
	DWORD numOfBlocksToRead;
	DWORD numOfBlocksRead =0;
	BOOLEAN read_ssb ;
	CString strNo;
	CString strBuffer;
	DWORD bytesToWrite=0;
	BYTE newBlkData[8] ={0x00};
	int byLen=0;
	m_cbbBlkAddr.GetWindowText(strNo);
	blockno = _tstoi(strNo);
	GetDlgItem(IDC_EDIT_BLKDATA)->GetWindowText(strBuffer);
	if(!IsHexStr(strBuffer)&&(strBuffer.GetLength()==8||strBuffer.GetLength()==16))
	{
		MessageBox(_T("The data is error."),_T(""),MB_OK) ;
		return;
	}
	HexStrToBytes(strBuffer,newBlkData,&byLen);
	bytesToWrite = byLen;
	err_t iret=ISO15693_WriteSingleBlock(hr,hp,blockno,newBlkData,bytesToWrite);
	if(iret == NO_ERR) 
	{
		MessageBox(_T("ok"),_T(""),MB_OK) ;
	}
	else
	{
		ShowError(iret) ;
	}

}

void CDlgTagRF430FRL15x::OnBnClickedButtonGettaginfor()
{
	err_t iret;
	BYTE uid[8] ;
	BYTE dsfid;
	BYTE afi ;
	DWORD blk_size;
	DWORD total_num ;
	BYTE ic_ref ;
	iret =  ISO15693_GetSystemInfo(hr,hp,uid,&dsfid,&afi,&blk_size,&total_num,&ic_ref ) ;
	if(iret != NO_ERR) {
		//MessageBox("get system infor fail","",MB_OK) ;
		ShowError(iret) ;
		return  ;
	}
	CDlgSysInfor dlg ;
	memcpy(dlg.m_uid,uid,8) ;
	dlg.m_dsfid = dsfid ;
	dlg.m_afi = afi ;
	dlg.m_blocksize = blk_size;
	dlg.m_totalnum = total_num ;
	dlg.m_icref =  ic_ref ;
	dlg.DoModal() ;	
}

void CDlgTagRF430FRL15x::OnBnClickedButtonWriteblks()
{
	int iret;
	DWORD blockno ;
	DWORD numOfBlocksToWrite;
	BOOLEAN read_ssb ;
	read_ssb = TRUE;
	INT32 idx;
	CString strBlkNo,strBlkNum;
	CString strBlkData;
	m_cbbBlkAddr.GetWindowText(strBlkNo);
	m_cbbBlkNum.GetWindowText(strBlkNum);
	GetDlgItem(IDC_EDIT_BLKDATA)->GetWindowText(strBlkData);
	blockno = _tstoi(strBlkNo);
	if(blockno < 0) {
		MessageBox(_T("Select block no"),_T(""),MB_OK) ;
		return ;
	}
	

	numOfBlocksToWrite = _tstoi(strBlkNum) ;
	if(numOfBlocksToWrite< 0)
	{
		MessageBox(_T("select number of blocks"),_T(""),MB_OK) ;
		return ;
	}

	if(!IsHexStr(strBlkData))
	{
		MessageBox(_T("The data is error."),_T(""),MB_OK) ;
		return ;
	}

	BYTE *blocksdata = new BYTE[strBlkData.GetLength()/2];
	int byLen = 0;
	HexStrToBytes(strBlkData,blocksdata,&byLen);
	if(numOfBlocksToWrite*8!=byLen&&numOfBlocksToWrite*4!=byLen)
	{
		MessageBox(_T("The data is error."),_T(""),MB_OK) ;
		return ;
	}


	iret = ISO15693_WriteMultipleBlocks(hr,hp,blockno,numOfBlocksToWrite,blocksdata,byLen) ;
	if(iret != NO_ERR) 
	{
		if(blocksdata)
		{
			delete[] blocksdata;
		}
		ShowError(iret) ;
		return ;
	}
	if(blocksdata) 
	{
		delete[] blocksdata;
	}
	MessageBox(_T("ok"),_T(""),MB_OK) ;
}
