#ifndef WTL_MYTHREAD_H
#define WTL_MYTHREAD_H


namespace WTL
{

#define	DEFAULT_STOP_TIMEOUT		10000


class CThread
{
public:
	CThread(void) ;
	~CThread(void) ;

public:
	//create a thread 
	bool	Start(LPVOID datAddr,LPTHREAD_START_ROUTINE threadProc)	 ;
	//stop the thread 
	bool	Stop() ;
	//set m_exit_flag to true and m_exit_event to notifying status
	void	SetExitVar()  ;
	//get the current value of m_exit_flag
	bool	GetExitFlag()  ;
	//set a new value to m_stop_timeout
	void	SetStopTimeout(int timeout) ;
	//get the current value of m_stop_timeout
	int		GetStopTimeout()  ;

	int		Suspend() ;

	int		Resume() ;
	
	HANDLE	m_exit_event;
	bool	m_exit_flag ;
private:
	HANDLE	m_hthread;          
	DWORD	m_pdwThreadId  ;
	LPTHREAD_START_ROUTINE  m_thread_proc ;
	LPVOID	m_thread_data;
	bool	m_started ;
	
	int		m_stop_timeout;
	
};





inline CThread::CThread(void)
{
	m_stop_timeout=DEFAULT_STOP_TIMEOUT ;
	m_exit_event=CreateEvent(NULL,true,false,NULL) ;
	m_hthread=NULL ;
	m_pdwThreadId=0 ;
	m_started=false;
}
inline CThread::~CThread(void)
{
	if(m_started) Stop()  ;
	CloseHandle(m_exit_event) ;
}

//create a thread 
inline bool CThread::Start(LPVOID datAddr,LPTHREAD_START_ROUTINE threadProc)	
{
	if(m_started ) return true;
	m_started=true;

	m_thread_data=(LPVOID)datAddr;
	m_thread_proc=threadProc ; 
	m_hthread=NULL ;
	m_pdwThreadId=0 ;
	m_hthread= CreateThread(NULL,
								   0,
								   m_thread_proc,
								   m_thread_data,
								   CREATE_SUSPENDED,
								   &m_pdwThreadId) ;
	if(m_hthread== NULL )
	{
	   Stop() ;
	   return false;
	}
	m_exit_flag=false;
	ResetEvent(m_exit_event) ;
	ResumeThread(m_hthread) ;

	return true;
}
//stop the thread 
inline bool CThread::Stop()
{
    DWORD dwRes;
	if(!m_started) return true;

	if(m_hthread)
	{
        m_exit_flag=true;	
	    dwRes=WaitForSingleObject(m_hthread,m_stop_timeout) ; 
        switch(dwRes)
	    {
            case  WAIT_OBJECT_0   :  break;  

            case  WAIT_TIMEOUT    :  
			  //超时则强制关闭线程
              TerminateThread(m_hthread,0);
			  break;
            default:  
			  break;     
	     }
		CloseHandle(m_hthread) ;
		m_hthread=NULL ;
		m_pdwThreadId=0 ;

    }

	m_started=false;

	return true;
}
//set m_exit_flag to true and m_exit_event to notifying status
inline void CThread::SetExitVar() 
{
	m_exit_flag=true;
	SetEvent(m_exit_event) ;
}
//get the current value of m_exit_flag
inline bool CThread::GetExitFlag() 
{
	return m_exit_flag ;
}
//set a new value to m_stop_timeout
inline void CThread::SetStopTimeout(int timeout)
{
	m_stop_timeout=timeout ;
}
//get the current value of m_stop_timeout
inline int CThread::GetStopTimeout() 
{
	return m_stop_timeout ;
}


inline int	CThread::Suspend() 
{
	if(SuspendThread(m_hthread)!=-1) return 1;
	else 
		return 0 ;
}

inline int	CThread::Resume() 
{
	if(ResumeThread(m_hthread) != -1 )
		return 1;
	else
		return 0;
}











}


#define CTHREAD		WTL::CThread









#endif