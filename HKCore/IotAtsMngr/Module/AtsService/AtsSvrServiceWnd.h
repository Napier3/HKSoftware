//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrService.h  CAtsSvrService

#pragma once

#include "AtsSvrService.h"

class CAtsSvrServiceWnd : public CWnd
{
public:
	CAtsSvrServiceWnd();
	virtual ~CAtsSvrServiceWnd();

	void CreateAtsSvrServiceWnd(CAtsSvrService *pService);

protected:
	CAtsSvrService *m_pAtsService;

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnSttEngineCmdRcv(WPARAM wParam, LPARAM lParam);

};

