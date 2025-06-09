//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestResources.cpp  CAtsSvrTestResources


#include "stdafx.h"
#include "AtsSvrTestResources.h"

CAtsSvrTestResources::CAtsSvrTestResources()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrTestResources::~CAtsSvrTestResources()
{
}

long CAtsSvrTestResources::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestResources::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestResources::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAtsSvrTestResources::InitAfterRead()
{
}

BOOL CAtsSvrTestResources::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrTestResources *p = (CAtsSvrTestResources*)pObj;

	return TRUE;
}

BOOL CAtsSvrTestResources::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrTestResources *p = (CAtsSvrTestResources*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrTestResources::Clone()
{
	CAtsSvrTestResources *p = new CAtsSvrTestResources();
	Copy(p);
	return p;
}

BOOL CAtsSvrTestResources::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRTESTRESOURCE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrTestResources::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrTestResourceKey)
	{
		pNew = new CAtsSvrTestResource();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestResources::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRTESTRESOURCE)
	{
		pNew = new CAtsSvrTestResource();
	}

	return pNew;
}
