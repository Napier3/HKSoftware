#pragma once

#include "../SttAuthority/SttTestRemoteRegister.h"

#include "SttTestEngineServerBase.h"
#include "SttNativeClientTestEngine.h"

#ifdef _SttTestServer_For_Debug_
//Debug仍放在Engine路径，以便大家都能获取
#include"../Engine/SttSmartTest_SvrDebug.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#else
#include"../SttAtsSvr/XSttSmartTestEntry.h"
#endif

class CSttAtsInterface
{
public:
	virtual DWORD CreateTest() = 0;
	virtual DWORD StartTest() = 0;
	virtual DWORD StopTest() = 0;
	virtual DWORD TestItem() = 0;
	virtual DWORD TestFrom() = 0;
	virtual DWORD TestAllFailedItems() = 0;
	virtual DWORD GetItemReport() = 0;
	virtual DWORD GetReportFile() = 0;
	virtual DWORD GetSystemState() = 0;
};

extern CDataGroup *g_pDeviceAttrs;

class CSttNativeTestEngine : public CPxiDeviceCommCmdMessage
{
public:  //CPxiDeviceCommCmdMessage
    virtual void OnCommCmdMessage(WPARAM wParam, LPARAM lParam);
    virtual void OnSysMessage(WPARAM wParam, LPARAM lParam);
    //2020-11-24  lijunqing LINUX  post msg to ats
    virtual void OnEngineDataDeleted(const CString &strDeviceID);

public:
	CSttNativeTestEngine();
	virtual ~CSttNativeTestEngine();

public:
	virtual void x_Return_Ats_Success(void  *pClientSocket, CSttAtsCmd &oAtsCmd, unsigned int nState=STT_CMD_ExecStatus_SUCCESS
		, CDvmDataset *pDatas=NULL, CExBaseObject *pGuideBook = NULL) = 0;
	virtual void x_Return_NoDevice(void  *pClientSocket, CSttSysState &oSysState) = 0;
	virtual void x_Return_Ats_Event(void  *pClientSocket, CSttSysState &oSysState) = 0;
	virtual long x_ReturnSysState(void  *pSocket, int nCmdType, char *pszCmdID, BOOL bIsSuccess) = 0;
	virtual long x_ReturnSysState(void  *pSocket,CSttSysState *pSysState, BOOL bSpyAllCmd) = 0;
	virtual long x_ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,CSttCmdData *pRetData) = 0;  //lijunqing 2020-10-20
	virtual long x_ReturnSysState(CSttCmdBase *pSttCmd, long nCmdExecStatus,void  *pSocket, CSttCmdData *pRetData) = 0;  //lijunqing 2020-10-21

	virtual long x_SendCmd(void  *pClientSocket, CSttCmdBase *pCmd,BOOL bCompress=FALSE,BOOL bReset=TRUE) = 0;
	virtual long x_SendCmdEx(void  *pClientSocket, CSttCmdBase *pCmd,long nSrcID=0) = 0;
	virtual long x_SendSysState(void  *pClientSocket, CSttSysState *pSysState) = 0;
	virtual long x_SendSysStateEx(void  *pClientSocket, CSttSysState *pSysState,long nDstID=0) = 0;
	virtual long x_SendHeartbeatCmd(void  *pClientSocket) = 0;
	virtual long x_RetFailureSysState(void  *pClientSocket, CSttCmdBase *pCmd) = 0;
	virtual long x_SendCmd(CSttCmdBase *pCmd, BOOL bSpyAllCmd) = 0;
	virtual long x_ReturnSysStateToChildren(void *pExceptSocket,CSttSysState *pSysState) = 0;

public:
	virtual long Process_Cmd_System_Request(void  *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_Cmd_System_Authority(void  *pClientSocket, CSttSystemCmd &oSysCmd);
	virtual long Process_SysState(void  *pClientSocket, CSttSysState &oSysState);
	virtual long Process_SysState_Register(CSttSysState &oSysState);
	virtual long Process_SysState_UnRegister(CSttSysState &oSysState);
	virtual long Process_SysState_InputData(void  *pClientSocket,CSttSysState &oSysState);
	
public:
    //2020-5-18  lijunqing
    virtual long Process_Cmd_Ats(void  *pClientSocket, CSttAtsCmd &oAtsCmd);

	//当前自动测试命令
	CSttAtsCmd m_oSttAtsCmd;
	long ReturnExecReply(long nCmdExecStatus,CSttCmdData *pRetData=NULL);

protected:
    CDvmDataset* Ats_GetDataset(CSttAtsCmd &oAtsCmd);
     long Ats_SetDataset(CSttAtsCmd &oAtsCmd);
     long Ats_ConfigDevice(CSttAtsCmd &oAtsCmd);

    long Process_Cmd_Ats_CreateTest(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_StartTest(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_StopTest(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CloseTest(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestItem(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestFrom(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_TestAllFailedItems(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetItemReport(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetReportFile(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetSystemState(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CreateDevice(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ConnectDevice(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ConfigDevice(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GetDataset(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SetDataset(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_RunProcedure(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_CloseDevice(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ConfigEngine(void  *pClientSocket, CSttAtsCmd &oAtsCmd);

	long Process_Cmd_Ats_FinishInputData(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_QueryAtsFile(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SetItemState(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_GenerateTemplate(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_GenerateItems(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_GenerateMacroTest(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SetItemPara(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Procss_Cmd_Ats_SetItemPara_SystemConfig(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_ManualTrigger(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
    long Process_Cmd_Ats_SaveTemplate(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_SaveTest(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ExportWordRpt(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_OpenTemplate(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_OpenGbrptFile(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_AdjustMainWnd(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_ExportReport(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_QueryItem(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_UpdateItem(void  *pClientSocket, CSttAtsCmd &oAtsCmd);
	long Process_Cmd_Ats_AdjustReport(void  *pClientSocket, CSttAtsCmd &oAtsCmd);


    void Return_Ats_Success(void  *pClientSocket, CSttAtsCmd &oAtsCmd, unsigned int nState=STT_CMD_ExecStatus_SUCCESS, CDvmDataset *pDatas=NULL, CExBaseObject *pGuideBook = NULL);
    void Return_NoDevice(void  *pClientSocket, CSttSysState &oSysState);
    void Return_Ats_Event(void  *pClientSocket, CSttSysState &oSysState);
    long ValidateSmartTest(void  *pClientSocket, CSttSysState &oSysState);
	//shaolei 20220326 
	void Return_DeviceParameter_AfterLogin(void  *pClientSocket, CSttSysState &oSysState);

public:
    //SmartTest  目前只处理但装置的测试
    CSttSmartTest *m_pSmartTest;
	void SetSttSmartTest(CSttSmartTest *pSmartTest)	{	m_pSmartTest = pSmartTest;	}
	
public:

private:
	//测试控制管理接口，对于有界面的TestMain，由界面启动，对于没有界面的TestMain,由TestMainCore启动
	CSttAtsInterface *m_pSttAtsInterface;

//2020-11-25  lijunqing
public:
	virtual long Ats_InputData(void  *pClientSocket,CDataGroup *pDatas,CExBaseList *pMsgs);
    void OnTimer();

};

extern CSttNativeTestEngine *g_theNativeTestEngine;
extern CSttTestAppCfg *g_pTheSttTestAppCfg ;
