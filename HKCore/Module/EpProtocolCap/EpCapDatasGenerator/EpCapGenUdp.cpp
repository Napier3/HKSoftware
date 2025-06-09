//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapGenUdp.cpp  CEpCapGenUdp


#include "stdafx.h"
#include "EpCapGenUdp.h"

CEpCapGenUdp::CEpCapGenUdp()
{
	//初始化属性

	//初始化成员变量
}

CEpCapGenUdp::~CEpCapGenUdp()
{
}

long CEpCapGenUdp::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapGenBase::XmlReadOwn(oNode, pXmlRWKeys);

	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strLocalIPKey, oNode, m_strLocalIP);
	xml_GetAttibuteValue(pXmlKeys->m_strLocalPortKey, oNode, m_strLocalPort);
	xml_GetAttibuteValue(pXmlKeys->m_strRemotePortKey, oNode, m_strRemotePort);
	xml_GetAttibuteValue(pXmlKeys->m_strRemoteIPKey, oNode, m_strRemoteIP);
	return 0;
}

long CEpCapGenUdp::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapGenBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLocalIPKey, oElement, m_strLocalIP);
	xml_SetAttributeValue(pXmlKeys->m_strLocalPortKey, oElement, m_strLocalPort);
	xml_SetAttributeValue(pXmlKeys->m_strRemotePortKey, oElement, m_strRemotePort);
	xml_SetAttributeValue(pXmlKeys->m_strRemoteIPKey, oElement, m_strRemoteIP);
	return 0;
}

BOOL CEpCapGenUdp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpCapGenBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpCapGenUdp *p = (CEpCapGenUdp*)pObj;

	if(m_strLocalIP != p->m_strLocalIP)
	{
		return FALSE;
	}

	if(m_strLocalPort != p->m_strLocalPort)
	{
		return FALSE;
	}

	if(m_strRemotePort != p->m_strRemotePort)
	{
		return FALSE;
	}

	if(m_strRemoteIP != p->m_strRemoteIP)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapGenUdp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapGenBase::CopyOwn(pDest);

	CEpCapGenUdp *p = (CEpCapGenUdp*)pDest;

	p->m_strLocalIP = m_strLocalIP;
	p->m_strLocalPort = m_strLocalPort;
	p->m_strRemotePort = m_strRemotePort;
	p->m_strRemoteIP = m_strRemoteIP;
	return TRUE;
}

CBaseObject* CEpCapGenUdp::Clone()
{
	CEpCapGenUdp *p = new CEpCapGenUdp();
	Copy(p);
	return p;
}

