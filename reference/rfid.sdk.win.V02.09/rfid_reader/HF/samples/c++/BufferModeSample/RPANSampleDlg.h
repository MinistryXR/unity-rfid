// RPANSampleDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include "rfidlib.h"
#include "rfidlib_reader.h"
#include "rfidlib_drv_rpan.h"
#include "RpanRecord.h"
using namespace std;

//ANRPAN_SetSysTime(RFID_READER_HANDLE hr,WORD year,BYTE month,BYTE day,BYTE hour,BYTE min,BYTE sec);



// CRPANSampleDlg �Ի���
class CRPANSampleDlg : public CDialog
{
// ����
public:
	CRPANSampleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RPANSAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtonclose();
	afx_msg void OnBnClickedButtonsettime();
	afx_msg void OnBnClickedButtonClearrecord();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	static UINT GetRecordPro(void *lp);
private:
	CComboBox m_cmb_type;
	CComboBox m_cmb_comName;
	CComboBox m_cmb_baud;
	CComboBox m_cmb_frame;
	CEdit m_edit_addr;
	CEdit m_edit_port;
	CListCtrl m_listTagData;
	RFID_READER_HANDLE hReader;
	bool b_threadRun;
	CComboBox m_cmb_bluetoothName;
	vector<CString>blueAddrList;
public:
	afx_msg void OnCbnSelchangeCmbBluetoothname();
};
