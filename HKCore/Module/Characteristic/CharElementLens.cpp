//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLens.cpp  CCharElementLens


#include "stdafx.h"
#include "CharElementLens.h"

CCharElementLens::CCharElementLens()
{
	//初始化属性
	m_strName = "lens";
	m_strID = m_strName;
	//初始化成员变量
}

CCharElementLens::~CCharElementLens()
{
}

long CCharElementLens::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strForwardReachKey, oNode, m_strForwardReach);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strOffsetKey, oNode, m_strOffset);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_strWidth);
	return 0;
}

long CCharElementLens::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strForwardReachKey, oElement, m_strForwardReach);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strOffsetKey, oElement, m_strOffset);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_strWidth);
	return 0;
}

void CCharElementLens::InitAfterRead()
{
}

BOOL CCharElementLens::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLens *p = (CCharElementLens*)pObj;

	if(m_strForwardReach != p->m_strForwardReach)
	{
		return FALSE;
	}

	if(m_strAngle != p->m_strAngle)
	{
		return FALSE;
	}

	if(m_strOffset != p->m_strOffset)
	{
		return FALSE;
	}

	if(m_strWidth != p->m_strWidth)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementLens::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementLens *p = (CCharElementLens*)pDest;

	p->m_strForwardReach = m_strForwardReach;
	p->m_strAngle = m_strAngle;
	p->m_strOffset = m_strOffset;
	p->m_strWidth = m_strWidth;
	return TRUE;
}

CBaseObject* CCharElementLens::Clone()
{
	CCharElementLens *p = new CCharElementLens();
	Copy(p);
	return p;
}

CString CCharElementLens::ReturnXml()
{
	CString str;
	str.Format(_T("Lens angle=\"%s\" width=\"%s\" forward-reach=\"%s\" offset=\"%s\""),m_strAngle,m_strWidth,m_strForwardReach,m_strOffset);
	return str;
}