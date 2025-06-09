//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GridCharElement.cpp  CGridCharElementDev


#include "stdafx.h"
#include "GridCharElement.h"

#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGridCharElementDev::CGridCharElementDev()
{
	//初始化属性
	m_bViewElementDetail = TRUE;

	//初始化成员变量
}

CGridCharElementDev::~CGridCharElementDev()
{

}


void CGridCharElementDev::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);

	if (m_bViewElementDetail)
	{
		SetColumnCount(CHARELEMENT_COLS);
	}
	else
	{
		SetColumnCount(CHARELEMENT_COLS-1);
	}

	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridCharElementDev::InitGridTitle()
{
	CString astrSclIecCfgTitleGIn[CHARELEMENT_COLS] = {g_sLangTxt_Index/*_T("编号")*/,g_sLangTxt_EdgeType/*_T("边类型")*/,g_sLangTxt_TestPoint/*_T("测点数")*/,g_sLangTxt_ErrorBand/*_T("误差带")*/,g_sLangTxt_EdgeDetails/*_T("边详细信息")*/};

	int iSclIecCfgWidthGin[CHARELEMENT_COLS]={40,80,80,80, 200};

	if (m_bViewElementDetail)
	{
		CExBaseListGrid::InitGridTitle(astrSclIecCfgTitleGIn, iSclIecCfgWidthGin, CHARELEMENT_COLS);
	}
	else
	{
		CExBaseListGrid::InitGridTitle(astrSclIecCfgTitleGIn, iSclIecCfgWidthGin, CHARELEMENT_COLS-1);
	}
}

void CGridCharElementDev::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharElement *pElement = (CCharElement*)pData;

	Show_Index(pElement, nRow, CHARELEMENT_COL_INDEX);
	Show_StaticString(pElement, nRow, CHARELEMENT_COL_TYPE, &pElement->m_strName);

	Show_Long(pElement, nRow, CHARELEMENT_COL_POINTS, pElement->GetTestPointsRef(), TRUE, _T(""), EndEditCell_TestPoints);
	Show_String(pElement, nRow, CHARELEMENT_COL_ERROR, &pElement->m_strErrLength, EndEditCell_ErrorLength);

	if (m_bViewElementDetail)
	{
		Show_StaticString(pElement, nRow, CHARELEMENT_COL_DETAIL, pElement->ReturnXml());
		SetItemFormat(nRow, CHARELEMENT_COL_DETAIL, DT_LEFT);
	}

	nRow++;
}


void CGridCharElementDev::EndEditCell_TestPoints(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pString != NULL);
	ASSERT (pVellData->nVt == VCD_LONG);

	if (pVellData->nVt != VCD_LONG)
	{
		return;
	}

	long nValue =  CString_To_long(pCell->szText);

	if (nValue != *(pVellData->pnValue))
	{
		*(pVellData->pnValue) = nValue;
		pCell->szText.Format(_T("%d"), *(pVellData->pnValue));
		pGrid->RedrawCell(nRow, nCol);
		CCharElement *pCharElement = (CCharElement*)pVellData->pObj;
		pCharElement->SetTestPoint(nValue);
		pCharElement->CalByExpression(TRUE, NULL);
		char_dev_SetModifiedFlag(pCharElement, TRUE);

		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(pGrid, nRow, nCol);
	}
}


void CGridCharElementDev::EndEditCell_ErrorLength (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

	if (*pVCellData->pString == pCell->szText)
	{
		return;
	}

	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	*pVCellData->pString = pCell->szText;

// 	if (((CExBaseListGrid*)pGrid)->GetAdjustBeginCol() >= 0)
// 	{
// 		pGrid->AutoSizeColumn(nCol);
// 		pGrid->ResetScrollBars();
// 		pGrid->InvalidateGrid(FALSE);
// 	}

	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(pGrid, nRow, nCol);
}

