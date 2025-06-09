//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef_TextComb.cpp  CSttGdColDef_TextComb


#include "stdafx.h"
#include "SttGdColDef_TextComb.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef_TextComb::CSttGdColDef_TextComb()
{
	//初始化属性
	m_nWithUnit = 0;

	//初始化成员变量
}

CSttGdColDef_TextComb::~CSttGdColDef_TextComb()
{
}

long CSttGdColDef_TextComb::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPrev_TextKey, oNode, m_strPrevText);
	xml_GetAttibuteValue(pXmlKeys->m_strAfter_TextKey, oNode, m_strAfterText);
	xml_GetAttibuteValue(pXmlKeys->m_strWith_UnitKey, oNode, m_nWithUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strDecimalKey, oNode, m_strDecimal);
	return 0;
}

long CSttGdColDef_TextComb::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPrev_TextKey, oElement, m_strPrevText);
	xml_SetAttributeValue(pXmlKeys->m_strAfter_TextKey, oElement, m_strAfterText);
	xml_SetAttributeValue(pXmlKeys->m_strWith_UnitKey, oElement, m_nWithUnit);
	xml_SetAttributeValue(pXmlKeys->m_strDecimalKey, oElement, m_strDecimal);
	return 0;
}

long CSttGdColDef_TextComb::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPrevText);
		BinarySerializeCalLen(oBinaryBuffer, m_strAfterText);
		BinarySerializeCalLen(oBinaryBuffer, m_nWithUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_strDecimal);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPrevText);
		BinarySerializeRead(oBinaryBuffer, m_strAfterText);
		BinarySerializeRead(oBinaryBuffer, m_nWithUnit);
		BinarySerializeRead(oBinaryBuffer, m_strDecimal);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPrevText);
		BinarySerializeWrite(oBinaryBuffer, m_strAfterText);
		BinarySerializeWrite(oBinaryBuffer, m_nWithUnit);
		BinarySerializeWrite(oBinaryBuffer, m_strDecimal);
	}
	return 0;
}

void CSttGdColDef_TextComb::InitAfterRead()
{
}

BOOL CSttGdColDef_TextComb::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdColDef_TextComb *p = (CSttGdColDef_TextComb*)pObj;

	if(m_strPrevText != p->m_strPrevText)
	{
		return FALSE;
	}

	if(m_strAfterText != p->m_strAfterText)
	{
		return FALSE;
	}

	if(m_nWithUnit != p->m_nWithUnit)
	{
		return FALSE;
	}

	if(m_strDecimal != p->m_strDecimal)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdColDef_TextComb::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdColDef_TextComb *p = (CSttGdColDef_TextComb*)pDest;

	p->m_strPrevText = m_strPrevText;
	p->m_strAfterText = m_strAfterText;
	p->m_nWithUnit = m_nWithUnit;
	p->m_strDecimal = m_strDecimal;
	return TRUE;
}

CBaseObject* CSttGdColDef_TextComb::Clone()
{
	CSttGdColDef_TextComb *p = new CSttGdColDef_TextComb();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef_TextComb::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef_TextComb *p = new CSttGdColDef_TextComb();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

