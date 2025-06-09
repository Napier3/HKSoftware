//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdDataCal.cpp  CSttGdDataCal


#include "stdafx.h"
#include "SttGdDataCal.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdDataCal::CSttGdDataCal()
{
	//初始化属性

	//初始化成员变量
}

CSttGdDataCal::~CSttGdDataCal()
{
}

long CSttGdDataCal::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strExprKey, oNode, m_strExpr);
	xml_GetAttibuteValue(pXmlKeys->m_strData_IdKey, oNode, m_strDataID);
	return 0;
}

long CSttGdDataCal::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strExprKey, oElement, m_strExpr);
	xml_SetAttributeValue(pXmlKeys->m_strData_IdKey, oElement, m_strDataID);
	return 0;
}

long CSttGdDataCal::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strExpr);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strExpr);
		BinarySerializeRead(oBinaryBuffer, m_strDataID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strExpr);
		BinarySerializeWrite(oBinaryBuffer, m_strDataID);
	}
	return 0;
}

void CSttGdDataCal::InitAfterRead()
{
}

BOOL CSttGdDataCal::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdDataCal *p = (CSttGdDataCal*)pObj;

	if(m_strExpr != p->m_strExpr)
	{
		return FALSE;
	}

	if(m_strDataID != p->m_strDataID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdDataCal::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdDataCal *p = (CSttGdDataCal*)pDest;

	p->m_strExpr = m_strExpr;
	p->m_strDataID = m_strDataID;
	return TRUE;
}

CBaseObject* CSttGdDataCal::Clone()
{
	CSttGdDataCal *p = new CSttGdDataCal();
	Copy(p);
	return p;
}

CBaseObject* CSttGdDataCal::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdDataCal *p = new CSttGdDataCal();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

