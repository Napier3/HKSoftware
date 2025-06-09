//GridTestMacro.cpp
#include "stdafx.h"
#include "GridTestMacro.h"

CGridTestMacro::CGridTestMacro()
{
	//初始化属性

	//初始化成员变量
	m_nAdjustBeginCol = 1;
}

CGridTestMacro::~CGridTestMacro()
{

}


void CGridTestMacro::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);

	SetColumnCount(TESTMCACRO_COLS);

	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridTestMacro::InitGridTitle()
{
	CString strGridTitle[TESTMCACRO_COLS] = {_T("编号"), _T("Ats功能名称") ,_T("Ats功能ID")};
	int  iColType[TESTMCACRO_COLS]={GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT};
	int iGridWidth[TESTMCACRO_COLS]={40,150,150};
	CExBaseListGrid::InitGridTitle(strGridTitle, iGridWidth, TESTMCACRO_COLS);
}

void CGridTestMacro::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CTestMacros *pTestMacro = (CTestMacros*)pData;

	Show_Index(pTestMacro, nRow, 0);
	Show_StaticString(pTestMacro, nRow, 1, &pTestMacro->m_strName);
	Show_StaticString(pTestMacro, nRow, 2, &pTestMacro->m_strID);
	
	nRow++;
}

void CGridTestMacro::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	CTestMacro* pTestMacro = (CTestMacro*) GetData(nRow, nCol);

	if (pTestMacro == NULL)
	{
		return;
	}

	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}

	m_pMsgRcvWnd->PostMessage(WM_MACRO_MAP, (WPARAM)pTestMacro, (LPARAM)pTestMacro);

}