//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceNode101Yx.cpp  CEpDeviceNode101Yx


#include "stdafx.h"
#include "EpDeviceNode101Yx.h"

CEpDeviceNode101Yx::CEpDeviceNode101Yx()
{
	//初始化属性

	//初始化成员变量
}

CEpDeviceNode101Yx::~CEpDeviceNode101Yx()
{
}

long CEpDeviceNode101Yx::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceNode::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode101Yx::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceNode::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode101Yx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEpDeviceNode::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CEpDeviceNode101Yx::InitAfterRead()
{
}

BOOL CEpDeviceNode101Yx::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDeviceNode::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceNode101Yx *p = (CEpDeviceNode101Yx*)pObj;

	return TRUE;
}

BOOL CEpDeviceNode101Yx::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDeviceNode::CopyOwn(pDest);

	CEpDeviceNode101Yx *p = (CEpDeviceNode101Yx*)pDest;

	return TRUE;
}

CBaseObject* CEpDeviceNode101Yx::Clone()
{
	CEpDeviceNode101Yx *p = new CEpDeviceNode101Yx();
	Copy(p);
	return p;
}

BOOL CEpDeviceNode101Yx::CanPaste(UINT nClassID)
{
	if (nClassID == EPDCLASSID_CEPDEVICEDATA101YX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpDeviceNode101Yx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpDeviceData101YxKey)
	{
		pNew = new CEpDeviceData101Yx();
	}

	return pNew;
}

CExBaseObject* CEpDeviceNode101Yx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPDCLASSID_CEPDEVICEDATA101YX)
	{
		pNew = new CEpDeviceData101Yx();
	}

	return pNew;
}
