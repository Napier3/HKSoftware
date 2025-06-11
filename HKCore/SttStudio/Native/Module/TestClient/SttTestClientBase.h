//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestClientBase.h  CSttTestClientBase

#pragma once

#include "../../../Module/TestMacro/TestMacros.h"
#include "../Engine/SttClientTestEngine.h"

#include "../../Module/SttTestAppConfig/SttTestAppConfigTool.h"

#ifndef _PSX_IDE_QT_
#include "../../Module/SttTestAppConfig/Dialog/SttTestAppConfigDlg.h"
#endif

#include "../../../Module/BaseClass/SttFileTransferProgress.h"
#include "../../../Module/BaseClass/XTimer.h"


#define STT_TIMER_ID_HEARTBEAT 1827

class CSttTestClientBase : public CExBaseList
	, public CSttTestMsgViewInterface, public CMacroTestEventInterface
	, public CXTimer //2021-9-3  lijunqing 使用窗口作为定时器，以及后续的消息扩展
{
public:
	CSttTestClientBase();
	virtual ~CSttTestClientBase();


	//2021-8-·3 lijuniqng
	CSttTestAppCfg m_oTestAppCfg;

public:
	//2020-11-29 lijunqing 
	virtual void OnTestMsg(BYTE *pBuf, long nLen);
	virtual void OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType);
	virtual void On_Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);
	
	void RemovePkgDispatchInterface(CSttPkgDispatchInterface *p);
	void AddPkgDispatchInterface(CSttPkgDispatchInterface *p);

	//2023-5-31  shaolei 
	virtual long SendTestCmd(CSttCmdBase *pTestCmd);
	//2022-4-20 shaolei lijunq 
	virtual long SendTestCmd(BYTE *pBuf, long nLen);
//////////////////////////////////////////////////////////////////////////
protected:  //shaolei 改为protected 20220812
	CSttTestEngineClientData *m_pXClientEngine;
	CSttSocketFileTransferProgress *m_pFileTransferProgress;
	long m_nSttClientTimerID;

	CTestEventBaseInterface *m_pTestEventRcv; //事件接收对象

	void FreeXClientEngine();

public:
	CSttTestEngineClientData* GetTestEngineClient()	{	return m_pXClientEngine;	}
	CSttSocketFileTransferProgress *GetFileTransferProgress()	{	return m_pFileTransferProgress;	}
	long GetSttClientTimerID()		{	return m_nSttClientTimerID;		}
	void SetSttClientTimerID(long nTimerID)	{	m_nSttClientTimerID = nTimerID;	}
	BOOL OnTimer(UINT nTimerID, DWORD dwTime);

	void AttachSttSocketFileTransferProgress(CSttSocketFileTransferProgress *pProgress){	m_pFileTransferProgress=pProgress;	}
	void ConfigTest(CSttTestAppConfigTool *pTool);

	void StopTest();
	virtual void CloseDevice(const CString &strDeviceSN = _T(""));

	//2022-10-23  lijunqing
	void SetSttCmdDataFormat(long nSttCmdDataFormat);

//////////////////////////////////////////////////////////////////////////
//2021-8-14  lijunqing  提取的，基于STT协议部分的公共接口函数，便于STT和MQTT两种方式进行兼容
public:
	//CSttTestEngineClientData* GetTestEngineClient()	{	return m_pXClientEngine;	}

	virtual long SetTestAppConfig(const CString & bstrConfig);
	virtual long SetTestAppConfig(CSttTestAppCfg *pSttTestAppCfg);

	BOOL ConnectSttServer(CSttTestAppConfigTool *pTool);
	BOOL IsConnectSuccess();
	void DisConnect();	
	void DisConnectForClose(BOOL bDelete);
	
	//lijunqing 2021-8-14  将System_Login 从 SttMacroTest 移到此处，便于封装
	long System_LoginEx();

	//2020-10-26  shaolei
	void CreateSttTimer();
	void KillSttTimer();

	void SetTestEventInterface(CTestEventBaseInterface *pTestEventRcv);	

/*
	void AttachSttSocketFileTransferProgress(CSttSocketFileTransferProgress *pProgress){	m_pFileTransferProgress=pProgress;	}

	long Test_CloseDevice(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Turn off the device
	long Test_StopTest(const CString &strMacroID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Stop testing
	long Test_StartTest(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);	//start testing

	//校准命令：adj-cmd
	long Adjust_Adjust(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	long Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	long Adjust_WriteFile(BOOL bSendCmdAsync=FALSE, BOOL bDoEvents=TRUE);
*/

//////////////////////////////////////////////////////////////////////////

private:
	long Login_Local();
	long Login_Remote();
	long Remote_BindAndLogin(CSttTestRemoteRegister *pRegister,CSttTestClientUser *pUser);

