#include "stdafx.h"
#include "SttNativeTestEngine_Mqtt.h"
#include "../SttCmd/SttRemoteCmd.h"

#include "../../../System/Module/XAtsSysSvrGlobalDef.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"
#include "../../../AutoTest/Module/GuideBook/GuideBookDefine.h"

#include "SttQueryAtsFileTool.h"

//2022-1-3  lijunqing
#include "../SttCmd/GuideBook/SttCmdGuideBookTransTool.h"
#include "../AdjustTool/SttAdjDevice.h"

#include "../SmartTestInterface/AtsOutInterfaceMqttClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define STRING2(x) #x  
#define STRING(x) STRING2(x)  


CSttNativeTestEngine_Mqtt* CSttNativeTestEngine_Mqtt::g_pNativeTestEngine = NULL;
long CSttNativeTestEngine_Mqtt::g_nNativeTestEngineRef = 0;

CSttNativeTestEngine_Mqtt* CSttNativeTestEngine_Mqtt::Create(const CString &strBentchSN, CSttSmartTest *pSttSmartTest)
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

		g_pNativeTestEngine = new CSttNativeTestEngine_Mqtt();
		g_pNativeTestEngine->m_strBentchSN = strBentchSN;
		g_pNativeTestEngine->InitSttServerEngine(NULL, 0);

		CAtsOutInterfaceMqttClient::Create(strBentchSN);
		//创建时，还没有连接MQTT服务端，无法订阅，注释此处  shaolei   2023-8-24
		//g_theAtsOutMqttClient->MqttAdd(g_pNativeTestEngine);
	}

//	if (pSttSmartTest == NULL)
//	{
//#ifndef _SttTestServer_For_Debug_
//		//远程测试仪，因为需要向云服务器注册，此处先暂时不创建TestControl
//		CSttTestAppCfg oAppCfg;
//		oAppCfg. Open(_T("SttTestAppCfg-remote.xml"));

//		if(!oAppCfg.IsRemote())
//		{
//			pSttSmartTest = CSttSmartTest::Create();
//			pSttSmartTest->InitTestControl(true);
//		}
//#endif
//	}

	if (pSttSmartTest != NULL)
		{
		g_pNativeTestEngine->SetSttSmartTest(pSttSmartTest);
	}

	return g_pNativeTestEngine;
}

void CSttNativeTestEngine_Mqtt::Release()
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
	
		g_theAtsOutMqttClient->MqttRemove(g_pNativeTestEngine);
		CAtsOutInterfaceMqttClient::Release();

        //2020-4-6  lijq
        g_pNativeTestEngine->ExitSttServerEngine();
        delete g_pNativeTestEngine;
        g_pNativeTestEngine = NULL;


    }

	CSttNativeTestEngineInterfaces::Release();
}

CSttNativeTestEngine_Mqtt* CSttNativeTestEngine_Mqtt::GetNativeTestEngine()
{
    return g_pNativeTestEngine;
}



//MQTT事件处理接口，共CMqttMsgInterface对象调用
//class CMqttMsgProcessInterface
//根据收到的MQTT主题进行匹配，如果匹配成功，则返回TRUE，否则返回FALSE
BOOL CSttNativeTestEngine_Mqtt::MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser)
{
	if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1] , MQTT_CMD_ID_AtsCmd ) == 0)
	{
		if (m_strBentchSN == oSttMqttTopicParser.m_pszSubTopic[0])
		{//测试台SN/AtsCmd/QueryItems
			return TRUE;
		}
	}
	else if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2] , MQTT_CMD_ID_AtsCmd ) == 0)
		{
			if (m_strBentchSN == oSttMqttTopicParser.m_pszSubTopic[1])
			{//  ats/测试台SN/AtsCmd/CreateTest
				return TRUE;
			}
		}
	else  if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3] , MQTT_CMD_ID_AtsCmd ) == 0)
	{
		CString strBenchSN = oSttMqttTopicParser.m_pszSubTopic[1];
		strBenchSN += _T("/");
		strBenchSN += oSttMqttTopicParser.m_pszSubTopic[2];
		if (m_strBentchSN == strBenchSN)
		{//  ats/测试台SN/子设备/AtsCmd/CreateTest   例如充电桩的A枪、B枪
			return TRUE;
		}
	}
	else
	{
		
	}

	return FALSE;
}

