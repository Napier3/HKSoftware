#include "stdafx.h"

#include "MdTestEditGrid.h"
#include "TaskMngr\TestTask.h"
#include "XLanguageResourceAts_AutoTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MDTEST_GRID_COL_INDEX    0
#define MDTEST_GRID_COL_NAME     1
#define MDTEST_GRID_COL_IP       2
#define MDTEST_GRID_COL_DVMFILE  3
#define MDTEST_GRID_COLS         4

CMdTestEditGrid::CMdTestEditGrid(void)
{
	m_nAdjustBeginCol = 0;
}

CMdTestEditGrid::~CMdTestEditGrid(void)
{
}

void CMdTestEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);

	InitGridTitle();

	ResetScrollBars();
}

void CMdTestEditGrid::InitGridTitle()
{
	CString cTempStr[MDTEST_GRID_COLS]={g_sLangTxt_SerNumber/*_T("序号")*/,g_sLangTxt_Name/*_T("名称")*/,_T("IP"),g_sLangTxt_ModelFile/*_T("模型文件")*/};
	int iWidth[MDTEST_GRID_COLS]={60,120, 200, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, MDTEST_GRID_COLS);
}
// 
// void CMdTestEditGrid::ShowTask(CTestTask *pTask)
// {
// 	m_pDataset = pDatas;
// 
// 	CDvmData * pShortData = NULL;
// 	long nIndex = 0;
// 	long nRows = 0;
// 	long nCount = m_pDataset->GetCount();
// 	SetRowCount(nCount + 1);
// 
// 	for (nIndex=0;nIndex<nCount;nIndex++)
// 	{
// 		pShortData = (CDvmData*)m_pDataset->GetAtIndex(nIndex);
// 		nRows++;
// 		ShowOneParaObject(pShortData,nRows);
// 	}
// }

void CMdTestEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CTestProject *pTestProject = (CTestProject*)pData;

	Show_Index(pData, nRow, MDTEST_GRID_COL_INDEX);

	Show_String(pData, nRow, MDTEST_GRID_COL_NAME, &pTestProject->m_strID, EndEditCell_String_NameAndID);
	Show_String(pData, nRow, MDTEST_GRID_COL_IP, &pTestProject->m_strLocalID);

	CString strTemp = GetPathFileNameFromFilePathName(pTestProject->m_strPpDeviceFile);
	Show_StaticString(pData, nRow, MDTEST_GRID_COL_DVMFILE, strTemp);
	nRow++;
}

BOOL CMdTestEditGrid::EndEditCell(int nRow, int nCol, DWORD dwItemData)
{
	

	return CExBaseListGrid::EndEditCell(nRow, nCol, dwItemData);;
}

