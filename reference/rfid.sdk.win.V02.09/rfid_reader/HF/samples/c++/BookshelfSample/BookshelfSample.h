// BookshelfSample.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBookshelfSampleApp:
// �йش����ʵ�֣������ BookshelfSample.cpp
//

class CBookshelfSampleApp : public CWinApp
{
public:
	CBookshelfSampleApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBookshelfSampleApp theApp;