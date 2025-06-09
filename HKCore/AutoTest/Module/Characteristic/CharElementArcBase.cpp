//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArcBase.cpp  CCharElementArcBase


#include "stdafx.h"
#include "CharElementArcBase.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementArcBase::CCharElementArcBase()
{

}

CCharElementArcBase::~CCharElementArcBase()
{
}

long CCharElementArcBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strRadiusKey, oNode, m_strRadius);
	xml_GetAttibuteValue(pXmlKeys->m_strStartAngleKey, oNode, m_strAngleBegin);
	xml_GetAttibuteValue(pXmlKeys->m_strEndAngleKey, oNode, m_strAngleEnd);
	xml_GetAttibuteValue(pXmlKeys->m_strClockwiseKey, oNode, m_strClockwise);

	return 0;
}

long CCharElementArcBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strRadiusKey, oElement, m_strRadius);
	xml_SetAttributeValue(pXmlKeys->m_strStartAngleKey, oElement, m_strAngleBegin);
	xml_SetAttributeValue(pXmlKeys->m_strEndAngleKey, oElement, m_strAngleEnd);
	xml_SetAttributeValue(pXmlKeys->m_strClockwiseKey, oElement, m_strClockwise);

	return 0;
}

void CCharElementArcBase::InitAfterRead()
{
}

BOOL CCharElementArcBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementArcBase *p = (CCharElementArcBase*)pObj;

	if(m_strRadius != p->m_strRadius)
	{
		return FALSE;
	}

	if(m_strAngleBegin != p->m_strAngleBegin)
	{
		return FALSE;
	}

	if(m_strAngleEnd != p->m_strAngleEnd)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CCharElementArcBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElement::CopyOwn(pDest);

	CCharElementArcBase *p = (CCharElementArcBase*)pDest;

	p->m_strClockwise = m_strClockwise;
	p->m_strRadius = m_strRadius;
	p->m_strAngleBegin = m_strAngleBegin;
	p->m_strAngleEnd = m_strAngleEnd;

	return TRUE;
}

long CCharElementArcBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElement::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strRadius);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngleBegin);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngleEnd);
		BinarySerializeCalLen(oBinaryBuffer, m_strClockwise);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strRadius);
		BinarySerializeRead(oBinaryBuffer, m_strAngleBegin);
		BinarySerializeRead(oBinaryBuffer, m_strAngleEnd);
		BinarySerializeRead(oBinaryBuffer, m_strClockwise);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strRadius);
		BinarySerializeWrite(oBinaryBuffer, m_strAngleBegin);
		BinarySerializeWrite(oBinaryBuffer, m_strAngleEnd);
		BinarySerializeWrite(oBinaryBuffer, m_strClockwise);
	}

	return 0;
}

CXDrawBase* CCharElementArcBase::CreateDrawElement()
{	
	CXDrawArc *pNew = new CXDrawArc();
	CXDrawData_Arc::DataCopy(pNew);
	m_pDataRef = pNew;	

	return (CXDrawBase*)m_pDataRef;
}


void CCharElementArcBase::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	CalCharElementExpression(m_strRadius, m_fXRadius, TRUE);
	CalCharElementExpression(m_strAngleBegin, m_fAngleBegin, TRUE);
	CalCharElementExpression(m_strAngleEnd, m_fAngleEnd, TRUE);
	CalCharElementExpression(m_strErrLength, m_dErrLength, TRUE);
	m_nClockwise = char_Cllockwise_To_UINT(m_strClockwise);

	m_fYRadius = m_fXRadius;
}

void CCharElementArcBase::CalTestLines(UINT nTestLineMode)
{
	
	CalTestLines_Plumb_Arc((CXDrawArc*)m_pDataRef);
}


CXDrawDataBase* CCharElementArcBase::GetCXDrawDataBase()
{
	return this;
}
