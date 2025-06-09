#include "StdAfx.h"
#include "DsvScriptEditGrid.h"
#include "..\..\XLanguage\XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CDsvScriptEditGrid
long CDsvScriptEditGrid::g_nDsvScriptAttrRef = 0;
CDataType *CDsvScriptEditGrid::g_pDsvAnyElementDataType = NULL;

void CDsvScriptEditGrid::CreateDsvAnyElementDataType()
{
	g_nDsvScriptAttrRef++;

	if (g_nDsvScriptAttrRef == 1)
	{
		g_pDsvAnyElementDataType = new CDataType();
		g_pDsvAnyElementDataType->m_strName = ANLYELEMENT_MODE_DATATYPE;
		g_pDsvAnyElementDataType->m_strID   = ANLYELEMENT_MODE_DATATYPE;
		g_pDsvAnyElementDataType->AddNewValue(g_sLangTxt_ArbitrElement/*_T("任意元素")*/, DSV_ANYELEMENT_MODE_ANY, _T("0"));
		g_pDsvAnyElementDataType->AddNewValue(g_sLangTxt_SpecifiedElement/*_T("指定的元素")*/, DSV_ANYELEMENT_MODE_DEFINE, _T("1"));
		g_pDsvAnyElementDataType->AddNewValue(g_sLangTxt_SequDefinElemIn/*_T("序列定义中的元素")*/, DSV_ANYELEMENT_MODE_IN_SEQUENCE, _T("2"));
		g_pDsvAnyElementDataType->AddNewValue(g_sLangTxt_SequDefinElemOut/*_T("序列定义之外的元素")*/, DSV_ANYELEMENT_MODE_OUT_SEQUENCE, _T("3"));
		g_pDsvAnyElementDataType->AddNewValue(g_sLangTxt_ReferElements/*_T("引用元素")*/, DSV_ANYELEMENT_MODE_REFERENCE, _T("4"));


	}
}

void CDsvScriptEditGrid::ReleaseDsvAnyElementDataType()
{
	g_nDsvScriptAttrRef--;

	if (g_nDsvScriptAttrRef == 0)
	{
		delete g_pDsvAnyElementDataType;
		g_pDsvAnyElementDataType = NULL;
	}
}

CDsvScriptEditGrid::CDsvScriptEditGrid()
{
	m_pAttrEditGrid = NULL;
	m_nAdjustBeginCol = 0;
	m_pDsvScriptDlgInterface = NULL;
	CreateDsvAnyElementDataType();
}


CDsvScriptEditGrid::~CDsvScriptEditGrid(void)
{
	ReleaseDsvAnyElementDataType();
}


void CDsvScriptEditGrid::SetEditDvData(CExBaseObject *pData)
{
	ASSERT( pData != NULL);

	CDsvElement *pDsvElement = (CDsvElement*)GetCurrSelData(1);

	if (pDsvElement == NULL)
	{
		return;
	}

	int nRow = m_pDatas->FindIndex(pDsvElement);

	if (nRow == -1)
	{
		return;
	}

	pDsvElement->m_strName = pData->m_strName;
	pDsvElement->m_strID   = pData->m_strID;
	nRow++;
	ShowData(pDsvElement, nRow, FALSE);

	AutoSizeColumn(DSV_ELEMENT_COL_NAME);
	AutoSizeColumn(DSV_ELEMENT_COL_ID);
	Invalidate(FALSE);
}

void CDsvScriptEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DSV_ELEMENT_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDsvScriptEditGrid::ShowDatas(CExBaseList *pExDataList)
{
	CExBaseListGrid::ShowDatas(pExDataList);

// 	AutoSizeColumn(DSV_ELEMENT_COL_INDEX);
// 	AutoSizeColumn(DSV_ELEMENT_COL_NAME);
// 	AutoSizeColumn(DSV_ELEMENT_COL_ID);
// 	AutoSizeColumn(DSV_ELEMENT_COL_MINOCC);
// 	AutoSizeColumn(DSV_ELEMENT_COL_MAXOCC);
}

void CDsvScriptEditGrid::InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	CExBaseListGrid::InsertData(pData, bInvalidate);

// 	AutoSizeColumn(DSV_ELEMENT_COL_NAME);
// 	AutoSizeColumn(DSV_ELEMENT_COL_ID);
// 	AutoSizeColumn(DSV_ELEMENT_COL_MINOCC);
// 	AutoSizeColumn(DSV_ELEMENT_COL_MAXOCC);

	Invalidate(FALSE);
}

CDataType* CDsvScriptEditGrid::FindDataType(const CString &strDataType)
{
	return g_pDsvAnyElementDataType;
}

