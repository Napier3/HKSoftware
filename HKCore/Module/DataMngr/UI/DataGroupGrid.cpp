//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利


#include "stdafx.h"
#include "DataGroupGrid.h"
#include "..\..\System\Module\XAtsSysSvrClient.h"
#include "..\..\XLanguage\XLanguageMngr.h"

CDataGroupGrid::CDataGroupGrid()
{
	//初始化属性
	m_pDataGroupListViewRef = NULL;
	m_pDataTypesRef = NULL;

	//初始化成员变量
}

CDataGroupGrid::~CDataGroupGrid()
{

}


void CDataGroupGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DATAMNGRFOLDER_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CDataGroupGrid::InitGridTitle()
{
	CString astrGridTitle[DATAMNGRFOLDER_COLS] = {/*_T("编号")*/g_sLangTxt_Index,/*_T("名称")*/g_sLangTxt_Name,/*_T("选择")*/g_sLangTxt_Select,/*_T("数值")*/g_sLangTxt_Value};
	int iGridWidth[DATAMNGRFOLDER_COLS]={50,100,50, 50};

	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, DATAMNGRFOLDER_COLS);
}

void CDataGroupGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CSHORTDATA)
	{
		return;
	}

	CShortData *pShortData = (CShortData*)pData;

	Show_Index(pShortData, nRow, DATAMNGRFOLDER_COL_INDEX);
	Show_StaticString(pShortData, nRow, DATAMNGRFOLDER_COL_NAME, &pShortData->m_strName);
	Show_Check(pShortData, nRow, DATAMNGRFOLDER_COL_SEL, (long*)&pShortData->m_dwReserved);

#ifdef _UNICODE
	if (wcsicmp(pShortData->m_strDataTypeID, _T("bool")) == 0)
#else
	if (stricmp(pShortData->m_strDataTypeID, "bool") == 0)
#endif
	{
		Show_Check(pShortData, nRow, DATAMNGRFOLDER_COL_VALUE, (long*)&pShortData->m_dwItemData);
	}
	else
	{
		Show_DataType_Val(pShortData, nRow, DATAMNGRFOLDER_COL_VALUE, pShortData->m_strDataTypeID, (long*)&pShortData->m_dwItemData);
	}

	nRow++;
}

CDataType* CDataGroupGrid::FindDataType(const CString &strDataType)
{
	if (m_pDataTypesRef != NULL)
	{
		return (CDataType*)m_pDataTypesRef->FindByID(strDataType);
	}
	else
	{
		return NULL;
	}
}


void  CDataGroupGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	
}


void CDataGroupGrid::OnDataSelChanged(int nRow, int nCol)
{
	//CShortData *pData = (CShortData*)GetCurrSelData(1);
	CShortData *pData = (CShortData*)GetDataRow(nRow, 1);

	if (pData == NULL)
	{
		return;
	}


}

