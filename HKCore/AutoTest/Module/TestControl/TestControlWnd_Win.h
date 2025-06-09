#pragma once

#include "TestControlWnd.h"


class CTestControlWnd_Win : public CTestControlWnd
{
    DECLARE_DYNAMIC(CTestControlWnd_Win)

public:
	CTestControlWnd_Win();
	virtual ~CTestControlWnd_Win();
	
	virtual BOOL CreateTestControlWnd();
	
protected:
    DECLARE_MESSAGE_MAP()

};


