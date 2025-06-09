#pragma once

#ifdef _PSX_QT_LINUX_
#include "SttMqttClient_QT.h"
#else
#include "SttMqttClient.h"
#endif

#include "../../SttStudio/Module/SttCmd/SttCmdBase.h"
#include "DeviceMngr/SttXDevice.h"

class CSttOutInterfaceMqttClient : public CMqttMsgInterface, public CMqttMsgProcessInterfaceMngr
{
private:
	CSttOutInterfaceMqttClient();
	virtual ~CSttOutInterfaceMqttClient();

	static CSttOutInterfaceMqttClient *g_pSttOutInterfaceMqttClient;
	static long g_nSttOutInterfaceMqttClientRef;

public:
	static CSttOutInterfaceMqttClient* Create();
	static void Release();

public:
	virtual void OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser);
	virtual void OnMqttDisconnected(char *pszErr);

public:
	virtual BOOL Connect();
	virtual void Disconnect();
	BOOL IsConnectSuccessful()		{		return m_oMqttClient.IsConnectSuccessful();	}

	virtual BOOL SubcribeMqttTopic(int nQos){return FALSE;}
	virtual BOOL UnSubcribeMqttTopic(){return FALSE;}
	virtual void ReSubcribeMqttTopic();

	BOOL SubscribeTopic(const char* pszTopic,int nQos);
	BOOL UnSubscribeTopic(const char* pszTopic);
	long PublicTopic(char *strTopic, char *pBuf, long nLen);
	long PublicTopic(CSttMqttTopicCmbn &oTopicCmbn);

public:
	CMqttClient m_oMqttClient;

	CString m_strIP;
	long m_nPort;
	CString m_strClientID;

public:

	virtual CSttParas* stt_pst_get_paras(CSttMqttTopicParser &oParser);
	virtual void stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttParas &oSttParas);

	virtual void stt_mqtt_GetParasBuffer(CSttParas &oParas, CSttMqttTopicCmbn &oTopicCmbn);
	virtual void stt_mqtt_GetParasBuffer(CDataGroup *pDataGroup, CSttMqttTopicCmbn &oTopicCmbn);

	//评测项目需要转换成JSON格式的报文结构 —— chenxinan 2022.12.14
	virtual void stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttCmdBase &oSttTestCmd, const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual void stt_mqtt_GetParasBuffer(CSttCmdBase &oCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType = _PUGI_XML_TYPE_);
};

//全局唯一的自动测试外部调用的接口，例如：测试仪控制、通信引擎服务等
extern CSttOutInterfaceMqttClient *g_theSttOutMqttClient;

//2023-6-9 lijunqing 
void stt_mqtt_GetParasBuffer(CSttCmdBase *pCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType = _PUGI_XML_TYPE_);
