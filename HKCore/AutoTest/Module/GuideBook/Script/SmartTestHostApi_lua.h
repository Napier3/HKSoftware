//SmartTestHostApi.h
#ifndef _SmartTestHostApi_lua_h__
#define _SmartTestHostApi_lua_h__

#include "../../../../Module/GpsPcTime/GpsPcTime.h"
#include "../../TestControl/TestControl.h"

//GbScript_GuideBook/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//跳转到项目
void lua_GBS_GotoItem(const char* pszItemPath);  //
void lua_GBS_GotoItemEx(const char* pszItemPath, long nRslt, long nAndOr);  //

void lua_GBS_FireTestNextMsg();      //只针对试验中的通讯命令，目前只支持提示信息
void lua_GBS_BreakLoop(long nLevel);  //

//命令消息
void lua_GBS_MtExcuteCmd(const char *pszCmd, const char *pCmdPara);  //
void lua_GBS_MtRegistPpDataMsg(const char *pszDvmDataPath);  //
void lua_GBS_MtUnRegistPpDataMsg(const char *pszDvmDataPath);  //
void lua_GBS_MtRegistPpDataMsgRange(const char *pszDvmDataPath, double dMin, double dMax);  //
void lua_GBS_BreakItems(long nLevel);  //
void lua_GBS_SetUploadRptFile(const char *pszFileName);  //

void lua_GBS_MtRegistCmdMsg(const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam);  //
void lua_GBS_MtUnRegistCmdMsg(const char *pszCmdID);  //

//数据集访问
double lua_GBS_GetDsDataValue(const char* pszID);  //
double lua_GBS_GetDsDataAttr(const char* pszID, const char *pszAttrID);  //
const char* lua_GBS_GetDsDataAttrStr(const char* pszID, const char *pszAttrID);  //2024-2-26 shaolei
void lua_GBS_SetDsDataValue(const char* pszID, double dVal);  //
const char* lua_GBS_GetDsDataValueStr(const char* pszID);  //
void lua_GBS_SetDsDataValueStr(const char* pszID, const char* pszVal);  //
double lua_GBS_GetDsDataValueEx(long nDeviceIndex, const char* pszID);  //
void lua_GBS_SetDsDataValueEx(long nDeviceIndex, const char* pszID, double dVal);  //
const char* lua_GBS_GetDsDataValueStrEx(long nDeviceIndex, const char* pszID);  //
void lua_GBS_SetDsDataValueStrEx(long nDeviceIndex, const char* pszID, const char* pszVal);  //
long lua_GBS_CalAinError(const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);  //
long lua_GBS_CalAinErrorEx(double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr);  //
long lua_GBS_CalAinErrorNom(double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr);  //
long lua_GBS_CalAinStdError(double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr);  //
long lua_GBS_CalAinStdError2(const char *pszAinID, const char *pszAinBaseID,double dRefVal, double dAbsErr, double dRelErr);  //
long lua_GBS_CalAinError2(const char *pszAinID, const char *pszAinBaseID, double dRate, double dAbsErr, double dRelErr);  //

double lua_GBS_CalVariation(double dValue, double dTheoreticalVal, double dBaseValue, double dRate);  //
long lua_GBS_CalVariationErr(double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr);  //
long lua_GBS_CalVariationErrEx(const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate);  //

long lua_GBS_FlterCalErrorMax(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);  //
long lua_GBS_FlterCalErrorMin(const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr);  //

// 获取定值数据
// pszID：数据的ID
double lua_GBS_GetSetValue(const char* pszID);  //
void lua_GBS_SetSetValue(const char* pszID, double dVal);  //

//void lua_GBS_GetSoftswitchValue(const char* pszID
// void lua_GBS_SetSoftswitchValue(const char* pszID, double dVal

// 获取系统参数数据数据
// pszID：数据的ID
double lua_GBS_GetSysParaValue(const char* pszID);  //

void lua_GBS_SetSysParaValue(const char* pszID, double dValue);  //

