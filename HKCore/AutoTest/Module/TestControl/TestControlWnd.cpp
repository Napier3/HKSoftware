// D:\WorkPM\Source\PMTest\Module\TestControlWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "TestControlWnd.h"
#include "TestControlBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestControlWnd
CTestControlWnd::CTestControlWnd()
{
	m_bTIMER_TEST_CTRL_MACROFINISH = FALSE;
	m_bTIMER_TEST_FOR_APPEXCEPTION = FALSE;
}

CTestControlWnd::~CTestControlWnd()
{
}


// CTestControlWnd 消息处理程序
void CTestControlWnd::Gbs_SetTmTriggerCounter_Minute(long nMinute)
{
#ifndef _PSX_IDE_QT_
    m_oTimeTrgger.SetTmTriggerCounter_Minute(nMinute);
#endif
}

void CTestControlWnd::Gbs_SetTmTriggerSecond(long nSecond, long nOptr)
{
#ifndef _PSX_IDE_QT_
    m_oTimeTrgger.SetTmTriggerSecond(nSecond, nOptr);
#endif
}

void CTestControlWnd::Gbs_StartTmTrigger()
{
#ifndef _PSX_IDE_QT_
    m_oTimeTrgger.AttachMsgRcvWnd(this, WM_TIMER_TRIGGER);
	m_oTimeTrgger.StartTimerTigger();
#endif
}

void CTestControlWnd::Gbs_EnterTmTrigger()
{
#ifndef _PSX_IDE_QT_
    m_oTimeTrgger.EnterTimerTrigger();
#endif
}

void CTestControlWnd::Gbs_StopTmTrigger()
{
#ifndef _PSX_IDE_QT_
    m_oTimeTrgger.StopTimerTigger();
#endif
}

LRESULT CTestControlWnd::OnElectricTestMsg(WPARAM wParam, LPARAM lParam)
{
    //互斥量全部注释  20201213
    #ifndef _PSX_QT_LINUX_
  //  CAutoSimpleLock oLock(CTestControlBase::m_oTestCriticSection);
    #endif

	KillTimer(TIMER_TEST_CTRL_MACROFINISH);
	m_bTIMER_TEST_CTRL_MACROFINISH = FALSE;

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TestControlWnd::OnElectricTestMsg(%d, %d)"), wParam, lParam);
	return m_pTestControl->OnElectricTestMsg(wParam,lParam);
}

LRESULT CTestControlWnd::OnCommCommandMsg(WPARAM wParam, LPARAM lParam)
{
     //互斥量全部注释  20201213
   // CAutoSimpleLock oLock(CTestControlBase::m_oTestCriticSection);

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TestControlWnd::OnCommCommandMsg:%s "), m_pTestControl->m_strName);
	return m_pTestControl->OnCommCommandMsg(wParam,lParam);
}

LRESULT CTestControlWnd::OnSafetyTestFinished(WPARAM wParam, LPARAM lParam)
{
	//CLogPrint::LogString(XLOGLEVEL_TRACE, L"TestControlWnd::OnSafetyTestFinished");
	return m_pTestControl->OnSafetyTestFinished(wParam,lParam);
}

LRESULT CTestControlWnd::OnSysParaEditTestFinished(WPARAM wParam, LPARAM lParam)
{
	//CLogPrint::LogString(XLOGLEVEL_TRACE, L"TestControlWnd::OnSysParaEditTestFinished");

	return m_pTestControl->OnSysParaEditTestFinished(wParam,lParam);
}

LRESULT CTestControlWnd::OnCommCmdMamualTestFinished(WPARAM wParam, LPARAM lParam)
{
	//CLogPrint::LogString(XLOGLEVEL_TRACE, L"TestControlWnd::OnCommCmdMamualTestFinished");

	return m_pTestControl->OnCommCmdMamualTestFinished(wParam,lParam);
}

BOOL CTestControlWnd::CreateTestControlWnd()
{
#ifndef _PSX_QT_LINUX_
	//2016-12-16  屏蔽测试仪异常定时判断
	SetTimer(TIMER_TEST_CTRL_EXCEPTION, TIMER_TEST_CTRL_EXCEPTION_LONG, NULL);
#endif

	return TRUE;
}

// #define TIMER_BEFORE_CMM_CMD   4
// #define TIMER_AFTER_CMM_CMD    5

