//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TemplateItems.cpp  CIot_TemplateItems


#include "stdafx.h"
#include "Iot_TemplateItems.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_TemplateItems::CIot_TemplateItems()
{
	//初始化属性
	m_nIndex_Items = 0;
	m_nIndex_Template = 0;

	//初始化成员变量
}

CIot_TemplateItems::~CIot_TemplateItems()
{
}

long CIot_TemplateItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemsKey, oNode, m_nIndex_Items);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TemplateKey, oNode, m_nIndex_Template);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CIot_TemplateItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemsKey, oElement, m_nIndex_Items);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TemplateKey, oElement, m_nIndex_Template);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CIot_TemplateItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Items);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Template);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CIot_TemplateItems::InitAfterRead()
{
}

BOOL CIot_TemplateItems::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_TemplateItems *p = (CIot_TemplateItems*)pObj;

	if(m_nIndex_Items != p->m_nIndex_Items)
	{
		return FALSE;
	}

	if(m_nIndex_Template != p->m_nIndex_Template)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_TemplateItems::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_TemplateItems *p = (CIot_TemplateItems*)pDest;

	p->m_nIndex_Items = m_nIndex_Items;
	p->m_nIndex_Template = m_nIndex_Template;
	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CIot_TemplateItems::Clone()
{
	CIot_TemplateItems *p = new CIot_TemplateItems();
	Copy(p);
	return p;
}

CBaseObject* CIot_TemplateItems::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_TemplateItems *p = new CIot_TemplateItems();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_TemplateItems::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_ReadFields(pRecordset, pXmlRWKeys);

	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->GetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	return 0;
}

long CIot_TemplateItems::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::DB_WriteFields(pRecordset, pXmlRWKeys);
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemsKey, m_nIndex_Items);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TemplateKey, m_nIndex_Template);
	pRecordset->SetFieldValue(pXmlKeys->m_strTypeKey, m_strType);
	return 0;
}

BOOL CIot_TemplateItems::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOT_TEMPLATEITEM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIot_TemplateItems::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIot_TemplateItemKey)
	{
		pNew = new CIot_TemplateItem();
	}

	return pNew;
}

CExBaseObject* CIot_TemplateItems::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOT_TEMPLATEITEM)
	{
		pNew = new CIot_TemplateItem();
	}

	return pNew;
}
CExBaseObject* CIot_TemplateItems::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CIot_TemplateItem();

	return pNew;
}
