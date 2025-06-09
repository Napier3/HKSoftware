#include "stdafx.h"
#include "MqttClientToPxEngine.h"
#include "../../../SttStudio/Module/SttRegisterCode.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 


CMqttClientToPxEngine::CMqttClientToPxEngine()
{
	m_pTestEngine = NULL;
	m_strIP = _T("127.0.0.1");
	m_nPort = 1886;
	m_strClientID = _T("TestClientID");
}

CMqttClientToPxEngine::~CMqttClientToPxEngine()
{

}

// void CMqttClientToPxEngine::Init(const CString &strIP,long nPort,const CString &strClientID)
// {
// 	m_strIP = strIP;
// 	m_nPort = nPort;
// 	m_strClientID = strClientID;
// }

void CMqttClientToPxEngine::SetMqttEngineRef(CMqttEngineBase *pEngine)
{
	m_pTestEngine = pEngine;
	if (m_pTestEngine != NULL)
	{
		m_pTestEngine->m_strIP = m_strIP;
		m_pTestEngine->m_nPort = m_nPort;
	}
}


void CMqttClientToPxEngine::ReSubcribeMqttTopic()
{
	//先取消原先订阅的主题
	int nCnt = m_arrSubTopic.GetCount();

	for (int i=0; i<nCnt; i++)
	{
		m_oMqttClient.UnSubscribeTopic(m_arrSubTopic.GetAt(i));
	}

	SubcribeMqttTopic(0);
}


void CMqttClientToPxEngine::OnMqttDisconnected(char *pszErr)
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnDisconnected:[ErrInfo=%s]"),pszErr);

	OnClose(pszErr);
}

void CMqttClientToPxEngine::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
	long nCmdType = 0;
	char pszCmdID[64] = {0}, pszRetType[64] = {0};
	CString strFromSN;   //2021-8-22  lijunqing  
	BOOL bRet = AnalysisTopic(strTopic, strFromSN, nCmdType, pszCmdID, pszRetType);

	if (bRet)
	{
		OnRecieve(strFromSN, pBuf,nLen,nCmdType,pszCmdID,pszRetType);
	}
}

void CMqttClientToPxEngine::OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser)
{
	OnMqttMsgRecieve(oSttMqttTopicParser.m_strTopic, oSttMqttTopicParser.m_pMqttPkgBuffer, oSttMqttTopicParser.m_nMqttPkgBufferLen);
}

void CMqttClientToPxEngine::OnRecieve(const CString &strFromSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	if (m_pTestEngine != NULL)
	{
		m_pTestEngine->OnTestMsg(this, strFromSN, pBuf,nLen,nCmdType,pszCmdID,pszRetType);
	}
}

void CMqttClientToPxEngine::OnClose(char *pszErr)
{
	if (m_pTestEngine != NULL)
	{
		m_pTestEngine->OnClose(pszErr);
	}
}

long CMqttClientToPxEngine::Send(const CString &strToSN, char *pBuf,long nLen,long nCmdType, char *pszCmdID, char *pszRetType, char *pszEventID)
{
	CString strTopic = GenerateTopic(strToSN, nCmdType,pszCmdID,pszRetType,pszEventID);

	BOOL bRet = m_oMqttClient.PublicTopic(strTopic,pBuf,nLen);
	if (bRet)
	{
		return nLen;
	}
	return -1;
}

//2021-7-20  lijunqing
//因为此处已经是MQTT，所以发送的部分，可以就按照MQPTT处理，不一定需要兼容STT部分
//兼容的部分，就是Send(CExBaseObject *pCmdBase)函数
long CMqttClientToPxEngine::Send(char *pBuf,long nLen, const CString &strTopic)
{
	BOOL bRet = m_oMqttClient.PublicTopic(strTopic,pBuf,nLen);

	if (bRet)
	{
		return nLen;
	}

	return -1;
}


BOOL CMqttClientToPxEngine::Connect(const char *pszIP,long nPort, const char *pszClientIDKey)
{
	if (m_oMqttClient.IsConnectSuccessful())
	{
		return TRUE;
	}

	m_strIP = pszIP;
	m_nPort = nPort;

	if (pszClientIDKey != NULL)
	{
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		m_strClientID.Format(_T("%s_%u_%02d%02d%03d"), pszClientIDKey
			,stt_GetMachineCode_U32(),tm.wMinute,tm.wSecond,tm.wMilliseconds);
	}


	m_oMqttClient.AttachMqttMsgInterface(this);
	BOOL bRet = m_oMqttClient.InitMqttClient(pszIP,nPort,m_strClientID);

	if (bRet)
	{
		//连接成功后，主动订阅主题
		SubcribeMqttTopic(0);
	}

	return bRet;
}

BOOL CMqttClientToPxEngine::ConnectServer()
{
	return CMqttClientToPxEngine::Connect(m_strIP,m_nPort, NULL);
}

void CMqttClientToPxEngine::Disconnect()
{
	m_oMqttClient.Disconnect();
}