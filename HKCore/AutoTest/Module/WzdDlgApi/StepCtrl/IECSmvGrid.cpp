#include "stdafx.h"
#include "IECSmvGrid.h"
#include "../WzdDlgDef.h"

#define IECSV_GRID_SMVCOLS 4
#define IECSV_GRID_GOOSECOLS 6
#define IECSV_GRID_SMVCHCOLS 6

#define IECSV_GRID_SMVROWS	6
#define IECSV_GRID_SMVCHROWS 9

CIECSmvChGrid::CIECSmvChGrid()
{
	m_tagType = MODE_SMV;
	m_nAdjustBeginCol = -1;
	//m_pIecCfgGinChs = NULL;
	m_bInitDataTypes = FALSE;

	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/";
	m_nErrImgIndex = AddNewImage(strImg + "ch_error.png");
	m_nCorrImgIndex = AddNewImage(strImg + "ch_correct.png");
}

CIECSmvChGrid::~CIECSmvChGrid()
{
	m_oGsInChsList.RemoveAll();
	m_oGsOutChsList.RemoveAll();
}

void CIECSmvChGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(IECSV_GRID_SMVCHROWS);
	SetColumnCount(1);
	SetFixedRowCount(1);
	InitGridTitle();
}

void CIECSmvChGrid::InitGridTitle()
{
	if (m_tagType == MODE_SMV)
	{
		SetFixedColumnCount(1);
		CString astrSclIedsGirdTitle[IECSV_GRID_SMVCHCOLS] = {_T("序号"),_T("控制块所在描述"),_T("APPID"),_T("通道描述"),_T("通道类型"),_T("测试仪通道")};
		const int nSclIedsWidth[IECSV_GRID_SMVCHCOLS]={50, 250, 80, 250, 80, 90};
		SetColumnCount(IECSV_GRID_SMVCHCOLS);
		CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, IECSV_GRID_SMVCHCOLS);
	}
	else if(m_tagType == MODE_GOOSE_IN)
	{
		SetFixedColumnCount(0);
		//CString astrSclIedsGirdTitle[IECSV_GRID_GOOSECOLS] = {_T("GOOSE变位信息"),_T(""),_T("通道描述"),_T("IED描述"),_T("APPID"), _T("光口")};
		//const int nSclIedsWidth[IECSV_GRID_GOOSECOLS]={ 180, 100, 200, 160, 80, 80};
		//20230707 huangliang GOOSE中通道描述和IED描述合并
		CString astrSclIedsGirdTitle[IECSV_GRID_GOOSECOLS] = {_T("GOOSE变位信息"),_T(""),_T("通道描述【IED描述】"),_T("APPID"), _T("光口")};
		const int nSclIedsWidth[IECSV_GRID_GOOSECOLS]={ 180, 100, 380, 80, 80};
		SetColumnCount(IECSV_GRID_GOOSECOLS);
		CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, IECSV_GRID_GOOSECOLS);
	}
	else if(m_tagType == MODE_GOOSE_OUT)
	{
		SetFixedColumnCount(0);
		//CString astrSclIedsGirdTitle[IECSV_GRID_GOOSECOLS] = {_T("GOOSE变位信息"),_T(""),_T("通道描述"),_T("IED描述"),_T("APPID"), _T("光口")};
		//const int nSclIedsWidth[IECSV_GRID_GOOSECOLS]={ 180, 100, 200, 160, 80, 80};
		//20230707 huangliang GOOSE中通道描述和IED描述合并
		CString astrSclIedsGirdTitle[IECSV_GRID_GOOSECOLS] = {_T("GOOSE变位信息"),_T(""),_T("通道描述【IED描述】"),_T("APPID"), _T("光口")};
		const int nSclIedsWidth[IECSV_GRID_GOOSECOLS]={ 180, 100, 380, 80, 80};
		SetColumnCount(IECSV_GRID_GOOSECOLS);
		CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, IECSV_GRID_GOOSECOLS);
	}
}

void CIECSmvChGrid::SetGridType(tagType type)
{
	m_tagType = type;
	SetRowCount(1);
	InitGridTitle();
}

void CIECSmvChGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	CIECCfgSmvDataChsGridBase::ShowDatas(pDatas, bResetScrollBars);
	if(pDatas->GetCount() < IECSV_GRID_SMVCHCOLS)
	{
		long nHeight = GetRowHeight(0);
		SetRowCount(IECSV_GRID_SMVCHCOLS);
		for (int i = 0; i < IECSV_GRID_SMVCHCOLS; i++)
		{
			SetRowHeight(i, nHeight);
		}
	}
}

BOOL CIECSmvChGrid::ValidateIecCfgDatFiberIndex(CIecCfgGinData *pIecCfgData)
{
	return pIecCfgData->ValidateFiberIndex();
}

void CIECSmvChGrid::ClearDataTypes()
{
	m_bInitDataTypes = FALSE;
	m_oDataType.DeleteAll();
	m_oGsInChsList.RemoveAll();
}
void CIECSmvChGrid::ClearOutDataTypes()
{
	m_oGsOutDataType.DeleteAll();
	m_oGsOutChsList.RemoveAll();
}

//20230630 huangliang 添加数据类型
void CIECSmvChGrid::AddDataType(CIecCfgChsBase* pIecCfgGinChs)
{
	int iCount = m_oDataType.GetCount();
	if(iCount == 0)
	{
		CDataTypeValue* pValue = new CDataTypeValue;
		CString strIndex;
		strIndex.Format("%d", iCount);
		pValue->m_strIndex = strIndex;
		pValue->m_strID = "";
		m_oDataType.AddHead(pValue);
	}

	CIecCfgGinData* pGinData = (CIecCfgGinData*)pIecCfgGinChs->GetParent();
	if(pGinData == NULL)
		return ;

	CString strName;

	POS pos = pIecCfgGinChs->GetHeadPosition();
	while(pos)
	{
		CIecCfgGinCh* pCh = (CIecCfgGinCh*)pIecCfgGinChs->GetNext(pos);
		if(pCh->m_strExternAddr.GetLength())
		{
			//20230707 huangliang GOOSE中通道描述和IED描述合并
			strName.Format(_T("%s【%s】"), pCh->m_strName, pGinData->m_strIedRefDesc);
			CDataTypeValue* p_DValue=m_oDataType.AddNewValue(strName, pCh->m_strID, m_oDataType.GetCount());
			p_DValue->InitItemData((DWORD)pCh);
		}
		//20230628 huangliang 添加全部信息，在EndEditCell_GsInChs中需要对全部信息遍历以清除重复项
		m_oGsInChsList.AddTail(pCh);
	}
}
void CIECSmvChGrid::AddDataTypeForGsOut(CIecCfgChsBase* pIecCfgGoutChs)
{
	int iCount = m_oGsOutDataType.GetCount();
	if(iCount == 0)
	{
		CDataTypeValue* pValue = new CDataTypeValue;
		CString strIndex;
		strIndex.Format("%d", iCount);
		pValue->m_strIndex = strIndex;
		pValue->m_strID = "";
		m_oGsOutDataType.AddHead(pValue);
	}

	CIecCfgGoutData* pGoutData = (CIecCfgGoutData*)pIecCfgGoutChs->GetParent();
	if(pGoutData == NULL)
		return ;

	CString strName;

	POS pos = pIecCfgGoutChs->GetHeadPosition();
	while(pos)
	{
		CIecCfgGoutCh* pCh = (CIecCfgGoutCh*)pIecCfgGoutChs->GetNext(pos);
		if(pCh->m_strAddrExternal.GetLength())
		{
			strName.Format(_T("%s【%s】"), pCh->m_strDescExternal, pGoutData->m_strIedRefDesc);
			CDataTypeValue* p_DValue= m_oGsOutDataType.AddNewValue(strName, pCh->m_strID, m_oGsOutDataType.GetCount());
			p_DValue->InitItemData((DWORD)pCh);
			
		}
		m_oGsOutChsList.AddTail(pCh);
	}
}

