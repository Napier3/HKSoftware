#include "stdafx.h"
#include "IotVmServer_MqttClient.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"
#include "../../../Module/System/StringTokenizer.h"

CIotVmServer_MqttClient::CIotVmServer_MqttClient()
{
	m_pVmConfig = NULL;
}	

CIotVmServer_MqttClient::~CIotVmServer_MqttClient()
{

}

/************************
//主题：测试服务端SN/TestCmd/CreateDevice
//
**************************/
BOOL CIotVmServer_MqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	if (m_pVmConfig == NULL)
	{
		//表示配置文件不存在，则订阅所有仪器的主题
		m_oMqttClient.SubscribeTopic(_T("+/TestCmd/CreateDevice"),nQos);
		m_oMqttClient.SubscribeTopic(_T("+/TestCmd/CloseDevice"),nQos);
	}
	else if (m_pVmConfig->GetCount() == 0)
	{
		//表示配置文件中没有配置测试仪，则订阅所有仪器的主题
	m_oMqttClient.SubscribeTopic(_T("+/TestCmd/CreateDevice"),nQos);
		m_oMqttClient.SubscribeTopic(_T("+/TestCmd/CloseDevice"),nQos);
	}
	else
	{
		POS pos = m_pVmConfig->GetHeadPosition();
		CDvmData *pData = NULL;
		CString strTopic;

		while (pos != NULL)
		{
			pData = (CDvmData *)m_pVmConfig->GetNext(pos);
			strTopic.Format(_T("%s/TestCmd/CreateDevice"), pData->m_strValue);
			m_oMqttClient.SubscribeTopic(strTopic,nQos);

			strTopic.Format(_T("%s/TestCmd/CloseDevice"), pData->m_strValue);
			m_oMqttClient.SubscribeTopic(strTopic,nQos);
		}
	}

	return TRUE;
}

//请求端SN/TestCmd/CreateDevice
//IotVm_2840893088_0606673/TestCmd/CreateDevice
BOOL CIotVmServer_MqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() != 3)
	{
		return FALSE;
	}

	strFromSN = oToken.GetToken(0);
	m_strSrcSN = strFromSN;

	nCmdType = STT_CMD_TYPE_TEST;
	char *pTemp = (char *)oToken.GetToken(2);
	memcpy(pszCmdID,pTemp,strlen(pTemp));

	return TRUE;
}