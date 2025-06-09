// MmsEngineAppWnd_Win.h 
//

#pragma once

#include "MmsEngineAppWnd.h"

class CMmsEngineAppWnd_Win : public CMmsEngineAppWnd
{
	DECLARE_DYNAMIC(CMmsEngineAppWnd_Win)

public: // 仅从序列化创建
	CMmsEngineAppWnd_Win();
	virtual ~CMmsEngineAppWnd_Win();
	
	virtual BOOL CreateWnd();

	DECLARE_MESSAGE_MAP()

};
