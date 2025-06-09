#include "stdafx.h"
#include "IotEngineProtocolServer.h"
#include "IotEngineProtoServer_MqttClient.h"
#include "IotEngineToPxBase.h"
#include "../ProtocolBase/Factory/EngineToPxFactory.h"
#include "IotEngineServer_Mqtt.h"
#include "../IotEngineGlobalDef.h"

//2021-8-19  lijunqing  CIotEngineProtocolServer::CreateProtocol(CSttIotCmd &oIotCmd)函数，属于通用的函数
//不应该有具体的工程烙印，否则就不是工厂模式  x_Sensor_EngineProtoSvr_x
// #ifdef x_Sensor_EngineProtoSvr_x
// #include "../Sensor/IotSensorSvrEngine.h"
// #endif

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEngineProtocolServer::CIotEngineProtocolServer()
{
	m_pEngineProtoSvrImpInterface = NULL;
	m_pIotEngineMqttServer = NULL;
}

CIotEngineProtocolServer::~CIotEngineProtocolServer()
{
	//yzj 2021-10-25 closedevice时应该将过程中创建的mqtt client析构
	if(m_pPxCmmOptrInterface != NULL)
	{
		m_pPxCmmOptrInterface->Disconnect();
	}

	if (m_pEngineProtoSvrImpInterface != NULL)
	{
		delete m_pEngineProtoSvrImpInterface;
		m_pEngineProtoSvrImpInterface = NULL;
	}
}

//mqtt连接断链
void CIotEngineProtocolServer::OnClose(char *pszErr)
{
	FreePxCmmInterface();

	//删除自身
	m_pIotEngineMqttServer->OnCloseDevice(this);
}

BOOL CIotEngineProtocolServer::Init(const char *pszIP,long nPort, const char *pszDeviceSN)
{
	FreePxCmmInterface();

	CIotEngineProtoServer_MqttClient *pProtocolMqttClient = new CIotEngineProtoServer_MqttClient();

	//初始化请求端SN、装置ID,用于订阅主题 
	//2021-8-22  lijunqing   此协议对象，订阅针对此装置的所有主题，而不管是哪个请求端
	//pProtocolMqttClient->InitTopicSrcInfo(m_strFirstTopic,m_strID);
	pProtocolMqttClient->m_strDeviceSN = pszDeviceSN;
	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "EngProtoSvr");

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
订阅主题：
请求端SN/DeviceID/IotCmd/PkgParse
请求端SN/DeviceID/IotCmd/PkgProduce
请求端SN/DeviceID/IotCmd/RunProcedure
请求端SN/DeviceID/IotCmd/GetDataset
请求端SN/DeviceID/IotCmd/ConfigDevice
请求端SN/DeviceID/IotCmd/CloseDevice
**************************/
long CIotEngineProtocolServer::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN,char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	CString strBuf = pBuf;
	strBuf.Replace("&quot;","");

	CSttIotCmd oIotCmd;
	oIotCmd.m_strFromSN = strFromSN;
	BufToCmd(&oIotCmd, const_cast<char*>(strBuf.GetString()), strBuf.GetLength(), MQTT_DATA_FORMAT_XML);

	return Process_Cmd_Iot(oIotCmd);
}

long CIotEngineProtocolServer::Process_Cmd_Iot(CSttIotCmd &oIotCmd)
{
	if(oIotCmd.m_strID == STT_CMD_TYPE_IOT_PkgParse)
	{
		Process_Cmd_Iot_PkgParse(oIotCmd);
	}
	else if(oIotCmd.m_strID == STT_CMD_TYPE_IOT_PkgProduce)
	{
		Process_Cmd_Iot_PkgProduce(oIotCmd);
	}
	else if(oIotCmd.m_strID == STT_CMD_TYPE_IOT_RunProcedure)
	{
		Process_Cmd_Iot_RunProcedure(oIotCmd);
	}
	else if(oIotCmd.m_strID == STT_CMD_TYPE_IOT_GetDataset)
	{
		Process_Cmd_Iot_GetDataset(oIotCmd);
	}
	else if(oIotCmd.m_strID == STT_CMD_TYPE_IOT_ConfigDevice)
	{
		Process_Cmd_Iot_ConfigDevice(oIotCmd);
	}
	else if(oIotCmd.m_strID == STT_CMD_TYPE_IOT_CloseDevice)
	{
		Process_Cmd_Iot_CloseDevice(oIotCmd);
	}

	return 1;
}

