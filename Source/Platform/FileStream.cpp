#include "stdafx.h"


NS_CH_BEG


FileStream::FileStream( const string &szPath):
	m_szFilePath(szPath)
{
	if(szPath.size()==0)
	{
		CH_ERROR("[pl] error: szPath length is zero");
	}

	int nPos = m_szFilePath.rfind('/');
	if(nPos!=-1 && nPos== m_szFilePath.size() -1)
	{
		CH_ERROR("[pl] error: szPath not a file path %s",szPath.c_str());
	}
	
	const char* pExtension = GetFileExtension();
	if(pExtension)
	{
		m_szFileName=string((const char*)&m_szFilePath[nPos+1],--pExtension);
	}
	else
	{
		m_szFileName=string(&m_szFileName[nPos+1]);
	}
}

FileStream::~FileStream( void )
{

}


const char* FileStream::GetFileExtension()
{
	int nPos = m_szFilePath.rfind('.');
	if(nPos==-1 || nPos == m_szFilePath.size()-1)
	{
		return nullptr;
	}
	return &m_szFilePath[nPos+1];
}

const char* FileStream::GetFullFileName()
{
	int nPos = m_szFilePath.rfind('/');
	return &m_szFilePath[nPos+1];
}

const char* FileStream::GetFileName()
{
	return &m_szFileName[0];
}

const char* FileStream::GetFilePath()
{
	return &m_szFilePath[0];
}

string FileStream::GetDirectoryPath()
{
	return string((const char*)&m_szFilePath[0],GetFullFileName()-1);
}


NS_CH_END