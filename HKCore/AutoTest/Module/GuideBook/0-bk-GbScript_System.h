#pragma once

#include "GbScript_GlobalDefine.h"


// 在调试监视信息中显示消息
// pszMsg：消息文本/消息ID
void GBS_ShowMessage(const  char* pszMsg);

// 播放音乐文件
// pszFile：音乐文件
// nTimes：播放次数		 0<=表示循环播放 	>0表示实际播放的次数
void GBS_PlayMusicFile(const  char* pszFileName, long nTimes);

const char* GBS_GetTime();

double GBS_IEC(double dValue, double dTp, double dK, double dAlpha);
double GBS_IEEE(double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2);
double GBS_IAC(double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta);
double GBS_I2T(double dValue, double dTp, double dA);

long GBS_CmpDouble(const char *pszVal1, const char *pszVal2, const char *pszPrecision);
long GBS_CmpDoubleVal(double dVal1, double dVal2, double dPrecision);
double GBS_CalRelError(double dAbsErr, double dRefVal);

//外部程序接口部分(DLL调用)
//strPara格式：”Variable1=value1; Variable2=value2;”
//dllReadDatas返回结果的格式相同
long GBS_dllLoad(const char *pszDllFilePath, const char *pszDllID);
long GBS_dllCall(const char *pszDllID, const char *pszPara);
long GBS_dllReadDatas(const char *pszDllID, const char *pszPara);
long GBS_dllUnload(const char *pszDllID);

//EXE调用
long GBS_RunExe(const char *pszExeFile, const char *pszPara);
long GBS_ExitExe(const char *pszExeFile);

void GBS_AddLocalTime(long nHour, long nMinute, long nSecond);
void GBS_SubLocalTime(long nHour, long nMinute, long nSecond);
long GBS_RandLong(long nMin, long nMax);
float GBS_RandFloat(float fMin, float fMax);
double GBS_RandDouble(double fMin, double fMax);
void GBS_RandSeed();

//文件
const char* GBS_GetFileNameFromPath(const char *pszPath);
const char* GBS_ParseFilePostfix(const char* pszFileName);
const char* GBS_ParseFileName(const char *pszFileName);

long GBS_SubStrToLong(const char *pszString, long nBegin, long nLen);
const char* GBS_SubStrToStr(const char *pszString, long nBegin, long nLen);
long GBS_GetSecondsFromMidnight();