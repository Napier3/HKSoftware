//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