long CIotEngineProtocolServer::Process_Cmd_Iot_PkgParse(CSttIotCmd &oIotCmd)
{
	if (m_pEngineProtoSvrImpInterface == NULL)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	CSttParas oRetParas;
	long nRet = m_pEngineProtoSvrImpInterface->PkgPrase(oIotCmd,oRetParas);
	if (!nRet)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	CSttSysState oSysState;
	oSysState.AddNewChild((CExBaseObject *)oRetParas.Clone());
	oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceSN, m_strID);
	return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_SUCCESS,&oSysState);
}

long CIotEngineProtocolServer::Process_Cmd_Iot_PkgProduce(CSttIotCmd &oIotCmd)
{
	if (m_pEngineProtoSvrImpInterface == NULL)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	CSttParas oRetParas;
	long nRet = m_pEngineProtoSvrImpInterface->PkgProduce(oIotCmd,oRetParas);
	if (!nRet)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	CSttSysState oSysState;
	oSysState.AddNewChild((CExBaseObject *)oRetParas.Clone());
	oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceSN, m_strID);
	return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_SUCCESS,&oSysState);
}

/*************************************
主题：请求端SN/DeviceID/IotCmd/RunProcedure
<iot-cmd name="" id="RunProcedure" testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="装置SN"/>
		<data name="" id="RecordMode" data-type="" value="own"/>
		<data id="id-procedure" value="WriteSetting">【执行的通信过程】
			<value data-type="FLOAT" id="" name="" value=""/>【通信过程的参数】
		</data>
		<data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>【数据集的路径】
		<dataset id="LLN0$dsSetting1" name="">
			...............................
		</dataset>
	</paras>
</iot-cmd>
RecordMode：none=不录波、own=只录波自身数据、all=录波过程期间的全部数据

请求端SN/DeviceID/IotState/ RunProcedure /Reply
<sys-state name="" id="RunProcedure" mater-host="" ret-type="REPLY" id-cmd="iot-cmd">
	<paras>
		<data name="" id="DeviceID" data-type="" value="装置SN"/>
		<data id="ExecStatus" data-type=" " value="1|2|3|4" unit=""/>
	</paras>
</sys-state>
**************************************/
long CIotEngineProtocolServer::Process_Cmd_Iot_RunProcedure(CSttIotCmd &oIotCmd)
{
	if (m_pEngineProtoSvrImpInterface == NULL)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	//调用协议转换模块接口
	long nRet = m_pEngineProtoSvrImpInterface->RunProcedure(oIotCmd);

	//返回Reply应答
	if (!nRet)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_SUCCESS,m_strID);
}

long CIotEngineProtocolServer::Process_Cmd_Iot_GetDataset(CSttIotCmd &oIotCmd)
{
	if (m_pEngineProtoSvrImpInterface == NULL)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	CSttParas oRetParas;
	long nRet = m_pEngineProtoSvrImpInterface->GetDataset(oIotCmd,oRetParas);
	if (!nRet)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	CSttSysState oSysState;
	oSysState.AddNewChild((CExBaseObject *)oRetParas.Clone());
	oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceSN, m_strID);
	return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_SUCCESS,&oSysState);
}

long CIotEngineProtocolServer::Process_Cmd_Iot_ConfigDevice(CSttIotCmd &oIotCmd)
{
	if (m_pEngineProtoSvrImpInterface == NULL)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	m_pEngineProtoSvrImpInterface->ConfigDevice(oIotCmd);

	return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_SUCCESS,m_strID);
}

/*************************************
主题：请求端SN/DeviceID/IotCmd/CloseDevice
<iot-cmd name="" id=" CloseDevice " testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="装置SN"/>
	</paras>
</iot-cmd>

主题：请求端SN/DeviceIDIotState/CloseDevice/Reply
<sys-state name="" id=" CloseDevice " mater-host="" ret-type="REPLY" id-cmd="iot-cmd">
	<paras name="" id="">
		<data name="" id="DeviceID" data-type="" value="装置SN"/>
		<data id="ExecStatus" data-type="string" value="1|2|3" unit=""/>
	</paras>
</sys-state>
******************************************/

