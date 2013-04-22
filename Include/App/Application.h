#pragma once


#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "App/win32/Application_win32.h"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	CH_ERROR("not implement yet");
#elif CH_PLATFORM == CH_PLATFORM_MACOS
	CH_ERROR("not implement yet");
#endif