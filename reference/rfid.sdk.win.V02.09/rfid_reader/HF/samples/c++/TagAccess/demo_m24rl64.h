// demo_m24rl64.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cdemo_m24rl64App:
// �йش����ʵ�֣������ demo_m24rl64.cpp
//

class Cdemo_m24rl64App : public CWinApp
{
public:
	Cdemo_m24rl64App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cdemo_m24rl64App theApp;