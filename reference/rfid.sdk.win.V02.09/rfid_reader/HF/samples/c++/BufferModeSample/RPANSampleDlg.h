// RPANSampleDlg.h : 头文件
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



// CRPANSampleDlg 对话框
class CRPANSampleDlg : public CDialog
{
// 构造
public:
	CRPANSampleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RPANSAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
