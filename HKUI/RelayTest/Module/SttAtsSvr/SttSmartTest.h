#pragma once

#include "../Engine/SttTestEngineServerBase.h"
#include "../Engine/SttNativeClientTestEngine.h"
#include "../SmartTestInterface/SttSmartTestSvrInterface.h"

#include"../../../Protocol/Module/Engine/PpEngineBaseApp.h"
#include"../../../Protocol/Module/PxiEngine/PxiEngine.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"

#include "../../../AutoTest/Module/TestControl/TestControlBase.h"
#include "../../../AutoTest/Module/TCtrlCntrWorkSpace.h"

#include "../../../AutoTest/Module/GbItemsGen/SttGuideBookGenServer.h"
#include "../SmartTestInterface/VmSttMacroTest.h"

#define CREATE_TEST_CREATE_ERROR                   0
#define CREATE_TEST_CREATE_NEW                        1
#define CREATE_TEST_CURR_EXIST_SAME             2
#define CREATE_TEST_CURR_EXIST_NOT_SAME  3

class CSttSmartTest : public CTCtrlMsgRcvInterface, public CSttSmartTestSvrInterface
{
public:
    CSttSmartTest();
    virtual ~CSttSmartTest();

	static long g_nSttSmartTestRef;
	static CSttSmartTest* g_pSttSmartTest;
    //static CSttSmartTest* Create();
    //static void Release();

public:
	BOOL m_bTestCreated;
	BOOL m_bPpEngineReleased;
    BOOL m_bFirstInit;  //是否是第一次初始化。
    BOOL m_bIsAtsLib; //是否使用AtsLib

    void FreeTestControl(BOOL bResetTestControl = FALSE);
	void FreeTestControlEx(BOOL bDelete=TRUE);
	void StartTestAfterCreate();
    long BeforeCreateTest(const CString &strGbXmlFile, const CString &strTestProjectName);
    BOOL IsNowTesting();
    long UpdateParameter(CDataGroup *pParas);
	void SetTestControl(CTestControlBase *pTestControl)	{	m_pTestControl = pTestControl;	}
	BOOL IsInternational();

protected:
    CTestControlBase *m_pTestControl;
	CWnd *m_pSttMainFrame;   //自动测试主窗口，用于创建自动测试任务界面，并处理CreateTest和CloseTest
	long m_nStartTestAfterCreate;  //创建测试后，立即开始自动测试

public:
	void SetStartTestAfterCreate(long nVal)		{	m_nStartTestAfterCreate = nVal;	}
	CWnd* GetTestControlMainWnd()	{	return m_pSttMainFrame;	}
    void InitTestControlMainWnd(CWnd *pWnd);
	void InitTestControl(bool bCreate);
	void ConnectSttServer_WhenInit();//初始化时，连接19814服务
	void CreateSmartTestWnd();
	CVmSttMacroTest* GetMacroTestInterface(const CString &strType=_T("Relay"), const CString &strProgID=_T("SttTestEngine"));
    CTestControlBase* GetTestControl();
    CGuideBook* GetGuideBook();
	CDvmDataset* GetGlobalDatas();
	CExBaseList* GetSysPara();
    BOOL IsTestCreated();
    CString GetProjectName();
	void GetReadDeviceParameter(CSttParas *pParas);
	virtual CString ValidFileName(const CString &strPath, const CString &strFileName, const CString &strProfix);

public:
    //CTCtrlMsgRcvInterface
    virtual long OnException(long nError, const CString &strError, CExBaseObject *pTestControl);
    virtual long OnConnectSuccess(CExBaseObject *pTestControl);
    virtual long OnConnectFailed(CExBaseObject *pTestControl);
    virtual long OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop=TRUE);
    virtual long OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj);
    virtual long OnTestBegin(CExBaseObject *pTestControl);
    virtual long OnStopTest(long nType, CExBaseObject *pTestControl);
    virtual void OnTestItemCount(long nCount, CExBaseObject *pTestControl);
    virtual long OnUpdateMeasure(long nData, CExBaseObject *pTestControl);
    virtual BOOL IsRunning(long nType, CExBaseObject *pTestControl);
    virtual long HideAllTestItemUI(long nData, CExBaseObject *pTestControl);
    virtual HWND GetFrameHwnd();
    virtual void ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate=TRUE, BOOL bShow=TRUE);
    virtual void ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow=TRUE);
    virtual void EditItemPara(CExBaseObject *pGbItem);
    virtual void LocateItemReport(CExBaseObject *pGbItem);
	virtual void OnExportRptEvent(CExBaseObject *pTestControl, const CString &strEventID);

