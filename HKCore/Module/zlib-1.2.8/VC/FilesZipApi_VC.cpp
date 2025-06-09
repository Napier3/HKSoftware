// FilesZipApi_VC.cpp : 实现文件
//

#include "../FilesZipApi.h"
#include "../contrib/minizip/zip.h"
#include "../contrib/minizip/unzip.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/StringApi.h"

#include <io.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//获取指定目录下指定扩展名的所有文件
void GetFilesInDir(CString strRootDir,CString strDir,CStringArray& strFileArray,CString strPostfix,BOOL bRelPath)
{
	ASSERT(!strRootDir.IsEmpty());
	ASSERT(!strDir.IsEmpty());

	if (strPostfix.IsEmpty())
	{
		strPostfix = _T("*");
	}

	if(strRootDir.Right(1) == _T("\\") || strRootDir.Right(1) == _T("//"))
	{
		strRootDir = strRootDir.Left(strRootDir.GetLength()-1);
	}

	if(strDir.Right(1) == _T("\\") || strDir.Right(1) == _T("//"))
	{
		strDir = strDir.Left(strDir.GetLength()-1);
	}

	long nCutOffPos = 0;
	if (bRelPath)
	{
		nCutOffPos = strRootDir.GetLength() + 1;
	}

	CString strFilePath,strFindFile;
	CString strRelPath;

	CFileFind oFileFind;
	
	strFindFile.Format(_T("%s\\*.%s"),strDir,strPostfix);
	BOOL bFind=oFileFind.FindFile(strFindFile);

	while(bFind)
	{
		bFind = oFileFind.FindNextFile();

		//每个文件夹下都有两个默认的文件夹，用来指示当前目录或者上一级目录，
		//其中"."表示当前目录，".."表示上一级目录，遍历文件夹时要排除这两个文件夹

		if (!oFileFind.IsDots())
		{
			strFilePath = oFileFind.GetFilePath();

			strRelPath = strFilePath.Mid(nCutOffPos);

			//判断当前文件是否是一个文件夹，如果是文件夹则进行迭代
			if (oFileFind.IsDirectory())
			{
				GetFilesInDir(strRootDir,strFilePath,strFileArray,strPostfix,bRelPath);
			}
			else
			{
				strFileArray.Add(strRelPath);
			}
		}
	}

	oFileFind.Close();
}

//获取指定文件的修改时间
void GetFileModifiedTime(const CString& strFilePath,zip_fileinfo& fileInfo)
{
	struct _stat64i32 statbuf;    
#ifdef _UNICODE
	_wstat(strFilePath,&statbuf);    
#else
	BSTR bstrFile = strFilePath.AllocSysString();
	_wstat(bstrFile, &statbuf); 
	::SysFreeString(bstrFile);
	fileInfo.dosDate = statbuf.st_mtime;
#endif

}

BOOL FilesZip(CStringArray& strFileArray,const CString& strZipFile,CString strRootDir)
{
	if(strFileArray.GetCount()==0 || strZipFile.IsEmpty())
	{
		return FALSE;
	}

	if(strRootDir.Right(1) == _T("\\"))
	{
		strRootDir = strRootDir.Left(strRootDir.GetLength()-1);
	}

	//创建压缩流
	zipFile zf = NULL;

	USES_CONVERSION; 
	zf = zipOpen((LPCSTR)T2A((LPTSTR)(LPCTSTR)strZipFile),0);

	//压缩文件
	zip_fileinfo FileInfo; 
	ZeroMemory(&FileInfo, sizeof(FileInfo));

	for(int i=0;i<strFileArray.GetCount();i++)
	{
		CString strFilePath = strFileArray.GetAt(i);

		//取得文件的时间信息
        ZeroMemory(&FileInfo, sizeof(FileInfo));
		CString strFileTotalPath = strRootDir + _T("\\") + strFilePath;
		GetFileModifiedTime(strFileTotalPath,FileInfo);

		zipOpenNewFileInZip(zf, (LPCSTR)T2A((LPTSTR)(LPCTSTR)strFilePath)
			, &FileInfo, NULL, 0, NULL, 0, NULL,Z_DEFLATED, Z_DEFAULT_COMPRESSION);

		strFilePath = strRootDir + _T("\\") + strFilePath;

		CFile zpFile;
		if(!zpFile.Open(strFilePath,CFile::modeReadWrite))
		{
			zipCloseFileInZip(zf);
			continue;
		}

		ULONGLONG size = zpFile.GetLength();
		void* pData = malloc(size);
		zpFile.Read(pData,(UINT)size);
		zipWriteInFileInZip(zf,pData,size);
		zipCloseFileInZip(zf);
		free(pData);
	}

	//关闭流
	zipClose(zf,0);
	return TRUE;
}

