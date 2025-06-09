//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_RowDef.cpp  CRptTemp_RowDef


#include "stdafx.h"
#include "RptTemp_RowDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_RowDef::CRptTemp_RowDef()
{
	//初始化属性

	m_nRowHeight = 0;
	//初始化成员变量
}

CRptTemp_RowDef::~CRptTemp_RowDef()
{
}

long CRptTemp_RowDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strRowHeightKey, oNode, m_nRowHeight);
	return 0;
}

long CRptTemp_RowDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strRowHeightKey, oElement, m_nRowHeight);
	return 0;
}

long CRptTemp_RowDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nRowHeight);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nRowHeight);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nRowHeight);
	}
	return 0;
}

void CRptTemp_RowDef::InitAfterRead()
{
}

BOOL CRptTemp_RowDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_RowDef *p = (CRptTemp_RowDef*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_nRowHeight != p->m_nRowHeight)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_RowDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_RowDef *p = (CRptTemp_RowDef*)pDest;

	p->m_strType = m_strType;
	p->m_strID = m_strID;
	p->m_nRowHeight = m_nRowHeight;
	return TRUE;
}

CBaseObject* CRptTemp_RowDef::Clone()
{
	CRptTemp_RowDef *p = new CRptTemp_RowDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_RowDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_RowDef *p = new CRptTemp_RowDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

