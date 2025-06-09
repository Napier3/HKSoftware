#include "StdAfx.h"
#include "IecCfgDataGridBase.h"


//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgDataGridBase::CIecCfgDataGridBase()
{
	m_pRefChsGrid = NULL;
}


CIecCfgDataGridBase::~CIecCfgDataGridBase(void)
{
	
}

BOOL CIecCfgDataGridBase::ValidateIecCfgDatFiberIndex(CIecCfgDataBase *pIecCfgData)
{
	return pIecCfgData->ValidateFiberIndex();
}

CString CIecCfgDataGridBase::GetSynModeDataTypeValue(long nSyn)
{
	CString strDataType;
	strDataType = GetSynModeDataType();
	CDataType *pSynModeType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	if (pSynModeType != NULL)
	{
		CDataTypeValue* pDataTypeValue = pSynModeType->FindByIndex(nSyn);

		if (pDataTypeValue != NULL)
		{
			return pDataTypeValue->m_strName;
		}
	}

	return _T("");
}

void CIecCfgDataGridBase::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (bInsertRow)
	{
		InsertRow(NULL);
	}

	Show_Index(pData, nRow, IECCFG_COL_ID_INDEX);

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	Show_Check(pData, nRow, IECCFG_COL_ID_DATA_CHECK, &pIecCfgData->m_nUseFlag, EndEditCell_IecCfgDataCheck);
}

void  CIecCfgDataGridBase::Show_ChNum(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnChannelNum, BOOL bSetColor)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol, bSetColor);

	Item.nDataType = GVET_EDITBOX;
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pnChannelNum, pData, NULL, EndEditCell_ChNum);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("%d"), *pnChannelNum);

	SetItem(&Item);
}

void CIecCfgDataGridBase::EndEditCell_ChNum (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (EXBASECELLDATA*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pnValue != NULL);
	ASSERT (pVellData->nVt == VCD_LONG);
	ASSERT (pVellData->pObj != NULL);

	long nChNum = CString_To_long(pCell->szText);
	long nNewChNUm = iecfg_ValidateChsMiMax(nChNum);

	if (nChNum != nNewChNUm)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("通道数%d超出范围， 调整到%d"), nChNum, nNewChNUm);
	}

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;

	if (nNewChNUm == pIecCfgData->m_nChannelNum)
	{
		pCell->szText.Format(_T("%d"), pIecCfgData->m_nChannelNum);
		pGrid->RedrawCell(nRow, nCol);
		return;
	}

	//在此对通道数量进行有效性验证
	pIecCfgData->m_nChannelNum = nNewChNUm;
	pCell->szText.Format(_T("%d"), nNewChNUm);
	pGrid->RedrawCell(nRow, nCol);

	pIecCfgData->SetChannelNum(nNewChNUm);

	CIecCfgDataGridBase *pIecCfgDataGrid = (CIecCfgDataGridBase*)pGrid;
	ASSERT (pIecCfgDataGrid->m_pRefChsGrid != NULL);
	pIecCfgDataGrid->m_pRefChsGrid->ShowDatas(pIecCfgData->m_pCfgChs);
	iecfg_SetModified(pIecCfgData);
}


void  CIecCfgDataGridBase::EndEditCell_IecCfgDataCheck (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	ASSERT (pVellData->pnValue != NULL);
	ASSERT (pVellData->nVt == VCD_LONG);

	//父对象必须有一个对象被选中
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVellData->pObj);
	*(pVellData->pnValue) = pCell->dwValue;

	CIecCfgDatasBase *pDatas = (CIecCfgDatasBase*)pVellData->pObj->GetParent();
	long nUseCount = pDatas->GetUseDatasCount();
	BOOL bTrue = TRUE,b2M_Datas = FALSE;

	if (pDatas->GetClassID() == CFGCLASSID_CIECCFGDATASSMV)
	{
		CIecCfgDatasSMV *pIecCfgDatasSMV = (CIecCfgDatasSMV*)pDatas;

		if (pIecCfgDatasSMV->IsSmvType2M())
		{
			b2M_Datas = TRUE;
		}
	}

