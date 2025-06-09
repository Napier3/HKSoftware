#include "stdafx.h"
#include "IotEngineServer_Mqtt.h"
#include "../SttMqttClientEngineConfig.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"
#include "IotEngineServer_MqttClient.h"
#include "../ProtocolBase/XEngineProtoSrvrBaseApp.h"
#include "../../../Module/XFileHttpClient/XFileHttpClient.h"

//2021-8-19  lijunqing  ����ģ�鲻�����κ�ʵ����ĿӦ�õĺۼ�
// #ifdef x_Edge_EngineProtoSvr_x
// #include "../Edge/EdgeEngineProtoSvrBaseApp.h"
// #elif defined x_Sensor_EngineProtoSvr_x
// #include "../Sensor/IotSensorSvrEngine.h"
// #include "../Sensor/SensorEngineProtoSrvrBaseApp.h"
// #endif

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEngineServer_Mqtt::CIotEngineServer_Mqtt()
{
	m_pXCommSvrWnd = NULL;
}

CIotEngineServer_Mqtt::~CIotEngineServer_Mqtt()
{
	if (m_pXCommSvrWnd != NULL)
	{
		delete m_pXCommSvrWnd;
		m_pXCommSvrWnd = NULL;
	}
}

//����IotEngineProtocolServerģ����Ϣ�����߼�
void CIotEngineServer_Mqtt::OnXCommMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1)
	{//����Ϣɾ��IotEngineProtocolServerģ��

		//��ʱ100ms����֤CloseDevice��������
		CTickCount32 oTick;
		oTick.DoEvents(100);

		CIotEngineProtocolServer *pIotEngineProtocolServer = (CIotEngineProtocolServer *)lParam;
		Delete(pIotEngineProtocolServer);
		return;
	}

	//����Ϣ����IotEngineProtocolServerģ��
	CSttIotCmd *pTempCmd = (CSttIotCmd*)lParam;

	if (pTempCmd == NULL)
	{
		return;
	}

	CString strDeviceSN;
	pTempCmd->GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	long nExecStatus = STT_CMD_ExecStatus_SUCCESS;

	//����IotEngineProtocolServerģ��
	if (!CreateIotEngineProtocolServer(*pTempCmd))
	{
		nExecStatus = STT_CMD_ExecStatus_FAILURE;
	}

	//����ReplyӦ��
	ReturnSysState(pTempCmd,nExecStatus,strDeviceSN);

	delete pTempCmd;
}

//mqtt���Ӷ����¼�
void CIotEngineServer_Mqtt::OnClose(char *pszErr)
{
	FreePxCmmInterface();
	DeleteAll();
}

BOOL CIotEngineServer_Mqtt::Init(const char *pszIP,long nPort)
{
	if (m_pXCommSvrWnd == NULL)
	{//������Ϣ����
		m_pXCommSvrWnd = new CXCommSvrWnd;
		m_pXCommSvrWnd->CreateXCommSvrWnd(this);
	}

	//ɾ��ԭ�ȵ�Mqtt�ͻ�����Ϣ��IotEngineProtocolServer����
	FreePxCmmInterface();
	DeleteAll();

	CIotEngineServer_MqttClient *pProtocolMqttClient = new CIotEngineServer_MqttClient();
	BOOL bRet = pProtocolMqttClient->Connect(pszIP,nPort, "EngSvr");

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
���ĵ����⣺
�����SN/��Լ����߷���ID/IotCmd/CreateDevice
**************************/
long CIotEngineServer_Mqtt::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	CSttIotCmd oIotCmd;
	oIotCmd.m_strFromSN = strFromSN;
	BufToCmd(&oIotCmd,pBuf,nLen,MQTT_DATA_FORMAT_XML);

	return Process_Cmd_Iot(oIotCmd);
}

long CIotEngineServer_Mqtt::Process_Cmd_Iot(CSttIotCmd &oIotCmd)
{
	if(oIotCmd.m_strID == STT_CMD_TYPE_IOT_CreateDevice)
	{
		return Process_Cmd_Iot_CreateDevice(oIotCmd);
	}

	return 1;
}

/******************************
<iot-cmd name="" id="CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
		<data name="" id="ppxml-file" data-type="" value="SZNR-TTU.ppxml"/>
		<data name="" id="dvm-file" data-type="" value="SZNR-TTU.xml"/>
		<data name="" id="cmm-cfg-file" data-type="" value="SZNR-TTU202012131700"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
	</paras>
</iot-cmd>

<sys-state name="" id="CreateDevice" mater-host="" ret-type="REPLY" id-cmd="iot-cmd">
	<paras name="" id="">
		<data name="" id="DeviceID" data-type="" value="װ��SN"/>
		<data id="ExecStatus" data-type="string" value="1|2|3" unit=""/>
	</paras>
</sys-state>
******************************/
/***********************************
��������ߣ�ֻ��Ҫ�����¼����������ɣ�
<iot-cmd name="" id="CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="TEST765342"/>
		<data name="" id="ppxml-file" data-type="" value="WSD.iotxml"/>
		<data name="" id="ppxml-file_s" data-type="" value="/profile/upload/2021/07/31/4e42cc98113b4bfa8fe90ec5e13447ec.iotxml"/>
		<data name="" id="dvm-file" data-type="" value="WSD.xml"/>
		<data name="" id="dvm-file_s" data-type="" value="/profile/upload/2021/07/31/360770cc768a45fab98c0db2277a2780.xml"/>
	</paras>
</iot-cmd>
�����õ����⣺123/345/IotCmd/CreateDevice
********************************/
// #ifdef x_Edge_EngineProtoSvr_x

