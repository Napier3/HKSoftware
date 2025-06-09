// D:\WorkLiJQ\Source\AutoTest\GuideBookDev\UI\Device\GbUIGuidebookExtendRptTempateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ExtendRptTempateGrid.h"
#include "..\XLanguageResourceAts.h"
#include "..\GuideBook\GuideBookDefine.h"

//////////////////////////////////////////////////////////////////////////
//
#define EXTEND_RPT_TEMPLATE_COL_INDEX  0
#define EXTEND_RPT_TEMPLATE_COL_NAME   1
#define EXTEND_RPT_TEMPLATE_COL_ADDED  2
#define EXTEND_RPT_TEMPLATE_COLS  3

CGridExtendRptTempalte::CGridExtendRptTempalte()
{
	
}

CGridExtendRptTempalte::~CGridExtendRptTempalte()
{

}


void CGridExtendRptTempalte::InitGridTitle()
{
	CString cTempStr[EXTEND_RPT_TEMPLATE_COLS]={g_sLangTxt_SerNumber
		,g_sLangTxt_ReportTemplateFile
		,g_sLangTxt_Add};
	int iWidth[EXTEND_RPT_TEMPLATE_COLS]={60,300, 150};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, EXTEND_RPT_TEMPLATE_COLS);
}

void CGridExtendRptTempalte::InitGrid()
{
	SetListMode(TRUE);
	//SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);

	InitGridTitle();

	ResetScrollBars();
}

void CGridExtendRptTempalte::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pExtRptTtt = (CDvmData*)pData;

	Show_Index(pData, nRow, EXTEND_RPT_TEMPLATE_COL_INDEX);

	Show_StaticString(pData, nRow, EXTEND_RPT_TEMPLATE_COL_NAME, &pExtRptTtt->m_strName);
	Show_String(pData, nRow, EXTEND_RPT_TEMPLATE_COL_ADDED, &pExtRptTtt->m_strFormat);

	nRow++;
}

void CGridExtendRptTempalte::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	Gb_SetGbModifiedFlag(pData);
}
