// mfcdemo1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfcdemo1App:
// �йش����ʵ�֣������ mfcdemo1.cpp
//

class Cmfcdemo1App : public CWinApp
{
public:
	Cmfcdemo1App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfcdemo1App theApp;