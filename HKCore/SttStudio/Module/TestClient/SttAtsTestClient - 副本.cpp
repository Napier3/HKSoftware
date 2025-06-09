#include "stdafx.h"
#include "SttAtsTestClient.h"
#include "../SttTest/Common/tmt_adjust_sys_para_module_def.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../SttTestResourceMngr/RtDataMngr/SttGlobalRtDataMngr.h"
#include "../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../Module/Socket/XPing.h"

#define STT_EXCEPTION_TIMEOUT               2000//异常事件超时时间,超过2s未收到,默认超时已恢复

//2022-10-6  lijunqing  
//CSttAtsTestClient与CSttPowerTestEngineBase功能重复，当时因为时间紧，就没有进行相同功能的抽象处理
//因此把CSttPowerTestEngineBase也包含到工程中，2022-10-6 lijq移去CSttPowerTestEngineBase
CSttTestAppConfigTool g_oSttTestAppConfigTool;
CSttTestAppCfg g_oSttTestAppCfg;//zhouhj 20210823  李工因为兼容物联网多配置文件问题已修改相关功能类,在单机软件中只会有一台测试仪,故此处采用全局唯一对象

//此处放在6.3版本的上位机软件中编译，故直接extern。到时候在脱机框架中，需要重新定义
extern CSttTestAppCfg g_oSttTestAppCfg;   //脱机软件中，只有一个测试仪，因此使用全局唯一对象
extern CSttTestAppConfigTool g_oSttTestAppConfigTool;
extern CSttTestResourceMngr g_oSttTestResourceMngr;

CSttAtsTestClient::CSttAtsTestClient(void)
{
	m_pXClientEngine = NULL;
	m_pLastEventResult = NULL;
	m_bTestAppConnect = FALSE;
	m_pAtsEventRcv = NULL;
	m_oCurrEventResult.init(true);
	m_bLockFlag = NULL;

	SttOpen("TestAppConfig.xml");
}

CSttAtsTestClient::~CSttAtsTestClient(void)
{
}

void CSttAtsTestClient::SttOpen(const CString &strTestAppCfgFile)
{
	g_oSttTestAppCfg.SttOpen(strTestAppCfgFile);
}

CSttTestAppCfg* CSttAtsTestClient::GetSttTestAppCfg()
{
	return &g_oSttTestAppCfg;
}

void CSttAtsTestClient::AppenEventInfo(CEventResult *pEventInfo)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	if (pEventInfo->m_strEventID.IsEmpty())
	{
		int nIndex = 0;
		nIndex++;
		pEventInfo->m_strEventID = _T("");
	}

	m_oFlushEventList.AddTail(pEventInfo);
}

void CSttAtsTestClient::GetEventInfo(CExBaseList &oEventInfoList)
{
	CAutoSimpleLock oLock(m_oCriticSection);

	oEventInfoList.AppendEx(m_oFlushEventList);
	m_oFlushEventList.RemoveAll();
}

CEventResult *CSttAtsTestClient::InitEvent(const CString &strEventID,double fTime,double fRealTime
										   ,const CString &strTimeStr/*,BOOL bUpdateLastResult*/) //yyj modify 20210902
{
	CEventResult *pEventInfo = NULL;
	SYSTEMTIME tmEvent;
	//::GetLocalTime(&tmEvent);
	tmEvent.wYear = 1970;
	tmEvent.wMonth = 1;
	tmEvent.wDay = 1;
	tmEvent.wHour = 0;
	tmEvent.wMinute = 0;
	tmEvent.wSecond = 0;
	tmEvent.wMilliseconds = 0;

	if (strEventID != SYS_STATE_EVENT_OnTestStoped)
	{
		struct timeval ts;
		ts.tv_sec = (long)fTime;   //秒
		double dNs = fTime - ts.tv_sec;  //纳秒
		ts.tv_usec = dNs * 1000000;
		ep_cap_timeval_to_systime(ts,tmEvent);
	}
	
	if (strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		pEventInfo = (CEventResult *)m_oCurrEventResult.Clone();

		pEventInfo->m_tmStart = tmEvent;
		pEventInfo->m_fActStart = 0;
		pEventInfo->m_nCurrStateIndex = 0;
	}
	else
	{
		m_pLastEventResult = &m_oCurrEventResult;
		pEventInfo = (CEventResult *)m_pLastEventResult->Clone();	
	}

	if (strEventID == SYS_STATE_REPORT_OnStateChanged)
	{
		pEventInfo->m_fActStart = pEventInfo->m_fActTime;
		pEventInfo->m_nCurrStateIndex = pEventInfo->m_nCurrStateIndex;
	}

	pEventInfo->m_fActTime = 0;
	pEventInfo->m_tmEvent = tmEvent;
	pEventInfo->m_strTimeStr = strTimeStr;
	pEventInfo->m_strEventID = strEventID;
	
	return pEventInfo;
}


//连接底层自动测试服务，nPort = STT_PORT_NATIVE_SERVER。
BOOL CSttAtsTestClient::ConnectAtsTestServer(const CString &strIP,long nPort,const CString &strSoftID)
{
	if (IsConnectSuccess())
	{
		return TRUE;
	}

	//连接登录
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "正在连接测试仪......");

	g_oSttTestAppConfigTool.m_pSttTestMsgViewInterface = this;
	BOOL bRet = g_oSttTestAppConfigTool.Local_ConnectServer(&g_oSttTestAppCfg,strIP,nPort,strSoftID,this);

	if(bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "测试仪连接成功");

		g_oSttTestAppCfg.SetTestAppIP(strIP);
		g_oSttTestAppCfg.SetNativeServerPort(nPort);

		g_oSttTestAppConfigTool.GetSttTestEngineClientData(&m_pXClientEngine);//联机成功后，从Tool中获取Client对象
		m_pXClientEngine->SetTestEventInterface(this);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, "连接测试仪失败，请检查网络链路是否连通，IP地址及端口配置是否正确；然后点击网络连接按钮重新连接");
	}

	return bRet;
}

