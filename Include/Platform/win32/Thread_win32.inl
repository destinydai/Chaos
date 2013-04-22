
inline Thread::Thread():m_thread(0),m_threadID(0)
{

}


inline Thread::~Thread()
{
	if(m_thread)
	{
		CloseHandle(m_thread);
		m_thread=0;
		m_threadID=0;
	}
}

inline bool Thread::startThread( StartFunction f, void* pData, int threadStackSize /*= JU_THREAD_DEFAULT_STACKSIZE */ )
{
	DWORD dwThreadID=0;
	HANDLE hThread = ::CreateThread(0,threadStackSize,(LPTHREAD_START_ROUTINE)f,pData,0,&dwThreadID);
	m_thread = hThread;
	m_threadID = dwThreadID;
	return hThread != NULL;
}

inline void Thread::join()
{
	DWORD dwResult = ::WaitForSingleObject(m_thread,INFINITE);
	if(dwResult != WAIT_OBJECT_0)
	{
		CH_TRACE("sys_error:%d call api WaitForSingleObject() failed.",GetLastError());
	}
}

inline void Thread::sleep( unsigned int millsec )
{
	::Sleep(millsec);
}

inline uint64 Thread::getThreadID()
{
	return m_threadID;
}

inline void* Thread::getHandle()
{
	return m_thread;
}