#ifndef _PpSttIotDeviceClientWnd_h__
#define _PpSttIotDeviceClientWnd_h__

#include "../../../../Module/API/StringApi.h"

class CPpSttIotDeviceClient;

class CPpSttIotDeviceClientMsgRcv
{
public:
	virtual void OnCommCommandMsg(CPpSttIotDeviceClient *pDeviceClient, WPARAM wParam, LPARAM lParam) = NULL;
	virtual void OnEngineSystemMessage(CPpSttIotDeviceClient *pDeviceClient, WPARAM wParam, LPARAM lParam) = NULL;
	virtual void OnEngineEventMessage(CPpSttIotDeviceClient *pDeviceClient, WPARAM wParam, LPARAM lParam) = NULL;

}

//////////////////////////////////////////////////////////////////////////
//CPpSttIotDeviceClientWnd
class CPpSttIotDeviceClientWnd : public CWnd
{
public:
	CPpSttIotDeviceClientWnd();
	virtual ~CPpSttIotDeviceClientWnd();

	CPpSttIotDeviceClientMsgRcv *m_pDeviceClientMsgRcv;
  CPpSttIotDeviceClient *m_pIotDevice;

public:
	afx_msg LRESULT OnCommCommandMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEngineSystemMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEngineEventMessage(WPARAM wParam, LPARAM lParam);

};

#endif // _PpSttIotDeviceClientWnd_h__
