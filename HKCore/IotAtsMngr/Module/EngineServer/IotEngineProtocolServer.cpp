#include "stdafx.h"
#include "IotEngineProtocolServer.h"
#include "IotEngineProtoServer_MqttClient.h"
#include "IotEngineToPxBase.h"
#include "../ProtocolBase/Factory/EngineToPxFactory.h"
#include "IotEngineServer_Mqtt.h"
#include "../IotEngineGlobalDef.h"

//2021-8-19  lijunqing  CIotEngineProtocolServer::CreateProtocol(CSttIotCmd &oIotCmd)����������ͨ�õĺ���
//��Ӧ���о���Ĺ�����ӡ������Ͳ��ǹ���ģʽ  x_Sensor_EngineProtoSvr_x
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
	//yzj 2021-10-25 closedeviceʱӦ�ý������д�����mqtt client����
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

//mqtt���Ӷ���
void CIotEngineProtocolServer::OnClose(char *pszErr)
{
	FreePxCmmInterface();

	//ɾ������
	m_pIotEngineMqttServer->OnCloseDevice(this);
}

BOOL CIotEngineProtocolServer::Init(const char *pszIP,long nPort, const char *pszDeviceSN)
{
	FreePxCmmInterface();

	CIotEngineProtoServer_MqttClient *pProtocolMqttClient = new CIotEngineProtoServer_MqttClient();

	//��ʼ�������SN��װ��ID,���ڶ������� 
	//2021-8-22  lijunqing   ��Э����󣬶�����Դ�װ�õ��������⣬���������ĸ������
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
�������⣺
�����SN/DeviceID/IotCmd/PkgParse
�����SN/DeviceID/IotCmd/PkgProduce
�����SN/DeviceID/IotCmd/RunProcedure
�����SN/DeviceID/IotCmd/GetDataset
�����SN/DeviceID/IotCmd/ConfigDevice
�����SN/DeviceID/IotCmd/CloseDevice
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
���⣺�����SN/DeviceID/IotCmd/RunProcedure
<iot-cmd name="" id="RunProcedure" testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
		<data name="" id="RecordMode" data-type="" value="own"/>
		<data id="id-procedure" value="WriteSetting">��ִ�е�ͨ�Ź��̡�
			<value data-type="FLOAT" id="" name="" value=""/>��ͨ�Ź��̵Ĳ�����
		</data>
		<data id="dataset-path" value="PT5001EPROT$LLN0$dsSetting1"/>�����ݼ���·����
		<dataset id="LLN0$dsSetting1" name="">
			...............................
		</dataset>
	</paras>
</iot-cmd>
RecordMode��none=��¼����own=ֻ¼���������ݡ�all=¼�������ڼ��ȫ������

�����SN/DeviceID/IotState/ RunProcedure /Reply
<sys-state name="" id="RunProcedure" mater-host="" ret-type="REPLY" id-cmd="iot-cmd">
	<paras>
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
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

	//����Э��ת��ģ��ӿ�
	long nRet = m_pEngineProtoSvrImpInterface->RunProcedure(oIotCmd);

	//����ReplyӦ��
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
���⣺�����SN/DeviceID/IotCmd/CloseDevice
<iot-cmd name="" id=" CloseDevice " testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
	</paras>
</iot-cmd>

���⣺�����SN/DeviceIDIotState/CloseDevice/Reply
<sys-state name="" id=" CloseDevice " mater-host="" ret-type="REPLY" id-cmd="iot-cmd">
	<paras name="" id="">
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
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

	//���عر�װ���¼�
	OnDeviceClosed(0);

	//ɾ������
	m_pIotEngineMqttServer->OnCloseDevice(this);

	return 1;
}

//����Э��ת��ģ���Э�����ģ��
BOOL CIotEngineProtocolServer::CreateProtocol(CSttIotCmd &oIotCmd)
{
	CString strDeviceID,strPpxml,strDvmFile,strCmmCfgFile;
	oIotCmd.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);
	oIotCmd.GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpxml);//��Լ�ļ��ֶΣ�������ͬת��ģ��
	oIotCmd.GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);
	oIotCmd.GetParasDataValueByID(XPARA_ID_CommCfgFile, strCmmCfgFile);

	//����ģʽ����Э��ת���ӿں�Э�����ģ��
	CIotEngineToPxBase* pIotEngineToPx = Px_CreateEngineToPxByPxProtoID(strPpxml, this, &oIotCmd);
	if (pIotEngineToPx == NULL)
	{
		return FALSE;
	}

	m_pEngineProtoSvrImpInterface = pIotEngineToPx;

	return TRUE;
}

//Э��ת��ģ����̽����¼�����
/******************************
���⣺�����SN/DeviceID/IotState/RunProcedure/EVENT/�¼�ID
<sys-state name="" id="RunProcedure" mater-host="" ret-type="EVENT" id-cmd="iot-cmd">
	<paras>
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
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
���⣺�����SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed
<sys-state name="" id="EngineEvent" mater-host="" ret-type="EVENT" id-cmd="iot-cmd">
	<paras name="" id="">
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
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

//���¶�������:��Ҫ���IotEngine�����󣬹�Լ�������֪����ͬһ��װ�������յ�CreateDevice���⣬
//��Ҫȡ������֮ǰ�����⣬���¶����µ�����
void CIotEngineProtocolServer::ReSubcribeMqttTopic()
{
	ASSERT(m_pPxCmmOptrInterface != NULL);

	CIotEngineProtoServer_MqttClient *pClient = (CIotEngineProtoServer_MqttClient *)m_pPxCmmOptrInterface;

	pClient->ReSubcribeMqttTopic();
}