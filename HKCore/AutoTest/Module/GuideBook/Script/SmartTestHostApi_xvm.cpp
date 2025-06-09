#include "StdAfx.h"
#include "SmartTestHostApi_xvm.h"

#include "GbScriptFunctions.h"
#include "GbScript_System.h"
#include "GbScript_Engine.h"
#include "GbScript_GuideBook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//GbScript_GuideBook/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//跳转到项目
void xvm_GBS_GotoItem(LPVOID pXvm, const char* pszItemPath) 
{
	return GBS_GotoItem(pszItemPath);
}

void xvm_GBS_GotoItemEx(LPVOID pXvm, const char* pszItemPath, long nRslt, long nAndOr)
{
	return GBS_GotoItemEx(pszItemPath, nRslt, nAndOr);
}

void xvm_GBS_FireTestNextMsg(LPVOID pXvm) //只针对试验中的通讯命令，目前只支持提示信息
{
	return GBS_FireTestNextMsg();
}

void xvm_GBS_BreakLoop(LPVOID pXvm, long nLevel)
{
	return GBS_BreakLoop(nLevel);
}

//命令消息
void xvm_GBS_MtExcuteCmd(LPVOID pXvm, const char *pszCmd, const char *pCmdPara)
{
	return GBS_MtExcuteCmd(pszCmd, pCmdPara);
}

void xvm_GBS_MtRegistPpDataMsg(LPVOID pXvm, const char *pszDvmDataPath)
{
	return GBS_MtRegistPpDataMsg(pszDvmDataPath);
}

void xvm_GBS_MtUnRegistPpDataMsg(LPVOID pXvm, const char *pszDvmDataPath)
{
	return GBS_MtUnRegistPpDataMsg(pszDvmDataPath) ;
}

void xvm_GBS_MtRegistPpDataMsgRange(LPVOID pXvm, const char *pszDvmDataPath, double dMin, double dMax)
{
	return GBS_MtRegistPpDataMsgRange(pszDvmDataPath, dMin, dMax);
}

void xvm_GBS_BreakItems(LPVOID pXvm, long nLevel) 
{
	return GBS_BreakItems(nLevel);
}

void xvm_GBS_SetUploadRptFile(LPVOID pXvm, const char *pszFileName) 
{
	return GBS_SetUploadRptFile(pszFileName);
}

void xvm_GBS_MtRegistCmdMsg(LPVOID pXvm, const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam)
{
	return GBS_MtRegistCmdMsg(pszCmdID, nCmdState, nCmdWParam, nCmdLParam);
}

void xvm_GBS_MtUnRegistCmdMsg(LPVOID pXvm, const char *pszCmdID)
{
	return GBS_MtUnRegistCmdMsg(pszCmdID);
}

//数据集访问
double xvm_GBS_GetDsDataValue(LPVOID pXvm, const char* pszID)
{
	return GBS_GetDsDataValue(pszID);
}

double xvm_GBS_GetDsDataAttr(LPVOID pXvm, const char* pszID, const char *pszAttrID)
{
	return GBS_GetDsDataAttr(pszID, pszAttrID);
}

void xvm_GBS_SetDsDataValue(LPVOID pXvm, const char* pszID, double dVal)
{
	return GBS_SetDsDataValue(pszID, dVal);
}
const char* xvm_GBS_GetDsDataValueStr(LPVOID pXvm, const char* pszID)
{
	return GBS_GetDsDataValueStr(pszID);
}
void xvm_GBS_SetDsDataValueStr(LPVOID pXvm, const char* pszID, const char* pszVal)
{
	return GBS_SetDsDataValueStr(pszID, pszVal);
}
double xvm_GBS_GetDsDataValueEx(LPVOID pXvm, long nDeviceIndex, const char* pszID)
{
	return GBS_GetDsDataValueEx(nDeviceIndex, pszID);
}
void xvm_GBS_SetDsDataValueEx(LPVOID pXvm, long nDeviceIndex, const char* pszID, double dVal)
{
	return GBS_SetDsDataValueEx(nDeviceIndex, pszID, dVal);
}
const char* xvm_GBS_GetDsDataValueStrEx(LPVOID pXvm, long nDeviceIndex, const char* pszID)
{
	return GBS_GetDsDataValueStrEx(nDeviceIndex, pszID);
}
void xvm_GBS_SetDsDataValueStrEx(LPVOID pXvm, long nDeviceIndex, const char* pszID, const char* pszVal)
{
	return GBS_SetDsDataValueStrEx(nDeviceIndex, pszID, pszVal);
}
long xvm_GBS_CalAinError(LPVOID pXvm, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_CalAinError(pszAinID, dRefVal, dAbsErr, dRelErr);
}
long xvm_GBS_CalAinErrorEx(LPVOID pXvm, double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_CalAinErrorEx(dRate, pszAinID, dRefVal, dAbsErr, dRelErr);
}
long xvm_GBS_CalAinErrorNom(LPVOID pXvm, double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr)
{
	return GBS_CalAinErrorNom(dRate, pszAinID, dRefVal, dNom, dAbsErr, dRelErr);
}

long xvm_GBS_CalAinStdError(LPVOID pXvm, double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_CalAinStdError(dRate, pszAinID, dRefVal, dAbsErr, dRelErr);
}

long xvm_GBS_CalAinStdError2(LPVOID pXvm, const char *pszAinID, const char *pszAinBaseID,double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_CalAinStdError2(pszAinID, pszAinBaseID, dRefVal, dAbsErr, dRelErr);
}

long xvm_GBS_CalAinError2(LPVOID pXvm, const char *pszAinID, const char *pszAinBaseID, double dRate, double dAbsErr, double dRelErr)
{
	return GBS_CalAinError2(pszAinID, pszAinBaseID, dRate, dAbsErr, dRelErr);
}


double xvm_GBS_CalVariation(double dValue, double dTheoreticalVal, double dBaseValue, double dRate)
{
	return GBS_CalVariation(dValue, dTheoreticalVal, dBaseValue, dRate);
}

long xvm_GBS_CalVariationErr(LPVOID pXvm, double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr)
{
	return GBS_CalVariationErr(dValue, dTheoreticalVal, dBaseValue, dRate, dRelErr);
}

long xvm_GBS_CalVariationErrEx(LPVOID pXvm, const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate)
{
	return GBS_CalVariationErrEx(pszAinID, pszTheoreticalID, pszBaseValueID, pszRsltID, pszRelErr, dRate);
}


long xvm_GBS_FlterCalErrorMax(LPVOID pXvm, const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_FlterCalErrorMax(pszValID, pszAbsErrID, pszRelErrID, dRefVal, dAbsErr, dRelErr);
}

