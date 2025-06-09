// PtAtsParaMapGrid.cpp : 实现文件
//

#include "stdafx.h"
#include "PtAtsParaMapGrid.h"
#include "..\ParaMap.h"
#include "..\MacroMaps.h"
//#include "..\PtAtsMacroMap.h"

#define PARAMAP_TABLE_COLS   6    

//extern CString _GetAuditFolderPath(const CString &strFolderPath, bool bBackSlash);
// CPtAtsParaMapGrid

CPtAtsParaMapGrid::CPtAtsParaMapGrid()
{
	m_nAdjustBeginCol = 1;
}

CPtAtsParaMapGrid::~CPtAtsParaMapGrid()
{
}

BEGIN_MESSAGE_MAP(CPtAtsParaMapGrid, CExBaseListGrid)
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(GRID_PARAMAP_DELETE, &CPtAtsParaMapGrid::OnDeleteParaMap)
	//ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CPtAtsParaMapGrid 成员函数
void CPtAtsParaMapGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(PARAMAP_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CPtAtsParaMapGrid::InitGridTitle()
{
	CString astrGridTitle[PARAMAP_TABLE_COLS] = {_T("编号"),_T("PowerTest参数"),_T("Use"),_T("Ats参数名称"),_T("Ats参数ID"),_T("域数")};
	int  iColType[PARAMAP_TABLE_COLS]={GVET_NOEDIT, GVET_NOEDIT, GVET_EDITBOX, GVET_NOEDIT, GVET_NOEDIT, GVET_NOEDIT};
	int iGridWidth[PARAMAP_TABLE_COLS]={40, 150, 40, 150, 150, 40};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, PARAMAP_TABLE_COLS);
}

void CPtAtsParaMapGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);
	CParaMap *pParaMap = (CParaMap*)pData;

	if (pParaMap == NULL)
	{
		return;
	}

	if (pData->GetClassID() != MPCLASSID_CPARAMAP)
	{
		return;
	}

	Show_Index(pParaMap, nRow, 0);//编号
	Show_StaticString(pData, nRow, 1, pParaMap->m_strName);
	Show_Check(pData, nRow, 2, &pParaMap->m_nUse);
	Show_String(pData, nRow, 3, &pParaMap->m_strMapName);
	Show_String(pData, nRow, 4, &pParaMap->m_strMapID);
	Show_IndexEx(pData, nRow, 5, pParaMap->GetCount());

// 	if (pParaMap->GetCount() >= 1)
// 	{
// 		SetItemFgColour(nRow, 1, cr);
// 	}

	nRow++;
}

BOOL CPtAtsParaMapGrid::UpdateData(CExBaseObject *pData)
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

void CPtAtsParaMapGrid::SetMidifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	CMacroMaps *pMaps = (CMacroMaps*)pData->GetAncestor(MPCLASSID_CMACROMAPS);
	pMaps->SetModifiedFlag(bModified);
}

void CPtAtsParaMapGrid::OnLButtonDown(UINT nFlags, CPoint point)
{
	CXGridCtrlBase::OnLButtonDown(nFlags, point);
	CParaMap *pSelParaMap = (CParaMap *)GetData(m_idCurrentCell.row, 1);
	//CParaMap *pSelParaMap = GetData(m_idCurrentCell.row, m_idCurrentCell.col);

	if (pSelParaMap == NULL)
	{
		return ;
	}

	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}

	m_pMsgRcvWnd->PostMessage(WM_SHOW_VALUEMAP, (WPARAM)pSelParaMap, (LPARAM)pSelParaMap);
}

void CPtAtsParaMapGrid::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CRect rect;
	GetWindowRect(rect);

	point.x -= rect.left;
	point.y -= rect.top;

	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();

	SetFocus();

	menu.AppendMenu(MF_STRING,GRID_PARAMAP_DELETE,_T("删除参数映射"));

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y, this);
	//资源回收
	//CUIWndThread::Attach_Wnd_WM_COMMAND(NULL);
	HMENU hmenu=menu.Detach();			
	menu.DestroyMenu();	
}

void CPtAtsParaMapGrid::OnDeleteParaMap()
{	
	CParaMap *pSelParaMap = (CParaMap *)GetCurrCellData();

	if (pSelParaMap == NULL)
	{
		CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("请先选中需要删除的参数行，再进行删除！"));
		return;
	}
	
	ASSERT (m_pMsgRcvWnd != NULL);

	if (m_pMsgRcvWnd == NULL)
	{
		return;
	}
	m_pMsgRcvWnd->PostMessage(WM_DELETE_PARAMAP, (WPARAM)pSelParaMap, (LPARAM)pSelParaMap);

}
