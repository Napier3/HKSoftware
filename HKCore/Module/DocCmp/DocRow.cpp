//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocRow.cpp  CDocRow


#include "stdafx.h"
#include "DocRow.h"

CDocRow::CDocRow()
{
	//初始化属性
	m_fWidth = 0;
	m_fHeigh = 0;

	//初始化成员变量
}

CDocRow::~CDocRow()
{
}

long CDocRow::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_fWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strHeightKey, oNode, m_fHeigh);
	return 0;
}

long CDocRow::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_fWidth);
	xml_SetAttributeValue(pXmlKeys->m_strHeightKey, oElement, m_fHeigh);
	return 0;
}

void CDocRow::InitAfterRead()
{
}

BOOL CDocRow::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDocRow *p = (CDocRow*)pObj;

	if(m_fWidth != p->m_fWidth)
	{
		return FALSE;
	}

	if(m_fHeigh != p->m_fHeigh)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDocRow::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDocRow *p = (CDocRow*)pDest;

	p->m_fWidth = m_fWidth;
	p->m_fHeigh = m_fHeigh;
	return TRUE;
}

CBaseObject* CDocRow::Clone()
{
	CDocRow *p = new CDocRow();
	Copy(p);
	return p;
}

CExBaseObject* CDocRow::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDocCelKey)
	{
		pNew = new CDocCel();
	}

	return pNew;
}

CExBaseObject* CDocRow::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DOCMPCLASSID_CDOCCEL)
	{
		pNew = new CDocCel();
	}

	return pNew;
}


void CDocRow::SetCmpError()
{
	POS pos = GetHeadPosition();
	CDocCel *p = NULL;

	while (pos != NULL)
	{
		p = (CDocCel *)GetNext(pos);
		p->SetCmpError();
	}
}

void CDocRow::Cmp(CDocRow *pRef)
{
	if (pRef == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CDocCel *p = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = (CDocCel *)GetNext(pos);
		p->Cmp((CDocCel*)pRef->GetAtIndex(nIndex));
		nIndex++;
	}
}

