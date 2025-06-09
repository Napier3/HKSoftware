//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_FileGetResp.cpp  CTcpEdgePkgData_FileGetResp


#include "stdafx.h"
#include "TcpEdgePkgData_FileGetResp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_FileGetResp::CTcpEdgePkgData_FileGetResp()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_Note;
	m_arrayNotMust[1] = PkgData_Node_ErrorCode;
}

CTcpEdgePkgData_FileGetResp::~CTcpEdgePkgData_FileGetResp()
{
}

BOOL CTcpEdgePkgData_FileGetResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//值不存在时检查是否必需
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("【错误】【必需项缺失】FileGetResp：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】FileGetResp：[%1]=>[%2]字段类型错误;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	if(strAttrName == L"Status")
	{
		if(strAttrVal == "0")
		{
			m_arrayNotMust[1] = PkgData_Node_ErrorCode;

		}
		else if(strAttrVal == "1")
		{
			m_arrayNotMust[1] = PkgData_Node_FileCrc;
			m_arrayNotMust[2] = PkgData_Node_FileSize;
			m_arrayNotMust[3] = PkgData_Node_ModifyTime;
		}
	}

	return bRet;
}

long CTcpEdgePkgData_FileGetResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCmdIdKey, oNode, m_strCmdId);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorCodeKey, oNode, m_strErrorCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNoteKey, oNode, m_strNote);
	xml_GetAttibuteValue(pXmlKeys->m_strFileCrcKey, oNode, m_strFileCrc);
	xml_GetAttibuteValue(pXmlKeys->m_strFileSizeKey, oNode, m_strFileSize);
	xml_GetAttibuteValue(pXmlKeys->m_strModifyTimeKey, oNode, m_strModifyTime);
	return 0;
}

long CTcpEdgePkgData_FileGetResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCmdIdKey, oElement, m_strCmdId);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strErrorCodeKey, oElement, m_strErrorCode);
	xml_SetAttributeValue(pXmlKeys->m_strNoteKey, oElement, m_strNote);
	xml_SetAttributeValue(pXmlKeys->m_strFileCrcKey, oElement, m_strFileCrc);
	xml_SetAttributeValue(pXmlKeys->m_strFileSizeKey, oElement, m_strFileSize);
	xml_SetAttributeValue(pXmlKeys->m_strModifyTimeKey, oElement, m_strModifyTime);
	return 0;
}

long CTcpEdgePkgData_FileGetResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCmdId);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strNote);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileCrc);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileSize);
		BinarySerializeCalLen(oBinaryBuffer, m_strModifyTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCmdId);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strErrorCode);
		BinarySerializeRead(oBinaryBuffer, m_strNote);
		BinarySerializeRead(oBinaryBuffer, m_strFileCrc);
		BinarySerializeRead(oBinaryBuffer, m_strFileSize);
		BinarySerializeRead(oBinaryBuffer, m_strModifyTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCmdId);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorCode);
		BinarySerializeWrite(oBinaryBuffer, m_strNote);
		BinarySerializeWrite(oBinaryBuffer, m_strFileCrc);
		BinarySerializeWrite(oBinaryBuffer, m_strFileSize);
		BinarySerializeWrite(oBinaryBuffer, m_strModifyTime);
	}
	return 0;
}

void CTcpEdgePkgData_FileGetResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_FileGetResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_FileGetResp *p = (CTcpEdgePkgData_FileGetResp*)pObj;

	if(m_strCmdId != p->m_strCmdId)
	{
		return FALSE;
	}

	if(m_strStatus != p->m_strStatus)
	{
		return FALSE;
	}

	if(m_strErrorCode != p->m_strErrorCode)
	{
		return FALSE;
	}

	if(m_strNote != p->m_strNote)
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

BOOL CTcpEdgePkgData_FileGetResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_FileGetResp *p = (CTcpEdgePkgData_FileGetResp*)pDest;

	p->m_strCmdId = m_strCmdId;
	p->m_strStatus = m_strStatus;
	p->m_strErrorCode = m_strErrorCode;
	p->m_strNote = m_strNote;
	p->m_strFileCrc = m_strFileCrc;
	p->m_strFileSize = m_strFileSize;
	p->m_strModifyTime = m_strModifyTime;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_FileGetResp::Clone()
{
	CTcpEdgePkgData_FileGetResp *p = new CTcpEdgePkgData_FileGetResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_FileGetResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_FileGetResp *p = new CTcpEdgePkgData_FileGetResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_FileGetResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_FileGetResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_FileGetResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_FileGetResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strCmdIdKey, m_strCmdId);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileSizeKey, m_strFileSize);
	pRecordset->GetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	return 0;
}

long CTcpEdgePkgData_FileGetResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strCmdIdKey, m_strCmdId);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileCrcKey, m_strFileCrc);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileSizeKey, m_strFileSize);
	pRecordset->SetFieldValue(pXmlKeys->m_strModifyTimeKey, m_strModifyTime);
	return 0;
}
CDvmDataset* CTcpEdgePkgData_FileGetResp::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_CmdId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Status);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ErrorCode);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Note);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FileCrc);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FileSize);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_ModifyTime);


	return pDataset;
}