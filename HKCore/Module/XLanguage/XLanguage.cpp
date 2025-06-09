//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguage.cpp  CXLanguage


#include "stdafx.h"
#include "XLanguage.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "XLanguageMngr.h"
#endif

#include "../API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CXLanguage::g_strLanguageStrError = _T("#err#");

CXLanguage::CXLanguage()
{
	//初始化属性

	//初始化成员变量
}

CXLanguage::~CXLanguage()
{
}

void CXLanguage::CloseFile()
{
	m_strXLangFile.Empty();
}

long CXLanguage::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CXLanguageXmlRWKeys *pXmlKeys = (CXLanguageXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CXLanguage::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CXLanguageXmlRWKeys *pXmlKeys = (CXLanguageXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CXLanguage::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CXLanguage::InitAfterRead()
{
}

BOOL CXLanguage::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXLanguage *p = (CXLanguage*)pObj;

	return TRUE;
}

BOOL CXLanguage::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CXLanguage *p = (CXLanguage*)pDest;

	return TRUE;
}

CBaseObject* CXLanguage::Clone()
{
	CXLanguage *p = new CXLanguage();
	Copy(p);
	return p;
}

BOOL CXLanguage::CanPaste(UINT nClassID)
{
	if (nClassID == LGUGCLASSID_CLANGITEM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXLanguage::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXLanguageXmlRWKeys *pXmlKeys = (CXLanguageXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXLangItemKey)
	{
		pNew = new CXLangItem();
	}

	return pNew;
}

CExBaseObject* CXLanguage::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == LGUGCLASSID_CLANGITEM)
	{
		pNew = new CXLangItem();
	}

	return pNew;
}

BOOL CXLanguage::SaveLanguagegResourceFile()
{
	return SaveXmlFile(m_strXLangFile, CXLanguageXmlRWKeys::g_pXmlKeys);
}

BOOL CXLanguage::SaveLanguagegResourceFile(const CString &strFileName)
{
	m_strXLangFile = _P_GetLanguagePath();

	if (strFileName.GetLength() == 0)
	{
        m_strXLangFile.AppendFormat(_T("%s.xml"), m_strID.GetString());
	}
	else
	{
		if (m_strID.GetLength() > 0)
		{
            m_strXLangFile.AppendFormat(_T("%s\\%s.xml"), m_strID.GetString(), strFileName.GetString());
		}
		else
		{
            m_strXLangFile.AppendFormat(_T("%s.xml"), strFileName.GetString());
		}
	}

	return SaveXmlFile(m_strXLangFile, CXLanguageXmlRWKeys::g_pXmlKeys);
}

BOOL CXLanguage::SaveLanguagegResourceFileEx(const CString &strFileName)
{
#ifdef NOT_USE_XLANGUAGE
	return FALSE;
#else
	if (strFileName.GetLength() == 0)
	{
		return FALSE;
	}

// 	m_strXLangFile = _P_GetLanguagePath();
// 	m_strXLangFile.AppendFormat(_T("%s\\%s.xml"), xlang_GetCurrLanguageID(), strFileName);
	m_strXLangFile = xlang_GetCurrLanguagePath(strFileName);

#ifdef _DEBUG
//	TRACE(_T("\r\nSave XLangResourceFile:%s\r\n"), m_strXLangFile);
#endif

	return SaveXmlFile(m_strXLangFile, CXLanguageXmlRWKeys::g_pXmlKeys);
#endif
}

BOOL CXLanguage::SaveLanguagegResourceFile_Chinese(const CString &strFileName, BOOL bUseLangCommonPath)
{
	if (strFileName.GetLength() == 0)
	{
		return FALSE;
	}

	m_strXLangFile = _P_GetLanguagePath(bUseLangCommonPath);
    m_strXLangFile.AppendFormat(_T("Chinese\\%s"), strFileName.GetString());

#ifdef _DEBUG
//	TRACE(_T("\r\nSave XLangResourceFile:%s\r\n"), m_strXLangFile);
#endif

	return SaveXmlFile(m_strXLangFile, CXLanguageXmlRWKeys::g_pXmlKeys);
}

BOOL CXLanguage::HasOpenXLangFile()
{
	return (m_strXLangFile.GetLength() > 0);
}

BOOL CXLanguage::OpenXLangFile(const CString &strFilePath)
{
	m_strXLangFile = strFilePath;
	return OpenXmlFile(m_strXLangFile, CXLanguageXmlRWKeys::g_pXmlKeys);
}