long xvm_GBS_FlterCalErrorMin(LPVOID pXvm, const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_FlterCalErrorMin(pszValID, pszAbsErrID, pszRelErrID, dRefVal, dAbsErr, dRelErr);
}


// 获取定值数据
// pszID：数据的ID
double xvm_GBS_GetSetValue(LPVOID pXvm, const char* pszID)
{
	return GBS_GetSetValue(pszID);
}

void xvm_GBS_SetSetValue(LPVOID pXvm, const char* pszID, double dVal)
{
	return GBS_SetSetValue(pszID, dVal);
}


//void xvm_GBS_GetSoftswitchValue(LPVOID pXvm, const char* pszID
// void xvm_GBS_SetSoftswitchValue(LPVOID pXvm, const char* pszID, double dVal

// 获取系统参数数据数据
// pszID：数据的ID
double xvm_GBS_GetSysParaValue(LPVOID pXvm, const char* pszID)
{
	return GBS_GetSysParaValue(pszID);
}


void xvm_GBS_SetSysParaValue(LPVOID pXvm, const char* pszID, double dValue)
{
	return GBS_SetSysParaValue(pszID, dValue);
}


// 获取测试参数数据
// pszID：数据的ID
double xvm_GBS_GetTestParaValue(LPVOID pXvm, const char* pszID)
{
	return GBS_GetTestParaValue(pszID);
}

const char* xvm_GBS_GetTestParaStr(LPVOID pXvm, const char* pszID)
{
	return GBS_GetTestParaStr(pszID);
}


// 设置测试参数数据
// pszID：数据的ID
void xvm_GBS_SetTestParaValue(LPVOID pXvm, const char* pszID, double dValue)
{
	return GBS_SetTestParaValue(pszID, dValue);
}

void xvm_GBS_SetTestParaStr(LPVOID pXvm, const char* pszID, const char *pszValue)
{
	return GBS_SetTestParaStr(pszID, pszValue);
}


//设置满足条件的项目的Show属性
//pszItemPath为Item的路径
void xvm_GBS_SetItemShow(LPVOID pXvm, const char* pszItemPath, long nShow)
{
	return GBS_SetItemShow(pszItemPath, nShow);
}


// 获取满足条件的项目的Show属性
// pszItemPath为Item的路径
long xvm_GBS_GetItemShow(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemShow(pszItemPath);
}


// 设置满足条件的项目的Enable属性
// pszItemPath为Item的路径
void xvm_GBS_SetItemEnable(LPVOID pXvm, const char* pszItemPath, long nEnable)
{
	return GBS_SetItemEnable(pszItemPath, nEnable);
}


// 获取满足条件的项目的Enable属性
// pszItemPath为Item的路径
long xvm_GBS_GetItemEnable(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemEnable(pszItemPath);
}



//Seelct
void xvm_GBS_SetItemSelect(LPVOID pXvm, const char* pszItemPath, long nSelect)
{
	return GBS_SetItemSelect(pszItemPath, nSelect);
}

long xvm_GBS_GetItemSelect(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemSelect(pszItemPath);
}


// 设置满足条件的项目的Name属性
// pszItemPath为Item的路径
void xvm_GBS_SetItemName(LPVOID pXvm, const char* pszItemPath, const char* pszName)
{
	return GBS_SetItemName(pszItemPath, pszName);
}


// 获取满足条件的项目的Name属性
// pszItemPath为Item的路径
const char* xvm_GBS_GetItemName(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemName(pszItemPath);
}


// 设置满足条件的项目的结果判断
// pszItemPath为Item的路径
void xvm_GBS_SetItemResultJudge(LPVOID pXvm, const char* pszItemPath, long nResult)
{
	return GBS_SetItemResultJudge(pszItemPath, nResult);
}


long xvm_GBS_GetItemResultJudge(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemResultJudge(pszItemPath);
}



// 设置满足条件的项目的数据的值
// pszItemPath为Item的路径
void xvm_GBS_SetItemParaValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dValue)
{
	return GBS_SetItemParaValue(pszItemPath, pszValID, dValue);
}

void xvm_GBS_SetItemParaValueStr(LPVOID pXvm, const char* pszItemPath, const char* pszValID, const char *pszValue)
{
	return GBS_SetItemParaValueStr(pszItemPath, pszValID, pszValue);
}


double xvm_GBS_GetItemParaValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemParaValue(pszItemPath, pszValID);
}

const char* xvm_GBS_GetItemParaString(LPVOID pXvm, const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemParaString(pszItemPath, pszValID);
}

const  char* xvm_GBS_GetItemTestTime(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemTestTime(pszItemPath);
}

const  char* xvm_GBS_GetItemTestBeginTime(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemTestBeginTime(pszItemPath);
}

const  char* xvm_GBS_GetItemTestEndTime(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemTestEndTime(pszItemPath);
}


//通讯命令的参数脚本函数 2019-3-19
void xvm_GBS_ClearCommCmdParas(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_ClearCommCmdParas(pszItemPath);
}

void xvm_GBS_AddCommCmdParaValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dValue)
{
	return GBS_AddCommCmdParaValue(pszItemPath, pszValID, dValue);
}

void xvm_GBS_AddCommCmdParaValue_Long(LPVOID pXvm, const char* pszItemPath, const char* pszValID, long nValue)
{
	return GBS_AddCommCmdParaValue_Long(pszItemPath, pszValID, nValue);
}

void xvm_GBS_AddCommCmdParaValue_String(LPVOID pXvm, const char* pszItemPath, const char* pszValID, const char *pszValue)
{
	return GBS_AddCommCmdParaValue_String(pszItemPath, pszValID, pszValue);
}


//////////////////////////////////////////////////////////////////////////
//常规报告数据处理,处理当前项目的报告数据
//////////////////////////////////////////////////////////////////////////
//多装置、数据库模式下，临时记录，通过添加RptDataMap保证数据不被清除
void xvm_GBS_AddRptMapData(LPVOID pXvm, const char* pszValID)
{
	return GBS_AddRptMapData(pszValID);
}


//设置报告数据
void xvm_GBS_SetItemReportValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dValue)
{
	return GBS_SetItemReportValue(pszItemPath, pszValID, dValue);
}

void xvm_GBS_SetItemReportValueString(LPVOID pXvm, const char* pszItemPath, const char* pszValID, const char* pszValString)
{
	return GBS_SetItemReportValueString(pszItemPath, pszValID, pszValString);
}


