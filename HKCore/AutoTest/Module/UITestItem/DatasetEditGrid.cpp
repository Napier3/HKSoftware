#include "StdAfx.h"
#include "DatasetEditGrid.h"
#include "..\XLanguageResourceAts.h"

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CDatasetEditGrid::CDatasetEditGrid()
{

}


CDatasetEditGrid::~CDatasetEditGrid(void)
{
	
}

void CDatasetEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DATASET_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDatasetEditGrid::InitGridTitle()
{
	CString cTempStr[DATASET_COLS]={CXLanguageResourceAtsBase::g_sLangTxt_SerNumber/*_T("���")*/,CXLanguageResourceAtsBase::g_sLangTxt_Name/*_T("����")*/,_T("ID"),CXLanguageResourceAtsBase::g_sLangTxt_Value/*_T("��ֵ")*/,CXLanguageResourceAtsBase::g_sLangTxt_Unit/* _T("��λ")*/};
	int iWidth[DATASET_COLS]={60,200, 200,160,120};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DATASET_COLS);
}


void CDatasetEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	CDvmData *pDataObj = (CDvmData*)pData;

	Show_Index(pData, nRow, DATASET_COL_ID_INDEX);
	Show_StaticString(pData, nRow, DATASET_COL_ID_NAME, &pDataObj->m_strName);
	Show_StaticString(pData, nRow, DATASET_COL_ID_ID,   &pDataObj->m_strID);
	Show_String(pData, nRow, DATASET_COL_ID_VALUE,      &pDataObj->m_strValue); 
	Show_StaticString(pData, nRow, DATASET_COL_ID_UNIT, &pDataObj->m_strUnit);

	nRow++;
}

