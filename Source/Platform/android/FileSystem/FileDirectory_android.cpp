#include "stdafx.h"

#if CH_PLATFORM == CH_PLATFORM_ANDROID

NS_CH_BEG

FileDirectory_android::FileDirectory_android( const string &szPath,AAssetDir* pDir):
	FileDirectory(szPath),
	m_pDirectory(pDir)
{


}

FileDirectory_android::~FileDirectory_android( void )
{
	if(m_pDirectory)
	{
		AAssetDir_close(m_pDirectory);
		m_pDirectory=nullptr;
	}
}

void FileDirectory_android::ListAllFiles( StringArray &outArray )
{
	CH_ERROR("[pl] error: android can't call this method");
}

void FileDirectory_android::ListFiles( StringArray &outArray )
{
	AAssetDir_rewind(m_pDirectory);
	const char* szName = nullptr;
	while( (szName=AAssetDir_getNextFileName(m_pDirectory)) != nullptr)
	{
		outArray.push_back(szName);
	}
}

void FileDirectory_android::ListDirectory( StringArray &outArray )
{
	CH_ERROR("[pl] error: android can't call this method");
}

void FileDirectory_android::ListAllDirectory( StringArray &outArray )
{
	CH_ERROR("[pl] error: android can't call this method");
}

IFileStream* FileDirectory_android::OpenFile( const char* szRelPath, FileOpenMode mode )
{
	string szPath = m_szDirectoryPath + string(szRelPath);
	AAsset* pFile = AAssetManager_open(FileSystem_android::GetAssetManager(),szPath.c_str(),AASSET_MODE_STREAMING);
	if(pFile==nullptr)
	{
		return nullptr;
	}

	return new FileStream_android(szPath,pFile);
}

NS_CH_END
#endif