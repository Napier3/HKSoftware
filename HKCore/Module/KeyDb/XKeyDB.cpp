//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XKeyDB.cpp  CXKeyDB


#include "stdafx.h"
#include "XKeyDB.h"
#include "XKeyBase.h"
#include "XKeyStringParser.h"
#include "../API/GlobalConfigApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXKeyDB::CXKeyDB()
{
	//初始化属性
	m_pdwKeyRefBuffer = NULL;

	//初始化成员变量
	m_pXKeyMngr = NULL;
	m_pXKeyMaps = NULL;
	m_nMinRate = 0;

	CKeyDbXmlRWKeys::Create();
	CXCharNumConfig::Create();
}

CXKeyDB::~CXKeyDB()
{
	FreeKeyRefBuffer();
	CXCharNumConfig::Release();
	CKeyDbXmlRWKeys::Release();
}

//2022-5-10  lijunqing
void CXKeyDB::SetRemoveSubKeys(bool b)
{
	CXKeyStringParser::SetRemoveSubKeys(b);
}


long CXKeyDB::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strMinRateKey, oNode, m_nMinRate);

	return 0;
}

long CXKeyDB::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strMinRateKey, oElement, m_nMinRate);

	return 0;
}

long CXKeyDB::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nMinRate);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nMinRate);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nMinRate);
	}

	return 0;
}

void CXKeyDB::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == KDBCLASSID_CXKEYMNGR)
		{
			m_pXKeyMngr = (CXKeyMngr *)p;
		}
		else if (nClassID == KDBCLASSID_CXKEYMAPS)
		{
			m_pXKeyMaps = (CXKeyMaps *)p;
		}
	}

	if (m_pXKeyMngr == NULL)
	{
		m_pXKeyMngr = new CXKeyMngr();
		AddNewChild(m_pXKeyMngr);
	}

	if (m_pXKeyMaps == NULL)
	{
		m_pXKeyMaps = new CXKeyMaps();
		AddNewChild(m_pXKeyMaps);
	}
}

long CXKeyDB::UpdateXKeyMngrByMap()
{
	long nAddCount = 0;
	CXMultiKeyBase *p = NULL;
	POS pos = m_pXKeyMaps->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXMultiKeyBase *)m_pXKeyMaps->GetNext(pos);
		nAddCount += UpdateXKeyMngrByMap(p);
	}

	return nAddCount;
}

long CXKeyDB::UpdateXKeyMngrByMap(CXMultiKeyBase *pXMultiKey)
{
	CXMultiSubKey *p = NULL;
	POS pos = pXMultiKey->GetHeadPosition();
	long nAddCount = 0;

	while (pos != NULL)
	{
		p = (CXMultiSubKey*)m_pXKeyMaps->GetNext(pos);
		
		if (m_pXKeyMngr->FindByName(p->m_strName) == NULL)
		{
			CXKeyBase *pNew = new CXKeyBase();
			pNew->m_strName = p->m_strName;
			pNew->m_strID = p->m_strID;

			if (p->m_nArrayIndex > 0)
			{
				pNew->m_nIsArray = 3;
			}

			m_pXKeyMngr->AddNewChild(pNew);
			nAddCount++;
		}
	}

	return nAddCount;
}

void CXKeyDB::InitMultiKeyArray()
{
	POS pos = m_pXKeyMngr->GetHeadPosition();
	CXKeyBase *pKey = NULL;

	while (pos != NULL)
	{
		pKey = (CXKeyBase *)m_pXKeyMngr->GetNext(pos);
		InitMultiKeyArray(pKey);
	}
}

void CXKeyDB::InitMultiKeyArray(CXKeyBase *pXKey)
{
	CExBaseList listMultiKey;
	POS pos = m_pXKeyMaps->GetHeadPosition();
	CXMultiKeyBase *pMultiKey = NULL;
	CXMultiSubKey *pSub = NULL;

	while (pos != NULL)
	{
		pMultiKey = (CXMultiKeyBase *)m_pXKeyMaps->GetNext(pos);
		pSub = (CXMultiSubKey *)pMultiKey->FindByName(pXKey->m_strName);

		if (pSub != NULL)
		{
			if (pSub->m_strName == pXKey->m_strName)
			{
				pSub->m_pXKeyRef = pXKey;
				listMultiKey.AddTail(pMultiKey);
			}
		}
	}

	pXKey->InitMultiKeyArray(listMultiKey);

	listMultiKey.RemoveAll();
}