// 获取测试参数数据
// pszID：数据的ID
double lua_GBS_GetTestParaValue(const char* pszID);  //
const char* lua_GBS_GetTestParaStr(const char* pszID);  //

// 设置测试参数数据
// pszID：数据的ID
void lua_GBS_SetTestParaValue(const char* pszID, double dValue);  //
void lua_GBS_SetTestParaStr(const char* pszID, const char *pszValue);  //

//设置满足条件的项目的Show属性
//pszItemPath为Item的路径
void lua_GBS_SetItemShow(const char* pszItemPath, long nShow);

// 获取满足条件的项目的Show属性
// pszItemPath为Item的路径
long lua_GBS_GetItemShow(const char* pszItemPath);

// 设置满足条件的项目的Enable属性
// pszItemPath为Item的路径
void lua_GBS_SetItemEnable(const char* pszItemPath, long nEnable);

// 获取满足条件的项目的Enable属性
// pszItemPath为Item的路径
long lua_GBS_GetItemEnable(const char* pszItemPath);


//Seelct
void lua_GBS_SetItemSelect(const char* pszItemPath, long nSelect);  //
long lua_GBS_GetItemSelect(const char* pszItemPath);  //

// 设置满足条件的项目的Name属性
// pszItemPath为Item的路径
void lua_GBS_SetItemName(const char* pszItemPath, const char* pszName);  //

// 获取满足条件的项目的Name属性
// pszItemPath为Item的路径
const char* lua_GBS_GetItemName(const char* pszItemPath);  //

// 设置满足条件的项目的结果判断
// pszItemPath为Item的路径
void lua_GBS_SetItemResultJudge(const char* pszItemPath, long nResult);  //

long lua_GBS_GetItemResultJudge(const char* pszItemPath);  //


// 设置满足条件的项目的数据的值
// pszItemPath为Item的路径
void lua_GBS_SetItemParaValue(const char* pszItemPath, const char* pszValID, double dValue);  //
void lua_GBS_SetItemParaValueStr(const char* pszItemPath, const char* pszValID, const char *pszValue);  //

double lua_GBS_GetItemParaValue(const char* pszItemPath, const char* pszValID);  //
const char* lua_GBS_GetItemParaString(const char* pszItemPath, const char* pszValID);  //
const char* lua_GBS_GetItemTestTime(const char* pszItemPath);  //
const char* lua_GBS_GetItemTestBeginTime(const char* pszItemPath);  //
const char* lua_GBS_GetItemTestEndTime(const char* pszItemPath);  //

//通讯命令的参数脚本函数  2019-3-19
void lua_GBS_ClearCommCmdParas(const char* pszItemPath);  //
void lua_GBS_AddCommCmdParaValue(const char* pszItemPath, const char* pszValID, double dValue);  //
void lua_GBS_AddCommCmdParaValue_Long(const char* pszItemPath, const char* pszValID, long nValue);  //
void lua_GBS_AddCommCmdParaValue_String(const char* pszItemPath, const char* pszValID, const char *pszValue);  //

//////////////////////////////////////////////////////////////////////////
//常规报告数据处理,处理当前项目的报告数据
//////////////////////////////////////////////////////////////////////////
//多装置、数据库模式下，临时记录，通过添加RptDataMap保证数据不被清除
void lua_GBS_AddRptMapData(const char* pszValID);  //

//设置报告数据
void lua_GBS_SetItemReportValue(const char* pszItemPath, const char* pszValID, double dValue);  //
void lua_GBS_SetItemReportValueString(const char* pszItemPath, const char* pszValID, const char* pszValString);  //

//获取报告数据，返回浮点数
double lua_GBS_GetItemReportValue(const char* pszItemPath, const char* pszValID);  //
//获取报告数据，返回整数
long lua_GBS_GetItemReportValueLong(const char* pszItemPath, const char* pszValID);  //
//获取报告数据，返回string
const char* lua_GBS_GetItemReportValueString(const char* pszItemPath, const char* pszValID);  //

