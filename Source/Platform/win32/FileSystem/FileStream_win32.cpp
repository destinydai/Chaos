#include "stdafx.h"


NS_CH_BEG

FileStream_win32::FileStream_win32( const string& szPath, HANDLE hFile):
	FileStream(szPath),
	m_hFile(hFile)
{
	
}

FileStream_win32::~FileStream_win32( void )
{
	if(m_hFile!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile=INVALID_HANDLE_VALUE;
	}
}

uint FileStream_win32::GetFileSize()
{
	DWORD dwHigh=0;
	DWORD dwSize = ::GetFileSize(m_hFile,&dwHigh);
	if(dwHigh!=0)
	{
		CH_ERROR("[pl] error: not support big file");
	}
	return dwSize;
}

uint FileStream_win32::Seek( uint offset,FileSeekFlag pos )
{
	return SetFilePointer(m_hFile,offset,0,pos);
}

uint FileStream_win32::GetRemainingLength()
{
	DWORD dwCurPos = ::SetFilePointer(m_hFile,0,0,FILE_CURRENT);
	DWORD dwFileLen = this->GetFileSize();
	return dwFileLen - dwCurPos;
}

int FileStream_win32::Read( void* buf,uint count )
{
	DWORD dwReaded=0;
	if(!ReadFile(m_hFile,buf,count,&dwReaded,NULL))
	{
		return -1;
	}
	return dwReaded;
}


NS_CH_END