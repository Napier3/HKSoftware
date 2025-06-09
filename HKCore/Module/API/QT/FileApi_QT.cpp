#include "../FileApi.h"
#include "../GlobalConfigApi.h"
#include <stdio.h>
#include "time.h"

#ifdef _PSX_QT_LINUX_
#include "utime.h"
#else
#include "sys/utime.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <QDir>

//将文件的路径写入注册表：传入的参数为文件的绝对路径
void WriteFilePathToRegByFilePathName(const CString &strRoot,const CString &strRegKey,const CString &strPathName)
{
//	CString strPath = GetPathFromFilePathName(strPathName);
//	WriteDataToRegister(strRoot,strRegKey,strPath);
}



BOOL PopupSaveAsFileDialog(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey
						   ,const CString &strFilter,const CString &strPostFix)
{
	return FALSE;
}

BOOL PopupSaveAsFileDialog(CWnd *pParent,CString &strFilePath ,const CString &strFilter,const CString &strPostFix)
{

	return FALSE;
}

BOOL PopupSaveAsFileDialogEx(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey
						   ,const CString &strFilter,const CString &strPostFix,const CString &strDefaultFile)
{
	return FALSE;
}

BOOL PopupOpenFileDialog(CWnd *pParent,CString &strFilePath,const CString &strFilter
						 ,const CString &strPostFix, const CString &strCaption)
{
	return FALSE;
}

BOOL PopupOpenFileDialog(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey
						 ,const CString &strFilter,const CString &strPostFix
						 ,const CString &strCaption)
{
	return FALSE;
}

BOOL PopupOpenFileDialog(CStringArray &vecFiles,const CString &strFilter
						 ,const CString &strPostfix,const CString &strCaption,int nMaxFiles)
{
 	return FALSE;
}

BOOL FGetDirectory(HWND hParent, CString &strPath, const CString &strTitle)
{
	
        return TRUE;
}

BOOL FGetDirectoryA(HWND hParent, CString &strPath, const CString &strTitle)
{

	return TRUE;
}

BOOL FGetDirectory(HWND hParent, wchar_t* szDir, wchar_t* strTitle)
{ 
	
        return TRUE;
} 


BOOL FGetDirectory(HWND hParent, char* szDir, char* strTitle)
{

        return TRUE;
}

CString mkDir(const CString& strDir)
{
    QDir dir(strDir);
    if ( dir.exists(strDir))
    {
            return strDir;
    }

    QString parentDir = mkDir(strDir.mid(0,strDir.lastIndexOf('/')));
	QString dirname = strDir.mid(strDir.lastIndexOf('/') + 1);

    QDir parentPath(parentDir);

    if ( !dirname.isEmpty() )
    {
            parentPath.mkpath(dirname);
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
    }

    return parentDir + "/" + dirname;
}

void CreateAllDirectories(CString strDir)
{
    mkDir(strDir);
}

BOOL DeleteAllDirectorys(const CString &strDirName, BOOL bDelOwn)
{
	//add by yyj at 20201019 begin
	QDir directory(strDirName);
	if (!directory.exists())
	{
		return true;
	}

	QString srcPath = QDir::toNativeSeparators(strDirName);
	if (!srcPath.endsWith(QDir::separator()))
		srcPath += QDir::separator();


	QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
	bool error = false;
	for (QStringList::size_type i=0; i != fileNames.size(); ++i)
	{
		QString filePath = srcPath + fileNames.at(i);
		QFileInfo fileInfo(filePath);
		if (fileInfo.isFile() || fileInfo.isSymLink())
		{
			QFile::setPermissions(filePath, QFile::WriteOwner);
			if (!QFile::remove(filePath))
			{
				error = true;
			}
            else
            {
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
            }
		}
		else if (fileInfo.isDir())
		{
			if (!DeleteAllDirectorys(fileInfo.absoluteFilePath()))
			{
				error = true;
			}
		}
	}

	if(bDelOwn)
	{
		if (!directory.rmdir(QDir::toNativeSeparators(directory.path())))
		{
			error = true;
		}
        else
        {
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
        }
	}

	return !error;
	//add by yyj at 20201019 end
}