double lua_GBS_GetItemReportValueEx(const char* pszItemPath, const char* pszValID, long nIndex);  //
long lua_GBS_GetItemReportValueLongEx(const char* pszItemPath, const char* pszValID, long nIndex);  //
const char* lua_GBS_GetItemReportValueStringEx(const char* pszItemPath, const char* pszValID, long nIndex);  //
long lua_GBS_GetItemReportCount(const char* pszItemPath);  //
void lua_GBS_ClearReports(const char* pszItemPath);  //
double lua_GBS_CalRptValMax(const char* pszItemPath, const char* pszValID, double dDefVal);  //
double lua_GBS_CalRptValMin(const char* pszItemPath, const char* pszValID, double dDefVal);  //
double lua_GBS_CalRptValAvg(const char* pszItemPath, const char* pszValID, double dDefVal);  //

//获取满足条件的报告数据的个数，即根据数据ID和数据值
long lua_GBS_LGetItemReportDataCount(const char* pszItemPath, const char *pszDataID, long nDataValue);  //

//////////////////////////////////////////////////////////////////////////
//扩展报告数据
//////////////////////////////////////////////////////////////////////////
//获取扩展报告数据的CReport->m_pRptDataEx
//nIndex：报告的数据索引
//pszValID：数据的值ID
double lua_GBS_GetItemReportExValue(long nIndex, const char* pszValID);  //
double lua_GBS_GetItemReportExValue_D(const char* pszDataID, const char* pszValID);  //
long   lua_GBS_GetItemReportExValue_L(const char* pszDataID, const char* pszValID);  //
char*  lua_GBS_GetItemReportExValue_S(const char* pszDataID, const char* pszValID);  //
const char* lua_GBS_GetFileInReportEx(const char *pszFilePostfix, long nFileIndex);  //
long lua_GBS_GetFileNumInReportEx(const char *pszFilePostfix);  //

//获得报告对象的数据个数
long lua_GBS_GetItemReportExCount();

//根据ID获得项目的报告的数据个数
long lua_GBS_GetItemReportExDataCountByID(const char* pszDataAttrID);  //

//根据ID以及要获取此ID的第几个数据返回其在报告中对应的Index值；nIndex从0开始 
long lua_GBS_GetItemReportDataIndexByIDIndex(const char* pszDataAttrID, long nIndex);  //

long lua_GBS_CalTimeGapStr(const char* pszTime1, const char* pszTime2);  //
long lua_GBS_CalTimeGapStr_us(const char* pszTime1, const char* pszTime2);  //
long lua_GBS_CalItemReportTimeGap(long nItem1Index, long nItem2Index, const char* pszValID);  //
long lua_GBS_CalItemReportTimeGapEx(long nItem1Index, long nItem2Index, const char* pszValID1, const char* pszValID2);  //
long lua_GBS_CalItemReportTimeGapEx2(long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2);  //

//报告过滤
void lua_GBS_FilterInit();
long lua_GBS_FilterReportExEqualValueL(const char* pszDataAttrID, long nAttrValue);  //
long lua_GBS_FilterReportExEqualValueStr(const char* pszDataAttrID, const char* pszValue);  //
long lua_GBS_FilterReportExHasValueStr(const char* pszDataAttrID, const char* pszValue);  //
long lua_GBS_FilterReportExHasNoValueStr(const char* pszDataAttrID, const char* pszValue);  //
void lua_GBS_FilterCombineReportEx(const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator);  //

long lua_GBS_FilterRptExQuery(const char* pszQuery);  //
long lua_GBS_FilterRptExGetCount();
long lua_GBS_FilterRptExGetLong(long nIndex, const char* pszDataAttrID);  //
const char* lua_GBS_FilterRptExGetString(long nIndex, const char* pszDataAttrID);  //
double lua_GBS_FilterRptExGetDouble(long nIndex, const char* pszDataAttrID);  //

long lua_GBS_FilterRptExGetValCount(long nDataIndex);  //
long lua_GBS_FilterRptExGetValLong(long nDataIndex, const char* pszValIndex);  //
char* lua_GBS_FilterRptExGetValString(long nDataIndex, const char* pszValIndex);  //
double lua_GBS_FilterRptExGetValDouble(long nDataIndex, const char* pszValIndex);  //
long lua_GBS_FilterRptExCalValError(long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr);  //
long lua_GBS_FilterRptExCalValErrorEx(const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr);  //

