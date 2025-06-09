#include "StdAfx.h"
#include "IECCfgOtherSettingGrid.h"

#include "../../../../../61850/Module/XLanguageResourceIec.h"



//////////////////////////////////////////////////////////////////////////
//CIecCfgDataChsGridBase

#define IECCFG_SETTING_COLS 2

CIECCfgOtherSettingGrid::CIECCfgOtherSettingGrid()
{
	m_pLastDatas = NULL;
}


CIECCfgOtherSettingGrid::~CIECCfgOtherSettingGrid(void)
{

}

void CIECCfgOtherSettingGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_SETTING_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
	SetEditable(FALSE);
}

void CIECCfgOtherSettingGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_SETTING_COLS]={
		_T("名称"),
		_T("值")
	};
	int iWidth[IECCFG_SETTING_COLS]={200,300};

	CIECCfgDataChsGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_SETTING_COLS);
}

void CIECCfgOtherSettingGrid::AddNewLine_StaticString(CExBaseList *pData, long& nRow, 
													  CString strName, CString strValue)
{
	Show_StaticString(pData, nRow, 0, strName);
	Show_StaticString(pData, nRow, 1, strValue);
	nRow++;	
}

void CIECCfgOtherSettingGrid::AddNewLine_Long(CExBaseList *pData, long& nRow, 
													  CString strName, long* pnNum)
{
	Show_StaticString(pData, nRow, 0, strName);
	Show_Long(pData, nRow, 1, pnNum, TRUE, _T(""), EndEditCell_Value);
	nRow++;	
}

void CIECCfgOtherSettingGrid::AddNewLine_Fiber(CExBaseList *pData, long& nRow, 
													  CString strName, long* pnFiber, GRID_CELL_EDIT_FUNC pFunc)
{
	Show_StaticString(pData, nRow, 0, strName);

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CString strDataType = g_strAppPortDataType_Fiber;
	if (pFunc != NULL)
	{
		Show_DataType_Val(pData, nRow, 1, strDataType, pnFiber, pFunc);
	}
	else
	{
		Show_DataType_Val(pData, nRow, 1, strDataType, pnFiber, EndEditCell_Fiber);
	}

	nRow++;	
}

void CIECCfgOtherSettingGrid::AddNewLine_Syn(CExBaseList *pData, long&nRow, 
											 CString strName, long* pnSyn, GRID_CELL_EDIT_FUNC pFunc)
{
	Show_StaticString(pData, nRow, 0, strName);

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CString strDataType = g_strSynModeDataType_Fiber;
	if (pFunc != NULL)
	{
		Show_DataType_Val(pData, nRow, 1, strDataType, pnSyn, pFunc);
	}
	else
	{
		Show_DataType_Val(pData, nRow, 1, strDataType, pnSyn, EndEditCell_Fiber);
	}

	nRow++;	
}

void CIECCfgOtherSettingGrid::AddNewLine_Test(CExBaseList *pData, long& nRow, 
											   CString strName, long* pnFiber, GRID_CELL_EDIT_FUNC pFunc)
{
	Show_StaticString(pData, nRow, 0, strName);

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CString strDataType = g_strAppTestSetDataType;
	if (pFunc != NULL)
	{
		Show_DataType_Val(pData, nRow, 1, strDataType, pnFiber, pFunc);
	}
	else
	{
		Show_DataType_Val(pData, nRow, 1, strDataType, pnFiber, EndEditCell_Fiber);
	}

	nRow++;	
}

void CIECCfgOtherSettingGrid::AddNewLine_Check(CExBaseList *pData, long& nRow, 
											  CString strName, long* pnCheck)
{
	Show_StaticString(pData, nRow, 0, strName);
	Show_Check(pData, nRow, 1, pnCheck, EndEditCell_Check);
	nRow++;	
}
// 
// void CIECCfgOtherSettingGrid::EndEditCell_Check(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
// {
// 	CIECCfgDataChsGridBase::EndEditCell_Check(nRow, nCol, pCell, pGrid);
// 	CIECCfgDataChsGridBase *pIecCfgDataChsGrid = (CIECCfgDataChsGridBase*)pGrid;
// 	pIecCfgDataChsGrid->UpdateRefGridData(nRow, nCol);
// }
// 
// void CIECCfgOtherSettingGrid::EndEditCell_Value(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
// {
// 	CIECCfgDataChsGridBase::EndEditCell_Value(nRow, nCol, pCell, pGrid);
// 	CIECCfgDataChsGridBase *pIecCfgDataChsGrid = (CIECCfgDataChsGridBase*)pGrid;
// 	pIecCfgDataChsGrid->UpdateRefGridData(nRow, nCol);
// }
// 
void CIECCfgOtherSettingGrid::EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIECCfgDataChsGridBase *pIecCfgDataChsGrid = (CIECCfgDataChsGridBase*)pGrid;
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;
	long nFiberIndex = pIecCfgData->m_nFiberIndex;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
	if (nFiberIndex == pIecCfgData->m_nFiberIndex)
	{
		return;
	}

	//pIecCfgDataChsGrid->UpdateRefGridData(nRow, nCol);
}

