#include "SclCtrlSmvInChsGrid.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../XLangResource_Native.h"

QSclCtrlSmvInChsGrid::QSclCtrlSmvInChsGrid(QWidget* pparent):QSclCtrlChsGridBase(pparent)
{
}

QSclCtrlSmvInChsGrid::~QSclCtrlSmvInChsGrid()
{

}

void QSclCtrlSmvInChsGrid::InitGridTitle()
{
	CString strChoose,strType,strMACAddr,strChAllNum,strSubChNum,strSubIED,strDataSets,strDataSetText,strSampRate;
	/*xlang_GetLangStrByFile(strChoose,"sSelect");
	xlang_GetLangStrByFile(strType,"sType");
	xlang_GetLangStrByFile(strMACAddr,"IEC_MACAddr");
	xlang_GetLangStrByFile(strChAllNum,"IEC_ChAllNumber");
	xlang_GetLangStrByFile(strSubChNum,"IEC_SubChNumber");
	xlang_GetLangStrByFile(strSubIED,"IEC_SubIED");
	xlang_GetLangStrByFile(strDataSets,"sDataSets");
	xlang_GetLangStrByFile(strDataSetText,"IEC_DataSetText");
	xlang_GetLangStrByFile(strSampRate,"IEC_SamplingRate");*/

//	CString astrGridTitle[SCLCTRLS_SMVIN_CHS_GRID_COLS] = {"ÒýÓÃ", "ÃèÊö", "¶©ÔÄË÷Òý", "¶©ÔÄÒýÓÃ", "¶©ÔÄÃèÊö"};
	CString astrGridTitle[SCLCTRLS_SMVIN_CHS_GRID_COLS] = {g_sLangTxt_Native_quote, g_sLangTxt_State_Description, 
	g_sLangTxt_Native_subscriptionIndex, g_sLangTxt_Native_subscriptionReference, g_sLangTxt_Native_subscriptionDescription};
	int iGridWidth[SCLCTRLS_SMVIN_CHS_GRID_COLS]={200, 200,80,200,250};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCTRLS_SMVIN_CHS_GRID_COLS);
}

void QSclCtrlSmvInChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_CH_SMV_IN)
	{
		return;
	}

	CSclChSmvIn *pSclChSmvIn = (CSclChSmvIn*)pData;
	CString strTmp;
	strTmp.Format(_T("%ld"),pSclChSmvIn->outIndex);
	Show_StaticString(pData,nRow,0,&pSclChSmvIn->inPath);
#ifdef USE_SISCO_SCL_PARSE
	Show_StaticString(pData,nRow,1,&pSclChSmvIn->fcda_desc);
#else
	Show_StaticString(pData,nRow,1,&pSclChSmvIn->m_strName);
#endif
	Show_StaticString(pData,nRow,2,strTmp);
	Show_StaticString(pData,nRow,3,&pSclChSmvIn->fcda_name);
	Show_StaticString(pData,nRow,4,&pSclChSmvIn->inDODesc); //Ã»ÕÒµ½
	nRow++;
	//Show_StaticString(pData,nRow,1,&pCurObj-);

}

// void QSclCtrlSmvInChsGrid::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow)
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


