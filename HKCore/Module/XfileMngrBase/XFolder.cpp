#include "stdafx.h"
#include "XFolder.h"
#include "XFileMngr.h"
#include "../MemBuffer/BufferBase.h"

#include "XFileFindEx.h"

#ifdef _PSX_IDE_QT_
#include <QDir>
// #include <strings.h>
// using namespace std;
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXFolder::CXFolder()
{
	m_bIsYun = FALSE;
	m_bHasSearched = FALSE;
	m_pYunFolder = NULL;
}

CXFolder::~CXFolder()
{
	if (m_pYunFolder != NULL)
	{
		delete m_pYunFolder;
		m_pYunFolder = NULL;
	}
}


BOOL CXFolder::DeleteAllInFolder()
{
	//查找是否有打开的文件
	if(CheckFileOpen())
	{
		return FALSE;
	}

	CXFolder* pParent = (CXFolder*)this->GetParent();

	if(pParent != NULL)
	{
		DeleteAllDirectorys(this->GetFolderPath());
		pParent->Delete(this);

		return TRUE;
	}

	return FALSE;
}

BOOL CXFolder::CheckFileOpen()
{
	POS pos = this->GetHeadPosition();
	BOOL bFlag = FALSE;

	CExBaseObject* pObj = NULL;
	while(pos != NULL)
	{
		pObj = this->GetNext(pos);
		if(xfile_IsFile(pObj->GetClassID()))
		{
			CXFile* pFile = (CXFile*)pObj;
			if(pFile->m_bIsOpen)
			{
				bFlag = TRUE;
				return bFlag;
			}
		}
		else if(xfile_IsFolder(pObj->GetClassID()))
		{
			CXFolder* pFolder = (CXFolder*)pObj;
			bFlag = pFolder->CheckFileOpen();
			if(bFlag)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CXFolder::RenameFolder(const CString& strNewName)
{
	if (strNewName == m_strName)
	{
		return FALSE;
	}

	CXFolder *pParent = (CXFolder*)GetParent();
	CString strDestPath = pParent->m_strPath + strNewName;
	CString strSrcPath = m_strPath;

	if (strSrcPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
		strSrcPath=strSrcPath.Left(strSrcPath.GetLength() - 1);
	}

#ifdef _UNICODE
	int nRet = _wrename(strSrcPath, strDestPath);
#else
	char* pstrSrcPath,*pstrDestPath;
	CString_to_char(strSrcPath, &pstrSrcPath);
	CString_to_char(strDestPath, &pstrDestPath);
	int nRet = rename(pstrSrcPath, pstrDestPath);
	delete pstrSrcPath;
	delete pstrDestPath;
#endif

	if (nRet == 0)//IsFileExist(strDestPath))
	{
		m_strName = strNewName;
		m_strID = strNewName;
		m_strPath = strDestPath;
		return TRUE;
	}
	else
	{
		return FALSE;
	}


	return FALSE;
}

CXFolder* CXFolder::AddFolderByPath(const CString &strRelPath)
{
	CXFolder *pNew = NULL;
	CXFolder *pFind = NULL;
#ifndef _PSX_IDE_QT_
	long nPos = strRelPath.Find('\\');

	if (nPos < 0)
	{
		nPos = strRelPath.Find('/');

		if (nPos < 0)
		{
			nPos = strRelPath.Find('$');
		}
	}
#else
	long nPos = strRelPath.indexOf('\\');

	if (nPos < 0)
	{
		nPos = strRelPath.indexOf('/');

		if (nPos < 0)
		{
			nPos = strRelPath.indexOf('$');
		}
	}
#endif

	if (nPos < 0)
	{
		if (strRelPath.GetLength() == 0)
		{
			return NULL;
		}
		else
		{
			pFind = (CXFolder *)FindFolder(strRelPath);

			if (pFind == NULL)
			{
				pFind = AddFolder(strRelPath, TRUE);
			}

			return pFind;
		}
	}
	else
	{
		CString strFolder = strRelPath.Left(nPos);
		pFind = (CXFolder *)FindFolder(strFolder);

		if (pFind == NULL)
		{
			pFind = AddFolder(strFolder, TRUE);
		}

		strFolder = strRelPath.Mid(nPos + 1);

		if (strFolder.GetLength() > 0)
		{
			pFind = pFind->AddFolderByPath(strFolder);
		}

		return pFind;
	}
}


CXFile* CXFolder::AddFile(const CString& strFileName,BOOL bOverWrite)
{
	if(bOverWrite)
	{
		CXFile* pFileOld = (CXFile*)FindByLowerName(strFileName);

		//mym 2020-12-5 add 判断是否为空；
		if (pFileOld != NULL)
		{
			ASSERT(pFileOld != NULL);
			Delete(pFileOld);
		}
	}
	
	CXFile* pFile = new CXFile();
	pFile->m_strName = strFileName;
	pFile->m_strID = pFile->m_strName;
	AddTail(pFile);
	pFile->SetParent(this);
	
	return pFile;
}

BOOL CXFolder::IsFileExist(const CString& strFilePath)
{
	CString strName = GetLastFolderNameFromPathName(strFilePath);

	return (FindByID(strName) != NULL);
}

CXFile* CXFolder::AddFile(const CString& strFilePath)
{
	CString strName = GetLastFolderNameFromPathName(strFilePath);

	CXFile* pFile = new CXFile();
	pFile->m_strName = strName;
	pFile->m_strID = pFile->m_strName;
	pFile->m_strFileType = _T("");
	AddTail(pFile);
	pFile->SetParent(this);

	CString strDestFile = pFile->GetRelativePath(TRUE);

	//::X_CopyFile(strFilePath, strDestFile, FALSE);
	XCopyFile(strFilePath, strDestFile, FALSE);

	return pFile;
}

CXFile* CXFolder::AddFile2(const CString& strFile)
{
	CXFile* pFile = new CXFile();
	pFile->m_strName = strFile;
	pFile->m_strID = pFile->m_strName;
	pFile->m_strFileType = _T("");
	AddTail(pFile);
	pFile->SetParent(this);

	return pFile;
}

CXFile* CXFolder::OverWriteFile(const CString& strFilePath)
{
	CString strName = GetLastFolderNameFromPathName(strFilePath);
	CXFile* pFile = (CXFile*)FindByID(strName);

	if (pFile != NULL)
	{
		CString strDestFile = pFile->GetRelativePath(TRUE);
		//::X_CopyFile(strFilePath, strDestFile, FALSE);
		XCopyFile(strFilePath, strDestFile, FALSE);
	}

	return pFile;
}


CXFile* CXFolder::AddFile(CXFile *pSrcFile)
{
	CXFile *pNewFile = (CXFile*)pSrcFile->Clone();
	AddTail(pNewFile);
	pNewFile->SetParent(this);

	CString strSrcPath = pSrcFile->GetRelativePath(TRUE);
	CString strDestPath = pNewFile->GetRelativePath(TRUE);

	//::X_CopyFile(strSrcPath, strDestPath, FALSE);
	XCopyFile(strSrcPath, strDestPath, FALSE);

	return pNewFile;
}

CXFile* CXFolder::AddFile(CXFile *pSrcFile, const CString &strFileName)
{
	CXFile *pNewFile = (CXFile*)pSrcFile->Clone();
	AddTail(pNewFile);
	pNewFile->SetParent(this);
	pNewFile->m_strName = strFileName;
	pNewFile->m_strID = strFileName;

	CString strSrcPath = pSrcFile->GetRelativePath(TRUE);
	CString strDestPath = pNewFile->GetRelativePath(TRUE);

	//::X_CopyFile(strSrcPath, strDestPath, TRUE);
	XCopyFile(strSrcPath, strDestPath, TRUE);

	return pNewFile;
}

CXFolder* CXFolder::AddFolder(const CString& strFolderName, BOOL bCreateFolder)
{
	CXFolder* pNewFolder = (CXFolder*)FindByLowerName(strFolderName);

	if(pNewFolder  == NULL)
	{
		pNewFolder = new CXFolder();
		AddTail(pNewFolder);
		pNewFolder->SetParent(this);
		pNewFolder->m_strName = strFolderName;
		pNewFolder->m_strID = strFolderName;
	
		CString strPath = m_strPath + strFolderName + _P_FOLDER_PATH_SEPARATOR_;
		pNewFolder->m_strPath = strPath;

		if (bCreateFolder)
		{
			CreateAllDirectories(strPath);
		}

// 		return pNewFolder;
	}
	
	return pNewFolder;
}

BOOL CXFolder::GetFolderModifyTime(CString& strModifyTime)
{
	BOOL bTrue = FALSE;
#ifndef _PSX_IDE_QT_
	// 打开文件夹
	HANDLE hFolder = CreateFile (GetFolderPath(), 
		GENERIC_READ,
		FILE_SHARE_READ|FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL);

	FILETIME lpCreationTime; // 文件夹的创建时间
	FILETIME lpLastAccessTime; // 对文件夹的最近访问时间
	FILETIME lpLastWriteTime; // 文件夹的最近修改时间

	SYSTEMTIME systime;

	// 获取文件夹时间属性信息
	if (GetFileTime(hFolder, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime))
	{
		FILETIME ftime;
		FileTimeToLocalFileTime(&lpLastWriteTime, &ftime); // 转换成本地时间
		FileTimeToSystemTime(&ftime, &systime); // 转换成系统时间格式

		strModifyTime.Format(_T("%4d-%02d-%02d %02d:%02d")
			,systime.wYear,systime.wMonth,systime.wDay,systime.wHour
			,systime.wMinute);

		bTrue = TRUE;
	}

	CloseHandle(hFolder); // 关闭打开过的文件夹
#else
	QDir dir(GetFolderPath());
	dir.setFilter( QDir::Files | QDir::Hidden | QDir::NoSymLinks );
	dir.setSorting( QDir::Time | QDir::Reversed );

	QFileInfoList fileList = dir.entryInfoList();
	QFileInfo fileInfo = fileList.at(0);
	QDateTime dateTime = fileInfo.lastModified();
	QDate date = dateTime.date();
	QTime time = dateTime.time();
	strModifyTime.Format(_T("%4d-%02d-%02d %02d:%02d")
		,date.year(),date.month(),date.day(),time.hour(),time.minute());

	bTrue = TRUE;
#endif
	return bTrue;	
}

BOOL CXFolder::IsFolderExist()
{
	BOOL rValue = FALSE;

	m_strPath = GetFolderPath();
	CString strPath = m_strPath;

#ifndef _PSX_IDE_QT_
	if(strPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
		int nCount = m_strPath.ReverseFind('\\');
		strPath = m_strPath.Left(nCount);
	}
#else
	if(strPath.Right(1) == _T("//"))
	{
		int nCount = m_strPath.lastIndexOf('//');
		strPath = m_strPath.Left(nCount);
	}
#endif

#ifndef _PSX_IDE_QT_
	WIN32_FIND_DATA   wfd;

	HANDLE hFind = FindFirstFile(strPath, &wfd);
	
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;   
	}

	FindClose(hFind);
#else
	QDir dir(strPath);
	if(dir.exists())
	{
		rValue = TRUE;
	}
#endif
	return rValue;
}

//在磁盘中查找子对象指向的文件和文件夹是否存在
//如果文件夹不存在，则在磁盘中创建
//如果文件不存在，则将子对象从链表中删除
BOOL CXFolder::CheckFileExist()
{
	//首先验证this指向的文件夹是否存在
	BOOL bChange = FALSE;
	BOOL bFlag = IsFolderExist();

	if(bFlag)
	{
		POS pos = this->GetHeadPosition();
		CExBaseObject* pObj = NULL;

		while(pos != NULL)
		{
			pObj = this->GetNext(pos);
			if( xfile_IsFolder(pObj->GetClassID()) )
			{
				CXFolder* pFolderBase = (CXFolder*)pObj;

				if( !pFolderBase->IsFolderExist() )
				{
					CreateAllDirectories(pFolderBase->GetFolderPath());
				}
			}
			else if( xfile_IsFile(pObj->GetClassID()) )
			{
				CXFile* pFileBase = (CXFile*)pObj;

				if( !pFileBase->IsFileExist() )
				{
					this->Delete(pObj);
					bChange = TRUE;
				}
			}
		}
	}
	else
	{
		CreateAllDirectories(GetFolderPath());
	}
	
	return bChange;
}

//不区分大小写的查找
CExBaseObject* CXFolder::FindByLowerName(const CString &strFolderName)
{	
	CExBaseObject* pTemp = NULL;
	CExBaseObject* pFind = NULL;

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pTemp = (CXFolder*)GetNext(pos);
		//CString strName = pTemp->m_strName;

#ifdef _PSX_IDE_QT_
// 		char* pstrFolderName = NULL,*pstrTempName = NULL;//20220702 zhouhj 不用在new
// 		CString_to_char(strFolderName.GetString(), &pstrFolderName);
// 		CString_to_char(pTemp->m_strName.GetString(), &pstrTempName);

#ifdef _PSX_QT_LINUX_
		if (strcasecmp(strFolderName.GetString(), pTemp->m_strName.GetString()) == 0)
#else
		if (stricmp(strFolderName.GetString(), pTemp->m_strName.GetString()) == 0)
#endif
#else
#ifdef _UNICODE
	if (_wcsicmp(strFolderName, pTemp->m_strName) == 0)
#else
	if (stricmp(strFolderName, pTemp->m_strName) == 0)
#endif
#endif
		{
			pFind = pTemp;
			break;
		}
// #ifdef _PSX_IDE_QT_
// 		delete (char*)(*pstrFolderName);
// 		delete (char*)(*pstrTempName);
// #endif
	}

	return pFind;
}

CXFile* CXFolder::SelectFileInCurrFolder(const CString &strFile, BOOL bUseFullPath)
{
	CExBaseObject* pTemp = NULL;
	CExBaseObject* pFind = NULL;

	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->IsBaseObject())
		{
			//strTemp = pTemp->m_strName;
			if (bUseFullPath)
			{
				strTemp = ((CXFile*)pTemp)->GetTotalFileName();
			}
			else
			{
				strTemp = pTemp->m_strName;
			}

			strTemp.MakeLower();

			if (strTemp == strFile)
			{
				pFind = pTemp;
				break;
			}
		}

	}

	return (CXFile*)pFind;
}

