// WriteEPC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWriteEPCApp:
// �йش����ʵ�֣������ WriteEPC.cpp
//

class CWriteEPCApp : public CWinApp
{
public:
	CWriteEPCApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWriteEPCApp theApp;