//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Role.cpp  CIot_Role


#include "stdafx.h"
#include "Iot_Role.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Role::CIot_Role()
{
	//初始化属性
	m_nIndex_Role = 0;

	//初始化成员变量
}

CIot_Role::~CIot_Role()
{
}

long CIot_Role::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_RoleKey, oNode, m_nIndex_Role);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);
	return 0;
}

long CIot_Role::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_RoleKey, oElement, m_nIndex_Role);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strDescriptionKey, oElement, m_strDescription);
	return 0;
}

long CIot_Role::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Role);
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Role);
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strDescription);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Role);
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strDescription);
	}
	return 0;
}

void CIot_Role::InitAfterRead()
{
}

BOOL CIot_Role::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_Role *p = (CIot_Role*)pObj;

	if(m_nIndex_Role != p->m_nIndex_Role)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strDescription != p->m_strDescription)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Role::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_Role *p = (CIot_Role*)pDest;

	p->m_nIndex_Role = m_nIndex_Role;
	p->m_strName = m_strName;
	p->m_strDescription = m_strDescription;
	return TRUE;
}

CBaseObject* CIot_Role::Clone()
{
	CIot_Role *p = new CIot_Role();
	Copy(p);
	return p;
}

CBaseObject* CIot_Role::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Role *p = new CIot_Role();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIot_Role::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_ROLERIGHT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_Role::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_RoleRightKey)
	{
		pNew = new CIot_RoleRight();
	}

	return pNew;
}

CExBaseObject* CIot_Role::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_ROLERIGHT)
	{
		pNew = new CIot_RoleRight();
	}

	return pNew;
}
long CIot_Role::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_RoleKey, m_nIndex_Role);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strDescriptionKey, m_strDescription);
	return 0;
}

long CIot_Role::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_RoleKey, m_nIndex_Role);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strDescriptionKey, m_strDescription);
	return 0;
}

CExBaseObject* CIot_Role::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_RoleRight();

	return pNew;
}
