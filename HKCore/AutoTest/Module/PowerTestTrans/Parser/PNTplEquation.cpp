//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PNTplEquation.cpp  CPNTplEquation


#include "stdafx.h"
#include "PNTplEquation.h"

CPNTplEquation::CPNTplEquation()
{
	//初始化属性

	//初始化成员变量
	m_fValueCal = 0;
	m_bHasCal = FALSE;
}

CPNTplEquation::~CPNTplEquation()
{
}

long CPNTplEquation::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;

	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CPNTplEquation::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;

	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CPNTplEquation::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CPNTplEquation::InitAfterRead()
{
}

BOOL CPNTplEquation::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPNTplEquation *p = (CPNTplEquation*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPNTplEquation::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPNTplEquation *p = (CPNTplEquation*)pDest;

	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CPNTplEquation::Clone()
{
	CPNTplEquation *p = new CPNTplEquation();
	Copy(p);
	return p;
}

double CPNTplEquation::GetValue()
{
	ASSERT(m_bHasCal);

	return m_fValueCal;
}

void CPNTplEquation::SetValueCal(double dCal)
{
	m_bHasCal = TRUE;
	m_fValueCal = dCal;
}