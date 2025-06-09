//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XKeyBase.cpp  CXKeyBase


#include "stdafx.h"
#include "XKeyBase.h"
#include "XMultiKeyBase.h"

#include "XKeyStringParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL xchar_CanOffset(wchar_t xChar);

//////////////////////////////////////////////////////////////////////////
CXKeyMatchRef::CXKeyMatchRef()
{
	m_nArrayIndex = -1;
	//m_nArrayIndexAfter = -1;
	//   m_nArrayIndexBefore = -1;
	m_pXKeyRef = NULL;
}

CXKeyMatchRef::~CXKeyMatchRef()
{

}

CXKeyMatchRef* CXKeyMatchRef::Clone()
{
	CXKeyMatchRef *pNew = new CXKeyMatchRef();
	pNew->m_pXKeyRef = m_pXKeyRef;
	pNew->m_nArrayIndex = m_nArrayIndex;

	return pNew;
}

void CXKeyMatchRef::Init(CXKeyBase *pKey)
{
	m_pXKeyRef = pKey;
	//m_nArrayIndex = pKey->m_ni
}

BOOL CXKeyMatchRef::Match(CXKeyMatchRef *pXKeyMatchRef)
{
	if (m_pXKeyRef == NULL && pXKeyMatchRef->m_pXKeyRef == NULL)
	{
		return m_nArrayIndex == pXKeyMatchRef->m_nArrayIndex;
	}

	if (m_pXKeyRef == NULL || pXKeyMatchRef->m_pXKeyRef == NULL)
	{
		return FALSE;
	}

	ASSERT (m_pXKeyRef != NULL); 

	if (m_pXKeyRef == pXKeyMatchRef->m_pXKeyRef)
	{//如果是相同的Key，
		if (m_pXKeyRef->IsArrayKey())
		{//则判断是否为数组关键字,比较下标是否相同
			return (m_nArrayIndex == pXKeyMatchRef->m_nArrayIndex);
		}
		else
		{
			return TRUE;
		}
	}
	else
	{//如果是不同的Key
		if (m_pXKeyRef->m_dwMultiKeyArray == 0 || pXKeyMatchRef->m_pXKeyRef->m_dwMultiKeyArray == 0)
		{//没有关联的MultiKey，即单一关键字
			return FALSE;
		}
		else
		{
			CXMultiKeyBase *pMkey1 = xkey_Get_XMultiKeyBase(m_nArrayIndex, m_pXKeyRef);
			CXMultiKeyBase *pMkey2 = xkey_Get_XMultiKeyBase(pXKeyMatchRef->m_nArrayIndex, pXKeyMatchRef->m_pXKeyRef);

			if (pMkey1 != NULL && pMkey2 != NULL)
			{
				return (pMkey1 == pMkey2);
			}
			else
			{
				return FALSE;
			}
		}
	}
}

long CXKeyMatchRef::GetImportance()
{
//	ASSERT (m_pXKeyRef != NULL);

	if (m_pXKeyRef == NULL)
	{
		return 80;
	}

	return m_pXKeyRef->m_nImportance;
}

BOOL CXKeyMatchRef::IsSubKey(CXKeyMatchRef *pXKeyRef)
{
	ASSERT (m_pXKeyRef != NULL);

	return m_pXKeyRef->IsSubKey(pXKeyRef->m_pXKeyRef);
}

BOOL CXKeyMatchRef::IsArrayKey()
{
	if (m_pXKeyRef == NULL)
	{
		return FALSE;
	}

	return m_pXKeyRef->IsArrayKey() ;
}

BOOL CXKeyMatchRef::IsArrayTypeBefore()
{
	if (m_pXKeyRef == NULL)
	{
		return FALSE;
	}

	return m_pXKeyRef->IsArrayTypeBefore() ;
}

BOOL CXKeyMatchRef::IsArrayTypeAfter()
{
	if (m_pXKeyRef == NULL)
	{
		return FALSE;
	}

	return m_pXKeyRef->IsArrayTypeAfter() ;
}

BOOL CXKeyMatchRef::IsArrayTypeAll()
{
	if (m_pXKeyRef == NULL)
	{
		return FALSE;
	}

	return m_pXKeyRef->IsArrayTypeAll() ;
}

