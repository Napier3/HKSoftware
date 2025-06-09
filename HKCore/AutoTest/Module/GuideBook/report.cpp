#include "stdafx.h"
#include "report.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const CString CReport::g_pszCalReportKey = _T("CAL_");

CReport::CReport()
{
	m_pValues = new CValues();
	ASSERT(m_pValues != NULL);

	m_pRptDvmDataset = new CDvmDatasetGroup();
	ASSERT(m_pRptDvmDataset != NULL);

	m_pLogs = new CDvmLogs();
	ASSERT(m_pLogs != NULL);

	SetResultJudge(1);
	AddRptValues_ErrorCal();//报告中，增加几个固定的结果值，用于绑定误差判断的计算值
}

CReport::~CReport()
{
	if (m_pValues != NULL)
	{
		delete m_pValues;
		m_pValues = NULL;
	}

// 	if (m_pRptDataEx != NULL)
// 	{
// 		delete m_pRptDataEx;
// 		m_pRptDataEx = NULL;
// 	}

	if (m_pRptDvmDataset != NULL)
	{
		delete m_pRptDvmDataset;
		m_pRptDvmDataset = NULL;
	}

	if (m_pLogs != NULL)
	{
		delete m_pLogs;
		m_pLogs = NULL;
	}
}

CString CReport::GetTestTime(long nMode)
{
	if (nMode == 1)
	{
		return m_strBeginTime;
	}
	else if (nMode == 2)
	{
		return m_strEndTime;
	}
	else
	{
		CGpsPcTime tm1, tm2;
		tm1.FromStringEx(m_strBeginTime);
		tm2.FromStringEx(m_strEndTime);

		CGpsPcTimeSpan tmSpan;
		tmSpan = tm2 - tm1;

		DWORD dwMs = tmSpan.GetTotalMilliseconds();
		dwMs /= 2;
		tmSpan.InitByMilliseconds(dwMs);

		tm2 = tm1 + tmSpan;

		CString strTime;
		tm2.ToString(strTime);

		return strTime;
	}
}

void CReport::SetBeginTime()
{
	GetCurrSystemtimeString(m_strBeginTime);
}

void CReport::SetEndTime()
{
	GetCurrSystemtimeString(m_strEndTime);
}

BOOL CReport::SetReportValues(CValues* pValues)
{
	ASSERT (pValues != NULL);
	if(pValues == NULL)
	{
		return FALSE;
	}

	if(m_pValues != NULL)
	{
		m_pValues->DeleteAll();
	}

// 	POS pos = pValues->GetHeadPosition();
// 	CValue *p = NULL;
// 	CValue *pFind = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pValues->GetNext(pos);
// 		pFind = (CValue*)m_pValues->FindByID(p->m_strID);
// 
// 		if (pFind == NULL)
// 		{
// 			pFind = (CValue*)p->Clone();
// 		}
// 		else
// 		{
// 			pFind->m_strValue = p->m_strValue;
// 		}
// 	}
	m_pValues->AppendClone(pValues);

//shaolei   2019.11.18  修改电气量直接返回结果时，注释此行
//lijq  2020-3-8  构造函数，已经添加了默认为合格的结果判断，此处注释掉，没有问题
//	AddResultJudgeKey(0);

	return TRUE;
}

BOOL CReport::UpdateReportValues(CValues* pValues)
{
	ASSERT (pValues != NULL);
	if(pValues == NULL)
	{
		return FALSE;
	}

	m_pValues->SetValuesByDatas(pValues);

//shaolei   2019.11.18  修改电气量直接返回结果时，注释此行
//lijq  2020-3-8  构造函数，已经添加了默认为合格的结果判断，此处注释掉，没有问题
//	AddResultJudgeKey(0);            

	return TRUE;
}

BOOL CReport::SetReportValues(CDataSet* pDataset)
{
	if (m_pValues != NULL)
	{
		delete m_pValues;
		m_pValues = NULL;
	}

	m_pValues = pDataset->GetValues();
	AddResultJudgeKey(0);

	return (m_pValues != NULL);
}

