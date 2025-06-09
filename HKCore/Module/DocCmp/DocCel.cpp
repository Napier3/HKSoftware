//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocCel.cpp  CDocCel


#include "stdafx.h"
#include "DocCel.h"

CDocCel::CDocCel()
{
	//初始化属性
	m_nRow = 0;
	m_nCol = 0;
	m_fWidth = 0;
	m_fHeight = 0;

	//初始化成员变量
}

CDocCel::~CDocCel()
{
}

long CDocCel::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDocText::XmlReadOwn(oNode, pXmlRWKeys);
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRowKey, oNode, m_nRow);
	xml_GetAttibuteValue(pXmlKeys->m_strColKey, oNode, m_nCol);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_fWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strHeightKey, oNode, m_fHeight);
	return 0;
}

long CDocCel::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDocText::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRowKey, oElement, m_nRow);
	xml_SetAttributeValue(pXmlKeys->m_strColKey, oElement, m_nCol);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_fWidth);
	xml_SetAttributeValue(pXmlKeys->m_strHeightKey, oElement, m_fHeight);
	return 0;
}

void CDocCel::InitAfterRead()
{
	CDocText::InitAfterRead();
}

BOOL CDocCel::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDocText::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDocCel *p = (CDocCel*)pObj;

	if(m_nRow != p->m_nRow)
	{
		return FALSE;
	}

	if(m_nCol != p->m_nCol)
	{
		return FALSE;
	}

	if(m_fWidth != p->m_fWidth)
	{
		return FALSE;
	}

	if(m_fHeight != p->m_fHeight)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDocCel::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDocText::CopyOwn(pDest);

	CDocCel *p = (CDocCel*)pDest;

	p->m_nRow = m_nRow;
	p->m_nCol = m_nCol;
	p->m_fWidth = m_fWidth;
	p->m_fHeight = m_fHeight;
	return TRUE;
}

CBaseObject* CDocCel::Clone()
{
	CDocCel *p = new CDocCel();
	Copy(p);
	return p;
}