double lua_Gbs_FilterRptExQueryUseErr(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);  //
double lua_Gbs_FilterRptExQueryUseErrEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);  //
double lua_Gbs_FilterRptExQueryUseAvg(const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs);  //
double lua_Gbs_FilterRptExQueryUseAvgEx(const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs);  //
long lua_Gbs_FilterRptExQueryClearNotUse();

//########################################################################
//报告检索处理函数，处理检索出来的报告数据
//########################################################################
//扩展报告数据为CDvmDataset对象，数据为CDvmData对象
//CTag对象表示一个数据的值
//普通报告数据为CValues*对象，数据值为CValue对象
//所以，对普通报告数据的处理和扩展报告数据的处理方式不一样

//选择某个项目
long lua_GBS_SSelectItem(const char *pszItemPath);  //

//普通报告处理函数******************************************************

//获得当前选择的项目的报告的个数
long lua_GBS_SGetItemReportCount();

//选择项目的报告对象
long lua_GBS_SSelectItemReport(long nReportIndex);  //

//获得项目的指定的报告的数据：浮点数
double lua_GBS_SGetItemReportValue(const char* pszValID);  //

//获得项目的指定的报告的数据：整数
long lua_GBS_SGetItemReportValueLong(const char* pszValID);  //

//获得项目的指定的报告的数据：字符串
const char* lua_GBS_SGetItemReportValueString(const char* pszValID);  //

//获得项目的指定的报告的数据个数
long lua_GBS_SGetItemReportValueCount();   

//获取报告的第nDataIndex数据的值
double lua_GBS_SGetItemReportValue2(long nDataIndex); 
long lua_GBS_SGetItemReportValueLong2(long nDataIndex);  //
const char* lua_GBS_SGetItemReportValueString2(long nDataIndex);  //

//扩展报告处理函数******************************************************

//获得项目的指定的报告的数据个数
long lua_GBS_SGetItemReportExDataCount();

//获得项目的指定的报告的数据：浮点数
double lua_GBS_SGetItemReportExDataValue(long nDataIndex, const char* pszValID);  //

//获得项目的指定的报告的数据：整数
long lua_GBS_SGetItemReportExDataValueLong(long nDataIndex, const char* pszValID);  //

//获得项目的指定的报告的数据：整数
const char* lua_GBS_SGetItemReportExDataValueString(long nDataIndex, const char* pszValID);  //
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
long lua_GBS_RptExDsGetCount(const char* pszPath);  //

//获得项目的指定的报告的数据：浮点数
double lua_GBS_RptExDsGetValueD(const char* pszPath, long nIndex);  //

//获得项目的指定的报告的数据：整数
long lua_GBS_RptExDsGetValueL(const char* pszPath, long nIndex);  //

//获得项目的指定的报告的数据：整数
const char* lua_GBS_RptExDsGetValueStr(const char* pszPath, long nIndex);  //

//数据验证
void lua_GBS_RptExDsValidClear();
void lua_GBS_RptExDsValidAddElement(const char* pszText, long nOption, long nUnbound);  //
void lua_GBS_RptExDsValidAddElementChoice(const char* pszText, long nOption, long nUnbound);  //
long lua_GBS_RptExDsValid(long nValidateHead);  //

long lua_GBS_RecordCmd(const char *pszCmdID, const char *pszCmdPara);  //
long lua_GBS_AdjustWord(long nPopDlg);  //

void lua_GBS_CalSoeTime(const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2);  //
void lua_GBS_CalSoeTimeEx(const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2);  //
void lua_GBS_SetSoeTripDesc(const char *pszRptID, const char *pszSoeID);  //
long lua_GBS_CalSoeError(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr);  //
long lua_GBS_CalSoeError2(double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr);  //


