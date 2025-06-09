#include "StdAfx.h"
#include "DvmDsRptListCtrl.h"
#include "..\XLanguageResourceAts_AutoTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDvmDsRptListCtrl::CDvmDsRptListCtrl(void)
{
	
}


CDvmDsRptListCtrl::~CDvmDsRptListCtrl(void)
{
	
}

void CDvmDsRptListCtrl::InitListHeader()
{
	InsertColumn(0,g_sLangTxt_Index/*_T("编号")*/,LVCFMT_LEFT,40);
	InsertColumn(1,g_sLangTxt_Name/*_T("名称")*/,LVCFMT_LEFT,200);
	InsertColumn(2,_T("ID/Path"),LVCFMT_LEFT,220);
	InsertColumn(3,g_sLangTxt_Type/*_T("类型")*/,LVCFMT_LEFT,80);
	InsertColumn(4,g_sLangTxt_Data/*_T("数据")*/,LVCFMT_LEFT,140);
}

void CDvmDsRptListCtrl::ShowDvmDataset(CDvmDataset *pDvmDataset)
{
	LockWindowUpdate();
	SetRedraw(FALSE);
	DeleteAllItems();

	long nDataCount = pDvmDataset->GetCount();
	long nDataIndex = 0;

	if (nDataCount == 0)
	{
		UnlockWindowUpdate();
		SetRedraw(TRUE);
		return;
	}

	POS pos = pDvmDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	long nRowIndex = 0;

	while (pos != NULL)
	{
		CExBaseObject *pObj = pDvmDataset->GetNext(pos);
		UINT nClassID = pObj->GetClassID();

#ifdef exbase_not_use_m_dwReserved
		if (pObj->m_dwItemData == 0)
#else
		if (pObj->m_dwReserved == 0)
#endif
		{
			continue;
		}

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData *)pObj;
		ShowDvmData(nRowIndex, pData, nDataIndex);

		nRowIndex++;
		nDataIndex++;
	}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup *)pObj;
			ShowDvmDatasetGroup(nRowIndex, pDatasetGroup, nDataIndex);
		}
	}

	UnlockWindowUpdate();
	SetRedraw(TRUE);
}

void CDvmDsRptListCtrl::ShowDvmData(long &nRow, CDvmData *pData, long nDataIndex)
{
	CString strText;
	strText.Format(_T("%d"), nDataIndex+1);
	InsertItem(nRow, strText);
	SetItemText(nRow, 1, pData->m_strName);
	SetItemText(nRow, 2, pData->m_strID);
	SetItemText(nRow, 3, pData->m_strDataType);
	SetItemText(nRow, 4, pData->m_strValue);

	POS pos = pData->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CString strValTitle;
	long nCol = 0;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pData->GetNext(pos);

		if (!CanShowDvmValue(pValue))
		{
			continue;
		}

		strValTitle = GetValueTitle(pData, pValue);

		nRow++;
		InsertItem(nRow, _T(""));
		SetItemText(nRow, 1, pValue->m_strName);
		SetItemText(nRow, 2, pValue->m_strID);
		SetItemText(nRow, 3, pValue->m_strDataType);
		SetItemText(nRow, 4, pValue->m_strValue);

		ShowDvmDataValues(nRow, pValue, 1);
	}
}

void CDvmDsRptListCtrl::ShowDvmDatasetGroup(long &nRow, CDvmDatasetGroup *pDatasetGroup, long &nDataIndex)
{
	POS pos = pDatasetGroup->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		CExBaseObject *pObj = pDatasetGroup->GetNext(pos);
		UINT nClassID = pObj->GetClassID();

#ifdef exbase_not_use_m_dwReserved
		if (pObj->m_dwItemData == 0)
#else
		if (pObj->m_dwReserved == 0)
#endif
		{
			continue;
		}

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			pData = (CDvmData *)pObj;
			ShowDvmData(nRow, pData, nDataIndex);
			nRow++;
			nDataIndex++;
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup *)pObj;
			ShowDvmDatasetGroup(nRow, pDatasetGroup, nDataIndex);
		}
	}
}

