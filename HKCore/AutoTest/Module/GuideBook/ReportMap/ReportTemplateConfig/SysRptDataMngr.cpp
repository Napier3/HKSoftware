//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SysRptDataMngr.cpp  CSysRptDataMngr


#include "stdafx.h"
#include "SysRptDataMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSysRptDataMngr::CSysRptDataMngr()
{
	//初始化属性

	//初始化成员变量
}

CSysRptDataMngr::~CSysRptDataMngr()
{
}

long CSysRptDataMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSysRptDataMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CSysRptDataMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSysRptDataMngr *p = (CSysRptDataMngr*)pDest;

	return TRUE;
}

CBaseObject* CSysRptDataMngr::Clone()
{
	CSysRptDataMngr *p = new CSysRptDataMngr();
	Copy(p);
	return p;
}

CExBaseObject* CSysRptDataMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSysRptDataKey)
	{
		pNew = new CSysRptData();
	}

	return pNew;
}

CExBaseObject* CSysRptDataMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RPTCFGCLASSID_CSYSRPTDATA)
	{
		pNew = new CSysRptData();
	}

	return pNew;
}
