// Setoutput.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSetoutputApp:
// �йش����ʵ�֣������ Setoutput.cpp
//

class CSetoutputApp : public CWinApp
{
public:
	CSetoutputApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSetoutputApp theApp;