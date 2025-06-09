#include "stdafx.h"
#include "IotEngineProtoServer_MqttClient.h"
#include "../../../Module/System/StringTokenizer.h"

CIotEngineProtoServer_MqttClient::CIotEngineProtoServer_MqttClient()
{

}

CIotEngineProtoServer_MqttClient::~CIotEngineProtoServer_MqttClient()
{

}

// BOOL CIotEngineProtoServer_MqttClient::Connect(const char *pszIP,long nPort)
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 
// 	CString strClientID;
// 	strClientID.Format(_T("SttProtoSvrEx_%u_%02d%02d%03d")
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
请求端SN/DeviceID/IotCmd/PkgParse
请求端SN/DeviceID/IotCmd/PkgProduce
请求端SN/DeviceID/IotCmd/RunProcedure
请求端SN/DeviceID/IotCmd/GetDataset
请求端SN/DeviceID/IotCmd/ConfigDevice
请求端SN/DeviceID/IotCmd/CloseDevice
**************************/
BOOL CIotEngineProtoServer_MqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	CString strTopic;
	//2021-8-22  lijunqing  
	//strTopic.Format(_T("%s/%s/IotCmd/+"),m_strSrcID,m_strDeviceSN);
	strTopic.Format(_T("+/%s/IotCmd/+"),m_strDeviceSN);

	//保存订阅的主题
	m_arrSubTopic.Add(strTopic);

	m_oMqttClient.SubscribeTopic(strTopic,nQos);
	return TRUE;
}

/*
请求端SN/DeviceID/IotCmd/PkgParse
请求端SN/DeviceID/IotState/ PkgParse/REPLY

请求端SN/DeviceID/IotCmd/PkgProduce
请求端SN/DeviceID/IotState /PkgProduce/REPLY

请求端SN/DeviceID/IotCmd/RunProcedure
请求端SN/DeviceID/IotState/ RunProcedure /REPLY
请求端SN/DeviceID/IotState/ RunProcedure /EVENT/事件ID

请求端SN/DeviceID/IotCmd/GetDataset
请求端SN/DeviceID/IotState/GetDataset/REPLY

请求端SN/DeviceID/IotCmd/ConfigDevice
请求端SN/DeviceID/IotState/ConfigDevice/REPLY

请求端SN/DeviceID/IotCmd/CloseDevice
请求端SN/DeviceID/IotState/CloseDevice/REPLY
请求端SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed
*/
CString CIotEngineProtoServer_MqttClient::GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;
 	CString strSrcSN;
 
 	if (strToSN.IsEmpty())
 	{
 		strSrcSN = m_strSrcSN;
 	}
 	else
 	{
 		strSrcSN = strToSN;
 	}

	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		if (!strcmp(pszRetType,SYS_STATE_RETTYPE_EVENT))
		{//如果是事件
			strTopic.Format(_T("%s/%s/IotState/%s/%s/%s"),strSrcSN,m_strDeviceSN
				,pszCmdID,pszRetType,pszEventID);
		}
		else
		{//reply
			strTopic.Format(_T("%s/%s/IotState/%s/%s"),strSrcSN,m_strDeviceSN,pszCmdID,pszRetType);
		}	
	}
	else
	{
		strTopic.Format(_T("%s/%s/IotCmd/%s"),strSrcSN,m_strDeviceSN,pszCmdID);
	}

	return strTopic;
}

/************************
收到主题解析
请求端SN/DeviceID/IotCmd/PkgParse
请求端SN/DeviceID/IotCmd/PkgProduce
请求端SN/DeviceID/IotCmd/RunProcedure
请求端SN/DeviceID/IotCmd/GetDataset
请求端SN/DeviceID/IotCmd/ConfigDevice
请求端SN/DeviceID/IotCmd/CloseDevice

根据解析主题生成cmdType,cmdID,retType
**************************/
BOOL CIotEngineProtoServer_MqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() != 4)
	{
		return FALSE;
	}

	strFromSN = oToken.GetToken(0);
	m_strSrcSN = strFromSN;

	nCmdType = STT_CMD_TYPE_IOT;
	char *pTemp = (char *)oToken.GetToken(3);
	memcpy(pszCmdID,pTemp,strlen(pTemp));

	return TRUE;
}