//获取报告数据，返回浮点数
double xvm_GBS_GetItemReportValue(LPVOID pXvm, const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemReportValue(pszItemPath, pszValID);
}

//获取报告数据，返回整数
long xvm_GBS_GetItemReportValueLong(LPVOID pXvm, const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemReportValueLong(pszItemPath, pszValID);
}

//获取报告数据，返回string
const  char* xvm_GBS_GetItemReportValueString(LPVOID pXvm, const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemReportValueString(pszItemPath, pszValID);
}


double xvm_GBS_GetItemReportValueEx(LPVOID pXvm, const char* pszItemPath, const char* pszValID, long nIndex)
{
	return GBS_GetItemReportValueEx(pszItemPath, pszValID, nIndex);
}

long xvm_GBS_GetItemReportValueLongEx(LPVOID pXvm, const char* pszItemPath, const char* pszValID, long nIndex)
{
	return GBS_GetItemReportValueLongEx(pszItemPath, pszValID, nIndex);
}

const  char* xvm_GBS_GetItemReportValueStringEx(LPVOID pXvm, const char* pszItemPath, const char* pszValID, long nIndex)
{
	return GBS_GetItemReportValueStringEx(pszItemPath, pszValID, nIndex);
}

long xvm_GBS_GetItemReportCount(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetItemReportCount(pszItemPath);
}

void xvm_GBS_ClearReports(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_ClearReports(pszItemPath);
}

double xvm_GBS_CalRptValMax(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dDefVal)
{
	return GBS_CalRptValMax(pszItemPath, pszValID, dDefVal);
}

double xvm_GBS_CalRptValMin(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dDefVal)
{
	return GBS_CalRptValMin(pszItemPath, pszValID, dDefVal);
}

double xvm_GBS_CalRptValAvg(LPVOID pXvm, const char* pszItemPath, const char* pszValID, double dDefVal)
{
	return GBS_CalRptValAvg(pszItemPath, pszValID, dDefVal);
}


//获取满足条件的报告数据的个数，即根据数据ID和数据值
long xvm_GBS_LGetItemReportDataCount(LPVOID pXvm, const char* pszItemPath, const char *pszDataID, long nDataValue)
{
	return GBS_LGetItemReportDataCount(pszItemPath, pszDataID, nDataValue);
}


//////////////////////////////////////////////////////////////////////////
//扩展报告数据
//////////////////////////////////////////////////////////////////////////
//获取扩展报告数据的CReport->m_pRptDataEx
//nIndex：报告的数据索引
//pszValID：数据的值ID
double xvm_GBS_GetItemReportExValue(LPVOID pXvm, long nIndex, const char* pszValID)
{
	return GBS_GetItemReportExValue(nIndex, pszValID);
}

double xvm_GBS_GetItemReportExValue_D(LPVOID pXvm, const char* pszDataID, const char* pszValID)
{
	return GBS_GetItemReportExValue_D(pszDataID, pszValID);
}

void xvm_GBS_GetItemReportExValue_L(LPVOID pXvm, const char* pszDataID, const char* pszValID)
{
	void xvm_GBS_GetItemReportExValue_L(LPVOID pXvm, const char* pszDataID, const char* pszValID);
}

void xvm_GBS_GetItemReportExValue_S(LPVOID pXvm, const char* pszDataID, const char* pszValID)
{
	void xvm_GBS_GetItemReportExValue_S(LPVOID pXvm, const char* pszDataID, const char* pszValID);
}

const char* xvm_GBS_GetFileInReportEx(LPVOID pXvm, const char *pszFilePostfix, long nFileIndex)
{
	return GBS_GetFileInReportEx(pszFilePostfix, nFileIndex);
}

long xvm_GBS_GetFileNumInReportEx(LPVOID pXvm, const char *pszFilePostfix)
{
	return GBS_GetFileNumInReportEx(pszFilePostfix);
}


//获得报告对象的数据个数
long xvm_GBS_GetItemReportExCount(LPVOID pXvm)
{
	return GBS_GetItemReportExCount(LPVOID pXvm);
}


//根据ID获得项目的报告的数据个数
long xvm_GBS_GetItemReportExDataCountByID(LPVOID pXvm, const char* pszDataAttrID)
{
	return GBS_GetItemReportExDataCountByID(pszDataAttrID);
}


//根据ID以及要获取此ID的第几个数据返回其在报告中对应的Index值；nIndex从0开始 
long xvm_GBS_GetItemReportDataIndexByIDIndex(LPVOID pXvm, const char* pszDataAttrID, long nIndex)
{
	return GBS_GetItemReportDataIndexByIDIndex(pszDataAttrID, nIndex);
}


long xvm_GBS_CalTimeGapStr(LPVOID pXvm, const char* pszTime1, const char* pszTime2)
{
	return GBS_CalTimeGapStr(pszTime1, pszTime2);
}

long xvm_GBS_CalTimeGapStr_us(LPVOID pXvm, const char* pszTime1, const char* pszTime2)
{
	return GBS_CalTimeGapStr_us(pszTime1, pszTime2);
}

long xvm_GBS_CalItemReportTimeGap(LPVOID pXvm, long nItem1Index, long nItem2Index, const char* pszValID)
{
	return GBS_CalItemReportTimeGap(nItem1Index, nItem2Index, pszValID);
}

long xvm_GBS_CalItemReportTimeGapEx(LPVOID pXvm, long nItem1Index, long nItem2Index, const char* pszValID1, const char* pszValID2)
{
	return GBS_CalItemReportTimeGapEx(nItem1Index, nItem2Index, pszValID1, pszValID2);
}

long xvm_GBS_CalItemReportTimeGapEx2(LPVOID pXvm, long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2)
{
	return GBS_CalItemReportTimeGapEx2(nItem1Index, nItem2Index, nValIndex1, nValIndex2);
}


//报告过滤
void xvm_GBS_FilterInit(LPVOID pXvm)
{
	return GBS_FilterInit(LPVOID pXvm);
}

long xvm_GBS_FilterReportExEqualValueL(LPVOID pXvm, const char* pszDataAttrID, long nAttrValue)
{
	return GBS_FilterReportExEqualValueL(pszDataAttrID, nAttrValue);
}

long xvm_GBS_FilterReportExEqualValueStr(LPVOID pXvm, const char* pszDataAttrID, const char* pszValue)
{
	return GBS_FilterReportExEqualValueStr(pszDataAttrID, pszValue);
}

long xvm_GBS_FilterReportExHasValueStr(LPVOID pXvm, const char* pszDataAttrID, const char* pszValue)
{
	return GBS_FilterReportExHasValueStr(pszDataAttrID, pszValue);
}

