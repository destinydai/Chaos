#include "stdafx.h"

NS_CH_BEG

FileSystem* FileSystem::GetInstancePtr()
{
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	static FileSystem_win32 instance;
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	static FileSystem_android instance;
#else
	CH_ERROR("not implement yet");
#endif
	return &instance;
}

bool FileSystem::IsAbsoluteFilePath( const char* szFilePath )
{
	return false;
}


NS_CH_END