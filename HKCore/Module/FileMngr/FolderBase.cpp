#include "stdafx.h"
#include "FolderBase.h"
#include "FileMngrBase.h"


CFolderBase::CFolderBase()
{

}

CFolderBase::~CFolderBase()
{

}

long CFolderBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CFolderBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strNameKey,oNode,m_strName);
	m_strID = m_strName;

	return 0;
}

long CFolderBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	oElement->setAttribute(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strNameKey,(_bstr_t)m_strName);

	return 0;
}

CString CFolderBase::GetFolderPath()
{
	CString strTemp, strRet;
	CFolderBase* pTemp;

	for (pTemp = this; pTemp != NULL; pTemp = (CFolderBase*)pTemp->GetParent())
	{
		strTemp = strRet;
		strRet = pTemp->m_strID;
		strRet += "\\";
		strRet += strTemp;
	}

	strRet.Replace(_T("\\\\"), _T("\\"));

	return strRet;
}

BOOL CFolderBase::DeleteAllInFolder()
{
	//查找是否有打开的文件
	if(CheckFileOpen())
	{
		return FALSE;
	}

	CFolderBase* pParent = (CFolderBase*)this->GetParent();
	if(pParent != NULL)
	{
		DeleteAllDirectorys(this->GetPath());
		pParent->Delete(this);

		return TRUE;
	}

	return FALSE;
}

