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

	//release˳��Ӧ����create�෴
	//CGbXMLKeys::Release();
	CDataMngrXmlRWKeys::Release();
	//CCfgDataMngrXmlRWKeys::Release();
}

// ����˷���topic������Ϣ��ָ��topic�Ŀͻ���
BOOL CSttIotMqttSvrBase::SendTopicData(const CString& strTopic, char *pBuf, long nLen)
{
	mosquitto_db* pDb = _mosquitto_get_db();
	struct mosquitto_msg_store *pMsg;
	pMsg = (struct mosquitto_msg_store *)_mosquitto_malloc(sizeof(struct mosquitto_msg_store));

	mqtt3_db_message_store(pDb, 0, 0, strTopic, 0, nLen, pBuf, 0, &pMsg, 0);
	//���ڿͻ��˵������,������Ϣ���в���ʼmqtt��������������
	if(pDb->contexts_by_sock)
		mqtt3_db_messages_queue(pDb, pDb->contexts_by_sock->id, strTopic, 0, 0, &pMsg);
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������: ������Ҫ����һ�����ӵĿͻ���!"));

	_mosquitto_free(pMsg);

	return TRUE;
}

void CSttIotMqttSvrBase::SetMsgWnd(const HWND hWnd)
{
	m_hWnd = hWnd;
	// ����һ��ȫ�ֵ�HWND����,ʹMqtt�����֪���ͻ���������Ҫ���ĸ����ڽ���ת��
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
		strLog = _T("�����桿: ") + strLog;
		break;
	case MOSQ_LOG_ERR:
		strLog = _T("������: ") + strLog;
		break;
	case MOSQ_LOG_SUBSCRIBE:
		strLog = _T("�����ġ�: ") + strLog.Mid(0, strLog.Find(' ') + 1) + _T("QoS:")
			+ strLog.Mid(strLog.Find(' ') + 1, 1) + _T(" Topic:") 
			+ strLog.Mid(strLog.ReverseFind(' ') + 1);
		break;
	case MOSQ_LOG_UNSUBSCRIBE:
		strLog = _T("���˶���: ") + strLog.Mid(0, strLog.Find(' ') + 1) + _T("Topic:") 
			+ strLog.Mid(strLog.Find(' ') + 1);
		break;
	//case MOSQ_LOG_DEBUG:
	//	strLog = _T("�����ԡ�: ") + strLog;
	//	break;
	case MOSQ_LOG_NOTICE:
		strLog = _T("��֪ͨ��: ") + strLog;
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������: ����һ����ͬID�Ŀͻ���!"));
	else
		m_oClientList.AddNewChild(NewMosquittoClient(strIP, strID));
}

void CSttIotMqttSvrBase::Process_Disconnect(const char* strID)
{
	CExBaseObject* pClient = m_oClientList.FindChildByID(strID);
	if(pClient)
	{
		//����̨�Ͽ�����ʱ,�Ͽ�����̨�����ݿ������
		m_oClientList.DeleteByID(strID);
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������: ���ԶϿ�һ��ID�����ڵĿͻ���!"));
}

void CSttIotMqttSvrBase::Process_Subscribe(const char* strTopic, const char* strID)
{
	CMosquittoClient* pClient = (CMosquittoClient*)m_oClientList.FindChildByID(strID);
	if(pClient)
	{
		CExBaseObject* pTopic = pClient->m_oTopics.FindChildByID(strTopic);
		if(pTopic)
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������: �ͻ����Ѿ�������һ������!"));
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
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������: �ͻ��˲�����!"));
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
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������: �ͻ��˲�������Ҫȡ�����ĵ�����!"));
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������: �ͻ��˲�����!"));
}
