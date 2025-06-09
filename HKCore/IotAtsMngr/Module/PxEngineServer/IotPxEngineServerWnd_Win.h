#pragma once

#include "IotPxEngineServerWnd.h"


class CIotPxEngineServerWnd_Win : public CIotPxEngineServerWnd
{
    DECLARE_DYNAMIC(CIotPxEngineServerWnd_Win)

public:
	CIotPxEngineServerWnd_Win();
	virtual ~CIotPxEngineServerWnd_Win();
	
	virtual BOOL CreateIotPxEngineServerWnd();
	
protected:
    DECLARE_MESSAGE_MAP()

	LRESULT XOnIotCmd(WPARAM wParam, LPARAM lParam);

};