void  CDsvScriptEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
	if (m_pAttrEditGrid != NULL)
	{
		CDsvElement *pDsvElement = (CDsvElement*)GetData(nRow);

		if (pDsvElement != NULL)
		{
			m_pAttrEditGrid->ShowDatas(pDsvElement);
		}
	}

	if (m_pDsvScriptDlgInterface != NULL)
	{
		m_pDsvScriptDlgInterface->SetCurrDsvScriptEditInterface(this);
	}

	return CExBaseListGrid::OnEditCell(nRow, nCol, nChar);
}

void CDsvScriptEditGrid::InitGridTitle()
{
	CString cTempStr[DSV_ELEMENT_COLS]={g_sLangTxt_SerNumber/*_T("序号")*/,g_sLangTxt_Name/*_T("名称")*/,_T("ID"),g_sLangTxt_MinTime/*_T("最小次数")*/,g_sLangTxt_MaxTime/*_T("最大次数")*/};
	int iWidth[DSV_ELEMENT_COLS]={60,120, 200, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DSV_ELEMENT_COLS);
}	


void CDsvScriptEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (DVMCLASSID_CDSVELEMENT == nClassID)
	{
		CDsvElement *pDsvElement = (CDsvElement *)pData;

		Show_Index(pData, nRow, DSV_ELEMENT_COL_INDEX);

		Show_String(pData, nRow, DSV_ELEMENT_COL_NAME, &pDsvElement->m_strName);
		Show_String(pData, nRow, DSV_ELEMENT_COL_ID, &pDsvElement->m_strID);
		Show_Long(pData, nRow, DSV_ELEMENT_COL_MINOCC, &pDsvElement->m_nMinOcc);
		Show_Long(pData, nRow, DSV_ELEMENT_COL_MAXOCC, &pDsvElement->m_nMaxOcc);

		nRow++;
	}
	else if (DVMCLASSID_CDSVANYELEMENT == nClassID)
	{
		CDsvAnyElement *pDsvElement = (CDsvAnyElement *)pData;

		Show_Index(pData, nRow, DSV_ELEMENT_COL_INDEX);

		Show_StaticString(pData, nRow, DSV_ELEMENT_COL_NAME, &pDsvElement->m_strName);
		Show_DataType_Val(pData, nRow, DSV_ELEMENT_COL_ID,ANLYELEMENT_MODE_DATATYPE, &pDsvElement->m_strMode);
		Show_Long(pData, nRow, DSV_ELEMENT_COL_MINOCC, &pDsvElement->m_nMinOcc);
		Show_Long(pData, nRow, DSV_ELEMENT_COL_MAXOCC, &pDsvElement->m_nMaxOcc);

		nRow++;
	}
	else
	{
		return;
	}

	
}


//////////////////////////////////////////////////////////////////////////
//CDsvScriptAttrEditGrid
long CDsvScriptAttrEditGrid::g_nDsvScriptAttrRef = 0;
CDataType* CDsvScriptAttrEditGrid::g_pDsvAttrDataType = NULL;
CDataType* CDsvScriptAttrEditGrid::g_pDsvAttrOptr = NULL;
CDataType* CDsvScriptAttrEditGrid::g_pDsvAttrAttrs = NULL;
CDataType* CDsvScriptAttrEditGrid::g_pDsvAttrAttrsAll = NULL;
CDataType* CDsvScriptAttrEditGrid::g_pDsvAttrVariables = NULL;

CDsvScriptAttrEditGrid::CDsvScriptAttrEditGrid()
{
	m_pDsvScriptDlgInterface = NULL;
	m_nAdjustBeginCol = 0;
	g_nDsvScriptAttrRef++;

	if (g_nDsvScriptAttrRef == 1)
	{
		InitDsvAttrDataType();
	}
}


CDsvScriptAttrEditGrid::~CDsvScriptAttrEditGrid(void)
{
	g_nDsvScriptAttrRef--;

	if (g_nDsvScriptAttrRef == 0)
	{
		delete g_pDsvAttrDataType;
		g_pDsvAttrDataType = NULL;

		delete g_pDsvAttrOptr;
		g_pDsvAttrOptr = NULL;

		delete g_pDsvAttrAttrs;
		g_pDsvAttrAttrs = NULL;

		delete g_pDsvAttrAttrsAll;
		g_pDsvAttrAttrsAll = NULL;

		delete g_pDsvAttrVariables;
		g_pDsvAttrVariables = NULL;
	}
}

