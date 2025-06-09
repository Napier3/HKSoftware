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
	::GetLocalTime(&m_tmLogin_Date);
	::GetLocalTime(&m_tmCreate_Time);
	::GetLocalTime(&m_tmUpdate_Time);

	//初始化成员变量
}

CSys_User::~CSys_User()
{
}

long CSys_User::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUser_IdKey, oNode, m_nUser_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strDept_IdKey, oNode, m_nDept_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strUser_NameKey, oNode, m_strUser_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strNick_NameKey, oNode, m_strNick_Name);
	xml_GetAttibuteValue(pXmlKeys->m_strUser_TypeKey, oNode, m_strUser_Type);
	xml_GetAttibuteValue(pXmlKeys->m_strEmailKey, oNode, m_strEmail);
	xml_GetAttibuteValue(pXmlKeys->m_strPhonenumberKey, oNode, m_strPhonenumber);
	xml_GetAttibuteValue(pXmlKeys->m_strSexKey, oNode, m_strSex);
	xml_GetAttibuteValue(pXmlKeys->m_strAvatarKey, oNode, m_strAvatar);
	xml_GetAttibuteValue(pXmlKeys->m_strPasswordKey, oNode, m_strPassword);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strDel_FlagKey, oNode, m_strDel_Flag);
	xml_GetAttibuteValue(pXmlKeys->m_strLogin_IpKey, oNode, m_strLogin_Ip);
	xml_GetAttibuteValue(pXmlKeys->m_strLogin_DateKey, oNode, m_tmLogin_Date);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_ByKey, oNode, m_strCreate_By);
	xml_GetAttibuteValue(pXmlKeys->m_strCreate_TimeKey, oNode, m_tmCreate_Time);
	xml_GetAttibuteValue(pXmlKeys->m_strUpdate_ByKey, oNode, m_strUpdate_By);
	xml_GetAttibuteValue(pXmlKeys->m_strUpdate_TimeKey, oNode, m_tmUpdate_Time);
	xml_GetAttibuteValue(pXmlKeys->m_strRemarkKey, oNode, m_strRemark);
	return 0;
}