BOOL CSttAtsTestClient::ConnectAtsTestServer(const CString &strTestAppIP)
{
	if (IsConnectSuccess())
	{
		return TRUE;
	}

	CString strIP;
	
	if (strTestAppIP.GetLength() > 0)
	{
		strIP = strTestAppIP;
	}
	else
	{
		strIP = g_oSttTestAppCfg.GetTestAppIP();
	}
	
	long nPort = g_oSttTestAppCfg.GetNativeServerPort();
//#ifndef _PSX_QT_LINUX_
// 	if(!xping(strIP))
// 	{
// 		m_bTestAppConnect = false;
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("联机失败[%s][%ld]."),strIP.GetString(),nPort);
// 		return m_bTestAppConnect;
// 	}
//#endif
	m_bTestAppConnect = ConnectAtsTestServer(strIP,nPort, STT_SOFT_ID_ATS);

	return m_bTestAppConnect;
}

void CSttAtsTestClient::FreeXClientEngine()
{
	if (m_pXClientEngine != NULL)
	{
		m_pXClientEngine->PrepareFreeClientEngine();
		delete m_pXClientEngine;
		m_pXClientEngine = NULL;
	}
}

BOOL CSttAtsTestClient::IsConnectSuccess()
{
	if (m_pXClientEngine == NULL)
	{
		return FALSE;
	}

	return m_pXClientEngine->IsConnectServerSucc();
}


// 
// long CSttAtsTestClient::SendStartCmd()
// {
// 	long nRet = 0;
// 	//读取命令参数
// 	CSttTestCmd oSttCmd;
// 	GenerateTestCmdFromParas(oSttCmd,true);
// 
// 	//yyj 20210809 
// 	if (g_bSaveFile)
// 	{
// 		SYSTEMTIME tm;
// 		::GetLocalTime(&tm);
// 		CString strTmpPath = _P_GetLibraryPath();
// 		strTmpPath.AppendFormat(_T("StartCmd%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
// 			, tm.wHour, tm.wMinute, tm.wSecond);
// 		oSttCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
// 	}
// 
// 	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
// 	{
// 		//		m_oEventResultList.DeleteAll();
// 		m_oFlushEventList.DeleteAll();
// 		m_pLastEventResult = NULL;
// 
// 		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
// 	}
// 	else
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_INFOR,"测试仪连接中断，请先与测试仪建立连接。");
// 	}
// 
// 	return nRet;
// }
// 
// long CSttAtsTestClient::SendStopCmd()
// {
// 	long nRet = 0;
// 	if (m_pXClientEngine != NULL && m_pXClientEngine->m_pSttClientSocket != NULL)
// 	{
// 		CSttTestCmd oSttCmd;
// 		oSttCmd.m_strID = STT_CMD_TYPE_TEST_StopTest;
// 
// 		//yyj 20210809 
// 		if (g_bSaveFile)
// 		{
// 			SYSTEMTIME tm;
// 			::GetLocalTime(&tm);
// 			CString strTmpPath = _P_GetLibraryPath();
// 			strTmpPath.AppendFormat(_T("Test_StopTest%d-%d-%d %d-%d-%d.xml"), tm.wYear, tm.wMonth, tm.wDay
// 				, tm.wHour, tm.wMinute, tm.wSecond);
// 			oSttCmd.SaveXmlFile(strTmpPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
// 		}
// 
// 		nRet = m_pXClientEngine->SendCmdSync(&oSttCmd,g_nTimeOut_Test);
// 	}
// 
// 	return nRet;
// }
long CSttAtsTestClient::Ats_CreateTest(CExBaseList *pSttParas)
{
	return m_pXClientEngine->Ats_CreateTest(pSttParas);
}

long CSttAtsTestClient::Ats_CreateTest(const CString &strTestID,const CString &strGbXmlFile,const CString &strPpXmlFile
							,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas
							,BOOL bDoEvents,CSttCmdData *pRetData)
{
	
	return 0;
}

long CSttAtsTestClient::Ats_ConnectDevice(const CString &strPpXmlFile,const CString &strDvmFile,CDataGroup *pCommParas
										  ,BOOL bDoEvents, CSttCmdData *pRetData)
{

	return 0;
}


long CSttAtsTestClient::Ats_StartTest(CDataGroup *pTestMacroUI, CDataGroup *pUIParas, CDataGroup *pCommCmd
									  , CSttContents *pCharacteristic, BOOL bDoEvents,CSttCmdData *pRetData
									  ,const CString &strDvmFile, long nTestMode)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_StartTest(pTestMacroUI, pUIParas, pCommCmd, pCharacteristic, bDoEvents, pRetData,strDvmFile, nTestMode);
}

