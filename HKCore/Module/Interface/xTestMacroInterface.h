//////////////////////////////////////////////////////////////////////////
//TestMacroInterface.h
//TestMacro组件的接口定义和扩展文件

#ifndef _TESTMACRO_INTERFACE_H__
#define _TESTMACRO_INTERFACE_H__

#include "SystemToolInterface.h"
#import "TestMacro.tlb"

//监视信息：”测试功能"XXxxxxx"不存在“
extern CString g_strFormatMacroNotExist;

//获取测试功能的参数数据，包括FaultParas、SysParas
void TM_GetTestMacroParasValues(const CString &strMacroID, SystemTool::IValuesPtr &oValues);
void TM_GetTestMacroParasValues(TestMacroLib::ITestMacroPtr &oMacro, SystemTool::IValuesPtr &oValues);
void TM_GetTestMacroParasShortDatas(const CString &strMacroID, CShortDatas  &oDatas);
void TM_GetTestMacroParasShortDatas(TestMacroLib::ITestMacroPtr &oMacro, CShortDatas  &oDesDatas);

//测试功能数据接口对象在一个进程中只创建一次，参见TestMacroInterface.cpp
//创建测试功能数据接口对象
TestMacroLib::ITestMacrosPtr TM_CreateTestMacros();

//查找功能数据接口对象
TestMacroLib::ITestMacroPtr  TM_FindTestMacro(const CString &strMacroID);

//释放测试功能数据接口对象
void TM_ReleaseTestMacros();

#endif