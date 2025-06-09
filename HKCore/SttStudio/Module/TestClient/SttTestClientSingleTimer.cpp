//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CSttTestClientTimer.cpp  CSttTestClientTimer
#include "stdafx.h"

#ifdef _PSX_IDE_QT_
#include "QT/SttTestClientSingleTimer_QT.cpp"
#else
#include "VC/SttTestClientSingleTimer_VC.cpp"
#endif

#include "SttTestClientSingleTimer.h"
#include "SttTestClientBase.h"

//VOID (CALLBACK* TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
//调用SetTimer时指定窗口句柄hWnd，nIDEvent中指定计时器ID，lpTimerFunc参数不为NULL而指定为TimerProc函数的指针。
//这种方法使用TimerProc函数(名字可自定)处理WM_TIMER消息：　　
//void CALLBACK TimerProc ( HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)　　{　　//处理WM_TIMER讯息　　}　
//　TimerProc的参数hwnd是在调用SetTimer时指定的窗口句柄。Windows只把WM_TIMER消息送给TimerProc，因此消息参数总是等于WM_TIMER。
//iTimerID值是计时器ID，dwTimer值是与从GetTickCount函数的返回值相容的值。这是自Windows启动后所经过的毫秒数。 
void CALLBACK stt_test_single_client_timer_win(HWND hWnd, unsigned int wParam, unsigned int nTimerID, unsigned long dwTime)
{
	if (g_theSingleSttTestClient != NULL)
	{
		g_theSingleSttTestClient->OnTimer(nTimerID, dwTime);
	}
}

void stt_test_singleclient_timer(long nTimerID, DWORD dwTime)
{
	if (g_theSingleSttTestClient != NULL)
	{
		g_theSingleSttTestClient->OnTimer(nTimerID, dwTime);
	}
}