BOOL CXKeyMatchRef::IsNumber()
{
	if (m_pXKeyRef == NULL && m_nArrayIndex > 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


CXKeyMatchRef* CXKeyMatchRefList::AddKey(CXKeyBase *pXKey, long nArrayIndex)
{
	CXKeyMatchRef *pKeyRef = new CXKeyMatchRef();
	pKeyRef->m_pXKeyRef = pXKey;
	pKeyRef->m_nArrayIndex = nArrayIndex;
	AddTail(pKeyRef);

	return pKeyRef;
}

BOOL CXKeyMatchRefList::IsSubKey(CXKeyMatchRef *pXKeyRef,CString strText)
{
	POS pos = GetHeadPosition();
	CXKeyMatchRef *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p == pXKeyRef)
		{
			continue;
		}

		//剔除子关键字，位置相同时剔除，不同不剔除
		long m_pos,m_posRef,m_LengthRef,m_Length;
		m_pos=strText.Find(p->m_pXKeyRef->m_strName);
		m_posRef=strText.Find(pXKeyRef->m_pXKeyRef->m_strName);
		m_Length=p->m_pXKeyRef->m_strName.GetLength();
		m_LengthRef=pXKeyRef->m_pXKeyRef->m_strName.GetLength();
		if (p->IsSubKey(pXKeyRef))
		{

			if (m_posRef>=m_pos && (m_pos+m_Length)>=m_posRef)
			{
				if (m_pos==m_posRef && pXKeyRef->m_pXKeyRef->m_nIsArray==1)
				{ 

					CString chartemp=strText.Mid(m_posRef+m_LengthRef,m_Length-m_LengthRef);

					long longtemp =CString_To_long(chartemp);
					if (pXKeyRef->m_nArrayIndex>longtemp)
					{
						return FALSE;
					}
				}
				return TRUE;
			}
			else
			{

				continue;
			}
		}
		else
		{
			if (m_pos>=m_posRef && m_Length<m_LengthRef)

			{

				if (m_pos==m_posRef && p->m_pXKeyRef->m_nIsArray==1)
				{ 

					CString chartempref=strText.Mid(m_pos+m_Length,m_LengthRef-m_Length);

					long longtempref =CString_To_long(chartempref);
					if (p->m_nArrayIndex>longtempref)
					{
						return TRUE;
					}
				}

			}
		}
	}

	return FALSE;
}

BOOL CXKeyMatchRefList::Match(CXKeyMatchRef *pXKeyRef)
{
	POS pos = GetHeadPosition();
	CXKeyMatchRef *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->Match(pXKeyRef))
		{
			return TRUE;
		}
	}

	return FALSE;
}

//2022-5-10  lijunqing
void CXKeyMatchRefList::RemoveKey(CXKeyMatchRef *pXKeyRef)
{
	POS pos = GetHeadPosition();
	CXKeyMatchRef *p = NULL;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = GetNext(pos);

		if (p->Match(pXKeyRef))
		{
			RemoveAt(posPrev);
			delete p;
		}
	}
}

long CXKeyMatchRefList::XFindIndex(CXKeyMatchRef *pXKeyRef)
{
	POS pos = GetHeadPosition();
	CXKeyMatchRef *p = NULL;
	long nIndex = 0;
	long nIndexFind = -1;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->Match(pXKeyRef))
		{
			nIndexFind = nIndex;
		}

		nIndex++;
	}

	return nIndexFind;
}

void CXKeyMatchRefList::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{

}

CXKeyBase* CXKeyMatchRefList::FindByName(const CString &strName)
{
	CXKeyMatchRef* pTemp = NULL;
	CXKeyMatchRef* pFind = NULL;

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->m_pXKeyRef->m_strName == strName)
		{
			pFind = pTemp;
			break;
		}
	}

	if (pFind == NULL)
	{
		return NULL;
	}
	else
	{
		return pFind->m_pXKeyRef;
	}
}

CXKeyBase* CXKeyMatchRefList::FindByID(const CString &strID)
{
	CXKeyMatchRef* pTemp = NULL;
	CXKeyMatchRef* pFind = NULL;

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pTemp = GetNext(pos);

		if (pTemp->m_pXKeyRef->m_strID == strID)
		{
			pFind = pTemp;
			break;
		}
	}

	if (pFind == NULL)
	{
		return NULL;
	}
	else
	{
		return pFind->m_pXKeyRef;
	}
}

