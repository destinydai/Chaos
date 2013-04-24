#pragma once

NS_CH_BEG

class FileStream : public IFileStream
{
public:
	FileStream(const string &szPath);
	virtual ~FileStream(void);

public: // interface 
	virtual const char* GetFileExtension();

	virtual const char* GetFullFileName();

	virtual const char* GetFileName();

	virtual const char* GetFilePath();

	virtual string GetDirectoryPath();
	 
private:
	string m_szFilePath;
	string m_szFileName;
};


NS_CH_END