BOOL CDvmDsRptListCtrl::CanShowDvmValue(CDvmValue *pValue)
{
#ifdef exbase_not_use_m_dwReserved
	return (pValue->m_dwItemData != 0);
#else
	return (pValue->m_dwReserved != 0);
#endif
}

void CDvmDsRptListCtrl::ShowDvmDataValues(long &nRow, CExBaseList *pValues, long nLevel)
{
	POS pos = pValues->GetHeadPosition();
	CDvmValue *pValue = NULL;
	CString strValTitle;
	long nCol = 0;
	CString strLevel;
	TCHAR chVal = 0;

	for (long nIndex=0; nIndex<nLevel; nIndex++)
	{
		strLevel += _T("----");
	}

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pValues->GetNext(pos);

		if (!CanShowDvmValue(pValue))
		{
			continue;
		}

		GetValueTitle2(pValues, pValue, strValTitle);
		strValTitle = strLevel + strValTitle;

		nRow++;
		InsertItem(nRow, _T(""));
		chVal = pValue->m_strDataType.GetAt(0);

		if (chVal == 'S' || chVal == 'A')
		{
			SetItemText(nRow, 1, strLevel + pValue->m_strID);
		}

		SetItemText(nRow, 2, strValTitle);
		SetItemText(nRow, 3, pValue->m_strDataType);
		SetItemText(nRow, 4, pValue->m_strValue);

		ShowDvmDataValues(nRow, pValue, nLevel+1);
	}
}


void CDvmDsRptListCtrl::GetValueTitle2(CExBaseObject *pParent, CDvmValue *pValue, CString &strValTitle)
{
	if (pValue->m_strID.GetAt(pValue->m_strID.GetLength()-1) == '$')
	{
		strValTitle = pValue->m_strID;
	}
	else
	{
		if (pParent->m_strID.GetAt(pParent->m_strID.GetLength()-1) == '$')
		{
			strValTitle = pValue->m_strID.Mid(pParent->m_strID.GetLength());
		}
		else
		{
			strValTitle = pValue->m_strID.Mid(pParent->m_strID.GetLength() + 1);
		}
	}
}

CString CDvmDsRptListCtrl::GetValueTitle(CDvmData *pData, CDvmValue *pValue)
{
	CString strValTitle;
	strValTitle = pValue->m_strID;
	strValTitle.Replace(pData->m_strID, _T(""));
	return strValTitle;
}


//////////////////////////////////////////////////////////////////////////
//CValuesRptListCtrl
CValuesRptListCtrl::CValuesRptListCtrl()
{
	m_pCurrMacro = NULL;
}

CValuesRptListCtrl::~CValuesRptListCtrl()
{

}

void CValuesRptListCtrl::InitListHeader()
{
	CRect rc;
	GetClientRect(rc);
	long nWidth = (rc.Width() - 15) / 2 ;
	InsertColumn(0, _T("ID"), LVCFMT_LEFT, nWidth);
	InsertColumn(1, g_sLangTxt_Data/*L"数据"*/, LVCFMT_LEFT, nWidth);
}

void CValuesRptListCtrl::ShowValues(CValues *pValues, BOOL bIsItemMacroTest)
{
	m_pCurrMacro = NULL;

	CValue * pValue = NULL;
	long nCount = pValues->GetCount();
	long nIndex = 0;
	long nRows = GetItemCount();
	CString strValue;

	if (nRows > nCount)
	{
		long nDeleteRows = nRows-nCount;

		for (nIndex=0; nIndex<nDeleteRows; nIndex++)
		{
			DeleteItem(nCount);
		}
	}
	else if (nCount > nRows)
	{
		long nAddRows = nCount - nRows;

		for (nIndex=0; nIndex<nAddRows; nIndex++)
		{
			InsertItem(nRows+nIndex, _T(""));
		}
	}

	if (bIsItemMacroTest)
	{
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			pValue = (CValue*)pValues->GetAtIndex(nIndex);
			//SetItemText(nIndex, 0, oValue->m_strID);
			strValue = pValue->m_strValue;
			ChopFloatString(strValue, -1);
			SetItemText(nIndex, 1, strValue);//oValue->m_strValue);
			SetItemData(nIndex, (DWORD)pValue);
		}
	}
	else
	{
		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			pValue = (CValue*)pValues->GetAtIndex(nIndex);
			SetItemText(nIndex, 0, pValue->m_strID);
			strValue = pValue->m_strValue;
			ChopFloatString(strValue, -1);
			SetItemText(nIndex, 1, strValue);//oValue->m_strValue);
			SetItemData(nIndex, (DWORD)pValue);
		}
	}
}

