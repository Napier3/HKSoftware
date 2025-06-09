#include "StdAfx.h"
#include "SmartTestHostApi_lua.h"

#include "GbScriptFunctions.h"
#include "GbScript_System.h"
#include "GbScript_Engine.h"
#include "GbScript_GuideBook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//GbScript_GuideBook/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//跳转到项目
void lua_GBS_GotoItem(const char* pszItemPath) 
{
	return GBS_GotoItem(NULL, pszItemPath);
}

void lua_GBS_GotoItemEx(const char* pszItemPath, long nRslt, long nAndOr)
{
	return GBS_GotoItemEx(NULL, pszItemPath, nRslt, nAndOr);
}

void lua_GBS_FireTestNextMsg() //只针对试验中的通讯命令，目前只支持提示信息
{
	return GBS_FireTestNextMsg(NULL);
}

void lua_GBS_BreakLoop(long nLevel)
{
	return GBS_BreakLoop(NULL, nLevel);
}

//命令消息
void lua_GBS_MtExcuteCmd(const char *pszCmd, const char *pCmdPara)
{
	return GBS_MtExcuteCmd(NULL, pszCmd, pCmdPara);
}

void lua_GBS_MtRegistPpDataMsg(const char *pszDvmDataPath)
{
	return GBS_MtRegistPpDataMsg(NULL, pszDvmDataPath);
}

void lua_GBS_MtUnRegistPpDataMsg(const char *pszDvmDataPath)
{
	return GBS_MtUnRegistPpDataMsg(NULL, pszDvmDataPath) ;
}

void lua_GBS_MtRegistPpDataMsgRange(const char *pszDvmDataPath, double dMin, double dMax)
{
	return GBS_MtRegistPpDataMsgRange(NULL, pszDvmDataPath, dMin, dMax);
}

void lua_GBS_BreakItems(long nLevel) 
{
	return GBS_BreakItems(NULL, nLevel);
}

void lua_GBS_SetUploadRptFile(const char *pszFileName) 
{
	return GBS_SetUploadRptFile(NULL, pszFileName);
}

void lua_GBS_MtRegistCmdMsg(const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam)
{
	return GBS_MtRegistCmdMsg(NULL, pszCmdID, nCmdState, nCmdWParam, nCmdLParam);
}

void lua_GBS_MtUnRegistCmdMsg(const char *pszCmdID)
{
	return GBS_MtUnRegistCmdMsg(NULL, pszCmdID);
}

//数据集访问
double lua_GBS_GetDsDataValue(const char* pszID)
{
	return GBS_GetDsDataValue(NULL, pszID);
}

double lua_GBS_GetDsDataAttr(const char* pszID, const char *pszAttrID)
{
	return GBS_GetDsDataAttr(NULL, pszID, pszAttrID);
}

const char* lua_GBS_GetDsDataAttrStr(const char* pszID, const char *pszAttrID)
{
	return GBS_GetDsDataAttrStr(NULL, pszID, pszAttrID);
}

void lua_GBS_SetDsDataValue(const char* pszID, double dVal)
{
	return GBS_SetDsDataValue(NULL, pszID, dVal);
}
const char* lua_GBS_GetDsDataValueStr(const char* pszID)
{
	return GBS_GetDsDataValueStr(NULL, pszID);
}
void lua_GBS_SetDsDataValueStr(const char* pszID, const char* pszVal)
{
	return GBS_SetDsDataValueStr(NULL, pszID, pszVal);
}
double lua_GBS_GetDsDataValueEx(long nDeviceIndex, const char* pszID)
{
	return GBS_GetDsDataValueEx(NULL, nDeviceIndex, pszID);
}
void lua_GBS_SetDsDataValueEx(long nDeviceIndex, const char* pszID, double dVal)
{
	return GBS_SetDsDataValueEx(NULL, nDeviceIndex, pszID, dVal);
}
const char* lua_GBS_GetDsDataValueStrEx(long nDeviceIndex, const char* pszID)
{
	return GBS_GetDsDataValueStrEx(NULL, nDeviceIndex, pszID);
}
void lua_GBS_SetDsDataValueStrEx(long nDeviceIndex, const char* pszID, const char* pszVal)
{
	return GBS_SetDsDataValueStrEx(NULL, nDeviceIndex, pszID, pszVal);
}
long lua_GBS_CalAinError(const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_CalAinError(NULL, pszAinID, dRefVal, dAbsErr, dRelErr);
}
long lua_GBS_CalAinErrorEx(double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_CalAinErrorEx(NULL, dRate, pszAinID, dRefVal, dAbsErr, dRelErr);
}
long lua_GBS_CalAinErrorNom(double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr)
{
	return GBS_CalAinErrorNom(NULL, dRate, pszAinID, dRefVal, dNom, dAbsErr, dRelErr);
}

long lua_GBS_CalAinStdError(double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_CalAinStdError(NULL, dRate, pszAinID, dRefVal, dAbsErr, dRelErr);
}

long lua_GBS_CalAinStdError2(const char *pszAinID, const char *pszAinBaseID,double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_CalAinStdError2(NULL, pszAinID, pszAinBaseID, dRefVal, dAbsErr, dRelErr);
}

long lua_GBS_CalAinError2(const char *pszAinID, const char *pszAinBaseID, double dRate, double dAbsErr, double dRelErr)
{
	return GBS_CalAinError2(NULL, pszAinID, pszAinBaseID, dRate, dAbsErr, dRelErr);
}


double lua_GBS_CalVariation(double dValue, double dTheoreticalVal, double dBaseValue, double dRate)
{
	return GBS_CalVariation(NULL, dValue, dTheoreticalVal, dBaseValue, dRate);
}

long lua_GBS_CalVariationErr(double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr)
{
	return GBS_CalVariationErr(NULL, dValue, dTheoreticalVal, dBaseValue, dRate, dRelErr);
}

long lua_GBS_CalVariationErrEx(const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate)
{
	return GBS_CalVariationErrEx(NULL, pszAinID, pszTheoreticalID, pszBaseValueID, pszRsltID, pszRelErr, dRate);
}


long lua_GBS_FlterCalErrorMax(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_FlterCalErrorMax(NULL, pszValID, pszAbsErrID, pszRelErrID, dRefVal, dAbsErr, dRelErr);
}

long lua_GBS_FlterCalErrorMin(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_FlterCalErrorMin(NULL, pszValID, pszAbsErrID, pszRelErrID, dRefVal, dAbsErr, dRelErr);
}


