//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcNetDevices.cpp  CEmcNetDevices


#include "stdafx.h"
#include "EmcNetDevices.h"

CEmcNetDevices::CEmcNetDevices()
{
	//初始化属性
	m_strName = _T("网卡监视管理");
	m_strID = _T("EmcNetDevices");

	//初始化成员变量
}

CEmcNetDevices::~CEmcNetDevices()
{
}

long CEmcNetDevices::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcNetDevices::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEmcNetDevices::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CEmcNetDevices::InitAfterRead()
{
}

BOOL CEmcNetDevices::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEmcNetDevices *p = (CEmcNetDevices*)pObj;

	return TRUE;
}

BOOL CEmcNetDevices::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEmcNetDevices *p = (CEmcNetDevices*)pDest;

	return TRUE;
}

CBaseObject* CEmcNetDevices::Clone()
{
	CEmcNetDevices *p = new CEmcNetDevices();
	Copy(p);
	return p;
}

BOOL CEmcNetDevices::CanPaste(UINT nClassID)
{
	if (nClassID == EMCCLASSID_CEMCNETDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEmcNetDevices::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEmcNetDeviceKey)
	{
		pNew = new CEmcNetDevice();
	}

	return pNew;
}

CExBaseObject* CEmcNetDevices::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCNETDEVICE)
	{
		pNew = new CEmcNetDevice();
	}

	return pNew;
}
