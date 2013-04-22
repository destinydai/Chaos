#pragma once

NS_CH_BEG

class Semaphore
{
public:
	/// Create a semaphore with an initial count and a maximum count
	inline Semaphore( int initialCount = 0, int maxCount = 0xffffffff>>1);

	//��ֹ��ֵ
	Semaphore(const Semaphore &obj);
	Semaphore &operator=(const Semaphore &obj);

		/// Destruct the Semaphore
	inline ~Semaphore();

	//�ȴ��ź�ֱ�����źź�ŷ���
	//���t��Ϊ0��ô�ȴ�t����󷵻ط���false
	//�õ��źŷ���true
	inline bool waitSignal(uint t=0);

	//�ͷ��źţ�ʹ��waitSignal����true
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