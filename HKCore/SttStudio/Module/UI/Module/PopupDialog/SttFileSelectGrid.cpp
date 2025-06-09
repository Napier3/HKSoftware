#include "SttFileSelectGrid.h"
#include "../../../../Module/SttCmd/SttChMap.h"
#include "../../SttTestCntrFrameBase.h"

#define STTFILESELECT_GRID_COL_INDEX_SELECT                    0
#define STTFILESELECT_GRID_COL_INDEX_NAME                      1


CSttFileSelectGrid::CSttFileSelectGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pFileSelectDelegate = NULL;
}

CSttFileSelectGrid::~CSttFileSelectGrid()
{

}

void CSttFileSelectGrid::InitGrid()
{
 	InitGridTitle();
	setSelectionBehavior(QTableWidget::SelectRows);
	setSelectionMode(QTableWidget::SingleSelection/*SelectRows*/);

	m_pFileSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pFileSelectDelegate);
	SetDefaultRowHeight(50);
//	AutoAdjColWidth();

	SetEditable(TRUE);
	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_clicked(int,int)),Qt::UniqueConnection);
	connect(this,SIGNAL(sig_UpdateCheckState(int)),this,SLOT(slot_UpdateCheckState(int)));
}

void CSttFileSelectGrid::InitGridTitle()
{
	CString strName,strAnalog,strDigital,strWeek;
	CString astrGridTitle[2];
	xlang_GetLangStrByFile(astrGridTitle[0],_T("sSelect"));
	xlang_GetLangStrByFile(astrGridTitle[1],_T("Native_Name"));
	//CString astrGridTitle[STTFILESELECT_GRID_COLS] = {_T("Ñ¡Ôñ"),_T("Ãû³Æ")};
	int iGridWidth[STTFILESELECT_GRID_COLS]={60, 300};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTFILESELECT_GRID_COLS);
}

void CSttFileSelectGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);
	Show_Check(pData,nRow,0,(long *)&pData->m_dwItemData,EndEditCell_SelectFile);
	Show_StaticString(pData,nRow,1,pData->m_strName);
 	nRow++;
}

void CSttFileSelectGrid::EndEditCell_SelectFile (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	CSttFileSelectGrid *pOwnGrid = (CSttFileSelectGrid*)pGrid;

	if ((pVCellData->pObj != NULL)&&(pVCellData->pObj->m_dwItemData))
	{
		CExBaseList *pDatas = pGrid->GetDatas();
		CExBaseObject *pCurrObj = NULL;
		POS pos = pDatas->GetHeadPosition();

		while(pos)
		{
			pCurrObj = pDatas->GetNext(pos);

			if (pCurrObj == pVCellData->pObj)
			{
				continue;
			}

			if (pCurrObj->m_dwItemData)
			{
				pCurrObj->m_dwItemData = 0;
				emit pOwnGrid->sig_UpdateCheckState(pDatas->FindIndex(pCurrObj));
			}
		}
	}
}

void CSttFileSelectGrid::slot_clicked( int nRow,int nCol )
{
	if (nCol == 1)
	{
		QGV_ITEM *pCellSelected = GetCell(nRow,0);
		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCellSelected->lParam;
		*pVCellData->pdwValue = (!(*pVCellData->pdwValue));
		Show_Check(pVCellData->pObj,nRow,0,(long *)&pVCellData->pObj->m_dwItemData,EndEditCell_SelectFile);
		OnDataSelChanged(nRow,nCol);
	}
}

void CSttFileSelectGrid::slot_CurrentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	QExBaseListGridBase::slot_CurrentCellChanged(currentRow,currentColumn,previousRow,previousColumn);

	if (previousRow >= 0)
	{
		QGV_ITEM *pCellSelected = GetCell(previousRow,0);
		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCellSelected->lParam;

		if (*pVCellData->pdwValue == 1)
		{
			*pVCellData->pdwValue = 0;
			Show_Check(pVCellData->pObj,previousRow,0,(long *)&pVCellData->pObj->m_dwItemData,EndEditCell_SelectFile);
			OnDataSelChanged(0,0);
		}
	}
}

void CSttFileSelectGrid::slot_UpdateCheckState(int nRow)
{
	QGV_ITEM *pCellSelected = GetCell(nRow,0);
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCellSelected->lParam;
	Show_Check(pVCellData->pObj,nRow,0,(long *)&pVCellData->pObj->m_dwItemData,EndEditCell_SelectFile);
	OnDataSelChanged(0,0);
}
