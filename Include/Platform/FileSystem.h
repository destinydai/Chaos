#pragma once


NS_CH_BEG

enum FileOpenMode
{
	FILE_OPEN_READ = 1,
	FILE_OPEN_WRITE = 1>>1,

	FILE_OPEN_EXPAND=0xffffffff
};

enum FileSeekFlag
{
	FILE_SEEK_BEG=0,
	FILE_SEEK_CUR=1,
	FILE_SEEK_END=2,
	
	FILE_SEEK_EXPAND=0xffffffff
};

class IFileStream
{
public:
	virtual ~IFileStream(){}
	//����ļ���С
	virtual uint GetFileSize() =0;
	//�ƶ��ļ�ָ��
	virtual uint Seek(uint offset,FileSeekFlag pos) =0;
	//��ȡʣ��Ļ�û��ȡ���ֽ���
	virtual uint GetRemainingLength()=0;
	//��ȡָ�����ֽ���
	virtual int Read(void* buf,uint count)=0;
	//�õ��ļ���չ��
	virtual const char* GetFileExtension()=0;
	//�õ��ļ�����,������չ��
	virtual const char* GetFullFileName() =0;
	//�õ��ļ�������������չ��
	virtual const char* GetFileName() =0;
	//�õ��ļ�������ļ�ϵͳ��·��
	virtual const char* GetFilePath() =0;
	//�õ�����Ŀ¼��·��
	virtual string GetDirectoryPath()=0;
};

class IFileDirectory 
{
public:
	virtual ~IFileDirectory(void){}
	//list all file in sub directory
	virtual void ListAllFiles(StringArray &outArray)=0;
	//list file in current directory
	virtual void ListFiles(StringArray &outArray)=0;
	//list current sub directory
	virtual void ListDirectory(StringArray &outArray)=0;
	//list all sub directory
	virtual void ListAllDirectory(StringArray &outArray)=0;
	//open file  relative to current path
	virtual IFileStream* OpenFile(const char* szRelPath, FileOpenMode mode)=0;
	//get directory path
	virtual const char* GetDirectoryPath() =0;
};

class FileSystem 
{
public:

	static FileSystem* GetInstancePtr();
	//the object returned here should be delete
	virtual IFileDirectory* OpenRootDirectory() =0;
	//get file system root directory path
	virtual const char* GetRootPath() =0;
	//the object returned here should be delete
	virtual IFileDirectory* OpenDirectory(const char* dirName) = 0;
	//open file by path relative to the root path
	virtual IFileStream* OpenFile(const char* szPath, FileOpenMode mode=FILE_OPEN_READ)=0;
	//list all file path in file system
	virtual void ListAllFiles(StringArray &outArray)=0;
	//return all file count in file system
	virtual uint GetSystemFileCount() =0;
	//return all file size in byte
	virtual uint64 GetSystemFileSize() =0;

public://inner use
	virtual void SetAPIContex(void* pParm){}
public:
	//��֤·���Ƿ���һ����Ч���ļ�·��, ����ʾ�ļ��Ƿ����
	static bool IsAbsoluteFilePath(const char* szFilePath);

};


NS_CH_END