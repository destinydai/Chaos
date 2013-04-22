#pragma once

NS_CH_BEG

class Thread
{
public:
	typedef void (*StartFunction)(void*);

	inline Thread();
	inline ~Thread();
	Thread(const Thread &obj)
	{
		Thread &a = const_cast<Thread&>(obj);
		m_thread = a.m_thread;
		m_threadID = a.m_threadID;
		a.m_thread = 0;
		a.m_threadID = 0;
	}
	Thread &operator =(const Thread &obj)
	{
		Thread &a = const_cast<Thread&>(obj);
		m_thread = a.m_thread;
		m_threadID = a.m_threadID;
		a.m_thread = 0;
		a.m_threadID = 0;
		return *this;
	};
public:
	enum{
		THREAD_DEFAULT_STACKSIZE = 0,
	};

	enum Status
	{
		THREAD_TERMINATED,
		THREAD_RUNNING,
		THREAD_NOT_STARTED
	};

	inline bool startThread(StartFunction f, void*, int threadStackSize = THREAD_DEFAULT_STACKSIZE );

	//Status getStatus();

	inline uint64 getThreadID();

	inline void *getHandle();
	//等待线程执行完成
	inline void join();

	static inline void sleep(unsigned int millsec);
protected:
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	uint64 m_threadID;
	void *m_thread;
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	pthread_attr_t m_threadAttr;
	pthread_t m_thread;
#else
	CH_ERROR("not implement yet");
#endif
	
	
};

#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "Platform/win32/Thread_win32.inl"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include "Platform/android/Thread_android.inl"
#else
	CH_ERROR("not implement yet");
#endif


NS_CH_END