//MQTT消息处理
//hd_res_req/ATS/TestState/StartTest/REPLY
//hd_res_req/ATS/TestState/EVENT/TestFinished
void CSttNativeTestEngine_Mqtt::MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser)
{
	char *pszAtsCmd = GetAtsCmdID(oSttMqttTopicParser);

	if (pszAtsCmd == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Topic [%s] Error.."), oSttMqttTopicParser.GetTopic());
		return;
	}

	//2023-8-30 lijunqing 动态访问模式， m_nObjectRefCount初始值为0，所以手动调用AddRef
	CSttAtsCmd *pAtsCmd = new CSttAtsCmd();
	pAtsCmd->AddRef();  

	 //暂时只考虑AtsCmd
	dvm_IncGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	pAtsCmd->SetXml_UTF8(oSttMqttTopicParser.m_pMqttPkgBuffer, oSttMqttTopicParser.m_nMqttPkgBufferLen, CSttCmdDefineXmlRWKeys::g_pXmlKeys, m_nXmlRWType);
	dvm_DecGroupUseDvmData(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	Process_Cmd_Ats(NULL, *pAtsCmd);
	pAtsCmd->Release();
}

//MQTT主题订阅接口函数：MQTT Client连接成功后，遍历各CMqttMsgProcessInterface
//订阅相关的主题
/*
南瑞传感器自动测试管理平台:		ats/测试台SN/AtsCmd/CreateTest
充电桩：	测试服务端SN/AtsCmd/CreateTest
				测试台SN/AtsCmd/QueryItems
*/
BOOL CSttNativeTestEngine_Mqtt::MqttSubscribeTopic()
{
	CString strTopic ;

	//ats/测试台SN/AtsCmd/CreateTest    
	strTopic.Format(_T("+/%s/AtsCmd/#"), m_strBentchSN.GetString());
	g_theAtsOutMqttClient->SubscribeTopic(strTopic, 0);

	//ats/测试台SN/AtsCmd/CreateTest    
	strTopic.Format(_T("%s/AtsCmd/#"), m_strBentchSN.GetString());
	g_theAtsOutMqttClient->SubscribeTopic(strTopic, 0);

	return TRUE;
}

//MQTT取消主题订阅接口函数：MQTT Client断开连接后，遍历各CMqttMsgProcessInterface
//T取消订阅相关的主题
BOOL CSttNativeTestEngine_Mqtt::MqttUnSubscribeTopic()
{
	CString strTopic ;

	//ats/测试台SN/AtsCmd/CreateTest    
	strTopic.Format(_T("+/%s/AtsCmd/#"), m_strBentchSN.GetString());
	g_theAtsOutMqttClient->UnSubscribeTopic(strTopic);

	//ats/测试台SN/AtsCmd/CreateTest    
	strTopic.Format(_T("%s/AtsCmd/#"), m_strBentchSN.GetString());
	g_theAtsOutMqttClient->UnSubscribeTopic(strTopic);

	return TRUE;
}

char* CSttNativeTestEngine_Mqtt::GetAtsCmdID(CSttMqttTopicParser &oSttMqttTopicParser)
{
	InitMqttTopicCmbn(oSttMqttTopicParser);

	if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1] , MQTT_CMD_ID_AtsCmd ) == 0)
	{//测试台SN/AtsCmd/QueryItems
		return oSttMqttTopicParser.m_pszSubTopic[2];
	}
	else if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2] , MQTT_CMD_ID_AtsCmd ) == 0)
	{
		return oSttMqttTopicParser.m_pszSubTopic[3];
	}
	else if (strcmp(oSttMqttTopicParser.m_pszSubTopic[3] , MQTT_CMD_ID_AtsCmd ) == 0)
		{
		return oSttMqttTopicParser.m_pszSubTopic[4];
		}
	else
	{
		
	}

	return NULL;
}

void CSttNativeTestEngine_Mqtt::InitMqttTopicCmbn(CSttMqttTopicParser &oSttMqttTopicParser)
{
	if (m_pMqttTopicCmbn != NULL)
	{
		return;
	}

	m_pMqttTopicCmbn = new CSttMqttTopicCmbn();
	m_pMqttTopicCmbn->ResetSubTopics();
	m_nXmlRWType = oSttMqttTopicParser.GetXmlRWType();

	if (strcmp(oSttMqttTopicParser.m_pszSubTopic[1] , MQTT_CMD_ID_AtsCmd ) == 0)
	{//测试台SN/AtsCmd/QueryItems
		m_pMqttTopicCmbn->AddSubTopic(m_strBentchSN);
		m_pMqttTopicCmbn->AddSubTopic(MQTT_CMD_ID_AtsState);
	}
	else
	{
		if (strcmp(oSttMqttTopicParser.m_pszSubTopic[2] , MQTT_CMD_ID_AtsCmd ) == 0)
		{
			m_pMqttTopicCmbn->AddSubTopic(oSttMqttTopicParser.m_pszSubTopic[0]);
			m_pMqttTopicCmbn->AddSubTopic(m_strBentchSN);
			m_pMqttTopicCmbn->AddSubTopic(MQTT_CMD_ID_AtsState);
		}
	}
}

