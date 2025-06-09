//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_DI.cpp  CSetsFileXml_DI


#include "stdafx.h"
#include "SetsFileXml_DI.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_DI::CSetsFileXml_DI()
{
	//初始化属性

	//初始化成员变量
}

CSetsFileXml_DI::~CSetsFileXml_DI()
{
}

long CSetsFileXml_DI::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strDesc);
	xml_GetCDATA(oNode, m_strText);
	return 0;
}

long CSetsFileXml_DI::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strDesc);
	//xml_SetCDATA(oXMLDoc,oElement, m_strText);
	xml_SetElementOwnText(NULL, oXMLDoc, oElement, m_strText);
	return 0;
}

long CSetsFileXml_DI::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDesc);
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDesc);
		BinarySerializeRead(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDesc);
		BinarySerializeWrite(oBinaryBuffer, m_strText);
	}
	return 0;
}

void CSetsFileXml_DI::InitAfterRead()
{
}

BOOL CSetsFileXml_DI::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_DI *p = (CSetsFileXml_DI*)pObj;

	if(m_strDesc != p->m_strDesc)
	{
		return FALSE;
	}

	if(m_strText != p->m_strText)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_DI::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_DI *p = (CSetsFileXml_DI*)pDest;

	p->m_strDesc = m_strDesc;
	p->m_strText = m_strText;
	return TRUE;
}

CBaseObject* CSetsFileXml_DI::Clone()
{
	CSetsFileXml_DI *p = new CSetsFileXml_DI();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_DI::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_DI *p = new CSetsFileXml_DI();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

