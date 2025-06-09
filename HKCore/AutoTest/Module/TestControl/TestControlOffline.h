#pragma once

/*
	功能描述：离线测试控制对象
*/
#include "TestControl.h"

#define OFFLINE_TEST_STEP_TEST       0
#define OFFLINE_TEST_STEP_REPORT   1

class CTestControlOffline : public CTestControl
{
public:
	CTestControlOffline();
	virtual ~CTestControlOffline();

public:
	void SetOfflineTestStep_Test()	{	m_nOfflineTestStep = OFFLINE_TEST_STEP_TEST;	}
	void SetOfflineTestStep_Report()	{	m_nOfflineTestStep = OFFLINE_TEST_STEP_REPORT;	}
	BOOL IsOfflineTestStep_Test()	{	return m_nOfflineTestStep == OFFLINE_TEST_STEP_TEST;	}
	BOOL IsOfflineTestStep_Report()	{	return m_nOfflineTestStep == OFFLINE_TEST_STEP_REPORT;	}
	void InitOfflineTestStepByGuideBook();

protected:
	long m_nOfflineTestStep;   //离线测试的步骤  0=控制测试输出；  1=导入报告数据

	BOOL GetTestBeinEndTime(CString &strTestBeginTime, CString &strTestEndTime);
	void AddDataInterface_TestTime(CCommCmd* pItem, BOOL bReset);
	void SetTestEndTime(CGbItemBase *pItem);
public:
	virtual void InitEngineDataInterface(CCommCmd* pItem);
	virtual CReport* AddReport(CGbItemBase* pItem, long nRepeatTimes, long nTestIndex);

	//执行通讯过程
	virtual BOOL RunProcedure(const CString &bstrProcedureID, const CString &bstrDatasetPath
		, WPARAM wParam, LPARAM lParam, UINT nProcedureType, HWND hMsgRcvWnd);

	virtual long FillReportEx(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible);
	virtual long TestItemMacroTest(CMacroTest* pItem);
	virtual CReport* UpdateMacroTestReport(CMacroTest* pItem);

	virtual long FinishTestItemSysParaEdit_ProcessReport(CSysParaEdit* pItem);
	virtual long TestItemSysParaEdit_Test(CSysParaEdit* pItem);

	virtual long TestItemSafety(CSafety* pItem);
	virtual long FinishTestItemSafety(CSafety* pItem);

	virtual long ProcessFinishCommCmd(CCommCmd* pItem);
	virtual long GetDelayBeforeCmd(CCommCmd* pItem);
	virtual long GetDelayAfterCmd(CCommCmd* pItem);

	virtual BOOL WriteItemTempFile(CGbItemBase* pItem);
};
