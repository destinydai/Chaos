#pragma once


NS_CH_BEG

class FileStream_win32 : public FileStream
{
public:
	FileStream_win32(const string& szPath,HANDLE hFile);
	virtual ~FileStream_win32(void);

public:// interface
	virtual uint GetFileSize();

	virtual uint Seek(uint offset,FileSeekFlag pos);

	virtual uint GetRemainingLength();

	virtual int Read(void* buf,uint count);
private:
	HANDLE m_hFile;
};


NS_CH_END