// 获取定值数据
// pszID：数据的ID
double lua_GBS_GetSetValue(const char* pszID)
{
	return GBS_GetSetValue(NULL, pszID);
}

void lua_GBS_SetSetValue(const char* pszID, double dVal)
{
	return GBS_SetSetValue(NULL, pszID, dVal);
}


//void lua_GBS_GetSoftswitchValue(const char* pszID
// void lua_GBS_SetSoftswitchValue(const char* pszID, double dVal

// 获取系统参数数据数据
// pszID：数据的ID
double lua_GBS_GetSysParaValue(const char* pszID)
{
	return GBS_GetSysParaValue(NULL, pszID);
}


void lua_GBS_SetSysParaValue(const char* pszID, double dValue)
{
	return GBS_SetSysParaValue(NULL, pszID, dValue);
}


// 获取测试参数数据
// pszID：数据的ID
double lua_GBS_GetTestParaValue(const char* pszID)
{
	return GBS_GetTestParaValue(NULL, pszID);
}

const char* lua_GBS_GetTestParaStr(const char* pszID)
{
	return GBS_GetTestParaStr(NULL, pszID);
}


// 设置测试参数数据
// pszID：数据的ID
void lua_GBS_SetTestParaValue(const char* pszID, double dValue)
{
	return GBS_SetTestParaValue(NULL, pszID, dValue);
}

void lua_GBS_SetTestParaStr(const char* pszID, const char *pszValue)
{
	return GBS_SetTestParaStr(NULL, pszID, pszValue);
}


//设置满足条件的项目的Show属性
//pszItemPath为Item的路径
void lua_GBS_SetItemShow(const char* pszItemPath, long nShow)
{
	return GBS_SetItemShow(NULL, pszItemPath, nShow);
}


// 获取满足条件的项目的Show属性
// pszItemPath为Item的路径
long lua_GBS_GetItemShow(const char* pszItemPath)
{
	return GBS_GetItemShow(NULL, pszItemPath);
}


// 设置满足条件的项目的Enable属性
// pszItemPath为Item的路径
void lua_GBS_SetItemEnable(const char* pszItemPath, long nEnable)
{
	return GBS_SetItemEnable(NULL, pszItemPath, nEnable);
}


// 获取满足条件的项目的Enable属性
// pszItemPath为Item的路径
long lua_GBS_GetItemEnable(const char* pszItemPath)
{
	return GBS_GetItemEnable(NULL, pszItemPath);
}



//Seelct
void lua_GBS_SetItemSelect(const char* pszItemPath, long nSelect)
{
	return GBS_SetItemSelect(NULL, pszItemPath, nSelect);
}

long lua_GBS_GetItemSelect(const char* pszItemPath)
{
	return GBS_GetItemSelect(NULL, pszItemPath);
}


// 设置满足条件的项目的Name属性
// pszItemPath为Item的路径
void lua_GBS_SetItemName(const char* pszItemPath, const char* pszName)
{
	return GBS_SetItemName(NULL, pszItemPath, pszName);
}


// 获取满足条件的项目的Name属性
// pszItemPath为Item的路径
const char* lua_GBS_GetItemName(const char* pszItemPath)
{
	return GBS_GetItemName(NULL, pszItemPath);
}


// 设置满足条件的项目的结果判断
// pszItemPath为Item的路径
void lua_GBS_SetItemResultJudge(const char* pszItemPath, long nResult)
{
	return GBS_SetItemResultJudge(NULL, pszItemPath, nResult);
}


long lua_GBS_GetItemResultJudge(const char* pszItemPath)
{
	return GBS_GetItemResultJudge(NULL, pszItemPath);
}



// 设置满足条件的项目的数据的值
// pszItemPath为Item的路径
void lua_GBS_SetItemParaValue(const char* pszItemPath, const char* pszValID, double dValue)
{
	return GBS_SetItemParaValue(NULL, pszItemPath, pszValID, dValue);
}

void lua_GBS_SetItemParaValueStr(const char* pszItemPath, const char* pszValID, const char *pszValue)
{
	return GBS_SetItemParaValueStr(NULL, pszItemPath, pszValID, pszValue);
}


double lua_GBS_GetItemParaValue(const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemParaValue(NULL, pszItemPath, pszValID);
}

const char* lua_GBS_GetItemParaString(const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemParaString(NULL, pszItemPath, pszValID);
}

const  char* lua_GBS_GetItemTestTime(const char* pszItemPath)
{
	return GBS_GetItemTestTime(NULL, pszItemPath);
}

const  char* lua_GBS_GetItemTestBeginTime(const char* pszItemPath)
{
	return GBS_GetItemTestBeginTime(NULL, pszItemPath);
}

const  char* lua_GBS_GetItemTestEndTime(const char* pszItemPath)
{
	return GBS_GetItemTestEndTime(NULL, pszItemPath);
}


//通讯命令的参数脚本函数 2019-3-19
void lua_GBS_ClearCommCmdParas(const char* pszItemPath)
{
	return GBS_ClearCommCmdParas(NULL, pszItemPath);
}

void lua_GBS_AddCommCmdParaValue(const char* pszItemPath, const char* pszValID, double dValue)
{
	return GBS_AddCommCmdParaValue(NULL, pszItemPath, pszValID, dValue);
}

void lua_GBS_AddCommCmdParaValue_Long(const char* pszItemPath, const char* pszValID, long nValue)
{
	return GBS_AddCommCmdParaValue_Long(NULL, pszItemPath, pszValID, nValue);
}

void lua_GBS_AddCommCmdParaValue_String(const char* pszItemPath, const char* pszValID, const char *pszValue)
{
	return GBS_AddCommCmdParaValue_String(NULL, pszItemPath, pszValID, pszValue);
}


//////////////////////////////////////////////////////////////////////////
//常规报告数据处理,处理当前项目的报告数据
//////////////////////////////////////////////////////////////////////////
//多装置、数据库模式下，临时记录，通过添加RptDataMap保证数据不被清除
void lua_GBS_AddRptMapData(const char* pszValID)
{
	return GBS_AddRptMapData(NULL, pszValID);
}


//设置报告数据
void lua_GBS_SetItemReportValue(const char* pszItemPath, const char* pszValID, double dValue)
{
	return GBS_SetItemReportValue(NULL, pszItemPath, pszValID, dValue);
}

