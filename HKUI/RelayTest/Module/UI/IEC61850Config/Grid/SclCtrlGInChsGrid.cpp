#include "SclCtrlGInChsGrid.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../XLangResource_Native.h"

QSclCtrlGInChsGrid::QSclCtrlGInChsGrid(QWidget* pparent):QSclCtrlChsGridBase(pparent)
{
}

QSclCtrlGInChsGrid::~QSclCtrlGInChsGrid()
{

}

void QSclCtrlGInChsGrid::InitGridTitle()
{
	

//	CString astrGridTitle[SCLCTRLS_GOOSEIN_CHS_GRID_COLS] = {"类型", "引用", "描述", "订阅索引", "订阅引用", "订阅描述"};
	CString astrGridTitle[SCLCTRLS_GOOSEIN_CHS_GRID_COLS] = {g_sLangTxt_Type, g_sLangTxt_Native_quote, g_sLangTxt_State_Description,
	 g_sLangTxt_Native_subscriptionIndex, g_sLangTxt_Native_subscriptionReference, g_sLangTxt_Native_subscriptionDescription};
	int iGridWidth[SCLCTRLS_GOOSEIN_CHS_GRID_COLS]={80, 300,250,80,200,250};

#ifdef _PSX_QT_WINDOWS_
	iGridWidth[0] = 300;
#endif

	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCTRLS_GOOSEIN_CHS_GRID_COLS);
}

void QSclCtrlGInChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_CH_GS_IN)
	{
		return;
	}

	CSclChGsIn *pIecCfgGinCh = (CSclChGsIn*)pData;
	CString strTmp;
	strTmp.Format(_T("%ld"),pIecCfgGinCh->outIndex);

	Show_StaticString(pData,nRow,0,&pIecCfgGinCh->fcda_type); 
	Show_StaticString(pData,nRow,1,&pIecCfgGinCh->inPath);
#ifdef USE_SISCO_SCL_PARSE
	Show_StaticString(pData,nRow,2,&pIecCfgGinCh->fcda_desc);
#else
	Show_StaticString(pData,nRow,2,&pIecCfgGinCh->m_strName);
#endif
	Show_StaticString(pData,nRow,3,strTmp);
	Show_StaticString(pData,nRow,4,&pIecCfgGinCh->fcda_name);
	Show_StaticString(pData,nRow,5,&pIecCfgGinCh->inDODesc); 

	nRow++;
}
// 
// void QSclCtrlGInChsGrid::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow)
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



