#pragma once

/*
	�����������Զ����ԵĽӿ�App
*/
//#include "AtsRpc\AtsRpcServerGlobalApi.h"  //lijunqing 2022-6-25

#include "XSmartTestInterface.h"
//#include "AutoTestGlobalDefine.h"   //lijunqing 2022-6-25
#include "XSmartTestClientInterface.h"   //lijunqing 2022-6-25

//#include "../../SttStudio/Module/SttCmd/SttParas.h"//2022-2-5  lijunqingȥ��

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
	//CSttParas* GetAtsTestDefine()		{	return &m_oParas;	}//2022-2-5  lijunqingȥ��

protected:
	SmartTest::CSmartTest m_oSmartTest;
	//CSttParas m_oParas;//2022-2-5  lijunqingȥ��

//////////////////////////////////////////////////////////////////////////
//CXSmartTestClientInterface
public:
	//���·���ֵΪlong�ĺ���������ֵΪ0����ʶִ�гɹ������򷵻ط���ֵ�� //shaolei  20210512
	//Ŀǰ��һ������̨��һ��SmartTestʵ�������нӿ��е�DeviceID����ʱ������������������SmartTest�����У���Ծ���ı����豸���в���
	//long CreateTest(CSttParas *pParas);  //2022-2-5  lijunqingȥ��
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
	virtual long OpenGbrptFile(const CString &strFilePath, long nDeviceIndex=-1);  //Ĭ�ϲ��� -1 ��ʾ����̨װ��
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

 //2021-7-25  lijunqing  ��Ϊ���ص��ı����ܱȽϴ�ͨ������CString�ķ�ʽ����һ�ι�������
	//Ч����ԱȽϵͣ����Ը�Ϊ��ַ����
	//CString GetGuideBook(const CString &strDeviceID);
	virtual long GetGuideBook(const CString &strDeviceID, char **ppszGuideBookUft8);

	//strFile�������б����ļ���CDataGroup����ÿ���ļ���¼����·��
	virtual long GetReportFiles(const CString &strDeviceID, CString &strFile);

	//��ȡ���в�����Ŀ����   shaolei  20211031
	virtual long GetTotalItemsCount(const CString &strDeviceID, long &nCount);
	//��ѯ���Բ��������ò��Բ���
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
