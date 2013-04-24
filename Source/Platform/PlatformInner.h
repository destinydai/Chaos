#pragma once


#include "ChoPlatform.h"


#include "Platform/FileStream.h"
#include "Platform/FileDirectory.h"


#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "Platform/win32/FileSystem/FileSystem_win32.h"
#include "Platform/win32/FileSystem/FileStream_win32.h"
#include "Platform/win32/FileSystem/FileDirectory_win32.h"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include "Platform/android/FileSystem/FileSystem_android.h"
#include "Platform/android/FileSystem/FileStream_android.h"
#include "Platform/android/FileSystem/FileDirectory_android.h"
#else
	CH_ERROR("not implement yet");
#endif