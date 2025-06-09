#include "stdafx.h"
#include "MosquittoServerBase.h"
#include "MqttServerConfig.h"
#include "MosquittoClient.h"
#include "MqttServerConfig.h"
#include "..\..\Module\System\StringTokenizer.h"
#include "..\MosquittoServer\MosquittoServer.h"
#include "..\..\Module\UserDB\XUserTcpClientBase.h"
#include "..\..\AutoTest\Module\GuideBook\reports.h"
#include "..\..\Module\XFileHttpClient\XFileHttpClient.h"
#include "Iot_AtsMngrDB\Iot_TestTaskDevice.h"
#include "Iot_AtsMngrDB\Iot_DeviceOutReports.h"
#include "Iot_AtsMngrDB\Iot_DeviceOutReportExs.h"
#include "Iot_AtsMngrDB\Iot_DeviceReportEx.h"
#include "Iot_AtsMngrDB\Iot_RTDeviceData.h"
#include "Iot_AtsMngrDB\Iot_RTDeviceHisDataTitles.h"
#include "SttMqttClientEngineConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString g_strRTDeviceRptPath;

CMosquittoServerBase::CMosquittoServerBase()
{
	m_pszXmlBuffer = NULL;
	m_nXmlBufferLen = 0;
	SetXmlBufferLen(1048576); //1M
}

CMosquittoServerBase::~CMosquittoServerBase()
{
	delete m_pszXmlBuffer;
}

long CMosquittoServerBase::GenerateIndexTest()
{
	static long nIndex = 1;

	return (nIndex++);
}

long CMosquittoServerBase::GenerateIndexItem()
{
	static long nIndex = 1;

	return (nIndex++);
}

CExBaseObject* CMosquittoServerBase::NewMosquittoClient(const char* strName, const char* strID)
{
	CMosquittoClient* pClient = new CMosquittoClient();
	pClient->m_strName = strName;
	pClient->m_strID = strID;
	return pClient;
}

void CMosquittoServerBase::InitMosquittoServerBase()
{
	_P_InitSystemPath();

// 	g_strRTDeviceRptPath = _P_GetDBPath();
// 	g_strRTDeviceRptPath += _T("RTDeviceRpt\\");
	g_strRTDeviceRptPath = _T("D:\\tyh\\uploadPath\\");

	CIot_AtsMngrXmlRWKeys::Create();
	CSttCmdDefineXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CDataMngrXmlRWKeys::Create();
	//CGbXMLKeys::CreatetGbXMLkeys();
	CMqttServerConfig::Create();
	CSttMqttClientEngineConfig::Create();

	CDBServerInfoBase oDBServerInfo;
// 	oDBServerInfo.m_strHostIp = _T("121.41.92.56");//IP
// 	oDBServerInfo.m_strDbName = _T("tyh");//���ݿ�����
// 	oDBServerInfo.m_strUserName = _T("root");
// 	oDBServerInfo.m_strPasswd = _T("tyh12345678");
// 	oDBServerInfo.m_iPort = 3306;
// 	InitMySqlDB(oDBServerInfo);

	oDBServerInfo.m_strDbName = CMqttServerConfig::GetDBName();//_T("tyh");//���ݿ�����
	oDBServerInfo.m_strUserName = _T("root");
	oDBServerInfo.m_strPasswd = CMqttServerConfig::GetDBPasswd();//_T("123456");
	oDBServerInfo.m_strHostIp = CMqttServerConfig::GetDBIP();
	oDBServerInfo.m_iPort = CString_To_long(CMqttServerConfig::GetDBPort());
	oDBServerInfo.m_strEncoding = CMqttServerConfig::GetDBEncoding();
	InitMySqlDB(oDBServerInfo);

	CXFileHttpClient::InitXFileHttpClient();
}
void CMosquittoServerBase::ExitMosquittoServerBase()
{
	CXFileHttpClient::ExitXFileHttpClient();

	DisconnectDB();

	//release˳��Ӧ����create�෴
	CMqttServerConfig::Release();
	CSttMqttClientEngineConfig::Release();
	//CGbXMLKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CIot_AtsMngrXmlRWKeys::Release();
}

// ����˷���topic������Ϣ��ָ��topic�Ŀͻ���
BOOL CMosquittoServerBase::SendTopicData(const CString& strTopic, char *pBuf, long nLen)
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

void CMosquittoServerBase::SetMsgWnd(const HWND hWnd)
{
	m_hWnd = hWnd;
	// ����һ��ȫ�ֵ�HWND����,ʹMqtt�����֪���ͻ���������Ҫ���ĸ����ڽ���ת��
	Mosquitto_SetMsgWnd(hWnd);
}

void CMosquittoServerBase::Process_UpdateLog(int nPriority, const char* strMsg)
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

void CMosquittoServerBase::Process_Connect(const char* strIP, const char* strID)
{
	CExBaseObject* pClient = m_oClientList.FindChildByID(strID);
	if(pClient)
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("������: ����һ����ͬID�Ŀͻ���!"));
	else
		m_oClientList.AddNewChild(NewMosquittoClient(strIP, strID));
}

void CMosquittoServerBase::Process_Disconnect(const char* strID)
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

void CMosquittoServerBase::Process_Subscribe(const char* strTopic, const char* strID)
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

void CMosquittoServerBase::Process_Unsubscribe(const char* strTopic, const char* strID)
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

/******************************
����̨SN/AtsState/EVENT/TestCreated
����̨SN/AtsState/EVENT/TestStarted
����̨SN/AtsState/EVENT/TestStoped
����̨SN/AtsState/EVENT/ExportFinish
����̨SN/AtsState/CloseTest/REPLY
����̨SN/AtsState/EVENT/ItemStateChanged
����̨SN/AtsState/EVENT/TestFinished
*******************************/
BOOL CMosquittoServerBase::Process_Ats_Event(const char* strTopic, const char* strMsg)
{
	int nLen = strlen(strMsg);
	CStringTokenizer oStrTokenizer;
	oStrTokenizer.Init(strTopic, '/');
	int nCnt = oStrTokenizer.GetStringsCount();

	CString strBenchSN = oStrTokenizer.GetToken(0);
	CString strEventID = oStrTokenizer.GetToken(nCnt - 1);

	//�ж�format���������жϣ�����msg�ĵ�һ���ַ���<����{
	CSttSysState oSysState;
	if(strMsg[0] == '<')
		PraseCmdBuf(&oSysState, strMsg, nLen, MQTT_DATA_FORMAT_XML);
	else
		PraseCmdBuf(&oSysState, strMsg, nLen, MQTT_DATA_FORMAT_JSON);

	if (strEventID == SYS_STATE_EVENT_OnTestCreated)
	{
		return Process_TestCreated(strBenchSN,oSysState);
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		return Process_TestStarted(strBenchSN,oSysState);
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestStoped)
	{
		return Process_TestStoped(strBenchSN,oSysState);
	}
	else if (strEventID == SYS_STATE_EVENT_ExportReport)
	{
		return Process_ExportReport(strBenchSN,oSysState);
	}
	else if (strEventID == SYS_STATE_EVENT_OnItemStateChanged)
	{
		return Process_ItemStateChanged(strBenchSN,oSysState);
	}
	else if (strEventID == SYS_STATE_RETTYPE_REPORT)
	{
		return Process_Report(strBenchSN,oSysState);
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestFinished)
	{
		return Process_TestFinished(strBenchSN,oSysState);
	}
	else if (strEventID == SYS_STATE_RETTYPE_REPLY)
	{
		return Process_CloseTestReply(strBenchSN,oSysState);
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestProcess)
	{
		return Process_TestProcess(strBenchSN,oSysState);
	}
	//9��30����ʾ�İ汾�� ���¼��������ǣ�IOT/AtsState/EVENT/UploadReportFinished
	else if (strEventID == SYS_STATE_EVENT_UploadReportFinished)
	{
		return Process_UploadReportFinished(strBenchSN,oSysState);
	}

	return TRUE;
}

