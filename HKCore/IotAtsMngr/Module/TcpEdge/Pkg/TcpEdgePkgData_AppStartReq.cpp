//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_AppStartReq.cpp  CTcpEdgePkgData_AppStartReq


#include "stdafx.h"
#include "TcpEdgePkgData_AppStartReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppStartReq::CTcpEdgePkgData_AppStartReq()
{
	//20230919,lmy注释, App是必需项
	//m_arrayNotMust[0] = PkgData_Node_App;
}

CTcpEdgePkgData_AppStartReq::~CTcpEdgePkgData_AppStartReq()
{
}

long CTcpEdgePkgData_AppStartReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppStartReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppStartReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strApp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
	}
	return 0;
}

void CTcpEdgePkgData_AppStartReq::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_AppStartReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppStartReq *p = (CTcpEdgePkgData_AppStartReq*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppStartReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppStartReq *p = (CTcpEdgePkgData_AppStartReq*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strApp = m_strApp;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppStartReq::Clone()
{
	CTcpEdgePkgData_AppStartReq *p = new CTcpEdgePkgData_AppStartReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppStartReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppStartReq *p = new CTcpEdgePkgData_AppStartReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppStartReq::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppStartReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppStartReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_AppStartReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->GetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppStartReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->SetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	return 0;
}

CDvmDataset *CTcpEdgePkgData_AppStartReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Container);
	//20230919,lmy注释, App是必需项
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_App);

	return pDataset;
}