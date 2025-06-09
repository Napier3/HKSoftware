#include "stdafx.h"
#include "FileMngrBase.h"

CFileBase* FindFileBaseByName(const CString& strFileName,CFolderBase* pFolder,CFolderBase* &pFolderFind)
{
	CExBaseObject* pObj = NULL;
	POS pos = pFolder->GetHeadPosition();

	while(pos != NULL)
	{
		pObj = pFolder->GetNext(pos);
		if( IsFile(pObj->GetClassID()) )
		{
			//如果是文件
			CFileBase* pFile = (CFileBase*)pObj;
			if(pFile->GetTotalFileName() == strFileName)
			{
				pFolderFind = pFolder;
				return pFile;
			}
		}
		else if( IsFolder(pObj->GetClassID()) )
		{
			FindFileBaseByName(strFileName,(CFolderBase*)pObj,pFolderFind);
		}
	}

	return NULL;
}

CFileMngrBase::CFileMngrBase()
{

}

CFileMngrBase::~CFileMngrBase()
{

}

BOOL CFileMngrBase::SaveXMLFile()
{
	return FALSE;
}

BOOL CFileMngrBase::OpenXMLFile()
{
	//打开判断文件管理模块的配置文件是否存在
	CFileFind fileFind;
	BOOL bFlag = fileFind.FindFile(m_strMngrFileName);

	if(bFlag)
	{
		//如果文件存在

	}
	else
	{
		//如果文件不存在,创建文件并遍历该文件夹下的所有文件（包含子文件夹）
		
	}

	return FALSE;
}

void CFileMngrBase::Traverse(const CString& strPath,const CString& strFilePostFix/*,const CString& strFileType*/, BOOL bTraveSubFolder)
{
	SetRootPath(strPath);
	TraverseFolder(this, strPath, strFilePostFix, /*strFileType,*/ bTraveSubFolder);
}

UINT file_GetImageIndex(UINT nClassID)
{
	if (IsFolder(nClassID))
	{
		return 0;
	}
	else
	{
		return 2;
	}
}

void file_InsertToTreeCtrl(CExBaseObject *pFileBase, CTreeCtrl *pTreeCtrl, HTREEITEM hParent);

void file_InsertToTreeCtrl(CExBaseList *pFileList, CTreeCtrl *pTreeCtrl, HTREEITEM hParent)
{
	POS pos = pFileList->GetHeadPosition();
	CExBaseObject *pFileBase = NULL;

	while (pos != NULL)
	{
		pFileBase = (CExBaseObject *)pFileList->GetNext(pos);
		file_InsertToTreeCtrl(pFileBase, pTreeCtrl, hParent);
	}
}

void file_InsertToTreeCtrl(CExBaseObject *pFileBase, CTreeCtrl *pTreeCtrl, HTREEITEM hParent)
{
	UINT nImage = file_GetImageIndex(pFileBase->GetClassID());
	
	HTREEITEM hItem = pTreeCtrl->InsertItem(pFileBase->m_strName, nImage, nImage +1, hParent);
	pFileBase->m_dwItemData = (DWORD)hItem;
	pTreeCtrl->SetItemData(hItem, (DWORD)pFileBase);

	if (IsFolder(pFileBase->GetClassID()))
	{
		file_InsertToTreeCtrl((CExBaseList*)pFileBase, pTreeCtrl, hItem);
	}	
}



void file_InsertChildrenToTreeCtrl(CFileMngrBase *pFileMngr, CTreeCtrl *pTreeCtrl)
{
	file_InsertToTreeCtrl((CExBaseList*)pFileMngr, pTreeCtrl, TVI_ROOT);
}

void file_InsertToTreeCtrl(CFileMngrBase *pFileMngr, CTreeCtrl *pTreeCtrl)
{
	file_InsertToTreeCtrl((CExBaseObject*)pFileMngr, pTreeCtrl, TVI_ROOT);
}


