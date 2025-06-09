//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArc.cpp  CCharElementArc


#include "stdafx.h"
#include "CharElementArc.h"

CCharElementArc::CCharElementArc()
{
	//初始化属性
	m_strName = "arc";
	m_strID = m_strName;
	//初始化成员变量
}

CCharElementArc::~CCharElementArc()
{
}

long CCharElementArc::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_strX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_strY);
	xml_GetAttibuteValue(pXmlKeys->m_strRadiusKey, oNode, m_strRadius);
	xml_GetAttibuteValue(pXmlKeys->m_strStartAngleKey, oNode, m_strStartAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strEndAngleKey, oNode, m_strEndAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	return 0;
}

long CCharElementArc::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_strX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_strY);
	xml_SetAttributeValue(pXmlKeys->m_strRadiusKey, oElement, m_strRadius);
	xml_SetAttributeValue(pXmlKeys->m_strStartAngleKey, oElement, m_strStartAngle);
	xml_SetAttributeValue(pXmlKeys->m_strEndAngleKey, oElement, m_strEndAngle);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	return 0;
}

void CCharElementArc::InitAfterRead()
{
}

BOOL CCharElementArc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementArc *p = (CCharElementArc*)pObj;

	if(m_strX != p->m_strX)
	{
		return FALSE;
	}

	if(m_strY != p->m_strY)
	{
		return FALSE;
	}

	if(m_strRadius != p->m_strRadius)
	{
		return FALSE;
	}

	if(m_strStartAngle != p->m_strStartAngle)
	{
		return FALSE;
	}

	if(m_strEndAngle != p->m_strEndAngle)
	{
		return FALSE;
	}

	if(m_strDir != p->m_strDir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementArc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementArc *p = (CCharElementArc*)pDest;

	p->m_strX = m_strX;
	p->m_strY = m_strY;
	p->m_strRadius = m_strRadius;
	p->m_strStartAngle = m_strStartAngle;
	p->m_strEndAngle = m_strEndAngle;
	p->m_strDir = m_strDir;
	return TRUE;
}

CBaseObject* CCharElementArc::Clone()
{
	CCharElementArc *p = new CCharElementArc();
	Copy(p);
	return p;
}

CString CCharElementArc::ReturnXml()
{
	CString str;
	str.Format(_T("arc start-angle=\" %s \" end-angle=\"%s \" x=\"%s\" y=\" %s \" radius=\"%s \" dir=\"%s \""),m_strStartAngle,m_strEndAngle,m_strX,m_strY,m_strRadius,m_strDir);
	return str;
}