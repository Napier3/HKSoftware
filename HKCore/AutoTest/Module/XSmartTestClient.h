#pragma once

/*
	功能描述：自动测试的接口App
*/
//#include "AtsRpc\AtsRpcServerGlobalApi.h"  //lijunqing 2022-6-25

#include "XSmartTestInterface.h"
//#include "AutoTestGlobalDefine.h"   //lijunqing 2022-6-25
#include "XSmartTestClientInterface.h"   //lijunqing 2022-6-25

//#include "../../SttStudio/Module/SttCmd/SttParas.h"//2022-2-5  lijunqing去掉

//////////////////////////////////////////////////////////////////////////
//CXSmartTestClient
#define  SMART_TEST_COM_EXEC_SUCC	0

class CXSmartTestClient : public CXSmartTestClientInterface   //lijunqing 2022-6-25
{
public:
	CXSmartTestClient();
	virtual ~CXSmartTestClient();

public:
	virtual BOOL InitXSmartTestClient();
	virtual void ExitXSmartTestClient();

	SmartTest::CSmartTest GetSmartTest();
	//CSttParas* GetAtsTestDefine()		{	return &m_oParas;	}//2022-2-5  lijunqing去掉

protected:
	SmartTest::CSmartTest m_oSmartTest;
	//CSttParas m_oParas;//2022-2-5  lijunqing去掉

//////////////////////////////////////////////////////////////////////////
//CXSmartTestClientInterface
public:
	//以下返回值为long的函数，返回值为0，标识执行成功，否则返回非零值。 //shaolei  20210512
	//目前，一个测试台起一个SmartTest实例，下列接口中的DeviceID，暂时不作处理。后续可以在SmartTest程序中，针对具体的被测设备进行操作
	//long CreateTest(CSttParas *pParas);  //2022-2-5  lijunqing去掉
	virtual long CreateTest(const CString &strTestDefine);
	virtual long BeginTest(const CString &strDeviceID);
	virtual long StopTest(const CString &strDeviceID);
	virtual long Retest(const CString &strDeviceID, const CString &strCommConfig);
	virtual long ExportRpt(const CString &strDeviceID);
	virtual long CloseTest(const CString &strDeviceID);
	virtual long ViewItemRpt(const CString &strDeviceID, long nItemIndex);
	virtual long TestAllInlegibleItems(const CString &strDeviceID);
	virtual long TestPoint(const CString &strDeviceID, const CString &strItemPath);
	virtual long TestBelow(const CString &strDeviceID, const CString &strItemPath);
	virtual long OpenGbrptFile(const CString &strFilePath, long nDeviceIndex=-1);  //默认参数 -1 表示测两台装置
	virtual CString GetAllTestItems(const CString &strDeviceID);
	virtual CString GetTestItemReports(const CString &strDeviceID);
	virtual long SetAppVisible(long nVisible);
	virtual long FinishInputData(const CString& strDeviceID, const CString& strReports);
	virtual long SetItemStateEx(const CString& strItemPath, long nSelect, long nEnable, long nShow, long nState);
	virtual long AddEventSink(const CString &strEventSinkProgID, const CString& strDeviceID);
	virtual long RemoveEventSink(const CString &strEventSinkProgID, const CString& strDeviceID);
	virtual long ClearReport(const CString &strDeviceID);
	virtual long GetReports(const CString &strDeviceID, const CString &strItemPath, char **ppszReports);
	virtual long SetReports(const CString &strDeviceID, const CString &strItemPath, const CString &strReports);
	virtual long QueryItems(const CString &strDeviceID, const CString &strItemPath, char **ppszItems);
	virtual long ConfigTest(const CString &strDeviceID, const CString &strConfig);
	virtual long QueryAtsFile(const CString &strDeviceID, const CString &strConfig);
	virtual CString GetDataset(const CString &strDatasetPath);
	virtual long SetDataset(const CString &strDatasetPath, const CString &strDataset);
	virtual long RunProcedure(const CString &strProcedureID, const CString &strParas);
	virtual long SetItemState(const CString &strParas);

 //2021-7-25  lijunqing  因为返回的文本可能比较大，通过返回CString的方式会多出一次构造析构
	//效率相对比较低，所以改为传址返回
	//CString GetGuideBook(const CString &strDeviceID);
	virtual long GetGuideBook(const CString &strDeviceID, char **ppszGuideBookUft8);

	//strFile返回所有报告文件的CDataGroup对象，每个文件记录绝对路径
	virtual long GetReportFiles(const CString &strDeviceID, CString &strFile);

	//获取所有测试项目数量   shaolei  20211031
	virtual long GetTotalItemsCount(const CString &strDeviceID, long &nCount);
	//查询测试参数、设置测试参数
	virtual long QueryTestParas(const CString &strDeviceID, CString &strTestParas);
	virtual long SetTestParas(const CString &strDeviceID, CString &strTestParas);
	virtual long AdjustMainWnd(LONG hMainParent, LONG hLogParent);
	virtual long AttatchLogWnd(unsigned long hWnd);  //shaolei 20220516
};

//////////////////////////////////////////////////////////////////////////
//
class CSmartTestEventMsg
{
public:
	CSmartTestEventMsg(const CString &strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, const CString &strItemID, const CString &strState)
	{
		m_strTestID = strTestID;
		m_nDeviceIndex = nDeviceIndex;
		m_nReportIndex = nReportIndex;
		m_nItemIndex = nItemIndex;
		m_strItemID = strItemID;
		m_strState = strState;
	}
	virtual ~CSmartTestEventMsg(){}

public:
	CString m_strTestID;
	LONG   m_nDeviceIndex;
	LONG   m_nReportIndex;
	LONG   m_nItemIndex;
	CString m_strItemID;
	CString m_strState;
};

#define  WM_SMARTTEST_EVENT_SINK   (WM_USER + 1527)

#define SMARTTEST_EVENT_OnOpenGbrptFileFailed   8
#define SMARTTEST_EVENT_OnTestCreated			7
#define SMARTTEST_EVENT_OnEngineEvent			6
#define SMARTTEST_EVENT_OnTestAppEvent			5
#define SMARTTEST_EVENT_OnExportRptEvent	4
#define SMARTTEST_EVENT_OnTestStoped				3
#define SMARTTEST_EVENT_OnTestFinished			2
#define SMARTTEST_EVENT_OnItemStateChanged	1

LONG TES_OnItemStateChanged(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState);
LONG TES_OnTestFinished(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnTestStoped(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnExportRptEvent(CWnd *pWnd, LPCTSTR strTestID, LPCTSTR strEvent, LONG nDeviceIndex, LONG nReportIndex);
LONG TES_OnTestAppEvent(CWnd *pWnd, LPCTSTR strTestID, LPCTSTR strEvent);
LONG TES_OnEngineEvent(CWnd *pWnd, LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent);
LONG TES_OnTestCreated(CWnd *pWnd, LPCTSTR strTestID);
LONG TES_OnOpenGbrptFileFailed(CWnd *pWnd, LPCTSTR strTestID);