long CIotEngineServer_Mqtt::Process_Cmd_Iot_CreateDevice(CSttIotCmd &oIotCmd)
{
	//2021-8-19  lijunqing  �˴�û�б�Ҫ�����κ��жϣ�ֱ�Ӵ������ɣ������Ӧ���豸������
	//��ʵ�ʵĶ����д�����
// 	CString strDeviceID,strDvmFile;
// 	oIotCmd.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceID);
// 	oIotCmd.GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);

	CString strHttpUrlHead,strUrl; 
	CSttMqttClientEngineConfig::GetHttpUrlHead(strHttpUrlHead);

	CString strPpxml,strDvmFile, strFile_s, strFileDownLoad;
	oIotCmd.GetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpxml);//��Լ�ļ��ֶΣ�������ͬת��ģ��
	oIotCmd.GetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);
	oIotCmd.GetParasDataValueByID(XPARA_ID_DVMFILE_S, strFile_s);
	//20210902  ��֤�������ֶβ���·����Ϣ
	strDvmFile = GetFileNameFromFilePath(strDvmFile);
	strPpxml = GetFileNameFromFilePath(strPpxml);
	oIotCmd.SetParasDataValueByID(XPARA_ID_PPXMLFILE, strPpxml);
	oIotCmd.SetParasDataValueByID(XPARA_ID_DVMFILE, strDvmFile);

	if (!strFile_s.IsEmpty())
	{
		strFileDownLoad = g_strDvmFilePath + strDvmFile;
		strUrl = strHttpUrlHead + strFile_s;
		CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
	}

	strFile_s.Empty();
	oIotCmd.GetParasDataValueByID(XPARA_ID_PPXMLFILE_S, strFile_s);

	if (!strFile_s.IsEmpty())
	{
		strFileDownLoad = g_strPpxmlFilePath + strPpxml;
		strUrl = strHttpUrlHead + strFile_s;
		CXFileHttpClient::DownloadFile(strUrl, strFileDownLoad);
	}

	//����Ϣ����CIotEngineProtocolServer   CreateIotEngineProtocolServer
	PostMsg_CreateIotEngineProtoSvr(oIotCmd);

	return 1;
}

BOOL CIotEngineServer_Mqtt::CreateIotEngineProtocolServer(CSttIotCmd &oIotCmd)
{
	//����IotEngineProtocolServer�ӿ�
	CString strDeviceSN;
	oIotCmd.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	CIotEngineProtocolServer *pFind = (CIotEngineProtocolServer *)FindByID(strDeviceSN);
	if (pFind != NULL)
	{
		//����װ�ö�Ӧ��IotEngineProtocolServer�Ѿ�������
		//����Ҫȡ��֮ǰ���ĵ����⣬�����µ����⣬��Ϊ�����SN�Ѹı�
		//pFind->ReSubcribeMqttTopic();
		return TRUE;
	}

	//����װ�ö�Ӧ��IotEngineProtocolServerģ�鲻���ڣ��򴴽�����ʼ��

	pFind = new CIotEngineProtocolServer();
	pFind->m_strID = strDeviceSN;
	pFind->SetIotEngineMqttServer(this);
	//pFind->InitTopicSrcInfo(m_strFirstTopic,strDeviceID);//��ʼ������Դ����Ϣ�����ڶ�������

	//��ʼ��IotEngineProtocolServer�ӿ�Mqtt�ͻ���ģ��
	BOOL bRet = pFind->Init(m_strIP,m_nPort, strDeviceSN);

	if(bRet)
	{
		//����Э��ת��ģ���Э�����ģ��
		if (pFind->CreateProtocol(oIotCmd))
		{
			//��IotEngineProtocolServerģ����ӵ��Ӷ���������
			AddNewChild(pFind);
		}
		else
		{
			delete pFind;
			bRet = FALSE;
		}	
	}
	else
	{
		delete pFind;
	}

	return bRet;
}



long CIotEngineServer_Mqtt::OnCloseDevice(CIotEngineProtocolServer *pIotEngineProtocolServer)
{
	//ɾ���Ӷ���IotEngineProtocolServer��
	//ͬʱ��IotEngineProtocolServer����������ɾ��Э��ת��ģ�顾��Э�����ģ�飬��Ա��豸Э�����ģ�顿
//	Delete(pIotEngineProtocolServer);

	if (m_pXCommSvrWnd != NULL)
	{
		m_pXCommSvrWnd->PostMessage(XCOMM_WND_MSG,1,(LPARAM)pIotEngineProtocolServer);	
	}

	return 0;
}

void CIotEngineServer_Mqtt::PostMsg_CreateIotEngineProtoSvr(CSttIotCmd &oIotCmd)
{
	if (m_pXCommSvrWnd != NULL)
	{
		CSttIotCmd *pTempCmd = (CSttIotCmd*)oIotCmd.Clone();
		m_pXCommSvrWnd->PostMessage(XCOMM_WND_MSG,0,(LPARAM)pTempCmd);	
	}
}