CXFile* CXFolder::SelectFileInSubFolder(const CString &strFile, BOOL bUseFullPath)
{
	CExBaseObject* pTemp = NULL;
	CExBaseObject* pFind = NULL;

	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->IsBaseList())
		{
			pFind = ((CXFolder*)pTemp)->SelectFile(strFile, bUseFullPath);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return (CXFile*)pFind;
}

CXFile* CXFolder::SelectFile(const CString &strFile, BOOL bUseFullPath)
{
	CXFile *pFileFind = SelectFileInCurrFolder(strFile, bUseFullPath);

	if (pFileFind != NULL)
	{
		return pFileFind;
	}

	pFileFind = SelectFileInSubFolder(strFile, bUseFullPath);

	return pFileFind;
}


long CXFolder::SelectAllFiles(CExBaseList &listFiles)
{
	CExBaseObject* pTemp = NULL;
	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->IsBaseObject())
		{
			listFiles.AddTail(pTemp);
		}
		else
		{
			((CXFolder*)pTemp)->SelectAllFiles(listFiles);
		}

	}

	return listFiles.GetCount();
}

CXFolder* CXFolder::SelectFolderInCurrFolder(const CString &strFolder, BOOL bUseFullPath)
{
	CExBaseObject* pTemp = NULL;
	CExBaseObject* pFind = NULL;

	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->IsBaseList())
		{
			if (bUseFullPath)
			{
				strTemp = ((CXFolder*)pTemp)->GetFolderPath();
			}
			else
			{
				strTemp = pTemp->m_strName;
			}

			strTemp.MakeLower();

			if (strTemp == strFolder)
			{
				pFind = pTemp;
				break;
			}
		}

	}

	return (CXFolder*)pFind;
}