public:
    //CSttSmartTestSvrInterface
    virtual long Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

    //2021-11-30  lijunqing
    virtual long Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_QueryItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_QueryTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_SetTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_GenerateTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_GenerateItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_GenerateMacroTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SetItemPara(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_ManualTrigger(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SaveTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SaveTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_ExportWordRpt(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_OpenTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_OpenGbrptFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_AdjustMainWnd(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_UpdateItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual CString Ats_QueryItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_AdjustReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_ClearReportsRslts(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_ConfigDevice(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
	long Post_Ats_CreateTest(CSttAtsCmd *pAtsCmd);  //2023-8-31 lijunqing 发送自动测试创建消息给主线程，创建测试，自动测试主线程调用 On_Ats_CreateTest
	long On_Ats_CreateTest(CSttAtsCmd *pAtsCmd);   //2023-8-31 lijunqing 执行自动测试创建，被主线程消息函数调用
 	long Post_Ats_ExportReport(CSttAtsCmd *pAtsCmd);  //2023-8-31 lijunqing 发送自动测试创建消息给主线程，创建测试，自动测试主线程调用 On_Ats_CreateTest
	virtual long Pre_Ats_ExportReport(CSttAtsCmd *pAtsCmd);   //2023-8-31 lijunqing 执行自动测试创建，被主线程消息函数调用
	virtual long Pre_Ats_ExportReport_single(CSttAtsCmd *pAtsCmd);  
	virtual long Pre_Ats_ExportReport_RptFiles(CTestControlBase *pTestControl, CDataGroup *pRptFiles);  
	virtual long Pre_Ats_ExportReport_RptFile(CGuideBook *pGuideBook, CDataGroup *pRptFile);  
	virtual long Pre_Ats_ExportReport_docs(CSttAtsCmd *pAtsCmd);  
	virtual long Pre_Ats_ExportReport_gbrpts(CSttAtsCmd *pAtsCmd);  

	virtual long Ats_CreateTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_CreateTest_MdvMgrpSpo(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StartTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StopTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_CloseTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestFrom(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestAllFailedItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetItemReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetReportFile(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetSystemState(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_FinishInputData(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_SetItemState(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);

    //2021-11-30  lijunqing
    virtual long Ats_InputData(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_ExportReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_SetItemsReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_QueryItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_ConfigTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_QueryTestParas(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_SetTestParas(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_GenerateTemplate(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_GenerateItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_GenerateMacroTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SetItemPara(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_SetItemPara_SystemConfig(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
    virtual long Ats_ManualTrigger(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SaveTemplate(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SaveTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_ExportWordRpt(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_OpenTemplate(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_OpenGbrptFile(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_AdjustMainWnd(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_UpdateItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual CString Ats_QueryItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_AdjustReport(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_ClearReportsRslts(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_ConfigDevice(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;

	virtual long Process_Cmd_SysState_ItemStateChanged(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_TestFinished(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_TestStarted(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_TestStoped(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_OnReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_ExportReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}

	//shaolei 2022-1-13  获取模板生成服务生成的模板或项目
	CGuideBook* GetGuideBook_AtsGen();
	CItems* GetItems_AtsGen();
	CSttItems* GetSttItems_AtsGen();//将生成的CItems对象，转换为CSttItems对象，并返回
	CItems* GetItems_AtsGen_CmdAddGrp();
	CSttItems* GetSttItems_AtsGen_CmdAddGrp();//将生成的CItems对象，转换为CSttItems对象，并返回
	CItems* GetItems_AtsGen_ImportDvm();
	CSttItems* GetSttItems_AtsGen_ImportDvm();//将生成的CItems对象，转换为CSttItems对象，并返回
	CItems* GetItems_AtsGen_AinCfg();
	CSttItems* GetSttItems_AtsGen_AinCfg();//将生成的CItems对象，转换为CSttItems对象，并返回	
	CMacroTest* GetSttMacroTest_AtsGen();  //将生成的CMacroTest对象，返回
	CSttItems* GetSttItems_AtsGenEx();//通过当前选中的节点，将新生成的项目，追加到临时链表。转换成CSttItems，返回
	void FreeItems_AinCfg();
	void SetMacroTestSaveParas(BOOL bSaveParas);
    void AfterGenGuideBook();
	void SetTemplateGenMode(UINT nMode);
	BOOL Is_GenerateItems_CmdWzd();   //是否是通讯命令向导
	CDataGroup* GetGenrateItems_CmdWzd_Reply();   //获取通讯命令向导的应答group
	void SetDeviceSN_AfterTestCreated(CDataGroup *pDevices);
	void AfterSetItemPara(CSttParas *pParas);
	void AfterSetItemPara_IECConfig(CSttContents *pContents);
	void AfterSetItemPara_SystemConfig(CSttContents *pContents);
	void AfterSetItemPara_ChMapsConfig(CSttContents *pContents);

	virtual void CreateDeviceRefs();
	virtual void ReleasePpEngine();

    ///
    virtual long Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase);
    virtual long Ats_ConfigTest(const CString &strDeviceSN, CExBaseList *pTestApps);

	//2022-4-20 shaolei lijunq 
	//virtual long Process_Cmd_Test(BYTE *pBuf, long nLen);
	virtual long Process_Cmd_Test(CSttTestCmd *pTestCmd);

protected:
	CGbItemBase* GetItemFromAtsCmd(CSttAtsCmd &oAtsCmd);

	long Ats_CreateTest_OneTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
	long Ats_CreateTest_OneTest_devices(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol, CString &strDeviceFile);
	void SetGbrptFileFullPath(CString &strGbrptFile);
	void InitGuideBook_ItemsSel(CGuideBook *pGuideBook, CDataGroup *pItemsSel);
	void InitGuideBook_ItemSel(CGuideBook *pGuideBook, CDataGroup *pItemSel);
	void InitGuideBook_UpdateSysParas(CGuideBook *pGuideBook, CDataGroup *pSttParas);
	void WaitForTestFinished(const CString &strCmd);  //等待正在执行的项目执行结束
	BOOL IsTestStarted();  //判断试验是否已经开始
	void SetStopFlag(BOOL bStop);  //设置停止标记，已接收到停止命令时，设置为true
};

extern CSttSmartTest *g_theSttSmartTest;
extern CSttParas g_oReadDeviceParameter;  //shaolei  2023-12-19

long stt_Return_Ats_Event(CTestControlBase *pTestControl, CGbItemBase* pItem, BOOL bReports, BOOL bRptMapDatas);
long stt_Return_Ats_Event(CTestControlBase *pTestControl, CGbItemBase* pItem, char *pszEventID);
long stt_Return_Ats_Event_TestItemCount(CTestControlBase *pTestControl, long nTestItemCount);
void stt_Ats_InitSttReports(CSttReports *pSttReports, CGbItemBase *pItem);
void stt_Ats_InitSttReports_Ex(CSttReports *pSttReports, CReports *pReports, CGbItemBase *pItem);   
void stt_Ats_InitSttRptMapDatas(CSttRptMapDatas *pSttRptMapDatas, CGbItemBase *pItem);
void stt_Ats_InitSttStateDatas(CDvmDataset *pDvmDataset, CTestControlBase *pTestControl, CGbItemBase *pItem);

//返回 TestAppEvent、EngineEvent的事件  2020-11-24  lijunqing
void stt_Return_Ats_X_AddPatas(CTestControlBase *pTestControl, CSttParas *pSttParas, long nMode=0);
long stt_Return_Ats_Event_Ex(CTestControlBase *pTestControl, const CString &strEventType, const CString &strEventID);
long stt_Return_Ats_EngineEvent(const CString &strDeviceID, const CString &strEventType, const CString &strEventID, CDvmDataset *pDataset=NULL);

long stt_Return_Ats_ParentItem_StateChanged(CTestControlBase *pTestControl, CGbItemBase *pItem);
long stt_Return_Ats_Event_Process(CTestControlBase *pTestControl, CGbItemBase *pItem);
long stt_Return_Ats_Event_Process(CTestControlBase *pTestControl, const CString &strCurrItemName, const CString &strNextItemName);
long stt_Return_Ats_Event_ExportFinish(CTestControlBase *pTestControl);

BOOL stt_Is_SmartTest_Run_Local();
BOOL stt_Is_SmartTest_Run_Server();
