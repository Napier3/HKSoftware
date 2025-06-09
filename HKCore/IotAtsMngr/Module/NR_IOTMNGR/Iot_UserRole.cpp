//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_UserRole.cpp  CIot_UserRole


#include "stdafx.h"
#include "Iot_UserRole.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_UserRole::CIot_UserRole()
{
	//初始化属性
	m_nIndex_Usrrole = 0;
	m_nIndex_User = 0;
	m_nIndex_Role = 0;

	//初始化成员变量
}

CIot_UserRole::~CIot_UserRole()
{
}

long CIot_UserRole::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_UsrroleKey, oNode, m_nIndex_Usrrole);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_UserKey, oNode, m_nIndex_User);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_RoleKey, oNode, m_nIndex_Role);
	return 0;
}

long CIot_UserRole::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_UsrroleKey, oElement, m_nIndex_Usrrole);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_UserKey, oElement, m_nIndex_User);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_RoleKey, oElement, m_nIndex_Role);
	return 0;
}

long CIot_UserRole::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Usrrole);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_User);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Role);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Usrrole);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_User);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Role);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Usrrole);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_User);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Role);
	}
	return 0;
}

void CIot_UserRole::InitAfterRead()
{
}

BOOL CIot_UserRole::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_UserRole *p = (CIot_UserRole*)pObj;

	if(m_nIndex_Usrrole != p->m_nIndex_Usrrole)
	{
		return FALSE;
	}

	if(m_nIndex_User != p->m_nIndex_User)
	{
		return FALSE;
	}

	if(m_nIndex_Role != p->m_nIndex_Role)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_UserRole::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_UserRole *p = (CIot_UserRole*)pDest;

	p->m_nIndex_Usrrole = m_nIndex_Usrrole;
	p->m_nIndex_User = m_nIndex_User;
	p->m_nIndex_Role = m_nIndex_Role;
	return TRUE;
}

CBaseObject* CIot_UserRole::Clone()
{
	CIot_UserRole *p = new CIot_UserRole();
	Copy(p);
	return p;
}

CBaseObject* CIot_UserRole::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_UserRole *p = new CIot_UserRole();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_UserRole::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_UsrroleKey, m_nIndex_Usrrole);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_RoleKey, m_nIndex_Role);
	return 0;
}

long CIot_UserRole::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_UsrroleKey, m_nIndex_Usrrole);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_UserKey, m_nIndex_User);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_RoleKey, m_nIndex_Role);
	return 0;
}

BOOL CIot_UserRole::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_USER)
	{
		m_nIndex_User = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_ROLE)
	{
		m_nIndex_Role = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