void CSttNativeTestEngine_Mqtt::InitMqttTopicCmbn(const CString &strAtsServiceSN, const CString &strBentchSN)
{
	if (m_pMqttTopicCmbn != NULL)
	{
		return;
	}

	m_strBentchSN = strBentchSN;
	m_pMqttTopicCmbn = new CSttMqttTopicCmbn();
	m_pMqttTopicCmbn->ResetSubTopics();
	m_pMqttTopicCmbn->AddSubTopic(strAtsServiceSN);
	m_pMqttTopicCmbn->AddSubTopic(m_strBentchSN);
	m_pMqttTopicCmbn->AddSubTopic(MQTT_CMD_ID_AtsState);
}

void CSttNativeTestEngine_Mqtt::OnCommCmdMessage(WPARAM wParam, LPARAM lParam)
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

void CSttNativeTestEngine_Mqtt::OnSysMessage(WPARAM wParam, LPARAM lParam)
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
void CSttNativeTestEngine_Mqtt::OnEngineDataDeleted(const CString &strDeviceID)
{
#ifdef _PSX_QT_LINUX_
    stt_Return_Ats_EngineEvent(strDeviceID, SYS_STATE_EVENT_OnEngineEvent, EngineEvent_DeviceClosed);
#endif
}


//2022-2-12  lijunqing
void CSttNativeTestEngine_Mqtt::DispatchMsg(unsigned char *pBuf, long nLen)
{
	
}

//////////////////////////////////////////////////////////////////////////
//CSttNativeTestEngine_MqttInterface
long CSttNativeTestEngine_Mqtt::X_ReturnSysStateToChildren(void *pCommInterface, CSttSysState *pSysState)
{
	return ReturnSysState(pCommInterface, pSysState,  1);
}

long CSttNativeTestEngine_Mqtt::X_Ats_InputData(void *pCommInterface, CDataGroup *pDatas,CExBaseList *pMsgs)
{
	return Ats_InputData(NULL, pDatas, pMsgs);
}

CSttNativeTestEngine_Mqtt::CSttNativeTestEngine_Mqtt()
{
    //m_pSmartTest = new CSttSmartTest();
#ifdef _PSX_QT_LINUX_
    g_thePxiDeviceCommCmdMessage = this;
#endif

	//服务端管理对象
    g_theNativeTestEngine->AddTail(this);

    m_pSttAtsInterface = NULL;
	m_pSmartTest = NULL;

    InitClientUserMngr();
	m_pMqttTopicCmbn = NULL;
    m_pNativeClientTestEngine = new CSttNativeClientTestEngine();
	//m_nXmlRWType = _PUGI_XML_TYPE_;
	m_nXmlRWType = _JSON_TYPE_;
}

CSttNativeTestEngine_Mqtt::~CSttNativeTestEngine_Mqtt()
{
    if (m_pNativeClientTestEngine != NULL)
    {
        m_pNativeClientTestEngine->PrepareFreeClientEngine();
        delete m_pNativeClientTestEngine;
        m_pNativeClientTestEngine = NULL;
    }

//	CSttSmartTest::Release();

#ifndef _SttTestServer_For_Debug_
	CXSmartTestEntry::Release();
#endif

	delete m_pMqttTopicCmbn;
}

void CSttNativeTestEngine_Mqtt::InitClientUserMngr()
{
//     m_oTestControlUser.ID_Terminal(STT_TERMINAL_TYPE_NATIVE_TESTCONTROL);
//     m_oTestControlUser.Name_User(STT_TERMINAL_TYPE_NATIVE_TESTCONTROL);
//     m_oTestControlUser.SetAuthority(KEY_AUTHORITY_MODULE_ClientEngine,0);
}

void CSttNativeTestEngine_Mqtt::AttachRefAtsUser(CSttTestClientUser *pRefAtsUser)
{
}

