// RioIndex.cpp: 实现文件
//

#include "stdafx.h"

#include "RioIndex.h"

// CRioIndex

CRioIndex::CRioIndex()
{
	//初始化属性
	m_strValue = _T("");
	m_strValueFormula = _T("");
    m_strType = _T("");
    m_strRefParam = _T("");

}

CRioIndex::~CRioIndex()
{
}

long CRioIndex::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	xml_GetElementText(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetElementText(pXmlKeys->m_strValueFormulaKey, oNode, m_strValueFormula);
    xml_GetElementText(pXmlKeys->m_strRefParamKey, oNode, m_strRefParam);

	return 0;
}

long CRioIndex::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	xml_SetElementText(pXmlKeys->m_strValueKey, oXMLDoc, oElement, m_strValue);
	xml_SetElementText(pXmlKeys->m_strValueFormulaKey, oXMLDoc, oElement, m_strValueFormula);
    xml_SetElementText(pXmlKeys->m_strRefParamKey, oXMLDoc, oElement, m_strRefParam);

	return 0;
}

long CRioIndex::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strValueFormula);
        BinarySerializeCalLen(oBinaryBuffer, m_strRefParam);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strValueFormula);
        BinarySerializeRead(oBinaryBuffer, m_strRefParam);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strValueFormula);
        BinarySerializeWrite(oBinaryBuffer, m_strRefParam);
	}
	return 0;
}

void CRioIndex::InitAfterRead()
{

}

BOOL CRioIndex::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

    CRioIndex *p = (CRioIndex*)pObj;

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strValueFormula != p->m_strValueFormula)
	{
		return FALSE;
	}

    if(m_strRefParam != p->m_strRefParam)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRioIndex::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

    CRioIndex *p = (CRioIndex*)pDest;

	p->m_strValue = m_strValue;
	p->m_strValueFormula = m_strValueFormula;
    p->m_strRefParam = m_strRefParam;

	return TRUE;
}

CBaseObject* CRioIndex::Clone()
{
    CRioIndex *p = new CRioIndex();
	Copy(p);
	return p;
}

BOOL CRioIndex::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_VALUEREFLIST
	)
	{
		return TRUE;
	}
	
	return FALSE;
}

CExBaseObject* CRioIndex::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

     if (strClassID == pXmlKeys->m_strValueRefListKey)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

CExBaseObject* CRioIndex::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_VALUEREFLIST)
	{
		pNew = new CXrioValueRefList();
	}

	return pNew;
}

void CRioIndex::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{

}


