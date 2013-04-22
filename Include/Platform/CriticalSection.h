#pragma once

NS_CH_BEG

class CriticalSection
{
public:
	class ScopeLock
	{
	public:
		inline ScopeLock(CriticalSection &section):m_section(section)
		{
			m_section.enter();
		}
		inline ~ScopeLock(void)
		{
			m_section.leave();
		}
	private:
		CriticalSection &m_section;
	};
public:
	inline CriticalSection( int spinCount = 0);
	inline  ~CriticalSection();
private:
	//禁止赋值构造函数
	inline CriticalSection(const CriticalSection &obj);
	inline CriticalSection &operator=(const CriticalSection &obj);
public:
	inline void enter();

	inline void leave();

public:
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	CRITICAL_SECTION m_section;
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	pthread_mutex_t m_mutex;
#else
	CH_ERROR("not implement yet");
#endif
};

#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "Platform/win32/CriticalSection_win32.inl"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include "Platform/android/CriticalSection_android.inl"
#else
	CH_ERROR("not implement yet");
#endif


NS_CH_END

