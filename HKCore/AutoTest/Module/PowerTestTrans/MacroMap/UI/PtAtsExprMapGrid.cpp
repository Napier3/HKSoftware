// PtAtsExprMapGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "PtAtsExprMapGrid.h"
#include "..\ParaMapExpr.h"
#include "..\MacroMaps.h"

// #include "..\PtAtsMacroMap.h"

#define EXPRMAP_TABLE_COLS   4    

//extern CString _GetAuditFolderPath(const CString &strFolderPath, bool bBackSlash);
// CPtAtsExprMapGrid
CPtAtsExprMapGrid::CPtAtsExprMapGrid()
{
	m_nAdjustBeginCol = 1;
}

CPtAtsExprMapGrid::~CPtAtsExprMapGrid()
{
	
}

BEGIN_MESSAGE_MAP(CPtAtsExprMapGrid, CExBaseListGrid)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CPtAtsExprMapGrid 成员函数
void CPtAtsExprMapGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(EXPRMAP_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CPtAtsExprMapGrid::InitGridTitle()
{
	CString astrGridTitle[EXPRMAP_TABLE_COLS] = {_T("编号"), _T("名称"), _T("ID"), _T("表达式")};
	int  iColType[EXPRMAP_TABLE_COLS]={GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT};
	int iGridWidth[EXPRMAP_TABLE_COLS]={40, 100, 100, 100};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, EXPRMAP_TABLE_COLS);
}

void CPtAtsExprMapGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	if (pData->GetClassID() != MPCLASSID_CPARAMAPEXPR)
	{
		return;
	}

	CParaMapExpr* pExprMap = (CParaMapExpr*)pData;

	if (pExprMap == NULL)
	{
		return;
	}

	Show_Index(pExprMap, nRow, 0);//编号
	Show_String(pExprMap, nRow, 1, &pExprMap->m_strName);
	Show_String(pExprMap, nRow, 2, &pExprMap->m_strID);
	Show_String(pExprMap, nRow, 3, &pExprMap->m_strExpr);

	nRow++;
}

BOOL CPtAtsExprMapGrid::UpdateData(CExBaseObject *pData)
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

void CPtAtsExprMapGrid::SetMidifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	CMacroMaps *pMaps = (CMacroMaps*)pData->GetAncestor(MPCLASSID_CMACROMAPS);
	pMaps->SetModifiedFlag(bModified);
}

void CPtAtsExprMapGrid::OnLButtonDown(UINT nFlags, CPoint point)
{
	CXGridCtrlBase::OnLButtonDown(nFlags, point);
	CParaMapExpr *pSelParaMapExpr = (CParaMapExpr *)GetCurrCellData();

	if (pSelParaMapExpr == NULL)
	{
		return ;
	}

	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}

	m_pMsgRcvWnd->PostMessage(WM_SHOW_EXPRCAL, (WPARAM)pSelParaMapExpr, (LPARAM)pSelParaMapExpr);
}