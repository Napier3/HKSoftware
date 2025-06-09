#pragma once

#include "Interface/MacroTestEngine.h"
#include "../../Module/TestMacro/TestMacroInterface.h"
#include "GuideBook/GbDataTypeMngr.h"
#include "GuideBook/GbParaTypeMngr.h"

//////////////////////////////////////////////////////////////////////////
//CMacroTestEngineCreate
class CMacroTestEngineCreate : public CExBaseObject
{
public:
	CMacroTestEngineCreate();
	virtual ~CMacroTestEngineCreate();

	MacroTest::IMacroTestEngine m_pMacroTestEngine;
	MacroTest::IMacroTest m_oMacroTest;
	unsigned long m_hLogWnd;

	MacroTest::IMacroTestEngine GetMacroTestEngine(const CString &strProgID);
	MacroTest::IMacroTest GetMacroTest(const CString &strProgID, CDataGroup *pTestApps, BOOL &bFirstCreate); //lijq 2019-1-14   add  strTestAppGroup
	void ReleaseMacroTestEngine();
	void ReleaseAllDevice();

	void ShowSpyWnd();
	void ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara);
	void ConfigEngine(const CString &strIP);
	long AttatchLogWnd(unsigned long hWnd);
	void TestApp_InitTestApps(CDvmDataset *pDestApps, CDataGroup *pTestApps);
};

class CMacroTestEngineCreateMngr : public CExBaseList
{
public:
	CMacroTestEngineCreateMngr();
	virtual ~CMacroTestEngineCreateMngr();

	MacroTest::IMacroTestEngine GetMacroTestEngine(const CString &strProgID);
	MacroTest::IMacroTest GetMacroTest(const CString &strProgID, CDataGroup *pTestApps, BOOL &bFirstCreate);
	void ReleaseMacroTestEngine();
	void ReleaseMacroTestEngine(const CString &strProgID);
	void ShowSpyWnd();
	void ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara);

	void ConfigEngine(const CString &strProgID, const CString &strIP);
	long AttatchLogWnd(unsigned long hWnd);

public:
	unsigned long m_hLogWnd;
};

extern CString g_strActiveTestMacroProgID;
