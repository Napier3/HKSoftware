//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//����SetTimerʱָ�����ھ��hWnd��nIDEvent��ָ����ʱ��ID��lpTimerFunc������ΪNULL��ָ��ΪTimerProc������ָ�롣
//���ַ���ʹ��TimerProc����(���ֿ��Զ�)����WM_TIMER��Ϣ������
//void CALLBACK TimerProc ( HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)����{����//����WM_TIMERѶϢ����}��
//��TimerProc�Ĳ���hwnd���ڵ���SetTimerʱָ���Ĵ��ھ����Windowsֻ��WM_TIMER��Ϣ�͸�TimerProc�������Ϣ�������ǵ���WM_TIMER��
//iTimerIDֵ�Ǽ�ʱ��ID��dwTimerֵ�����GetTickCount�����ķ���ֵ���ݵ�ֵ��������Windows�������������ĺ������� 
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