BOOL CXKeyDB::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXKeyDB *p = (CXKeyDB*)pObj;

	if(m_nMinRate != p->m_nMinRate)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXKeyDB::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXKeyDB *p = (CXKeyDB*)pDest;
	p->m_nMinRate = m_nMinRate;

	return TRUE;
}

CBaseObject* CXKeyDB::Clone()
{
	CXKeyDB *p = new CXKeyDB();
	Copy(p);
	return p;
}

BOOL CXKeyDB::CanPaste(UINT nClassID)
{
	if (nClassID == KDBCLASSID_CXKEYBASE)
	{
		return TRUE;
	}

	if (nClassID == KDBCLASSID_CXMULTIKEYBASE)
	{
		return TRUE;
	}
	/*if (nClassID == KDBCLASSID_CXMATCHKEYBASE)
	{
		return TRUE;
	}*/
	if (nClassID == KDBCLASSID_CXKEYGROUPBASE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXKeyDB::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCXKeyMngrKey)
	{
		pNew = new CXKeyMngr();
	}
	else if (strClassID == pXmlKeys->m_strCXKeyMapsKey)
	{
		pNew = new CXKeyMaps();
	}

	return pNew;
}


CExBaseObject* CXKeyDB::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == KDBCLASSID_CXKEYMNGR)
	{
		pNew = new CXKeyMngr();
	}
	else if (nClassID == KDBCLASSID_CXKEYMAPS)
	{
		pNew = new CXKeyMaps();
	}
	else
	{
		ASSERT (FALSE);
	}

	return pNew;
}


DWORD CXKeyDB::Filter(const CString &strTxtFilter, DWORD dwMode)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->FilterOwn(strTxtFilter, dwMode);
	}

	return 0;
}

void CXKeyDB::OpenKeyDbFile(const CString &strFileName, BOOL bCommon)
{
	CString strFilePath;

	if (bCommon)
	{
		strFilePath = _P_GetCommonLibraryPath();
	}
	else
	{
		strFilePath = _P_GetLibraryPath();
	}

	OpenKeyDbFile(strFileName, strFilePath);
}

void CXKeyDB::OpenKeyDbFile(const CString &strFileName, const CString &strPath)
{
	CString strFile;

	if (strPath.GetLength() < 2)
	{
		strFile = _P_GetLibraryPath();
	}
	else
	{
		strFile = strPath;
	}

	if (strFileName.GetLength() < 5)
	{
		strFile += _T("RelayTestKeyDb.xml");
	}
	else
	{
		strFile += strFileName;
	}

	OpenKeyDbFile(strFile);
}

void CXKeyDB::OpenKeyDbFile(const CString &strFilePath)
{
	DeleteAll();
	m_pXKeyMaps = NULL;
	m_pXKeyMngr = NULL;
	
	if (!OpenXmlFile(strFilePath, CKeyDbXmlRWKeys::CXKeyDBKey(), CKeyDbXmlRWKeys::g_pXmlKeys))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("KeyDB file [%s] not exit!"), strFilePath.GetString());
		InitAfterRead();
	}
	
	long nCount = UpdateXKeyMngrByMap();

	if (nCount > 0)
	{
		SaveKeyDbFile(strFilePath);
	}
	
	InitKeyRefBuffer();
	InitMultiKeyArray();
	m_strXKeyDbFile = strFilePath;
}

void CXKeyDB::InsertKeyDbFile(const CString &strFilePath)
{
	CXKeyDB oKeyDB;
	oKeyDB.OpenKeyDbFile(strFilePath);

	if (GetCount() == 0)
	{
		Append(oKeyDB);
		oKeyDB.RemoveAll();
	}
	else
	{
		CExBaseObject *p = NULL;
		POS pos = oKeyDB.GetHeadPosition();

		while (pos != NULL)
		{
			p = oKeyDB.GetNext(pos);

			if (FindByName(p->m_strName) == NULL)
			{
				AddNewChild((CExBaseObject*)p->Clone());
			}
		}
	}
}

