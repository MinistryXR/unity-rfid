// DlgInventory.cpp : 实现文件
//

#include "stdafx.h"
#include "WriteEPC.h"
#include "DlgInventory.h"
#include "rfidlib_reader.h"
#include "rfidlib_aip_iso18000p6c.h"
#include "gfunctions.h"

#define WM_INVENOTYR_STOPPED			(WM_USER+ 2)




// CDlgInventory 对话框

IMPLEMENT_DYNAMIC(CDlgInventory, CDialog)

CDlgInventory::CDlgInventory(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInventory::IDD, pParent)
{

}

CDlgInventory::~CDlgInventory()
{
}

void CDlgInventory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listTagData);
	DDX_Control(pDX, IDC_STATIC_TOTAL, m_staTotal);
	DDX_Control(pDX, IDC_BUTTON1, m_bntInvenStart);
	DDX_Control(pDX, IDC_BUTTON2, m_bntInvenStop);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richedtInvnRes);
	DDX_Control(pDX, IDC_EDIT1, m_editTimeout);
}


BEGIN_MESSAGE_MAP(CDlgInventory, CDialog)
	ON_MESSAGE(WM_INVENOTYR_STOPPED,msg_inventory_stopped)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgInventory::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgInventory::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDlgInventory 消息处理程序