BOOL CReport::SetReportValues(CExBaseList* pListDataObj)
{
	POS pos = pListDataObj->GetHeadPosition();
	CDataObj *pData = NULL;
	m_pValues->DeleteAll();

	while (pos != NULL)
	{
		pData = (CDataObj *)pListDataObj->GetNext(pos);
		m_pValues->AddNew(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	AddResultJudgeKey(0);

	return (m_pValues != NULL);
}

//该函数的目的，是将pSrcReport中存在，而this指针中不存在的报告数据，添加到this。
void CReport::UpdateReportValues(CReport *pSrcReport)
{
	if (pSrcReport == NULL)
	{
		return;
	}

	CValues *pSrcValues = pSrcReport->m_pValues;

	if (pSrcValues == NULL)
	{
		return;
	}

	if (pSrcValues->GetCount() == 0)
	{
		return;
	}

	POS pos = pSrcValues->GetHeadPosition();

	while (pos != NULL)
	{
		CValue *pValue = (CValue*)pSrcValues->GetNext(pos);
		CValue *pFind = (CValue *)m_pValues->FindByID(pValue->m_strID);

		if (pFind == NULL)
		{
			m_pValues->AddNew(pValue->m_strID, pValue->m_strName, pValue->m_strValue);
		}
	}
}

BOOL CReport::AppendReportValues(CExBaseList *pListDataObj)
{
	POS pos = pListDataObj->GetHeadPosition();
	//CDataObj *pData = NULL;
	CExBaseObject *pObj = NULL;
	CValue *pValue = NULL;
	CString strName, strID, strValue;

	while (pos != NULL)
	{
		pObj = pListDataObj->GetNext(pos);
		//pData = (CDataObj *)pListDataObj->GetNext(pos);

		if (pObj->GetClassID() == GBCLASSID_DATAOBJ)
		{
			CDataObj *pData = (CDataObj *)pObj;
			strName = pData->m_strName;
			strID = pData->m_strID;
			strValue = pData->m_strValue;
		}
		else if (pObj->GetClassID() == DTMCLASSID_CSHORTDATA)
		{
			CShortData *pData = (CShortData *)pObj;
			strName = pData->m_strName;
			strID = pData->m_strID;
			strValue = pData->m_strValue;
		}
		else if (pObj->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;
			strName = pData->m_strName;
			strID = pData->m_strID;
			strValue = pData->m_strValue;
		}

		pValue = (CValue*)m_pValues->FindByID(strID);

		if (pValue == NULL)
		{
			m_pValues->AddNew(strID, strName, strValue);
		}
		else
		{
			pValue->m_strValue = strValue;
		}
	}

	return TRUE;
}

BOOL CReport::SetReportValues(CShortDatas *pDatas)
{
	if (m_pValues != NULL)
	{
		delete m_pValues;
		m_pValues = NULL;
	}

	m_pValues = pDatas->GetValues();
	AddResultJudgeKey(0);
	AddRptValues_ErrorCal();

	return (m_pValues != NULL);
}

BOOL CReport::AddReportValues(CValues* pValues)
{
	ASSERT (pValues != NULL);
	if(pValues == NULL)
	{
		return FALSE;
	}

	m_pValues->AppendClone(pValues);

	return TRUE;
}

void CReport::AddReportValues(CTags *pTags)
{
	ASSERT (m_pValues != NULL);

	if (m_pValues == NULL)
	{
		return;
	}

	POS pos = pTags->GetHeadPosition();
	CTag *pTag = NULL;
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pTag = (CTag*)pTags->GetNext(pos);
		pValue = (CValue*)m_pValues->FindByID(pTag->m_strID);

		if (pValue == NULL)
		{
			m_pValues->AddValue(pTag->m_strID, pTag->m_strName, pTag->m_strValue);
		}
		else
		{
			pValue->m_strValue = pTag->m_strValue;
		}
	}
}


BOOL CReport::AddReportEx(CShortDatas  *pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);
		AddReportEx(pData);
	}

	return TRUE;
}

BOOL CReport::AddReportEx(CShortData  *pData)
{
	CDvmData *pDvmData = m_pRptDvmDataset->AddNewData();
	
	pDvmData->m_strName = pData->m_strName;
	pDvmData->m_strID = pData->m_strID;
	pDvmData->m_strValue = pData->m_strValue;
	pDvmData->m_strUnit = pData->m_strUnit;
	pDvmData->m_strDataType = pData->m_strDataTypeID;
	pDvmData->m_strFormat = pData->m_strFormat;

	return TRUE;
}
BOOL CReport::AddReport(CShortDatas  *pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);
		AddReport(pData);
	}

	return TRUE;
}

