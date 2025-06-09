// PtAtsVmParaGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "PtAtsVmParaGrid.h"
#include "..\MacroMap.h"
//#include "..\PtAtsMacroMap.h"
//#include "..\PtAtsMacroMapView.h"

#define VMPARA_TABLE_COLS   3    

//extern CString _GetAuditFolderPath(const CString &strFolderPath, bool bBackSlash);
// CPtAtsVmParaGrid
CPtAtsVmParaGrid::CPtAtsVmParaGrid()
{
	m_nAdjustBeginCol = 1;
}

CPtAtsVmParaGrid::~CPtAtsVmParaGrid()
{
}

// CPtAtsVmParaGrid 成员函数
void CPtAtsVmParaGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(VMPARA_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CPtAtsVmParaGrid::InitGridTitle()
{
	CString astrGridTitle[VMPARA_TABLE_COLS] = {_T("编号"),_T("Ats参数名称"),_T("Ats参数ID")};
	int  iColType[VMPARA_TABLE_COLS]={GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT};
	int iGridWidth[VMPARA_TABLE_COLS]={40, 150, 150};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, VMPARA_TABLE_COLS);
}

void CPtAtsVmParaGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	if (pData == NULL)
	{
		return;
	}

	Show_Index(pData, nRow, 0);//编号
	Show_StaticString(pData, nRow, 1, pData->m_strName);
	Show_StaticString(pData, nRow, 2, pData->m_strID);

	nRow++;
}

BOOL CPtAtsVmParaGrid::UpdateData(CExBaseObject *pData)
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

//双击实现参数映射
void CPtAtsVmParaGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	CExBaseObject* pAtsPara = GetData(nRow, nCol);

	if (pAtsPara == NULL)
	{
		return;
	}

	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}

	m_pMsgRcvWnd->PostMessage(WM_MAP_PTATSPARA, (WPARAM)pAtsPara, (LPARAM)pAtsPara);
}