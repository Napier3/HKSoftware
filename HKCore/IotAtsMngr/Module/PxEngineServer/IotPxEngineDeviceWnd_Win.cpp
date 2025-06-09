// D:\WorkPM\Source\PMTest\Module\IotPxEngineDeviceWnd_Win.cpp : 实现文件
//

#include "stdafx.h"
#include "IotPxEngineDeviceWnd_Win.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIotPxEngineDeviceWnd_Win
IMPLEMENT_DYNAMIC(CIotPxEngineDeviceWnd_Win, CWnd)

CIotPxEngineDeviceWnd_Win::CIotPxEngineDeviceWnd_Win()
{

}

CIotPxEngineDeviceWnd_Win::~CIotPxEngineDeviceWnd_Win()
{
}

BOOL CIotPxEngineDeviceWnd_Win::CreateIotPxEngineDeviceWnd()
{
#ifndef _PSX_QT_LINUX_
	CreateEx(0, AfxRegisterWndClass(0), _T("_Test_Ctrl_Wnd_"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);
#endif

	return CIotPxEngineDeviceWnd::CreateIotPxEngineDeviceWnd();
}

BEGIN_MESSAGE_MAP(CIotPxEngineDeviceWnd_Win, CWnd)
	ON_MESSAGE(WM_PROCEDURE_END_MSG, &CIotPxEngineDeviceWnd_Win::XOnProcedureEndMsg)
	ON_WM_TIMER()
	ON_MESSAGE(WM_SYSTEM_MSG, &CIotPxEngineDeviceWnd_Win::XOnEngineSystemMessage)
	ON_MESSAGE(WM_EVENT_MSG, &CIotPxEngineDeviceWnd_Win::XOnEngineEventMessage)
	ON_MESSAGE(WM_MMS_REPORT_MSG, &CIotPxEngineDeviceWnd_Win::XOnMmsReportMessage)
END_MESSAGE_MAP()

LRESULT CIotPxEngineDeviceWnd_Win::XOnProcedureEndMsg(WPARAM wParam, LPARAM lParam)
{
	return OnProcedureEndMsg(wParam, lParam);
}

LRESULT CIotPxEngineDeviceWnd_Win::XOnEngineSystemMessage(WPARAM wPara,LPARAM lPara)
{
	return OnEngineSystemMessage(wPara, lPara);
}

LRESULT CIotPxEngineDeviceWnd_Win::XOnEngineEventMessage(WPARAM wPara,LPARAM lPara)
{
	return OnEngineEventMessage(wPara, lPara);
}

LRESULT CIotPxEngineDeviceWnd_Win::XOnMmsReportMessage(WPARAM wPara,LPARAM lPara)
{
	return OnMmsReportMessage(wPara, lPara);
}

void CIotPxEngineDeviceWnd_Win::OnTimer(unsigned int nIDEvent)
{
	if (nIDEvent == TIMER_PPENGINE_RTDATA)
	{
		if (m_pIotPxEngineDevice != NULL)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR, _T("+++OnTimer_RTDATA+++"));
			m_pIotPxEngineDevice->XOnEngineTimer_RTDATA();
		}
	}

	CWnd::OnTimer(nIDEvent);
}