#include "StdAfx.h"
#include "MacroTestDataEditGrid.h"
#include "..\Module\GuideBook\GbDataTypeMngr.h"
#include "..\Module\GuideBook\Device.h"
#include "..\Module\GuideBook\MacroTest.h"
#include "..\AutoTest\XLanguageResourceAts_AutoTest.h"

CMacroTestDataEditGrid::CMacroTestDataEditGrid()
{	
	m_crBkColor = RGB(255,255,255);
	m_crTextColor = RGB(0,0,0);
	m_pItemMacroTest = NULL;
	SetListMode(TRUE);
}

CMacroTestDataEditGrid::~CMacroTestDataEditGrid()
{

}

void CMacroTestDataEditGrid::SetMacroTestDatas(CShortDatas* oDatas, CBaseObject *pDevice)
{
	m_pItemMacroTest = pDevice;
	m_oDatas = oDatas;
	SetGridRows();

	LONG nCount = m_oDatas->GetCount();
	CShortData * oData = NULL;

	for (int i=0;i<nCount;i++)
	{
		oData = (CShortData*)m_oDatas->GetAtIndex(i);
		ShowValData(oData, i+1);
	}

	ResetScrollBars();
	Invalidate(TRUE);
}

void CMacroTestDataEditGrid::ShowValData(CShortData * oData, int nRowIndex)
{
	GV_ITEM Item;
	Item.state  = GVIS_READONLY;//state
	Item.mask=GVIF_FORMAT|GVIF_PARAM|GVIF_TEXT | GVIF_FGCLR|GVIF_BKCLR | GVIF_DATATYPE |GVIF_VALUE|GVIS_FOCUSED;	
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = 0;

	Item.row = nRowIndex;
	Item.crBkClr=m_crBkColor;
	Item.crFgClr=m_crTextColor;
	Item.dwValue = 0;
	Item.lParam = nRowIndex;

	//Name
	Item.col = 0;
	Item.dwValue = 0;
	Item.nDataType = GVET_NOEDIT;
	Item.szText = oData->m_strName;
	SetItem(&Item);

	//Value
	Item.col = 1;
	CString bstrDataTypeID = oData->m_strDataTypeID;

	if ( IsComboMacroTestDataType(bstrDataTypeID) )
	{
		Item.nDataType = GVET_COMBOBOXDROPLIST;

		if (g_strGbDataTypeSet == bstrDataTypeID)
		{//定值
			CDevice *pDevice = (CDevice*)GetDevice();
			Item.szText = oData->m_strValue;
			CSet *pSet = pDevice->FindSetByID(Item.szText);

			if (pSet != NULL)
			{
				Item.szText = pSet->m_strName;
			}
		}
		else
		{
			GetDataTypeNameByValue(CGbDataTypeMngr::GetMacroTestDataTypes(), bstrDataTypeID, oData->m_strValue, Item.szText);
			//Item.szText = (LPCTSTR)oData->GetValue();
		}
	}
	else
	{
		Item.nDataType = GVET_EDITBOX;
		Item.szText = oData->m_strValue;
	}

	SetItem(&Item);

	//Unit
	Item.col = 2;
	Item.nDataType = GVET_NOEDIT;
	Item.szText = oData->m_strUnit;
	SetItem(&Item);
}

CShortData * CMacroTestDataEditGrid::SetItemValue(const CString &strValue)
{
	int nCol,nRow;
	GetFocusCell(nRow,nCol);
	CGridCell* pCell = GetCell(nRow, 1);

	if (pCell == NULL)
	{
		return NULL;
	}

	CShortData * oData = (CShortData*)m_oDatas->GetAtIndex(nRow - 1);

	if (oData == NULL)
	{
		return oData;
	}

	CString bstrDataTypeID = oData->m_strDataTypeID;
	oData->PutValue(strValue);

	if (g_strGbDataTypeSet == bstrDataTypeID)
	{//定值
		CDevice *pDevice = (CDevice*)GetDevice();
		CSet *pSet = pDevice->FindSetByID(strValue);

		if (pSet != NULL)
		{
			pCell->szText = pSet->m_strName;
		}
		else
		{
			pCell->szText = strValue;
		}
	}
	else
	{
		pCell->szText = strValue;
	}

	CMacroTest *pMacroTest = (CMacroTest*)m_pItemMacroTest;
	pMacroTest->UpdateMacroTestParaData(oData, FALSE);

//	CMacroTestParaDatas *pParaUser = pMacroTest->GetFultParaDatas();//User();
//	CMacroTestParaData *pFind = (CMacroTestParaData*)pParaUser->FindMacroTestParaData(oData);
//	pParaUser->UpdateMacroTestParaData(oData, strValue, TRUE);

// 	if (pFind != NULL)
// 	{
// 		//pFind->AddMacroTestParaDataUser(strValue);
// 		pFind->SetExpression(strValue);
// 	}
// 	else
// 	{
// 		
// 	}

	Invalidate(FALSE);
	
	return oData;
}

CShortData * CMacroTestDataEditGrid::GetData(int nRow)
{
	CShortData * oData = NULL;

	if (nRow <= 0)
	{
		int nCol = 0;
		GetFocusCell(nRow, nCol);
		nRow -= 1;
	}
	else
	{
		nRow -= 1;
	}

	if (nRow >= 0)
	{
		oData = (CShortData*)m_oDatas->GetAtIndex(nRow);

	}

	return oData;
}

