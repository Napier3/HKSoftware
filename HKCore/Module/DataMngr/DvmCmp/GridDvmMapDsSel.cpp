#include "StdAfx.h"
#include "GridDvmMapDsSel.h"
#include "..\..\Module\XLanguage\XLanguageResource.h"

//////////////////////////////////////////////////////////////////////////
//CDsvScriptEditGrid


CGridDvmMapDsSel::CGridDvmMapDsSel()
{
	m_nAdjustBeginCol = 0;
}


CGridDvmMapDsSel::~CGridDvmMapDsSel(void)
{
	
}


void CGridDvmMapDsSel::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DVMDSMAPSEL_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CGridDvmMapDsSel::ShowDatas(CExBaseList *pExDataList)
{

	CExBaseListGrid::ShowDatas(pExDataList);

}

void CGridDvmMapDsSel::InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	CExBaseListGrid::InsertData(pData, bInvalidate);



	Invalidate(FALSE);
}

void  CGridDvmMapDsSel::OnEditCell(int nRow, int nCol, UINT nChar)
{
	CExBaseListGrid::OnEditCell(nRow, nCol, nChar);

}

void CGridDvmMapDsSel::InitGridTitle()
{
	CString cTempStr[DVMDSMAPSEL_COLS];//={_T("序号"),_T("选择"),_T("逻辑设备"),_T("目标逻辑设备"),_T("数据集"),_T("目标数据集")};
	cTempStr[0] = g_sLangTxt_Index;
	cTempStr[1] = g_sLangTxt_Select;
	cTempStr[2] = g_sLangTxt_LogicDevice;
	cTempStr[3] = g_sLangTxt_LogicDeviceMap;
	cTempStr[4] = g_sLangTxt_DataSets;
	cTempStr[5] = g_sLangTxt_DataSetsMap;

	int iWidth[DVMDSMAPSEL_COLS]={60,120, 120,100, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DVMDSMAPSEL_COLS);
}	

void CGridDvmMapDsSel::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (DMPCLASSID_CDVMDATASETMAP == nClassID);
	CDvmDatasetMap *pDsMap = (CDvmDatasetMap *)pData;

	Show_Index(pData, nRow, DVMDSMAPSEL_COL_INDEX);
	Show_Check(pData, nRow, DVMDSMAPSEL_COL_SEL, &pDsMap->m_nCmpResult);

	Show_StaticString(pData, nRow, DVMDSMAPSEL_COL_LDNAME, &pDsMap->m_strLdvice);
	Show_StaticString(pData, nRow, DVMDSMAPSEL_COL_LDMAPNAME, &pDsMap->m_strLdviceMap);
	Show_StaticString(pData, nRow, DVMDSMAPSEL_COL_DSNAME, &pDsMap->m_strID);
	Show_StaticString(pData, nRow, DVMDSMAPSEL_COL_DSMAPNAME, &pDsMap->m_strMapID);

	UpdateRowBkColor(nRow);

	nRow++;
}

void CGridDvmMapDsSel::DataViewOptr_DataChanged(int nRow, int nCol)
{
	CExBaseListGrid::DataViewOptr_DataChanged(this, nRow, nCol);
	UpdateRowBkColor(nRow);
	Invalidate(FALSE);
}

void CGridDvmMapDsSel::UpdateRowBkColor(long nRow)
{
	CDvmDatasetMap *pDsMap = (CDvmDatasetMap *)GetDataRow(nRow, DVMDSMAPSEL_COL_SEL);

	if (pDsMap == NULL)
	{
		return;
	}

	COLORREF crBk = RGB(255, 255, 255);

	if (pDsMap->m_nCmpResult != 0)
	{
		crBk = RGB(34, 177, 76);
	}

	SetItemBkColour(nRow, DVMDSMAPSEL_COL_SEL, crBk);
	SetItemBkColour(nRow, DVMDSMAPSEL_COL_LDNAME, crBk);
	SetItemBkColour(nRow, DVMDSMAPSEL_COL_LDMAPNAME, crBk);
	SetItemBkColour(nRow, DVMDSMAPSEL_COL_DSNAME, crBk);
	SetItemBkColour(nRow, DVMDSMAPSEL_COL_DSMAPNAME, crBk);
}