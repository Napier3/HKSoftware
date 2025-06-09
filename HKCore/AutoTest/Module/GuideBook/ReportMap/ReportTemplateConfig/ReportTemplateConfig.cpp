//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ReportTemplateConfig.cpp  CReportTemplateConfig


#include "stdafx.h"
#include "ReportTemplateConfig.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../Module/XLanguage/XLanguageMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CReportTemplateConfig::CReportTemplateConfig()
{
	//初始化属性

	//初始化成员变量
	m_pBkmkDataProcessMngr = NULL;
	m_pSysRptDataMngr = NULL;
	m_pCommCmdStrcutAttrs = NULL;
	m_pMgrpCmbn = NULL;
}

CReportTemplateConfig::~CReportTemplateConfig()
{
}

long CReportTemplateConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CReportTemplateConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CReportTemplateConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CReportTemplateConfig *p = (CReportTemplateConfig*)pObj;

	return TRUE;
}

BOOL CReportTemplateConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CReportTemplateConfig *p = (CReportTemplateConfig*)pDest;

	return TRUE;
}

CBaseObject* CReportTemplateConfig::Clone()
{
	CReportTemplateConfig *p = new CReportTemplateConfig();
	Copy(p);
	return p;
}

CExBaseObject* CReportTemplateConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCBkmkDataProcessMngrKey)
	{
		pNew = new CBkmkDataProcessMngr();
	}
	else if (strClassID == pXmlKeys->m_strCCommCmdStrcutAttrsKey)
	{
		pNew = new CCommCmdStrcutAttrs();
	}
	else if (strClassID == pXmlKeys->m_strCSysRptDataMngrKey)
	{
		pNew = new CSysRptDataMngr();
	}
	else if (strClassID == pXmlKeys->m_strCMgrpCmbnDataMngrKey)
	{
		pNew = new CMgrpCmbnDataMngr();
	}

	return pNew;
}

CExBaseObject* CReportTemplateConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RPTCFGCLASSID_CBKMKDATAPROCESSMNGR)
	{
		pNew = new CBkmkDataProcessMngr();
	}
	else if (nClassID == RPTCFGCLASSID_CCOMMCMDSTRCUTATTRS)
	{
		pNew = new CCommCmdStrcutAttrs();
	}
	else if (nClassID == RPTCFGCLASSID_CSYSRPTDATAMNGR)
	{
		pNew = new CSysRptDataMngr();
	}

	return pNew;
}
void CReportTemplateConfig::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == RPTCFGCLASSID_CBKMKDATAPROCESSMNGR)
		{
			m_pBkmkDataProcessMngr = (CBkmkDataProcessMngr*)p;
		}
		else if (nClassID == RPTCFGCLASSID_CSYSRPTDATAMNGR)
		{
			m_pSysRptDataMngr = (CSysRptDataMngr*)p;
		}
		else if (nClassID == RPTCFGCLASSID_CCOMMCMDSTRCUTATTRS)
		{
			m_pCommCmdStrcutAttrs = (CCommCmdStrcutAttrs*)p;
		}
		else if (nClassID == RPTCFGCLASSID_CMGRPCMBNDATAMNGR)
		{
			m_pMgrpCmbn = (CMgrpCmbnDataMngr*)p;
		}
	}

	if (m_pBkmkDataProcessMngr == NULL)
	{
		m_pBkmkDataProcessMngr = (CBkmkDataProcessMngr*)AddNewChild(new CBkmkDataProcessMngr());
	}

	if (m_pSysRptDataMngr == NULL)
	{
		m_pSysRptDataMngr = (CSysRptDataMngr*)AddNewChild(new CSysRptDataMngr());
	}

	if (m_pCommCmdStrcutAttrs == NULL)
	{
		m_pCommCmdStrcutAttrs = (CCommCmdStrcutAttrs*)AddNewChild(new CCommCmdStrcutAttrs());
	}

	if (m_pMgrpCmbn == NULL)
	{
		m_pMgrpCmbn = (CMgrpCmbnDataMngr*)AddNewChild(new CMgrpCmbnDataMngr());
	}
}

BOOL CReportTemplateConfig::OpenReportTemplateConfigFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("ReportTemplateConfig.xml");

	BOOL b = OpenXmlFile(strFile, CReportTemplateConfigXmlRWKeys::CReportTemplateConfigKey(), CReportTemplateConfigXmlRWKeys::g_pXmlKeys);

#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(this, _T("ReportTemplateConfig.xml"));
#endif

	return TRUE;
}

