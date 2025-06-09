#include "SclCtrlsSmvOutGrid.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../../Module/API/GlobalConfigApi.h"

CSclCtrlsSmvOutGrid::CSclCtrlsSmvOutGrid(QWidget* pparent):CSclCtrlsGridBase(pparent)
{
}

CSclCtrlsSmvOutGrid::~CSclCtrlsSmvOutGrid()
{

}

void CSclCtrlsSmvOutGrid::InitGridTitle()
{
	CString strChoose/*,strType*/,strMACAddr,strChNum,strDataSets,strDataSetText,strGoose,strVlanPri,strConfigV,strSamRate,strASDU;
	xlang_GetLangStrByFile(strChoose,"sSelect");
	//xlang_GetLangStrByFile(strType,"sType");
	xlang_GetLangStrByFile(strMACAddr,"IEC_MACAddr");
	xlang_GetLangStrByFile(strChNum,"IEC_ChannelNumber");
	xlang_GetLangStrByFile(strDataSets,"sDataSets");
	xlang_GetLangStrByFile(strDataSetText,"IEC_DataSetText");
	xlang_GetLangStrByFile(strGoose,"IEC_GOOSEIndex");
	xlang_GetLangStrByFile(strVlanPri,"IEC_VlanPri");
	xlang_GetLangStrByFile(strConfigV,"IEC_ConfigVersion");
	xlang_GetLangStrByFile(strSamRate,"IEC_SamplingRate");
	xlang_GetLangStrByFile(strASDU,"IEC_ASDU");

	CString astrGridTitle[SCLCTRLS_SMVOUT_GRID_COLS] = {strChoose/*,strType*/,_T("APPID"),strMACAddr,_T("AP"),strChNum,_T("svID"),strDataSets
	,strDataSetText,_T("VlanID"),strVlanPri,strConfigV,strASDU,strSamRate};
	int iGridWidth[SCLCTRLS_SMVOUT_GRID_COLS]={40/*,140*/, 80, 170, 40, 80, 100, 100, 150, 80, 80, 80,80,80};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCTRLS_SMVOUT_GRID_COLS);
}

void CSclCtrlsSmvOutGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_CTRL_SMV_OUT)
	{
		return;
	}

	CString strTmp;
 	CSclCtrlSmvOut *pSclCtrlSmvOut = (CSclCtrlSmvOut*)pData;
 	Show_Check(pData,nRow,0,&pSclCtrlSmvOut->m_nSelect,EndEditCell_CheckChanged);
	/*UpdatePubSubCfg(pSclCtrlSmvOut,nRow);*/

	strTmp.Format(_T("0X%04X"),pSclCtrlSmvOut->m_dwAppID);
 	Show_StaticString(pData,nRow,1,&strTmp); 
	Show_StaticString(pData,nRow,2,&pSclCtrlSmvOut->m_strMac); 
	Show_StaticString(pData,nRow,3,&pSclCtrlSmvOut->apName); 
	Show_Long(pData,nRow,4,&pSclCtrlSmvOut->m_nChnCount,FALSE); 
	Show_StaticString(pData,nRow,5,&pSclCtrlSmvOut->m_strSVID); 
	Show_StaticString(pData,nRow,6,&pSclCtrlSmvOut->m_strDataSet); 
	Show_StaticString(pData,nRow,7,&pSclCtrlSmvOut->m_strDataSetDesc); 
	strTmp.Format(_T("0X%03X"),pSclCtrlSmvOut->scl_smv_VLANID);
	Show_StaticString(pData,nRow,8,&strTmp); 
	strTmp.Format(_T("%ld"),pSclCtrlSmvOut->scl_smv_VLANPRI);
	Show_StaticString(pData,nRow,9,&strTmp); 
	Show_Long(pData,nRow,10,&pSclCtrlSmvOut->scl_svcb_confRev,FALSE); 
	Show_Long(pData,nRow,11,&pSclCtrlSmvOut->scl_svcb_nofASDU,FALSE); 
	Show_Long(pData,nRow,12,&pSclCtrlSmvOut->scl_svcb_smpRate,FALSE); 
	nRow++;
}

// void CSclCtrlsSmvOutGrid::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow)
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



