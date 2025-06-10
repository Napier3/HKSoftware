#pragma once

#include "../../../IotAtsMngr/Module/SttMqttClient_QT.h"
#include "../../../IotAtsMngr/Module/DeviceMngr/SttXDevice.h"
#include "../../../Module/SttCmd/SttTestCmd.h"

class CSttMqttEngineBase:public CMqttMsgInterface
{
public:
	CSttMqttEngineBase();
	virtual ~CSttMqttEngineBase();

public:
	virtual void OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser);
	virtual void OnMqttDisconnected(char *pszErr);
	virtual CString GetIotClientID()	{	return _T("TestServer");	}

	//主题处理
	virtual void OnRegister(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnUnRegister(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnQueryDevice(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnQueryFile(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnCreateTest(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnCloseTest(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnStartTest(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnStopTest(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnConfigDevice(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnRecordSend(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnRecordStopSend(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnRecordBegin(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnRecordFinish(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnRecordCancel(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnRecordData(CSttMqttTopicParser &oSttMqttTopicParser){}
	virtual void OnRecordCall(CSttMqttTopicParser &oSttMqttTopicParser){}

public:
	virtual BOOL Connect(const CString &strIP,long nPort, const CString &strClientIDKey,const CString &strUser,const CString &strPwd,BOOL bAuthority = FALSE);
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
	CString m_strTopicHeart;
	CSttMqttTopicCmbn m_oTopicHeartCmbn;	
};

extern CSttXDevice g_oTheOwnIotDevice;

CSttParas* stt_mqtt_get_paras(CSttMqttTopicParser &oParser);
void stt_mqtt_get_paras(CSttMqttTopicParser &oParser, CSttParas &oSttParas);

void stt_mqtt_GetParasBuffer(CSttParas &oParas, CSttMqttTopicCmbn &oTopicCmbn);
void stt_mqtt_GetParasBuffer(CDataGroup *pDataGroup, CSttMqttTopicCmbn &oTopicCmbn);

//评测项目需要转换成JSON格式的报文结构 —— chenxinan 2022.12.14
void stt_mqtt_get_paras(CSttMqttTopicParser &oParser, CSttTestCmd &oSttTestCmd, const long &nXmlRWType = _PUGI_XML_TYPE_);
void stt_mqtt_GetParasBuffer(CSttTestCmd &oCmd, CSttMqttTopicCmbn &oTopicCmbn, const long &nXmlRWType = _PUGI_XML_TYPE_);

//初始化，第一个子主题为当前设备SN，pDestDevice为目标主题
void stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, CSttXDevice *pDestDevice=NULL);

//初始化，第一个子主题为当前设备SN，pDestDevice为目标主题；pszSttCmdID、pszSttCmdID2为一次的命令主题
void stt_mqtt_InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, const char *pszSttCmdID, const char *pszSttCmdID2=NULL, CSttXDevice *pDestDevice=NULL);

