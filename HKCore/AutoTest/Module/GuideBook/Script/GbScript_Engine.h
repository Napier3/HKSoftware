#pragma once

#include "GbScript_GlobalDefine.h"
#include "../../../../Module/XVM/TVMSingle.h"

/*

*/
class CGuideBook;
CGuideBook* GBS_GetGuideBook(CTScriptSingleVM *pXvm);

// 规约帧录波设置
void GBS_RecordPackage(CTScriptSingleVM *pXvm, const  char* pszPkgID);
void GBS_UnRecordPackage(CTScriptSingleVM *pXvm, const  char* pszPkgID);
void GBS_GetPackagePcTime(CTScriptSingleVM *pXvm, const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail);

// 读取标准源装置GPS时间与PC时间的之间对应关系
void GBS_GetGpsPcTimeMap(CTScriptSingleVM *pXvm, const char *pszGpsTime, const char *pszPcTime);

//读取输出开始时刻的标准源装置GPS时间
void GBS_GetOutGpsTime(CTScriptSingleVM *pXvm, const char *pszGpsTimeID);

//计算时间间隔
long GBS_CalGpsPcTimeGap(CTScriptSingleVM *pXvm, const char *pszTimeID1, const char *pszTimerID2);
long GBS_CalTimeGap(CTScriptSingleVM *pXvm, const char *pszTime1, const char *pszTimer2);
long GBS_CalTimeGapCurr(CTScriptSingleVM *pXvm, const char *pszTime);


//创建一个GPS的时间变量
long GBS_CreateGpsDateTime(CTScriptSingleVM *pXvm, const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs);
long GBS_CreateGpsTime(CTScriptSingleVM *pXvm, const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs);

//读取标准源的结果数据
long GBS_ReadMacroTestResult(CTScriptSingleVM *pXvm);

//重新下载电气量测试项目的参数
void GBS_DownloadMacroTestPara(CTScriptSingleVM *pXvm);

//通讯规约引擎接口函数
double GBS_PpGetDeviceAttr(CTScriptSingleVM *pXvm, const char *pszAttrID);
long GBS_PpGetDeviceAttrL(CTScriptSingleVM *pXvm, const char *pszAttrID);
const char* GBS_PpGetDeviceAttrStr(CTScriptSingleVM *pXvm, const char *pszAttrID);
void GBS_PpSetDeviceAttrL(CTScriptSingleVM *pXvm, const char *pszAttrID, long nValue);
void GBS_PpSetDeviceAttrStr(CTScriptSingleVM *pXvm, const char *pszAttrID, const char *pszValue);

long GBS_PpRptGetDevieNodeDatas(CTScriptSingleVM *pXvm, const char *pszNodePath);
long GBS_PpRptGetDeviceAttrs(CTScriptSingleVM *pXvm);//void
double GBS_PpGetDevieNodeDataAttr(CTScriptSingleVM *pXvm, const char *strDataPath, const char *strAttrID);
// long GBS_PpSetDevieNodeDataAttr(CTScriptSingleVM *pXvm, const char *strDataPath, const char *strAttrID, const char *strValue);
long GBS_PpSetDevieNodeDataAttr(CTScriptSingleVM *pXvm, const char *strDataPath, const char *strAttrID, double dValue);
long GBS_PpDeleteAllNodeData(CTScriptSingleVM *pXvm, const char *pszNodePath);

long GBS_PpCreateDevice(CTScriptSingleVM *pXvm, const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID);
long GBS_PpReleaseDevice(CTScriptSingleVM *pXvm, const char *pszDeviceID);
long GBS_PpReleaseAllDevice(CTScriptSingleVM *pXvm);
// long GBS_PpRun(CTScriptSingleVM *pXvm, const char *pszDeviceID, const char *pszProcedureID, const char *pszPara);
long GBS_GetTestIndex(CTScriptSingleVM *pXvm);

long GBS_IsProtocol(CTScriptSingleVM *pXvm, const char *pszProtocol);
