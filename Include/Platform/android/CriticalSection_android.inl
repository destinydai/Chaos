#pragma once

NS_CH_BEG

inline CriticalSection::CriticalSection(int spinCount )
{
	pthread_mutex_init(&m_mutex,nullptr);
}

inline CriticalSection::~CriticalSection()
{
	pthread_mutex_destroy(&m_mutex);
}

inline void CriticalSection::enter()
{
	pthread_mutex_lock(&m_mutex);
}

inline void CriticalSection::leave()
{
	pthread_mutex_unlock(&m_mutex);
}


NS_CH_END

