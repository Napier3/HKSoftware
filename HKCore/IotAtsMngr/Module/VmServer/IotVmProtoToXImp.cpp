#include "stdafx.h"
#include "IotVmProtoToXImp.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"
// #include "../../../SttStudio/Module/SmartTestInterface/MacroTestFactory.h"

#include "IotVmServer_Mqtt.h"
#include "IotVmProtoToXImp_MqttClient.h"

//Vm模块对象
#include "../Vm/Simpac/VmSimpac.h"
#include "../../../SttStudio/Module/SttCmd/SttMacro.h"
#include "../../../Module/Serial/SerialConfig/SerialConfig.h"
#include "../Vm/Dtvp200/VmDtvp200.h"
#include "../Vm/DKSource/VmDKSource.h"
//#include "../Vm/DKSource/VmDKSource.h"
#include "../Vm/GuBei/VmGuBei.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

//////////////////////////////////////////////////////////////////////////
//CIotVmProtoToXImp
CIotVmProtoToXImp::CIotVmProtoToXImp(CIotVmServer_Mqtt *pVmServer)
{
	m_pIotVmServer_Mqtt = pVmServer;
	m_pVmXImpBase = NULL;
}

CIotVmProtoToXImp::CIotVmProtoToXImp()
{
	m_pVmXImpBase = NULL;
}

CIotVmProtoToXImp::~CIotVmProtoToXImp()
{
	try
	{
		delete m_pVmXImpBase;
		m_pVmXImpBase = NULL;
	}
	catch(...)
	{
	}

}

//////////////////////////////////////////////////////////////////////////
//协议接口函数
void CIotVmProtoToXImp::InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
				  ,const CString &strCmmCfgFile,CDataGroup *pCfgGroup)
{
	//根据测试仪的类型，创建测试仪控制接口，参考SmartTest：SttTestEngine、VmEngine、..........
	//CMacroTestFactory::AttatchLogWnd(m_hMacroTestLogWnd);

	CPxProtocolBase::InitProtocol(strDeviceID,strDvmFile,strPpxmlFile,strCmmCfgFile,pCfgGroup);
}

BOOL CIotVmProtoToXImp::Init(const char *pszIP,long nPort)
{
	CIotVmProtoToXImp_MqttClient *pProtocolMqttClient = new CIotVmProtoToXImp_MqttClient();
	pProtocolMqttClient->m_strDeviceSN = m_strID;

	//初始化请求端SN、装置ID,用于订阅主题 
	//2021-8-22  lijunqing   此协议对象，订阅针对此装置的所有主题，而不管是哪个请求端
	//pProtocolMqttClient->InitTopicSrcInfo(m_strFirstTopic,m_strID);

	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "VmProtoImp");

	if (bRet)
	{
		pProtocolMqttClient->SetMqttEngineRef(this);
		AttachPxCmmInterface(pProtocolMqttClient);
	}
	else
	{
		delete pProtocolMqttClient;
	}

	return bRet;
}

/************************
测试仪主题：
//主题：测试仪SN/TestCmd/SetParameter
//主题：测试仪SN/TestState/SetParameter/Reply
//主题：测试仪SN/TestState/EVENT/TestStarted
//主题：测试仪SN/TestState/REPORT
#define STT_CMD_TYPE_TEST_SetParameter		_T("SetParameter")
#define STT_CMD_TYPE_TEST_UpdateParameter	_T("UpdateParameter")
#define STT_CMD_TYPE_TEST_StartTest			_T("StartTest")
#define STT_CMD_TYPE_TEST_StopTest			_T("StopTest")
#define STT_CMD_TYPE_TEST_GetReport			_T("GetReport")
#define STT_CMD_TYPE_TEST_CloseDevice		_T("CloseDevice")
#define STT_CMD_TYPE_TEST_GetSystemState	_T("GetSystemState")
#define STT_CMD_TYPE_TEST_SysDefaultOutput	_T("SystemDefaultOutput")
#define STT_CMD_TYPE_TEST_CreateDevice	_T("CreateDevice")
#define STT_CMD_TYPE_TEST_ConfigDevice	_T("ConfigDevice")
#define STT_CMD_TYPE_TEST_ConnectDevice	_T("ConnectDevice")

**************************/
long CIotVmProtoToXImp::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	CXObjectRefDriver oDriver(CSttTestCmd::New);
	CSttTestCmd *pTestCmd = (CSttTestCmd*)oDriver.New();
	pTestCmd->m_strFromSN = strFromSN;

	BufToCmd(pTestCmd, pBuf, nLen, MQTT_DATA_FORMAT_XML);//_PUGI_XML_TYPE_
	oDriver.AddRef();

	//2021-9-5  lijunqing 避免堵塞网络通信，采用发送消息的模式
	//CVmXImpBase::OnVmServerCmdRcv

	if (m_pVmXImpBase == NULL)
	{
		return -1;
	}

	m_pVmXImpBase->PostVmServerRcvCmd(pCmmOptrInterface, pTestCmd);


