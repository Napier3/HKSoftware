//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArcp.cpp  CCharElementArcp


#include "stdafx.h"
#include "CharElementArcp.h"

CCharElementArcp::CCharElementArcp()
{
	//初始化属性
	m_strName = "arcp";
	m_strID = m_strName;
	//初始化成员变量
}

CCharElementArcp::~CCharElementArcp()
{
}

long CCharElementArcp::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strZKey, oNode, m_strZ);
	xml_GetAttibuteValue(pXmlKeys->m_strPhKey, oNode, m_strPh);
	xml_GetAttibuteValue(pXmlKeys->m_strRadiusKey, oNode, m_strRadius);
	xml_GetAttibuteValue(pXmlKeys->m_strStartAngleKey, oNode, m_strStartAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strEndAngleKey, oNode, m_strEndAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	return 0;
}

long CCharElementArcp::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strZKey, oElement, m_strZ);
	xml_SetAttributeValue(pXmlKeys->m_strPhKey, oElement, m_strPh);
	xml_SetAttributeValue(pXmlKeys->m_strRadiusKey, oElement, m_strRadius);
	xml_SetAttributeValue(pXmlKeys->m_strStartAngleKey, oElement, m_strStartAngle);
	xml_SetAttributeValue(pXmlKeys->m_strEndAngleKey, oElement, m_strEndAngle);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	return 0;
}

void CCharElementArcp::InitAfterRead()
{
}

BOOL CCharElementArcp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementArcp *p = (CCharElementArcp*)pObj;

	if(m_strZ != p->m_strZ)
	{
		return FALSE;
	}

	if(m_strPh != p->m_strPh)
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

BOOL CCharElementArcp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementArcp *p = (CCharElementArcp*)pDest;

	p->m_strZ = m_strZ;
	p->m_strPh = m_strPh;
	p->m_strRadius = m_strRadius;
	p->m_strStartAngle = m_strStartAngle;
	p->m_strEndAngle = m_strEndAngle;
	p->m_strDir = m_strDir;
	return TRUE;
}

CBaseObject* CCharElementArcp::Clone()
{
	CCharElementArcp *p = new CCharElementArcp();
	Copy(p);
	return p;
}

CString CCharElementArcp::ReturnXml()
{
	CString str;
	str.Format(_T("arcp start-angle=\" %s\" end-angle=\"%s\" z=\"%s\" radius=\"%s\" ph=\"%s\" dir=\"%s\""),m_strStartAngle,m_strEndAngle,m_strZ,m_strRadius,m_strPh,m_strDir);
	return str;
}