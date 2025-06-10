#include "stdafx.h"
#include "SttMqttEngine.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 


CSttMqttEngine::CSttMqttEngine()
{

}

CSttMqttEngine::~CSttMqttEngine()
{

}

void CSttMqttEngine::PublicTopic(CSttMqttTopicCmbn &oTopicCmbn, CSttParas &oParas)
{
	stt_mqtt_GetParasBuffer(oParas, oTopicCmbn);
	CSttMqttEngineBase::PublicTopic(oTopicCmbn);
}

void CSttMqttEngine::PublicTopic2(CSttMqttTopicCmbn &oTopicCmbn, CSttParas &oParas)
{
	stt_mqtt_GetParasBuffer(oParas, oTopicCmbn);
	CSttMqttEngineBase::PublicTopic(oTopicCmbn.GetTopic2(), oTopicCmbn.m_pszBuffer, oTopicCmbn.m_nBufferLength);
}

void CSttMqttEngine::ConnectMqttSvr(CString strIP,long nPort,const CString &strUser,const CString &strPwd,BOOL bAuthority)
{
	m_strTopicHeart = g_oTheOwnIotDevice.GetSN() + "/HeartBeat";
	m_oMqttClient.m_pTopic = (char *)m_strTopicHeart.GetString();

	MQTT::Message message;
	message.qos = MQTT::QOS0;
	message.retained = false;
	message.dup = false;
	message.payload = m_oTopicHeartCmbn.m_pszBuffer;
	message.payloadlen = m_oTopicHeartCmbn.m_nBufferLength;
	m_oMqttClient.m_oMqttSendBuff = message;

	BOOL bRet = Connect(strIP, nPort, GetIotClientID(), strUser, strPwd, bAuthority);

	if (bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("连接云平台[%s] [%d] 成功"), strIP.GetString(), nPort);

		// Register();
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("连接云平台[%s] [%d] 失败"), strIP.GetString(), nPort);
	}
}

void CSttMqttEngine::OnStartTest(CSttMqttTopicParser &oSttMqttTopicParser)
{

}

void CSttMqttEngine::OnStopTest(CSttMqttTopicParser &oSttMqttTopicParser)
{

}
