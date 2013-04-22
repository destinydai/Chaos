



inline Semaphore::Semaphore( int initialCount /*= 0*/, int maxCount /*= 0xffffffff>>1 */ )
{
	m_semaphore = ::CreateSemaphore(0,initialCount,maxCount,0);
	if(0==m_semaphore)
	{
		DWORD dwError = GetLastError();
		CH_ERROR("sys_error:%d call API CreateSemaphore() failed.",dwError);
	}
}

inline Semaphore::~Semaphore()
{
	if(m_semaphore)
	{
		CloseHandle(m_semaphore);
	}
}

inline bool Semaphore::waitSignal(uint t)
{
	DWORD dwResult = t==0?WaitForSingleObject(m_semaphore,INFINITE) : WaitForSingleObject(m_semaphore,t);
	return dwResult == WAIT_OBJECT_0;
}

inline void Semaphore::releaseSignal( int count /*= 1*/ )
{
	BOOL bResult = ::ReleaseSemaphore(m_semaphore,count,0);
	if(!bResult)
	{
		CH_ERROR("sys_error:%d call API ReleaseSemaphore() failed.",GetLastError());
	}
}