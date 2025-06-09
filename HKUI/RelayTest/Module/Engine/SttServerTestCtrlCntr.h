#pragma once

#include "SttTestEngineBase.h"
#include "../SttTestBase/SttTestBase.h"

class CSttServerTestCtrlCntr
{
public:
    static CSttServerTestCtrlCntr* Create();
	static void Release();

private:
    CSttServerTestCtrlCntr();
    virtual ~CSttServerTestCtrlCntr();

    static CSttServerTestCtrlCntr * g_pCSttServerTestCtrlCntr;
    static long g_nCSttServerTestCtrlCntrRef;

protected:
	CSttTestBase* m_pCurrSttTest;
    CSttTestBase* m_pOldSttTest;  //
public:
	static BOOL EventProcess();
	static BOOL EventProcessEx();
	static void ProcessTestFinish();
    static void Test(CSttTestBase *pTest);
    static void Test();
    static void UpdateParameter();
	static void SetParameter(CSttTestBase *pTest);
	static void SetParameter();
    static void ManualTrigger();//手动触发
    static CSttTestBase* GetCurrTest();
    static void OnHeartbeat();
protected:
	BOOL In_EventProcess();
	BOOL In_EventProcessEx();
	void In_ProcessTestFinish();
    void In_Test(CSttTestBase *pTest);
    void In_Test();
    void In_UpdateParameter();
	void In_SetParameter(CSttTestBase *pTest);
	void In_SetParameter();
};
