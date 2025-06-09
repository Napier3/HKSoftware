//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
	//��ʼ������

	//��ʼ����Ա����
}

CRptTemp_PngDef::~CRptTemp_PngDef()
{
}

long CRptTemp_PngDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPngPathKey, oNode, m_strPngPath);
	return 0;
}

long CRptTemp_PngDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPngPathKey, oElement, m_strPngPath);
	return 0;
}

long CRptTemp_PngDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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