//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestClientBase.cpp  CSttTestClientBase


#include "stdafx.h"
#include "SttTestClientBase.h"

/*
//2020-10-27  lijunqing
//LINUX  只处理单测试仪的测试
#ifndef _PSX_QT_LINUX_
#include "SttTestClientTimer.h"
#endif

#include "SttTestClientSingleTimer.h"
*/

#include "../../../Module/API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttTestClientBase *g_theSingleSttTestClient = NULL;
CSttTestEngineClientData *g_theSingleSttTestEngineClient = NULL;
CSttParas g_oReadDeviceParameter;  //shaolei  2023-12-19

void stt_CreateSingleSttTestClient()
{
	if (g_theSingleSttTestClient == NULL)
	{
		g_theSingleSttTestClient = new CSttTestClientBase();

// 		long nTimerID = stt_test_singleclient_timer_create(5000);
// 		g_theSingleSttTestClient->SetSttClientTimerID(nTimerID); 
	}
}

void stt_RelaseSingleSttTestClient()
{
	if (g_theSingleSttTestClient != NULL)
	{
// 		stt_test_singleclient_timer_free(g_theSingleSttTestClient->GetSttClientTimerID());
		delete g_theSingleSttTestClient;
		g_theSingleSttTestClient = NULL;
	}
}

CSttTestClientBase::CSttTestClientBase()
{
	m_pTestEventRcv = NULL;
	m_pXClientEngine = NULL;
	m_pFileTransferProgress = NULL;
	m_nSttClientTimerID = -1;
	m_oTestAppCfg.SttOpen(_T(""));

	//2021-9-2  lijunqing
	CreateXTimer();
}

CSttTestClientBase::~CSttTestClientBase()
{
	CXTimer::DestroyWindow();

	FreeXClientEngine();
}

void CSttTestClientBase::SetTestEventInterface(CTestEventBaseInterface *pTestEventRcv)
{
	m_pTestEventRcv = pTestEventRcv;
	CSttTestEngineClientData *pClient = GetTestEngineClient();
	
	if (pClient != NULL)
	{
		pClient->SetTestEventInterface(pTestEventRcv);
	}
}

long CSttTestClientBase::SetTestAppConfig(CSttTestAppCfg *pSttTestAppCfg)
{
	pSttTestAppCfg->Copy(&m_oTestAppCfg);

	return 0;
}

long CSttTestClientBase::SetTestAppConfig(const CString & bstrConfig)
{
	m_oTestAppCfg.SttSetXml(bstrConfig);

	return 0;
}

BOOL CSttTestClientBase::IsConnectSuccess()
{
	if (m_pXClientEngine == NULL)
	{
		return FALSE;
	}

	return m_pXClientEngine->IsConnectServerSucc();
}

void CSttTestClientBase::DisConnect()
{
	KillSttTimer();
	FreeXClientEngine();
}

void CSttTestClientBase::StopTest()
{
	if (m_pXClientEngine == NULL)
	{
		return;
	}

	m_pXClientEngine->Test_StopTest(_T(""));
}

void CSttTestClientBase::CloseDevice(const CString &strDeviceSN)
{
	if (m_pXClientEngine == NULL)
	{
		return;
	}

	m_pXClientEngine->Test_CloseDevice();
}

//2022-10-23  lijunqing
void CSttTestClientBase::SetSttCmdDataFormat(long nSttCmdDataFormat)
{
	if (m_pXClientEngine != NULL)
	{
		m_pXClientEngine->SetSttCmdDataFormat(nSttCmdDataFormat);
	}
}

void CSttTestClientBase::FreeXClientEngine()
{
	if (m_pXClientEngine != NULL)
	{
       // stt_test_singleclient_timer_free(m_nSttClientTimerID);
		m_pXClientEngine->PrepareFreeClientEngine();

		delete m_pXClientEngine;
		m_pXClientEngine = NULL;
	}
}

void CSttTestClientBase::DisConnectForClose(BOOL bDelete)
{
	if (m_pXClientEngine == NULL)
	{
		return;
	}

	if (m_pXClientEngine->m_pSttClientSocket != NULL)
	{
		m_pXClientEngine->m_pSttClientSocket->CloseSttXcmdCh();
	}

	if (bDelete)
	{
		delete m_pXClientEngine;
		m_pXClientEngine = NULL;
	}
}

