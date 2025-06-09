// TplSettingGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "TplSettingGrid.h"
#include "..\..\..\Module\DataMngr\DvmData.h"
#include "..\XrioReadTool\XrioReadTool.h"

#define XRIO_PARAMETER_TABLE_COLS       7

#define XRIO_PARAMETER_COL_INDEX        0
#define XRIO_PARAMETER_COL_NAME         1
#define XRIO_PARAMETER_COL_ID           2
#define XRIO_PARAMETER_COL_TYPE         3
#define XRIO_PARAMETER_COL_UNIT         4
#define XRIO_PARAMETER_COL_VALUE        5
#define XRIO_PARAMETER_COL_MAPPARA      6
// CTplSettingGrid

CTplSettingGrid::CTplSettingGrid()
{
	m_nAdjustBeginCol = 1;
}

CTplSettingGrid::~CTplSettingGrid()
{
}

// CTplSettingGrid 成员函数
void CTplSettingGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(XRIO_PARAMETER_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CTplSettingGrid::InitGridTitle()
{
	CString astrGridTitle[XRIO_PARAMETER_TABLE_COLS] = {_T("编号"),_T("名称"),_T("ID"),_T("类型"),_T("单位"),_T("值"),_T("匹配的参数")};
	int iGridWidth[XRIO_PARAMETER_TABLE_COLS]={50, 300, 150, 50, 50, 80, 80};
	SetColumnCount(XRIO_PARAMETER_TABLE_COLS);
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, XRIO_PARAMETER_TABLE_COLS);
}

void CTplSettingGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pDvmData = ((CXrioTplMapObj *)pData)->m_pTplSetting;
	CExBaseList *pList = &((CXrioTplMapObj *)pData)->m_listMapXrioParas;
	CString *pstrText = &pList->m_strName;
	if (pList->GetCount() > 0)
	{
		pstrText = &pList->GetHead()->m_strName;
	}
		
	if (pDvmData == NULL)
	{
		Show_Index(pDvmData, nRow, XRIO_PARAMETER_COL_INDEX);//编号
		nRow++;
		return;
	}

	Show_Index(pDvmData, nRow, XRIO_PARAMETER_COL_INDEX);//编号
	Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_NAME, pDvmData->m_strName);//名称
	Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_ID, pDvmData->m_strID);   //ID
	Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_TYPE, pDvmData->m_strDataType);	//类型
	Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_UNIT, pDvmData->m_strUnit);	//单位
	Show_StaticString(pDvmData, nRow, XRIO_PARAMETER_COL_VALUE, pDvmData->m_strValue);	//值

	Show_ComboBox(pDvmData, pList, nRow, XRIO_PARAMETER_COL_MAPPARA, pstrText, EndEditCell_XrioPara);
	
	nRow++;
}

BOOL CTplSettingGrid::UpdateData(CExBaseObject *pData)
{
	CXrioTplMapObj *pMapObj = (CXrioTplMapObj *)pData;
	int nRow = GetDataRow(pMapObj->m_pTplSetting);

	if (nRow != -1)
	{
		ShowData(pMapObj, nRow, FALSE);
		Invalidate(FALSE);
	}
	else
	{
	}

	return TRUE;
}

void CTplSettingGrid::EndEditCell_XrioPara(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);
	//	ASSERT (pVCellData->pExBaseList != NULL);

	if (pVCellData->pExBaseList == NULL)
	{
#ifdef NOT_USE_XLANGUAGE
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Row=%d  Col=%d  数据类型对象不存在"), nRow, nCol);
#else
		CLogPrint::LogFormatString(LOGLEVEL_TRACE,CXLanguageResourceBase::g_sLangTxt_DataTypeUnExist/* _T("Row=%d  Col=%d  数据类型对象不存在")*/, nRow, nCol);
#endif
		return;
	}

	CExBaseList *pList = pVCellData->pExBaseList;
	ASSERT (pList != NULL);

	CDvmData *pDvmData  = (CDvmData *)pVCellData->pObj;
	CXrioCustomParameter *pXrioPara = (CXrioCustomParameter*)pList->FindByName(pCell->szText);

	if (pXrioPara != NULL)
	{
		pDvmData->m_strValue = pXrioPara->m_strValue;
		pGrid->SetItemText(nRow, XRIO_PARAMETER_COL_VALUE, pDvmData->m_strValue);
		pGrid->InvalidateGrid(FALSE);
	}
}

BEGIN_MESSAGE_MAP(CTplSettingGrid, CExBaseListGrid)
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

void CTplSettingGrid::OnRButtonUp(UINT nFlags, CPoint point)
{
	CDvmData* pDvmData = (CDvmData*)GetCurrCellData();

	if (pDvmData == NULL)
	{
		return;
	}

	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}

	m_pMsgRcvWnd->PostMessage(WM_XRIOPARASET_DIALOG_OPEN, (WPARAM)pDvmData, NULL);
}