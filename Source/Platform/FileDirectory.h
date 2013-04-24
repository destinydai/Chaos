#pragma once


NS_CH_BEG

class FileDirectory : public IFileDirectory
{
public:
	FileDirectory(const string &szPath);
	virtual ~FileDirectory(void);

public:// interface 

	//get directory path
	virtual const char* GetDirectoryPath();

protected:
	string m_szDirectoryPath;
};


NS_CH_END