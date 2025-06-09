#include "stdafx.h"
#include "reports.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CReports::CReports()
{

}

CReports::~CReports()
{
}


void CReports::GetReportsForCal(CExBaseList &oReports)
{
	CReport *pReport = NULL;
	POS pos = GetTailPosition();

	if (pos == NULL)
	{
		return;
	}

	pReport = (CReport*)GetAt(pos);
	
	if (pReport->IsCalReport())
	{
		pReport = (CReport*)GetPrev(pos);
	}

	while (pos != NULL)
	{
		pReport = (CReport*)GetPrev(pos);

		if (pReport->IsCalReport())
		{
			break;
		}

		oReports.AddTail(pReport);
	}
}

void CReports::GetReportsForCalEx(CExBaseList &oReports)
{
	CReport *pReport = NULL;
	POS pos = GetTailPosition();

	if (pos == NULL)
	{
		return;
	}

	pReport = (CReport*)GetPrev(pos);

	if (!pReport->IsCalReport())
	{
		oReports.AddTail(pReport);
	}

	while (pos != NULL)
	{
		pReport = (CReport*)GetPrev(pos);

		if (pReport->IsCalReport())
		{
			break;
		}

		oReports.AddTail(pReport);
	}
}

//公共接口
CReport* CReports::AddReport(const CString &strName, const CString &strReportID)
{
	CReport* pReport = new CReport();
	pReport->m_strID = strReportID;
	pReport->m_strName = strName;
	AddTail(pReport);
	pReport->SetParent(this);
	pReport->SetBeginTime();
	return pReport;
}

BOOL CReports::SetReportValues(CValues* pValues)
{
	ASSERT (pValues != NULL);
	if(pValues == NULL)
		return FALSE;

	//对Reports中的最后一个Report调用CReport::SetReportValues
	long nCount = GetCount();
	CReport* pReport = (CReport*)GetAt(nCount-1);
	ASSERT(pReport != NULL);
	pReport->SetReportValues(pValues);
	
	return TRUE;
}

BOOL CReports::SetReportValues(CShortDatas *pDatas)
{
	ASSERT (pDatas != NULL);
	if(pDatas == NULL)
		return FALSE;

	//对Reports中的最后一个Report调用CReport::SetReportValues
	long nCount = GetCount();
	CReport* pReport = (CReport*)GetAt(nCount-1);
	ASSERT(pReport != NULL);
	pReport->SetReportValues(pDatas);

	return TRUE;
}


void  CReports::SetResultJudge(long nResult)
{
	//对Reports中的最后一个Report调用CReport::SetReportValues
	long nCount = GetCount();
	//ASSERT (nCount > 0);

	if (nCount == 0)
	{
		return;
	}

	CReport* pReport = (CReport*)GetTail();
	ASSERT(pReport != NULL);
	pReport->SetResultJudge(nResult);
}

//重写父类方法
UINT CReports::GetClassID()
{
	return GBCLASSID_REPORTS;
}

long CReports::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

//2020-12-21 shaolei
long CReports::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
#ifdef GUIDEBOOK_DEV_MODE
	long nCount = 0;

	if (oBinaryBuffer.IsCalSizeMode())
	{
		oBinaryBuffer.AddBufferLength(sizeof(nCount));
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		oBinaryBuffer.PutLong(nCount);
	}

	return 0;
#endif

	return CExBaseList::SerializeChildren(oBinaryBuffer);
}

long CReports::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CReports::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CReports::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (g_bGbExportXmlReportFile)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportRptOnlySaveLast)
		{
			CExBaseObject *pObj = GetTail();

			if (pObj != NULL)
			{
				pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
			}
			else
			{
				CString strNamePath;
				strNamePath = ((CExBaseObject*)m_pParent)->GetNamePathEx(GBCLASSID_DEVICE, TRUE);
                //CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s] has no report"), strNamePath.GetString());
			}

			return 0;
		}
	}

	if (CGbXMLKeys::g_pGbXMLKeys->m_nSaveItemRpts <= 0)
	{
		CExBaseObject *pObj = GetHead();

		if (pObj != NULL)
		{
			pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
		}

		return 0;
	}

	return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

BSTR CReports::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strReportsKey;
}

CExBaseObject* CReports::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strReportKey)
	{
		CReport* pReport = new CReport();
		return pReport;
	}

	return NULL;
}

CExBaseObject* CReports::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_REPORT)
	{
		CReport* pReport = new CReport();
		return pReport;
	}

	return NULL;
}

BOOL CReports::IsEqual(CBaseObject* pObj)
{
	return CBaseObject::IsEqual(pObj);
}

BOOL CReports::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);

	if(pDesObj == this)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDesObj);

	return 0;
}

CBaseObject* CReports::Clone()
{
	CReports* pReports = new CReports();

	Copy(pReports);
	
	return pReports;
}

BOOL CReports::IsSame(CBaseObject* pObj)
{
	return FALSE;
}

void CReports::ClearItemInDbState()
{
	POS pos = GetHeadPosition();
	CReport *pReport = NULL;

	while (pos != NULL)
	{
		pReport = (CReport *)GetNext(pos);
		pReport->ClearItemInDbState();
	}
}

BOOL CReports::HasReportEx()
{
	if (GetCount() == 0)
	{
		return FALSE;
	}

	CReport *pReport = (CReport*)GetAtIndex(0);

	return pReport->m_pValues->GetCount();
}

//2021-8-10 lijunqing
void CReports::InitReports(CReports *pSrcReports)
{
	CReport *p = NULL;
	POS pos = pSrcReports->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CReport *)pSrcReports->GetNext(pos);

		if (FindByID(p->m_strID) == NULL)
		{
			CReport *pNew = (CReport*)p->Clone();
			AddNewChild(pNew);
		}
	}
}