BOOL CReport::AddReport(CShortData  *pData)
{
	CValue *pFind = (CValue*)m_pValues->FindByID(pData->m_strID);

	if (pFind != NULL)
	{
		pFind->m_strValue = pData->m_strValue;
	}
	else
	{
		pFind = m_pValues->AddValue(pData->m_strID, pData->m_strName, pData->m_strValue);
	}

	return TRUE;
}

BOOL CReport::AddReportDataset(CDvmDataset  *pDataset)
{
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CValue *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);
		pFind = (CValue*)m_pValues->FindByID(pData->m_strID);

		if (pFind != NULL)
		{
			pFind->m_strValue = pData->m_strValue;
		}
		else
		{
			pFind = m_pValues->AddValue(pData->m_strID, pData->m_strName, pData->m_strValue);
		}
	}

	return TRUE;
}

BOOL CReport::AppendRptValues(CExBaseList *pListValue)
{
	if (m_pValues == NULL)
	{
		return FALSE;
	}

	m_pValues->AppendEx(*pListValue);
	return TRUE;
}

//报告中，增加几个固定的结果值，用于绑定误差判断的计算值
BOOL CReport::AddRptValues_ErrorCal()
{
	//暂不添加这几个固定的结果值，因为不同的功能，已经定制了结果判断
	return TRUE;

	if (m_pValues == NULL)
	{
		return FALSE;
	}

	if (m_pValues->FindByID(g_strTestResultAbsRsltCal1Key) == NULL)
	{
		m_pValues->AddValue(g_strTestResultAbsRsltCal1Key, _T("未计算"));
	}

	if (m_pValues->FindByID(g_strTestResultAbsRsltCal2Key) == NULL)
	{
		m_pValues->AddValue(g_strTestResultAbsRsltCal2Key, _T("未计算"));
	}

	if (m_pValues->FindByID(g_strTestResultRelRsltCal1Key) == NULL)
	{
		m_pValues->AddValue(g_strTestResultRelRsltCal1Key, _T("未计算"));
	}

	if (m_pValues->FindByID(g_strTestResultRelRsltCal2Key) == NULL)
	{
		m_pValues->AddValue(g_strTestResultRelRsltCal2Key, _T("未计算"));
	}

	return TRUE;
}

CValue* CReport::FindReportData(const CString &strID)
{
	ASSERT (m_pValues != NULL);

	if (m_pValues == NULL)
	{
		return NULL;
	}

	CValue *pVal = (CValue*)m_pValues->FindByID(strID);

	return pVal;
}

CValue* CReport::FindReportData(BSTR strID)
{
	ASSERT (m_pValues != NULL);

	if (m_pValues == NULL)
	{
		return NULL;
	}

	CValue *pVal = (CValue*)m_pValues->FindByID((CString)strID);

	return pVal;
}

