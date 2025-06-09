//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapNetRemote.cpp  CEpCapNetRemote


#include "stdafx.h"
#include "EpCapNetRemote.h"

CEpCapNetRemote::CEpCapNetRemote()
{
	//初始化属性

	//初始化成员变量
}

CEpCapNetRemote::~CEpCapNetRemote()
{
}

long CEpCapNetRemote::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	return 0;
}

long CEpCapNetRemote::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	return 0;
}

long CEpCapNetRemote::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
	}
	return 0;
}

void CEpCapNetRemote::InitAfterRead()
{
}

BOOL CEpCapNetRemote::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapNetRemote *p = (CEpCapNetRemote*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEpCapNetRemote::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapNetRemote *p = (CEpCapNetRemote*)pDest;

	p->m_strName = m_strName;
	return TRUE;
}

CBaseObject* CEpCapNetRemote::Clone()
{
	CEpCapNetRemote *p = new CEpCapNetRemote();
	Copy(p);
	return p;
}

BOOL CEpCapNetRemote::CanPaste(UINT nClassID)
{
	if (nClassID == ECCLASSID_CEPCAPNETSUBREMOTE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpCapNetRemote::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapConfigXmlRWKeys *pXmlKeys = (CEpCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapNetSubRemoteKey)
	{
		pNew = new CEpCapNetSubRemote();
	}

	return pNew;
}

CExBaseObject* CEpCapNetRemote::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECCLASSID_CEPCAPNETSUBREMOTE)
	{
		pNew = new CEpCapNetSubRemote();
	}

	return pNew;
}
