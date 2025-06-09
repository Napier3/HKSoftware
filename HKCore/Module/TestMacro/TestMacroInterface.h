//////////////////////////////////////////////////////////////////////////
//TestMacroInterface.h
//TestMacro组件的接口定义和扩展文件

#ifndef _TESTMACRO_INTERFACE_H__
#define _TESTMACRO_INTERFACE_H__

#include "TestMacros.h"
#include "TestMacrosFile.h"
#include "../TestMacroScript/TestMacroScriptMngr.h"

//监视信息：”测试功能"XXxxxxx"不存在“
extern CString g_strFormatMacroNotExist;

//获取测试功能的参数数据，包括FaultParas、SysParas
void TM_GetTestMacroParasValues(CTestMacros *pTestMacros, const CString &strMacroID,CValues *pValues);
void TM_GetTestMacroParasValues(CTestMacro *pMacro, CValues *pValues);
void TM_GetTestMacroParasShortDatas(CTestMacros *pTestMacros, const CString &strMacroID, CShortDatas  *pDatas);
void TM_GetTestMacroParasShortDatas(CTestMacro *pMacro, CShortDatas  *pDesDatas);

//测试功能数据接口对象在一个进程中只创建一次，参见TestMacroInterface.cpp
//创建测试功能数据接口对象
CTestMacros* TM_CreateTestMacros();
CTestMacrosFile* TM_GetTestMacrosFile(CString &strMacroFile);
CTestMacros* TM_GetTestMacros(CString &strMacroFile);

//2021-8-15  lijunqing
#ifndef NOT_USE_TestMacroScriptMngr
CTestMacroScriptMngr* TM_GetTestMacroScriptMngr(const CString &strMacroFile);
CTestMacroScriptMngr* TM_GetTestMacroScriptMngr(CTestMacros *pMacros);
CTestMacroScript* TM_GetTestMacroScript(CTestMacro *pMacro);
#endif

//查找功能数据接口对象
//CTestMacro*  TM_FindTestMacro(const CString &strMacroID);

//释放测试功能数据接口对象
void TM_ReleaseTestMacros();

inline CString TM_GetDefaultTestMacrosFile()
{
	return _T("TestMacro.xml");
}

#endif