void CSttNativeTestEngine_Mqtt::InitSttServerEngine(const char *pszIP, int nPort,int nReplayPort)
{
    CGbXMLKeys::CreatetGbXMLkeys();
    CCfgDataMngrXmlRWKeys::Create();
    CSttCmdOverTimeTool::Create();

}

//2020-4-6  lijq
//如果没有这部分，Server的Accept线程无法退出
void CSttNativeTestEngine_Mqtt::ExitSttServerEngine()
{
     CGbXMLKeys::Release();
    CCfgDataMngrXmlRWKeys::Release();
    CSttCmdOverTimeTool::Release();
}

void CSttNativeTestEngine_Mqtt::OnSocketClose(void *pSocket)
{
 
}

BOOL CSttNativeTestEngine_Mqtt::SendBufferToChildren(void *pExceptSocket,BYTE *pBuf,long nLen)
{
 
    return 1;
}

long CSttNativeTestEngine_Mqtt::SendSysState(CSttSysState *pSysState)
{
#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  使用MQTT实现"  ) 

    return 0;
}

//收到测试命令，先检查是否有权限，无权限则返回失败
BOOL CSttNativeTestEngine_Mqtt::CheckBeforeProcessCmdTest(void *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
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

         RetFailureSysState(&oTestCmd);
    }

    return bRet;
}

BOOL CSttNativeTestEngine_Mqtt::CheckBeforeProcessCmdAts(void *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
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
/*
        SetXmlBufferLen(nLen * 2);
        oAtsCmd.ParsePkgXml(pBuf,nLen, pBuf);

        pClientSocket->RetFailureSysState(&oAtsCmd);
*/
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
long CSttNativeTestEngine_Mqtt::ProcessCmd_CloudTest(void *pClientSocket, CSttSystemCmd &oSysCmd)
{
#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  使用MQTT实现"  ) 

    return 0;
}

//本地Ats和远程登录
long CSttNativeTestEngine_Mqtt::Process_Cmd_System_Login(void *pClientSocket, CSttSystemCmd &oSysCmd)
{
#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  使用MQTT实现"  ) 

    return 1;
}

long CSttNativeTestEngine_Mqtt::Process_Cmd_System_Logout(void *pClientSocket, CSttSystemCmd &oSysCmd)
{
#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  使用MQTT实现"  ) 

    return 1;
}

void CSttNativeTestEngine_Mqtt::CheckStopTestAfterReleaseUser()
{//退出登录或断链，检查是否停止测试

}

//只检测具有单机测试权限的测试端心跳超时
void CSttNativeTestEngine_Mqtt::CheckHeartbeatOverTime()
{
    long nTimeGap = m_nRecvHeartbeatCounter++;//zhouhj 20210821 参考SttTestServerBase修改

    if (nTimeGap/*pFind->m_pRefSttSckt->m_oRecvHeartbeatTick.GetTickCountLong(FALSE)*/ >= g_nRecvHeartbeatTimeGap)
    {//主动断链，断链后StopTest,CloseDevice
        //释放NativeClient的Test权限
        m_pNativeClientTestEngine->m_oCurrUser.SetAuthority(KEY_AUTHORITY_MODULE_Test,0);

        CheckUpdateTestControlAuthority();

        //具有远程测试权限的单机测试端，停止测试
        m_pNativeClientTestEngine->Test_CloseDevice();
    }
}

long CSttNativeTestEngine_Mqtt::Process_SysState(void *pClientSocket, CSttSysState &oSysState)
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

long CSttNativeTestEngine_Mqtt::Process_SysState_Register(CSttSysState &oSysState)
{//收到云端注册应答
    long nCmdExecState = oSysState.Get_ExecStatus();

#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  使用MQTT实现"  ) 

    return nCmdExecState;
}

long CSttNativeTestEngine_Mqtt::Process_SysState_UnRegister(CSttSysState &oSysState)
{//收到取消云端注册应答
    long nCmdExecState = oSysState.Get_ExecStatus();

#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  使用MQTT实现"  ) 

    return nCmdExecState;
}

long CSttNativeTestEngine_Mqtt::Process_SysState_InputData(void *pClientSocket,CSttSysState &oSysState)
{
    long nCmdExecState = oSysState.Get_ExecStatus();
    //CSttCmdOverTimeTool::OnSocketReceive_FixedCmd(pClientSocket,oSysState,nCmdExecState);

    return nCmdExecState;
}

long CSttNativeTestEngine_Mqtt::ConnectCloudServer(const CString &strIPServer,long nPort)
{
   return 0;
}

void CSttNativeTestEngine_Mqtt::DisConnectCloudServer()
{

}

BOOL  CSttNativeTestEngine_Mqtt::IsConnectColudServerSuccess()
{
     return TRUE;
}

long CSttNativeTestEngine_Mqtt::SendCmd(CSttCmdBase *pCmd,long nTimeOut,BOOL bCompress,BOOL bReset)
{
	return 0; 
}

long CSttNativeTestEngine_Mqtt::SendCmdSync(CSttCmdBase *pCmd,long nTimeOut,CSttCmdData *pRetData,BOOL bDoEvents)
{
	return 0;
}

// long CSttNativeTestEngine_Mqtt::ReturnSysState(long nCmdExecStatus)
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

long CSttNativeTestEngine_Mqtt::Register(CSttCmdData *pRetData)
{
#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  使用MQTT实现"  ) 

	return 0;
}

long CSttNativeTestEngine_Mqtt::UnRegister(CSttCmdData *pRetData)
{
#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  使用MQTT实现"  ) 

	return 0;
}

long CSttNativeTestEngine_Mqtt::Ats_InputData(void *pClientSocket,CDataGroup *pDatas,CExBaseList *pMsgs)
{
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
    X_SendCmd(pClientSocket, &oAtsCmd, g_nSttLogServerSpyAllCmd);
	oAtsCmd.RemoveMsgs();

    return 0;// SendCmdAsync(&oAtsCmd,3000,this);
}

BOOL CSttNativeTestEngine_Mqtt::AuthorityToAtsUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser)
{
 /*   long nAuthority = 0;
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
*/

#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  功能暂时屏蔽 "  ) 

    return TRUE;
}

