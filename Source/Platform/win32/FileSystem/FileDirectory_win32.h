#pragma once


NS_CH_BEG

class FileDirectory_win32 : public FileDirectory
{
public:
	FileDirectory_win32(const string& szPath);
	virtual ~FileDirectory_win32(void);
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
};


NS_CH_END