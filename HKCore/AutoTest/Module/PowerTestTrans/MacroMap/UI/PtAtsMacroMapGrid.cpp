// PtAtsMacroMapGrid.cpp : ʵ���ļ�
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

// CPtAtsMacroMapGrid ��Ա����
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
	CString astrGridTitle[MACROMAP_TABLE_COLS] = {_T("���"), _T("PowerTest����"), _T("Ats����") ,_T("AtsID")};
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

	Show_Index(pMacroMap, nRow, 0);//���

	Show_StaticString(pData, nRow, 1, pMacroMap->m_strID);
	Show_StaticString(pData, nRow, 2, pMacroMap->m_strMapName);
	Show_StaticString(pData, nRow, 3, pMacroMap->m_strMapID);

	nRow++;
}

BOOL CPtAtsMacroMapGrid::UpdateData(CExBaseObject *pData)
{
	//��ȡ��֤���½ڵ��ڵ�ǰgrid�ڵ�����
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