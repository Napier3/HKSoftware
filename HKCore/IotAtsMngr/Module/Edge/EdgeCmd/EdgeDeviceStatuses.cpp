//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeDeviceStatuses.cpp  CEdgeDeviceStatuses


#include "stdafx.h"
#include "EdgeDeviceStatuses.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeDeviceStatuses::CEdgeDeviceStatuses()
{
	//初始化属性

	//初始化成员变量
}

CEdgeDeviceStatuses::~CEdgeDeviceStatuses()
{
}

long CEdgeDeviceStatuses::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceStatusKey, oNode, m_strDeviceStatus);
	return 0;
}

long CEdgeDeviceStatuses::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceStatusKey, oElement, m_strDeviceStatus);
	return 0;
}

long CEdgeDeviceStatuses::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceStatus);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceStatus);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceStatus);
	}
	return 0;
}

void CEdgeDeviceStatuses::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pDeviceStatus = new CExBaseList;
	pDeviceStatus->m_strID = CEdgeCmdMngrXmlRWKeys::DeviceStatusKey();
	pDeviceStatus->m_strName = m_strDeviceStatus;
	AddNewChild(pDeviceStatus);

	CExBaseList* pDeviceId = new CExBaseList;
	pDeviceId->m_strID = CEdgeCmdMngrXmlRWKeys::DeviceIdKey();
	pDeviceId->m_strName = m_strDeviceId;
	AddNewChild(pDeviceId);
}

BOOL CEdgeDeviceStatuses::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeDeviceStatuses *p = (CEdgeDeviceStatuses*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_strDeviceStatus != p->m_strDeviceStatus)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeDeviceStatuses::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDeviceStatuses *p = (CEdgeDeviceStatuses*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strDeviceStatus = m_strDeviceStatus;
	return TRUE;
}

CBaseObject* CEdgeDeviceStatuses::Clone()
{
	CEdgeDeviceStatuses *p = new CEdgeDeviceStatuses();
	Copy(p);
	return p;
}

CBaseObject* CEdgeDeviceStatuses::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeDeviceStatuses *p = new CEdgeDeviceStatuses();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeDeviceStatuses::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeDeviceStatuses::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeDeviceStatuses::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
