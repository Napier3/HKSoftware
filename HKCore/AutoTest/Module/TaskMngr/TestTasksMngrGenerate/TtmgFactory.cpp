//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgFactory.cpp  CTtmgFactory


#include "stdafx.h"
#include "TtmgFactory.h"
#include "TestTasksMngrGenerate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTtmgFactory::CTtmgFactory()
{
	//初始化属性

	//初始化成员变量
}

CTtmgFactory::~CTtmgFactory()
{
}

long CTtmgFactory::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCodeKey, oNode, m_strCode);
	xml_GetAttibuteValue(pXmlKeys->m_strOwnDefKey, oNode, m_strOwnDef);
	xml_GetAttibuteValue(pXmlKeys->m_strHdVerKey, oNode, m_strHdVer);
	return 0;
}

long CTtmgFactory::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCodeKey, oElement, m_strCode);
	xml_SetAttributeValue(pXmlKeys->m_strOwnDefKey, oElement, m_strOwnDef);
	xml_SetAttributeValue(pXmlKeys->m_strHdVerKey, oElement, m_strHdVer);
	return 0;
}

long CTtmgFactory::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strOwnDef);
		BinarySerializeCalLen(oBinaryBuffer, m_strHdVer);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCode);
		BinarySerializeRead(oBinaryBuffer, m_strOwnDef);
		BinarySerializeRead(oBinaryBuffer, m_strHdVer);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCode);
		BinarySerializeWrite(oBinaryBuffer, m_strOwnDef);
		BinarySerializeWrite(oBinaryBuffer, m_strHdVer);
	}
	return 0;
}

void CTtmgFactory::InitAfterRead()
{
}

BOOL CTtmgFactory::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTtmgFactory *p = (CTtmgFactory*)pObj;

	if(m_strCode != p->m_strCode)
	{
		return FALSE;
	}

	if(m_strOwnDef != p->m_strOwnDef)
	{
		return FALSE;
	}

	if(m_strHdVer != p->m_strHdVer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTtmgFactory::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTtmgFactory *p = (CTtmgFactory*)pDest;

	p->m_strCode = m_strCode;
	p->m_strOwnDef = m_strOwnDef;
	p->m_strHdVer = m_strHdVer;
	return TRUE;
}

CBaseObject* CTtmgFactory::Clone()
{
	CTtmgFactory *p = new CTtmgFactory();
	Copy(p);
	return p;
}


CTtmgFactory* TTMG_FindFactory(const CString &strStation)
{
	CTestTasksMngrGenerate *pGenerate = CTestTasksMngrGenerate::GetTestTasksMngrGenerate();
	return (CTtmgFactory*)pGenerate->m_pFactorys->FindByName(strStation);
}