long CIotEngineProtocolServer::Process_Cmd_Iot_CloseDevice(CSttIotCmd &oIotCmd)
{
	if (m_pEngineProtoSvrImpInterface == NULL)
	{
		return ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_FAILURE,m_strID);
	}

	m_pEngineProtoSvrImpInterface->CloseDevice(oIotCmd);

	ReturnSysState(&oIotCmd, STT_CMD_ExecStatus_SUCCESS,m_strID);

	//返回关闭装置事件
	OnDeviceClosed(0);

	//删除自身
	m_pIotEngineMqttServer->OnCloseDevice(this);

	return 1;
}

//创建协议转换模块和协议服务模块
BOOL CIotEngineProtocolServer::CreateProtocol(CSttIotCmd &oIotCmd)
{
	CString strDeviceID,strPpxml,strDvmFile,strCmmCfgFile;
	oIotCmd.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);
	oIotCmd.GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpxml);//规约文件字段，创建不同转换模块
	oIotCmd.GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);
	oIotCmd.GetParasDataValueByID(XPARA_ID_CommCfgFile, strCmmCfgFile);

	//工厂模式创建协议转换接口和协议服务模块
	CIotEngineToPxBase* pIotEngineToPx = Px_CreateEngineToPxByPxProtoID(strPpxml, this, &oIotCmd);
	if (pIotEngineToPx == NULL)
	{
		return FALSE;
	}

	m_pEngineProtoSvrImpInterface = pIotEngineToPx;

	return TRUE;
}

//协议转换模块过程结束事件返回
/******************************
主题：请求端SN/DeviceID/IotState/RunProcedure/EVENT/事件ID
<sys-state name="" id="RunProcedure" mater-host="" ret-type="EVENT" id-cmd="iot-cmd">
	<paras>
		<data name="" id="DeviceID" data-type="" value="装置SN"/>
		<data name="EventID" id="EventID" data-type="string" value="CommFinish"/>
		<dataset id="LLN0$dsSetting1" name="">
			...............................
		</dataset>
	</paras>
</sys-state>
********************************/
long CIotEngineProtocolServer::OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset)
{
	CSttSysState oSysState;
	oSysState.m_strID = STT_CMD_TYPE_IOT_RunProcedure;
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_IOT;
	oSysState.SetEvent();
	oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceSN, m_strID);
	oSysState.SetParasDataAttr(SYS_STATE_XEVENT_EVENTID, strEventID);

	if (strEventID == RUNPROCEDURE_EVENT_CommFinish)
	{
		if (pDataset != NULL)
		{
			CSttParas *pParas = oSysState.GetSttParas();
			CDvmDataset *pResDataset = (CDvmDataset *)pDataset->Clone();
			pParas->AddNewChild(pResDataset);
		}
	}

	return Send(&oSysState);
}

/****************************************
主题：请求端SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed
<sys-state name="" id="EngineEvent" mater-host="" ret-type="EVENT" id-cmd="iot-cmd">
	<paras name="" id="">
		<data name="" id="DeviceID" data-type="" value="装置SN"/>
		<data name="EventID" id="EventID" data-type="string" value="DeviceClosed"/>
		<data name="DeviceID" id="DeviceID" data-type="string" value="nari_104"/>
	</paras>
</sys-state>
****************************************/
void CIotEngineProtocolServer::OnDeviceClosed(long nDeviceIndex)
{
	CSttSysState oSysState;
	oSysState.m_strID = SYS_STATE_EVENT_OnEngineEvent;
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_IOT;
	oSysState.SetEvent();
	oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceSN, m_strID);
	oSysState.SetParasDataAttr(SYS_STATE_XEVENT_EVENTID, _T("DeviceClosed"));
	oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceIndex, nDeviceIndex);

	Send(&oSysState);
}

//重新订阅主题:主要解决IotEngine断链后，规约引擎服务不知道，同一个装置再试收到CreateDevice主题，
//需要取消订阅之前的主题，重新订阅新的主题
void CIotEngineProtocolServer::ReSubcribeMqttTopic()
{
	ASSERT(m_pPxCmmOptrInterface != NULL);

	CIotEngineProtoServer_MqttClient *pClient = (CIotEngineProtoServer_MqttClient *)m_pPxCmmOptrInterface;

	pClient->ReSubcribeMqttTopic();
}