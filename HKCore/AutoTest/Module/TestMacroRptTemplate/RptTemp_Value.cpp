//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Value.cpp  CRptTemp_Value


#include "stdafx.h"
#include "RptTemp_Value.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Value::CRptTemp_Value()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_Value::~CRptTemp_Value()
{
}

long CRptTemp_Value::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValKey, oNode, m_strVal);
	return 0;
}

long CRptTemp_Value::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValKey, oElement, m_strVal);
	return 0;
}

long CRptTemp_Value::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CRptTemp_Value::InitAfterRead()
{
}

BOOL CRptTemp_Value::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_Value *p = (CRptTemp_Value*)pObj;

	if(m_strVal != p->m_strVal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_Value::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_Value *p = (CRptTemp_Value*)pDest;

	p->m_strVal = m_strVal;
	return TRUE;
}

CBaseObject* CRptTemp_Value::Clone()
{
	CRptTemp_Value *p = new CRptTemp_Value();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Value::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Value *p = new CRptTemp_Value();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

