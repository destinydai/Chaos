


inline ThreadEvent::ThreadEvent( bool bManualReset,bool bInitialState )
{
	m_event = CreateEvent(0,bManualReset,bInitialState,NULL);
	if(m_event==NULL)
	{
		CH_TRACE("sys_error:%d call API CreateEvent failed",GetLastError());
	}
}

inline ThreadEvent::~ThreadEvent()
{
	if(m_event)
	{
		CloseHandle(m_event);
	}
}

inline void ThreadEvent::resetEvent()
{
	BOOLEAN bResult = ::ResetEvent(m_event);
	if(!bResult)
	{
		CH_TRACE("sys_error:%d call API ResetEvent() failed.",GetLastError());
	}
}

inline void ThreadEvent::setEvent()
{
	BOOLEAN bResult = ::SetEvent(m_event);
	if(!bResult)
	{
		CH_TRACE("sys_error:%d call API SetEvent failed.",GetLastError());
	}
}

inline bool ThreadEvent::waitSignal( uint t )
{
	DWORD dwResult = t==0?WaitForSingleObject(m_event,INFINITE) : WaitForSingleObject(m_event,t);
	return dwResult == WAIT_OBJECT_0;
}