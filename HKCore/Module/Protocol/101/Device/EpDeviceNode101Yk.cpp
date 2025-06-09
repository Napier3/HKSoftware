//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpDeviceNode101Yk.cpp  CEpDeviceNode101Yk


#include "stdafx.h"
#include "EpDeviceNode101Yk.h"

CEpDeviceNode101Yk::CEpDeviceNode101Yk()
{
	//��ʼ������

	//��ʼ����Ա����
}

CEpDeviceNode101Yk::~CEpDeviceNode101Yk()
{
}

long CEpDeviceNode101Yk::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceNode::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode101Yk::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDeviceNode::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDeviceNode101Yk::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEpDeviceNode101Yk::InitAfterRead()
{
}

BOOL CEpDeviceNode101Yk::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDeviceNode::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDeviceNode101Yk *p = (CEpDeviceNode101Yk*)pObj;

	return TRUE;
}

BOOL CEpDeviceNode101Yk::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDeviceNode::CopyOwn(pDest);

	CEpDeviceNode101Yk *p = (CEpDeviceNode101Yk*)pDest;

	return TRUE;
}

CBaseObject* CEpDeviceNode101Yk::Clone()
{
	CEpDeviceNode101Yk *p = new CEpDeviceNode101Yk();
	Copy(p);
	return p;
}

BOOL CEpDeviceNode101Yk::CanPaste(UINT nClassID)
{
	if (nClassID == EPDCLASSID_CEPDEVICEDATA101YK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpDeviceNode101Yk::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpDeviceData101YkKey)
	{
		pNew = new CEpDeviceData101Yk();
	}

	return pNew;
}

CExBaseObject* CEpDeviceNode101Yk::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPDCLASSID_CEPDEVICEDATA101YK)
	{
		pNew = new CEpDeviceData101Yk();
	}

	return pNew;
}
