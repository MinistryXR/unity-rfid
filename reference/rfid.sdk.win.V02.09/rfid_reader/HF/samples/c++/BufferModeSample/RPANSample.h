// RPANSample.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRPANSampleApp:
// �йش����ʵ�֣������ RPANSample.cpp
//

class CRPANSampleApp : public CWinApp
{
public:
	CRPANSampleApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRPANSampleApp theApp;