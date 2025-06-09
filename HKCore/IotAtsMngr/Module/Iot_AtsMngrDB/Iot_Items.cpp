//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Items.cpp  CIot_Items


#include "stdafx.h"
#include "Iot_Items.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_Items::CIot_Items()
{
	//初始化属性
	m_nIndex_Items = 0;

	//初始化成员变量
}

CIot_Items::~CIot_Items()
{
}

long CIot_Items::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemsKey, oNode, m_nIndex_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CIot_Items::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemsKey, oElement, m_nIndex_Items);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CIot_Items::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CIot_Items::InitAfterRead()
{
}

BOOL CIot_Items::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_Items *p = (CIot_Items*)pObj;

	if(m_nIndex_Items != p->m_nIndex_Items)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_Items::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_Items *p = (CIot_Items*)pDest;

	p->m_nIndex_Items = m_nIndex_Items;
	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CIot_Items::Clone()
{
	CIot_Items *p = new CIot_Items();
	Copy(p);
	return p;
}

CBaseObject* CIot_Items::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_Items *p = new CIot_Items();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_Items::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	return 0;
}

long CIot_Items::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strNameKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strIDKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	return 0;
}

BOOL CIot_Items::QueryItemsBySN(CXDbBaseLib *pXDbLib,const CString &strItemsSN)
{
	CString strTable,strSql;
	strTable = CIot_AtsMngrXmlRWKeys::CIot_ItemsKey();

	strSql.Format(_T("select * from %s where id=\"%s\" limit 1"),strTable, strItemsSN);

	return DB_Select_OwnEx(pXDbLib, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, strSql);
}