CXFolder* CXFolder::SelectFolderInSubFolder(const CString &strFolder, BOOL bUseFullPath)
{
	CExBaseObject* pTemp = NULL;
	CExBaseObject* pFind = NULL;

	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->IsBaseList())
		{
			pFind = ((CXFolder*)pTemp)->SelectFolder(strFolder, bUseFullPath);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return (CXFolder*)pFind;
}

CXFolder* CXFolder::FindFolder(const CString &strFolder)
{
	CExBaseObject* pTemp = NULL;
	CExBaseObject* pFind = NULL;

	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->IsBaseList())
		{
			strTemp = pTemp->m_strName;
			strTemp.MakeLower();

			if (strTemp == strFolder)
			{
				pFind = pTemp;
				break;
			}
		}
	}

	return (CXFolder*)pFind;
}

CXFolder* CXFolder::SelectFolder(const CString &strFolder, BOOL bUseFullPath)
{
	CXFolder *pFileFind = SelectFolderInCurrFolder(strFolder, bUseFullPath);

	if (pFileFind != NULL)
	{
		return pFileFind;
	}

	pFileFind = SelectFolderInSubFolder(strFolder, bUseFullPath);

	return pFileFind;
}

CXFolder* CXFolder::SelectFolder(CStringArray &strIdArray, long nPos)
{
	CXFolder*pFind = SelectFolderInCurrFolder(strIdArray, nPos);

	if (pFind == NULL)
	{
		return NULL;
	}

	if (strIdArray.GetSize() == nPos+1)
	{
		return pFind;
	}

	pFind = pFind->SelectFolder(strIdArray, nPos+1);

	return pFind;
}