BOOL CXKeyMatchRefList::Match(CXKeyMatchRefList *pDstXKeys, long &nMatchRatio)
{
	ASSERT (pDstXKeys != NULL);

	BOOL bTrue = TRUE;
	POS pos = GetHeadPosition();
	CXKeyMatchRef *p = NULL;
	long nMatchCount = 0;
	long nSrcCount = GetCount();
	long nDstCount = pDstXKeys->GetCount();
	long nClassID = 0;
	long nImportance = 0;
	BOOL bIsSubKey = FALSE;
	long nTotal = 0;
	nMatchRatio = 0;

	if (nSrcCount == 0 || nDstCount == 0)   //shaolei 2018.10.30
	{
		return FALSE;
	}

	while (pos != NULL)
	{
		p = GetNext(pos);

		bIsSubKey = pDstXKeys->IsSubKey(p, nImportance);
		//nTotal += nImportance * bIsSubKey;

		if (bIsSubKey)
		{
			nMatchCount++;
		}
		// 		if ((nImportance > 90) && (!bIsSubKey))
		// 		{
		// 			nMatchCount = 0;
		// 			break;
		// 		}
		// 		else if (bIsSubKey)
		// 		{
		// 			nMatchCount++;
		// 		}
	}

	long nTemp = nMatchCount * 200;
	nTemp = nTemp / (nSrcCount + nDstCount);
	bTrue = (nSrcCount == nMatchCount /*&& nDstCount == nMatchCount*/);  //shaolei 2018.10.30
	//nMatchRatio += nTemp;
	nMatchRatio = nTemp;  //shaolei 2018.11.01

	return bTrue;
}

//2023-2-6  lijunqing 判断是否为子集
BOOL CXKeyMatchRefList::IsSubset(CXKeyMatchRefList *pKeysSub)
{
	POS pos = pKeysSub->GetHeadPosition();
	CXKeyMatchRef *p = NULL;

	while (pos != NULL)
	{
		p = (CXKeyMatchRef *)pKeysSub->GetNext(pos);

		if (! Match(p))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CXKeyMatchRefList::IsSubKey(CXKeyMatchRef *pXKey, long &nImportance)
{
	ASSERT (pXKey != NULL);
	nImportance = pXKey->GetImportance();

	return Match(pXKey);
}

//////////////////////////////////////////////////////////////////////////
CXKeyBase::CXKeyBase()
{
	//初始化属性
	m_nImportance = 0;
	m_nIsArray = 0;

	m_dwMultiKeyArray = 0;
	m_pMultiKeyArray = NULL;

	//m_nArrayIndexTotal = -1;
	//ArabinNum="123456789";
	//ChnNum="一二三四五六七八九";
	//ChnNum1="百十零";
	//RomNum="ⅠⅡⅢⅣⅤⅥⅦⅧⅨ";
	//RomNum1="I 1 II 2 III 3 IV 4 V 5 VI 6 VII 7 VIII 8 IX 9";
	//初始化成员变量
}

CXKeyBase::~CXKeyBase()
{
	delete m_pMultiKeyArray;
	m_pMultiKeyArray = NULL;
}

long CXKeyBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strImportanceKey, oNode, m_nImportance);
	xml_GetAttibuteValue(pXmlKeys->m_strIsArrayKey, oNode, m_nIsArray);
// 	xml_GetAttibuteValue(pXmlKeys->m_strArrayIndexKey, oNode, m_nArrayIndexTotal);

	return 0;
}

long CXKeyBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strImportanceKey, oElement, m_nImportance);
	xml_SetAttributeValue(pXmlKeys->m_strIsArrayKey, oElement, m_nIsArray);

	return 0;
}

long CXKeyBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nImportance);
		BinarySerializeCalLen(oBinaryBuffer, m_nIsArray);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nImportance);
		BinarySerializeRead(oBinaryBuffer, m_nIsArray);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nImportance);
		BinarySerializeWrite(oBinaryBuffer, m_nIsArray);
	}

	return 0;
}

// 
// BOOL CXKeyBase::IsCharVarChar(wchar_t xChar)
// {
// 	if ('0' <= xChar && xChar <= '9')
// 	{
// 		return TRUE;
// 	}
// 
// 	if ('a' <= xChar && xChar <= 'z')
// 	{
// 		return TRUE;
// 	}
// 
// 	if ('A' <= xChar && xChar <= 'Z')
// 	{
// 		return TRUE;
// 	}
// 
// 	if ('-' == xChar)
// 	{
// 		return TRUE;
// 	}
// 
// 	if ('_' == xChar)
// 	{
// 		return TRUE;
// 	}
// 
// 	return FALSE;
// }
// 
// void CXKeyBase::OffsetBefore(const CString &strText, long &nPos)
// {
// 	wchar_t xChar = 0;
// 
// 	//跳过一些字符
// 	while (nPos>=0)
// 	{
// 		xChar = strText.GetAt(nPos);
// 
// 		if (xChar == '-' || xChar == '_')
// 		{
// 			nPos--;
// 		}
// 		else
// 		{
// #ifdef _UNICODE
// 			if (xchar_CanOffset(xChar))
// 			{
// 				nPos--;
// 			}
// #else
// 			CString strTemp;
// 			strTemp = strText.Mid(nPos-2);
// 			if (strTemp == _T("号"))
// 			{
// 				nPos -= 2;
// 			}
// #endif
// 			else
// 			{
// 				break;
// 			}
// 		}
// 	}
// }

