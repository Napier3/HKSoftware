//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_ConStopReq.cpp  CTcpEdgePkgData_ConStopReq


#include "stdafx.h"
#include "TcpEdgePkgData_ConStopReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_ConStopReq::CTcpEdgePkgData_ConStopReq()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_ConStopReq::~CTcpEdgePkgData_ConStopReq()
{
}

long CTcpEdgePkgData_ConStopReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	return 0;
}

long CTcpEdgePkgData_ConStopReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	return 0;
}

long CTcpEdgePkgData_ConStopReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
	}
	return 0;
}

void CTcpEdgePkgData_ConStopReq::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ConStopReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ConStopReq *p = (CTcpEdgePkgData_ConStopReq*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_ConStopReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ConStopReq *p = (CTcpEdgePkgData_ConStopReq*)pDest;

	p->m_strContainer = m_strContainer;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ConStopReq::Clone()
{
	CTcpEdgePkgData_ConStopReq *p = new CTcpEdgePkgData_ConStopReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_ConStopReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_ConStopReq *p = new CTcpEdgePkgData_ConStopReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_ConStopReq::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ConStopReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ConStopReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_ConStopReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	return 0;
}

long CTcpEdgePkgData_ConStopReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_ConStopReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Container);

	return pDataset;
}