/******************************
[IOT|MQTT]/AtsState/EVENT/TestCreated
[IOT|MQTT]/AtsState/EVENT/TestStarted
[IOT|MQTT]/AtsState/EVENT/TestStoped
[IOT|MQTT]/AtsState/EVENT/TestFinished
*******************************/
BOOL CMosquittoServerBase::Process_IotAts_Event(const char* strTopic, const char* strMsg)
{
	//CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_IotAts_Event"));
	CStringTokenizer oStrTokenizer;
	oStrTokenizer.Init(strTopic, '/');
	int nCnt = oStrTokenizer.GetStringsCount();

	CString strTestType = oStrTokenizer.GetToken(0);
	CString strEventID = oStrTokenizer.GetToken(nCnt - 1);

	BOOL bRet = FALSE;
	CJSON * pJson = CJSON_Parse(strMsg);

	if (strEventID == SYS_STATE_EVENT_OnTestCreated)
	{
		bRet = Process_Iot_TestCreated(strTestType,pJson);
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestStarted)
	{
		bRet = Process_Iot_TestStarted(strTestType,pJson);
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestStoped)
	{
		bRet = Process_Iot_TestStoped(strTestType,pJson);
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestFinished)
	{
		bRet = Process_Iot_TestFinished(strTestType,pJson);
	}
	else if (strEventID == SYS_STATE_EVENT_OnExternTestFinished)
	{
		bRet = Process_Iot_ExternTestFinished(strTestType,pJson);
	}

	//9��30����ʾ�İ汾�� ���¼��������ǣ�IOT/AtsState/EVENT/UploadReportFinished
	else if (strEventID == SYS_STATE_EVENT_UploadReportFinished)
	{
		int nLen = strlen(strMsg);

		//�ж�format���������жϣ�����msg�ĵ�һ���ַ���<����{
		CSttSysState oSysState;
		PraseCmdBuf(&oSysState, strMsg, nLen, MQTT_DATA_FORMAT_JSON);
		bRet = Process_UploadReportFinished(strTestType,oSysState);
	}
	else if (strEventID == SYS_STATE_EVENT_OnTestProcess)
	{
		bRet = Process_Iot_TestProcess(strTestType,pJson);
	}

	CJSON_Delete(pJson);

	return bRet;
}

/******************************
����̨SN/AtsState/REPORT
*******************************/
BOOL CMosquittoServerBase::Process_Ats_Report(const char* strTopic, const char* strMsg)
{
	//CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Ats_Report"));
	int nLen = strlen(strMsg);
	CStringTokenizer oStrTokenizer;
	oStrTokenizer.Init(strTopic, '/');
	int nCnt = oStrTokenizer.GetStringsCount();

	CString strBenchSN = oStrTokenizer.GetToken(0);

	//�ж�format���������жϣ�����msg�ĵ�һ���ַ���<����{
	CSttSysState oSysState;
	if(strMsg[0] == '<')
		PraseCmdBuf(&oSysState, strMsg, nLen, MQTT_DATA_FORMAT_XML);
	else
		PraseCmdBuf(&oSysState, strMsg, nLen, MQTT_DATA_FORMAT_JSON);

	return Process_Report(strBenchSN,oSysState);
}

/*********************
���⣺[IOT|MQTT]/AtsState/EVENT/TestCreated
���ݣ�
{
	"id":"TestCreated",
	"time":"2021-3-24 10:10:10",
	"DeviceSN ":"123456123456",
	"TotalItems":"6",   //�ܵ���Ŀ����������
	"BenchSN":"TX001"              //����̨SN��������
}
************************/
//�ڴ�������ʱ����¼����Ŀ����
//��Ŀǰ��ҳ�����������У�Э��һ���ԵĲ��Դ���Ҫ�������ܲ��ԵĴ���
BOOL CMosquittoServerBase::Process_Iot_TestCreated(const CString &strTestType,CJSON *pJson)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Iot_TestCreated"));

	//�Ȳ����²���̨��״̬
// 	CJSON* pBenchSNJson = CJSON_GetObjectItem(pJson, STT_CMD_PARA_BenchSN);
// 	if (pBenchSNJson == NULL)
// 	{
// 		return FALSE;
// 	}
// 	CString strBenchSN = pBenchSNJson->valuestring;
// 	//���²���̨״̬
// 	CIot_Bench oBench;
// 	oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_TESTCREATED);

	CJSON* pDeviceSNJson = CJSON_GetObjectItem(pJson, STT_CMD_PARA_DeviceSN);
	if (pDeviceSNJson == NULL)
	{
		return FALSE;
	}
	CString strDeviceSN = pDeviceSNJson->valuestring;

	//��ѯ����̨����װ�ñ�
	CIot_TestTaskDevice oTestTaskDevice;
	BOOL bRet = oTestTaskDevice.QueryDeviceByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTaskDevice.DB_Select_OwnEx failed![%s]"),strDeviceSN);
		return FALSE;
	}

	CJSON* pTotalItemsSNJson = CJSON_GetObjectItem(pJson, STT_CMD_PARA_TotalItems);
	if (pTotalItemsSNJson == NULL)
	{
		return FALSE;
	}
	
	oTestTaskDevice.m_nTotalItems_Protocol = pTotalItemsSNJson->valueint;
	oTestTaskDevice.m_nTotalItems = /*oTestTaskDevice.m_nTotalItems_Function + */oTestTaskDevice.m_nTotalItems_Protocol;

	//���²����������ʱ��
	oTestTaskDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	g_pTheMySqlApp->Commit();

	return TRUE;

// 	CIot_Device oDevice;
// 	BOOL bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp,strDeviceSN);
// 	if (!bRet)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
// 		return FALSE;
// 	}
// 
// 	if (strTestType == TEST_TYPE_IOT)
// 	{
// 		oDevice.m_nTest_State = DEVICE_TEST_STATE_IotTesting;
// 	}
// 	else
// 	{
// 		oDevice.m_nTest_State = DEVICE_TEST_STATE_MqttTesting;
// 	}
// 
// 	return oDevice.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
}

/*****************************
���⣺[IOT|MQTT]/AtsState/EVENT/TestStarted 
{
	"id":" TestStarted",
	"time":"2021-3-24 10:10:10",
	"DeviceSN":"123456123456",
	"BenchSN":"1253684"
}
*****************************/
BOOL CMosquittoServerBase::Process_Iot_TestStarted(const CString &strTestType,CJSON *pJson)
{
	//���ڲ���̨��״̬����Process_Ats_TestFinished�¼��У��Ѿ�����Ϊ�����Խ�������
	//����Ӣ����Э��һ���Բ������̺󣬽��޷��޸Ĳ���̨״̬��
	//�����Ľ���������Ӣ������ҳ��ʱ�����ݵĲ�������BenchSN����Ӣ�����Ĳ����¼��У�����BenchSN��Ϊ�������ء�
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Iot_TestStarted"));

	CJSON* pDeviceSN = CJSON_GetObjectItem(pJson, STT_CMD_PARA_DeviceSN);
	if (pDeviceSN == NULL)
	{
		return FALSE;
	}

	if (pDeviceSN->type != CJSON_String)
	{
		return FALSE;
	}

	CString strDeviceSN;
	strDeviceSN = pDeviceSN->valuestring;

	CIot_Device oDevice;
	BOOL bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp,strDeviceSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	oDevice.m_nTest_State = DEVICE_TEST_STATE_IotTesting;
	oDevice.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

 	CJSON* pBenchSNJson = CJSON_GetObjectItem(pJson, STT_CMD_PARA_BenchSN);
 	if (pBenchSNJson == NULL)
 	{
 		return FALSE;
 	}
 	CString strBenchSN = pBenchSNJson->valuestring;
 	//���²���̨״̬
 	CIot_Bench oBench;
 	oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_TESTING_PROTOCOL);

	return TRUE;
}

/*****************************
���⣺[IOT|MQTT]/AtsState/EVENT/TestStoped
{
	"id":" TestStoped",
	"time":"2021-3-24 10:10:10",
	"DeviceSN":"123456123456"
}
*****************************/
BOOL CMosquittoServerBase::Process_Iot_TestStoped(const CString &strTestType,CJSON *pJson)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Iot_TestStoped"));

	CJSON* pDeviceSN = CJSON_GetObjectItem(pJson, "DeviceSN");
	if (pDeviceSN == NULL)
	{
		return FALSE;
	}

	if (pDeviceSN->type != CJSON_String)
	{
		return FALSE;
	}

	CString strDeviceSN;
	strDeviceSN = pDeviceSN->valuestring;

	//�����豸û�в���ֹͣ��״̬���ʴ˴�����Ҫ���±����豸��״̬

	CJSON* pBenchSNJson = CJSON_GetObjectItem(pJson, STT_CMD_PARA_BenchSN);
	if (pBenchSNJson == NULL)
	{
		return FALSE;
	}
	CString strBenchSN = pBenchSNJson->valuestring;
	//���²���̨״̬
	CIot_Bench oBench;
	oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_TESTSTOPED_PROTOCOL);

	return TRUE;
}	

