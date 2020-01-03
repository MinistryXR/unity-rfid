// SetoutputDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "rfidlib.h"


// CSetoutputDlg �Ի���
class CSetoutputDlg : public CDialog
{
// ����
public:
	CSetoutputDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SETOUTPUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