//Record
long lua_GBS_RcdSetProgID(const char* pszRcdProgID);  //
long lua_GBS_RcdExit();
long lua_GBS_RcdConfig(const char* pszPara);  //
long lua_GBS_RcdSelect(const char* pszPara);  //
long lua_GBS_RcdValidate(const char* pszRsltID);  //
long lua_GBS_RcdCmpClear();
long lua_GBS_RcdCmpInit(const char* pszRcdFilePathRoot, long nCreateTestTimesDir);  //
long lua_GBS_RcdCmp(const char* pszStdFile, const char* pszTestFile);  //
long lua_GBS_RcdCopyFile(const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir);  //
long lua_GBS_RcdAnalyse(const char* pszRcdFile);  //
long lua_GBS_RcdSetPath(long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir);  //

//重复测试相关
long lua_GBS_GetRepeatTimes(const char* pszItemPath);  //
long lua_GBS_GetRepeatSuccTimes(const char* pszItemPath);  //

//
void lua_GBS_SetCmdZoneIndex(long nZoneIndex);  //

//修正动作值的起始值和终止值
void lua_Gbs_ValidBeginEndValRange(const char *pBeginValID, const char *pEndValID, const char *pStepID, double dMinRange, double dMinStep, long nMinSteps, long nMaxSteps, long nUseNeg);  //

//时间出发函数
void lua_Gbs_SetTmTriggerSecond(long nSecond, long nOptr);  //
void lua_Gbs_SetTmTriggerCountMinute(long nMinute);  //
void lua_Gbs_EnterTmTrigger();
void lua_Gbs_StartTimerTigger();
void lua_Gbs_StopTimerTrigger();

//数据修约
double lua_Gbs_ValueRevised(double dValue, long nDots);  //

//////////////////////////////////////////////////////////////////////////
//日志部分
long lua_Gbs_log_query_clear();
long lua_Gbs_log_query_time(const char *pszBeginTine, const char *pszEndTime);  //
long lua_Gbs_log_query_entryid(const char *pszEntryID);  //
long lua_Gbs_log_query_logctrl(const char *pszLogCtrl);  //
long lua_Gbs_log_query_dataset(const char *pszDataset);  //

long lua_Gbs_log_query_data_clear();
long lua_Gbs_log_query_data(const char *pszDataID);  //
long lua_Gbs_log_query_data_get_count();
long lua_Gbs_log_query_data_add_to_rpt();

long lua_Gbs_log_query(const char *pszScript);  //

long lua_Gbs_log_get_count();
const char* lua_Gbs_log_get_attr(long nLogIndex, const char *pszAttr);  //
long lua_Gbs_log_get_data_count(long nLogIndex);  //
const char* lua_Gbs_log_get_data_attr(long nLogIndex, long nDataIndex, const char *pszAttr);  //
const char* lua_Gbs_log_get_data_attr2(long nLogIndex, const char *pszDataID, const char *pszAttr);  //

//////////////////////////////////////////////////////////////////////////
//字符串处理
long lua_GBS_InitStrTok(const char *pszString, const char *pControl);  //
long lua_GBS_StrTokCount();
const char* lua_GBS_StrTokIndex(long nIndex);  //
const char* lua_GBS_StrTokNext();

//装置的全局参数
void lua_GBS_SetGlobal_Str(const char *pszID, const char *pszValue);  //
void lua_GBS_SetGlobal_Long(const char *pszID, long nValue);  //
void lua_GBS_SetGlobal_Float(const char *pszID, float fValue);  //

const char* lua_GBS_GetGlobal_Str(const char *pszID);  //
long lua_GBS_GetGlobal_Long(const char *pszID);  //
float lua_GBS_GetGlobal_Float(const char *pszID);  //
long lua_GBS_GetGlobal_Long2(const CString &strID);  //

void lua_GBS_Set_TestError(const char *pszTestError);  //

long lua_GBS_BinRslt(const char *pszParaID, const char *pszRsltID);  //
long lua_GBS_BinStateRslt(const char *pszParaID, const char *pszRsltID);  //
long lua_GBS_BinChngCntRslt(const char *pszBinChngData, const char *pszRsltID);  //
/*long lua_GBS_BinRsltEx();*///const char *pszParaDatas, const char *pszRsltDatas