long xvm_GBS_FilterReportExHasNoValueStr(LPVOID pXvm, const char* pszDataAttrID, const char* pszValue)
{
	return GBS_FilterReportExHasNoValueStr(pszDataAttrID, pszValue);
}

void xvm_GBS_FilterCombineReportEx(LPVOID pXvm, const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator)
{
	return GBS_FilterCombineReportEx(pszDataAttrID, pszRptDataID, pszSeparator);
}


long xvm_GBS_FilterRptExQuery(LPVOID pXvm, const char* pszQuery)
{
	return GBS_FilterRptExQuery(pszQuery);
}

long xvm_GBS_FilterRptExGetCount(LPVOID pXvm)
{
	return GBS_FilterRptExGetCount(LPVOID pXvm);
}

long xvm_GBS_FilterRptExGetLong(LPVOID pXvm, long nIndex, const char* pszDataAttrID)
{
	return GBS_FilterRptExGetLong(nIndex, pszDataAttrID);
}

const char* xvm_GBS_FilterRptExGetString(LPVOID pXvm, long nIndex, const char* pszDataAttrID)
{
	return GBS_FilterRptExGetString(nIndex, pszDataAttrID);
}

double xvm_GBS_FilterRptExGetDouble(LPVOID pXvm, long nIndex, const char* pszDataAttrID)
{
	return GBS_FilterRptExGetDouble(nIndex, pszDataAttrID);
}


long xvm_GBS_FilterRptExGetValCount(LPVOID pXvm, long nDataIndex)
{
	return GBS_FilterRptExGetValCount(nDataIndex);
}

void xvm_GBS_FilterRptExGetValLong(LPVOID pXvm, long nDataIndex, const char* pszValIndex)
{
	return GBS_FilterRptExGetValLong(nDataIndex, pszValIndex);
}

void xvm_GBS_FilterRptExGetValString(LPVOID pXvm, long nDataIndex, const char* pszValIndex)
{
	return GBS_FilterRptExGetValString(nDataIndex, pszValIndex);
}

void xvm_GBS_FilterRptExGetValDouble(LPVOID pXvm, long nDataIndex, const char* pszValIndex)
{
	return GBS_FilterRptExGetValDouble(nDataIndex, pszValIndex);
}

void xvm_GBS_FilterRptExCalValError(LPVOID pXvm, long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_FilterRptExCalValError(nDataIndex, pszValIndex, dRefVal, dAbsErr, dRelErr);
}

void xvm_GBS_FilterRptExCalValErrorEx(LPVOID pXvm, const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_FilterRptExCalValErrorEx(pszDataID, pszValID, dRefVal, dAbsErr, dRelErr);
}


void xvm_Gbs_FilterRptExQueryUseErr(LPVOID pXvm, const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs)
{
	return Gbs_FilterRptExQueryUseErr(pszDataID, pszAttrID, nMaxCount, dStand, nWriteDs);
}

void xvm_Gbs_FilterRptExQueryUseErrEx(LPVOID pXvm, const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs)
{
	return Gbs_FilterRptExQueryUseErrEx(pszDataID, pszAttrID1, pszAttrID2, pszOptr, nMaxCount, dStand, nWriteDs);
}

void xvm_Gbs_FilterRptExQueryUseAvg(LPVOID pXvm, const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs)
{
	return Gbs_FilterRptExQueryUseAvg(pszDataID, pszAttrID, nMaxCount, dStand, nWriteDs);
}

void xvm_Gbs_FilterRptExQueryUseAvgEx(LPVOID pXvm, const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs)
{
	return Gbs_FilterRptExQueryUseAvgEx(pszDataID, pszAttrID1, pszAttrID2, pszOptr, nMaxCount, dStand, nWriteDs);
}

void xvm_Gbs_FilterRptExQueryClearNotUse(LPVOID pXvm)
{
	return Gbs_FilterRptExQueryClearNotUse(LPVOID pXvm);
}


//########################################################################
//报告检索处理函数，处理检索出来的报告数据
//########################################################################
//扩展报告数据为CDvmDataset对象，数据为CDvmData对象
//CTag对象表示一个数据的值
//普通报告数据为CValues*对象，数据值为CValue对象
//所以，对普通报告数据的处理和扩展报告数据的处理方式不一样

//选择某个项目
void xvm_GBS_SSelectItem(LPVOID pXvm, const char *pszItemPath)
{
	return GBS_SSelectItem(pszItemPath);
}


//普通报告处理函数******************************************************

//获得当前选择的项目的报告的个数
void xvm_GBS_SGetItemReportCount(LPVOID pXvm)
{
	return GBS_SGetItemReportCount(LPVOID pXvm);
}


//选择项目的报告对象
void xvm_GBS_SSelectItemReport(LPVOID pXvm, long nReportIndex)
{
	return GBS_SSelectItemReport(nReportIndex);
}


//获得项目的指定的报告的数据：浮点数
void xvm_GBS_SGetItemReportValue(LPVOID pXvm, const char* pszValID)
{
	return GBS_SGetItemReportValue(pszValID);
}


//获得项目的指定的报告的数据：整数
void xvm_GBS_SGetItemReportValueLong(LPVOID pXvm, const char* pszValID)
{
	return GBS_SGetItemReportValueLong(pszValID);
}


//获得项目的指定的报告的数据：字符串
void xvm_GBS_SGetItemReportValueString(LPVOID pXvm, const char* pszValID)
{
	return GBS_SGetItemReportValueString(pszValID);
}


//获得项目的指定的报告的数据个数
void xvm_GBS_SGetItemReportValueCount(LPVOID pXvm) 
{
	return GBS_SGetItemReportValueCount(LPVOID pXvm) 

}


//获取报告的第nDataIndex数据的值
void xvm_GBS_SGetItemReportValue2(nDataIndex) 
{
	return GBS_SGetItemReportValue2(nDataIndex) 

}

void xvm_GBS_SGetItemReportValueLong2(nDataIndex)
{
	return GBS_SGetItemReportValueLong2(nDataIndex);
}

void xvm_GBS_SGetItemReportValueString2(LPVOID pXvm, long nDataIndex)
{
	return GBS_SGetItemReportValueString2(nDataIndex);
}


//扩展报告处理函数******************************************************

//获得项目的指定的报告的数据个数
void xvm_GBS_SGetItemReportExDataCount(LPVOID pXvm)
{
	return GBS_SGetItemReportExDataCount(LPVOID pXvm);
}