BOOL CSttTestClientBase::OnTimer(UINT nTimerID, DWORD dwTime)
{
	if (m_nSttClientTimerID == -1)
	{
		return FALSE;
	}

	if (m_nSttClientTimerID != nTimerID)
	{
		return FALSE;
	}

	if (m_pXClientEngine == NULL)
	{
		return TRUE;
	}

	if (m_pXClientEngine->IsConnectServerSucc())
	{
		Test_SendHeartbeat();
	}
	else
	{
		KillSttTimer();
	}

	return TRUE;
}

BOOL CSttTestClientBase::ConnectSttServer(CSttTestAppConfigTool *pTool, CString &strErrorInfo)
{
	if (m_oTestAppCfg.IsLocal())
	{
		if (!CSttTestAppConfigTool::IsTestAppExist(&m_oTestAppCfg, strErrorInfo))
		{
			return FALSE;
		}
	}

    //FreeXClientEngine();  // shaolei 20201212  断链会导致输出无法保持，故注释
	if (pTool != NULL)
	{
		pTool->m_pSttTestMsgViewInterface = this;

		m_pXClientEngine = pTool->CreateTestEngine(&m_oTestAppCfg, strErrorInfo);
	}
	else
	{
		CSttTestAppConfigTool oSttTestAppConfigTool;
		oSttTestAppConfigTool.m_pSttTestMsgViewInterface = this;

		m_pXClientEngine = oSttTestAppConfigTool.CreateTestEngine(&m_oTestAppCfg, strErrorInfo);
	}

	if (m_pTestEventRcv != NULL && m_pXClientEngine != NULL)
	{
		m_pXClientEngine->SetTestEventInterface(m_pTestEventRcv);
	}

	return (m_pXClientEngine != NULL);
}

void CSttTestClientBase::ConfigTest(CSttTestAppConfigTool *pTool)
{
#ifndef _PSX_IDE_QT_
	CSttTestAppConfigTool oSttTestAppConfigTool;

	if (pTool == NULL)
	{
		pTool = &oSttTestAppConfigTool;
	}

	pTool->m_pSttTestAppCfg = &m_oTestAppCfg;
	pTool->TestAppConfig(&m_pXClientEngine, this, AfxGetMainWnd());

	if (m_pXClientEngine != NULL)
	{
		m_pXClientEngine->SetTestEventInterface(m_pTestEventRcv);
	}

#endif
}

void CSttTestClientBase::OnTestMsg(BYTE *pBuf, long nLen)
{
	if (m_pTestEventRcv != NULL)
	{
		m_pTestEventRcv->OnTestMsg(pBuf, nLen);
	}
}

void CSttTestClientBase::OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType)
{
	// 	LogString(XLOGLEVEL_TRACE, pszCmdID);
	// 
	// 	char *pszCmdString = (char*)(pBuf+STT_PKG_HEAD_LEN);
	// 	long nStrLen = nLen - STT_PKG_HEAD_LEN;
	// 	nLen += nLen / 10;
	// 	char *pNewString = new char [nLen];
	// 	char *pDest=pNewString, *pSrc = pszCmdString;
	// 	char *pEnd = pszCmdString + nStrLen;
	// 
	// 	while (pSrc <= pEnd)
	// 	{
	// 		if (*pSrc == 0x0a)
	// 		{
	// 			*pDest = 0x0d;
	// 			pDest++;
	// 			nStrLen++;
	// 		}
	// 
	// 		*pDest = *pSrc;
	// 		pSrc++;
	// 		pDest++;
	// 	}
	// 
	// 	*pDest = 0;
	// 
	// 
	// 	wchar_t *pwszGbk = NULL;
	// 	long nDestLen = 0;
	// 	charUtf8_to_wcharGBK(pNewString, nStrLen, &pwszGbk, nDestLen);
	// 	CString strText;
	// 	strText = pwszGbk;
	// 
	// 	nLen = m_wndCmdReceive.GetWindowTextLength();
	// 	m_wndCmdReceive.SetSel(nLen, -1);
	// 	m_wndCmdReceive.ReplaceSel(strText);
	// 	m_wndCmdReceive.ReplaceSel(_T("\r\n"));
	// 
	// 	if (m_bWriteCmdFile)
	// 	{
	// 		m_oFile.Write(strText, strText.GetLength());
	// 		m_oFile.Write(_T("\r\n"), 2);
	// 	}
	// 
	// 	delete pNewString;
	// 	delete pwszGbk;
}

