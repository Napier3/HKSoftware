//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLined.cpp  CCharElementLined


#include "stdafx.h"
#include "CharElementLined.h"

CCharElementLined::CCharElementLined()
{
	//初始化属性
	m_strName = "lined";
	m_strID = m_strName;
	//初始化成员变量
}

CCharElementLined::~CCharElementLined()
{
}

long CCharElementLined::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXbKey, oNode, m_strXb);
	xml_GetAttibuteValue(pXmlKeys->m_strYbKey, oNode, m_strYb);
	xml_GetAttibuteValue(pXmlKeys->m_strXeKey, oNode, m_strXe);
	xml_GetAttibuteValue(pXmlKeys->m_strYeKey, oNode, m_strYe);
	return 0;
}

long CCharElementLined::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXbKey, oElement, m_strXb);
	xml_SetAttributeValue(pXmlKeys->m_strYbKey, oElement, m_strYb);
	xml_SetAttributeValue(pXmlKeys->m_strXeKey, oElement, m_strXe);
	xml_SetAttributeValue(pXmlKeys->m_strYeKey, oElement, m_strYe);
	return 0;
}

BOOL CCharElementLined::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLined *p = (CCharElementLined*)pObj;

	if(m_strXb != p->m_strXb)
	{
		return FALSE;
	}

	if(m_strYb != p->m_strYb)
	{
		return FALSE;
	}

	if(m_strXe != p->m_strXe)
	{
		return FALSE;
	}

	if(m_strYe != p->m_strYe)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementLined::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementLined *p = (CCharElementLined*)pDest;

	p->m_strXb = m_strXb;
	p->m_strYb = m_strYb;
	p->m_strXe = m_strXe;
	p->m_strYe = m_strYe;
	return TRUE;
}

CBaseObject* CCharElementLined::Clone()
{
	CCharElementLined *p = new CCharElementLined();
	Copy(p);
	return p;
}

CExBaseObject* CCharElementLined::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CCharElementLined::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CString CCharElementLined::ReturnXml()
{
	CString str;
	str.Format(_T("lined x-b=\"%s\" y-b=\"%s\" x-e=\"%s\" y-e=\"%s\" "),m_strXb,m_strYb,m_strXe,m_strYe);
	return str;
}