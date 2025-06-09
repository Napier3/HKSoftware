#ifndef _PpSttIotDeviceClientWnd_QT_h__
#define _PpSttIotDeviceClientWnd_QT_h__

#include "PpSttIotDeviceClientWnd.h"

//CPpSttIotDeviceClientWnd_QT
class CPpSttIotDeviceClientWnd_QT : public CPpSttIotDeviceClientWnd
{
public:
	CPpSttIotDeviceClientWnd_QT();
	virtual ~CPpSttIotDeviceClientWnd_QT();

	virtual BOOL CreateIotDeviceClientWnd();
	
protected:
	virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
	virtual void OnWndTimer(unsigned int nIDEvent);

signals:
    void sig_OnCommCommandMsg(int wParam,int lParam);
    void sig_OnEngineSystemMessage(int wParam, int lParam);
	void sig_OnEngineEventMessage(int wParam, int lParam);

private slots:
    void slot_OnCommCommandMsg(int wParam,int lParam);
    void slot_OnEngineSystemMessage(int wParam, int lParam);
	void slot_OnEngineEventMessage(int wParam, int lParam);

};

#endif // _PpSttIotDeviceClientWnd_QT_h__
