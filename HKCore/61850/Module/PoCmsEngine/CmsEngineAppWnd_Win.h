// CmsEngineAppWnd_Win.h 
//

#pragma once

#include "CmsEngineAppWnd.h"

class CCmsEngineAppWnd_Win : public CCmsEngineAppWnd
{
	DECLARE_DYNAMIC(CCmsEngineAppWnd_Win)

public: // 仅从序列化创建
	CCmsEngineAppWnd_Win();
	virtual ~CCmsEngineAppWnd_Win();
	
	virtual BOOL CreateWnd();

	DECLARE_MESSAGE_MAP()

};
