#include "stdafx.h"
#include "SttProtoClientMqttClient.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"

CSttProtoClientMqttClient::CSttProtoClientMqttClient()
{

}

CSttProtoClientMqttClient::~CSttProtoClientMqttClient()
{

}

// BOOL CSttProtoClientMqttClient::Connect(const char *pszIP,long nPort)
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 
// 	CString strClientID;
// 	strClientID.Format(_T("SttProtoClient_%u_%02d%02d%03d")
// 		,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
// 
// 	m_strSrcID = strClientID;	//请求端SN
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
主题：
请求端SN/DeviceID/IotState/PkgParse/REPLY
请求端SN/DeviceID/IotState/PkgProduce/REPLY
请求端SN/DeviceID/IotState/RunProcedure/REPLY
请求端SN/DeviceID/IotState/GetDataset/REPLY
请求端SN/DeviceID/IotState/ConfigDevice/REPLY
请求端SN/DeviceID/IotState/CloseDevice/REPLY

请求端SN/DeviceID/IotState/RunProcedure/EVENT/事件ID
请求端SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed
**************************/
BOOL CSttProtoClientMqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	CString strTopic1,strTopic2,strTopic3;
	strTopic1.Format(_T("%s/%s/IotState/#"),m_strClientID,m_strDeviceID);

	m_oMqttClient.SubscribeTopic(strTopic1,nQos);
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
CString CSttProtoClientMqttClient::GenerateTopic(long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;

	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		if (!strcmp(pszRetType,SYS_STATE_RETTYPE_EVENT))
		{//如果是事件
			strTopic.Format(_T("%s/%s/IotState/%s/%s/%s"),m_strClientID,m_strDeviceID
				,pszCmdID,pszRetType,pszEventID);
		}
		else
		{//reply
			strTopic.Format(_T("%s/%s/IotState/%s/%s"),m_strClientID,m_strDeviceID,pszCmdID,pszRetType);
		}	
	}
	else
	{
		strTopic.Format(_T("%s/%s/IotCmd/%s"),m_strClientID,m_strDeviceID,pszCmdID);
	}

	return strTopic;
}

//请求端SN/DeviceID/IotCmd/RunProcedure
CString CSttProtoClientMqttClient::GenerateTopic(CSttIotCmd *pIotCmd)
{
	CString strTopic;
	strTopic.Format(_T("%s/%s/IotCmd/%s"),m_strClientID,m_strDeviceID,pIotCmd->m_strID);
	return strTopic;
}
/************************
收到主题解析
请求端SN/DeviceID/IotState/PkgParse/REPLY
请求端SN/DeviceID/IotState/PkgProduce/REPLY
请求端SN/DeviceID/IotState/RunProcedure/REPLY
请求端SN/DeviceID/IotState/GetDataset/REPLY
请求端SN/DeviceID/IotState/ConfigDevice/REPLY
请求端SN/DeviceID/IotState/CloseDevice/REPLY

请求端SN/DeviceID/IotState/RunProcedure/EVENT/事件ID
请求端SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed

根据解析主题生成cmdType,cmdID,retType
**************************/
BOOL CSttProtoClientMqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{//说明：如果是事件时，ppszCmdID解析为EventID
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');
	long nStringsCnt = oToken.GetStringsCount();

	char *pTemp = NULL;
	pTemp = (char *)oToken.GetToken(0);
	strFromSN = pTemp;

	if (nStringsCnt == 5)
	{//REPLY
		nCmdType = STT_CMD_TYPE_SYSSTATE;
		pTemp = (char *)oToken.GetToken(3);
		memcpy(pszCmdID,pTemp,strlen(pTemp));
		pTemp = (char *)oToken.GetToken(4);
		memcpy(pszRetType,pTemp,strlen(pTemp));
		return TRUE;
	}
	else if (nStringsCnt == 6)
	{
		nCmdType = STT_CMD_TYPE_SYSSTATE;
		pTemp = (char *)oToken.GetToken(5);		//解析为EventID
		memcpy(pszCmdID,pTemp,strlen(pTemp));
		pTemp = (char *)oToken.GetToken(4);
		memcpy(pszRetType,pTemp,strlen(pTemp));
		return TRUE;
	}
	//yzj 2021-10-5 
	else if (nStringsCnt == 4)
	{
		//是UpdateDataset
		nCmdType = STT_CMD_TYPE_SYSSTATE;
		pTemp = (char *)oToken.GetToken(3);
		memcpy(pszCmdID,pTemp,strlen(pTemp));
		return TRUE;
	}
	return FALSE;
}

void CSttProtoClientMqttClient::InitTopicSrcInfo(const CString &strFirst,const CString &strSecond)
{
//	m_strSrcID = strFirst;
	m_strDeviceID = strSecond;
}