CXFolder* CXFolder::SelectFolderInCurrFolder(CStringArray &strIdArray, long nPos)
{
	CString strID = strIdArray.GetAt(nPos);

	CExBaseObject* pTemp = NULL;
	CExBaseObject* pFind = NULL;

	POS pos = GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->IsBaseList())
		{
			strTemp = pTemp->m_strName;
			strTemp.MakeLower();

			if (strTemp == strID)
			{
				pFind = pTemp;
				break;
			}
		}
	}

	return (CXFolder*)pFind;
}
// 
// CXFolder* CXFolder::SelectFolderInSubFolder(CStringArray &strIdArray, long nPos)
// {
// 	CExBaseObject* pTemp = NULL;
// 	CExBaseObject* pFind = NULL;
// 
// 	nPos = nPos + 1;
// 	POS pos = GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pTemp = GetNext(pos);
// 
// 		if (pTemp->IsBaseList())
// 		{
// 			pFind = ((CXFolder*)pTemp)->SelectFolder(strIdArray, nPos);
// 
// 			if (pFind != NULL)
// 			{
// 				break;
// 			}
// 		}
// 	}
// 
// 	return (CXFolder*)pFind;
// }
// 


CXFile* CXFolder::SelectFile(CStringArray &strIdArray)
{
	long nIndex = strIdArray.GetSize() - 1;
	CString strFile = strIdArray.GetAt(nIndex);
	strIdArray.RemoveAt(nIndex);

	CXFolder*pFolder = NULL;
	
	if (nIndex == 0)
	{
		pFolder = this;
	}
	else
	{
		pFolder = SelectFolder(strIdArray, 0);
	}

	if (pFolder == NULL)
	{
		return NULL;
	}

	CXFile *pFile = NULL;
	CExBaseObject *p = NULL;
	POS pos = pFolder->GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->IsBaseObject())
		{
			strTemp = p->m_strID;
			strTemp.MakeLower();

			if (strTemp == strFile)
			{
				pFile = (CXFile *)p;
				break;
			}
		}
	}

	return pFile;
}

