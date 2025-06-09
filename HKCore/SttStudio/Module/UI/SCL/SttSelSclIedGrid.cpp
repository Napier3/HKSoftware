#include "SttSelSclIedGrid.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../XLangResource_Native.h"
#include "../../../../61850/Module/XLanguageResourcePp_Mms.h"

CSttSelSclIedGrid::CSttSelSclIedGrid(QWidget *parent): QExBaseListGridBase(parent)
{

}

CSttSelSclIedGrid::~CSttSelSclIedGrid()
{

}

void CSttSelSclIedGrid::InitGrid()
{
	InitGridTitle();
	m_pSelectSclIedDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pSelectSclIedDelegate);

	SetDefaultRowHeight(50);
	SetEditable(TRUE);
}

void CSttSelSclIedGrid::InitGridTitle()
{
	CString astrGridTitle[STTSELSCLIED_GRID_COLS];
	int iGridWidth[STTSELSCLIED_GRID_COLS]={80, 150,100, 120, 120};
	astrGridTitle[0] = g_sLangTxt_IEC_Choose; //_T("选择");
	astrGridTitle[1] = g_sLangTxt_devicedesc;//_T("装置描述");
	astrGridTitle[2] = g_sLangTxt_Report_DeviceName; //_T("装置名称");
	astrGridTitle[3] = g_sLangTxt_IpAddr; //_T("IP地址");
	astrGridTitle[4] =g_sLangTxt_unittype;//_T("设备型号");
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTSELSCLIED_GRID_COLS);
}

void CSttSelSclIedGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_IED)
	{
		return;
	}

	CSclIed *pXSclIed = (CSclIed*)pData;
	Show_Check(pData,nRow,0,&pXSclIed->m_nSelected,EndEditCell_SclIedSel);
	//_T("IED名称")
	Show_StaticString(pData, nRow, 1, &(pXSclIed->m_strName));

	//_T("IED标识")
	Show_StaticString(pData, nRow, 2, &(pXSclIed->m_strID));

	//_T("IP地址")
	Show_String(pData, nRow, 3, &(pXSclIed->m_strIP));

	//_T("设备型号")
	Show_StaticString(pData, nRow, 4, &(pXSclIed->m_strModel));
	nRow++;
}

void CSttSelSclIedGrid::EndEditCell_SclIedSel(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	CSttSelSclIedGrid *pOwnGrid = (CSttSelSclIedGrid*)pGrid;
	CSclStation *pSclStation = (CSclStation*)pOwnGrid->GetDatas();

	if (pCell->dwValue)
	{
		CExBaseObject *pCurrObj = NULL;
		CSclIed *pSclIed = NULL;
		BOOL bHasChanged = FALSE;
		POS pos = pSclStation->GetHeadPosition();

		while(pos)
		{
			pCurrObj = (CExBaseObject *)pSclStation->GetNext(pos);

			if (pCurrObj->GetClassID() != SCLIECCLASSID_IED)
			{
				continue;
			}

			if (pVCellData->pObj == pCurrObj)
			{
				continue;
			}

			pSclIed = (CSclIed *)pCurrObj;

			if (pSclIed->m_nSelected)
			{
				pSclIed->m_nSelected = 0;
				bHasChanged = TRUE;
			}
		}

		if (bHasChanged)
		{
			pOwnGrid->UpdateSelectState();
		} 
	}
}

void CSttSelSclIedGrid::UpdateSelectState()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	DisConnectAll_SigSlot();
	CExBaseObject *pCurrObj = NULL;
	CSclIed *pSclIed = NULL;	
	int nRowIndex = 0;
	POS pos = m_pDatas->GetHeadPosition();

	while (pos != NULL)
	{
		pCurrObj = (CExBaseObject*)m_pDatas->GetNext(pos);

		if (pCurrObj->GetClassID() != SCLIECCLASSID_IED)
		{
			continue;
		}

		pSclIed = (CSclIed *)pCurrObj;
		Show_Check(pSclIed,nRowIndex,0,&pSclIed->m_nSelected,EndEditCell_SclIedSel);
		nRowIndex++;
	}

	ConnectAll_SigSlot();
}