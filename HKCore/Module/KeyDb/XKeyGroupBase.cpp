//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XKeyGroupBase.cpp  CXKeyGroupBase


#include "stdafx.h"
#include "XKeyGroupBase.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CXKeyGroupBase::CXKeyGroupBase()
{
	//初始化属性
	m_nImportance = 0;

	//初始化成员变量
}

CXKeyGroupBase::~CXKeyGroupBase()
{
}

long CXKeyGroupBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strImportanceKey, oNode, m_nImportance);
	return 0;
}

long CXKeyGroupBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strImportanceKey, oElement, m_nImportance);
	return 0;
}

long CXKeyGroupBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nImportance);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nImportance);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nImportance);
	}
	return 0;
}

void CXKeyGroupBase::InitAfterRead()
{
}

BOOL CXKeyGroupBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXKeyGroupBase *p = (CXKeyGroupBase*)pObj;

	if(m_nImportance != p->m_nImportance)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXKeyGroupBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CXKeyGroupBase *p = (CXKeyGroupBase*)pDest;

	p->m_nImportance = m_nImportance;
	return TRUE;
}

CBaseObject* CXKeyGroupBase::Clone()
{
	CXKeyGroupBase *p = new CXKeyGroupBase();
	Copy(p);
	return p;
}

BOOL CXKeyGroupBase::CanPaste(UINT nClassID)
{
	if (nClassID == KDBCLASSID_CXKEYREF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXKeyGroupBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CKeyDbXmlRWKeys *pXmlKeys = (CKeyDbXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXKeyRefKey)
	{
		pNew = new CXKeyRef();
	}

	return pNew;
}

CExBaseObject* CXKeyGroupBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == KDBCLASSID_CXKEYREF)
	{
		pNew = new CXKeyRef();
	}

	return pNew;
}
