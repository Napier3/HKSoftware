// CmsEngineAppWnd_Linux.h 
//

#pragma once

#include "CmsEngineAppWnd.h"

class CCmsEngineAppWnd_Linux : public CCmsEngineAppWnd
{
	
public: // �������л�����
	CCmsEngineAppWnd_Linux();
	virtual ~CCmsEngineAppWnd_Linux();
	
	virtual BOOL CreateWnd();

    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
    virtual void OnWndTimer(unsigned int nIDEvent);

};
