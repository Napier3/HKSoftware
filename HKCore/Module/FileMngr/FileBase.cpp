#include "stdafx.h"
#include "FileBase.h"
#include "FileMngrBase.h"

CFileBase::CFileBase()
{
	m_nSelected = 0;
	m_bIsOpen = FALSE;
}

CFileBase::~CFileBase()
{

}

long CFileBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CFileBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode,CFileMngrXMLKeys::g_pFileMngrXMLKeys);
	xml_GetAttibuteValue(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strNameKey,oNode,m_strName);
	//xml_GetAttibuteValue(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFileTypeKey,oNode,m_strFileType);

	m_strID = m_strName;

	return 0;
}

long CFileBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CFileMngrXMLKeys::g_pFileMngrXMLKeys);
	oElement->setAttribute(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strNameKey,(_bstr_t)m_strName);
	//oElement->setAttribute(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFileTypeKey,(_bstr_t)m_strFileType);
	
	return 0;
}

BOOL CFileBase::DeleteFile()
{
	if(m_bIsOpen)
	{
		//如果文件已被打开
		return FALSE;	
	}
	CFolderBase* pFolder = (CFolderBase*)this->GetParent();
	BOOL bFlag =  ::DeleteFile(GetPath());
	pFolder->Delete(this);

	return bFlag;
}

BOOL CFileBase::GetFilePostfix(CString &strPostfix)
{
	BOOL bFlag = IsFileExist();
	
	if(bFlag)
	{
		int nIndex = m_strName.ReverseFind('.');
		strPostfix = m_strName.Right(m_strName.GetLength()- nIndex);
	}

	return TRUE;
}

BOOL CFileBase::RenameFile(const CString& strNewName)
{
	if(m_bIsOpen)
	{
		return FALSE;
	}

	CString strOldName = this->m_strName;
	CString strFromName = GetPath();	

	CString strPostfix;
	VERIFY( GetFilePostfix(strPostfix) );
	this->m_strName = strNewName + strPostfix;
	this->m_strID = strNewName + strPostfix;
	CString strToName = GetPath();

	if(strOldName == this->m_strName)
	{
		return TRUE;
	}

	SHFILEOPSTRUCT FileOp; 
	ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

	FileOp.fFlags = FOF_NOCONFIRMATION ; 
	FileOp.pFrom = strFromName; 
	FileOp.pTo = strToName; 
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

BOOL  CFileBase::GetModifyTime(CString& strModifyTime)
{
	//首先判断指定的文件是否存在
	BOOL bFlag = IsFileExist();

	if(bFlag)
	{
		HANDLE hFile;
		WIN32_FIND_DATA wfd;
		SYSTEMTIME systime;
		FILETIME localtime;
		memset(&wfd,0,sizeof(wfd));
		hFile = FindFirstFile(GetPath(),&wfd);

		if( hFile != INVALID_HANDLE_VALUE)
		{
			FileTimeToLocalFileTime(&wfd.ftLastWriteTime,&localtime);
			FileTimeToSystemTime(&localtime,&systime);
			strModifyTime.Format(_T("%4d-%02d-%02d %02d:%02d")
				,systime.wYear,systime.wMonth,systime.wDay,systime.wHour
				,systime.wMinute);
			
			FindClose(hFile);
			return TRUE;

		}

		FindClose(hFile);
		return FALSE;
	}

	return bFlag;
}

BOOL CFileBase::GetFileSize(CString& strFileSize)
{ 
	WIN32_FIND_DATA fileInfo; 
	HANDLE hFind; 
	double fileSize; 

	hFind = FindFirstFile(GetPath() ,&fileInfo); 
	if(hFind != INVALID_HANDLE_VALUE) 
	{
		fileSize = fileInfo.nFileSizeLow; 
		strFileSize.Format(_T("%.2f KB"),fileSize/1024);
		FindClose(hFind);

		return TRUE;
	}

	FindClose(hFind); 
	return FALSE;
}

BOOL CFileBase::IsFileExist()
{
	CString strFileName = GetPath();
	CFileFind fileFind;

	return fileFind.FindFile(strFileName);
}

CString CFileBase::GetPath()
{
	CFolderBase *pFolder = (CFolderBase*)GetParent();
	CString strPath = pFolder->GetFolderPath();
	strPath += m_strID;
	return strPath;
}

CString CFileBase::GetRelativePath(BOOL bAddRoot)
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

		strPath = pParent->m_strID + L"\\" + strPath;

		pParent = pRoot;
	}

	return strPath;
}

CString CFileBase::GetTotalFileName()
{
	CString strTotalFileName = GetPath();
	strTotalFileName.Replace(_T("\\\\"), _T("\\"));
	return strTotalFileName;
}

//全局函数
BOOL TraverseFolder(CFolderBase* pFolder,const CString& strPath,const CString& strFilePostFix/*,const CString& strFileType*/, BOOL bTraveSubFolder)
{
	CFileFind finder;
	//CString strFinder = strPath + _T("\\") + _T("*") + strFilePostFix;
	CString strFinder = strPath;
	
	if (strFinder.Right(1) != _T("\\"))
	{
		strFinder += _T("\\");
	}
	
	strFinder += _T("*.*");// + strFilePostFix;

	BOOL IsFinded = finder.FindFile(strFinder);
	BOOL bAddAllFile = FALSE;

	if (strFilePostFix.GetLength() == 0)
	{
		bAddAllFile = TRUE;
	}

	while(IsFinded)
	{
		IsFinded = (BOOL)finder.FindNextFile();

		if( !finder.IsDots())
		{
			if(finder.IsDirectory())
			{
				if (bTraveSubFolder)
				{
					CFolderBase* pChildFolder = pFolder->AddFolder(finder.GetFileName(), FALSE);
					TraverseFolder(pChildFolder,finder.GetFilePath(),strFilePostFix/*,strFileType*/, bTraveSubFolder);
				}
			}
			else
			{
				CString strFileName = finder.GetFileName();// finder.GetFileTitle()+strFilePostFix;
				
				if (bAddAllFile)
				{
					pFolder->AddFile(NULL,strFileName/*,strFileType*/,FALSE);
				}
				else
				{
					if (ParseFilePostfix(strFileName) == strFilePostFix)
					{
						pFolder->AddFile(NULL,strFileName/*,strFileType*/,FALSE);
					}
				}

				//获取后缀

// 				CString strFileWithExtension = finder.GetFileName();
// 				int npos = strFileWithExtension.ReverseFind('.'); 
// 			
// 				if(npos != -1)
// 				{
// 					CString strLastName = strFileWithExtension.Right(strFileWithExtension.GetLength() - npos); 
// 					if(strLastName == strFilePostFix)
// 					{
// 						CString strFileName = finder.GetFileTitle()+strFilePostFix;
// 						pFolder->AddFile(NULL,strFileName/*,strFileType*/,FALSE);
// 					}
// 				}
			}
		}
	}

	finder.Close();

	return TRUE;
}

// BOOL IsFileExist(const CString& strFile)
// {
// 	CFileFind finder;
// 	BOOL bRet = finder.FindFile(strFile);
// 	finder.Close();
// 
// 	return bRet;
// }