//获得项目的指定的报告的数据：浮点数
void xvm_GBS_SGetItemReportExDataValue(LPVOID pXvm, long nDataIndex, const char* pszValID)
{
	return GBS_SGetItemReportExDataValue(nDataIndex, pszValID);
}


//获得项目的指定的报告的数据：整数
void xvm_GBS_SGetItemReportExDataValueLong(LPVOID pXvm, long nDataIndex, const char* pszValID)
{
	return GBS_SGetItemReportExDataValueLong(nDataIndex, pszValID);
}


//获得项目的指定的报告的数据：整数
void xvm_GBS_SGetItemReportExDataValueString(LPVOID pXvm, long nDataIndex, const char* pszValID)
{
	return GBS_SGetItemReportExDataValueString(nDataIndex, pszValID);
}

// 
// //获得项目的指定的报告的数据：浮点数
// double xvm_GBS_SFindItemReportExDataValue(LPVOID pXvm, const char* pszValID
// 
// //获得项目的指定的报告的数据：整数
// long xvm_GBS_SFindItemReportExDataValueLong(LPVOID pXvm, const char* pszValID
// 
// //获得项目的指定的报告的数据：整数
// const char* xvm_GBS_SFindItemReportExDataValueString(LPVOID pXvm, const char* pszValID

//数据集判断函数功能
//获得项目的指定的报告的数据个数
void xvm_GBS_RptExDsGetCount(LPVOID pXvm, const char* pszPath)
{
	return GBS_RptExDsGetCount(pszPath);
}


//获得项目的指定的报告的数据：浮点数
void xvm_GBS_RptExDsGetValueD(LPVOID pXvm, const char* pszPath, long nIndex)
{
	return GBS_RptExDsGetValueD(pszPath, nIndex);
}


//获得项目的指定的报告的数据：整数
void xvm_GBS_RptExDsGetValueL(LPVOID pXvm, const char* pszPath, long nIndex)
{
	return GBS_RptExDsGetValueL(pszPath, nIndex);
}


//获得项目的指定的报告的数据：整数
void xvm_GBS_RptExDsGetValueStr(LPVOID pXvm, const char* pszPath, long nIndex)
{
	return GBS_RptExDsGetValueStr(pszPath, nIndex);
}


//数据验证
void xvm_GBS_RptExDsValidClear(LPVOID pXvm)
{
	return GBS_RptExDsValidClear(LPVOID pXvm);
}

void xvm_GBS_RptExDsValidAddElement(LPVOID pXvm, const char* pszText, long nOption, long nUnbound)
{
	return GBS_RptExDsValidAddElement(pszText, nOption, nUnbound);
}

void xvm_GBS_RptExDsValidAddElementChoice(LPVOID pXvm, const char* pszText, long nOption, long nUnbound)
{
	return GBS_RptExDsValidAddElementChoice(pszText, nOption, nUnbound);
}

void xvm_GBS_RptExDsValid(LPVOID pXvm, long nValidateHead)
{
	return GBS_RptExDsValid(nValidateHead);
}


void xvm_GBS_RecordCmd(LPVOID pXvm, const char *pszCmdID, const char *pszCmdPara)
{
	return GBS_RecordCmd(pszCmdID, pszCmdPara);
}

void xvm_GBS_AdjustWord(LPVOID pXvm, long nPopDlg)
{
	return GBS_AdjustWord(nPopDlg);
}


void xvm_GBS_CalSoeTime(LPVOID pXvm, const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2)
{
	return GBS_CalSoeTime(pszRptID, pszSoeID1, pszSoeID2);
}

void xvm_GBS_CalSoeTimeEx(LPVOID pXvm, const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2)
{
	return GBS_CalSoeTimeEx(pszRptID, pszSoeID1, pszVal1, pszSoeID2, pszVal2);
}

void xvm_GBS_SetSoeTripDesc(LPVOID pXvm, const char *pszRptID, const char *pszSoeID)
{
	return GBS_SetSoeTripDesc(pszRptID, pszSoeID);
}

void xvm_GBS_CalSoeError(LPVOID pXvm, double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr)
{
	return GBS_CalSoeError(dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dAbsErr, dRelErr);
}

void xvm_GBS_CalSoeError2(LPVOID pXvm, double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr)
{
	return GBS_CalSoeError2(dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dErrRefStandVal, dAbsErr, dRelErr);
}



//Record
void xvm_GBS_RcdSetProgID(LPVOID pXvm, const char* pszRcdProgID)
{
	return GBS_RcdSetProgID(pszRcdProgID);
}

void xvm_GBS_RcdExit(LPVOID pXvm)
{
	return GBS_RcdExit(LPVOID pXvm);
}

void xvm_GBS_RcdConfig(LPVOID pXvm, const char* pszPara)
{
	return GBS_RcdConfig(pszPara);
}

void xvm_GBS_RcdSelect(LPVOID pXvm, const char* pszPara)
{
	return GBS_RcdSelect(pszPara);
}

void xvm_GBS_RcdValidate(LPVOID pXvm, const char* pszRsltID)
{
	return GBS_RcdValidate(pszRsltID);
}

void xvm_GBS_RcdCmpClear(LPVOID pXvm)
{
	return GBS_RcdCmpClear(LPVOID pXvm);
}

void xvm_GBS_RcdCmpInit(LPVOID pXvm, const char* pszRcdFilePathRoot, long nCreateTestTimesDir)
{
	return GBS_RcdCmpInit(pszRcdFilePathRoot, nCreateTestTimesDir);
}

void xvm_GBS_RcdCmp(LPVOID pXvm, const char* pszStdFile, const char* pszTestFile)
{
	return GBS_RcdCmp(pszStdFile, pszTestFile);
}

void xvm_GBS_RcdCopyFile(LPVOID pXvm, const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir)
{
	return GBS_RcdCopyFile(pszSrcFile, pszDestFile, nCreateTestTimesDir);
}

void xvm_GBS_RcdAnalyse(LPVOID pXvm, const char* pszRcdFile)
{
	return GBS_RcdAnalyse(pszRcdFile);
}

void xvm_GBS_RcdSetPath(LPVOID pXvm, long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir)
{
	return GBS_RcdSetPath(nAppendItemPath, pszRcdFilePathRoot, nAppendTestTimeDir);
}


//重复测试相关
void xvm_GBS_GetRepeatTimes(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetRepeatTimes(pszItemPath);
}

void xvm_GBS_GetRepeatSuccTimes(LPVOID pXvm, const char* pszItemPath)
{
	return GBS_GetRepeatSuccTimes(pszItemPath);
}


//
void xvm_GBS_SetCmdZoneIndex(LPVOID pXvm, long nZoneIndex)
{
	return GBS_SetCmdZoneIndex(nZoneIndex);
}


