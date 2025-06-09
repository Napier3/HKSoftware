//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMultiKeyBase.cpp  CXMultiKeyBase


#include "stdafx.h"
#include "XMultiKeyBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CXMultiSubKey::CXMultiSubKey()
{

}

CXMultiSubKey::~CXMultiSubKey()
{

}

long CXMultiSubKey::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIsArrayKey, oNode, m_nArrayIndex);

	return 0;
}

long CXMultiSubKey::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strIsArrayKey, oElement, m_nArrayIndex);

	return 0;
}

long CXMultiSubKey::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nArrayIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nArrayIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nArrayIndex);
	}

	return 0;
}

BOOL CXMultiSubKey::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXMultiSubKey *p = (CXMultiSubKey*)pObj;

	if(m_nArrayIndex != p->m_nArrayIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXMultiSubKey::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CXMultiSubKey *p = (CXMultiSubKey*)pDest;

	p->m_nArrayIndex = m_nArrayIndex;

	return TRUE;
}

CBaseObject* CXMultiSubKey::Clone()
{
	CXMultiSubKey *p = new CXMultiSubKey();
	Copy(p);
	return p;
}


//////////////////////////////////////////////////////////////////////////
//CXMultiKeyBase
CXMultiKeyBase::CXMultiKeyBase()
{
	//初始化属性
	//m_nImportance = 0;

	//初始化成员变量
}

CXMultiKeyBase::~CXMultiKeyBase()
{
}

long CXMultiKeyBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CXMultiKeyBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

long CXMultiKeyBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	return 0;
}

void CXMultiKeyBase::InitAfterRead()
{

}

BOOL CXMultiKeyBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseList::IsEqualOwn(pObj))
	{
		return FALSE;
	}
// 
// 	CXMultiKeyBase *p = (CXMultiKeyBase*)pObj;
// 
// 	if(m_nImportance != p->m_nImportance)
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}

BOOL CXMultiKeyBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);

// 	CXMultiKeyBase *p = (CXMultiKeyBase*)pDest;
// 
// 	p->m_nImportance = m_nImportance;
	return TRUE;
}

CBaseObject* CXMultiKeyBase::Clone()
{
	CXMultiKeyBase *p = new CXMultiKeyBase();
	Copy(p);
	return p;
}

BOOL CXMultiKeyBase::CanPaste(UINT nClassID)
{
	if (nClassID == KDBCLASSID_CXKEYBASE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXMultiKeyBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCXKeyBaseKey)
	{
		pNew = new CXMultiSubKey();
	}

	return pNew;
}

CExBaseObject* CXMultiKeyBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == KDBCLASSID_CXMULTISUBKEY)
	{
		pNew = new CXMultiSubKey();
	}

	return pNew;
}

BOOL CXMultiKeyBase::Query(const CString &strText, CExBaseList *pListKeys)
{
	return TRUE;
}

BOOL CXMultiKeyBase::Match(CXKeyBase *pKey)
{
	return Find(pKey) != NULL;
   
}

BOOL CXMultiKeyBase::IsSubKey(CXKeyBase *pXKeyRef)
{
	POS pos = GetHeadPosition();
	CXKeyBase *p = NULL;

	while (pos != NULL)
	{
		p = (CXKeyBase *)GetNext(pos);

		if (p->IsSubKey(pXKeyRef))
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CXMultiKeyBase::HasXKey(long nArrayIndex, CXKeyBase *pKey)
{
	CXMultiSubKey *p = NULL;
	CXMultiSubKey *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXMultiSubKey *)GetNext(pos);

		if (p->m_pXKeyRef == pKey)
		{
			if (pKey->IsArrayKey())
			{
				if (p->m_nArrayIndex == nArrayIndex)
				{
					pFind = p;
					break;
				}
			}
			else
			{
				pFind = p;
				break;
			}
		}
	}

	return (pFind != NULL);
}

//////////////////////////////////////////////////////////////////////////
//CXKeyMaps
CXKeyMaps::CXKeyMaps()
{

}

CXKeyMaps::~CXKeyMaps()
{

}

long CXKeyMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CXKeyMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CXKeyMaps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

// void CXKeyMaps::InitAfterRead()
// {
// 
// }
// 
// BOOL CXKeyMaps::IsEqualOwn(CBaseObject* pObj)
// {
// 	return 0;
// }
// 
// BOOL CXKeyMaps::CopyOwn(CBaseObject* pDest)
// {
// 	return 0;
// }

CBaseObject* CXKeyMaps::Clone()
{
	CXKeyMaps *pNew = new CXKeyMaps();
	Copy(pNew);

	return pNew;
}

// BOOL CXKeyMaps::CanPaste(UINT nClassID)
// {
// 	return 0;
// }

CExBaseObject* CXKeyMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCXMultiKeyBaseKey)
	{
		pNew = new CXMultiKeyBase();
	}

	return pNew;
}

CExBaseObject* CXKeyMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return 0;
}

