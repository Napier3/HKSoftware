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
// 	m_strSrcID = strClientID;	//�����SN
// 
// 	Init(pszIP,nPort,strClientID);
// 	BOOL bRet = ConnectServer();
// 
// 	if (bRet)
// 	{
// 		//���ӳɹ���������������
// 		SubcribeMqttTopic(0);
// 	}
// 
// 	return bRet;
// }

/************************
���⣺
�����SN/DeviceID/IotState/PkgParse/REPLY
�����SN/DeviceID/IotState/PkgProduce/REPLY
�����SN/DeviceID/IotState/RunProcedure/REPLY
�����SN/DeviceID/IotState/GetDataset/REPLY
�����SN/DeviceID/IotState/ConfigDevice/REPLY
�����SN/DeviceID/IotState/CloseDevice/REPLY

�����SN/DeviceID/IotState/RunProcedure/EVENT/�¼�ID
�����SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed
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
�����SN/DeviceID/IotCmd/PkgParse
�����SN/DeviceID/IotState/ PkgParse/REPLY

�����SN/DeviceID/IotCmd/PkgProduce
�����SN/DeviceID/IotState /PkgProduce/REPLY

�����SN/DeviceID/IotCmd/RunProcedure
�����SN/DeviceID/IotState/ RunProcedure /REPLY
�����SN/DeviceID/IotState/ RunProcedure /EVENT/�¼�ID

�����SN/DeviceID/IotCmd/GetDataset
�����SN/DeviceID/IotState/GetDataset/REPLY

�����SN/DeviceID/IotCmd/ConfigDevice
�����SN/DeviceID/IotState/ConfigDevice/REPLY

�����SN/DeviceID/IotCmd/CloseDevice
�����SN/DeviceID/IotState/CloseDevice/REPLY
�����SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed
*/
CString CSttProtoClientMqttClient::GenerateTopic(long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic;

	if (nCmdType == STT_CMD_TYPE_SYSSTATE)
	{
		if (!strcmp(pszRetType,SYS_STATE_RETTYPE_EVENT))
		{//������¼�
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

//�����SN/DeviceID/IotCmd/RunProcedure
CString CSttProtoClientMqttClient::GenerateTopic(CSttIotCmd *pIotCmd)
{
	CString strTopic;
	strTopic.Format(_T("%s/%s/IotCmd/%s"),m_strClientID,m_strDeviceID,pIotCmd->m_strID);
	return strTopic;
}
/************************
�յ��������
�����SN/DeviceID/IotState/PkgParse/REPLY
�����SN/DeviceID/IotState/PkgProduce/REPLY
�����SN/DeviceID/IotState/RunProcedure/REPLY
�����SN/DeviceID/IotState/GetDataset/REPLY
�����SN/DeviceID/IotState/ConfigDevice/REPLY
�����SN/DeviceID/IotState/CloseDevice/REPLY

�����SN/DeviceID/IotState/RunProcedure/EVENT/�¼�ID
�����SN/DeviceID/IotState/EngineEvent/EVENT/DeviceClosed

���ݽ�����������cmdType,cmdID,retType
**************************/
BOOL CSttProtoClientMqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{//˵����������¼�ʱ��ppszCmdID����ΪEventID
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
		pTemp = (char *)oToken.GetToken(5);		//����ΪEventID
		memcpy(pszCmdID,pTemp,strlen(pTemp));
		pTemp = (char *)oToken.GetToken(4);
		memcpy(pszRetType,pTemp,strlen(pTemp));
		return TRUE;
	}
	//yzj 2021-10-5 
	else if (nStringsCnt == 4)
	{
		//��UpdateDataset
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