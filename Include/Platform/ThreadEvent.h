#pragma once

NS_CH_BEG

class ThreadEvent
{
public:
	ThreadEvent(bool bManualReset,bool bInitialState);
	inline ~ThreadEvent();

	ThreadEvent(const ThreadEvent &obj);
	ThreadEvent &operator=(const ThreadEvent &obj);

	//手动重设信号为无信号状态
	inline void resetEvent();
	//发出信号
	inline void setEvent();
	//等待信号直到有信号后才返回
	//如果t不为0那么等待t毫秒后返回返回false
	//得到信号返回true
	inline bool waitSignal(uint t=0);
private:
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	void *m_event;
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	pthread_cond_t m_event;
	pthread_mutex_t m_mutex;
	int m_bSignal;
	int m_bManualReset;
#else
	CH_ERROR("not implement yet");
#endif
	
};

#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "Platform/win32/ThreadEvent_win32.inl"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include "Platform/android/ThreadEvent_android.inl"
#else
	CH_ERROR("not implement yet");
#endif

NS_CH_END