int FilesUnzip(const CString& strZipFile,const CString& strDestPath,CStringArray& arrUnzipFiles,bool bOverWrite)//strZipFile:zip压缩文件完整路径
{
	ASSERT(!strDestPath.IsEmpty());
	arrUnzipFiles.RemoveAll();

	int rv = UNZ_ERRNO;
	unzFile uzf=NULL;
	unz_global_info global_info;
	unz_file_info file_info;

	CString strDestRootPath = strDestPath;
	if(strDestRootPath.Right(1) != _T("\\"))
	{
		strDestRootPath = strDestRootPath + _T("\\");
	}

	USES_CONVERSION;
	uzf = unzOpen((LPCSTR)T2A((LPTSTR)(LPCTSTR)strZipFile));

	if(uzf==NULL)
	{
		return rv;
	}

	rv = unzGetGlobalInfo(uzf, &global_info);
	if (rv != UNZ_OK)
	{
		return rv;
	}

	rv = unzGoToFirstFile(uzf);
	if (rv != UNZ_OK)
	{
		return rv;
	}

	for(int i=0; i<global_info.number_entry; ++i)
	{
		char szFileName[MAX_PATH]={0};
		char chExtraField[255]={0};
		char szComment[255]={0};

		rv = unzGetCurrentFileInfo(uzf, &file_info, szFileName, MAX_PATH, chExtraField, sizeof(chExtraField), szComment, sizeof(szComment));  
		if(rv != UNZ_OK)
		{
			break;
		}

		for(int j=0; szFileName[j]; j++) 
		{ 
			if(szFileName[j]=='/') 
			{
				szFileName[j]='\\';
			}
		} 
		rv = unzOpenCurrentFile(uzf);			  //无密码
		//		rv = unzOpenCurrentFilePassword(uzf,NULL);//有密码
		if(rv != UNZ_OK)
		{
			break;
		}

		//读取内容
		void *pData = malloc(file_info.uncompressed_size);
		if(!pData)
		{
			unzCloseCurrentFile(uzf);
			break;
		}

		UINT size = file_info.uncompressed_size;
		int sizeRead = unzReadCurrentFile(uzf,pData,size);
		if(sizeRead!= size)
		{
			unzCloseCurrentFile(uzf);
			free(pData);
			break;
		}

		//创建解压后的文件
		CString strFileName = A2T(szFileName);
		CString strUnzipFilePath,strUnzipFile;

		if (strFileName.Left(1)== _T("\\"))
		{
			strUnzipFile = strFileName.Mid(1);
		}

		strUnzipFile = strDestRootPath + strFileName;
		strUnzipFilePath = GetPathFromFilePathName(strUnzipFile);

		CreateAllDirectories(strUnzipFilePath);

		//yyj modify 20210902
		if (bOverWrite == true || (bOverWrite == false && !IsFileExist(strUnzipFile)))
		{
			CFile file;
			if(file.Open(strUnzipFile,CFile::modeCreate|CFile::modeReadWrite))
			{
				file.Write(pData,size);
				file.Close();
			}

			SetFileModifiedTime(strUnzipFile,file_info);
		}

		free(pData);

		arrUnzipFiles.Add(strUnzipFile);

		//关闭当前文件
		rv = unzCloseCurrentFile(uzf);
		if(rv != UNZ_OK)
		{
			break;
		}

		rv = unzGoToNextFile(uzf);
		if(rv != UNZ_OK)
		{
			break;
		}
	}

	//关闭流
	unzClose(uzf);

	return UNZ_OK;
}