BOOL CSttNativeTestEngine_Mqtt::AuthorityToTestUser(CSttSystemCmd &oSysCmd,CSttTestClientUser *pUser)
{//远程单机测试权限
/*
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
*/

#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  功能暂时屏蔽 "  ) 

    return TRUE;
}

long CSttNativeTestEngine_Mqtt::AuthorityToUser(CSttSystemCmd &oSysCmd,BOOL bRequest,BOOL bBroadcastWhenSuccess)
{//本地自动测试、远程单机、远程自动测试：请求或授权处理
 /*   CSttTestClientUser *pUser = m_pSttTestClientUserMngr->FindByIDTest(oSysCmd.m_nIDTester);
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
	*/

#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  功能暂时屏蔽 "  ) 

	return 0;
}

BOOL CSttNativeTestEngine_Mqtt::IsCanAuthorityToRefAtsUser(long nAtsAuthority,BOOL bRequest)
{
/*
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

*/

#pragma message( __FILE__ "[" __FUNCTION__ "]("  STRING(__LINE__) ") :  功能暂时屏蔽 "  ) 

    return FALSE;
}

//界面模块RefAtsUser请求或授权处理
long CSttNativeTestEngine_Mqtt::AuthorityToRefAtsUser(long nAtsAuthority,BOOL bRequest)
{
/*
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
*/

    return 1;
}

long CSttNativeTestEngine_Mqtt::CheckCancelNativeClientAuthority()
{//如果没有ClientEngine权限，则释放NativeClient的Test权限
/*
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
*/
	return 0;
}

/*
1、如果没有Ats权限，则释放TestControl的ClientEngine权限；
2、如果有Ats权限，且ClientEngine权限未被占用，则设置TestControl的ClientEngine权限；
*/
long CSttNativeTestEngine_Mqtt::CheckUpdateTestControlAuthority()
{
 /*   CSttTestClientUser *pFind = m_oClientUserMngr.FindHasAuthority(KEY_AUTHORITY_MODULE_Ats);
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
    }*/

    return 0;
}

CSttTestClientUser* CSttNativeTestEngine_Mqtt::User_Login(void *pClientSocket, CSttSystemCmd &oSysCmd)
{
	return NULL;
}

