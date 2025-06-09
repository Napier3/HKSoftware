#include "SclCtrlGoutChsGrid.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../XLangResource_Native.h"

QSclCtrlGoutChsGrid::QSclCtrlGoutChsGrid(QWidget* pparent):QSclCtrlChsGridBase(pparent)
{
}

QSclCtrlGoutChsGrid::~QSclCtrlGoutChsGrid()
{

}

void QSclCtrlGoutChsGrid::InitGridTitle()
{

//	CString astrGridTitle[SCLCTRLS_GOOSEOUT_CHS_GRID_COLS] = {"类型","引用","描述"};
	CString astrGridTitle[SCLCTRLS_GOOSEOUT_CHS_GRID_COLS] = {g_sLangTxt_Type,g_sLangTxt_Native_quote,g_sLangTxt_State_Description};

	int iGridWidth[SCLCTRLS_GOOSEOUT_CHS_GRID_COLS]={80, 300, 300};

	//20230725 suyang 适配分辨率 1024X768
#ifdef _PSX_QT_WINDOWS_

	iGridWidth[0] = 300;
#endif

	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCTRLS_GOOSEOUT_CHS_GRID_COLS);
}

void QSclCtrlGoutChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_CH_GS_OUT)
	{
		return;
	}

	CSclChGsOut *pSclChSmvIn = (CSclChGsOut*)pData;
	Show_StaticString(pData,nRow,0,&pSclChSmvIn->fcda_type);
	Show_StaticString(pData,nRow,1,&pSclChSmvIn->fcda_name);
	Show_StaticString(pData,nRow,2,&pSclChSmvIn->fcda_dodesc);
	
	nRow++;
}

// void QSclCtrlGoutChsGrid::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow)
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



