#include "stdafx.h"

#if CH_PLATFORM == CH_PLATFORM_ANDROID

NS_CH_BEG

FileSystem_android::FileSystem_android( void )
{

}

FileSystem_android::~FileSystem_android( void )
{

}

IFileDirectory* FileSystem_android::OpenRootDirectory()
{
	return OpenDirectory("");
}

const char* FileSystem_android::GetRootPath()
{
	return "";
}

IFileDirectory* FileSystem_android::OpenDirectory( const char* dirName )
{
	if(FileSystem_android::GetAssetManager()==nullptr)
	{
		CH_ERROR("[pl] error: the AAssetManager m_pMgr is null please set before.");
	}
	AAssetDir* pDir= AAssetManager_openDir(FileSystem_android::GetAssetManager(),dirName);
	if(pDir==nullptr)
		return nullptr;
	FileDirectory_android* pDirectory = new FileDirectory_android(dirName,pDir);
	return pDirectory;
}

IFileStream* FileSystem_android::OpenFile( const char* szPath, FileOpenMode mode )
{
	if( (mode & FILE_OPEN_WRITE) !=0 )
	{
		CH_ERROR("[pl] error: android not support write to assets");
	}

	AAsset* pAsset = AAssetManager_open(m_pMgr,szPath,AASSET_MODE_STREAMING);
	FileStream_android* pFileStream = new FileStream_android(szPath,pAsset);
	return pFileStream;
}

void FileSystem_android::ListAllFiles( StringArray &outArray )
{
	CH_ERROR("[pl] error: not implement yet");
}

uint FileSystem_android::GetSystemFileCount()
{
	CH_ERROR("[pl] error: not implement yet");
	return 0;
}

uint64 FileSystem_android::GetSystemFileSize()
{
	CH_ERROR("[pl] error: not implement yet");
	return 0;
}

AAssetManager* FileSystem_android::m_pMgr;

NS_CH_END

#endif