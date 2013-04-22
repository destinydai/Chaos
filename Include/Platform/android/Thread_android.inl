
inline Thread::Thread():m_thread(0)
{
	pthread_attr_init(&m_threadAttr);
}


inline Thread::~Thread()
{
	pthread_attr_destroy(&m_threadAttr);
	m_thread = 0;
}

inline bool Thread::startThread( StartFunction f, void* pData, int threadStackSize /*= JU_THREAD_DEFAULT_STACKSIZE */ )
{
	int r= pthread_attr_setdetachstate(&m_threadAttr, PTHREAD_CREATE_JOINABLE);
	r=pthread_create(&m_thread, &m_threadAttr, StartFunction, pData);
	return r==0;
}

inline void Thread::join()
{
	pthread_join(m_thread,0);
}

inline void Thread::sleep( unsigned int millsec )
{
	usleep(millsec*1000);
}

inline uint64 Thread::getThreadID()
{
	return m_thread;
}

inline void* Thread::getHandle()
{
	return (void*)m_thread;
}