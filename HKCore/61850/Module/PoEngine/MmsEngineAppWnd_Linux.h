// MmsEngineAppWnd_Linux.h 
//

#pragma once

#include "MmsEngineAppWnd.h"

class CMmsEngineAppWnd_Linux : public CMmsEngineAppWnd
{
	
public: // 仅从序列化创建
	CMmsEngineAppWnd_Linux();
	virtual ~CMmsEngineAppWnd_Linux();
	
	virtual BOOL CreateWnd();

    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
    virtual void OnWndTimer(unsigned int nIDEvent);

};
