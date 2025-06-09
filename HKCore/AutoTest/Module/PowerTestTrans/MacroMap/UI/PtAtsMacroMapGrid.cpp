// PtAtsMacroMapGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "PtAtsMacroMapGrid.h"
#include "..\MacroMap.h"
//#include "..\PtAtsMacroMap.h"

#define MACROMAP_TABLE_COLS   4    

//extern CString _GetAuditFolderPath(const CString &strFolderPath, bool bBackSlash);
// CPtAtsMacroMapGrid
CPtAtsMacroMapGrid::CPtAtsMacroMapGrid()
{
	m_nAdjustBeginCol = 1;
	
}

CPtAtsMacroMapGrid::~CPtAtsMacroMapGrid()
{
}

// CPtAtsMacroMapGrid 成员函数
void CPtAtsMacroMapGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(MACROMAP_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CPtAtsMacroMapGrid::InitGridTitle()
{
	CString astrGridTitle[MACROMAP_TABLE_COLS] = {_T("编号"), _T("PowerTest功能"), _T("Ats功能") ,_T("AtsID")};
	int  iColType[MACROMAP_TABLE_COLS]={GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT};
	int iGridWidth[MACROMAP_TABLE_COLS]={40, 100, 100, 100};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, MACROMAP_TABLE_COLS);
}

void CPtAtsMacroMapGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);
	CMacroMap* pMacroMap = (CMacroMap*)pData;
	//CTestMacro* pTestMacro;

	if (pMacroMap == NULL)
	{
		return;
	}

	Show_Index(pMacroMap, nRow, 0);//编号

	Show_StaticString(pData, nRow, 1, pMacroMap->m_strID);
	Show_StaticString(pData, nRow, 2, pMacroMap->m_strMapName);
	Show_StaticString(pData, nRow, 3, pMacroMap->m_strMapID);

	nRow++;
}

BOOL CPtAtsMacroMapGrid::UpdateData(CExBaseObject *pData)
{
	//获取验证更新节点在当前grid节点的序号
	/*int nRow = GetDataRow(pData);

	if (nRow != -1)
	{
		ShowData(pData, nRow, FALSE);
		Invalidate(FALSE);
	}
	else
	{
	}*/

	return TRUE;
}

void CPtAtsMacroMapGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	CMacroMap* pMacroMap = (CMacroMap*) GetData(nRow, nCol);

	if (pMacroMap == NULL)
	{
		return;
	}

	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}

	m_pMsgRcvWnd->PostMessage(WM_OPEN_MACROMAPOBJ, (WPARAM)pMacroMap, (LPARAM)pMacroMap);

}