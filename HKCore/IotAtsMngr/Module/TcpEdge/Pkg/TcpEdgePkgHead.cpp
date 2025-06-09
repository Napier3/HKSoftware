//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkgHead.cpp  CTcpEdgePkgHead


#include "stdafx.h"
#include "TcpEdgePkgHead.h"
#include "TcpEdgePkgData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgHead::CTcpEdgePkgHead()
{
	//初始化属性

	//初始化成员变量
}

CTcpEdgePkgHead::~CTcpEdgePkgHead()
{
}

long CTcpEdgePkgHead::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strFunNameKey, oNode, m_strFunName);
	xml_GetAttibuteValue(pXmlKeys->m_strCotKey, oNode, m_strCot);
	xml_GetAttibuteValue(pXmlKeys->m_strMidKey, oNode, m_strMid);
	xml_GetAttibuteValue(pXmlKeys->m_strTimestampKey, oNode, m_strTimestamp);
	return 0;
}

long CTcpEdgePkgHead::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strFunNameKey, oElement, m_strFunName);
	xml_SetAttributeValue(pXmlKeys->m_strCotKey, oElement, m_strCot);
	xml_SetAttributeValue(pXmlKeys->m_strMidKey, oElement, m_strMid);
	xml_SetAttributeValue(pXmlKeys->m_strTimestampKey, oElement, m_strTimestamp);
	return 0;
}

long CTcpEdgePkgHead::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strFunName);
		BinarySerializeCalLen(oBinaryBuffer, m_strCot);
		BinarySerializeCalLen(oBinaryBuffer, m_strMid);
		BinarySerializeCalLen(oBinaryBuffer, m_strTimestamp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strFunName);
		BinarySerializeRead(oBinaryBuffer, m_strCot);
		BinarySerializeRead(oBinaryBuffer, m_strMid);
		BinarySerializeRead(oBinaryBuffer, m_strTimestamp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strFunName);
		BinarySerializeWrite(oBinaryBuffer, m_strCot);
		BinarySerializeWrite(oBinaryBuffer, m_strMid);
		BinarySerializeWrite(oBinaryBuffer, m_strTimestamp);
	}
	return 0;
}

void CTcpEdgePkgHead::InitAfterRead()
{
}

BOOL CTcpEdgePkgHead::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTcpEdgePkgHead *p = (CTcpEdgePkgHead*)pObj;

	if(m_strFunName != p->m_strFunName)
	{
		return FALSE;
	}

	if(m_strCot != p->m_strCot)
	{
		return FALSE;
	}

	if(m_strMid != p->m_strMid)
	{
		return FALSE;
	}

	if(m_strTimestamp != p->m_strTimestamp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgHead::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgHead *p = (CTcpEdgePkgHead*)pDest;

	p->m_strFunName = m_strFunName;
	p->m_strCot = m_strCot;
	p->m_strMid = m_strMid;
	p->m_strTimestamp = m_strTimestamp;
	return TRUE;
}

CBaseObject* CTcpEdgePkgHead::Clone()
{
	CTcpEdgePkgHead *p = new CTcpEdgePkgHead();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgHead::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgHead *p = new CTcpEdgePkgHead();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgHead::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgHead::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgHead::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgHead::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strFunNameKey, m_strFunName);
	pRecordset->GetFieldValue(pXmlKeys->m_strCotKey, m_strCot);
	pRecordset->GetFieldValue(pXmlKeys->m_strMidKey, m_strMid);
	pRecordset->GetFieldValue(pXmlKeys->m_strTimestampKey, m_strTimestamp);
	return 0;
}

long CTcpEdgePkgHead::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strFunNameKey, m_strFunName);
	pRecordset->SetFieldValue(pXmlKeys->m_strCotKey, m_strCot);
	pRecordset->SetFieldValue(pXmlKeys->m_strMidKey, m_strMid);
	pRecordset->SetFieldValue(pXmlKeys->m_strTimestampKey, m_strTimestamp);
	return 0;
}

CDvmDataset* CTcpEdgePkgHead::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Head;
	pDataset->m_strDataType = PkgData_Type_Object;
	pDataset->m_dwItemData = 1;
	pDataset->m_dwReserved = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_FunName);
	CDvmData* pData = CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Cot, 1, "1-主动请求;2-请求应答;3-周期上送;4-变化上送;5-主动确认");
	CTcpEdgePkgData::SetDataFormat(pData, PkgData_Node_ComboBox, 5, "1", "2", "3", "4", "5");
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Mid, 1, "0~4294967295");
	pData = CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Timestamp, 1, "YYYY-MM-DD HH:MM:SS.AAA");
	CTcpEdgePkgData::SetDataFormat(pData, PkgData_Node_Time);

	return pDataset;
}