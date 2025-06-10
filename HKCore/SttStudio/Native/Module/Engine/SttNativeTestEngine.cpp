#include "stdafx.h"
#include "SttNativeTestEngine.h"
#include "../SttCmd/SttRemoteCmd.h"
#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"

#include "../SttSocket/TestServer/VC/SttTestServerSocket.h"

#include "../../../System/Module/XAtsSysSvrGlobalDef.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"
#include "../../../AutoTest/Module/GuideBook/GuideBookDefine.h"
#include "../../../Module/Socket/SocketGlobal.h"

#include "SttQueryAtsFileTool.h"

//2022-1-3  lijunqing
#include "../SttCmd/GuideBook/SttCmdGuideBookTransTool.h"
#include "../AdjustTool/SttAdjDevice.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttNativeTestEngine* CSttNativeTestEngine::g_pNativeTestEngine = NULL;
long CSttNativeTestEngine::g_nNativeTestEngineRef = 0;
//CSttNativeTestEngine *g_theNativeTestEngine = NULL;
CSttTestAppCfg *g_pTheSttTestAppCfg = NULL;
extern CAutoCriticSection m_oUserMngrSection;

CSttNativeTestEngine* CSttNativeTestEngine::Create(const CString &strConfigFile, CSttSmartTest *pSttSmartTest)
{
	CSttTestAppCfg oAppConfig;
	oAppConfig.SttOpen(strConfigFile);

	return Create(oAppConfig.GetLocalIP().GetString(), 19815, pSttSmartTest);
}

CSttNativeTestEngine* CSttNativeTestEngine::Create(const char *pszIP, int nPort, CSttSmartTest *pSttSmartTest)
{
	CSttNativeTestEngineInterfaces::Create();

    g_nNativeTestEngineRef++;

    if (g_nNativeTestEngineRef == 1)
    {
        CDataMngrXmlRWKeys::Create();
        CSttCmdDefineXmlRWKeys::Create();

#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
        CPxiEngine::Create();
#endif

        g_pNativeTestEngine = new CSttNativeTestEngine();
        g_pNativeTestEngine->InitSttServerEngine(pszIP, nPort);
    }

    if (pSttSmartTest == NULL)
    {
#ifndef _SttTestServer_For_Debug_
        //远程测试仪，因为需要向云服务器注册，此处先暂时不创建TestControl
        CSttTestAppCfg oAppCfg;
         oAppCfg. Open(_T("SttTestAppCfg-remote.xml"));

        if(!oAppCfg.IsRemote())
        {
            pSttSmartTest = CSttSmartTest::Create();
            pSttSmartTest->InitTestControl(true);
        }
#endif
    }

	if (pSttSmartTest != NULL)
        {
		g_pNativeTestEngine->SetSttSmartTest(pSttSmartTest);
        }
	
    return g_pNativeTestEngine;
}

void CSttNativeTestEngine::Release()
{
    g_nNativeTestEngineRef--;

    if (g_nNativeTestEngineRef == 0)
    {
        if(g_pNativeTestEngine->IsConnectColudServerSuccess())
        {
            g_pNativeTestEngine->UnRegister(NULL);
            g_pNativeTestEngine->DisConnectCloudServer();
        }

#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
        CPxiEngine::Release();
#endif

        CSttCmdDefineXmlRWKeys::Release();
        CDataMngrXmlRWKeys::Release();

        //2020-4-6  lijq
        g_pNativeTestEngine->ExitSttServerEngine();
        delete g_pNativeTestEngine;
        g_pNativeTestEngine = NULL;
    }

	CSttNativeTestEngineInterfaces::Release();
}

CSttNativeTestEngine* CSttNativeTestEngine::GetNativeTestEngine()
{
    return g_pNativeTestEngine;
}

void CSttNativeTestEngine::OnCommCmdMessage(WPARAM wParam, LPARAM lParam)
{
#ifdef _PSX_QT_LINUX_
    if (m_pSmartTest != NULL)
    {
        if (m_pSmartTest->IsTestCreated())
        {
            return;
        }
    }

    CString strDeviceID;
    strDeviceID = "0";

    if ( lParam == 1 )
    {
        stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_CommError);
        return ;
    }

    if (lParam == engineCommError)
    {
        stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_CommError);
        return ;
    }

    CPxiDevice *pPxiDevice = g_thePxiEngine->GetItem(wParam);
    CDvmDataset *pDataset = NULL;

    if (pPxiDevice != NULL)
    {
        pDataset = pPxiDevice->FindDvmDataset(pPxiDevice->m_strDatasetPathOfProcedure);
    }

    stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_CommFinish, pDataset);
#endif
}

void CSttNativeTestEngine::OnSysMessage(WPARAM wParam, LPARAM lParam)
{
#ifdef _PSX_QT_LINUX_
    if (m_pSmartTest != NULL)
    {
        if (m_pSmartTest->IsTestCreated())
        {
            return;
        }
    }

    CString strDeviceID;
    strDeviceID = "0";

    switch (lParam)
    {
    case engineConnectDeviceFailed:
        stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_ConnectDeviceFailed);
        break;

    case engineConnectDeviceSuccessful:
        stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_ConnectDeviceSuccessful);
        break;

    case engineCommError:
        stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_CommError);
        break;

    case engineException:
        stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_CommError);
        break;

    default:
        break;
    }
#endif
}

//2020-11-24  lijunqing LINUX  post msg to ats
void CSttNativeTestEngine::OnEngineDataDeleted(const CString &strDeviceID)
{
#ifdef _PSX_QT_LINUX_
    stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_DeviceClosed);
#endif
}


//2022-2-12  lijunqing
void CSttNativeTestEngine::DispatchMsg(unsigned char *pBuf, long nLen)
{
	CAutoSimpleLock oLock(&m_pSttTestClientUserMngr->m_oUserMngrSection);

	CSttTestClientUser *pUser = NULL;
	POS pos = m_pSttTestClientUserMngr->GetHeadPosition();

	while(pos != NULL)
	{
		pUser = (CSttTestClientUser *)m_pSttTestClientUserMngr->GetNext(pos);

		//        if (! pUser->HasAuthority(KEY_AUTHORITY_MODULE_Ats))
		//        {
		//            continue;
		//        }

		if (pUser->m_pRefSttSckt != NULL)
		{
			pUser->m_pRefSttSckt->SendBuffer(pBuf,nLen);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CSttNativeTestEngineInterface
long CSttNativeTestEngine::X_ReturnSysStateToChildren(void *pCommInterface, CSttSysState *pSysState)
{
	return ReturnSysStateToChildren(NULL, pSysState);
}

long CSttNativeTestEngine::X_Ats_InputData(void *pCommInterface, CDataGroup *pDatas,CExBaseList *pMsgs)
{
	return Ats_InputData(NULL, pDatas, pMsgs);
}

CSttNativeTestEngine::CSttNativeTestEngine()
{
    //m_pSmartTest = new CSttSmartTest();
#ifdef _PSX_QT_LINUX_
    g_thePxiDeviceCommCmdMessage = this;
#endif

	//服务端管理对象
    g_theNativeTestEngine->AddTail(this);

    m_pSttCloudClientSocket = NULL;
    m_pSttAtsInterface = NULL;
    m_pRefAtsUser = NULL;
	m_pSmartTest = NULL;

    InitClientUserMngr();

    m_pNativeClientTestEngine = new CSttNativeClientTestEngine();
    m_pNativeClientTestEngine->SetExternEngineRef(this);
}

CSttNativeTestEngine::~CSttNativeTestEngine()
{
    if (m_pNativeClientTestEngine != NULL)
    {
        m_pNativeClientTestEngine->PrepareFreeClientEngine();
        delete m_pNativeClientTestEngine;
        m_pNativeClientTestEngine = NULL;
    }

    if (m_pSttCloudClientSocket != NULL)
    {
        delete m_pSttCloudClientSocket;
        m_pSttCloudClientSocket = NULL;
    }

    if (m_pRefAtsUser != NULL)
    {
        m_oClientUserMngr.Remove(m_pRefAtsUser);
    }
    m_oClientUserMngr.Remove(&m_oTestControlUser);

//	CSttSmartTest::Release();

#ifndef _SttTestServer_For_Debug_
	CXSmartTestEntry::Release();
#endif
}

void CSttNativeTestEngine::InitClientUserMngr()
{
    m_oClientUserMngr.AddTail(&m_oTestControlUser);
    m_oTestControlUser.ID_Terminal(STT_TERMINAL_TYPE_NATIVE_TESTCONTROL);
    m_oTestControlUser.Name_User(STT_TERMINAL_TYPE_NATIVE_TESTCONTROL);
    m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
}

void CSttNativeTestEngine::AttachRefAtsUser(CSttTestClientUser *pRefAtsUser)
{
    m_pRefAtsUser = pRefAtsUser;
    m_oClientUserMngr.AddTail(m_pRefAtsUser);
}

void CSttNativeTestEngine::InitSttServerEngine(const char *pszIP, int nPort,int nReplayPort)
{
    CGbXMLKeys::CreatetGbXMLkeys();
    CCfgDataMngrXmlRWKeys::Create();
    CSttCmdOverTimeTool::Create();

    CSttTestServerSocket *pCSttServerSocketDataBase = new CSttTestServerSocket();
    SetServerSocketDataBase((CSttServerSocketDataBase *)pCSttServerSocketDataBase);
    m_pServerSocket->m_nMaxClientCount=5;
    m_pServerSocket->CreateServer(pszIP, nPort);
    m_pServerSocket->AttachCmdOverTimeMsgRcv(this);
    m_pServerSocket->SetTestEngine(this);
}

//2020-4-6  lijq
//如果没有这部分，Server的Accept线程无法退出
void CSttNativeTestEngine::ExitSttServerEngine()
{
    if (m_pServerSocket != NULL)
    {
        m_pServerSocket->CloseSttServer();
        delete m_pServerSocket;
        m_pServerSocket = NULL;
    }

    CGbXMLKeys::Release();
    CCfgDataMngrXmlRWKeys::Release();
    CSttCmdOverTimeTool::Release();
}

void CSttNativeTestEngine::OnSocketClose(CSttSocketDataBase *pSocket)
{
    //20210123 xxy 必须最后一行，防止软件关闭时，执行了该行之后delete ServerEngine,而这个函数还没执行完
    //参考CSttServerSocketDataBase::CloseSttServer()
    if(pSocket != m_pSttCloudClientSocket)
    {//本地自动测试连接断链
//		m_pServerSocket->CSttServerSocketDataBase::OnSttScktClose(pSocket);
        m_oClientUserMngr.DeleteUserByRefSocket(pSocket);
    }
    else
    {//连接云端socket断链
//         if (m_pSttCloudClientSocket != NULL)
//         {
//            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("云端：%s Disonnect"), pSocket->m_strIPRemote.GetString());

//             delete m_pSttCloudClientSocket;
//             m_pSttCloudClientSocket = NULL;
//         }

        //删除用户管理中的所有远程用户
        m_oClientUserMngr.DeleteUserByIDTerminal(STT_TERMINAL_TYPE_REMOTE);
        m_oRemoteRegister.Code_Register(_T(""));
    }

    //如果没有Ats权限，则释放TestControl的ClientEngine权限
    CheckUpdateTestControlAuthority();

    CSttSysState oSysState;
    ReturnBroadcastUserMngr(oSysState);

    //断链或退出登录后
    CheckStopTestAfterReleaseUser();


    //20210123 xxy 必须最后一行，防止软件关闭时，执行了该行之后delete ServerEngine,而这个函数还没执行完
    //参考CSttServerSocketDataBase::CloseSttServer()
    if(pSocket != m_pSttCloudClientSocket)
    {//本地自动测试连接断链
        m_pServerSocket->CSttServerSocketDataBase::OnSttScktClose(pSocket);
    }
    else
    {//连接云端socket断链
        if (m_pSttCloudClientSocket != NULL)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("云端：%s Disonnect"), pSocket->m_strIPRemote.GetString());

            delete m_pSttCloudClientSocket;
            m_pSttCloudClientSocket = NULL;
        }
    }
}

BOOL CSttNativeTestEngine::SendBufferToChildren(CSttSocketDataBase *pExceptSocket,BYTE *pBuf,long nLen)
{
    if(m_pSttCloudClientSocket != NULL)
    {
        m_pSttCloudClientSocket->SendBuffer(pBuf,nLen);
    }

    if (m_pServerSocket != NULL)
    {
        m_pServerSocket->SendBufferToChildren(pExceptSocket,pBuf,nLen);
    }
    return 1;
}

long CSttNativeTestEngine::SendSysState(CSttSysState *pSysState)
{
    if(m_pSttCloudClientSocket == NULL)
        return 0;

    return m_pSttCloudClientSocket->SendSysState(pSysState);
}

//收到测试命令，先检查是否有权限，无权限则返回失败
BOOL CSttNativeTestEngine::CheckBeforeProcessCmdTest(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
    CSttSystemCmd oSysCmd;
    oSysCmd.m_strTestor = STT_SOFT_ID_TEST;
    oSysCmd.m_nIDTester = stt_pkg_get_idtester(pBuf);
    oSysCmd.AddNewParasData(KEY_AUTHORITY_MODULE_Test, 1);

    //判断是否具有Test权限（或可以申请Test权限）
    BOOL bRet = (AuthorityToUser(oSysCmd,TRUE,TRUE) != 0);

    if (!bRet)
    {
        CSttTestCmd oTestCmd;
        oTestCmd.ParsePkgHead(pBuf);

        pClientSocket->RetFailureSysState(&oTestCmd);
    }

    return bRet;
}

BOOL CSttNativeTestEngine::CheckBeforeProcessCmdAts(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
    CSttSystemCmd oSysCmd;
    oSysCmd.m_strTestor = STT_SOFT_ID_ATS;
    oSysCmd.m_nIDTester = stt_pkg_get_idtester(pBuf);
    oSysCmd.AddNewParasData(KEY_AUTHORITY_MODULE_Ats, 1);

    //判断是否具有Ats权限（或可以申请Ats权限）
    BOOL bRet = (AuthorityToUser(oSysCmd,TRUE,TRUE) != 0);

    if (!bRet)
    {
        CSttAtsCmd oAtsCmd;
        SetXmlBufferLen(nLen * 2);
        oAtsCmd.ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);

        pClientSocket->RetFailureSysState(&oAtsCmd);
    }

    return bRet;
}

