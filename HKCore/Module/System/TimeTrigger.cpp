// TimeTrigger.cpp: implementation of the CTimeTrigger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TimeTrigger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CWinThread* CTimeTrigger::g_pTimerTriggerThread = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimeTrigger::CTimeTrigger()
{
	m_dwTmTriggerMode   = TIME_TRIGGER_MODE_SECOND;
	m_nTmTrigger_Second = 10;
	m_dwTmTrigger_Optr   = TIME_TRIGGER_OPTR_L;

	m_bExitTimerTrigger = FALSE;
	g_pTimerTriggerThread = NULL;
	m_nOldMinute = 0;
	m_bEnterTimerTrigger = FALSE;
}

CTimeTrigger::~CTimeTrigger()
{
	
}

void CTimeTrigger::AttachMsgRcvWnd(CWnd *pMsgRcvWnd, UINT nMsg)
{
	m_pMsgRcvWnd = pMsgRcvWnd;
	m_nTimerTiggerMsg = nMsg;
}

void CTimeTrigger::SetTmTriggerNone()
{
	m_dwTmTriggerMode = TIME_TRIGGER_MODE_NONE;
}

void CTimeTrigger::SetTmTriggerSecond(long nSecond, DWORD dwOptr)
{
	m_nTmTrigger_Second = nSecond;
	m_dwTmTrigger_Optr = dwOptr;
	m_dwTmTriggerMode = TIME_TRIGGER_MODE_SECOND;
}

void CTimeTrigger::SetTmTriggerCounter_Minute(long nMinute)
{
	m_nTmTrigger_Minute = nMinute;
}

BOOL CTimeTrigger::NeedTrigger()
{
	return m_bEnterTimerTrigger;//(m_dwTmTriggerMode != TIME_TRIGGER_MODE_NONE);
}
// 
// BOOL CTimeTrigger::TimeTrigger()
// {
// 	switch (m_dwTmTriggerMode)
// 	{
// 	case TIME_TRIGGER_MODE_SECOND:
// 		TimeTrigger_Second();
// 		break;
// 
// 	default:
// 		break;
// 	}
// 
// 	return TRUE;
// }

void CTimeTrigger::EnterTimerTrigger()
{
	m_bEnterTimerTrigger = TRUE;
}

void CTimeTrigger::StartTimerTigger()
{
	if (g_pTimerTriggerThread != NULL)
	{
		return;
	}

	m_bExitTimerTrigger = FALSE;
	g_pTimerTriggerThread = AfxBeginThread(TimerTriggerThread, (LPVOID)this); //启动线程 
	g_pTimerTriggerThread->m_bAutoDelete = TRUE;
}

void CTimeTrigger::StopTimerTigger()
{
	m_bExitTimerTrigger = TRUE;
}

BOOL CTimeTrigger::TimeTrigger_Second(SYSTEMTIME &tmSys)
{
	switch(m_dwTmTrigger_Optr)
	{
	case TIME_TRIGGER_OPTR_L:
		return tmSys.wSecond < m_nTmTrigger_Second;

	case TIME_TRIGGER_OPTR_LE:
		return tmSys.wSecond <= m_nTmTrigger_Second;

	case TIME_TRIGGER_OPTR_G:
		return tmSys.wSecond > m_nTmTrigger_Second;

	case TIME_TRIGGER_OPTR_GE:
		return tmSys.wSecond > m_nTmTrigger_Second;

	case TIME_TRIGGER_OPTR_E:
		return tmSys.wSecond == m_nTmTrigger_Second;

	default:
		return tmSys.wSecond == m_nTmTrigger_Second;
	}
}

UINT CTimeTrigger::TimerTriggerThread(LPVOID pParam)
{
	CTimeTrigger *pTimeTrigger = (CTimeTrigger*)pParam;
	pTimeTrigger->TimerTrigger();

	pTimeTrigger->g_pTimerTriggerThread = NULL;
	return 0;
}

void CTimeTrigger::TimerTrigger()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("------------------TimerTrigger Begin"));

	m_nTmTrigger_Counter_Minute = 0;
	ASSERT(m_nTmTrigger_Minute > 0);
	BOOL bFirst = TRUE;

	SYSTEMTIME tmSys;
	::GetSystemTime(&tmSys);
	m_nOldMinute = tmSys.wMinute;

	while (TRUE)
	{
		if (m_bExitTimerTrigger)
		{
			break;
		}

		::GetSystemTime(&tmSys);

		//分钟计数
		if (m_nOldMinute != tmSys.wMinute)
		{
			if (bFirst)
			{
				bFirst = FALSE;
			}
			else
			{
				m_nTmTrigger_Counter_Minute++;
			}

			m_nOldMinute = tmSys.wMinute;
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("------------------TimerTrigger Minute Counter=%d"), m_nTmTrigger_Counter_Minute);
		}

		//分钟计数判断
		if (m_nTmTrigger_Counter_Minute >= m_nTmTrigger_Minute)
		{
			if (TimeTrigger_Second(tmSys))
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("------------------TimerTrigger Message Post"));
				m_pMsgRcvWnd->PostMessage(m_nTimerTiggerMsg, 0, 0);
				m_nTmTrigger_Counter_Minute = 0;
				m_bEnterTimerTrigger = FALSE;
			}
		}

		Sleep(500);
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("------------------TimerTrigger Finish"));

}

