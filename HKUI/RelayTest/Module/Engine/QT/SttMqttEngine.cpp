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

void CSttMqttEngine::OnMqttConnected()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("连接云平台成功"));
}

void CSttMqttEngine::ConnectMqttSvr(CString strIP,long nPort,const CString &strUser,const CString &strPwd,BOOL bAuthority)
{
	m_strTopicHeart = g_oTheOwnIotDevice.GetSN() + "/HeartBeat";
	m_oMqttClient.m_pTopicHeart = (char *)m_strTopicHeart.GetString();

	Connect(strIP, nPort, GetIotClientID(), strUser, strPwd, bAuthority);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("连接云平台[%s] [%d]"), strIP.GetString(), nPort);
}

void CSttMqttEngine::OnTimer()
{
	m_oMqttClient.SendHeart();
}

void CSttMqttEngine::OnStartTest(CSttMqttTopicParser &oSttMqttTopicParser)
{

}

void CSttMqttEngine::OnStopTest(CSttMqttTopicParser &oSttMqttTopicParser)
{

}
