#include "PpSttIotEngineClientAppWnd.h"

#include "../../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "../../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#include "PpSttIotEngineClientWidget.h"

//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineClientWidgetWnd
QPpSttIotEngineClientWidgetWnd::QPpSttIotEngineClientWidgetWnd()
{
    m_pMainWidget = NULL;
    m_pIotDevice = NULL;

    connect(this,SIGNAL(sig_OnCommCommandMsg(int, int)),this,SLOT(slot_OnCommCommandMsg(int, int)));
    connect(this,SIGNAL(sig_OnEngineSystemMessage(int, int)),this,SLOT(slot_OnEngineSystemMessage(int, int)));
	connect(this,SIGNAL(sig_OnEngineEventMessage(int, int)),this,SLOT(slot_OnEngineEventMessage(int, int)));
}

QPpSttIotEngineClientWidgetWnd::~QPpSttIotEngineClientWidgetWnd()
{

}


//重载函数OnWndMsg，实现消息处理
void QPpSttIotEngineClientWidgetWnd::OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
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
//	case (WM_USER + 1118)://zhouhj ???此处需要确认实际使用的宏  2024.1.23
		emit sig_OnEngineEventMessage(wParam, lParam);
		break;

	default:
		break;
	}
}

void QPpSttIotEngineClientWidgetWnd::OnWndTimer(unsigned int nIDEvent) 
{
	
}

void QPpSttIotEngineClientWidgetWnd::slot_OnCommCommandMsg(int wParam,int lParam)
{
    m_pMainWidget->OnCommCommandMsg(m_pIotDevice, wParam, lParam);
}

void QPpSttIotEngineClientWidgetWnd::slot_OnEngineSystemMessage(int wParam, int lParam)
{
    m_pMainWidget->OnEngineSystemMessage(m_pIotDevice, wParam, lParam);
}

void QPpSttIotEngineClientWidgetWnd::slot_OnEngineEventMessage(int wParam, int lParam)
{
	m_pMainWidget->OnEngineEventMessage(m_pIotDevice, wParam, lParam);
}
