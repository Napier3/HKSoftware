#pragma once

#ifdef _PSX_QT_LINUX_
#include "../../../IotAtsMngr/Module/SttMqttClient_QT.h"
#else
#include "../../../IotAtsMngr/Module/SttMqttClient.h"
#endif

#include "../SttCmd/SttTestCmd.h"
#include "../../../IotAtsMngr/Module/DeviceMngr/SttXDevice.h"

class CAtsOutInterfaceMqttClient : public CMqttMsgInterface, public CMqttMsgProcessInterfaceMngr
{
private:
	CAtsOutInterfaceMqttClient();
	virtual ~CAtsOutInterfaceMqttClient();

	static CAtsOutInterfaceMqttClient *g_pAtsOutInterfaceMqttClient;
	static long g_nAtsOutInterfaceMqttClientRef;

public:
	static CAtsOutInterfaceMqttClient* Create(const CString &strSN);
	static void Release();

public:
	virtual void OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser);
	virtual void OnMqttDisconnected(char *pszErr);

public:
	virtual BOOL Connect(const CString &strSN);
	virtual void Disconnect();
	BOOL IsConnectSuccessful()		{		return m_oMqttClient.IsConnectSuccessful();	}

	virtual BOOL SubcribeMqttTopic(int nQos){return FALSE;}
	virtual BOOL UnSubcribeMqttTopic(){return FALSE;}
	virtual void ReSubcribeMqttTopic();

	BOOL SubscribeTopic(const CString &strTopic,int nQos);
	BOOL UnSubscribeTopic(const CString &strTopic);
	BOOL SubscribeTopic(const char* pszTopic,int nQos);
	BOOL UnSubscribeTopic(const char* pszTopic);
	long PublicTopic(char *strTopic, char *pBuf, long nLen);
	long PublicTopic(CSttMqttTopicCmbn &oTopicCmbn);

public:
	CMqttClient m_oMqttClient;

	CString m_strIP;
	long m_nPort;
	CString m_strClientID;

	CSttXDevice m_oAtsIotDevice;

public:

	virtual CSttParas* stt_pst_get_paras(CSttMqttTopicParser &oParser);
	virtual void stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttParas &oSttParas);

	virtual void stt_mqtt_GetParasBuffer(CSttParas &oParas, CSttMqttTopicCmbn &oTopicCmbn);
	virtual void stt_mqtt_GetParasBuffer(CDataGroup *pDataGroup, CSttMqttTopicCmbn &oTopicCmbn);

	//������Ŀ��Ҫת����JSON��ʽ�ı��Ľṹ ���� chenxinan 2022.12.14
	virtual void stt_pst_get_paras(CSttMqttTopicParser &oParser, CSttTestCmd &oSttTestCmd, const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual void stt_mqtt_GetParasBuffer(CSttTestCmd &oCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType = _PUGI_XML_TYPE_);

	//��ʼ������һ��������Ϊ��ǰ�豸SN��pDestDeviceΪĿ������
	virtual void stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, CSttXDevice *pDestDevice=NULL);

	//��ʼ������һ��������Ϊ��ǰ�豸SN��pDestDeviceΪĿ�����⣻pszSttCmdID��pszSttCmdID2Ϊһ�ε���������
	virtual void stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, const char *pszSttCmdID, const char *pszSttCmdID2=NULL, CSttXDevice *pDestDevice=NULL);


};

//��ǰ���Զ˶���
extern CSttXDevice *g_pTheOwnIotDevice;

//ȫ��Ψһ���Զ������ⲿ���õĽӿڣ����磺�����ǿ��ơ�ͨ����������
extern CAtsOutInterfaceMqttClient *g_theAtsOutMqttClient;

//2023-6-9 lijunqing 
void stt_mqtt_GetParasBuffer(CSttCmdBase *pCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType = _PUGI_XML_TYPE_);
