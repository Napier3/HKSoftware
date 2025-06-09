// PtAtsExprCalGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "PtAtsExprCalGrid.h"
#include "..\ParaMapExpr.h"
#include "..\MacroMaps.h"

// #include "..\PtAtsMacroMap.h"

#define EXPRCAL_TABLE_COLS   4    

//extern CString _GetAuditFolderPath(const CString &strFolderPath, bool bBackSlash);
// CPtAtsExprCalGrid
CPtAtsExprCalGrid::CPtAtsExprCalGrid()
{
	m_nAdjustBeginCol = 1;
}

CPtAtsExprCalGrid::~CPtAtsExprCalGrid()
{
	
}

// CPtAtsExprCalGrid 成员函数
void CPtAtsExprCalGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(EXPRCAL_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CPtAtsExprCalGrid::InitGridTitle()
{
	CString astrGridTitle[EXPRCAL_TABLE_COLS] = {_T("编号"), _T("Ats参数名称"), _T("Ats参数ID"), _T("计算表达式")};
	int  iColType[EXPRCAL_TABLE_COLS]={GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT};
	int iGridWidth[EXPRCAL_TABLE_COLS]={40, 100, 100, 100};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, EXPRCAL_TABLE_COLS);
}

void CPtAtsExprCalGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);
	CParaMapCal* pExprCal = (CParaMapCal*)pData;

	if (pExprCal == NULL)
	{
		return;
	}

	Show_Index(pExprCal, nRow, 0);//编号
	Show_String(pExprCal, nRow, 1, &pExprCal->m_strMapName);
	Show_String(pExprCal, nRow, 2, &pExprCal->m_strMapID);
	Show_String(pExprCal, nRow, 3, &pExprCal->m_strScript);

	nRow++;
}

BOOL CPtAtsExprCalGrid::UpdateData(CExBaseObject *pData)
{
	//获取验证更新节点在当前grid节点的序号
	int nRow = GetDataRow(pData);

	if (nRow != -1)
	{
		ShowData(pData, nRow, FALSE);
		Invalidate(FALSE);
	}
	else
	{
	}

	return TRUE;
}

void CPtAtsExprCalGrid::SetMidifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	CMacroMaps *pMaps = (CMacroMaps*)pData->GetAncestor(MPCLASSID_CMACROMAPS);
	pMaps->SetModifiedFlag(bModified);
}

