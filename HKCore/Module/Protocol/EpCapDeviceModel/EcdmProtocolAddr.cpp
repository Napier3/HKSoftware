//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EcdmProtocolAddr.cpp  CEcdmProtocolAddr


#include "stdafx.h"
#include "EcdmProtocolAddr.h"

CEcdmProtocolAddr::CEcdmProtocolAddr()
{
	//初始化属性
	m_nYxAddr = 0;
	m_nYcAddr = 0;
	m_nYtAddr = 0;

	//初始化成员变量
}

CEcdmProtocolAddr::~CEcdmProtocolAddr()
{
}

long CEcdmProtocolAddr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strYxAddrKey, oNode, m_nYxAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strYcAddrKey, oNode, m_nYcAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strYtAddrKey, oNode, m_nYtAddr);
	return 0;
}

long CEcdmProtocolAddr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strYxAddrKey, oElement, m_nYxAddr);
	xml_SetAttributeValue(pXmlKeys->m_strYcAddrKey, oElement, m_nYcAddr);
	xml_SetAttributeValue(pXmlKeys->m_strYtAddrKey, oElement, m_nYtAddr);
	return 0;
}

BOOL CEcdmProtocolAddr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEcdmProtocolAddr *p = (CEcdmProtocolAddr*)pObj;

	if(m_nYxAddr != p->m_nYxAddr)
	{
		return FALSE;
	}

	if(m_nYcAddr != p->m_nYcAddr)
	{
		return FALSE;
	}

	if(m_nYtAddr != p->m_nYtAddr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEcdmProtocolAddr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEcdmProtocolAddr *p = (CEcdmProtocolAddr*)pDest;

	p->m_nYxAddr = m_nYxAddr;
	p->m_nYcAddr = m_nYcAddr;
	p->m_nYtAddr = m_nYtAddr;
	return TRUE;
}

CBaseObject* CEcdmProtocolAddr::Clone()
{
	CEcdmProtocolAddr *p = new CEcdmProtocolAddr();
	Copy(p);
	return p;
}

