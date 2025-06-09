//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Sys_User.cpp  CSys_User


#include "stdafx.h"
#include "Sys_User.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSys_User::CSys_User()
{
	//初始化属性
	m_nUser_Id = 0;
	m_nDept_Id = 0;

	//初始化成员变量
}

CSys_User::~CSys_User()
{
}

long CSys_User::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUser_IdKey, oNode, m_nUser_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strDept_IdKey, oNode, m_nDept_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strUser_NameKey, oNode, m_strUser_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strNick_NameKey, oNode, m_strNick_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strPasswordKey, oNode, m_strPassword);
	return 0;
}

long CSys_User::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUser_IdKey, oElement, m_nUser_Id);
	xml_SetAttributeValue(pXmlKeys->m_strDept_IdKey, oElement, m_nDept_Id);
	xml_SetAttributeValue(pXmlKeys->m_strUser_NameKey, oElement, m_strUser_Name);
	xml_SetAttributeValue(pXmlKeys->m_strNick_NameKey, oElement, m_strNick_Name);
	xml_SetAttributeValue(pXmlKeys->m_strPasswordKey, oElement, m_strPassword);
	return 0;
}

long CSys_User::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nUser_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_nDept_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strUser_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strNick_Name);
		BinarySerializeCalLen(oBinaryBuffer, m_strPassword);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nUser_Id);
		BinarySerializeRead(oBinaryBuffer, m_nDept_Id);
		BinarySerializeRead(oBinaryBuffer, m_strUser_Name);
		BinarySerializeRead(oBinaryBuffer, m_strNick_Name);
		BinarySerializeRead(oBinaryBuffer, m_strPassword);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nUser_Id);
		BinarySerializeWrite(oBinaryBuffer, m_nDept_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strUser_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strNick_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strPassword);
	}
	return 0;
}

void CSys_User::InitAfterRead()
{
}

BOOL CSys_User::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSys_User *p = (CSys_User*)pObj;

	if(m_nUser_Id != p->m_nUser_Id)
	{
		return FALSE;
	}

	if(m_nDept_Id != p->m_nDept_Id)
	{
		return FALSE;
	}

	if(m_strUser_Name != p->m_strUser_Name)
	{
		return FALSE;
	}

	if(m_strNick_Name != p->m_strNick_Name)
	{
		return FALSE;
	}

	if(m_strPassword != p->m_strPassword)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSys_User::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSys_User *p = (CSys_User*)pDest;

	p->m_nUser_Id = m_nUser_Id;
	p->m_nDept_Id = m_nDept_Id;
	p->m_strUser_Name = m_strUser_Name;
	p->m_strNick_Name = m_strNick_Name;
	p->m_strPassword = m_strPassword;
	return TRUE;
}

CBaseObject* CSys_User::Clone()
{
	CSys_User *p = new CSys_User();
	Copy(p);
	return p;
}

CBaseObject* CSys_User::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSys_User *p = new CSys_User();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CSys_User::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strUser_IdKey, m_nUser_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strDept_IdKey, m_nDept_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strUser_NameKey, m_strUser_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strNick_NameKey, m_strNick_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strPasswordKey, m_strPassword);
	return 0;
}

long CSys_User::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strUser_IdKey, m_nUser_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strDept_IdKey, m_nDept_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strUser_NameKey, m_strUser_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strNick_NameKey, m_strNick_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strPasswordKey, m_strPassword);
	return 0;
}

long CSys_User::GetIndexUser(CXDbBaseLib *pXDbLib,const CString &strLoginName)
{
	if (strLoginName.IsEmpty())
	{
		return 0;
	}

	CString strUserTable,strUser_NameKey,strSql;
	strUserTable = CIot_AtsMngrXmlRWKeys::CSys_UserKey();
	strUser_NameKey = CIot_AtsMngrXmlRWKeys::User_NameKey();

	strSql.Format(_T("select * from %s where %s=\"%s\" limit 1"),strUserTable,strUser_NameKey,strLoginName);
	DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);

	return m_nUser_Id;
}

BOOL CSys_User::QueryUserByUserID(CXDbBaseLib *pXDbLib, long nUser_ID, CString &strUserName)
{
	CString strUserTable,strUser_IDKey,strSql;
	strUserTable = CIot_AtsMngrXmlRWKeys::CSys_UserKey();
	strUser_IDKey = CIot_AtsMngrXmlRWKeys::User_IdKey();

	strSql.Format(_T("select * from %s where %s=\"%d\" limit 1"),strUserTable,strUser_IDKey,nUser_ID);
	BOOL bRet = DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);

	if (bRet)
	{
		strUserName = m_strUser_Name;
	}

	return bRet;
}