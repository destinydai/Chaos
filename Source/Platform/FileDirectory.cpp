#include "stdafx.h"


NS_CH_BEG


FileDirectory::FileDirectory( const string &szPath):
	m_szDirectoryPath(szPath)
{
	if(m_szDirectoryPath.size()==0)
	{
		CH_ERROR("[pl] szPath length is zero.");
		return;
	}

	if(m_szDirectoryPath[m_szDirectoryPath.size()-1]!='/')
	{
		m_szDirectoryPath.push_back('/');
	}
}

FileDirectory::~FileDirectory( void )
{

}

const char* FileDirectory::GetDirectoryPath()
{
	return &m_szDirectoryPath[0];
}

NS_CH_END