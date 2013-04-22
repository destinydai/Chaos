#pragma once

NS_CH_BEG

class Semaphore
{
public:
	/// Create a semaphore with an initial count and a maximum count
	inline Semaphore( int initialCount = 0, int maxCount = 0xffffffff>>1);

	//禁止赋值
	Semaphore(const Semaphore &obj);
	Semaphore &operator=(const Semaphore &obj);

		/// Destruct the Semaphore
	inline ~Semaphore();

	//等待信号直到有信号后才返回
	//如果t不为0那么等待t毫秒后返回返回false
	//得到信号返回true
	inline bool waitSignal(uint t=0);

	//释放信号，使得waitSignal返回true
	inline void releaseSignal(int count = 1);
			
protected:	
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	void* m_semaphore;
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	sem_t m_semaphore;
#elif CH_PLATFORM == CH_PLATFORM_MACOS
	CH_ERROR("not implement yet");
#endif
	
};

#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "Platform/win32/Semaphore_win32.inl"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include "Platform/android/Semaphore_android.inl"
#elif CH_PLATFORM == CH_PLATFORM_MACOS
	CH_ERROR("not implement yet");
#endif


NS_CH_END