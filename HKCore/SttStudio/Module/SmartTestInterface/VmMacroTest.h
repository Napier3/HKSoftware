#pragma once

#include"MacroTestInterface.h"

#include "../../../AutoTest/Module/Interface/MacroTestEngine.h"
#include "../../../AutoTest/Module/MacroTestEngineCreateMngr.h"

#ifdef _USE_SMARTTEST_INTERFACE_COM_
class CVmMacroTest : public CMacroTestInterface
{
public:
	CVmMacroTest();
	virtual ~CVmMacroTest(void);

	MacroTest::IMacroTest m_oMacroTest;

public:
	virtual long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID);
	virtual CString GetConfig();
	virtual long SetConfig(const CString & bstrConfig);
	virtual long Test(const CString & strMacroID, const CString & strParameter);
	virtual CString GetReport();
	virtual long StopTest();
	virtual long CloseDevice();
	virtual CString GetSearchReport();
	virtual long FinishTest(long nState);
	virtual long ExcuteCmd(const CString &strCmdID, const CString & strCmdParameter);
	virtual unsigned long GetExternMsgRcvWnd();
	virtual unsigned long GetExternMsgID();
	virtual unsigned long StopDevice(void);
};


class CVmMacroTestEngine : public CMacroTestEngineInterface
{
public:
	CVmMacroTestEngine();
	virtual ~CVmMacroTestEngine(void);

	virtual CMacroTestInterface* CreateMacroTest(const CString &bstrConfig);
	virtual long ExitEngine();
	virtual long ExcuteCmd(const CString &strCmdID, const CString &strCmdParameter);
	virtual long ShowSpyWnd(long nShow) ;
	virtual long ConfigEngine();
	virtual long AttatchLogWnd(unsigned long hWnd);

	MacroTest::IMacroTestEngine m_oMacroTestEngine;
};

class CVmMacroTestCreator : public CMacroTestCreatorInterface
{
public:
	CVmMacroTestCreator();
	virtual ~CVmMacroTestCreator();

	CMacroTestEngineCreateMngr m_oMacroTestEngineCreateMngr;

public:
	virtual CMacroTestEngineInterface* CreateMacroTestEngine(const CString &strMacroFile);
	virtual CMacroTestEngineInterface* GetMacroTestEngine(const CString &strType, const CString &strProgID, const CString &strMacroFile);
	virtual CMacroTestInterface* GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps);
	virtual void ReleaseMacroTestEngine();
	virtual void ReleaseMacroTestEngine(const CString &strProgID);
	virtual void InitMacroTestEngineShowSpyWnd();
	virtual void ShowSpyWnd();
	virtual void ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara);
	virtual long ConfigEngine(const CString &strProgID, const CString &strIP);
	virtual long AttatchLogWnd(unsigned long hWnd);

};
#endif

