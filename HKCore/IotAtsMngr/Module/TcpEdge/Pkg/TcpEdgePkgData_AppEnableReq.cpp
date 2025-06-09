//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_AppEnableReq.cpp  CTcpEdgePkgData_AppEnableReq


#include "stdafx.h"
#include "TcpEdgePkgData_AppEnableReq.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppEnableReq::CTcpEdgePkgData_AppEnableReq()
{
	//20230919,lmyע��, App�Ǳ�����
	//m_arrayNotMust[0] = PkgData_Node_App;
}

CTcpEdgePkgData_AppEnableReq::~CTcpEdgePkgData_AppEnableReq()
{
}

long CTcpEdgePkgData_AppEnableReq::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppEnableReq::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppEnableReq::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTcpEdgePkgData_AppEnableReq::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_AppEnableReq::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppEnableReq *p = (CTcpEdgePkgData_AppEnableReq*)pObj;

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

BOOL CTcpEdgePkgData_AppEnableReq::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppEnableReq *p = (CTcpEdgePkgData_AppEnableReq*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strApp = m_strApp;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppEnableReq::Clone()
{
	CTcpEdgePkgData_AppEnableReq *p = new CTcpEdgePkgData_AppEnableReq();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppEnableReq::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppEnableReq *p = new CTcpEdgePkgData_AppEnableReq();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppEnableReq::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppEnableReq::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppEnableReq::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_AppEnableReq::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->GetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	return 0;
}

long CTcpEdgePkgData_AppEnableReq::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->SetFieldValue(pXmlKeys->m_strAppKey, m_strApp);
	return 0;
}

CDvmDataset *CTcpEdgePkgData_AppEnableReq::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Container);
	//20230919,lmy�޸�, App�Ǳ�����
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_App);

	return pDataset;
}