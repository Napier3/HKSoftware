#include "QIecDevicesGrid.h"
#include "..\Module\QExBaseListGridBase\QExBaseListComBoxDelegBase.h"

QIecDevicesGrid::QIecDevicesGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pSelectIed = NULL;
}

QIecDevicesGrid::~QIecDevicesGrid(void)
{
}

void QIecDevicesGrid::InitGrid()
{
	QExBaseListGridBase::InitGrid();
	InitGridTitle();
	QExBaseListCheckBoxDelegate *pIEDSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,pIEDSelectDelegate);
}

void QIecDevicesGrid::InitGridTitle()
{
	CString astrGridTitle[QIECDEVICESGRID_COL] = {_T("选择"),_T("IED名称"),_T("IED标识"),_T("IP地址"),_T("设备型号")};
	int iGridWidth[QIECDEVICESGRID_COL]={100,300,150,150,200};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QIECDEVICESGRID_COL);
}

void QIecDevicesGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow/*=TRUE*/)
{
	ASSERT(pData);
	CSclIed *pIed = (CSclIed*)pData;
	Show_Check(pData, nRow, 0, &pIed->m_nSelected, EndEditCell_SelectIED);
	Show_StaticString(pData, nRow, 1, pIed->m_strName);
	Show_StaticString(pData, nRow, 2, pIed->m_strID);
	Show_StaticString(pData, nRow, 3, pIed->m_strIP_SUBNET);
	Show_StaticString(pData, nRow, 4, pIed->m_strModel);
	nRow ++;
}

void QIecDevicesGrid::EndEditCell_SelectIED(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	QIecDevicesGrid *pOwnGrid = (QIecDevicesGrid*)pGrid;
	CSclIed *pIed = (CSclIed *)pVCellData->pObj;

	pOwnGrid->m_pDataViewOptrInterface->OnDataSelChanged(pOwnGrid, nRow, nCol);

}

void QIecDevicesGrid::UpdateSelectState(int nRow)
{
	QTableWidgetItem *pItem = item(nRow,1);
	if (pItem == NULL)
	{
		return;
	}
	CString strItemName = pItem->text();

	if (m_pDatas == NULL)
	{
		return;
	}
	DisConnectAll_SigSlot();

	CSclIed *pSclIed = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;

	while (pos != NULL)
	{
		pSclIed = (CSclIed*)m_pDatas->GetNext(pos);

		if (pSclIed->m_strName == strItemName)
		{
			pSclIed->m_nSelected = 1;
			m_pSelectIed = pSclIed;
		}
		else
		{
			pSclIed->m_nSelected = 0;
		}

		Show_Check(pSclIed,nRowIndex,0,&pSclIed->m_nSelected,EndEditCell_SelectIED);

		nRowIndex++;
	}

	ConnectAll_SigSlot();
}