//2019-1-6:增加数据对象是否合格的功能   lijq
void lua_GBS_Set_AddDataErrorValueToRpt(long nValue);  //
void lua_GBS_AddDataErrorToRpt(const char* pszDataID, long nValue);  //

//2019-6-5  测试记录文件相关
const char* lua_GBS_GetTemplateFile(long nWithPath);  //
const char* lua_GBS_GetGbrptFile(long nWithPath);  //
void lua_GBS_SetGbrptFileName(const char *pszFileName);  //

//2019-7-19     根据装置的编号，调整动作时间
void lua_GBS_OffsetTestDataByGbrptIndex(const char *pszDestDataID);  //

//2020-05-22   磐能版本比对功能  shaolei；
long lua_GBS_VersionInfoCompare (const char* pszPath, const char* pszFilePath);  //

//GbScript_System/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 在调试监视信息中显示消息
// pszMsg：消息文本/消息ID
void lua_GBS_ShowMessage(const  char* pszMsg);  //

// 播放音乐文件
// pszFile：音乐文件
// nTimes：播放次数		 0<=表示循环播放 	>0表示实际播放的次数
void lua_GBS_PlayMusicFile(const  char* pszFileName, long nTimes);  //

const char* lua_GBS_GetTime();

double lua_GBS_IEC(double dValue, double dTp, double dK, double dAlpha);  //
double lua_GBS_IEEE(double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2);  //
double lua_GBS_IAC(double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta);  //
double lua_GBS_I2T(double dValue, double dTp, double dA);  //

long lua_GBS_CmpDouble(const char *pszVal1, const char *pszVal2, const char *pszPrecision);  //
long lua_GBS_CmpDoubleVal(double dVal1, double dVal2, double dPrecision);  //
double lua_GBS_CalRelError(double dAbsErr, double dRefVal);  //

//外部程序接口部分(DLL调用)
//strPara格式：”Variable1=value1; Variable2=value2;”
//dllReadDatas返回结果的格式相同
long lua_GBS_dllLoad(const char *pszDllFilePath, const char *pszDllID);  //
long lua_GBS_dllCall(const char *pszDllID, const char *pszPara);  //
long lua_GBS_dllReadDatas(const char *pszDllID, const char *pszPara);  //
long lua_GBS_dllUnload(const char *pszDllID);  //

//EXE调用
long lua_GBS_RunExe(const char *pszExeFile, const char *pszPara);  //
long lua_GBS_ExitExe(const char *pszExeFile);  //

void lua_GBS_AddLocalTime(long nHour, long nMinute, long nSecond);  //
void lua_GBS_SubLocalTime(long nHour, long nMinute, long nSecond);  //
long lua_GBS_RandLong(long nMin, long nMax);  //
float lua_GBS_RandFloat(float fMin, float fMax);  //
double lua_GBS_RandDouble(double fMin, double fMax);  //
void lua_GBS_RandSeed();

//文件
const char* lua_GBS_GetFileNameFromPath(const char *pszPath);  //
const char* lua_GBS_ParseFilePostfix(const char* pszFileName);  //
const char* lua_GBS_ParseFileName(const char *pszFileName);  //

long lua_GBS_SubStrToLong(const char *pszString, long nBegin, long nLen);  //
const char* lua_GBS_SubStrToStr(const char *pszString, long nBegin, long nLen);  //
long lua_GBS_GetSecondsFromMidnight();

// void lua_GBS_LogTime_PcTime(PPCTIME pTm);
// void lua_GBS_LogTime_GpsTime(PGPSTIME pTm);

//GbScript_Engine////////////////////////////////////////////////////////////////////////////////////////////////
// 规约帧录波设置
void lua_GBS_RecordPackage(const  char* pszPkgID);  //
void lua_GBS_UnRecordPackage(const  char* pszPkgID);  //
void lua_GBS_GetPackagePcTime(const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail);  //

// 读取标准源装置GPS时间与PC时间的之间对应关系
void lua_GBS_GetGpsPcTimeMap(const char *pszGpsTime, const char *pszPcTime);  //