BOOL DeleteAllFiles(const CString &strDirName, const CString &strFileType)
{
	//add by yyj at 20200416 begin
	if (strDirName.isEmpty())
	{
		return false;
	}

	long nCount = 0;
	long nLen = strDirName.GetLength();
	CString strFileNeedFind; 
	strFileNeedFind = strDirName;
	if (strDirName[nLen-1] != '//')
	{
		strFileNeedFind = strFileNeedFind + _T("//");
	}

	QDir dir(strDirName);
	if(!dir.exists())
	{
		 return true;
	}

	dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
	QFileInfoList fileList = dir.entryInfoList();
	foreach (QFileInfo file, fileList)
	{
	   if (file.isFile())
	   {
		  file.dir().remove(file.fileName());
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif
		  nCount++;
	   }
	}

	return nCount > 0;
	//add by yyj at 20200416 end
}

void ClearFileReadOnlyAttr(const CString &strFile)
{
	//add by yyj at 20200416 begin
	if(QFile::exists(strFile))
	{
		QFile file(strFile);
		file.setPermissions(strFile,QFile::ReadOther|QFile::WriteOther);
	}
	//add by yyj at 20200416 end
}

int file_size2(const CString &strFile)
{
	//add by yyj at 20200416 begin
	QFileInfo fileInfo(strFile);
	if (!fileInfo.exists())
	{
    return 0;
	}

	return fileInfo.size();
	//add by yyj at 20200416 end
}

long file_GetFileSize(const CString &strFile)
{
	return file_size2(strFile);
}

void file_get_time(const CString &strFile, CString &strTime)
{
	//add by yyj at 20200416 begin
	QFileInfo fileInfo(strFile);
	if (!fileInfo.exists())
	{
		return;
	}

	QDateTime dateTime = fileInfo.lastModified();
	QDate date = dateTime.date();
	QTime time = dateTime.time();

	strTime.Format(_T("%d-%d-%d %d:%d:%d"), date.year(), date.month(), date.day(), time.hour(), time.minute(), time.second());
	//add by yyj at 20200416 end
}

CString file_get_time(const CString &strFile)
{
    CString strTime;
    file_get_time(strFile, strTime);
    return strTime;
}

CString file_get_time(const char* pstrFile)
{
	CString strTime;
	file_get_time((CString)pstrFile, strTime);
	return strTime;
}

void file_set_time(HANDLE hFile,SYSTEMTIME &tm)
{
// 	ASSERT(hFile != INVALID_HANDLE_VALUE);
// 
// 	FILETIME ft,ft1;
// 	SystemTimeToFileTime(&tm, &ft);
// 	LocalFileTimeToFileTime(&ft,&ft1); 
// 	SetFileTime(hFile, NULL, NULL, &ft1);
}

void file_set_time(const CString& strFile,SYSTEMTIME &tm)
{
	struct tm tma = {0};
	tma.tm_year = tm.wYear-1900;
	tma.tm_mon = tm.wMonth-1;
	tma.tm_mday = tm.wDay;
	tma.tm_hour = tm.wHour;
	tma.tm_min = tm.wMinute;
	tma.tm_sec = tm.wSecond;
	tma.tm_isdst = 0;
#ifndef _PSX_QT_LINUX_
	struct _utimbuf ut;
#else
	struct utimbuf ut;
#endif
	ut.modtime = mktime(&tma);
	ut.actime=mktime(&tma);
	QByteArray ary = strFile.toLocal8Bit();
	char *fileName = ary.data();

	int result=-1;
#ifndef _PSX_QT_LINUX_
	result=_utime(fileName, &ut );
#else
	result=utime(fileName, &ut );
#endif
}

//add by yyj at 20200416 begin
void file_set_time(const CString& strFile,unsigned long uTime)
{
	QDateTime dateTime;
	dateTime.setTime_t(uTime);
	struct tm tma = {0};
	tma.tm_year = dateTime.date().year()-1900;
	tma.tm_mon = dateTime.date().month()-1;
	tma.tm_mday = dateTime.date().day();
	tma.tm_hour = dateTime.time().hour();
	tma.tm_min = dateTime.time().minute();
	tma.tm_sec = dateTime.time().second();
	tma.tm_isdst = 0;
#ifndef _PSX_QT_LINUX_
	struct _utimbuf ut;
#else
	struct utimbuf ut;
#endif
	ut.modtime = mktime(&tma);
	ut.actime=mktime(&tma);
	QByteArray ary = strFile.toLocal8Bit();
	char *fileName = ary.data();

	int result=-1;
#ifndef _PSX_QT_LINUX_
	result=_utime(fileName, &ut );
#else
	result=utime(fileName, &ut );
#endif
}
//add by yyj at 20200416 end

