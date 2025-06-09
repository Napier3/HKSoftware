#include "stdafx.h"
#include "AutoTestGlobalDefine.h"
#include "TCtrlCntrConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString g_strReportFillProgID = REPORTFILL_PROGID_WORD;


CString Gb_GetTestStateDesc(const CString &strState)
{
	if (strState == TEST_STATE_DESC_NORMAL)
	{
		return _T("未测试");
	}
	else if (strState == TEST_STATE_DESC_TESTING) 
	{
		return _T("测试中");
	}
	else if (strState == TEST_STATE_DESC_ELIGIBLE)
	{
		return _T("合格");
	}
	else if (strState == TEST_STATE_DESC_STOPED) 
	{
		return _T("停止测试");
	}
	else if (strState == TEST_STATE_DESC_INLEGIBLE) 
	{
		return _T("不合格");
	}
	else if (strState == TEST_STATE_DESC_ELIGIBLEEX) 
	{
		return _T("合格");
	}
	else if (strState == TEST_STATE_DESC_SKIP) 
	{
		return _T("跳过");
	}
	else
	{
		return _T("未测试");
	}
}


CString Gb_GetTestStateByID(UINT nTestState)
{
	switch (nTestState)
	{
	case TEST_STATE_NORMAL://     0  //准备测试，初始状态
		return TEST_STATE_DESC_NORMAL;
	case TEST_STATE_TESTING://    1  //测试中
		return TEST_STATE_DESC_TESTING;
	case TEST_STATE_ELIGIBLE://    2  //合格的
		return TEST_STATE_DESC_ELIGIBLE;
	case TEST_STATE_STOPED://     3  //停止测试
		return TEST_STATE_DESC_STOPED;
	case TEST_STATE_INLEGIBLE://  4  //不合格
		return TEST_STATE_DESC_INLEGIBLE;
	case TEST_STATE_COUNT://      5  //测试状态的个数
		return TEST_STATE_DESC_COUNT;
	case TEST_STATE_ELIGIBLEEX:// 6  //合格的
		return TEST_STATE_DESC_ELIGIBLEEX;
	case TEST_STATE_SKIP://       7  //跳过的
		return TEST_STATE_DESC_SKIP;
	default:
		return TEST_STATE_DESC_NORMAL;
	}
}

long GB_GetTestStateByIDEx(const CString &strState)
{
	long nRet = 0;

	if (strState == TEST_STATE_DESC_NORMAL)
	{
		nRet = TEST_STATE_NORMAL;
	}
	else if (strState == TEST_STATE_DESC_TESTING) 
	{
		nRet = TEST_STATE_TESTING;
	}
	else if (strState == TEST_STATE_DESC_ELIGIBLE)
	{
		nRet = TEST_STATE_ELIGIBLE;
	}
	else if (strState == TEST_STATE_DESC_STOPED) 
	{
		nRet = TEST_STATE_STOPED;
	}
	else if (strState == TEST_STATE_DESC_INLEGIBLE) 
	{
		nRet = TEST_STATE_INLEGIBLE;
	}
	else if (strState == TEST_STATE_DESC_ELIGIBLEEX) 
	{
		nRet = TEST_STATE_ELIGIBLE;
	}
	else if (strState == TEST_STATE_DESC_SKIP) 
	{
		nRet = TEST_STATE_SKIP;
	}
	else if (strState == TEST_STATE_TEST_ERROR) 
	{
		nRet = TEST_STATE_ERROR;
	}

	return nRet;
}


void ats_SetReportFillProgID_Word()
{
	g_strReportFillProgID = REPORTFILL_PROGID_WORD;
}

void ats_SetReportFillProgID_WPS()
{
	g_strReportFillProgID = REPORTFILL_PROGID_WPS;
}

void ats_SetReportFillProgID_System()
{
	g_strReportFillProgID = REPORTFILL_PROGID_SYSTEM;
}

void ats_SetReportFillProgID_None()
{
	g_strReportFillProgID = REPORTFILL_PROGID_NONE;
}

void ats_SetReportFillProgID(DWORD dwReportType)
{
	if (dwReportType == REPORTFILL_INDEX_WORD)
	{
		ats_SetReportFillProgID_Word();
	}
	else if (dwReportType == REPORTFILL_INDEX_SYSTEM)
	{
		ats_SetReportFillProgID_System();
	}
	else if (dwReportType == REPORTFILL_INDEX_WPS)
	{
		ats_SetReportFillProgID_WPS();
	}
	else
	{
		ats_SetReportFillProgID_None();
	}
}

void ats_SetReportFillProgID(const CString &strReportFillProgID)
{
	gb_SetReportFillProgID(strReportFillProgID, g_strReportFillProgID);
}

void ats_InitReportFillProgID()
{
//2020-03-09  lijq PpTestTool 编译问题，没有用到这个部分，所以去掉
#ifndef _not_use_CTCtrlCntrConfig
	ats_SetReportFillProgID(CTCtrlCntrConfig::GetReportMode());
#endif
}