/********************************
���⣺[IOT|MQTT]/AtsState/EVENT/TestFinished
{
	"id":"TestFinished",
	"time":"2021-3-24 10:10:10",
	"data":[
		{
			"id":"test_name",
			"value":"��������"
		},
		{
			"id":"testuser",
			"value":"�û���¼��"
		},
		{
			"id":"DeviceSN",
			"value":"123456123456"
		},
		{
			"id":"tm_begin",
			"value":"2021-3-24 10:10:10"
		},
		{
			"id":"tm_end",
			"value":"2021-3-24 10:10:10"
		},
		{
			"id":"doc_file",
			"value":"�����ļ���.doc"
		},
		{
			"id":"doc_file_s",
			"value":" doc_file  http�ļ����䷵�صķ�����·��fileName"
		},
		{
			"id":"pcap_file",
			"value":"�����ļ���_pcap.rar"
		},
		{
			"id":"pcap_file_s",
			"value":" pcap_file  http�ļ����䷵�صķ�����·��fileName"
		},
		{
			"id":"report_result",
			"value":"0/1"
		}
	]
}
********************************/
BOOL CMosquittoServerBase::Process_Iot_TestFinished(const CString &strTestType,CJSON *pJson)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Iot_TestFinished"));

	CJSON* pArrData = CJSON_GetObjectItem(pJson, "data");
	if (pArrData == NULL)
	{
		return FALSE;
	}

	//����װ�ò��Լ�¼����
	CIot_DeviceHisTest oDeviceHisTest;
	oDeviceHisTest.UpdateAttrs(strTestType,pArrData);

	CSys_User oUser;
	oDeviceHisTest.m_nIndex_User = oUser.GetIndexUser(g_pTheMySqlApp,oDeviceHisTest.m_strLoginName);

	CIot_Device oDevice;
	BOOL bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp,oDeviceHisTest.m_strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),oDeviceHisTest.m_strDeviceSN);
		return FALSE;
	}
	oDevice.m_nTest_State = DEVICE_TEST_STATE_IDLE;
	oDeviceHisTest.m_nIndex_Device = oDevice.m_nIndex_Device;

	g_pTheMySqlApp->StartTransaction();

	oDevice.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	if (strTestType == TEST_TYPE_IOT)
	{
		//ֻ��Ҫ���±����豸��״̬���ɡ�
		bRet = TRUE;
	}
	else
	{
	//����װ�úͿ�ʼʱ���ѯ������������룬���������
	bRet = oDeviceHisTest.UpdateDeviceHisTest(g_pTheMySqlApp);
	}

	g_pTheMySqlApp->Commit();

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDeviceHisTest.UpdateDeviceHisTest failed![%s]"),oDeviceHisTest.m_strDeviceSN);
		return FALSE;
	}
	return TRUE;
}

BOOL CMosquittoServerBase::Process_Iot_ExternTestFinished(const CString &strTestType,CJSON *pJson)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Iot_ExternTestFinished"));

	CJSON* pArrData = CJSON_GetObjectItem(pJson, "data");
	if (pArrData == NULL)
	{
		return FALSE;
	}

	if (pArrData->type != CJSON_Array)
	{
		return FALSE;
	}

	int nArrSize = CJSON_GetArraySize(pArrData);
	CJSON *pData = NULL;
	CJSON *pAttr = NULL;
	CJSON *pAttrVal = NULL;
	CString strID, strDeviceSN, strBenchSN;

	for (int i=0; i<nArrSize; i++)
	{
		pData = CJSON_GetArrayItem(pArrData,i);

		pAttr = CJSON_GetObjectItem(pData, "id");
		if (pAttr != NULL)
		{
			strID = pAttr->valuestring;

			if (strID == STT_CMD_PARA_DeviceSN)
			{
				pAttrVal = CJSON_GetObjectItem(pData, "value");
				if (pAttrVal != NULL)
				{
					strDeviceSN = pAttrVal->valuestring;
				}
			}
			if (strID == STT_CMD_PARA_BenchSN)
			{
				pAttrVal = CJSON_GetObjectItem(pData, "value");
				if (pAttrVal != NULL)
				{
					strBenchSN = pAttrVal->valuestring;
				}
			}
		}	
	}

	CIot_Device oDevice;
	BOOL bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp,strDeviceSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	oDevice.m_nTest_State = DEVICE_TEST_STATE_IDLE;
	g_pTheMySqlApp->StartTransaction();
	bRet = oDevice.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	//���²���̨״̬
	CIot_Bench oBench;
	oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_FINISHED);

	g_pTheMySqlApp->Commit();

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.DB_Update failed![%s]"),strDeviceSN);
		return FALSE;
	}

	return TRUE;
}

