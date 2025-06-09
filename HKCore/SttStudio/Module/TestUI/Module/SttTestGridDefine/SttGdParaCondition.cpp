//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdParaCondition.cpp  CSttGdParaCondition


#include "stdafx.h"
#include "SttGdParaCondition.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdParaCondition::CSttGdParaCondition()
{
	//初始化属性

	//初始化成员变量
}

CSttGdParaCondition::~CSttGdParaCondition()
{
}

long CSttGdParaCondition::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CSttGdParaCondition::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CSttGdParaCondition::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CSttGdParaCondition::InitAfterRead()
{
}

BOOL CSttGdParaCondition::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttGdParaCondition *p = (CSttGdParaCondition*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdParaCondition::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttGdParaCondition *p = (CSttGdParaCondition*)pDest;

	p->m_strID = m_strID;
	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CSttGdParaCondition::Clone()
{
	CSttGdParaCondition *p = new CSttGdParaCondition();
	Copy(p);
	return p;
}

CBaseObject* CSttGdParaCondition::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdParaCondition *p = new CSttGdParaCondition();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

