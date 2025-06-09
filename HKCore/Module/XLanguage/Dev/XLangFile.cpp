//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangFile.cpp  CXLangFile


#include "stdafx.h"
#include "XLangFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXLangFile::CXLangFile()
{
	//初始化属性
	m_bRefXLanguage = FALSE;

	//初始化成员变量
}

CXLangFile::~CXLangFile()
{
	FreeXLanguage();
}

BOOL CXLangFile::CopyOwn(CBaseObject* pDest)
{
	CExBaseList::CopyOwn(pDest);

	return TRUE;
}

CBaseObject* CXLangFile::Clone()
{
	CXLangFile *pNew = new CXLangFile();
	Copy(pNew);

	return pNew;
}

void CXLangFile::FreeXLanguage()
{
	if (m_bRefXLanguage)
	{
		m_oXLanguage.RemoveAll();
	}
	else
	{
		m_oXLanguage.DeleteAll();
	}

	m_oXLanguage.CloseFile();
}

BOOL CXLangFile::OpenXLangFile()
{
	if (m_bRefXLanguage)
	{
		return TRUE;
	}

	CExBaseObject *pFolder = (CExBaseObject*)GetParent();

	if(pFolder->m_strID.GetLength() == 0)
	{
		return TRUE;
	}

	if (m_oXLanguage.HasOpenXLangFile())
	{
		return TRUE;
	}

	CString strFile;
	strFile = _P_GetLanguagePath(TRUE);
	strFile.AppendFormat(_T("%s\\%s"), pFolder->m_strID, m_strID);

	return m_oXLanguage.OpenXLangFile(strFile);
}

