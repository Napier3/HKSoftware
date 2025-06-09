#pragma once

#include "../../../Protocol/Module/Engine/PpGlobalDefine.h"

class CIotPxEngineServer;

#define WM_IOT_CMD_MSG    0X7178

class CIotPxEngineServerWnd : public CWnd
{
public:
	CIotPxEngineServerWnd();
	virtual ~CIotPxEngineServerWnd();
	
	virtual BOOL CreateIotPxEngineServerWnd();

public:
	CIotPxEngineServer* m_pIotPxEngineServer;

protected:
	unsigned long OnIotCmd(unsigned long wParam, unsigned long lParam);
};


