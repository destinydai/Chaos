#pragma once


NS_CH_BEG

class FileSystem_android : public FileSystem
{
public:
	FileSystem_android(void);
	virtual ~FileSystem_android(void);

public: // interface

	virtual IFileDirectory* OpenRootDirectory();

	virtual const char* GetRootPath();

	virtual IFileDirectory* OpenDirectory(const char* dirName) ;

	virtual IFileStream* OpenFile(const char* szPath, FileOpenMode mode);

	virtual void ListAllFiles(StringArray &outArray);

	virtual uint GetSystemFileCount();

	virtual uint64 GetSystemFileSize();

	virtual void SetAPIContex(void* pParm) { m_pMgr = (AAssetManager*)pParm;  } 

public:
	static AAssetManager* GetAssetManager() { return m_pMgr; }

public:
	static AAssetManager* m_pMgr;
};

NS_CH_END