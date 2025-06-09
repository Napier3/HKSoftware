//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_FileSend.cpp  CTcpEdgePkgData_FileSend


#include "stdafx.h"
#include "TcpEdgePkgData_FileSend.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_FileSend::CTcpEdgePkgData_FileSend()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_FileSend::~CTcpEdgePkgData_FileSend()
{
}

long CTcpEdgePkgData_FileSend::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCmdIdKey, oNode, m_strCmdId);
	xml_GetAttibuteValue(pXmlKeys->m_strFullPathFileNameKey, oNode, m_strFullPathFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strFileCrcKey, oNode, m_strFileCrc);
	xml_GetAttibuteValue(pXmlKeys->m_strFileSizeKey, oNode, m_strFileSize);
	xml_GetAttibuteValue(pXmlKeys->m_strModifyTimeKey, oNode, m_strModifyTime);
	return 0;
}

long CTcpEdgePkgData_FileSend::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCmdIdKey, oElement, m_strCmdId);
	xml_SetAttributeValue(pXmlKeys->m_strFullPathFileNameKey, oElement, m_strFullPathFileName);
	xml_SetAttributeValue(pXmlKeys->m_strFileCrcKey, oElement, m_strFileCrc);
	xml_SetAttributeValue(pXmlKeys->m_strFileSizeKey, oElement, m_strFileSize);
	xml_SetAttributeValue(pXmlKeys->m_strModifyTimeKey, oElement, m_strModifyTime);
	return 0;
}

long CTcpEdgePkgData_FileSend::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCmdId);
		BinarySerializeCalLen(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileCrc);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileSize);
		BinarySerializeCalLen(oBinaryBuffer, m_strModifyTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCmdId);
		BinarySerializeRead(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeRead(oBinaryBuffer, m_strFileCrc);
		BinarySerializeRead(oBinaryBuffer, m_strFileSize);
		BinarySerializeRead(oBinaryBuffer, m_strModifyTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCmdId);
		BinarySerializeWrite(oBinaryBuffer, m_strFullPathFileName);
		BinarySerializeWrite(oBinaryBuffer, m_strFileCrc);
		BinarySerializeWrite(oBinaryBuffer, m_strFileSize);
		BinarySerializeWrite(oBinaryBuffer, m_strModifyTime);
	}
	return 0;
}

void CTcpEdgePkgData_FileSend::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_FileSend::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_FileSend *p = (CTcpEdgePkgData_FileSend*)pObj;

	if(m_strCmdId != p->m_strCmdId)
	{
		return FALSE;
	}

	if(m_strFullPathFileName != p->m_strFullPathFileName)
	{
		return FALSE;
	}

	if(m_strFileCrc != p->m_strFileCrc)
	{
		return FALSE;
	}

	if(m_strFileSize != p->m_strFileSize)
	{
		return FALSE;
	}

	if(m_strModifyTime != p->m_strModifyTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_FileSend::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_FileSend *p = (CTcpEdgePkgData_FileSend*)pDest;

	p->m_strCmdId = m_strCmdId;
	p->m_strFullPathFileName = m_strFullPathFileName;
	p->m_strFileCrc = m_strFileCrc;
	p->m_strFileSize = m_strFileSize;
	p->m_strModifyTime = m_strModifyTime;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_FileSend::Clone()
{
	CTcpEdgePkgData_FileSend *p = new CTcpEdgePkgData_FileSend();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_FileSend::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_FileSend *p = new CTcpEdgePkgData_FileSend();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_FileSend::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_FileSend::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_FileSend::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_FileSend::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strCmdIdKey, m_strCmdId);
	pRecordset->GetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileSizeKey, m_strFileSize);
	pRecordset->GetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	return 0;
}

long CTcpEdgePkgData_FileSend::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strCmdIdKey, m_strCmdId);
	pRecordset->SetFieldValue(pXmlKeys->m_strFullPathFileNameKey, m_strFullPathFileName);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileSizeKey, m_strFileSize);
	pRecordset->SetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	return 0;
}

CDvmDataset* CTcpEdgePkgData_FileSend::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_CmdId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FullPathFileName);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FileCrc);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FileSize);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ModifyTime);

	return pDataset;
}