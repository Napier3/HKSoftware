//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_FileGet.cpp  CTcpEdgePkgData_FileGet


#include "stdafx.h"
#include "TcpEdgePkgData_FileGet.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_FileGet::CTcpEdgePkgData_FileGet()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_FileGet::~CTcpEdgePkgData_FileGet()
{
}

long CTcpEdgePkgData_FileGet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCmdIdKey, oNode, m_strCmdId);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathFileNameKey, oNode, m_strFullPathFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strStartByteKey, oNode, m_strStartByte);
	return 0;
}

long CTcpEdgePkgData_FileGet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCmdIdKey, oElement, m_strCmdId);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathFileNameKey, oElement, m_strFullPathFileName);
	xml_SetAttributeValue(pXmlKeys->m_strStartByteKey, oElement, m_strStartByte);
	return 0;
}

long CTcpEdgePkgData_FileGet::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCmdId);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strStartByte);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCmdId);
		BinarySerializeRead(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeRead(oBinaryBuffer, m_strStartByte);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCmdId);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strStartByte);
	}
	return 0;
}

void CTcpEdgePkgData_FileGet::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_FileGet::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_FileGet *p = (CTcpEdgePkgData_FileGet*)pObj;

	if(m_strCmdId != p->m_strCmdId)
	{
		return FALSE;
	}

	if(m_strFullPathFileName != p->m_strFullPathFileName)
	{
		return FALSE;
	}

	if(m_strStartByte != p->m_strStartByte)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_FileGet::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_FileGet *p = (CTcpEdgePkgData_FileGet*)pDest;

	p->m_strCmdId = m_strCmdId;
	p->m_strFullPathFileName = m_strFullPathFileName;
	p->m_strStartByte = m_strStartByte;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_FileGet::Clone()
{
	CTcpEdgePkgData_FileGet *p = new CTcpEdgePkgData_FileGet();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_FileGet::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_FileGet *p = new CTcpEdgePkgData_FileGet();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_FileGet::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_FileGet::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_FileGet::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_FileGet::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strCmdIdKey, m_strCmdId);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strStartByteKey, m_strStartByte);
	return 0;
}

long CTcpEdgePkgData_FileGet::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strCmdIdKey, m_strCmdId);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strStartByteKey, m_strStartByte);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_FileGet::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_CmdId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FullPathFileName);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_StartByte);

	return pDataset;
}