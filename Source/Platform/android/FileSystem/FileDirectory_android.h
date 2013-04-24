#pragma once

NS_CH_BEG


class FileDirectory_android : public FileDirectory
{
public:
	FileDirectory_android(const string &szPath,AAssetDir* pDir);
	virtual ~FileDirectory_android(void);

public:// interface
	//list all file in sub directory
	virtual void ListAllFiles(StringArray &outArray);
	//list file in current directory
	virtual void ListFiles(StringArray &outArray);
	//list current sub directory
	virtual void ListDirectory(StringArray &outArray);
	//list all sub directory
	virtual void ListAllDirectory(StringArray &outArray);
	//open file  relative to current path
	virtual IFileStream* OpenFile(const char* szRelPath, FileOpenMode mode);
private:
	AAssetDir* m_pDirectory;
};



NS_CH_END