//修正动作值的起始值和终止值
void xvm_Gbs_ValidBeginEndValRange(LPVOID pXvm, const char *pBeginValID, const char *pEndValID, const char *pStepID, double dMinRange, double dMinStep, long nMinSteps, long nMaxSteps, long nUseNeg)
{
	return Gbs_ValidBeginEndValRange(pBeginValID, pEndValID, pStepID, dMinRange, dMinStep, nMinSteps, nMaxSteps, nUseNeg);
}


//时间出发函数
void xvm_Gbs_SetTmTriggerSecond(LPVOID pXvm, long nSecond, long nOptr)
{
	return Gbs_SetTmTriggerSecond(nSecond, nOptr);
}

void xvm_Gbs_SetTmTriggerCountMinute(LPVOID pXvm, long nMinute)
{
	return Gbs_SetTmTriggerCountMinute(nMinute);
}

void xvm_Gbs_EnterTmTrigger(LPVOID pXvm)
{
	return Gbs_EnterTmTrigger(LPVOID pXvm);
}

void xvm_Gbs_StartTimerTigger(LPVOID pXvm)
{
	return Gbs_StartTimerTigger(LPVOID pXvm);
}

void xvm_Gbs_StopTimerTrigger(LPVOID pXvm)
{
	return Gbs_StopTimerTrigger(LPVOID pXvm);
}


//数据修约
void xvm_Gbs_ValueRevised(LPVOID pXvm, double dValue, long nDots)
{
	return Gbs_ValueRevised(dValue, nDots);
}


//////////////////////////////////////////////////////////////////////////
//日志部分
void xvm_Gbs_log_query_clear(LPVOID pXvm)
{
	return Gbs_log_query_clear(LPVOID pXvm);
}

void xvm_Gbs_log_query_time(LPVOID pXvm, const char *pszBeginTine, const char *pszEndTime)
{
	return Gbs_log_query_time(pszBeginTine, pszEndTime);
}

void xvm_Gbs_log_query_entryid(LPVOID pXvm, const char *pszEntryID)
{
	return Gbs_log_query_entryid(pszEntryID);
}

void xvm_Gbs_log_query_logctrl(LPVOID pXvm, const char *pszLogCtrl)
{
	return Gbs_log_query_logctrl(pszLogCtrl);
}

void xvm_Gbs_log_query_dataset(LPVOID pXvm, const char *pszDataset)
{
	return Gbs_log_query_dataset(pszDataset);
}


void xvm_Gbs_log_query_data_clear(LPVOID pXvm)
{
	return Gbs_log_query_data_clear(LPVOID pXvm);
}

void xvm_Gbs_log_query_data(LPVOID pXvm, const char *pszDataID)
{
	return Gbs_log_query_data(pszDataID);
}

void xvm_Gbs_log_query_data_get_count(LPVOID pXvm)
{
	return Gbs_log_query_data_get_count(LPVOID pXvm);
}

void xvm_Gbs_log_query_data_add_to_rpt(LPVOID pXvm)
{
	return Gbs_log_query_data_add_to_rpt(LPVOID pXvm);
}


void xvm_Gbs_log_query(LPVOID pXvm, const char *pszScript)
{
	return Gbs_log_query(pszScript);
}


void xvm_Gbs_log_get_count(LPVOID pXvm)
{
	return Gbs_log_get_count(LPVOID pXvm);
}

void xvm_Gbs_log_get_attr(LPVOID pXvm, long nLogIndex, const char *pszAttr)
{
	return Gbs_log_get_attr(nLogIndex, pszAttr);
}

void xvm_Gbs_log_get_data_count(LPVOID pXvm, long nLogIndex)
{
	return Gbs_log_get_data_count(nLogIndex);
}

void xvm_Gbs_log_get_data_attr(LPVOID pXvm, long nLogIndex, long nDataIndex, const char *pszAttr)
{
	return Gbs_log_get_data_attr(nLogIndex, nDataIndex, pszAttr);
}

void xvm_Gbs_log_get_data_attr2(LPVOID pXvm, long nLogIndex, const char *pszDataID, const char *pszAttr)
{
	return Gbs_log_get_data_attr2(nLogIndex, pszDataID, pszAttr);
}


//////////////////////////////////////////////////////////////////////////
//字符串处理
void xvm_GBS_InitStrTok(LPVOID pXvm, const char *pszString, const char *pControl)
{
	return GBS_InitStrTok(pszString, pControl);
}

void xvm_GBS_StrTokCount(LPVOID pXvm)
{
	return GBS_StrTokCount(LPVOID pXvm);
}

void xvm_GBS_StrTokIndex(LPVOID pXvm, long nIndex)
{
	return GBS_StrTokIndex(nIndex);
}

void xvm_GBS_StrTokNext(LPVOID pXvm)
{
	return GBS_StrTokNext(LPVOID pXvm);
}


//装置的全局参数
void xvm_GBS_SetGlobal_Str(LPVOID pXvm, const char *pszID, const char *pszValue)
{
	return GBS_SetGlobal_Str(pszID, pszValue);
}


void xvm_GBS_SetGlobal_Long(LPVOID pXvm, const char *pszID, long nValue)
{
	return GBS_SetGlobal_Long(pszID, nValue);
}

void xvm_GBS_SetGlobal_Float(LPVOID pXvm, const char *pszID, float fValue)
{
	return GBS_SetGlobal_Float(pszID, float fValue);
}


void xvm_GBS_GetGlobal_Str(LPVOID pXvm, const char *pszID)
{
	return GBS_GetGlobal_Str(pszID);
}

void xvm_GBS_GetGlobal_Long(LPVOID pXvm, const char *pszID)
{
	return GBS_GetGlobal_Long(pszID);
}

void xvm_GBS_GetGlobal_Float(LPVOID pXvm, const char *pszID)
{
	return GBS_GetGlobal_Float(pszID);
}

void xvm_GBS_GetGlobal_Long2(LPVOID pXvm, const CString &strID)
{
	return GBS_GetGlobal_Long2(const CString &strID);
}


void xvm_GBS_Set_TestError(LPVOID pXvm, const char *pszTestError)
{
	return GBS_Set_TestError(pszTestError);
}


void xvm_GBS_BinRslt(LPVOID pXvm, const char *pszParaID, const char *pszRsltID)
{
	return GBS_BinRslt(pszParaID, pszRsltID);
}

void xvm_GBS_BinStateRslt(LPVOID pXvm, const char *pszParaID, const char *pszRsltID)
{
	return GBS_BinStateRslt(pszParaID, pszRsltID);
}

