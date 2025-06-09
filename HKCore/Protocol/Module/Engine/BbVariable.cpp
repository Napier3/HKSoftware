#include "StdAfx.h"
#include "BbVariable.h"
#include "PpPackage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBbVariable::CBbVariable(void)
{
	  m_strType = _T("");
	  m_strValue = _T("");
	  m_strVarKind = _T("");
}

CBbVariable::~CBbVariable(void)
{
}


long CBbVariable::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strDataTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pKeys->m_strVariableKindKey,oNode,m_strVarKind);

	return 0;
}

long CBbVariable::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKeys->m_strDataTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pKeys->m_strVariableKindKey,oElement,m_strVarKind);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CBbVariable::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strValue != ((CBbVariable*)pObj)->m_strValue)
	{
		return FALSE;
	}

	if (m_strType != ((CBbVariable*)pObj)->m_strType)
	{
		return FALSE;
	}

	//if ( ((CBbVariable*)pObj)->m_oValue == m_oValue)
	//{
	//	return FALSE;
	//}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CBbVariable::Clone()
{
	CBbVariable* pNew = new CBbVariable();
	Copy(pNew);
	return pNew;
}

BOOL CBbVariable::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CBbVariable*)pDest)->m_strType = m_strType;
	((CBbVariable*)pDest)->m_strVarKind =m_strVarKind;
	((CBbVariable*)pDest)->m_strValue = m_strValue;
	((CBbVariable*)pDest)->m_oValue =m_oValue;

	return CExBaseObject::CopyOwn(pDest);
}

CPpPackage* CBbVariable::GetPackage(UINT nClassID)
{
	CPpPackage* pPackage = NULL;
	pPackage = (CPpPackage*)GetAncestor(nClassID);
	ASSERT(pPackage != NULL);

	return pPackage;
}