/*
<sys-cmd name="" id="CloudTest" testor="TEST$LOCAL">
    <paras>
        <data id="ip" value="47.111.12.170" />
        <group name="SubIP1" id="SubIP1" data-type="SubIP">
            <data id="IP" value="192.168.1.100" />
            <data id="mask" value="255.255.255.0" />
            <data id="GateWay" value="192.168.1.1" />
        </group>
    </paras>
</sys-cmd>
*/
long CSttNativeTestEngine::ProcessCmd_CloudTest(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    CSttSysState oSysState;
    CSttParas* pParas = oSysCmd.GetSttParas();

    //先修改辅助IP，网关等信息；
    CDataGroup *pSubIP = (CDataGroup *)pParas->FindByID(_T("SubIP1"));

    if (pSubIP != NULL)
    {
        CDataGroup *pSysConfig = new CDataGroup;
        CDataGroup *pGroup = (CDataGroup *)pSubIP->Clone();
        pSysConfig->AddNewChild(pGroup);
        long nRet = m_pNativeClientTestEngine->System_SetSysConfig(pSysConfig);
        delete pSysConfig;

        if (!Stt_Is_ExecStatus_Success(nRet))
        {
            oSysState.Set_ExecStatus_Failure();
            oSysState.Set_IsSuccess(FALSE);
            pClientSocket->SendSysState(&oSysState);
            return nRet;
        }
    }

    CTickCount32 oTick;
    oTick.DoEvents(500);  //延时500ms，确保修改网关生效

    CString strCloudServerIP;
    strCloudServerIP.Format(_T("47.111.12.170"));
    CDvmData *pIP = (CDvmData *)pParas->FindByID(_T("ip"));

    if (pIP != NULL)
    {
        strCloudServerIP = pIP->m_strValue;
    }

    //连接云服务端
    long nRet = ConnectCloudServer(strCloudServerIP, STT_PORT_CLOUD_SERVER);

    if (nRet)
    {
        CString strSN;
        CDvmData *pSN = (CDvmData *)g_pDeviceAttrs->FindByID(_T("SN"));
        strSN = pSN->m_strValue;
        m_oRemoteRegister.SN_TestApp(strSN);
        m_oRemoteRegister.Name_Cop(_T("PowerSky"));
        m_oRemoteRegister.Name_User(_T("SmartTest"));
        m_oRemoteRegister.Description(_T("SmartTest"));
        m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_SmartTest, _T("1.0.0.2"));
        m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_TestServer, _T("1.0.0.3"));
        CSttCmdData oRetData;
        nRet = Register(&oRetData);
    }

    if (Stt_Is_ExecStatus_Success(nRet))
    {
        oSysState.Set_ExecStatus_Success();
        oSysState.Set_IsSuccess(TRUE);
    }
    else
    {
        //pClientSocket->RetFailureSysState(&oSysCmd);
        oSysState.Set_ExecStatus_Failure();
        oSysState.Set_IsSuccess(FALSE);
    }

    pClientSocket->SendSysState(&oSysState);

    return nRet;
}

//本地Ats和远程登录
long CSttNativeTestEngine::Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    CSttTestClientUser *pUser = User_Login(pClientSocket, oSysCmd);

    //生成应答命令返回
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    if(pUser != NULL)
    {
        oSysState.Set_ExecStatus_Success();
        oSysState.AddNewParasData(STT_CMD_PARA_IDTESTER, pUser->GetIDTest());
    }
    else
    {
        oSysState.Set_ExecStatus_Failure();
    }
    pClientSocket->SendSysState(&oSysState);	//应答自身登录信息

    if (pUser != NULL)
    {
        ReturnBroadcastUserMngr(oSysState);

//#ifdef _PSX_QT_LINUX_   原先只在linux下开放，因国际版7.0也需要。windows下也开放 2024-8-14
		//应答ReadDeviceParameter信息   shaolei 20220326
		Return_DeviceParameter_AfterLogin(pClientSocket, oSysState);

        //从主界面登录时，需要直接连接到19814。以获取RTDATA【从功能模块退出到主界面，CloseTest，会导致与19814会断链】
        if (m_pSmartTest != NULL)
        {
            m_pSmartTest->InitTestControl(TRUE);
        }
//#endif
    }

    return 1;
}

long CSttNativeTestEngine::Process_Cmd_System_Logout(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    //更新用户链表
    DWORD nIDTester = 0;
    oSysCmd.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nIDTester);
    m_pSttTestClientUserMngr->DeleteUserByIDTest(nIDTester);

    //如果没有Ats权限，则释放TestControl的ClientEngine权限
    CheckUpdateTestControlAuthority();

    //生成应答命令返回
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AddNewParasData(STT_CMD_PARA_IDTESTER, nIDTester);
    pClientSocket->SendSysState(&oSysState);	//应答自身登录信息

    ReturnBroadcastUserMngr(oSysState);

    //客户端保证，发送Logout之前权限都已释放
    CheckStopTestAfterReleaseUser();

    return 1;
}

void CSttNativeTestEngine::CheckStopTestAfterReleaseUser()
{//退出登录或断链，检查是否停止测试
    CLogPrint::LogString(XLOGLEVEL_INFOR,_T("【Native:CheckStopTestAfterReleaseUser】"));

    if ((m_pNativeClientTestEngine == NULL)
        || (!m_pNativeClientTestEngine->m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test)))
    {//如果NativeClient没有Test权限
        return;
    }

    CSttTestClientUser *pUser = m_pSttTestClientUserMngr->FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
    if (pUser != NULL)
    {
        return;
    }

    //释放NativeClient的Test权限
    m_pNativeClientTestEngine->m_oCurrUser.SetAuthority(KEY_AUTHORITY_MODULE_Test,0);

    //具有远程测试权限的单机测试端
    m_pNativeClientTestEngine->Test_CloseDevice();
}

//只检测具有单机测试权限的测试端心跳超时
void CSttNativeTestEngine::CheckHeartbeatOverTime()
{
    if (g_nRecvHeartbeatTimeGap <= 0)
    {//屏蔽心跳检测
        return;
    }

    if (m_pNativeClientTestEngine == NULL
        || (!m_pNativeClientTestEngine->m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test)))
    {//NativeClient无Test权限
        return;
    }

    //查找当前Test权限用户
    CSttTestClientUser *pFind = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
    if (pFind == NULL || pFind->m_pRefSttSckt == NULL)
    {
        return;
    }

    if (pFind->id_soft() != STT_SOFT_ID_TEST)
    {//不是远程单机测试
        return;
    }

    long nTimeGap = pFind->m_pRefSttSckt->m_nRecvHeartbeatCounter++;//zhouhj 20210821 参考SttTestServerBase修改

    if (nTimeGap/*pFind->m_pRefSttSckt->m_oRecvHeartbeatTick.GetTickCountLong(FALSE)*/ >= g_nRecvHeartbeatTimeGap)
    {//主动断链，断链后StopTest,CloseDevice
        //删除用户链表
        m_oClientUserMngr.Delete(pFind);

        //释放NativeClient的Test权限
        m_pNativeClientTestEngine->m_oCurrUser.SetAuthority(KEY_AUTHORITY_MODULE_Test,0);

        CheckUpdateTestControlAuthority();

        //广播
        CSttSysState oSysState;
        ReturnBroadcastUserMngr(oSysState);

        //具有远程测试权限的单机测试端，停止测试
        m_pNativeClientTestEngine->Test_CloseDevice();
    }
}

