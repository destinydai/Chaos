



inline Semaphore::Semaphore( int initialCount /*= 0*/, int maxCount /*= 0xffffffff>>1 */ )
{
	int r = sem_init(&m_semaphore,0,initialCount);
	if(0!=r)
	{
		CH_ERROR("sys_error: call API sem_init() failed.");
	}
}

inline Semaphore::~Semaphore()
{
	sem_close(&m_semaphore);
	sem_destroy(&m_semaphore);
}

inline bool Semaphore::waitSignal(uint t)
{
	int r=0;
	if(t==0)
	{
		r = sem_wait(&m_semaphore);
		return r==0;
	}
	else
	{
		struct timespec spec;
		r=sem_timedwait(&m_semaphore,getTimeout(&spec,t));
		return r==0;
	}
}

inline void Semaphore::releaseSignal( int count /*= 1*/ )
{
	int r=0;
	while(count>0)
	{
		r = sem_post(&m_semaphore);
		--count;
		if(r!=0)
		{
			CH_ERROR("sys_error call API releaseSignal() failed.");
		}
	}
}