//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharsDef.cpp  CGbCharsDef


#include "stdafx.h"
#include "GbCharsDef.h"

CGbCharsDef::CGbCharsDef()
{
	//初始化属性

	//初始化成员变量
}

CGbCharsDef::~CGbCharsDef()
{
}

long CGbCharsDef::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	return 0;
}

long CGbCharsDef::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	return 0;
}

long CGbCharsDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
	}
	return 0;
}

BOOL CGbCharsDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharsDef *p = (CGbCharsDef*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharsDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharsDef *p = (CGbCharsDef*)pDest;

	p->m_strID = m_strID;
	return TRUE;
}

CBaseObject* CGbCharsDef::Clone()
{
	CGbCharsDef *p = new CGbCharsDef();
	Copy(p);
	return p;
}

CExBaseObject* CGbCharsDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGbCharAxisesKey)
	{
		pNew = new CGbCharAxises();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharDefKey)
	{
		pNew = new CGbCharDef();
	}

	return pNew;
}

CExBaseObject* CGbCharsDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHRCLASSID_CGBCHARAXISES)
	{
		pNew = new CGbCharAxises();
	}
	else if (nClassID == CHRCLASSID_CGBCHARDEF)
	{
		pNew = new CGbCharDef();
	}

	return pNew;
}