/**************************************
���⣺YRQ/AtsState/EVENT/TestProcess
�������ݸ�ʽ
{
	"id":"TestProcess",
	"time":"2021-3-24 10:10:10",
	"data":[
		{
			"id":"DeviceState",
			"value":"�ϸ�|���ϸ�"  //�����Ѳ�����Ŀ���ܽ��ۣ���һ�����ϸ�Ϊ���ϸ�
		},
		{
			"id":"RemainTime",
			"value":"56"   //Ԥ��ʣ��ʱ�䣬��λs
		},
		{
			"id":"TotalTime",
			"value":"142"   //��ʱ�䣬��λs
		},
		{
			"id":"CurrItem",
			"value":"3"     //��ǰ������Ŀ����1��ʼ
		},
		{
			"id":"TotalItems",
			"value":"6"   //�ܵĲ�����Ŀ����
		},
		{
			"id":"DeviceSN",
			"value":"װ��SN"
		}
		{
			"id":"BenchSN",
			"value":"TX001"
		}   //������������̨SN
	]
}
*****************************************/
BOOL CMosquittoServerBase::Process_Iot_TestProcess(const CString &strTestType,CJSON *pJson)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Iot_TestProcess"));

	CJSON* pArrData = CJSON_GetObjectItem(pJson, "data");
	if (pArrData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("JSON��ʽ����δ�鵽data"));
		return FALSE;
	}

	if (pArrData->type != CJSON_Array)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("JSON��ʽ����data����Array"));
		return FALSE;
	}

	int nArrSize = CJSON_GetArraySize(pArrData);
	CJSON *pData = NULL;
	CJSON *pAttr = NULL;
	CJSON *pAttrVal = NULL;
	CString strID, strDeviceSN, strDeviceState;
	long nTotalItems = 0;
	long nCurrItem = 0;

	for (int i=0; i<nArrSize; i++)
	{
		pData = CJSON_GetArrayItem(pArrData,i);

		pAttr = CJSON_GetObjectItem(pData, "id");
		if (pAttr != NULL)
		{
			strID = pAttr->valuestring;

			if (strID == STT_CMD_PARA_DeviceSN)
			{
				pAttrVal = CJSON_GetObjectItem(pData, "value");
				if (pAttrVal != NULL)
				{
					strDeviceSN = pAttrVal->valuestring;
				}
			}

			if (strID == STT_CMD_PARA_CurrItem)
			{
				pAttrVal = CJSON_GetObjectItem(pData, "value");
				if (pAttrVal != NULL)
				{
					nCurrItem = pAttrVal->valueint;
				}
			}
			
			if (strID == STT_CMD_PARA_DeviceState)
			{
				pAttrVal = CJSON_GetObjectItem(pData, "value");
				if (pAttrVal != NULL)
				{
					strDeviceState = pAttrVal->valuestring;
				}
			}
		}	
	}

	//��ѯ����̨����װ�ñ�
	CIot_TestTaskDevice oTestTaskDevice;
	BOOL bRet = oTestTaskDevice.QueryDeviceByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTaskDevice.DB_Select_OwnEx failed![%s]"),strDeviceSN);
		return FALSE;
	}

	if (strDeviceState == _T("0"))
	{
		oTestTaskDevice.m_strDeviceState = _T("���ϸ�");
	}

	//���²����������װ�ñ�Ľ�����Ϣ
	//Э�����ʱ��ҵ�����ܲ����Ѿ��������ʵ�ǰ��Ŀ���ȿ���ֱ�Ӽ���ҵ�����ܲ��ԵĲ�����Ŀ����
	oTestTaskDevice.m_nCurrItem = nCurrItem + oTestTaskDevice.m_nTotalItems_Function;
	oTestTaskDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	g_pTheMySqlApp->Commit();

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.DB_Update failed![%s]"),strDeviceSN);
		return FALSE;
	}

	return TRUE;
}
/******************************
���⣺����̨SN/ AtsState/EVENT/TestCreated
�������ݸ�ʽ��
<sys-state name="" id="TestCreated" mid="0" time="2021-09-08 14:49:03" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="DeviceSN" id="DeviceSN" data-type="string" value="A92E082FA1F3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="BenchSN" id="BenchSN" data-type="string" value="TX001" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="Test_Total_Time_Long" id="Test_Total_Time_Long" data-type="string" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<guidebook name="ATS-Template" id="REALTIMEDATA">
			<job-guide name="��ҵָ��" id="JobGuide" />
			<device name="�豸" id="Device">
				<items name="����" id="Items" tkid="65535" select="1">
					<safety name="����" id="Safety" tkid="65535" select="1" />
					<safety name="����1" id="Safety1" tkid="65535" select="1" />
					<safety name="����2" id="Safety2" tkid="65535" select="1" />
					<safety name="����3" id="Safety3" tkid="65535" select="1" />
					<safety name="����4" id="Safety4" tkid="65535" select="1" />
					<safety name="����5" id="Safety5" tkid="65535" select="1" />
					<safety name="����6" id="Safety6" tkid="65535" select="1" />
					<safety name="����7" id="Safety7" tkid="65535" select="1" />
					<safety name="����8" id="Safety8" tkid="65535" select="1" />
					<safety name="����9" id="Safety9" tkid="65535" select="1" />
					<safety name="����10" id="Safety10" tkid="65535" select="1" />
				</items>
			</device>
		</guidebook>
	</paras>
</sys-state>

����MQTT�������յ�TestCreated�¼������߼���
1����ѯ����̨��iot_bench������״̬�ֶ�status= TEST_BENCH_STATE_PRETEST��1��
2����ѯ���������iot_test_task���²���������е�time_long_total_test��tm_begin�ֶΣ�
3����ѯ�豸��iot_device�����������iot_test_task�Ͳ���̨����װ�ñ�iot_test_task_device�������豸״̬test_state = TEST_DEV_STATE_TESTING��1��
3����ѯ�豸��iot_testapp�����������iot_test_task�Ͳ���̨����װ�ñ�iot_test_tase_testapp�������豸״̬test_state = TEST_DEV_STATE_TESTING��1��
4������GuideBook����������װ�ò�����Ŀʵʱ�����iot_device_item_rslt��
����������ֶΣ�����index_test_task; index_bench; index_device; index_item; 
name_item_path; id_item_path; rsltjdg; state; select_state;
******************************/
//����豸ͬʱ����ʱ��ÿ�������豸����һ��TestCreated�¼�
BOOL CMosquittoServerBase::Process_TestCreated(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestCreated"));
	BOOL bRet = FALSE;

	//Ԥ����ʱ��
	long nTotalTime = 0;
	long nTotalItems = 0;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_TestTotalTimeLong, nTotalTime);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_TotalItems, nTotalItems);

	//��ѯ����̨��
	CIot_Bench oBench;
	bRet = oBench.QueryBenchBySN(g_pTheMySqlApp, strBenchSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oBench.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	if (CMqttServerConfig::IsTestModeFunction_Protocol())
	{
	oBench.m_nStatus = TEST_BENCH_STATE_TESTCREATED;
	}
	else
	{
		oBench.m_nStatus = TEST_BENCH_STATE_Funtion_TESTCREATED;
	}
	

	//��ѯ���������
	CIotTestTask oTestTask;
	oTestTask.m_nIndex_Test_Task = oBench.m_nIndex_Test_Task;
	bRet = oTestTask.DB_Select_OwnEx(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTask.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}
	oTestTask.m_nTime_Long_Total_Test = nTotalTime;
	GetLocalTime(&oTestTask.m_tmTm_Begin);

	//�����ݿ��ȡdevice����
// 	CIot_Devices oIotDevices;
// 	bRet = oIotDevices.QueryDevicesByIndexTask(g_pTheMySqlApp, oTestTask.m_nIndex_Test_Task);
// 	if (!bRet)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oIotDevices.DB_Select_OwnEx failed![%s]"),strBenchSN);
// 		return FALSE;
// 	}
	CString strDeviceSN;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	CIot_Device oIotDevice;
	bRet = oIotDevice.QueryByDeviceSN(g_pTheMySqlApp,strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	//�����ݿ��ȡtestapp����
	CIot_TestApps oIotTestApps;
	bRet = oIotTestApps.QueryTestAppsByIndexTask(g_pTheMySqlApp, oTestTask.m_nIndex_Test_Task);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oIotTestApps.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	//��ѯ����̨����װ�ñ�
	CIot_TestTaskDevice oTestTaskDevice;
	bRet = oTestTaskDevice.QueryDeviceByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTaskDevice.DB_Select_OwnEx failed![%s]"),strDeviceSN);
		return FALSE;
	}

	oTestTaskDevice.m_nTotalItems_Function = nTotalItems;
	oTestTaskDevice.m_nTotalItems = oTestTaskDevice.m_nTotalItems_Function + oTestTaskDevice.m_nTotalItems_Protocol;

	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("TestCreated::nTotalItems = %d, FunctionItems = %d, ProtocolItems = %d"), oTestTaskDevice.m_nTotalItems, oTestTaskDevice.m_nTotalItems_Function ,oTestTaskDevice.m_nTotalItems_Protocol);

	//���²����������װ�õ��ܲ�����Ŀ����
	oTestTaskDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	g_pTheMySqlApp->Commit();

	CIot_DeviceItemRslts oIotDeviceItemRslts;
	CSttParas* pParas =  oSysState.GetSttParas();
	CSttGuideBook* pGuideBook = pParas->GetGuideBook();

	if (pGuideBook == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("�������Դ���***û�з�����ҵָ����  GuideBook = NULL***"));
		return FALSE;
	}

	CSttDevice* pDevice = (CSttDevice*)pGuideBook->FindByClassID(STTGBXMLCLASSID_CSTTDEVICE);

	if (pDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("�������Դ���***��ҵָ����û�з����豸��Ϣ  Device = NULL***"));
		return FALSE;
	}

	CExBaseList oListItem;
	pDevice->SelectAllRootItem(oListItem);
	pDevice->RemoveAll();
	
	CreateIotItemRslts(oIotDeviceItemRslts, oBench.m_nIndex_Test_Task,oBench.m_nIndex_Bench, &oIotDevice, &oListItem);
	g_pTheMySqlApp->StartTransaction();

	//���²���̨״̬
	oBench.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	//���²�������ʱ������ʼʱ��
	oTestTask.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	//����װ�ñ�Ĺ���װ��(���ǹ���װ�ñ�)iot_device
	//oIotDevices.UpdateDeviceState(g_pTheMySqlApp,DEVICE_TEST_STATE_SvrTesting);
	oIotDevice.m_nTest_State = DEVICE_TEST_STATE_SvrTesting;
	oIotDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	//����װ�ñ�Ĺ���������(���ǹ���װ�ñ�)iot_testapp
	oIotTestApps.UpdateTestAppState(g_pTheMySqlApp,TEST_DEV_STATE_TESTING);

	g_pTheMySqlApp->Commit();

	//����iot_device_test
		CXDb_PKeyValue oPKeyValue;
		oIotDeviceItemRslts.DB_InsertEx(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, oPKeyValue);
	
	return TRUE;
}

/*******************************
���⣺����̨SN/ AtsState/EVENT/TestStarted
�������ݸ�ʽ��
<sys-state name="" id="TestStarted" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id=" DeviceSN " data-type="long" value="0" unit=""/>
	</paras>
</sys-state>

�����������յ�TestStarted�¼������߼���
���²���̨iot_bench����state=2�������С���
********************************/
BOOL CMosquittoServerBase::Process_TestStarted(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestStarted"));
	//���²���̨״̬
	CIot_Bench oBench;

	if (CMqttServerConfig::IsTestModeFunction_Protocol())
	{
		return oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_TESTING_FUNCTION);
	}
	else
	{
		return oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_Funtion_TESTING);
	}
}