void CSttTestClientBase::On_Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{

}

void CSttTestClientBase::RemovePkgDispatchInterface(CSttPkgDispatchInterface *p)
{
	if (m_pXClientEngine != NULL)
	{
		m_pXClientEngine->RemovePkgDispatch(p);
	}
}

void CSttTestClientBase::AddPkgDispatchInterface(CSttPkgDispatchInterface *p)
{
	if (m_pXClientEngine != NULL)
	{
		m_pXClientEngine->AddPkgDispatch(p);
	}
}
///
long CSttTestClientBase::SendTestCmd(CSttTestCmd *pTestCmd)
{
	if (m_pXClientEngine == NULL)
	{
		return -1;
	}

	//改为同步发送  2023-7-6
	return m_pXClientEngine->SendCmdAsync(pTestCmd,g_nTimeOut_Test);
	//long nExecStatus = m_pXClientEngine->SendCmdSync(pTestCmd,g_nTimeOut_Test,NULL,TRUE);

	//return nExecStatus;
}

long CSttTestClientBase::SendTestCmd(BYTE *pBuf, long nLen)
{
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("++++CSttTestClientBase::SendTestCmd++++"));
	if (m_pXClientEngine == NULL)
	{
		//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("++++CSttTestClientBase::SendTestCmd++++ m_pXClientEngine == NULL"));
		return -1;
	}

	long nRet = m_pXClientEngine->SendBuffer(pBuf, nLen);

	if (nRet == 0)
	{
		return -1;
	}

	return nRet;
}

//////////////////////////////////////////////////////////////////////////
//
//system command
//lijunqing 2021-8-14  将System_Login 从 SttMacroTest 移到此处，便于封装
long CSttTestClientBase::System_LoginEx()
{
	if (m_oTestAppCfg.IsLocal())
	{
		return Login_Local();
	}

	return Login_Remote();
}

long CSttTestClientBase::Login_Local()
{
	return System_Login_Local_Test();
}

long CSttTestClientBase::Login_Remote()
{
	if (m_oTestAppCfg.IsLocal())
	{
		return 0;
	}

	//远程要先查询再登录；
	CSttCmdData oRetData;
	CSttTestEngineClientData* pClientData = GetTestEngineClient();
	long nExecStatus = pClientData->Remote_Query(_T(""),TRUE,&oRetData);
	if (Stt_Is_ExecStatus_Success(nExecStatus))
	{
		CSttTestEngineRemoteClientData *pRemoteEngine = (CSttTestEngineRemoteClientData *)pClientData;

		if (pRemoteEngine != NULL)
		{
			CString strSN = m_oTestAppCfg.GetTestAppSN();
			CSttTestRemoteRegister *pSelRegister = pRemoteEngine->FindRegisterBySN(strSN);

			if (pSelRegister == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("查询注册的测试仪失败，测试仪SN=%s"), strSN.GetString());
				return 0;
			}

			CSttTestClientUser oUser;
			oUser.id_soft(STT_SOFT_ID_TEST);
			oUser.Name_User(_T("SmartTest"));
			oUser.Name_Cop(_T("PowerSky"));
			oUser.SN_TestApp(pSelRegister->SN_TestApp());
			oUser.Code_Register(pSelRegister->Code_Register());

			return Remote_BindAndLogin(pSelRegister,&oUser);
		}
	}

	return 0;  //表示失败
}