// 	if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_ConfigDevice)
// 	{
// 		m_pVmXImpBase->TestCmd_ConfigDevice(pTestCmd->GetSttParas());
// 	}
// 	else if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_ConnectDevice)
// 	{
// 		m_pVmXImpBase->TestCmd_ConnectDevice(pTestCmd->GetSttParas());
// 	}
// 	else if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_StartTest)
// 	{
// 		m_pVmXImpBase->TestCmd_StartTest(pTestCmd->GetSttMacro());
// 	}
// 	else if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_StopTest)
// 	{
// 		m_pVmXImpBase->TestCmd_StopTest(pTestCmd->GetSttParas());
// 	}
// 	else if (pTestCmd->m_strID == STT_CMD_TYPE_TEST_CloseDevice)
// 	{
// 		m_pVmXImpBase->TestCmd_CloseDevice(pTestCmd->GetSttParas());
// 	}

	return 0;
}

void CIotVmProtoToXImp::OnTestState_Reply(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{
	ASSERT (FALSE);
}

//mqtt连接断链
void CIotVmProtoToXImp::OnClose(char *pszErr)
{
	m_pIotVmServer_Mqtt->OnClseDevice(this);
	FreePxCmmInterface();
}

//重新订阅主题:主要解决IotEngine断链后，规约引擎服务不知道，同一个装置再试收到CreateDevice主题，
//需要取消订阅之前的主题，重新订阅新的主题
void CIotVmProtoToXImp::ReSubcribeMqttTopic()
{
	ASSERT(m_pPxCmmOptrInterface != NULL);
	CIotVmProtoToXImp_MqttClient *pClient = (CIotVmProtoToXImp_MqttClient *)m_pPxCmmOptrInterface;

	pClient->ReSubcribeMqttTopic();
}

/*
<test-cmd name="" id=" CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<group id="test-app">
			<data id="DeviceSN" value="123456789"/>
			<data id="EngineProgID" value="IotVm"/>
			<data id="dvm-file" value="MacroTest.xml"/>
			<data id="remote-ip" value="127.0.0.1"/>
			<data id="remote-port" value="9988"/>
		</group>
	</paras>
</test-cmd>
*/
//创建协议转换模块和协议服务模块
BOOL CIotVmProtoToXImp::CreateProtocol(CSttTestCmd &oTestCmd)
{
	CString strDeviceSN,strDvmFile, strProtocolID;
	CDataGroup *pTestApp = (CDataGroup*)oTestCmd.FindByID(XPARA_ID_test_app);
	CDataGroup *pAppConfig = NULL;

	if (pTestApp != NULL)
	{
		pAppConfig = pTestApp;
	}
	else
	{
		pAppConfig = oTestCmd.GetSttParas();
		//yzj 2021-9-24 查找的子节点层级不对
		pAppConfig = (CDataGroup*)pAppConfig->FindByID(XPARA_ID_test_app);
	}

	stt_GetDataValueByID(pAppConfig, STT_CMD_PARA_DeviceSN, strDeviceSN);
	//stt_GetDataValueByID(pAppConfig, XPARA_ID_PPXMLFILE, strPpxml);
	stt_GetDataValueByID(pAppConfig, XPARA_ID_DVMFILE, strDvmFile);
	//stt_GetDataValueByID(pAppConfig, XPARA_ID_CommCfgFile, strCmmCfgFile);
	stt_GetDataValueByID(pAppConfig, STT_CMD_PARA_ProtocolID, strProtocolID);

	if (m_strCurrPortocolID.GetLength() > 4)
	{//如果已经创建，就不再创建。
		if (m_strCurrPortocolID != strProtocolID)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("创建不同的规约通信对象[%s] [%s]")
				, m_strCurrPortocolID.GetString(), strProtocolID.GetString());
		}

		return TRUE;
	}

	m_strCurrPortocolID = strProtocolID;

	BOOL bRet = FALSE;
	//根据测试仪的类型，创建测试仪控制接口，参考SmartTest：SttTestEngine、VmEngine、..........
	//CMacroTestFactory::AttatchLogWnd(m_hMacroTestLogWnd);
	if (_T("IotVm.Simpac") == strProtocolID)
	{
		//验证中心的温控箱
		CVmSimpacApp *pVmSimpacApp = new CVmSimpacApp();
		pVmSimpacApp->m_pSttMacroTestEventServerInterface = this;
		bRet = pVmSimpacApp->TestCmd_ConfigDevice((CSttCmmOptrInterface *)oTestCmd.GetSttCmmOptrInterface(), pAppConfig);
		m_pVmXImpBase = pVmSimpacApp;
		m_pVmXImpBase->m_strDeviceSN = strDeviceSN;
	}
	//yzj 2021-11-4 dk系列接口
 	else if (_T("IotVm.XLDL") == strProtocolID)
 	{
		CString strPath = _P_GetConfigPath() + strDeviceSN + _T(".xml");
 		CVmDKSourceApp *pVmDKSourceApp = new CVmDKSourceApp();
		pVmDKSourceApp->m_oDK51E1.m_oConfig.Create(strPath);
 		pVmDKSourceApp->m_pSttMacroTestEventServerInterface = this;
		pVmDKSourceApp->m_strDeviceSN = strDeviceSN;
 		bRet = pVmDKSourceApp->TestCmd_ConfigDevice((CSttCmmOptrInterface *)oTestCmd.GetSttCmmOptrInterface(), pAppConfig);
 		m_pVmXImpBase = pVmDKSourceApp;
 	}
	else if (_T("IotVm.Dtvp200") == strProtocolID) //sf 20211115
	{
		//验证中心的倾角检定校准装置
		CString strPath = _P_GetConfigPath() + strDeviceSN + _T(".xml");
		CVmDtvp200 *pVmDtvp200App = new CVmDtvp200();
		pVmDtvp200App->m_oDtvp200.m_Serial.m_oConfig.Create(strPath);
		pVmDtvp200App->m_pSttMacroTestEventServerInterface = this;
		pVmDtvp200App->m_strDeviceSN = strDeviceSN;
		bRet = pVmDtvp200App->TestCmd_ConfigDevice((CSttCmmOptrInterface *)oTestCmd.GetSttCmmOptrInterface(), pAppConfig);
		m_pVmXImpBase = pVmDtvp200App;
	}
	//联研院温控槽-串口设备
	else if (_T("IotVm.GuBei") == strProtocolID)
	{
		CString strPath = _P_GetConfigPath() + strDeviceSN + _T(".xml");
		CVmGuBeiApp *pVmGuBeiApp = new CVmGuBeiApp();
		pVmGuBeiApp->m_oGuBeiTest.m_Serial.m_oConfig.Create(strPath);
		pVmGuBeiApp->m_pSttMacroTestEventServerInterface = this;
		pVmGuBeiApp->m_strDeviceSN = strDeviceSN;
		bRet = pVmGuBeiApp->TestCmd_ConfigDevice((CSttCmmOptrInterface *)oTestCmd.GetSttCmmOptrInterface(), pAppConfig);
		m_pVmXImpBase = pVmGuBeiApp;
	}

	return bRet;
}


