//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDevice.cpp  CEpDevice


#include "stdafx.h"
#include "EpDevice.h"

CEpDevice::CEpDevice()
{
	//初始化属性
	m_nAddress = 0;

	//初始化成员变量
}

CEpDevice::~CEpDevice()
{
}

long CEpDevice::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDeviceXmlRWKeys *pXmlKeys = (CEpDeviceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDevice::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDeviceXmlRWKeys *pXmlKeys = (CEpDeviceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CEpDevice::InitAfterRead()
{
}

BOOL CEpDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDevice *p = (CEpDevice*)pObj;

	return TRUE;
}

BOOL CEpDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEpDevice *p = (CEpDevice*)pDest;

	return TRUE;
}

CBaseObject* CEpDevice::Clone()
{
	CEpDevice *p = new CEpDevice();
	Copy(p);
	return p;
}

BOOL CEpDevice::CanPaste(UINT nClassID)
{
	if (nClassID == EPDCLASSID_CEPDEVICENODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDeviceXmlRWKeys *pXmlKeys = (CEpDeviceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpDeviceNodeKey)
	{
		pNew = new CEpDeviceNode();
	}

	return pNew;
}

CExBaseObject* CEpDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPDCLASSID_CEPDEVICENODE)
	{
		pNew = new CEpDeviceNode();
	}

	return pNew;
}