void CIECSmvChGrid::EndEditCell_GsInChs (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIECSmvChGrid *pIecCfgChGrid = (CIECSmvChGrid*)pGrid;
	
	CIECChMap* pMap = (CIECChMap*)pVellData->pObj;
	CString strTempName = "";

	CDataTypeValue* p_DValue = (CDataTypeValue*)pIecCfgChGrid->m_oDataType.FindByIndex(pCell->dwValue);
	CIecCfgGinCh* pCh = (CIecCfgGinCh*)p_DValue->m_dwItemData;

	if(pMap->m_pCh != NULL && pCh != NULL)
	{
		if(pMap->m_pCh->m_strID == pCh->m_strID)
			return ;
	}

	CString strBin = pMap->m_pChMap->m_strID;
	if(strBin.Find(';') == -1)
	{
		strBin += ';';
	}

	//20230629 huangliang 找到原pCh对象，并清空m_strAppChID值
	if(pMap->m_pCh != NULL)
	{
		CIecCfgGinCh* pChTmp = (CIecCfgGinCh*)pIecCfgChGrid->m_oGsInChsList.FindByID(pMap->m_pCh->m_strID);
		if(pChTmp != NULL)
		{
			pChTmp->m_strAppChID.Replace(strBin, "");
			if(!pChTmp->m_strAppChID.GetLength())
			{
				pChTmp->m_strAppChID = "none";
			}
		}
	}

	//20230629 huangliang 修改选中Ch中app-ch值
	if(pCh != NULL)
	{
		if(pCh->m_strAppChID == "0" || pCh->m_strAppChID == "none")
		{
			pCh->m_strAppChID = strBin;
		}
		else if(pCh->m_strAppChID.Find(strBin) == -1)
		{
			pCh->m_strAppChID.Format("%s%s", pCh->m_strAppChID, strBin);
		}

		if(pMap->m_pCh)
		{
			delete pMap->m_pCh;
			pMap->m_pCh = (CIecCfgGinCh*)pCh->Clone();
		}
		else
		{
			pMap->m_pCh = (CIecCfgGinCh*)pCh->Clone();
		}
	}
	else
	{
		POS pos = pIecCfgChGrid->m_oGsInChsList.GetHeadPosition();
		while (pos)
		{
			CIecCfgGinCh* pChTmp = (CIecCfgGinCh*)pIecCfgChGrid->m_oGsInChsList.GetNext(pos);
			pChTmp->m_strAppChID.Replace(strBin, "");
			if(!pChTmp->m_strAppChID.GetLength())
			{
				pChTmp->m_strAppChID = "none";
			}

			if(pMap->m_pCh)
			{
				pMap->m_pCh->m_strAppChID.Replace(strBin, "");
				if(!pMap->m_pCh->m_strAppChID.GetLength())
				{
					delete pMap->m_pCh;
					pMap->m_pCh = NULL;
				}
			}
		}
	}
	pIecCfgChGrid->GetParentWnd()->SendMessage(WM_IECCFG_UPDATEGS, 0, 0);
}

void CIECSmvChGrid::Show_GsInChs(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CIecCfgGinCh* pIecCfgGinCh = (CIecCfgGinCh*)pData;
	Show_DataType_Val(pData, nRow, nCol, &m_oDataType, pstrValue, EndEditCell_GsInChs);
}

void CIECSmvChGrid::ShowData_SMVCh(CExBaseObject *pData, int& nRow)
{
	CIecCfg92Ch* pCh = (CIecCfg92Ch*)pData;
	if(pCh->GetClassID() != CFGCLASSID_CIECCFG92CH)
	{
		return;
	}

	CIecCfg92Data* pParent = (CIecCfg92Data*)pCh->GetParent()->GetParent();

	Show_Index(pCh, nRow, 0);
	CString strName = pParent->m_pSclRef->m_strName;
	if(strName.Find("--") != -1)
	{
		strName = strName.Mid(strName.Find("--") + 2);
	}
	Show_StaticString(pCh, nRow, 1, strName);
	CString strAppID;
	strAppID.Format(_T("0X%04X"),pParent->m_dwAppID);
	Show_StaticString(pCh, nRow, 2, strAppID);
	Show_StaticString(pCh, nRow, 3, pCh->m_strDescExternal);
	ShowCfgCh_Type(pCh, nRow, 4, &pCh->m_strChType, iecfg_Smv92ChDataType);
	ShowCfgCh_AppCh(pCh, nRow, 5, &pCh->m_strAppChID, iecfg_SmvAppChDataType);

	DeleteCellImage(nRow, 1);

	nRow++;
}

