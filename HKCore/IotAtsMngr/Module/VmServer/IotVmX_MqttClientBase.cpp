#include "stdafx.h"
#include "IotVmX_MqttClientBase.h"
#include "../../../Module/System/StringTokenizer.h"

#include "../../../SttStudio/Module/SttCmd\SttTestCmd.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CIotVmX_MqttClientBase::CIotVmX_MqttClientBase()
:CSttMqttClientBase()
{

}

CIotVmX_MqttClientBase::~CIotVmX_MqttClientBase()
{

}

//物联协议命令发送
long CIotVmX_MqttClientBase::Send(CExBaseObject *pCmdBase)
{
	if (!ConnectServer())
	{
		return -3;
	}

	CSttSysState *pSysState = (CSttSysState *)pCmdBase;
	CString strTopic;
	strTopic = CSttMqttClientBase::GenerateTopic(pSysState);

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

CString CIotVmX_MqttClientBase::GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic, strSrcSN;

	if (strToSN.IsEmpty())
	{
		strSrcSN = m_strSrcSN;
	}
	else
	{
		strSrcSN = strToSN;
	}

	strTopic.Format(_T("%s/%s/%s/%s"), strSrcSN, pszCmdType, pszCmdID, pszRetType);
	return strTopic;
}

//请求端SN/TestCmd/CreateDevice
//IotVm_2840893088_0606673/TestCmd/CreateDevice
BOOL CIotVmX_MqttClientBase::AnalysisTopic(const CString &strTopic, CString &strFromSN, long &nCmdType, char *pszCmdID, char *pszRetType)
{
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	if (oToken.GetStringsCount() != 3)
	{
		return FALSE;
	}

	CString strTopicType, strVersion, strCurDeviceID;
	strVersion = oToken.GetToken(0);
	strCurDeviceID = oToken.GetToken(1);
	strTopicType = oToken.GetToken(2);

	if (strCurDeviceID != m_strDeviceSN)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("VM[%s] != [%s]")
			, m_strDeviceSN, strCurDeviceID);
	}

	strFromSN = strCurDeviceID;

	ASSERT (FALSE);
	nCmdType = 0;
	char *pTemp = (char *)oToken.GetToken(3);
	memcpy(pszCmdID,pTemp,strlen(pTemp));

	return TRUE;
}