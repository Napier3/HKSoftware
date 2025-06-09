//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharDef.cpp  CGbCharDef


#include "stdafx.h"
#include "GbCharDef.h"

CGbCharDef::CGbCharDef()
{
	//初始化属性

	//初始化成员变量
}

CGbCharDef::~CGbCharDef()
{
}

long CGbCharDef::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	return 0;
}

long CGbCharDef::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	return 0;
}

long CGbCharDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CGbCharDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbCharDef *p = (CGbCharDef*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbCharDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbCharDef *p = (CGbCharDef*)pDest;

	p->m_strID = m_strID;
	return TRUE;
}

CBaseObject* CGbCharDef::Clone()
{
	CGbCharDef *p = new CGbCharDef();
	Copy(p);
	return p;
}

CExBaseObject* CGbCharDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbCharDefMngrXmlRWKeys *pXmlKeys = (CGbCharDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGbCharCurveKey)
	{
		pNew = new CGbCharCurve();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharMhoKey)
	{
		pNew = new CGbCharMho();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharLenTomatoKey)
	{
		pNew = new CGbCharLenTomato();
	}
	else if (strClassID == pXmlKeys->m_strCGbCharFuncKey)
	{
		pNew = new CGbCharFunc();
	}

	return pNew;
}

CExBaseObject* CGbCharDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHRCLASSID_CGBCHARCURVE)
	{
		pNew = new CGbCharCurve();
	}
	else if (nClassID == CHRCLASSID_CGBCHARMHO)
	{
		pNew = new CGbCharMho();
	}
	else if (nClassID == CHRCLASSID_CGBCHARLENTOMATO)
	{
		pNew = new CGbCharLenTomato();
	}
	else if (nClassID == CHRCLASSID_CGBCHARFUNC)
	{
		pNew = new CGbCharFunc();
	}

	return pNew;
}
