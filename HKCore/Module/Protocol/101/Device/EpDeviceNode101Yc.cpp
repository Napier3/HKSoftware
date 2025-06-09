//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceNode101Yc.cpp  CEpDeviceNode101Yc


#include "stdafx.h"
#include "EpDeviceNode101Yc.h"

CEpDeviceNode101Yc::CEpDeviceNode101Yc()
{
	//初始化属性

	//初始化成员变量
}

CEpDeviceNode101Yc::~CEpDeviceNode101Yc()
{
}

long CEpDeviceNode101Yc::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceNode::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode101Yc::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceNode::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode101Yc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEpDeviceNode101Yc::InitAfterRead()
{
}

BOOL CEpDeviceNode101Yc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDeviceNode::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceNode101Yc *p = (CEpDeviceNode101Yc*)pObj;

	return TRUE;
}

BOOL CEpDeviceNode101Yc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDeviceNode::CopyOwn(pDest);

	CEpDeviceNode101Yc *p = (CEpDeviceNode101Yc*)pDest;

	return TRUE;
}

CBaseObject* CEpDeviceNode101Yc::Clone()
{
	CEpDeviceNode101Yc *p = new CEpDeviceNode101Yc();
	Copy(p);
	return p;
}

BOOL CEpDeviceNode101Yc::CanPaste(UINT nClassID)
{
	if (nClassID == EPDCLASSID_CEPDEVICEDATA101YC)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpDeviceNode101Yc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpDeviceData101YcKey)
	{
		pNew = new CEpDeviceData101Yc();
	}

	return pNew;
}

CExBaseObject* CEpDeviceNode101Yc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPDCLASSID_CEPDEVICEDATA101YC)
	{
		pNew = new CEpDeviceData101Yc();
	}

	return pNew;
}