BOOL CSttNativeTestEngine::OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet)
{
    //2020-11-29  lijunqing  监视所有命令报文
    if (g_nSttLogServerSpyAllCmd)
    {
        if (nCmdType != STT_CMD_TYPE_DEBUG)
        {
            SendToAllUser(STT_SOFT_ID_DEBUG, pBuf, nLen);
        }
    }

    //收到数据后，接受心跳计时器清0
    DWORD nIDTester = stt_pkg_get_idtester(pBuf);
    m_oClientUserMngr.RestartRecvHeartbeatTickCount(nIDTester);

    //Native端：test命令、debug命令肯定是远程测试发过来的，所以交于m_pClientTestEngine去执行
    //心跳报文：测试控制的心跳报文，有m_pClientTestEngine维护
    if (nCmdType == STT_CMD_TYPE_DEBUG)
    {
        return m_pNativeClientTestEngine->SendBuffer(pBuf, nLen);
    }

    if (nCmdType == STT_CMD_TYPE_TEST)
    {//单机测试命令，先判断是否具有ClientEngine权限

		//pBuf是携带报文头的，应当重新拼报文头
		char* pszXmlBuffer = new char[2 * nLen + 10];
		memset(pszXmlBuffer, 0, 2 * nLen + 10);
		CSttTestCmd *pTestCmd = new CSttTestCmd();
		pTestCmd->ParsePkgXml(pBuf,nLen, pszXmlBuffer);
		delete pszXmlBuffer;

		CSttSysState oSysState;
		oSysState.UpdateSysStateHead(pTestCmd);
		oSysState.Set_ExecStatus(STT_CMD_ExecStatus_ACK);

		BYTE *pSendBuf = NULL;
		long nSendBufLen = 0;
		stt_InitRetSendBuf(&pSendBuf,nSendBufLen,&oSysState, FALSE, pClientSocket->m_nSttCmdDataFormat);;
		pClientSocket->SendBuffer(pSendBuf,nSendBufLen);
		delete pSendBuf;
		pSendBuf = NULL;
		nSendBufLen = 0;

		// ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);
		
		//不判权限-2023-11-23
// 		if(!CheckBeforeProcessCmdTest(pClientSocket,pBuf,nLen,pszCmdID,pszTestor))
//         {
// 			oSysState.Set_ExecStatus(STT_CMD_ExecStatus_FAILURE);
// 			stt_InitRetSendBuf(&pSendBuf,nSendBufLen,&oSysState, FALSE, pClientSocket->m_nSttCmdDataFormat);;
// 			pClientSocket->SendBuffer(pSendBuf,nSendBufLen);
// 			delete pSendBuf;
// 			pSendBuf = NULL;
// 			nSendBufLen = 0;
// 			// ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_FAILURE);
//             return FALSE;
//         }

		long nRet = -1;
        if(m_pSmartTest == NULL)
        {
            nRet = m_pNativeClientTestEngine->SendBuffer(pBuf, nLen);
        }
        else
        {
            nRet = m_pSmartTest->Process_Cmd_Test(pTestCmd);
        }

		if (nRet >= 0)
		{
			oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
			// ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_SUCCESS);
		}
		else
		{
			oSysState.Set_ExecStatus(STT_CMD_ExecStatus_FAILURE);
			// ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_FAILURE);
		}

		stt_InitRetSendBuf(&pSendBuf,nSendBufLen,&oSysState, FALSE, pClientSocket->m_nSttCmdDataFormat);;
		pClientSocket->SendBuffer(pSendBuf,nSendBufLen);
		delete pSendBuf;
		//delete pTestCmd;   //shaolei 注释此处  2023-10-10。因为没有使用RefCount。在使用完了之后delete

		return nRet;
    }
    if (nCmdType == STT_CMD_TYPE_ATS)
    {//自动测试命令，先判断是否具有Ats权限
        if(!CheckBeforeProcessCmdAts(pClientSocket,pBuf,nLen,pszCmdID,pszTestor))
        {
            return FALSE;
        }
    }

    if (nCmdType == STT_CMD_TYPE_SYSSTATE)
    {
        CSttSysState oSysState;

        //2020-5-25 lijq
        SetXmlBufferLen(nLen * 2);
        oSysState.ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);

        //SysState:返回的test命令、debug命令结果，肯定是从m_pClientTestEngine，这部分是必须返回给远程端的
        if (oSysState.m_strRetSttCmd == STT_CMD_SYSSTATE_TEST  || oSysState.m_strRetSttCmd == STT_CMD_SYSSTATE_DEBUG)
        {
            if(oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetSocketConnect)
            {//如果是GetSocketConnect应答，需合并Native和TestServer用户链表
                return ReturnGetSocketConnect(oSysState);
            }

            if(m_pSttCloudClientSocket == NULL)
                return TRUE;

            return m_pSttCloudClientSocket->SendBuffer(pBuf, nLen);
        }
    }

    return CSttTestEngineServerBase::OnTestMsgEx(pClientSocket, pBuf, nLen, nCmdType, pszCmdID, pszTestor, pszRetCmdType, bRet);
}

long CSttNativeTestEngine::Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
    if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_Register)
    {
        return Process_SysState_Register(oSysState);
    }
    else if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_UnRegister)
    {
        return Process_SysState_UnRegister(oSysState);
    }
    else if (oSysState.m_strID == STT_CMD_TYPE_ATS_InputData)
    {
        return Process_SysState_InputData(pClientSocket,oSysState);
    }
    else
    {//其他测试命令,根据目标IDTest，转发

    }

    return 0;
}

long CSttNativeTestEngine::Process_SysState_Register(CSttSysState &oSysState)
{//收到云端注册应答
    long nCmdExecState = oSysState.Get_ExecStatus();

    if (Stt_Is_ExecStatus_Success(nCmdExecState))
    {
        CString strCode_Register,strSN_TestApp;
        oSysState.GetParasDataValueByID(ID_STT_USER_ATTR_Code_Register, strCode_Register);
        oSysState.GetParasDataValueByID(ID_STT_USER_ATTR_SN_TestApp, strSN_TestApp);
        m_oRemoteRegister.Code_Register(strCode_Register);
        m_oRemoteRegister.SN_TestApp(strSN_TestApp);
    }

    CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttCloudClientSocket,oSysState,nCmdExecState);

    return nCmdExecState;
}

long CSttNativeTestEngine::Process_SysState_UnRegister(CSttSysState &oSysState)
{//收到取消云端注册应答
    long nCmdExecState = oSysState.Get_ExecStatus();

    if (Stt_Is_ExecStatus_Success(nCmdExecState))
    {
        //删除远程用户
        m_oClientUserMngr.DeleteUserByIDTerminal(STT_TERMINAL_TYPE_REMOTE);
        m_oRemoteRegister.Code_Register(_T(""));
    }

    CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(m_pSttCloudClientSocket,oSysState,nCmdExecState);

    return nCmdExecState;
}

long CSttNativeTestEngine::Process_SysState_InputData(CSttSocketDataBase *pClientSocket,CSttSysState &oSysState)
{
    long nCmdExecState = oSysState.Get_ExecStatus();
    CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(pClientSocket,oSysState,nCmdExecState);

    return nCmdExecState;
}

long CSttNativeTestEngine::ConnectCloudServer(const CString &strIPServer,long nPort)
{
    if (m_pSttCloudClientSocket == NULL)
    {
        m_pSttCloudClientSocket = new CSttNativeRemoteClientSocket;
        m_pSttCloudClientSocket->SetTestEngine(this);
        m_pSttCloudClientSocket->AttachCmdOverTimeMsgRcv(this);
    }

   BOOL bRet = m_pSttCloudClientSocket->ConnectServer(strIPServer,nPort);

   if(!bRet)
   {
       delete m_pSttCloudClientSocket;
       m_pSttCloudClientSocket = NULL;
   }

   return bRet;
}

void CSttNativeTestEngine::DisConnectCloudServer()
{
    if (m_pSttCloudClientSocket != NULL)
    {
        m_pSttCloudClientSocket->CloseSocket();
    }
}

BOOL  CSttNativeTestEngine::IsConnectColudServerSuccess()
{
    if(m_pSttCloudClientSocket == NULL)
        return FALSE;

    if(m_pSttCloudClientSocket->m_hSocket == NULL)
        return FALSE;

    return TRUE;
}

long CSttNativeTestEngine::SendCmd(CSttCmdBase *pCmd,long nTimeOut,BOOL bCompress,BOOL bReset)
{
    if (m_pSttCloudClientSocket == NULL)
    {
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_pSttCloudClientSocket == NULL"));
        return 0;
    }

    return m_pSttCloudClientSocket->SendCmdAsync(pCmd,nTimeOut,this,bCompress,bReset);
}

long CSttNativeTestEngine::SendCmdSync(CSttCmdBase *pCmd,long nTimeOut,CSttCmdData *pRetData,BOOL bDoEvents)
{
    if (m_pSttCloudClientSocket == NULL)
    {
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_pSttCloudClientSocket == NULL"));
        return 0;
    }

    return m_pSttCloudClientSocket->SendCmdSync(pCmd,nTimeOut,pRetData,bDoEvents);
}

// long CSttNativeTestEngine::ReturnSysState(long nCmdExecStatus)
// {
// 	//xxy测试命令应答
// 	if (m_oSttAtsCmd.GetRefSocketData() == NULL)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oSttAtsCmd.m_pRefSocketDataBase == NULL"));
// 		return 0;
// 	}
//
// 	CSttSysState oSysState;
// 	oSysState.UpdateSysStateHead(&m_oSttAtsCmd);
// 	oSysState.Set_ExecStatus(nCmdExecStatus);
//
// 	return m_oSttAtsCmd.GetRefSocketData()->SendSysState(&oSysState);
//
// 	return 0;
// }

long CSttNativeTestEngine::Register(CSttCmdData *pRetData)
{
    if (m_oRemoteRegister.HasRegister())
    {
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("已经注册"));
        return STT_CMD_ExecStatus_SUCCESS;
    }

    CSttRemoteCmd oRemoteCmd;
    oRemoteCmd.m_strID = STT_CMD_TYPE_REMOTE_Register;
    oRemoteCmd.m_strTestor = STT_REGISTER_MODE_OWN;
    oRemoteCmd.AddNewParasData(ID_STT_USER_ATTR_SN_TestApp,m_oRemoteRegister.SN_TestApp());
    oRemoteCmd.AddNewParasData(ID_STT_REGISTER_ATTR_Model_TestApp,m_oRemoteRegister.Model_TestApp());
    oRemoteCmd.AddNewParasData(ID_STT_REGISTER_ATTR_Model_Dv,m_oRemoteRegister.Model_Dv());
    oRemoteCmd.AddNewParasData(ID_STT_USER_ATTR_Name_Cop,m_oRemoteRegister.Name_Cop());
    oRemoteCmd.AddNewParasData(ID_STT_USER_ATTR_Name_User,m_oRemoteRegister.Name_User());
    oRemoteCmd.AddNewParasData(ID_STT_REGISTER_ATTR_Description,m_oRemoteRegister.Description());
    oRemoteCmd.AddNewParasData(ID_STT_REGISTER_ATTR_Ver_SmartTest,m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_SmartTest));
    oRemoteCmd.AddNewParasData(ID_STT_REGISTER_ATTR_Ver_TestServer,m_oRemoteRegister.Ver(ID_STT_REGISTER_ATTR_Ver_TestServer));

    return SendCmdSync(&oRemoteCmd,3000,pRetData,TRUE);
}

long CSttNativeTestEngine::UnRegister(CSttCmdData *pRetData)
{
    CSttRemoteCmd oRemoteCmd;
    oRemoteCmd.m_strID = STT_CMD_TYPE_REMOTE_UnRegister;
    oRemoteCmd.AddNewParasData(ID_STT_USER_ATTR_SN_TestApp,m_oRemoteRegister.SN_TestApp());
    oRemoteCmd.AddNewParasData(ID_STT_USER_ATTR_Code_Register,m_oRemoteRegister.Code_Register());

    return SendCmdSync(&oRemoteCmd,3000,pRetData,TRUE);
}

long CSttNativeTestEngine::Ats_InputData(CSttSocketDataBase *pClientSocket,CDataGroup *pDatas,CExBaseList *pMsgs)
{
    if (pClientSocket == NULL)
    {
        pClientSocket = FindSocketByAuthority(KEY_AUTHORITY_MODULE_Ats);
    }

    if (pClientSocket == NULL)
    {
        return 0;
    }


    CSttAtsCmd oAtsCmd(STT_CMD_TYPE_ATS_InputData);

    if (pDatas != NULL)
    {
        oAtsCmd.AppendParas2(*pDatas);
    }

    if (pMsgs != NULL)
    {
        oAtsCmd.AppendMsgs(*pMsgs);
    }

    //2020-12-08  lijunqing
    oAtsCmd.Set_Xml_Pkg_With_Name(TRUE);   //2020-12-09  lijunqing  return data with name
    m_oClientUserMngr.SendCmd(pClientSocket, &oAtsCmd, g_nSttLogServerSpyAllCmd);
	oAtsCmd.RemoveMsgs();

    return 0;//pClientSocket->SendCmdAsync(&oAtsCmd,3000,this);
}

BOOL CSttNativeTestEngine::AuthorityToAtsUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser)
{
    long nAuthority = 0;
    oSysCmd.GetParasDataValueByID(KEY_AUTHORITY_MODULE_Ats, nAuthority);

    if (nAuthority == 0)
    {//取消权限
        if (pUser->HasAuthority(KEY_AUTHORITY_MODULE_Ats))
        {//如果当前用户具有Ats权限，则取消ClientEngine权限
            m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
        }
    }
    else
    {//请求权限
        CSttTestClientUser *pFind = m_pSttTestClientUserMngr->FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
        if (pFind == NULL)
        {//如果远程单机测试软件没有ClientEngine权限，则设置ClientEngine权限
            m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,1);
        }
    }

    //设置权限
    CSttParas *pParas = oSysCmd.GetSttParas();
    pUser->SetAuthoritys(pParas);
    m_oClientUserMngr.ClearOtherAuthoritys(pParas, pUser);

    return TRUE;
}