BOOL CXLanguage::LoadLanguagegResourceFile(const CString &strFileName)
{
	m_strXLangFile = _P_GetLanguagePath();

	if (strFileName.GetLength() == 0)
	{
        m_strXLangFile.AppendFormat(_T("%s.xml"), m_strID.GetString());
	}
	else
	{
        m_strXLangFile.AppendFormat(_T("%s\\%s.xml"), m_strID.GetString(), strFileName.GetString());
	}

	return OpenXmlFile(m_strXLangFile, CXLanguageXmlRWKeys::g_pXmlKeys);
}

BOOL CXLanguage::LoadLanguagegResourceFileEx(const CString &strFileName)
{
#ifdef NOT_USE_XLANGUAGE
	return FALSE;
#else
	if (strFileName.GetLength() == 0)
	{
		return FALSE;
	}

// 	m_strXLangFile = _P_GetLanguagePath();
// 	m_strXLangFile.AppendFormat(_T("%s\\%s.xml"), xlang_GetCurrLanguageID(), strFileName);
	m_strXLangFile = xlang_GetCurrLanguagePath(strFileName);

#ifdef _DEBUG
//	TRACE(_T("\r\nOpen XLangResourceFile:%s\r\n"), m_strXLangFile);
#endif

	return OpenXmlFile(m_strXLangFile, CXLanguageXmlRWKeys::g_pXmlKeys);
#endif
}

BOOL CXLanguage::InitResourceByLangFile(CXLanguage *pLangConstResource, BOOL bIsDebug)
{
	POS pos = pLangConstResource->GetHeadPosition();
	CXLangItem *p = NULL;
	CXLangItem *pDest = NULL;
	BOOL bNeedWrite = FALSE;

	while (pos != NULL)
	{
		pDest = (CXLangItem*)pLangConstResource->GetNext(pos);

		//根据Resource，查找语言资源文件对象
		p = (CXLangItem*)FindByID(pDest->m_strID);

		//如果语言资源文件的数据对象存在，则设置
		if (p != NULL)
		{
			//改变Resourc对象的常量数据对象
			if (pDest->m_pstrResourceRef != NULL)
			{
				*pDest->m_pstrResourceRef = p->m_strTranslation;
			}

			//更新语言对象
			pDest->m_strTranslation = p->m_strTranslation;
		}
		else
		{
			if (bIsDebug)
			{
				//如果语言资源文件的数据不存在，则更新语言资源文件
				bNeedWrite = TRUE;
				//AddString(pDest->m_strID, pDest->m_strTranslation);
			}
		}
	}

	return bNeedWrite;
}

BOOL CXLanguage::InsertNoExist(CXLanguage *pLangSrc)
{
	POS pos = pLangSrc->GetHeadPosition();
	CXLangItem *p = NULL;
	CXLangItem *pFind = NULL;
	BOOL bNeedWrite = FALSE;

	while (pos != NULL)
	{
		p = (CXLangItem*)pLangSrc->GetNext(pos);
		pFind = (CXLangItem*)FindByID(p->m_strID);

		//如果语言资源文件的数据对象存在，则设置
		if (pFind == NULL)
		{
			bNeedWrite = TRUE;
			AddString(p->m_strID, p->m_strTranslation);
		}
	}

	return bNeedWrite;
}

// 
// BOOL CXLanguage::InitByResource(CXLanguage *pLangResource)
// {
// 	POS pos = GetHeadPosition();
// 	CXLangItem *p = NULL;
// 	CXLangItem *pDest = NULL;
// 	BOOL bNeedWrite = FALSE;
// 
// 	while (pos != NULL)
// 	{
// 		pDest = (CXLangItem*)GetNext(pos);
// 		p = (CXLangItem*)pLangResource->FindByID(pDest->m_strID);
// 
// 		if (p != NULL)
// 		{
// 			if (pDest->m_pstrResourceRef != NULL)
// 			{
// 				*pDest->m_pstrResourceRef = p->m_strTranslation;
// 			}
// 
// 			pDest->m_strTranslation = p->m_strTranslation;
// 		}
// 		else
// 		{
// 			bNeedWrite = TRUE;
// 			AddString(pDest->m_strID, pDest->m_strTranslation);
// 		}
// 	}
// 
// 	return bNeedWrite;
// }

CXLangItem* CXLanguage::AddString(const CString &strID, const CString &strString)
{
	CXLangItem *pItem = NULL;

	pItem = (CXLangItem *)FindByID(strID);
	//ASSERT(pItem == NULL);

	if (pItem != NULL)
	{
		return pItem;
	}
	
	pItem = new CXLangItem();
	pItem->m_strID = strID;
	pItem->m_strTranslation = strString;

#ifndef _PSX_QT_LINUX_   //2023-2-28  lijunqing  LINUX下，提高加载的效率
	pItem->m_strSrcText = strString;
#endif

	AddNewChild(pItem);
	
	return pItem;
}

