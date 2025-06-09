//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgData_FileDataTrans.cpp  CTcpEdgePkgData_FileDataTrans


#include "stdafx.h"
#include "TcpEdgePkgData_FileDataTrans.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_FileDataTrans::CTcpEdgePkgData_FileDataTrans()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgData_FileDataTrans::~CTcpEdgePkgData_FileDataTrans()
{
}

BOOL CTcpEdgePkgData_FileDataTrans::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("【错误】【必需项缺失】FileDataTrans：[%1]=>[%2]必需字段缺失;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】FileDataTrans：[%1]=>[%2]字段类型错误;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_FileDataTrans::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCmdIdKey, oNode, m_strCmdId);
	xml_GetAttibuteValue(pXmlKeys->m_strFileSegNoKey, oNode, m_strFileSegNo);
	xml_GetAttibuteValue(pXmlKeys->m_strContentKey, oNode, m_strContent);
	xml_GetAttibuteValue(pXmlKeys->m_strContinueKey, oNode, m_strContinue);
	return 0;
}

long CTcpEdgePkgData_FileDataTrans::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCmdIdKey, oElement, m_strCmdId);
	xml_SetAttributeValue(pXmlKeys->m_strFileSegNoKey, oElement, m_strFileSegNo);
	xml_SetAttributeValue(pXmlKeys->m_strContentKey, oElement, m_strContent);
	xml_SetAttributeValue(pXmlKeys->m_strContinueKey, oElement, m_strContinue);
	return 0;
}

long CTcpEdgePkgData_FileDataTrans::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCmdId);
		BinarySerializeCalLen(oBinaryBuffer, m_strFileSegNo);
		BinarySerializeCalLen(oBinaryBuffer, m_strContent);
		BinarySerializeCalLen(oBinaryBuffer, m_strContinue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strCmdId);
		BinarySerializeRead(oBinaryBuffer, m_strFileSegNo);
		BinarySerializeRead(oBinaryBuffer, m_strContent);
		BinarySerializeRead(oBinaryBuffer, m_strContinue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCmdId);
		BinarySerializeWrite(oBinaryBuffer, m_strFileSegNo);
		BinarySerializeWrite(oBinaryBuffer, m_strContent);
		BinarySerializeWrite(oBinaryBuffer, m_strContinue);
	}
	return 0;
}

void CTcpEdgePkgData_FileDataTrans::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_FileDataTrans::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_FileDataTrans *p = (CTcpEdgePkgData_FileDataTrans*)pObj;

	if(m_strCmdId != p->m_strCmdId)
	{
		return FALSE;
	}

	if(m_strFileSegNo != p->m_strFileSegNo)
	{
		return FALSE;
	}

	if(m_strContent != p->m_strContent)
	{
		return FALSE;
	}

	if(m_strContinue != p->m_strContinue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_FileDataTrans::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_FileDataTrans *p = (CTcpEdgePkgData_FileDataTrans*)pDest;

	p->m_strCmdId = m_strCmdId;
	p->m_strFileSegNo = m_strFileSegNo;
	p->m_strContent = m_strContent;
	p->m_strContinue = m_strContinue;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_FileDataTrans::Clone()
{
	CTcpEdgePkgData_FileDataTrans *p = new CTcpEdgePkgData_FileDataTrans();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_FileDataTrans::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_FileDataTrans *p = new CTcpEdgePkgData_FileDataTrans();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_FileDataTrans::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_FileDataTrans::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_FileDataTrans::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_FileDataTrans::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strCmdIdKey, m_strCmdId);
	pRecordset->GetFieldValue(pXmlKeys->m_strFileSegNoKey, m_strFileSegNo);
	pRecordset->GetFieldValue(pXmlKeys->m_strContentKey, m_strContent);
	pRecordset->GetFieldValue(pXmlKeys->m_strContinueKey, m_strContinue);
	return 0;
}

long CTcpEdgePkgData_FileDataTrans::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strCmdIdKey, m_strCmdId);
	pRecordset->SetFieldValue(pXmlKeys->m_strFileSegNoKey, m_strFileSegNo);
	pRecordset->SetFieldValue(pXmlKeys->m_strContentKey, m_strContent);
	pRecordset->SetFieldValue(pXmlKeys->m_strContinueKey, m_strContinue);
	return 0;
}
CDvmDataset* CTcpEdgePkgData_FileDataTrans::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Data;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_CmdId);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FileSegNo);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Content);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Continue);

	return pDataset;
}
