#include "StdAfx.h"
#include "SclIedsGrid.h"
#include "SclIecCfgDatas.h"

#define SCL_IEDS_GRID_COLS                        6


CSclIedsGrid::CSclIedsGrid()
{
	m_nAdjustBeginCol = 1;
}

CSclIedsGrid::~CSclIedsGrid()
{
}

void CSclIedsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSclIedsGrid::InitGridTitle()
{
	CString astrSclIedsGirdTitle[SCL_IEDS_GRID_COLS] = {_T("序号"),_T("选择"),_T("装置描述"),_T("装置名称"),_T("IP地址"),_T("设备型号")};
	const int nSclIedsWidth[SCL_IEDS_GRID_COLS]={50,60,150 ,80 ,100,100 };
	SetColumnCount(SCL_IEDS_GRID_COLS);
	CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, SCL_IEDS_GRID_COLS);
}

void CSclIedsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	switch (nClassID)
	{
	case SCLIECCLASSID_IED:
		ShowData_Ied(pData, nRow);
		break;
	}
}

void CSclIedsGrid::ShowData_Ied(CExBaseObject *pObj,int &nRow)
{
	CSclIed *pSclIed = (CSclIed *)pObj;

	if (pSclIed->LDTYPE_RPIT || pSclIed->LDTYPE_MU)// 暂时屏蔽掉智能终端和合并单元
	{
		return;
	}
	//_T("序号")
	Show_Index(pObj, nRow, 0);

	Show_Check(pObj, nRow, 1, &pSclIed->m_nSelected,EndEditCell_Check_IedSelect);
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

void CSclIedsGrid::ShowDatas(CExBaseList *pDatas)
{
	CExBaseListGrid::ShowDatas(pDatas);
}

CGridCell *CSclIedsGrid::GetSelectCell(int nRow)
{
	return GetCell(nRow,1);
}

void CSclIedsGrid::EndEditCell_Check_IedSelect (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pnValue != NULL);
	ASSERT ( exgrid_get_vcd_type(pVCellData->nVt) == VCD_LONG);

	if( *(pVCellData->pnValue) != pCell->dwValue )
	{
		*(pVCellData->pnValue) = pCell->dwValue;
		((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
		((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);

		if (pCell->dwValue)
		{
			long nCount = pGrid->GetRowCount();
			CGridCell *pTmpCell = NULL;

			for (int nIndex = 1;nIndex< nCount;nIndex++)
			{
				pTmpCell = ((CSclIedsGrid*)pGrid)->GetSelectCell(nIndex);

				if ((pTmpCell != pCell)&&(pTmpCell->dwValue))
				{
					pTmpCell->dwValue = 0;
					PEXBASECELLDATA pVCellDataTmp = (_ExBaseCellData*)pTmpCell->lParam;
					*(pVCellDataTmp->pnValue) = 0;
					((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellDataTmp->pObj);
					pGrid->RedrawCell(nIndex,nCol);
					((CExBaseListGrid*)pGrid)->DataViewOptr_DataChanged(nIndex, nCol);
				}
			}
		}
	}
}

