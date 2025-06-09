//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_BenchCommPort.cpp  CIot_BenchCommPort


#include "stdafx.h"
#include "Iot_BenchCommPort.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_BenchCommPort::CIot_BenchCommPort()
{
	//初始化属性
	m_nIndex_Comm = 0;
	m_nIndex_Bench = 0;
	m_nPort = 0;

	//初始化成员变量
}

CIot_BenchCommPort::~CIot_BenchCommPort()
{
}

long CIot_BenchCommPort::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_CommKey, oNode, m_nIndex_Comm);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strIpKey, oNode, m_strIp);
	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_nPort);
	return 0;
}

long CIot_BenchCommPort::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_CommKey, oElement, m_nIndex_Comm);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strIpKey, oElement, m_strIp);
	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_nPort);
	return 0;
}

long CIot_BenchCommPort::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Comm);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strIp);
		BinarySerializeCalLen(oBinaryBuffer, m_nPort);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Comm);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strIp);
		BinarySerializeRead(oBinaryBuffer, m_nPort);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Comm);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strIp);
		BinarySerializeWrite(oBinaryBuffer, m_nPort);
	}
	return 0;
}

void CIot_BenchCommPort::InitAfterRead()
{
}

BOOL CIot_BenchCommPort::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_BenchCommPort *p = (CIot_BenchCommPort*)pObj;

	if(m_nIndex_Comm != p->m_nIndex_Comm)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strIp != p->m_strIp)
	{
		return FALSE;
	}

	if(m_nPort != p->m_nPort)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_BenchCommPort::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_BenchCommPort *p = (CIot_BenchCommPort*)pDest;

	p->m_nIndex_Comm = m_nIndex_Comm;
	p->m_nIndex_Bench = m_nIndex_Bench;
	p->m_strType = m_strType;
	p->m_strIp = m_strIp;
	p->m_nPort = m_nPort;
	return TRUE;
}

CBaseObject* CIot_BenchCommPort::Clone()
{
	CIot_BenchCommPort *p = new CIot_BenchCommPort();
	Copy(p);
	return p;
}

CBaseObject* CIot_BenchCommPort::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_BenchCommPort *p = new CIot_BenchCommPort();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_BenchCommPort::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_CommKey, m_nIndex_Comm);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	pRecordset->GetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->GetFieldValue(pXmlKeys->m_strPortKey, m_nPort);
	return 0;
}

long CIot_BenchCommPort::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_CommKey, m_nIndex_Comm);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	pRecordset->SetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->SetFieldValue(pXmlKeys->m_strPortKey, m_nPort);
	return 0;
}

BOOL CIot_BenchCommPort::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	return TRUE;
}

