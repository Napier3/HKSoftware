#include "StdAfx.h"
#include "SysParaGrid.h"
#include <math.h>
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSysParaGrid::CSysParaGrid(void)
{
	ResetVaraibles();
}

void CSysParaGrid::ResetVaraibles()
{
	m_pShortDatas = NULL;
	m_pCurVectorSet = NULL;
	m_pValues = NULL;
}

CSysParaGrid::~CSysParaGrid(void)
{
}

void CSysParaGrid::InitGrid(BOOL bEditable)
{
	SetListMode(TRUE);
//	EnableDragAndDrop(TRUE);
	SetTextBkColor(RGB(0x0FF, 0x0FF, 0x0E0));
//	m_oColumns.DeleteAll();
	DeleteAllItems();
	SetRowCount(1);
	SetColumnCount(4);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);

	InitGridTitle();

	ResetScrollBars();
}

void CSysParaGrid::InitGridTitle()
{
	int iNum=4;
	CString cTempStr[6]={g_sLangTxt_ParaName/*"参数名称"*/
		               ,g_sLangTxt_ParaVarious/*"参数变量"*/
					   ,g_sLangTxt_ParaValue/*"参数值"*/
					   ,g_sLangTxt_Unit/*"单位"*/
					   ,g_sLangTxt_DataType/*"数据类型"*/
					   ,g_sLangTxt_Format/*"格式"*/};
	int  iColType[6]={GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT,GVET_NOEDIT};
	int nColWidth[6] = {200, 100, 100, 60, 100, 100};

	GV_ITEM Item;
	Item.mask = GVIF_FORMAT|GVIF_TEXT|GVIF_PARAM;
	Item.row = 0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	for (int iCol=0;iCol<iNum;iCol++)
	{
		Item.col = iCol+0;
		SetColumnType(iCol,iColType[iCol]);
		Item.szText=cTempStr[iCol];
		Item.lParam=iCol;
		SetItem(&Item);
		SetColumnWidth(iCol, nColWidth[iCol]);
	}	

	SetRowHeight(0,20);
}

//用于定值、软压板、控制字
void CSysParaGrid::InitVariables_Sets(CExBaseList *pDatas, CValues * pValues)
{
	m_pListDatas = pDatas;

	if (pDatas == NULL/* || pValues == NULL*/)
	{
		return;
	}

	m_pValues = pValues;

	UpdateVariables_Dataset();

	ResetScrollBars();
}

void CSysParaGrid::InitVariables_Dataset(CExBaseList *pSets, CValues * pValues)
{
	ResetVaraibles();

	if (pSets == NULL/* || pValues == NULL*/)
	{
		return;
	}

	m_pCurVectorSet = pSets;
	m_pValues = pValues;

	UpdateVariables_Dataset();

	ResetScrollBars();
}

//用于系统参数和测试参数
void CSysParaGrid::InitVariables_Datas(CExBaseList* pShortDatas,CValues * pValues)
{
	ResetVaraibles();

	if (pValues == NULL || pShortDatas == NULL)
	{
		return;
	}

	m_pShortDatas = pShortDatas;
	m_pValues = pValues;

	UpdateVariables1();

	ResetScrollBars();
}

void CSysParaGrid::UpdateVariables()
{
	if (m_pCurVectorSet != NULL && m_pValues != NULL)
	{
		UpdateVariables2();
	}
	else if (m_pShortDatas != NULL && m_pValues != NULL)
	{
		UpdateVariables1();
	}
}

void CSysParaGrid::UpdateVariables1()
{
	CValue * ParaObject = NULL;
	CShortData * pShortData = NULL;
	long nIndex = 0;
	long nRows = 0;
	long nCount = m_pShortDatas->GetCount();
	SetRowCount(nCount + 1);

	for (nIndex=0;nIndex<nCount;nIndex++)
	{
		pShortData = (CShortData*)m_pShortDatas->GetAtIndex(nIndex);
		nRows++;
		ShowOneParaObject(pShortData,nRows/*,ParaObject->m_strValue*/);
	}
}