// 	if (nUseCount == 0)//zhouhj 20211025 考虑到常规采样GOOSE跳闸,可以选择的数量为0
// 	{
// 		bTrue = FALSE;
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("必须有一个数据对象被使用"));
// 		*(pVellData->pnValue) = 1;
// 		pCell->dwValue = 1;
// 	}
/*	else */if ((nUseCount > pDatas->GetMaxCfgDataCount())&&(!b2M_Datas))
	{
		bTrue = FALSE;
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("选择的数据对象超出【%d】个"), pDatas->GetMaxCfgDataCount());
		*(pVellData->pnValue) = 0;
		pCell->dwValue = 0;
	}
	
	if (!bTrue)
	{
		pGrid->RedrawCell(nRow, nCol);
	}
#ifdef  USE_IECFG_ChsGrid_Desc_Not_Editable
	else// 在ISmartTeset中需要根据当前控制块的勾选状态,确认当前控制块对应的通道内容是否可编辑
	{

		((CIecCfgDataGridBase*)pGrid)->Update_RefChsGrid(pCell->dwValue);
	}
#endif
}

void CIecCfgDataGridBase::Update_RefChsGrid(long nSelected)
{
	ASSERT (m_pRefChsGrid != NULL);

	m_pRefChsGrid->SetEditable(nSelected);

	if (nSelected)
	{
		m_pRefChsGrid->SetTextColor(RGB(0,0,0));
	} 
	else
	{
		m_pRefChsGrid->SetTextColor(RGB(128,128,128));
	}

	m_pRefChsGrid->UpdateDatas();
}

void  CIecCfgDataGridBase::Show_Fiber(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc)
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CString strDataType = GetAppPortDataType();

	if (pFunc != NULL)
	{
		Show_DataType_Val(pData, nRow, nCol, strDataType, pnFiber, pFunc);
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, strDataType, pnFiber, EndEditCell_Fiber);
	}
}

void  CIecCfgDataGridBase::Show_Fiber2(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnFiber, GRID_CELL_EDIT_FUNC pFunc)
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CString strDataType = GetAppPortDataType();

	if (pFunc != NULL)
	{
		Show_DataType_Val(pData, nRow, nCol, strDataType, pnFiber, pFunc);
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, strDataType, pnFiber, EndEditCell_Fiber2);
	}
}

void CIecCfgDataGridBase::EndEditCell_Fiber (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgDataGridBase *pIecCfgDataGrid = (CIecCfgDataGridBase*)pGrid;

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;
	long nFiberIndex = pIecCfgData->m_nFiberIndex;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
	
	if (nFiberIndex == pIecCfgData->m_nFiberIndex)
	{
		return;
	}

	if (pIecCfgDataGrid->ValidateIecCfgDatFiberIndex(pIecCfgData))
	{
		return;
	}

	pIecCfgData->m_nFiberIndex = nFiberIndex;
	pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
	pIecCfgDataGrid->Show_Fiber(pIecCfgData, nRow, nCol, &pIecCfgData->m_nFiberIndex);
}

void CIecCfgDataGridBase::EndEditCell_Fiber2 (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgDataGridBase *pIecCfgDataGrid = (CIecCfgDataGridBase*)pGrid;

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;
	long nFiber2Index = pIecCfgData->m_nFiber2Index;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

// 	if (nFiber2Index == pIecCfgData->m_nFiber2Index) //zhouhj 20201205 对于Fiber2不再进行光口有效性验证，默认有效
// 	{
// 		return;
// 	}
// 
// 	if (pIecCfgDataGrid->ValidateIecCfgDatFiberIndex(pIecCfgData))
// 	{
// 		return;
// 	}
// 
// 	pIecCfgData->m_nFiber2Index = nFiber2Index;
// 	pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
// 	pIecCfgDataGrid->Show_Fiber2(pIecCfgData, nRow, nCol, &pIecCfgData->m_nFiber2Index);
}

void  CIecCfgDataGridBase::Show_Syn(CExBaseObject *pData, const int& nRow, const int& nCol, long *pnSyn, GRID_CELL_EDIT_FUNC pFunc)
{
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pData;
	CString strDataType = GetSynModeDataType();

	if (pFunc != NULL)
	{
		Show_DataType_Val(pData, nRow, nCol, strDataType, pnSyn, pFunc);
	}
	else
	{
		Show_DataType_Val(pData, nRow, nCol, strDataType, pnSyn, EndEditCell_Syn);
	}
}