void CXKeyBase::InitAfterRead()
{

}

BOOL CXKeyBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXKeyBase *p = (CXKeyBase*)pObj;

	if(m_nImportance != p->m_nImportance)
	{
		return FALSE;
	}

	if(m_nIsArray != p->m_nIsArray)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXKeyBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CXKeyBase *p = (CXKeyBase*)pDest;

	p->m_nImportance = m_nImportance;
	p->m_nIsArray = m_nIsArray;

	return TRUE;
}

CBaseObject* CXKeyBase::Clone()
{
	CXKeyBase *p = new CXKeyBase();
	Copy(p);
	return p;
}

// BOOL CXKeyBase::CmpAscii(const CString &strText, long nPos, long nCmpLen)
// {
// 	long nIndex = 0;
// 	long nEndPos = nPos + nCmpLen;
// 	wchar_t xCharSrc = 0;
// 	wchar_t xCharDest = 0;
// 
// 	for (nIndex=nPos; nIndex<nEndPos; nIndex++)
// 	{
// 		xCharSrc = strText.GetAt(nIndex);
// 
// 		if (xCharSrc > 128)
// 		{
// 			return FALSE;
// 		}
// 
// 		xCharDest = m_strName.GetAt(nIndex - nPos);
// 
// 		if (::toupper(xCharDest) != ::toupper(xCharSrc))
// 		{
// 			return FALSE;
// 		}
// 	}
// 
// 	return TRUE;
// }
// 
// long CXKeyBase::FindPos(const CString &strText)
// {
// 	long nLenKey = m_strName.GetLength();
// 	long nLenText = strText.GetLength();
// 
// 	if (nLenText < nLenKey)
// 	{
// 		return -1;
// 	}
// 
// 	long nIndex = 0;
// 	long nCmpCount = nLenText - nLenKey;
// 	long nFind = -1;
// 
// 	for (nIndex=0; nIndex<= nCmpCount; nIndex++)
// 	{
// 		if (CmpAscii(strText, nIndex, nLenKey))
// 		{
// 			nFind = nIndex;
// 			break;
// 		}
// 	}
// 
// 	return nFind;
// }

BOOL CXKeyBase::Query(const CString &strText, CXKeyMatchRefList *pListKeys)
{
	long nPos =QueryString(strText, m_strName);

	if (nPos < 0)
	{
		return FALSE;
	}

	pListKeys->AddKey(this);

	return TRUE;
}

BOOL CXKeyBase::Match(CXKeyBase *pKey)
{
	return (this == pKey);
}

BOOL CXKeyBase::IsSubKey(CXKeyBase *pXKeyRef)
{
	if (xkeydb_IsXKeyBase(pXKeyRef))
	{
		return (m_strName.Find(pXKeyRef->m_strName) >= 0);
	}
	else
	{
		return FALSE;
	}
}

BOOL CXKeyBase::IsArrayKey()
{
	return (m_nIsArray > 0);
}

BOOL CXKeyBase::IsArrayTypeBefore()
{
	return (m_nIsArray == 1);
}

BOOL CXKeyBase::IsArrayTypeAfter()
{
	return (m_nIsArray == 2);
}

BOOL CXKeyBase::IsArrayTypeAll()
{
	return (m_nIsArray == 3);
}

void CXKeyBase::InitMultiKeyArray(CExBaseList &listMultiKey)
{
	m_dwMultiKeyArray = listMultiKey.GetCount();
	if (m_dwMultiKeyArray == 0)
	{
		return;
	}

	m_pMultiKeyArray = new DWORD [m_dwMultiKeyArray];
	DWORD *pMultiKeyArray = m_pMultiKeyArray;
	POS pos = listMultiKey.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = listMultiKey.GetNext(pos);
		*pMultiKeyArray = (DWORD)p;
		pMultiKeyArray++;
	}
}

