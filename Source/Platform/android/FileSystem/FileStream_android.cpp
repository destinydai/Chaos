#include "stdafx.h"

#if CH_PLATFORM == CH_PLATFORM_ANDROID

NS_CH_BEG

FileStream_android::FileStream_android( const string &szPath ,AAsset* pAsset):
	FileStream(szPath),
	m_pFile(pAsset)
{

}

FileStream_android::~FileStream_android( void )
{
	if(m_pFile)
	{
		AAsset_close(m_pFile);
		m_pFile=nullptr;
	}
}

uint FileStream_android::GetFileSize()
{
	return AAsset_getLength(m_pFile);
}

uint FileStream_android::Seek(uint offset,FileSeekFlag pos)
{	
	return AAsset_seek(m_pFile,offset,pos);
}

uint FileStream_android::GetRemainingLength()
{
	off_t nFileLen = (off_t)GetFileSize();
	return nFileLen - AAsset_seek(m_pFile,0,SEEK_CUR);
}

int FileStream_android::Read( void* buf,uint count )
{
	return AAsset_read(m_pFile,buf,count);
}

NS_CH_END
#endif