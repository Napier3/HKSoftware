//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceNode101Yt.cpp  CEpDeviceNode101Yt


#include "stdafx.h"
#include "EpDeviceNode101Yt.h"

CEpDeviceNode101Yt::CEpDeviceNode101Yt()
{
	//初始化属性

	//初始化成员变量
}

CEpDeviceNode101Yt::~CEpDeviceNode101Yt()
{
}

long CEpDeviceNode101Yt::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceNode::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode101Yt::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceNode::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode101Yt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEpDeviceNode101Yt::InitAfterRead()
{

}

BOOL CEpDeviceNode101Yt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDeviceNode::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceNode101Yt *p = (CEpDeviceNode101Yt*)pObj;

	return TRUE;
}

BOOL CEpDeviceNode101Yt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDeviceNode::CopyOwn(pDest);

	CEpDeviceNode101Yt *p = (CEpDeviceNode101Yt*)pDest;

	return TRUE;
}

CBaseObject* CEpDeviceNode101Yt::Clone()
{
	CEpDeviceNode101Yt *p = new CEpDeviceNode101Yt();
	Copy(p);
	return p;
}

BOOL CEpDeviceNode101Yt::CanPaste(UINT nClassID)
{
	if (nClassID == EPDCLASSID_CEPDEVICEDATA101YT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpDeviceNode101Yt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpDeviceData101YtKey)
	{
		pNew = new CEpDeviceData101Yt();
	}

	return pNew;
}

CExBaseObject* CEpDeviceNode101Yt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPDCLASSID_CEPDEVICEDATA101YT)
	{
		pNew = new CEpDeviceData101Yt();
	}

	return pNew;
}
