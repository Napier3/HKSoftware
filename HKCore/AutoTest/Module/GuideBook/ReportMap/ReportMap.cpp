#include "StdAfx.h"
#include "ReportMap.h"
#include "RptBkmk.h"
#include "RptData.h"
#include "../../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


 long g_nCloneReportMapInCopy = 0;

CReportMap::CReportMap(void)
{
	m_pArea = NULL;

#ifndef NOT_USE_XLANGUAGE
    m_strName = g_sLangTxt_ReportDefinition/*L"报表定义"*/;
#endif
    m_strName = _T("_rpt_map");
    m_strID = _T("_rpt_map");
}

CReportMap::CReportMap(CString strFilePath)
{
}

CReportMap::~CReportMap(void)
{
	//DeleteAll();
}

CRptMapRepeat* CReportMap::FindRptMapRepeat(long nRepeatIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CRptMapRepeat *pFind = NULL;
	CRptMapRepeat *pTemp = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTMAPREPEAT)
		{
			pTemp = (CRptMapRepeat*)p;

			if (nRepeatIndex == pTemp->m_nIndex)
			{
				pFind = pTemp;
				break;
			}
		}
	}

	return pFind;
}


CRptMapRepeat* CReportMap::AddRptMapRepeat(long nRepeatIndex)
{
	CRptMapRepeat *pFind = FindRptMapRepeat(nRepeatIndex);

	if (pFind == NULL)
	{
		pFind = new CRptMapRepeat();
		pFind->m_nIndex = nRepeatIndex;
		AddNewChild(pFind);
	}

	return pFind;
}

void CReportMap::SelectAllRptData(CExBaseList &listDatas)
{
	SelectAllRptData(this, listDatas);
}

void CReportMap::SelectAllRptData(CExBaseList *pDatas, CExBaseList &listDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pDatas->GetNext(pos);
		
		if (p->GetClassID() == RPTCLASSID_RPTDATA)
		{
			listDatas.AddTail(p);
		}
		else if (p->IsBaseList())
		{
			SelectAllRptData((CExBaseList*)p, listDatas);
		}
	}
}

CRptArea* CReportMap::AddArea(const CString &strAreaType)
{
	if (m_pArea == NULL)
	{
		m_pArea = new CRptArea();
		AddNewChild(m_pArea);
		m_pArea->SetRptAreaType(strAreaType);
	}

	return m_pArea;
}

CRptData* CReportMap::AddNewData(const CString  &strName, const CString  &strID, const CString &strPrecision, long nRepeatIndex)
{
	if (nRepeatIndex < 1)
	{
		return AddNewRptData(strName, strID, strPrecision);
	}
	
	CRptMapRepeat *pRepeat = AddRptMapRepeat(nRepeatIndex);
	ASSERT (pRepeat != NULL);

	return pRepeat->AddNewRptData(strName, strID, strPrecision);
}

CRptData* CReportMap::FindRptData(const CString  &strID, long nRepeatIndex)
{
	CRptData *pData = NULL;

	if (nRepeatIndex < 1)
	{
		pData = (CRptData*)FindByID(strID);
		return pData;
	}
	
	CRptMapRepeat *pRepeat = FindRptMapRepeat(nRepeatIndex);
	
	if (pRepeat != NULL)
	{
		pData =  (CRptData*)pRepeat->FindByID(strID);
	}

	return pData;
}

void CReportMap::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == RPTCLASSID_RPTAREA)
		{
			m_pArea = (CRptArea *)p;
		}
	}
// 	if (m_pArea == NULL)
// 	{
// 		m_pArea = (CRptArea *)AddNewChild(new CRptArea());
// 	}
}

CBaseObject* CReportMap::Clone()	
{	
#ifdef GUIDEBOOK_DEV_MODE
	if (g_nCloneReportMapInCopy == 0)
	{
		return NULL;
	}
#endif

	CReportMap *pMap = new CReportMap();
	Copy(pMap);
	return pMap;
}


BOOL CReportMap::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if(this == pDest)
		return TRUE;

	CExBaseObject::CopyOwn(pDest);

	return TRUE;
}

CExBaseObject* CReportMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CGbXMLKeys *pKeys = (CGbXMLKeys*)pXmlRWKeys;

	if (strClassID == pKeys->m_strDataKey)
	{
		return new CRptData();
	}
	else if (strClassID == pKeys->m_strAreaKey)
	{
		m_pArea =  new CRptArea();
		return m_pArea;
	}
	else if (strClassID == pKeys->m_strMapRepeatKey)
	{
		return  new CRptMapRepeat();
	}

	return NULL;

}

CExBaseObject* CReportMap::CreateNewChild(long nClassID)
{
	if(nClassID == RPTCLASSID_RPTDATA)
	{
		return new CRptData();
	}
	else if(nClassID == RPTCLASSID_RPTAREA)
	{
		m_pArea =  new CRptArea();
		return m_pArea;
	}
	else if(nClassID == RPTCLASSID_RPTMAPREPEAT)
	{
		return  new CRptMapRepeat();
	}

	return NULL;
}


long CReportMap::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (g_bGbExportXmlReportFile)
		{
			if (nClassID == RPTCLASSID_RPTAREA)
			{
				continue;
			}
		}

		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

void CReportMap::AddRptDataClone(CRptData *pRptData)
{
	ASSERT(pRptData != NULL);

	CRptData *pNew = (CRptData *)pRptData->Clone();
	AddNewChild(pNew);
}

void Gb_GetRptBkmkNamePathString(CRptBkmk *pBkmk, CString &strPath)
{
	ASSERT (pBkmk != NULL);
	strPath.Empty();

	if (pBkmk == NULL)
	{
		return;
	}

	CExBaseObject *pParent = (CExBaseObject*)pBkmk->GetParent();
	CString strName;

	while (pParent->GetClassID() != GBCLASSID_GUIDEBOOK)
	{
		if (pParent->GetClassID() != RPTCLASSID_RPTREPORTMAP)
		{
			if (pParent->GetClassID() == RPTCLASSID_RPTMAPREPEAT)
			{
				//strName.Format(_T("第%d次测试"), ( (CRptMapRepeat*)pParent)->m_nIndex);
				strName = ( (CRptMapRepeat*)pParent)->GetRptMapRepeatName();
			}
			else if (pParent->GetClassID() == RPTCLASSID_RPTDATA)
			{
                strName.Format(_T("%s[%s]"), pParent->m_strName.GetString(), pParent->m_strID.GetString());
			}
			else
			{
				strName = pParent->m_strName;
			}

			if (strPath.GetLength() > 0)
			{
				strPath = strName + _T(" >> ") + strPath;
			}
			else
			{
				strPath = strName;
			}
		}

		pParent = (CExBaseObject*)pParent->GetParent();
	}
}
