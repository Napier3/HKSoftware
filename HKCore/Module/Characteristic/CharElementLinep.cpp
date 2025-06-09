//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLinep.cpp  CCharElementLinep


#include "stdafx.h"
#include "CharElementLinep.h"

CCharElementLinep::CCharElementLinep()
{
	//初始化属性
	m_strName = "linep";
	m_strID = m_strName;
	//初始化成员变量
}

CCharElementLinep::~CCharElementLinep()
{
}

long CCharElementLinep::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strZKey, oNode, m_strZ);
	xml_GetAttibuteValue(pXmlKeys->m_strPhKey, oNode, m_strPh);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_strDir);
	return 0;
}

long CCharElementLinep::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strZKey, oElement, m_strZ);
	xml_SetAttributeValue(pXmlKeys->m_strPhKey, oElement, m_strPh);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_strDir);
	return 0;
}

void CCharElementLinep::InitAfterRead()
{
}

BOOL CCharElementLinep::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementLinep *p = (CCharElementLinep*)pObj;

	if(m_strZ != p->m_strZ)
	{
		return FALSE;
	}

	if(m_strPh != p->m_strPh)
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

BOOL CCharElementLinep::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementLinep *p = (CCharElementLinep*)pDest;

	p->m_strZ = m_strZ;
	p->m_strPh = m_strPh;
	p->m_strAngle = m_strAngle;
	p->m_strDir = m_strDir;
	return TRUE;
}

CString CCharElementLinep::ReturnXml()
{
	CString str;
	str.Format(_T("linep angle=\"%s\" z=\"%s\" ph=\"%s\" dir=\"%s\" "),m_strAngle,m_strZ,m_strPh,m_strDir);
	return str;
}