void lua_GBS_SetItemReportValueString(const char* pszItemPath, const char* pszValID, const char* pszValString)
{
	return GBS_SetItemReportValueString(NULL, pszItemPath, pszValID, pszValString);
}


//获取报告数据，返回浮点数
double lua_GBS_GetItemReportValue(const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemReportValue(NULL, pszItemPath, pszValID);
}

//获取报告数据，返回整数
long lua_GBS_GetItemReportValueLong(const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemReportValueLong(NULL, pszItemPath, pszValID);
}

//获取报告数据，返回string
const  char* lua_GBS_GetItemReportValueString(const char* pszItemPath, const char* pszValID)
{
	return GBS_GetItemReportValueString(NULL, pszItemPath, pszValID);
}


double lua_GBS_GetItemReportValueEx(const char* pszItemPath, const char* pszValID, long nIndex)
{
	return GBS_GetItemReportValueEx(NULL, pszItemPath, pszValID, nIndex);
}

long lua_GBS_GetItemReportValueLongEx(const char* pszItemPath, const char* pszValID, long nIndex)
{
	return GBS_GetItemReportValueLongEx(NULL, pszItemPath, pszValID, nIndex);
}

const  char* lua_GBS_GetItemReportValueStringEx(const char* pszItemPath, const char* pszValID, long nIndex)
{
	return GBS_GetItemReportValueStringEx(NULL, pszItemPath, pszValID, nIndex);
}

long lua_GBS_GetItemReportCount(const char* pszItemPath)
{
	return GBS_GetItemReportCount(NULL, pszItemPath);
}

void lua_GBS_ClearReports(const char* pszItemPath)
{
	return GBS_ClearReports(NULL, pszItemPath);
}

double lua_GBS_CalRptValMax(const char* pszItemPath, const char* pszValID, double dDefVal)
{
	return GBS_CalRptValMax(NULL, pszItemPath, pszValID, dDefVal);
}

double lua_GBS_CalRptValMin(const char* pszItemPath, const char* pszValID, double dDefVal)
{
	return GBS_CalRptValMin(NULL, pszItemPath, pszValID, dDefVal);
}

double lua_GBS_CalRptValAvg(const char* pszItemPath, const char* pszValID, double dDefVal)
{
	return GBS_CalRptValAvg(NULL, pszItemPath, pszValID, dDefVal);
}


//获取满足条件的报告数据的个数，即根据数据ID和数据值
long lua_GBS_LGetItemReportDataCount(const char* pszItemPath, const char *pszDataID, long nDataValue)
{
	return GBS_LGetItemReportDataCount(NULL, pszItemPath, pszDataID, nDataValue);
}


//////////////////////////////////////////////////////////////////////////
//扩展报告数据
//////////////////////////////////////////////////////////////////////////
//获取扩展报告数据的CReport->m_pRptDataEx
//nIndex：报告的数据索引
//pszValID：数据的值ID
double lua_GBS_GetItemReportExValue(long nIndex, const char* pszValID)
{
	return GBS_GetItemReportExValue(NULL, nIndex, pszValID);
}

double lua_GBS_GetItemReportExValue_D(const char* pszDataID, const char* pszValID)
{
	return GBS_GetItemReportExValue_D(NULL, pszDataID, pszValID);
}

long lua_GBS_GetItemReportExValue_L(const char* pszDataID, const char* pszValID)
{
	return GBS_GetItemReportExValue_L(NULL, pszDataID, pszValID);
}

char* lua_GBS_GetItemReportExValue_S(const char* pszDataID, const char* pszValID)
{
	return GBS_GetItemReportExValue_S(NULL, pszDataID, pszValID);
}

const char* lua_GBS_GetFileInReportEx(const char *pszFilePostfix, long nFileIndex)
{
	return GBS_GetFileInReportEx(NULL, pszFilePostfix, nFileIndex);
}

long lua_GBS_GetFileNumInReportEx(const char *pszFilePostfix)
{
	return GBS_GetFileNumInReportEx(NULL, pszFilePostfix);
}


//获得报告对象的数据个数
long lua_GBS_GetItemReportExCount()
{
	return GBS_GetItemReportExCount(NULL);
}


//根据ID获得项目的报告的数据个数
long lua_GBS_GetItemReportExDataCountByID(const char* pszDataAttrID)
{
	return GBS_GetItemReportExDataCountByID(NULL, pszDataAttrID);
}


//根据ID以及要获取此ID的第几个数据返回其在报告中对应的Index值；nIndex从0开始 
long lua_GBS_GetItemReportDataIndexByIDIndex(const char* pszDataAttrID, long nIndex)
{
	return GBS_GetItemReportDataIndexByIDIndex(NULL, pszDataAttrID, nIndex);
}


long lua_GBS_CalTimeGapStr(const char* pszTime1, const char* pszTime2)
{
	return GBS_CalTimeGapStr(NULL, pszTime1, pszTime2);
}

long lua_GBS_CalTimeGapStr_us(const char* pszTime1, const char* pszTime2)
{
	return GBS_CalTimeGapStr_us(NULL, pszTime1, pszTime2);
}

long lua_GBS_CalItemReportTimeGap(long nItem1Index, long nItem2Index, const char* pszValID)
{
	return GBS_CalItemReportTimeGap(NULL, nItem1Index, nItem2Index, pszValID);
}

long lua_GBS_CalItemReportTimeGapEx(long nItem1Index, long nItem2Index, const char* pszValID1, const char* pszValID2)
{
	return GBS_CalItemReportTimeGapEx(NULL, nItem1Index, nItem2Index, pszValID1, pszValID2);
}

long lua_GBS_CalItemReportTimeGapEx2(long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2)
{
	return GBS_CalItemReportTimeGapEx2(NULL, nItem1Index, nItem2Index, nValIndex1, nValIndex2);
}


//报告过滤
void lua_GBS_FilterInit()
{
	return GBS_FilterInit(NULL);
}

long lua_GBS_FilterReportExEqualValueL(const char* pszDataAttrID, long nAttrValue)
{
	return GBS_FilterReportExEqualValueL(NULL, pszDataAttrID, nAttrValue);
}

long lua_GBS_FilterReportExEqualValueStr(const char* pszDataAttrID, const char* pszValue)
{
	return GBS_FilterReportExEqualValueStr(NULL, pszDataAttrID, pszValue);
}