BOOL CReport::FindReportData(const CString &strID, long &nValue)
{
	CValue *pValue = (CValue*)FindReportData(strID);

	if (pValue != NULL)
	{
		nValue = CString_To_long(pValue->m_strValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CReport::GetReportValue(const CString &strValueID, double &dValue)
{
	CValue *pVal = NULL;
	BOOL bTrue = FALSE;

	pVal = FindReportData(strValueID);

	if (pVal != NULL)
	{
#ifdef _UNICODE
		dValue = _wtof(pVal->m_strValue);
#else
        dValue = atof(pVal->m_strValue.GetString());
#endif
		bTrue = TRUE;
	}
	else
	{
		//显示：数据不存在
	}

	return bTrue;
}

BOOL CReport::GetReportValue(const CString &strValueID, CString &strValue)
{
	CValue *pVal = NULL;
	BOOL bTrue = FALSE;

	pVal = FindReportData(strValueID);

	if (pVal != NULL)
	{
		strValue = pVal->m_strValue;
		bTrue = TRUE;
	}
	else
	{
		strValue.Empty();
		//显示：数据不存在
	}

	return bTrue;
}

BOOL CReport::GetReportValue(const CString &strValueID, long &nValue)
{
	CValue *pVal = NULL;
	BOOL bTrue = FALSE;

	pVal = FindReportData(strValueID);

	if (pVal != NULL)
	{
#ifdef _UNICODE
		nValue = _wtol(pVal->m_strValue);
#else
        nValue = atol(pVal->m_strValue.GetString());
#endif
		bTrue = TRUE;
	}
	else
	{
		//显示：数据不存在
	}

	return bTrue;
}

BOOL CReport::GetReportValue(const CString &strValueID, char *pszValue)
{
	CValue *pVal = NULL;
	BOOL bTrue = FALSE;

	pVal = FindReportData(strValueID);

	if (pVal != NULL)
	{
		CString_to_char(pVal->m_strValue, pszValue);
		bTrue = TRUE;
	}
	else
	{
		*pszValue = 0;
	}

	return bTrue;
}

//根据数据ID，查找报告的值
//先查找m_pValues里面的，再查找m_pRptDvmDataset
//若是在m_pRptDvmDataset中查找，则需要从strDataID中解析$，查找到对应的属性的部分
BOOL CReport::GetReportValueEx(const CString &strDataID, CString &strValue)
{
	BOOL bFind = FALSE;
	bFind = GetReportValue(strDataID, strValue);

	if (bFind)
	{
		return bFind;
	}

	if (m_pRptDvmDataset == NULL)
	{
		return FALSE;
	}

	CDvmData *pData = (CDvmData*)m_pRptDvmDataset->FindByID(strDataID);

	if (pData != NULL)
	{
		strValue = pData->m_strValue;
		return TRUE;
	}

	CString strAttrID, strID;
	long nPos = strDataID.Find(_T("$"));

	if (nPos < 0)
	{
		return FALSE;
	}

	strAttrID = strDataID.Mid(nPos + 1);
	strID = strDataID.Left(nPos);
	CDvmValue *pValue = FindRptValueByID(strID, strAttrID);

	if (pValue == NULL)
	{
		return FALSE;
	}

	strValue = pValue->m_strValue;
	return TRUE;
}

CDvmValue* CReport::FindRptValueByID(const CString &strDataID, const CString &strAttrID)
{
	if (m_pRptDvmDataset == NULL)
	{
		return NULL;
	}

	CDvmData *pData = (CDvmData*)m_pRptDvmDataset->FindByID(strDataID);

	if (pData == NULL)
	{
		return NULL;
	}

	POS pos = pData->GetHeadPosition();
	CDvmValue *p = NULL;
	CDvmValue *pFind = NULL;
	long nLen = strAttrID.GetLength();

	while (pos != NULL)
	{
		p = (CDvmValue *)pData->GetNext(pos);

		if (p->m_strID.Right(nLen) == strAttrID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

//根据ValueID，遍历扩展报告下所有扩展属性    shaolei  2019.07.27
CDvmValue* CReport::FindRptValueExByValueID(const CString &strValueID)
{
	if (m_pRptDvmDataset == NULL)
	{
		return NULL;
	}

	POS posData = m_pRptDvmDataset->GetHeadPosition();
	POS posValue = NULL;
	CDvmValue *pFind = NULL;
	CDvmValue *pValue = NULL;

	while (posData != NULL)
	{
		CDvmData *pData = (CDvmData *)m_pRptDvmDataset->GetNext(posData);

		posValue = pData->GetHeadPosition();

		while (posValue != NULL)
		{
			pValue = (CDvmValue *)pData->GetNext(posValue);

			if (pValue->m_strID == strValueID)
			{
				pFind = pValue;
				break;;
			}
		}
	}

	return pFind;
}

//shaolei 20211018
CDvmData* CReport::FindRptExDataByDataID(const CString &strDataID)
{
	if (m_pRptDvmDataset == NULL)
	{
		return NULL;
	}

	POS posData = m_pRptDvmDataset->GetHeadPosition();
	CDvmData *pFind = NULL;

	while (posData != NULL)
	{
		CDvmData *pData = (CDvmData *)m_pRptDvmDataset->GetNext(posData);

		if (pData->m_strID == strDataID)
		{
			pFind = pData;
			break;
		}
	}

	return pFind;
}

void CReport::ClearReportDatas()
{
	//m_pRptDvmDataset->DeleteAll();
	
	CValue *pJdg = (CValue*)m_pValues->FindByID(g_strTestResultJudgeKey);
	CValue *pDsc = (CValue*)m_pValues->FindByID(g_strTestResultDescriptKey);
	CValue *pTime = (CValue*)m_pValues->FindByID(g_strTestResultTimeKey);

	m_pValues->Remove(pJdg);
	m_pValues->Remove(pDsc);
	m_pValues->Remove(pTime);
	m_pValues->DeleteAll();

	m_pValues->AddNewChild(pJdg);
	m_pValues->AddNewChild(pDsc);
	m_pValues->AddNewChild(pTime);
}

void CReport::ClearReportDatasByMap()
{
	m_pValues->DeleteAll();
	m_pRptDvmDataset->DeleteAll();
	m_pLogs->DeleteAll();
}

void CReport::GetReportDatasByMap(CExBaseList *pReportMap, CExBaseList *pListDest)
{
    CExBaseList listRptDataMap;
    pReportMap->SelectChildrenByClassIDEx(listRptDataMap, RPTCLASSID_RPTDATA);

    POS pos = m_pValues->GetHeadPosition();
    CValue *pValue = NULL, *pNew = NULL;
    CExBaseObject *pFind = NULL;

    while (pos != NULL)
    {
        pValue = (CValue *)m_pValues->GetNext(pos);
        pFind = listRptDataMap.FindByID(pValue->m_strID);

        if (pFind != NULL)
        {
            pNew = (CValue*)pValue->Clone();
            pNew->m_dwItemData = (DWORD)pFind;
            pListDest->AddNewChild(pNew);
        }
    }

    listRptDataMap.RemoveAll();
}

void CReport::ClearReportDatasByMap(CExBaseList *pReportMap, BOOL bClearValues, UINT nClearSoe)
{
	ClearReportDatasByMap();  //去掉全部的报告数据
	return;
	if (bClearValues)
	{
		CExBaseList listRptDataMap;
		CExBaseList listValues;
		pReportMap->SelectChildrenByClassIDEx(listRptDataMap, RPTCLASSID_RPTDATA);

		POS pos = m_pValues->GetHeadPosition();
		CValue *pValue = NULL;
		POS posPrev = NULL;

		while (pos != NULL)
		{
			posPrev = pos;
			pValue = (CValue *)m_pValues->GetNext(pos);

			if (g_strTestResultJudgeKey == pValue->m_strID
				|| g_strTestResultDescriptKey == pValue->m_strID
				|| g_strTestResultTimeKey == pValue->m_strID)
			{
				listValues.AddTail(pValue);
				m_pValues->RemoveAt(posPrev);
			}
			else
			{
				if (listRptDataMap.FindByID(pValue->m_strID) != NULL)
				{
					listValues.AddTail(pValue);
					m_pValues->RemoveAt(posPrev);
				}
			}
		}

		m_pValues->DeleteAll();
		m_pValues->Append(listValues);
		listValues.RemoveAll();

		listRptDataMap.RemoveAll();
	}
	
	if (nClearSoe == 2)
	{
		m_pRptDvmDataset->DeleteAll();
		m_pLogs->DeleteAll();
	}
	else if (nClearSoe == 1)
	{
		m_pRptDvmDataset->ClearByReserved(RPTEX_QUERY_FLAG_VAL);
		m_pLogs->ClearByReserved(RPTEX_QUERY_FLAG_VAL);
	}
}

void CReport::ClearReportDatasByDsValid(CExBaseList *pReportMap)
{

}

long CReport::GetTestIndex()
{
	long nPos = m_strID.ReverseFind('_');

	if (nPos < 0)
	{
		return 0;
	}

	long nTestIndex = CString_To_long(m_strID.Mid(nPos+1));
	return nTestIndex;
}

void CReport::SetResultJudge(long nResult)
{
	AddResultJudgeKey(nResult);
}

long CReport::GetResultJudge()
{
	if (m_pValues == NULL)
	{
		return 0;
	}

	CValue *pJdg = (CValue*)m_pValues->FindByID(g_strTestResultJudgeKey);

	if (pJdg == NULL)
	{
		return 1;
	}

	return CString_To_long(pJdg->m_strValue);
}

BOOL CReport::IsCalReport()
{
	if (m_strID.GetLength() < 4)
	{
		return FALSE;
	}

	if (m_strID.Left(4) == g_pszCalReportKey)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CReport::IsCalReportEx()
{
	long nPos1=0, nPos2=0;
	nPos1 = m_strID.ReverseFind('_');

	if (nPos1 <= 0)
	{
		return FALSE;
	}

	CString strMax = m_strID.Mid(nPos1+1);
	CString strLeft = m_strID.Left(nPos1);
	nPos2 = strLeft.ReverseFind('_');

	if (nPos2 <= 0)
	{
		return FALSE;
	}

	CString strIndex = strLeft.Mid(nPos2+1);

	return (strMax == strIndex);
}

void CReport::SetCalReport()
{
	if (IsCalReport())
	{
		return;
	}

	m_strID = g_pszCalReportKey + m_strID;
}

void CReport::DeleteRptValues()
{
	if (m_pValues == NULL)
	{
		return;
	}

	m_pValues->DeleteAll();
}

CValue* CReport::AddValue(BSTR bstrID)
{
	CValue *pVal = NULL;

	if (m_pValues == NULL)
	{
		m_pValues = new CValues();
	}

	CString strID;
	strID = bstrID;
	pVal = m_pValues->AddNew(strID, _T(""), _T(""));

// 	if (pVal != NULL)
// 	{
// 		pVal->m_strID = bstrID;
// 	}

	return pVal;
}

CValue* CReport::AddValue(const CString &strID, const CString &strValue)
{
	CValue *pVal = NULL;

	if (m_pValues == NULL)
	{
		m_pValues = new CValues();
	}

	pVal = m_pValues->AddNew(strID, _T(""), strValue);
// 	pVal->m_strID = strID;
// 	pVal->m_strValue = strValue;

	return pVal;
}

CValue* CReport::AddValue(BSTR bstrID, BSTR bstrName)
{
	CValue *pVal = NULL;

	if (m_pValues == NULL)
	{
		m_pValues = new CValues();
	}

	CString strID, strName;
	strID = bstrID;
	strName = bstrName;

	pVal = m_pValues->AddNew(strID, strName, _T(""));
// 	if (pVal != NULL)
// 	{
// 		pVal->m_strID = bstrID;
// 	}

	return pVal;
}

CValue* CReport::AddValue(const CString &strID, const CString &strName, const CString &strValue)
{
	CValue *pVal = NULL;

	if (m_pValues == NULL)
	{
		m_pValues = new CValues();
	}

	pVal = m_pValues->AddNew(strID, strName, strValue);
// 	pVal->m_strID = strID;
// 	pVal->m_strValue = strValue;

	return pVal;
}

BOOL CReport::SetValue(const CString &strValueID,const CString &strValue)
{
	CValue *pVal = FindReportData(strValueID);

	if (pVal != NULL)
	{
		pVal->m_strValue = strValue;
		return TRUE;
	}
	else
	{
		//显示：数据不存在
		return FALSE;
	}
}

//重写父类方法
long CReport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strBeginTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strEndTime);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strBeginTime);
		BinarySerializeRead(oBinaryBuffer, m_strEndTime);
		m_pValues->DeleteAll();
		m_pRptDvmDataset->DeleteAll();
		m_pLogs->DeleteAll();
	}
	else
	{
		BinarySerializeWrite(oBinaryBuffer, m_strBeginTime);
		BinarySerializeWrite(oBinaryBuffer, m_strEndTime);
	}

	 if (oBinaryBuffer.IsReadMode())
	 {
		 m_pValues->Serialize(oBinaryBuffer);
		 m_pRptDvmDataset->Serialize(oBinaryBuffer);
	 }
	 else
	 {
		 if (m_pValues != NULL)
		 {
			 m_pValues->Serialize(oBinaryBuffer);
		 }

		 if (m_pRptDvmDataset != NULL)
		 {
			 m_pRptDvmDataset->Serialize(oBinaryBuffer);
		 }
	 }

	 if (oBinaryBuffer.IsReadMode())
	 {
		 if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_31)
		 {
			 m_pLogs->Serialize(oBinaryBuffer);
		 }

		 InitAfterSerializeOwn();
	 }
	 else
	 {
		 if (m_pLogs != NULL)
		 {
			  m_pLogs->Serialize(oBinaryBuffer);
		 }
	 }

	return 0;
}

long CReport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);
	
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strBeginTimeKey,oNode,m_strBeginTime);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strEndTimeKey,oNode,m_strEndTime);

	CXmlRWNodeListBase *oNodes = oNode.GetChildNodes();
	long nCount = oNodes->GetNodeNum();
	long nIndex = 0;
	CXmlRWNodeBase *oNodeChild = NULL;
	CString strNodeName;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oNodeChild = oNodes->GetChild(nIndex);
		CString strNodeName =  oNodeChild->GetNodeName();

		if (strNodeName == CGbXMLKeys::g_pGbXMLKeys->CValuesKey())
		{
			ASSERT (m_pValues != NULL);
			m_pValues->DeleteAll();
			m_pValues->XmlRead(*oNodeChild, CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys);
		}
		else if (strNodeName == CGbXMLKeys::g_pGbXMLKeys->CDvmDatasetKey()
			|| strNodeName == CGbXMLKeys::g_pGbXMLKeys->CDvmDatasetGroupKey())
		{
			ASSERT (m_pRptDvmDataset != NULL);
			m_pRptDvmDataset->DeleteAll();
			m_pRptDvmDataset->XmlRead(*oNodeChild, CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys);
		}
	}

	return 0;
}

