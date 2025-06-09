#include "stdafx.h"
#include "SttGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "../../Module/System/TickCount32.h"
CTickCount32 *g_oTickLongLogBegin = 0;

#ifdef use_sttdebuglogwidget
//2024-9-9 lijunqing 
extern long g_sttdebuglogwidget;
#endif

void debug_enter_time_long_log()
{
#ifdef use_sttdebuglogwidget
	if (g_sttdebuglogwidget == 0)
	{
		return;
	}


	if (g_oTickLongLogBegin == 0)
	{
		g_oTickLongLogBegin = new CTickCount32();
	}

	g_oTickLongLogBegin->Enter();
#endif
}

void debug_time_long_log(char *pszText, bool bResetBegin)
{
#ifdef use_sttdebuglogwidget
	if (g_sttdebuglogwidget == 0)
	{
		return;
	}


	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s = [%d]") , pszText, g_oTickLongLogBegin->GetTickCountLong(bResetBegin));
#endif
}

void debug_time_long_log(const char *pszFileOrFunc, long nLine, bool bResetBegin)
{
#ifdef use_sttdebuglogwidget
	if (g_sttdebuglogwidget == 0)
	{
		return;
	}


	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s(%d) = [%d]") , pszFileOrFunc, nLine, g_oTickLongLogBegin->GetTickCountLong(bResetBegin));
#endif
}

void debug_time_long_log(const char *pszFileOrFunc, long nLine, char *pszText, bool bResetBegin)
{
#ifdef use_sttdebuglogwidget
	if (g_sttdebuglogwidget == 0)
	{
		return;
	}


	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s(%d)(%s) = [%d]") , pszFileOrFunc, nLine, pszText, g_oTickLongLogBegin->GetTickCountLong(bResetBegin));
#endif
}
