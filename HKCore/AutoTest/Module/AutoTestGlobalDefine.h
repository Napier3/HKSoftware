#ifndef _AutoTestGlobalDefine_h__
#define _AutoTestGlobalDefine_h__


#define REPORTFILL_PROGID_WORD		_T("WORD")
#define REPORTFILL_PROGID_WPS       _T("WPS")
#define REPORTFILL_PROGID_SYSTEM	_T("SYSTEMP")
#define REPORTFILL_PROGID_NONE		_T("NONE")
#define REPORTFILL_PROGID_XML		_T("XML")
#define REPORTFILL_PROGID_JSON		_T("JSON")
#define REPORTFILL_PROGID_HTML		_T("HTML")


#define REPORTFILL_INDEX_SYSTEM		0
#define REPORTFILL_INDEX_WORD		1
#define REPORTFILL_INDEX_WPS		2
#define REPORTFILL_INDEX_NONE		3
#define REPORTFILL_INDEX_XML		4
#define REPORTFILL_INDEX_JSON		5
#define REPORTFILL_INDEX_HTML		6

//shaolei 2023-10-08 
//启用自动测试服务时，开放的服务场景。不同的场景，对应不同的服务派生类
#define STT_ATS_SVR_SCENE_PAL    _T("pal")   //PAL：南瑞，实验验证中心

inline void gb_SetReportFillProgID(const CString &strReportFillProgID, CString &strReportFillMode)
{
	strReportFillMode = strReportFillProgID;

	if (strReportFillMode != REPORTFILL_PROGID_WORD && strReportFillMode != REPORTFILL_PROGID_WPS
		&& strReportFillMode != REPORTFILL_PROGID_SYSTEM && strReportFillMode != REPORTFILL_PROGID_NONE)
	{
		strReportFillMode = REPORTFILL_PROGID_WORD;
	}
}

inline DWORD gb_GetReportFillProgID(const CString &strReportFillProgID)
{
	if (strReportFillProgID == REPORTFILL_PROGID_WORD)
	{
		return REPORTFILL_INDEX_WORD;
	}
	
	if (strReportFillProgID == REPORTFILL_PROGID_WPS)
	{
		return REPORTFILL_INDEX_WPS;
	}


	if (strReportFillProgID == REPORTFILL_PROGID_SYSTEM)
	{
		return REPORTFILL_INDEX_SYSTEM;
	}

	return REPORTFILL_INDEX_WORD;
}

#define EngineEvent_ConnectDeviceFailed		_T("ConnectFailed")
#define EngineEvent_ConnectDeviceSuccessful	_T("ConnectSuccess")
#define EngineEvent_CommError						_T("CommError")
#define EngineEvent_CommFinish					_T("CommFinish")
#define EngineEvent_CommCmdError				_T("CommCmdError")
//2020-11-24  lijunqing
#define EngineEvent_DeviceClosed					_T("DeviceClosed")
//2023-2-1  lijunqing 
#define EngineEvent_DvmEnumFinish					_T("DvmEnumFinish")
//2023-9-12
#define EngineEvent_ID_ex_ConnectDeviceSuccessful  _T("ConnectDeviceSuccessful")
#define EngineEvent_ID_ex_ConnectDeviceFailed      _T("ConnectDeviceFailed")
//////////////////////////////////////////////////////////////////////////
//2023-2-1  lijunqing 
#define EngineEvent_ID_ConnectDeviceFailed		     1
#define EngineEvent_ID_ConnectDeviceSuccessful	 2
#define EngineEvent_ID_CommError					3
#define EngineEvent_ID_CommFinish					4
#define EngineEvent_ID_CommCmdError				5
#define EngineEvent_ID_DeviceClosed					6
#define EngineEvent_ID_DvmEnumFinish				7
#define EngineEvent_ID_Report							8
#define EngineEvent_ID_PkgSpy							9//zhouhj 2024.1.27 此处待确认zhouhj [2024.2.5号已与邵雷确认]


