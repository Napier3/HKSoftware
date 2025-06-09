#pragma once
#include "../SttMqttClientTool.h"
#include "MqttEngineBase.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"

//2021-7-20  lijunqing ����STTЭ����MQTT�����õ��Ĺؼ���
#define STT_MQTTTOPIC_KEY_TestCmd     _T("TestCmd")
#define STT_MQTTTOPIC_KEY_TestState    _T("TestState")
#define STT_MQTTTOPIC_KEY_AtsCmd       _T("AtsCmd")
#define STT_MQTTTOPIC_KEY_AtsState       _T("AtsState")
#define STT_MQTTTOPIC_KEY_IotCmd        _T("IotCmd")
#define STT_MQTTTOPIC_KEY_IotState       _T("IotState")

inline long mqtt_cmd_to_stt_cmd_id(const CString &strMqttCmd)
{
	if (strMqttCmd == STT_MQTTTOPIC_KEY_TestCmd)
	{
		return STT_CMD_TYPE_TEST;
	}

	if (strMqttCmd == STT_MQTTTOPIC_KEY_AtsCmd)
	{
		return STT_CMD_TYPE_ATS;
	}

	if (strMqttCmd == STT_MQTTTOPIC_KEY_IotCmd)
	{
		return STT_CMD_TYPE_IOT;
	}


	if (strMqttCmd == STT_MQTTTOPIC_KEY_TestState
		|| strMqttCmd == STT_MQTTTOPIC_KEY_AtsState
		|| strMqttCmd == STT_MQTTTOPIC_KEY_IotState)
	{
		return STT_CMD_TYPE_SYSSTATE;
	}

	return -1;
}

class CMqttClientToPxEngine:public CMqttMsgInterface,public CSttCmmMsgInterface,public CSttCmmOptrInterface
{
public:
	CMqttClientToPxEngine();
	virtual ~CMqttClientToPxEngine();

	//2021-7-19  lijunqing
	BOOL IsConnectSuccessful()		{		return m_oMqttClient.IsConnectSuccessful();	}

//ͨ�Žӿ�
public:
	virtual void OnRecieve(const CString &strFromSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
	virtual void OnClose(char *pszErr);
	virtual long Send(const CString &strToSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	//��������ƴ��������ݷ��ͣ���Ҫ����
	virtual long Send(CExBaseObject *pCmdBase)=0;
	virtual BOOL Connect(const char *pszIP,long nPort, const char *pszClientIDKey);
	virtual void Disconnect();

	virtual void OnMqttDisconnected(char *pszErr);
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	virtual void OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser);

	//void Init(const CString &strIP,long nPort,const CString &strClientID);
	virtual BOOL ConnectServer();
	void SetMqttEngineRef(CMqttEngineBase *pEngine);

	virtual BOOL SubcribeMqttTopic(int nQos){return FALSE;}
	virtual void ReSubcribeMqttTopic();

	/**********************************
	���SttЭ�飺
	nCmdType���������͡���pszCmdID������ID��,pszRetType��Ӧ��ret-type��,pszEventID�������¼������¼�ID,�������ΪNULL��
	���EdgeЭ�飺
	nCmdType���������ͣ������ڶ��ֶΡ���pszCmdID����������ID��������һ�ֶΡ�
	,pszRetType��������ΪNULL��,pszEventID������ΪNULL��
	**********************************/
	//2021-8-22  lijunqing ��������strFromSN����ʾ˭�������ģ� ������������strToSN����ʾ���͸�˭
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID){return _T("");}
	//shaolei 20210805 
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID){return _T("");}
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType){return FALSE;}

	//2021-7-20  lijunqing
	//��Ϊ�˴��Ѿ���MQTT�����Է��͵Ĳ��֣����ԾͰ���MQPTT������һ����Ҫ����STT����
	//���ݵĲ��֣�����Send(CExBaseObject *pCmdBase)����
	virtual long Send(char *pBuf,long nLen, const CString &strTopic);

public:
	CMqttClient m_oMqttClient;
	CMqttEngineBase *m_pTestEngine;

	CString m_strIP;
	long m_nPort;
	CString m_strClientID;

	//2021-8-26  lijunqing   �ܶ�ط����õ�DeviceID����˶��嵽���࣬����ΪDeviceSN
	CString m_strDeviceSN;

	//2021-8-27  lijunjunqing
	CStringArray m_arrSubTopic;

	CString m_strSrcSN;  //�����SN���ڷ���sysStateʱ����������ʱ���������Ҫ��¼�����SN

};