/******************************
���⣺����̨SN/ AtsState/EVENT/TestStoped
�������ݸ�ʽ��
<sys-state name="" id="TestStoped" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id=" DeviceSN" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>

��վ�������յ�TestStoped�¼������߼���
���²���̨iot_bench����state=3��ֹͣ���ԡ���
*******************************/
BOOL CMosquittoServerBase::Process_TestStoped(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestStoped"));
	//���²���̨״̬
	CIot_Bench oBench;

	if (CMqttServerConfig::IsTestModeFunction_Protocol())
	{
		return oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_TESTSTOPED_FUNCTION);
	}
	else
	{
		return oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_Funtion_STOPED);
	}
}

/*************************
���⣺����̨SN/AtsState/EVENT/ExportFinish
�������ݸ�ʽ��
<sys-state name="" id="ExportReported" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name=" " id="EventID" data-type="string" value=" ExportFinish "/>
		<data name="" id="TotalDevices" data-type="" value="4"/>
		<data name="" id="CurrDevice" data-type="" value="1"/>
		<data name="" id=" DeviceSN " data-type="" value="װ��SN"/>
		<data name="����̨��ʶ" id="TestID" value="����̨SN"/>
		<data name="�����¼�ļ�" id="gbrpt-file" value=" SZNR-TTU202012131427"/>
		<data name="�����������¼�ļ�" id="gbrpt-file_s" value=" http�ļ����䷵�ص�fileName"/>
		<data name="�����ļ�" id="doc-file" value="SZNR-TTU202012131427.doc"/>
		<data name="�����������ļ�" id="doc-file_s" value=" http�ļ����䷵�ص�fileName "/>
	</paras>
</sys-state>

1������deviceID��tm_begin��ѯ���Լ�¼��iot_device_test��¼���Ƿ���ڣ�����������£��������򴴽���
2�����²���̨��¼iot_bench��state=5��������ɣ����ѵ������桿
**************************/
BOOL CMosquittoServerBase::Process_ExportReport(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_ExportReport"));
	BOOL bRet = FALSE;
	CString strEventID;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_EventID,strEventID);
	if (strEventID != SYS_STATE_XEVENT_EVENTID_ExportFinish)
	{
		return FALSE;
	}

	CString strDeviceSN;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceSN,strDeviceSN);
	if (strDeviceSN.IsEmpty())
	{
		return FALSE;
	}

	//��ѯ����̨����װ�ñ�
	CIot_TestTaskDevice oTestTaskDevice;
	bRet = oTestTaskDevice.QueryDeviceByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTaskDevice.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	//��ѯװ��
	CIot_Device oDevice;
	bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	//��ѯ���������
	CIotTestTask oTestTask;
	bRet = oTestTask.QueryByBenchSN(g_pTheMySqlApp, strBenchSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTask.QueryByBenchSN failed![%s]"),strBenchSN);
		return FALSE;
	}

	//�����ݿ��ȡtestapp����
	CIot_TestApps oIotTestApps;
	bRet = oIotTestApps.QueryTestAppsByIndexTask(g_pTheMySqlApp, oTestTask.m_nIndex_Test_Task);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oIotTestApps.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	CIot_DeviceItemRslts oDeviceItemRslts;
	CIot_DeviceHisTest oDeviceHisTest;
	oDeviceHisTest.m_nIndex_Device = oDevice.m_nIndex_Device;
	oDeviceHisTest.m_nIndex_User = oTestTask.m_nIndex_Tester;
	oDeviceHisTest.m_nIndex_Test_Task = oTestTask.m_nIndex_Test_Task;
	oDeviceHisTest.m_tmTm_Begin = oTestTask.m_tmTm_Begin;
	oDeviceHisTest.m_tmTm_End = oTestTask.m_tmTm_End;
	oDeviceHisTest.m_strName = oTestTask.m_strName;

	oSysState.GetParasDataValueByID(XPARA_ID_DOCFILE,oDeviceHisTest.m_strDoc_File);
	oSysState.GetParasDataValueByID(XPARA_ID_DOCRPTFILE_S,oDeviceHisTest.m_strDoc_File_S);
	oSysState.GetParasDataValueByID(XPARA_ID_GBRPTFILE,oDeviceHisTest.m_strGbrpt_File);
	oSysState.GetParasDataValueByID(XPARA_ID_GBRPTFILE_S,oDeviceHisTest.m_strGbrpt_File_S);
	oSysState.GetParasDataValueByID(XPARA_ID_PDFFILE,oDeviceHisTest.m_strPdf_File);
	oSysState.GetParasDataValueByID(XPARA_ID_PDFFILE_S,oDeviceHisTest.m_strPdf_File_S);
	oDeviceHisTest.m_nReport_Result = oDeviceItemRslts.GetDeviceReportResult(g_pTheMySqlApp,oDevice.m_nIndex_Device,oTestTask.m_nIndex_Test_Task);
	oDeviceHisTest.m_nTest_Type = DEVICE_TEST_TYPE_SERVICE;

	//����װ�úͿ�ʼʱ���ѯ������������룬���������
	bRet = oDeviceHisTest.UpdateDeviceHisTest(g_pTheMySqlApp);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDeviceHisTest.UpdateDeviceHisTest failed![%s]"),strBenchSN);
		return FALSE;
	}

	//������չ������ñ����¼ҵ�����ܲ��Ե�ԭʼ��¼�ļ�
	CIot_DeviceReportEx oReportEx;
	oReportEx.m_nIndex_Device_Histest = oDeviceHisTest.m_nIndex_Device_Histest;
	oSysState.GetParasDataValueByID(XPARA_ID_DOCRPTFILE_EX,oReportEx.m_strDoc_File);
	oSysState.GetParasDataValueByID(XPARA_ID_DOCRPTFILE_EX_S,oReportEx.m_strDoc_File_S);
	//�о͸��£�û�оͲ���
	bRet = oReportEx.UpdateDeviceReportEx(g_pTheMySqlApp);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oReportEx.UpdateDeviceReportEx failed![%s]"),strBenchSN);
		//�˴����ܷ���FALSE����Ϊ�������еĲ��Զ�����չ����
		//return FALSE;
	}

	//���²���̨״̬
	CIot_Bench oBench;

	if (CMqttServerConfig::IsTestModeFunction_Protocol())
	{
	bRet = oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_EXPORTED);
	}
	else
	{
		bRet = oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_Funtion_EXPORTED);
	}
	
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oBench.UpdateBenchState failed![%s]"),strBenchSN);
		return FALSE;
	}

	//���±����豸��״̬
	oDevice.m_nTest_State = DEVICE_TEST_STATE_Standby;
	oDevice.m_nTest_Rslt = GetTestRsltByDeviceState(oTestTaskDevice.m_strDeviceState);
	bRet = oDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.DB_Update failed![%s]"),strDeviceSN);
		return FALSE;
	}

	long nCurrDevice = 0;
	long nTotalDevices = 1;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_CurrDevice,nCurrDevice);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_TotalDevices,nTotalDevices);

	if (nCurrDevice == nTotalDevices)
	{
		//����װ�ñ�Ĺ���������(���ǹ���װ�ñ�)iot_testapp
		oIotTestApps.UpdateTestAppState(g_pTheMySqlApp,TEST_DEV_STATE_STANDBY);
	}

	return bRet;
}