long CSys_User::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUser_IdKey, oElement, m_nUser_Id);
	xml_SetAttributeValue(pXmlKeys->m_strDept_IdKey, oElement, m_nDept_Id);
	xml_SetAttributeValue(pXmlKeys->m_strUser_NameKey, oElement, m_strUser_Name);
	xml_SetAttributeValue(pXmlKeys->m_strNick_NameKey, oElement, m_strNick_Name);
	xml_SetAttributeValue(pXmlKeys->m_strUser_TypeKey, oElement, m_strUser_Type);
	xml_SetAttributeValue(pXmlKeys->m_strEmailKey, oElement, m_strEmail);
	xml_SetAttributeValue(pXmlKeys->m_strPhonenumberKey, oElement, m_strPhonenumber);
	xml_SetAttributeValue(pXmlKeys->m_strSexKey, oElement, m_strSex);
	xml_SetAttributeValue(pXmlKeys->m_strAvatarKey, oElement, m_strAvatar);
	xml_SetAttributeValue(pXmlKeys->m_strPasswordKey, oElement, m_strPassword);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strDel_FlagKey, oElement, m_strDel_Flag);
	xml_SetAttributeValue(pXmlKeys->m_strLogin_IpKey, oElement, m_strLogin_Ip);
	xml_SetAttributeValue(pXmlKeys->m_strLogin_DateKey, oElement, m_tmLogin_Date);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_ByKey, oElement, m_strCreate_By);
	xml_SetAttributeValue(pXmlKeys->m_strCreate_TimeKey, oElement, m_tmCreate_Time);
	xml_SetAttributeValue(pXmlKeys->m_strUpdate_ByKey, oElement, m_strUpdate_By);
	xml_SetAttributeValue(pXmlKeys->m_strUpdate_TimeKey, oElement, m_tmUpdate_Time);
	xml_SetAttributeValue(pXmlKeys->m_strRemarkKey, oElement, m_strRemark);
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
		BinarySerializeCalLen(oBinaryBuffer, m_strUser_Type);
		BinarySerializeCalLen(oBinaryBuffer, m_strEmail);
		BinarySerializeCalLen(oBinaryBuffer, m_strPhonenumber);
		BinarySerializeCalLen(oBinaryBuffer, m_strSex);
		BinarySerializeCalLen(oBinaryBuffer, m_strAvatar);
		BinarySerializeCalLen(oBinaryBuffer, m_strPassword);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strDel_Flag);
		BinarySerializeCalLen(oBinaryBuffer, m_strLogin_Ip);
		BinarySerializeCalLen(oBinaryBuffer, m_tmLogin_Date);
		BinarySerializeCalLen(oBinaryBuffer, m_strCreate_By);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeCalLen(oBinaryBuffer, m_strUpdate_By);
		BinarySerializeCalLen(oBinaryBuffer, m_tmUpdate_Time);
		BinarySerializeCalLen(oBinaryBuffer, m_strRemark);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nUser_Id);
		BinarySerializeRead(oBinaryBuffer, m_nDept_Id);
		BinarySerializeRead(oBinaryBuffer, m_strUser_Name);
		BinarySerializeRead(oBinaryBuffer, m_strNick_Name);
		BinarySerializeRead(oBinaryBuffer, m_strUser_Type);
		BinarySerializeRead(oBinaryBuffer, m_strEmail);
		BinarySerializeRead(oBinaryBuffer, m_strPhonenumber);
		BinarySerializeRead(oBinaryBuffer, m_strSex);
		BinarySerializeRead(oBinaryBuffer, m_strAvatar);
		BinarySerializeRead(oBinaryBuffer, m_strPassword);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strDel_Flag);
		BinarySerializeRead(oBinaryBuffer, m_strLogin_Ip);
		BinarySerializeRead(oBinaryBuffer, m_tmLogin_Date);
		BinarySerializeRead(oBinaryBuffer, m_strCreate_By);
		BinarySerializeRead(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeRead(oBinaryBuffer, m_strUpdate_By);
		BinarySerializeRead(oBinaryBuffer, m_tmUpdate_Time);
		BinarySerializeRead(oBinaryBuffer, m_strRemark);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nUser_Id);
		BinarySerializeWrite(oBinaryBuffer, m_nDept_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strUser_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strNick_Name);
		BinarySerializeWrite(oBinaryBuffer, m_strUser_Type);
		BinarySerializeWrite(oBinaryBuffer, m_strEmail);
		BinarySerializeWrite(oBinaryBuffer, m_strPhonenumber);
		BinarySerializeWrite(oBinaryBuffer, m_strSex);
		BinarySerializeWrite(oBinaryBuffer, m_strAvatar);
		BinarySerializeWrite(oBinaryBuffer, m_strPassword);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strDel_Flag);
		BinarySerializeWrite(oBinaryBuffer, m_strLogin_Ip);
		BinarySerializeWrite(oBinaryBuffer, m_tmLogin_Date);
		BinarySerializeWrite(oBinaryBuffer, m_strCreate_By);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreate_Time);
		BinarySerializeWrite(oBinaryBuffer, m_strUpdate_By);
		BinarySerializeWrite(oBinaryBuffer, m_tmUpdate_Time);
		BinarySerializeWrite(oBinaryBuffer, m_strRemark);
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

	if(m_strUser_Type != p->m_strUser_Type)
	{
		return FALSE;
	}

	if(m_strEmail != p->m_strEmail)
	{
		return FALSE;
	}

	if(m_strPhonenumber != p->m_strPhonenumber)
	{
		return FALSE;
	}

	if(m_strSex != p->m_strSex)
	{
		return FALSE;
	}

	if(m_strAvatar != p->m_strAvatar)
	{
		return FALSE;
	}

	if(m_strPassword != p->m_strPassword)
	{
		return FALSE;
	}

	if(m_strStatus != p->m_strStatus)
	{
		return FALSE;
	}

	if(m_strDel_Flag != p->m_strDel_Flag)
	{
		return FALSE;
	}

	if(m_strLogin_Ip != p->m_strLogin_Ip)
	{
		return FALSE;
	}

	if(m_strCreate_By != p->m_strCreate_By)
	{
		return FALSE;
	}

	if(m_strUpdate_By != p->m_strUpdate_By)
	{
		return FALSE;
	}

	if(m_strRemark != p->m_strRemark)
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
	p->m_strUser_Type = m_strUser_Type;
	p->m_strEmail = m_strEmail;
	p->m_strPhonenumber = m_strPhonenumber;
	p->m_strSex = m_strSex;
	p->m_strAvatar = m_strAvatar;
	p->m_strPassword = m_strPassword;
	p->m_strStatus = m_strStatus;
	p->m_strDel_Flag = m_strDel_Flag;
	p->m_strLogin_Ip = m_strLogin_Ip;
	p->m_tmLogin_Date = m_tmLogin_Date;
	p->m_strCreate_By = m_strCreate_By;
	p->m_tmCreate_Time = m_tmCreate_Time;
	p->m_strUpdate_By = m_strUpdate_By;
	p->m_tmUpdate_Time = m_tmUpdate_Time;
	p->m_strRemark = m_strRemark;
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
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strUser_IdKey, m_nUser_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strDept_IdKey, m_nDept_Id);
	pRecordset->GetFieldValue(pXmlKeys->m_strUser_NameKey, m_strUser_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strNick_NameKey, m_strNick_Name);
	pRecordset->GetFieldValue(pXmlKeys->m_strUser_TypeKey, m_strUser_Type);
	pRecordset->GetFieldValue(pXmlKeys->m_strEmailKey, m_strEmail);
	pRecordset->GetFieldValue(pXmlKeys->m_strPhonenumberKey, m_strPhonenumber);
	pRecordset->GetFieldValue(pXmlKeys->m_strSexKey, m_strSex);
	pRecordset->GetFieldValue(pXmlKeys->m_strAvatarKey, m_strAvatar);
	pRecordset->GetFieldValue(pXmlKeys->m_strPasswordKey, m_strPassword);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strDel_FlagKey, m_strDel_Flag);
	pRecordset->GetFieldValue(pXmlKeys->m_strLogin_IpKey, m_strLogin_Ip);
	pRecordset->GetFieldValue(pXmlKeys->m_strLogin_DateKey, m_tmLogin_Date);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_ByKey, m_strCreate_By);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	pRecordset->GetFieldValue(pXmlKeys->m_strUpdate_ByKey, m_strUpdate_By);
	pRecordset->GetFieldValue(pXmlKeys->m_strUpdate_TimeKey, m_tmUpdate_Time);
	pRecordset->GetFieldValue(pXmlKeys->m_strRemarkKey, m_strRemark);
	return 0;
}