public:
	//system command
	long System_SetSysConfig(CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_GetSysConfig(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Login(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Login_Local_Test(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Login_Local_ATS(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Login_Local(const CString &strTestID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Logout(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Request(const CString &strAuthorityID, long nAuthorityVal,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long System_Authority(const CString &strAuthorityID, long nAuthorityVal,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);


	//Remote cmd
	long Remote_Bind(CSttTestRemoteRegister *pRegister,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Remote_Query(const CString &strCode_Register=_T(""),BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Remote_Register(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Remote_UnRegister(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);

	//Smart Test Terminal : Test Command
	long Test_SetParameter(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Preset test parameters
	long Test_UpdateParameter(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Test_StartTest(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);	//start testing
	long Test_StopTest(const CString &strMacroID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);	//Stop testing
	long Test_GetReport(const CString &strMacroID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Get report data
	long Test_CloseDevice(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Turn off the device
	long Test_GetSystemState(CStringArray &astrTypes, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);	//Query system status
	long Test_SendHeartbeat();

	//校准命令：adj-cmd
	long Adjust_Adjust(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	long Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	long Adjust_WriteFile(BOOL bSendCmdAsync=FALSE, BOOL bDoEvents=TRUE);

	//2021-9-30  lijunqing
	long Meas_Read(BOOL bSendCmdAsync=FALSE, BOOL bDoEvents=TRUE);

	//2020-10-09 文件处理  lijunqing
	//读文件 strRealFilePath，目标文件相对路径，例如："Config/DeviceSystemParas.xml"  strDestFilePath,本地绝对路径
	long ReadFile(const CString &strSrcFileRealPath, const CString &strDestFilePath,CSttSocketFileTransferProgress *pProgress);
	//写文件：strSrcFilePath，本地绝对路径；strSrcFileRealPath目标文件相对路径
	long Write(const CString &strSrcFilePath, const CString &strDestFileRealPath,CSttSocketFileTransferProgress *pProgress);

	//故障回放命令
	//上位机给测试仪：手动触发命令、数据发送完成命令
	long Test_SendTrigger();
	long Comtrade_SendDataFinish(long nIndex,long nSendLen,BOOL bLast);
	long Comtrade_SendDataStart(long nIndex,long nSendLen);

	//ats cmd
	long Ats_CreateTest(const CString &strTestID,const CString &strGbXmlFile,const CString &strPpXmlFile
		,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_ConnectDevice(const CString &strPpXmlFile,const CString &strDvmFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);

	long Ats_StartTest(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_StopTest(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_CloseTest(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_SetItemState(const CString &strItemPath,long nSelect,long nEnable,long nShow,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_TestItem (const CString &strItemPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_TestFrom (const CString &strItemPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_TestAllFailedItems(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_GetReportFile(long nGbrptFile,long nXmlRptFile,const CString &strDestPath=_T(""),BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long GetSystemState(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_CreateDevice(const CString &strDeviceID,const CString &strPpXmlFile
		,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_ConfigDevice(CDataGroup *pCommParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_GetDataset(const CString &strDatasetPath,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_SetDataset(const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_RunProcedure(CDvmData *pData,const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_CloseDevice(const CString &strDeviceID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_ConfigEngine(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
		,long nLogDebugInfor,long nNoChangeWhenSame,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Ats_FinishInputData(CDataGroup *pDatas,CExBaseList *pMsgs);
	long Process_Cmd_Ats_InputData(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd);

	//debug command
	long Debug_Command(const CString &strCmdID,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetProcessState(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetMemState(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetTestParas(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetTestReports(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetBasicTestParas(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetBasicReportData(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetDrvTestData(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetDrvReportData(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetFpgaData(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_GetSocketConnect(BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);

	long Debug_ConfigDebug(CDataGroup *pGroup,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_ConfigDebug(CSttDebugCmd *pCmd,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL);
	long Debug_ConfigDebug(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
		,long nLogDebugInfor,long nNoChangeWhenSame, long nSpyCmd);  //2020-12-04  lijunqing add spy-cmd
	long Debug_ConfigDebug(const CString &strDebugParaID, long nValue); //2020-12-04  lijunqing add spy-cmd

	//测试功能事件接口
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas)	{}
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas)	{}
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)	{}
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)	{}
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas)	{}
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){ }

public:
	virtual long OnMeas(CDataGroup *pParas);

	CDataGroup m_oMeasData;
	void OpenMeasDataFile();

//2021-9-2  lijunqing
public:
	virtual void OnXTimer(DWORD dwTimerID);

};

//单一测试客户端对象，用于简单小工具，例如校准工具、SttDebug等
extern CSttTestClientBase *g_theSingleSttTestClient;
void stt_CreateSingleSttTestClient();
void stt_RelaseSingleSttTestClient();

extern CSttParas g_oReadDeviceParameter;  //shaolei  2023-12-19

//处理ReadDeviceParameter的应答
void stt_OnReport_ReadDeviceParameter(CSttParas *pParas);
void stt_OnReport_ReadDeviceParameter_Linux(CSttParas *pParas);
void stt_OnReport_ReadDeviceParameter_Windows(CSttParas *pParas);

void stt_OnReport_ReadDeviceParameter_GetSysVersion(CSttParas *pParas, CString &strSysVersion);