long CXFolder::Search(CExBaseList *pListPostfix, BOOL bTraveSubFolder, BOOL bAddFiles)
{
	return Search(pListPostfix,bAddFiles,bTraveSubFolder,bTraveSubFolder);
// 	//CFileFind finder;
// 	CXFileFindEx finder;
// 	CString strPath = m_strPath;
// 
// #ifdef _PSX_IDE_QT_
// 	CString strFinder = strPath/* + _T("*.*")*/;//20220702 zhouhj Qt下不用加+ _T("*.*")
// #else
// 	CString strFinder = strPath + _T("*.*");
// #endif
// 	BOOL bIsFinded = finder.FindFile(strFinder);
// 
// 	while(bIsFinded)
// 	{
// 		bIsFinded = (BOOL)finder.FindNextFile();
// 
// 		if( !finder.IsDots())
// 		{
// 			if(finder.IsDirectory())
// 			{
// 				if (bTraveSubFolder)
// 				{
// 					CXFolder* pChildFolder = AddFolder(finder.GetFileName(), FALSE);
// 				}
// 			}
// 			else
// 			{
// 				if (!bAddFiles)  //2022-3-23  lijunqing 如果不添加文件，则继续
// 				{
// 					continue;
// 				}
// 
// 				//获取后缀
// 				CString strFileWithExtension = finder.GetFileName();
// 				int npos = strFileWithExtension.ReverseFind('.'); 
// 
// 				if(npos != -1)
// 				{
// 					npos++;
// 					//CString strFilePostFix = strFileWithExtension.Right(strFileWithExtension.GetLength() - npos); 
// 
// 					//if(pListPostfix->FindByID(strFileWithExtension.Mid(npos)) != NULL)
// 					if (XFile_IsFilePostFixExist(pListPostfix, strFileWithExtension.Mid(npos)))
// 					{
// 						//CString strFileName = finder.GetFileName();//finder.GetFileTitle()+_T(".") + strFilePostFix;
// 						AddFile(finder.GetFileName(),FALSE);
// 					}
// 				}
// 				else
// 				{
// 					//mym 注释 这个函数有点问题 GetFileName（）返回值不对 2020-12-04
// 					AddFile(finder.GetFileName(),TRUE);	//无扩展名的二进制文件
// 				}
// 			}
// 		}
// 	}
// 
// 	finder.Close();
// 
// 	if (bTraveSubFolder)
// 	{
// 		SearchChildren(pListPostfix, bTraveSubFolder);
// 	}
// 
// 	return 0;
}

long CXFolder::Search(CExBaseList *pListPostfix, BOOL bAddSubFiles, BOOL bAddSubFolders,BOOL bSearchSubFolders)
{
	m_bHasSearched = TRUE;
	//CFileFind finder;
	CXFileFindEx finder;
	CString strPath = m_strPath;
	CString strName;

#ifdef _PSX_IDE_QT_
	CString strFinder = strPath/* + _T("*.*")*/;//20220702 zhouhj Qt下不用加+ _T("*.*")
#else
	CString strFinder = strPath + _T("*.*");
#endif
	BOOL bIsFinded = finder.FindFile(strFinder);

	while(bIsFinded)
	{
		bIsFinded = (BOOL)finder.FindNextFile();

		if( !finder.IsDots())
		{
			if(finder.IsDirectory())
			{
				if (bAddSubFolders)
				{
					strName = finder.GetFileName();//此处单独定义临时变量,AddFolder采用的是引用方式
					CXFolder* pChildFolder = AddFolder(strName, FALSE);
				}
			}
			else
			{
				if (!bAddSubFiles)  //2022-3-23  lijunqing 如果不添加文件，则继续
				{
					continue;
				}

				//获取后缀
				CString strFileWithExtension = finder.GetFileName();
// 				CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("[%s]"),strFileWithExtension.GetString());
//                 CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("[%s]"),finder.GetFileName().GetString());
				int npos = strFileWithExtension.ReverseFind('.'); 

				if(npos != -1)
				{
					npos++;
					//CString strFilePostFix = strFileWithExtension.Right(strFileWithExtension.GetLength() - npos); 

					//if(pListPostfix->FindByID(strFileWithExtension.Mid(npos)) != NULL)
					if (XFile_IsFilePostFixExist(pListPostfix, strFileWithExtension.Mid(npos)))
					{
						//CString strFileName = finder.GetFileName();//finder.GetFileTitle()+_T(".") + strFilePostFix;
						AddFile(finder.GetFileName(),FALSE);
					}
				}
				else
				{
					//mym 注释 这个函数有点问题 GetFileName（）返回值不对 2020-12-04
					AddFile(finder.GetFileName(),TRUE);	//无扩展名的二进制文件
				}
			}
		}
	}

	finder.Close();

	if (bSearchSubFolders)
	{
		SearchChildren(pListPostfix, bAddSubFiles, bAddSubFolders,bSearchSubFolders);
	}

	return 0;
}

long CXFolder::SearchChildren(CExBaseList *pListPostfix,BOOL bAddSubFiles, BOOL bAddSubFolders,BOOL bSearchSubFolders)
{
POS pos =  GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList oListFolder;
	CExBaseList oListFile;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			oListFolder.AddTail(p);
		}
		else
		{
			oListFile.AddTail(p);
		}
	}

	RemoveAll();
	Append(oListFolder);
	Append(oListFile);
	oListFile.RemoveAll();

	pos =  oListFolder.GetHeadPosition();

	while (pos != NULL)
	{
		p =  oListFolder.GetNext(pos);
		((CXFolder*)p)->Search(pListPostfix, bAddSubFiles, bAddSubFolders,bSearchSubFolders);
	}

	oListFolder.RemoveAll();

	return 0;
}

