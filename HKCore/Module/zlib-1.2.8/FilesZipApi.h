#pragma once

#include "../OSInterface/OSInterface.h"

//��ȡָ��Ŀ¼��ָ����չ���������ļ�
void GetFilesInDir(CString strRootDir,CString strDir,CStringArray& strFileArray,CString strPostfix=_T(""),BOOL bRelPath=FALSE);

BOOL FilesZip(CStringArray& strFileArray,const CString& strZipFile,CString strRootDir);//strFileArray:��ѹ���ļ���·�����飻strZipFile:ѹ�����ļ�.zip
BOOL FolderZip(const CString &strDir,const CString& strZipFile);

int FilesUnzip(const CString& strZipFile,const CString& strDestPath,CStringArray& arrUnzipFiles,bool bOverWrite=true);//yyj modofy 20210902


