#pragma once


NS_CH_BEG

class FileSystem_win32 : public FileSystem
{
public:
	FileSystem_win32(void);
	virtual ~FileSystem_win32(void);

public: // interface
	virtual IFileDirectory* OpenRootDirectory();

	virtual const char* GetRootPath();

	virtual IFileDirectory* OpenDirectory(const char* dirName) ;

	virtual IFileStream* OpenFile(const char* szPath, FileOpenMode mode);

	virtual void ListAllFiles(StringArray &outArray);

	virtual uint GetSystemFileCount();

	virtual uint64 GetSystemFileSize();

public:// inner use
	static void ScanFolder(StringArray* _resultFiles,StringArray* _resultDirectorys, const string& _folder, bool _recursive, bool _fullpath);
private:
	string m_szExeFolderPath;
};


NS_CH_END