long CXFolder::SearchChildren(CExBaseList *pListPostfix, BOOL bTraveSubFolder, BOOL bAddFiles)
{
	return SearchChildren(pListPostfix,bAddFiles,bTraveSubFolder,bTraveSubFolder);
// 	POS pos =  GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	CExBaseList oListFolder;
// 	CExBaseList oListFile;
// 
// 	while (pos != NULL)
// 	{
// 		p = GetNext(pos);
// 
// 		if (p->GetClassID() == CLASSID_XFOLDER)
// 		{
// 			oListFolder.AddTail(p);
// 		}
// 		else
// 		{
// 			oListFile.AddTail(p);
// 		}
// 	}
// 
// 	RemoveAll();
// 	Append(oListFolder);
// 	Append(oListFile);
// 	oListFile.RemoveAll();
// 
// 	pos =  oListFolder.GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		p =  oListFolder.GetNext(pos);
// 		((CXFolder*)p)->Search(pListPostfix, bTraveSubFolder, bAddFiles);
// 	}
// 
// 	oListFolder.RemoveAll();
// 
// 	return 0;
}


BOOL XFile_IsFilePostFixExist(CExBaseList *pListFilePostFix, const CString &strPostfix)
{
	POS pos = pListFilePostFix->GetHeadPosition();

	if (pos == NULL)
	{
		return TRUE;
	}

	CXFileTypePostfix *pPostfix = NULL;

	while (pos != NULL)
	{
		pPostfix = (CXFileTypePostfix *)pListFilePostFix->GetNext(pos);

#ifdef _PSX_IDE_QT_
		char* pstrPostfix,*pstrID;
		CString_to_char(strPostfix, &pstrPostfix);
		CString_to_char(pPostfix->m_strID, &pstrID);

#ifdef _PSX_QT_LINUX_
		if (strcasecmp(pstrPostfix, pstrID) == 0)
#else
		if (stricmp(pstrPostfix, pstrID) == 0)
#endif
#else
#ifdef UNICODE
		if (_wcsicmp(strPostfix, pPostfix->m_strID) == 0)
#else
		if (stricmp(strPostfix, pPostfix->m_strID) == 0)
#endif
#endif
		{
#ifdef _PSX_IDE_QT_
			delete (char*)(pstrPostfix);
			delete (char*)(pstrID);
#endif
			return TRUE;
		}
#ifdef _PSX_IDE_QT_
		delete (char*)(pstrPostfix);
		delete (char*)(pstrID);
#endif
	}

	return FALSE;
}

BOOL CXFolder::DeleteFolder()
{
	CString strPath = m_strPath;

	if (strPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
		strPath = strPath.Left(strPath.GetLength() - 1);
	}
#ifndef _PSX_IDE_QT_
	BOOL bFlag =  ::RemoveDirectory(strPath);
#else
	QDir dir(strPath);
	BOOL bFlag = dir.rmpath(dir.absolutePath());
#endif

	return bFlag;
}

BOOL CXFolder::DeleteFolderEx()
{
	CString strPath = m_strPath;

	if (strPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
		strPath = strPath.Left(strPath.GetLength() - 1);
	}

	BOOL bFlag =  DeleteAllDirectorys(strPath);
	return bFlag;
}

long CXFolder::DeleteFile(const CString &strFile)
{
	return 0;
}

long CXFolder::DeleteFile(CXFile *pFile)
{
	pFile->DeleteFile();
	Delete(pFile);
	return 0;
}

#ifndef _PSX_IDE_QT_
long CXFolder::DeleteFile_byTime(long nSpanDays)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	SYSTEMTIME tmSysCurr;
	::GetLocalTime(&tmSysCurr);
	SYSTEMTIME tmFileTime;
	CTimeSpan tmSpan;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (pObj->GetClassID()  == CLASSID_XFOLDER)
		{
			CXFolder *pFolder = (CXFolder *)pObj;
			pFolder->DeleteFile_byTime(nSpanDays);

			if (pFolder->GetCount() == 0)
			{
				pFolder->DeleteFolder();
				Delete(pFolder);
				pFolder = NULL;
				continue;
			}
		}

		if (pObj->GetClassID()  == CLASSID_XFILE)
		{
			CXFile *pFile = (CXFile *)pObj;
			pFile->GetModifyTime(tmFileTime);

			CTime tmCurr(tmSysCurr);
			CTime tmFile(tmFileTime);
			tmSpan = tmCurr - tmFile;
			int dwDaysOver = tmSpan.GetDays();

			if (dwDaysOver >= nSpanDays)
			{
				//::X_DeleteFile(strPath + pFile->m_strName);
				pFile->DeleteFile();
				Delete(pFile);
				pFile = NULL;
			}
		}	
	}

	return 0;
}

#endif

