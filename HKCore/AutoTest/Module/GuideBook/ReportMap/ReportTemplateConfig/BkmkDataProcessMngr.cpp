//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//BkmkDataProcessMngr.cpp  CBkmkDataProcessMngr


#include "stdafx.h"
#include "BkmkDataProcessMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBkmkDataProcessMngr::CBkmkDataProcessMngr()
{
	//初始化属性

	//初始化成员变量
}

CBkmkDataProcessMngr::~CBkmkDataProcessMngr()
{
}

long CBkmkDataProcessMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CBkmkDataProcessMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CBkmkDataProcessMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CBkmkDataProcessMngr *p = (CBkmkDataProcessMngr*)pObj;

	return TRUE;
}

BOOL CBkmkDataProcessMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CBkmkDataProcessMngr *p = (CBkmkDataProcessMngr*)pDest;

	return TRUE;
}

CBaseObject* CBkmkDataProcessMngr::Clone()
{
	CBkmkDataProcessMngr *p = new CBkmkDataProcessMngr();
	Copy(p);
	return p;
}

CExBaseObject* CBkmkDataProcessMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CReportTemplateConfigXmlRWKeys *pXmlKeys = (CReportTemplateConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCBkmkDataProcessKey)
	{
		pNew = new CBkmkDataProcess();
	}

	return pNew;
}

CExBaseObject* CBkmkDataProcessMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == RPTCFGCLASSID_CBKMKDATAPROCESS)
	{
		pNew = new CBkmkDataProcess();
	}

	return pNew;
}


BOOL CBkmkDataProcessMngr::ProcessData(const CString &strID, CString &strValue, CString &strAdd, long nPrecision)
{
	if (IsSysBkmkDataProcess(strID))
	{
		return FALSE;
	}

	CBkmkDataProcess *pProcess = (CBkmkDataProcess*)FindByID(strID);

	if (pProcess == NULL)
	{
		return FALSE;
	}

	return pProcess->ProcessData(strValue, strAdd, nPrecision);
}
