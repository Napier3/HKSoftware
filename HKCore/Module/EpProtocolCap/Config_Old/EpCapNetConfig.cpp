//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetConfig.cpp  CEpCapNetConfig


#include "stdafx.h"
#include "EpCapNetConfig.h"

CEpCapNetConfig::CEpCapNetConfig()
{
	//初始化属性
	m_nTcp = 0;
	m_nUdp = 0;

	//初始化成员变量
}

CEpCapNetConfig::~CEpCapNetConfig()
{
}

long CEpCapNetConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTcpKey, oNode, m_nTcp);
	xml_GetAttibuteValue(pXmlKeys->m_strUdpKey, oNode, m_nUdp);
	return 0;
}

long CEpCapNetConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTcpKey, oElement, m_nTcp);
	xml_SetAttributeValue(pXmlKeys->m_strUdpKey, oElement, m_nUdp);
	return 0;
}

long CEpCapNetConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nTcp);
		BinarySerializeCalLen(oBinaryBuffer, m_nUdp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nTcp);
		BinarySerializeRead(oBinaryBuffer, m_nUdp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nTcp);
		BinarySerializeWrite(oBinaryBuffer, m_nUdp);
	}
	return 0;
}

void CEpCapNetConfig::InitAfterRead()
{
}

BOOL CEpCapNetConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapNetConfig *p = (CEpCapNetConfig*)pObj;

	if(m_nTcp != p->m_nTcp)
	{
		return FALSE;
	}

	if(m_nUdp != p->m_nUdp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapNetConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapNetConfig *p = (CEpCapNetConfig*)pDest;

	p->m_nTcp = m_nTcp;
	p->m_nUdp = m_nUdp;
	return TRUE;
}

CBaseObject* CEpCapNetConfig::Clone()
{
	CEpCapNetConfig *p = new CEpCapNetConfig();
	Copy(p);
	return p;
}

BOOL CEpCapNetConfig::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPNETCARD)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapNetConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapNetCardKey)
	{
		pNew = new CEpCapNetCard();
	}

	return pNew;
}

CExBaseObject* CEpCapNetConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPNETCARD)
	{
		pNew = new CEpCapNetCard();
	}

	return pNew;
}
