#pragma once

#include "GbScript_GlobalDefine.h"

#include "../../../../Module/XVM/TVMSingle.h"

//////////////////////////////////////////////////////////////////////////
//项目及其相关参数处理
//////////////////////////////////////////////////////////////////////////

//跳转到项目
void GBS_GotoItem(CTScriptSingleVM *pXvm, const char* pszItemPath);
void GBS_GotoItemEx(CTScriptSingleVM *pXvm, const char* pszItemPath, long nRslt, long nAndOr);

void GBS_FireTestNextMsg(CTScriptSingleVM *pXvm);      //只针对试验中的通讯命令，目前只支持提示信息
void GBS_BreakLoop(CTScriptSingleVM *pXvm, long nLevel);

//命令消息
void GBS_MtExcuteCmd(CTScriptSingleVM *pXvm, const char *pszCmd, const char *pCmdPara);
void GBS_MtRegistPpDataMsg(CTScriptSingleVM *pXvm, const char *pszDvmDataPath);
void GBS_MtUnRegistPpDataMsg(CTScriptSingleVM *pXvm, const char *pszDvmDataPath);
void GBS_MtRegistPpDataMsgRange(CTScriptSingleVM *pXvm, const char *pszDvmDataPath, double dMin, double dMax);
void GBS_BreakItems(CTScriptSingleVM *pXvm, long nLevel);
void GBS_SetUploadRptFile(CTScriptSingleVM *pXvm, const char *pszFileName);

void GBS_MtRegistCmdMsg(CTScriptSingleVM *pXvm, const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam);
void GBS_MtUnRegistCmdMsg(CTScriptSingleVM *pXvm, const char *pszCmdID);