void CTestControlWnd::OnTimer(unsigned int nIDEvent)
{
     //互斥量全部注释  20201213
    //CAutoSimpleLock oLock(CTestControlBase::m_oTestCriticSection);
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"TestControlWnd::OnTimer(%d)", nIDEvent);
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (TIMER_DELAY_BEFORE_CMM_CMD == nIDEvent)
	{
		KillTimer(TIMER_DELAY_BEFORE_CMM_CMD);
		m_pTestControl->ExcuteCommCmdOnDelayBeforeFinish((CCommCmd*)m_pTestItemRef);
	}
	else if (TIMER_DELAY_AFTER_CMM_CMD == nIDEvent)
	{
		KillTimer(TIMER_DELAY_AFTER_CMM_CMD);
		m_pTestControl->ExcuteCommCmdOnDelayAfterFinish((CCommCmd*)m_pTestItemRef);
	}
	else if (TIMER_DELAY_CMM_CMD_ITEMSEXPR == nIDEvent)
	{
		KillTimer(TIMER_DELAY_CMM_CMD_ITEMSEXPR);
		m_pTestControl->ExcuteCommCmdOnDelayBeforeFinish((CCommCmd*)m_pTestItemRef);
	}
	else if (TIMER_TEST_FOR_OVERTIME == nIDEvent)
	{
		KillTimer(TIMER_TEST_FOR_OVERTIME);
		m_pTestControl->TestOverTimerItem();
	}
	else if (TIMER_TEST_CTRL_EXCEPTION == nIDEvent)
	{
		m_pTestControl->IsMacroTCtrlException();
	}
	else if (TIMER_RETRY_CMM_CMD == nIDEvent)
	{
		KillTimer(TIMER_RETRY_CMM_CMD);
		m_pTestControl->TestItemCommCmd((CCommCmd*)m_pTestItemRef);
	}
	else if (TIMER_TEST_CTRL_MACROFINISH == nIDEvent)
	{
		KillTimer(TIMER_TEST_CTRL_MACROFINISH);

		if (m_bTIMER_TEST_CTRL_MACROFINISH )
		{
			//if (g_nLog_TestControl_Msg == 1)
			{
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug CTestControlWnd::OnTimer(TIMER_TEST_CTRL_MACROFINISH) ==>> OnElectricTestMsg  -->m_bTestStarted=false"));
			}

			m_bTIMER_TEST_CTRL_MACROFINISH = FALSE;
			m_pTestControl->m_pMacroTestInterface->m_bTestStarted = FALSE;
			OnElectricTestMsg(MTMSG_TestFinished, MTMSG_TestFinished);
		}
	}
	else if (TIMER_PPENGINE_EXCEPTION == nIDEvent)
	{
		m_pTestControl->OnPpEngineExceptionTimer();
		KillTimer(TIMER_PPENGINE_EXCEPTION);
	}
	else if (TIMER_TEST_FOR_APPEXCEPTION == nIDEvent)
	{
		KillTimer(TIMER_TEST_FOR_APPEXCEPTION);
		m_pTestControl->TestFrom((CGbItemBase *)m_pTestItemRef);
    }
    else if (TIMER_EXEC_SAFETY_ITEM == nIDEvent)
    {
        KillTimer(TIMER_EXEC_SAFETY_ITEM);
        PostMessage(WM_SAFETY_TEST_FINISHED, (unsigned long)m_pTestItemRef, 1);
    }

#ifndef _PSX_IDE_QT_
    CWnd::OnTimer(nIDEvent);
#endif
}

void CTestControlWnd::Set_TIMER_TEST_CTRL_MACROFINISH()
{
	m_bTIMER_TEST_CTRL_MACROFINISH = TRUE;
	SetTimer(TIMER_TEST_CTRL_MACROFINISH, TIMER_TEST_CTRL_MACROFINISH_LONG, NULL);
}

void CTestControlWnd::SetPpEngineTimer()
{
	SetTimer(TIMER_PPENGINE_EXCEPTION, TIMER_PPENGINE_EXCEPTION_LONG, NULL);
}

void CTestControlWnd::KillPpEngineTimer()
{
	KillTimer(TIMER_PPENGINE_EXCEPTION);
}

void CTestControlWnd::StopTest()
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T(">>>>>>>>>>>>>>>>>>CTestControlWnd::StopTest---------------1"));
	KillTimer(TIMER_DELAY_BEFORE_CMM_CMD);
	KillTimer(TIMER_DELAY_AFTER_CMM_CMD);
	KillTimer(TIMER_TEST_FOR_OVERTIME);
	KillTimer(TIMER_TEST_CTRL_EXCEPTION);
	KillTimer(TIMER_PPENGINE_EXCEPTION);
	KillTimer(TIMER_TEST_FOR_APPEXCEPTION);
	KillTimer(TIMER_TEST_CTRL_MACROFINISH);

	KillPpEngineTimer();

#ifndef _PSX_IDE_QT_
    m_oTimeTrgger.StopTimerTigger();
#endif
}

LRESULT CTestControlWnd::OnManualTestMsg(WPARAM wParam, LPARAM lParam)
{
	return m_pTestControl->OnManualTestMsg(wParam,lParam);
}

DWORD g_dwEngineSystemMessageTick = 0;
LRESULT CTestControlWnd::OnEngineSystemMessage(WPARAM wParam, LPARAM lParam)
{
     //互斥量全部注释  20201213
    //CAutoSimpleLock oLock(CTestControlBase::m_oTestCriticSection);
	DWORD dwCurr = ::GetTickCount();

	//if (dwCurr - g_dwEngineSystemMessageTick > 30000)
	{
		m_pTestControl->OnEngineSystemMessage(wParam,lParam);
	}

	g_dwEngineSystemMessageTick = dwCurr;

	return 0;
}

LRESULT CTestControlWnd::OnEngineEventMessage(WPARAM wParam, LPARAM lParam)
{
     //互斥量全部注释  20201213
    //CAutoSimpleLock oLock(CTestControlBase::m_oTestCriticSection);
	DWORD dwCurr = ::GetTickCount();

	//if (dwCurr - g_dwEngineSystemMessageTick > 30000)
	{
		//m_pTestControl->OnEngineEventMessage(wParam,lParam);
	}

	g_dwEngineSystemMessageTick = dwCurr;

	return 0;
}

LRESULT CTestControlWnd::OnTimerTrigger(WPARAM wParam, LPARAM lParam)
{
	m_pTestControl->ExcuteCommCmdOnDelayBeforeFinish((CCommCmd*)m_pTestItemRef);

	return 0;
}
