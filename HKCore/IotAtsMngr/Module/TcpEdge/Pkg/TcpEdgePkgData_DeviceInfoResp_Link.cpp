//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_DeviceInfoResp_Link.cpp  CTcpEdgePkgData_DeviceInfoResp_Link


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceInfoResp_Link.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceInfoResp_Link::CTcpEdgePkgData_DeviceInfoResp_Link()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_DeviceInfoResp_Link::~CTcpEdgePkgData_DeviceInfoResp_Link()
{
}

long CTcpEdgePkgData_DeviceInfoResp_Link::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strIdKey, oNode, m_strId);
	xml_GetAttibuteValue(pXmlKeys->m_strMacKey, oNode, m_strMac);
	return 0;
}

long CTcpEdgePkgData_DeviceInfoResp_Link::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strIdKey, oElement, m_strId);
	xml_SetAttributeValue(pXmlKeys->m_strMacKey, oElement, m_strMac);
	return 0;
}

long CTcpEdgePkgData_DeviceInfoResp_Link::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strId);
		BinarySerializeCalLen(oBinaryBuffer, m_strMac);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strId);
		BinarySerializeRead(oBinaryBuffer, m_strMac);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strId);
		BinarySerializeWrite(oBinaryBuffer, m_strMac);
	}
	return 0;
}

void CTcpEdgePkgData_DeviceInfoResp_Link::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_DeviceInfoResp_Link::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceInfoResp_Link *p = (CTcpEdgePkgData_DeviceInfoResp_Link*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strId != p->m_strId)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strMac != p->m_strMac)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceInfoResp_Link::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceInfoResp_Link *p = (CTcpEdgePkgData_DeviceInfoResp_Link*)pDest;

	p->m_strType = m_strType;
	p->m_strId = m_strId;
	p->m_strName = m_strName;
	p->m_strMac = m_strMac;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceInfoResp_Link::Clone()
{
	CTcpEdgePkgData_DeviceInfoResp_Link *p = new CTcpEdgePkgData_DeviceInfoResp_Link();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceInfoResp_Link::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceInfoResp_Link *p = new CTcpEdgePkgData_DeviceInfoResp_Link();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceInfoResp_Link::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceInfoResp_Link::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceInfoResp_Link::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_DeviceInfoResp_Link::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	pRecordset->GetFieldValue(pXmlKeys->m_strIdKey, m_strId);
	pRecordset->GetFieldValue(pXmlKeys->m_strMacKey, m_strMac);
	return 0;
}

long CTcpEdgePkgData_DeviceInfoResp_Link::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	pRecordset->SetFieldValue(pXmlKeys->m_strIdKey, m_strId);
	pRecordset->SetFieldValue(pXmlKeys->m_strMacKey, m_strMac);
	return 0;
}

