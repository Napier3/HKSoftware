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
        //Զ�̲����ǣ���Ϊ��Ҫ���Ʒ�����ע�ᣬ�˴�����ʱ������TestControl
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

	//����˹������
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
//���û���ⲿ�֣�Server��Accept�߳��޷��˳�
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
    //20210123 xxy �������һ�У���ֹ����ر�ʱ��ִ���˸���֮��delete ServerEngine,�����������ûִ����
    //�ο�CSttServerSocketDataBase::CloseSttServer()
    if(pSocket != m_pSttCloudClientSocket)
    {//�����Զ��������Ӷ���
//		m_pServerSocket->CSttServerSocketDataBase::OnSttScktClose(pSocket);
        m_oClientUserMngr.DeleteUserByRefSocket(pSocket);
    }
    else
    {//�����ƶ�socket����
//         if (m_pSttCloudClientSocket != NULL)
//         {
//            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�ƶˣ�%s Disonnect"), pSocket->m_strIPRemote.GetString());

//             delete m_pSttCloudClientSocket;
//             m_pSttCloudClientSocket = NULL;
//         }

        //ɾ���û������е�����Զ���û�
        m_oClientUserMngr.DeleteUserByIDTerminal(STT_TERMINAL_TYPE_REMOTE);
        m_oRemoteRegister.Code_Register(_T(""));
    }

    //���û��AtsȨ�ޣ����ͷ�TestControl��ClientEngineȨ��
    CheckUpdateTestControlAuthority();

    CSttSysState oSysState;
    ReturnBroadcastUserMngr(oSysState);

    //�������˳���¼��
    CheckStopTestAfterReleaseUser();


    //20210123 xxy �������һ�У���ֹ����ر�ʱ��ִ���˸���֮��delete ServerEngine,�����������ûִ����
    //�ο�CSttServerSocketDataBase::CloseSttServer()
    if(pSocket != m_pSttCloudClientSocket)
    {//�����Զ��������Ӷ���
        m_pServerSocket->CSttServerSocketDataBase::OnSttScktClose(pSocket);
    }
    else
    {//�����ƶ�socket����
        if (m_pSttCloudClientSocket != NULL)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�ƶˣ�%s Disonnect"), pSocket->m_strIPRemote.GetString());

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

//�յ���������ȼ���Ƿ���Ȩ�ޣ���Ȩ���򷵻�ʧ��
BOOL CSttNativeTestEngine::CheckBeforeProcessCmdTest(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
{
    CSttSystemCmd oSysCmd;
    oSysCmd.m_strTestor = STT_SOFT_ID_TEST;
    oSysCmd.m_nIDTester = stt_pkg_get_idtester(pBuf);
    oSysCmd.AddNewParasData(KEY_AUTHORITY_MODULE_Test, 1);

    //�ж��Ƿ����TestȨ�ޣ����������TestȨ�ޣ�
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

    //�ж��Ƿ����AtsȨ�ޣ����������AtsȨ�ޣ�
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

    //���޸ĸ���IP�����ص���Ϣ��
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
    oTick.DoEvents(500);  //��ʱ500ms��ȷ���޸�������Ч

    CString strCloudServerIP;
    strCloudServerIP.Format(_T("47.111.12.170"));
    CDvmData *pIP = (CDvmData *)pParas->FindByID(_T("ip"));

    if (pIP != NULL)
    {
        strCloudServerIP = pIP->m_strValue;
    }

    //�����Ʒ����
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

//����Ats��Զ�̵�¼
long CSttNativeTestEngine::Process_Cmd_System_Login(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    CSttTestClientUser *pUser = User_Login(pClientSocket, oSysCmd);

    //����Ӧ�������
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
    pClientSocket->SendSysState(&oSysState);	//Ӧ�������¼��Ϣ

    if (pUser != NULL)
    {
        ReturnBroadcastUserMngr(oSysState);

//#ifdef _PSX_QT_LINUX_   ԭ��ֻ��linux�¿��ţ�����ʰ�7.0Ҳ��Ҫ��windows��Ҳ���� 2024-8-14
		//Ӧ��ReadDeviceParameter��Ϣ   shaolei 20220326
		Return_DeviceParameter_AfterLogin(pClientSocket, oSysState);

        //���������¼ʱ����Ҫֱ�����ӵ�19814���Ի�ȡRTDATA���ӹ���ģ���˳��������棬CloseTest���ᵼ����19814�������
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
    //�����û�����
    DWORD nIDTester = 0;
    oSysCmd.GetParasDataValueByID(STT_CMD_PARA_IDTESTER, nIDTester);
    m_pSttTestClientUserMngr->DeleteUserByIDTest(nIDTester);

    //���û��AtsȨ�ޣ����ͷ�TestControl��ClientEngineȨ��
    CheckUpdateTestControlAuthority();

    //����Ӧ�������
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AddNewParasData(STT_CMD_PARA_IDTESTER, nIDTester);
    pClientSocket->SendSysState(&oSysState);	//Ӧ�������¼��Ϣ

    ReturnBroadcastUserMngr(oSysState);

    //�ͻ��˱�֤������Logout֮ǰȨ�޶����ͷ�
    CheckStopTestAfterReleaseUser();

    return 1;
}

void CSttNativeTestEngine::CheckStopTestAfterReleaseUser()
{//�˳���¼�����������Ƿ�ֹͣ����
    CLogPrint::LogString(XLOGLEVEL_INFOR,_T("��Native:CheckStopTestAfterReleaseUser��"));

    if ((m_pNativeClientTestEngine == NULL)
        || (!m_pNativeClientTestEngine->m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test)))
    {//���NativeClientû��TestȨ��
        return;
    }

    CSttTestClientUser *pUser = m_pSttTestClientUserMngr->FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
    if (pUser != NULL)
    {
        return;
    }

    //�ͷ�NativeClient��TestȨ��
    m_pNativeClientTestEngine->m_oCurrUser.SetAuthority(KEY_AUTHORITY_MODULE_Test,0);

    //����Զ�̲���Ȩ�޵ĵ������Զ�
    m_pNativeClientTestEngine->Test_CloseDevice();
}

//ֻ�����е�������Ȩ�޵Ĳ��Զ�������ʱ
void CSttNativeTestEngine::CheckHeartbeatOverTime()
{
    if (g_nRecvHeartbeatTimeGap <= 0)
    {//�����������
        return;
    }

    if (m_pNativeClientTestEngine == NULL
        || (!m_pNativeClientTestEngine->m_oCurrUser.HasAuthority(KEY_AUTHORITY_MODULE_Test)))
    {//NativeClient��TestȨ��
        return;
    }

    //���ҵ�ǰTestȨ���û�
    CSttTestClientUser *pFind = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
    if (pFind == NULL || pFind->m_pRefSttSckt == NULL)
    {
        return;
    }

    if (pFind->id_soft() != STT_SOFT_ID_TEST)
    {//����Զ�̵�������
        return;
    }

    long nTimeGap = pFind->m_pRefSttSckt->m_nRecvHeartbeatCounter++;//zhouhj 20210821 �ο�SttTestServerBase�޸�

    if (nTimeGap/*pFind->m_pRefSttSckt->m_oRecvHeartbeatTick.GetTickCountLong(FALSE)*/ >= g_nRecvHeartbeatTimeGap)
    {//����������������StopTest,CloseDevice
        //ɾ���û�����
        m_oClientUserMngr.Delete(pFind);

        //�ͷ�NativeClient��TestȨ��
        m_pNativeClientTestEngine->m_oCurrUser.SetAuthority(KEY_AUTHORITY_MODULE_Test,0);

        CheckUpdateTestControlAuthority();

        //�㲥
        CSttSysState oSysState;
        ReturnBroadcastUserMngr(oSysState);

        //����Զ�̲���Ȩ�޵ĵ������Զˣ�ֹͣ����
        m_pNativeClientTestEngine->Test_CloseDevice();
    }
}

BOOL CSttNativeTestEngine::OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType, BOOL &bRet)
{
    //2020-11-29  lijunqing  �������������
    if (g_nSttLogServerSpyAllCmd)
    {
        if (nCmdType != STT_CMD_TYPE_DEBUG)
        {
            SendToAllUser(STT_SOFT_ID_DEBUG, pBuf, nLen);
        }
    }

    //�յ����ݺ󣬽���������ʱ����0
    DWORD nIDTester = stt_pkg_get_idtester(pBuf);
    m_oClientUserMngr.RestartRecvHeartbeatTickCount(nIDTester);

    //Native�ˣ�test���debug����϶���Զ�̲��Է������ģ����Խ���m_pClientTestEngineȥִ��
    //�������ģ����Կ��Ƶ��������ģ���m_pClientTestEngineά��
    if (nCmdType == STT_CMD_TYPE_DEBUG)
    {
        return m_pNativeClientTestEngine->SendBuffer(pBuf, nLen);
    }

    if (nCmdType == STT_CMD_TYPE_TEST)
    {//��������������ж��Ƿ����ClientEngineȨ��

		//pBuf��Я������ͷ�ģ�Ӧ������ƴ����ͷ
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
		
		//����Ȩ��-2023-11-23
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
		//delete pTestCmd;   //shaolei ע�ʹ˴�  2023-10-10����Ϊû��ʹ��RefCount����ʹ������֮��delete

		return nRet;
    }
    if (nCmdType == STT_CMD_TYPE_ATS)
    {//�Զ�����������ж��Ƿ����AtsȨ��
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

        //SysState:���ص�test���debug���������϶��Ǵ�m_pClientTestEngine���ⲿ���Ǳ��뷵�ظ�Զ�̶˵�
        if (oSysState.m_strRetSttCmd == STT_CMD_SYSSTATE_TEST  || oSysState.m_strRetSttCmd == STT_CMD_SYSSTATE_DEBUG)
        {
            if(oSysState.m_strID == STT_CMD_TYPE_DEBUG_GetSocketConnect)
            {//�����GetSocketConnectӦ����ϲ�Native��TestServer�û�����
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
    {//������������,����Ŀ��IDTest��ת��

    }

    return 0;
}

long CSttNativeTestEngine::Process_SysState_Register(CSttSysState &oSysState)
{//�յ��ƶ�ע��Ӧ��
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
{//�յ�ȡ���ƶ�ע��Ӧ��
    long nCmdExecState = oSysState.Get_ExecStatus();

    if (Stt_Is_ExecStatus_Success(nCmdExecState))
    {
        //ɾ��Զ���û�
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
// 	//xxy��������Ӧ��
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
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("�Ѿ�ע��"));
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
    {//ȡ��Ȩ��
        if (pUser->HasAuthority(KEY_AUTHORITY_MODULE_Ats))
        {//�����ǰ�û�����AtsȨ�ޣ���ȡ��ClientEngineȨ��
            m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
        }
    }
    else
    {//����Ȩ��
        CSttTestClientUser *pFind = m_pSttTestClientUserMngr->FindHasAuthority(KEY_AUTHORITY_MODULE_ClientEngine);
        if (pFind == NULL)
        {//���Զ�̵����������û��ClientEngineȨ�ޣ�������ClientEngineȨ��
            m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,1);
        }
    }

    //����Ȩ��
    CSttParas *pParas = oSysCmd.GetSttParas();
    pUser->SetAuthoritys(pParas);
    m_oClientUserMngr.ClearOtherAuthoritys(pParas, pUser);

    return TRUE;
}

BOOL CSttNativeTestEngine::AuthorityToTestUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser)
{//Զ�̵�������Ȩ��
    long nAuthority = 0;
    long nExecStatus = 0;
    oSysCmd.GetParasDataValueByID(KEY_AUTHORITY_MODULE_ClientEngine, nAuthority);

    if (nAuthority == 0)
    {//ȡ��TestȨ��
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
    {//����TestȨ��
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

    //����Ȩ��
    CSttParas *pParas = oSysCmd.GetSttParas();
    pUser->SetAuthoritys(pParas);
    m_oClientUserMngr.ClearOtherAuthoritys(pParas, pUser);

    //����TestControlȨ��
    CheckUpdateTestControlAuthority();

    return TRUE;
}

long CSttNativeTestEngine::AuthorityToUser(CSttSystemCmd &oSysCmd,BOOL bRequest,BOOL bBroadcastWhenSuccess)
{//�����Զ����ԡ�Զ�̵�����Զ���Զ����ԣ��������Ȩ����
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

    //0:������Ȩ��1������Ȩ��2������Ȩ��δ��Ȩ
    long nRet = IsCanAuthorityToUser(oSysCmd,bRequest);
    if (nRet == 1)
    {//����Ȩ
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
    {//�Զ�����
        if (!AuthorityToAtsUser(oSysCmd,pUser))
        {
            return 0;
        }
    }
    else
    {//Զ�̵�������Ȩ��
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
    {//ȡ��Ȩ�ޣ�ֱ��ȡ��
        return TRUE;
    }

    //��Ȩ����Ҫ�ж��Ƿ����û�ӵ����ͬ��Ȩ��
    CSttTestClientUser *pFind = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_Ats);

    if ((pFind == NULL) || (pFind == m_pRefAtsUser))
    {//��Ȩ�ɹ�
        return TRUE;
    }
    else
    {//Ȩ�ޱ�ռ��
        //������ڲ��ԣ�����Ȩʧ��

        //���򣬸����ȼ���ϵ����ȼ�
        if((!bRequest) && (m_pRefAtsUser->CompareUserPriority(pFind) > 0))
        {//������Ȩ
            return TRUE;
        }
    }

    return FALSE;
}

//����ģ��RefAtsUser�������Ȩ����
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
{//���û��ClientEngineȨ�ޣ����ͷ�NativeClient��TestȨ��
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
1�����û��AtsȨ�ޣ����ͷ�TestControl��ClientEngineȨ�ޣ�
2�������AtsȨ�ޣ���ClientEngineȨ��δ��ռ�ã�������TestControl��ClientEngineȨ�ޣ�
*/
long CSttNativeTestEngine::CheckUpdateTestControlAuthority()
{
    CSttTestClientUser *pFind = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_Ats);
    if (m_oTestControlUser.HasAuthority(KEY_AUTHORITY_MODULE_ClientEngine))
    {//TestControl��ClientEngineȨ��
        if (pFind == NULL)
        {
            m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
            return 1;
        }
    }
    else
    {//TestControlû��ClientEngineȨ��
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
    {//����Ats�������µ�¼
        pPrevSocket = pUser->m_pRefSttSckt;
        pUser->m_pRefSttSckt = pClientSocket;
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Test,0);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_Ats,0);
        pUser->SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
    }

    //�ظ���¼���ı��û���Ȩ��
    pUser->AnalysisLoginUser(oSysCmd);
    pClientSocket->m_nIDTester = nIDTester;
    pUser->m_pRefSttSckt = pClientSocket;
    pUser->m_pRefSttSckt->SetUser(pUser);

    if (strIDTerminal == STT_TERMINAL_TYPE_REMOTE)
    {//Զ�����µ�¼
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
            strInfo.Format(_T("User_Login��%u��repeat"),nIDTester);
            LogDebugInfor(strInfo);
        }
    }

    return pUser;
}

long CSttNativeTestEngine::Process_Cmd_System_Request(CSttSocketDataBase *pClientSocket, CSttSystemCmd &oSysCmd)
{
    //0:������Ȩ��1������Ȩ��2������Ȩ��δ��Ȩ
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
    //0:������Ȩ��1������Ȩ��2������Ȩ��δ��Ȩ
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
    //xxy��������Ӧ��
    if (pCmd->GetRefSocketData() == NULL)
    {
        CLogPrint::LogString(XLOGLEVEL_INFOR,_T("m_oSttAtsCmd.m_pRefSocketDataBase == NULL"));
        return 0;
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(pCmd);

    if (pRetData != NULL)
    {//���ؽ������
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
{//���µ�ǰ�Զ���������
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
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>�����ݼ���·����
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
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>�����ݼ���·����
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
        <group id="comm-config" >  ��ͨ�ŵ�ַ���á�
            �μ�CreateDeviceָ��
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
		//ע�ʹ˴�������ȫ·��  shaolei 20220707
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

    //�˴���Ҫ��UIParas�Ƿ�Ҳ��Ϊ�գ���Ϊ��λ����Ҫ�жϽ�������Ƿ�ı䣬����ı䣬����Ҫ�·��������
    if(pUIParas != NULL && pTestMacroUI != NULL)
    {
        //��ǿ�н�oAtsCmd��ID ��ΪGenerateTemplate��������ģ������
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
        <data id="ppxml-file" value="*.ppxml" /> ����Լģ���ļ���
        <data id="dvm-file" value="*.xml" />  ������ļ���
        <data id="cmm-cfg-file" value="*.xml" />  ��ͨ�ŵ�ַ�����ļ���
        <group id="omm-config" >  ��ͨ�ŵ�ַ���á�
            <data id="serial" value=""/>�����ڡ�
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
        <data id="ConnectState" value=""/>�����ӳɹ�����״̬��
        <data id="FileNotExist" value="�ļ���"/> ������ļ������ڡ�
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

    //lijunqing 2020-09-09 ֻ���ǵ�װ��
    //pPxiDevice = g_thePxiEngine->FindDevice(strDeviceID);
    pPxiDevice = g_thePxiEngine->GetDeviceByIndex(0);

    if (pPxiDevice != NULL)
    {
        if (!pPxiDevice->IsConnectSuccessful())
        {
            //�Ѿ����ڣ��򷵻ز�����
            return 0;
        }
    }
    else
    {
        pPxiDevice = g_thePxiEngine->CreateDevice(strPpTemplateFile, strDeviceFile, strDeviceID, NULL);
    }
#endif

    long nRet = Ats_ConfigDevice(oAtsCmd);

    //����ϵͳ״̬
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

    //����ϵͳ״̬
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
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>�����ݼ���·����
    </paras>
</ats -cmd>
<sys-state name="" id="CreateDevice" mater-host="">
    <paras name="" id="">
        <dataset id="LLN0$dsSetting1" name="">
            <data name="��ٶϵ�����ֵ" id="PDIF1$SG$StrValSG"
                data-type="STRUCT" unit="" unit-path="PDIF1$CF$StrValSG$units"
                unit-value="0" value="4.000000" default-value="4.000000"
                max="20.000000" min="0.050000" step="0.001000">
                <value data-type="FLOAT" id="PDIF1$SG$StrValSG$setMag$f"
                    name="" value="4.000000"/>
            </data>
            <data name="���������������ֵ" id="PDIF2$SG$StrValSG"
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
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>�����ݼ���·����
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
        <data id="id-procedure" value="WriteSetting">��ִ�е�ͨ�Ź��̡�
            <value data-type="FLOAT" id="" name="" value="" />��ͨ�Ź��̵Ĳ�����
        </data>
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>�����ݼ���·����
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

    //��ʼ������Ĳ���
    if (pData_Procedure->GetCount() > 0)
    {
#ifdef _NATIVE_ENGINE_USE_PXIENGINE_
        CPxiDataInterface *pXiDataInterface = pPxiDevice->GetDataInterface();
        pXiDataInterface->InitDataInterface(pData_Procedure);
#endif
    }

    //���ݼ���������
    Ats_SetDataset(oAtsCmd);

    //ִ��ͨ�Ź���
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
        //ͨ��ʱ��ϳ�������ִ�п�ʼ
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

    //��ʱ�����Ƕ�װ�õ����
    pPxiDevice->UnLoad();
#endif

    oSysState.Set_ExecStatus_Success();
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}

/*
<ats-cmd name="" id="ConfigEngine" testor="" >
    <paras name="" id="">
        <data id=" log-data-bind " value=" "/>����ʾ���ݰ󶨴���
        <data id=" log-pkg-data-infor " value=" "/>����ʾ����������Ϣ��
        <data id=" log-pkg " value=" "/>����ʾ���͡����ܱ��ġ�
        <data id=" log-debug-infor " value=" "/>����ʾ������Ϣ��
        <data id=" no-change-when-same " value=" "/>��������ͬ��ִ���޸ġ�
    </paras>
</ats -cmd>
*/
long CSttNativeTestEngine::Process_Cmd_Ats_ConfigEngine(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_ACK);

    //���� �������ùؼ��� 2020-10-18  lijunqing
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
    //����ִ�гɹ�������ŵ�Ats_FinishInputDataָ��ǰ�棬�����ȷ����˽������
     ReturnExecReply(&oAtsCmd, STT_CMD_ExecStatus_SUCCESS);

    //ִ��
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

    //shaolei ע�ʹ˴�   2022-1-12
    //����ģ��ʱ����û�д������ԣ����m_pSmartTestָ�뻹Ϊ�գ��˴������ж�ValidateSmartTest����ע�ʹ˴�
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
    strRetMode = STT_CMD_PARA_TtRetMode_GBXML;   //Ĭ�Ϸ���ȫģ��
    pParas->GetDataValue(STT_CMD_PARA_TtRetMode, strRetMode);

    if (nRet == 0)
    {
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
        CGuideBook *pGuideBook = m_pSmartTest->GetGuideBook_AtsGen();
#endif
        CSttParas *pParas = oSysState.GetSttParas();
        oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);

        //�˴���Ҫ����ģ�巵��ģʽ��ȷ����Ӵ����CSttGuideBook����CGuideBook��
        if(strRetMode == STT_CMD_PARA_TtRetMode_GBXML)
        {

        }
        else
        {
        }

        //��ʱʹ��SCttGuideBook
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
		long nAddDevReset = 0;   //�Ƿ����װ�ø���̬

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
			CDataGroup *pCommCmd = pRetParas->AddNewGroup(_T("ͨѶ������������"), STT_CMD_PARA_CommCmd, _T(""));
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

			//���ر��ĺ������ͷ�
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
			//�����createָ�Ӧ������ȫ�����ݺ�ϵͳ����
			pGlobalDatas = new CDataGroup;
			pGlobalDatas->m_strName = _T("ȫ������");
			pGlobalDatas->m_strID = STT_CMD_PARA_GlobalDatas;
			CExBaseList *pDatas = m_pSmartTest->GetGlobalDatas();
			pGlobalDatas->AppendCloneEx(*pDatas, TRUE);

			pSysPara = new CDataGroup;
			pSysPara->m_strName = _T("ϵͳ����");
			pSysPara->m_strID = STT_CMD_PARA_SysPara;
			CDataSet *p = (CDataSet *)m_pSmartTest->GetSysPara();//(CDataSet*����)
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
					//CDevice�µ���Ŀ������Ŀ·��Ϊ��
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
			pItems = (CItems *)pMacroTest->GetParent()->GetParent();  //paras�ڵ�Ŀǰֻ��Я��items
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

    //����SystemConfig����Ҫ����HasDigital����̬��������ɾ��Iec61850Config��Ŀ
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

//ϵͳ�������ã������Ƿ���������������ľ����£������ظ���λ����ˢ����Ŀ�б�
long CSttNativeTestEngine::Procss_Cmd_Ats_SetItemPara_SystemConfig(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oAtsCmd);

	//���ⲿ�Ѿ����ù�ValidateSmartTest���˴�����Ҫ�����ˡ�
//     if ( !ValidateSmartTest(pClientSocket, oSysState))
//     {
//         return 0;
//     }

    m_pSmartTest->Ats_SetItemPara_SystemConfig(&oAtsCmd, NULL);

    //����GenerateTemplate��Success�¼����Ա���λ��ȥˢ����Ŀ�б�
    oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
    oSysState.UpdateSysStateHead(&oAtsCmd);
	CSttParas *pReturnParas = oSysState.GetSttParas();
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
    CGuideBook *pGuideBook = m_pSmartTest->GetGuideBook_AtsGen();
//     CString strPath;
//     strPath = _P_GetLibraryPath();
//     strPath += _T("0000-1.gbxml");
//     pGuideBook->SaveXMLFile(strPath);
    //�˴���Ҫ����ģ�巵��ģʽ��ȷ����Ӵ����CSttGuideBook����CGuideBook��
    //��ʱʹ��SCttGuideBook
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

	//�˴���Ҫ��UIParas�Ƿ�Ҳ��Ϊ�գ���Ϊ��λ����Ҫ�жϽ�������Ƿ�ı䣬����ı䣬����Ҫ�·��������
	if(pUIParas != NULL && pTestMacroUI != NULL)
	{
		//��ǿ�н�oAtsCmd��ID ��ΪGenerateTemplate��������ģ������
		oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
		m_pSmartTest->SetMacroTestSaveParas(TRUE);
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK//zhouhj 2024.8.24 ��������������
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

	//�˴���Ҫ��UIParas�Ƿ�Ҳ��Ϊ�գ���Ϊ��λ����Ҫ�жϽ�������Ƿ�ı䣬����ı䣬����Ҫ�·��������
	if(pUIParas != NULL && pTestMacroUI != NULL)
	{
		//��ǿ�н�oAtsCmd��ID ��ΪGenerateTemplate��������ģ������
		oAtsCmd.m_strID = STT_CMD_TYPE_ATS_GenerateTemplate;
		m_pSmartTest->SetMacroTestSaveParas(TRUE);
#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK//zhouhj 2024.8.24 ��������������
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
		<data id="gbrpt-file" data-type="string" value="d:\Program Files\EPOTO\e-Report\Workspace\PT220_220kV�����µ�ѹ�ȼ����䱣��װ��ȫ��ʽ������������������ҵָ����\G����վ.gbrpt" />
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
		//ע�ʹ˴�������ȫ·��  shaolei 20220707
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
		//�ɹ�������������
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
	//ԭ�Ȳ��ô��ļ���ת����ȡ����ȱ�ٿ��뿪����Ϣ���ʴ˴���Ϊ�ײ���Է��񷵻ؼ�¼����ı���   shaolei 20220414
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

	//����Զ����԰汾�ź��������
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
				pDeviceAttrs->AddNewData(_T("SttTestMainCore����"), _T("SttTestMainCore_Name"), _T("AppName"), strAppName);
			}
			else
			{
				pAppName->m_strValue = strAppName;
			}

			if (pAppVersion == NULL)
			{
				pDeviceAttrs->AddNewData(_T("SttTestMainCore�汾"), _T("SttTestMainCore_Ver"), _T("AppVersion"), strVersion);
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
