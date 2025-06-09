#include "stdafx.h"
#include "PpSttIotDeviceClientWnd_MFC.h"

IMPLEMENT_DYNAMIC(CPpSttIotDeviceClientWnd_MFC, CWnd)

//////////////////////////////////////////////////////////////////////////
//CPpSttIotDeviceClientWnd
CPpSttIotDeviceClientWnd_MFC::CPpSttIotDeviceClientWnd_MFC()
{
    
}

CPpSttIotDeviceClientWnd_MFC::~CPpSttIotDeviceClientWnd_MFC()
{

}

BOOL CPpSttIotDeviceClientWnd_MFC::CreateIotDeviceClientWnd()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("Iot_Device_Client_Wnd"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CPpSttIotDeviceClientWnd_MFC, CWnd)
	ON_MESSAGE(WM_ENGINE_SYSTEM_MSG, &CPpSttIotDeviceClientWnd::OnElectricTestMsg)
	ON_MESSAGE(WM_COMM_COMMAND, &CPpSttIotDeviceClientWnd::OnCommCommandMsg)
	ON_MESSAGE(WM_ENGINE_EVENT_MSG, &CPpSttIotDeviceClientWnd::OnSafetyTestFinished)
END_MESSAGE_MAP()
