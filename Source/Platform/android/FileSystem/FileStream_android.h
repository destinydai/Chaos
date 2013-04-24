#pragma once


NS_CH_BEG

class FileStream_android : public FileStream
{
public:
	FileStream_android(const string &szPath,AAsset* pAsset);
	virtual ~FileStream_android(void);

public:// interface
	virtual uint GetFileSize();

	virtual uint Seek(uint offset,FileSeekFlag pos);

	virtual uint GetRemainingLength();

	virtual int Read(void* buf,uint count);

	
private:
	AAsset* m_pFile;
};


NS_CH_END