long CSttTestClientBase::Remote_BindAndLogin(CSttTestRemoteRegister *pRegister,CSttTestClientUser *pUser)
{
	if (m_oTestAppCfg.IsLocal())
	{
		return 0;
	}

	CSttTestEngineClientData* pClientData = GetTestEngineClient();
	long nExecStatus = pClientData->Remote_Bind(pRegister);

	if (nExecStatus != STT_CMD_ExecStatus_SUCCESS)
	{
		return 0;
	}

	pClientData->m_oCurrUser.DeleteAll();
	pClientData->m_oCurrUser.AppendEx(*pUser);
	pUser->RemoveAll();

	//设置LocalIP
	pClientData->m_pSttClientSocket->SttXmdChAddr(m_oTestAppCfg.GetLocalIP() );

	pClientData->m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_REMOTE);
	pClientData->m_pSttClientSocket->SetSocketType(STT_SOCKET_TYPE_REMOTE);
	pClientData->m_oCurrUser.ID_Tester(g_nIDTester);
	pClientData->m_oCurrUser.IP_User(pClientData->m_pSttClientSocket->SttXmdChAddr());

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("登录远程测试仪【SN=%s】"), pRegister->SN_TestApp().GetString());
	return pClientData->System_Login();
}


long CSttTestClientBase::System_SetSysConfig(CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_SetSysConfig(pParas, bDoEvents, pRetData);
}

long CSttTestClientBase::System_GetSysConfig(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_GetSysConfig(bDoEvents, pRetData);
}

long CSttTestClientBase::System_Login(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_Login(bDoEvents, pRetData);
}

long CSttTestClientBase::System_Login_Local_Test(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_Login_Local_Test(bDoEvents, pRetData);
}

long CSttTestClientBase::System_Login_Local_ATS(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_Login_Local_ATS(bDoEvents, pRetData);
}

long CSttTestClientBase::System_Login_Local(const CString &strTestID,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_Login_Local(strTestID,bDoEvents, pRetData);
}

long CSttTestClientBase::System_Logout(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_Logout(bDoEvents, pRetData);
}

long CSttTestClientBase::System_Request(const CString &strAuthorityID, long nAuthorityVal,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_Request(strAuthorityID,nAuthorityVal,bDoEvents, pRetData);
}

long CSttTestClientBase::System_Authority(const CString &strAuthorityID, long nAuthorityVal,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->System_Authority(strAuthorityID,nAuthorityVal,bDoEvents, pRetData);
}


//Remote cmd
long CSttTestClientBase::Remote_Bind(CSttTestRemoteRegister *pRegister,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Remote_Bind(pRegister,bDoEvents, pRetData);
}

long CSttTestClientBase::Remote_Query(const CString &strCode_Register,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Remote_Query(strCode_Register,bDoEvents, pRetData);
}

long CSttTestClientBase::Remote_Register(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Remote_Register(bDoEvents, pRetData);
}

long CSttTestClientBase::Remote_UnRegister(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Remote_UnRegister(bDoEvents, pRetData);
}


//Smart Test Terminal : Test Command
long CSttTestClientBase::Test_SetParameter(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Test_SetParameter(strMacroID, pParas,bDoEvents, pRetData);
}
//Preset test parameters
long CSttTestClientBase::Test_UpdateParameter(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Test_UpdateParameter(strMacroID, pParas,bDoEvents, pRetData);
}

long CSttTestClientBase::Test_StartTest(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Test_StartTest(strMacroID, pParas, bDoEvents, pRetData, bSendCmdAsync);
}
//start testing
long CSttTestClientBase::Test_StopTest(const CString &strMacroID,BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Test_StopTest(strMacroID,bDoEvents, pRetData, bSendCmdAsync);
}
//Stop testing
long CSttTestClientBase::Test_GetReport(const CString &strMacroID,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Test_GetReport(strMacroID,bDoEvents, pRetData);
}
//Get report data
long CSttTestClientBase::Test_CloseDevice(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Test_CloseDevice(bDoEvents, pRetData);
}
//Turn off the device
long CSttTestClientBase::Test_GetSystemState(CStringArray &astrTypes, BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Test_GetSystemState(astrTypes, bDoEvents, pRetData);
}
//Query system status
long CSttTestClientBase::Test_SendHeartbeat()
{
	if (m_pXClientEngine == NULL)
    {
		return 0;
	}

	return m_pXClientEngine->Test_SendHeartbeat();
}


//校准命令：adj-cmd
long CSttTestClientBase::Adjust_Adjust(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Adjust_Adjust(strMacroID, pParas,bDoEvents, pRetData, bSendCmdAsync);
}

long CSttTestClientBase::Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents,CSttCmdData *pRetData,BOOL bSendCmdAsync)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Adjust_ReadDeviceParameter(astrTypes,bDoEvents, pRetData, bSendCmdAsync);
}