long lua_GBS_FilterReportExHasValueStr(const char* pszDataAttrID, const char* pszValue)
{
	return GBS_FilterReportExHasValueStr(NULL, pszDataAttrID, pszValue);
}

long lua_GBS_FilterReportExHasNoValueStr(const char* pszDataAttrID, const char* pszValue)
{
	return GBS_FilterReportExHasNoValueStr(NULL, pszDataAttrID, pszValue);
}

void lua_GBS_FilterCombineReportEx(const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator)
{
	return GBS_FilterCombineReportEx(NULL, pszDataAttrID, pszRptDataID, pszSeparator);
}


long lua_GBS_FilterRptExQuery(const char* pszQuery)
{
	return GBS_FilterRptExQuery(NULL, pszQuery);
}

long lua_GBS_FilterRptExGetCount()
{
	return GBS_FilterRptExGetCount(NULL);
}

long lua_GBS_FilterRptExGetLong(long nIndex, const char* pszDataAttrID)
{
	return GBS_FilterRptExGetLong(NULL, nIndex, pszDataAttrID);
}

const char* lua_GBS_FilterRptExGetString(long nIndex, const char* pszDataAttrID)
{
	return GBS_FilterRptExGetString(NULL, nIndex, pszDataAttrID);
}

double lua_GBS_FilterRptExGetDouble(long nIndex, const char* pszDataAttrID)
{
	return GBS_FilterRptExGetDouble(NULL, nIndex, pszDataAttrID);
}


long lua_GBS_FilterRptExGetValCount(long nDataIndex)
{
	return GBS_FilterRptExGetValCount(NULL, nDataIndex);
}

long lua_GBS_FilterRptExGetValLong(long nDataIndex, const char* pszValIndex)
{
	return GBS_FilterRptExGetValLong(NULL, nDataIndex, pszValIndex);
}

char* lua_GBS_FilterRptExGetValString(long nDataIndex, const char* pszValIndex)
{
	return GBS_FilterRptExGetValString(NULL, nDataIndex, pszValIndex);
}

double lua_GBS_FilterRptExGetValDouble(long nDataIndex, const char* pszValIndex)
{
	return GBS_FilterRptExGetValDouble(NULL, nDataIndex, pszValIndex);
}

long lua_GBS_FilterRptExCalValError(long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_FilterRptExCalValError(NULL, nDataIndex, pszValIndex, dRefVal, dAbsErr, dRelErr);
}

long lua_GBS_FilterRptExCalValErrorEx(const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr)
{
	return GBS_FilterRptExCalValErrorEx(NULL, pszDataID, pszValID, dRefVal, dAbsErr, dRelErr);
}


double lua_Gbs_FilterRptExQueryUseErr(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs)
{
	return Gbs_FilterRptExQueryUseErr(NULL, pszDataID, pszAttrID, nMaxCount, dStand, nWriteDs);
}

double lua_Gbs_FilterRptExQueryUseErrEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs)
{
	return Gbs_FilterRptExQueryUseErrEx(NULL, pszDataID, pszAttrID1, pszAttrID2, pszOptr, nMaxCount, dStand, nWriteDs);
}

double lua_Gbs_FilterRptExQueryUseAvg(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs)
{
	return Gbs_FilterRptExQueryUseAvg(NULL, pszDataID, pszAttrID, nMaxCount, dStand, nWriteDs);
}

double lua_Gbs_FilterRptExQueryUseAvgEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs)
{
	return Gbs_FilterRptExQueryUseAvgEx(NULL, pszDataID, pszAttrID1, pszAttrID2, pszOptr, nMaxCount, dStand, nWriteDs);
}

long lua_Gbs_FilterRptExQueryClearNotUse()
{
	return Gbs_FilterRptExQueryClearNotUse(NULL);
}


//########################################################################
//报告检索处理函数，处理检索出来的报告数据
//########################################################################
//扩展报告数据为CDvmDataset对象，数据为CDvmData对象
//CTag对象表示一个数据的值
//普通报告数据为CValues*对象，数据值为CValue对象
//所以，对普通报告数据的处理和扩展报告数据的处理方式不一样

//选择某个项目
long lua_GBS_SSelectItem(const char *pszItemPath)
{
	return GBS_SSelectItem(NULL, pszItemPath);
}


//普通报告处理函数******************************************************

//获得当前选择的项目的报告的个数
long lua_GBS_SGetItemReportCount()
{
	return GBS_SGetItemReportCount(NULL);
}


//选择项目的报告对象
long lua_GBS_SSelectItemReport(long nReportIndex)
{
	return GBS_SSelectItemReport(NULL, nReportIndex);
}


//获得项目的指定的报告的数据：浮点数
double lua_GBS_SGetItemReportValue(const char* pszValID)
{
	return GBS_SGetItemReportValue(NULL, pszValID);
}


//获得项目的指定的报告的数据：整数
long lua_GBS_SGetItemReportValueLong(const char* pszValID)
{
	return GBS_SGetItemReportValueLong(NULL, pszValID);
}


//获得项目的指定的报告的数据：字符串
const char* lua_GBS_SGetItemReportValueString(const char* pszValID)
{
	return GBS_SGetItemReportValueString(NULL, pszValID);
}


//获得项目的指定的报告的数据个数
long lua_GBS_SGetItemReportValueCount() 
{
	return GBS_SGetItemReportValueCount(NULL) ;
}


//获取报告的第nDataIndex数据的值
double lua_GBS_SGetItemReportValue2(long nDataIndex) 
{
	return GBS_SGetItemReportValue2(NULL, nDataIndex) ;

}

long lua_GBS_SGetItemReportValueLong2(long nDataIndex)
{
	return GBS_SGetItemReportValueLong2(NULL, nDataIndex);
}

const char* lua_GBS_SGetItemReportValueString2(long nDataIndex)
{
	return GBS_SGetItemReportValueString2(NULL, nDataIndex);
}


//扩展报告处理函数******************************************************

//获得项目的指定的报告的数据个数
long lua_GBS_SGetItemReportExDataCount()
{
	return GBS_SGetItemReportExDataCount(NULL);
}


//获得项目的指定的报告的数据：浮点数
double lua_GBS_SGetItemReportExDataValue(long nDataIndex, const char* pszValID)
{
	return GBS_SGetItemReportExDataValue(NULL, nDataIndex, pszValID);
}


