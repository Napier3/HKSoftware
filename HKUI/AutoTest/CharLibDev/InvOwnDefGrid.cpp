// InvOwnDefGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "InvOwnDefGrid.h"

#define ATS_INVOWNDEF_GRID_COLS      3

// CInvOwnDefGrid
CInvOwnDefGrid::CInvOwnDefGrid()
{
	m_nAdjustBeginCol = 1;
}

CInvOwnDefGrid::~CInvOwnDefGrid()
{
}

void CInvOwnDefGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(ATS_INVOWNDEF_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CInvOwnDefGrid::InitGridTitle()
{
	CString astrGridTitle[ATS_INVOWNDEF_GRID_COLS] = {_T("编号"),_T("x"),_T("y")};
	int iGridWidth[ATS_INVOWNDEF_GRID_COLS]={60, 60, 60};

	SetColumnCount(ATS_INVOWNDEF_GRID_COLS);
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, ATS_INVOWNDEF_GRID_COLS);
}

void CInvOwnDefGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	CCharElementPoint *pPoint = (CCharElementPoint *)pData;

	Show_Index(pPoint, nRow, 0);//编号

	Show_Double(pPoint, nRow, 1, &(pPoint->m_fX), TRUE, _T(""), NULL, FALSE);
	Show_Double(pPoint, nRow, 2, &(pPoint->m_fY), TRUE, _T(""), NULL, FALSE);

	nRow++;
}
