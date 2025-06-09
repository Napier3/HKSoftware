//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttIotDevice.cpp  CSttIotDevice


#include "stdafx.h"
#include "SttIotDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttIotDevice::CSttIotDevice()
{
	//初始化属性
	m_nDevType = 0;

	//初始化成员变量
}

CSttIotDevice::~CSttIotDevice()
{
}

long CSttIotDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDevCodeKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDevTypeKey, oNode, m_nDevType);
	return 0;
}

long CSttIotDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDevCodeKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDevTypeKey, oElement, m_nDevType);
	return 0;
}

long CSttIotDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nDevType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nDevType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nDevType);
	}
	return 0;
}

void CSttIotDevice::InitAfterRead()
{
}

BOOL CSttIotDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttIotDevice *p = (CSttIotDevice*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_nDevType != p->m_nDevType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttIotDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttIotDevice *p = (CSttIotDevice*)pDest;

	p->m_strID = m_strID;
	p->m_nDevType = m_nDevType;
	return TRUE;
}

CBaseObject* CSttIotDevice::Clone()
{
	CSttIotDevice *p = new CSttIotDevice();
	Copy(p);
	return p;
}

CBaseObject* CSttIotDevice::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttIotDevice *p = new CSttIotDevice();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

