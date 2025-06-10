#include "stdafx.h"
#include "SttAssistWndDynEffectBase.h"

CSttAssistWndDynEffectBase::CSttAssistWndDynEffectBase()
{
	m_pCurrWnd = NULL;
	m_bIsStoped = false;
	m_nTimeLong = 0;
	m_nTimeExec = 0;
}


CSttAssistWndDynEffectBase::~CSttAssistWndDynEffectBase()
{
	
}

void CSttAssistWndDynEffectBase::ast_Exec(long nTimeGap)
{
	if (m_nTimeLong <= 0)
	{
		return;
	}

	if (m_nTimeExec >= m_nTimeLong)
	{
		m_bIsStoped = true;
	}
	else
	{
		m_nTimeExec += nTimeGap;
	}
}

void CSttAssistWndDynEffectBase::ast_Stop()
{

}

//¶¨Ê±Æ÷º¯Êý
void CSttAssistWndDynEffectBase::ast_on_timer(const CString &strTimerID)
{
	ast_Exec(0);
}

void CSttAssistWndDynEffectBase::ast_on_timer(long nTimerID)
{
	ast_Exec(0);
}

