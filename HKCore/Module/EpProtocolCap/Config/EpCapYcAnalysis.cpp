//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapYcAnalysis.cpp  CEpCapYcAnalysis


#include "stdafx.h"
#include "EpCapYcAnalysis.h"

CEpCapYcAnalysis::CEpCapYcAnalysis()
{
	//初始化属性
	m_nProtocol = 0;

	//初始化成员变量
}

CEpCapYcAnalysis::~CEpCapYcAnalysis()
{
}

long CEpCapYcAnalysis::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strProtocolKey, oNode, m_nProtocol);
	xml_GetAttibuteValue(pXmlKeys->m_strFileKey, oNode, m_strDeviceModelFile);

	return 0;
}

long CEpCapYcAnalysis::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strProtocolKey, oElement, m_nProtocol);
	xml_SetAttributeValue(pXmlKeys->m_strFileKey, oElement, m_strDeviceModelFile);

	return 0;
}

CExBaseObject* CEpCapYcAnalysis::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapYcAnalysisItemKey)
	{
		pNew = new CEpCapYcAnalysisItem();
	}

	return pNew;
}

CExBaseObject* CEpCapYcAnalysis::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEPCAPYCANALYSISITEM)
	{
		pNew = new CEpCapYcAnalysisItem();
	}

	return pNew;
}

BOOL CEpCapYcAnalysis::CopyOwn(CBaseObject* pDest)
{
	CEpCapYcAnalysis *p = (CEpCapYcAnalysis*)pDest;

	if (p == this)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);

	p->m_nProtocol = m_nProtocol;
	p->m_strDeviceModelFile = m_strDeviceModelFile;

	return TRUE;
}

CBaseObject* CEpCapYcAnalysis::Clone()
{
	CEpCapYcAnalysis *pNew = new CEpCapYcAnalysis();
	Copy(pNew);
	return pNew;
}

