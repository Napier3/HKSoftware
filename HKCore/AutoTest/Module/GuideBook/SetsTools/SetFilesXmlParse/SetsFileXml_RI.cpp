//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_RI.cpp  CSetsFileXml_RI


#include "stdafx.h"
#include "SetsFileXml_RI.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_RI::CSetsFileXml_RI()
{
	//初始化属性

	//初始化成员变量
}

CSetsFileXml_RI::~CSetsFileXml_RI()
{
}

long CSetsFileXml_RI::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_GetCDATA(oNode, m_strVal);
	return 0;
}

long CSetsFileXml_RI::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	if (m_strVal.GetLength() > 0)
	{
		//xml_SetCDATA(oXMLDoc,oElement, m_strVal);
		xml_SetElementOwnText(NULL, oXMLDoc, oElement, m_strVal);
	}

	return 0;
}

long CSetsFileXml_RI::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strVal);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strVal);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strVal);
	}
	return 0;
}

void CSetsFileXml_RI::InitAfterRead()
{
}

BOOL CSetsFileXml_RI::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_RI *p = (CSetsFileXml_RI*)pObj;

	if(m_strVal != p->m_strVal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_RI::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_RI *p = (CSetsFileXml_RI*)pDest;

	p->m_strVal = m_strVal;
	return TRUE;
}

CBaseObject* CSetsFileXml_RI::Clone()
{
	CSetsFileXml_RI *p = new CSetsFileXml_RI();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_RI::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_RI *p = new CSetsFileXml_RI();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

