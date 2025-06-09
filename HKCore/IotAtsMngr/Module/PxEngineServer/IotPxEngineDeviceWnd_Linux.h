#pragma once

#include "IotPxEngineDeviceWnd.h"

class CIotPxEngineDeviceWnd_Linux : public CIotPxEngineDeviceWnd
{
public:
	CIotPxEngineDeviceWnd_Linux();
	virtual ~CIotPxEngineDeviceWnd_Linux();

	virtual BOOL CreateIotPxEngineDeviceWnd();


  virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
  virtual void OnWndTimer(unsigned int nIDEvent);

};