long CReport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strBeginTimeKey,oElement,m_strBeginTime);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strEndTimeKey,oElement,m_strEndTime);

	ASSERT(m_pValues != NULL);
	m_pValues->XmlWrite(oXMLDoc, oElement, CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys);

	ASSERT(m_pRptDvmDataset != NULL);
	if (m_pRptDvmDataset->GetCount() > 0)
	{
		m_pRptDvmDataset->XmlWrite(oXMLDoc, oElement, CGbXMLKeys::g_pGbXMLKeys);
	}

	ASSERT(m_pLogs != NULL);
	if (m_pLogs->GetCount() > 0)
	{
		m_pLogs->XmlWrite(oXMLDoc, oElement, CGbXMLKeys::g_pGbXMLKeys);
	}

	return 0;
}

BSTR CReport::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strReportKey;
}

void CReport::AddResultJudgeKey(long nResult)
{
	ASSERT (m_pValues != NULL);
	if (m_pValues == NULL)
	{
		return;
	}

	Gb_AddResultJudgeKey(m_pValues, nResult);
}

BOOL CReport::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if(pDest == this)
		return TRUE;

	CExBaseObject::CopyOwn(pDest);

	CReport* pReport = (CReport*)pDest;
	pReport->m_strBeginTime = m_strBeginTime;
	pReport->m_strEndTime = m_strEndTime;

	if(pReport->m_pValues != NULL)
	{
		delete pReport->m_pValues;
		pReport->m_pValues = NULL;
	}
	
	if(pReport->m_pRptDvmDataset != NULL)
	{
		delete pReport->m_pRptDvmDataset;
		pReport->m_pRptDvmDataset = NULL;
	}

	if(pReport->m_pLogs != NULL)
	{
		delete pReport->m_pLogs;
		pReport->m_pLogs = NULL;
	}

	pReport->m_pValues = (CValues*)m_pValues->Clone();
	pReport->m_pRptDvmDataset = (CDvmDatasetGroup *)m_pRptDvmDataset->Clone();
	pReport->m_pLogs = (CDvmLogs *)m_pLogs->Clone();

	return TRUE;
}

