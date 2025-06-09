#include "stdafx.h"
#include "IEDSelGrid.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../WzdDlgDef.h"

#define SCL_IEDS_GRID_COLS                        6

IMPLEMENT_DYNCREATE(CIEDSelGrid, CGridCtrl)
BEGIN_MESSAGE_MAP(CIEDSelGrid, CGridCtrl)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

CIEDSelGrid::CIEDSelGrid()
{
	CString strIcon = _P_GetResourcePath();
	strIcon += "iSmartTestWzd/";
	AddNewImage(strIcon + "btn_n.png");

	m_nCurSelect = 0;
	m_nCurHotRow = 0;
	m_bHotLight = FALSE;
	m_crHot = RGB(255, 255, 255);
}

CIEDSelGrid::~CIEDSelGrid()
{
	ClearImageList();
}

void CIEDSelGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	SetGridColor(g_crLightBlue);
	SetHeaderSort(TRUE);
	SetColumnResize(FALSE);
	SetRowResize(FALSE);
	InitGridTitle();
	ExpandColumnsToFitEx();
}

void CIEDSelGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	switch (nClassID)
	{
	case SCLIECCLASSID_IED:
		ShowData_Ied(pData, nRow);
		break;
	}
}

void CIEDSelGrid::InitGridTitle()
{
	CString astrSclIedsGirdTitle[SCL_IEDS_GRID_COLS] = {_T("序号"),_T("选中"),_T("装置描述"),_T("装置名称"),_T("IP地址"),_T("设备型号")};
	const int nSclIedsWidth[SCL_IEDS_GRID_COLS]={50, 50,180 ,120 ,120, 120 };
	SetColumnCount(SCL_IEDS_GRID_COLS);
	CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, SCL_IEDS_GRID_COLS);
}

void CIEDSelGrid::ShowData_Ied(CExBaseObject *pObj,int &nRow)
{
	CSclIed *pSclIed = (CSclIed *)pObj;

	if (pSclIed->LDTYPE_RPIT || pSclIed->LDTYPE_MU)// 暂时屏蔽掉智能终端和合并单元
	{
		return;
	}
	//_T("序号")
	Show_Index(pObj, nRow, 0);

	Show_Check(pObj, nRow, 1, &(pSclIed->m_nSelected), EndEditCell_Check);

	//_T("IED名称")
	Show_StaticString(pObj, nRow, 2, &(pSclIed->m_strName));

	//_T("IED标识")
	Show_StaticString(pObj, nRow, 3, &(pSclIed->m_strID));

	//_T("IP地址")
	Show_String(pObj, nRow, 4, &(pSclIed->m_strIP));

	//_T("设备型号")
	Show_StaticString(pObj, nRow, 5, &(pSclIed->m_strModel));

	nRow++;
}

CExBaseObject* CIEDSelGrid::GetCurrSelIED(long nStateForCol)
{
	if(m_nCurSelect == 0)
	{
		return NULL;
	}

	CExBaseObject *pSelData = NULL;
	if (IsValid(m_nCurSelect, 1))	//20240311 huangliang m_nCurSelect就是当前勾选项
	{
		pSelData = GetDataRow(m_nCurSelect);
		if (pSelData != NULL)
		{
			return pSelData;
		}
	}
	return NULL;
	//if (IsValid(m_idCurrentCell))
	//{
	//	pSelData = GetDataRow(m_idCurrentCell.row);//20240305luozibing 获取最新当前选中行

	//	if (pSelData != NULL)
	//	{
	//		return pSelData;
	//	}
	//}

	//if (m_nRows <= 1)
	//{
	//	return NULL;
	//}

	//long nRow = 1;
	//long nCount = 0;
	//UINT nState = 0;

	//for (nRow=1; nRow < m_nRows; nRow++)
	//{
	//	nState = GetItemState(nRow, nStateForCol);

	//	if ( (nState & GVIS_SELECTED) == GVIS_SELECTED
	//		|| (nState & GVIS_FOCUSED) == GVIS_FOCUSED)
	//	{
	//		pSelData = GetDataRow(nRow);
	//		nCount++;
	//	}
	//}

	//if (nCount > 1)
	//{
	//	return NULL;
	//}
	//else
	//{
	//	return pSelData;
	//}
}

void CIEDSelGrid::EndEditCell_Check (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	CIEDSelGrid* pIEDGrid = (CIEDSelGrid*)pGrid;
	if(pIEDGrid->m_nCurSelect != 0)
	{
		CExBaseListGrid::EndEditCell_Check(nRow, nCol, pCell, pGrid);

		PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pGrid->GetItemData(pIEDGrid->m_nCurSelect, nCol);
		*(pVCellData->pnValue) = 0;
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(pIEDGrid->m_nCurSelect, nCol);
		pIEDGrid->UpdateDatas();

		if(pIEDGrid->m_nCurSelect == nRow)
		{
			pIEDGrid->m_nCurSelect = 0;
		}
		else
		{
			pIEDGrid->m_nCurSelect = nRow;
		}
	}
	else
	{
		pIEDGrid->m_nCurSelect = nRow;
	}
}

long CIEDSelGrid::AddNewImage(const CString& strFilePath)
{
	CImage* pImage = new CImage;
	pImage->Load(strFilePath);
	long nIndex = m_imageList.size();
	m_imageList.insert(std::pair<long, CImage*>(nIndex, pImage));
	return nIndex;
}

