//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CSttTestClientTimer.cpp  CSttTestClientTimer


#include "stdafx.h"
#include "SttTestClientTimer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttTestClientTimer *g_theSttTestClientTimer = NULL;

CSttTestClientTimer::CSttTestClientTimer()
{
	for (long nIndex=0; nIndex<=99; nIndex++)
	{
		m_dwSttTestClient[nIndex] = NULL;
	}
}

CSttTestClientTimer::~CSttTestClientTimer()
{

}

VOID CALLBACK CSttTestClientTimer::stt_test_client_timer(HWND hWnd, UINT wParam, UINT_PTR lParam, DWORD dwPara)
{
	for (long nIndex=0; nIndex<=99; nIndex++)
	{
		CSttTestClientBase* p = g_theSttTestClientTimer->m_dwSttTestClient[nIndex];

		if (p != NULL)
		{
			p->OnTimer(lParam, dwPara);
		}
	}
}

void CSttTestClientTimer::AddSttTestClientBase(CSttTestClientBase* pTestClient)
{
	for (long nIndex=0; nIndex<=99; nIndex++)
	{
		if (g_theSttTestClientTimer->m_dwSttTestClient[nIndex] == NULL)
		{
			g_theSttTestClientTimer->m_dwSttTestClient[nIndex] = pTestClient;
			break;
		}
	}
}

void CSttTestClientTimer::RemoveSttTestClientBase(CSttTestClientBase* pTestClient)
{
	for (long nIndex=0; nIndex<=99; nIndex++)
	{
		CSttTestClientBase* p = g_theSttTestClientTimer->m_dwSttTestClient[nIndex];

		p = NULL;
		delete p;
	}
}

void stt_CreateSttTestClientTimer()
{
	if (g_theSttTestClientTimer == NULL)
	{
		g_theSttTestClientTimer = new CSttTestClientTimer();
	}
}

void stt_RelaseSttTestClientTimer()
{
	if (g_theSttTestClientTimer != NULL)
	{
		delete g_theSttTestClientTimer;
		g_theSttTestClientTimer = NULL;
	}
}