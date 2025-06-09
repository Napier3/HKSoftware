#include "ScanLanTesterGrid.h"
#include <QMenu>
#include <QAction>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include "../../../../Module/SttGlobalDef.h"
#include "../../../../Module/SttCmd/SttParas.h"
#include "..\ReportView\XLangResource_PowerTestWin.h"
#define ScanLanTester_GRID_COL_INDEX_Mode                    0
#define ScanLanTester_GRID_COL_INDEX_NO                      1
#define ScanLanTester_GRID_COL_INDEX_IP                      2


CScanLanTesterGrid::CScanLanTesterGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CScanLanTesterGrid::~CScanLanTesterGrid()
{

}

void CScanLanTesterGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(TRUE);
}

void CScanLanTesterGrid::InitGridTitle()
{
	CString astrGridTitle[ScanLanTester_GRID_COLS] = {/*_T("型号")*/g_sLangTxt_Report_AppModel.GetString(),/*_T("编号")*/g_sLangTxt_Index.GetString(),/*_T("IP地址")*/g_sLangTxt_Native_IPAddr.GetString()};
	int  iColType[ScanLanTester_GRID_COLS]={QT_GVET_NOEDIT, QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[ScanLanTester_GRID_COLS]={130, 130, 130};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, ScanLanTester_GRID_COLS);
//	SetFont(g_pGlobalFont11);
}

void CScanLanTesterGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	ASSERT (pData != NULL);

	CDataGroup *p = (CDataGroup *)pData;
	CString strVal = _T("");
	stt_GetDataValueByID(p, ID_STT_REGISTER_ATTR_Model_TestApp, strVal);
	Show_StaticString(p, nRow, 0, &strVal);	

	stt_GetDataValueByID(p, ID_STT_USER_ATTR_SN_TestApp, strVal);
	Show_StaticString(p, nRow, 1, &strVal);

	CDataGroup *pGroup = (CDataGroup *)p->FindByID(STT_SYS_DATA_ID_DeviceIP);

	if (pGroup != NULL)
	{
		stt_GetDataValueByID(pGroup, STT_SYS_DATA_ID_IP, strVal);
	}
	else
	{
		strVal = _T("");
	}

	Show_StaticString(p, nRow, 2, &strVal);

 	nRow++;
}

void CScanLanTesterGrid::EndEditCell_WeakRateSetString (int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
// 	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
// 	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
// 	ASSERT(pVCellData->pObj != NULL);
// 	CSttChMap *pChMap = (CSttChMap*)pVCellData->pObj;
// 
// 	CSttHdChs *pHdChs = pChMap->GetHdChs(STT_MODULETYPE_ID_WEEK);
// 
// 	if (pHdChs == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pHdChs->GetCount() <= 0)
// 	{
// 		return;
// 	}
// 
// 	if (*pVCellData->pString != pCell->text())
// 	{
// 		*pVCellData->pString = pCell->text();
// 		//		((QExBaseListGridBase*)pGrid)->DataViewOptr_DataChanged(nRow, nCol);
// 	}
// 
// 	CSttHdCh *pHdCh = (CSttHdCh*)pHdChs->GetHead();
// 	float fPrimaryValue = pHdCh->GetPrimaryValue_Float();
// 	float fSecondaryValue = pHdCh->GetSecondaryValue_Float();
// 	
// 	POS pos = pHdChs->GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pHdCh = (CSttHdCh *)pHdChs->GetNext(pos);
// 		pHdCh->SetTransRate_Weak(fPrimaryValue,fSecondaryValue);
// 	}
}