CBaseObject* CReport::Clone()
{
	CReport* pReport = new CReport();
	Copy(pReport);

	return pReport;
}

CBaseObject* CReport::CloneEx(BOOL bCopyOwn/*=TRUE*/,BOOL bCopyChildren/*=FALSE*/)
{
	CReport *p = new CReport();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CReport::GetReportExValue(long nIndex, const CString &strValueID, CString &strValue)
{
	CDvmData* pData = (CDvmData*)m_pRptDvmDataset->GetAtIndex(nIndex);
	BOOL bTrue = FALSE;

	if (pData != NULL)
	{
		bTrue = pData->GetValueByID(strValueID, strValue);
	}

	return bTrue;
}

BOOL CReport::GetReportExValue(const CString &strDataID, const CString &strValueID, CString &strValue)
{
	CDvmData* pData = (CDvmData*)m_pRptDvmDataset->FindByID(strDataID);
	BOOL bTrue = FALSE;

	if (pData != NULL)
	{
		bTrue = pData->GetValueByID(strValueID, strValue);
	}

	return bTrue;
}

CString CReport::GetLastRcdFile()
{
	POS pos = m_pRptDvmDataset->GetTailPosition();
	CDvmData *pData = NULL;
	CString strFile;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pRptDvmDataset->GetPrev(pos);
		strFile = pData->m_strID.Right(4);
		strFile.MakeLower();

		if (strFile == _T(".cfg") || strFile == _T(".dat"))
		{
			return pData->m_strID;
		}
	}

	return _T("");
}

