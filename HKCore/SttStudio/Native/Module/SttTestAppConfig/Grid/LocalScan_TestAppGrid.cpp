// LocalScan_TestAppGrid.cpp : ÊµÏÖÎÄ¼þ
//

#include "stdafx.h"
#include "LocalScan_TestAppGrid.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/SttGlobalDef.h"
#include "../../../Module/SttCmd/SttParas.h"

#define ATS_TESTAPP_LOCALSEARCH_GRID_COLS       4

// CLocalScan_TestAppGrid
CLocalScan_TestAppGrid::CLocalScan_TestAppGrid()
{
	m_nAdjustBeginCol = 1;
}

CLocalScan_TestAppGrid::~CLocalScan_TestAppGrid()
{
}

void CLocalScan_TestAppGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(ATS_TESTAPP_LOCALSEARCH_GRID_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CLocalScan_TestAppGrid::InitGridTitle()
{
	CString astrGridTitle[ATS_TESTAPP_LOCALSEARCH_GRID_COLS] = {_T("±àºÅ"),_T("²âÊÔÒÇÐÍºÅ"),_T("²âÊÔÒÇ±àºÅ"),_T("IP")};
	int iGridWidth[ATS_TESTAPP_LOCALSEARCH_GRID_COLS]={60, 120, 120, 120};

	SetColumnCount(ATS_TESTAPP_LOCALSEARCH_GRID_COLS);
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, ATS_TESTAPP_LOCALSEARCH_GRID_COLS);

	SetFont(g_pGlobalFont14);
}

void CLocalScan_TestAppGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	CDataGroup *p = (CDataGroup *)pData;
	CString strVal = _T("");

	Show_Index(p, nRow, 0);//±àºÅ

	stt_GetDataValueByID(p, ID_STT_REGISTER_ATTR_Model_TestApp, strVal);
	Show_StaticString(p, nRow, 1, &strVal);	

	stt_GetDataValueByID(p, ID_STT_USER_ATTR_SN_TestApp, strVal);
	Show_StaticString(p, nRow, 2, &strVal);

	CDataGroup *pGroup = (CDataGroup *)p->FindByID(STT_SYS_DATA_ID_DeviceIP);
	if (pGroup != NULL)
	{
		stt_GetDataValueByID(pGroup, STT_SYS_DATA_ID_IP, strVal);
	}
	else
	{
		strVal = _T("");
	}
	Show_StaticString(p, nRow, 3, &strVal);

	nRow++;
}
