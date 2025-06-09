//////////////////////////////////////////////////////////////////////////
//TestMacroInterface.h
//TestMacro����Ľӿڶ������չ�ļ�

#ifndef _TESTMACRO_INTERFACE_H__
#define _TESTMACRO_INTERFACE_H__

#include "SystemToolInterface.h"
#import "TestMacro.tlb"

//������Ϣ�������Թ���"XXxxxxx"�����ڡ�
extern CString g_strFormatMacroNotExist;

//��ȡ���Թ��ܵĲ������ݣ�����FaultParas��SysParas
void TM_GetTestMacroParasValues(const CString &strMacroID, SystemTool::IValuesPtr &oValues);
void TM_GetTestMacroParasValues(TestMacroLib::ITestMacroPtr &oMacro, SystemTool::IValuesPtr &oValues);
void TM_GetTestMacroParasShortDatas(const CString &strMacroID, CShortDatas  &oDatas);
void TM_GetTestMacroParasShortDatas(TestMacroLib::ITestMacroPtr &oMacro, CShortDatas  &oDesDatas);

//���Թ������ݽӿڶ�����һ��������ֻ����һ�Σ��μ�TestMacroInterface.cpp
//�������Թ������ݽӿڶ���
TestMacroLib::ITestMacrosPtr TM_CreateTestMacros();

//���ҹ������ݽӿڶ���
TestMacroLib::ITestMacroPtr  TM_FindTestMacro(const CString &strMacroID);

//�ͷŲ��Թ������ݽӿڶ���
void TM_ReleaseTestMacros();

#endif