#include "GbItemBase.h"
void CReport::InitAfterSerializeOwn()
{
	//串行化打开时，报告数据是没有名称的，此处重新初始化报告数据的name属性
	if (m_pValues == NULL)
	{
		return;
	}

	Gb_AtsInitReport_Name(this);
}

void CReport::CalChildrenSize(BOOL bCalChild, long &nObjCount, long &nTotalSize, CFile *pFile)
{

	if (m_pValues != NULL)
	{
#ifdef _DEBUG
        m_pValues->m_strName.Format(_T("%s:Values"), m_strName.GetString());
        m_pValues->m_strID.Format(_T("%s:Values"), m_strID.GetString());
#endif
		m_pValues->CalObjSize(bCalChild, nObjCount, nTotalSize, pFile);
	}

	if (m_pRptDvmDataset != NULL)
	{
#ifdef _DEBUG
        m_pRptDvmDataset->m_strName.Format(_T("%s:RptDvmDataset"), m_strName.GetString());
        m_pRptDvmDataset->m_strID.Format(_T("%s:RptDvmDataset"), m_strID.GetString());
#endif
		m_pRptDvmDataset->CalObjSize(bCalChild, nObjCount, nTotalSize, pFile);
	}

	if (m_pLogs != NULL)
	{
#ifdef _DEBUG
        m_pLogs->m_strName.Format(_T("%s:Logs"), m_strName.GetString());
        m_pLogs->m_strID.Format(_T("%s:Logs"), m_strID.GetString());
#endif
		m_pLogs->CalObjSize(bCalChild, nObjCount, nTotalSize, pFile);
	}
}

