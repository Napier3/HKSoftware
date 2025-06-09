#include "StdAfx.h"
#include "SafetyTestGrid.h"
#include "..\XLanguageResourceAts.h"

//////////////////////////////////////////////////////////////////////////
//CSafetyTestGrid
#define  SAFETYTEST_COL_INDEX    0
#define  SAFETYTEST_COL_NAME     1
#define  SAFETYTEST_COL_ID       2
#define  SAFETYTEST_COL_VALUE    3
#define  SAFETYTEST_COL_UNIT     4
#define  SAFETYTEST_COLS         5

CSafetyTestGrid::CSafetyTestGrid()
{
	m_nAdjustBeginCol = 0;
}


CSafetyTestGrid::~CSafetyTestGrid(void)
{
	
}

void CSafetyTestGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(SAFETYTEST_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSafetyTestGrid::InitGridTitle()
{
	CString cTempStr[SAFETYTEST_COLS]={
		/*L"编号"*/CXLanguageResourceAtsBase::g_sLangTxt_Index,
		/*L"名称"*/CXLanguageResourceAtsBase::g_sLangTxt_Name,
		/*L"ID"*/CXLanguageResourceAtsBase::g_sLangTxt_Id,
		/*L"缺省值"*/CXLanguageResourceAtsBase::g_sLangTxt_Value,
		/*L"单位"*/CXLanguageResourceAtsBase::g_sLangTxt_Unit
	};

	int iWidth[SAFETYTEST_COLS]={60,200, 80, 150, 60};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, SAFETYTEST_COLS);
}	

CDataType* CSafetyTestGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}


void CSafetyTestGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	CShortData *pShortData = (CShortData *)pData;
	ASSERT (nClassID == DTMCLASSID_CSHORTDATA);

	Show_Index(pData, nRow, SAFETYTEST_COL_INDEX);

	Show_StaticString(pData, nRow, SAFETYTEST_COL_NAME, &pData->m_strName);
	Show_StaticString(pData, nRow, SAFETYTEST_COL_ID, &pData->m_strID);
	
	Show_StaticString(pData, nRow, SAFETYTEST_COL_UNIT, &pShortData->m_strUnit);

	nRow++;
}


// 
// void CSafetyTestGrid::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
// {
// 	Show_DataType_Val(pData, nRow, nCol, strDataType, pstrAppCh, EndEditCell_AppCh);
// }
// 
// 
// void CSafetyTestGrid::EndEditCell_AppCh (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
// {
// 	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
// }