CXLangItem* CXLanguage::AddString(const CString &strID, CString *pstrString)
{
	CXLangItem *pItem = NULL;

#ifdef _DEBUG
	pItem = (CXLangItem *)FindByID(strID);

	if (pItem != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, strID);
	}
#endif

	pItem = new CXLangItem();
	pItem->m_strID = strID;
	pItem->m_strTranslation = *pstrString;
	pItem->m_pstrResourceRef = pstrString;
	pItem->m_strSrcText = *pstrString;
	AddNewChild(pItem);

	return pItem;
}


BOOL CXLanguage::xlang_GetLgugStr(const CString &strID, CString &strLanguageString)
{
	CXLangItem *pItem = NULL;
	pItem = (CXLangItem*)FindByID(strID);
	
	if (pItem == NULL)
	{
		strLanguageString = _T("#err#");
		return FALSE;
	}
	else
	{
		strLanguageString = pItem->m_strTranslation;
		return TRUE;
	}
}

const CString& CXLanguage::xlang_GetLgugStr(const CString &strID)
{
	CXLangItem *pItem = NULL;
	pItem = (CXLangItem*)FindByID(strID);
	
	if (pItem == NULL)
	{
		return g_strLanguageStrError;
	}
	else
	{
		return pItem->m_strTranslation;
	}
}


BOOL CXLanguage::RegisterString(const CString &strID, const CString &strString)
{
	CXLangItem *pItem = NULL;
	pItem = (CXLangItem*)FindByID(strID);

	if (pItem != NULL)
	{
		return FALSE;
	}

	AddString(strID, strString);
	
	return TRUE;
}

CXLangItem* CXLanguage::FindBySrcText(const CString &strSrcText)
{
	POS pos = GetHeadPosition();
	CXLangItem *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXLangItem *)GetNext(pos);

		if (p->m_strSrcText == strSrcText)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CXLangItem* CXLanguage::FindBySrcTextAndID(const CString &strID, const CString &strSrcText)
{
	POS pos = GetHeadPosition();
	CXLangItem *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXLangItem *)GetNext(pos);

		if (p->m_strSrcText == strSrcText && p->m_strID == strID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CXLanguage::xlang_GetID(const CString &strObjId, CString &strXLangID)
{
    strXLangID.Format(_T("#s%s"), strObjId.GetString());
	long nIndex = 1;

	while (FindByID(strXLangID) != NULL)
	{
        strXLangID.Format(_T("#s%s_%d"), strObjId.GetString(), nIndex);
		nIndex++;
	}
}

void CXLanguage::xlang_GetID_Ex(CExBaseObject *pObj, CExBaseObject *pParent, CString &strXLangID, long &nIndex)
{
	CString strTemp;

	if (IsStringNumber(pObj->m_strID))
	{
        strTemp.Format(_T("%s_%d"), pParent->m_strID.GetString(), nIndex);
		xlang_GetID(strTemp, strXLangID);
		nIndex++;
	}
	else
	{
		pObj->GetXLangID(strXLangID);

// 		while (FindByID(strXLangID) != NULL)
// 		{
// 			if (pParent == NULL)
// 			{
// 				xlang_GetID(pObj->m_strID, strXLangID);
// 				break;
// 			}
// 
// 			if (pParent->m_strID.GetLength() != 0)
// 			{
// 				strXLangID.AppendFormat(_T("_%s"), pParent->m_strID);
// 			}
// 			
// 			pParent = (CExBaseObject*)pParent->GetParent();
// 		}
	}
}

void CXLanguage::xlang_GetID_Ex(CExBaseObject *pObj, CExBaseObject *pParent, CString &strXLangID)
{
	CString strTemp;

	if (IsStringNumber(pObj->m_strID))
	{
        strTemp.Format(_T("%s_%s"), pParent->m_strID.GetString(), pObj->m_strID.GetString());
		xlang_GetID(strTemp, strXLangID);
	}
	else
	{
		pObj->GetXLangID(strXLangID);

		/*while (FindByID(strXLangID) != NULL)
		{
			if (pParent == NULL)
			{
				xlang_GetID(pObj->m_strID, strXLangID);
				break;
			}

			if (pParent->m_strID.GetLength() != 0)
			{
				strXLangID.AppendFormat(_T("_%s"), pParent->m_strID);
			}

			pParent = (CExBaseObject*)pParent->GetParent();
		}*/
	}
}

void CXLanguage::xlang_Buid(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CXLangItem *pXLangItem = NULL;
	CString strXLangID, strTemp;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->m_strName.GetLength() > 0)
		{
			if (p->m_strName.GetAt(0) != '#')
			{
				pXLangItem = FindBySrcText(p->m_strName);

				if (pXLangItem == NULL)
				{
					if (IsStringNumber(p->m_strID))
					{
                        strTemp.Format(_T("%s_%d"), pList->m_strID.GetString(), nIndex);
						xlang_GetID(strTemp, strXLangID);
						nIndex++;
					}
					else
					{
						xlang_GetID(p->m_strID, strXLangID);
					}
					
					AddString(strXLangID, p->m_strName);
					p->m_strName = strXLangID;
				}
				else
				{
					p->m_strName = pXLangItem->m_strID;
				}
			}
		}

		if (p->IsBaseList())
		{
			xlang_Buid((CExBaseList*)p);
		}
	}
}

