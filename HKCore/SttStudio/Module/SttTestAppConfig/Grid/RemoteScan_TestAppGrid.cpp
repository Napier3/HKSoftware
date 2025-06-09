// RemoteScan_TestAppGrid.cpp : ÊµÏÖÎÄ¼þ
//

#include "stdafx.h"
#include "RemoteScan_TestAppGrid.h"
#include "../../../Module/SttAuthority/SttTestRemoteRegister.h"
#ifndef NOT_USE_XLANGUAGE
#include "../../XLangResource_Native.h"
#endif
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
#ifndef NOT_USE_XLANGUAGE
	CString astrGridTitle[ATS_TESTAPP_REMOTESEARCH_GRID_COLS] = {/*_T("±àºÅ")*/g_sLangTxt_Index,/*_T("µ¥Î»")*/g_sLangTxt_Unit,/*_T("ÐÕÃû")*/g_sLangTxt_Name,/*_T("²âÊÔÒÇÐÍºÅ")*/g_sLangTxt_Native_TestInstrumentModel,/*_T("²âÊÔÒÇ±àºÅ")*/g_sLangTxt_Native_TestInstrumentID};
#else
	CString astrGridTitle[ATS_TESTAPP_REMOTESEARCH_GRID_COLS] = {_T("±àºÅ"),_T("µ¥Î»"),_T("ÐÕÃû"),_T("²âÊÔÒÇÐÍºÅ"),_T("²âÊÔÒÇ±àºÅ")};
#endif
	int iGridWidth[ATS_TESTAPP_REMOTESEARCH_GRID_COLS]={60, 120, 120, 120, 120};

	SetColumnCount(ATS_TESTAPP_REMOTESEARCH_GRID_COLS);
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, ATS_TESTAPP_REMOTESEARCH_GRID_COLS);

	SetFont(g_pGlobalFont14);
}

void CRemoteScan_TestAppGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	CSttTestRemoteRegister *pRegister = (CSttTestRemoteRegister *)pData;

	Show_Index(pRegister, nRow, 0);//±àºÅ

	Show_StaticString(pRegister, nRow, 1, &pRegister->Name_Cop());		//µ¥Î»
	Show_StaticString(pRegister, nRow, 2, &pRegister->Name_User());		//ÓÃ»§
	Show_StaticString(pRegister, nRow, 3, &pRegister->Model_TestApp());	
	Show_StaticString(pRegister, nRow, 4, &pRegister->SN_TestApp());

	nRow++;
}