CXMultiKeyBase* CXKeyBase::GetXMultiKeyBase(long nArrayIndex)
{
	CXMultiKeyBase *pXMultiKey = NULL;
	CXMultiKeyBase *pFind = NULL;
	long nIndex = 0;

	for (nIndex=0; nIndex<m_dwMultiKeyArray; nIndex++)
	{
		pXMultiKey = (CXMultiKeyBase *)m_pMultiKeyArray[nIndex];

		if (pXMultiKey->HasXKey(nArrayIndex, this))
		{
			pFind = pXMultiKey;
			break;
		}
	}

	return pFind;
}

BOOL CXKeyBase::QueryString(const CString &strText, const CString &strKey)
{
	long nPos = xkey_find_string_pos(strText, strKey, 0);

	return (nPos >= 0);
}

#ifdef _UNICODE

const wchar_t* xkey_find_string(const wchar_t *strText, const wchar_t *strKey, long nPos)
{
	long nLenSrc = wcslen(strText);
	long nLen = wcslen(strKey);

	if (nLenSrc < nPos)
	{
		return NULL;
	}

	if (nLenSrc < nPos + nLen)
	{
		return NULL;
	}

	const wchar_t *pBegin = strText + nPos;
	const wchar_t *pFindEnd =   strText + nLenSrc - nLen;
	const wchar_t *pFind = NULL;

	while ( pBegin <= pFindEnd )
	{
		if (_wcsnicmp(pBegin, strKey, nLen) == 0)
		{
			pFind = pBegin;
			break;
		}

		pBegin++;
	}

	return pFind;
}

long xkey_find_string_pos(const wchar_t *strText, const wchar_t *strKey, long nPos)
{
	const wchar_t *pFind = xkey_find_string(strText, strKey, nPos);

	if (pFind == NULL)
	{
		return  -1;
	}

	return pFind - strText;
}

#else


char* xkey_find_string(const char *strText, const char *strKey, long nPos)
{
	long nLenSrc = strlen(strText);
	long nLen = strlen(strKey);

	if (nLenSrc <= nPos)
	{
		return NULL;
	}

	if (nLenSrc < nPos + nLen)
	{
		return NULL;
	}

	const char *pBegin = strText + nPos;
	const char *pFindEnd =   strText + nLenSrc - nLen + 1;
	const char *pFind = NULL;

	while ( pBegin <= pFindEnd )
	{
#ifndef _PSX_QT_LINUX_
		if (strnicmp(pBegin, strKey, nLen) == 0)
		{
			pFind = pBegin;
			break;
		}
#else
        if (stricmp(pBegin, strKey) == 0)
        {
            pFind = pBegin;
            break;
        }
#endif

		pBegin++;
	}

	return (char*)pFind;
}

long xkey_find_string_pos(const char *strText, const char *strKey, long nPos)
{
	char *pFind = xkey_find_string(strText, strKey, nPos);

	if (pFind == NULL)
	{
		return  -1;
	}

	return pFind - strText;
}

#endif


long xkey_find_string_pos(const CString &strText, const CString &strKey, long nPos)
{
#ifdef _UNICODE
	const wchar_t *pszText = strText.GetString();
	const wchar_t *pszKey = strKey.GetString();
	return xkey_find_string_pos(pszText, pszKey, nPos);
#else

#ifndef _PSX_IDE_QT_
	const char *pszText = strText.GetString();
	const char *pszKey = strKey.GetString();
	return xkey_find_string_pos(pszText, pszKey, nPos);
#else
	return strText.Find(strKey, nPos);
#endif

#endif
}


//////////////////////////////////////////////////////////////////////////
//CXKeyMngr
CXKeyMngr::CXKeyMngr()
{

}

CXKeyMngr::~CXKeyMngr()
{

}

long CXKeyMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CXKeyMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CXKeyMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

void CXKeyMngr::InitAfterRead()
{
	
}

BOOL CXKeyMngr::IsEqualOwn(CBaseObject* pObj)
{
	return 0;
}

BOOL CXKeyMngr::CopyOwn(CBaseObject* pDest)
{
	return 0;
}

CBaseObject* CXKeyMngr::Clone()
{
	CXKeyMngr *pNew = new CXKeyMngr();
	Copy(pNew);

	return pNew;
}


CExBaseObject* CXKeyMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCXKeyBaseKey)
	{
		pNew = new CXKeyBase();
	}

	return pNew;
}



//////////////////////////////////////////////////////////////////////////
//

CXMultiKeyBase* xkey_Get_XMultiKeyBase(long nArrayIndex, CXKeyBase *pXKey)
{
	ASSERT (pXKey->m_dwMultiKeyArray > 0);
	return pXKey->GetXMultiKeyBase(nArrayIndex);
}

