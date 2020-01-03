// SetoutputDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "rfidlib.h"


// CSetoutputDlg 对话框
class CSetoutputDlg : public CDialog
{
// 构造
public:
	CSetoutputDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SETOUTPUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnCbnSelchangeCmbCommunicatetype();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnSetoutput();

private:
	void EnableAllCtr(BOOL isOpen);
	void ListOutput();
	CComboBox m_cmb_devType;
	CComboBox m_cmb_communicateType;
	CComboBox m_com_name;
	CIPAddressCtrl m_ipaddress_ip;
	CEdit m_edit_port;
	CComboBox m_cmb_baund;
	CComboBox m_cmb_frame;	
	CComboBox m_cmb_activeTime;
	CComboBox m_cmb_frequecy;
	CComboBox m_cmb_stoptime;
	CCheckListBox m_list_outPut;
	RFID_READER_HANDLE hr;	
	
};