BOOL CXLangFile::HasXLangFileOpen()
{
	if (m_oXLanguage.HasOpenXLangFile())
	{
		return TRUE;
	}

	if (m_oXLanguage.GetCount() > 0)
	{
		return TRUE;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//
CXLangItemDev::CXLangItemDev()
{
	m_nRefCount = 0;
	m_pRefItem = NULL;

}

CXLangItemDev::~CXLangItemDev()
{
	RemoveAll();
}

CXLangItem* CXLangItemDev::FindXLangItem(long nXLangIndex)
{
	CXLangItem *p = NULL;
	CXLangItem *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXLangItem *)GetNext(pos);

		if (p->m_dwItemData == nXLangIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CXLangItemDev::HasError()
{
	if (m_nRefCount != GetCount())
	{
		return TRUE;
	}

	CXLangItem *p = NULL;
	BOOL bHasError = FALSE;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXLangItem *)GetNext(pos);

		if (p->m_strID != m_pRefItem->m_strID)
		{
			bHasError = TRUE;
			break;
		}

		if (p->m_strSrcText != m_pRefItem->m_strSrcText)
		{
			bHasError = TRUE;
			break;
		}
	}

	return bHasError;
}

void CXLangItemDev::DeleteXLang()
{
	CXLangItem *p = NULL;
	POS pos = GetHeadPosition();
	CExBaseList *pParent = NULL;

	while (pos != NULL)
	{
		p = (CXLangItem *)GetNext(pos);
		pParent = (CExBaseList *)p->GetParent();
		pParent->Delete(p);
	}
}

void CXLangItemDev::CopyXLang(CExBaseList &listAllFiles)
{
	POS pos = GetHeadPosition();
	long nIndex = 2;
	long nCount = listAllFiles.GetCount();
	CXLangItem *pFind = NULL;
	CXLangFile *pFile = NULL;
	CXLangFileRsItemMngr *pParent = (CXLangFileRsItemMngr*)GetParent();

	for (nIndex=2; nIndex<=nCount; nIndex++)
	{
		pFind = FindXLangItem(nIndex);
		pFile = (CXLangFile *)listAllFiles.GetAtIndex(nIndex-1);
		ASSERT (pFile != NULL);

		if (pFind == NULL)
		{
			pFind = (CXLangItem*)pFile->m_oXLanguage.FindByID(m_pRefItem->m_strID);

			if (pFind == NULL)
			{
				pFind = (CXLangItem*)m_pRefItem->Clone();
				pFile->m_oXLanguage.AddNewChild(pFind);
			}
			else
			{
				//需要重新关联
				CXLangItemDev *pFindXLangItemDev = pParent->FindXBy_Item(pFind, nIndex);
				ASSERT (pFindXLangItemDev != NULL);
				pFind->m_strSrcText = m_pRefItem->m_strSrcText;
				pFind->m_strTranslation = m_pRefItem->m_strTranslation;
				pFindXLangItemDev->Remove(pFind);
			}

			pFind->m_dwItemData = nIndex;
			pFind->m_dwReserved = nIndex;
			AddTail(pFind);
		}
		else
		{
			pFind->m_strID = m_pRefItem->m_strID;
			pFind->m_strSrcText = m_pRefItem->m_strSrcText;
			pFind->m_strTranslation = m_pRefItem->m_strTranslation;
		}
	}
}


void CXLangItemDev::OverWriteID(CExBaseList &listAllFiles)
{
	POS pos = GetHeadPosition();
	long nIndex = 2;
	long nCount = listAllFiles.GetCount();
	CXLangItem *pFind = NULL;
	CXLangFile *pFile = NULL;
	CXLangFileRsItemMngr *pParent = (CXLangFileRsItemMngr*)GetParent();

	for (nIndex=2; nIndex<=nCount; nIndex++)
	{
		pFind = FindXLangItem(nIndex);
		pFile = (CXLangFile *)listAllFiles.GetAtIndex(nIndex-1);
		ASSERT (pFile != NULL);

		if (pFind == NULL)
		{
			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s：第%d种语言资源不存在"), m_pRefItem->m_strID, nIndex);
		}
		else
		{
			pFind->m_strID = m_pRefItem->m_strID;
		}
	}
}

void CXLangItemDev::OverWriteSrcText(CExBaseList &listAllFiles)
{
	POS pos = GetHeadPosition();
	long nIndex = 2;
	long nCount = listAllFiles.GetCount();
	CXLangItem *pFind = NULL;
	CXLangFile *pFile = NULL;
	CXLangFileRsItemMngr *pParent = (CXLangFileRsItemMngr*)GetParent();

	for (nIndex=2; nIndex<=nCount; nIndex++)
	{
		pFind = FindXLangItem(nIndex);
		pFile = (CXLangFile *)listAllFiles.GetAtIndex(nIndex-1);
		ASSERT (pFile != NULL);

		if (pFind == NULL)
		{
			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s：第%d种语言资源不存在"), m_pRefItem->m_strID, nIndex);
		}
		else
		{
			pFind->m_strSrcText = m_pRefItem->m_strSrcText;
		}
	}
}

void CXLangItemDev::MatchTransText(CExBaseList &listAllFiles)
{
	POS pos = GetHeadPosition();
	long nIndex = 2;
	long nCount = listAllFiles.GetCount();
	CXLangItem *pFind = NULL;
	CXLangFile *pFile = NULL;
	CXLangFileRsItemMngr *pParent = (CXLangFileRsItemMngr*)GetParent();

	for (nIndex=2; nIndex<=nCount; nIndex++)
	{
		pFind = FindXLangItem(nIndex);
		pFile = (CXLangFile *)listAllFiles.GetAtIndex(nIndex-1);
		ASSERT (pFile != NULL);

		if (pFind == NULL)
		{
			CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s：第%d种语言资源不存在"), m_pRefItem->m_strID, nIndex);
		}
		else
		{
			CXLangItem *pTransTextItem = pFile->m_oXLanguage.FindBySrcText(pFind->m_strSrcText);

			if (pTransTextItem != NULL)
			{
				pFind->m_strTranslation = pTransTextItem->m_strTranslation;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//
CXLangFileRsItemMngr::CXLangFileRsItemMngr()
{
	m_bModifiedFlag = FALSE;
}

CXLangFileRsItemMngr::~CXLangFileRsItemMngr()
{
	m_listFiles.RemoveAll();
}

long CXLangFileRsItemMngr::FindXLangItemIndex(CXLangItem *pItem)
{
	POS pos = GetHeadPosition();
	CXLangItemDev *p = NULL;
	long nFindIndex = -1;
	long nIndex = 1;

	while (pos != NULL)
	{
		p = (CXLangItemDev *)GetNext(pos);

		if (p->Find(pItem) != NULL)
		{
			nFindIndex = nIndex;
			return nFindIndex;
		}

		nIndex++;
	}

	return nFindIndex;
}

void CXLangFileRsItemMngr::UpdateRefCount(long nCount)
{
	POS pos = GetHeadPosition();
	CXLangItemDev *p = NULL;

	while (pos != NULL)
	{
		p = (CXLangItemDev *)GetNext(pos);
		p->m_nRefCount = nCount;
	}
}

void CXLangFileRsItemMngr::AddFile(CXLangFile *pFile)
{
	m_listFiles.AddTail(pFile);
	pFile->FreeXLanguage();
	pFile->OpenXLangFile();
	CXLanguage *pXLanguage = &pFile->m_oXLanguage;
	POS pos = pXLanguage->GetHeadPosition();
	CXLangItem *p = NULL;

	while (pos != NULL)
	{
		p = (CXLangItem *)pXLanguage->GetNext(pos);
		AddXLangItem(p);
	}
}

void CXLangFileRsItemMngr::AddFile(CXLangFile *pFile, long nXLangIndex)
{
	m_listFiles.AddTail(pFile);
	pFile->FreeXLanguage();
	pFile->OpenXLangFile();
	CXLanguage *pXLanguage = &pFile->m_oXLanguage;
	POS pos = pXLanguage->GetHeadPosition();
	CXLangItem *p = NULL;

	while (pos != NULL)
	{
		p = (CXLangItem *)pXLanguage->GetNext(pos);
		AddXLangItem(p, nXLangIndex);
	}
}

void CXLangFileRsItemMngr::AddXLangItem(CXLangItem *pItem)
{
	CXLangItemDev *pNew = NULL;
	pNew = new CXLangItemDev();

	pItem->m_dwReserved = 1;
	pItem->m_dwItemData = 1;
	pNew->m_nRefCount = 1;
	
	pNew->m_pRefItem = pItem;
	pNew->AddTail(pItem);
	AddNewChild(pNew);
}

void CXLangFileRsItemMngr::AddXLangItem(CXLangItem *pItem, long nXLangIndex)
{
	CXLangItemDev *pNew = NULL;

	pItem->m_dwReserved = nXLangIndex;
	pItem->m_dwItemData = nXLangIndex;
	pNew = FindXBy_Id_SrcText(pItem, nXLangIndex);

	if (pNew != NULL)
	{
		pNew->m_nRefCount = nXLangIndex;
		pNew->AddTail(pItem);
		return;
	}

	pNew = FindXBy_Id(pItem, nXLangIndex);

	if (pNew != NULL)
	{
		pNew->m_nRefCount = nXLangIndex;
		pNew->AddTail(pItem);
		return;
	}

	pNew = FindXBy_SrcText(pItem, nXLangIndex);

	if (pNew != NULL)
	{
		pNew->m_nRefCount = nXLangIndex;
		pNew->AddTail(pItem);
		return;
	}

	pNew = new CXLangItemDev();
	pNew->m_pRefItem = pItem;
	pNew->AddTail(pItem);
	pNew->m_nRefCount = nXLangIndex;
	AddNewChild(pNew);
}

CXLangItemDev* CXLangFileRsItemMngr::FindXBy_Id_SrcText(CXLangItem *pItem, long nXLangIndex)
{
	POS pos = GetHeadPosition();
	CXLangItemDev *p = NULL;
	CXLangItemDev *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXLangItemDev *)GetNext(pos);

		if (p->m_pRefItem->m_strID == pItem->m_strID 
			&& p->m_pRefItem->m_strSrcText == pItem->m_strSrcText
			&& p->m_nRefCount < nXLangIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CXLangItemDev* CXLangFileRsItemMngr::FindXBy_SrcText(CXLangItem *pItem, long nXLangIndex)
{
	POS pos = GetHeadPosition();
	CXLangItemDev *p = NULL;
	CXLangItemDev *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXLangItemDev *)GetNext(pos);

		if (p->m_pRefItem->m_strSrcText == pItem->m_strSrcText
			&& p->m_nRefCount < nXLangIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CXLangItemDev* CXLangFileRsItemMngr::FindXBy_Id(CXLangItem *pItem, long nXLangIndex)
{
	POS pos = GetHeadPosition();
	CXLangItemDev *p = NULL;
	CXLangItemDev *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXLangItemDev *)GetNext(pos);

		if (p->m_pRefItem->m_strID == pItem->m_strID
			&& p->m_nRefCount < nXLangIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CXLangFileRsItemMngr::DeleteRsItem(CXLangItemDev *pXLangItemDev)
{
	
}

void CXLangFileRsItemMngr::CopyRsItem(CXLangItemDev *pXLangItemDev, CXLangItem *pItem)
{
	
}

void CXLangFileRsItemMngr::SaveXLangFiles()
{
	POS pos = m_listFiles.GetHeadPosition();
	CXLangFile *pFile = NULL;

	while (pos != NULL)
	{
		pFile = (CXLangFile *)m_listFiles.GetNext(pos);
		pFile->m_oXLanguage.SaveLanguagegResourceFile();
	}

	m_bModifiedFlag = FALSE;
}

BOOL CXLangFileRsItemMngr::CopyXLangItems(CExBaseList &listItems)
{
	POS pos = listItems.GetHeadPosition();
	CXLangItemDev *pXLangItemDev = NULL;
	CString strSame, strHasChinese;

	while (pos != NULL)
	{
		pXLangItemDev = (CXLangItemDev *)listItems.GetNext(pos);

		if (pXLangItemDev->FindXLangItem(1) == NULL)
		{
			strHasChinese.AppendFormat(_T("[%s]"), pXLangItemDev->m_pRefItem->m_strID);
		}
	}

	if (strHasChinese.GetLength() > 0)
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("%s：没有中文基础资源"), strHasChinese);
		return FALSE;
	}

	pos = listItems.GetHeadPosition();

	while (pos != NULL)
	{
		pXLangItemDev = (CXLangItemDev *)listItems.GetNext(pos);
		pXLangItemDev->CopyXLang(m_listFiles);
	}

	m_bModifiedFlag = TRUE;

	return TRUE;
}


BOOL CXLangFileRsItemMngr::OverWriteID(CExBaseList &listItems)
{
	CXLangItemDev *pXLangItemDev = NULL;
	POS pos = listItems.GetHeadPosition();

	while (pos != NULL)
	{
		pXLangItemDev = (CXLangItemDev *)listItems.GetNext(pos);
		pXLangItemDev->OverWriteID(m_listFiles);
	}

	m_bModifiedFlag = TRUE;

	return TRUE;
}

BOOL CXLangFileRsItemMngr::OverWriteSrcText(CExBaseList &listItems)
{
	CXLangItemDev *pXLangItemDev = NULL;
	POS pos = listItems.GetHeadPosition();

	while (pos != NULL)
	{
		pXLangItemDev = (CXLangItemDev *)listItems.GetNext(pos);
		pXLangItemDev->OverWriteSrcText(m_listFiles);
	}

	m_bModifiedFlag = TRUE;

	return TRUE;
}

BOOL CXLangFileRsItemMngr::MatchTransText(CExBaseList &listItems)
{
	CXLangItemDev *pXLangItemDev = NULL;
	POS pos = listItems.GetHeadPosition();

	while (pos != NULL)
	{
		pXLangItemDev = (CXLangItemDev *)listItems.GetNext(pos);
		pXLangItemDev->MatchTransText(m_listFiles);
	}

	m_bModifiedFlag = TRUE;

	return TRUE;
}

CXLangItemDev* CXLangFileRsItemMngr::FindXBy_Item(CXLangItem *pItem, long nXLangIndex)
{
	POS pos = GetHeadPosition();
	CXLangItemDev *p = NULL;
	CXLangItemDev *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXLangItemDev *)GetNext(pos);

		if (p->FindXLangItem(nXLangIndex) == pItem)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

