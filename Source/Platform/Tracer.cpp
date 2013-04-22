#include "stdafx.h"


#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "Platform/win32/Tracer_win32.cpp"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include "Platform/android/Tracer_android.cpp"
#else
	CH_ERROR("not implement yet");
#endif