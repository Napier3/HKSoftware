//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArcd.cpp  CCharElementArcd


#include "stdafx.h"
#include "CharElementArcd.h"

CCharElementArcd::CCharElementArcd()
{
	//初始化属性
	m_strName = "arcd";
	m_strID = m_strName;
	//初始化成员变量
}

CCharElementArcd::~CCharElementArcd()
{
}

long CCharElementArcd::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXcKey, oNode, m_strXc);
	xml_GetAttibuteValue(pXmlKeys->m_strYcKey, oNode, m_strYc);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleBKey, oNode, m_strAngleB);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleEKey, oNode, m_strAngleE);
	xml_GetAttibuteValue(pXmlKeys->m_strRadiusKey, oNode, m_strRadius);
	return 0;
}

long CCharElementArcd::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXcKey, oElement, m_strXc);
	xml_SetAttributeValue(pXmlKeys->m_strYcKey, oElement, m_strYc);
	xml_SetAttributeValue(pXmlKeys->m_strAngleBKey, oElement, m_strAngleB);
	xml_SetAttributeValue(pXmlKeys->m_strAngleEKey, oElement, m_strAngleE);
	xml_SetAttributeValue(pXmlKeys->m_strRadiusKey, oElement, m_strRadius);
	return 0;
}

BOOL CCharElementArcd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementArcd *p = (CCharElementArcd*)pDest;

	p->m_strXc = m_strXc;
	p->m_strYc = m_strYc;
	p->m_strAngleB = m_strAngleB;
	p->m_strAngleE = m_strAngleE;
	p->m_strRadius = m_strRadius;
	return TRUE;
}

CBaseObject* CCharElementArcd::Clone()
{
	CCharElementArcd *p = new CCharElementArcd();
	Copy(p);
	return p;
}

CExBaseObject* CCharElementArcd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CCharElementArcd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
BOOL CCharElementArcd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementArcd *p = (CCharElementArcd*)pObj;

	if(m_strXc != p->m_strXc)
	{
		return FALSE;
	}

	if(m_strYc != p->m_strYc)
	{
		return FALSE;
	}

	if(m_strAngleB != p->m_strAngleB)
	{
		return FALSE;
	}

	if(m_strAngleE != p->m_strAngleE)
	{
		return FALSE;
	}

	if(m_strRadius != p->m_strRadius)
	{
		return FALSE;
	}

	return TRUE;
}

CString CCharElementArcd::ReturnXml()
{
	CString str;
	str.Format(_T("lined x-c=\"%s\" y-c=\"%s\" angle-b=\"%s\" angle-e=\"%s\" radius=\"%s\" "),m_strXc,m_strYc,m_strAngleB,m_strAngleE,m_strRadius);
	return str;
}