//获得项目的指定的报告的数据：整数
long lua_GBS_SGetItemReportExDataValueLong(long nDataIndex, const char* pszValID)
{
	return GBS_SGetItemReportExDataValueLong(NULL, nDataIndex, pszValID);
}


//获得项目的指定的报告的数据：整数
const char* lua_GBS_SGetItemReportExDataValueString(long nDataIndex, const char* pszValID)
{
	return GBS_SGetItemReportExDataValueString(NULL, nDataIndex, pszValID);
}

// 
// //获得项目的指定的报告的数据：浮点数
// double lua_GBS_SFindItemReportExDataValue(const char* pszValID
// 
// //获得项目的指定的报告的数据：整数
// long lua_GBS_SFindItemReportExDataValueLong(const char* pszValID
// 
// //获得项目的指定的报告的数据：整数
// const char* lua_GBS_SFindItemReportExDataValueString(const char* pszValID

//数据集判断函数功能
//获得项目的指定的报告的数据个数
long lua_GBS_RptExDsGetCount(const char* pszPath)
{
	return GBS_RptExDsGetCount(NULL, pszPath);
}


//获得项目的指定的报告的数据：浮点数
double lua_GBS_RptExDsGetValueD(const char* pszPath, long nIndex)
{
	return GBS_RptExDsGetValueD(NULL, pszPath, nIndex);
}


//获得项目的指定的报告的数据：整数
long lua_GBS_RptExDsGetValueL(const char* pszPath, long nIndex)
{
	return GBS_RptExDsGetValueL(NULL, pszPath, nIndex);
}


//获得项目的指定的报告的数据：整数
const char* lua_GBS_RptExDsGetValueStr(const char* pszPath, long nIndex)
{
	return GBS_RptExDsGetValueStr(NULL, pszPath, nIndex);
}


//数据验证
void lua_GBS_RptExDsValidClear()
{
	return GBS_RptExDsValidClear(NULL);
}

void lua_GBS_RptExDsValidAddElement(const char* pszText, long nOption, long nUnbound)
{
	return GBS_RptExDsValidAddElement(NULL, pszText, nOption, nUnbound);
}

void lua_GBS_RptExDsValidAddElementChoice(const char* pszText, long nOption, long nUnbound)
{
	return GBS_RptExDsValidAddElementChoice(NULL, pszText, nOption, nUnbound);
}

long lua_GBS_RptExDsValid(long nValidateHead)
{
	return GBS_RptExDsValid(NULL, nValidateHead);
}


long lua_GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara)
{
	return GBS_RecordCmd(NULL, pszCmdID, pszCmdPara);
}

long lua_GBS_AdjustWord(long nPopDlg)
{
	return GBS_AdjustWord(NULL, nPopDlg);
}


void lua_GBS_CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2)
{
	return GBS_CalSoeTime(NULL, pszRptID, pszSoeID1, pszSoeID2);
}

void lua_GBS_CalSoeTimeEx(const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2)
{
	return GBS_CalSoeTimeEx(NULL, pszRptID, pszSoeID1, pszVal1, pszSoeID2, pszVal2);
}

void lua_GBS_SetSoeTripDesc(const char *pszRptID, const char *pszSoeID)
{
	return GBS_SetSoeTripDesc(NULL, pszRptID, pszSoeID);
}

long lua_GBS_CalSoeError(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr)
{
	return GBS_CalSoeError(NULL, dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dAbsErr, dRelErr);
}

long lua_GBS_CalSoeError2(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr)
{
	return GBS_CalSoeError2(NULL, dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dErrRefStandVal, dAbsErr, dRelErr);
}



//Record
long lua_GBS_RcdSetProgID(const char* pszRcdProgID)
{
	return GBS_RcdSetProgID(NULL, pszRcdProgID);
}

long lua_GBS_RcdExit()
{
	return GBS_RcdExit(NULL);
}

long lua_GBS_RcdConfig(const char* pszPara)
{
	return GBS_RcdConfig(NULL, pszPara);
}

long lua_GBS_RcdSelect(const char* pszPara)
{
	return GBS_RcdSelect(NULL, pszPara);
}

long lua_GBS_RcdValidate(const char* pszRsltID)
{
	return GBS_RcdValidate(NULL, pszRsltID);
}

long lua_GBS_RcdCmpClear()
{
	return GBS_RcdCmpClear(NULL);
}

long lua_GBS_RcdCmpInit(const char* pszRcdFilePathRoot, long nCreateTestTimesDir)
{
	return GBS_RcdCmpInit(NULL, pszRcdFilePathRoot, nCreateTestTimesDir);
}

long lua_GBS_RcdCmp(const char* pszStdFile, const char* pszTestFile)
{
	return GBS_RcdCmp(NULL, pszStdFile, pszTestFile);
}

long lua_GBS_RcdCopyFile(const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir)
{
	return GBS_RcdCopyFile(NULL, pszSrcFile, pszDestFile, nCreateTestTimesDir);
}

long lua_GBS_RcdAnalyse(const char* pszRcdFile)
{
	return GBS_RcdAnalyse(NULL, pszRcdFile);
}

long lua_GBS_RcdSetPath(long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir)
{
	return GBS_RcdSetPath(NULL, nAppendItemPath, pszRcdFilePathRoot, nAppendTestTimeDir);
}


//重复测试相关
long lua_GBS_GetRepeatTimes(const char* pszItemPath)
{
	return GBS_GetRepeatTimes(NULL, pszItemPath);
}

long lua_GBS_GetRepeatSuccTimes(const char* pszItemPath)
{
	return GBS_GetRepeatSuccTimes(NULL, pszItemPath);
}


//
void lua_GBS_SetCmdZoneIndex(long nZoneIndex)
{
	return GBS_SetCmdZoneIndex(NULL, nZoneIndex);
}


//修正动作值的起始值和终止值
void lua_Gbs_ValidBeginEndValRange(const char *pBeginValID, const char *pEndValID, const char *pStepID, double dMinRange, double dMinStep, long nMinSteps, long nMaxSteps, long nUseNeg)
{
	return Gbs_ValidBeginEndValRange(NULL, pBeginValID, pEndValID, pStepID, dMinRange, dMinStep, nMinSteps, nMaxSteps, nUseNeg);
}


//时间出发函数
void lua_Gbs_SetTmTriggerSecond(long nSecond, long nOptr)
{
	return Gbs_SetTmTriggerSecond(NULL, nSecond, nOptr);
}

