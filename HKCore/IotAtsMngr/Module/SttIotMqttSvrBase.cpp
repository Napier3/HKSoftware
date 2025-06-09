#include "stdafx.h"
#include "SttIotMqttSvrBase.h"
#include "MqttServerConfig.h"
#include "MosquittoClient.h"
#include "MqttServerConfig.h"
#include "..\..\Module\System\StringTokenizer.h"
#include "../../Module/DataMngr/DataGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString g_strRTDeviceRptPath;

CSttIotMqttSvrBase::CSttIotMqttSvrBase()
{
	m_pszXmlBuffer = NULL;
	m_nXmlBufferLen = 0;
}

CSttIotMqttSvrBase::~CSttIotMqttSvrBase()
{
	delete m_pszXmlBuffer;
}

long CSttIotMqttSvrBase::GenerateIndexTest()
{
	static long nIndex = 1;

	return (nIndex++);
}

long CSttIotMqttSvrBase::GenerateIndexItem()
{
	static long nIndex = 1;

	return (nIndex++);
}

CExBaseObject* CSttIotMqttSvrBase::NewMosquittoClient(const char* strName, const char* strID)
{
	CMosquittoClient* pClient = new CMosquittoClient();
	pClient->m_strName = strName;
	pClient->m_strID = strID;
	return pClient;
}

void CSttIotMqttSvrBase::InitSttIotMqttSvrBase()
{
	_P_InitSystemPath();

	g_strRTDeviceRptPath = _P_GetDBPath();
	g_strRTDeviceRptPath += _T("RTDeviceRpt\\");

	CDataMngrXmlRWKeys::Create();
}
void CSttIotMqttSvrBase::ExitSttIotMqttSvrBase()
{
	//CXFileHttpClient::ExitXFileHttpClient();

	//release顺序应该与create相反
	//CGbXMLKeys::Release();
	CDataMngrXmlRWKeys::Release();
	//CCfgDataMngrXmlRWKeys::Release();
}

// 服务端发送topic数据消息给指定topic的客户端
BOOL CSttIotMqttSvrBase::SendTopicData(const CString& strTopic, char *pBuf, long nLen)
{
	mosquitto_db* pDb = _mosquitto_get_db();
	struct mosquitto_msg_store *pMsg;
	pMsg = (struct mosquitto_msg_store *)_mosquitto_malloc(sizeof(struct mosquitto_msg_store));

	mqtt3_db_message_store(pDb, 0, 0, strTopic, 0, nLen, pBuf, 0, &pMsg, 0);
	//存在客户端的情况下,插入消息队列并开始mqtt分析、发送流程
	if(pDb->contexts_by_sock)
		mqtt3_db_messages_queue(pDb, pDb->contexts_by_sock->id, strTopic, 0, 0, &pMsg);
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【错误】: 至少需要存在一个连接的客户端!"));

	_mosquitto_free(pMsg);

	return TRUE;
}

void CSttIotMqttSvrBase::SetMsgWnd(const HWND hWnd)
{
	m_hWnd = hWnd;
	// 设置一个全局的HWND变量,使Mqtt服务端知道客户端数据需要向哪个窗口进行转发
	Mosquitto_SetMsgWnd(hWnd);
}

void CSttIotMqttSvrBase::Process_UpdateLog(int nPriority, const char* strMsg)
{
	CString strLog = strMsg;
	char* strUtf8 = NULL;
	long nUtf8Len = 0;
	charUtf8_to_charGBK(const_cast<char*>(strLog.GetString()), strLog.GetLength(), &strUtf8, nUtf8Len);
	strLog = strUtf8;
	delete strUtf8;

	switch(nPriority)
	{
	case MOSQ_LOG_WARNING:
		strLog = _T("【警告】: ") + strLog;
		break;
	case MOSQ_LOG_ERR:
		strLog = _T("【错误】: ") + strLog;
		break;
	case MOSQ_LOG_SUBSCRIBE:
		strLog = _T("【订阅】: ") + strLog.Mid(0, strLog.Find(' ') + 1) + _T("QoS:")
			+ strLog.Mid(strLog.Find(' ') + 1, 1) + _T(" Topic:") 
			+ strLog.Mid(strLog.ReverseFind(' ') + 1);
		break;
	case MOSQ_LOG_UNSUBSCRIBE:
		strLog = _T("【退订】: ") + strLog.Mid(0, strLog.Find(' ') + 1) + _T("Topic:") 
			+ strLog.Mid(strLog.Find(' ') + 1);
		break;
	//case MOSQ_LOG_DEBUG:
	//	strLog = _T("【调试】: ") + strLog;
	//	break;
	case MOSQ_LOG_NOTICE:
		strLog = _T("【通知】: ") + strLog;
		break;
	case MOSQ_LOG_NONE:
	case MOSQ_LOG_INFO:
	case MOSQ_LOG_WEBSOCKETS:
	case MOSQ_LOG_ALL:
	default:
		return;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, strLog);
}

void CSttIotMqttSvrBase::Process_Connect(const char* strIP, const char* strID)
{
	CExBaseObject* pClient = m_oClientList.FindChildByID(strID);
	if(pClient)
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【错误】: 存在一个相同ID的客户端!"));
	else
		m_oClientList.AddNewChild(NewMosquittoClient(strIP, strID));
}

void CSttIotMqttSvrBase::Process_Disconnect(const char* strID)
{
	CExBaseObject* pClient = m_oClientList.FindChildByID(strID);
	if(pClient)
	{
		//测试台断开连接时,断开测试台与数据库的连接
		m_oClientList.DeleteByID(strID);
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【错误】: 尝试断开一个ID不存在的客户端!"));
}

void CSttIotMqttSvrBase::Process_Subscribe(const char* strTopic, const char* strID)
{
	CMosquittoClient* pClient = (CMosquittoClient*)m_oClientList.FindChildByID(strID);
	if(pClient)
	{
		CExBaseObject* pTopic = pClient->m_oTopics.FindChildByID(strTopic);
		if(pTopic)
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【错误】: 客户端已经订阅了一个主题!"));
		else
		{
			CString strText = strTopic;
			char* strUtf8 = NULL;
			long nUtf8Len = 0;
			charUtf8_to_charGBK(const_cast<char*>(strText.GetString()), strText.GetLength(), &strUtf8, nUtf8Len);
			strText = strUtf8;
			delete strUtf8;
			pClient->m_oTopics.AddNew(strID, strText);
		}
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【错误】: 客户端不存在!"));
}

void CSttIotMqttSvrBase::Process_Unsubscribe(const char* strTopic, const char* strID)
{
	CMosquittoClient* pClient = (CMosquittoClient*)m_oClientList.FindChildByID(strID);
	if(pClient)
	{
		CExBaseObject* pTopic = pClient->m_oTopics.FindChildByID(strTopic);
		if(pTopic)
			pClient->m_oTopics.DeleteByID(strTopic);
		else
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【错误】: 客户端不存在需要取消订阅的主题!"));
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【错误】: 客户端不存在!"));
}
