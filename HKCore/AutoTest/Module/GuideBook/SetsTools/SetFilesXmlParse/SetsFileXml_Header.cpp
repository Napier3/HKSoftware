//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_Header.cpp  CSetsFileXml_Header


#include "stdafx.h"
#include "SetsFileXml_Header.h"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_Header::CSetsFileXml_Header()
{
	//初始化属性
	m_pNode = NULL;
	m_strHeaderMD5_Cal= "";
	//初始化成员变量
}

CSetsFileXml_Header::~CSetsFileXml_Header()
{
}

long CSetsFileXml_Header::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);

	xml_GetAttibuteValue(pXmlKeys->m_strDevTypeKey, oNode, m_strDevType);
	xml_GetAttibuteValue(pXmlKeys->m_strDevIdKey, oNode, m_strDevID);
	xml_GetAttibuteValue(pXmlKeys->m_strIedNameKey, oNode, m_strIedName);
	xml_GetAttibuteValue(pXmlKeys->m_strUpdateTimeKey, oNode, m_strUpdateTime);
	xml_GetAttibuteValue(pXmlKeys->m_strMd5Key, oNode, m_strmd5);
	return 0;
}

long CSetsFileXml_Header::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDevTypeKey, oElement, m_strDevType);
	xml_SetAttributeValue(pXmlKeys->m_strDevIdKey, oElement, m_strDevID);
	xml_SetAttributeValue(pXmlKeys->m_strIedNameKey, oElement, m_strIedName);
	xml_SetAttributeValue(pXmlKeys->m_strUpdateTimeKey, oElement, m_strUpdateTime);
	xml_SetAttributeValue(pXmlKeys->m_strMd5Key, oElement, m_strmd5);
	return 0;
}

long CSetsFileXml_Header::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDevType);
		BinarySerializeCalLen(oBinaryBuffer, m_strDevID);
		BinarySerializeCalLen(oBinaryBuffer, m_strIedName);
		BinarySerializeCalLen(oBinaryBuffer, m_strUpdateTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strmd5);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDevType);
		BinarySerializeRead(oBinaryBuffer, m_strDevID);
		BinarySerializeRead(oBinaryBuffer, m_strIedName);
		BinarySerializeRead(oBinaryBuffer, m_strUpdateTime);
		BinarySerializeRead(oBinaryBuffer, m_strmd5);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDevType);
		BinarySerializeWrite(oBinaryBuffer, m_strDevID);
		BinarySerializeWrite(oBinaryBuffer, m_strIedName);
		BinarySerializeWrite(oBinaryBuffer, m_strUpdateTime);
		BinarySerializeWrite(oBinaryBuffer, m_strmd5);
	}
	return 0;
}

void CSetsFileXml_Header::InitAfterRead()
{
}

BOOL CSetsFileXml_Header::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_Header *p = (CSetsFileXml_Header*)pObj;

	if(m_strDevType != p->m_strDevType)
	{
		return FALSE;
	}

	if(m_strDevID != p->m_strDevID)
	{
		return FALSE;
	}

	if(m_strIedName != p->m_strIedName)
	{
		return FALSE;
	}

	if(m_strUpdateTime != p->m_strUpdateTime)
	{
		return FALSE;
	}

	if(m_strmd5 != p->m_strmd5)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_Header::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_Header *p = (CSetsFileXml_Header*)pDest;

	p->m_strDevType = m_strDevType;
	p->m_strDevID = m_strDevID;
	p->m_strIedName = m_strIedName;
	p->m_strUpdateTime = m_strUpdateTime;
	p->m_strmd5 = m_strmd5;
	return TRUE;
}

CBaseObject* CSetsFileXml_Header::Clone()
{
	CSetsFileXml_Header *p = new CSetsFileXml_Header();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_Header::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_Header *p = new CSetsFileXml_Header();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

void CSetsFileXml_Header::SetMd5(const CString &strMd5)
{
	m_strmd5 = strMd5;

	if (m_pNode != NULL)
	{
		pugi::xml_attribute attrTime = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strMd5Key);
		char* pszTime = NULL;
		CString_to_char(strMd5, &pszTime);
		wchar_t *pWTime = NULL;
		Char_to_WChart(pszTime, &pWTime);
		attrTime.set_value(pWTime);
		delete []pszTime;
		delete []pWTime;
	}
}

void CSetsFileXml_Header::SetUpdateTime(const CString &strTime)
{
	m_strUpdateTime = strTime;

	if (m_pNode != NULL)
	{
		pugi::xml_attribute attrTime = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strUpdateTimeKey);
		char* pszTime = NULL;
		CString_to_char(strTime, &pszTime);
		wchar_t *pWTime = NULL;
		Char_to_WChart(pszTime, &pWTime);
		attrTime.set_value(pWTime);
		delete []pszTime;
		delete []pWTime;
	}
}