void CValuesRptListCtrl::UpdateParasName(CTestMacro *pCurrMacro)
{
	m_pCurrMacro = pCurrMacro;

	if (pCurrMacro == NULL)
	{
		return;
	}

	long nIndex = 0;
	long nRows = GetItemCount();
	CValue *pValue = NULL;
	CShortData *pData = NULL;

	for (nIndex=0; nIndex<nRows; nIndex++)
	{
		pValue = (CValue *)GetItemData(nIndex);
		pData = FindMacroPara(pValue);

		if (pData != NULL)
		{
			SetItemText(nIndex, 0, pData->m_strName);
		}
		else
		{
			SetItemText(nIndex, 0, pValue->m_strID);
		}
	}
}

CExBaseObject* CValuesRptListCtrl::FindPara(CValue *pValue, CExBaseList *pDatasRef, CExBaseList *pDatasRef2)
{
	CExBaseObject *pFind = pDatasRef->FindByID(pValue->m_strID);

	if (pFind == NULL)
	{
		if (pDatasRef2 != NULL)
		{
			pFind = pDatasRef2->FindByID(pValue->m_strID);
		}
	}

	return pFind;
}

void CValuesRptListCtrl::UpdateParasName(CExBaseList *pDatasRef, CExBaseList *pDatasRef2)
{
	long nIndex = 0;
	long nRows = GetItemCount();
	CValue *pValue = NULL;
	CExBaseObject *pData = NULL;

	for (nIndex=0; nIndex<nRows; nIndex++)
	{
		pValue = (CValue *)GetItemData(nIndex);
		pData = FindPara(pValue, pDatasRef, pDatasRef2);

		if (pData != NULL)
		{
			SetItemText(nIndex, 0, pData->m_strName);
		}
	}
}

CShortData* CValuesRptListCtrl::FindMacroPara(CValue *pValue)
{
	ASSERT (m_pCurrMacro != NULL);

	CShortData *pData = (CShortData*)m_pCurrMacro->GetFaultParas()->FindByID(pValue->m_strID);

	if (pData != NULL)
	{
		return pData;
	}

	pData = (CShortData*)m_pCurrMacro->GetSysParas()->FindByID(pValue->m_strID);

	if (pData != NULL)
	{
		return pData;
	}

	pData = (CShortData*)m_pCurrMacro->GetResults()->FindByID(pValue->m_strID);

	if (pData != NULL)
	{
		return pData;
	}

	return pData;
}

//////////////////////////////////////////////////////////////////////////
//CLogsRptListCtrl
CLogsRptListCtrl::CLogsRptListCtrl(void)
{

}

CLogsRptListCtrl::~CLogsRptListCtrl(void)
{

}

void CLogsRptListCtrl::InitListHeader()
{
	InsertColumn(0,g_sLangTxt_Index/*_T("编号")*/,LVCFMT_LEFT,40);
	InsertColumn(1,_T("entry_id"),LVCFMT_LEFT,130);
	InsertColumn(2,g_sLangTxt_Time,LVCFMT_LEFT,140);
	InsertColumn(3,g_sLangTxt_DataSets,LVCFMT_LEFT,120);
}

void CLogsRptListCtrl::ShowLogs(CDvmLogs *pLogs)
{
	ShowBaseList(pLogs);
}