BOOL CFolderBase::CheckFileOpen()
{
	POS pos = this->GetHeadPosition();
	BOOL bFlag = FALSE;

	CExBaseObject* pObj = NULL;
	while(pos != NULL)
	{
		pObj = this->GetNext(pos);
		if(IsFile(pObj->GetClassID()))
		{
			CFileBase* pFile = (CFileBase*)pObj;
			if(pFile->m_bIsOpen)
			{
				bFlag = TRUE;
				return bFlag;
			}
		}
		else if(IsFolder(pObj->GetClassID()))
		{
			CFolderBase* pFolder = (CFolderBase*)pObj;
			bFlag = pFolder->CheckFileOpen();
			if(bFlag)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CFolderBase::RenameFolder(const CString& strNewName)
{
	if(CheckFileOpen())
	{
		return FALSE;
	}

	CString strOldName = this->m_strName;
	CString strFromPath = GetPath();	
	this->m_strName = strNewName;
	this->m_strID = strNewName;
	CString strNewPath = GetPath();
	
	if(strFromPath.Right(1) == _T("\\"))
	{
		strFromPath.Delete(strFromPath.GetLength()-1,1);
	}
	if(strNewPath.Right(1) == _T("\\"))
	{
		strNewPath.Delete(strNewPath.GetLength()-1,1);
	}

	SHFILEOPSTRUCT FileOp; 
	ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

	FileOp.fFlags = FOF_NOCONFIRMATION ; 
	FileOp.hNameMappings = NULL; 
	FileOp.hwnd = NULL; 
	FileOp.lpszProgressTitle = NULL; 
	FileOp.pFrom = strFromPath; 
	FileOp.pTo = strNewPath; 
	FileOp.wFunc = FO_RENAME; 

	int nRet = SHFileOperation(&FileOp);		//返回0为成功

	if(nRet == 0)
	{
		return TRUE;
	}
	
	this->m_strName = strOldName;
	this->m_strID = strOldName;

	return FALSE;
}

CFileBase* CFolderBase::AddFile(CExBaseObject* pNode,const CString& strFileName,/*const CString& strFileType,*/BOOL bOverWrite)
{
	//ASSERT(pNode != NULL);

	if(bOverWrite)
	{
		CFileBase* pFileOld = (CFileBase*)FindByLowerName(strFileName);
		ASSERT(pFileOld != NULL);
		Delete(pFileOld);
	}
	
	CFileBase* pFile = new CFileBase();
	pFile->m_strName = strFileName;
	pFile->m_strID = pFile->m_strName;
// 	pFile->m_strFileType = strFileType;
	AddTail(pFile);
	pFile->SetParent(this);

	
	return pFile;
}

//CFileBase* CFolderBase::AddFile(CGuideBook* pGuideBook,const CString& strFileName,const CString& strFileType,BOOL bOverWrite)
//{
//	ASSERT(pGuideBook != NULL);
//
//	if(bOverWrite)
//	{
//		CFileBase* pFileOld = (CFileBase*)FindByLowerName(strFileName);
//		ASSERT(pFileOld != NULL);
//		Delete(pFileOld);
//	}
//	
//	CFileBase* pFile = new CFileBase();
//	pFile->m_strName = strFileName;
//	pFile->m_strID = pFile->m_strName;
//	pFile->m_strFileType = strFileType;
//	AddTail(pFile);
//	pFile->SetParent(this);
//
//	pGuideBook->SaveXMLFile(pFile->GetPath());
//
//	return pFile;
//}

CFolderBase* CFolderBase::AddFolder(const CString& strFolderName, BOOL bCreateFolder)
{
	CFolderBase* pNewFolder = new CFolderBase();
	pNewFolder->m_strName = strFolderName;
	pNewFolder->m_strID = pNewFolder->m_strName;

	if( FindByLowerName(pNewFolder->m_strName) == NULL)
	{
		AddTail(pNewFolder);
		pNewFolder->SetParent(this);

		if (bCreateFolder)
		{
			CString strPath = pNewFolder->GetPath();
			CreateAllDirectories(strPath);
		}

		return pNewFolder;
	}
	
	delete pNewFolder;
	return NULL;
}

//void  CFolderBase::UpdateSelectStateByChildren()
//{
//
//}
//
//void  CFolderBase::UpdateChildrenSelectState(long nSelect)
//{
//}

//BOOL CFolderBase::GetCreateTime(CString& strCreateTime)
//{
//	CString strTime, strPath;
//	SYSTEMTIME sysTime;
//
//	if (m_strPath.Right(1) == "\\")
//	{
//		int nCount = m_strPath.ReverseFind('\\');
//		strPath = m_strPath.Left(nCount);
//	}
//	else
//	{
//		strPath = m_strPath;
//	}
//
//	if (GetFolderModifyTime(strPath, sysTime))
//	{
//		strCreateTime.Format(_T("%d-%d-%d %d:%d:%d"), 
//			sysTime.wYear, 
//			sysTime.wMonth, 
//			sysTime.wDay, 
//			sysTime.wHour, 
//			sysTime.wMinute, 
//			sysTime.wSecond);
//
//		return TRUE;
//	}
//	else
//	{
//		return FALSE;
//		//LOG_WriteLawString("Get Folder Create Time Failed!!!!!"); 
//	}
//}
//

BOOL CFolderBase::GetFolderModifyTime(CString& strModifyTime)
{
	BOOL bTrue = FALSE;
	// 打开文件夹
	HANDLE hFolder = CreateFile (GetPath(), 
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
	if (GetFileTime(hFolder, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime)){
		FILETIME ftime;
		FileTimeToLocalFileTime(&lpLastWriteTime, &ftime); // 转换成本地时间
		FileTimeToSystemTime(&ftime, &systime); // 转换成系统时间格式

		strModifyTime.Format(_T("%4d-%02d-%02d %02d:%02d")
			,systime.wYear,systime.wMonth,systime.wDay,systime.wHour
			,systime.wMinute);

		bTrue = TRUE;
	}

	CloseHandle(hFolder); // 关闭打开过的文件夹
	return bTrue;	
}

BOOL CFolderBase::IsFolderExist()
{
	WIN32_FIND_DATA   wfd;
	BOOL rValue = FALSE;

	m_strPath = GetPath();
	CString strPath = m_strPath;
	if(strPath.Right(1) == _T("\\"))
	{
		int nCount = m_strPath.ReverseFind('\\');
		strPath = m_strPath.Left(nCount);
	}
	
	HANDLE hFind = FindFirstFile(strPath, &wfd);
	
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		rValue = TRUE;   
	}

	FindClose(hFind);

	return rValue;
}

//在磁盘中查找子对象指向的文件和文件夹是否存在
//如果文件夹不存在，则在磁盘中创建
//如果文件不存在，则将子对象从链表中删除
BOOL CFolderBase::CheckFileExist()
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
			if( IsFolder(pObj->GetClassID()) )
			{
				CFolderBase* pFolderBase = (CFolderBase*)pObj;
				if( !pFolderBase->IsFolderExist() )
				{
					CreateAllDirectories(pFolderBase->GetPath());
				}
			}
			else if( IsFile(pObj->GetClassID()) )
			{
				CFileBase* pFileBase = (CFileBase*)pObj;
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
		CreateAllDirectories(GetPath());
	}
	
	return bChange;
}

//不区分大小写的查找
CExBaseObject* CFolderBase::FindByLowerName(CString strFolderName)
{	
	CExBaseObject* pTemp = NULL;
	CExBaseObject* pFind = NULL;

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pTemp = (CFolderBase*)GetNext(pos);
		CString strName = pTemp->m_strName;
		
		if (strName.MakeLower() == strFolderName.MakeLower())
		{
			pFind = pTemp;
			break;
		}
	}

	return pFind;
}

CFileBase* CFolderBase::SelectFileInCurrFolder(const CString &strFile, BOOL bUseFullPath)
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
			if (bUseFullPath)
			{
				strTemp = ((CFileBase*)pTemp)->GetTotalFileName();
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

	return (CFileBase*)pFind;
}

CFileBase* CFolderBase::SelectFileInSubFolder(const CString &strFile, BOOL bUseFullPath)
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
			pFind = ((CFolderBase*)pTemp)->SelectFile(strFile, bUseFullPath);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return (CFileBase*)pFind;
}

CFileBase* CFolderBase::SelectFile(const CString &strFile, BOOL bUseFullPath)
{
	CFileBase *pFileFind = SelectFileInCurrFolder(strFile, bUseFullPath);

	if (pFileFind != NULL)
	{
		return pFileFind;
	}

	pFileFind = SelectFileInSubFolder(strFile, bUseFullPath);

	return pFileFind;
}



CFolderBase* CFolderBase::SelectFolderInCurrFolder(const CString &strFolder, BOOL bUseFullPath)
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
				strTemp = ((CFolderBase*)pTemp)->GetFolderPath();
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

	return (CFolderBase*)pFind;
}

CFolderBase* CFolderBase::SelectFolderInSubFolder(const CString &strFolder, BOOL bUseFullPath)
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
			pFind = ((CFolderBase*)pTemp)->SelectFolder(strFolder, bUseFullPath);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return (CFolderBase*)pFind;
}

CFolderBase* CFolderBase::SelectFolder(const CString &strFolder, BOOL bUseFullPath)
{
	CFolderBase *pFileFind = SelectFolderInCurrFolder(strFolder, bUseFullPath);

	if (pFileFind != NULL)
	{
		return pFileFind;
	}

	pFileFind = SelectFolderInSubFolder(strFolder, bUseFullPath);

	return pFileFind;
}