/********************************
���⣺����̨SN/AtsState/CloseTest/REPLY
�������ݸ�ʽ��
<sys-state name="" id=" CloseTest " mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="1|2|3|4" unit=""/>
	</paras>
</sys-state>

�����������յ�CloseTest/REPLY������߼���
ִ�йرղ��Ժ����߼���
1��	���²���̨iot_bench����state=0�����С���
2��	����װ�ñ�iot_device��iot_testapp��test_state=0�����С���
3��	ɾ������̨������ʵʱ���¼��iot_bench_device��iot_device_item_rslt
4��	ɾ����ǰ����װ����ʱʵʱ�����ļ���
**********************************/
BOOL CMosquittoServerBase::Process_CloseTestReply(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_CloseTestReply"));

	CString strStatus;
	oSysState.GetParasDataValueByID(STT_SYS_STATE_ID_ExecStatus,strStatus);
	if (strStatus != _T("3"))
	{
		return FALSE;
	}

	//��ѯ����̨��
	CIot_Bench oBench;
	BOOL bRet = oBench.QueryBenchBySN(g_pTheMySqlApp, strBenchSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oBench.QueryBenchBySN failed![%s]"),strBenchSN);
		return FALSE;
	}
	long nIndex_TestTask = oBench.m_nIndex_Test_Task;

	if (CMqttServerConfig::IsTestModeFunction_Protocol())
	{
	oBench.m_nStatus = TEST_BENCH_STATE_NORMAL;
	}
	else
	{
		oBench.m_nStatus = TEST_BENCH_STATE_Funtion_NORMAL;
	}
	
	oBench.m_nIndex_Test_Task = 0;

	//��ѯ���������
	CIotTestTask oTestTask;
	oTestTask.m_nIndex_Test_Task = nIndex_TestTask;
	bRet = oTestTask.DB_Select_OwnEx(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTask.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	//�����ݿ��ȡdevice����
	CIot_Devices oIotDevices;
	bRet = oIotDevices.QueryDevicesByIndexTask(g_pTheMySqlApp, oTestTask.m_nIndex_Test_Task);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oIotDevices.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	CString strDeleteBenchDeviceSql,strDeleteItemRsltsSql;
	CString strBenchDeviceTable,strItemRsltsTable,strIndex_TestTaskKey;
	strBenchDeviceTable = CIot_AtsMngrXmlRWKeys::CIot_TestTaskDeviceKey();
	strItemRsltsTable = CIot_AtsMngrXmlRWKeys::CIot_DeviceItemRsltKey();
	strIndex_TestTaskKey = CIot_AtsMngrXmlRWKeys::Index_Test_TaskKey();

	//ɾ��ʵʱ��
	strDeleteBenchDeviceSql.Format(_T("delete from %s where %s=%d")
		,strBenchDeviceTable,strIndex_TestTaskKey,oTestTask.m_nIndex_Test_Task);
	strDeleteItemRsltsSql.Format(_T("delete from %s where %s=%d")
		,strItemRsltsTable,strIndex_TestTaskKey,oTestTask.m_nIndex_Test_Task);

	//�����ݿ��ȡtestapp����
	CIot_TestApps oIotTestApps;
	bRet = oIotTestApps.QueryTestAppsByIndexTask(g_pTheMySqlApp, oTestTask.m_nIndex_Test_Task);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oIotTestApps.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	g_pTheMySqlApp->StartTransaction();

	//���²���̨״̬
	oBench.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	//����װ�ñ�Ĺ���װ��(���ǹ���װ�ñ�)iot_device
	oIotDevices.UpdateDeviceState(g_pTheMySqlApp,DEVICE_TEST_STATE_IDLE);

	//����װ�ñ�Ĺ���������(���ǹ���װ�ñ�)iot_testapp
	oIotTestApps.UpdateTestAppState(g_pTheMySqlApp,TEST_DEV_STATE_NORMAL);

	//ɾ��ʵʱ��
	g_pTheMySqlApp->ExecuteCmd(strDeleteBenchDeviceSql);
	g_pTheMySqlApp->ExecuteCmd(strDeleteItemRsltsSql);

	g_pTheMySqlApp->Commit();

	//ɾ����ǰ����װ����ʱʵʱ�����ļ���
	oIotDevices.DeleteRTDeviceRpt(g_strRTDeviceRptPath);

	return TRUE;
}

//��ѯָ��������ʵʱ���ݼ�¼
BOOL CMosquittoServerBase::QueryDeviceItemRslt(const CString &strBenchSN,CSttSysState &oSysState
											   ,CIot_DeviceItemRslt &oDeviceItemRslt)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::QueryDeviceItemRslt"));
	BOOL bRet = FALSE;
	CString strDeviceSN,strItemPath;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceSN,strDeviceSN);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_ItemPath,strItemPath);
	if (strDeviceSN.IsEmpty() || strItemPath.IsEmpty())
	{
		return FALSE;
	}

	//��ѯװ��
	CIot_Device oDevice;
	bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	//��ѯ���������
	CIotTestTask oTestTask;
	bRet = oTestTask.QueryByBenchSN(g_pTheMySqlApp, strBenchSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTask.QueryByBenchSN failed![%s]"),strBenchSN);
		return FALSE;
	}

	//��ѯָ��������ʵʱ���ݼ�¼
	bRet = oDeviceItemRslt.QueryDeviceItemRslt(g_pTheMySqlApp, oTestTask.m_nIndex_Test_Task
		,oDevice.m_nIndex_Device,strItemPath);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDeviceItemRslt.QueryDeviceItemRslt failed![%s]"),strBenchSN);
		return FALSE;
	}

	return TRUE;
}

BOOL CMosquittoServerBase::IsItemBaseClassID(UINT nClassID)
{
	return ( (nClassID & STTGBXMLCLASSID_CSTTITEMBASE) == STTGBXMLCLASSID_CSTTITEMBASE);
}

/************************************
���⣺����̨SN/ AtsState/EVENT/ItemStateChanged
�������ݸ�ʽ��
<sys-state name="" id="ItemStateChanged" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id=" DeviceSN " data-type="" value="װ��SN"/>
		<data id="DeviceIndex" data-type="long" value="0" unit=""/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
		<data id="ItemIndex" data-type="long" value="2" unit=""/>
		<data id=" ItemPath " data-type="string" value="***$MacroTest1" unit=""/>
		<data id="State" data-type="string" value="TESTING" unit=""/>
	</paras>
</sys-state>

�����������յ�ItemStateChanged�¼������߼���
���ݲ���̨SN������װ��SN��ItemPath��Ϣ��λiot_device_item_rslt��¼������State��Ϣ����state�ֶΣ�rsltjdg��rsltdsc��
����״̬˵��������ݿ��˵����
************************************/
BOOL CMosquittoServerBase::Process_ItemStateChanged(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_ItemStateChanged"));
	//��ѯָ��������ʵʱ���ݼ�¼
	CIot_DeviceItemRslt oDeviceItemRslt;
	BOOL bRet = QueryDeviceItemRslt(strBenchSN,oSysState,oDeviceItemRslt);
	if (!bRet)
	{
		return bRet;
	}

	long nState;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_State,nState);
	CString strItemPath;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_ItemPath, strItemPath);

	bRet = oDeviceItemRslt.UpdateRslt(g_pTheMySqlApp, nState);
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++Process_ItemStateChanged++++++%s++++++%ld++++����ֵ = %d"), strItemPath, nState, bRet);

	return bRet;
}

