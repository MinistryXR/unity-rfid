// demo_m24rl64.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "demo_m24rl64.h"
#include "demo_m24rl64Dlg.h"
#include "rfidlib_reader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdemo_m24rl64App

BEGIN_MESSAGE_MAP(Cdemo_m24rl64App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cdemo_m24rl64App ����

Cdemo_m24rl64App::Cdemo_m24rl64App()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cdemo_m24rl64App ����

Cdemo_m24rl64App theApp;
int ReaderType=-1;
DWORD AntennaSelected =0 ;
DWORD AntennaIFCountOfReader ;
READER_CLOSE_API reader_close_api = NULL ;
BOOLEAN InventoryOn =FALSE;
// Cdemo_m24rl64App ��ʼ��

BOOL Cdemo_m24rl64App::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	AfxInitRichEdit();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	RDR_LoadReaderDrivers(_T("\\Drivers")) ;

	AntennaSelected =0 ;
	Cdemo_m24rl64Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