void CSysParaGrid::UpdateVariables2()
{
// 	CSet* pSet;
// 	long nRows = 0;
// 	CValue * pValue = NULL;
// 	long nCount = m_pCurVectorSet->GetCount();
// 	SetRowCount(nCount + 1);
// 	CString strID;
// 
// 	for(long nIndex=0;nIndex<nCount;nIndex++)
// 	{
// 		pSet = (CSet*)m_pCurVectorSet->GetAtIndex(nIndex);
// 		nRows++;
// 		ShowOneParaObject(pSet, nRows/*,pValue->m_strValue*/);
// 	}
}

void CSysParaGrid::UpdateVariables_Dataset()
{
	CDataObj* pData = NULL;
	long nRows = 0;
	CValue * pValue = NULL;
	long nCount = m_pCurVectorSet->GetCount();
	SetRowCount(nCount + 1);
	CString strID;

	for(long nIndex=0;nIndex<nCount;nIndex++)
	{
		pData = (CDataObj*)m_pCurVectorSet->GetAtIndex(nIndex);
		nRows++;
		ShowOneData(pData, nRows/*,pValue->m_strValue*/);
	}
}
void CSysParaGrid::InitGvItem(GV_ITEM &Item)
{
	Item.mask=GVIF_FORMAT|GVIF_PARAM|GVIF_TEXT | GVIF_FGCLR|GVIF_BKCLR | GVIF_DATATYPE;	
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = 0;
	Item.crBkClr=RGB(200, 251, 196);
	Item.crFgClr=RGB(0,0,255);

}

void CSysParaGrid::InitValueColor(const CString &strValue, const CString &strDefValue, GV_ITEM &Item)
{
	//if (fabs (CString_To_double(ParaObject->m_strValue) - CString_To_double(ParaObject->m_strDefaultValue)) < 0.001)
	if (strValue != strDefValue)
	{
		Item.crBkClr=RGB(170, 221, 166);
	}
}

void CSysParaGrid::ShowOneParaObject(CShortData * ParaObject,long nRow/*,_bstr_t strValue*/)
{
	GV_ITEM Item;
	InitGvItem(Item);

	Item.lParam = nRow;
	Item.row = nRow;	
	Item.col = 0;
	Item.szText = ParaObject->m_strName;
	SetItem(&Item);	

	Item.col++;
	Item.szText = ParaObject->m_strID;
	SetItem(&Item);

	Item.nDataType = GVET_CreateDataTyp(GVET_EDITBOX, 0);
	Item.col++;
	Item.szText = ParaObject->m_strValue;
	InitValueColor(ParaObject->m_strValue, ParaObject->m_strDefaultValue, Item);
	SetItem(&Item);

	InitGvItem(Item);
	Item.col++;
	Item.szText = ParaObject->m_strUnit;
	SetItem(&Item);

	Item.col++;
	Item.szText = ParaObject->m_strDataTypeID;
	SetItem(&Item);

	SetRowHeight(nRow,20);
}
// 
// void CSysParaGrid::ShowOneParaObject(CSet* pSet,long nRow/*,_bstr_t strValue*/)
// {
// 	GV_ITEM Item;
// 	InitGvItem(Item);
// 
// 	Item.lParam = nRow;
// 	Item.row = nRow;	
// 	Item.col = 0;
// 	Item.szText = pSet->m_strName;
// 	SetItem(&Item);	
// 
// 	Item.col++;
// 	Item.szText = pSet->m_strID;
// 	SetItem(&Item);
// 
// 	Item.nDataType = GVET_CreateDataTyp(GVET_EDITBOX, 0);
// 	Item.col++;
// 	Item.szText = pSet->m_strValue;
// 	InitValueColor(pSet->m_strValue, pSet->m_strDefaultValue, Item);
// 	SetItem(&Item);
// 
// 	InitGvItem(Item);
// 	Item.col++;
// 	Item.szText = pSet->m_strUnit;
// 	SetItem(&Item);
// 
// 	Item.col++;
// 	Item.szText = pSet->m_strDataType;
// 	SetItem(&Item);
// 
// 	SetRowHeight(nRow,20);
// }

