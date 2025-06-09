#pragma once

#include "GbScript_GlobalDefine.h"
#include "../../../../Module/XVM/TVMSingle.h"


// 在调试监视信息中显示消息
// pszMsg：消息文本/消息ID
void GBS_ShowMessage(CTScriptSingleVM *pXvm, const  char* pszMsg);

// 播放音乐文件
// pszFile：音乐文件
// nTimes：播放次数		 0<=表示循环播放 	>0表示实际播放的次数
void GBS_PlayMusicFile(CTScriptSingleVM *pXvm, const  char* pszFileName, long nTimes);

const char* GBS_GetTime(CTScriptSingleVM *pXvm);

double GBS_IEC(CTScriptSingleVM *pXvm, double dValue, double dTp, double dK, double dAlpha);
double GBS_IEEE(CTScriptSingleVM *pXvm, double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2);
double GBS_IAC(CTScriptSingleVM *pXvm, double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta);
double GBS_I2T(CTScriptSingleVM *pXvm, double dValue, double dTp, double dA);

long GBS_CmpDouble(CTScriptSingleVM *pXvm, const char *pszVal1, const char *pszVal2, const char *pszPrecision);
long GBS_CmpDoubleVal(CTScriptSingleVM *pXvm, double dVal1, double dVal2, double dPrecision);
double GBS_CalRelError(CTScriptSingleVM *pXvm, double dAbsErr, double dRefVal);

//外部程序接口部分(CTScriptSingleVM *pXvm, DLL调用)
//strPara格式：”Variable1=value1; Variable2=value2;”
//dllReadDatas返回结果的格式相同
long GBS_dllLoad(CTScriptSingleVM *pXvm, const char *pszDllFilePath, const char *pszDllID);
long GBS_dllCall(CTScriptSingleVM *pXvm, const char *pszDllID, const char *pszPara);
long GBS_dllReadDatas(CTScriptSingleVM *pXvm, const char *pszDllID, const char *pszPara);
long GBS_dllUnload(CTScriptSingleVM *pXvm, const char *pszDllID);

//EXE调用
long GBS_RunExe(CTScriptSingleVM *pXvm, const char *pszExeFile, const char *pszPara);
long GBS_ExitExe(CTScriptSingleVM *pXvm, const char *pszExeFile);

void GBS_AddLocalTime(CTScriptSingleVM *pXvm, long nHour, long nMinute, long nSecond);
void GBS_SubLocalTime(CTScriptSingleVM *pXvm, long nHour, long nMinute, long nSecond);
long GBS_RandLong(CTScriptSingleVM *pXvm, long nMin, long nMax);
float GBS_RandFloat(CTScriptSingleVM *pXvm, float fMin, float fMax);
double GBS_RandDouble(CTScriptSingleVM *pXvm, double fMin, double fMax);
void GBS_RandSeed(CTScriptSingleVM *pXvm);

//文件
const char* GBS_GetFileNameFromPath(CTScriptSingleVM *pXvm, const char *pszPath);
const char* GBS_ParseFilePostfix(CTScriptSingleVM *pXvm, const char* pszFileName);
const char* GBS_ParseFileName(CTScriptSingleVM *pXvm, const char *pszFileName);

long GBS_SubStrToLong(CTScriptSingleVM *pXvm, const char *pszString, long nBegin, long nLen);
const char* GBS_SubStrToStr(CTScriptSingleVM *pXvm, const char *pszString, long nBegin, long nLen);
long GBS_GetSecondsFromMidnight(CTScriptSingleVM *pXvm);