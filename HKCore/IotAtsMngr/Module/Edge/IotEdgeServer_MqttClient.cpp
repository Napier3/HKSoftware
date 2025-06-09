#include "stdafx.h"
#include "IotEdgeServer_MqttClient.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEdgeServer_MqttClient::CIotEdgeServer_MqttClient()
{

}

CIotEdgeServer_MqttClient::~CIotEdgeServer_MqttClient()
{

}

// BOOL CIotEdgeServer_MqttClient::Connect(const char *pszIP,long nPort)
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 
// 	CString strClientID;
// 	strClientID.Format(_T("EdgeProtoSvr_%u_%02d%02d%03d")
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
订阅主题：请求接入、主动断开
/v1/{edgeId}/device/request
/v1/{edgeId}/device/data
**************************/
BOOL CIotEdgeServer_MqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	m_oMqttClient.SubscribeTopic(_T("/+/+/device/request"),nQos);
	m_oMqttClient.SubscribeTopic(_T("/+/+/device/data"),nQos);
	return TRUE;
}