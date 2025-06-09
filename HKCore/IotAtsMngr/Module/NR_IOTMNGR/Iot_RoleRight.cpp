//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RoleRight.cpp  CIot_RoleRight


#include "stdafx.h"
#include "Iot_RoleRight.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RoleRight::CIot_RoleRight()
{
	//初始化属性
	m_nIndex_Roleright = 0;
	m_nIndex_Role = 0;
	m_nVal_Right = 0;
	m_nType = 0;

	//初始化成员变量
}

CIot_RoleRight::~CIot_RoleRight()
{
}

long CIot_RoleRight::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_RolerightKey, oNode, m_nIndex_Roleright);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_RoleKey, oNode, m_nIndex_Role);
	xml_GetAttibuteValue(pXmlKeys->m_strVal_RightKey, oNode, m_nVal_Right);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_nType);
	return 0;
}

long CIot_RoleRight::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_RolerightKey, oElement, m_nIndex_Roleright);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_RoleKey, oElement, m_nIndex_Role);
	xml_SetAttributeValue(pXmlKeys->m_strVal_RightKey, oElement, m_nVal_Right);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_nType);
	return 0;
}

long CIot_RoleRight::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Roleright);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Role);
		BinarySerializeCalLen(oBinaryBuffer, m_nVal_Right);
		BinarySerializeCalLen(oBinaryBuffer, m_nType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Roleright);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Role);
		BinarySerializeRead(oBinaryBuffer, m_nVal_Right);
		BinarySerializeRead(oBinaryBuffer, m_nType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Roleright);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Role);
		BinarySerializeWrite(oBinaryBuffer, m_nVal_Right);
		BinarySerializeWrite(oBinaryBuffer, m_nType);
	}
	return 0;
}

void CIot_RoleRight::InitAfterRead()
{
}

BOOL CIot_RoleRight::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RoleRight *p = (CIot_RoleRight*)pObj;

	if(m_nIndex_Roleright != p->m_nIndex_Roleright)
	{
		return FALSE;
	}

	if(m_nIndex_Role != p->m_nIndex_Role)
	{
		return FALSE;
	}

	if(m_nVal_Right != p->m_nVal_Right)
	{
		return FALSE;
	}

	if(m_nType != p->m_nType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RoleRight::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RoleRight *p = (CIot_RoleRight*)pDest;

	p->m_nIndex_Roleright = m_nIndex_Roleright;
	p->m_nIndex_Role = m_nIndex_Role;
	p->m_nVal_Right = m_nVal_Right;
	p->m_nType = m_nType;
	return TRUE;
}

CBaseObject* CIot_RoleRight::Clone()
{
	CIot_RoleRight *p = new CIot_RoleRight();
	Copy(p);
	return p;
}

CBaseObject* CIot_RoleRight::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RoleRight *p = new CIot_RoleRight();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RoleRight::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_RolerightKey, m_nIndex_Roleright);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_RoleKey, m_nIndex_Role);
	pRecordset->GetFieldValue(pXmlKeys->m_strVal_RightKey, m_nVal_Right);
	pRecordset->GetFieldValue(pXmlKeys->m_strTypeKey, m_nType);
	return 0;
}

long CIot_RoleRight::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_RolerightKey, m_nIndex_Roleright);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_RoleKey, m_nIndex_Role);
	pRecordset->SetFieldValue(pXmlKeys->m_strVal_RightKey, m_nVal_Right);
	pRecordset->SetFieldValue(pXmlKeys->m_strTypeKey, m_nType);
	return 0;
}

BOOL CIot_RoleRight::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_ROLE)
	{
		m_nIndex_Role = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_RIGHT)
	{
		m_nVal_Right = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