//读取输出开始时刻的标准源装置GPS时间
void lua_GBS_GetOutGpsTime(const char *pszGpsTimeID);  //

//计算时间间隔
long lua_GBS_CalGpsPcTimeGap(const char *pszTimeID1, const char *pszTimerID2);  //
long lua_GBS_CalTimeGap(const char *pszTime1, const char *pszTimer2);  //
long lua_GBS_CalTimeGapCurr(const char *pszTime);  //


//创建一个GPS的时间变量
long lua_GBS_CreateGpsDateTime(const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs);  //
long lua_GBS_CreateGpsTime(const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs);  //

//读取标准源的结果数据
long lua_GBS_ReadMacroTestResult();

//重新下载电气量测试项目的参数
void lua_GBS_DownloadMacroTestPara();

//通讯规约引擎接口函数
double lua_GBS_PpGetDeviceAttr(const char *pszAttrID);  //
long lua_GBS_PpGetDeviceAttrL(const char *pszAttrID);  //
const char* lua_GBS_PpGetDeviceAttrStr(const char *pszAttrID);  //
void lua_GBS_PpSetDeviceAttrL(const char *pszAttrID, long nValue);  //
void lua_GBS_PpSetDeviceAttrStr(const char *pszAttrID, const char *pszValue);  //

long lua_GBS_PpRptGetDevieNodeDatas(const char *pszNodePath);  //
long lua_GBS_PpRptGetDeviceAttrs();  //
double lua_GBS_PpGetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID);  //
// long lua_GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, const char *strValue
long lua_GBS_PpSetDevieNodeDataAttr(const char *strDataPath, const char *strAttrID, double dValue);  //
long lua_GBS_PpDeleteAllNodeData(const char *pszNodePath);  //

long lua_GBS_PpCreateDevice(const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID);  //
long lua_GBS_PpReleaseDevice(const char *pszDeviceID);  //
long lua_GBS_PpReleaseAllDevice();
// long lua_GBS_PpRun(const char *pszDeviceID, const char *pszProcedureID, const char *pszPara
long lua_GBS_GetTestIndex();

long lua_GBS_IsProtocol(const char *pszProtocol);  //


//2020-07-24  波形图绘制设置
void lua_GBS_SetComtradeDrawLineMode(const char *pszMode);

//2021-2-21  lijunqing
void lua_GBS_RcdAnalysis(const char *pszRcdFile, const char *pszAnalysisFile);

//2021-3-28  lijunqing  根据数据集创建安全措施的数据对象
void lua_GBS_CreateSafetyDatasByDvmDataset(const char *pszDvmDatasetPath, const char *pszAttrs
									   , const char *pszDataType, const char *pszDataFormat, const char *pszDefValue);

void lua_GBS_ImportSets();

//2021-5-20  shaolei
void lua_GBS_Sleep(long nMs);

//2021-11-12 shaolei
void lua_GBS_SaveExportDatas(const char *pszDestFile, const char *pszDataConfig);
void lua_GBS_SetExportData(const char *pszName, const char *pszID, const char *pszDataType, const char *pszValue);
//根据ID，判断是否在设备数据模型中存在。shaolei 20220330
long lua_GBS_IsDsDataExist(const char* pszDataID);

//山东项目，根据SV接收压板，动态生成测试项目   shaolei  20220618
void lua_GBS_GenSvMatchItems(const char* pszDataNameHas);
//山东项目，将模板中的模型，保存到本地、从本地文件恢复模型：用于定值备份后恢复
void lua_GBS_SaveDvmToLocal(const char* pszFileName);
void lua_GBS_ReadDvmFromLocal(const char* pszFileName);

//2023-4-17  lijunqing
void lua_GBS_IecfgAddCnnInfoToSft(const char* pszItemPath, const char* pszIecfgID);

//南瑞科技，故障回放。根据文件夹中的波形文件的数量，动态生成故障回放项目  shaolei  20230614
void lua_GBS_GenTransPlayItems(const char* pszFilePath);
#endif