#pragma once

#include "SttSmartTestWnd.h"


class CSttSmartTestWnd_Win : public CSttSmartTestWnd
{
    DECLARE_DYNAMIC(CSttSmartTestWnd_Win)

public:
	CSttSmartTestWnd_Win();
	virtual ~CSttSmartTestWnd_Win();
	
	virtual BOOL CreateSttSmartTestWnd();

protected:
    DECLARE_MESSAGE_MAP()

};