void CMacroTestDataEditGrid::ShowColumnTitle()
{
	SetColumnCount(3);
	SetRowCount(1);
	SetFixedRowCount(1);
	GV_ITEM Item;
	Item.state  = GVIS_READONLY;//state
	Item.mask=GVIF_FORMAT|GVIF_TEXT /*| GVIF_FGCLR|GVIF_BKCLR*/ | GVIF_DATATYPE;	
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = GVET_NOEDIT;
	Item.row = 0;
	Item.crFgClr=m_crTextColor;
	Item.crBkClr = RGB(192, 192, 192);

	Item.col = 0;
	Item.szText = CXLanguageResourceAts_AutoTest::g_sLangTxt_Name/*L"名称"*/;
	SetItem(&Item);	

	Item.col = 1;
	Item.szText = CXLanguageResourceAts_AutoTest::g_sLangTxt_Value/*L"数值"*/;
	SetItem(&Item);	

	Item.col = 2;
	Item.szText = CXLanguageResourceAts_AutoTest::g_sLangTxt_Unit/*L"单位"*/;
	SetItem(&Item);	

	CRect rc;
	GetClientRect(rc);
	long nWidth = rc.Width() - 70;
	nWidth /= 2;
	SetColumnWidth(0, nWidth+10);
	SetColumnWidth(1, nWidth-10);
	SetColumnWidth(2,50);
}

void CMacroTestDataEditGrid::SetGridRows()
{
	LONG nCount = m_oDatas->GetCount() + 1;
	SetRowCount(nCount);

	for (int i=1; i<nCount; i++)
	{
		SetRowHeight(i,22);
	}
}

BOOL CMacroTestDataEditGrid::EndEditCell(int nRow, int nCol, DWORD dwItemData)
{
	if (nCol != 1)
	{
		return FALSE;
	}

	CGridCell *pCell = GetCell(nRow, nCol);
	CShortData * oData = (CShortData*)m_oDatas->GetAtIndex(nRow - 1);

	if (oData == NULL)
	{
		return FALSE;
	}

	CString bstrDataTypeID = oData->m_strDataTypeID;
	CString strValue;

	if (IsComboMacroTestDataType(bstrDataTypeID))
	{
		if (g_strGbDataTypeSet == bstrDataTypeID)
		{//定值
			EndEditCell_Set(pCell, strValue);
		}
		else if (bstrDataTypeID == _T("iec-config"))
		{
			strValue = pCell->szText;
		}
		else
		{
			strValue.Format(L"%d", pCell->dwValue);
		}
	}
	else
	{
		strValue = pCell->szText;
	}

	oData->PutValue(strValue);
	Invalidate(FALSE);

	CMacroTest *pMacroTest = (CMacroTest*)m_pItemMacroTest;
	pMacroTest->UpdateMacroTestParaData(oData, TRUE);

	return TRUE;
}

BOOL CMacroTestDataEditGrid::EndEditCell_Set(CGridCell *pCell, CString &strValue)
{
	CDevice *pDevice = (CDevice*)GetDevice();
	CSet *pSet = pDevice->GetSetAtIndex(pCell->dwValue);

	if (pSet != NULL)
	{
		strValue = pSet->m_strID;
	}
	else
	{
		strValue = pCell->szText;
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(CMacroTestDataEditGrid, CGridCtrl)
ON_WM_SIZE()
END_MESSAGE_MAP()

void CMacroTestDataEditGrid::OnSize(UINT nType, int cx, int cy)
{
	CGridCtrl::OnSize(nType, cx, cy);

}
// 
// void CMacroTestDataEditGrid::EndEditValue(int nRow, int nCol, MacroTestGrideCellData* pCellData, CGridCell* pCell, CGridCtrl* pGrid)
// {
// 	CShortData * oData = NULL;
// 	pCellData->oData->QueryInterface(__uuidof(CShortData *),(void**)&oData);
// 	oData->PutValue((_bstr_t)pCellData->val);
// }

void CMacroTestDataEditGrid::FillComboBoxItems(int nRow, int nCol, LPARAM cltWnd)
{
	CGridCell *pCell = GetCell(nRow, nCol);
	CShortData * oDataPtr = (CShortData*)m_oDatas->GetAtIndex(nRow-1);
	ASSERT (oDataPtr != NULL);

	if (oDataPtr == NULL)
	{
		return;
	}

	CString strDataType = oDataPtr->m_strDataTypeID;
	CComboBox* pBox = (CComboBox*)cltWnd;
	pBox->ResetContent();

	if (g_strGbDataTypeSet == strDataType)
	{
		if (m_pItemMacroTest != NULL)
		{
			CDevice *pDevice = (CDevice*)GetDevice();
			pDevice->InsertSetsToComboBox(pBox);
/*
			pDevice->InsertSysParasToComboBox(pBox);
			pDevice->InsertTestParasToComboBox(pBox);
*/
		}
	}
	else if (IsComboMacroTestDataType(strDataType))
	{
		CDataTypes* oDataTypes = CGbDataTypeMngr::GetMacroTestDataTypes();
		CDataType* oDataType = (CDataType*)oDataTypes->FindByID(strDataType);

		if (oDataType != NULL)
		{
			InsertDataTypeToComboBox(oDataType, pBox);
		}
	}
	else
	{

	}
}

CGridCell* CMacroTestDataEditGrid::GetSelectedCell()
{
	int nRow =-1;
	int nCol = -1;
	GetFocusCell(nRow,nCol);

	if (nRow == -1||nCol == -1)
	{
		return NULL;
	}

	CGridCell* pCell = GetCell(nRow,nCol);
	return pCell;
}
