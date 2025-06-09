#include "StdAfx.h"
#include "PpDataBind.h"
#include "BbVariable.h"
#include "PpPackage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpDataBind::CPpDataBind(void)
{
	 m_strDataAttrID="";
}

CPpDataBind::~CPpDataBind(void)
{
}

long CPpDataBind::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pKeys->m_strIDKey, oNode, m_strDataAttrID);
	xml_GetAttibuteValue(pKeys->m_strDataTypeKey, oNode, m_strDataType);

	m_strID = m_strDataAttrID;

	return 0;
}

long CPpDataBind::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	m_strID = m_strDataAttrID;

	xml_SetAttributeValue(pKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pKeys->m_strIDKey, oElement, m_strDataAttrID);
	xml_SetAttributeValue(pKeys->m_strDataTypeKey, oElement, m_strDataType);

	return 0;
}

long CPpDataBind::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CPpDataBind::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return NULL;
}

CExBaseObject* CPpDataBind::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpDataBind::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_strDataAttrID != ((CPpDataBind*)pObj)->m_strDataAttrID)
	{
		return FALSE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CPpDataBind::Clone()
{
	CPpDataBind* pNew = new CPpDataBind();
	Copy(pNew);
	return pNew;
}

BOOL CPpDataBind::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpDataBind*)pDest)->m_strDataAttrID = m_strDataAttrID;
	((CPpDataBind*)pDest)->m_strDataType = m_strDataType;

	return CExBaseObject::CopyOwn(pDest);
}

void CPpDataBind::InitDataType()
{
	CBbVariable *pVariable = PpFindVariableByID(this, m_strDataAttrID);

	if (pVariable != NULL)
	{
		m_strDataType = pVariable->m_strType;
	}
}

