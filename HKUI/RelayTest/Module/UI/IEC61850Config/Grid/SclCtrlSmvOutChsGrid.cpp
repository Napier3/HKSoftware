#include "SclCtrlSmvOutChsGrid.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../61850/Module/GlobalDataMngr/IecGlobalDataMngr.h"
#include "../../../XLangResource_Native.h"

QSclCtrlSmvOutChsGrid::QSclCtrlSmvOutChsGrid(QWidget* pparent):QSclCtrlChsGridBase(pparent)
{
}

QSclCtrlSmvOutChsGrid::~QSclCtrlSmvOutChsGrid()
{

}

void QSclCtrlSmvOutChsGrid::InitGridTitle()
{

//	CString astrGridTitle[SCLCTRLS_SMVOUT_CHS_GRID_COLS] = {"类型", "相别", "描述"};
	CString astrGridTitle[SCLCTRLS_SMVOUT_CHS_GRID_COLS] = {g_sLangTxt_Type, g_sLangTxt_Native_phaseDifference, g_sLangTxt_State_Description};
	int iGridWidth[SCLCTRLS_SMVOUT_CHS_GRID_COLS]={150,150,300};

	//20230725 suyang 适配分辨率 1024X768
#ifdef _PSX_QT_WINDOWS_

	iGridWidth[0] = 300;
#endif

	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCTRLS_SMVOUT_CHS_GRID_COLS);
}

void QSclCtrlSmvOutChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_CH_SMV_OUT)
	{
		return;
	}

	CSclChSmvOut *pIecCfgSmvOutCh = (CSclChSmvOut*)pData;
	CString strChType,strPhase;
	GetSmvChTypeAndPhase(pIecCfgSmvOutCh->m_strName,pIecCfgSmvOutCh->m_strID,strChType,strPhase);
	Show_StaticString(pData,nRow,0,strChType); 
	Show_StaticString(pData, nRow, 1,strPhase); 
	Show_StaticString(pData, nRow, 2,&pIecCfgSmvOutCh->fcda_dodesc);

	nRow++;
}

// void QSclCtrlSmvOutChsGrid::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow)
// {
// 	if (pSclCtrlBase->m_nSelect)
// 	{
// 		Show_DataType_Val(pSclCtrlBase, nRow, 1,iecfg_TesterSubPubDataType, (long *)&pSclCtrlBase->m_dwItemData);
// 	} 
// 	else
// 	{
// 		Show_StaticString(pSclCtrlBase,nRow,1,_T("--")); 
// 	}
// }