void xvm_GBS_BinChngCntRslt(LPVOID pXvm, const char *pszBinChngData, const char *pszRsltID)
{
	return GBS_BinChngCntRslt(pszBinChngData, pszRsltID);
}

/*long xvm_GBS_BinRsltEx(LPVOID pXvm)*///const char *pszParaDatas, const char *pszRsltDatas

//2019-1-6:增加数据对象是否合格的功能 lijq
void xvm_GBS_Set_AddDataErrorValueToRpt(LPVOID pXvm, long nValue)
{
	return GBS_Set_AddDataErrorValueToRpt(nValue);
}

void xvm_GBS_AddDataErrorToRpt(LPVOID pXvm, const char* pszDataID, long nValue)
{
	return GBS_AddDataErrorToRpt(pszDataID, nValue);
}


//2019-6-5 测试记录文件相关
void xvm_GBS_GetTemplateFile(LPVOID pXvm, long nWithPath)
{
	return GBS_GetTemplateFile(nWithPath);
}

void xvm_GBS_GetGbrptFile(LPVOID pXvm, long nWithPath)
{
	return GBS_GetGbrptFile(nWithPath);
}

void xvm_GBS_SetGbrptFileName(LPVOID pXvm, const char *pszFileName)
{
	return GBS_SetGbrptFileName(pszFileName);
}


//2019-7-19 根据装置的编号，调整动作时间
void xvm_GBS_OffsetTestDataByGbrptIndex(LPVOID pXvm, const char *pszDestDataID)
{
	return GBS_OffsetTestDataByGbrptIndex(pszDestDataID);
}


//2020-05-22 磐能版本比对功能 shaolei；
void xvm_GBS_VersionInfoCompare (LPVOID pXvm, const char* pszPath, const char* pszFilePath)
{
	return GBS_VersionInfoCompare (pszPath, pszFilePath);
}


//GbScript_System/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 在调试监视信息中显示消息
// pszMsg：消息文本/消息ID
void xvm_GBS_ShowMessage(LPVOID pXvm, const char* pszMsg)
{
	return GBS_ShowMessage(pszMsg);
}


// 播放音乐文件
// pszFile：音乐文件
// nTimes：播放次数		 0<=表示循环播放 	>0表示实际播放的次数
void xvm_GBS_PlayMusicFile(LPVOID pXvm, const char* pszFileName, long nTimes)
{
	return GBS_PlayMusicFile(pszFileName, nTimes);
}


void xvm_GBS_GetTime(LPVOID pXvm)
{
	return GBS_GetTime(LPVOID pXvm);
}


void xvm_GBS_IEC(LPVOID pXvm, double dValue, double dTp, double dK, double dAlpha)
{
	return GBS_IEC(dValue, dTp, dK, dAlpha);
}

void xvm_GBS_IEEE(LPVOID pXvm, double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2)
{
	return GBS_IEEE(dValue, dTp, dA, dB, dP, dQ, dK1, dK2);
}

void xvm_GBS_IAC(LPVOID pXvm, double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta)
{
	return GBS_IAC(dValue, dTp, dA, dB, dC, dD, dE, dBeta);
}

void xvm_GBS_I2T(LPVOID pXvm, double dValue, double dTp, double dA)
{
	return GBS_I2T(dValue, dTp, dA);
}


void xvm_GBS_CmpDouble(LPVOID pXvm, const char *pszVal1, const char *pszVal2, const char *pszPrecision)
{
	return GBS_CmpDouble(pszVal1, pszVal2, pszPrecision);
}

void xvm_GBS_CmpDoubleVal(LPVOID pXvm, double dVal1, double dVal2, double dPrecision)
{
	return GBS_CmpDoubleVal(dVal1, dVal2, dPrecision);
}

void xvm_GBS_CalRelError(LPVOID pXvm, double dAbsErr, double dRefVal)
{
	return GBS_CalRelError(dAbsErr, dRefVal);
}


//外部程序接口部分(DLL调用)
//strPara格式：”Variable1=value1 Variable2=value2”
//dllReadDatas返回结果的格式相同
void xvm_GBS_dllLoad(LPVOID pXvm, const char *pszDllFilePath, const char *pszDllID)
{
	return GBS_dllLoad(pszDllFilePath, pszDllID);
}

void xvm_GBS_dllCall(LPVOID pXvm, const char *pszDllID, const char *pszPara)
{
	return GBS_dllCall(pszDllID, pszPara);
}

void xvm_GBS_dllReadDatas(LPVOID pXvm, const char *pszDllID, const char *pszPara)
{
	return GBS_dllReadDatas(pszDllID, pszPara);
}

void xvm_GBS_dllUnload(LPVOID pXvm, const char *pszDllID)
{
	return GBS_dllUnload(pszDllID);
}


//EXE调用
void xvm_GBS_RunExe(LPVOID pXvm, const char *pszExeFile, const char *pszPara)
{
	return GBS_RunExe(pszExeFile, pszPara);
}

void xvm_GBS_ExitExe(LPVOID pXvm, const char *pszExeFile)
{
	return GBS_ExitExe(pszExeFile);
}


void xvm_GBS_AddLocalTime(LPVOID pXvm, long nHour, long nMinute, long nSecond)
{
	return GBS_AddLocalTime(nHour, nMinute, nSecond);
}

void xvm_GBS_SubLocalTime(LPVOID pXvm, long nHour, long nMinute, long nSecond)
{
	return GBS_SubLocalTime(nHour, nMinute, nSecond);
}

void xvm_GBS_RandLong(LPVOID pXvm, long nMin, long nMax)
{
	return GBS_RandLong(nMin, nMax);
}

void xvm_GBS_RandFloat(LPVOID pXvm, float fMin, float fMax)
{
	return GBS_RandFloat(float fMin, float fMax);
}

void xvm_GBS_RandDouble(LPVOID pXvm, double fMin, double fMax)
{
	return GBS_RandDouble(fMin, fMax);
}

void xvm_GBS_RandSeed(LPVOID pXvm)
{
	return GBS_RandSeed(LPVOID pXvm);
}


//文件
void xvm_GBS_GetFileNameFromPath(LPVOID pXvm, const char *pszPath)
{
	return GBS_GetFileNameFromPath(pszPath);
}

void xvm_GBS_ParseFilePostfix(LPVOID pXvm, const char* pszFileName)
{
	return GBS_ParseFilePostfix(pszFileName);
}

void xvm_GBS_ParseFileName(LPVOID pXvm, const char *pszFileName)
{
	return GBS_ParseFileName(pszFileName);
}


