// ExBaseListUpdateToolBase.cpp : 实现文件
//

#include "stdafx.h"
#include "GuideBookUpdateTool.h"
#include "GuideBook.h"

//////////////////////////////////////////////////////////////////////////
// CGuideBookUpdateTool

CGuideBookUpdateTool::CGuideBookUpdateTool()
{
	m_dwGbUpdateTypeMask = 0;
}

CGuideBookUpdateTool::~CGuideBookUpdateTool()
{

}

BOOL CGuideBookUpdateTool::Update_Own(CExBaseObject *pSrc, CExBaseObject *pDest)
{
	UINT nClassID = pSrc->GetClassID();

	if ((m_dwGbUpdateTypeMask & GBUPDATE_TYPE_REPORTMAP) == GBUPDATE_TYPE_REPORTMAP)
	{
		if (nClassID == RPTCLASSID_RPTREPORTMAP)
		{
			return Update_Own_ReportMap(pSrc, pDest);
		}
	}

	return FALSE;
}

BOOL CGuideBookUpdateTool::Update_Own_ReportMap(CExBaseObject *pSrc, CExBaseObject *pDest)
{
	CReportMap *pSrcMap = (CReportMap*)pSrc;
	CReportMap *pDestMap = (CReportMap*)pDest;

	pDestMap->DeleteAll();
	pSrcMap->Copy(pDestMap);

	return TRUE;
}

void CGuideBookUpdateTool::Update_ReportMap(CExBaseObject *pSrc, CExBaseObject *pDest)
{
	m_dwGbUpdateTypeMask = GBUPDATE_TYPE_REPORTMAP;

	Update_ByName(pSrc, pDest);
}

void CGuideBookUpdateTool::Update_ReportMap(CExBaseObject *pGuideBook)
{
	CGuideBook oGuideBook;
	CGuideBook *pDestGb = (CGuideBook*)pGuideBook;
	
	oGuideBook.OpenXMLFile(pDestGb->m_strGbXmlFile);
	CDvmDataset *pSrcExtendRptTemplate = oGuideBook.GetExtendRptTemplateDef(FALSE);

	if (pSrcExtendRptTemplate != NULL)
	{
		CDvmDataset *pDestExtendRptTemplate = pDestGb->GetExtendRptTemplateDef(TRUE);
		pSrcExtendRptTemplate->Copy(pDestExtendRptTemplate);
	}
	
	Update_ReportMap(&oGuideBook, pDestGb);
}