BOOL CSttNativeTestEngine::AuthorityToTestUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser)
{//远程单机测试权限
    long nAuthority = 0;
    long nExecStatus = 0;
    oSysCmd.GetParasDataValueByID(KEY_AUTHORITY_MODULE_ClientEngine, nAuthority);

    if (nAuthority == 0)
    {//取消Test权限
        if (pUser->HasAuthority(KEY_AUTHORITY_MODULE_Test))
        {
            if ((m_pNativeClientTestEngine == NULL)
                || (m_pNativeClientTestEngine->m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test)))
            {
                nExecStatus = m_pNativeClientTestEngine->System_Request(KEY_AUTHORITY_MODULE_Test,0);
                if (!Stt_Is_ExecStatus_Success(nExecStatus))
                {
                    return FALSE;
                }
            }
        }
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Test,0);
    }
    else
    {//请求Test权限
        if (m_pNativeClientTestEngine == NULL)
        {
            return FALSE;
        }

        if (!m_pNativeClientTestEngine->m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test))
        {
            nExecStatus = m_pNativeClientTestEngine->System_Request(KEY_AUTHORITY_MODULE_Test,1);
            if (!Stt_Is_ExecStatus_Success(nExecStatus))
            {
                return FALSE;
            }
        }
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Test,1);
    }

    //设置权限
    CSttParas *pParas = oSysCmd.GetSttParas();
    pUser->SetAuthoritys(pParas);
    m_oClientUserMngr.ClearOtherAuthoritys(pParas, pUser);

    //更新TestControl权限
    CheckUpdateTestControlAuthority();

    return TRUE;
}

long CSttNativeTestEngine::AuthorityToUser(CSttSystemCmd &oSysCmd,BOOL bRequest,BOOL bBroadcastWhenSuccess)
{//本地自动测试、远程单机、远程自动测试：请求或授权处理
    CSttTestClientUser *pUser = m_pSttTestClientUserMngr->FindByIDTest(oSysCmd.m_nIDTester, oSysCmd.m_strTestor);
    if (pUser == NULL)
    {
        return 0;
    }

    long nAuthority = 0;
    CString strIdSoft = pUser->id_soft();
    if (strIdSoft == STT_SOFT_ID_TEST)
    {
        oSysCmd.GetParasDataValueByID(KEY_AUTHORITY_MODULE_Test, nAuthority);
        oSysCmd.DeleteParasDataByID(KEY_AUTHORITY_MODULE_Test);
        oSysCmd.SetParasDataAttr(KEY_AUTHORITY_MODULE_ClientEngine,nAuthority);
    }

    //0:不可授权，1：已授权，2、可授权但未授权
    long nRet = IsCanAuthorityToUser(oSysCmd,bRequest);
    if (nRet == 1)
    {//已授权
        if(CheckUpdateTestControlAuthority() != 0)
        {
            if (bBroadcastWhenSuccess)
            {
                CSttSysState oSysState;
                ReturnBroadcastUserMngr(oSysState);
            }
        }
    }
    if (nRet != 2)
    {
        return nRet;
    }

    if (strIdSoft == STT_SOFT_ID_ATS)
    {//自动测试
        if (!AuthorityToAtsUser(oSysCmd,pUser))
        {
            return 0;
        }
    }
    else
    {//远程单机测试权限
        if (!AuthorityToTestUser(oSysCmd,pUser))
        {
            return 0;
        }
    }

    if (bBroadcastWhenSuccess && (nRet == 2))
    {
        CSttSysState oSysState;
        ReturnBroadcastUserMngr(oSysState);
    }

    return nRet;
}

BOOL CSttNativeTestEngine::IsCanAuthorityToRefAtsUser(long nAtsAuthority,BOOL bRequest)
{
    ASSERT(m_pRefAtsUser != NULL);

    if (nAtsAuthority == 0)
    {//取消权限，直接取消
        return TRUE;
    }

    //授权，需要判断是否有用户拥有相同的权限
    CSttTestClientUser *pFind = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_Ats);

    if ((pFind == NULL) || (pFind == m_pRefAtsUser))
    {//授权成功
        return TRUE;
    }
    else
    {//权限被占用
        //如果正在测试，则授权失败

        //否则，高优先级打断底优先级
        if((!bRequest) && (m_pRefAtsUser->CompareUserPriority(pFind) > 0))
        {//若是授权
            return TRUE;
        }
    }

    return FALSE;
}

//界面模块RefAtsUser请求或授权处理
long CSttNativeTestEngine::AuthorityToRefAtsUser(long nAtsAuthority,BOOL bRequest)
{
    if (m_pRefAtsUser == NULL)
    {
        return 0;
    }

    BOOL bSuccess = IsCanAuthorityToRefAtsUser(nAtsAuthority,bRequest);

    if (bSuccess)
    {
        if (nAtsAuthority == 0)
        {
            if (m_pRefAtsUser->HasAuthority(KEY_AUTHORITY_MODULE_Ats))
            {
                m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
            }
        }
        else
        {
            m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,1);
        }
    }

    CSttSystemCmd oSysCmd;
    oSysCmd.AddNewParasData(KEY_AUTHORITY_MODULE_Ats,nAtsAuthority);
    CSttParas *pParas = oSysCmd.GetSttParas();
    m_pRefAtsUser->SetAuthoritys(pParas);
    m_oClientUserMngr.ClearOtherAuthoritys(pParas, m_pRefAtsUser);

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    ReturnBroadcastUserMngr(oSysState);

    return 1;
}

long CSttNativeTestEngine::CheckCancelNativeClientAuthority()
{//如果没有ClientEngine权限，则释放NativeClient的Test权限
    CSttTestClientUser *pFind = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
    if (pFind != NULL)
    {
        return 0;
    }
    if ((m_pNativeClientTestEngine == NULL)
        || (!m_pNativeClientTestEngine->m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test)))
    {
        return 0;
    }

    return m_pNativeClientTestEngine->System_Request(KEY_AUTHORITY_MODULE_Test,0);
}

/*
1、如果没有Ats权限，则释放TestControl的ClientEngine权限；
2、如果有Ats权限，且ClientEngine权限未被占用，则设置TestControl的ClientEngine权限；
*/
long CSttNativeTestEngine::CheckUpdateTestControlAuthority()
{
    CSttTestClientUser *pFind = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_Ats);
    if (m_oTestControlUser.HasAuthority(KEY_AUTHORITY_MODULE_ClientEngine))
    {//TestControl有ClientEngine权限
        if (pFind == NULL)
        {
            m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
            return 1;
        }
    }
    else
    {//TestControl没有ClientEngine权限
        if (pFind != NULL)
        {
            CSttTestClientUser *pUser = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
            if (pUser == NULL)
            {
                m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,1);
                return 1;
            }
        }
    }

    return 0;
}

CSttTestClientUser* CSttNativeTestEngine::User_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    CSttTestClientUser *pUser = NULL;
    CString strIDTerminal , strSoftID;
    DWORD nIDTester = 0;
    oSysCmd.GetParasDataValueByID(ID_STT_USER_ATTR_ID_Terminal, strIDTerminal);
    oSysCmd.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nIDTester);
    oSysCmd.GetParasDataValueByID(ID_STT_USER_ATTR_id_soft, strSoftID);

    CSttSocketDataBase *pPrevSocket = NULL;

    pUser = m_pSttTestClientUserMngr->FindByIDTest(nIDTester, strSoftID);
    if (pUser == NULL)
    {
        pUser = new CSttTestClientUser();
        m_pSttTestClientUserMngr->AddNewChild(pUser);
    }
    else if (pUser->m_pRefSttSckt != pClientSocket)
    {//本地Ats断链重新登录
        pPrevSocket = pUser->m_pRefSttSckt;
        pUser->m_pRefSttSckt = pClientSocket;
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Test,0);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Ats,0);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
    }

    //重复登录不改变用户的权限
    pUser->AnalysisLoginUser(oSysCmd);
    pClientSocket->m_nIDTester = nIDTester;
    pUser->m_pRefSttSckt = pClientSocket;
    pUser->m_pRefSttSckt->SetUser(pUser);

    if (strIDTerminal == STT_TERMINAL_TYPE_REMOTE)
    {//远程重新登录
        BOOL bAtsAuthority = pUser->HasAuthority(KEY_AUTHORITY_MODULE_Ats);
        BOOL bTestAuthority = pUser->HasAuthority(KEY_AUTHORITY_MODULE_Test);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Test,0);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Ats,0);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
        if (bAtsAuthority)
        {
            CheckUpdateTestControlAuthority();
        }
        else if (bTestAuthority)
        {
            CheckCancelNativeClientAuthority();
        }
    }

    if (strIDTerminal != STT_TERMINAL_TYPE_REMOTE)
    {
        if (pUser->IsTerminalType_Local())
        {
            pClientSocket->SetSocketType(STT_SOCKET_TYPE_LOCAL);
        }
        else
        {
            pClientSocket->SetSocketType(STT_SOCKET_TYPE_OWN);
        }
    }
    else
    {
        pClientSocket->SetSocketType(STT_SOCKET_TYPE_REMOTE);
    }

    if (pPrevSocket != NULL)
    {
        pPrevSocket->CloseSocket();

        if (CanSendLog())
        {
            CString strInfo;
            strInfo.Format(_T("User_Login【%u】repeat"),nIDTester);
            LogDebugInfor(strInfo);
        }
    }

    return pUser;
}

