#include "stdafx.h"
#include "MqttMngr.h"
#include "../TcpEdgeGlobalDef.h"
#include "../../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../../Module/API/GlobalConfigApi.h"

CMqttMngr::CMqttMngr()
{
	m_mqttClient = NULL;
}

CMqttMngr::~CMqttMngr()
{

}

bool CMqttMngr::InitMqttClient(CDvmDatasetGroup* pCfg, QString strID)
{
	QString strIP;
	long nPort = 0;
	QString strConfigFile = _P_GetConfigPath();
	strConfigFile += "TcpEdgeServerCfg.xml";

	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	pCfg->OpenXmlFile(strConfigFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	//����IP��ʷ��¼
	CDvmDatasetGroup* pAPIGroup = (CDvmDatasetGroup*)pCfg->FindByID(Cfg_RemoteAPI);
	if(pAPIGroup)
	{
		CDvmData* pIP = (CDvmData*)pAPIGroup->FindByID(Cfg_RemoteIp);
		if(pIP)
		{
			strIP = pIP->m_strValue;
			CDvmData* pPort = (CDvmData*)pAPIGroup->FindByID(Cfg_RemotePort);
			if(pPort)
			{
				nPort = CString_To_long(pPort->m_strValue);
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	//����MQTT����
	if(m_mqttClient)
	{
		MQTTClient_destroy(&m_mqttClient);
		m_mqttClient = NULL;
	}

	QString strUrl = QString("tcp://%1:%2").arg(strIP).arg(nPort);
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_create(&m_mqttClient, strUrl.toStdString().c_str(), strID.toStdString().c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL);
	conn_opts.keepAliveInterval = 120;
	conn_opts.cleansession = 1;
	conn_opts.connectTimeout = 5;
	MQTTClient_setCallbacks(m_mqttClient, NULL, &OnMqttLost, &OnMqttArrived, &OnMqttComplete);
	int nRet = MQTTClient_connect(m_mqttClient, &conn_opts);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		return false;
	}

	//�������ӳɹ���ı�������
	//...
	return true;
}

void CMqttMngr::ExitMqttClient()
{
	MQTTClient_disconnect(m_mqttClient, 2000);
	MQTTClient_destroy(&m_mqttClient);
}

void CMqttMngr::OnMqttLost(void* context, char* cause)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Զ�̽ӿ��Ѷ���!"));
}

int CMqttMngr::OnMqttArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message)
{
	//��ת������MQTT��Ϣ
	//...
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 0;
}

void CMqttMngr::OnMqttComplete(void* context, MQTTClient_deliveryToken dt)
{

}

bool CMqttMngr::PublicTopic(QString strTopic, QString strData)
{
	long nQos = 0;
	long nTimeout = 2000;
	MQTTClient_message pubmsg = MQTTClient_message_initializer;
	MQTTClient_deliveryToken token = 0;
	pubmsg.payload = (void*)strData.toStdString().c_str();
	pubmsg.payloadlen = strData.length();
	pubmsg.qos = nQos;
	pubmsg.retained = 0;
	long nRet = MQTTClient_publishMessage(m_mqttClient, strTopic.toStdString().c_str(), &pubmsg, &token);
	if (MQTTCLIENT_SUCCESS != nRet)
	{
		return false;
	}
	return true;
}

bool CMqttMngr::SubscribeTopic(QString strTopic)
{
	long nQos = 0;
	long nRet = MQTTClient_subscribe(m_mqttClient, strTopic.toStdString().c_str(), nQos);
	if (nRet != MQTTCLIENT_SUCCESS)
	{
		return false;
	}
	return true;
}