/*********************************
���⣺����̨SN/AtsState/EVENT/REPORT
�������ݸ�ʽ��
<sys-state name="" id="" mater-host="" ret-type="REPORT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id=" DeviceSN " data-type="" value="װ��SN"/>
		<data id="ItemIndex" data-type="long" value="2" unit=""/>
		<data id="ItemPath" data-type="string" value="MacroTest1" unit=""/>
		<data id="State" data-type="string" value="ELIGIBLE" unit=""/>
		<reports>
			<report name="1970-1-1 1:28:48" id="Rpt00_1_0" begintime="1970-1-1 1:28:48" endtime="">
				<values name="" id="">
					<value id="RsltJdg" value="1"/>
					<value id="RsltDsc" value="�ϸ�"/>
				</values>
				<dataset name="Dataset" id="dataset" data-type="" write-mode="0" index="0">
					���ݶ���
				</dataset>
			</report>
			������������������.
		</reports>
		<rpt-map-datas>����ӳ������</rpt-map-datas>
	<paras>
</sys-state>

�����������յ�REPORT�¼������߼���
1��	���ݲ���̨SN������װ��SN��ItemPath��Ϣ��λiot_device_item_rslt��¼��
2��	��ȡreports�ڵ㱣�浽 ��Ӧװ��SN\����.xml;
3��	����file_report���ļ�����Ϊreports�ڵ�xml�ַ�������file_report_s��file_pkgs��file_pkgs_s�ֶΣ�
**********************************/
BOOL CMosquittoServerBase::Process_Report(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Report"));
	//��ѯָ��������ʵʱ���ݼ�¼
	CIot_DeviceItemRslt oDeviceItemRslt;
	BOOL bRet = QueryDeviceItemRslt(strBenchSN,oSysState,oDeviceItemRslt);
	if (!bRet)
	{
		return bRet;
	}

	CSttParas* pParas = oSysState.GetSttParas();
	CSttReports *pReports = pParas->GetSttReports();

	if (pReports != NULL)
	{
		CString strFileRpt,strFileRpt_s;
		strFileRpt.Format(_T("%d.xml"),oDeviceItemRslt.m_nIndex_Item_Rslt);

		//strFileRpt_s.Format(_T("%s%d\\%s")
			//,g_strRTDeviceRptPath,oDeviceItemRslt.m_nIndex_Device,strFileRpt);
		strFileRpt_s.Format(_T("%s%d\\")
		,g_strRTDeviceRptPath,oDeviceItemRslt.m_nIndex_Device);
		CreateAllDirectories(strFileRpt_s);
		strFileRpt_s.AppendFormat(_T("%s"), strFileRpt);

		CString strRealPath;
		strRealPath.Format(_T("/%d/%s"),oDeviceItemRslt.m_nIndex_Device,strFileRpt);

		pReports->SaveXmlFile(strFileRpt_s,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	//47\93.xml
	//C:\EPOTO\IotAtsMngr\DB\RTDeviceRpt
	//HTTP://111111:1111/
#ifdef _ITEM_RSLT_REPORT_USE_HTTP_
		strFileRpt_s = strRealPath;
#endif

		oDeviceItemRslt.m_strFile_Report = strFileRpt;
		oDeviceItemRslt.m_strFile_Report_S = strFileRpt_s;

		return oDeviceItemRslt.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	}

	return TRUE;
}

/*******************************
���⣺����̨SN/AtsState/EVENT/TestFinished
�������ݸ�ʽ��
<sys-state name="" id="TestFinished" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id=" DeviceSN " data-type="" value="װ��SN"/>
		<data id="DeviceIndex" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>

�����������յ�TestFinished�¼������߼���
���²���̨iot_bench��state=4��������ɣ�δ�������桿��tm_end;
*******************************/
BOOL CMosquittoServerBase::Process_TestFinished(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestFinished"));
	//��ѯ����̨��
	CIot_Bench oBench;
	BOOL bRet = oBench.QueryBenchBySN(g_pTheMySqlApp, strBenchSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oBench.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	if (CMqttServerConfig::IsTestModeFunction_Protocol())
	{
	oBench.m_nStatus = TEST_BENCH_STATE_FINISHED;
	}
	else
	{
		oBench.m_nStatus = TEST_BENCH_STATE_Funtion_FINISHED;
	}	

	//��ѯ���������
	CIotTestTask oTestTask;
	oTestTask.m_nIndex_Test_Task = oBench.m_nIndex_Test_Task;
	bRet = oTestTask.DB_Select_OwnEx(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTask.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}
	GetLocalTime(&oTestTask.m_tmTm_End);

	g_pTheMySqlApp->StartTransaction();

	//���²���̨״̬
	oBench.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	//���²����������ʱ��
	oTestTask.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	g_pTheMySqlApp->Commit();

	return TRUE;
}
/*******************************
<sys-state name="" id="TestProcess" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
		<data name="" id="BenchSN" data-type="" value="����̨SN/"/>
		<data id="TotalItems" data-type="long" value="100" unit=""/>
		<data id="CurrItem" data-type="long" value="30" unit=""/>
		<data id="TotalTime" data-type="long" value="6000" unit="s"/>
		<data id="RemainTime" data-type="long" value="3000" unit="s"/>
		<data name="" id="DeviceState" data-type="" value="�ϸ�|���ϸ�"/>
	</paras>
</sys-state>
���⣺����̨SN/AtsState/EVENT/ TestProcess
�յ�TestProcess�¼������²���̨�������ݿ��iot_test_task_device
�������еĲ��Խ�����ص��ֶ�
*******************************/
BOOL CMosquittoServerBase::Process_TestProcess(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestProcess"));
	CString strDeviceSN;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	//��ѯ����̨����װ�ñ�
	CIot_TestTaskDevice oTestTaskDevice;
	BOOL bRet = oTestTaskDevice.QueryDeviceByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTaskDevice.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	CString strDeviceState;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceState, strDeviceState);
	long nTotalItems, nCurrItem, nTotalTime, nRemainTime;
	nTotalTime = nCurrItem = nTotalItems = nRemainTime = 0;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_TotalItems, nTotalItems);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_CurrItem, nCurrItem);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_TotalTime, nTotalTime);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_RemainTime, nRemainTime);
	strDeviceState = Gb_GetTestStateDesc(strDeviceState);

	if (strDeviceState == _T("δ����"))
	{
		strDeviceState = _T("����");
	}

	oTestTaskDevice.m_nRemainTime = nRemainTime;
	oTestTaskDevice.m_nTotalTime = nTotalTime;
	//oTestTaskDevice.m_nTotalItems = nTotalItems;  ��Ŀ������ˢ�£��ڴ�������ʱ�Ѿ�ˢ��
	oTestTaskDevice.m_nCurrItem = nCurrItem;
	oTestTaskDevice.m_strDeviceState = strDeviceState;

	//���²����������ʱ��
	oTestTaskDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	g_pTheMySqlApp->Commit();
	return TRUE;
}

BOOL CMosquittoServerBase::Process_UploadReportFinished(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_UploadReportFinished"));
	CString strDocFile, strDocFile_s, strDocFileEx, strDocFileEx_s, strDeviceSN, strPcapFile, strPcapFile_s;
	//��Ӣ����ȷ���Ĳ�����ID ������ϵͳ�в�һ�� ����ͳһ
	oSysState.GetParasDataValueByID(_T("doc_file"), strDocFile);
	oSysState.GetParasDataValueByID(_T("doc_file_s"), strDocFile_s);
	oSysState.GetParasDataValueByID(_T("doc_ex_file"), strDocFileEx);
	oSysState.GetParasDataValueByID(_T("doc_ex_file_s"), strDocFileEx_s);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);
	oSysState.GetParasDataValueByID(_T("pcap_file"), strPcapFile);
	oSysState.GetParasDataValueByID(_T("pcap_file_s"), strPcapFile_s);

	CIot_Device oDevice;
	BOOL bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp,strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	//�ⲿϵͳ��������
	//CIot_DeviceOutReports oOutReports;
	CIot_DeviceOutReport oOutReport;
	oOutReport.m_nIndex_Device = oDevice.m_nIndex_Device;
	oOutReport.m_strDoc_File = strDocFile;
	oOutReport.m_strDoc_File_s = strDocFile_s;
	oOutReport.m_strPcap_File = strPcapFile;
	oOutReport.m_strPcap_File_s = strPcapFile_s;
	bRet = oOutReport.UpdateDeviceOutReport(g_pTheMySqlApp);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oOutReport.UpdateDeviceOutReport failed![%s]"),strDeviceSN);
	}
	//CXDb_PKeyValue oPkValue;
	//oOutReports.DB_InsertEx(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, oPkValue);


	//�ⲿϵͳ��չ�����
	//CIot_DeviceOutReportExs oOutReportExs;
	CIot_DeviceOutReportEx oOutReportEx;
	oOutReportEx.m_nIndexRpt = oOutReport.m_nIndex_Rpt;   //���������������������
	oOutReportEx.m_strDoc_File = strDocFileEx;
	oOutReportEx.m_strDoc_File_s = strDocFileEx_s;
	bRet = oOutReportEx.UpdateDeviceOutReportEx(g_pTheMySqlApp);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oOutReportEx.UpdateDeviceOutReportEx failed![%s]"),strDeviceSN);
	}
	//oOutReportExs.DB_InsertEx(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, oPkValue);

	return TRUE;
}

//2021-10-10  lijunqing
/**********************
<group>
	<data name="" id="DeviceSN" value="1921681112"/>
	<group name="" id="RTDATA">
		<data name="" id="RealTemp" value="23.15"/>
		<data name="" id="SetTemp" value="22.00"/>
	</group>
</group>
****************************/
//��������������ʵʱ���ݣ�ֻ����Ҫ�����ߵ����ݣ���������������д���ݿ�
BOOL CMosquittoServerBase::Process_RtData(const char* strTopic, const char* strMsg)
{
// 	CIot_RTDeviceData oRtDeviceData;
// 	oRtDeviceData.WriteToDB_ByBuffer((char*)strMsg);

	BOOL bRet = FALSE;
	long nLen = strlen(strMsg);
	CDataGroup oGroup;
	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	oGroup.SetXml_UTF8((char *)strMsg, nLen, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	CString strDeviceSN;
	oGroup.GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);

	//�ȸ���SN����ѯ��Ӧ�Ĳ�����
	CIot_TestApp oTestApp;
	bRet = oTestApp.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CMosquittoServerBase::Process_RtData++++++oTestApp.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	//�����߶�����У���ѯ���豸���͵����ߵ����ݶ���
	CIot_RTDeviceHisDataTitles oDataTitles;
	bRet = oDataTitles.QueryRTDeviceHisDataTitlesByDeviceType(g_pTheMySqlApp, oTestApp.m_nIndex_Device_Type);
	
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CMosquittoServerBase::Process_RtData++++++oDataTitles.QueryRTDeviceHisDataTitlesByDeviceType failed![%d]")
			,oTestApp.m_nIndex_Device_Type);
		return FALSE;
	}

	CDataGroup *pParas = (CDataGroup *)oGroup.FindByID(_T("RTDATA"));
	//����ʵʱ���ݵ�ʵʱ������ʷ����
	bRet = oDataTitles.InsertRtDeviceHisData(g_pTheMySqlApp, strDeviceSN, pParas);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CMosquittoServerBase::Process_RtData++++++oDataTitles.InsertRtDeviceHisData failed![%s]"), strDeviceSN);
		return FALSE;
	}

	return TRUE;
}

