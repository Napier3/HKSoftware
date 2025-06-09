#include "SclCtrlsGooseInGrid.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../XLangResource_Native.h"


CSclCtrlsGooseInGrid::CSclCtrlsGooseInGrid(QWidget* pparent):CSclCtrlsGridBase(pparent)
{
}

CSclCtrlsGooseInGrid::~CSclCtrlsGooseInGrid()
{

}

void CSclCtrlsGooseInGrid::InitGridTitle()
{
	CString strChoose/*,strType*/,strMACAddr,strChAllNum,strSubChNum,strSubIED,strDataSets,strDataSetText,strGoose,strVlanPri,strConfigV;
	xlang_GetLangStrByFile(strChoose,"sSelect");
	/*xlang_GetLangStrByFile(strType,"sType");*/
	xlang_GetLangStrByFile(strMACAddr,"IEC_MACAddr");
	xlang_GetLangStrByFile(strChAllNum,"IEC_ChAllNumber");
	xlang_GetLangStrByFile(strSubChNum,"IEC_SubChNumber");
	xlang_GetLangStrByFile(strSubIED,"IEC_SubIED");
	xlang_GetLangStrByFile(strDataSets,"sDataSets");
	xlang_GetLangStrByFile(strDataSetText,"IEC_DataSetText");
	xlang_GetLangStrByFile(strGoose,"IEC_GOOSEIndex");
	xlang_GetLangStrByFile(strVlanPri,"IEC_VlanPri");
	xlang_GetLangStrByFile(strConfigV,"IEC_ConfigVersion");

	CString astrGridTitle[SCLCTRLS_GOOSEIN_GRID_COLS] = {strChoose/*,strType*/,_T("APPID"),/*_T("外部IED描述")*/g_sLangTxt_Gradient_ExIEDdescrip,strMACAddr,_T("AP"),strChAllNum,strSubChNum,strSubIED,strDataSets
	,strDataSetText,_T("GoID"),strGoose,_T("VlanID"),strVlanPri,strConfigV};
	int iGridWidth[SCLCTRLS_GOOSEIN_GRID_COLS]={40/*, 140*/,80, 200,170, 40, 80, 100, 100, 150, 150, 150, 200,80,80,80};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCTRLS_GOOSEIN_GRID_COLS);
}

void CSclCtrlsGooseInGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_CTRL_GS_IN)
	{
		return;
	}

	CString strTmp;
 	CSclCtrlGsIn *pSclCtrlGsIn = (CSclCtrlGsIn*)pData;
 	Show_Check(pData,nRow,0,&pSclCtrlGsIn->m_nSelect,EndEditCell_CheckChanged);
	/*UpdatePubSubCfg(pSclCtrlGsIn,nRow);*/
	strTmp.Format(_T("0X%04X"),pSclCtrlGsIn->m_dwAppID);
 	Show_StaticString(pData,nRow,1,&strTmp); 
	Show_StaticString(pData,nRow,2,&pSclCtrlGsIn->m_strExIedDesc);
	Show_StaticString(pData,nRow,3,&pSclCtrlGsIn->m_strMac); 
	Show_StaticString(pData,nRow,4,&pSclCtrlGsIn->apName); 
	Show_Long(pData,nRow,5,&pSclCtrlGsIn->m_nChnRefCount,FALSE); 
	Show_Long(pData,nRow,6,&pSclCtrlGsIn->m_nChnCount,FALSE); 
	Show_StaticString(pData,nRow,7,&pSclCtrlGsIn->m_strIedID); 
	Show_StaticString(pData,nRow,8,&pSclCtrlGsIn->m_strDataSet); 
	Show_StaticString(pData,nRow,9,&pSclCtrlGsIn->m_strDataSetDesc); 
	Show_StaticString(pData,nRow,10,&pSclCtrlGsIn->m_strGooseId); 
	Show_StaticString(pData,nRow,11,&pSclCtrlGsIn->m_strgocbRef); 
	

	strTmp.Format(_T("0X%03X"),pSclCtrlGsIn->m_dwVLandID);
	Show_StaticString(pData,nRow,12,&strTmp); 
	strTmp.Format(_T("%ld"),pSclCtrlGsIn->m_dwVLandPriority);
	Show_StaticString(pData,nRow,13,&strTmp); 

	Show_Long(pData,nRow,14,&pSclCtrlGsIn->m_dwVersion,FALSE); 
	nRow++;
}
// 
// void CSclCtrlsGooseInGrid::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow)
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