long CSttNativeTestEngine::Process_Cmd_System_Request(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    //0:不可授权，1：已授权，2、可授权但未授权
    long nRet = AuthorityToUser(oSysCmd,TRUE,FALSE);
    if (nRet == 0)
    {
        return pClientSocket->RetFailureSysState(&oSysCmd);
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AppendParas(oSysCmd);
    pClientSocket->SendSysState(&oSysState);

    if (nRet == 2)
    {
        ReturnBroadcastUserMngr(oSysState);
    }

    return 1;
}

long CSttNativeTestEngine::Process_Cmd_System_Authority(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    //0:不可授权，1：已授权，2、可授权但未授权
    long nRet = AuthorityToUser(oSysCmd,FALSE,FALSE);
    if (nRet == 0)
    {
        return pClientSocket->RetFailureSysState(&oSysCmd);
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AppendParas(oSysCmd);
    pClientSocket->SendSysState(&oSysState);

    if (nRet == 2)
    {
        ReturnBroadcastUserMngr(oSysState);
    }

    return 1;
}

long CSttNativeTestEngine:: ReturnExecReply(CSttCmdBase *pCmd, long nCmdExecStatus,CSttCmdData *pRetData)
{
    //xxy测试命令应答
    if (pCmd->GetRefSocketData() == NULL)
    {
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oSttAtsCmd.m_pRefSocketDataBase == NULL"));
        return 0;
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(pCmd);

    if (pRetData != NULL)
    {//返回结果数据
        oSysState.AppendEx(*pRetData);
        pRetData->RemoveAll();
    }

    oSysState.Set_ExecStatus(nCmdExecStatus);

    //2020-11-29  lijunqing
    m_oClientUserMngr.SendSysState(pCmd->GetRefSocketData(), &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}

//autotest command

long CSttNativeTestEngine::Process_Cmd_Ats(CSttSocketDataBase *pClientSocket
                                         , BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{//更新当前自动测试命令
    if (g_nSttLogServerDebugInfor)
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, ">> rcv socket cmd............");
    }

	CSttAtsCmd *pAtsCmd = new CSttAtsCmd();
	pAtsCmd->AddRef();

    SetXmlBufferLen(nLen * 2);
    pAtsCmd->ParsePkgXml(pBuf,nLen, m_pszXmlBuffer);
    pAtsCmd->SetRefSocketData(pClientSocket);

    if (g_nSttLogServerDebugInfor)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, ">> rcv cmd [%s]............", m_oSttAtsCmd.m_strID.GetString());
    }

#ifdef _SttTestServer_For_Debug_
    if ((m_oSttAtsCmd.m_strID == STT_CMD_TYPE_ATS_ConnectDevice)
        || (m_oSttAtsCmd.m_strID == STT_CMD_TYPE_ATS_FinishInputData))
    {
        return Process_Cmd_Ats(pClientSocket, *pAtsCmd);
    }
    return 0;
#endif

    long nRet = Process_Cmd_Ats(pClientSocket, *pAtsCmd);
	pAtsCmd->Release();

	return nRet;
}

//2020-5-18  lijunqing
long CSttNativeTestEngine::Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
// #ifdef _SttTestServer_For_Debug_
// 	ReturnSysState(STT_CMD_ExecStatus_ACK);
// 	Sleep(1000);
// 	ReturnSysState(STT_CMD_ExecStatus_SUCCESS);
// 	return 0;
// #endif
    if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_CreateTest)
    {
        return Process_Cmd_Ats_CreateTest(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_StartTest)
    {
        return Process_Cmd_Ats_StartTest(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_StopTest)
    {
        return Process_Cmd_Ats_StopTest(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_CloseTest)
    {
        return Process_Cmd_Ats_CloseTest(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_TestItem)
    {
        return Process_Cmd_Ats_TestItem(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_TestFrom)
    {
        return Process_Cmd_Ats_TestFrom(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_TestAllFailedItems)
    {
        return Process_Cmd_Ats_TestAllFailedItems(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_GetItemReport)
    {
        return Process_Cmd_Ats_GetItemReport(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_GetReportFile)
    {
        return Process_Cmd_Ats_GetReportFile(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_GetSystemState)
    {
        return Process_Cmd_Ats_GetSystemState(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_CreateDevice)
    {
        return Process_Cmd_Ats_CreateDevice(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_ConnectDevice)
    {
        //return Process_Cmd_Ats_ConnectDevice(pClientSocket, oAtsCmd);
        return 0;
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_ConfigDevice)
    {
        return Process_Cmd_Ats_ConfigDevice(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_GetDataset)
    {
        return Process_Cmd_Ats_GetDataset(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_SetDataset)
    {
        return Process_Cmd_Ats_SetDataset(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_RunProcedure)
    {
        return Process_Cmd_Ats_RunProcedure(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_CloseDevice)
    {
        return Process_Cmd_Ats_CloseDevice(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_ConfigEngine)
    {
        return Process_Cmd_Ats_ConfigEngine(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_FinishInputData)
    {
        return Process_Cmd_Ats_FinishInputData(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_QueryAtsFile)
    {
        return Process_Cmd_Ats_QueryAtsFile(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_SetItemState)
    {
        return Process_Cmd_Ats_SetItemState(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_GenerateTemplate)
    {
        return Process_Cmd_Ats_GenerateTemplate(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_GenerateItems)
    {
        return Process_Cmd_Ats_GenerateItems(pClientSocket, oAtsCmd);
    }
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_GenerateMacroTest)
	{
		return Process_Cmd_Ats_GenerateMacroTest(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_SetItemPara)
    {
        return Process_Cmd_Ats_SetItemPara(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_ManuTriger)
    {
        return Process_Cmd_Ats_ManualTrigger(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_SaveTemplate)
    {
        return Process_Cmd_Ats_SaveTemplate(pClientSocket, oAtsCmd);
    }
    else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_SaveTest)
    {
        return Process_Cmd_Ats_SaveTest(pClientSocket, oAtsCmd);
    }
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_ExportWordRpt)
	{
		return Process_Cmd_Ats_ExportWordRpt(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_OpenTemplate)
	{
		return Process_Cmd_Ats_OpenTemplate(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_OpenGbrptFile)
	{
		return Process_Cmd_Ats_OpenGbrptFile(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_AdjustMainWnd)
	{
		return Process_Cmd_Ats_AdjustMainWnd(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_ExportReport)
	{
		return Process_Cmd_Ats_ExportReport(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_QueryItem)
	{
		return Process_Cmd_Ats_QueryItem(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_UpdateItem)
	{
		return Process_Cmd_Ats_UpdateItem(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_AdjustReport)
	{
		return Process_Cmd_Ats_AdjustReport(pClientSocket, oAtsCmd);
	}
	else if (oAtsCmd.m_strID == STT_CMD_TYPE_ATS_ClearReportsRslts)
	{
		return Process_Cmd_Ats_ClearReportsRslts(pClientSocket, oAtsCmd);
	}
	else
    {
        return 0;
    }
}

long CSttNativeTestEngine::Process_Cmd_Test(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
	char* pszXmlBuffer = new char[2 * nLen + 10];
	memset(pszXmlBuffer, 0, 2 * nLen + 10);
	CSttTestCmd *pTestCmd = new CSttTestCmd();
	pTestCmd->ParsePkgXml(pBuf,nLen, pszXmlBuffer);
	delete pszXmlBuffer;

	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("++++CSttNativeTestEngine::Process_Cmd_Test++++"));
	 ReturnExecReply(pTestCmd, STT_CMD_ExecStatus_ACK);
	long nRet = m_pSmartTest->Process_Cmd_Test(pTestCmd);

	if (nRet >= 0)
	{
		 ReturnExecReply(pTestCmd, STT_CMD_ExecStatus_SUCCESS);
	}
	else
	{
		 ReturnExecReply(pTestCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return nRet;
}
/*
<ats-cmd name="" id="GetDataset" testor="" >
    <paras name="" id="">
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
    </paras>
</ats -cmd>
*/
CDvmDataset* CSttNativeTestEngine::Ats_GetDataset(CSttAtsCmd &oAtsCmd)
{
    CDvmDataset *pDatset = NULL;
    CString strDatasetPath;
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_DatasetPath, strDatasetPath);

#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    CPxiDevice *pPxiDevice = g_thePxiEngine->GetDeviceByIndex(0);

    if (pPxiDevice == NULL)
    {
        return NULL;
    }

    CPxiDataSet *pXiDataset = pPxiDevice->FindDataSet(strDatasetPath);

    if (pXiDataset != NULL)
    {
        pDatset = pXiDataset->m_pDataset;
        delete pXiDataset;
    }
#endif
    return pDatset;
}

/*
<ats-cmd name="" id="SetDataset" testor="" >
    <paras name="" id="">
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
        <dataset id="LLN0$dsSetting1" name="">
            ...............................
        </dataset>
    </paras>
</ats -cmd>
*/
long CSttNativeTestEngine::Ats_SetDataset(CSttAtsCmd &oAtsCmd)
{
    CDvmDataset *pDataset = oAtsCmd.GetDataset();

    if (pDataset == NULL)
    {
        return 0;
    }

    CString strDatasetPath;
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_DatasetPath, strDatasetPath);

#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    CPxiDevice *pPxiDevice = g_thePxiEngine->GetDeviceByIndex(0);
    CPxiDataSet *pXiDataset = pPxiDevice->FindDataSet(strDatasetPath);

    if (pXiDataset != NULL)
    {
        pXiDataset->InitByDataset(pDataset);
        delete pXiDataset;
        return 1;
    }
    else
    {
        return 0;
    }
#endif
	return 0;
}

/*
<ats-cmd name="" id="ConfigDevice" testor="" >
    <paras name="" id="">
        <group id="comm-config" >  【通信地址设置】
            参见CreateDevice指令
        </group>
    </paras>
</ats -cmd>
*/
long CSttNativeTestEngine::Ats_ConfigDevice(CSttAtsCmd &oAtsCmd)
{
#ifdef _PSX_QT_LINUX_
    CPxiDevice *pPxiDevice = NULL;
    pPxiDevice = g_thePxiEngine->GetDeviceByIndex(0);

    if (pPxiDevice == NULL)
    {
        return 0;
    }

    //STT_CMD_PARA_CommConfig
    CSttParas *pParas = oAtsCmd.GetSttParas();
    CDataGroup *pCommConfig = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_CommConfig);
    pPxiDevice->InitCmmConfig(pCommConfig, TRUE);
#endif
    return 1;
}

void CSttNativeTestEngine::Return_Ats_Success(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd, unsigned int nState, CDvmDataset *pDatas, CExBaseObject *pGuideBook)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
    oSysState.Set_ExecStatus(nState);
    CSttParas *pParas = NULL;
    pParas = oSysState.GetSttParas();

    //2020-11-30   lijunqing
    if (pDatas != NULL)
    {
        pParas->AppendClone(*pDatas);
    }

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
    //2020-12-01  lijunqing
    if (pGuideBook != NULL)
    {
        CSttGuideBook *pSttGuideBook = pParas->NewGuideBook();
        CSttCmdGuideBookTransTool oTool;
        oTool.Trans((CGuideBook*)pGuideBook, pSttGuideBook);
    }
#endif

    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
}

long CSttNativeTestEngine::Process_Cmd_Ats_CreateTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if (m_pSmartTest == NULL)
    {
		 if (g_theSttSmartTest != NULL)
		 {
			 m_pSmartTest = g_theSttSmartTest;
		 }
		 else
		 {
        m_pSmartTest = new CSttSmartTest();
    }
	 }

	m_pSmartTest->m_bTestCreated = FALSE;
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("@@@@@@@@@@@@@@@@@@@@degub---------0000"));
    long nRet = m_pSmartTest->Ats_CreateTest(&oAtsCmd, NULL);

// 	CTickCount32 oTick;
// 	while (TRUE)
// 	{
// 		if (m_pSmartTest->m_bTestCreated)
// 		{
// 			break;
// 		}
// 
// 		oTick.DoEvents(100);
// 	}

	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("@@@@@@@@@@@@@@@@@@@@degub---------1111"));

    if (nRet == CREATE_TEST_CREATE_ERROR || nRet == CREATE_TEST_CURR_EXIST_NOT_SAME)
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }
    else if (CREATE_TEST_CREATE_NEW  == nRet || CREATE_TEST_CURR_EXIST_SAME == nRet)
    {
        CDvmDataset oDatas;
        CString strGbrptFile = m_pSmartTest->GetProjectName();
		//注释此处，传递全路径  shaolei 20220707
        //strGbrptFile = GetPathFileNameFromFilePathName(strGbrptFile);
        oDatas.AddNewData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, "string", strGbrptFile);
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oDatas, NULL);
       // stt_Return_Ats_Event_Ex(m_pSmartTest->GetTestControl(), SYS_STATE_EVENT_OnTestCreated, _T(""));
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_StartTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	CSttParas *pParas = oAtsCmd.GetSttParas();
    CDataGroup *pUIParas = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_MacroUIParas);
    CDataGroup *pTestMacroUI = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_TestMacroUI);

    //此处需要判UIParas是否也不为空，因为上位机需要判断界面参数是否改变，如果改变，才需要下发界面参数
    if(pUIParas != NULL && pTestMacroUI != NULL)
    {
        //先强行将oAtsCmd的ID 改为GenerateTemplate，并进行模板生成
        oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
		m_pSmartTest->SetTemplateGenMode(TEMPLATE_GEN_MODE_STARTTEST);
        Process_Cmd_Ats_GenerateTemplate(pClientSocket, oAtsCmd);
        oAtsCmd.m_strID = STT_CMD_TYPE_ATS_StartTest;
    }

    if (m_pSmartTest->Ats_StartTest(&oAtsCmd, NULL))
    {
        Return_Ats_Success(pClientSocket, oAtsCmd);
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_StopTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

    m_pSmartTest->Ats_StopTest(&oAtsCmd, NULL);
    Return_Ats_Success(pClientSocket, oAtsCmd);

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_CloseTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    m_pSmartTest->Ats_CloseTest(&oAtsCmd, NULL);

    Return_Ats_Success(pClientSocket, oAtsCmd);

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_TestItem(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    if (m_pSmartTest->Ats_TestItem(&oAtsCmd, NULL))
    {
        Return_Ats_Success(pClientSocket, oAtsCmd);
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_TestFrom(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    if (m_pSmartTest->Ats_TestFrom(&oAtsCmd, NULL))
    {
        Return_Ats_Success(pClientSocket, oAtsCmd);
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_TestAllFailedItems(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    m_pSmartTest->Ats_TestAllFailedItems(&oAtsCmd, NULL);
    Return_Ats_Success(pClientSocket, oAtsCmd);

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_GetItemReport(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    if (m_pSmartTest->Ats_GetItemReport(&oAtsCmd, NULL))
    {
        Return_Ats_Success(pClientSocket, oAtsCmd);
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_GetReportFile(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    if (m_pSmartTest->Ats_GetReportFile(&oAtsCmd, NULL))
    {
        Return_Ats_Success(pClientSocket, oAtsCmd);
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_GetSystemState(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    m_pSmartTest->Ats_GetSystemState(&oAtsCmd, NULL);

    return 0;
}

/*
<ats-cmd name="" id="CreateDevice" testor="" >
    <paras name="" id="">
        <data id="ppxml-file" value="*.ppxml" /> 【规约模板文件】
        <data id="dvm-file" value="*.xml" />  【点表文件】
        <data id="cmm-cfg-file" value="*.xml" />  【通信地址设置文件】
        <group id="omm-config" >  【通信地址设置】
            <data id="serial" value=""/>【串口】
                <value id="port_number" value="4"/>
                <value id="baud-rate" value="4800"/>
                <value id="byte-size" value="8"/>
                <value id="stop-bit" value="2"/>
                <value id="parity" value="0"/>
                <value id="port_number" value="4"/>
            </data>
            <data id="tcp-server" value=""/>
                <value id="local-ip" value="127.0.0.1"/>
                <value id="local-port" value="2404"/>
            </data>
            <data id="tcp-client" value=""/>
                <value id="local-ip" value="127.0.0.1"/>
                <value id="local-port" value="0"/>
                <value id="remote-ip" value="100.100.102.1"/>
                <value id="remote-port" value="2404"/>
            </data>
            <data id="udp-server" value=""/>
                <value id="local-ip" value="127.0.0.1"/>
                <value id="local-port" value="2404"/>
                <value id="use-broadcast" value="0"/>
                <value id="multicast-ip" value="0.0.0.0"/>
                <value id="multicast-port" value="0"/>
            </data>
            <data id="udp-client" value=""/>
                <value id="local-ip" value="127.0.0.1"/>
                <value id="local-port" value="2404"/>
                <value id="remote-ip" value="100.100.102.1"/>
                <value id="remote-port" value="2404"/>
                <value id="use-broadcast" value="0"/>
                <value id="multicast-ip" value="0.0.0.0"/>
                <value id="multicast-port" value="0"/>
            </data>
        </group>
    </paras>
</ats -cmd>
<sys-state name="" id="CreateDevice" mater-host="">
    <paras name="" id="">
        <data id="ConnectState" value=""/>【连接成功与否的状态】
        <data id="FileNotExist" value="文件名"/> 【如果文件不存在】
    </paras>
<sys-state>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_CreateDevice(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    CString strPpTemplateFile, strDeviceFile, strDeviceID;
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    CPxiDevice *pPxiDevice = NULL;

    oAtsCmd.GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpTemplateFile);
    oAtsCmd.GetParasDataValueByID(XPARA_ID_DVMFILE, strDeviceFile);
    oAtsCmd.GetParasDataValueByID(DATAID_DEVICEID, strDeviceID);

    //lijunqing 2020-09-09 只考虑单装置
    //pPxiDevice = g_thePxiEngine->FindDevice(strDeviceID);
    pPxiDevice = g_thePxiEngine->GetDeviceByIndex(0);

    if (pPxiDevice != NULL)
    {
        if (!pPxiDevice->IsConnectSuccessful())
        {
            //已经存在，则返回不处理
            return 0;
        }
    }
    else
    {
        pPxiDevice = g_thePxiEngine->CreateDevice(strPpTemplateFile, strDeviceFile, strDeviceID, NULL);
    }
#endif

    long nRet = Ats_ConfigDevice(oAtsCmd);

    //返回系统状态
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
    oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    oSysState.Set_ConnectState(pPxiDevice->IsConnectSuccessful());
#endif
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}

/*
long CSttNativeTestEngine::Process_Cmd_Ats_ConnectDevice(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    CString strTemplateFile, strDeviceFile;
    CString strDeviceIP = _T(""),strTestAppIP = _T("");
    CSttParas *pParas = oAtsCmd.GetSttParas();
    BOOL bPpXml = pParas->GetDataValue(XPARA_ID_PPXMLFILE, strTemplateFile);
    BOOL bDvmFile = pParas->GetDataValue(XPARA_ID_DVMFILE, strDeviceFile);

    CString strCmmConfigKey;
    strCmmConfigKey = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey;
    CDataGroup *pGroup = (CDataGroup*)pParas->FindByID(strCmmConfigKey);
    if (pGroup == NULL)
    {
         ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_FAILURE);
        return 0;
    }
    CDvmData *pData = (CDvmData *)pGroup->GetHead();
    if (pData == NULL)
    {
         ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_FAILURE);
        return 0;
    }

    pData->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey, strDeviceIP);
    DWORD nDeviceIP = csIP2dwIP(strDeviceIP);
    nDeviceIP++;
    strTestAppIP = dwIP2csIP(nDeviceIP);

// 	CString strCmdInfo;
// 	strCmdInfo.Format(_T("ifconfig eth0:1 %s netmask 255.255.255.0 up"),strTestAppIP);
// 	system(strCmdInfo);

    //返回系统状态
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
    oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
    oSysState.Set_ConnectState(1);
    ReturnSysState(pClientSocket, &oSysState);

    return 0;
}
*/

long CSttNativeTestEngine::Process_Cmd_Ats_ConfigDevice(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);

    CString strDeviceID;
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_DeviceID, strDeviceID);
#ifdef _PSX_QT_LINUX_
    //STT_CMD_PARA_CommConfig
    CSttParas *pParas = oAtsCmd.GetSttParas();
    CDataGroup *pCommConfig = (CDataGroup*)pParas->FindByID(STT_CMD_PARA_CommConfig);
#endif

#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    CPxiDevice *pPxiDevice = g_thePxiEngine->GetItem(0);

    if (pPxiDevice == NULL)
    {
        oSysState.Set_ExecStatus_Failure();
        oSysState.Set_ExecStatus(0);
        CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("ConfigDevice: has no device"));

        return 0;
    }

    pPxiDevice->InitCmmConfig(pCommConfig, TRUE);
#endif


	if (m_pSmartTest != NULL)
	{
		m_pSmartTest->Ats_ConfigDevice(&oAtsCmd, NULL);
	}

    oSysState.Set_ExecStatus_Success();
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    oSysState.Set_ConnectState(pPxiDevice->IsConnectSuccessful());
#endif
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}

/*
<ats-cmd name="" id="GetDataset" testor="" >
    <paras name="" id="">
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
    </paras>
</ats -cmd>
<sys-state name="" id="CreateDevice" mater-host="">
    <paras name="" id="">
        <dataset id="LLN0$dsSetting1" name="">
            <data name="差动速断电流定值" id="PDIF1$SG$StrValSG"
                data-type="STRUCT" unit="" unit-path="PDIF1$CF$StrValSG$units"
                unit-value="0" value="4.000000" default-value="4.000000"
                max="20.000000" min="0.050000" step="0.001000">
                <value data-type="FLOAT" id="PDIF1$SG$StrValSG$setMag$f"
                    name="" value="4.000000"/>
            </data>
            <data name="差动保护启动电流定值" id="PDIF2$SG$StrValSG"
                data-type="STRUCT" unit="" unit-path="PDIF2$CF$StrValSG$units"
                unit-value="0" value="0.500000" default-value="0.500000"
                max="5.000000" min="0.050000" step="0.001000">
                <value data-type="FLOAT" id="PDIF2$SG$StrValSG$setMag$f"
                    name="" value="0.500000"/>
            </data>
            ...............................
        </dataset>
    </paras>
<sys-state>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_GetDataset(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);

    CDvmDataset *pDataset = Ats_GetDataset(oAtsCmd);
    CSttParas *pParas = oSysState.GetSttParas();

    if (pDataset != NULL)
    {
        pParas->AddTail(pDataset);
    }

    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
    pParas->RemoveAll();

    return 0;
}

/*
<ats-cmd name="" id="SetDataset" testor="" >
    <paras name="" id="">
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
        <dataset id="LLN0$dsSetting1" name="">
            ...............................
        </dataset>
    </paras>
</ats -cmd>
<sys-state name="" id=" SetDataset " mater-host="">
    <paras name="" id="">
        <data id="ExecStatus" value="1"/>
    </paras>
<sys-state>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_SetDataset(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    CPxiDevice *pPxiDevice = g_thePxiEngine->GetItem(0);

    if (pPxiDevice == NULL)
    {
        Return_NoDevice(pClientSocket, oSysState);
        return 0;
    }
#endif
    if (Ats_SetDataset(oAtsCmd))
    {
        oSysState.Set_ExecStatus_Success();
        ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
    }
    else
    {
        oSysState.Set_ExecStatus_Failure();
        ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
    }

    return 0;
}

/*
<ats-cmd name="" id="RunProcedure" testor="" >
    <paras name="" id="">
        <data id="id-procedure" value="WriteSetting">【执行的通信过程】
            <value data-type="FLOAT" id="" name="" value="" />【通信过程的参数】
        </data>
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
        <dataset id="LLN0$dsSetting1" name="">
            ...............................
        </dataset>
    </paras>
</ats -cmd>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_RunProcedure(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    CPxiDevice *pPxiDevice = g_thePxiEngine->GetItem(0);

    if (pPxiDevice == NULL)
    {
        Return_NoDevice(pClientSocket, oSysState);
        return 0;
    }
#endif
    CDvmData *pData_Procedure = oAtsCmd.FindParasDataByID(STT_CMD_PARA_ProcedureID);
    CDvmData *pData_DS = oAtsCmd.FindParasDataByID(STT_CMD_PARA_DatasetPath);

    if (pData_Procedure == NULL)
    {
         oSysState.Set_ExecStatus_Failure();
         ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
         return 0;
    }

    //初始化命令的参数
    if (pData_Procedure->GetCount() > 0)
    {
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
        CPxiDataInterface *pXiDataInterface = pPxiDevice->GetDataInterface();
        pXiDataInterface->InitDataInterface(pData_Procedure);
#endif
    }

    //数据集数据设置
    Ats_SetDataset(oAtsCmd);

    //执行通信过程
     long nRet = 0;
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    if (pData_DS != NULL)
    {
        nRet = pPxiDevice->RunProcedure(pData_Procedure->m_strValue, pData_DS->m_strValue);
    }
    else
    {
        nRet = pPxiDevice->RunProcedure(pData_Procedure->m_strValue, _T(""));
    }
#endif
    if (nRet == 0)
    {
        //通信时间较长，返回执行开始
        oSysState.Set_ExecStatus_Success();
    }
    else if (nRet == -1)
    {
        oSysState.Set_ExecStatus_Failure();
    }
    else
    {
         oSysState.Set_ExecStatus_Success();
         oSysState.AddNewParasData(PXI_DATA_ID_EngineSysState, pxi_get_engine_sys_state(nRet));
    }

    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}

/*
<ats-cmd name="CloseDevice" id="" testor="" >
    <paras name="" id="">
        <data id="DeviceID" value=" "/>
    </paras>
</ats -cmd>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_CloseDevice(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
    CPxiDevice *pPxiDevice = g_thePxiEngine->GetItem(0);

    if (pPxiDevice == NULL)
    {
        Return_NoDevice(pClientSocket, oSysState);
        return 0;
    }

    //暂时不考虑多装置的情况
    pPxiDevice->UnLoad();
#endif

    oSysState.Set_ExecStatus_Success();
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}

/*
<ats-cmd name="" id="ConfigEngine" testor="" >
    <paras name="" id="">
        <data id=" log-data-bind " value=" "/>【显示数据绑定错误】
        <data id=" log-pkg-data-infor " value=" "/>【显示报文数据信息】
        <data id=" log-pkg " value=" "/>【显示发送、接受报文】
        <data id=" log-debug-infor " value=" "/>【显示调试信息】
        <data id=" no-change-when-same " value=" "/>【数据相同不执行修改】
    </paras>
</ats -cmd>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_ConfigEngine(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    //兼容 两个设置关键字 2020-10-18  lijunqing
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_LogServerDebugInfor,  g_nSttLogServerDebugInfor);
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_LogDebugInfor,  g_nSttLogServerDebugInfor);

    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_LogDataBind,  g_bLogBindQueryErrorInfor);
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_LogPkg,  g_bLogPackageInfor);
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_LogProtocolDebugInfor,  g_bLogEngineDebugInfor);
    oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_CloseTestWhenDisconnect,  g_nCloseTestWhenDisconnect);

    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_FinishInputData(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    //2020-10-18  lijunqing
    //返回执行成功，必须放到Ats_FinishInputData指令前面，否则先返回了结果数据
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_SUCCESS);

    //执行
    CSttParas *pParas = oAtsCmd.GetSttParas();
    m_pSmartTest->Ats_FinishInputData(&oAtsCmd, NULL);

    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_QueryAtsFile(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    CSttQueryAtsFileTool oQueryTool;
    oQueryTool.QueryAtsFile(oAtsCmd, oSysState);

    oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}


long CSttNativeTestEngine::Process_Cmd_Ats_SetItemState(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    if (m_pSmartTest->Ats_SetItemState(&oAtsCmd, NULL))
    {
        Return_Ats_Success(pClientSocket, oAtsCmd);
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_GenerateTemplate(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    //shaolei 注释此处   2022-1-12
    //生成模板时，还没有创建测试，因此m_pSmartTest指针还为空，此处不能判断ValidateSmartTest，故注释此处
//     if ( !ValidateSmartTest(pClientSocket, oSysState))
//     {
//         return 0;
//     }


    if (m_pSmartTest == NULL)
    {
		if (g_theSttSmartTest != NULL)
		{
			m_pSmartTest = g_theSttSmartTest;
		}
		else
		{
        m_pSmartTest = new CSttSmartTest();
    }
    }

    long nRet = m_pSmartTest->Ats_GenerateTemplate(&oAtsCmd, NULL);
    CSttParas *pParas = oAtsCmd.GetSttParas();
    CString strRetMode;
    strRetMode = STT_CMD_PARA_TtRetMode_GBXML;   //默认返回全模板
    pParas->GetDataValue(STT_CMD_PARA_TtRetMode, strRetMode);

    if (nRet == 0)
    {
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
        CGuideBook *pGuideBook = m_pSmartTest->GetGuideBook_AtsGen();
#endif
        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);

        //此处需要根据模板返回模式，确认是哟功能CSttGuideBook还是CGuideBook；
        if(strRetMode == STT_CMD_PARA_TtRetMode_GBXML)
        {

        }
        else
        {
        }

        //暂时使用SCttGuideBook
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
        CSttCmdGuideBookTransTool oTool;
        CSttGuideBook *pNewSttGuideBook = pParas->NewGuideBook();
        oTool.Trans(pGuideBook, pNewSttGuideBook);
#endif
#ifdef _PSX_QT_LINUX_
		CSttCmdDefineXmlRWKeys::SetOnlyGetItem(TRUE);
#endif
        ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
#ifdef _PSX_QT_LINUX_
		CSttCmdDefineXmlRWKeys::SetOnlyGetItem(FALSE);
#endif
        pParas->RemoveAll();
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

	m_pSmartTest->SetTemplateGenMode(TEMPLATE_GEN_MODE_NORMAL);
    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_GenerateItems(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    long nRet = m_pSmartTest->Ats_GenerateItems(&oAtsCmd, NULL);
	CSttItems *pItems = NULL;
	CDataGroup *pGlobalDatas = NULL;
	CDataGroup *pSysPara = NULL;
	CString strGenerateItems;
	CSttParas *pRetParas = oSysState.GetSttParas();

    if (nRet == 0)
    {
		oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
		CSttParas *pSttCmdParas = oAtsCmd.GetSttParas();
		CDataGroup *pGenerateItems = (CDataGroup *)pSttCmdParas->FindByID(STT_CMD_PARA_generate_items);
		long nAddDevReset = 0;   //是否添加装置复归态

		if (pGenerateItems != NULL)
		{
			strGenerateItems = pGenerateItems->m_strValue;

			CDataGroup *p_device = (CDataGroup*)pGenerateItems->FindByID(XPARA_ID_device);

			if (p_device != NULL)
			{
				p_device->GetDataValue(XPARA_ID_AddDevReset, nAddDevReset);
			}
		}

		if (m_pSmartTest->Is_GenerateItems_CmdWzd())
		{
			CDataGroup *pReply = m_pSmartTest->GetGenrateItems_CmdWzd_Reply();
			CDataGroup *pCommCmd = pRetParas->AddNewGroup(_T("通讯命令生成配置"), STT_CMD_PARA_CommCmd, _T(""));
			pCommCmd->AppendCloneEx2(*pReply, TRUE, TRUE);
		}
		else if (strGenerateItems == STT_CMD_PARA_generate_items_cmd_add_grp)
		{
			pItems = m_pSmartTest->GetSttItems_AtsGen_CmdAddGrp();

			if (pItems != NULL)
			{
				CString strParentItemPath;
				pGenerateItems->GetDataValue(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
				pRetParas->AddNewData(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
				pRetParas->AddTail(pItems);
			}
		}
		else if (strGenerateItems == STT_CMD_PARA_generate_items_import_dvm_file)
		{
			pItems = m_pSmartTest->GetSttItems_AtsGen_ImportDvm();

			if (pItems != NULL)
			{
				pRetParas->AddTail(pItems);
			}
		}
		else if(strGenerateItems == STT_CMD_PARA_generate_items_ain_data_map)
		{
			pItems = m_pSmartTest->GetSttItems_AtsGen_AinCfg();

			if (pItems != NULL)
			{
				pRetParas->AddTail(pItems);
			}

			//返回报文后，立刻释放
			m_pSmartTest->FreeItems_AinCfg();
		}
		else
		{
			pItems = m_pSmartTest->GetSttItems_AtsGen();

			if (pItems != NULL && pItems->m_strID != STT_ITEMS_ID_DEVRESET)
			{
				CString strParentItemPath;
				oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
				pRetParas->AddNewData(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
				pRetParas->AddTail(pItems);
			}
		}

		if (strGenerateItems == STT_CMD_PARA_generate_items_create)
		{
			//如果是create指令，应当返回全局数据和系统参数
			pGlobalDatas = new CDataGroup;
			pGlobalDatas->m_strName = _T("全局数据");
			pGlobalDatas->m_strID = STT_CMD_PARA_GlobalDatas;
			CExBaseList *pDatas = m_pSmartTest->GetGlobalDatas();
			pGlobalDatas->AppendCloneEx(*pDatas, TRUE);

			pSysPara = new CDataGroup;
			pSysPara->m_strName = _T("系统参数");
			pSysPara->m_strID = STT_CMD_PARA_SysPara;
			CDataSet *p = (CDataSet *)m_pSmartTest->GetSysPara();//(CDataSet*类型)
			CDvmDataset *pDsNew = new CDvmDataset();
			p->Data_Gb_to_Dvm(pDsNew);
			pSysPara->AppendEx(*pDsNew, TRUE);
			pDsNew->RemoveAll();
			delete pDsNew;

			pRetParas->AddNewChild(pGlobalDatas);
			pRetParas->AddNewChild(pSysPara);

			if (nAddDevReset == 1)
			{
				pItems = m_pSmartTest->GetSttItems_AtsGen();

				if (pItems != NULL)
				{
					CString strParentItemPath;
					//CDevice下的项目，父项目路径为空
					pRetParas->AddNewData(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
					pRetParas->AddTail(pItems);
				}
			}
		}

		oSysState.Set_Xml_Pkg_With_Name(TRUE);
		ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
		oSysState.Set_Xml_Pkg_With_Name(FALSE);

		/*
		if (pItems != NULL)
		{
			pRetParas->Delete(pItems);
		}

		if (pGlobalDatas != NULL)
		{
			pRetParas->Delete(pGlobalDatas);
		}

		if (pSysPara != NULL)
		{
			pRetParas->Delete(pSysPara);
		}

		pRetParas->RemoveAll();
		*/
    }
    else if (nRet == -1)
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS);
	}

	/*
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("stt_return.xml");
	oSysState.SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	*/

    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_GenerateMacroTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	long nRet = m_pSmartTest->Ats_GenerateMacroTest(&oAtsCmd, NULL);

	CMacroTest *pMacroTest = NULL;
	CItems *pItems = NULL;
	CSttItems *pSttItems = NULL;

	if (nRet == 0)
	{
		oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
		CSttParas *pParas = oSysState.GetSttParas();

		pMacroTest = m_pSmartTest->GetSttMacroTest_AtsGen();

		if (pMacroTest != NULL)
		{
			pItems = (CItems *)pMacroTest->GetParent()->GetParent();  //paras节点目前只能携带items
			CString strParentItemPath;
			CString strItemsID;
            strItemsID.Format(_T("%s$"), pItems->m_strID.GetString());
			oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
			strParentItemPath = strItemsID + strParentItemPath;
			pParas->AddNewData(STT_CMD_PARA_ParentItemsPath, strParentItemPath);

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
			pSttItems = new CSttItems();
			CSttCmdGuideBookTransTool oTool;
			oTool.Trans(pItems, pSttItems);

			pParas->AddTail(pSttItems);
#endif
		}

		oSysState.Set_Xml_Pkg_With_Name(TRUE);
		ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
		oSysState.Set_Xml_Pkg_With_Name(FALSE);

		if (pItems != NULL)
		{
			pParas->Delete(pSttItems);
		}

		pParas->RemoveAll();
	}
	else if (nRet == -1)
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS);
	}

	return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_SetItemPara(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    //对于SystemConfig，需要根据HasDigital，动态创建或者删除Iec61850Config项目
    CString strMacroID;
    CSttParas *pParas = oAtsCmd.GetSttParas();
    pParas->GetDataValue(STT_CMD_PARA_MacroID, strMacroID);

    if(strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig)
    {
        Procss_Cmd_Ats_SetItemPara_SystemConfig(pClientSocket, oAtsCmd);
    }

    long nRet = m_pSmartTest->Ats_SetItemPara(&oAtsCmd, NULL);

    if (nRet == 0)
    {
        Return_Ats_Success(pClientSocket, oAtsCmd);

        CSttParas *pSttParas = oAtsCmd.GetSttParas();
        m_pSmartTest->UpdateParameter(pSttParas);
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}

//系统参数配置，根据是否含有数字量，进行木板更新，并返回给上位机，刷新项目列表
long CSttNativeTestEngine::Procss_Cmd_Ats_SetItemPara_SystemConfig(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);

	//在外部已经调用过ValidateSmartTest，此处不需要调用了。
//     if ( !ValidateSmartTest(pClientSocket, oSysState))
//     {
//         return 0;
//     }

    m_pSmartTest->Ats_SetItemPara_SystemConfig(&oAtsCmd, NULL);

    //返回GenerateTemplate的Success事件，以便上位机去刷新项目列表
    oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	CSttParas *pReturnParas = oSysState.GetSttParas();
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
    CGuideBook *pGuideBook = m_pSmartTest->GetGuideBook_AtsGen();
//     CString strPath;
//     strPath = _P_GetLibraryPath();
//     strPath += _T("0000-1.gbxml");
//     pGuideBook->SaveXMLFile(strPath);
    //此处需要根据模板返回模式，确认是哟功能CSttGuideBook还是CGuideBook；
    //暂时使用SCttGuideBook
	if (pGuideBook != NULL)
	{
		CSttCmdGuideBookTransTool oTool;
		CSttGuideBook *pNewSttGuideBook = pReturnParas->NewGuideBook();
		oTool.Trans(pGuideBook, pNewSttGuideBook);
	}
#endif
	oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
    pReturnParas->RemoveAll();
    oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SetItemPara;
    return 0;
}

long  CSttNativeTestEngine::Process_Cmd_Ats_ManualTrigger(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    if ( !ValidateSmartTest(pClientSocket, oSysState))
    {
        return 0;
    }

    long nRet = m_pSmartTest->Ats_ManualTrigger(&oAtsCmd, NULL);

    if (nRet > 0 )
    {
        Return_Ats_Success(pClientSocket, oAtsCmd);
    }
    else
    {
        Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
    }

    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_SaveTemplate(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	CSttParas *pParas = oAtsCmd.GetSttParas();
	CDataGroup *pUIParas = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_MacroUIParas);
	CDataGroup *pTestMacroUI = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_TestMacroUI);

	//此处需要判UIParas是否也不为空，因为上位机需要判断界面参数是否改变，如果改变，才需要下发界面参数
	if(pUIParas != NULL && pTestMacroUI != NULL)
	{
		//先强行将oAtsCmd的ID 改为GenerateTemplate，并进行模板生成
		oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
		m_pSmartTest->SetMacroTestSaveParas(TRUE);
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK//zhouhj 2024.8.24 处理解决编译问题
		m_pSmartTest->SetTemplateGenMode(TEMPLATE_GEN_MODE_SAVE);
#endif
		Process_Cmd_Ats_GenerateTemplate(pClientSocket, oAtsCmd);
#ifndef _PSX_QT_LINUX_
		m_pSmartTest->SetMacroTestSaveParas(FALSE);
#endif
		oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SaveTemplate;
	}

	long nRet = m_pSmartTest->Ats_SaveTemplate(&oAtsCmd, NULL);

	if (nRet > 0 )
	{
		Return_Ats_Success(pClientSocket, oAtsCmd);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_SaveTest(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	CSttParas *pParas = oAtsCmd.GetSttParas();
	CDataGroup *pUIParas = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_MacroUIParas);
	CDataGroup *pTestMacroUI = (CDataGroup *)pParas->FindByID(STT_CMD_PARA_TestMacroUI);

	//此处需要判UIParas是否也不为空，因为上位机需要判断界面参数是否改变，如果改变，才需要下发界面参数
	if(pUIParas != NULL && pTestMacroUI != NULL)
	{
		//先强行将oAtsCmd的ID 改为GenerateTemplate，并进行模板生成
		oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
		m_pSmartTest->SetMacroTestSaveParas(TRUE);
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK//zhouhj 2024.8.24 处理解决编译问题
		m_pSmartTest->SetTemplateGenMode(TEMPLATE_GEN_MODE_SAVE);
#endif
		Process_Cmd_Ats_GenerateTemplate(pClientSocket, oAtsCmd);
#ifndef _PSX_QT_LINUX_
		m_pSmartTest->SetMacroTestSaveParas(FALSE);
#endif
		oAtsCmd.m_strID = STT_CMD_TYPE_ATS_SaveTest;
	}

	long nRet = m_pSmartTest->Ats_SaveTest(&oAtsCmd, NULL);

	if (nRet > 0 )
	{
		Return_Ats_Success(pClientSocket, oAtsCmd);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

    return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_ExportWordRpt(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	long nRet = m_pSmartTest->Ats_ExportWordRpt(&oAtsCmd, NULL);

	if (nRet > 0 )
	{
		Return_Ats_Success(pClientSocket, oAtsCmd);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_OpenTemplate(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	long nRet = m_pSmartTest->Ats_OpenTemplate(&oAtsCmd, NULL);

	if (nRet > 0 )
	{
		Return_Ats_Success(pClientSocket, oAtsCmd);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return 0;
}

/*
<ats-cmd name="" id="OpenGbrptFile" mid="0" time="2022-07-18 13:50:09" testor="ATS">
	<paras name="" id="">
		<data id="gbrpt-file" data-type="string" value="d:\Program Files\EPOTO\e-Report\Workspace\PT220_220kV及以下电压等级主变保护装置全检式调试削验收削更换作业指导书\G智能站.gbrpt" />
	</paras>
</ats-cmd>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_OpenGbrptFile(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if (m_pSmartTest == NULL)
	{
		 if (g_theSttSmartTest != NULL)
		 {
			 m_pSmartTest = g_theSttSmartTest;
		 }
		 else
		 {
		m_pSmartTest = new CSttSmartTest();
	}
	 }

	long nRet = m_pSmartTest->Ats_OpenGbrptFile(&oAtsCmd, NULL);

	if (nRet > 0 )
	{
		//Return_Ats_Success(pClientSocket, oAtsCmd);

		CDvmDataset oDatas;
		CString strGbrptFile = m_pSmartTest->GetProjectName();
		//注释此处，传递全路径  shaolei 20220707
		//strGbrptFile = GetPathFileNameFromFilePathName(strGbrptFile);
		oDatas.AddNewData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, "string", strGbrptFile);
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oDatas, NULL);
		stt_Return_Ats_Event_Ex(m_pSmartTest->GetTestControl(), SYS_STATE_EVENT_OnTestCreated, _T(""));
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return 0;
}

/*
<ats-cmd name="" id="AdjustMainWnd" mid="0" time="2022-07-18 13:50:09" testor="ATS">
	<paras name="" id="">
		<data id="main-wnd" data-type="long" value="724972" />
		<data id="log-wnd" data-type="long" value="397634" />
	</paras>
</ats-cmd>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_AdjustMainWnd(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	long nRet = m_pSmartTest->Ats_AdjustMainWnd(&oAtsCmd, NULL);

	if (nRet > 0 )
	{
		//成功，返回主窗口
		CDvmDataset oDatas;

		if (m_pSmartTest->GetTestControlMainWnd() != NULL)
		{
			LONG nMainWnd = (LONG)m_pSmartTest->GetTestControlMainWnd()->m_hWnd;
			CString strMainWnd;
			strMainWnd.Format(_T("%ld"), nMainWnd);
			oDatas.AddNewData(XPARA_ID_MainWnd, XPARA_ID_MainWnd, "long", strMainWnd);
		}

		//CString strGbrptFile = m_pSmartTest->GetProjectName();
		//oDatas.AddNewData(XPARA_ID_GBRPTFILE, XPARA_ID_GBRPTFILE, "string", strGbrptFile);
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS, &oDatas, NULL);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_ExportReport(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	long nRet = m_pSmartTest->Ats_ExportReport(&oAtsCmd, NULL);

	if (nRet > 0 )
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_QueryItem(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	CSttContents *pItemParas = new CSttContents;

	pItemParas->m_strText = m_pSmartTest->Ats_QueryItem(&oAtsCmd, NULL);

	if (pItemParas->m_strText.GetLength() > 0 )
	{
		pItemParas->m_strID = STT_CMD_PARA_ItemParas;
		CSttParas *pParas = oSysState.GetSttParas();
		pParas->AddNewChild(pItemParas);
		oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);

		Return_Ats_Event(pClientSocket, oSysState);
	}
	else
	{
		delete pItemParas;
		oSysState.Set_ExecStatus(STT_CMD_ExecStatus_FAILURE);
		Return_Ats_Event(pClientSocket, oSysState);
	}

	return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_UpdateItem(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	long nRet = m_pSmartTest->Ats_UpdateItem(&oAtsCmd, NULL);

	if (nRet == 0 )
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_AdjustReport(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	long nRet = m_pSmartTest->Ats_AdjustReport(&oAtsCmd, NULL);

	if (nRet == 0 )
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return 0;
}

long CSttNativeTestEngine::Process_Cmd_Ats_ClearReportsRslts(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(&oAtsCmd);
	 ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

	if ( !ValidateSmartTest(pClientSocket, oSysState))
	{
		return 0;
	}

	long nRet = m_pSmartTest->Ats_ClearReportsRslts(&oAtsCmd, NULL);

	if (nRet == 0 )
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_SUCCESS);
	}
	else
	{
		Return_Ats_Success(pClientSocket, oAtsCmd, STT_CMD_ExecStatus_FAILURE);
	}

	return 0;
}

void CSttNativeTestEngine::Return_NoDevice(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
    oSysState.Set_ExecStatus_Failure();
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("ConfigDevice: has no device"));
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
}

void CSttNativeTestEngine::Return_Ats_Event(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
    if (pClientSocket != NULL)
    {
        //2020-11-29  lijunqing
        m_oClientUserMngr.SendSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
        //pClientSocket->SendSysState(&oSysState);
    }
    else
    {
        ReturnSysStateToChildren(NULL, &oSysState);
    }
}

long CSttNativeTestEngine::ValidateSmartTest(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
    if (m_pSmartTest != NULL)
    {
        return 1;
    }

    oSysState.Set_ExecStatus_Failure();
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("SmartTest has not created"));
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}

void CSttNativeTestEngine::Return_DeviceParameter_AfterLogin(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug -->CSttNativeTestEngine::Return_DeviceParameter_AfterLogin"));
	oSysState.Free();
	oSysState.m_strID = STT_CMD_TYPE_ADJUST_ReadDeviceParameter;
	oSysState.SetReporting();
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ADJUST;

	CSttParas *pParas = oSysState.GetSttParas();
	//原先采用从文件中转换获取，但缺少开入开出信息，故此处改为底层测试服务返回记录保存的报文   shaolei 20220414
	if (m_pSmartTest != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug -->CSttNativeTestEngine::Return_DeviceParameter_AfterLogin-->1"));
		m_pSmartTest->GetReadDeviceParameter(pParas);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug -->CSttNativeTestEngine::Return_DeviceParameter_AfterLogin-->2"));
	 	CString strPath = _P_GetConfigPath();
	 	strPath += _T("DeviceSystemParas.xml");
	 	CSttAdjDevice oAdjDevicve;
	 	CDataGroup *pModel = new CDataGroup;
	 	oAdjDevicve.OpenSttAdjFile(strPath);
	 	oAdjDevicve.GetDeviceVersioninfors(*pModel);
	 	pModel->m_strName = _T("Device");
	 	pModel->m_strID = pModel->m_strName;
	 	pParas->AddNewChild(pModel);
	}

	//添加自动测试版本号和软件名称
	CString strAppName, strVersion;
#ifdef _PSX_QT_LINUX_
	strAppName = _T("SttTestMainCore");
#else
	strAppName = _T("SmartTestCore");
#endif

    strVersion = _T("2024.08.15 - 09:30");
	CDataGroup *pDevice = (CDataGroup *)pParas->FindByID(_T("Device"));

	if (pDevice != NULL)
	{
		CDataGroup *pDeviceAttrs = (CDataGroup *)pDevice->FindByID(_T("DeviceAttrs"));

		if (pDeviceAttrs != NULL)
		{
			CDvmData *pAppName = (CDvmData *)pDeviceAttrs->FindByID(_T("SttTestMainCore_Name"));
			CDvmData *pAppVersion = (CDvmData *)pDeviceAttrs->FindByID(_T("SttTestMainCore_Ver"));

			if (pAppName == NULL)
			{
				pDeviceAttrs->AddNewData(_T("SttTestMainCore名称"), _T("SttTestMainCore_Name"), _T("AppName"), strAppName);
			}
			else
			{
				pAppName->m_strValue = strAppName;
			}

			if (pAppVersion == NULL)
			{
				pDeviceAttrs->AddNewData(_T("SttTestMainCore版本"), _T("SttTestMainCore_Ver"), _T("AppVersion"), strVersion);
			}
			else
			{
				pAppVersion->m_strValue = strVersion;
			}
		}
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("for debug -->CSttNativeTestEngine::Return_DeviceParameter_AfterLogin-->device not find"));
	}

	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value--;
	long nRet = pClientSocket->SendSysState(&oSysState);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value++;

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("pClientSocket->SendSysState --> len=%d"), nRet);
}

//2020-11-25  lijunqing
void CSttNativeTestEngine::OnTimer()
{
    if (!g_bLogPackageInfor)
    {
        return;
    }

    long nBegin1, nEnd1, nBegin2, nEnd2, k;
    CXPpPkgLogTool::GetPpPkgLogIndex(nBegin1, nEnd1, nBegin2, nEnd2);

    if (nBegin1 < 0)
    {
        return;
    }

    CSttSysState oSysState;
    oSysState.m_strRetType = SYS_STATE_RETTYPE_PACKAGE;
    oSysState.m_strID = SYS_STATE_RETTYPE_PACKAGE;
    CSttMsgs *pMsgs = oSysState.GetSttMsgs();
    CSttMsg *pMsg = NULL;

    for (k=nBegin1; k<=nEnd1; k++)
    {
        pMsg = new CSttMsg();
        pMsgs->AddNewChild(pMsg);
        CXPpPkgLogTool::PpPkgLogStr(k, pMsg->m_strMsg, pMsg->m_strID);
    }

    if (nEnd2 >= 0)
    {
        for (k=nBegin2; k<=nEnd2; k++)
        {
            pMsg = new CSttMsg();
            pMsgs->AddNewChild(pMsg);
            CXPpPkgLogTool::PpPkgLogStr(k, pMsg->m_strMsg, pMsg->m_strID);
        }
    }

    ReturnSysStateToChildren(NULL, &oSysState);
}