void GetRelativePathTo(const CString &strFrom, const CString &strTo, CString &strOut)
{

}

void GetPathFromRelative(const CString &strFrom, const CString &strFile, CString &strOut)
{

}

BOOL ValidateFileName(CString &strFileName)
{
	if (strFileName.Find((CString)_T("\\")) >= 0)
		return FALSE;

	if (strFileName.Find((CString)_T("/")) >= 0)
		return FALSE;

	if (strFileName.Find((CString)_T(":")) >= 0)
		return FALSE;

	if (strFileName.Find((CString)_T("*")) >= 0)
		return FALSE;

	if (strFileName.Find((CString)_T("?")) >= 0)
		return FALSE;

	if (strFileName.Find((CString)_T("<")) >= 0)
		return FALSE;

	if (strFileName.Find((CString)_T(">")) >= 0)
		return FALSE;

	if (strFileName.Find((CString)_T("|")) >= 0)
		return FALSE;

	if (strFileName.Find((CString)_T("\"")) >= 0)
		return FALSE;
	return TRUE;
}

BOOL IsFileExist(const CString &strFile)
{
	if (strFile.GetLength() < 3)
	{
		return FALSE;
	}

    bool bRet = false;

#ifdef _PSX_QT_LINUX_
    //yzj 2024.2.2 解决linux下保存文件中文乱码问题
    QTextCodec *pOldTextCodec = NULL;
    InitLocalCodec_BeforeReadWrite(strFile, &pOldTextCodec);
    bRet = QFile::exists(strFile);
    ResetLocalCodec(pOldTextCodec);
#else
    bRet = QFile::exists(strFile);
#endif
     return bRet;
}

BOOL X_CopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists)
{
	//add by yyj at 20200416 begin
	CString strSrcPath = GetPathFromFilePathName(strSrcFile,_T('//'));
	CString strDestPath = GetPathFromFilePathName(strDestFile,_T('//'));

	if(strSrcFile == strDestFile)
	{
		return TRUE;
	}

	if(!QFile::exists(strSrcFile))
	{
		return FALSE;
	}

	if(bFailIfExists && QFile::exists(strDestFile))
	{
		return FALSE;
	}

	QDir* newDir = new QDir;
	bool bExist = newDir->exists(strDestPath);
	if(!bExist)
	{
		if(!newDir->mkdir(strDestPath))
		{
			return FALSE;
		}
	}

    QFile::remove(strDestFile);//???????
	if(!QFile::copy(strSrcFile, strDestFile))
	{
		return FALSE;
	}

#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
                system("sync");
#endif

	return TRUE;
	//add by yyj at 20200416 end
}

BOOL X_DeleteFile(const CString &strFile)
{
	BOOL bRet = FALSE;
	//add by yyj at 20200416 begin
	QFileInfo fileInfo(strFile);
	if(!fileInfo.exists())
	{
		bRet = TRUE;
	}

#ifdef _PSX_QT_LINUX_
	QTextCodec *pOldTextCodec = NULL;
        InitLocalCodec_BeforeReadWrite(strFile,&pOldTextCodec);
#endif

	bRet = fileInfo.dir().remove(fileInfo.fileName());
#ifdef _PSX_QT_LINUX_  //20220509 zhouhj  linux下写文件后,需要进行同步操作
         system("sync");
	 ResetLocalCodec(pOldTextCodec);
#endif
//	 if (!bRet)
//	 {
//		 CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("文件(%s)删除失败."),strFile.GetString());
//	 }
	//add by yyj at 20200416 end
	return bRet;
}

BOOL GetFileVersion(const CString &filePath,unsigned int &nFileVersionMS,  
					unsigned int &nFileVersionLS)  
{  

	return TRUE;  
} 

BOOL GetFileVersion(const CString& strFile,CString &strVersion)
{

	return FALSE;
}