void CXKeyDB::SaveKeyDbFile(const CString &strFile)
{
	CString strSaveFile = strFile;

	if (strSaveFile.GetLength() == 0)
	{
		strSaveFile = m_strXKeyDbFile;
	}

	SaveXmlFile(strSaveFile, CKeyDbXmlRWKeys::g_pXmlKeys);
}

void CXKeyDB::InitKeyRefBuffer(CExBaseList *pList, CExBaseList *pListDst)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == KDBCLASSID_CXKEYBASE)
		{
			pListDst->AddTail(p);
		}
// 		else if (nClassID == KDBCLASSID_CXMULTIKEYBASE)
// 		{
// 			InitKeyRefBuffer((CExBaseList*)p, pListDst);
// 		}
// 		else if (nClassID == KDBCLASSID_CXMATCHKEYBASE)
// 		{
// 			InitKeyRefBuffer((CExBaseList*)p, pListDst);
// 		}
	}
}

void CXKeyDB::FreeKeyRefBuffer()
{
	if (m_pdwKeyRefBuffer != NULL)
	{
		delete m_pdwKeyRefBuffer;
		m_pdwKeyRefBuffer = NULL;
	}

	m_nKeyRefCount = 0;
}


void CXKeyDB::InitKeyRefBuffer()
{
	FreeKeyRefBuffer();
	CExBaseList oListTemp;
	InitKeyRefBuffer(m_pXKeyMngr, &oListTemp);
	m_nKeyRefCount = oListTemp.GetCount();
	m_pdwKeyRefBuffer = new DWORD [m_nKeyRefCount+10];
	CExBaseObject *p = NULL;
	POS pos = oListTemp.GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		p = oListTemp.GetNext(pos);
		m_pdwKeyRefBuffer[nIndex] = (DWORD)p;
		nIndex++;
	}

	oListTemp.RemoveAll();
}