void xvm_GBS_SubStrToLong(LPVOID pXvm, const char *pszString, long nBegin, long nLen)
{
	return GBS_SubStrToLong(pszString, nBegin, nLen);
}

void xvm_GBS_SubStrToStr(LPVOID pXvm, const char *pszString, long nBegin, long nLen)
{
	return GBS_SubStrToStr(pszString, nBegin, nLen);
}

void xvm_GBS_GetSecondsFromMidnight(LPVOID pXvm)
{
	return GBS_GetSecondsFromMidnight(LPVOID pXvm);
}


// void xvm_GBS_LogTime_PcTime(PPCTIME pTm)
// void xvm_GBS_LogTime_GpsTime(PGPSTIME pTm)

//GbScript_Engine////////////////////////////////////////////////////////////////////////////////////////////////
// 规约帧录波设置
void xvm_GBS_RecordPackage(LPVOID pXvm, const char* pszPkgID)
{
	return GBS_RecordPackage(pszPkgID);
}

void xvm_GBS_UnRecordPackage(LPVOID pXvm, const char* pszPkgID)
{
	return GBS_UnRecordPackage(pszPkgID);
}

void xvm_GBS_GetPackagePcTime(LPVOID pXvm, const char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail)
{
	return GBS_GetPackagePcTime(pszPkgID, pszPcTimeID, nUseHeadOrTail);
}


// 读取标准源装置GPS时间与PC时间的之间对应关系
void xvm_GBS_GetGpsPcTimeMap(LPVOID pXvm, const char *pszGpsTime, const char *pszPcTime)
{
	return GBS_GetGpsPcTimeMap(pszGpsTime, pszPcTime);
}


//读取输出开始时刻的标准源装置GPS时间
void xvm_GBS_GetOutGpsTime(LPVOID pXvm, const char *pszGpsTimeID)
{
	return GBS_GetOutGpsTime(pszGpsTimeID);
}


//计算时间间隔
void xvm_GBS_CalGpsPcTimeGap(LPVOID pXvm, const char *pszTimeID1, const char *pszTimerID2)
{
	return GBS_CalGpsPcTimeGap(pszTimeID1, pszTimerID2);
}

void xvm_GBS_CalTimeGap(LPVOID pXvm, const char *pszTime1, const char *pszTimer2)
{
	return GBS_CalTimeGap(pszTime1, pszTimer2);
}

void xvm_GBS_CalTimeGapCurr(LPVOID pXvm, const char *pszTime)
{
	return GBS_CalTimeGapCurr(pszTime);
}



//创建一个GPS的时间变量
void xvm_GBS_CreateGpsDateTime(LPVOID pXvm, const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs)
{
	return GBS_CreateGpsDateTime(pszTimeID, nYear, nMonth, nDay, nHour, nMinute, nS, nMs, nUs);
}

void xvm_GBS_CreateGpsTime(LPVOID pXvm, const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs)
{
	return GBS_CreateGpsTime(pszTimeID, nHour, nMinute, nS, nMs, nUs);
}


//读取标准源的结果数据
void xvm_GBS_ReadMacroTestResult(LPVOID pXvm)
{
	return GBS_ReadMacroTestResult(LPVOID pXvm);
}


//重新下载电气量测试项目的参数
void xvm_GBS_DownloadMacroTestPara(LPVOID pXvm)
{
	return GBS_DownloadMacroTestPara(LPVOID pXvm);
}


//通讯规约引擎接口函数
void xvm_GBS_PpGetDeviceAttr(LPVOID pXvm, const char *pszAttrID)
{
	return GBS_PpGetDeviceAttr(pszAttrID);
}

void xvm_GBS_PpGetDeviceAttrL(LPVOID pXvm, const char *pszAttrID)
{
	return GBS_PpGetDeviceAttrL(pszAttrID);
}

void xvm_GBS_PpGetDeviceAttrStr(LPVOID pXvm, const char *pszAttrID)
{
	return GBS_PpGetDeviceAttrStr(pszAttrID);
}

void xvm_GBS_PpSetDeviceAttrL(LPVOID pXvm, const char *pszAttrID, long nValue)
{
	return GBS_PpSetDeviceAttrL(pszAttrID, nValue);
}

void xvm_GBS_PpSetDeviceAttrStr(LPVOID pXvm, const char *pszAttrID, const char *pszValue)
{
	return GBS_PpSetDeviceAttrStr(pszAttrID, pszValue);
}


void xvm_GBS_PpRptGetDevieNodeDatas(LPVOID pXvm, const char *pszNodePath)
{
	return GBS_PpRptGetDevieNodeDatas(pszNodePath);
}

void xvm_GBS_PpRptGetDeviceAttrs(LPVOID pXvm)
{
	return GBS_PpRptGetDeviceAttrs(LPVOID pXvm);
}

void xvm_GBS_PpGetDevieNodeDataAttr(LPVOID pXvm, const char *strDataPath, const char *strAttrID)
{
	return GBS_PpGetDevieNodeDataAttr(strDataPath, strAttrID);
}

// long xvm_GBS_PpSetDevieNodeDataAttr(LPVOID pXvm, const char *strDataPath, const char *strAttrID, const char *strValue
void xvm_GBS_PpSetDevieNodeDataAttr(LPVOID pXvm, const char *strDataPath, const char *strAttrID, double dValue)
{
	return GBS_PpSetDevieNodeDataAttr(strDataPath, strAttrID, dValue);
}

void xvm_GBS_PpDeleteAllNodeData(LPVOID pXvm, const char *pszNodePath)
{
	return GBS_PpDeleteAllNodeData(pszNodePath);
}


void xvm_GBS_PpCreateDevice(LPVOID pXvm, const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID)
{
	return GBS_PpCreateDevice(pszPpFile, pszDeviceFile, pszDeviceID);
}

void xvm_GBS_PpReleaseDevice(LPVOID pXvm, const char *pszDeviceID)
{
	return GBS_PpReleaseDevice(pszDeviceID);
}

void xvm_GBS_PpReleaseAllDevice(LPVOID pXvm)
{
	return GBS_PpReleaseAllDevice(LPVOID pXvm);
}

// long xvm_GBS_PpRun(LPVOID pXvm, const char *pszDeviceID, const char *pszProcedureID, const char *pszPara
void xvm_GBS_GetTestIndex(LPVOID pXvm)
{
	return GBS_GetTestIndex(LPVOID pXvm);
}


void xvm_GBS_IsProtocol(LPVOID pXvm, const char *pszProtocol)
{
	return GBS_IsProtocol(pszProtocol);
}

