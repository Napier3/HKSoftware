// RemoteScan_TestAppGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteScan_TestAppGrid.h"
#include "../../../Module/SttAuthority/SttTestRemoteRegister.h"

#define ATS_TESTAPP_REMOTESEARCH_GRID_COLS       5

// CRemoteScan_TestAppGrid
CRemoteScan_TestAppGrid::CRemoteScan_TestAppGrid()
{
	m_nAdjustBeginCol = 1;
}

CRemoteScan_TestAppGrid::~CRemoteScan_TestAppGrid()
{
}

void CRemoteScan_TestAppGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(ATS_TESTAPP_REMOTESEARCH_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CRemoteScan_TestAppGrid::InitGridTitle()
{
	CString astrGridTitle[ATS_TESTAPP_REMOTESEARCH_GRID_COLS] = {_T("编号"),_T("单位"),_T("姓名"),_T("测试仪型号"),_T("测试仪编号")};
	int iGridWidth[ATS_TESTAPP_REMOTESEARCH_GRID_COLS]={60, 120, 120, 120, 120};

	SetColumnCount(ATS_TESTAPP_REMOTESEARCH_GRID_COLS);
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, ATS_TESTAPP_REMOTESEARCH_GRID_COLS);

	SetFont(g_pGlobalFont14);
}

void CRemoteScan_TestAppGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	CSttTestRemoteRegister *pRegister = (CSttTestRemoteRegister *)pData;

	Show_Index(pRegister, nRow, 0);//编号

	Show_StaticString(pRegister, nRow, 1, &pRegister->Name_Cop());		//单位
	Show_StaticString(pRegister, nRow, 2, &pRegister->Name_User());		//用户
	Show_StaticString(pRegister, nRow, 3, &pRegister->Model_TestApp());	
	Show_StaticString(pRegister, nRow, 4, &pRegister->SN_TestApp());

	nRow++;
}