void CIecCfgDataGridBase::EndEditCell_Syn (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgDataGridBase *pIecCfgDataGrid = (CIecCfgDataGridBase*)pGrid;

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;
	long nSynMode = pIecCfgData->m_nSyn;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

	if (nSynMode == pIecCfgData->m_nSyn)
	{
		return;
	}

	if (pIecCfgDataGrid->ValidateIecCfgDatFiberIndex(pIecCfgData))
	{
		return;
	}

	pIecCfgData->m_nFiberIndex = nSynMode;
	pIecCfgData->m_nFiber2Index = nSynMode;
	pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
	pIecCfgDataGrid->Show_Syn(pIecCfgData, nRow, nCol, &pIecCfgData->m_nSyn);
}

void CIecCfgDataGridBase::EndEditCell_Priority(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	long nValue =  CString_To_long(pCell->szText);

	if (nValue>7)
	{
		nValue = 7;
	}

	if (nValue<0)
	{
		nValue = 0;
	}

	*(pVCellData->pnValue) = nValue;
	pCell->szText.Format(_T("%d"), *(pVCellData->pnValue));
	pGrid->RedrawCell(nRow, nCol);
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void CIecCfgDataGridBase::EndEditCell_Delay(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	long nValue =  CString_To_long(pCell->szText);

	if (nValue>99999)//采样延时暂时限定不操作100ms(老版PowerTest限定为3ms,参考昂立及豪迈软件后改为此值)
	{
		nValue = 99999;
	}

	if (nValue<0)
	{
		nValue = 0;
	}

	*(pVCellData->pnValue) = nValue;
	pCell->szText.Format(_T("%d"), *(pVCellData->pnValue));
	pGrid->RedrawCell(nRow, nCol);
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void CIecCfgDataGridBase::Show_VlanID(CExBaseObject *pData, const int& nRow, const int& nCol, DWORD *pdwValue,BOOL bCanEdit, BOOL bSetColor)
{
	GV_ITEM Item;
	InitDataCellItem(Item, pData, nRow, nCol, bSetColor);

	Item.nDataType = bCanEdit ? GVET_HEXEDIT : GVET_NOEDIT;
	Item.iMaxLen = 2;
	Item.mask |= GVIF_MAXLEN;

	FreeExBaseCellData(nRow, nCol);
	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pdwValue, pData, NULL, EndEditCell_VlanID);
	Item.lParam = (LPARAM)pVCellData;
	Item.szText.Format(_T("0X%04X"), *pdwValue);

	Item.pEditFunc = EndEditCell_VlanID;

	SetItem(&Item);
}

void CIecCfgDataGridBase::EndEditCell_VlanID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pdwValue != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_DWORD);

	DWORD dwValue = 0;
	HexToDWORD(pCell->szText, dwValue);

	if (dwValue>4095)
	{
		dwValue = 4095;
		pCell->szText.Format(_T("0X%04X"), dwValue);
	}

	if (*(pVCellData->pdwValue) != dwValue)
	{
		*(pVCellData->pdwValue) = dwValue;
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
	}
}

// void CIecCfgDataGridBase::EndEditCell_VlanID(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
// {
// 	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
// 	ASSERT (pVCellData != NULL);
// 	ASSERT (pVCellData->pString != NULL);
// 
// 	unsigned long nValue =  CString_To_long(pCell->szText);
// 
	
// 
// 	*(pVCellData->pdwValue) = nValue;
// 	pCell.szText.Format(_T("0X%%04X"), *(pVCellData->pdwValue));
// 	pGrid->RedrawCell(nRow, nCol);
// 	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
// 	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
// 	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
// }

BOOL CIecCfgDataGridBase::OnCellRButtonUpEx(UINT nFlags, CPoint point)
{
	CCellID rightClickDownCell = GetCellFromPt(point);

	if (!IsValid(rightClickDownCell))
	{
		return FALSE;
	}

	if (rightClickDownCell.row != m_idCurrentCell.row)
	{
		return FALSE;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)GetItemData(rightClickDownCell.row, rightClickDownCell.col);
	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVCellData->pObj;

	ASSERT (pIecCfgData != NULL);

	pIecCfgData->SaveCfgDefaultConfigFile();
	CString strMsg;
	strMsg.Format(_T("保存缺省配置文件【%s】成功"), pIecCfgData->GetCfgDefaultConfigFile());
	MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONINFORMATION);

	return TRUE;
}

