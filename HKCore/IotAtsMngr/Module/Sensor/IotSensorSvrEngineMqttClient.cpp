#include "stdafx.h"
#include "IotSensorSvrEngineMqttClient.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"

CIotSensorSvrEngineMqttClient::CIotSensorSvrEngineMqttClient()
{

}

CIotSensorSvrEngineMqttClient::~CIotSensorSvrEngineMqttClient()
{

}

// BOOL CIotSensorSvrEngineMqttClient::Connect(const char *pszIP,long nPort)
// {
// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 
// 	CString strClientID;
// 	strClientID.Format(_T("SensorSvrEngine_%u_%02d%02d%03d")
// 		,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
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
���������⣺
������IP/Monitor
**************************/
BOOL CIotSensorSvrEngineMqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	m_oMqttClient.SubscribeTopic(_T("+/Monitor"),nQos);
	m_oMqttClient.SubscribeTopic(_T("/v1/+/service/data"),nQos);   //����Ժ������ҵ�������⣬�ӽ���ڵ��豸����
	//shaolei 20211007
	m_oMqttClient.SubscribeTopic(_T("/accnode/net/up/data"),nQos);
	return TRUE;
}

/*
���Ҳ�����
������IP/������SN/SensorCmd
*/
CString CIotSensorSvrEngineMqttClient::GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	//pszCmdID:������SN,pszRetType:������SN
	CString strTopic = _T("");
	strTopic.Format(_T("%s/%s/SensorCmd"),pszCmdID,pszRetType);

	return strTopic;
}

/************************
������ҵ���ģ�����̶������ý���

������SN/Monitor
/accnode/net/up/data
**************************/
BOOL CIotSensorSvrEngineMqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
// 	CStringTokenizer oToken;
// 	oToken.Init(strTopic, '/');
// 
// 	if (oToken.GetStringsCount() != 2)
// 	{
// 		return FALSE;
// 	}
// 
// 	m_strSrcTestAppID = oToken.GetToken(0);
//	m_strSensorID = oToken.GetToken(1);
	//m_pTestEngine->InitTopicSrcInfo(m_strSrcTestAppID,m_strSensorID);

	return TRUE;
}