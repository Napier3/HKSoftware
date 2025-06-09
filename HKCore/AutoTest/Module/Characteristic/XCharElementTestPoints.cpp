//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XCharElementTestPoints.cpp  CXCharElementTestPoints


#include "stdafx.h"
#include "XCharElementTestPoints.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXCharElementTestPoints::CXCharElementTestPoints()
{
	//初始化属性
	m_strFrom = _T("BeginValue");
	m_strTo = _T("EndValue");
	m_strStep = _T("StepValue");

	m_dFrom = 0.0;
	m_dTo = 0.0;
	m_dStep = 0.0;
	//初始化成员变量
}

CXCharElementTestPoints::~CXCharElementTestPoints()
{
}

long CXCharElementTestPoints::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFromKey, oNode, m_strFrom);
	xml_GetAttibuteValue(pXmlKeys->m_strToKey, oNode, m_strTo);
	xml_GetAttibuteValue(pXmlKeys->m_strStepKey, oNode, m_strStep);

	return 0;
}

long CXCharElementTestPoints::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFromKey, oElement, m_strFrom);
	xml_SetAttributeValue(pXmlKeys->m_strToKey, oElement, m_strTo);
	xml_SetAttributeValue(pXmlKeys->m_strStepKey, oElement, m_strStep);

	return 0;
}

void CXCharElementTestPoints::InitAfterRead()
{
	m_dFrom = CString_To_double(m_strFrom);
	m_dTo = CString_To_double(m_strTo);
	m_dStep = CString_To_double(m_strStep);
}

BOOL CXCharElementTestPoints::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXCharElementTestPoints *p = (CXCharElementTestPoints*)pObj;

	if(m_strFrom != p->m_strFrom)
	{
		return FALSE;
	}

	if(m_strTo != p->m_strTo)
	{
		return FALSE;
	}

	if(m_strStep != p->m_strStep)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXCharElementTestPoints::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXCharElementTestPoints *p = (CXCharElementTestPoints*)pDest;

	p->m_strFrom = m_strFrom;
	p->m_strTo = m_strTo;
	p->m_strStep = m_strStep;

	return TRUE;
}

CBaseObject* CXCharElementTestPoints::Clone()
{
	CXCharElementTestPoints *p = new CXCharElementTestPoints();
	Copy(p);
	return p;
}

long CXCharElementTestPoints::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFrom);
		BinarySerializeCalLen(oBinaryBuffer, m_strTo);
		BinarySerializeCalLen(oBinaryBuffer, m_strStep);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFrom);
		BinarySerializeRead(oBinaryBuffer, m_strTo);
		BinarySerializeRead(oBinaryBuffer, m_strStep);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFrom);
		BinarySerializeWrite(oBinaryBuffer, m_strTo);
		BinarySerializeWrite(oBinaryBuffer, m_strStep);
	}

	return 0;
}