void lua_Gbs_SetTmTriggerCountMinute(long nMinute)
{
	return Gbs_SetTmTriggerCountMinute(NULL, nMinute);
}

void lua_Gbs_EnterTmTrigger()
{
	return Gbs_EnterTmTrigger(NULL);
}

void lua_Gbs_StartTimerTigger()
{
	return Gbs_StartTimerTigger(NULL);
}

void lua_Gbs_StopTimerTrigger()
{
	return Gbs_StopTimerTrigger(NULL);
}


//数据修约
double lua_Gbs_ValueRevised(double dValue, long nDots)
{
	return Gbs_ValueRevised(NULL, dValue, nDots);
}


//////////////////////////////////////////////////////////////////////////
//日志部分
long lua_Gbs_log_query_clear()
{
	return Gbs_log_query_clear(NULL);
}

long lua_Gbs_log_query_time(const char *pszBeginTine, const char *pszEndTime)
{
	return Gbs_log_query_time(NULL, pszBeginTine, pszEndTime);
}

long lua_Gbs_log_query_entryid(const char *pszEntryID)
{
	return Gbs_log_query_entryid(NULL, pszEntryID);
}

long lua_Gbs_log_query_logctrl(const char *pszLogCtrl)
{
	return Gbs_log_query_logctrl(NULL, pszLogCtrl);
}

long lua_Gbs_log_query_dataset(const char *pszDataset)
{
	return Gbs_log_query_dataset(NULL, pszDataset);
}


long lua_Gbs_log_query_data_clear()
{
	return Gbs_log_query_data_clear(NULL);
}

long lua_Gbs_log_query_data(const char *pszDataID)
{
	return Gbs_log_query_data(NULL, pszDataID);
}

long lua_Gbs_log_query_data_get_count()
{
	return Gbs_log_query_data_get_count(NULL);
}

long lua_Gbs_log_query_data_add_to_rpt()
{
	return Gbs_log_query_data_add_to_rpt(NULL);
}


long lua_Gbs_log_query(const char *pszScript)
{
	return Gbs_log_query(NULL, pszScript);
}


long lua_Gbs_log_get_count()
{
	return Gbs_log_get_count(NULL);
}

const char* lua_Gbs_log_get_attr(long nLogIndex, const char *pszAttr)
{
	return Gbs_log_get_attr(NULL, nLogIndex, pszAttr);
}

long lua_Gbs_log_get_data_count(long nLogIndex)
{
	return Gbs_log_get_data_count(NULL, nLogIndex);
}

const char* lua_Gbs_log_get_data_attr(long nLogIndex, long nDataIndex, const char *pszAttr)
{
	return Gbs_log_get_data_attr(NULL, nLogIndex, nDataIndex, pszAttr);
}

const char* lua_Gbs_log_get_data_attr2(long nLogIndex, const char *pszDataID, const char *pszAttr)
{
	return Gbs_log_get_data_attr2(NULL, nLogIndex, pszDataID, pszAttr);
}


//////////////////////////////////////////////////////////////////////////
//字符串处理
long lua_GBS_InitStrTok(const char *pszString, const char *pControl)
{
	return GBS_InitStrTok(NULL, pszString, pControl);
}

long lua_GBS_StrTokCount()
{
	return GBS_StrTokCount(NULL);
}

const char* lua_GBS_StrTokIndex(long nIndex)
{
	return GBS_StrTokIndex(NULL, nIndex);
}

const char* lua_GBS_StrTokNext()
{
	return GBS_StrTokNext(NULL);
}


//装置的全局参数
void lua_GBS_SetGlobal_Str(const char *pszID, const char *pszValue)
{
	return GBS_SetGlobal_Str(NULL, pszID, pszValue);
}


void lua_GBS_SetGlobal_Long(const char *pszID, long nValue)
{
	return GBS_SetGlobal_Long(NULL, pszID, nValue);
}

void lua_GBS_SetGlobal_Float(const char *pszID, float fValue)
{
	return GBS_SetGlobal_Float(NULL, pszID, fValue);
}


const char* lua_GBS_GetGlobal_Str(const char *pszID)
{
	return GBS_GetGlobal_Str(NULL, pszID);
}

long lua_GBS_GetGlobal_Long(const char *pszID)
{
	return GBS_GetGlobal_Long(NULL, pszID);
}

float lua_GBS_GetGlobal_Float(const char *pszID)
{
	return GBS_GetGlobal_Float(NULL, pszID);
}

long lua_GBS_GetGlobal_Long2(const CString &strID)
{
	return GBS_GetGlobal_Long2(NULL, strID);
}


void lua_GBS_Set_TestError(const char *pszTestError)
{
	return GBS_Set_TestError(NULL, pszTestError);
}


long lua_GBS_BinRslt(const char *pszParaID, const char *pszRsltID)
{
	return GBS_BinRslt(NULL, pszParaID, pszRsltID);
}

long lua_GBS_BinStateRslt(const char *pszParaID, const char *pszRsltID)
{
	return GBS_BinStateRslt(NULL, pszParaID, pszRsltID);
}

long lua_GBS_BinChngCntRslt(const char *pszBinChngData, const char *pszRsltID)
{
	return GBS_BinChngCntRslt(NULL, pszBinChngData, pszRsltID);
}

/*long lua_GBS_BinRsltEx()*///const char *pszParaDatas, const char *pszRsltDatas

//2019-1-6:增加数据对象是否合格的功能 lijq
void lua_GBS_Set_AddDataErrorValueToRpt(long nValue)
{
	return GBS_Set_AddDataErrorValueToRpt(NULL, nValue);
}

void lua_GBS_AddDataErrorToRpt(const char* pszDataID, long nValue)
{
	return GBS_AddDataErrorToRpt(NULL, pszDataID, nValue);
}


//2019-6-5 测试记录文件相关
const char* lua_GBS_GetTemplateFile(long nWithPath)
{
	return GBS_GetTemplateFile(NULL, nWithPath);
}

const char* lua_GBS_GetGbrptFile(long nWithPath)
{
	return GBS_GetGbrptFile(NULL, nWithPath);
}

void lua_GBS_SetGbrptFileName(const char *pszFileName)
{
	return GBS_SetGbrptFileName(NULL, pszFileName);
}


