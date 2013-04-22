

inline ThreadEvent::ThreadEvent( bool bManualReset,bool bInitialState ):
	m_bSignal(bInitialState),
	m_bManualReset(bManualReset)
{
	pthread_mutex_init(&m_mutex,nullptr);
	pthread_cond_init(&m_event->cond, NULL);
}

inline ThreadEvent::~ThreadEvent()
{
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_event);
}

inline void ThreadEvent::resetEvent()
{
	pthread_mutex_lock(&m_mutex);
	m_bSignal = false;
	pthread_mutex_unlock(&m_mutex);
}

inline void ThreadEvent::setEvent()
{
	int r= pthread_mutex_lock(&m_mutex);
	m_bSignal = true;
	r =pthread_cond_signal(&m_event);
	r =pthread_mutex_unlock(&m_mutex);
}

inline bool ThreadEvent::waitSignal( uint t )
{
	int r=0;
	struct timespec spec;

	pthread_mutex_lock(&m_mutex);
	if(t==0)
	{
		while(m_bSignal==false)
		{
			r=pthread_cond_wait(&m_event,&m_mutex);
			if(!m_bManualReset)
			{
				m_bSignal = false;
				break;
			}
		}
	}
	else
	{
		r = pthread_cond_timedwait(&m_event,&m_mutex,getTimeout(&spec,t));
	}
	pthread_mutex_unlock(&m_mutex);
	return r!=ETIMEDOUT;
}