void CReport::ClearItemInDbState()
{
	m_pValues->DeleteAll();
	m_pRptDvmDataset->DeleteAll();
	m_pLogs->DeleteAll();

// 	if (m_pValues != NULL)
// 	{
// 		delete m_pValues;
// 		m_pValues = NULL;
// 	}
// 
// 	if (m_pRptDvmDataset != NULL)
// 	{
// 		delete m_pRptDvmDataset;
// 		m_pRptDvmDataset = NULL;
// 	}
// 
// 	if (m_pLogs != NULL)
// 	{
// 		delete m_pLogs;
// 		m_pLogs = NULL;
// 	}
}

void CReport::AddRptDvmDataset(CDvmDataset *pDvmDataset)
{
	m_pRptDvmDataset->AppendCloneEx(*pDvmDataset);
}

void CReport::AddRptDvmDataset(CDvmDataset &oDvmDataset)
{
	AddRptDvmDataset(&oDvmDataset);
}

void CReport::AddRptDvmDataset(CExBaseList &oDataList)
{
	m_pRptDvmDataset->AppendCloneEx(oDataList);
}

void CReport::InitValues(CDvmValues *pSrc)
{
	if (m_pValues == NULL)
	{
		m_pValues = new CValues();
	}

	if (pSrc != NULL)
	{
		POS pos = pSrc->GetHeadPosition();

		while (pos != NULL)
		{
			CDvmValue *pValue = (CDvmValue *)pSrc->GetNext(pos);
			CValue *pFind = (CValue *)m_pValues->FindByID(pValue->m_strID);

			if (pFind == NULL)
			{
			m_pValues->AddValue(pValue->m_strID, pValue->m_strName, pValue->m_strValue);
		}
			else
			{
				pFind->m_strValue = pValue->m_strValue;
				pFind->m_strName = pValue->m_strName;
			}
		}
	}
}

void CReport::InitRptDvmDataset(CDvmDataset *pSrc)
{
	if (m_pRptDvmDataset == NULL)
	{
		m_pRptDvmDataset = new CDvmDatasetGroup();
	}

	m_pRptDvmDataset->AppendCloneEx(*pSrc);
}
