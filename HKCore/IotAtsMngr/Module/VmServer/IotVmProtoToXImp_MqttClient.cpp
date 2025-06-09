#include "stdafx.h"
#include "IotVmProtoToXImp_MqttClient.h"
#include "../../../Module/System/StringTokenizer.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CIotVmProtoToXImp_MqttClient::CIotVmProtoToXImp_MqttClient()
{

}

CIotVmProtoToXImp_MqttClient::~CIotVmProtoToXImp_MqttClient()
{

}

/************************
//主题：测试仪SN/TestCmd/ConfigTest
//主题：测试仪SN/TestCmd/StartTest
//
**************************/
//此处也会订阅到CreateDevice，在处理时需要过滤
BOOL CIotVmProtoToXImp_MqttClient::SubcribeMqttTopic(int nQos)
{
	if (!ConnectServer())
	{
		return FALSE;
	}

	CString strTopic;
	strTopic.Format(_T("%s/TestCmd/+"), m_strDeviceSN);
	m_oMqttClient.SubscribeTopic(strTopic, nQos);

	return TRUE;
}

//物联协议命令发送
long CIotVmProtoToXImp_MqttClient::Send(CExBaseObject *pCmdBase)
{
	if (!ConnectServer())
	{
		return -3;
	}

	CSttSysState *pSysState = (CSttSysState *)pCmdBase;
	CString strTopic;
	strTopic = GenerateTopic(m_strDeviceSN, 0, 
		const_cast<char*>(pSysState->m_strRetType.GetString()), 
		const_cast<char*>(pSysState->m_strID.GetString()), NULL);

	char *pszBuf = NULL;
	long nLen = pSysState->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszBuf,0);

	if (pszBuf == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CIotVmX_MqttClientBase::pszBuf==NULL"));
		return -1;
	}

	BOOL bRet = m_oMqttClient.PublicTopic(strTopic,pszBuf,nLen);

	return bRet;
}

//主题：测试仪SN/TestCmd/SetParameter
//主题：测试仪SN/TestState/SetParameter/Reply
//主题：测试仪SN/TestState/EVENT/TestStarted
//主题：测试仪SN/TestState/REPORT
CString CIotVmProtoToXImp_MqttClient::GenerateTopic(const CString &strToSN, long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopicType = _T("TestState");
	CString strTopic, strSrcSN;

	if (strToSN.IsEmpty())
	{
		strSrcSN = m_strSrcSN;
	}
	else
	{
		strSrcSN = strToSN;
	}

	CString strCmdID = pszCmdID;
	if(strCmdID == _T("EVENT"))
	{
		strTopic.Format(_T("%s/%s/%s/%s"),strSrcSN,strTopicType, pszCmdID, pszRetType);
	}
	else if(strCmdID == _T("REPLY"))
	{
		strTopic.Format(_T("%s/%s/%s/%s"),strSrcSN,strTopicType, pszRetType, pszCmdID);
	}

	return strTopic;
}

BOOL CIotVmProtoToXImp_MqttClient::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() != 3)
	{
		return FALSE;
	}

	strFromSN = oToken.GetToken(0);
	m_strSrcSN = oToken.GetToken(1);

	nCmdType = STT_CMD_TYPE_TEST;
	char *pTemp = (char *)oToken.GetToken(2);
	memcpy(pszCmdID,pTemp,strlen(pTemp));

	return TRUE;
}