BOOL CXFolder::CopyTo(const CString &strPath, BOOL bCopySubFolder)
{
	CXFile *pFile = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CString strDestPath;

	strDestPath = strPath;
	CreateAllDirectories(strDestPath);

	while (pos != NULL)
	{
		p = GetNext(pos);
		
		if (p->GetClassID() == CLASSID_XFILE)
		{
			((CXFile*)p)->CopyTo(strPath);
		}
		else
		{
			if (bCopySubFolder)
			{
                strDestPath.Format(_T("%s%s\\"), strPath.GetString(), p->m_strID.GetString());
				((CXFolder*)p)->CopyTo(strDestPath, bCopySubFolder);
			}
		}
	}

	return 0;
}

CXFolder* CXFolder::AddPath(const CString &strPath)
{
	CString strName = GetLastFolderNameFromPathName(strPath);
	CXFileMngr *pMngr = xfile_GetXFileMngr(this);//(CXFileMngr*)GetAncestor(CLASSID_XFILEMNGR);
	ASSERT(pMngr != NULL);
	CXFolder *pSrcFolder = new CXFolder();

	pSrcFolder->m_strPath = strPath;

	if (pSrcFolder->m_strPath.Right(1) != _P_FOLDER_PATH_SEPARATOR_)
	{
		pSrcFolder->m_strPath += _P_FOLDER_PATH_SEPARATOR_;
	}

	pSrcFolder->m_strID = strName;
	pSrcFolder->m_strName = strName;

	pSrcFolder->Search(pMngr->GEtFilePostfixList(), TRUE);

	CXFolder *pDestFolder = (CXFolder*)Paste(pSrcFolder);
	delete pSrcFolder;
	return pDestFolder;
}

CString CXFolder::GetFolderPath(BOOL bValidateLastChar)
{
	CString strPath = m_strPath;

	if (strPath.GetLength() == 0)
	{//拼接路径
		CXFileMngr *pFileMngr = (CXFileMngr*)GetRoot();
		strPath = pFileMngr->m_strRootPath + GetRelativePath();
	}

	if (bValidateLastChar)
	{
		if (strPath.Right(1) != _P_FOLDER_PATH_SEPARATOR_)
		{
			strPath += _P_FOLDER_PATH_SEPARATOR_;
		}
	}
	
	return strPath;
}

CString CXFolder::GetRelativePath()
{
	CExBaseObject *pRoot = NULL;
	CExBaseObject *pParent = NULL;

	pParent = (CExBaseObject*)GetParent();
	CString strPath = m_strID;

	while (pParent != NULL)
	{
		pRoot = (CExBaseObject*)pParent->GetParent();

		if (pRoot == NULL)
		{
			break;
		}

		strPath = pParent->m_strID + _P_FOLDER_PATH_SEPARATOR_ + strPath;

		pParent = pRoot;
	}

	return strPath;
}

CString CXFolder::GetFolderPathByName(BOOL bValidateLastChar)
{
	CString strPath = m_strPath;

	if (strPath.GetLength() == 0)
	{//拼接路径
		CXFileMngr *pFileMngr = (CXFileMngr*)GetRoot();
		strPath = pFileMngr->m_strRootPath + GetRelativePathByName();
	}

	if (bValidateLastChar)
	{
		if (strPath.Right(1) != _P_FOLDER_PATH_SEPARATOR_)
		{
			strPath += _P_FOLDER_PATH_SEPARATOR_;
		}
	}

	return strPath;
}

CString CXFolder::GetRelativePathByName()
{
	CExBaseObject *pRoot = NULL;
	CExBaseObject *pParent = NULL;

	pParent = (CExBaseObject*)GetParent();
	CString strPath = m_strName;

	while (pParent != NULL)
	{
		pRoot = (CExBaseObject*)pParent->GetParent();

		if (pRoot == NULL)
		{
			break;
		}

		strPath = pParent->m_strName + _P_FOLDER_PATH_SEPARATOR_ + strPath;

		pParent = pRoot;
	}

	return strPath;
}

CExBaseObject* CXFolder::Paste(CExBaseObject *pObj)
{
	UINT nClassID = pObj->GetClassID();
	CExBaseObject *pRet = NULL;

	if (nClassID == CLASSID_XFOLDER)
	{
		CXFolder *pNew = new CXFolder();
		pObj->CopyOwn(pNew);
		CString strPath = m_strPath + pObj->m_strName;
		pNew->m_strPath =strPath;
		pNew->m_strPath += _P_FOLDER_PATH_SEPARATOR_;
		CreateAllDirectories(strPath);
		AddNewChild(pNew);
		pRet = pNew;

		CXFolder *pFolder = (CXFolder*)pObj;
		POS pos = pFolder->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pFolder->GetNext(pos);
			pNew->Paste(p);
		}
	}
	else if (nClassID == CLASSID_XFILE)
	{
		pRet = AddFile((CXFile*)pObj, pObj->m_strName);
	}

	return pRet;
}

CExBaseObject* CXFolder::Paste(CExBaseList *pList)
{
	return Paste((CExBaseObject*)pList);
}

