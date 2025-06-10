#pragma once

#include "SttTestEngineServerBase.h"
#include "SttNativeClientTestEngine.h"
#include "../SmartTestInterface/SttSmartTestSvrInterface.h"

#include"../../../Protocol/Module/Engine/PpEngineBaseApp.h"
#include"../../../Protocol/Module/PxiEngine/PxiEngine.h"
#include "../../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "../../../AutoTest/Module/TCtrlMsgRcvInterface.h"
#include "../SttCmd/GuideBook/SttItems.h"

#define CREATE_TEST_CREATE_ERROR                   0
#define CREATE_TEST_CREATE_NEW                        1
#define CREATE_TEST_CURR_EXIST_SAME             2
#define CREATE_TEST_CURR_EXIST_NOT_SAME  3

#define  STT_ITEMS_ID_DEVRESET                            "DEVRESET"

#ifdef _SttTestServer_For_Debug_
//测试模板生成模式：0-普通模式；1-开始测试时生成模板
#define TEMPLATE_GEN_MODE_NORMAL     0   //普通模式，需要重新生成测试前准备项目：系统配置、硬件通道配置、IEC配置
#define TEMPLATE_GEN_MODE_STARTTEST  1   //开始测试时生成模式，不重新生成测试前准备项目（测试前准备项目的参数，可能是重新设置过的，不能重新生成覆盖）
#endif

class CSttSmartTest : public CTCtrlMsgRcvInterface
{
public:
    CSttSmartTest();
    virtual ~CSttSmartTest();

	static long g_nSttSmartTestRef;
	static CSttSmartTest* g_pSttSmartTest;
	static CSttSmartTest* Create();
	static void Release();

    void FreeTestControl();
	long UpdateParameter(CDataGroup *pParas);

public:
	CExBaseObject* GetTestControl()	{	return NULL;	}
	CExBaseObject* GetGuideBook();
	BOOL IsTestCreated();
	CString GetProjectName();

public:
	virtual void InitTestControl(BOOL bBOOL){}
	virtual BOOL Process_Cmd_Test(BYTE *pBuf, long nLen){ return FALSE;}
	virtual BOOL Process_Cmd_Test(CSttTestCmd *pAtsCmd){ return FALSE;}
	virtual long Ats_ConfigDevice(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol){ return 0;}
	virtual long Ats_ExportWordRpt(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol){ return 0;}
	virtual long Ats_AdjustReport(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol){ return 0;}
	virtual long Ats_ClearReportsRslts(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol){ return 0;}
	virtual CSttItems* GetSttItems_AtsGen_ImportDvm(){return NULL;}
	virtual CSttItems* GetSttItems_AtsGen_AinCfg(){return NULL;}
	virtual CMacroTest* GetSttMacroTest_AtsGen(){return NULL;}
	virtual void FreeItems_AinCfg(){}
	virtual BOOL Is_GenerateItems_CmdWzd(){ return FALSE;}
	virtual long Ats_SaveTemplate(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol) { return 0;}
	virtual long Ats_SaveTest(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol) { return 0;}
	virtual long Ats_OpenTemplate(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol) { return 0;}
	virtual long Ats_OpenGbrptFile(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol) { return 0;}
	virtual long Ats_ExportReport(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol) { return 0;}
	virtual long Ats_AdjustMainWnd(CSttAtsCmd *pAtsCmd,CSttProtocolInterface *pSttProtocol) { return 0;}
	virtual long GetReadDeviceParameter(CSttParas *pParas) { return 0;}
	virtual CWnd* GetTestControlMainWnd(){return NULL;}
	virtual CDataGroup* GetGenrateItems_Cmd_Reply() {return NULL;}
	virtual CDataGroup* GetGenrateItems_CmdWzd_Reply() {return NULL;}
	virtual CSttItems* GetSttItems_AtsGen(){return NULL;}
	virtual CSttItems* GetSttItems_AtsGen_CmdAddGrp(){return NULL;}
	virtual CString Ats_QueryItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol){return "";}
	virtual long Ats_UpdateItem(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) {return 0;}
	virtual long Ats_GenerateMacroTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);


	virtual long OnException(long nError, const CString &strError, CExBaseObject *pTestControl){return 0;}
	virtual long OnConnectSuccess(CExBaseObject *pTestControl){return 0;}
	virtual long OnStopTest(long nType, CExBaseObject *pTestControl){return 0;}

	virtual long OnUpdateMeasure(long nData, CExBaseObject *pTestControl){return 0;}
	virtual BOOL IsRunning(long nType, CExBaseObject *pTestControl){return 0;}
	virtual long HideAllTestItemUI(long nData, CExBaseObject *pTestControl){return 0;}

    virtual long OnException(long nError, const CString &strError);
    virtual long OnConnectSuccess();
	virtual long OnConnectFailed();
     virtual long OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop=TRUE);
     virtual long OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj);
    virtual long OnTestBegin();
    virtual long OnStopTest(long nType);
    virtual long OnUpdateMeasure(long nData);
    virtual BOOL IsRunning(long nType);
	virtual BOOL Is_GenerateItems_Cmd(){return FALSE;}
    virtual long HideAllTestItemUI(long nData);
    virtual HWND GetFrameHwnd();
    virtual void ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate=TRUE, BOOL bShow=TRUE);
    virtual void ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow=TRUE);
    virtual void EditItemPara(CExBaseObject *pGbItem);
    virtual void LocateItemReport(CExBaseObject *pGbItem);
	virtual CExBaseList* GetGlobalDatas(){return NULL;}
	virtual CExBaseList* GetSysPara(){return NULL;}
	virtual void SetMacroTestSaveParas(BOOL b){}

public:
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
	virtual long Ats_GenerateTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_GenerateItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_GenerateMacroTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SetItemPara(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SetItemPara_SystemConfig(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_ManualTrigger(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) ;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual long Ats_CreateTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol);
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
	virtual long Ats_GenerateTemplate(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_GenerateItems(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
//	virtual long Ats_GenerateMacroTest(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SetItemPara(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_SetItemPara_SystemConfig(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;
	virtual long Ats_ManualTrigger(CSttAtsCmd *pAtsCmd, CSttProtocolInterface *pSttProtocol) ;

	//shaolei 2022-1-13  获取模板生成服务生成的模板或项目
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
	CGuideBook* GetGuideBook_AtsGen();
#endif
	CItems* GetItems_AtsGen();
	void SetTemplateGenMode(UINT nMode);
	BOOL m_bTestCreated;

};

//返回 TestAppEvent、EngineEvent的事件  2020-11-24  lijunqing
long stt_Return_Ats_Event_Ex(CExBaseObject *pTestControl, const CString &strEventType, const CString &strEventID);
long stt_Return_Ats_EngineEvent(const CString &strDeviceID, const CString &strEventType, const CString &strEventID, CDvmDataset *pDataset=NULL);
