#include "StdAfx.h"
#include "GridiDetailInfoReportWzd.h"

CGridiDetailInfoReportWzd::CGridiDetailInfoReportWzd(void)
{
}

CGridiDetailInfoReportWzd::~CGridiDetailInfoReportWzd(void)
{
}

void CGridiDetailInfoReportWzd::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(RECORD_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CGridiDetailInfoReportWzd::InitGridTitle()
{
	CString astrGridTitle[RECORD_TABLE_COLS] = {_T("Ãû³Æ"),_T("Êý¾Ý")};
	int iGridWidth[RECORD_TABLE_COLS]={180, 180};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, RECORD_TABLE_COLS);
}

void CGridiDetailInfoReportWzd::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	if(pData->GetClassID() == DTMCLASSID_CVALUE)
	{
		CValue* pValue = (CValue*)pData;

		if (pValue->m_strName.GetLength() > 0)
		{
			Show_StaticString(pValue, nRow, 0, &pValue->m_strName);
		}
		else
		{
			Show_StaticString(pValue, nRow, 0, &pValue->m_strID);
		}
		
		Show_StaticString(pValue, nRow, 1, &pValue->m_strValue);
	}
	else if(pData->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		CDvmData* pDvmData = (CDvmData*)pData;

		if (pDvmData->m_strName.GetLength() > 0)
		{
			Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strName);
		}
		else
		{
			Show_StaticString(pDvmData, nRow, 0, &pDvmData->m_strID);
		}
		
		Show_StaticString(pDvmData, nRow, 1, &pDvmData->m_strValue);
	}

	nRow++;
}

void CGridiDetailInfoReportWzd::ShowDatas(CExBaseList *pDataList, BOOL bInsertRow)
{
	if (pDataList == NULL)
	{
		SetRowCount(1);
		return;
	}

	POS pos = pDataList->GetHeadPosition();
	int nRowIndex = 1;
	CExBaseObject *pObj = NULL;
	long nCalRows = pDataList->GetCount() + 1;
	SetRowCount(nCalRows, bInsertRow);

	while (pos != NULL)
	{
		pObj = pDataList->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bInsertRow);
	AfterShowDatas(1, bInsertRow);
	
	//SortTextItems(SORT_TABLE_COLS, false);
}
