//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GridCharElement.cpp  CGridCharMacroTest


#include "stdafx.h"
#include "GridCharMacroTest.h"

#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGridCharMacroTest::CGridCharMacroTest()
{
	//初始化属性

	//初始化成员变量
}

CGridCharMacroTest::~CGridCharMacroTest()
{

}


void CGridCharMacroTest::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(CHARMACROTEST_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridCharMacroTest::InitGridTitle()
{
	CString astrSclIecCfgTitleGIn[CHARMACROTEST_COLS] = {g_sLangTxt_Index/*_T("编号")*/,g_sLangTxt_EdgeType/*_T("类型")*/,g_sLangTxt_CordnPtn/*_T("坐标模式")*/,g_sLangTxt_TestFctnSel/*_T("测试功能选择")*/
	,_T("bx-id"),_T("ey-id"),_T("setx-id"),_T("sety-id")
	,_T("ex-id"),_T("ey-id"),_T("actx-id"), _T("acty-id")};

	int iSclIecCfgWidthGin[CHARMACROTEST_COLS]={40,80,80, 100,80,80,80,80,80,80,80,80 };

	CExBaseListGrid::InitGridTitle(astrSclIecCfgTitleGIn, iSclIecCfgWidthGin, CHARMACROTEST_COLS);
}

void CGridCharMacroTest::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCharElement *pElement = (CCharElement*)pData;

	Show_Index(pElement, nRow, CHARMACROTEST_COL_INDEX);
	Show_StaticString(pElement, nRow, CHARMACROTEST_COL_TYPE, &pElement->m_strName);

// 	Show_Long(pElement, nRow, CHARMACROTEST_COL_POINTS, &pElement->m_nTestPoints);
// 	Show_StaticString(pElement, nRow, CHARMACROTEST_COL_DETAIL, pElement->ReturnXml());

	nRow++;
}

void  CGridCharMacroTest::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{

}