void CIEDSelGrid::ClearImageList()
{
	std::map<long, CImage*>::iterator itor = m_imageList.begin();
	while (itor != m_imageList.end())
	{
		if (itor->second)
		{
			CImage* pImage = (CImage*)itor->second;
			pImage->Destroy();
			delete pImage;
			itor = m_imageList.erase(itor);
		}
		else
		{
			itor++;
		}
	}
}

void CIEDSelGrid::DrawTransparent(CDC* pDC, HBITMAP hBitmap, CRect rc)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = memDC.SelectObject(CBitmap::FromHandle(hBitmap));
	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), &bm);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	pDC->StretchBlt(rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	if(pOldBitmap)
	{
		memDC.SelectObject(pOldBitmap);
	}
	memDC.DeleteDC();
}

BOOL CIEDSelGrid::DrawFixedCell(CGridCells &oCells, CDC *pDC, int nRow, int nCol, CRect rect, BOOL bCalMerge, BOOL bEraseBk)
{
	CGridCell *pCell = GetCell(nRow, nCol);
	UINT nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

	CRect rcCell = rect;
	CString strText = GetItemText(nRow, nCol);
	CImage* pImage = (CImage*)m_imageList.find(0)->second;
	DrawTransparent(pDC, *pImage, rcCell);
	CFont* font = GetParent()->GetFont();
	pDC->SelectObject(font);
	pDC->DrawText(strText, -1, rcCell, nFormat);
	return TRUE;
}

void CIEDSelGrid::OnDraw(CDC* pDC)
{
	CRect rect;
	int row,col;

	CRect clipRect;
	if (GetGridClipRect(pDC, clipRect) == ERROR) return;

	EraseBkgnd(pDC);

	DrawGridLines(pDC);

	int nFixedRowHeight = GetFixedRowHeight();
	int nFixedColWidth  = GetFixedColumnWidth();

	CCellID idTopLeft = GetTopleftNonFixedCell();
	int minVisibleRow = idTopLeft.row,
		minVisibleCol = idTopLeft.col;

	CRect VisRect;
	CGridCellRange VisCellRange = GetVisibleNonFixedCellRange(VisRect);
	int maxVisibleRow = VisCellRange.GetMaxRow(),
		maxVisibleCol = VisCellRange.GetMaxCol();

	rect.bottom = nFixedRowHeight-1 + m_posTopLeft.y;
	CGridCells oCells;

	for (row = minVisibleRow; row <= maxVisibleRow; row++)
	{
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + GetRowHeight(row)-1;

		if (rect.top > clipRect.bottom) break;   
		if (rect.bottom < clipRect.top) continue;

		rect.right = nFixedColWidth-1 + m_posTopLeft.x;
		for (col = minVisibleCol; col <= maxVisibleCol; col++)
		{
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;

			if (rect.left > clipRect.right) break;   
			if (rect.right < clipRect.left) continue;

			if(m_nCurHotRow == row && m_bHotLight)
			{
				//画悬浮高亮
				CGridCell *pCell = GetCell(row, col);
				pCell->crBkClr = m_crHot;
				DrawCell(oCells, pDC, row, col, rect);
				pCell->crBkClr = CLR_DEFAULT;
			}
			else
			{
				DrawCell(oCells, pDC, row, col, rect);
			}
		}
	}

	oCells.RemoveAll();

	//绘制Fixed-固定行的固定列单元
	rect.bottom = -1 + m_posTopLeft.y;
	for (row = 0; row < m_nFixedRows; row++)
	{
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + GetRowHeight(row)-1;
		rect.right = m_posTopLeft.x - 1;

		for (col = 0; col < m_nFixedCols; col++)
		{
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;
			DrawFixedCell(oCells, pDC, row, col, rect, TRUE, TRUE);
		}
	}

	//绘制可见行的固定列单元
	rect.bottom = nFixedRowHeight-1;
	for (row = minVisibleRow; row <= maxVisibleRow; row++)
	{
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + GetRowHeight(row)-1;

		if (rect.top > clipRect.bottom) break;   
		if (rect.bottom < clipRect.top) continue;

		rect.right = -1;
		for (col = 0; col < m_nFixedCols; col++)
		{
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;

			if (rect.left > clipRect.right) break;   
			if (rect.right < clipRect.left) continue;
			DrawFixedCell(oCells, pDC, row, col, rect, TRUE, TRUE);
		}
	}

	//绘制固定行的各列
	rect.bottom = m_posTopLeft.y-1;
	for (row = 0; row < m_nFixedRows; row++)
	{
		rect.top = rect.bottom+1;
		rect.bottom = rect.top + GetRowHeight(row)-1;

		if (rect.top > clipRect.bottom) break;   
		if (rect.bottom < clipRect.top) continue;

		rect.right = m_posTopLeft.x + nFixedColWidth-1;

		for (col = minVisibleCol; col <= maxVisibleCol; col++)
		{                                       
			rect.left = rect.right+1;
			rect.right = rect.left + GetColumnWidth(col)-1;

			if (rect.left > clipRect.right) break;    
			if (rect.right < clipRect.left) continue;
			DrawFixedCell(oCells, pDC, row, col, rect, TRUE, TRUE);
		}
	}
}

void CIEDSelGrid::OnMouseMove(UINT nFlags, CPoint point)
{
	CGridCtrl::OnMouseMove(nFlags, point);

	if(m_bHotLight)
	{
		CCellID oCellID = GetCellFromPt(point);
		if(oCellID.row > 0 && oCellID.col > 0)
		{
			m_nCurHotRow = oCellID.row;
		}
		else
		{
			m_nCurHotRow = 0;
		}

		Invalidate();
	}
}