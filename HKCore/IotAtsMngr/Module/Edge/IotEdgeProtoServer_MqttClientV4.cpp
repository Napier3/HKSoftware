#include "stdafx.h"
#include "IotEdgeProtoServer_MqttClientV4.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEdgeProtoServer_MqttClientV4::CIotEdgeProtoServer_MqttClientV4()
{

}

CIotEdgeProtoServer_MqttClientV4::~CIotEdgeProtoServer_MqttClientV4()
{

}

// BOOL CIotEdgeProtoServer_MqttClientV4::Connect(const char *pszIP,long nPort)
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 
// 	CString strClientID;
// 	strClientID.Format(_T("EdgeProtoSvrExV4_%u_%02d%02d%03d")
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
订阅主题：DeviceID
/v1/${edgeId}/device/request
**************************/
BOOL CIotEdgeProtoServer_MqttClientV4::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	CString strTopic;
	strTopic.Format(_T("/v1/%s/device/reply"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/device/data"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/device/request"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	strTopic.Format(_T("/v1/%s/topo/request"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	strTopic.Format(_T("/v1/%s/app/reply"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/app/data"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/app/response"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	strTopic.Format(_T("/v1/%s/container/reply"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/container/data"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/container/response"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	strTopic.Format(_T("/v1/%s/service/reply"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/service/data"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/service/event"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	strTopic.Format(_T("/v1/%s/service/file"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);
	return TRUE;
}

/*
/v1/${edgeId}/device/request
/v1/${edgeId}/device/response
*/
CString CIotEdgeProtoServer_MqttClientV4::GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;

// 	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
// 	{
// 		strTopic.Format(_T("%s/%s/XML/IotState/%s/%s"),m_strSrcID,m_strCurProtocolSrvID,pszCmdID,pszRetType);
// 	}
// 	else
// 	{
// 		strTopic.Format(_T("%s/%s/XML/IotCmd/%s"),m_strSrcID,m_strCurProtocolSrvID,pszCmdID);
// 	}

	return strTopic;
}

/************************
测试仪主题：
请求端SN/规约引擎边服务ID/XML/IotCmd/CreateDevice

/v1/edgeId/server/reply?

根据解析主题生成cmdType,cmdID,retType
**************************/
BOOL CIotEdgeProtoServer_MqttClientV4::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	if(strTopic.GetAt(0) == '/')
		oToken.Init(strTopic.Mid(1), '/');
	else
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() != 4)
	{
		return FALSE;
	}

	CString strDeviceID;
	strDeviceID = oToken.GetToken(1);	
	nCmdType = edge_CmdTypeID_Str_To_Idx(oToken.GetToken(2));
	char *pTemp = (char *)oToken.GetToken(3);
	memcpy(pszCmdID,pTemp,strlen(pTemp));
	return TRUE;
}