BOOL CDlgInventory::OnInitDialog()
{
	CDialog::OnInitDialog();
	DWORD dwStyle = m_listTagData.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
    dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
    //dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
    m_listTagData.SetExtendedStyle(dwStyle); //设置扩展风格
	m_listTagData.InsertColumn( 0, _T("EPC code"), LVCFMT_LEFT, 250 );//插入列
	m_listTagData.InsertColumn( 1, _T("Antenna"),LVCFMT_LEFT,80);
	m_listTagData.InsertColumn( 2, _T("Found count"),LVCFMT_LEFT,100) ;

	

	m_editTimeout.SetWindowText(_T("200")) ;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CDlgInventory::OnBnClickedButton1()
{
	TCHAR chrTimeoutBuf[32] ;
	memset(chrTimeoutBuf,0,sizeof(chrTimeoutBuf)) ;
	m_editTimeout.GetWindowText(chrTimeoutBuf ,sizeof(chrTimeoutBuf)/ sizeof(TCHAR)) ;
	m_invenTimeout =_ttoi(chrTimeoutBuf);
	m_readCount =0 ;
	m_taglist.RemoveAll() ;
	m_staTotal.SetWindowText(_T("0")) ;
	m_listTagData.DeleteAllItems() ;
	m_thrdInventory.Start(this,proc_inventory) ;
	m_bntInvenStart.EnableWindow(FALSE) ;
	m_bntInvenStop.EnableWindow(TRUE) ;
	m_richedtInvnRes.SetWindowText(_T("")) ;
	InventoryOn = TRUE;
}

void CDlgInventory::handle_tag_report(DWORD AIPType, DWORD tagType, DWORD antID, DWORD metaFlags, BYTE* tagData, DWORD datlen, CSTR writeOper, CSTR lockOper)
{

            WORD epcBitsLen = 0;
            int idx = 0;
            CArray<BYTE> epc;
            CArray<BYTE> readData;
            int i;
            CSTR strAntId;
            DWORD timestamp;
            DWORD frequency;
            BYTE rssi;
            BYTE readCnt;

			strAntId.Format(_T("%d"), antID) ;

            timestamp = 0;
            frequency = 0;
            rssi = 0;
            readCnt = 0;
            if (metaFlags == 0) metaFlags |= ISO18000p6C_META_BIT_MASK_EPC;
            if ((metaFlags & ISO18000p6C_META_BIT_MASK_EPC) > 0)
            {
                if (datlen < 2)
                {
                    //error data size 
                    return;
                }

                epcBitsLen = (tagData[idx] | (tagData[idx+1] << 8));
                idx += 2;
                int epcBytes = ((epcBitsLen + 7) / 8);
                if ((datlen - idx) < epcBytes)
                {
                    // error data size 
                    return;
                }
                for (i = 0; i < epcBytes; i++) epc.Add(tagData[idx + i]);
                idx += epcBytes;
            }
            if ((metaFlags & ISO18000P6C_META_BIT_MASK_TIMESTAMP) > 0)
            {
                if ((datlen - idx) < 4)
                {
                    //error data size 
                    return;
                }
                timestamp =(tagData[idx] | (tagData[idx + 1] << 8 & 0xff00) | (tagData[idx + 2] << 16 & 0xff0000) | (tagData[idx + 3] << 24 & 0xff000000));
                idx += 4;
            }
            if ((metaFlags & ISO18000P6C_META_BIT_MASK_FREQUENCY) > 0)
            {
                if ((datlen - idx) < 4)
                {
                    //error data size 
                    return;
                }
                frequency = (tagData[idx] | (tagData[idx + 1] << 8 & 0xff00) | (tagData[idx + 2] << 16 & 0xff0000) | (tagData[idx + 3] << 24 & 0xff000000));
                idx += 4;
            }
            if ((metaFlags & ISO18000p6C_META_BIT_MASK_RSSI) > 0)
            {
                if ((datlen - idx) < 1)
                {
                    //error data size 
                    return;
                }
                rssi = tagData[idx];
                idx += 1;
            }
            if ((metaFlags & ISO18000P6C_META_BIT_MASK_READCOUNT) > 0)
            {
                if ((datlen - idx) < 1)
                {
                    //error data size 
                    return;
                }
                readCnt = tagData[idx];
                idx += 1;
            }
            if ((metaFlags & ISO18000P6C_META_BIT_MASK_TAGDATA) > 0)
            {
                for (i = idx; i < datlen; i++) readData.Add(tagData[i]);
            }
			
			TCHAR  *pStrUid ;
			int strReqLen  = (epc.GetCount() +readData.GetCount()) * 2 + 1 ;
			pStrUid = new TCHAR[strReqLen ] ;
			if(pStrUid) {
				memset(pStrUid,0,strReqLen * sizeof(TCHAR)) ;
				BytesToHexStr(epc.GetData(),epc.GetCount(),pStrUid) ;	
			}

 	//to find uid .
	for( i=0;i<m_taglist.GetCount();i++) {
		if(m_taglist[i].m_uid ==pStrUid && m_taglist[i].m_antNo == antID) {
			break;
		}
	}

	if(i>=m_taglist.GetCount()) {
		/* it is a new tag ,then add to list */
		CTag newtag;
		newtag.m_counter = 1;
		newtag.m_uid =pStrUid ;
		newtag.m_type = 0;
		newtag.m_antNo =antID ;
		newtag.m_AIP =0  ;
		m_taglist.Add(newtag) ;
		int nRow=m_listTagData.InsertItem(m_taglist.GetCount()-1,pStrUid);        //插入行
		m_listTagData.SetItemText(nRow,1,strAntId) ;
		m_listTagData.SetItemText(nRow,2,_T("1"));
	}
	else{
		/* the tag is exist ,then only update found counter */
		m_taglist[i].m_counter++ ;
		if(m_taglist[i].m_counter>=500000)
		{
			m_taglist[i].m_counter = 1;
		}
		CString sc ;
		sc.Format(_T("%d"),m_taglist[i].m_counter) ;
		m_listTagData.SetItemText(i,2,sc) ;
	}

	/* update total found */
	CString strTotal;
	strTotal.Format(_T("%d"),m_taglist.GetCount()) ;
	m_staTotal.SetWindowText(strTotal) ;
}



int CDlgInventory::tag_inventory(
                                BYTE AIType,
                                DWORD *nTagCount )
{

    int iret;
    RFID_DN_HANDLE InvenParamSpecList =NULL ;
    InvenParamSpecList = RDR_CreateInvenParamSpecList();
    if (InvenParamSpecList)
    {
        /* set timeout */
        RDR_SetInvenStopTrigger(InvenParamSpecList,INVEN_STOP_TRIGGER_TYPE_TIMEOUT,m_invenTimeout, 0);
        /* create ISO18000p6C air protocol inventory parameters */
        RFID_DN_HANDLE  AIPIso18000p6c = ISO18000p6C_CreateInvenParam(InvenParamSpecList, 0, 0,ISO18000p6C_S0, ISO18000p6C_TARGET_A, ISO18000p6C_Dynamic_Q);
        if(AIPIso18000p6c) {

        }
    }
    nTagCount = 0;
LABEL_TAG_INVENTORY:
    iret = RDR_TagInventory(hr, AIType, 0, NULL, InvenParamSpecList);
    if (iret == 0 || iret == -21)
    {
        nTagCount +=RDR_GetTagDataReportCount(hr);
        RFID_DN_HANDLE TagDataReport;
        TagDataReport = NULL;
        TagDataReport = RDR_GetTagDataReport(hr, RFID_SEEK_FIRST); //first
        while (TagDataReport)
        {
            DWORD aip_id = 0;
            DWORD tag_id = 0;
            DWORD ant_id = 0;
            BYTE tagData[256] ;
            DWORD nSize =sizeof(tagData)  ;
            DWORD metaFlags = 0;

            iret = ISO18000p6C_ParseTagReport(TagDataReport,&aip_id,&tag_id,&ant_id,&metaFlags, tagData,&nSize);
            if (iret == 0)
            {
                handle_tag_report(aip_id,tag_id,ant_id,metaFlags,tagData,nSize,_T(""),_T("")) ;
            }

            TagDataReport = RDR_GetTagDataReport(hr, RFID_SEEK_NEXT); //next
        }
        if (iret == -21) // stop trigger occur,need to inventory left tags
        {
            AIType = AI_TYPE_CONTINUE;//use only-new-tag inventory 
            goto LABEL_TAG_INVENTORY;
        }
        iret = 0;
    }
    if (InvenParamSpecList) DNODE_Destroy(InvenParamSpecList);
    return iret;
}


DWORD WINAPI CDlgInventory::proc_inventory(LPVOID lpv)
{
	err_t iret;
	BYTE Antennas[64];
	BYTE AntCount =0 ;
	DWORD PrevTotalCount ;
	DWORD totalCount  ;
	CDlgInventory *pT = (CDlgInventory *)lpv;
	BYTE newAI= AI_TYPE_NEW ;


	totalCount =0 ;
	PrevTotalCount =0 ;
	while(!pT->m_thrdInventory.m_exit_flag) {
		//if AntCount =0  ,use default
		iret = pT->tag_inventory(newAI,&totalCount) ;
		if(iret == NO_ERR) {
			pT->m_readCount++ ;
			CString strReadCount;
			strReadCount.Format(_T("%d"),pT->m_readCount) ;

			//if(totalCount > 0)
			//{
			//	if(pT->m_ckbBeep.GetCheck()) {
			//		Beep(700,100) ;
			//	}
			//}

			if(PrevTotalCount != totalCount) { // tag count changed 
				CString stmp;
				stmp.Format(_T("Report count changed from:%d to %d\n"),PrevTotalCount,totalCount) ;
				pT->LogInventoryResult(stmp) ;		 
			}
			PrevTotalCount = totalCount ;
			totalCount =0 ;

			newAI=AI_TYPE_NEW;
		}
		else {
				totalCount =0 ;
				if(iret == -17) {// error from reader
					err_t rdr_err= RDR_GetReaderLastReturnError(hr) ;
					CString stmp;
					stmp.Format(_T("Inventory fail:%d,%d\n"),iret,rdr_err) ;
					pT->LogInventoryResult(stmp) ;
				}
				else {
					if(iret  != -35) {
						CString stmp;
						stmp.Format(_T("Inventory fail:%d\n"),iret) ;
						pT->LogInventoryResult(stmp) ;
					}
				}
				//inventory error
				newAI=AI_TYPE_NEW;
		}
	}
	/*
	*  If API RDR_SetCommuImmeTimeout is called when stop, API RDR_ResetCommuImmeTimeout 
	*  must be called too, Otherwise, an error -5 may occurs .
	*/
	RDR_ResetCommuImmeTimeout(hr) ;
	pT->PostMessage(WM_INVENOTYR_STOPPED,0,0) ;
	return 1;

}

void CDlgInventory::LogInventoryResult(CString msg)
{
	long  nInsertAfterChar = m_richedtInvnRes.GetWindowTextLength();
	m_richedtInvnRes.SetSel(nInsertAfterChar, nInsertAfterChar);
	m_richedtInvnRes.ReplaceSel(msg, FALSE);
}

LRESULT CDlgInventory::msg_inventory_stopped(WPARAM wp, LPARAM lp)
{
	m_thrdInventory.Stop() ;
	m_bntInvenStart.EnableWindow(TRUE) ;
	m_bntInvenStop.EnableWindow(FALSE) ;
	InventoryOn=FALSE;
	
	return  0 ;
}
void CDlgInventory::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	if(!InventoryOn) 
		return ;
	m_bntInvenStop.EnableWindow(FALSE) ;
	RDR_SetCommuImmeTimeout(hr) ; // 尝试让RDR_TagInventory马上超时退出 ，与RDR_ResetCommuImmeTimeout配对使用
	m_thrdInventory.SetStopTimeout(50000);//多标签时需要等待长时间, RDR_TagInventory的超时是30秒
	m_thrdInventory.SetExitVar() ;
}
