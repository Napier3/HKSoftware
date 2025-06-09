#ifndef _PpSttIotEngineClientWidgetWnd_h__
#define _PpSttIotEngineClientWidgetWnd_h__

#include "../../../../Module/API/StringApi.h"

#include "../PpSttIotEngineClientApp.h"

class QPpSttIotEngineClientWidget;

//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineClientWidgetWnd
class QPpSttIotEngineClientWidgetWnd : public CWnd
{
    Q_OBJECT

public:
	QPpSttIotEngineClientWidgetWnd();
	virtual ~QPpSttIotEngineClientWidgetWnd();

    QPpSttIotEngineClientWidget *m_pMainWidget;
    CPpSttIotDeviceClient *m_pIotDevice;

public://CWnd
	//重载函数OnWndMsg，实现消息处理
	virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	virtual void OnWndTimer(unsigned int nIDEvent) ;

signals:
    void sig_OnCommCommandMsg(int wParam,int lParam);
    void sig_OnEngineSystemMessage(int wParam, int lParam);
	void sig_OnEngineEventMessage(int wParam, int lParam);

private slots:
    void slot_OnCommCommandMsg(int wParam,int lParam);
    void slot_OnEngineSystemMessage(int wParam, int lParam);
	void slot_OnEngineEventMessage(int wParam, int lParam);

};

#endif // _PpSttIotEngineClientWidgetWnd_h__
