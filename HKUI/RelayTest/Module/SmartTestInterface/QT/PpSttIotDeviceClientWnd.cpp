#include "stdafx.h"
#include "PpSttIotDeviceClientWnd.h"
#include "PpSttIotEngineClientApp.h"

#include "../../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"

//////////////////////////////////////////////////////////////////////////
//CPpSttIotDeviceClientWnd
CPpSttIotDeviceClientWnd::CPpSttIotDeviceClientWnd()
{
    m_pIotDevice = NULL;

    m_pDeviceClientMsgRcv = NULL;
}

CPpSttIotDeviceClientWnd::~CPpSttIotDeviceClientWnd()
{

}

void CPpSttIotDeviceClientWnd::OnCommCommandMsg(WPARAM wParam, LPARAM lParam)
{
    m_pDeviceClientMsgRcv->OnCommCommandMsg(m_pIotDevice, wParam, lParam);
}

void CPpSttIotDeviceClientWnd::OnEngineSystemMessage(WPARAM wParam, LPARAM lParam)
{
    m_pDeviceClientMsgRcv->OnEngineSystemMessage(m_pIotDevice, wParam, lParam);
}

void CPpSttIotDeviceClientWnd::OnEngineEventMessage(WPARAM wParam, LPARAM lParam)
{
	m_pDeviceClientMsgRcv->OnEngineEventMessage(m_pIotDevice, wParam, lParam);
}