LRESULT CIotVmProtoToXImp::OnElectricTestMsg(WPARAM wParam, LPARAM lParam)
{
	long nEvent = wParam;

	switch (nEvent)
	{
	case MTMSG_ConnectSuccess : //0,
		//atsrpc_OnTestAppEvent(this, TestAppEvent_ConnectSuccess);
		//m_pTCtrlMsgRcv->OnConnectSuccess();
		break;

	case MTMSG_ConnectFaild : //1,
		//atsrpc_OnTestAppEvent(this, TestAppEvent_ConnectFaild);
		//m_pTCtrlMsgRcv->OnException(nEvent, CXLanguageResourceAtsBase::g_sLangTxt_OnlineFail.GetString() /*_T("联机失败")*/);
		//StopTestExtern();
		break;

	case MTMSG_ConnectConfig : //2,
		//2020-11-24  lijunqing 处理异常消息，解决在m_pCurrTestItem==NULL的情况下无法发出事件消息
// 		if (m_pCurrTestItem != NULL)
// 		{
// 			TestItemMacroTestChildItem((CMacroTest*)m_pCurrTestItem);
// 		}
		break;

	case MTMSG_TestBegin : //3,
		//atsrpc_OnTestAppEvent(this, TestAppEvent_TestBegin);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceAtsBase::g_sLangTxt_TestStartInf/*_T("------收到电气量测试开始消息【%s】")*/, m_pCurrTestItem->m_strName);
		//TestFirstSubItems_MacroTest(TRUE);
		//m_pTCtrlMsgRcv->OnCurrItemStateChanged(m_pCurrTestItem);
		//UpdateMacroCharTest((CMacroTest*)m_pCurrTestItem); //更新特性曲线的过程状态
		break;

	case MTMSG_TestFinished : //4,
		//atsrpc_OnTestAppEvent(this, TestAppEvent_TestFinished);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("收到电气量测试结束消息【%s】"), m_pCurrTestItem->m_strName);
		//FinishTestItemMacroTest((CMacroTest*)m_pCurrTestItem);
		//m_nMacroTestReTestTimes = 0;
		break;

	case MTMSG_SearchPointFinished : //5,
		//atsrpc_OnTestAppEvent(this, TestAppEvent_SearchPointFinished);
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("收到电气量测试结束消息【%s】"), m_pCurrTestItem->m_strName);
		//UpdateMacroCharTest((CMacroTest*)m_pCurrTestItem);  //更新特性曲线的过程状态
		break;

	case MTMSG_CommError : //5,
		//atsrpc_OnTestAppEvent(this, TestAppEvent_CommError);
		//m_pTCtrlMsgRcv->OnException(nEvent,CXLanguageResourceAtsBase::g_sLangTxt_ParaDnldFail.GetString() /*_T("------参数下载失败")*/);
		//StopTestExtern();
		break;

	case MTMSG_Not_Surport : //6,
		//2020-11-24  lijunqing 处理异常消息，解决在m_pCurrTestItem==NULL的情况下无法发出事件消息
// 		if (m_pCurrTestItem != NULL)
// 		{
// 			CMacroTest *pMacroTest = (CMacroTest*)m_pCurrTestItem;
// 			CMacroTestPara *pPara = pMacroTest->GetMacroTestPara();
// 			CString strMsg;
// 			strMsg.Format(CXLanguageResourceAtsBase::g_sLangTxt_TestUnsuptFctn.GetString()/*L"------测试仪器底层功能接口不支持测试功能[%s]"*/,  pPara->GetMacroID().GetString());
// 			m_pTCtrlMsgRcv->OnException(nEvent, strMsg);
// 		}
// 
// 		StopTestExtern();
		break;

	case MTMSG_ManualTestBegin : //7,
		break;

	case MTMSG_ManualTestReturn : //8,
		break;

	case MTMSG_ManualTestStop : //9,
		break;

	case MTMSG_ShowCurItem : //10
		break;

	case MTMSG_TestOverTime :
		ASSERT (FALSE);

		break;

	case MTMSG_AppWarning :
	case MTMSG_AppError :
		//atsrpc_OnTestAppEvent(this, TestAppEvent_AppError);
		//OnElectricTestAppMsg( wParam, lParam);
		break;
	case MTMSG_TestManualStop:
		//atsrpc_OnTestAppEvent(this, TestAppEvent_TestStoped);
		//m_pTCtrlMsgRcv->OnStopTest(0);  //0表示测试停止
		//StopTestExtern();
		break;

	default:
		break;
	}

	return 0;
}

