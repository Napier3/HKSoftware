//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgReportsMngr.cpp  CTtmgReportsMngr


#include "stdafx.h"
#include "TtmgReportsMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTtmgReportsMngr::CTtmgReportsMngr()
{
	//初始化属性

	//初始化成员变量
	m_pReportsError = NULL;
	m_pReportsSucc = NULL;
	m_pReportsDestructive = NULL;
	m_pReportsNonDestructive = NULL;
	m_pReportsSummary = NULL;

	m_pReportSumAllSuc = NULL;
	m_pReportSumError  = NULL;
	m_pReportSumSucc  = NULL;
}

CTtmgReportsMngr::~CTtmgReportsMngr()
{
}

long CTtmgReportsMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgReportsMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgReportsMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CTtmgReportsMngr::InitAfterRead()
{
	m_pReportsError = (CTtmgReports *)FindByID(_T("Error"));
	m_pReportsSucc = (CTtmgReports *)FindByID(_T("Succ"));
	m_pReportsDestructive = (CTtmgReports *)FindByID(_T("Destructive"));
	m_pReportsNonDestructive = (CTtmgReports *)FindByID(_T("NonDestructive"));
	m_pReportsSummary = (CTtmgReports *)FindByID(_T("Summary"));

	ASSERT (m_pReportsError != NULL);
	ASSERT (m_pReportsSucc != NULL);
	ASSERT (m_pReportsDestructive != NULL);
	ASSERT (m_pReportsNonDestructive != NULL);
	ASSERT (m_pReportsSummary != NULL);

	if (m_pReportsError != NULL)
	{
		m_pReportsError->InitAllReports();
	}

	if (m_pReportsSucc != NULL)
	{
		m_pReportsSucc->InitAllReports();
	}

	if (m_pReportsDestructive != NULL)
	{
		m_pReportsDestructive->InitAllReports();
	}

	if (m_pReportsNonDestructive != NULL)
	{
		m_pReportsNonDestructive->InitAllReports();
	}

	if (m_pReportsSummary != NULL)
	{
		m_pReportsSummary->InitAllReports();

		m_pReportSumAllSuc = m_pReportsSummary->FindReportByID(_T("全测试汇总表"));
		m_pReportSumError  = m_pReportsSummary->FindReportByID(_T("仅自动测试汇总表_不合格"));
		m_pReportSumSucc  = m_pReportsSummary->FindReportByID(_T("仅自动测试汇总表_合格"));
	}

	ASSERT (m_pReportSumAllSuc != NULL);
	ASSERT (m_pReportSumError != NULL);
	ASSERT (m_pReportSumSucc != NULL);

}

BOOL CTtmgReportsMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTtmgReportsMngr *p = (CTtmgReportsMngr*)pObj;

	return TRUE;
}

BOOL CTtmgReportsMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTtmgReportsMngr *p = (CTtmgReportsMngr*)pDest;

	return TRUE;
}

CBaseObject* CTtmgReportsMngr::Clone()
{
	CTtmgReportsMngr *p = new CTtmgReportsMngr();
	Copy(p);
	return p;
}

BOOL CTtmgReportsMngr::CanPaste(UINT nClassID)
{
	if (nClassID == TTMGCLASSID_CTTMGREPORTS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTtmgReportsMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTtmgReportsKey)
	{
		pNew = new CTtmgReports();
	}

	return pNew;
}

CExBaseObject* CTtmgReportsMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TTMGCLASSID_CTTMGREPORTS)
	{
		pNew = new CTtmgReports();
	}

	return pNew;
}
