// RS485Sample.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRS485SampleApp:
// �йش����ʵ�֣������ RS485Sample.cpp
//

class CRS485SampleApp : public CWinApp
{
public:
	CRS485SampleApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRS485SampleApp theApp;