void CIotVmProtoToXImp::OnTimer(UINT nIDEvent)
{

}

void CIotVmProtoToXImp::OnTestState_Reply(CSttCmmOptrInterface* pSttCmmOptrInterface, CSttCmdData *pParas, long nExecStaus, char *pszEventID, char *pszRetCmdType)
{
	ReturnSysState_REPLY(pSttCmmOptrInterface, nExecStaus, pParas, pszEventID, pszRetCmdType);
}

void CIotVmProtoToXImp::OnTestState_Report(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{
	
}

void CIotVmProtoToXImp::OnTestState_Exception(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{

}


void CIotVmProtoToXImp::OnTestEvent_ExecCmd(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{

}

void CIotVmProtoToXImp::OnTestEvent_ConnectSuccess(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{

}

void CIotVmProtoToXImp::OnTestEvent_ConnectFailed(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{

}

void CIotVmProtoToXImp::OnTestEvent_TestStarted(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{
	//2021-9-5  lijunqing
	//在此添加返回测试开始的事件
	CSttSysState oSttSysState;
	ReturnSysState_EVENT(pSttCmmOptrInterface, &oSttSysState, SYS_STATE_EVENT_OnTestStarted, STT_CMD_SYSSTATE_TEST);
}

void CIotVmProtoToXImp::OnTestEvent_TestFinished(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{
	//2021-9-24 yzj 加入结束测试	
	CSttSysState oSttSysState;
	CSttMacro* pMacro = oSttSysState.GetSttMacro();
	pMacro->m_strID = pParas->m_strID;
	CSttResults *pResults = pMacro->GetResults();
	pResults->AppendCloneEx(*pParas, TRUE);
	//pMacro->AddNewChild(pParas);
	ReturnSysState_EVENT(pSttCmmOptrInterface, &oSttSysState, SYS_STATE_EVENT_OnTestFinished, STT_CMD_SYSSTATE_TEST);
}

void CIotVmProtoToXImp::OnTestEvent_TestStoped(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{

}

void CIotVmProtoToXImp::OnTestEvent_SearchPointReport(CSttCmmOptrInterface* pSttCmmOptrInterface, CDataGroup *pParas)
{

}
