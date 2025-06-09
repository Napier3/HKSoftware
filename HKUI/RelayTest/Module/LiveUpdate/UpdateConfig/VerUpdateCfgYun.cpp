// VerUpdateCfgYun.cpp : 实现文件
//

#include "stdafx.h"
#include "VerUpdateCfgYun.h"

// CVerUpdateCfgYun

CVerUpdateCfgYun::CVerUpdateCfgYun()
{
	//初始化属性
	m_strIP = _T("47.111.12.170");
	m_nPort = 9900;
	m_nFtpPort = 9994;
}

CVerUpdateCfgYun::~CVerUpdateCfgYun()
{
}

void CVerUpdateCfgYun::Init()
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

long CVerUpdateCfgYun::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;

	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetElementText(pXmlKeys->m_strIPKey, oNode, m_strIP);
	xml_GetElementText(pXmlKeys->m_strPortKey, oNode, m_nPort);
	xml_GetElementText(pXmlKeys->m_strFtpPortKey, oNode, m_nFtpPort);
	Init();

	return 0;
}

long CVerUpdateCfgYun::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CVerUpdateCfgXmlRWKeys *pXmlKeys = (CVerUpdateCfgXmlRWKeys*)pXmlRWKeys;
	
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	Init();
	xml_SetElementText(pXmlKeys->m_strIPKey, oXMLDoc, oElement, m_strIP);
	xml_SetElementText(pXmlKeys->m_strPortKey, oXMLDoc, oElement, m_nPort);
	xml_SetElementText(pXmlKeys->m_strFtpPortKey, oXMLDoc, oElement, m_nFtpPort);

	return 0;
}

long CVerUpdateCfgYun::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CVerUpdateCfgYun::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CVerUpdateCfgYun *p = (CVerUpdateCfgYun*)pObj;

	if(m_strIP != p->m_strIP)
	{
		return FALSE;
	}

	if(m_nPort != p->m_nPort && m_nFtpPort != p->m_nFtpPort)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CVerUpdateCfgYun::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CVerUpdateCfgYun *p = (CVerUpdateCfgYun*)pDest;
	p->m_strIP = m_strIP;
	p->m_nPort = m_nPort;
	p->m_nFtpPort = m_nFtpPort;

	return TRUE;
}

CBaseObject* CVerUpdateCfgYun::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CExBaseObject *pNew = new CVerUpdateCfgYun();

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
