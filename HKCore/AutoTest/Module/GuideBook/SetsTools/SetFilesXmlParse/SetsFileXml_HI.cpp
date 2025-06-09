//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_HI.cpp  CSetsFileXml_HI


#include "stdafx.h"
#include "SetsFileXml_HI.h"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_HI::CSetsFileXml_HI()
{
	//初始化属性

	//初始化成员变量
	m_pNode = NULL;
}

CSetsFileXml_HI::~CSetsFileXml_HI()
{
}

long CSetsFileXml_HI::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);


	xml_GetAttibuteValue(pXmlKeys->m_strClassKey, oNode, m_strClass);
	xml_GetAttibuteValue(pXmlKeys->m_strMd5Key, oNode, m_strmd5);
	return 0;
}

long CSetsFileXml_HI::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strClassKey, oElement, m_strClass);
	xml_SetAttributeValue(pXmlKeys->m_strMd5Key, oElement, m_strmd5);
	return 0;
}

long CSetsFileXml_HI::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strClass);
		BinarySerializeCalLen(oBinaryBuffer, m_strmd5);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strClass);
		BinarySerializeRead(oBinaryBuffer, m_strmd5);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strClass);
		BinarySerializeWrite(oBinaryBuffer, m_strmd5);
	}
	return 0;
}

void CSetsFileXml_HI::InitAfterRead()
{
}

BOOL CSetsFileXml_HI::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_HI *p = (CSetsFileXml_HI*)pObj;

	if(m_strClass != p->m_strClass)
	{
		return FALSE;
	}

	if(m_strmd5 != p->m_strmd5)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_HI::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_HI *p = (CSetsFileXml_HI*)pDest;

	p->m_strClass = m_strClass;
	p->m_strmd5 = m_strmd5;
	return TRUE;
}

CBaseObject* CSetsFileXml_HI::Clone()
{
	CSetsFileXml_HI *p = new CSetsFileXml_HI();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_HI::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_HI *p = new CSetsFileXml_HI();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

