#include "stdafx.h"
#include "SttAtsSvrMqttClient.h"
#include "../../SttStudio/Module/SttRegisterCode.h"
#include "../../Module/System/StringTokenizer.h"

CSttAtsSvrMqttClient::CSttAtsSvrMqttClient()
{

}

CSttAtsSvrMqttClient::~CSttAtsSvrMqttClient()
{

}

BOOL CSttAtsSvrMqttClient::Connect(const char *pszIP,long nPort)
{
	SYSTEMTIME tm;
	GetLocalTime(&tm);

	CString strClientID;
	strClientID.Format(_T("SttProtoSvr_%d_%02d%02d"),stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond);

	Init(pszIP,nPort,strClientID);
	BOOL bRet = ConnectServer();

	if (bRet)
	{
		//连接成功后，主动订阅主题
		SubcribeMqttTopic(0);
	}

	return bRet;
}

/************************
测试仪主题：
请求端SN/规约引擎边服务ID/IotCmd/CreateDevice
**************************/
BOOL CSttAtsSvrMqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	m_oMqttClient.SubscribeTopic(_T("+/+/IotCmd/CreateDevice"),nQos);
	return TRUE;
}

/*
请求端SN/规约引擎边服务ID/IotState/CreateDevice/Reply
*/
CString CSttAtsSvrMqttClient::GenerateTopic(long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;

	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		strTopic.Format(_T("%s/%s/IotState/%s/%s"),m_strSrcID,m_strCurProtocolSrvID,pszCmdID,pszRetType);
	}
	else
	{
		strTopic.Format(_T("%s/%s/IotCmd/%s"),m_strSrcID,m_strCurProtocolSrvID,pszCmdID);
	}

	return strTopic;
}

/************************
测试仪主题：
请求端SN/规约引擎边服务ID/IotCmd/CreateDevice

根据解析主题生成cmdType,cmdID,retType
**************************/
BOOL CSttAtsSvrMqttClient::AnalysisTopic(const CString &strTopic,long &nCmdType, char **ppszCmdID, char **ppszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() != 4)
	{
		return FALSE;
	}

	m_strSrcID = oToken.GetToken(0);
	m_strCurProtocolSrvID = oToken.GetToken(1);
	m_pTestEngine->InitTopicSrcInfo(m_strSrcID,m_strCurProtocolSrvID);

	nCmdType = STT_CMD_TYPE_IOT;
	*ppszCmdID = (char *)oToken.GetToken(4);
	*ppszRetType = NULL;

	return TRUE;
}