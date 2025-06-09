#pragma once

#include "GbScript_GlobalDefine.h"


// �ڵ��Լ�����Ϣ����ʾ��Ϣ
// pszMsg����Ϣ�ı�/��ϢID
void GBS_ShowMessage(const  char* pszMsg);

// ���������ļ�
// pszFile�������ļ�
// nTimes�����Ŵ���		 0<=��ʾѭ������ 	>0��ʾʵ�ʲ��ŵĴ���
void GBS_PlayMusicFile(const  char* pszFileName, long nTimes);

const char* GBS_GetTime();

double GBS_IEC(double dValue, double dTp, double dK, double dAlpha);
double GBS_IEEE(double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2);
double GBS_IAC(double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta);
double GBS_I2T(double dValue, double dTp, double dA);

long GBS_CmpDouble(const char *pszVal1, const char *pszVal2, const char *pszPrecision);
long GBS_CmpDoubleVal(double dVal1, double dVal2, double dPrecision);
double GBS_CalRelError(double dAbsErr, double dRefVal);

//�ⲿ����ӿڲ���(DLL����)
//strPara��ʽ����Variable1=value1; Variable2=value2;��
//dllReadDatas���ؽ���ĸ�ʽ��ͬ
long GBS_dllLoad(const char *pszDllFilePath, const char *pszDllID);
long GBS_dllCall(const char *pszDllID, const char *pszPara);
long GBS_dllReadDatas(const char *pszDllID, const char *pszPara);
long GBS_dllUnload(const char *pszDllID);

//EXE����
long GBS_RunExe(const char *pszExeFile, const char *pszPara);
long GBS_ExitExe(const char *pszExeFile);

void GBS_AddLocalTime(long nHour, long nMinute, long nSecond);
void GBS_SubLocalTime(long nHour, long nMinute, long nSecond);
long GBS_RandLong(long nMin, long nMax);
float GBS_RandFloat(float fMin, float fMax);
double GBS_RandDouble(double fMin, double fMax);
void GBS_RandSeed();

//�ļ�
const char* GBS_GetFileNameFromPath(const char *pszPath);
const char* GBS_ParseFilePostfix(const char* pszFileName);
const char* GBS_ParseFileName(const char *pszFileName);

long GBS_SubStrToLong(const char *pszString, long nBegin, long nLen);
const char* GBS_SubStrToStr(const char *pszString, long nBegin, long nLen);
long GBS_GetSecondsFromMidnight();