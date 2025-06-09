//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_TimeSyncReq.cpp  CTcpEdgePkgData_TimeSyncReq


#include "stdafx.h"
#include "TcpEdgePkgData_TimeSyncReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_TimeSyncReq::CTcpEdgePkgData_TimeSyncReq()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_TimeSyncReq::~CTcpEdgePkgData_TimeSyncReq()
{
}

long CTcpEdgePkgData_TimeSyncReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_strTime);
	return 0;
}

long CTcpEdgePkgData_TimeSyncReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_strTime);
	return 0;
}

long CTcpEdgePkgData_TimeSyncReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTime);
	}
	return 0;
}

void CTcpEdgePkgData_TimeSyncReq::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_TimeSyncReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_TimeSyncReq *p = (CTcpEdgePkgData_TimeSyncReq*)pObj;

	if(m_strTime != p->m_strTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_TimeSyncReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_TimeSyncReq *p = (CTcpEdgePkgData_TimeSyncReq*)pDest;

	p->m_strTime = m_strTime;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_TimeSyncReq::Clone()
{
	CTcpEdgePkgData_TimeSyncReq *p = new CTcpEdgePkgData_TimeSyncReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_TimeSyncReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_TimeSyncReq *p = new CTcpEdgePkgData_TimeSyncReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_TimeSyncReq::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_TimeSyncReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_TimeSyncReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_TimeSyncReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strTimeKey, m_strTime);
	return 0;
}

long CTcpEdgePkgData_TimeSyncReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strTimeKey, m_strTime);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_TimeSyncReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CDvmData* pData = CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Time, 1, "YYYY-MM-DD HH:MM:SS.AAA");
	CTcpEdgePkgData::SetDataFormat(pData, PkgData_Node_Time);

	return pDataset;
}