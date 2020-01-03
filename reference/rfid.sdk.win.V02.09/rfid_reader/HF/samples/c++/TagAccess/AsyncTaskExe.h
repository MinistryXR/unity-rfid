#ifndef __ASYNCTASKEXE_H__
#define __ASYNCTASKEXE_H__


#include "wtlthread.h"


typedef void (*ASYNC_EXE_TASK)(void *lparam ,void *wparam ) ;


class CAsyncTaskExe:public WTL::CThread 
{
public:
	CAsyncTaskExe() ;
	virtual ~CAsyncTaskExe() ;
public:
	void AsyncExecute(ASYNC_EXE_TASK cbExeTask,void *lparam ,void *wparam) ;
protected:
	ASYNC_EXE_TASK  m_cbExeTask  ;
	void *m_lparam ;
	void *m_wparam ;
	WTL::CThread  m_thrd ;
protected:
	static DWORD WINAPI ProcExeTask(LPVOID lpv) ;
};















#endif
