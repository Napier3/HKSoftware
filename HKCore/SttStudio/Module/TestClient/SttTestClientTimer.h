//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestClientBase.h  CSttTestClientBase

#pragma once

#include "SttTestClientBase.h"

class CSttTestClientTimer
{
public:
	CSttTestClientTimer();
	virtual ~CSttTestClientTimer();
	
	CSttTestClientBase* m_dwSttTestClient[100];

	static VOID CALLBACK stt_test_client_timer(HWND hWnd, UINT wParam, UINT_PTR lParam, DWORD dwPara);

	static void AddSttTestClientBase(CSttTestClientBase* pTestClient);
	static void RemoveSttTestClientBase(CSttTestClientBase* pTestClient);

	long stt_test_timer_create(long nTimerLong)
	{
		return ::SetTimer(NULL, 0, nTimerLong, stt_test_client_timer);
	}

	void stt_test_timer_free(long nTimerID)
	{
		::KillTimer(NULL, nTimerID);
	}



};

extern CSttTestClientTimer *g_theSttTestClientTimer;
void stt_CreateSttTestClientTimer();
void stt_RelaseSttTestClientTimer();
