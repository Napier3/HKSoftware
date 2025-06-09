#pragma once
#include "../SttMqttClientTool.h"
#include "MqttEngineBase.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"

//2021-7-20  lijunqing 定义STT协议中MQTT主题用到的关键字
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

//通信接口
public:
	virtual void OnRecieve(const CString &strFromSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType);
	virtual void OnClose(char *pszErr);
	virtual long Send(const CString &strToSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);
	//根据命令拼主题和数据发送，需要重载
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
	针对Stt协议：
	nCmdType【命令类型】，pszCmdID【命令ID】,pszRetType【应答ret-type】,pszEventID【若是事件，则事件ID,其他情况为NULL】
	针对Edge协议：
	nCmdType【主题类型，倒数第二字段】，pszCmdID【主题命令ID，倒数第一字段】
	,pszRetType【保留，为NULL】,pszEventID【保留为NULL】
	**********************************/
	//2021-8-22  lijunqing 分析增加strFromSN，表示谁发过来的； 产生主题增加strToSN，表示发送给谁
	virtual CString GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID){return _T("");}
	//shaolei 20210805 
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID){return _T("");}
	virtual BOOL AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType){return FALSE;}

	//2021-7-20  lijunqing
	//因为此处已经是MQTT，所以发送的部分，可以就按照MQPTT处理，不一定需要兼容STT部分
	//兼容的部分，就是Send(CExBaseObject *pCmdBase)函数
	virtual long Send(char *pBuf,long nLen, const CString &strTopic);

public:
	CMqttClient m_oMqttClient;
	CMqttEngineBase *m_pTestEngine;

	CString m_strIP;
	long m_nPort;
	CString m_strClientID;

	//2021-8-26  lijunqing   很多地方都用到DeviceID，因此定义到基类，并改为DeviceSN
	CString m_strDeviceSN;

	//2021-8-27  lijunjunqing
	CStringArray m_arrSubTopic;

	CString m_strSrcSN;  //请求端SN。在返回sysState时，定义了临时对象，因此需要记录请求端SN

};