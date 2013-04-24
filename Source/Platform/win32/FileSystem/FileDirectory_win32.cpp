#include "stdafx.h"


NS_CH_BEG


FileDirectory_win32::FileDirectory_win32( const string& szPath ):
	FileDirectory(szPath)
{
	
}

FileDirectory_win32::~FileDirectory_win32( void )
{

}

void FileDirectory_win32::ListAllFiles( StringArray &outArray )
{
	FileSystem_win32::ScanFolder(&outArray,nullptr,m_szDirectoryPath,true,true);
}

void FileDirectory_win32::ListFiles( StringArray &outArray )
{
	FileSystem_win32::ScanFolder(&outArray,nullptr,m_szDirectoryPath,false,true);
}

void FileDirectory_win32::ListDirectory( StringArray &outArray )
{
	FileSystem_win32::ScanFolder(nullptr,&outArray,m_szDirectoryPath,false,true);
}

void FileDirectory_win32::ListAllDirectory( StringArray &outArray )
{
	FileSystem_win32::ScanFolder(nullptr,&outArray,m_szDirectoryPath,true,true);
}

IFileStream* FileDirectory_win32::OpenFile( const char* szRelPath, FileOpenMode mode )
{
	string szPath = m_szDirectoryPath + szRelPath;
	return FileSystem::GetInstancePtr()->OpenFile(szPath.c_str(),mode);
}

NS_CH_END