#pragma once

#include "GbScript_GlobalDefine.h"


//////////////////////////////////////////////////////////////////////////
//项目及其相关参数处理
//////////////////////////////////////////////////////////////////////////

//跳转到项目
void GBS_GotoItem(const char* pszItemPath);
void GBS_GotoItemEx(const char* pszItemPath, long nRslt, long nAndOr);

void GBS_FireTestNextMsg();      //只针对试验中的通讯命令，目前只支持提示信息
void GBS_BreakLoop(long nLevel);

//命令消息
void GBS_MtExcuteCmd(const char *pszCmd, const char *pCmdPara);
void GBS_MtRegistPpDataMsg(const char *pszDvmDataPath);
void GBS_MtUnRegistPpDataMsg(const char *pszDvmDataPath);
void GBS_MtRegistPpDataMsgRange(const char *pszDvmDataPath, double dMin, double dMax);
void GBS_BreakItems(long nLevel);
void GBS_SetUploadRptFile(const char *pszFileName);

void GBS_MtRegistCmdMsg(const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam);
void GBS_MtUnRegistCmdMsg(const char *pszCmdID);

//数据集访问
double GBS_GetDsDataValue(const char* pszID);
double GBS_GetDsDataAttr(const char* pszID, const char *pszAttrID);
void GBS_SetDsDataValue(const char* pszID, double dVal);
const char* GBS_GetDsDataValueStr(const char* pszID);
void GBS_SetDsDataValueStr(const char* pszID, const char* pszVal);
double GBS_GetDsDataValueEx(long nDeviceIndex, const char* pszID);
void GBS_SetDsDataValueEx(long nDeviceIndex, const char* pszID, double dVal);
const char* GBS_GetDsDataValueStrEx(long nDeviceIndex, const char* pszID);
void GBS_SetDsDataValueStrEx(long nDeviceIndex, const char* pszID, const char* pszVal);
long GBS_CalAinError(const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinErrorEx(double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinErrorNom(double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr);
long GBS_CalAinStdError(double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinStdError2(const char *pszAinID, const char *pszAinBaseID,double dRefVal, double dAbsErr, double dRelErr);
long GBS_CalAinError2(const char *pszAinID, const char *pszAinBaseID, double dRate, double dAbsErr, double dRelErr);

double GBS_CalVariation(double dValue, double dTheoreticalVal, double dBaseValue, double dRate);
long GBS_CalVariationErr(double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr);
long GBS_CalVariationErrEx(const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate);

long GBS_FlterCalErrorMax(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);
long GBS_FlterCalErrorMin(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);

// 获取定值数据
// pszID：数据的ID
double GBS_GetSetValue(const char* pszID);
void GBS_SetSetValue(const char* pszID, double dVal);

double GBS_GetSoftswitchValue(const char* pszID);
void GBS_SetSoftswitchValue(const char* pszID, double dVal);

// 获取系统参数数据数据
// pszID：数据的ID
double GBS_GetSysParaValue(const char* pszID);

void GBS_SetSysParaValue(const char* pszID, double dValue);

// 获取测试参数数据
// pszID：数据的ID
double GBS_GetTestParaValue(const char* pszID);
const char* GBS_GetTestParaStr(const char* pszID);

// 设置测试参数数据
// pszID：数据的ID
void GBS_SetTestParaValue(const char* pszID, double dValue);
void GBS_SetTestParaStr(const char* pszID, const char *pszValue);

//设置满足条件的项目的Show属性
//pszItemPath为Item的路径
void GBS_SetItemShow(const char* pszItemPath, long nShow);

// 获取满足条件的项目的Show属性
// pszItemPath为Item的路径
long GBS_GetItemShow(const char* pszItemPath);

// 设置满足条件的项目的Enable属性
// pszItemPath为Item的路径
void GBS_SetItemEnable(const char* pszItemPath, long nEnable);

// 获取满足条件的项目的Enable属性
// pszItemPath为Item的路径
long GBS_GetItemEnable(const char* pszItemPath);

//Seelct
void GBS_SetItemSelect(const char* pszItemPath, long nSelect);
long GBS_GetItemSelect(const char* pszItemPath);

// 设置满足条件的项目的Name属性
// pszItemPath为Item的路径
void GBS_SetItemName(const char* pszItemPath, const char* pszName);

// 获取满足条件的项目的Name属性
// pszItemPath为Item的路径
const char* GBS_GetItemName(const char* pszItemPath);

// 设置满足条件的项目的结果判断
// pszItemPath为Item的路径
void GBS_SetItemResultJudge(const char* pszItemPath, long nResult);

long GBS_GetItemResultJudge(const char* pszItemPath);


// 设置满足条件的项目的数据的值
// pszItemPath为Item的路径
void GBS_SetItemParaValue(const char* pszItemPath, const char* pszValID, double dValue);
void GBS_SetItemParaValueStr(const char* pszItemPath, const char* pszValID, const char *pszValue);

double GBS_GetItemParaValue(const char* pszItemPath, const char* pszValID);
const char* GBS_GetItemParaString(const char* pszItemPath, const char* pszValID);
const char* GBS_GetItemTestTime(const char* pszItemPath);
const char* GBS_GetItemTestBeginTime(const char* pszItemPath);
const char* GBS_GetItemTestEndTime(const char* pszItemPath);

//通讯命令的参数脚本函数  2019-3-19
void GBS_ClearCommCmdParas(const char* pszItemPath);
void GBS_AddCommCmdParaValue(const char* pszItemPath, const char* pszValID, double dValue);
void GBS_AddCommCmdParaValue_Long(const char* pszItemPath, const char* pszValID, long nValue);
void GBS_AddCommCmdParaValue_String(const char* pszItemPath, const char* pszValID, const char *pszValue);

//////////////////////////////////////////////////////////////////////////
//常规报告数据处理,处理当前项目的报告数据
//////////////////////////////////////////////////////////////////////////
//多装置、数据库模式下，临时记录，通过添加RptDataMap保证数据不被清除
void GBS_AddRptMapData(const char* pszValID);

//设置报告数据
void GBS_SetItemReportValue(const char* pszItemPath, const char* pszValID, double dValue);
void GBS_SetItemReportValueString(const char* pszItemPath, const char* pszValID, const char* pszValString);

//获取报告数据，返回浮点数
double GBS_GetItemReportValue(const char* pszItemPath, const char* pszValID);
//获取报告数据，返回整数
long GBS_GetItemReportValueLong(const char* pszItemPath, const char* pszValID);
//获取报告数据，返回string
const char* GBS_GetItemReportValueString(const char* pszItemPath, const char* pszValID);

double GBS_GetItemReportValueEx(const char* pszItemPath, const char* pszValID, long nIndex);
long GBS_GetItemReportValueLongEx(const char* pszItemPath, const char* pszValID, long nIndex);
const char* GBS_GetItemReportValueStringEx(const char* pszItemPath, const char* pszValID, long nIndex);
long GBS_GetItemReportCount(const char* pszItemPath);
void GBS_ClearReports(const char* pszItemPath);
double GBS_CalRptValMax(const char* pszItemPath, const char* pszValID, double dDefVal);
double GBS_CalRptValMin(const char* pszItemPath, const char* pszValID, double dDefVal);
double GBS_CalRptValAvg(const char* pszItemPath, const char* pszValID, double dDefVal);

//获取满足条件的报告数据的个数，即根据数据ID和数据值
long GBS_LGetItemReportDataCount(const char* pszItemPath, const char *pszDataID, long nDataValue);

//////////////////////////////////////////////////////////////////////////
//扩展报告数据
//////////////////////////////////////////////////////////////////////////
//获取扩展报告数据的CReport->m_pRptDataEx
//nIndex：报告的数据索引
//pszValID：数据的值ID
double GBS_GetItemReportExValue(long nIndex, const char* pszValID);
double GBS_GetItemReportExValue_D(const char* pszDataID, const char* pszValID);
long   GBS_GetItemReportExValue_L(const char* pszDataID, const char* pszValID);
char*  GBS_GetItemReportExValue_S(const char* pszDataID, const char* pszValID);
char* GBS_GetFileInReportEx(const char *pszFilePostfix, long nFileIndex);
long GBS_GetFileNumInReportEx(const char *pszFilePostfix);

//获得报告对象的数据个数
long GBS_GetItemReportExCount();

//根据ID获得项目的报告的数据个数
long GBS_GetItemReportExDataCountByID(const char* pszDataAttrID);

//根据ID以及要获取此ID的第几个数据返回其在报告中对应的Index值；nIndex从0开始 
long GBS_GetItemReportDataIndexByIDIndex(const char* pszDataAttrID, long nIndex);

long GBS_CalTimeGapStr(const char* pszTime1, const char* pszTime2);
long GBS_CalTimeGapStr_us(const char* pszTime1, const char* pszTime2);
long GBS_CalItemReportTimeGap(long nItem1Index, long nItem2Index, const char* pszValID);
long GBS_CalItemReportTimeGapEx(long nItem1Index, long nItem2Index, const char* pszValID1, const char* pszValID2);
long GBS_CalItemReportTimeGapEx2(long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2);

//报告过滤
void GBS_FilterInit();
long GBS_FilterReportExEqualValueL(const char* pszDataAttrID, long nAttrValue);
long GBS_FilterReportExEqualValueStr(const char* pszDataAttrID, const char* pszValue);
long GBS_FilterReportExHasValueStr(const char* pszDataAttrID, const char* pszValue);
long GBS_FilterReportExHasNoValueStr(const char* pszDataAttrID, const char* pszValue);
void GBS_FilterCombineReportEx(const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator);

long GBS_FilterRptExQuery(const char* pszQuery);
long GBS_FilterRptExGetCount();
long GBS_FilterRptExGetLong(long nIndex, const char* pszDataAttrID);
char* GBS_FilterRptExGetString(long nIndex, const char* pszDataAttrID);
double GBS_FilterRptExGetDouble(long nIndex, const char* pszDataAttrID);

long GBS_FilterRptExGetValCount(long nDataIndex);
long GBS_FilterRptExGetValLong(long nDataIndex, const char* pszValIndex);
char* GBS_FilterRptExGetValString(long nDataIndex, const char* pszValIndex);
double GBS_FilterRptExGetValDouble(long nDataIndex, const char* pszValIndex);
long GBS_FilterRptExCalValError(long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr);
long GBS_FilterRptExCalValErrorEx(const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr);

double Gbs_FilterRptExQueryUseErr(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseErrEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseAvg(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);
double Gbs_FilterRptExQueryUseAvgEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);
long Gbs_FilterRptExQueryClearNotUse();

//########################################################################
//报告检索处理函数，处理检索出来的报告数据
//########################################################################
//扩展报告数据为CDvmDataset对象，数据为CDvmData对象
//CTag对象表示一个数据的值
//普通报告数据为CValues*对象，数据值为CValue对象
//所以，对普通报告数据的处理和扩展报告数据的处理方式不一样

//选择某个项目
long GBS_SSelectItem(const char *pszItemPath);

//普通报告处理函数******************************************************

//获得当前选择的项目的报告的个数
long GBS_SGetItemReportCount();

//选择项目的报告对象
long GBS_SSelectItemReport(long nReportIndex);

//获得项目的指定的报告的数据：浮点数
double GBS_SGetItemReportValue(const char* pszValID);

//获得项目的指定的报告的数据：整数
long GBS_SGetItemReportValueLong(const char* pszValID);

//获得项目的指定的报告的数据：字符串
const char* GBS_SGetItemReportValueString(const char* pszValID);

//获得项目的指定的报告的数据个数
long GBS_SGetItemReportValueCount();   

//获取报告的第nDataIndex数据的值
double GBS_SGetItemReportValue2(long nDataIndex);  
long GBS_SGetItemReportValueLong2(long nDataIndex);
const char* GBS_SGetItemReportValueString2(long nDataIndex);

//扩展报告处理函数******************************************************

//获得项目的指定的报告的数据个数
long GBS_SGetItemReportExDataCount();

//获得项目的指定的报告的数据：浮点数
double GBS_SGetItemReportExDataValue(long nDataIndex, const char* pszValID);

//获得项目的指定的报告的数据：整数
long GBS_SGetItemReportExDataValueLong(long nDataIndex, const char* pszValID);

//获得项目的指定的报告的数据：整数
const char* GBS_SGetItemReportExDataValueString(long nDataIndex, const char* pszValID);
// 
// //获得项目的指定的报告的数据：浮点数
// double GBS_SFindItemReportExDataValue(const char* pszValID);
// 
// //获得项目的指定的报告的数据：整数
// long GBS_SFindItemReportExDataValueLong(const char* pszValID);
// 
// //获得项目的指定的报告的数据：整数
// const char* GBS_SFindItemReportExDataValueString(const char* pszValID);

//数据集判断函数功能
//获得项目的指定的报告的数据个数
long GBS_RptExDsGetCount(const char* pszPath);

//获得项目的指定的报告的数据：浮点数
double GBS_RptExDsGetValueD(const char* pszPath, long nIndex);

//获得项目的指定的报告的数据：整数
long GBS_RptExDsGetValueL(const char* pszPath, long nIndex);

//获得项目的指定的报告的数据：整数
const char* GBS_RptExDsGetValueStr(const char* pszPath, long nIndex);

//数据验证
void GBS_RptExDsValidClear();
void GBS_RptExDsValidAddElement(const char* pszText, long nOption, long nUnbound);
void GBS_RptExDsValidAddElementChoice(const char* pszText, long nOption, long nUnbound);
long GBS_RptExDsValid(long nValidateHead);

long GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara);
long GBS_AdjustWord(long nPopDlg);

void GBS_CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2);
void GBS_CalSoeTimeEx(const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2);
void GBS_SetSoeTripDesc(const char *pszRptID, const char *pszSoeID);
long GBS_CalSoeError(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr);
long GBS_CalSoeError2(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr);


//Record
long GBS_RcdSetProgID(const char* pszRcdProgID);
long GBS_RcdExit();
long GBS_RcdConfig(const char* pszPara);
long GBS_RcdSelect(const char* pszPara);
long GBS_RcdValidate(const char* pszRsltID);
long GBS_RcdCmpClear();
long GBS_RcdCmpInit(const char* pszRcdFilePathRoot, long nCreateTestTimesDir);
long GBS_RcdCmp(const char* pszStdFile, const char* pszTestFile);
long GBS_RcdCopyFile(const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir);
long GBS_RcdAnalyse(const char* pszRcdFile);
long GBS_RcdSetPath(long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir);

//重复测试相关
long GBS_GetRepeatTimes(const char* pszItemPath);
long GBS_GetRepeatSuccTimes(const char* pszItemPath);

//
void GBS_SetCmdZoneIndex(long nZoneIndex);

//修正动作值的起始值和终止值
void Gbs_ValidBeginEndValRange(const char *pBeginValID, const char *pEndValID
							   , const char *pStepID, double dMinRange, double dMinStep
							   , long nMinSteps, long nMaxSteps, long nUseNeg);

//时间出发函数
void Gbs_SetTmTriggerSecond(long nSecond, long nOptr);
void Gbs_SetTmTriggerCountMinute(long nMinute);
void Gbs_EnterTmTrigger();
void Gbs_StartTimerTigger();
void Gbs_StopTimerTrigger();

//数据修约
double Gbs_ValueRevised(double dValue, long nDots);

//////////////////////////////////////////////////////////////////////////
//日志部分
long Gbs_log_query_clear();
long Gbs_log_query_time(const char *pszBeginTine, const char *pszEndTime);
long Gbs_log_query_entryid(const char *pszEntryID);
long Gbs_log_query_logctrl(const char *pszLogCtrl);
long Gbs_log_query_dataset(const char *pszDataset);

long Gbs_log_query_data_clear();
long Gbs_log_query_data(const char *pszDataID);
long Gbs_log_query_data_get_count();
long Gbs_log_query_data_add_to_rpt();

long Gbs_log_query(const char *pszScript);

long Gbs_log_get_count();
const char* Gbs_log_get_attr(long nLogIndex, const char *pszAttr);
long Gbs_log_get_data_count(long nLogIndex);
const char* Gbs_log_get_data_attr(long nLogIndex, long nDataIndex, const char *pszAttr);
const char* Gbs_log_get_data_attr2(long nLogIndex, const char *pszDataID, const char *pszAttr);

//////////////////////////////////////////////////////////////////////////
//字符串处理
long GBS_InitStrTok(const char *pszString, const char *pControl);
long GBS_StrTokCount();
const char* GBS_StrTokIndex(long nIndex);
const char* GBS_StrTokNext();

//装置的全局参数
void GBS_SetGlobal_Str(const char *pszID, const char *pszValue);
void GBS_SetGlobal_Long(const char *pszID, long nValue);
void GBS_SetGlobal_Float(const char *pszID, float fValue);

const char* GBS_GetGlobal_Str(const char *pszID);
long GBS_GetGlobal_Long(const char *pszID);
float GBS_GetGlobal_Float(const char *pszID);
long GBS_GetGlobal_Long2(const CString &strID);

void GBS_Set_TestError(const char *pszTestError);

long GBS_BinRslt(const char *pszParaID, const char *pszRsltID);
long GBS_BinStateRslt(const char *pszParaID, const char *pszRsltID);
long GBS_BinChngCntRslt(const char *pszBinChngData, const char *pszRsltID);
/*long GBS_BinRsltEx(const char *pszParaDatas, const char *pszRsltDatas);*/

//2019-1-6:增加数据对象是否合格的功能   lijq
void GBS_Set_AddDataErrorValueToRpt(long nValue);
void GBS_AddDataErrorToRpt(const char* pszDataID, long nValue);

//2019-6-5  测试记录文件相关
const char* GBS_GetTemplateFile(long nWithPath);
const char* GBS_GetGbrptFile(long nWithPath);
void GBS_SetGbrptFileName(const char *pszFileName);

//2019-7-19     根据装置的编号，调整动作时间
void GBS_OffsetTestDataByGbrptIndex(const char *pszDestDataID);

//2020-05-22   磐能版本比对功能  shaolei；
long GBS_VersionInfoCompare (const char* pszPath, const char* pszFilePath);

//2020-07-24  波形图绘制设置
void GBS_SetComtradeDrawLineMode(const char *pszMode);

