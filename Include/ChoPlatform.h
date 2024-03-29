#pragma once

#include "Platform/Config.h"

#include "Platform/Tracer.h"
#include "Platform/CriticalSection.h"
#include "Platform/Semaphore.h"
#include "Platform/ThreadEvent.h"
#include "Platform/Thread.h"
#include "Platform/Atomic.h"
#include "Platform/Window.h"
#include "Platform/FileSystem.h"

#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "Platform/win32/Win32Window.h"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include "Platform/android/NativeWindow_android.h"
//#include "Platform/android/NativeActivity_android.h"
#else

#endif