void CXFolder::SetPath(const CString &strPath)
{
	if (strPath.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
		m_strPath = strPath;
	}
	else
	{
		m_strPath = strPath;
		m_strPath+= _P_FOLDER_PATH_SEPARATOR_;
	}
}

long CXFolder::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPath);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPath);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPath);
	}
	return 0;
}

void CXFolder::XFolderToDataGroup(CDataGroup *pDestGroup)
{
	ASSERT(pDestGroup);
	pDestGroup->m_strName = m_strName;
	pDestGroup->m_strID = m_strID;

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CXFolder *pFolder = NULL;
	CXFile *pFile = NULL;

	CDataGroup *pNew;
	CDvmData *pData;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CLASSID_XFOLDER)
		{
			pFolder = (CXFolder *)p;
			pNew = new CDataGroup();
			pNew->m_strName = m_strName;
			pDestGroup->AddNewChild(pNew);
			pFolder->XFolderToDataGroup(pNew);

			if (m_pYunFolder != NULL)
			{//DataGroup::m_strID：表示数据库中的Index_Group
				pNew->m_strID = m_pYunFolder->m_strID;
			}
		}
		else if (nClassID == CLASSID_XFILE)
		{
			pFile = (CXFile *)p;
			pData = new CDvmData;
			pData->m_strName = pFile->m_strName;
			if (pFile->m_pYunFile != NULL)
			{//Data::m_strID：表示数据库中的Index_Templ
		//		pFile->m_pYunFile->GetPKey(pData->m_strID);
				pData->m_strID = pFile->m_pYunFile->m_strID;
			}
			
			pDestGroup->AddNewChild(pData);
		}
	}
}

void CXFolder::DataGroupToXFolder(CDataGroup *pDestGroup)
{
	ASSERT(pDestGroup);
	if (!pDestGroup->m_strName.IsEmpty())
	{
		m_strName = pDestGroup->m_strName;
	}
	
	if (!pDestGroup->m_strID.IsEmpty())
	{
		m_strID = pDestGroup->m_strID;
	}
	
	POS pos = pDestGroup->GetHeadPosition();
	CExBaseObject *p = NULL;
	CXFolder *pFolder = NULL;
	CXFile *pFile = NULL;
	UINT nClassID = 0;
	CString strTemp;

	while (pos != NULL)
	{
		p = pDestGroup->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			strTemp = p->m_strName;
			strTemp.MakeLower();
			pFolder = FindFolder(strTemp);

			if (pFolder == NULL)
			{
				pFolder = new CXFolder;
				pFolder->m_strName = p->m_strName;
				pFolder->m_strID = p->m_strName;
				AddNewChild(pFolder);
			}

			pFolder->m_bIsYun = TRUE;
			if (pFolder->m_pYunFolder == NULL)
			{
				pFolder->m_pYunFolder = new CDataGroup;
			}
			p->Copy(pFolder->m_pYunFolder);
			pFolder->DataGroupToXFolder((CDataGroup*)p);
		}
		else if (nClassID == DVMCLASSID_CDVMDATA)
		{
			strTemp = p->m_strName;
			strTemp.MakeLower();
			pFile = SelectFileInCurrFolder(strTemp, FALSE);
			
			if (pFile == NULL)
			{
				pFile = new CXFile;
				AddNewChild(pFile);
			}
			pFile->m_strName = p->m_strName;
			pFile->m_strID = p->m_strID;
			if (pFile->m_pYunFile == NULL)
			{
				pFile->m_pYunFile = new CDvmData;
			}
			p->Copy(pFile->m_pYunFile);
			
			pFile->m_bIsYun = TRUE;
		}
	}
}

CDataGroup* CXFolder::ParentToDataGroup(CDataGroup* pGroup, CXFolder* pRootFolder)
{
	ASSERT(pGroup != NULL);
	ASSERT(pRootFolder != NULL);

	CXFolder* pParentFolder = (CXFolder*)GetParent();
	if (pParentFolder == pRootFolder)
	{
		return pGroup;
	}

	CDataGroup* pParentGroup = new CDataGroup;
	pParentGroup->m_strName = pParentFolder->m_strName;
	CDataGroup* pYunFolder = pParentFolder->GetYunFolder();
	if (pYunFolder != NULL)
	{
		pParentGroup->m_strID = pYunFolder->m_strID;
	}

	pParentGroup->AddNewChild(pGroup);

	return pParentFolder->ParentToDataGroup(pParentGroup, pRootFolder);
}

void XFile_BringFileHead(CXFolder *pFolder, const CString &strFilePostfix)
{
	CExBaseList oList;
	POS pos = pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;
	long nLen = strFilePostfix.GetLength();

	while (pos != NULL)
	{
		p = (CExBaseObject *)pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			XFile_BringFileHead((CXFolder*)p, strFilePostfix);
		}
		else
		{
			if (p->m_strID.Right(nLen) == strFilePostfix)
			{
				oList.AddTail(p);
			}
		}
	}

	pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CExBaseObject *)oList.GetNext(pos);
		pFolder->BringToHead(p);
	}

	oList.RemoveAll();
}
