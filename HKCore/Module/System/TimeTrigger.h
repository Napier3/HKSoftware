// TimeTrigger.h: interface for the CTimeTrigger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(TimeTrigger_H__)
#define TimeTrigger_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TIME_TRIGGER_MODE_NONE      0
#define TIME_TRIGGER_MODE_SECOND  1

#define TIME_TRIGGER_COUNTER_NONE       0
#define TIME_TRIGGER_COUNTER_MINUTE    1

//   ==
#define TIME_TRIGGER_OPTR_E        0
//   <
#define TIME_TRIGGER_OPTR_L        1
//   >
#define TIME_TRIGGER_OPTR_LE      2
#define TIME_TRIGGER_OPTR_G       3
//   >=
#define TIME_TRIGGER_OPTR_GE     4

class CTimeTrigger  
{
public:
	CTimeTrigger();
	virtual ~CTimeTrigger();

	void AttachMsgRcvWnd(CWnd *pMsgRcvWnd, UINT nMsg);

	void SetTmTriggerNone();
	void SetTmTriggerSecond(long nSecond, DWORD dwOptr=TIME_TRIGGER_OPTR_L);
	void SetTmTriggerCounter_Minute(long nMinute);
	BOOL NeedTrigger();
// 	BOOL TimeTrigger();
	void EnterTimerTrigger();
	void StartTimerTigger();
	void StopTimerTigger();

private:
	long      m_nTmTrigger_Counter_Minute;   //时钟触发：分钟计数器
	long      m_nTmTrigger_Minute;   //时钟触发设定值
	DWORD m_dwTmTriggerMode;
	long      m_nTmTrigger_Second;
	DWORD m_dwTmTrigger_Optr;
	BOOL     m_bEnterTimerTrigger;

	CWnd *m_pMsgRcvWnd;
	UINT  m_nTimerTiggerMsg;
	BOOL m_bExitTimerTrigger;
	long   m_nOldMinute;

	BOOL TimeTrigger_Second(SYSTEMTIME &tmSys);

protected:
	static UINT TimerTriggerThread(LPVOID pParam);
	void TimerTrigger();

	static CWinThread *g_pTimerTriggerThread;

};

#endif // !defined(TimeTrigger_H__)
