#include "stdafx.h"
#include "SttServerTestCtrlCntr.h"
#ifdef _PSX_QT_LINUX_
#include "../SttDevice/SttDeviceBase.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttServerTestCtrlCntr *CSttServerTestCtrlCntr::g_pCSttServerTestCtrlCntr=NULL;
long CSttServerTestCtrlCntr::g_nCSttServerTestCtrlCntrRef = 0;

CSttServerTestCtrlCntr* CSttServerTestCtrlCntr::Create()
{
	g_nCSttServerTestCtrlCntrRef++;

	if (g_nCSttServerTestCtrlCntrRef == 1)
	{
		g_pCSttServerTestCtrlCntr=new CSttServerTestCtrlCntr;
	}

	return g_pCSttServerTestCtrlCntr;
}

void CSttServerTestCtrlCntr::Release()
{
	g_nCSttServerTestCtrlCntrRef--;

	if(g_nCSttServerTestCtrlCntrRef == 0)
	{
		delete g_pCSttServerTestCtrlCntr;
		g_pCSttServerTestCtrlCntr=NULL;
	}
}

CSttServerTestCtrlCntr::CSttServerTestCtrlCntr()
{
	m_pCurrSttTest = NULL;
	m_pOldSttTest = NULL;
}

CSttServerTestCtrlCntr::~CSttServerTestCtrlCntr()
{
	if (m_pOldSttTest != NULL)
	{
		delete m_pOldSttTest;
		m_pOldSttTest = NULL;
	}

	if (m_pCurrSttTest != NULL)
	{
		delete m_pCurrSttTest;
		m_pCurrSttTest = NULL;
	}
}

BOOL CSttServerTestCtrlCntr::EventProcess()
{
	return g_pCSttServerTestCtrlCntr->In_EventProcess();
}

void CSttServerTestCtrlCntr::ProcessTestFinish()
{
	g_pCSttServerTestCtrlCntr->In_ProcessTestFinish();
}

void CSttServerTestCtrlCntr::Test(CSttTestBase *pTest)
{
	g_pCSttServerTestCtrlCntr->In_Test(pTest);
}

void CSttServerTestCtrlCntr::Test()
{
	g_pCSttServerTestCtrlCntr->In_Test();
}

void CSttServerTestCtrlCntr::UpdateParameter()
{
	g_pCSttServerTestCtrlCntr->In_UpdateParameter();
}

void CSttServerTestCtrlCntr::SetParameter(CSttTestBase *pTest)
{
	g_pCSttServerTestCtrlCntr->In_SetParameter(pTest);
}

void CSttServerTestCtrlCntr::SetParameter()
{
	g_pCSttServerTestCtrlCntr->In_SetParameter();
}

void CSttServerTestCtrlCntr::ManualTrigger()
{
	g_pCSttServerTestCtrlCntr->m_pCurrSttTest->Triger();
}

CSttTestBase* CSttServerTestCtrlCntr::GetCurrTest()
{
	return g_pCSttServerTestCtrlCntr->m_pCurrSttTest;
}

void CSttServerTestCtrlCntr::OnHeartbeat()
{

}

///////////////////////////////////////////////////
BOOL CSttServerTestCtrlCntr::In_EventProcess()
{
	//20211209zhoulei
	//ASSERT (m_pCurrSttTest != NULL);
//	if(m_pCurrSttTest == NULL)
//	{
//		CLogPrint::LogString(XLOGLEVEL_TRACE,"m_pCurrSttTest == NULL");
//	}

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->EventProcessEx();//用于表计采集消息
#endif
#endif

	if (m_pCurrSttTest != NULL && m_pCurrSttTest->GetTestStarting())
	{
		return m_pCurrSttTest->EventProcess();
	}

    return FALSE;
}

void CSttServerTestCtrlCntr::In_ProcessTestFinish()
{
	if(m_pCurrSttTest == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,"m_pCurrSttTest == NULL");
	}

	if (m_pCurrSttTest != NULL)
	{
		m_pCurrSttTest->ReturnTestStateEvent_TestFinish(m_pCurrSttTest->m_oTestFinishedTime.dTime,
														m_pCurrSttTest->m_oTestFinishedTime.dRealTime,FALSE);
	}
}

void CSttServerTestCtrlCntr::In_Test(CSttTestBase *pTest)
{
	if (m_pOldSttTest != NULL)
	{
		delete m_pOldSttTest;
		m_pOldSttTest = NULL;
	}
	m_pOldSttTest = m_pCurrSttTest;
	m_pCurrSttTest = pTest;
	m_pCurrSttTest->StartTest();
}

void CSttServerTestCtrlCntr::In_Test()
{
	m_pCurrSttTest->StartTest();
}

void CSttServerTestCtrlCntr::In_UpdateParameter()
{
	m_pCurrSttTest->UpdateParameter();
}

void CSttServerTestCtrlCntr::In_SetParameter(CSttTestBase *pTest)
{
	if (m_pOldSttTest != NULL)
	{
		delete m_pOldSttTest;
		m_pOldSttTest = NULL;
	}

	if (m_pCurrSttTest != NULL)
	{
		m_pCurrSttTest->Stop();
	}

	m_pOldSttTest = m_pCurrSttTest;
	m_pCurrSttTest = pTest;
	m_pCurrSttTest->SetParameter();
}

void CSttServerTestCtrlCntr::In_SetParameter()
{
	m_pCurrSttTest->SetParameter();
}
