//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef.cpp  CSttGdColDef


#include "stdafx.h"
#include "SttGdColDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdColDef::CSttGdColDef()
{
	//初始化属性
	m_nEditable = 0;
	m_nWidth = 50;

	//初始化成员变量
}

CSttGdColDef::~CSttGdColDef()
{
}

long CSttGdColDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strData_TypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);
	xml_GetAttibuteValue(pXmlKeys->m_strDecimalKey, oNode, m_strDecimal);
	xml_GetAttibuteValue(pXmlKeys->m_strMaxKey, oNode, m_strMax);
	xml_GetAttibuteValue(pXmlKeys->m_strMinKey, oNode, m_strMin);
	xml_GetAttibuteValue(pXmlKeys->m_strEditableKey, oNode, m_nEditable);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	return 0;
}

long CSttGdColDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strData_TypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	xml_SetAttributeValue(pXmlKeys->m_strDecimalKey, oElement, m_strDecimal);
	xml_SetAttributeValue(pXmlKeys->m_strMaxKey, oElement, m_strMax);
	xml_SetAttributeValue(pXmlKeys->m_strMinKey, oElement, m_strMin);
	xml_SetAttributeValue(pXmlKeys->m_strEditableKey, oElement, m_nEditable);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	return 0;
}

long CSttGdColDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strUnit);
		BinarySerializeCalLen(oBinaryBuffer, m_strDecimal);
		BinarySerializeCalLen(oBinaryBuffer, m_strMax);
		BinarySerializeCalLen(oBinaryBuffer, m_strMin);
		BinarySerializeCalLen(oBinaryBuffer, m_nEditable);
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strUnit);
		BinarySerializeRead(oBinaryBuffer, m_strDecimal);
		BinarySerializeRead(oBinaryBuffer, m_strMax);
		BinarySerializeRead(oBinaryBuffer, m_strMin);
		BinarySerializeRead(oBinaryBuffer, m_nEditable);
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strUnit);
		BinarySerializeWrite(oBinaryBuffer, m_strDecimal);
		BinarySerializeWrite(oBinaryBuffer, m_strMax);
		BinarySerializeWrite(oBinaryBuffer, m_strMin);
		BinarySerializeWrite(oBinaryBuffer, m_nEditable);
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
	}
	return 0;
}

void CSttGdColDef::InitAfterRead()
{
}

BOOL CSttGdColDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdColDef *p = (CSttGdColDef*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strUnit != p->m_strUnit)
	{
		return FALSE;
	}

	if(m_strDecimal != p->m_strDecimal)
	{
		return FALSE;
	}

	if(m_strMax != p->m_strMax)
	{
		return FALSE;
	}

	if(m_strMin != p->m_strMin)
	{
		return FALSE;
	}

	if(m_nEditable != p->m_nEditable)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdColDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdColDef *p = (CSttGdColDef*)pDest;

	p->m_strDataType = m_strDataType;
	p->m_strUnit = m_strUnit;
	p->m_strDecimal = m_strDecimal;
	p->m_strMax = m_strMax;
	p->m_strMin = m_strMin;
	p->m_nEditable = m_nEditable;
	p->m_nWidth = m_nWidth;
	return TRUE;
}

CBaseObject* CSttGdColDef::Clone()
{
	CSttGdColDef *p = new CSttGdColDef();
	Copy(p);
	return p;
}

CBaseObject* CSttGdColDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdColDef *p = new CSttGdColDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdColDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_PARA)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_SCRIPT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdColDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdColDef_ParaKey)
	{
		pNew = new CSttGdColDef_Para();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdColDef_ScriptKey)
	{
		pNew = new CSttGdColDef_Script();
	}

	return pNew;
}

CExBaseObject* CSttGdColDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_PARA)
	{
		pNew = new CSttGdColDef_Para();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDCOLDEF_SCRIPT)
	{
		pNew = new CSttGdColDef_Script();
	}

	return pNew;
}
