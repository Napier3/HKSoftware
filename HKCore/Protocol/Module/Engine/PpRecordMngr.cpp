#include "StdAfx.h"
#include "PpRecordMngr.h"
#include "PpPackageDetail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpRecordMngr::CPpRecordMngr()
{
	m_bRecordAllPackage = FALSE;
	m_bCanRecordPackage = FALSE;
	m_pPackageDataset = NULL;
}

CPpRecordMngr::~CPpRecordMngr(void)
{
	m_astrPackageID.RemoveAll();
}

LONG CPpRecordMngr::RecordPackage(const CString &strPkgID)
{
	m_bCanRecordPackage = TRUE;

	//空ID，表示全部的报文
	if (strPkgID.GetLength() == 0)
	{
		m_astrPackageID.RemoveAll();
		m_bRecordAllPackage = TRUE;
		return 0;
	}
	else
	{
		m_bRecordAllPackage = FALSE;
	}

	if (!IsPackageIDExist(strPkgID))
	{
		m_astrPackageID.Add(strPkgID);
	}

	return m_astrPackageID.GetCount();
}

LONG CPpRecordMngr::UnRecordPackage(const CString &strPkgID)
{
	//空ID，表示全部的报文
	if (strPkgID.GetLength() == 0)
	{
		m_astrPackageID.RemoveAll();
		m_bRecordAllPackage = FALSE;
		return 0;
	}

	BOOL bTrue = FALSE;
	long nCount = m_astrPackageID.GetCount();
	long nIndex = 0;
	CString strText;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strText = m_astrPackageID.GetAt(nIndex);

		if (strText == strPkgID)
		{
			m_astrPackageID.RemoveAt(nIndex);
			break;
		}
	}

	return 0;
}

BOOL CPpRecordMngr::IsPackageIDExist(const CString &strPkgID)
{
	if (m_bRecordAllPackage)
	{
		return TRUE;
	}

	BOOL bTrue = FALSE;
	long nCount = m_astrPackageID.GetCount();
	long nIndex = 0;
	CString strText;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strText = m_astrPackageID.GetAt(nIndex);

		if (strText == strPkgID)
		{
			bTrue = TRUE;
			break;
		}
	}

	return bTrue;
}

CDvmData* CPpRecordMngr::AddPackage(CExBaseObject *pPkg)
{
	if (!m_bCanRecordPackage)
	{
		return NULL;
	}

	CAutoSimpleLock oLock(m_oRecordAutoCriticSection);

	if (!IsPackageIDExist(pPkg->m_strID))
	{
		return NULL;
	}

	CPpPackageDetail *pDetail = (CPpPackageDetail*)pPkg;

	if (pDetail->m_bRecord)
	{
		return NULL;
	}

	pDetail->m_bRecord = TRUE;

	//AddTail(pPkg);
	long nValueCount = 0;
	CDvmData *pData = NULL;

	if (m_pPackageDataset != NULL)
	{
		pData = m_pPackageDataset->AddNewData();
		pData->m_strName = pDetail->m_strName;
		pData->m_strID = pDetail->m_strID;
		pDetail->GetTmString(pData->m_strValue);
		pData->m_strDataType = pDetail->m_strTID;

		//报文记录的数据
		pData->AppendClone(pDetail->m_oDvmValues);
		nValueCount = pDetail->m_oDvmValues.GetCount();
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("m_pPackageDataset == NULL"));
	}

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RecordPaackage:%s {%d:%d:%d.%d} ValCount=%d"), pDetail->m_strID.GetString()
		, pDetail->m_tm.wHour,  pDetail->m_tm.wMinute, pDetail->m_tm.wSecond, pDetail->m_tm.wMilliseconds, nValueCount);

	return pData;
}

void CPpRecordMngr::DeleteAllPackage()
{
	CAutoSimpleLock oLock(m_oRecordAutoCriticSection);
	//DeleteAll();
	OnDeleteAllRecordPackage();

// 	if (m_pPackageDataset != NULL)
// 	{
// 		m_pPackageDataset->Res();
// 	}
}

void CPpRecordMngr::OnProcedureExit(const CString &strProcedureID)
{
	if (m_strProcedureRecord.GetLength() == 0)
	{
		return;
	}

	if (m_strProcedureRecord == strProcedureID)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PpRecordMngr::OnProcedureExit=%s"), strProcedureID.GetString());
		m_bCanRecordPackage = FALSE;
	}
}

void CPpRecordMngr::OnProcedureStart(const CString &strProcedureID)
{
	if (m_strProcedureRecord.GetLength() == 0)
	{
		return;
	}

	if (m_strProcedureRecord == strProcedureID)
	{
		m_bCanRecordPackage = TRUE;
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PpRecordMngr::OnProcedureStart=%s"), strProcedureID.GetString());
	}
}

LONG CPpRecordMngr::RecordProcedure(const CString &strProcedureID)
{
	m_bRecordAllPackage = TRUE;
	m_bCanRecordPackage = FALSE;
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PpRecordMngr::RecordProcedure=%s"), strProcedureID.GetString());
	m_strProcedureRecord = strProcedureID;
	return 0;
}

LONG CPpRecordMngr::UnRecordProcedure(const CString &strProcedureID)
{
	m_strProcedureRecord = _T("");
	m_bRecordAllPackage = FALSE;
	m_bCanRecordPackage = TRUE;
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("PpRecordMngr::UnRecordProcedure=%s"), strProcedureID.GetString());
	return 0;
}

void CPpRecordMngr::OnDeleteAllRecordPackage()
{
	POS pos = GetHeadPosition();
	CPpPackageDetail *pDetail = NULL;

	while (pos != NULL)
	{
		pDetail = (CPpPackageDetail *)GetNext(pos);
		pDetail->m_bDelete = TRUE;
	}

	RemoveAll();
}