//2019-7-19 根据装置的编号，调整动作时间
void lua_GBS_OffsetTestDataByGbrptIndex(const char *pszDestDataID)
{
	return GBS_OffsetTestDataByGbrptIndex(NULL, pszDestDataID);
}


//2020-05-22 磐能版本比对功能 shaolei；
long lua_GBS_VersionInfoCompare (const char* pszPath, const char* pszFilePath)
{
	return GBS_VersionInfoCompare (NULL, pszPath, pszFilePath);
}


//GbScript_System/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 在调试监视信息中显示消息
// pszMsg：消息文本/消息ID
void lua_GBS_ShowMessage(const char* pszMsg)
{
	return GBS_ShowMessage(NULL, pszMsg);
}


// 播放音乐文件
// pszFile：音乐文件
// nTimes：播放次数		 0<=表示循环播放 	>0表示实际播放的次数
void lua_GBS_PlayMusicFile(const char* pszFileName, long nTimes)
{
	return GBS_PlayMusicFile(NULL, pszFileName, nTimes);
}


const char* lua_GBS_GetTime()
{
	return GBS_GetTime(NULL);
}


double lua_GBS_IEC(double dValue, double dTp, double dK, double dAlpha)
{
	return GBS_IEC(NULL, dValue, dTp, dK, dAlpha);
}

double lua_GBS_IEEE(double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2)
{
	return GBS_IEEE(NULL, dValue, dTp, dA, dB, dP, dQ, dK1, dK2);
}

double lua_GBS_IAC(double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta)
{
	return GBS_IAC(NULL, dValue, dTp, dA, dB, dC, dD, dE, dBeta);
}

double lua_GBS_I2T(double dValue, double dTp, double dA)
{
	return GBS_I2T(NULL, dValue, dTp, dA);
}


long lua_GBS_CmpDouble(const char *pszVal1, const char *pszVal2, const char *pszPrecision)
{
	return GBS_CmpDouble(NULL, pszVal1, pszVal2, pszPrecision);
}

long lua_GBS_CmpDoubleVal(double dVal1, double dVal2, double dPrecision)
{
	return GBS_CmpDoubleVal(NULL, dVal1, dVal2, dPrecision);
}

double lua_GBS_CalRelError(double dAbsErr, double dRefVal)
{
	return GBS_CalRelError(NULL, dAbsErr, dRefVal);
}


//外部程序接口部分(DLL调用)
//strPara格式：”Variable1=value1 Variable2=value2”
//dllReadDatas返回结果的格式相同
long lua_GBS_dllLoad(const char *pszDllFilePath, const char *pszDllID)
{
	return GBS_dllLoad(NULL, pszDllFilePath, pszDllID);
}

long lua_GBS_dllCall(const char *pszDllID, const char *pszPara)
{
	return GBS_dllCall(NULL, pszDllID, pszPara);
}

long lua_GBS_dllReadDatas(const char *pszDllID, const char *pszPara)
{
	return GBS_dllReadDatas(NULL, pszDllID, pszPara);
}

long lua_GBS_dllUnload(const char *pszDllID)
{
	return GBS_dllUnload(NULL, pszDllID);
}


//EXE调用
long lua_GBS_RunExe(const char *pszExeFile, const char *pszPara)
{
	return GBS_RunExe(NULL, pszExeFile, pszPara);
}

long lua_GBS_ExitExe(const char *pszExeFile)
{
	return GBS_ExitExe(NULL, pszExeFile);
}


void lua_GBS_AddLocalTime(long nHour, long nMinute, long nSecond)
{
	return GBS_AddLocalTime(NULL, nHour, nMinute, nSecond);
}

void lua_GBS_SubLocalTime(long nHour, long nMinute, long nSecond)
{
	return GBS_SubLocalTime(NULL, nHour, nMinute, nSecond);
}

long lua_GBS_RandLong(long nMin, long nMax)
{
	return GBS_RandLong(NULL, nMin, nMax);
}

float lua_GBS_RandFloat(float fMin, float fMax)
{
	return GBS_RandFloat(NULL, fMin, fMax);
}

double lua_GBS_RandDouble(double fMin, double fMax)
{
	return GBS_RandDouble(NULL, fMin, fMax);
}

void lua_GBS_RandSeed()
{
	return GBS_RandSeed(NULL);
}


//文件
const char* lua_GBS_GetFileNameFromPath(const char *pszPath)
{
	return GBS_GetFileNameFromPath(NULL, pszPath);
}

const char* lua_GBS_ParseFilePostfix(const char* pszFileName)
{
	return GBS_ParseFilePostfix(NULL, pszFileName);
}

const char* lua_GBS_ParseFileName(const char *pszFileName)
{
	return GBS_ParseFileName(NULL, pszFileName);
}


long lua_GBS_SubStrToLong(const char *pszString, long nBegin, long nLen)
{
	return GBS_SubStrToLong(NULL, pszString, nBegin, nLen);
}

const char* lua_GBS_SubStrToStr(const char *pszString, long nBegin, long nLen)
{
	return GBS_SubStrToStr(NULL, pszString, nBegin, nLen);
}

long lua_GBS_GetSecondsFromMidnight()
{
	return GBS_GetSecondsFromMidnight(NULL);
}


// void lua_GBS_LogTime_PcTime(PPCTIME pTm)
// void lua_GBS_LogTime_GpsTime(NULL, PGPSTIME pTm)

//GbScript_Engine////////////////////////////////////////////////////////////////////////////////////////////////
// 规约帧录波设置
void lua_GBS_RecordPackage(const char* pszPkgID)
{
	return GBS_RecordPackage(NULL, pszPkgID);
}

void lua_GBS_UnRecordPackage(const char* pszPkgID)
{
	return GBS_UnRecordPackage(NULL, pszPkgID);
}

void lua_GBS_GetPackagePcTime(const char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail)
{
	return GBS_GetPackagePcTime(NULL, pszPkgID, pszPcTimeID, nUseHeadOrTail);
}


// 读取标准源装置GPS时间与PC时间的之间对应关系
void lua_GBS_GetGpsPcTimeMap(const char *pszGpsTime, const char *pszPcTime)
{
	return GBS_GetGpsPcTimeMap(NULL, pszGpsTime, pszPcTime);
}


//读取输出开始时刻的标准源装置GPS时间
void lua_GBS_GetOutGpsTime(const char *pszGpsTimeID)
{
	return GBS_GetOutGpsTime(NULL, pszGpsTimeID);
}


