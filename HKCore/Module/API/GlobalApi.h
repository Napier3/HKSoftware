// GlobalApi.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GLOBAL_API_H__)
#define _GLOBAL_API_H__


#include "StringApi.h"

BOOL IsStringNumber(const char* pszString);
BOOL IsStringNumber(CString &strString);
BOOL IsStringNumber(const wchar_t *pszString);

//2021-5-30  lijunqig
BOOL IsStringInteger(const char* pszString);
BOOL IsStringInteger(CString &strString);


void ChopFloatString(CString &strValue, long nDecimal);
char* ChopFloatString(char* pszFloatString, long nDecimal);

long GetRGBColor(const char *pszRGBColor,COLORREF crDefColor=RGB(255,255,255));
long GetRGBColor(const CString &strRGBColor,COLORREF crDefColor=RGB(255,255,255));
void GetRGBColor(COLORREF crColor,char *pszRGBColor);


//注册表读写
bool ReadDataFromRegister(const CString &pszKey,const CString &pszValueName,CString &strData);
CString ReadDataFromRegister(const CString &strRoot,const CString &strRegKey);
bool WriteDataToRegister(const CString &pszKey,const CString &pszValueName,LPCSTR pszData);
bool WriteDataToRegister(const CString &strRoot,const CString &strRegKey,const CString &strRegKeyVal);

void ChangeSecondsToSystemTime(long nSeconds, SYSTEMTIME &tmSys);
void ChangeMSecondsToSystemTime(double dMSeconds, SYSTEMTIME &tmSys);
void ChangeSecondsToSystemTime(double dSeconds, SYSTEMTIME &tmSys);

void TransSecondsToSystemTime(long nSeconds, CString &strTime);
void TransMSecondsToSystemTime(double dMSeconds, CString &strTime);
void TransSecondsToSystemTime(double dSeconds, CString &strTime, BOOL bChop=FALSE);
void GetCurrSystemtimeString(CString &strTime);
void GetCurrSystemtimeString2(CString &strTime, BOOL bAddColon);
void GetCurrSystemtimeString2(char *pszTime, BOOL bAddColon);
void GetCurrSystemtimeString2_Short(char *pszTime, BOOL bAddColon);

//强行终止过程
BOOL IsProgramdExeFileSame(const CString &strExeFile, const CString &strProcessFile);

BOOL TerminateProgram(const CString &strProcessName);
BOOL IsProgramExist(const CString &strProcessName);
unsigned long GetProcID(const CString &strExeFileName);
HWND GetProcMainWndByPid(DWORD dwProcessID, CString &strTitle);
void ActiveProcMainWnd(const CString &strExeFileName);
BOOL KillProc(const CString &pn);
BOOL ExecuteFile(const CString &strExePath, const CString &strCmdLine, const CString &strMode);


#ifndef _PSX_IDE_QT_
void GetVariantString(VARIANT *pVar, CString &strVar);
#endif

BOOL IsCurrTickCountTimeOut(DWORD dwBeginTick, DWORD dwTickLong);

inline DWORD CalTickCountLongToNow(DWORD dwBegin)
{
	DWORD dwTickCount = ::GetTickCount();
	DWORD dwTimeLong = 0;

	if (dwTickCount > dwBegin)
	{
		dwTimeLong = dwTickCount - dwBegin;
	}
	else
	{
		dwTimeLong = 0xFFFFFFFF - dwBegin;
		dwTimeLong += dwTickCount;
	}

	return dwTimeLong;
}

void UI_ExpandAllChildren(CTreeCtrl *pTree, HTREEITEM hCurr);
void UI_BringWndToTop(CWnd *pWnd);
void UI_BringWndToTop(HWND hWnd);

void GetProgramCompileTime(SYSTEMTIME &st);


/*************************************************************************
Function Name    :CalArrayCrc
Description      :calculate array crc.
Algorithm        :
Calls            :CalSingleCharCrc
Called By        :anywhere
Table Accessed   :
Table Updated    :
Input            :u16Length,*ptr
Output           :crc
Return           :crc
Revision         :Date   :unknown
                  Author :huangjing
                  Remark :create
                  
                  Date   :2002.9.6
                  Author :xiaohh
                  Remark :modify
Others           :
**************************************************************************/
unsigned short CalArrayCrc(unsigned short u16length, char *ptr);


/*************************************************************************
Function Name    :CalSingleCharCrc
Description      :calculate single byte crc.
Algorithm        :
Calls            :
Called By        :anywhere
Table Accessed   :
Table Updated    :
Input            :u16crc
Output           :u16crc
Return           :u16crc
Revision         :Date   :unknown
                  Author :huangjing
                  Remark :create
                  
                  Date   :2002.9.6
                  Author :xiaohh
                  Remark :modify
Others           :
**************************************************************************/
unsigned short CalSingleCharCrc(unsigned short u16crc, char input);

void UI_ExpandAllChildren(CTreeCtrl *pTree, HTREEITEM hCurr);
void UI_BringWndToTop(CWnd *pWnd);
void UI_BringWndToTop(HWND hWnd);

//二进制数据转换
#include "HexTransApi.h"

#endif // !defined(_GLOBAL_API_H__)
