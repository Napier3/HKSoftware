//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_FI.cpp  CSetsFileXml_FI


#include "stdafx.h"
#include "SetsFileXml_FI.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_FI::CSetsFileXml_FI()
{
	//初始化属性

	//初始化成员变量
}

CSetsFileXml_FI::~CSetsFileXml_FI()
{
}

long CSetsFileXml_FI::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strDesc);
	xml_GetCDATA(oNode, m_strText);
	return 0;
}

long CSetsFileXml_FI::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strDesc);
	//xml_SetCDATA(oXMLDoc,oElement, m_strText);
	xml_SetElementOwnText(NULL, oXMLDoc, oElement, m_strText);

	return 0;
}

long CSetsFileXml_FI::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
		BinarySerializeCalLen(oBinaryBuffer, m_strDesc);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strText);
		BinarySerializeRead(oBinaryBuffer, m_strDesc);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strText);
		BinarySerializeWrite(oBinaryBuffer, m_strDesc);
	}
	return 0;
}

void CSetsFileXml_FI::InitAfterRead()
{
}

BOOL CSetsFileXml_FI::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_FI *p = (CSetsFileXml_FI*)pObj;

	if(m_strText != p->m_strText)
	{
		return FALSE;
	}

	if(m_strDesc != p->m_strDesc)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_FI::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_FI *p = (CSetsFileXml_FI*)pDest;

	p->m_strText = m_strText;
	p->m_strDesc = m_strDesc;
	return TRUE;
}

CBaseObject* CSetsFileXml_FI::Clone()
{
	CSetsFileXml_FI *p = new CSetsFileXml_FI();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_FI::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_FI *p = new CSetsFileXml_FI();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