void CSysParaGrid::ShowOneData(CDataObj* pData,long nRow/*,_bstr_t strValue*/)
{
	GV_ITEM Item;
	InitGvItem(Item);

	Item.lParam = nRow;
	Item.row = nRow;	
	Item.col = 0;
	Item.szText = pData->m_strName;
	SetItem(&Item);	

	Item.col++;
	Item.szText = pData->m_strID;
	SetItem(&Item);

	CDataType *pDataType = pData->GetDataType();
	Item.nDataType = GVET_CreateDataTyp(GVET_EDITBOX, 0);
	CString strValueText = pData->m_strValue;

	if (pDataType != NULL)
	{
		if (pDataType->GetCount() > 1)
		{
			Item.nDataType = GVET_CreateDataTyp(GVET_COMBOBOX, 0);
			CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByID(pData->m_strValue);

			if (pValue != NULL)
			{
				strValueText = pValue->m_strName;
			}
		}
	}

	Item.col++;
	Item.szText = strValueText;
	InitValueColor(pData->m_strValue, pData->m_strDefaultValue, Item);
	SetItem(&Item);

	InitGvItem(Item);
	Item.col++;
	Item.szText = pData->m_strUnit;
	SetItem(&Item);

	Item.col++;
	Item.szText = pData->m_strDataType;
	SetItem(&Item);

	SetRowHeight(nRow,20);
}

void CSysParaGrid::SetShortDataValue(long nRow,long nCol)
{
	CValue * ParaObject = NULL;
	CShortData * pShortData = NULL;
	CString str;

	pShortData = (CShortData*)m_pShortDatas->GetAtIndex(nRow-1);

	if(pShortData == NULL)
		return;

	pShortData->m_strValue = GetItemText(nRow,nCol);
	ParaObject = (CValue*)pShortData->m_dwItemData;

	if(ParaObject == NULL)
		return;

	ParaObject->PutValue(pShortData->m_strValue);
}

//用于定值、软压板、控制字
//修改后的消息响应
void CSysParaGrid::SetVectorDataValue(long nRow,long nCol)
{
// 	CValue * pValue = NULL;
// 	CSet* pSet = NULL;
// 	CString str;
// 
// 	//获取修改后的值
// 	str = GetItemText(nRow,nCol);
// 
// 	pSet = (CSet*)m_pCurVectorSet->GetAtIndex(nRow-1);
// 	pSet->m_strValue = str;
// 
// 	pValue = (CValue*)pSet->m_dwItemData;
// 
// 	if(pValue != NULL)
// 	{
// 		pValue->PutValue(str);
// 	}
}


void CSysParaGrid::FillComboBoxItems(int nRow, int nCol, LPARAM lParam)
{
	CDataObj* pData = NULL;
	pData = (CDataObj*)m_pCurVectorSet->GetAtIndex(nRow-1);
	CDataType *pDataType = pData->GetDataType();
	
	CComboBox *pComboBox = (CComboBox*)lParam;
	pDataType->InsertChildreComboBox(pComboBox);
}

void CSysParaGrid::OnEndEdit(long nRow,long nCol)
{
	CValue * pValue = NULL;
	CDataObj* pData = NULL;
	CString str;

	//获取修改后的值
	str = GetItemText(nRow,nCol);

	pData = (CDataObj*)m_pCurVectorSet->GetAtIndex(nRow-1);
	CDataType *pDataType = pData->GetDataType();
	
	//2019-4-7  修改值的时候，修改子对象的值
	//pData->m_strValue = str;
	pData->SetValue(str);
	pValue = (CValue*)pData->m_dwItemData;

	if (pDataType != NULL)
	{
		if (pDataType->GetCount() > 0)
		{
			CDataTypeValue *pDtValue = (CDataTypeValue*)pDataType->FindByName(str);

			if (pDtValue != NULL)
			{
				pData->m_strValue  = pDtValue->m_strID;
			}
		}
	}

	if(pValue != NULL)
	{
		pValue->PutValue(pData->m_strValue);
	}
}

