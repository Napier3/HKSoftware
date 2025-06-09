#include "StdAfx.h"
#include "XrioParameterGrid.h"

#include "..\XrioCustomParameter.h"

CXrioParameterGrid::CXrioParameterGrid(void)
{
//	m_nAdjustBeginCol = 0;
}

CXrioParameterGrid::~CXrioParameterGrid(void)
{
}

void CXrioParameterGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(XRIO_PARAMETER_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CXrioParameterGrid::InitGridTitle()
{
	CString cTempStr[XRIO_PARAMETER_GRID_COLS]={_T("序号"),_T("参数ID"),_T("名称"),_T("描述"),_T("值"),_T("单位")};

	int iWidth[XRIO_PARAMETER_GRID_COLS]={60,80,80,80,80,80};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, XRIO_PARAMETER_GRID_COLS);
}


void CXrioParameterGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != XRIOCLASSID_CUSTOMPARAMETER)
	{
		return;
	}

	Show_Index(pData, nRow, 0);
	CString strTmp;

	CXrioCustomParameter *pXrioParameter = (CXrioCustomParameter*)pData;
	pXrioParameter->GetParameterFullPath(strTmp);
	Show_StaticString(pData, nRow, 1, &strTmp);
	Show_StaticString(pData, nRow, 2, &pXrioParameter->m_strName);
	Show_StaticString(pData, nRow, 3, &pXrioParameter->m_strDescription);
	pXrioParameter->GetParameterValue(strTmp);
	Show_StaticString(pData, nRow, 4, &strTmp);
	Show_StaticString(pData, nRow, 5, &pXrioParameter->m_strUnit);

	nRow++;
}

void CXrioParameterGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	m_idCurrentCell.col = -1;
	m_idCurrentCell.row = -1;
	ClearSelect();
	CTLinkList <_ExBaseCellData> listVCellData;
	BackListCellData(listVCellData);
	//m_listVCellData.DeleteAll();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(1);
		return;
	}

	if (pDatas->GetCount()>1000)
	{
		SetRowCount(1);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 1;
	long nCalRows = GetDatasCount() + 1;//pDatas->GetCount() + 1;
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}