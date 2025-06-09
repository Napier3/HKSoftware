// SttNativeCfgYun.cpp : 实现文件
//

#include "stdafx.h"
#include "SttNativeCfgYun.h"

// CSttNativeCfgYun

CSttNativeCfgYun::CSttNativeCfgYun()
{
	//初始化属性
	m_strIP = _T("47.111.12.170");
	m_nPort = 9900;
	m_nFtpPort = 9994;
}

CSttNativeCfgYun::~CSttNativeCfgYun()
{
}

void CSttNativeCfgYun::Init()
{
	if(m_strIP.IsEmpty())
	{
		m_strIP = _T("47.111.12.170");
	}

	if (m_nPort == 0)
	{
		m_nPort = 9900;
	}

	if (m_nFtpPort == 0)
	{
		m_nFtpPort = 9994;
	}
}

long CSttNativeCfgYun::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttNativeCfgXmlRWKeys *pXmlKeys = (CSttNativeCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIPKey, oNode, m_strIP);
	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_nPort);
	xml_GetAttibuteValue(pXmlKeys->m_strFtpPortKey, oNode, m_nFtpPort);
	Init();

	return 0;
}

long CSttNativeCfgYun::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttNativeCfgXmlRWKeys *pXmlKeys = (CSttNativeCfgXmlRWKeys*)pXmlRWKeys;
	
	Init();
	xml_SetAttributeValue(pXmlKeys->m_strIPKey, oElement, m_strIP);
	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_nPort);
	xml_SetAttributeValue(pXmlKeys->m_strFtpPortKey, oElement, m_nFtpPort);

	return 0;
}

long CSttNativeCfgYun::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strIP);
		BinarySerializeCalLen(oBinaryBuffer, m_nPort);
		BinarySerializeCalLen(oBinaryBuffer, m_nFtpPort);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strIP);
		BinarySerializeRead(oBinaryBuffer, m_nPort);
		BinarySerializeRead(oBinaryBuffer, m_nFtpPort);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strIP);
		BinarySerializeWrite(oBinaryBuffer, m_nPort);
		BinarySerializeWrite(oBinaryBuffer, m_nFtpPort);
	}

	return 0;
}

BOOL CSttNativeCfgYun::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttNativeCfgYun *p = (CSttNativeCfgYun*)pObj;

	if(m_strIP != p->m_strIP)
	{
		return FALSE;
	}

	if(m_nPort  != p->m_nPort )
	{
		return FALSE;
	}

	if(m_nFtpPort  != p->m_nFtpPort )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttNativeCfgYun::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttNativeCfgYun *p = (CSttNativeCfgYun*)pDest;
	p->m_strIP = m_strIP;
	p->m_nPort = m_nPort;
	p->m_nFtpPort = m_nFtpPort;

	return TRUE;
}

CBaseObject* CSttNativeCfgYun::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CExBaseObject *pNew = new CSttNativeCfgYun();

	if(bCopyOwn)
	{
		CopyOwn(pNew);
	}
	if(bCopyChildren)
	{
		CopyChildren(pNew);
	}	

	return pNew;
}
