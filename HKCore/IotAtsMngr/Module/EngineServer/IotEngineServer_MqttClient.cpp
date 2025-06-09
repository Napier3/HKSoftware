#include "stdafx.h"
#include "IotEngineServer_MqttClient.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"

CIotEngineServer_MqttClient::CIotEngineServer_MqttClient()
{

}

CIotEngineServer_MqttClient::~CIotEngineServer_MqttClient()
{

}

// BOOL CIotEngineServer_MqttClient::Connect(const char *pszIP,long nPort)
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 
// 	//保证ClientID唯一
// 	CString strClientID;
// 	strClientID.Format(_T("SttProtoSvr_%u_%02d%02d%03d")
// 		,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
// 
// 	Init(pszIP,nPort,strClientID);
// 	BOOL bRet = ConnectServer();
// 
// 	if (bRet)
// 	{
// 		//连接成功后，主动订阅主题
// 		SubcribeMqttTopic(0);
// 	}
// 
// 	return bRet;
// }

/************************
测试仪主题：
请求端SN/规约引擎边服务ID/IotCmd/CreateDevice
**************************/
BOOL CIotEngineServer_MqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	m_oMqttClient.SubscribeTopic(_T("+/+/IotCmd/CreateDevice"),nQos);
	return TRUE;
}

/*
请求端SN/规约引擎边服务ID/IotState/CreateDevice/REPLY
*/
CString CIotEngineServer_MqttClient::GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;
// 	CString strSrcSN;
// 
// 	if (strToSN.IsEmpty())
// 	{
// 		strSrcSN = m_strSrcID;
// 	}
// 	else
// 	{
// 		strSrcSN = strToSN;
// 	}

	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		strTopic.Format(_T("%s/%s/IotState/%s/%s"),strToSN,m_strCurProtocolSrvID,pszCmdID,pszRetType);
	}
	else
	{
		strTopic.Format(_T("%s/%s/IotCmd/%s"),strToSN,m_strCurProtocolSrvID,pszCmdID);
	}

	return strTopic;
}

/************************
测试仪主题：
请求端SN/规约引擎边服务ID/IotCmd/CreateDevice

根据解析主题生成cmdType,cmdID,retType
**************************/
BOOL CIotEngineServer_MqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() != 4)
	{
		return FALSE;
	}

	strFromSN = oToken.GetToken(0);
	m_strSrcID = strFromSN;
	m_strCurProtocolSrvID = oToken.GetToken(1);
	//m_pTestEngine->InitTopicSrcInfo(m_strSrcID,m_strCurProtocolSrvID);

	nCmdType = STT_CMD_TYPE_IOT;
	char *pTemp = (char *)oToken.GetToken(3);
	memcpy(pszCmdID,pTemp,strlen(pTemp));

	return TRUE;
}