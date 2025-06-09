// D:\WorkPM\Source\PMTest\Module\IotPxEngineDeviceWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "IotPxEngineDeviceWnd.h"
#include "IotPxEngineDeviceBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIotPxEngineDeviceWnd
CIotPxEngineDeviceWnd::CIotPxEngineDeviceWnd()
{
	m_pIotPxEngineDevice = NULL;
	m_pTestItemRef = NULL;
}

CIotPxEngineDeviceWnd::~CIotPxEngineDeviceWnd()
{
	KillPpEngineTimer();
}


BOOL CIotPxEngineDeviceWnd::CreateIotPxEngineDeviceWnd()
{
	return TRUE;
}

void CIotPxEngineDeviceWnd::SetPpEngineTimer(UINT nIDEvent, long nTimerLong)
{
#ifndef _PSX_IDE_QT_
	SetTimer(nIDEvent, nTimerLong, NULL);
#endif
}

void CIotPxEngineDeviceWnd::SetPpEngineTimer()
{
#ifndef _PSX_IDE_QT_
	SetTimer(TIMER_PPENGINE_EXCEPTION, TIMER_PPENGINE_EXCEPTION_LONG, NULL);
	SetTimer(TIMER_PPENGINE_RTDATA, TIMER_PPENGINE_RTDATA_LONG, NULL);
#endif
}

void CIotPxEngineDeviceWnd::KillPpEngineTimer(UINT nIDEvent)
{
#ifndef _PSX_IDE_QT_
	KillTimer(nIDEvent);
#endif
}

void CIotPxEngineDeviceWnd::KillPpEngineTimer()
{
#ifndef _PSX_IDE_QT_
	if (::IsWindow(m_hWnd))
	{
		KillTimer(TIMER_PPENGINE_EXCEPTION);
		KillTimer(TIMER_PPENGINE_RTDATA);
	}
#endif
}

void CIotPxEngineDeviceWnd::OnTimer(unsigned int nIDEvent)
{
#ifndef _PSX_IDE_QT_
    CWnd::OnTimer(nIDEvent);
#endif
}

unsigned long CIotPxEngineDeviceWnd::OnProcedureEndMsg(unsigned long wParam, unsigned long lParam)
{
	if (m_pIotPxEngineDevice != NULL)
	{
		m_pIotPxEngineDevice->OnProcedureEndMsg(wParam,lParam);
	}

	return 0;
}

unsigned long CIotPxEngineDeviceWnd::OnEngineSystemMessage(unsigned long wParam, unsigned long lParam)
{
	if (m_pIotPxEngineDevice != NULL)
	{
		m_pIotPxEngineDevice->OnEngineSystemMessage(wParam,lParam);
	}

	return 0;
}

unsigned long CIotPxEngineDeviceWnd::OnEngineEventMessage(unsigned long wParam, unsigned long lParam)
{
	if (m_pIotPxEngineDevice != NULL)
	{
		m_pIotPxEngineDevice->OnEngineEventMessage(wParam,lParam);
	}

	return 0;
}

unsigned long CIotPxEngineDeviceWnd::OnMmsReportMessage(unsigned long wParam, unsigned long lParam)
{
	if (m_pIotPxEngineDevice != NULL)
	{
		m_pIotPxEngineDevice->OnMmsReportMessage(wParam,lParam);
	}

	return 0;
}
