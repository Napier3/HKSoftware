#pragma once

class CTScriptSingleVM;
class CPpScript;

CPpScript* PPS_GetPpScript(CTScriptSingleVM *pXvm);

// ��ȡ��Ʒ�������ı���ֵ
long script_GetMEA(CTScriptSingleVM *pXvm, long nIndex, long nBytes);		
long script_CalMEA(long nValue);

// ʱ�亯��
const char* script_GetCP32Time2a(CTScriptSingleVM *pXvm, long nIndex, long nBytes);
void script_SetBbCurrValueCP32Time2a(CTScriptSingleVM *pXvm,long nIndex);

const char* script_GetCP24Time2a(CTScriptSingleVM *pXvm,long nIndex, long nBytes);
void script_SetBbCurrValueCP24Time2a(CTScriptSingleVM *pXvm,long nIndex);

const char* script_GetCP56Time2a(CTScriptSingleVM *pXvm,long nIndex, long nBytes);
void script_SetBbCurrValueCP56Time2a(CTScriptSingleVM *pXvm,long nIndex);
void script_SetBbCurrValueCP56Time2aEx(CTScriptSingleVM *pXvm,long nIndex, const char *pszDateTime);
void script_SetBbCurrValue48TimeMs(CTScriptSingleVM *pXvm,long nIndex, const char *pszDateTime);

//2018-5-30  ����PM
const char* script_GetXujiTime(long nIndex,long nBytes);

// ��ȡIEEE754
float script_GetIEEE754(CTScriptSingleVM *pXvm,long nIndex);		
void script_SetIEEE754(CTScriptSingleVM *pXvm,long nIndex, float fValue);

// ��ȡASCII
const char* script_GetASCII(CTScriptSingleVM *pXvm,long nIndex, long nBytes);		
//void script_SetASCII(long nIndex, float fValue);