long CSttTestClientBase::Adjust_WriteFile(BOOL bSendCmdAsync, BOOL bDoEvents)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Adjust_WriteFile(bSendCmdAsync, bDoEvents);
}


//2021-9-30  lijunqing
long CSttTestClientBase::Meas_Read(BOOL bSendCmdAsync, BOOL bDoEvents)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Meas_Read(bSendCmdAsync, bDoEvents);
}


//2020-10-09 文件处理  lijunqing
//读文件 strRealFilePath，目标文件相对路径，例如："Config/DeviceSystemParas.xml"  strDestFilePath,本地绝对路径
long CSttTestClientBase::ReadFile(const CString &strSrcFileRealPath, const CString &strDestFilePath,CSttSocketFileTransferProgress *pProgress)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->ReadFile(strSrcFileRealPath, strDestFilePath, pProgress);
}

//写文件：strSrcFilePath，本地绝对路径；strSrcFileRealPath目标文件相对路径
long CSttTestClientBase::Write(const CString &strSrcFilePath, const CString &strDestFileRealPath,CSttSocketFileTransferProgress *pProgress)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Write(strSrcFilePath, strDestFileRealPath,pProgress);
}


//故障回放命令
//上位机给测试仪：手动触发命令、数据发送完成命令
long CSttTestClientBase::Test_SendTrigger()
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Test_SendTrigger();
}

long CSttTestClientBase::Comtrade_SendDataFinish(long nIndex,long nSendLen,BOOL bLast)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Comtrade_SendDataFinish(nIndex,nSendLen,bLast);
}

long CSttTestClientBase::Comtrade_SendDataStart(long nIndex,long nSendLen)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Comtrade_SendDataStart(nIndex,nSendLen);
}