long CSys_User::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strUser_IdKey, m_nUser_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strDept_IdKey, m_nDept_Id);
	pRecordset->SetFieldValue(pXmlKeys->m_strUser_NameKey, m_strUser_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strNick_NameKey, m_strNick_Name);
	pRecordset->SetFieldValue(pXmlKeys->m_strUser_TypeKey, m_strUser_Type);
	pRecordset->SetFieldValue(pXmlKeys->m_strEmailKey, m_strEmail);
	pRecordset->SetFieldValue(pXmlKeys->m_strPhonenumberKey, m_strPhonenumber);
	pRecordset->SetFieldValue(pXmlKeys->m_strSexKey, m_strSex);
	pRecordset->SetFieldValue(pXmlKeys->m_strAvatarKey, m_strAvatar);
	pRecordset->SetFieldValue(pXmlKeys->m_strPasswordKey, m_strPassword);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strDel_FlagKey, m_strDel_Flag);
	pRecordset->SetFieldValue(pXmlKeys->m_strLogin_IpKey, m_strLogin_Ip);
	pRecordset->SetFieldValue(pXmlKeys->m_strLogin_DateKey, m_tmLogin_Date);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_ByKey, m_strCreate_By);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreate_TimeKey, m_tmCreate_Time);
	pRecordset->SetFieldValue(pXmlKeys->m_strUpdate_ByKey, m_strUpdate_By);
	pRecordset->SetFieldValue(pXmlKeys->m_strUpdate_TimeKey, m_tmUpdate_Time);
	pRecordset->SetFieldValue(pXmlKeys->m_strRemarkKey, m_strRemark);
	return 0;
}

