// FilesZipApi.cpp : ʵ���ļ�
//

#include "../FilesZipApi.h"
#include "../contrib/minizip/zip.h"
#include "../contrib/minizip/unzip.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/StringApi.h"

#include <sys/io.h>
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//��ȡָ��Ŀ¼��ָ����չ���������ļ�
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

	QFileInfoList InfoList = QDir(strDir).entryInfoList();
	
	foreach(QFileInfo fileInfo, InfoList)
	{
		strFilePath = fileInfo.absoluteFilePath();

		strRelPath = strFilePath.Mid(nCutOffPos);

		if(fileInfo.isDir()) 
		{
			GetFilesInDir(strRootDir,strFilePath,strFileArray,strPostfix,bRelPath);
		}
		
		if (fileInfo.isFile() && fileInfo.suffix().compare(strPostfix,Qt::CaseInsensitive)==0)
		{
			strFileArray.Add(strRelPath);
		}
	}
}

//��ȡָ���ļ����޸�ʱ��
void GetFileModifiedTime(const CString& strFilePath,zip_fileinfo& fileInfo)
{
	QFileInfo fileInf(strFilePath);
	QDateTime dateTime = fileInf.lastModified();
	fileInfo.dosDate = dateTime.toTime_t();
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

	//����ѹ����
	zipFile zf = NULL;
	char* pstrZipFile;
	CString_to_char(strZipFile,pstrZipFile);
	zf = zipOpen(pstrZipFile,0);
	delete pstrZipFile;

	//ѹ���ļ�
	zip_fileinfo FileInfo; 
	ZeroMemory(&FileInfo, sizeof(FileInfo));

	for(int i=0;i<strFileArray.GetCount();i++)
	{
		CString strFilePath = strFileArray.GetAt(i);

		//ȡ���ļ���ʱ����Ϣ
		CString strFileTotalPath = strRootDir + _T("\\") + strFilePath;
		GetFileModifiedTime(strFileTotalPath,FileInfo);

		char* pstrFilePath;
		CString_to_char(strFilePath,pstrFilePath);
		zipOpenNewFileInZip(zf, pstrFilePath, &FileInfo, NULL, 0, NULL, 0, NULL,Z_DEFLATED, Z_DEFAULT_COMPRESSION);
		delete pstrFilePath;

		strFilePath = strRootDir + _T("\\") + strFilePath;

		CFile zpFile;
		if(!zpFile.Open(strFilePath,CFile::modeReadWrite))
		{
			zipCloseFileInZip(zf);
			continue;
		}

		__uint64 size = zpFile.GetLength();
		void* pData = malloc(size);
		zpFile.Read(pData,(UINT)size);
		zipWriteInFileInZip(zf,pData,size);
		zipCloseFileInZip(zf);
		free(pData);
	}

	//�ر���
	zipClose(zf,0);
	return TRUE;
}


int FilesUnzip(const CString& strZipFile,const CString& strDestPath,CStringArray& arrUnzipFiles,bool bOverWrite)//strZipFile:zipѹ���ļ�����·��
{
	ASSERT(!strDestPath.IsEmpty());

	int rv = UNZ_ERRNO;
	unzFile uzf=NULL;
	unz_global_info global_info;
	unz_file_info file_info;

	CString strDestRootPath = strDestPath;
	if(strDestRootPath.Right(1) != _T("/"))
	{
		strDestRootPath = strDestRootPath + _T("/");
	}

	char* pstrZipFile;
	CString_to_char(strZipFile,&pstrZipFile);
	uzf = unzOpen(pstrZipFile);
	delete pstrZipFile;

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

		rv = unzOpenCurrentFile(uzf);			  //������
//		rv = unzOpenCurrentFilePassword(uzf,NULL);//������
		if(rv != UNZ_OK)
		{
			break;
		}

		//��ȡ����
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

		//������ѹ����ļ�
		for(int j=0; szFileName[j]; j++)
		{
			if(szFileName[j]=='\\')
			{
				szFileName[j]='/';
			}
		}

		const QByteArray qarrFileName(szFileName);
		QTextCodec* codec = QTextCodec::codecForName("gb2312");
		CString strFileName = codec->toUnicode(qarrFileName);
		if(strFileName.Left(1) == "//")
			strFileName.remove(0,1);

		if(strFileName.Right(1) == _T("/"))
		{
			//�رյ�ǰ�ļ�
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

			continue;
		}

		CString strUnzipFilePath,strUnzipFile;

		strUnzipFile = strDestRootPath + strFileName;
		strUnzipFilePath = GetPathFromFilePathName(strUnzipFile,_T('/'));
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

		//�رյ�ǰ�ļ�
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

	//�ر���
	unzClose(uzf);

	return UNZ_OK;
}