BOOL  CXKeyDB::IsKeyExist(CExBaseObject *pKey, CExBaseList &oListTemp)
{
	CExBaseObject *p = NULL;
	CExBaseObject *pParent = NULL;
	CExBaseObject *pParentKey = NULL;
	CExBaseObject *pKeyFind = NULL;
	POS pos = oListTemp.GetHeadPosition();
	pParent = (CExBaseObject*)pKey->GetParent();

	if (pParent->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
	{
		pParentKey = pParent;
	}

	//如果pKey作为其中一个Key的子串，则不能要
	while (pos != NULL)
	{
		p = oListTemp.GetNext(pos);

		if (pKey != p)
		{
			if (p->m_strName.Find(pKey->m_strName) >= 0)
			{
				return TRUE;
			}

			pParent = (CExBaseObject*)p->GetParent();

			if (pParent->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
			{
				if (pParent == pParentKey)
				{
					return TRUE;
				}

				if (((CExBaseList*)pParent)->FindByName(pKey->m_strName) != NULL)
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

// void  CXKeyDB::QueryKeys(const CString &strText, CExBaseList *pListKeys, BOOL bRemoveSub)
// {
// 	ASSERT (m_pdwKeyRefBuffer != NULL);
// 	ASSERT (pListKeys != NULL);
// 	long nIndex = 0;
// 	CExBaseObject *pKey = NULL;
// 	CExBaseObject *pKeyFind = NULL;
// 	CExBaseObject *p = NULL;
// 	DWORD *pBegin = m_pdwKeyRefBuffer;
// 	DWORD *pEnd = m_pdwKeyRefBuffer + m_nKeyRefCount;
// 	CExBaseList oListTemp;
// 
// 	while (pBegin < pEnd)
// 	{
// 		if (strText.Find(((CExBaseObject*)(*pBegin))->m_strName) >= 0)
// 		{
// 			oListTemp.AddTail((CExBaseObject*)(*pBegin));
// 		}
// 
// 		pBegin++;
// 	}
// 
// 	pListKeys->Append(oListTemp);
// 
// 	if (bRemoveSub)
// 	{
// 		RemoveSubKeys(*pListKeys);
// 	}
// 
// 	oListTemp.RemoveAll();
// }

void  CXKeyDB::QueryKeys(const CString &strText, CXKeyMatchRefList *pListKeys, BOOL bRemoveSub)
{
	ASSERT (m_pdwKeyRefBuffer != NULL);
	ASSERT (pListKeys != NULL);
	long nIndex = 0;
	CXKeyBase *pKey = NULL;
	DWORD *pBegin = m_pdwKeyRefBuffer;
	DWORD *pEnd = m_pdwKeyRefBuffer + m_nKeyRefCount;
     CXKeyStringParser oStrParser;

	while (pBegin < pEnd)
	{
		pKey = (CXKeyBase *)(*pBegin);
		oStrParser.QueryKey(strText, pKey, pListKeys);
		pBegin++;
	}

     oStrParser.Parser(strText,pListKeys);
}

void  CXKeyDB::FilterAndQueryKeys(const CString &strText, BOOL bRemoveSub)
{
// 	ASSERT (m_pdwKeyRefBuffer != NULL);
// 	long nIndex = 0;
// 	CExBaseObject *pKey = NULL;
// 	CExBaseObject *pKeyFind = NULL;
// 	CExBaseObject *pParentKey = NULL;
// 	CExBaseObject *p = NULL;
// 	DWORD *pBegin = m_pdwKeyRefBuffer;
// 	DWORD *pEnd = m_pdwKeyRefBuffer + m_nKeyRefCount;
// 	CExBaseList oListTemp;
// 	UINT nClassID = 0;
// 
// 	while (pBegin < pEnd)
// 	{
// 		pKey = (CExBaseObject *)(*pBegin);
// 		nClassID = pKey->GetClassID();
// 		pParentKey = (CExBaseObject *)pKey->GetParent();
// 
// 		if (pParentKey->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
// 		{
// 			pParentKey->m_dwReserved = 0;
// 		}
// 		else
// 		{
// 			pKey->m_dwReserved = 0;
// 		}
// 
// 		if (strText.Find(pKey->m_strName) >= 0)
// 		{
// 			oListTemp.AddTail(pKey);
// 		}
// 
// 		pBegin++;
// 	}
// 
// 	POS pos = oListTemp.GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pKey = (CExBaseObject *)oListTemp.GetNext(pos);
// 		pParentKey = (CExBaseObject *)pKey->GetParent();
// 
// 		if (pParentKey->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
// 		{
// 			pParentKey->m_dwReserved = 1;
// 		}
// 		else
// 		{
// 			pKey->m_dwReserved = 1;
// 		}
// 
// 	}
// 	if (bRemoveSub)
// 	{
// 		RemoveSubKeys(oListTemp);
// 	}
// 	
// 	oListTemp.RemoveAll();
}

// void CXKeyDB::RemoveSubKeys(CExBaseList &oListKeys)
// {
// 	//过滤
// 	CExBaseList oListTemp;
// 	oListTemp.Append(oListKeys);
// 	oListKeys.RemoveAll();
// 	POS pos = oListTemp.GetHeadPosition();
// 	CExBaseObject *pParent = NULL;
// 	CExBaseObject *pParentKey = NULL;
// 	CExBaseObject *pKey = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		POS posRemove = pos;
// 		pKey = (CExBaseObject *)oListTemp.GetNext(pos);
// 
// 		if (IsKeyExist(pKey, oListTemp))
// 		{
// 			oListTemp.RemoveAt(posRemove);
// 			pKey->m_dwReserved = 0;
// 		}
// 		else
// 		{
// 			pParent = (CExBaseObject*)pKey->GetParent();
// 
// 			if (pParent->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
// 			{
// 				oListKeys.AddTail(pParent);
// 			}
// 			else
// 			{
// 				oListKeys.AddTail(pKey);
// 			}
// 		}
// 	}
// 
// 	oListTemp.RemoveAll();
// }
// 
// void CXKeyDB::RemoveSubKeys(CXKeyMatchRefList &oListKeys,CString strText)
// {
// 	//过滤
// 	CXKeyMatchRefList oListTemp;
// 	POS pos = oListKeys.GetHeadPosition();
// 	CXKeyMatchRef *pKeyRef = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pKeyRef = (CXKeyMatchRef *)oListKeys.GetNext(pos);
// 
// 		if (oListKeys.IsSubKey(pKeyRef,strText))
// 		{
// 			oListTemp.AddTail(pKeyRef);
// 		}
// 	}
// 
// 	pos = oListTemp.GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pKeyRef = (CXKeyMatchRef *)oListTemp.GetNext(pos);
// 		oListKeys.Delete(pKeyRef);
// 	}
// 
// 	oListTemp.RemoveAll();
// }

CExBaseObject* CXKeyDB::FindByKeyName(const CString &strKeyName)
{
	CExBaseObject *pFind = NULL;
	CExBaseObject *pKey = NULL;
	CExBaseObject *pParentKey = NULL;
	POS pos = GetHeadPosition();
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		pKey = (CExBaseObject *)GetNext(pos);

		if (pKey->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
		{
			if (((CExBaseList*)pKey)->FindByName(strKeyName) != NULL)
			{
				pFind = (CExBaseObject*)pKey->GetParent();
				break;
			}
		}
		else
		{
			if (pKey->m_strName == strKeyName)
			{
				pFind = pKey;
				break;
			}
		}
	}

	return pFind;
}

CXKeyMatchRef* CXKeyDB::CreateXKeyMatchRef(const CString &strKey, long nArrayIndex)
{
	CXKeyMatchRef *pNew = NULL;
	CXKeyBase *pKey = NULL;
	DWORD *pBegin = m_pdwKeyRefBuffer;
	DWORD *pEnd = m_pdwKeyRefBuffer + m_nKeyRefCount;

	while (pBegin < pEnd)
	{
		pKey = (CXKeyBase *)(*pBegin);
		
		if (pKey->m_strName == strKey)
		{
			pNew = new CXKeyMatchRef();
			pNew->m_pXKeyRef = pKey;
			pNew->m_nArrayIndex = nArrayIndex;
			break;
		}

		pBegin++;
	}

	return pNew;
}

BOOL CXKeyDB::CreateXKeyMatchRef(const CString &strKey, long nArrayIndex, CXKeyMatchRef &oKeyMatchRef)
{
	CXKeyBase *pKey = NULL;
	DWORD *pBegin = m_pdwKeyRefBuffer;
	DWORD *pEnd = m_pdwKeyRefBuffer + m_nKeyRefCount;

	while (pBegin < pEnd)
	{
		pKey = (CXKeyBase *)(*pBegin);

		if (pKey->m_strName == strKey)
		{
			oKeyMatchRef.m_pXKeyRef = pKey;
			oKeyMatchRef.m_nArrayIndex = nArrayIndex;
			return TRUE;
		}

		pBegin++;
	}

	return FALSE;
}

//2023-2-6  lijunqing  创建strKey对应的CXKeyMatchRef
CXKeyMatchRef* CXKeyDB::CreateXKeyMatchRef(const CString &strKey)
{
	CXKeyMatchRefList oList;
	QueryKeys(strKey, &oList);

	if (oList.GetCount() == 0)
	{
		return NULL;
	}
	else
	{
		CXKeyMatchRef *pKey = (CXKeyMatchRef*)oList.GetHead();
		oList.RemoveHead();
		return pKey;
	}
}


void CXKeyDB::SetIdSameAsName()
{
	SetIdSameAsName(this);
}

void CXKeyDB::SetIdSameAsName(CExBaseList *pList)
{
	CExBaseObject *pKey = NULL;
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pKey = (CExBaseObject *)pList->GetNext(pos);
		pKey->m_strID = pKey->m_strName;

		if (pKey->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
		{
			SetIdSameAsName((CExBaseList*)pKey);
		}
	}
}

CExBaseObject* XKey_GetXKey(CExBaseObject *pKey)
{
	ASSERT (pKey != NULL);

	UINT nClassID = pKey->GetClassID();

	if (nClassID == KDBCLASSID_CXKEYBASE || nClassID == KDBCLASSID_CXMULTIKEYBASE || nClassID == KDBCLASSID_CXKEYGROUPBASE)
	{
		return pKey;
	}

	CExBaseObject *pParent = (CExBaseObject*)pKey->GetParent();
	ASSERT (pParent != NULL);

	if (pParent->GetClassID() == KDBCLASSID_CXMULTIKEYBASE)
	{
		return pParent;
	}

	return NULL;
}

