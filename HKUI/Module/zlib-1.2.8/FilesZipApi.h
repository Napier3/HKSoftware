#pragma once

#include "../OSInterface/OSInterface.h"

//获取指定目录下指定扩展名的所有文件
void GetFilesInDir(CString strRootDir,CString strDir,CStringArray& strFileArray,CString strPostfix=_T(""),BOOL bRelPath=FALSE);

BOOL FilesZip(CStringArray& strFileArray,const CString& strZipFile,CString strRootDir);//strFileArray:被压缩文件的路径数组；strZipFile:压缩包文件.zip
BOOL FolderZip(const CString &strDir,const CString& strZipFile);

int FilesUnzip(const CString& strZipFile,const CString& strDestPath,CStringArray& arrUnzipFiles,bool bOverWrite=true);//yyj modofy 20210902


