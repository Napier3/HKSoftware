//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrRsAllocDef.cpp  CAtsSvrRsAllocDef


#include "stdafx.h"
#include "AtsSvrRsAllocDef.h"

CAtsSvrRsAllocDef::CAtsSvrRsAllocDef()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrRsAllocDef::~CAtsSvrRsAllocDef()
{
}

long CAtsSvrRsAllocDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strBenchSNKey, oNode, m_strBenchSN);
	return 0;
}

long CAtsSvrRsAllocDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strBenchSNKey, oElement, m_strBenchSN);
	return 0;
}

long CAtsSvrRsAllocDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strBenchSN);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strBenchSN);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strBenchSN);
	}
	return 0;
}

void CAtsSvrRsAllocDef::InitAfterRead()
{
}

BOOL CAtsSvrRsAllocDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrRsAllocDef *p = (CAtsSvrRsAllocDef*)pObj;

	if(m_strBenchSN != p->m_strBenchSN)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAtsSvrRsAllocDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrRsAllocDef *p = (CAtsSvrRsAllocDef*)pDest;

	p->m_strBenchSN = m_strBenchSN;
	return TRUE;
}

CBaseObject* CAtsSvrRsAllocDef::Clone()
{
	CAtsSvrRsAllocDef *p = new CAtsSvrRsAllocDef();
	Copy(p);
	return p;
}

CExBaseObject* CAtsSvrRsAllocDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrRsAllocParasKey)
	{
		pNew = new CAtsSvrRsAllocParas();
	}

	return pNew;
}

CExBaseObject* CAtsSvrRsAllocDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRRSALLOCPARAS)
	{
		pNew = new CAtsSvrRsAllocParas();
	}

	return pNew;
}