long CSttAtsTestClient::Ats_StopTest(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_StopTest(bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_ManuTrigger(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ManuTrigger(bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_SaveTemplate(const CString &strPath, const CString& strFileName, CDataGroup *pMacroTestUI
										 , CDataGroup *pUIParas, bool bDoEvents, CSttCmdData *pRetData,long nSynMode)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SaveTemplate(strPath, strFileName, pMacroTestUI, pUIParas, bDoEvents, pRetData, nSynMode);
}

long CSttAtsTestClient::Ats_SaveTest(const CString &strPath, const CString& strFileName, CDataGroup *pMacroTestUI
									 , CDataGroup *pUIParas, bool bDoEvents, CSttCmdData *pRetData,long nSynMode)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SaveTest(strPath, strFileName, pMacroTestUI, pUIParas, bDoEvents, pRetData, nSynMode);
}

long CSttAtsTestClient::Ats_ExportWordRpt(const CString &strPath, const CString& strFileName, CDataGroup *pParas, bool bDoEvents, CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ExportWordRpt(strPath, strFileName, pParas, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_OpenTemplate(const CString &strFileWithPath, const CString &strDvmFile, bool bDoEvents, CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_OpenTemplate(strFileWithPath, strDvmFile, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_GenerateItems_Items(CDataGroup *pGenItemsParas, CSttContents *pContents, bool bDoEvents,CSttCmdData *pRetData,long nSynMode)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_GenerateItems_Items(pGenItemsParas, pContents, bDoEvents, pRetData, nSynMode);
}

long CSttAtsTestClient::Ats_OpenGbrptFile(const CString &strGbrptFile, const CString &strDvmFile, const CString &strSmartTestRunMode,bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_OpenGbrptFile(strGbrptFile, strDvmFile, strSmartTestRunMode, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_AdjustMainWnd(LONG hMainParent, LONG hLogParent, bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_AdjustMainWnd(hMainParent, hLogParent, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_ExportRpt(const CString &strDeviceID, bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ExportRpt(strDeviceID, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_UpdateItem(const CString &strItemPath, CDataGroup *pItemParas, bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_UpdateItem(strItemPath, pItemParas, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_UpdateItem(const CString &strItemPath, const CString &strItemParas, const CString &strItemType, bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_UpdateItem(strItemPath, strItemParas, strItemType, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_QueryItem(const CString &strItemPath, bool bDoEvents, CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_QueryItem(strItemPath, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_AdjustReport(const CString &strDeviceSN, long nShowWnd, bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_AdjustReport(strDeviceSN, nShowWnd, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_ClearReportsRslts(CDataGroup *pParas, bool bDoEvents, CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ClearReportsRslts(pParas, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_AddSafety(CDataGroup *pParas, CExBaseList *pDatas, CExBaseList *pMsgs, bool bDoEvents, CSttCmdData *pRetData, long nSynMode)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_AddSafety(pParas, pDatas, pMsgs, bDoEvents, pRetData, nSynMode);
}

long CSttAtsTestClient::Ats_CloseTest(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_CloseTest(bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_SetItemState(CExBaseList *pSttParas, BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SetItemState(pSttParas,  bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_SetItemState(const CString &strItemPath,long nSelect,long nEnable,long nShow
										 ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SetItemState(strItemPath, nSelect, nEnable, nShow,  bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_TestItem (const CString &strItemPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_TestItem(strItemPath, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_TestFrom (const CString &strItemPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_TestFrom(strItemPath, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_TestAllFailedItems(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_TestAllFailedItems(bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_GetReportFile(long nGbrptFile,long nXmlRptFile,const CString &strDestPath
										  ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_GetReportFile(nGbrptFile, nXmlRptFile, strDestPath, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_GetSystemState(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->GetSystemState(bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_CreateDevice(const CString &strDeviceID,const CString &strPpXmlFile
							  ,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas
							  ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_CreateDevice(strDeviceID, strPpXmlFile, strDvmFile, strCommCfgFile, pCommParas, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_ConfigDevice(CDataGroup *pCommParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ConfigDevice(pCommParas, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_GetDataset(const CString &strDatasetPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_GetDataset(strDatasetPath, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_SetDataset(const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SetDataset(strDatasetPath, pDataset, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_RunProcedure(CDvmData *pData,const CString &strDatasetPath,CDvmDataset *pDataset
										 ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_RunProcedure(pData, strDatasetPath, pDataset, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_CloseDevice(const CString &strDeviceID,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_CloseDevice(strDeviceID, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_ConfigEngine(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
							  ,long nLogDebugInfor,long nNoChangeWhenSame,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ConfigEngine(nLogDataBind, nLogPkgDataInfor, nLogPkg, nLogDebugInfor, nNoChangeWhenSame, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_FinishInputData(CDataGroup *pDatas,CExBaseList *pMsgs)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_FinishInputData(pDatas, pMsgs);
}

long CSttAtsTestClient::Ats_QueryAtsFile(long nGetGbxmlFile,long nGetPpxmlFile,long nGetDvmFile,long nGetGbrptFile
										 ,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_QueryAtsFile(nGetGbxmlFile, nGetPpxmlFile, nGetDvmFile, nGetGbrptFile, bDoEvents, pRetData);
}

long CSttAtsTestClient::Process_Cmd_Ats_InputData(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Process_Cmd_Ats_InputData(pClientSocket, oAtsCmd);
}

long CSttAtsTestClient::Ats_SetTestParas(const CString &strDeviceID, CExBaseList *pTestParas, BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SetTestParas(strDeviceID, pTestParas, bDoEvents, pRetData);
}

//单个功能的模板生成
//新增通讯命令生成配置 + 特性曲线定义
long CSttAtsTestClient::Ats_GenerateTemplate(CDataGroup *pTestMacroUI, CDataGroup *pUIParas,CDataGroup *pCommCmd
											 , CSttContents *pCharacteristic, const CString &strRetMode, long nHasDigital
											 ,bool bDoEvents,CSttCmdData *pRetData,const CString &strDvmFile)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_GenerateTemplate(pTestMacroUI, pUIParas, pCommCmd, pCharacteristic, strRetMode, nHasDigital, bDoEvents, pRetData,strDvmFile);
}

//多功能的模板生成
long CSttAtsTestClient::Ats_GenerateTemplate(CDataGroup *pGenParas,const CString &strRetMode, long nHasDigital
											 ,bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_GenerateTemplate(pGenParas, strRetMode, nHasDigital, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_GenerateItems(const CString &strItemParentPath, const CString &strItemsName, const CString &strItemsID
										  , CDataGroup *pTestMacroUI, CDataGroup *pUIParas, CDataGroup *pCommCmd, CSttContents *pCharacteristic
										  , const CString &strDvmFile, const CString strTestClass, const CString &strRetMode, long nHasDigital
										  , long nRepeatTimes, long nRptTitle, long nTitleLevel, long nSynMode, bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_GenerateItems(strItemParentPath, strItemsName, strItemsID, pTestMacroUI, pUIParas, pCommCmd, pCharacteristic
		, strDvmFile, strTestClass, strRetMode, nHasDigital, nRepeatTimes, nRptTitle, nTitleLevel, nSynMode, bDoEvents, pRetData);
}

long CSttAtsTestClient::Ats_SetItemPara(const CString &strItemPath, const CString& strMacroID, CDataGroup *pItemParas
										,bool bDoEvents,CSttCmdData *pRetData, const CString &strContents
										, const CString &strRsltExpr)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SetItemPara(strItemPath, strMacroID, pItemParas, bDoEvents, pRetData, strContents, strRsltExpr);
}

long CSttAtsTestClient::Ats_AddMacro(const CString &strParentItemPath, const CString &strItemName, const CString &strItemID, const CString& strMacroID, const CString &strItemParas,bool bDoEvents,CSttCmdData *pRetData)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Ats_AddMacro(strParentItemPath, strItemName, strItemID, strMacroID, strItemParas, bDoEvents, pRetData);
}
///////////////////////////////////////////////////////////////////////////////
//事件接口
//直接从CSttPowerTestEngineBase拷贝过来，后期再考虑封装
void CSttAtsTestClient::OnException(CDataGroup *pParas)
{
	if (m_pXClientEngine == NULL)
	{
		return;
	}

	POS pos = pParas->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *p1 = NULL;
	CDataGroup *pModule = NULL;
	CDataGroup *pCh = NULL;
	POS posCh = NULL;
	m_oExceptionTick.Enter();

	long bOverHot_New = 0,bUShort_New = 0,bIBreak_New = 0;
	CExBaseList *pTestGlobalParas = m_pXClientEngine->GetTestGlobalParas();
	bIBreak_New = stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_IBreak, 0);
	bUShort_New = stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_UShort, 0);
	bOverHot_New = stt_GetDataValueByID2(pTestGlobalParas, STT_SYS_STATE_ID_OverHeat, 0);
	
	while(pos != NULL)
	{
		p = pParas->GetNext(pos);

		if (p->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pModule = (CDataGroup *)p;

		if (pModule->m_strDataType != _T("Module"))
		{
			continue;
		}

		CString strModuleType;
		stt_GetDataValueByID(pModule, _T("ModuleType"), strModuleType);

		//解析温度上、中、下
		float fT1 = 0.0,fT2 = 0.0,fT3 = 0.0;
		stt_GetDataValueByID(pModule, _T("T1"), fT1);
		stt_GetDataValueByID(pModule, _T("T2"), fT2);
		stt_GetDataValueByID(pModule, _T("T3"), fT3);

		if (fT1 > 85)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_EXCEPTION,_T("模块(%s,%s)的温度(上)值(%f)超限值85°"),pModule->m_strName.GetString()
				,strModuleType.GetString(),fT1);
//			bIsHot = TRUE;
		}

		if (fT2 > 85)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_EXCEPTION,_T("模块(%s,%s)的温度(下)值(%f)超限值85°"),pModule->m_strName.GetString()
				,strModuleType.GetString(),fT2);
//			bIsHot = TRUE;
		}

		if (fT3 > 85)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_EXCEPTION,_T("模块(%s,%s)的温度(中)值(%f)超限值85°"),pModule->m_strName.GetString()
				,strModuleType.GetString(),fT3);
//			bIsHot = TRUE;
		}

		posCh = pModule->GetHeadPosition();
		while(posCh != NULL)
		{
			p1 = pModule->GetNext(posCh);

			if (p1->m_strID == _T("DisableType"))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s被禁用(%s),模块类型(%s)."),pModule->m_strName.GetString(),p1->m_strName.GetString(),strModuleType.GetString());
			}

// 			if (p1->GetClassID() != DTMCLASSID_CDATAGROUP)
// 			{
// 				continue;
// 			}
// 
// 			pCh = (CDataGroup *)p1;
// 
// 			if (pCh->m_strDataType != _T("Channel"))
// 			{
// 				continue;
// 			}
//
// 			long nIsOverLoad = 0;
// 			stt_GetDataValueByID(pCh, _T("IsOverLoad"), nIsOverLoad);
// 
// 			if (nIsOverLoad)
// 			{
// 				if (strModuleType == STT_MODULE_TYPE_VOLT_ID)
// 				{
// 					bIsUOverLoad = TRUE;
// 				}
// 				else
// 				{
// 					bIsIOverLoad = TRUE;
// 				}	
// 			}
		}
	}

	m_pLastEventResult = &m_oCurrEventResult;
	
	if((m_pLastEventResult->m_nUOverLoad != (long)bUShort_New)
		|| (m_pLastEventResult->m_nIOverLoad != (long)bIBreak_New)
		|| (m_pLastEventResult->m_nOverHeat != (long)bOverHot_New))
	{
// 		CEventResult *pEventInfo = (CEventResult *)m_pLastEventResult->Clone();
		m_pLastEventResult->m_nUOverLoad = bUShort_New;
		m_pLastEventResult->m_nIOverLoad = bIBreak_New;
		m_pLastEventResult->m_nOverHeat = bOverHot_New;

		if ((m_pAtsEventRcv != NULL))
		{
			m_pAtsEventRcv->OnUpdateException();
		}

// 
// 		if (bIsHot || bIsUOverLoad || bIsIOverLoad)
// 		{
// 			pEventInfo->m_strEventID = SYS_STATE_EXCEPTION;
// 		}
// 		else
// 		{
// 			pEventInfo->m_strEventID = SYS_STATE_UNEXCEPTION;
// 		}
// 		
// 		pEventInfo->CopyOwn(&m_oCurrEventResult);
// 		AppenEventInfo(pEventInfo);
	}
}

void CSttAtsTestClient::ValidExceptionTimeOut()
{
	if (m_pXClientEngine == NULL)
	{
		return;
	}

	if (m_oCurrEventResult.m_nUOverLoad || m_oCurrEventResult.m_nIOverLoad || m_oCurrEventResult.m_nOverHeat)
	{
		m_oCurrEventResult.m_nUOverLoad = 0;
		m_oCurrEventResult.m_nIOverLoad = 0;
		m_oCurrEventResult.m_nOverHeat = 0;
		CExBaseList *pTestGlobalParas = m_pXClientEngine->GetTestGlobalParas();
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_IBreak, "0");
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_UShort, "0");
		stt_SetDataValueByID(pTestGlobalParas, STT_SYS_STATE_ID_OverHeat, "0");

		if ((m_pAtsEventRcv != NULL))
		{
			m_pAtsEventRcv->OnUpdateException();
		}
	}
}

long CSttAtsTestClient::OnDisConnect()
{
	m_bTestAppConnect = FALSE;

	if ((m_pAtsEventRcv != NULL)&&(m_pXClientEngine != NULL))
	{
		m_pAtsEventRcv->OnConnectStateChanged(false);//断链事件处理，Linux下不用 Window下用 sf 20220225
	}

	return 1;
}

//直接从CSttPowerTestEngineBase拷贝过来，后期再考虑封装
void CSttAtsTestClient::OnTestState(const CString &strMacroID, CDataGroup *pParas)
{
	double fTime = 0,fRealTime = 0;
	CString strTimeStr;
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_Time, fTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_RealTime, fRealTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_TimeStr, strTimeStr);

	// 	CDataGroup *pEventGroup = (CDataGroup *)pParas->FindByID(_T("Event"));
	// 	if ((pEventGroup == NULL) 
	// 		|| (pEventGroup->GetClassID() != DTMCLASSID_CDATAGROUP))
	// 	{
	// 		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("OnTestState:not find EventGroup"));
	// 		return;
	// 	}

	BOOL bRetIn = FALSE;
	BOOL bRetInEx = FALSE;
	BOOL bRetOut = FALSE; 
	BOOL bRetOutEx = FALSE;

	CString strTemp,strTmpTime;
	SYSTEMTIME tm;
	char strName[10];
	long nVal = 0;
	int i=0;

	CEventResult *pEventInfo = NULL;
	
	//处理开入变位
	if (pParas->m_strID == SYS_STATE_XEVENT_EVENTID_BIN)
	{
		if (!m_bLockFlag && fRealTime==0)
		{ 
			//开入(事件ID用参数更新)
			pEventInfo = InitEvent(SYS_STATE_RETTYPE_UPDATE,fTime,fRealTime,strTimeStr);
			for (i=1; i<=MAX_BINARYIN_COUNT; i++)
			{
				sprintf(strName,"Bin%03d",i);
				if (stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinIn[i-1]))
				{
					bRetIn = TRUE;
				}
			}

			if(bRetIn)
			{
				pEventInfo->CopyOwn(&m_oCurrEventResult);
				pEventInfo->m_fTime = fTime;
				AppenEventInfo(pEventInfo);
			}

			return;
		}

		pEventInfo = InitEvent(SYS_STATE_REPORT_OnSwichInChanged,fTime,fRealTime,strTimeStr);
		for (i=1; i<=MAX_BINARYIN_COUNT; i++)
		{
			sprintf(strName,"Bin%03d",i);
			if (stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinIn[i-1]))
			{
				bRetIn = TRUE;
			}
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BinEx%03d",i);
			if(stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinInEx[i-1]))
			{
				bRetInEx = TRUE;

				tm = pEventInfo->m_tmEvent;
				strTmpTime.Format(_T("%d-%d-%d %d-%d-%d.%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);

				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("扩展开入%d 状态：%d，变位时间：%s"),i,pEventInfo->m_BinInEx[i-1],strTmpTime.GetString());
			}
		}

		stt_GetDataValueByID(pParas, "BinActTime", pEventInfo->m_fActTime);	//取得开入动作时间

		if(bRetIn/*||bRetInEx*/)
		{
			pEventInfo->CopyOwn(&m_oCurrEventResult);
			pEventInfo->m_fTime = fTime;
			AppenEventInfo(pEventInfo);
		}
		else
		{
			delete pEventInfo;
		}
	}
	else if(pParas->m_strID == SYS_STATE_XEVENT_EVENTID_BOUT)
	{
		if (!m_bLockFlag && fRealTime==0)
		{ 
			//开出(事件ID用参数更新)
			pEventInfo = InitEvent(SYS_STATE_RETTYPE_UPDATE,fTime,fRealTime,strTimeStr);
			for (i=1; i<=MAX_BINARYOUT_COUNT; i++)
			{
				sprintf(strName,"Bout%03d",i);
				if (stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinOut[i-1]))
				{
					bRetOut = TRUE;
				}
			}

			if(bRetOut)
			{
				pEventInfo->CopyOwn(&m_oCurrEventResult);
				pEventInfo->m_fTime = fTime;
				AppenEventInfo(pEventInfo);
			}

			return;
		}

		pEventInfo = InitEvent(SYS_STATE_REPORT_OnSwichOutChanged,fTime,fRealTime,strTimeStr);
		for (i=1; i<=MAX_BINARYOUT_COUNT; i++)
		{
			sprintf(strName,"Bout%03d",i);
			if (stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinOut[i-1]))
			{
				bRetOut = TRUE;
			}
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BoutEx%03d",i);
			if(stt_GetDataValueByID(pParas, strName, pEventInfo->m_BinOutEx[i-1]))
			{
				bRetOutEx = TRUE;

				tm = pEventInfo->m_tmEvent;
				strTmpTime.Format(_T("%d-%d-%d %d-%d-%d.%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);

				//				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("扩展开出%d 状态：%d，变位时间：%s"),i,pEventInfo->m_BinOutEx[i-1],strTmpTime.GetString());
			}
		}

		if(bRetOut/*||bRetOutEx*/)
		{
			pEventInfo->CopyOwn(&m_oCurrEventResult);
			pEventInfo->m_fTime = fTime;
			AppenEventInfo(pEventInfo);
		}
		else
		{
			delete pEventInfo;
		}
	}
	else//如果没有开入、开出变位，则认为是状态切换或直流输出事件
	{
		if (stt_GetDataValueByID(pParas, STT_SYS_STATE_ID_StateChange, nVal))
		{
			if (nVal >= 0)
			{
				CEventResult *pEventInfo = InitEvent(SYS_STATE_REPORT_OnStateChanged,fTime,fRealTime,strTimeStr);
				pEventInfo->m_nCurrStateIndex = nVal;

				pEventInfo->CopyOwn(&m_oCurrEventResult);
				AppenEventInfo(pEventInfo);
			}	
		}

		if (stt_GetDataValueByID(pParas, STT_SYS_STATE_ID_Udc, nVal))
		{
			CEventResult *pEventInfo = InitEvent(SYS_STATE_REPORT_OnUdcChanged,fTime,fRealTime,strTimeStr);
			pEventInfo->m_nUdc = nVal;

			pEventInfo->CopyOwn(&m_oCurrEventResult);
			AppenEventInfo(pEventInfo);
		}
	}
}

//2022-10-6  lijunqing  美化OnRtData
void AtsTestClient_OnRtData_GlobalRtDataMngr(CDataGroup *pRtDataGroup)
{
	CSttGlobalRtDataMngr *pRtDataMngr = &g_oSttTestResourceMngr.m_oRtDataMngr;
	double dTime = 0,dRealTime = 0;

	if (!stt_GetDataValueByID(pRtDataGroup, TMT_RESULT_ID_Time, dTime))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取实时数据绝对时间失败."));
	}

	if (!stt_GetDataValueByID(pRtDataGroup, TMT_RESULT_ID_RealTime, dRealTime))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取实时数据相对时间失败."));
		return;
	}

	if (pRtDataMngr->m_nMode == STT_RT_DATA_MODE_SYN)
	{
		ASSERT(pRtDataMngr->m_pMacroChannels);
		CSttMacroChannels *pMacroChs = pRtDataMngr->m_pMacroChannels;
		CSttMacroChannel *pMacroCh = NULL;
		CDataGroup *pDataGroup = NULL;

		pMacroChs->m_oHisTimesBuf.AppendBuffer(&dTime,1);
		pMacroChs->m_oHisRealTimesBuf.AppendBuffer(&dRealTime,1);
		POS pos = pMacroChs->GetHeadPosition();

		while(pos)
		{
			pMacroCh = (CSttMacroChannel *)pMacroChs->GetNext(pos);
			pDataGroup = (CDataGroup*)pRtDataGroup->FindByID(pMacroCh->m_strID);

			if (pDataGroup == NULL)
			{
				//					pMacroCh->m_oRtDataCh.m_fMag = 0;
				//					pMacroCh->m_oHisMagBuf.AppendBuffer(&pMacroCh->m_oRtDataCh.m_fMag,1);//yyj delete 2021-08-25
				pMacroCh->m_oHisDataBuf.AppendBuffer(&pMacroCh->m_oRtDataCh,1);	//yyj add 2021-08-25
				//					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("实时数据中缺少(name=%s;id=%s;)通道."),pMacroCh->m_strName.GetString(),pMacroCh->m_strID.GetString());
				continue;
			}

			stt_GetDataValueByID(pDataGroup,_T("mag"), pMacroCh->m_oRtDataCh.m_fMag);
			stt_GetDataValueByID(pDataGroup,_T("ang"), pMacroCh->m_oRtDataCh.m_fAng);
			stt_GetDataValueByID(pDataGroup,_T("freq"), pMacroCh->m_oRtDataCh.m_fFreq);
			//				pMacroCh->m_oHisMagBuf.AppendBuffer(&pMacroCh->m_oRtDataCh.m_fMag,1);//yyj delete 2021-08-25
			pMacroCh->m_oHisDataBuf.AppendBuffer(&pMacroCh->m_oRtDataCh,1);	//yyj add 2021-08-25
		}

		pRtDataMngr->FireRtDataChangeEvent(); //yyj add 20211108
	}
	else if (pRtDataMngr->m_nMode == STT_RT_DATA_MODE_ASYN)
	{
	}
	else
	{
		
	}
}

//直接从CSttPowerTestEngineBase拷贝过来，后期再考虑封装
long CSttAtsTestClient::OnRtData(CSttParas *pParas)
{
	CExBaseObject *pChildObj = NULL;
	POS pos = pParas->GetHeadPosition();
	CDataGroup *pRtDataGroup = NULL;

	while(pos)
	{
		pChildObj = pParas->GetNext(pos);

		if (pChildObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pRtDataGroup = (CDataGroup *)pChildObj;

		if (pRtDataGroup->m_strID == XPARA_ID_IEC_CB)
		{
			m_pAtsEventRcv->On_IecDetect(pRtDataGroup);
			continue;
		}

		if (pRtDataGroup->m_strID == SYS_STATE_XEVENT_EVENTID_SYNCTIME)
		{
			//FrameBase中解析完成后删除
			CDataGroup* pCopy = (CDataGroup*)pRtDataGroup->Clone();
			OnUpdateSyncTime(pCopy);
			continue;
		}

		if (pRtDataGroup->m_strID == SYS_STATE_XEVENT_EVENTID_RtData)
		{////2022-10-6  lijunqing
			m_pAtsEventRcv->On_RtData(pRtDataGroup);  //实时数据处理
			AtsTestClient_OnRtData_GlobalRtDataMngr(pRtDataGroup);  //美化函数
		}
	}

	if (m_oExceptionTick.GetTickCountLong(FALSE)>STT_EXCEPTION_TIMEOUT)
	{
		ValidExceptionTimeOut();
	}

	return 1;
}

long CSttAtsTestClient::OnMeas(CDataGroup *pParas)
{
	return 0;
}

void CSttAtsTestClient::OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex
								 , const CString & strItemID, long nState, CSttParas *pParas)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	if (pParas->m_strID == STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
	{
		m_pAtsEventRcv->OnReport_ReadDevice((CDataGroup*)pParas->FindByID(_T("Device")));
		return;
	}

	if(!IsAtsRetCmd(pParas))
	{
		return;
	}

	m_pAtsEventRcv->OnReport(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, nState, pParas);
}

BOOL CSttAtsTestClient::IsAtsRetCmd(CSttParas *pParas)
{
	CSttSysState* pSysState = (CSttSysState*)pParas->GetParent();

	if (pSysState == NULL)
	{
		return FALSE;
	}

	if (pSysState->m_strRetSttCmd != STT_CMD_SYSSTATE_ATS)
	{
		return FALSE;
	}

	return TRUE;
}

long CSttAtsTestClient::OnItemStateChanged(const CString &strTestID, long nDeviceIndex, long nReportIndex
										   , long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas)
{
	if (m_pAtsEventRcv == NULL)
	{
		return 0;
	}

	if(!IsAtsRetCmd(pParas))
	{
		return 0;
	}

	return m_pAtsEventRcv->OnItemStateChanged(strTestID, nDeviceIndex, nReportIndex, nItemIndex, strItemID, nState, pParas);
}

void CSttAtsTestClient::OnTestInitialize(CEventResult *pEventInfo,CDataGroup *pParas)
{
	ASSERT(pParas != NULL);

	CDataGroup *pEventBinGroup = (CDataGroup*)pParas->FindByID(SYS_STATE_XEVENT_EVENTID_BIN);
	CDataGroup *pEventBoutGroup = (CDataGroup*)pParas->FindByID(SYS_STATE_XEVENT_EVENTID_BOUT);

	int i=0;
	char strName[10];
	if (pEventBinGroup)
	{
		for (i=1; i<=MAX_BINARYIN_COUNT; i++)
		{
			sprintf(strName,"Bin%03d",i);
			stt_GetDataValueByID(pEventBinGroup, strName, pEventInfo->m_BinIn[i-1]);
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BinEx%03d",i);
			stt_GetDataValueByID(pEventBinGroup, strName, pEventInfo->m_BinInEx[i-1]);
		}
	}

	if (pEventBoutGroup)
	{
		for (i=1; i<=MAX_BINARYOUT_COUNT; i++)
		{
			sprintf(strName,"Bout%03d",i);
			stt_GetDataValueByID(pEventBoutGroup, strName, pEventInfo->m_BinOut[i-1]);
		}

		for (i=1; i<=MAX_ExBINARY_COUNT; i++)
		{
			sprintf(strName,"BoutEx%03d",i);
			stt_GetDataValueByID(pEventBoutGroup, strName, pEventInfo->m_BinOutEx[i-1]);
		}
	}
}

long CSttAtsTestClient::OnTestFinished(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	if (m_pAtsEventRcv == NULL)
	{
		return 0;
	}

	if(!IsAtsRetCmd(pParas))
	{
		return 0;
	}

	double fTime = 0,fRealTime = 0;
	CString strTimeStr;
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_Time, fTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_RealTime, fRealTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_TimeStr, strTimeStr);

	CEventResult *pEventInfo = InitEvent(SYS_STATE_EVENT_OnTestFinished,fTime,fRealTime,strTimeStr);
	AppenEventInfo(pEventInfo);

	return m_pAtsEventRcv->OnTestFinished(strTestID, nDeviceIndex, nReportIndex, pParas);
}

long CSttAtsTestClient::OnTestStarted(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	if (m_pAtsEventRcv == NULL)
	{
		return 0;
	}

	if(IsAtsRetCmd(pParas))
	{
		return m_pAtsEventRcv->OnTestStarted(strTestID, nDeviceIndex, nReportIndex, pParas);
	}
	else
	{
		double fTime = 0,fRealTime = 0;
		CString strTimeStr;
		stt_GetDataValueByID(pParas, TMT_RESULT_ID_Time, fTime);
		stt_GetDataValueByID(pParas, TMT_RESULT_ID_RealTime, fRealTime);
		stt_GetDataValueByID(pParas, TMT_RESULT_ID_TimeStr, strTimeStr);

		if (fTime<=0.00001)//zhouhj 20220418 对于Iec等虚拟出来的开始测试命令,直接忽略,不在实际中处理
		{
			return 0;
		}

		CEventResult *pEventInfo = InitEvent(SYS_STATE_EVENT_OnTestStarted,fTime,fRealTime,strTimeStr);

		CDataGroup *pEventBinGroup = (CDataGroup*)pParas->FindByID(SYS_STATE_XEVENT_EVENTID_BIN);
		CDataGroup *pEventBoutGroup = (CDataGroup*)pParas->FindByID(SYS_STATE_XEVENT_EVENTID_BOUT);
		if (pEventBinGroup || pEventBoutGroup)
		{
			OnTestInitialize(pEventInfo,pParas);
		}

		pEventInfo->CopyOwn(&m_oCurrEventResult);
		pEventInfo->m_fTime = fTime;
		AppenEventInfo(pEventInfo);
		return 0;
	}
}

long CSttAtsTestClient::OnTestStoped(const CString &strTestID, long nDeviceIndex, long nReportIndex, CSttParas *pParas)
{
	if (m_pAtsEventRcv == NULL)
	{
		return 0;
	}

	if(!IsAtsRetCmd(pParas))
	{
		return 0;
	}

	double fTime = 0,fRealTime = 0;
	CString strTimeStr;
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_Time, fTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_RealTime, fRealTime);
	stt_GetDataValueByID(pParas, TMT_RESULT_ID_TimeStr, strTimeStr);

	CEventResult *pEventInfo = InitEvent(SYS_STATE_EVENT_OnTestStoped,fTime,fRealTime,strTimeStr);
	AppenEventInfo(pEventInfo);

	return m_pAtsEventRcv->OnTestStoped(strTestID, nDeviceIndex, nReportIndex, pParas);
}

void CSttAtsTestClient::OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults)
{
	m_pAtsEventRcv->OnSearchPointReport(strMacroID, pSearchResults);
}
long CSttAtsTestClient::OnTestCreated(const CString &strTestID, CSttParas *pParas)
{
	if (m_pAtsEventRcv != NULL)
	{
		m_pAtsEventRcv->OnTestCreated(strTestID, pParas);
	}

	return 0;
}

long CSttAtsTestClient::OnEngineEvent(const CString &strTestID, long nDeviceIndex, const CString & strEvent, CSttParas *pParas)
{
	return 0;
}

long CSttAtsTestClient::OnProcessInputDataCmd(CSttParas *pParas,CExBaseList *pMsgs)
{
	if (m_pAtsEventRcv != NULL)
	{
		m_pAtsEventRcv->OnProcessInputDataCmd(pParas, pMsgs);
	}

	return 0;
}

long CSttAtsTestClient::OnTestProcess(CSttParas *pParas)
{
	if (m_pAtsEventRcv != NULL)
	{
		m_pAtsEventRcv->OnTestProcess(pParas);
	}

	return 0;
}

long CSttAtsTestClient::OnExportRptEvent(CSttParas *pParas)
{
	if (m_pAtsEventRcv != NULL)
	{
		m_pAtsEventRcv->OnExportRptEvent(pParas);
	}

	return 0;
}

void CSttAtsTestClient::On_Ats_Generate(const CString &strAtsCmd, CSttParas *pParas)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	m_pAtsEventRcv->On_Ats_Generate(strAtsCmd, pParas);
}

void CSttAtsTestClient::On_Ats_SaveTest(CSttSysState *pSysState)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	m_pAtsEventRcv->On_Ats_SaveTest(pSysState);
}

void CSttAtsTestClient::On_Ats_ExportWordRpt(CSttSysState *pSysState)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	m_pAtsEventRcv->On_Ats_ExportWordRpt(pSysState);
}

void CSttAtsTestClient::On_Ats_SaveTemplate(CSttSysState *pSysState)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	m_pAtsEventRcv->On_Ats_SaveTemplate(pSysState);
}

void CSttAtsTestClient::On_Ats_CreateTest(CSttSysState *pSysState)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	m_pAtsEventRcv->On_Ats_CreateTest(pSysState);
}

/*
<sys-state name="" id="AdjustMainWnd" mid="0" time="2022-07-18 13:50:10" mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type="string" value="3" />
		<data id="main-wnd" data-type="long" value="592258" />【自动测试主窗口的句柄】
	</paras>
</sys-state>
*/
void CSttAtsTestClient::On_Ats_AdjustMainWnd(CSttSysState *pSysState)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	m_pAtsEventRcv->On_Ats_AdjustMainWnd(pSysState);
}

void CSttAtsTestClient::On_Ats_QueryItem(CSttSysState *pSysState)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	m_pAtsEventRcv->On_Ats_QueryItem(pSysState);
}

void CSttAtsTestClient::OnUpdateSyncTime(CDataGroup *pRtSyncTime)
{
	if (m_pAtsEventRcv == NULL)
	{
		return;
	}

	m_pAtsEventRcv->OnUpdateSyncTime(pRtSyncTime);
}

//2022-4-14 lijunqing
void CSttAtsTestClient::Ats_IecDetect(long bEnable)
{
	if (!ConnectAtsTestServer())
	{
		return ;
	}

	CDataGroup oGroup;
	oGroup.AddNewData(_T("Enable"), bEnable);
	m_pXClientEngine->Test_SetParameter(_T("IecDetect"), &oGroup);
}

long CSttAtsTestClient::Ats_SetParameter(const CString &strMacroID, CDataGroup *pParas)
{
	if (!ConnectAtsTestServer())
	{
		return 0;
	}

	return m_pXClientEngine->Test_SetParameter(strMacroID, pParas);
}

void CSttAtsTestClient::Ats_IecRecord(CDataGroup *pIecRecordParas)
{
	if (!ConnectAtsTestServer())
	{
		return ;
	}

	m_pXClientEngine->Test_SetParameter(_T("IecRecord"), pIecRecordParas);
}

