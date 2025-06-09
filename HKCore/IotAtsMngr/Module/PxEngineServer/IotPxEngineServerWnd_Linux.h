#pragma once

#include "IotPxEngineServerWnd.h"

class CIotPxEngineServerWnd_Linux : public CIotPxEngineServerWnd
{
public:
	CIotPxEngineServerWnd_Linux();
	virtual ~CIotPxEngineServerWnd_Linux();

	virtual BOOL CreateIotPxEngineServerWnd();


  virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
  virtual void OnWndTimer(unsigned int nIDEvent);

};


