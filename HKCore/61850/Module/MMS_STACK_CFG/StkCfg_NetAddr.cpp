//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//StkCfg_NetAddr.cpp  CStkCfg_NetAddr


#include "stdafx.h"
#include "StkCfg_NetAddr.h"

CStkCfg_NetAddr::CStkCfg_NetAddr()
{
	//初始化属性

	//初始化成员变量
}

CStkCfg_NetAddr::~CStkCfg_NetAddr()
{
}

long CStkCfg_NetAddr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	//xml_GetElementText(pXmlKeys->m_strNetAddrKey, oNode, m_strNetAddr);
	m_strNetAddr = oNode.Gettext();
	return 0;
}

long CStkCfg_NetAddr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMMS_STACK_CFGXmlRWKeys *pXmlKeys = (CMMS_STACK_CFGXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	//xml_SetElementText(pXmlKeys->m_strNetAddrKey, oXMLDoc, oElement, m_strNetAddr);
	//MSXML2::IXMLDOMNodePtr oChildNode = oElement;
	oElement.put_text(m_strNetAddr);

	return 0;
}

long CStkCfg_NetAddr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strNetAddr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strNetAddr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strNetAddr);
	}
	return 0;
}

void CStkCfg_NetAddr::InitAfterRead()
{
}

BOOL CStkCfg_NetAddr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CStkCfg_NetAddr *p = (CStkCfg_NetAddr*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strNetAddr != p->m_strNetAddr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CStkCfg_NetAddr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CStkCfg_NetAddr *p = (CStkCfg_NetAddr*)pDest;

	p->m_strType = m_strType;
	p->m_strNetAddr = m_strNetAddr;
	return TRUE;
}

CBaseObject* CStkCfg_NetAddr::Clone()
{
	CStkCfg_NetAddr *p = new CStkCfg_NetAddr();
	Copy(p);
	return p;
}

