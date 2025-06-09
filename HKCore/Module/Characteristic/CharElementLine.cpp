//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLine.cpp  CCharElementLine


#include "stdafx.h"
#include "CharElementLine.h"

CCharElementLine::CCharElementLine()
{
	//初始化属性
	m_strName = "line";
	m_strID = m_strName;
	//初始化成员变量
}

CCharElementLine::~CCharElementLine()
{
}

long CCharElementLine::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strXKey, oNode, m_strX);
	xml_GetAttibuteValue(pXmlKeys->m_strYKey, oNode, m_strY);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	return 0;
}

long CCharElementLine::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strXKey, oElement, m_strX);
	xml_SetAttributeValue(pXmlKeys->m_strYKey, oElement, m_strY);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	return 0;
}

void CCharElementLine::InitAfterRead()
{
}

BOOL CCharElementLine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLine *p = (CCharElementLine*)pObj;

	if(m_strX != p->m_strX)
	{
		return FALSE;
	}

	if(m_strY != p->m_strY)
	{
		return FALSE;
	}

	if(m_strAngle != p->m_strAngle)
	{
		return FALSE;
	}

	if(m_strDir != p->m_strDir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CCharElementLine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementLine *p = (CCharElementLine*)pDest;

	p->m_strX = m_strX;
	p->m_strY = m_strY;
	p->m_strAngle = m_strAngle;
	p->m_strDir = m_strDir;
	return TRUE;
}

CBaseObject* CCharElementLine::Clone()
{
	CCharElementLine *p = new CCharElementLine();
	Copy(p);
	return p;
}

CString CCharElementLine::ReturnXml()
{
	CString str;
	str.Format(_T("line angle=\"%s\" x=\"%s\" y=\"%s\" dir=\"%s\""),m_strAngle,m_strX,m_strY,m_strDir);
	return str;
}