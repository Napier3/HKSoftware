//////////////////////////////////////////////////////////////////////////
//TestMacroInterface.h
//TestMacro����Ľӿڶ������չ�ļ�

#ifndef _TESTMACRO_INTERFACE_H__
#define _TESTMACRO_INTERFACE_H__

#include "TestMacros.h"
#include "TestMacrosFile.h"
#include "../TestMacroScript/TestMacroScriptMngr.h"

//������Ϣ�������Թ���"XXxxxxx"�����ڡ�
extern CString g_strFormatMacroNotExist;

//��ȡ���Թ��ܵĲ������ݣ�����FaultParas��SysParas
void TM_GetTestMacroParasValues(CTestMacros *pTestMacros, const CString &strMacroID,CValues *pValues);
void TM_GetTestMacroParasValues(CTestMacro *pMacro, CValues *pValues);
void TM_GetTestMacroParasShortDatas(CTestMacros *pTestMacros, const CString &strMacroID, CShortDatas  *pDatas);
void TM_GetTestMacroParasShortDatas(CTestMacro *pMacro, CShortDatas  *pDesDatas);

//���Թ������ݽӿڶ�����һ��������ֻ����һ�Σ��μ�TestMacroInterface.cpp
//�������Թ������ݽӿڶ���
CTestMacros* TM_CreateTestMacros();
CTestMacrosFile* TM_GetTestMacrosFile(CString &strMacroFile);
CTestMacros* TM_GetTestMacros(CString &strMacroFile);

//2021-8-15  lijunqing
#ifndef NOT_USE_TestMacroScriptMngr
CTestMacroScriptMngr* TM_GetTestMacroScriptMngr(const CString &strMacroFile);
CTestMacroScriptMngr* TM_GetTestMacroScriptMngr(CTestMacros *pMacros);
CTestMacroScript* TM_GetTestMacroScript(CTestMacro *pMacro);
#endif

//���ҹ������ݽӿڶ���
//CTestMacro*  TM_FindTestMacro(const CString &strMacroID);

//�ͷŲ��Թ������ݽӿڶ���
void TM_ReleaseTestMacros();

inline CString TM_GetDefaultTestMacrosFile()
{
	return _T("TestMacro.xml");
}

#endif