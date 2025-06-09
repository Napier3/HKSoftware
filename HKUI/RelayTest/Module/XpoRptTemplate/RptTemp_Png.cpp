//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Png.cpp  CRptTemp_Png


#include "stdafx.h"
#include "RptTemp_Png.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Png::CRptTemp_Png()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_Png::~CRptTemp_Png()
{
}

long CRptTemp_Png::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPngPathKey, oNode, m_strPngPath);
	return 0;
}

long CRptTemp_Png::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPngPathKey, oElement, m_strPngPath);
	return 0;
}

long CRptTemp_Png::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPngPath);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPngPath);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPngPath);
	}
	return 0;
}

void CRptTemp_Png::InitAfterRead()
{
}

BOOL CRptTemp_Png::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Png *p = (CRptTemp_Png*)pObj;

	if(m_strPngPath != p->m_strPngPath)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_Png::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Png *p = (CRptTemp_Png*)pDest;

	p->m_strPngPath = m_strPngPath;
	return TRUE;
}

CBaseObject* CRptTemp_Png::Clone()
{
	CRptTemp_Png *p = new CRptTemp_Png();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Png::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Png *p = new CRptTemp_Png();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}
