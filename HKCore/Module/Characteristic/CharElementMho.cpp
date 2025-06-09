//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementMho.cpp  CCharElementMho


#include "stdafx.h"
#include "CharElementMho.h"

CCharElementMho::CCharElementMho()
{
	//��ʼ������
	m_strName = "mho";
	m_strID = m_strName;
	//��ʼ����Ա����
}

CCharElementMho::~CCharElementMho()
{
}

long CCharElementMho::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strForwardReachKey, oNode, m_strForwardReach);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strOffsetKey, oNode, m_strOffset);
	return 0;
}

long CCharElementMho::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strForwardReachKey, oElement, m_strForwardReach);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strOffsetKey, oElement, m_strOffset);
	return 0;
}

void CCharElementMho::InitAfterRead()
{
}

BOOL CCharElementMho::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementMho *p = (CCharElementMho*)pObj;

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

	return TRUE;
}

BOOL CCharElementMho::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementMho *p = (CCharElementMho*)pDest;

	p->m_strForwardReach = m_strForwardReach;
	p->m_strAngle = m_strAngle;
	p->m_strOffset = m_strOffset;
	return TRUE;
}

CBaseObject* CCharElementMho::Clone()
{
	CCharElementMho *p = new CCharElementMho();
	Copy(p);
	return p;
}

CString CCharElementMho::ReturnXml()
{
	CString str;
	str.Format(_T("MHO angle=\"%s\" forward-reach=\"%s\" offset=\"%s\""),m_strAngle,m_strForwardReach,m_strOffset);
	return str;
}