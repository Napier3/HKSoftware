#pragma once

class CTScriptSingleVM;
class CPpScript;

CPpScript* PPS_GetPpScript(CTScriptSingleVM *pXvm);

#define IP_DEFAULT 0X6464a8c0   //192.168.100.100
//////////////////////////////////////////////////////////////////////////
//logic
long script_LAnd(long nVal1, long nVal2);
long script_LOr(long nVal1, long nVal2);
long script_LNot(long nVal);
long script_LXor(long nVal1,long nVal2);

long script_LComplement(long nVal);
short script_LComplement2(short nVal);
char script_LComplement1(char nVal);
long script_LInverse(long nVal);
short script_LInverse2(short nVal);
char script_LInverse1(char nVal);
// long script_LRComplement(long nVal);

//////////////////////////////////////////////////////////////////////////
//bit

long script_LShift(long nVal, long nShift);
long script_RShift(long nVal, long nShift);
long script_MkWord(long nHigh, long nLow);

//////////////////////////////////////////////////////////////////////////
//time
long script_GetYear();
long script_GetMonth();
long script_GetDay();
long script_GetHour();
long script_GetMinute();
long script_GetSecond();
long script_GetMillionSecond();
const char* script_GetSystemTime();

//////////////////////////////////////////////////////////////////////////
//BCD/HEX
long script_BcdToHex(long nVal);
long script_HexToBcd(long nVal);
const char* script_StrBcdToHex(const char*);
const char* script_StrHexToBcd(const char*);


//系统相关的函数
//long script_GetIP(CTScriptSingleVM *pXvm, const char *pszTcpOrUdp);    //获取设备的IP地址
const char* script_GetIP(CTScriptSingleVM *pXvm, const char *pszTcpOrUdp);    //获取设备的IP地址
long script_GetRemoteIP(CTScriptSingleVM *pXvm, const char *pszTcpOrUdp);    //获取远程的IP地址
long script_GetDeviceAddr(CTScriptSingleVM *pXvm);   //获取设备地址
long script_GetDeviceAttrL(CTScriptSingleVM *pXvm, const char* pszAttrID);   //获取设备地址
const char* script_GetDeviceAttrStr(CTScriptSingleVM *pXvm, const char* pszAttrID);   //获取设备地址
long script_GetCmmMode(CTScriptSingleVM *pXvm);   //获取通讯模式
long script_GetPort(CTScriptSingleVM *pXvm, const char *pszCmmMode);  //获取通讯的端口
long script_SetPort(CTScriptSingleVM *pXvm, const char *pszTcpOrUdp, long nPort);  //获取通讯的端口
long script_GetSystemPara(CTScriptSingleVM *pXvm, const char* pszParaID);   //获取系统的参数

long script_SetDeviceAttrL(CTScriptSingleVM *pXvm, const char* pszAttrID, long nValue);
long script_SetDeviceAttrStr(CTScriptSingleVM *pXvm, const char* pszAttrID, const char *pszValue);


//////////////////////////////////////////////////////////////////////////
//timer
void script_KillTimer(const char *pszTimerID);
void script_ResetTimer(const char *pszTimerID);
void script_SetTimerLong(const char *pszTimerID, long nMs);


long script_GetBitInLong(long nValue, long nBitIndex);
long script_SetBitInLong(long nValue, long nBitIndex);
long script_ClearBitInLong(long nValue, long nBitIndex);

long script_GetBitInLong16(long nValue, long nBitIndex);
long script_Get2BitInLong16(long nValue, long nBitIndex);
long script_SetBitInLong16(long nValue, long nBitIndex);
long script_ClearBitInLong16(long nValue, long nBitIndex);

long script_GetBitInLong32(long nValue, long nBitIndex);
long script_SetBitInLong32(long nValue, long nBitIndex);
long script_ClearBitInLong32(long nValue, long nBitIndex);

long script_GetBitInLong8(long nValue, long nBitIndex);
long script_SetBitInLong8(long nValue, long nBitIndex);
long script_ClearBitInLong8(long nValue, long nBitIndex);

long script_GetBitRangeInLong8(long nValue, long nBitStart, long nBitEnd);

void script_LogPrint(const char *pszVariableID,long nValue);
void script_ShowMsg(const char *pszMsg);

//范围内的随机数
double script_RandInRange(float fMinVal, float fMaxValue);

//浮点数转换为整数
long script_FloatToLong(float fValue);

//获取指定数位的数值
long script_GetFloatDigit(float fValue, long nDigit);

//时间转换函数
const char* script_GetTimeStr1970(CTScriptSingleVM *pXvm, long nSeconds);
long script_GetTimeLong1970(const char *pszTime);
//2023-1-31  lijunqing
const char* script_GetTimeStr1970_ms(CTScriptSingleVM *pXvm, __int64 n64Ms);
__int64 script_GetTimeLong1970_ms(const char *pszTime);

//延时器
void script_Sleep(long time);
