#include "stdafx.h"
#include "PpSttIotDeviceClientWnd_QT.h"

IMPLEMENT_DYNAMIC(CPpSttIotDeviceClientWnd_QT, CWnd)

//////////////////////////////////////////////////////////////////////////
//CPpSttIotDeviceClientWnd
CPpSttIotDeviceClientWnd_QT::CPpSttIotDeviceClientWnd_QT()
{
	connect(this,SIGNAL(sig_OnCommCommandMsg(int, int)),this,SLOT(slot_OnCommCommandMsg(int, int)));
	connect(this,SIGNAL(sig_OnEngineSystemMessage(int, int)),this,SLOT(slot_OnEngineSystemMessage(int, int)));
	connect(this,SIGNAL(sig_OnEngineEventMessage(int, int)),this,SLOT(slot_OnEngineEventMessage(int, int)));
}

CPpSttIotDeviceClientWnd_QT::~CPpSttIotDeviceClientWnd_QT()
{

}

BOOL CPpSttIotDeviceClientWnd_QT::CreateIotDeviceClientWnd()
{
	CreateEx(0, AfxRegisterWndClass(0), _T("Iot_Device_Client_Wnd"), WS_OVERLAPPED, CRect(0,0,0,0), NULL, NULL);

	return TRUE;
}



//重载函数OnWndMsg，实现消息处理
void CPpSttIotDeviceClientWnd_QT::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	switch (nMsgID)
	{
	case WM_ENGINE_SYSTEM_MSG:
		emit sig_OnEngineSystemMessage(wParam, lParam);
		break;

	case WM_COMM_COMMAND:
		emit sig_OnCommCommandMsg(wParam, lParam);
		break;

	case WM_ENGINE_EVENT_MSG:
		emit sig_OnEngineEventMessage(wParam, lParam);
		break;

	default:
		break;
	}
}

void CPpSttIotDeviceClientWnd_QT::OnWndTimer(unsigned int nIDEvent) 
{
	
}



void CPpSttIotDeviceClientWnd_QT::slot_OnCommCommandMsg(int wParam,int lParam)
{
    OnCommCommandMsg(wParam, lParam);
}

void CPpSttIotDeviceClientWnd_QT::slot_OnEngineSystemMessage(int wParam, int lParam)
{
    OnEngineSystemMessage(wParam, lParam);
}

void CPpSttIotDeviceClientWnd_QT::slot_OnEngineEventMessage(int wParam, int lParam)
{
	OnEngineEventMessage(wParam, lParam);
}
