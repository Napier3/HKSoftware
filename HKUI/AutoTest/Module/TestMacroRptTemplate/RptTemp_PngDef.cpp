//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_PngDef.cpp  CRptTemp_PngDef


#include "stdafx.h"
#include "RptTemp_PngDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_PngDef::CRptTemp_PngDef()
{
	//初始化属性
	m_nPngChar = 0;
	m_bHasExport = FALSE;
	//初始化成员变量
}

CRptTemp_PngDef::~CRptTemp_PngDef()
{
}

long CRptTemp_PngDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strPngPathKey, oNode, m_strPngPath);
	xml_GetAttibuteValue(pXmlKeys->m_strPngCharKey, oNode, m_nPngChar);
	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	return 0;
}

long CRptTemp_PngDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strPngPathKey, oElement, m_strPngPath);
	xml_SetAttributeValue(pXmlKeys->m_strPngCharKey, oElement, m_nPngChar);
	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	return 0;
}

long CRptTemp_PngDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strPngPath);
		BinarySerializeCalLen(oBinaryBuffer, m_nPngChar);
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strPngPath);
		BinarySerializeRead(oBinaryBuffer, m_nPngChar);
		BinarySerializeRead(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strPngPath);
		BinarySerializeWrite(oBinaryBuffer, m_nPngChar);
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
	}
	return 0;
}

void CRptTemp_PngDef::InitAfterRead()
{
}

BOOL CRptTemp_PngDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_PngDef *p = (CRptTemp_PngDef*)pObj;

	if(m_strPngPath != p->m_strPngPath)
	{
		return FALSE;
	}

	if(m_nPngChar != p->m_nPngChar)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strMode != p->m_strMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_PngDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_PngDef *p = (CRptTemp_PngDef*)pDest;

	p->m_strPngPath = m_strPngPath;
	p->m_nPngChar = m_nPngChar;
	p->m_strName = m_strName;
	p->m_strMode = m_strMode;	
	return TRUE;
}

CBaseObject* CRptTemp_PngDef::Clone()
{
	CRptTemp_PngDef *p = new CRptTemp_PngDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_PngDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_PngDef *p = new CRptTemp_PngDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}