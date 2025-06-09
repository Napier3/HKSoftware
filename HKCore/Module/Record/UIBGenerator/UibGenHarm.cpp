//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UibGenHarm.cpp  CUibGenHarm


#include "stdafx.h"
#include "UibGenHarm.h"
#include "..\..\API\MathApi.h"

CUibGenHarm::CUibGenHarm()
{
	//初始化属性
	m_nUse = 0;
	m_nIndex = 0;
	m_fValue = 0;
	m_fAngle = 0;

	//初始化成员变量
}

CUibGenHarm::~CUibGenHarm()
{
}

long CUibGenHarm::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseKey, oNode, m_nUse);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_fValue);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_fAngle);

	m_fAngle = m_fAngle * _PI_D_180;

	return 0;
}

long CUibGenHarm::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBGeneratorXmlRWKeys *pXmlKeys = (CUIBGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUseKey, oElement, m_nUse);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_fValue);

	float fAngle = m_fAngle * _180_D_PI;
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, fAngle);

	return 0;
}

long CUibGenHarm::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nUse);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_fValue);
		BinarySerializeCalLen(oBinaryBuffer, m_fAngle);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nUse);
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
		BinarySerializeRead(oBinaryBuffer, m_fValue);
		BinarySerializeRead(oBinaryBuffer, m_fAngle);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nUse);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
		BinarySerializeWrite(oBinaryBuffer, m_fValue);
		BinarySerializeWrite(oBinaryBuffer, m_fAngle);
	}
	return 0;
}

void CUibGenHarm::InitAfterRead()
{
}

BOOL CUibGenHarm::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUibGenHarm *p = (CUibGenHarm*)pObj;

	if(m_nUse != p->m_nUse)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	if(m_fValue != p->m_fValue)
	{
		return FALSE;
	}

	if(m_fAngle != p->m_fAngle)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUibGenHarm::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUibGenHarm *p = (CUibGenHarm*)pDest;

	p->m_nUse = m_nUse;
	p->m_nIndex = m_nIndex;
	p->m_fValue = m_fValue;
	p->m_fAngle = m_fAngle;
	return TRUE;
}

CBaseObject* CUibGenHarm::Clone()
{
	CUibGenHarm *p = new CUibGenHarm();
	Copy(p);
	return p;
}

void CUibGenHarm::Generate(long &nUibGenIndex, double &dCoef_FreqAngleT, double &dGenValue)
{
	if (m_nUse == 0)
	{
		return;
	}

	if (m_nIndex == 0)
	{//直流
		dGenValue += m_fValue;
		return;
	}

	double dValue = m_fValue * sin(m_fAngle + dCoef_FreqAngleT*m_nIndex * nUibGenIndex);
	dValue *= 1.414216;  //不考虑节省此次乘法，如果需要节省，就可以在Analog处进行处理
	dGenValue += dValue;
}

