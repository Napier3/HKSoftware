//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpExpr.cpp  CPpExpr


#include "stdafx.h"
#include "PpExpr.h"

CPpExpr::CPpExpr()
{
	//初始化属性

	//初始化成员变量
}

CPpExpr::~CPpExpr()
{
}

long CPpExpr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetCDATA(oNode, m_strValue);

	return 0;
}

long CPpExpr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CExprMngrXmlRWKeys *pXmlKeys = (CExprMngrXmlRWKeys*)pXmlRWKeys;
	//xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetCDATA(oXMLDoc, oElement, m_strValue);


	return 0;
}

long CPpExpr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CPpExpr::InitAfterRead()
{
}

BOOL CPpExpr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpExpr *p = (CPpExpr*)pObj;

	return TRUE;
}

BOOL CPpExpr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpExpr *p = (CPpExpr*)pDest;
	p->m_strValue = m_strValue;

	return TRUE;
}

CBaseObject* CPpExpr::Clone()
{
	CPpExpr *p = new CPpExpr();
	Copy(p);
	return p;
}

