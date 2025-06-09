// FilesZipApi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FilesZipApi.h"
#include "contrib/minizip/zip.h"
#include "contrib/minizip/unzip.h"
#include "../../Module/API/FileApi.h"
#include "../../Module/API/StringApi.h"

BOOL FolderZip(const CString &strDir,const CString& strZipFile)
{
	ASSERT(!strDir.IsEmpty());
	ASSERT(!strZipFile.IsEmpty());

	CStringArray strFileArray;
	//��ȡָ��Ŀ¼��ָ����չ��չ���������ļ�
	GetFilesInDir(strDir,strDir,strFileArray,_T("*"),TRUE);

	if (strFileArray.GetCount() == 0)
	{
		return FALSE;
	}

	return FilesZip(strFileArray,strZipFile,strDir);
}

void SetFileModifiedTime(const CString& strUnzipFile,unz_file_info& unzipFileInfo)
{
	file_set_time(strUnzipFile,unzipFileInfo.dosDate);
}

#ifndef _PSX_IDE_QT_
#include "VC/FilesZipApi_VC.cpp"
#else
#include "QT/FilesZipApi_QT.cpp"
#endif