void CIECSmvChGrid::EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIECSmvChGrid *pIecCfgChGrid = (CIECSmvChGrid*)pGrid;

	CIecCfgGinData *pIecCfgData = (CIecCfgGinData*)pVellData->pObj;
	long nFiberIndex = pIecCfgData->m_nFiberIndex;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

	if (nFiberIndex == pIecCfgData->m_nFiberIndex)
	{
		return;
	}

	pIecCfgChGrid->UpdateDatas();
}

void CIECSmvChGrid::Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc)
{
	CIecCfgGinData *pIecCfgData = (CIecCfgGinData*)pData;
	CString strDataType = g_strAppPortDataType_Fiber;

	if (pFunc != NULL)
	{
		Show_DataType_Val(pData, nRow, nCol, strDataType, pnFiber, pFunc);
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, strDataType, pnFiber, EndEditCell_Fiber);
	}
}

void CIECSmvChGrid::ShowData_GOOSE(CExBaseObject *pData, int& nRow)
{
	CIECChMap* pMap = (CIECChMap*)pData;

	Show_StaticString(pMap->m_pChMap, nRow, 0, pMap->m_pChMap->m_strName);

	if(pMap->m_pCh)
	{
		CDataTypeValue* pValue = (CDataTypeValue*)m_oDataType.FindByID(pMap->m_pCh->m_strID);
		if(pValue)
		{
			SetCellImage(nRow, 1, m_nCorrImgIndex);
			CIecCfgGinData* pGinData = (CIecCfgGinData*)pMap->m_pCh->GetParent()->GetParent();
			Show_GsInChs(pMap, nRow, 2, &pMap->m_pCh->m_strID);

			CString strAppID;
			strAppID.Format("0x%04X", pGinData->m_dwAppID);
			Show_StaticString(pGinData, nRow, 3, strAppID);
			Show_Fiber(pGinData, nRow, 4, &pGinData->m_nFiberIndex);
		}
		else
		{
			SetCellImage(nRow, 1, m_nErrImgIndex);
			CString strName;
			Show_GsInChs(pMap, nRow, 2, &strName);
		}
	}
	else
	{
		SetCellImage(nRow, 1, m_nErrImgIndex);
		CString strName;
		Show_GsInChs(pMap, nRow, 2, &strName);
		Show_StaticString(pMap, nRow, 3, "");
		Show_StaticString(pMap, nRow, 4, "");
	}

	nRow++;
}

void CIECSmvChGrid::EndEditCell_GsOutChs (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIECSmvChGrid *pIecCfgChGrid = (CIECSmvChGrid*)pGrid;
	
	CIECChOutMap* pMap = (CIECChOutMap*)pVellData->pObj;
	CString strTempName = "";

	if(pMap == NULL)
		return ;

	CDataTypeValue* p_DValue = (CDataTypeValue*)pIecCfgChGrid->m_oGsOutDataType.FindByIndex(pCell->dwValue);
	CIecCfgGoutCh* pCh = (CIecCfgGoutCh*)p_DValue->m_dwItemData;
	if(pMap->m_pCh != NULL && pCh != NULL)
	{
		if(pMap->m_pCh->m_strID == pCh->m_strID)
			return ;
	}

	//初始化原对象
	if(pMap->m_pCh != NULL)
	{
		if(pMap->m_pCh->m_strDataType == g_strGooseChType_Single)
			pMap->m_pCh->m_strAppChID = "v0";
		else
			pMap->m_pCh->m_strAppChID = "v01";
		pMap->m_pCh->m_strDevChID = "none";
		pMap->m_pCh = NULL;
	}

	if(pCh != NULL)
	{
		CString strBin = pMap->m_strID;
		CString strDevBin = strBin;
		strDevBin.Replace(_T("bout"),_T("bin"));

		pCh->m_strAppChID = strBin;//设置新对象
		pCh->m_strDevChID = strDevBin;
		pMap->m_pCh = pCh;
	}
	pIecCfgChGrid->GetParentWnd()->SendMessage(WM_IECCFG_UPDATEGS, 0, 0);
}
void CIECSmvChGrid::Show_GsOutChs(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc)
{
	CIecCfgGoutCh* pIecCfgGoutCh = (CIecCfgGoutCh*)pData;
	Show_DataType_Val(pData, nRow, nCol, &m_oGsOutDataType, pstrValue, EndEditCell_GsOutChs);
}
void CIECSmvChGrid::ShowData_GOOSE_Out(CExBaseObject *pData, int& nRow)
{
	CIECChOutMap* pMap = (CIECChOutMap*)pData;

	Show_StaticString(pMap->m_pCh, nRow, 0, pMap->m_strName);

	if(pMap->m_pCh)
	{
		CDataTypeValue* pValue = (CDataTypeValue*)m_oGsOutDataType.FindByID(pMap->m_pCh->m_strID);
		if(pValue)
		{
			SetCellImage(nRow, 1, m_nCorrImgIndex);
			CIecCfgGoutData* pGoutData = (CIecCfgGoutData*)pMap->m_pCh->GetParent()->GetParent();
			Show_GsOutChs(pMap, nRow, 2, &pMap->m_pCh->m_strID);

			CString strAppID;
			strAppID.Format("0x%04X", pGoutData->m_dwAppID);
			Show_StaticString(pGoutData, nRow, 3, strAppID);
			Show_Fiber(pGoutData, nRow, 4, &pGoutData->m_nFiberIndex);
		}
		else
		{
			SetCellImage(nRow, 1, m_nErrImgIndex);
			CString strName;
			Show_GsOutChs(pMap, nRow, 2, &strName);
		}
	}
	else
	{
		SetCellImage(nRow, 1, m_nErrImgIndex);
		CString strName;
		Show_GsOutChs(pMap, nRow, 2, &strName);
		Show_StaticString(pMap, nRow, 3, "");
		Show_StaticString(pMap, nRow, 4, "");
	}

	nRow++;
}

void CIECSmvChGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if(m_tagType == MODE_SMV)
	{
		ShowData_SMVCh(pData, nRow);
	}
	else if (m_tagType == MODE_GOOSE_IN)
	{
		ShowData_GOOSE(pData, nRow);
	}
	else if (m_tagType == MODE_GOOSE_OUT)
	{
		ShowData_GOOSE_Out(pData, nRow);
	}
}


CIECSmvGrid::CIECSmvGrid()
{
	m_nAdjustBeginCol = -1;
}

CIECSmvGrid::~CIECSmvGrid()
{

}

void CIECSmvGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(IECSV_GRID_SMVROWS);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIECSmvGrid::InitGridTitle()
{
	CString astrSclIedsGirdTitle[IECSV_GRID_SMVCOLS] = {_T("序号"),_T("控制块所在描述"),_T("输出光口"),_T("采样延时")};
	const int nSclIedsWidth[IECSV_GRID_SMVCOLS]={50, 250, 250, 250};
	SetColumnCount(IECSV_GRID_SMVCOLS);
	CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, IECSV_GRID_SMVCOLS);
}

void CIECSmvGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	CIECCfgSmv92DataGrid::ShowDatas(pDatas, bResetScrollBars);
	if(pDatas->GetCount() < IECSV_GRID_SMVROWS)
	{
		long nHeight = GetRowHeight(0);
		SetRowCount(IECSV_GRID_SMVROWS);
		for (int i = 0; i < IECSV_GRID_SMVROWS; i++)
		{
			SetRowHeight(i, nHeight);
		}
	}
}

void CIECSmvGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CIecCfg92Data* p92Data = (CIecCfg92Data*)pData;
	if(p92Data->GetClassID() != CFGCLASSID_CIECCFG92DATA)
	{
		return;
	}

	if(!p92Data->m_nUseFlag)
	{
		return;
	}

	Show_Index(p92Data, nRow, 0);
	CString strName;
	if(p92Data->m_pSclRef)
	{
		strName = p92Data->m_pSclRef->m_strName;
	}
	else
	{
		strName = p92Data->m_strIedRefDesc;
	}


	if(strName.Find("--") != -1)
	{
		strName = strName.Mid(strName.Find("--") + 2);
	}
	Show_StaticString(p92Data, nRow, 1, strName);
	CString strAppID;
	Show_Fiber(p92Data, nRow, 2, &p92Data->m_nFiberIndex);
	Show_Long(p92Data, nRow, 3, &p92Data->m_nDelay);
	nRow++;
}void CIECSmvGrid::OnDataSelChanged(int nRow, int nCol)//20240221 luozibing 添加SMV配置中，当前选择项改变后Gs表格更新
{
	CExBaseListGrid::OnDataSelChanged(nRow,nCol);
	GetParentWnd()->SendMessage(WM_IECCFG_UPDATEGS, 0, 0);
}