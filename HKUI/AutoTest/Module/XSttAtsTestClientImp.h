#ifndef _CXSttAtsTestClientImp_H
#define _CXSttAtsTestClientImp_H

#include "../../SttStudio/Module/SttCmd/GuideBook/SttGuideBook.h"
#include "../../SttStudio/Module/TestClient/SttAtsTestClient.h"
#include "../../SttStudio/Module/SmartTestInterface/XSmartTestEventInterface.h"
#include "XSmartTestClientInterface.h"

//CAtsEventInterface:通过STT协议返回的数据，报文解析

class CXSttAtsTestClientImp : public CAtsEventInterface , public CXSmartTestClientInterface   //lijunqing 2022-6-26
{
public:
    CXSttAtsTestClientImp();
    virtual ~CXSttAtsTestClientImp();

	CSttGuideBook *m_pSttGuideBook;
	CXSmartTestEventInterface *m_pXSmartTestEventInterface;

//////////////////////////////////////////////////////////////////////////
//CXSmartTestClientInterface
public:
	virtual BOOL InitXSmartTestClient(const CString &strTestAppIP = _T(""));
	virtual void ExitXSmartTestClient();

	virtual long CreateTest(CExBaseList *pSttParas);
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
	virtual long OpenGbrptFile(const CString &strFilePath, const CString &strSmartTestRunMode, long nDeviceIndex=-1);  //默认参数 -1 表示测两台装置
	virtual CString GetAllTestItems(const CString &strDeviceID);
	virtual CString GetTestItemReports(const CString &strDeviceID);
	virtual long SetAppVisible(long nVisible);
	virtual long FinishInputData(const CString& strDeviceID, const CString& strReports);
	virtual long SetItemStateEx(const CString& strItemPath, long nSelect, long nEnable, long nShow, long nState);
	virtual long AddEventSink(const CString &strEventSinkProgID, const CString& strDeviceID);
	virtual long RemoveEventSink(const CString &strEventSinkProgID, const CString& strDeviceID);
	virtual long ClearReport(const CString &strDeviceID);
	virtual long GetReports(const CString &strDeviceID, const CString &strItemPath, char **ppszReports);
	virtual long GetReports(const CString &strDeviceID, const CString &strItemPath, CExBaseList *pRetSttReports);
	virtual long SetReports(const CString &strDeviceID, const CString &strItemPath, const CString &strReports);
	virtual long QueryItems(const CString &strDeviceID, const CString &strItemPath, char **ppszItems);
	virtual long ConfigTest(const CString &strDeviceID, const CString &strConfig);
	virtual long QueryAtsFile(const CString &strDeviceID, const CString &strConfig);
	virtual CString GetDataset(const CString &strDatasetPath);
	virtual long SetDataset(const CString &strDatasetPath, const CString &strDataset);
	virtual long RunProcedure(const CString &strProcedureID, const CString &strParas);
	virtual long SetItemState(const CString &strParas);
	virtual long SetItemState(CExBaseList *pSttParas);
	void SetItemState_ForDebug();

	virtual long GetGuideBook(const CString &strDeviceID, char **ppszGuideBookUft8);

	virtual long GetReportFiles(const CString &strDeviceID, CString &strFile);

	virtual long GetTotalItemsCount(const CString &strDeviceID, long &nCount);
	virtual long QueryTestParas(const CString &strDeviceID, CString &strTestParas);
	virtual long SetTestParas(const CString &strDeviceID, CString &strTestParas);
	virtual long AdjustMainWnd(LONG hMainParent, LONG hLogParent);
	virtual long AttatchLogWnd(unsigned long hWnd);  //shaolei 20220516

	//////////////以下接口，参考CSttTestCtrlCntrNative///////////
	//////////////删除了IEC、保存模板相关的部分//////////////////
public:
	void SttOpen(const CString &strTestAppCfgFile);
	CSttAtsTestClient m_oSttAtsClient;

//CAtsEventInterface
public:
	virtual long OnUpdateSyncTime(CDataGroup *pRtSyncTime);
	virtual long OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);
	virtual long OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas);
	virtual long OnTestCreated(const CString &strTestID, CSttParas *pParas);
	virtual long OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas);
	virtual long OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs) ;
	virtual long OnExportRptEvent(CSttParas *pParas) ;
	virtual long OnReTestFinished(CSttParas *pParas);
	virtual long OnTestProcess(CSttParas *pParas);

	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);

	virtual long OnConnectStateChanged(bool bState);

public:
	virtual CExBaseObject* GetGuideBook()		{	return m_pSttGuideBook;	}

	//shaolei 2023-12-14 增加形参nTestMode。取值0=单机测试；1=自动测试。
	//区别：自动测试暂停后，继续测试从暂停位置继续；单机测试暂停后，继续测试从第一个项开始；
	virtual BOOL StartTest(CDataGroup *pCurrentUIParas, long nTestMode);
	virtual BOOL StopTest();
	virtual void FillReport(CSttReports *pSttReports);
	virtual CExBaseList *GetReports();
	virtual void GetEventInfo(CExBaseList& oInfoList);
	virtual bool IsTestStarted();
	virtual bool IsTestAppConnect();
	virtual void ConnectAtsServer();

	virtual long TestItem(const CString &strItemPath);
	virtual long TestFrom(const CString &strItemPath);

	virtual void CloseTest();//关闭测试前要干的活 sf 20220318

	//2022-01-18  lijunqing
	virtual void On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas) {}
	//2022-04-18  shaolei
	virtual void On_Ats_SaveTest(CSttSysState *pSysState) {}
	virtual void On_Ats_SaveTemplate(CSttSysState *pSysState) {}
	virtual void On_Ats_CreateTest(CSttSysState *pSysState);
	virtual void On_Ats_AdjustMainWnd(CSttSysState *pSysState);
	//2022-4-13  lijunqing
	virtual void On_IecDetect(CDataGroup *pIecCb) {}
	virtual void On_Ats_QueryItem(CSttSysState *pSysState)	{	}
	//2022-06-25  shaolei
	virtual void On_Ats_ExportWordRpt(CSttSysState *pSysState) {	}

};

void stt_Start_SmartTest();


#endif // _CXSttAtsTestClientImp_H
