#include "SclCtrlsSmvInGrid.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../XLangResource_Native.h"

CSclCtrlsSmvInGrid::CSclCtrlsSmvInGrid(QWidget* pparent):CSclCtrlsGridBase(pparent)
{
}

CSclCtrlsSmvInGrid::~CSclCtrlsSmvInGrid()
{

}

void CSclCtrlsSmvInGrid::InitGridTitle()
{
	CString strChoose/*,strType*/,strMACAddr,strChAllNum,strSubChNum,strSubIED,strDataSets,strDataSetText,strSampRate;
	xlang_GetLangStrByFile(strChoose,"sSelect");
	/*xlang_GetLangStrByFile(strType,"sType");*/
	xlang_GetLangStrByFile(strMACAddr,"IEC_MACAddr");
	xlang_GetLangStrByFile(strChAllNum,"IEC_ChAllNumber");
	xlang_GetLangStrByFile(strSubChNum,"IEC_SubChNumber");
	xlang_GetLangStrByFile(strSubIED,"IEC_SubIED");
	xlang_GetLangStrByFile(strDataSets,"sDataSets");
	xlang_GetLangStrByFile(strDataSetText,"IEC_DataSetText");
	xlang_GetLangStrByFile(strSampRate,"IEC_SamplingRate");

	CString astrGridTitle[SCLCTRLS_SMVIN_GRID_COLS] = {strChoose/*,strType*/,_T("APPID"),/*_T("外部IED描述")*/g_sLangTxt_Gradient_ExIEDdescrip,strMACAddr,_T("AP"),strChAllNum,strSubChNum,strSubIED,_T("svID"),strDataSets
	,strDataSetText,strSampRate};
	int iGridWidth[SCLCTRLS_SMVIN_GRID_COLS]={40/*, 140*/,80, 150,170, 40, 80, 100, 100, 150, 150, 150, 60};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCTRLS_SMVIN_GRID_COLS);
}

void CSclCtrlsSmvInGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_CTRL_SMV_IN)
	{
		return;
	}

	CString strTmp;
 	CSclCtrlSmvIn *pSclCtrlSmvIn = (CSclCtrlSmvIn*)pData;
 	Show_Check(pData,nRow,0,&pSclCtrlSmvIn->m_nSelect,EndEditCell_CheckChanged);
	/*UpdatePubSubCfg(pSclCtrlSmvIn,nRow);*/
	strTmp.Format(_T("0X%04X"),pSclCtrlSmvIn->m_dwAppID);
 	Show_StaticString(pData,nRow,1,&strTmp); 
	Show_StaticString(pData,nRow,2,&pSclCtrlSmvIn->m_strExIedDesc); 
	Show_StaticString(pData,nRow,3,&pSclCtrlSmvIn->m_strMac); 
	Show_StaticString(pData,nRow,4,&pSclCtrlSmvIn->apName); 
	Show_Long(pData,nRow,5,&pSclCtrlSmvIn->m_nChnRefCount,FALSE); 
	Show_Long(pData,nRow,6,&pSclCtrlSmvIn->m_nChnCount,FALSE); 
	Show_StaticString(pData,nRow,7,&pSclCtrlSmvIn->iedExtName); 
	Show_StaticString(pData,nRow,8,&pSclCtrlSmvIn->m_strSVID); 
	Show_StaticString(pData,nRow,9,&pSclCtrlSmvIn->m_strDataSet); 
	Show_StaticString(pData,nRow,10,&pSclCtrlSmvIn->m_strDataSetDesc); 
	Show_Long(pData,nRow,11,&pSclCtrlSmvIn->scl_svcb_smpRate,FALSE); 
	nRow++;
}

// void CSclCtrlsSmvInGrid::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow)
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