long CSttNativeTestEngine_Mqtt::Process_Cmd_System_Request(void *pClientSocket, CSttSystemCmd &oSysCmd)
{
    //0:不可授权，1：已授权，2、可授权但未授权
    long nRet = AuthorityToUser(oSysCmd,TRUE,FALSE);
    if (nRet == 0)
    {
        return  0;// RetFailureSysState(&oSysCmd);
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AppendParas(oSysCmd);
     SendSysState(&oSysState);

    if (nRet == 2)
    {
        //ReturnBroadcastUserMngr(oSysState);
    }

    return 1;
}

long CSttNativeTestEngine_Mqtt::Process_Cmd_System_Authority(void *pClientSocket, CSttSystemCmd &oSysCmd)
{
    //0:不可授权，1：已授权，2、可授权但未授权
    long nRet = AuthorityToUser(oSysCmd,FALSE,FALSE);
    if (nRet == 0)
    {
        return  0;// RetFailureSysState(&oSysCmd);
    }

    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(&oSysCmd);
    oSysState.Set_ExecStatus_Success();
    oSysState.AppendParas(oSysCmd);
     SendSysState(&oSysState);

    if (nRet == 2)
    {
        //ReturnBroadcastUserMngr(oSysState);
    }

    return 1;
}

long CSttNativeTestEngine_Mqtt::ReturnExecReply(CSttAtsCmd *pAtsCmd, long nCmdExecStatus,CSttCmdData *pRetData)
{
    CSttSysState oSysState;
    oSysState.UpdateSysStateHead(pAtsCmd);

    if (pRetData != NULL)
    {//返回结果数据
        oSysState.AppendEx(*pRetData);
        pRetData->RemoveAll();
    }

    oSysState.Set_ExecStatus(nCmdExecStatus);

    //2020-11-29  lijunqing
    X_SendSysState(NULL, &oSysState, g_nSttLogServerSpyAllCmd);

    return 0;
}

//autotest command

//2020-5-18  lijunqing
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats(void *pClientSocket, CSttAtsCmd &oAtsCmd)
{
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
	else
    {
        return 0;
    }
}

// long CSttNativeTestEngine_Mqtt::Process_Cmd_Test(void *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor)
// {
// 	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("++++CSttNativeTestEngine_Mqtt::Process_Cmd_Test++++"));
// 	ReturnExecReply(NULL, STT_CMD_ExecStatus_ACK);
// 	long nRet = m_pSmartTest->Process_Cmd_Test(pBuf, nLen);
// 
// 	if (nRet >= 0)
// 	{
// 		ReturnExecReply(NULL, STT_CMD_ExecStatus_SUCCESS);
// 	}
// 	else
// 	{
// 		ReturnExecReply(NULL, STT_CMD_ExecStatus_FAILURE);
// 	}
// 
// 	return nRet;
// }
/*
<ats-cmd name="" id="GetDataset" testor="" >
    <paras name="" id="">
        <data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
    </paras>
</ats -cmd>
*/
CDvmDataset* CSttNativeTestEngine_Mqtt::Ats_GetDataset(CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Ats_SetDataset(CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Ats_ConfigDevice(CSttAtsCmd &oAtsCmd)
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

void CSttNativeTestEngine_Mqtt::Return_Ats_Success(void *pClientSocket, CSttAtsCmd &oAtsCmd, unsigned int nState, CDvmDataset *pDatas, CExBaseObject *pGuideBook)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_CreateTest(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

	m_pSmartTest->Post_Ats_CreateTest(&oAtsCmd);

/*  
	//创建部分，动态申请Guidebook的内存，放到主线程，参见CSttSmartTest::On_Ats_CreateTest
	//CSttSmartTest::On_Ats_CreateTest被主线程消息函数调用

	m_pSmartTest->m_bTestCreated = FALSE;
	//CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("@@@@@@@@@@@@@@@@@@@@degub---------0000"));
    long nRet = m_pSmartTest->Ats_CreateTest(&oAtsCmd, NULL);

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
*/

    return 0;
}


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_StartTest(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_StopTest(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_CloseTest(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_TestItem(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_TestFrom(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_TestAllFailedItems(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_GetItemReport(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_GetReportFile(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_GetSystemState(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_CreateDevice(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_ConnectDevice(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_ConfigDevice(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_GetDataset(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_SetDataset(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_RunProcedure(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_CloseDevice(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_ConfigEngine(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_FinishInputData(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_QueryAtsFile(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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


long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_SetItemState(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_GenerateTemplate(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_GenerateItems(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

    if (nRet == 0)
    {
		oSysState.Set_ExecStatus(STT_CMD_ExecStatus_SUCCESS);
		CSttParas *pParas = oSysState.GetSttParas();

		if (m_pSmartTest->Is_GenerateItems_CmdWzd())
		{
			CDataGroup *pReply = m_pSmartTest->GetGenrateItems_CmdWzd_Reply();
			CDataGroup *pCommCmd = pParas->AddNewGroup(_T("通讯命令生成配置"), STT_CMD_PARA_CommCmd, _T(""));
			pCommCmd->AppendCloneEx2(*pReply, TRUE, TRUE);
			oSysState.Set_Xml_Pkg_With_Name(TRUE);
		}
		else
		{
			pItems = m_pSmartTest->GetSttItems_AtsGen();

			if (pItems != NULL)
			{
				CString strParentItemPath;
				oAtsCmd.GetParasDataValueByID(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
				pParas->AddNewData(STT_CMD_PARA_ParentItemsPath, strParentItemPath);
				pParas->AddTail(pItems);
				oSysState.Set_Xml_Pkg_With_Name(TRUE);
			}
		}

		CString strGenerateItems;
		CSttParas *pPara = oAtsCmd.GetSttParas();
		CDataGroup *pGenerateItems = (CDataGroup *)pPara->FindByID(STT_CMD_PARA_generate_items);
		
		if (pGenerateItems != NULL)
		{
			strGenerateItems = pGenerateItems->m_strValue;
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

			pParas->AddNewChild(pGlobalDatas);
			pParas->AddNewChild(pSysPara);
		}

		oSysState.Set_Xml_Pkg_With_Name(TRUE);
		ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
		oSysState.Set_Xml_Pkg_With_Name(FALSE);

		if (pItems != NULL)
		{
			pParas->Delete(pItems);
		}

		if (pGlobalDatas != NULL)
		{
			pParas->Delete(pGlobalDatas);
		}

		if (pSysPara != NULL)
		{
			pParas->Delete(pSysPara);
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_GenerateMacroTest(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

			pSttItems = new CSttItems();
			CSttCmdGuideBookTransTool oTool;
			oTool.Trans(pItems, pSttItems);

			pParas->AddTail(pSttItems);
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_SetItemPara(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Procss_Cmd_Ats_SetItemPara_SystemConfig(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long  CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_ManualTrigger(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_SaveTemplate(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
		m_pSmartTest->SetTemplateGenMode(TEMPLATE_GEN_MODE_SAVE);
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_SaveTest(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
		m_pSmartTest->SetTemplateGenMode(TEMPLATE_GEN_MODE_SAVE);
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_ExportWordRpt(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_OpenTemplate(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_OpenGbrptFile(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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
long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_AdjustMainWnd(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_ExportReport(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_QueryItem(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_UpdateItem(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

long CSttNativeTestEngine_Mqtt::Process_Cmd_Ats_AdjustReport(void *pClientSocket, CSttAtsCmd &oAtsCmd)
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

void CSttNativeTestEngine_Mqtt::Return_NoDevice(void *pClientSocket, CSttSysState &oSysState)
{
    oSysState.Set_ExecStatus_Failure();
    CLogPrint::LogString(XLOGLEVEL_TRACE, _T("ConfigDevice: has no device"));
    ReturnSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
}

void CSttNativeTestEngine_Mqtt::Return_Ats_Event(void *pClientSocket, CSttSysState &oSysState)
{
    if (pClientSocket != NULL)
    {
        //2020-11-29  lijunqing
        X_SendSysState(pClientSocket, &oSysState, g_nSttLogServerSpyAllCmd);
        // SendSysState(&oSysState);
    }
    else
    {
        ReturnSysStateToChildren(NULL, &oSysState);
    }
}

long CSttNativeTestEngine_Mqtt::ValidateSmartTest(void *pClientSocket, CSttSysState &oSysState)
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

void CSttNativeTestEngine_Mqtt::Return_DeviceParameter_AfterLogin(void *pClientSocket, CSttSysState &oSysState)
{
	oSysState.Free();
	oSysState.m_strID = STT_CMD_TYPE_ADJUST_ReadDeviceParameter;
	oSysState.SetReporting();
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_ADJUST;

	CSttParas *pParas = oSysState.GetSttParas();
	//原先采用从文件中转换获取，但缺少开入开出信息，故此处改为底层测试服务返回记录保存的报文   shaolei 20220414
	if (m_pSmartTest != NULL)
	{
		m_pSmartTest->GetReadDeviceParameter(pParas);
	}
	else
	{
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
	CString strAppName;
#ifdef _PSX_QT_LINUX_
	strAppName = _T("SttTestMainCore");
#else
	strAppName = _T("SmartTestCore");
#endif

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
                pDeviceAttrs->AddNewData(_T("SttTestMainCore版本"), _T("SttTestMainCore_Ver"), _T("AppVersion"), _T("2024.08.15 - 09:30"));
			}
			else
			{
                pAppVersion->m_strValue = _T("2024.08.15 - 09:30");
			}
		}
	}

	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value--;
	 SendSysState(&oSysState);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value++;
}

//2020-11-25  lijunqing
void CSttNativeTestEngine_Mqtt::OnTimer()
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

/*
#define MQTT_SYSSTATE_TYPE_REPLY		_T("REPLY")
#define MQTT_SYSSTATE_TYPE_EVENT		_T("EVENT")
#define MQTT_SYSSTATE_TYPE_REPORT		_T("REPORT")
#define MQTT_SYSSTATE_TYPE_EXCEPTION	_T("EXCEPTION")
*/

long CSttNativeTestEngine_Mqtt::ReturnSysState(void *pComm, CSttSysState *pSysState, long nSpyAllCmd)
{
	CSttMqttTopicCmbn oCmbn;

	if (m_pMqttTopicCmbn == NULL)
	{
		oCmbn.AddSubTopic(_T("ats"));
		oCmbn.AddSubTopic(m_strBentchSN);
		oCmbn.AddSubTopic(MQTT_CMD_ID_AtsState);
	}
	else
	{
		oCmbn.InitTopic(m_pMqttTopicCmbn);
	}

	if (pSysState->m_strRetType == SYS_STATE_RETTYPE_REPLY)
	{//测试台SN/ AtsState/StopTest/REPLY
		oCmbn.AddSubTopic(pSysState->m_strID);
		oCmbn.AddSubTopic(pSysState->m_strRetType);
	}
	else if (pSysState->m_strRetType == SYS_STATE_RETTYPE_EVENT)
	{//测试台SN/ AtsState/EVENT/TestStoped
		oCmbn.AddSubTopic(pSysState->m_strRetType);
		oCmbn.AddSubTopic(pSysState->m_strID);
	}
	else  if (pSysState->m_strRetType == SYS_STATE_RETTYPE_RTDATA)
	{
		oCmbn.AddSubTopic(pSysState->m_strRetType);
	}
	else  if (pSysState->m_strRetType == SYS_STATE_RETTYPE_REPORT)
	{//测试台SN/ AtsState/EVENT/Report
		oCmbn.AddSubTopic(SYS_STATE_RETTYPE_EVENT);
		oCmbn.AddSubTopic(pSysState->m_strRetType);
	}
	else
	{
		oCmbn.AddSubTopic(pSysState->m_strID);
		oCmbn.AddSubTopic(pSysState->m_strRetType);
	}

	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oCmbn.m_nBufferLength = pSysState->GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys
		, &oCmbn.m_pszBuffer, 0, m_nXmlRWType);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	g_theAtsOutMqttClient->PublicTopic(oCmbn);
	//2020-11-29  lijunqing
	//X_SendSysState(pComm, pSysState, nSpyAllCmd);
	return 0;
}

long CSttNativeTestEngine_Mqtt::ReturnSysStateToChildren(void *pComm,CSttSysState *pSysState)
{
	ReturnSysState(pComm, pSysState, 1);
	return 0;
}

long CSttNativeTestEngine_Mqtt::X_SendSysState(void *pComm, CSttSysState *pSysState, long nSpyAllCmd)
{
	ReturnSysState(pComm, pSysState, nSpyAllCmd);
	return 0;
}

long CSttNativeTestEngine_Mqtt::X_SendCmd(void *pComm, CSttCmdBase *pSttCmd, long nSpyAllCmd)
{
	CSttMqttTopicCmbn oCmbn;
	oCmbn.InitTopic(m_pMqttTopicCmbn);
	long nCount = oCmbn.GetSubTopicCount();

	oCmbn.SetSubTopic(nCount-1,  MQTT_CMD_ID_AtsCmd);
	oCmbn.AddSubTopic(pSttCmd->m_strID);

	CSttCmdDefineXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oCmbn.m_nBufferLength = pSttCmd->GetXml_UTF8(CSttCmdDefineXmlRWKeys::g_pXmlKeys
		, &oCmbn.m_pszBuffer, 0, m_nXmlRWType);
	CSttCmdDefineXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	g_theAtsOutMqttClient->PublicTopic(oCmbn);
	return 0;
}

long CSttNativeTestEngine_Mqtt::RetFailureSysState(CSttCmdBase *pCmd)
{
	CSttSysState oSysState;
	oSysState.UpdateSysStateHead(pCmd);
	oSysState.Set_ExecStatus_Failure();

	return ReturnSysStateToChildren(NULL, &oSysState);
}