void CIECCfgOtherSettingGrid::ShowSMVData(CIecCfg92Data* pIecCfg92Data, long& nRow)
{
	SetRowCount(18, TRUE);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("控制块所在IED"), pIecCfg92Data->m_strIedRefDesc);
	AddNewLine_Fiber(pIecCfg92Data, nRow, _T("输出光口"), &pIecCfg92Data->m_nFiberIndex, NULL);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("源MAC地址"), pIecCfg92Data->m_strSrcAddress);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("目标MAC地址"), pIecCfg92Data->m_strDestAddress);
	CString strTmp;
	strTmp.Format(_T("0X%04X"),pIecCfg92Data->m_dwAppID);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("APPID"), strTmp);
	AddNewLine_Long(pIecCfg92Data, nRow, _T("采样延时"), &pIecCfg92Data->m_nDelay);
	strTmp.Format(_T("%d"),pIecCfg92Data->m_nPriority);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("TCI Priority"), strTmp);
	strTmp.Format(_T("0X%04X"),pIecCfg92Data->m_dwVID);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("TCI VID"), strTmp);
	strTmp.Format(_T("0X%04X"),pIecCfg92Data->m_dwVersion);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("版本号"), strTmp);
	AddNewLine_Syn(pIecCfg92Data, nRow, _T("同步方式"), &pIecCfg92Data->m_nSyn, NULL);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("svID"), pIecCfg92Data->m_strSVID);
	strTmp.Format(_T("%d"),pIecCfg92Data->m_nChannelNum);
	AddNewLine_StaticString(pIecCfg92Data, nRow, _T("通道数"), strTmp);
	AddNewLine_Check(pIecCfg92Data, nRow, _T("DataSet"), &pIecCfg92Data->m_nUseDataSet);
	AddNewLine_Check(pIecCfg92Data, nRow, _T("Security"), &pIecCfg92Data->m_nUseEncrupt);
	AddNewLine_Check(pIecCfg92Data, nRow, _T("SmpRate"), &pIecCfg92Data->m_nUseSampRate);
	AddNewLine_Check(pIecCfg92Data, nRow, _T("RefrTm"), &pIecCfg92Data->m_nUseRefreshTime);
}

void CIECCfgOtherSettingGrid::ShowGOOSEINData(CIecCfgGooseDataBase* pIecCfgGsData, long& nRow)
{
	SetRowCount(16, TRUE);
	AddNewLine_StaticString(pIecCfgGsData, nRow, _T("控制块所在IED"), pIecCfgGsData->m_strIedRefDesc);
	AddNewLine_Fiber(pIecCfgGsData, nRow, _T("输出光口"), &pIecCfgGsData->m_nFiberIndex, NULL);
	AddNewLine_StaticString(pIecCfgGsData, nRow, _T("源MAC地址"), pIecCfgGsData->m_strSrcAddress);
	AddNewLine_StaticString(pIecCfgGsData, nRow, _T("目标MAC地址"), pIecCfgGsData->m_strDestAddress);
	CString strTmp;
	strTmp.Format(_T("0X%04X"),pIecCfgGsData->m_dwAppID);
	AddNewLine_StaticString(pIecCfgGsData, nRow, _T("APPID"), strTmp);
	AddNewLine_StaticString(pIecCfgGsData, nRow, _T("描述"), pIecCfgGsData->m_strIedRefDesc);
	strTmp.Format(_T("0X%04X"),pIecCfgGsData->m_dwVersion);
	AddNewLine_StaticString(pIecCfgGsData, nRow, _T("版本号"), strTmp);
	AddNewLine_Test(pIecCfgGsData, nRow, _T("测试标记"), &pIecCfgGsData->m_bTest, NULL);
	AddNewLine_StaticString(pIecCfgGsData, nRow, _T("gocbRef"), pIecCfgGsData->m_strgocbRef);
	AddNewLine_StaticString(pIecCfgGsData, nRow, _T("goID"), pIecCfgGsData->m_strGooseId);
	AddNewLine_Check(pIecCfgGsData, nRow, _T("ndsCom"), &pIecCfgGsData->m_bNdsCom);
	AddNewLine_Long(pIecCfgGsData, nRow, _T("允许生存时间"), &pIecCfgGsData->m_nLiveTime);
	//AddNewLine_Check(pIecCfgGinData, nRow, _T("是否解析GoCB、GooseID和AppID"), );
	AddNewLine_Long(pIecCfgGsData, nRow, _T("通道数"), &pIecCfgGsData->m_nChannelNum);
}

void CIECCfgOtherSettingGrid::ShowGOOSEOUTData(CIecCfgGooseDataBase* pIecCfgGsData, long& nRow)
{
	ShowGOOSEINData(pIecCfgGsData, nRow);
}

void CIECCfgOtherSettingGrid::ShowData(CExBaseList *pData)
{
	m_pLastDatas = pData;
	UINT nClassID = pData->GetClassID();
	long nRow = 1;
	if(nClassID == CFGCLASSID_CIECCFG92DATA)
	{
		ShowSMVData((CIecCfg92Data*)pData, nRow);
	}
	else if(nClassID == CFGCLASSID_CIECCFGGINDATA)
	{
		ShowGOOSEINData((CIecCfgGinData*)pData, nRow);
	}
	else if (nClassID == CFGCLASSID_CIECCFGGOUTDATA)
	{
		ShowGOOSEOUTData((CIecCfgGoutData*)pData, nRow);
	}
	Invalidate();
}

void CIECCfgOtherSettingGrid::UpdateData()
{
	if(m_pLastDatas)
	{
		ShowData(m_pLastDatas);
		Invalidate();
	}
}