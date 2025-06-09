#include "SclCtrlsGooseOutGrid.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"

CSclCtrlsGooseOutGrid::CSclCtrlsGooseOutGrid(QWidget* pparent):CSclCtrlsGridBase(pparent)
{
}

CSclCtrlsGooseOutGrid::~CSclCtrlsGooseOutGrid()
{

}

void CSclCtrlsGooseOutGrid::InitGridTitle()
{
	CString strChoose/*,strType*/,strMACAddr,strChannelNumber,strDataSets,strDataSetText,strGoose,strVlanPri,strConfigV;
	xlang_GetLangStrByFile(strChoose,"sSelect");
	/*xlang_GetLangStrByFile(strType,"sType");*/
	xlang_GetLangStrByFile(strMACAddr,"IEC_MACAddr");
	xlang_GetLangStrByFile(strChannelNumber,"IEC_ChannelNumber");
	xlang_GetLangStrByFile(strDataSets,"sDataSets");
	xlang_GetLangStrByFile(strDataSetText,"IEC_DataSetText");
	xlang_GetLangStrByFile(strGoose,"IEC_GOOSEIndex");
	xlang_GetLangStrByFile(strVlanPri,"IEC_VlanPri");
	xlang_GetLangStrByFile(strConfigV,"IEC_ConfigVersion");

	CString astrGridTitle[SCLCTRLS_GOOSEOUT_GRID_COLS] = {strChoose,/*strType,*/_T("APPID"),strMACAddr,_T("AP"),strChannelNumber,strDataSets
	,strDataSetText,_T("GoID"),strGoose,_T("VlanID"),strVlanPri,strConfigV};
	int iGridWidth[SCLCTRLS_GOOSEOUT_GRID_COLS]={40/*,140*/, 80, 170, 40, 80, 100, 100, 150, 150, 80, 80,80};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SCLCTRLS_GOOSEOUT_GRID_COLS);
}

void CSclCtrlsGooseOutGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != SCLIECCLASSID_CTRL_GS_OUT)
	{
		return;
	}

	CString strTmp;
 	CSclCtrlGsOut *pSclCtrlGsOut = (CSclCtrlGsOut*)pData;
 	Show_Check(pData,nRow,0,&pSclCtrlGsOut->m_nSelect,EndEditCell_CheckChanged);
	/*UpdatePubSubCfg(pSclCtrlGsOut,nRow);*/
	strTmp.Format(_T("0X%04X"),pSclCtrlGsOut->m_dwAppID);
 	Show_StaticString(pData,nRow,1,&strTmp); 
	Show_StaticString(pData,nRow,2,&pSclCtrlGsOut->m_strMac); 
	Show_StaticString(pData,nRow,3,&pSclCtrlGsOut->apName); 
	Show_Long(pData,nRow,4,&pSclCtrlGsOut->m_nChnCount,FALSE); 
	Show_StaticString(pData,nRow,5,&pSclCtrlGsOut->m_strDataSet); 
	Show_StaticString(pData,nRow,6,&pSclCtrlGsOut->m_strDataSetDesc); 
	Show_StaticString(pData,nRow,7,&pSclCtrlGsOut->m_strGooseId); 
	Show_StaticString(pData,nRow,8,&pSclCtrlGsOut->m_strgocbRef); 
	strTmp.Format(_T("0X%03X"),pSclCtrlGsOut->m_dwVLandID);
	Show_StaticString(pData,nRow,9,&strTmp); 
	strTmp.Format(_T("%ld"),pSclCtrlGsOut->m_dwVLandPriority);
	Show_StaticString(pData,nRow,10,&strTmp); 
	Show_Long(pData,nRow,11,&pSclCtrlGsOut->m_dwVersion,FALSE); 
	nRow++;
}

// void CSclCtrlsGooseOutGrid::UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow)
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



