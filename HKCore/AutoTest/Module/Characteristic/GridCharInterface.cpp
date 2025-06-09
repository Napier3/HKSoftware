//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GridCharInterface.cpp  CGridCharInterface


#include "stdafx.h"
#include "GridCharInterface.h"

#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGridCharInterface::CGridCharInterface()
{
	//初始化属性

	//初始化成员变量
}

CGridCharInterface::~CGridCharInterface()
{

}


void CGridCharInterface::InitGrid()
{
	m_nAdjustBeginCol = -1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(CHARINTERFACE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridCharInterface::InitGridTitle()
{
	CString astrSclIecCfgTitleGIn[CHARINTERFACE_COLS] = {g_sLangTxt_Index/*_T("编号")*/,g_sLangTxt_VariableID/*_T("变量ID")*/,g_sLangTxt_Value/*_T("数值")*/};
	int iSclIecCfgWidthGin[CHARINTERFACE_COLS]={40,150,100};

	CExBaseListGrid::InitGridTitle(astrSclIecCfgTitleGIn, iSclIecCfgWidthGin, CHARINTERFACE_COLS);
}

void CGridCharInterface::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CHARCLASSID_CCHARINTERFACEVARIABLE)
	{
		return;
	}

	CCharInterfaceVariable *pVariable = (CCharInterfaceVariable*)pData;

	Show_Index(pVariable, nRow, CHARINTERFACE_COL_INDEX);
	Show_String(pVariable, nRow, CHARINTERFACE_COL_ID, &pVariable->m_strID, EndEditCell_ID);
	Show_String(pVariable, nRow, CHARINTERFACE_COL_VALUE, &pVariable->m_strValue, EndEditCell_Value);

	nRow++;
}


void CGridCharInterface::EndEditCell_Value (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

	if (*pVCellData->pString == pCell->szText)
	{
		return;
	}
	
	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	*pVCellData->pString = pCell->szText;

	if (((CExBaseListGrid*)pGrid)->GetAdjustBeginCol() >= 0)
	{
		pGrid->AutoSizeColumn(nCol);
		pGrid->ResetScrollBars();
		pGrid->InvalidateGrid(FALSE);
	}

	((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(pGrid, nRow, nCol);
}

void CGridCharInterface::EndEditCell_ID (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

	if (*pVCellData->pString == pCell->szText)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)pVCellData->pObj->GetParent();

	if (pParent == NULL)
	{
		return;
	}

	if (pParent->FindByID(pCell->szText) != NULL)
	{
		pCell->szText = pVCellData->pObj->m_strID;
		pGrid->InvalidateGrid(FALSE);
		return;
	}

	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strID = pCell->szText;
	pVCellData->pObj->m_strName = pCell->szText;
}



//////////////////////////////////////////////////////////////////////////
//

CGridCharInterfaceMap::CGridCharInterfaceMap()
{
	//初始化属性

	//初始化成员变量
}

CGridCharInterfaceMap::~CGridCharInterfaceMap()
{

}

void CGridCharInterfaceMap::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(CHARINTERFACEMAP_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CGridCharInterfaceMap::InitGridTitle()
{
	CString astrSclIecCfgTitleGIn[CHARINTERFACEMAP_COLS] = {g_sLangTxt_Index/*_T("编号")*/,g_sLangTxt_VariableID/*_T("变量ID")*/,g_sLangTxt_Value/*_T("数值")*/, g_sLangTxt_AssociationValue/*_T("关联定值")*/};


	int iSclIecCfgWidthGin[CHARINTERFACEMAP_COLS]={40,150,80, 120};

	CExBaseListGrid::InitGridTitle(astrSclIecCfgTitleGIn, iSclIecCfgWidthGin, CHARINTERFACEMAP_COLS);
}

void CGridCharInterfaceMap::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CHARCLASSID_CCHARINTERFACEVARIABLE)
	{
		return;
	}

	CCharInterfaceVariable *pVariable = (CCharInterfaceVariable*)pData;

	Show_Index(pVariable, nRow, CHARINTERFACE_COL_INDEX);
	Show_StaticString(pVariable, nRow, CHARINTERFACE_COL_ID, &pVariable->m_strID);

	if (pVariable->m_strScript.GetLength() > 5)
	{
		Show_StaticString(pVariable, nRow, CHARINTERFACE_COL_SCRIPT, &pVariable->m_strScript);
		
		if (!CharVar_CalScriptValue(pVariable))
		{
			SetItemFgColour(nRow, CHARINTERFACE_COL_SCRIPT, RGB(255, 0, 0));
		}
		else
		{
			SetItemFgColour(nRow, CHARINTERFACE_COL_SCRIPT, RGB(0, 0, 0));
		}
		

		Show_StaticString(pVariable, nRow, CHARINTERFACE_COL_VALUE, &pVariable->m_strValue);
	}
	else
	{
		Show_StaticString(pVariable, nRow, CHARINTERFACE_COL_SCRIPT, &pVariable->m_strScript);//, EndEditCell_Script);
		Show_String(pVariable, nRow, CHARINTERFACE_COL_VALUE, &pVariable->m_strValue, EndEditCell_Value);
	}

	nRow++;
}

void CGridCharInterfaceMap::EndEditCell_Script (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{

}