//数据集访问
double GBS_GetDsDataValue(CTScriptSingleVM *pXvm, const char* pszID);
double GBS_GetDsDataAttr(CTScriptSingleVM *pXvm, const char* pszID, const char *pszAttrID);
const char* GBS_GetDsDataAttrStr(CTScriptSingleVM *pXvm, const char* pszID, const char *pszAttrID);  //shaolei  2024-2-26
void GBS_SetDsDataValue(CTScriptSingleVM *pXvm, const char* pszID, double dVal);
const char* GBS_GetDsDataValueStr(CTScriptSingleVM *pXvm, const char* pszID);
void GBS_SetDsDataValueStr(CTScriptSingleVM *pXvm, const char* pszID, const char* pszVal);
double GBS_GetDsDataValueEx(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID);
void GBS_SetDsDataValueEx(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID, double dVal);
const char* GBS_GetDsDataValueStrEx(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID);
void GBS_SetDsDataValueStrEx(CTScriptSingleVM *pXvm, long nDeviceIndex, const char* pszID, const char* pszVal);
long GBS_CalAinError(CTScriptSingleVM *pXvm, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinErrorEx(CTScriptSingleVM *pXvm, double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinErrorNom(CTScriptSingleVM *pXvm, double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr);
long GBS_CalAinStdError(CTScriptSingleVM *pXvm, double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinStdError2(CTScriptSingleVM *pXvm, const char *pszAinID, const char *pszAinBaseID,double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinError2(CTScriptSingleVM *pXvm, const char *pszAinID, const char *pszAinBaseID, double dRate, double dAbsErr, double dRelErr);

double GBS_CalVariation(CTScriptSingleVM *pXvm, double dValue, double dTheoreticalVal, double dBaseValue, double dRate);
long GBS_CalVariationErr(CTScriptSingleVM *pXvm, double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr);
long GBS_CalVariationErrEx(CTScriptSingleVM *pXvm, const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate);

long GBS_FlterCalErrorMax(CTScriptSingleVM *pXvm, const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_FlterCalErrorMin(CTScriptSingleVM *pXvm, const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);

// 获取定值数据
// pszID：数据的ID
double GBS_GetSetValue(CTScriptSingleVM *pXvm, const char* pszID);
void GBS_SetSetValue(CTScriptSingleVM *pXvm, const char* pszID, double dVal);

// double GBS_GetSoftswitchValue(CTScriptSingleVM *pXvm, const char* pszID);
// void GBS_SetSoftswitchValue(CTScriptSingleVM *pXvm, const char* pszID, double dVal);

// 获取系统参数数据数据
// pszID：数据的ID
double GBS_GetSysParaValue(CTScriptSingleVM *pXvm, const char* pszID);

void GBS_SetSysParaValue(CTScriptSingleVM *pXvm, const char* pszID, double dValue);

// 获取测试参数数据
// pszID：数据的ID
double GBS_GetTestParaValue(CTScriptSingleVM *pXvm, const char* pszID);
const char* GBS_GetTestParaStr(CTScriptSingleVM *pXvm, const char* pszID);

// 设置测试参数数据
// pszID：数据的ID
void GBS_SetTestParaValue(CTScriptSingleVM *pXvm, const char* pszID, double dValue);
void GBS_SetTestParaStr(CTScriptSingleVM *pXvm, const char* pszID, const char *pszValue);

//设置满足条件的项目的Show属性
//pszItemPath为Item的路径
void GBS_SetItemShow(CTScriptSingleVM *pXvm, const char* pszItemPath, long nShow);

// 获取满足条件的项目的Show属性
// pszItemPath为Item的路径
long GBS_GetItemShow(CTScriptSingleVM *pXvm, const char* pszItemPath);

// 设置满足条件的项目的Enable属性
// pszItemPath为Item的路径
void GBS_SetItemEnable(CTScriptSingleVM *pXvm, const char* pszItemPath, long nEnable);

// 获取满足条件的项目的Enable属性
// pszItemPath为Item的路径
long GBS_GetItemEnable(CTScriptSingleVM *pXvm, const char* pszItemPath);

//Seelct
void GBS_SetItemSelect(CTScriptSingleVM *pXvm, const char* pszItemPath, long nSelect);
long GBS_GetItemSelect(CTScriptSingleVM *pXvm, const char* pszItemPath);

// 设置满足条件的项目的Name属性
// pszItemPath为Item的路径
void GBS_SetItemName(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszName);

// 获取满足条件的项目的Name属性
// pszItemPath为Item的路径
const char* GBS_GetItemName(CTScriptSingleVM *pXvm, const char* pszItemPath);

// 设置满足条件的项目的结果判断
// pszItemPath为Item的路径
void GBS_SetItemResultJudge(CTScriptSingleVM *pXvm, const char* pszItemPath, long nResult);

long GBS_GetItemResultJudge(CTScriptSingleVM *pXvm, const char* pszItemPath);


// 设置满足条件的项目的数据的值
// pszItemPath为Item的路径
void GBS_SetItemParaValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dValue);
void GBS_SetItemParaValueStr(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, const char *pszValue);

double GBS_GetItemParaValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID);
const char* GBS_GetItemParaString(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID);
const char* GBS_GetItemTestTime(CTScriptSingleVM *pXvm, const char* pszItemPath);
const char* GBS_GetItemTestBeginTime(CTScriptSingleVM *pXvm, const char* pszItemPath);
const char* GBS_GetItemTestEndTime(CTScriptSingleVM *pXvm, const char* pszItemPath);

//通讯命令的参数脚本函数  2019-3-19
void GBS_ClearCommCmdParas(CTScriptSingleVM *pXvm, const char* pszItemPath);
void GBS_AddCommCmdParaValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dValue);
void GBS_AddCommCmdParaValue_Long(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, long nValue);
void GBS_AddCommCmdParaValue_String(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, const char *pszValue);

//////////////////////////////////////////////////////////////////////////
//常规报告数据处理,处理当前项目的报告数据
//////////////////////////////////////////////////////////////////////////
//多装置、数据库模式下，临时记录，通过添加RptDataMap保证数据不被清除
void GBS_AddRptMapData(CTScriptSingleVM *pXvm, const char* pszValID);

//设置报告数据
void GBS_SetItemReportValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dValue);
void GBS_SetItemReportValueString(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, const char* pszValString);

//获取报告数据，返回浮点数
double GBS_GetItemReportValue(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID);
//获取报告数据，返回整数
long GBS_GetItemReportValueLong(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID);
//获取报告数据，返回string
const char* GBS_GetItemReportValueString(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID);

double GBS_GetItemReportValueEx(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, long nIndex);
long GBS_GetItemReportValueLongEx(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, long nIndex);
const char* GBS_GetItemReportValueStringEx(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, long nIndex);
long GBS_GetItemReportCount(CTScriptSingleVM *pXvm, const char* pszItemPath);
void GBS_ClearReports(CTScriptSingleVM *pXvm, const char* pszItemPath);
double GBS_CalRptValMax(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dDefVal);
double GBS_CalRptValMin(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dDefVal);
double GBS_CalRptValAvg(CTScriptSingleVM *pXvm, const char* pszItemPath, const char* pszValID, double dDefVal);

//获取满足条件的报告数据的个数，即根据数据ID和数据值
long GBS_LGetItemReportDataCount(CTScriptSingleVM *pXvm, const char* pszItemPath, const char *pszDataID, long nDataValue);

//////////////////////////////////////////////////////////////////////////
//扩展报告数据
//////////////////////////////////////////////////////////////////////////
//获取扩展报告数据的CReport->m_pRptDataEx
//nIndex：报告的数据索引
//pszValID：数据的值ID
double GBS_GetItemReportExValue(CTScriptSingleVM *pXvm, long nIndex, const char* pszValID);
double GBS_GetItemReportExValue_D(CTScriptSingleVM *pXvm, const char* pszDataID, const char* pszValID);
long   GBS_GetItemReportExValue_L(CTScriptSingleVM *pXvm, const char* pszDataID, const char* pszValID);
char*  GBS_GetItemReportExValue_S(CTScriptSingleVM *pXvm, const char* pszDataID, const char* pszValID);
char* GBS_GetFileInReportEx(CTScriptSingleVM *pXvm, const char *pszFilePostfix, long nFileIndex);
long GBS_GetFileNumInReportEx(CTScriptSingleVM *pXvm, const char *pszFilePostfix);

//获得报告对象的数据个数
long GBS_GetItemReportExCount(CTScriptSingleVM *pXvm);

//根据ID获得项目的报告的数据个数
long GBS_GetItemReportExDataCountByID(CTScriptSingleVM *pXvm, const char* pszDataAttrID);

//根据ID以及要获取此ID的第几个数据返回其在报告中对应的Index值；nIndex从0开始 
long GBS_GetItemReportDataIndexByIDIndex(CTScriptSingleVM *pXvm, const char* pszDataAttrID, long nIndex);

long GBS_CalTimeGapStr(CTScriptSingleVM *pXvm, const char* pszTime1, const char* pszTime2);
long GBS_CalTimeGapStr_us(CTScriptSingleVM *pXvm, const char* pszTime1, const char* pszTime2);
long GBS_CalItemReportTimeGap(CTScriptSingleVM *pXvm, long nItem1Index, long nItem2Index, const char* pszValID);
long GBS_CalItemReportTimeGapEx(CTScriptSingleVM *pXvm, long nItem1Index, long nItem2Index, const char* pszValID1, const char* pszValID2);
long GBS_CalItemReportTimeGapEx2(CTScriptSingleVM *pXvm, long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2);

//报告过滤
void GBS_FilterInit(LPVOID);
long GBS_FilterReportExEqualValueL(CTScriptSingleVM *pXvm, const char* pszDataAttrID, long nAttrValue);
long GBS_FilterReportExEqualValueStr(CTScriptSingleVM *pXvm, const char* pszDataAttrID, const char* pszValue);
long GBS_FilterReportExHasValueStr(CTScriptSingleVM *pXvm, const char* pszDataAttrID, const char* pszValue);
long GBS_FilterReportExHasNoValueStr(CTScriptSingleVM *pXvm, const char* pszDataAttrID, const char* pszValue);
void GBS_FilterCombineReportEx(CTScriptSingleVM *pXvm, const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator);

long GBS_FilterRptExQuery(CTScriptSingleVM *pXvm, const char* pszQuery);
long GBS_FilterRptExGetCount(CTScriptSingleVM *pXvm);
long GBS_FilterRptExGetLong(CTScriptSingleVM *pXvm, long nIndex, const char* pszDataAttrID);
char* GBS_FilterRptExGetString(CTScriptSingleVM *pXvm, long nIndex, const char* pszDataAttrID);
double GBS_FilterRptExGetDouble(CTScriptSingleVM *pXvm, long nIndex, const char* pszDataAttrID);

long GBS_FilterRptExGetValCount(CTScriptSingleVM *pXvm, long nDataIndex);
long GBS_FilterRptExGetValLong(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex);
char* GBS_FilterRptExGetValString(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex);
double GBS_FilterRptExGetValDouble(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex);
long GBS_FilterRptExCalValError(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr);
long GBS_FilterRptExCalValErrorEx(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr);

double Gbs_FilterRptExQueryUseErr(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseErrEx(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseAvg(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseAvgEx(CTScriptSingleVM *pXvm, const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);
long Gbs_FilterRptExQueryClearNotUse(CTScriptSingleVM *pXvm);

//########################################################################
//报告检索处理函数，处理检索出来的报告数据
//########################################################################
//扩展报告数据为CDvmDataset对象，数据为CDvmData对象
//CTag对象表示一个数据的值
//普通报告数据为CValues*对象，数据值为CValue对象
//所以，对普通报告数据的处理和扩展报告数据的处理方式不一样

//选择某个项目
long GBS_SSelectItem(CTScriptSingleVM *pXvm, const char *pszItemPath);

//普通报告处理函数******************************************************

//获得当前选择的项目的报告的个数
long GBS_SGetItemReportCount(CTScriptSingleVM *pXvm);

//选择项目的报告对象
long GBS_SSelectItemReport(CTScriptSingleVM *pXvm, long nReportIndex);

//获得项目的指定的报告的数据：浮点数
double GBS_SGetItemReportValue(CTScriptSingleVM *pXvm, const char* pszValID);

//获得项目的指定的报告的数据：整数
long GBS_SGetItemReportValueLong(CTScriptSingleVM *pXvm, const char* pszValID);

//获得项目的指定的报告的数据：字符串
const char* GBS_SGetItemReportValueString(CTScriptSingleVM *pXvm, const char* pszValID);

//获得项目的指定的报告的数据个数
long GBS_SGetItemReportValueCount(CTScriptSingleVM *pXvm);   

//获取报告的第nDataIndex数据的值
double GBS_SGetItemReportValue2(CTScriptSingleVM *pXvm, long nDataIndex);  
long GBS_SGetItemReportValueLong2(CTScriptSingleVM *pXvm, long nDataIndex);
const char* GBS_SGetItemReportValueString2(CTScriptSingleVM *pXvm, long nDataIndex);

//扩展报告处理函数******************************************************

//获得项目的指定的报告的数据个数
long GBS_SGetItemReportExDataCount(CTScriptSingleVM *pXvm);

//获得项目的指定的报告的数据：浮点数
double GBS_SGetItemReportExDataValue(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValID);

//获得项目的指定的报告的数据：整数
long GBS_SGetItemReportExDataValueLong(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValID);

//获得项目的指定的报告的数据：整数
const char* GBS_SGetItemReportExDataValueString(CTScriptSingleVM *pXvm, long nDataIndex, const char* pszValID);
// 
// //获得项目的指定的报告的数据：浮点数
// double GBS_SFindItemReportExDataValue(CTScriptSingleVM *pXvm, const char* pszValID);
// 
// //获得项目的指定的报告的数据：整数
// long GBS_SFindItemReportExDataValueLong(CTScriptSingleVM *pXvm, const char* pszValID);
// 
// //获得项目的指定的报告的数据：整数
// const char* GBS_SFindItemReportExDataValueString(CTScriptSingleVM *pXvm, const char* pszValID);

//数据集判断函数功能
//获得项目的指定的报告的数据个数
long GBS_RptExDsGetCount(CTScriptSingleVM *pXvm, const char* pszPath);

//获得项目的指定的报告的数据：浮点数
double GBS_RptExDsGetValueD(CTScriptSingleVM *pXvm, const char* pszPath, long nIndex);

//获得项目的指定的报告的数据：整数
long GBS_RptExDsGetValueL(CTScriptSingleVM *pXvm, const char* pszPath, long nIndex);

//获得项目的指定的报告的数据：整数
const char* GBS_RptExDsGetValueStr(CTScriptSingleVM *pXvm, const char* pszPath, long nIndex);

//数据验证
void GBS_RptExDsValidClear(CTScriptSingleVM *pXvm);
void GBS_RptExDsValidAddElement(CTScriptSingleVM *pXvm, const char* pszText, long nOption, long nUnbound);
void GBS_RptExDsValidAddElementChoice(CTScriptSingleVM *pXvm, const char* pszText, long nOption, long nUnbound);
long GBS_RptExDsValid(CTScriptSingleVM *pXvm, long nValidateHead);

long GBS_RecordCmd(CTScriptSingleVM *pXvm, const char *pszCmdID, const char *pszCmdPara);
long GBS_AdjustWord(CTScriptSingleVM *pXvm, long nPopDlg);

void GBS_CalSoeTime(CTScriptSingleVM *pXvm, const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2);
void GBS_CalSoeTimeEx(CTScriptSingleVM *pXvm, const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2);
void GBS_SetSoeTripDesc(CTScriptSingleVM *pXvm, const char *pszRptID, const char *pszSoeID);
long GBS_CalSoeError(CTScriptSingleVM *pXvm, double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr);
long GBS_CalSoeError2(CTScriptSingleVM *pXvm, double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr);


//Record
long GBS_RcdSetProgID(CTScriptSingleVM *pXvm, const char* pszRcdProgID);
long GBS_RcdExit(CTScriptSingleVM *pXvm);
long GBS_RcdConfig(CTScriptSingleVM *pXvm, const char* pszPara);
long GBS_RcdSelect(CTScriptSingleVM *pXvm, const char* pszPara);
long GBS_RcdValidate(CTScriptSingleVM *pXvm, const char* pszRsltID);
long GBS_RcdCmpClear(CTScriptSingleVM *pXvm);
long GBS_RcdCmpInit(CTScriptSingleVM *pXvm, const char* pszRcdFilePathRoot, long nCreateTestTimesDir);
long GBS_RcdCmp(CTScriptSingleVM *pXvm, const char* pszStdFile, const char* pszTestFile);
long GBS_RcdCopyFile(CTScriptSingleVM *pXvm, const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir);
long GBS_RcdAnalyse(CTScriptSingleVM *pXvm, const char* pszRcdFile);
long GBS_RcdSetPath(CTScriptSingleVM *pXvm, long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir);

//重复测试相关
long GBS_GetRepeatTimes(CTScriptSingleVM *pXvm, const char* pszItemPath);
long GBS_GetRepeatSuccTimes(CTScriptSingleVM *pXvm, const char* pszItemPath);

//
void GBS_SetCmdZoneIndex(CTScriptSingleVM *pXvm, long nZoneIndex);

//修正动作值的起始值和终止值
void Gbs_ValidBeginEndValRange(CTScriptSingleVM *pXvm, const char *pBeginValID, const char *pEndValID
							   , const char *pStepID, double dMinRange, double dMinStep
							   , long nMinSteps, long nMaxSteps, long nUseNeg);

//时间出发函数
void Gbs_SetTmTriggerSecond(CTScriptSingleVM *pXvm, long nSecond, long nOptr);
void Gbs_SetTmTriggerCountMinute(CTScriptSingleVM *pXvm, long nMinute);
void Gbs_EnterTmTrigger(CTScriptSingleVM *pXvm);
void Gbs_StartTimerTigger(CTScriptSingleVM *pXvm);
void Gbs_StopTimerTrigger(CTScriptSingleVM *pXvm);

//数据修约
double Gbs_ValueRevised(CTScriptSingleVM *pXvm, double dValue, long nDots);

//////////////////////////////////////////////////////////////////////////
//日志部分
long Gbs_log_query_clear(CTScriptSingleVM *pXvm);
long Gbs_log_query_time(CTScriptSingleVM *pXvm, const char *pszBeginTine, const char *pszEndTime);
long Gbs_log_query_entryid(CTScriptSingleVM *pXvm, const char *pszEntryID);
long Gbs_log_query_logctrl(CTScriptSingleVM *pXvm, const char *pszLogCtrl);
long Gbs_log_query_dataset(CTScriptSingleVM *pXvm, const char *pszDataset);

long Gbs_log_query_data_clear(CTScriptSingleVM *pXvm);
long Gbs_log_query_data(CTScriptSingleVM *pXvm, const char *pszDataID);
long Gbs_log_query_data_get_count(CTScriptSingleVM *pXvm);
long Gbs_log_query_data_add_to_rpt(CTScriptSingleVM *pXvm);

long Gbs_log_query(CTScriptSingleVM *pXvm, const char *pszScript);

long Gbs_log_get_count(CTScriptSingleVM *pXvm);
const char* Gbs_log_get_attr(CTScriptSingleVM *pXvm, long nLogIndex, const char *pszAttr);
long Gbs_log_get_data_count(CTScriptSingleVM *pXvm, long nLogIndex);
const char* Gbs_log_get_data_attr(CTScriptSingleVM *pXvm, long nLogIndex, long nDataIndex, const char *pszAttr);
const char* Gbs_log_get_data_attr2(CTScriptSingleVM *pXvm, long nLogIndex, const char *pszDataID, const char *pszAttr);

//////////////////////////////////////////////////////////////////////////
//字符串处理
long GBS_InitStrTok(CTScriptSingleVM *pXvm, const char *pszString, const char *pControl);
long GBS_StrTokCount(CTScriptSingleVM *pXvm);
const char* GBS_StrTokIndex(CTScriptSingleVM *pXvm, long nIndex);
const char* GBS_StrTokNext(CTScriptSingleVM *pXvm);

//装置的全局参数
void GBS_SetGlobal_Str(CTScriptSingleVM *pXvm, const char *pszID, const char *pszValue);
void GBS_SetGlobal_Long(CTScriptSingleVM *pXvm, const char *pszID, long nValue);
void GBS_SetGlobal_Float(CTScriptSingleVM *pXvm, const char *pszID, float fValue);

const char* GBS_GetGlobal_Str(CTScriptSingleVM *pXvm, const char *pszID);
long GBS_GetGlobal_Long(CTScriptSingleVM *pXvm, const char *pszID);
float GBS_GetGlobal_Float(CTScriptSingleVM *pXvm, const char *pszID);
long GBS_GetGlobal_Long2(CTScriptSingleVM *pXvm, const CString &strID);

void GBS_Set_TestError(CTScriptSingleVM *pXvm, const char *pszTestError);

long GBS_BinRslt(CTScriptSingleVM *pXvm, const char *pszParaID, const char *pszRsltID);
long GBS_BinStateRslt(CTScriptSingleVM *pXvm, const char *pszParaID, const char *pszRsltID);
long GBS_BinChngCntRslt(CTScriptSingleVM *pXvm, const char *pszBinChngData, const char *pszRsltID);
/*long GBS_BinRsltEx(CTScriptSingleVM *pXvm, const char *pszParaDatas, const char *pszRsltDatas);*/

//2019-1-6:增加数据对象是否合格的功能   lijq
void GBS_Set_AddDataErrorValueToRpt(CTScriptSingleVM *pXvm, long nValue);
void GBS_AddDataErrorToRpt(CTScriptSingleVM *pXvm, const char* pszDataID, long nValue);

//2019-6-5  测试记录文件相关
const char* GBS_GetTemplateFile(CTScriptSingleVM *pXvm, long nWithPath);
const char* GBS_GetGbrptFile(CTScriptSingleVM *pXvm, long nWithPath);
void GBS_SetGbrptFileName(CTScriptSingleVM *pXvm, const char *pszFileName);

//2019-7-19     根据装置的编号，调整动作时间
void GBS_OffsetTestDataByGbrptIndex(CTScriptSingleVM *pXvm, const char *pszDestDataID);

//2020-05-22   磐能版本比对功能  shaolei；
long GBS_VersionInfoCompare (CTScriptSingleVM *pXvm, const char* pszPath, const char* pszFilePath);

//2020-07-24  波形图绘制设置
void GBS_SetComtradeDrawLineMode(CTScriptSingleVM *pXvm, const char *pszMode);

//2021-2-21  lijunqing
void GBS_RcdAnalysis(CTScriptSingleVM *pXvm, const char *pszRcdFile, const char *pszAnalysisFile);

//2021-3-28  lijunqing  根据数据集创建安全措施的数据对象
void GBS_CreateSafetyDatasByDvmDataset(CTScriptSingleVM *pXvm, const char *pszDvmDatasetPath, const char *pszAttrs
									   , const char *pszDataType, const char *pszDataFormat, const char *pszDefValue);

//2021-5-23 lijunqing  
void GBS_ImportSets(CTScriptSingleVM *pXvm);

void GBS_Sleep(CTScriptSingleVM *pXvm, long nMs);//2021-11-12 shaolei
void GBS_SaveExportDatas(CTScriptSingleVM *pXvm, const char *pszDestFile, const char *pszDataConfig);
void GBS_SetExportData(CTScriptSingleVM *pXvm, const char *pszName, const char *pszID, const char *pszDataType, const char *pszValue);
long GBS_IsDsDataExist(CTScriptSingleVM *pXvm, const char* pszDataID);
void GBS_GenSvMatchItems(CTScriptSingleVM *pXvm, const char* pszDataNameHas);
void GBS_SaveDvmToLocal(CTScriptSingleVM *pXvm, const char* pszFileName);
void GBS_ReadDvmFromLocal(CTScriptSingleVM *pXvm, const char* pszFileName);

void GBS_IecfgAddCnnInfoToSft(CTScriptSingleVM *pSingleVm, const char* pszItemPath, const char* pszIecfgID);

void GBS_GenTransPlayItems(CTScriptSingleVM *pXvm, const char* pszFilePath);
