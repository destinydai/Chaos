#pragma once

NS_CH_BEG

class Atomic
{
public:
	static inline int AtomicAdd(int* var, int value);
	static inline int AtomicExchange(int *var, int value);

	static inline int64 AtomicAdd(int64 *var, int64 value);
	static inline int64 AtomicExchange(int64 *var, int64 value);

	/// waits until the value of *var is not value and returns the value of *var
	static inline int WaitForValueEqual( int* var, int value );
	static inline int WaitForValueNotEqual( int* var, int value );
};


#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include <Platform/win32/Atomic_win32.inl>
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	CH_ERROR("not implement yet");
#else
	CH_ERROR("not implement yet");
#endif



NS_CH_END