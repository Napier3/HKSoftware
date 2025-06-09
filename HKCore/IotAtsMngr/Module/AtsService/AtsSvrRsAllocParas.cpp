//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrRsAllocParas.cpp  CAtsSvrRsAllocParas


#include "stdafx.h"
#include "AtsSvrRsAllocParas.h"

CAtsSvrRsAllocParas::CAtsSvrRsAllocParas()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrRsAllocParas::~CAtsSvrRsAllocParas()
{
}

long CAtsSvrRsAllocParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceTypeKey, oNode, m_strDeviceType);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceSNKey, oNode, m_strDeviceSN);
	xml_GetAttibuteValue(pXmlKeys->m_strMacroIDKey, oNode, m_strMacroID);
	return 0;
}

long CAtsSvrRsAllocParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceTypeKey, oElement, m_strDeviceType);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceSNKey, oElement, m_strDeviceSN);
	xml_SetAttributeValue(pXmlKeys->m_strMacroIDKey, oElement, m_strMacroID);
	return 0;
}

long CAtsSvrRsAllocParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceType);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceSN);
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceType);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceSN);
		BinarySerializeRead(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceType);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceSN);
		BinarySerializeWrite(oBinaryBuffer, m_strMacroID);
	}
	return 0;
}

void CAtsSvrRsAllocParas::InitAfterRead()
{
}

BOOL CAtsSvrRsAllocParas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAtsSvrRsAllocParas *p = (CAtsSvrRsAllocParas*)pObj;

	if(m_strDeviceType != p->m_strDeviceType)
	{
		return FALSE;
	}

	if(m_strDeviceSN != p->m_strDeviceSN)
	{
		return FALSE;
	}

	if(m_strMacroID != p->m_strMacroID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CAtsSvrRsAllocParas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CAtsSvrRsAllocParas *p = (CAtsSvrRsAllocParas*)pDest;

	p->m_strDeviceType = m_strDeviceType;
	p->m_strDeviceSN = m_strDeviceSN;
	p->m_strMacroID = m_strMacroID;
	return TRUE;
}

CBaseObject* CAtsSvrRsAllocParas::Clone()
{
	CAtsSvrRsAllocParas *p = new CAtsSvrRsAllocParas();
	Copy(p);
	return p;
}