//ats cmd
long CSttTestClientBase::Ats_CreateTest(const CString &strTestID,const CString &strGbXmlFile,const CString &strPpXmlFile
										,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_CreateTest(strTestID, strGbXmlFile, strPpXmlFile, strDvmFile, strCommCfgFile, pCommParas, bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_ConnectDevice(const CString &strPpXmlFile,const CString &strDvmFile,CDataGroup *pCommParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ConnectDevice(strPpXmlFile, strDvmFile,pCommParas,bDoEvents, pRetData);
}


long CSttTestClientBase::Ats_StartTest(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

    return m_pXClientEngine->Ats_StartTest(NULL, NULL, NULL, NULL, bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_StopTest(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_StopTest(bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_CloseTest(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_CloseTest(bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_SetItemState(const CString &strItemPath,long nSelect,long nEnable,long nShow,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SetItemState(strItemPath,nSelect,nEnable,nShow,bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_TestItem (const CString &strItemPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

//	Ats_SetItemState(const CString &strItemPath,long nSelect,long nEnable,long nShow,BOOL bDoEvents,CSttCmdData *pRetData)

 	return m_pXClientEngine->Ats_TestItem(strItemPath,bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_TestFrom (const CString &strItemPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_TestFrom(strItemPath,bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_TestAllFailedItems(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_TestAllFailedItems(bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_GetReportFile(long nGbrptFile,long nXmlRptFile,const CString &strDestPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_GetReportFile(nGbrptFile,nXmlRptFile,strDestPath,bDoEvents, pRetData);
}

long CSttTestClientBase::GetSystemState(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->GetSystemState(bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_CreateDevice(const CString &strDeviceID,const CString &strPpXmlFile
										  ,const CString &strDvmFile,const CString &strCommCfgFile,CDataGroup *pCommParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_CreateDevice(strDeviceID, strPpXmlFile, strDvmFile, strCommCfgFile, pCommParas, bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_ConfigDevice(CDataGroup *pCommParas,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ConfigDevice(pCommParas,bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_GetDataset(const CString &strDatasetPath,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_GetDataset(strDatasetPath,bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_SetDataset(const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_SetDataset(strDatasetPath,pDataset,bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_RunProcedure(CDvmData *pData,const CString &strDatasetPath,CDvmDataset *pDataset,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_RunProcedure(pData,strDatasetPath,pDataset,bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_CloseDevice(const CString &strDeviceID,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_CloseDevice(strDeviceID,bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_ConfigEngine(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
										  ,long nLogDebugInfor,long nNoChangeWhenSame,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_ConfigEngine( nLogDataBind, nLogPkgDataInfor, nLogPkg, nLogDebugInfor, nNoChangeWhenSame, bDoEvents, pRetData);
}

long CSttTestClientBase::Ats_FinishInputData(CDataGroup *pDatas,CExBaseList *pMsgs)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Ats_FinishInputData(pDatas,pMsgs);
}

//debug command
long CSttTestClientBase::Debug_Command(const CString &strCmdID,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_Command(strCmdID,bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetProcessState(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetProcessState(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetMemState(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetMemState(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetTestParas(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetTestParas(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetTestReports(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetTestReports(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetBasicTestParas(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetBasicTestParas(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetBasicReportData(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetBasicReportData(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetDrvTestData(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetDrvTestData(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetDrvReportData(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetDrvReportData(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetFpgaData(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetFpgaData(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_GetSocketConnect(BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_GetSocketConnect(bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_ConfigDebug(CDataGroup *pGroup,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_ConfigDebug(pGroup, bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_ConfigDebug(CSttDebugCmd *pCmd,BOOL bDoEvents,CSttCmdData *pRetData)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_ConfigDebug(pCmd, bDoEvents, pRetData);
}

long CSttTestClientBase::Debug_ConfigDebug(long nLogDataBind,long nLogPkgDataInfor,long nLogPkg
										   ,long nLogDebugInfor,long nNoChangeWhenSame, long nSpyCmd)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_ConfigDebug(nLogDataBind, nLogPkgDataInfor, nLogPkg, nLogDebugInfor, nNoChangeWhenSame, nSpyCmd);
}

//2020-12-04  lijunqing add spy-cmd
long CSttTestClientBase::Debug_ConfigDebug(const CString &strDebugParaID, long nValue)
{
	if (m_pXClientEngine == NULL)
	{
		return 0;
	}

	return m_pXClientEngine->Debug_ConfigDebug(strDebugParaID, nValue);
}

long CSttTestClientBase::OnMeas(CDataGroup *pParas)
{
	//m_oMeasData
	CDataGroup *pMeas = (CDataGroup*)pParas->FindByID(_T("ModuleMeas"));

	if (pMeas != NULL)
	{
		m_oMeasData.InitDataValues(pMeas, TRUE);
	}

	return 0;
}

void CSttTestClientBase::OpenMeasDataFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("ModuleMeas.xml");
	
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oMeasData.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void CSttTestClientBase::OnXTimer(DWORD dwTimerID)
{
	OnTimer(dwTimerID, 0);
}

//2020-10-26  shaolei
void CSttTestClientBase::CreateSttTimer()
{
/*
//2020-10-27  lijunqing
//LINUX  只处理单测试仪的测试
#ifdef _PSX_QT_LINUX_
    m_nSttClientTimerID = stt_test_singleclient_timer_create(5000);
    stt_test_singleclient_timer_attactclient(this);
#else
    m_nSttClientTimerID = g_theSttTestClientTimer->stt_test_timer_create(5000);
    g_theSttTestClientTimer->AddSttTestClientBase(this);
#endif
	*/
	//2021-9-2  lijunqing
	m_nSttClientTimerID = CXTimer::SetXTimer(1, 5000);
}

void CSttTestClientBase::KillSttTimer()
{
/*
//2020-10-27  lijunqing
//LINUX  只处理单测试仪的测试
#ifdef _PSX_QT_LINUX_
    stt_test_singleclient_timer_free(m_nSttClientTimerID);
#else
    g_theSttTestClientTimer->stt_test_timer_free(m_nSttClientTimerID);
    g_theSttTestClientTimer->RemoveSttTestClientBase(this);
#endif
*/
	//2021-9-2  lijunqing
	CXTimer::KillXTimer(1);
}


void CSttTestClientBase::OnTestStarted(const CString &strMacroID, CDataGroup *pParas)	{}
void CSttTestClientBase::OnTestStoped(const CString &strMacroID, CDataGroup *pParas)	{}
void CSttTestClientBase::OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)	{}
void CSttTestClientBase::OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults)	{}
void CSttTestClientBase::OnTestState(const CString &strMacroID, CDataGroup *pParas)	{}
void CSttTestClientBase::OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){ }

/*
<paras name="" id="">
	<data name="ExecStatus" id="ExecStatus" data-type="string" default-value="" value="3" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
	<group name="Device" id="Device" data-type="Device">
		<data name="ModuleCount" id="ModuleCount" unit="" data-type="long" default="2" value="2"/>
		<data name="系统版本号" id="SysVersion" unit="" data-type="long" default="900797820" value="900797820"/>
		<group name="装置属性" id="DeviceAttrs" data-type="DeviceAttrs">
			<data name="型号" id="Model" unit="" data-type="string" default="PNS330" value="PNS330"/>
			……
		</group>
		<group name="开出量导通值定义" id="BoutTrunOnValueDef" data-type="BoutTrunOnValueDef">
			<data name="开出1导通值" id="Bout1" unit="" data-type="bool" default="1" value="1"/>
			……
		</group>
		<group name="模块0" id="Module" data-type="Module">
			<group name="模块属性" id="ModuleAttrs" data-type="ModuleAttrs">
				<data name="模块类型" id="ModuleType" unit="" data-type="ModuleType" default="VOLTAGE_CURRENT" value="VOLTAGE_CURRENT"/>
				<group name="通道映射定义" id="ChMapDef" data-type="ChMapDef">
					<group name="硬件通道定义" id="ChDefine" data-type="ChDefine">
						<data name="通道数" id="ChannelNum" unit="" data-type="long" default="7" value="7"/>
						……
					</group>
					<group name="通道驱动位置" id="ChDrvPos" data-type="ChDrvPos">
						<data name="通道1位置" id="Ch1Pos" unit="" data-type="long" default="6" value="6"/>
						……
					</group>
				</group>
			</group>
		</group>
		……
	</group>
</paras>
*/
void stt_OnReport_ReadDeviceParameter(CSttParas *pParas)
{
	if (pParas == NULL)
	{
		return;
	}

	if (pParas->m_strID != STT_CMD_TYPE_ADJUST_ReadDeviceParameter)
	{
		return;
	}
	
#ifdef _PSX_QT_LINUX_
	//Linux下，只读一次。判断全局对象中有数据，则不处理。
	stt_OnReport_ReadDeviceParameter_Linux(pParas);
#else
	//Windows下，根据系统版本号判断，判断系统版本号未发生变化，则不处理
	stt_OnReport_ReadDeviceParameter_Windows(pParas);
#endif
}

void stt_OnReport_ReadDeviceParameter_Linux(CSttParas *pParas)
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug -->stt_OnReport_ReadDeviceParameter_Linux"));
	CDataGroup *pDevice = (CDataGroup *)g_oReadDeviceParameter.FindByID(_T("Device"));

	if (pDevice != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug -->stt_OnReport_ReadDeviceParameter_Linux-->find no device"));
		return;
	}

	g_oReadDeviceParameter.DeleteAll();
	g_oReadDeviceParameter.AppendCloneEx2(*pParas);
}

void stt_OnReport_ReadDeviceParameter_Windows(CSttParas *pParas)
{
	CDataGroup *pDevice = (CDataGroup *)g_oReadDeviceParameter.FindByID(_T("Device"));

	if (pDevice == NULL)
	{
		g_oReadDeviceParameter.DeleteAll();
		g_oReadDeviceParameter.AppendCloneEx2(*pParas);
		return;
	}

	CString strSysVersion1, strSysVersion2;

	stt_OnReport_ReadDeviceParameter_GetSysVersion(&g_oReadDeviceParameter, strSysVersion1);
	stt_OnReport_ReadDeviceParameter_GetSysVersion(pParas, strSysVersion2);

	if (strSysVersion2 == strSysVersion1 && (! strSysVersion1.IsEmpty()))
	{
		return;
	}

	g_oReadDeviceParameter.DeleteAll();
	g_oReadDeviceParameter.AppendCloneEx2(*pParas);
}

void stt_OnReport_ReadDeviceParameter_GetSysVersion(CSttParas *pParas, CString &strSysVersion)
{
	CDataGroup *pDevice = (CDataGroup *)g_oReadDeviceParameter.FindByID(_T("Device"));

	if (pDevice == NULL)
	{
		return;
	}

	pDevice->GetDataValue(_T("SysVersion"), strSysVersion);
}
