//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapYcAnalysisMngr.cpp  CEpCapYcAnalysisMngr


#include "stdafx.h"
#include "EpCapYcAnalysisMngr.h"

CEpCapYcAnalysisMngr::CEpCapYcAnalysisMngr()
{
	//CCEpCapYcAnalysisConfigXmlRWKeys::Create();
	//初始化属性

	//初始化成员变量
}

CEpCapYcAnalysisMngr::~CEpCapYcAnalysisMngr()
{
	//CCEpCapYcAnalysisConfigXmlRWKeys::Release();
}

long CEpCapYcAnalysisMngr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpCapYcAnalysisMngr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CEpCapYcAnalysisMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpCapYcAnalysisKey)
	{
		pNew = new CEpCapYcAnalysis();
	}

	return pNew;
}

CExBaseObject* CEpCapYcAnalysisMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEPCAPYCANALYSIS)
	{
		pNew = new CEpCapYcAnalysis();
	}

	return pNew;
}


CString  CEpCapYcAnalysisMngr::GetConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("YcAnalysisConfig.xml");
	return strFile;
}

void  CEpCapYcAnalysisMngr::OpenYcDrawConfigFile()
{
	CString strFile = GetConfigFile();
	OpenXmlFile(strFile, GetXmlElementKey(), CMonitorCapConfigXmlRWKeys::g_pXmlKeys);
}


void  CEpCapYcAnalysisMngr::SaveYcDrawConfigFile()
{
	CString strFile = GetConfigFile();
	SaveXmlFile(strFile, CMonitorCapConfigXmlRWKeys::g_pXmlKeys);
}

