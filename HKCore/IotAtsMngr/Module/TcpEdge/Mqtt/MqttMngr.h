#ifndef MQTTMNGR_H
#define MQTTMNGR_H

#include "MQTTClient.h"           
#include "MQTTClientPersistence.h"
#include "MQTTProperties.h"       
#include "../../../../Module/DataMngr/DvmDatasetGroup.h"

class CMqttMngr
{
private:
	MQTTClient m_mqttClient;	

public:
	CMqttMngr();
	virtual ~CMqttMngr();

	bool InitMqttClient(CDvmDatasetGroup* pCfg, QString strID);
	void ExitMqttClient();
	static void OnMqttLost(void* context, char* cause);
	static int OnMqttArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message);
	static void OnMqttComplete(void* context, MQTTClient_deliveryToken dt);
	bool PublicTopic(QString strTopic, QString strData);
	bool SubscribeTopic(QString strTopic);
};

#endif