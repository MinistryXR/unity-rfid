// LSGateMFCDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CLSGateMFCDemoApp:
// �йش����ʵ�֣������ LSGateMFCDemo.cpp
//

class CLSGateMFCDemoApp : public CWinApp
{
public:
	CLSGateMFCDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()


};

extern CLSGateMFCDemoApp theApp;