//计算时间间隔
long lua_GBS_CalGpsPcTimeGap(const char *pszTimeID1, const char *pszTimerID2)
{
	return GBS_CalGpsPcTimeGap(NULL, pszTimeID1, pszTimerID2);
}

long lua_GBS_CalTimeGap(const char *pszTime1, const char *pszTimer2)
{
	return GBS_CalTimeGap(NULL, pszTime1, pszTimer2);
}

long lua_GBS_CalTimeGapCurr(const char *pszTime)
{
	return GBS_CalTimeGapCurr(NULL, pszTime);
}



//创建一个GPS的时间变量
long lua_GBS_CreateGpsDateTime(const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs)
{
	return GBS_CreateGpsDateTime(NULL, pszTimeID, nYear, nMonth, nDay, nHour, nMinute, nS, nMs, nUs);
}

long lua_GBS_CreateGpsTime(const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs)
{
	return GBS_CreateGpsTime(NULL, pszTimeID, nHour, nMinute, nS, nMs, nUs);
}


//读取标准源的结果数据
long lua_GBS_ReadMacroTestResult()
{
	return GBS_ReadMacroTestResult(NULL);
}


//重新下载电气量测试项目的参数
void lua_GBS_DownloadMacroTestPara()
{
	return GBS_DownloadMacroTestPara(NULL);
}


//通讯规约引擎接口函数
double lua_GBS_PpGetDeviceAttr(const char *pszAttrID)
{
	return GBS_PpGetDeviceAttr(NULL, pszAttrID);
}

long lua_GBS_PpGetDeviceAttrL(const char *pszAttrID)
{
	return GBS_PpGetDeviceAttrL(NULL, pszAttrID);
}

const char* lua_GBS_PpGetDeviceAttrStr(const char *pszAttrID)
{
	return GBS_PpGetDeviceAttrStr(NULL, pszAttrID);
}

void lua_GBS_PpSetDeviceAttrL(const char *pszAttrID, long nValue)
{
	return GBS_PpSetDeviceAttrL(NULL, pszAttrID, nValue);
}

void lua_GBS_PpSetDeviceAttrStr(const char *pszAttrID, const char *pszValue)
{
	return GBS_PpSetDeviceAttrStr(NULL, pszAttrID, pszValue);
}


long lua_GBS_PpRptGetDevieNodeDatas(const char *pszNodePath)
{
	return GBS_PpRptGetDevieNodeDatas(NULL, pszNodePath);
}

long lua_GBS_PpRptGetDeviceAttrs()
{
	return GBS_PpRptGetDeviceAttrs(NULL);
}

double lua_GBS_PpGetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID)
{
	return GBS_PpGetDevieNodeDataAttr(NULL, strDataPath, strAttrID);
}

// long lua_GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, const char *strValue
long lua_GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, double dValue)
{
	return GBS_PpSetDevieNodeDataAttr(NULL, strDataPath, strAttrID, dValue);
}

long lua_GBS_PpDeleteAllNodeData(const char *pszNodePath)
{
	return GBS_PpDeleteAllNodeData(NULL, pszNodePath);
}


long lua_GBS_PpCreateDevice(const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID)
{
	return GBS_PpCreateDevice(NULL, pszPpFile, pszDeviceFile, pszDeviceID);
}

long lua_GBS_PpReleaseDevice(const char *pszDeviceID)
{
	return GBS_PpReleaseDevice(NULL, pszDeviceID);
}

long lua_GBS_PpReleaseAllDevice()
{
	return GBS_PpReleaseAllDevice(NULL);
}

// long lua_GBS_PpRun(const char *pszDeviceID, const char *pszProcedureID, const char *pszPara
long lua_GBS_GetTestIndex()
{
	return GBS_GetTestIndex(NULL);
}


long lua_GBS_IsProtocol(const char *pszProtocol)
{
	return GBS_IsProtocol(NULL, pszProtocol);
}

void lua_GBS_SetComtradeDrawLineMode(const char *pszMode)
{
	GBS_SetComtradeDrawLineMode(NULL, pszMode);
}

//2021-2-21  lijunqing
void lua_GBS_RcdAnalysis(const char *pszRcdFile, const char *pszAnalysisFile)
{
	GBS_RcdAnalysis(NULL, pszRcdFile, pszAnalysisFile);
}

//2021-3-28  lijunqing  根据数据集创建安全措施的数据对象
void lua_GBS_CreateSafetyDatasByDvmDataset(const char *pszDvmDatasetPath, const char *pszAttrs
									   , const char *pszDataType, const char *pszDataFormat, const char *pszDefValue)
{
	GBS_CreateSafetyDatasByDvmDataset(NULL, pszDvmDatasetPath, pszAttrs
		, pszDataType, pszDataFormat, pszDefValue);
}

void lua_GBS_ImportSets()
{
	GBS_ImportSets(NULL);
}

void lua_GBS_Sleep(long nMs)
{
	GBS_Sleep(NULL, nMs);
}
//2021-11-12 shaolei 
void lua_GBS_SaveExportDatas(const char *pszDestFile, const char *pszDataConfig)
{
	GBS_SaveExportDatas(NULL, pszDestFile, pszDataConfig);
}

void lua_GBS_SetExportData(const char *pszName, const char *pszID, const char *pszDataType, const char *pszValue)
{
	//GBS_SetExportData(NULL, pszName, pszID, pszDataType, pszValue);
}

long lua_GBS_IsDsDataExist(const char* pszDataID)
{
	return GBS_IsDsDataExist(NULL, pszDataID);
}

void lua_GBS_GenSvMatchItems(const char* pszDataNameHas)
{
	GBS_GenSvMatchItems(NULL, pszDataNameHas);
}

void lua_GBS_SaveDvmToLocal(const char* pszFileName)
{
	GBS_SaveDvmToLocal(NULL, pszFileName);
}

void lua_GBS_ReadDvmFromLocal(const char* pszFileName)
{
	GBS_ReadDvmFromLocal(NULL, pszFileName);
}

//2023-4-17  lijunqing
void lua_GBS_IecfgAddCnnInfoToSft(const char* pszItemPath, const char* pszIecfgID)
{
	GBS_IecfgAddCnnInfoToSft(NULL,  pszItemPath, pszIecfgID);
}

void lua_GBS_GenTransPlayItems(const char* pszFilePath)
{
	GBS_GenTransPlayItems(NULL, pszFilePath);
}