//topic��DeviceSN/HeartBeat
/*
<group id="">
	<data id="DeviceSN" name="" value="PAL-E-ZH.0016"/>
</group>
*/
/*
�����豸sn����ѯiot_testapp���ж�isupdate�ֶ��Ƿ�Ϊ1��
��Ϊ1���򲻴���
����Ϊ1������е���ʹ����������ʹ���������ۼӡ�����isupdate�ֶ���1��
*/
BOOL CMosquittoServerBase::Process_TestApp_HeartBeat(const char* strTopic, const char* strMsg)
{
	BOOL bRet = FALSE;
	long nLen = strlen(strMsg);
	CDataGroup oGroup;
	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	oGroup.SetXml_UTF8((char *)strMsg, nLen, CDataMngrXmlRWKeys::g_pXmlKeys);
	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;

	CString strDeviceSN;
	oGroup.GetDataValue(STT_CMD_PARA_DeviceSN, strDeviceSN);

	//�ȸ���SN����ѯ��Ӧ�Ĳ�����
	CIot_TestApp oTestApp;
	bRet = oTestApp.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CMosquittoServerBase::Process_TestApp_HeartBeat++++++oTestApp.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	if (oTestApp.m_nIsUpdate == 1)
	{
		return TRUE;
	}

	oTestApp.m_nUseDays += 1;
	oTestApp.m_nUseDaysAll += 1;
	oTestApp.m_nIsUpdate = 1;
	oTestApp.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	return TRUE;
}

//topic:DeviceSN/TestState/CreateDevice/REPLY
/*
<sys-state name="" id="CreateDevice" mid="0" time="2021-10-22 16:34:14" mater-host="" ret-type="REPLY" id-cmd="test-cmd">
	<paras name="" id="">
		<data name="DeviceSN" id="DeviceSN" data-type="string" value="PAL_E_0028" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="ExecStatus" id="ExecStatus" data-type="string" value="2" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	</paras>
</sys-state>
*/
//�����豸SN����ѯiot_testapp����ʹ�ô���+1��
BOOL CMosquittoServerBase::Process_TestApp_CreateDeviceReply(const char* strTopic, const char* strMsg)
{
	long nLen = strlen(strMsg);
	CSttSysState oSysState;
	PraseCmdBuf(&oSysState, strMsg, nLen, MQTT_DATA_FORMAT_XML);

	if (oSysState.Get_ExecStatus() != STT_CMD_ExecStatus_SUCCESS)
	{
		return FALSE;
	}

	CString strDeviceSN;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	//�ȸ���SN����ѯ��Ӧ�Ĳ�����
	CIot_TestApp oTestApp;
	BOOL bRet = oTestApp.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CMosquittoServerBase::Process_TestApp_HeartBeat++++++oTestApp.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	oTestApp.m_nUseCounts += 1;
	oTestApp.DB_Update(g_pTheMySqlApp,CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	return TRUE;
}

void CMosquittoServerBase::PraseCmdBuf(CSttCmdBase* pSttCmd, const char* pBuf, int nLen, const CString& strFormat)
{
	if(strFormat == MQTT_DATA_FORMAT_XML)	
	{
		SetXmlBufferLen(nLen * 2);
		pSttCmd->PraseCmdBuf(const_cast<char*>(pBuf), 
			nLen, m_pszXmlBuffer, MQTT_DATA_FORMAT_XML);
	}
	else
		pSttCmd->PraseCmdBuf(const_cast<char*>(pBuf),
		nLen, NULL,MQTT_DATA_FORMAT_JSON);
}

BOOL CMosquittoServerBase::HasValidChild(CExBaseList* pList)
{
	POS posChild = pList->GetHeadPosition();
	CExBaseList *pChildItem = NULL;

	while(posChild != NULL)
	{
		pChildItem = (CExBaseList *)pList->GetNext(posChild);

		if (IsItemBaseClassID(pChildItem->GetClassID()))
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CMosquittoServerBase::SetXmlBufferLen(long nLen)
{
	if (nLen <= m_nXmlBufferLen)
	{
		return;
	}

	if (m_pszXmlBuffer != NULL)
	{
		delete m_pszXmlBuffer;
		m_pszXmlBuffer = NULL;
	}

	m_pszXmlBuffer = new char [nLen+10];
	m_nXmlBufferLen = nLen;
}

void CMosquittoServerBase::CreateIotItemRslts(CIot_DeviceItemRslts& oIotDeviceItemRslts, long nIndex_TestTask,long nIndex_Bench, 
											  CIot_Device *pIotDevice, CExBaseList* pList)
{
	BOOL bHasValidChild = FALSE;

	if (pList->m_strID == _T("RAin_U"))
	{
		long i = 0;
	}

	if (IsItemBaseClassID(pList->GetClassID()))
	{
		bHasValidChild = HasValidChild(pList);

		if (!bHasValidChild)
		{
			NewIotItemRslt(oIotDeviceItemRslts, nIndex_TestTask,nIndex_Bench, pIotDevice, (CSttItemBase*)pList);
			return;
		}
	}

	POS pos = pList->GetHeadPosition();
	while (pos != NULL)
	{
		CExBaseList* pItem = (CExBaseList*)pList->GetNext(pos);

		if (!IsItemBaseClassID(pItem->GetClassID()))
		{
			continue;
		}

		bHasValidChild = HasValidChild(pItem);

		if (bHasValidChild)
		{
	 		if (pItem->GetClassID() != STTGBXMLCLASSID_CSTTITEMS)
	 		{
	 			NewIotItemRslt(oIotDeviceItemRslts, nIndex_TestTask,nIndex_Bench, pIotDevice, (CSttItemBase*)pItem);
	 		}

			POS posChild = pItem->GetHeadPosition();
			CExBaseList *pChildItem = NULL;

			while(posChild != NULL)
			{
				pChildItem = (CExBaseList *)pItem->GetNext(posChild);

				CreateIotItemRslts(oIotDeviceItemRslts, nIndex_TestTask,nIndex_Bench, pIotDevice, pChildItem);
			}
		}
		else
		{
			NewIotItemRslt(oIotDeviceItemRslts, nIndex_TestTask,nIndex_Bench, pIotDevice, (CSttItemBase*)pItem);
		}
	}
}

void CMosquittoServerBase::NewIotItemRslt(CIot_DeviceItemRslts& oIotDeviceItemRslts, long nIndex_TestTask,long nIndex_Bench, 
										  CIot_Device *pIotDevice, CSttItemBase* pItem)
{
	//��������ʵʱ��
	CIot_DeviceItemRslt* oIotDeviceItemRslt = new CIot_DeviceItemRslt();
	oIotDeviceItemRslt->m_nIndex_Test_Task = nIndex_TestTask;
	oIotDeviceItemRslt->m_nIndex_Bench = nIndex_Bench;
	oIotDeviceItemRslt->m_nIndex_Device = pIotDevice->m_nIndex_Device;
	oIotDeviceItemRslt->m_nIndex_Item = 0;//Ĭ��Ϊ0
	CString strTemp = pItem->GetNamePathEx(STTGBXMLCLASSID_CSTTDEVICE, TRUE);
	strTemp = pIotDevice->m_strName + strTemp.Mid(strTemp.Find(_T("$")));
	oIotDeviceItemRslt->m_strName_Item_Path = strTemp;
	strTemp = pItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, TRUE);
	strTemp = pIotDevice->m_strID + strTemp.Mid(strTemp.Find(_T("$")));
	oIotDeviceItemRslt->m_strId_Item_Path = strTemp;
	oIotDeviceItemRslt->m_nRsltjdg = 1;//Ĭ��Ϊ1
	oIotDeviceItemRslt->m_nState = pItem->m_nState;
	oIotDeviceItemRslt->m_nSelect_State = pItem->m_nSelect;
	oIotDeviceItemRslts.AddNewChild(oIotDeviceItemRslt);
}