//////////////////////////////////////////////////////////////////////////
#define TestAppEvent_ConnectSuccess			_T("ConnectSuccess")
#define TestAppEvent_ConnectFaild				_T("ConnectFaild")
#define TestAppEvent_ConnectConfig			_T("ConnectConfig")
#define TestAppEvent_TestBegin					_T("TestBegin")
#define TestAppEvent_TestFinished				_T("TestFinished")
#define TestAppEvent_SearchPointFinished	_T("SearchPointFinished")
#define TestAppEvent_CommError				_T("CommError")
#define TestAppEvent_TestOverTime			_T("TestOverTime")
#define TestAppEvent_AppError					_T("AppError")
#define TestAppEvent_AppWarning				_T("AppWarning")
#define TestAppEvent_TestStoped             _T("TestStoped")

//测试项目的状态
//////////////////////////////////////////////////////////////////////////
//测试项目的测试状态
#define TEST_STATE_NORMAL     0  //准备测试，初始状态
#define TEST_STATE_TESTING    1  //测试中
#define TEST_STATE_ELIGIBLE    2  //合格的
#define TEST_STATE_STOPED     3  //停止测试
#define TEST_STATE_INLEGIBLE  4  //不合格
#define TEST_STATE_COUNT      5  //测试状态的个数
#define TEST_STATE_ELIGIBLEEX 6  //合格的
#define TEST_STATE_SKIP       7  //跳过的
#define TEST_STATE_ERROR      8  //测试错误

#define TEST_STATE_DESC_NORMAL     _T("NORMAL")  //准备测试，初始状态
#define TEST_STATE_DESC_TESTING    _T("TESTING")  //测试中
#define TEST_STATE_DESC_ELIGIBLE    _T("ELIGIBLE")  //合格的
#define TEST_STATE_DESC_STOPED     _T("STOPED")  //停止测试
#define TEST_STATE_DESC_INLEGIBLE  _T("INLEGIBLE")  //不合格
#define TEST_STATE_DESC_COUNT      _T("COUNT")  //测试状态的个数
#define TEST_STATE_DESC_ELIGIBLEEX _T("ELIGIBLEEX")  //合格的
#define TEST_STATE_DESC_SKIP           _T("SKIP") //跳过的
#define TEST_STATE_TEST_ERROR    _T("TEST_ERROR") //测试错误

CString Gb_GetTestStateDesc(const CString &strState);
CString Gb_GetTestStateByID(UINT nTestState);
long GB_GetTestStateByIDEx(const CString &strState);

void ats_SetReportFillProgID_Word();
void ats_SetReportFillProgID_WPS();
void ats_SetReportFillProgID_System();
void ats_SetReportFillProgID_None();

void ats_SetReportFillProgID(DWORD dwReportType);
void ats_SetReportFillProgID(const CString &strReportFillProgID);
void ats_InitReportFillProgID();

//2022-7-24  lijunqing  从CharElementTestLine.h移到此处
#define TESTLINE_ACT_STATE_NONE     -255
#define TESTLINE_ACT_STATE_ACT      1
#define TESTLINE_ACT_STATE_NOACT    0

//////////////////////////////////////////////////////////////////////////
//lijunqing 2022-7-24 from MacroCharItems.h
#define MACRO_CHAR_TEST_AXISMODE_XY       _T("x-y")
#define MACRO_CHAR_TEST_AXISMODE_RANGLE   _T("r-angle")
#define MACRO_CHAR_TEST_LINEDEF_POINT     _T("point")
#define MACRO_CHAR_TEST_LINEDEF_LINE      _T("line")

#define CharElementTestLine_ID   _T("Test")


//测试模式  2023-3-14  shaolei
#define TEST_MODE_SINGLETEST   0   //单机测试模式
#define TEST_MODE_AUTOTEST     1   //自动测试模式

#endif // _AutoTestGlobalDefine_h__

