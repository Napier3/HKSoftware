//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestClientBase.h  CSttTestClientBase

#pragma once

#include "../../../Module/OSInterface/OSInterface.h"
#include "../TestClient/SttTestClientBase.h"
//#include "SttTestClientTimer.h"

#ifdef _PSX_QT_LINUX_
#include "../../../Module/OSInterface/QT/CXCtrl_QT_CWnd.h"
#endif


void CALLBACK stt_test_single_client_timer_win(HWND hWnd, unsigned int wParam, unsigned int nTimerID, unsigned long dwTime);
void stt_test_singleclient_timer(long nTimerID, DWORD dwTime);

long stt_test_singleclient_timer_create(long nTimerLong);

void stt_test_singleclient_timer_free(long nTimerID);

void stt_test_singleclient_timer_attactclient(CSttTestClientBase *pClient);