void CDsvScriptAttrEditGrid::SetEditDvData(CExBaseObject *pData)
{
	ASSERT( pData != NULL);

	CDsvElemAttr *pDsvElemAttr = (CDsvElemAttr*)GetCurrSelData(1);

	if (pDsvElemAttr == NULL)
	{
		return;
	}

	int nRow = m_pDatas->FindIndex(pDsvElemAttr);

	if (nRow == -1)
	{
		return;
	}

	pDsvElemAttr->m_strValue = pData->m_strID;
	nRow++;
	ShowData(pDsvElemAttr, nRow, FALSE);
	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_VALUE);
	Invalidate(FALSE);
}

void CDsvScriptAttrEditGrid::InitDsvAttrDataType()
{
	g_pDsvAttrVariables = new CDataType();

	g_pDsvAttrAttrsAll = new CDataType();

	g_pDsvAttrAttrs = new CDataType();
	g_pDsvAttrAttrs->AddNewValue(g_sLangTxt_Name/*_T("名称")*/, _T("name"), _T("0"));
	g_pDsvAttrAttrs->AddNewValue(_T("ID"), _T("id"), _T("1"));
	g_pDsvAttrAttrs->AddNewValue(g_sLangTxt_Values/*_T("值")*/, _T("value"), _T("2"));
	g_pDsvAttrAttrs->AddNewValue(g_sLangTxt_Time/*_T("时间")*/, _T("time"), _T("3"));

	g_pDsvAttrDataType = new CDataType();
	g_pDsvAttrDataType->AddNewValue(g_sLangTxt_Integer/*_T("整数")*/, _T("int"), _T("0"));
	g_pDsvAttrDataType->AddNewValue(g_sLangTxt_FloatNumber/*_T("浮点数")*/, _T("float"), _T("1"));
	g_pDsvAttrDataType->AddNewValue(g_sLangTxt_CharacterString/*_T("字符串")*/, _T("string"), _T("2"));
	g_pDsvAttrDataType->AddNewValue(g_sLangTxt_Time/*_T("时间")*/, _T("date"), _T("3"));
	
	g_pDsvAttrOptr = new CDataType();
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_Equal/*_T("等于")*/, _T("=="), _T("0"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_LessThan/*_T("小于")*/, _T("<"), _T("1"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_LessOrEqual/*_T("小于等于")*/, _T("<="), _T("2"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_MoreThan/*_T("大于")*/, _T(">"), _T("3"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_MoreOrEqual/*_T("大于等于")*/, _T(">="), _T("4"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_NotEqual/*_T("不等于")*/, _T("!="), _T("5"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_CharStringIncl/*_T("字符串包含")*/, _T("[]"), _T("6"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_CharStringNIncl/*_T("字符串不包含")*/, _T("![]"), _T("7"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_NumberRange/*_T("数值范围")*/, _T("<>"), _T("8"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_BoundNumRange/*_T("数值范围带边界")*/, _T("<=>"), _T("9"));
	g_pDsvAttrOptr->AddNewValue(g_sLangTxt_DataVarAss/*_T("数据变量赋值")*/, _T("++"), _T("10"));
}


void CDsvScriptAttrEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DSV_ELEMENT_ATTR_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDsvScriptAttrEditGrid::ShowDatas(CExBaseList *pExDataList)
{
	m_pDatas = pExDataList;
	InitDsvAttrAttrs();

	CExBaseListGrid::ShowDatas(pExDataList);

// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_INDEX);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_ID);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_TYPE);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_OPTR);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_VALUE);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_VALUE2);
}

void CDsvScriptAttrEditGrid::InitDsvAttrVariables()
{
	g_pDsvAttrVariables->DeleteAll();
	g_pDsvAttrVariables->AddNewValue(g_sLangTxt_None/*_T("无")*/, _T(""), _T("0"));

	if (m_pDsvScriptDlgInterface != NULL)
	{
		m_pDsvScriptDlgInterface->InitAttrVariableDataType(g_pDsvAttrVariables);
	}
}

void CDsvScriptAttrEditGrid::InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	CExBaseListGrid::InsertData(pData, bInvalidate);

// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_ID);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_TYPE);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_OPTR);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_VALUE);
// 	AutoSizeColumn(DSV_ELEMENT_ATTR_COL_VALUE2);

	Invalidate(FALSE);
}

void CDsvScriptAttrEditGrid::InitGridTitle()
{
	CString cTempStr[DSV_ELEMENT_ATTR_COLS]={g_sLangTxt_SerNumber/*_T("序号")*/,g_sLangTxt_PropertyID/*_T("属性ID")*/,g_sLangTxt_DataType/*_T("数据类型")*/,g_sLangTxt_FunctionalSymbol/*_T("操作符号")*/,g_sLangTxt_Data/*_T("数据")*/,g_sLangTxt_Data2/*_T("数据2")*/, g_sLangTxt_ResultVariable/*_T("结果变量")*/};
	int iWidth[DSV_ELEMENT_ATTR_COLS]={60,100, 100, 100, 100, 100, 100};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DSV_ELEMENT_ATTR_COLS);
}	

void CDsvScriptAttrEditGrid::InitDsvAttrAttrs()
{
	InitDsvAttrVariables();

	g_pDsvAttrAttrsAll->DeleteAll();
	g_pDsvAttrAttrsAll->AppendClone(g_pDsvAttrAttrs);

	if (m_pDsvScriptDlgInterface != NULL)
	{
		m_pDsvScriptDlgInterface->InitAttrDataType(g_pDsvAttrAttrsAll, m_pDatas);
	}
}

void CDsvScriptAttrEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	ASSERT (DVMCLASSID_CDSVELEMATTR == nClassID);
	CDsvElemAttr *pDsvElemAttr = (CDsvElemAttr *)pData;
	//InitDsvAttrAttrs();
	CDsvElement *pElement = (CDsvElement*)pDsvElemAttr->GetParent();

	Show_Index(pData, nRow, DSV_ELEMENT_ATTR_COL_INDEX);

	if (pElement->IsAnyDsvObject())
	{
		Show_StaticString(pData, nRow, DSV_ELEMENT_ATTR_COL_TYPE,      &pDsvElemAttr->m_strName);
		Show_StaticString(pData, nRow, DSV_ELEMENT_ATTR_COL_ID,    &pDsvElemAttr->m_strID);
		Show_StaticString(pData, nRow, DSV_ELEMENT_ATTR_COL_OPTR,    &pDsvElemAttr->m_strOptr);
		Show_StaticString(pData, nRow, DSV_ELEMENT_ATTR_COL_VALUE,   &pDsvElemAttr->m_strValue);
		Show_StaticString(pData, nRow, DSV_ELEMENT_ATTR_COL_VALUE2,  &pDsvElemAttr->m_strValue2);
		Show_StaticString(pData, nRow, DSV_ELEMENT_ATTR_COL_VARIABLE,&pDsvElemAttr->m_strVariable);
	}
	else
	{
		Show_DataType_Val(pData, nRow, DSV_ELEMENT_ATTR_COL_ID,     g_pDsvAttrAttrsAll, &pDsvElemAttr->m_strID,       EndEditCell_AttrID);
		Show_DataType_Val(pData, nRow, DSV_ELEMENT_ATTR_COL_TYPE,   g_pDsvAttrDataType, &pDsvElemAttr->m_strDataType, EndEditCell_AttrDataType);
		Show_DataType_Val(pData, nRow, DSV_ELEMENT_ATTR_COL_OPTR,   g_pDsvAttrOptr , &pDsvElemAttr->m_strOptr,     EndEditCell_AttrOptr);
		Show_String(pData, nRow,   DSV_ELEMENT_ATTR_COL_VALUE,  &pDsvElemAttr->m_strValue);
		Show_String(pData, nRow,   DSV_ELEMENT_ATTR_COL_VALUE2, &pDsvElemAttr->m_strValue2);
		Show_DataType_Val(pData, nRow, DSV_ELEMENT_ATTR_COL_VARIABLE,     g_pDsvAttrVariables, &pDsvElemAttr->m_strVariable,       EndEditCell_Variable);
	}

	nRow++;
}


void CDsvScriptAttrEditGrid::EndEditCell_AttrID (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CDsvElemAttr *pDsvElemAttr = (CDsvElemAttr *)pVellData->pObj;
	ASSERT (pDsvElemAttr != NULL);

	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

	CDsvElement *pDsvElement = (CDsvElement*)pDsvElemAttr->GetParent();

	if (pVellData->nVt == VCD_STRING)
	{
		if (*(pVellData->pString) == _T("name"))
		{
			pDsvElemAttr->m_strValue = pDsvElement->m_strName;
			pGrid->SetItemText(nRow,   DSV_ELEMENT_ATTR_COL_VALUE,  pDsvElemAttr->m_strValue);
		}
		else if (*(pVellData->pString) == _T("id"))
		{
			pDsvElemAttr->m_strValue = pDsvElement->m_strID;
			pGrid->SetItemText(nRow,   DSV_ELEMENT_ATTR_COL_VALUE,  pDsvElemAttr->m_strValue);
		}
	}
}


void CDsvScriptAttrEditGrid::EndEditCell_AttrDataType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CDsvElemAttr *pDsvElemAttr = (CDsvElemAttr *)pVellData->pObj;
	ASSERT (pDsvElemAttr != NULL);

	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

// 	CDataTypeValue *pVal = g_pDsvAttrDataType->FindByIndex(pDsvElemAttr->m_strDataType);
// 
// 	if (pVal == NULL)
// 	{
// 		pVal = (CDataTypeValue*)g_pDsvAttrDataType->GetHead();
// 	}
// 
// 	pDsvElemAttr->m_strDataType = pVal->m_strID;
}

void CDsvScriptAttrEditGrid::EndEditCell_AttrOptr (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CDsvElemAttr *pDsvElemAttr = (CDsvElemAttr *)pVellData->pObj;
	ASSERT (pDsvElemAttr != NULL);

	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);

// 	CDataTypeValue *pVal = (CDataTypeValue*)g_pDsvAttrOptr->FindByIndex(pDsvElemAttr->m_strOptr);
// 
// 	if (pVal == NULL)
// 	{
// 		pVal = (CDataTypeValue*)g_pDsvAttrOptr->GetHead();
// 	}
// 	
// 	pDsvElemAttr->m_strOptr = pVal->m_strID;
}


void CDsvScriptAttrEditGrid::EndEditCell_Variable (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CDsvElemAttr *pDsvElemAttr = (CDsvElemAttr *)pVellData->pObj;
	ASSERT (pDsvElemAttr != NULL);

	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
}

void  CDsvScriptAttrEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
// 	if (m_pAttrEditGrid != NULL)
// 	{
// 		CDsvElement *pDsvElement = (CDsvElement*)GetData(nRow);
// 
// 		if (pDsvElement != NULL)
// 		{
// 			m_pAttrEditGrid->ShowDatas(pDsvElement);
// 		}
// 	}

	if (m_pDsvScriptDlgInterface != NULL)
	{
		m_pDsvScriptDlgInterface->SetCurrDsvScriptEditInterface(this);
	}

	return CExBaseListGrid::OnEditCell(nRow, nCol, nChar);
}


//////////////////////////////////////////////////////////////////////////
//CDsvScriptEditGrid

CDsvScriptEliminateEditGrid::CDsvScriptEliminateEditGrid()
{
	m_nAdjustBeginCol = 0;
	m_pDsvScriptDlgInterface = NULL;
}

CDsvScriptEliminateEditGrid::~CDsvScriptEliminateEditGrid(void)
{

}

void CDsvScriptEliminateEditGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(DSV_ELIMINATE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CDsvScriptEliminateEditGrid::InsertData(CExBaseObject *pData, BOOL bInvalidate)
{
	CExBaseListGrid::InsertData(pData, bInvalidate);

	Invalidate(FALSE);
}

void  CDsvScriptEliminateEditGrid::OnEditCell(int nRow, int nCol, UINT nChar)
{
	if (m_pDsvScriptDlgInterface != NULL)
	{
		m_pDsvScriptDlgInterface->SetCurrDsvScriptEditInterface(this);
	}

	return CExBaseListGrid::OnEditCell(nRow, nCol, nChar);
}

void CDsvScriptEliminateEditGrid::InitGridTitle()
{
	CString cTempStr[DSV_ELIMINATE_COLS]={g_sLangTxt_SerNumber/*_T("序号")*/,g_sLangTxt_Name/*_T("名称")*/,_T("ID")};
	int iWidth[DSV_ELIMINATE_COLS]={60,120, 200};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, DSV_ELIMINATE_COLS);
}	


void CDsvScriptEliminateEditGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	Show_Index(pData, nRow, DSV_ELIMINATE_COL_INDEX);

	Show_StaticString(pData, nRow, DSV_ELIMINATE_COL_NAME, &pData->m_strName);
	Show_StaticString(pData, nRow, DSV_ELIMINATE_COL_ID, &pData->m_strID);

	nRow++;
}


void CDsvScriptEliminateEditGrid::SetEditDvData(CExBaseObject *pData)
{
	ASSERT( pData != NULL);

	CExBaseObject *pDsvElement = (CExBaseObject*)GetCurrSelData(1);

	if (pDsvElement == NULL)
	{
		return;
	}

	int nRow = m_pDatas->FindIndex(pDsvElement);

	if (nRow == -1)
	{
		return;
	}

	pDsvElement->m_strName = pData->m_strName;
	pDsvElement->m_strID   = pData->m_strID;
	nRow++;
	ShowData(pDsvElement, nRow, FALSE);

	AutoSizeColumn(DSV_ELEMENT_COL_NAME);
	AutoSizeColumn(DSV_ELEMENT_COL_ID);
	Invalidate(FALSE);
}

