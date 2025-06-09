//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttLicenseModule.cpp  CSttLicenseModule


#include "stdafx.h"
#include "SttLicenseModule.h"

CSttLicenseModule::CSttLicenseModule()
{
	//初始化属性
	m_nYear = 0;
	m_nMonth = 0;
	m_nDay = 0;
	m_nDays = 0;
	m_nTimes = 0;

	//初始化成员变量
}

CSttLicenseModule::~CSttLicenseModule()
{
}

long CSttLicenseModule::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strKeyKey, oNode, m_strKey);
	xml_GetAttibuteValue(pXmlKeys->m_strYearKey, oNode, m_nYear);
	xml_GetAttibuteValue(pXmlKeys->m_strMonthKey, oNode, m_nMonth);
	xml_GetAttibuteValue(pXmlKeys->m_strDayKey, oNode, m_nDay);
	xml_GetAttibuteValue(pXmlKeys->m_strDaysKey, oNode, m_nDays);
	xml_GetAttibuteValue(pXmlKeys->m_strTimesKey, oNode, m_nTimes);
	return 0;
}

long CSttLicenseModule::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKeyKey, oElement, m_strKey);
	xml_SetAttributeValue(pXmlKeys->m_strYearKey, oElement, m_nYear);
	xml_SetAttributeValue(pXmlKeys->m_strMonthKey, oElement, m_nMonth);
	xml_SetAttributeValue(pXmlKeys->m_strDayKey, oElement, m_nDay);
	xml_SetAttributeValue(pXmlKeys->m_strDaysKey, oElement, m_nDays);
	xml_SetAttributeValue(pXmlKeys->m_strTimesKey, oElement, m_nTimes);
	return 0;
}

BOOL CSttLicenseModule::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttLicenseModule *p = (CSttLicenseModule*)pObj;

	if(m_strKey != p->m_strKey)
	{
		return FALSE;
	}

	if(m_nYear != p->m_nYear)
	{
		return FALSE;
	}

	if(m_nMonth != p->m_nMonth)
	{
		return FALSE;
	}

	if(m_nDay != p->m_nDay)
	{
		return FALSE;
	}

	if(m_nDays != p->m_nDays)
	{
		return FALSE;
	}

	if(m_nTimes != p->m_nTimes)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttLicenseModule::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttLicenseModule *p = (CSttLicenseModule*)pDest;

	p->m_strKey = m_strKey;
	p->m_nYear = m_nYear;
	p->m_nMonth = m_nMonth;
	p->m_nDay = m_nDay;
	p->m_nDays = m_nDays;
	p->m_nTimes = m_nTimes;
	return TRUE;
}

CBaseObject* CSttLicenseModule::Clone()
{
	CSttLicenseModule *p = new CSttLicenseModule();
	Copy(p);
	return p;
}

