


#include "stdafx.h"
#include "SetsFileXml_UI.h"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_UI::CSetsFileXml_UI()
{
	//初始化属性
	m_nGrp = 0;
	m_pNode = NULL;
	//初始化成员变量
}

CSetsFileXml_UI::~CSetsFileXml_UI()
{
}

long CSetsFileXml_UI::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);

	xml_GetAttibuteValue(pXmlKeys->m_strLdKey, oNode, m_strLd);
	xml_GetAttibuteValue(pXmlKeys->m_strClassKey, oNode, m_strClass);
	xml_GetAttibuteValue(pXmlKeys->m_strGrpKey, oNode, m_nGrp);
	xml_GetAttibuteValue(pXmlKeys->m_strMd5Key, oNode, m_strmd5);
	return 0;
}

long CSetsFileXml_UI::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strClassKey, oElement, m_strClass);
	xml_SetAttributeValue(pXmlKeys->m_strMd5Key, oElement, m_strmd5);

	//yuanting 2024-11-15
	xml_SetAttributeValue(pXmlKeys->m_strLdKey, oElement, m_strLd);

	if (m_nGrp > 0)
	{
		xml_SetAttributeValue(pXmlKeys->m_strGrpKey, oElement, m_nGrp);
	}

	return 0;
}

long CSetsFileXml_UI::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strClass);
		BinarySerializeCalLen(oBinaryBuffer, m_strmd5);

		BinarySerializeCalLen(oBinaryBuffer, m_strLd);
		BinarySerializeCalLen(oBinaryBuffer, m_nGrp);


	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strClass);
		BinarySerializeRead(oBinaryBuffer, m_strmd5);

		BinarySerializeRead(oBinaryBuffer, m_strLd);
		BinarySerializeRead(oBinaryBuffer, m_nGrp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strClass);
		BinarySerializeWrite(oBinaryBuffer, m_strmd5);

		BinarySerializeWrite(oBinaryBuffer, m_strLd);
		BinarySerializeWrite(oBinaryBuffer, m_nGrp);
	}
	return 0;
}

void CSetsFileXml_UI::InitAfterRead()
{
}

BOOL CSetsFileXml_UI::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_UI *p = (CSetsFileXml_UI*)pObj;

	if(m_strClass != p->m_strClass)
	{
		return FALSE;
	}

	if(m_strmd5 != p->m_strmd5)
	{
		return FALSE;
	}

	if(m_strLd != p->m_strLd)
	{
		return FALSE;
	}

	if(m_nGrp != p->m_nGrp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_UI::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_UI *p = (CSetsFileXml_UI*)pDest;

	p->m_strClass = m_strClass;
	p->m_strmd5 = m_strmd5;

	p->m_nGrp = m_nGrp;
	p->m_strLd = m_strLd;

	return TRUE;
}

CBaseObject* CSetsFileXml_UI::Clone()
{
	CSetsFileXml_UI *p = new CSetsFileXml_UI();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_UI::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_UI *p = new CSetsFileXml_UI();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

void CSetsFileXml_UI::SetGrp(long nGrp)
{
	m_nGrp = nGrp;

	if (m_pNode != NULL && nGrp > 0)
	{
		pugi::xml_attribute attr = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strGrpKey);
		attr.set_value(nGrp);
	}
}

void CSetsFileXml_UI::SetClass(const CString &strClass)
{
	m_strClass = strClass;

	if (m_pNode != NULL)
	{
		pugi::xml_attribute attr = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strClassKey);
		char* psz = NULL;
		CString_to_char(strClass, &psz);
		wchar_t *pW = NULL;
		Char_to_WChart(psz, &pW);
		attr.set_value(pW);
		delete []psz;
		delete []pW;
	}
}

void CSetsFileXml_UI::SetMd5(const CString &strMd5)
{
	m_strmd5 = strMd5;

	if (m_pNode != NULL)
	{
		pugi::xml_attribute attr = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strMd5Key);
		char* psz = NULL;
		CString_to_char(strMd5, &psz);
		wchar_t *pW = NULL;
		Char_to_WChart(psz, &pW);
		attr.set_value(pW);
		delete []psz;
		delete []pW;
	}
}

void CSetsFileXml_UI::SetLd(const CString &strLd)
{
	m_strLd = strLd;

	if (m_pNode != NULL)
	{
		pugi::xml_attribute attr = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strLdKey);
		char* psz = NULL;
		CString_to_char(strLd, &psz);
		wchar_t *pW = NULL;
		Char_to_WChart(psz, &pW);
		attr.set_value(pW);
		delete []psz;
		delete []pW;
	}
}