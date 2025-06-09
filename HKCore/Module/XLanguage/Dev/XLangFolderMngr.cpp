//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangFolderMngr.cpp  CXLangFolderMngr


#include "stdafx.h"
#include "XLangFolderMngr.h"
#include "..\..\XfileMngrBase\XFileMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CXLangFolderMngr::CXLangFolderMngr()
{
	//初始化属性

	//初始化成员变量
}

CXLangFolderMngr::~CXLangFolderMngr()
{
	
}

void CXLangFolderMngr::InitXLangFolderMngr()
{
	DeleteAll();
	m_oAllFile.DeleteAll();

	CXFileMngr oXFileMngr;
	CString strPath;
	strPath = _P_GetLanguagePath(TRUE);

	oXFileMngr.SearchFiles(_T("语言文件"), _T("xml"), strPath);

	POS pos = oXFileMngr.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)oXFileMngr.GetNext(pos);

		if (xfile_IsFolder(p->GetClassID()))
		{
			AddXLangFolder((CExBaseList*)p);
		}
	}

	InitAllFiles();

	CExBaseObject *pFind = FindByID(CXLanguageResourceBase::g_sLangID_Chinese );

	ASSERT (pFind != NULL);
	BringToHead(pFind);
}

void CXLangFolderMngr::AddXLangFolder(CExBaseList *pFolder)
{
	CXLangFolder *pXLangFolder = new CXLangFolder();
	pXLangFolder->m_strName = pFolder->m_strName;
	pXLangFolder->m_strID = pFolder->m_strID;
	AddNewChild(pXLangFolder);

	POS pos = pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pFolder->GetNext(pos);

		if (xfile_IsFile(p->GetClassID()))
		{
			CXLangFile *pXLangFile = new CXLangFile();
			pXLangFile->m_strName = p->m_strName;
			pXLangFile->m_strID = p->m_strID;
			pXLangFolder->AddNewChild(pXLangFile);
		}
	}
}

void CXLangFolderMngr::InitAllFiles()
{
	POS pos = GetHeadPosition();
	CXLangFolder *pXLangFolder = NULL;

// 	pXLangFolder = (CXLangFolder *)GetNext(pos);
// 	ASSERT (pXLangFolder != NULL);
// 
// 	if (pXLangFolder == NULL)
// 	{
// 		return;
// 	}
// 
// 	m_oAllFile.AppendClone(pXLangFolder);

	while (pos != NULL)
	{
		pXLangFolder = (CXLangFolder *)GetNext(pos);
		m_oAllFile.AppendLangFile(pXLangFolder);
	}
}

BOOL CXLangFolderMngr::CanOpenXLangFile(CXLangFile *pFile)
{
	POS pos = GetHeadPosition();
	CXLangFolder *pXLangFolder = NULL;
	BOOL bCan = TRUE;

	while (pos != NULL)
	{
		pXLangFolder = (CXLangFolder *)GetNext(pos);
		
		if (pXLangFolder->FindLangFile(pFile->m_strID) == NULL)
		{
			bCan = FALSE;
			break;
		}
	}

	return bCan;
}

//pListFiles：资源文件管理对象，管理多语言的一个资源文件的所有字符串资源
BOOL CXLangFolderMngr::OpenXLangFiles(CXLangFile *pFile, CXLangFileRsItemMngr *pXLangFileRsItemMngr)
{
	//m_oAllFile的CXLangFile对象，管理了CXLangFile对象对应的资源文件的所有字符串资源
	CXLangFile *pFileRef = m_oAllFile.FindLangFile(pFile->m_strID);
	ASSERT( pFileRef != NULL);
	CXLanguage *pXLanguageRef = &pFileRef->m_oXLanguage;

	POS pos = GetHeadPosition();
	CXLangFolder *pXLangFolder = NULL;
	CXLangFile *pFind = NULL;
	//BOOL bNeedOpen = ! pXLanguageRef->HasOpenXLangFile();

	//每次都重新打开资源文件，方便手动修改后再次进行对比
	pFileRef->FreeXLanguage();
	long nXFileIndex = 1;

	while (pos != NULL)
	{
		pXLangFolder = (CXLangFolder *)GetNext(pos);
		pFind = pXLangFolder->FindLangFile(pFile->m_strID);
		ASSERT (pFind != NULL);

		if (nXFileIndex == 1)
		{
			pXLangFileRsItemMngr->AddFile(pFind);
		}
		else
		{
			pXLangFileRsItemMngr->AddFile(pFind, nXFileIndex);
		}

		nXFileIndex++;
	}

	pXLangFileRsItemMngr->UpdateRefCount(nXFileIndex-1);

	return TRUE;
}

void CXLangFolderMngr::AppendXLanguage(CXLanguage *pRef, CXLanguage *pXLanguage)
{
	POS pos = pXLanguage->GetHeadPosition();
	CXLangItem *pItem = NULL;

	while (pos != NULL)
	{
		pItem = (CXLangItem *)pXLanguage->GetNext(pos);

		if (pRef->FindBySrcTextAndID(pItem->m_strID, pItem->m_strSrcText) == NULL)
		{
			pRef->AddTail(pItem);
		}
	}
}