void CXLanguage::xlang_BuidEx(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CXLangItem *pXLangItem = NULL;
	CString strXLangID, strTemp;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->m_strName.GetLength() > 0)
		{
			pXLangItem = FindBySrcText(p->m_strName);

			if (pXLangItem == NULL)
			{
				//xlang_GetID_Ex(p, pList, strXLangID, nIndex);
				xlang_GetID_Ex(p, pList, strXLangID);
				pXLangItem = AddString(strXLangID, p->m_strName);
				p->m_dwItemData = (DWORD)pXLangItem;
			}
			else
			{
				//如果ID不同，则不能使用同一个资源
				if (p->m_strID == pXLangItem->m_strID.Mid(2))
				{
					p->m_dwItemData = (DWORD)pXLangItem;
				}
				else
				{
					xlang_GetID_Ex(p, pList, strXLangID);
					pXLangItem = AddString(strXLangID, p->m_strName);
					p->m_dwItemData = (DWORD)pXLangItem;

					//if (FindBySrcTextAndID(strXLangID, pXLangItem->m_strSrcText) == NULL)
					//{//相同的ID，相同的资源文本如果不存在
					//	pList->GetXLangID(p, strXLangID);

					//	if (FindBySrcTextAndID(strXLangID, pXLangItem->m_strSrcText) == NULL)
					//	{//相同的ID，相同的资源文本如果不存在
					//		xlang_GetID_Ex(p, pList, strXLangID, nIndex);
					//		pXLangItem = AddString(strXLangID, p->m_strName);
					//		p->m_dwItemData = (DWORD)pXLangItem;
					//	}
					//	else
					//	{
					//		p->m_dwItemData = (DWORD)pXLangItem;
					//	}
					//}
					//else
					//{
					//	p->m_dwItemData = (DWORD)pXLangItem;
					//}
				}
			}
		}

		if (p->IsBaseList())
		{
			xlang_BuidEx((CExBaseList*)p);
		}
	}
}

void CXLanguage::xlang_Translate(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CXLangItem *pXLangItem = NULL;
	CString strXLangID;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->m_strName.GetLength() > 0)
		{
			if (p->m_strName.GetAt(0) == '#')
			{
				pXLangItem = (CXLangItem*)FindByID(p->m_strName);

				if (pXLangItem != NULL)
				{
					p->m_strName = pXLangItem->m_strTranslation;
				}
			}
		}

		if (p->IsBaseList())
		{
			xlang_Translate((CExBaseList*)p);
		}
	}
}


void CXLanguage::xlang_TranslateEx(CExBaseList *pList, CExBaseList *pListErr)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CXLangItem *pXLangItem = NULL;
	CXLangItem *pTemp = NULL;
	CString strXLangID;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		pTemp = (CXLangItem *)p->m_dwItemData;

		if (pTemp != NULL)
		{
			pXLangItem = (CXLangItem*)FindByID(pTemp->m_strID);

			if (pXLangItem != NULL)
			{
				p->m_strName = pXLangItem->m_strTranslation;
			}
			else
			{
				if (pListErr != NULL)
				{
					pXLangItem = new CXLangItem();
					pXLangItem->m_strID = pTemp->m_strID;
					pXLangItem->m_strName = pTemp->m_strID;
					pXLangItem->m_strSrcText = p->m_strName;
					pXLangItem->m_strTranslation = p->m_strName;

					pListErr->AddTail(pXLangItem);
				}
			}
		}

		if (p->IsBaseList())
		{
			xlang_TranslateEx((CExBaseList*)p, pListErr);
		}
	}
}

