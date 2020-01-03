#include "stdafx.h"
#include "AsyncTaskExe.h"




CAsyncTaskExe::CAsyncTaskExe()
{	
	m_cbExeTask =NULL;
}


CAsyncTaskExe::~CAsyncTaskExe()
{

}

void CAsyncTaskExe::AsyncExecute(ASYNC_EXE_TASK cbExeTask,void *lparam ,void *wparam)
{
	m_cbExeTask = cbExeTask ;
	m_lparam = lparam ;
	m_wparam = wparam ;
	m_thrd.Stop();
	m_thrd.Start(this,ProcExeTask) ;
}

DWORD WINAPI CAsyncTaskExe::ProcExeTask(LPVOID lpv)
{
	CAsyncTaskExe *pT  = (CAsyncTaskExe *)lpv ;
	pT->m_cbExeTask(pT->m_lparam,pT->m_wparam) ;

	return 1;
}
