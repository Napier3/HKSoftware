//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetGroup.cpp  CEpCapNetGroup


#include "stdafx.h"
#include "EpCapNetGroup.h"

CEpCapNetGroup::CEpCapNetGroup()
{
	//初始化属性
	m_nIndex = 0;
	m_nTcp = 0;
	m_nUdp = 0;

	//初始化成员变量
}

CEpCapNetGroup::~CEpCapNetGroup()
{
}

long CEpCapNetGroup::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strTcpKey, oNode, m_nTcp);
	xml_GetAttibuteValue(pXmlKeys->m_strUdpKey, oNode, m_nUdp);
	return 0;
}

long CEpCapNetGroup::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strTcpKey, oElement, m_nTcp);
	xml_SetAttributeValue(pXmlKeys->m_strUdpKey, oElement, m_nUdp);
	return 0;
}

long CEpCapNetGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_nTcp);
		BinarySerializeCalLen(oBinaryBuffer, m_nUdp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nIndex);
		BinarySerializeRead(oBinaryBuffer, m_nTcp);
		BinarySerializeRead(oBinaryBuffer, m_nUdp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex);
		BinarySerializeWrite(oBinaryBuffer, m_nTcp);
		BinarySerializeWrite(oBinaryBuffer, m_nUdp);
	}
	return 0;
}

void CEpCapNetGroup::InitAfterRead()
{
}

BOOL CEpCapNetGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapNetGroup *p = (CEpCapNetGroup*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

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

BOOL CEpCapNetGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapNetGroup *p = (CEpCapNetGroup*)pDest;

	p->m_strName = m_strName;
	p->m_nIndex = m_nIndex;
	p->m_nTcp = m_nTcp;
	p->m_nUdp = m_nUdp;
	return TRUE;
}

CBaseObject* CEpCapNetGroup::Clone()
{
	CEpCapNetGroup *p = new CEpCapNetGroup();
	Copy(p);
	return p;
}

BOOL CEpCapNetGroup::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPNETDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapNetGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapNetDeviceKey)
	{
		pNew = new CEpCapNetDevice();
	}

	return pNew;
}

CExBaseObject* CEpCapNetGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPNETDEVICE)
	{
		pNew = new CEpCapNetDevice();
	}

	return pNew;
}
