#include "StdAfx.h"
#include "GbScript_Engine.h"
#include "../GuideBook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern long g_nLog_TestControl_Msg;

CGuideBook* GBS_GetGuideBook(CTScriptSingleVM *pXvm)
{
	CGbItemBase *pItem = (CGbItemBase*)_CGbScriptGlobalDefine::g_pGbScriptGlobalDefine->SelectGbItem();
	ASSERT (pItem != NULL);

	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	return pGuideBook;
}

//计算时间间隔
long GBS_CalGpsPcTimeGap(CTScriptSingleVM *pXvm, const char *pszTimeID1, const char *pszTimeID2)
{
// 	CGuideBook *pGuideBook = GBS_GetGuideBook(pXvm);
// 	CString strVar1(pszTimeID1), strVar2(pszTimeID2);
// 	CScriptDataVariable *pVar1 = (CScriptDataVariable*)pGuideBook->m_oScriptDataVariables.FindByID(strVar1);
// 	CScriptDataVariable *pVar2 = (CScriptDataVariable*)pGuideBook->m_oScriptDataVariables.FindByID(strVar2);
// 
// 	if (pVar1 == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"变量[%s]不存在", strVar1);
// 		return 0;
// 	}
// 
// 	if (pVar2 == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"变量[%s]不存在", strVar2);
// 		return 0;
// 	}
// 
// 	if (! pVar1->IsTime() )
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"变量[%s]不是时间变量", strVar1);
// 		return 0;
// 	}
// 
// 	if (! pVar2->IsTime() )
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"变量[%s]不是时间变量", strVar2);
// 		return 0;
// 	}
// 
// 	CGpsPcTime *pTtm1 = pVar1->GetGpsPcTime();
// 	CGpsPcTime *pTtm2 = pVar2->GetGpsPcTime();
// 
// 	CGpsPcTimeSpan ts;
// 
// 	if (*pTtm1 > *pTtm2)
// 	{
// 		ts = *pTtm1 - *pTtm2;
// 	}
// 	else
// 	{
// 		ts = *pTtm2 - *pTtm1;
// 	}
// 
// 	delete pTtm1;
// 	delete pTtm2;
// 
// 	return ts.GetTotalMilliseconds();
	return 0;//
}

long GBS_CalTimeGap(CTScriptSingleVM *pXvm, const char *pszTime1, const char *pszTime2)
{
	CGpsPcTime tm1, tm2;

	tm1.FromString(CString(pszTime1));
	tm2.FromString(CString(pszTime2));

	CGpsPcTimeSpan ts;

	if (tm1 > tm2)
	{
		ts = tm1 - tm2;
	}
	else
	{
		ts = tm2 - tm1;
	}

	return ts.GetTotalMilliseconds();
}

long GBS_CalTimeGapCurr(CTScriptSingleVM *pXvm, const char *pszTime1)
{
	CGpsPcTime tm1, tm2;

	CString strTime1;
	strTime1 = pszTime1;
	tm1.FromString(strTime1);

	SYSTEMTIME stm;
	::GetLocalTime(&stm);
	CString strTime;
	strTime.Format(_T("%d-%d-%d %d:%d:%d.%d"), stm.wYear, stm.wMonth,stm.wDay, stm.wHour
		, stm.wMinute, stm.wSecond, stm.wMilliseconds);
	tm2.FromString(strTime);

	CGpsPcTimeSpan ts;

	if (tm1 > tm2)
	{
		ts = tm1 - tm2;
	}
	else
	{
		ts = tm2 - tm1;
	}

	long nMs = ts.GetTotalMilliseconds();

	if (g_nLog_TestControl_Msg == 1)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] - [%s] = %d ms"), strTime1.GetString(), strTime.GetString(), nMs);
	}

	return nMs;
}

//创建一个GPS的时间变量
long GBS_CreateGpsDateTime(CTScriptSingleVM *pXvm, const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs)
{
// 	PGPSTIME pTime = tm_CreateGpsTime(nYear, nMonth, nDay, nHour, nMinute, nS, nMs, nUs);
// 	CGuideBook *pGuideBook = GBS_GetGuideBook(pXvm);
// 
// 	CLogPrint::LogString(XLOGLEVEL_ERROR, L"************ CreateGpsDateTime");
// 	GBS_LogTime_GpsTime(pTime);
// 
// 	if (pGuideBook != NULL)
// 	{
// 		pGuideBook->m_oScriptDataVariables.AddScriptDataVariable(SDVT_GPSTIME, CString(pszTimeID), pTime);
// 	}

	return 0;
}

long GBS_CreateGpsTime(CTScriptSingleVM *pXvm, const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs)
{
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	return GBS_CreateGpsDateTime(pXvm, pszTimeID, tmSys.wYear, tmSys.wMonth, tmSys.wDay, nHour, nMinute, nS, nMs, nUs);
}
