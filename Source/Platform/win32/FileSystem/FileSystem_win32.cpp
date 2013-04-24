#include "stdafx.h"


NS_CH_BEG

FileSystem_win32::FileSystem_win32( void )
{
	CHAR buffer[CH_BUFSIZE];
	DWORD dwSize = GetModuleFileNameA(NULL,buffer,CH_BUFSIZE * sizeof(CHAR));
	CH_ASSERT(dwSize != 0 && dwSize < CH_BUFSIZE * sizeof(CHAR));

	string szBuf(buffer);
	int nPos = szBuf.rfind("\\");
	if(nPos==-1)
	{
		CH_ERROR("[pl] error: exe path error.");
		return;
	}

	m_szExeFolderPath = string(&szBuf[0],&szBuf[nPos+1]);

	for(uint i=0; i<m_szExeFolderPath.size(); ++i)
	{
		if(m_szExeFolderPath[i] == '\\')
		{
			m_szExeFolderPath[i]='/';
		}
	}

}

FileSystem_win32::~FileSystem_win32( void )
{

}

void FileSystem_win32::ScanFolder(StringArray* _resultFiles,StringArray* _resultDirectorys, const string& _folder, bool _recursive, bool _fullpath)
{
	if(_folder.size() == 0)
	{
		CH_ERROR("[pl] error:没有指定要收索的文件夹");
	}

	string folder = _folder;

	if(folder[folder.size()-1] != '/')
	{
		folder += "/";
	}

	vector<string> dir;

	WIN32_FIND_DATAA FindData;
	HANDLE file = FindFirstFileA((folder + "*").c_str(), &FindData);
	if (file != INVALID_HANDLE_VALUE)
	{
		do
		{
			string name = FindData.cFileName;
			if ((name == ".") || (name == "..")) 
				continue;

			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) 
				continue;

			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(_resultDirectorys!=nullptr)
				{
					if(_fullpath)
					{
						_resultDirectorys->push_back(folder + name);
					}
					else
					{
						_resultDirectorys->push_back(name);
					}
				}

				dir.push_back(folder + name);
			}
			else
			{
				if(_resultFiles!=nullptr)
				{
					if (_fullpath)
					{
						_resultFiles->push_back(folder + name);
					}
					else
					{
						_resultFiles->push_back(name);
					}
				}

			}

		}while (FindNextFileA(file, &FindData));
	}
	FindClose(file);

	if (_recursive)
	{
		for (vector<string>::iterator iter = dir.begin(); iter!=dir.end(); ++iter)
		{
			ScanFolder(_resultFiles,_resultDirectorys, *iter, _recursive, _fullpath);
		}
	}
}

IFileDirectory* FileSystem_win32::OpenRootDirectory()
{
	return OpenDirectory(m_szExeFolderPath.c_str());
}

const char* FileSystem_win32::GetRootPath()
{
	return "";
}

IFileDirectory* FileSystem_win32::OpenDirectory( const char* dirName )
{
	DWORD dwAttrib = GetFileAttributesA(dirName);

	if(dwAttrib != INVALID_FILE_ATTRIBUTES && 
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
	{
		return new FileDirectory_win32(dirName);
	}

	return nullptr;
}

IFileStream* FileSystem_win32::OpenFile( const char* szPath, FileOpenMode mode )
{
	string rootPath(FileSystem::GetInstancePtr()->GetRootPath());
	string szFilePath = rootPath + string(szPath);

	DWORD dwAccess = 0;
	if(mode & FILE_OPEN_READ)
	{
		dwAccess |= GENERIC_READ;
	}
	if(mode & FILE_OPEN_WRITE)
	{
		dwAccess |= GENERIC_WRITE;
	}

	HANDLE hFile = CreateFileA(szFilePath.c_str(),dwAccess,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		return nullptr;
	}
	FileStream_win32* pFile = new FileStream_win32(szPath,hFile);
	return pFile;
}

void FileSystem_win32::ListAllFiles( StringArray &outArray )
{
	ScanFolder(&outArray,0,m_szExeFolderPath,true,true);
}

uint FileSystem_win32::GetSystemFileCount()
{
	CH_ERROR("[pl] error: not implement yet");
	return 0;
}

uint64 FileSystem_win32::GetSystemFileSize()
{
	CH_ERROR("[pl] error: not implement yet")
	return 0;
}

NS_CH_END