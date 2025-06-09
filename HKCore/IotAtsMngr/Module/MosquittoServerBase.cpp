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
// 	oDBServerInfo.m_strDbName = _T("tyh");//数据库名称
// 	oDBServerInfo.m_strUserName = _T("root");
// 	oDBServerInfo.m_strPasswd = _T("tyh12345678");
// 	oDBServerInfo.m_iPort = 3306;
// 	InitMySqlDB(oDBServerInfo);

	oDBServerInfo.m_strDbName = CMqttServerConfig::GetDBName();//_T("tyh");//数据库名称
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

	//release顺序应该与create相反
	CMqttServerConfig::Release();
	CSttMqttClientEngineConfig::Release();
	//CGbXMLKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CSttCmdDefineXmlRWKeys::Release();
	CIot_AtsMngrXmlRWKeys::Release();
}

// 服务端发送topic数据消息给指定topic的客户端
BOOL CMosquittoServerBase::SendTopicData(const CString& strTopic, char *pBuf, long nLen)
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

void CMosquittoServerBase::SetMsgWnd(const HWND hWnd)
{
	m_hWnd = hWnd;
	// 设置一个全局的HWND变量,使Mqtt服务端知道客户端数据需要向哪个窗口进行转发
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

void CMosquittoServerBase::Process_Connect(const char* strIP, const char* strID)
{
	CExBaseObject* pClient = m_oClientList.FindChildByID(strID);
	if(pClient)
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【错误】: 存在一个相同ID的客户端!"));
	else
		m_oClientList.AddNewChild(NewMosquittoClient(strIP, strID));
}

void CMosquittoServerBase::Process_Disconnect(const char* strID)
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

void CMosquittoServerBase::Process_Subscribe(const char* strTopic, const char* strID)
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

void CMosquittoServerBase::Process_Unsubscribe(const char* strTopic, const char* strID)
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

/******************************
测试台SN/AtsState/EVENT/TestCreated
测试台SN/AtsState/EVENT/TestStarted
测试台SN/AtsState/EVENT/TestStoped
测试台SN/AtsState/EVENT/ExportFinish
测试台SN/AtsState/CloseTest/REPLY
测试台SN/AtsState/EVENT/ItemStateChanged
测试台SN/AtsState/EVENT/TestFinished
*******************************/
BOOL CMosquittoServerBase::Process_Ats_Event(const char* strTopic, const char* strMsg)
{
	int nLen = strlen(strMsg);
	CStringTokenizer oStrTokenizer;
	oStrTokenizer.Init(strTopic, '/');
	int nCnt = oStrTokenizer.GetStringsCount();

	CString strBenchSN = oStrTokenizer.GetToken(0);
	CString strEventID = oStrTokenizer.GetToken(nCnt - 1);

	//判断format不用主题判断，采用msg的第一个字符是<还是{
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
	//9月30日演示的版本中 该事件的主题是：IOT/AtsState/EVENT/UploadReportFinished
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

	//9月30日演示的版本中 该事件的主题是：IOT/AtsState/EVENT/UploadReportFinished
	else if (strEventID == SYS_STATE_EVENT_UploadReportFinished)
	{
		int nLen = strlen(strMsg);

		//判断format不用主题判断，采用msg的第一个字符是<还是{
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
测试台SN/AtsState/REPORT
*******************************/
BOOL CMosquittoServerBase::Process_Ats_Report(const char* strTopic, const char* strMsg)
{
	//CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Ats_Report"));
	int nLen = strlen(strMsg);
	CStringTokenizer oStrTokenizer;
	oStrTokenizer.Init(strTopic, '/');
	int nCnt = oStrTokenizer.GetStringsCount();

	CString strBenchSN = oStrTokenizer.GetToken(0);

	//判断format不用主题判断，采用msg的第一个字符是<还是{
	CSttSysState oSysState;
	if(strMsg[0] == '<')
		PraseCmdBuf(&oSysState, strMsg, nLen, MQTT_DATA_FORMAT_XML);
	else
		PraseCmdBuf(&oSysState, strMsg, nLen, MQTT_DATA_FORMAT_JSON);

	return Process_Report(strBenchSN,oSysState);
}

/*********************
主题：[IOT|MQTT]/AtsState/EVENT/TestCreated
内容：
{
	"id":"TestCreated",
	"time":"2021-3-24 10:10:10",
	"DeviceSN ":"123456123456",
	"TotalItems":"6",   //总的项目数，需新增
	"BenchSN":"TX001"              //测试台SN，需新增
}
************************/
//在创建测试时，记录总项目数量
//在目前网页操作的流程中，协议一致性的测试创建要先于性能测试的创建
BOOL CMosquittoServerBase::Process_Iot_TestCreated(const CString &strTestType,CJSON *pJson)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Iot_TestCreated"));

	//先不更新测试台的状态
// 	CJSON* pBenchSNJson = CJSON_GetObjectItem(pJson, STT_CMD_PARA_BenchSN);
// 	if (pBenchSNJson == NULL)
// 	{
// 		return FALSE;
// 	}
// 	CString strBenchSN = pBenchSNJson->valuestring;
// 	//更新测试台状态
// 	CIot_Bench oBench;
// 	oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_TESTCREATED);

	CJSON* pDeviceSNJson = CJSON_GetObjectItem(pJson, STT_CMD_PARA_DeviceSN);
	if (pDeviceSNJson == NULL)
	{
		return FALSE;
	}
	CString strDeviceSN = pDeviceSNJson->valuestring;

	//查询测试台关联装置表
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

	//更新测试任务结束时间
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
主题：[IOT|MQTT]/AtsState/EVENT/TestStarted 
{
	"id":" TestStarted",
	"time":"2021-3-24 10:10:10",
	"DeviceSN":"123456123456",
	"BenchSN":"1253684"
}
*****************************/
BOOL CMosquittoServerBase::Process_Iot_TestStarted(const CString &strTestType,CJSON *pJson)
{
	//关于测试台的状态，在Process_Ats_TestFinished事件中，已经设置为“测试结束”；
	//进入英锐祺协议一致性测试流程后，将无法修改测试台状态。
	//后续改进方案：打开英锐祺的页面时，传递的参数新增BenchSN。在英锐祺的测试事件中，将该BenchSN作为参数返回。
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
 	//更新测试台状态
 	CIot_Bench oBench;
 	oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_TESTING_PROTOCOL);

	return TRUE;
}

/*****************************
主题：[IOT|MQTT]/AtsState/EVENT/TestStoped
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

	//被测设备没有测试停止的状态，故此处不需要更新被测设备的状态

	CJSON* pBenchSNJson = CJSON_GetObjectItem(pJson, STT_CMD_PARA_BenchSN);
	if (pBenchSNJson == NULL)
	{
		return FALSE;
	}
	CString strBenchSN = pBenchSNJson->valuestring;
	//更新测试台状态
	CIot_Bench oBench;
	oBench.UpdateBenchState(g_pTheMySqlApp, strBenchSN,TEST_BENCH_STATE_TESTSTOPED_PROTOCOL);

	return TRUE;
}	

/********************************
主题：[IOT|MQTT]/AtsState/EVENT/TestFinished
{
	"id":"TestFinished",
	"time":"2021-3-24 10:10:10",
	"data":[
		{
			"id":"test_name",
			"value":"测试名称"
		},
		{
			"id":"testuser",
			"value":"用户登录名"
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
			"value":"报告文件名.doc"
		},
		{
			"id":"doc_file_s",
			"value":" doc_file  http文件传输返回的服务器路径fileName"
		},
		{
			"id":"pcap_file",
			"value":"报告文件名_pcap.rar"
		},
		{
			"id":"pcap_file_s",
			"value":" pcap_file  http文件传输返回的服务器路径fileName"
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

	//更新装置测试记录属性
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
		//只需要更新被测设备的状态即可。
		bRet = TRUE;
	}
	else
	{
	//根据装置和开始时间查询，不存在则插入，存在则更新
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

	//更新测试台状态
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
主题：YRQ/AtsState/EVENT/TestProcess
命令数据格式
{
	"id":"TestProcess",
	"time":"2021-3-24 10:10:10",
	"data":[
		{
			"id":"DeviceState",
			"value":"合格|不合格"  //所有已测试项目的总结论，有一个不合格即为不合格
		},
		{
			"id":"RemainTime",
			"value":"56"   //预计剩余时间，单位s
		},
		{
			"id":"TotalTime",
			"value":"142"   //总时间，单位s
		},
		{
			"id":"CurrItem",
			"value":"3"     //当前测试项目，从1开始
		},
		{
			"id":"TotalItems",
			"value":"6"   //总的测试项目数量
		},
		{
			"id":"DeviceSN",
			"value":"装置SN"
		}
		{
			"id":"BenchSN",
			"value":"TX001"
		}   //需新增，测试台SN
	]
}
*****************************************/
BOOL CMosquittoServerBase::Process_Iot_TestProcess(const CString &strTestType,CJSON *pJson)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Iot_TestProcess"));

	CJSON* pArrData = CJSON_GetObjectItem(pJson, "data");
	if (pArrData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("JSON格式错误，未查到data"));
		return FALSE;
	}

	if (pArrData->type != CJSON_Array)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("JSON格式错误，data不是Array"));
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

	//查询测试台关联装置表
	CIot_TestTaskDevice oTestTaskDevice;
	BOOL bRet = oTestTaskDevice.QueryDeviceByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTaskDevice.DB_Select_OwnEx failed![%s]"),strDeviceSN);
		return FALSE;
	}

	if (strDeviceState == _T("0"))
	{
		oTestTaskDevice.m_strDeviceState = _T("不合格");
	}

	//更新测试任务关联装置表的进度信息
	//协议测试时，业务性能测试已经结束，故当前项目进度可以直接加上业务性能测试的测试项目数量
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
主题：测试台SN/ AtsState/EVENT/TestCreated
命令数据格式：
<sys-state name="" id="TestCreated" mid="0" time="2021-09-08 14:49:03" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="DeviceSN" id="DeviceSN" data-type="string" value="A92E082FA1F3" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="BenchSN" id="BenchSN" data-type="string" value="TX001" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<data name="Test_Total_Time_Long" id="Test_Total_Time_Long" data-type="string" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
		<guidebook name="ATS-Template" id="REALTIMEDATA">
			<job-guide name="作业指导" id="JobGuide" />
			<device name="设备" id="Device">
				<items name="分类" id="Items" tkid="65535" select="1">
					<safety name="数据" id="Safety" tkid="65535" select="1" />
					<safety name="数据1" id="Safety1" tkid="65535" select="1" />
					<safety name="数据2" id="Safety2" tkid="65535" select="1" />
					<safety name="数据3" id="Safety3" tkid="65535" select="1" />
					<safety name="数据4" id="Safety4" tkid="65535" select="1" />
					<safety name="数据5" id="Safety5" tkid="65535" select="1" />
					<safety name="数据6" id="Safety6" tkid="65535" select="1" />
					<safety name="数据7" id="Safety7" tkid="65535" select="1" />
					<safety name="数据8" id="Safety8" tkid="65535" select="1" />
					<safety name="数据9" id="Safety9" tkid="65535" select="1" />
					<safety name="数据10" id="Safety10" tkid="65535" select="1" />
				</items>
			</device>
		</guidebook>
	</paras>
</sys-state>

物联MQTT服务器收到TestCreated事件处理逻辑：
1、查询测试台表iot_bench，更新状态字段status= TEST_BENCH_STATE_PRETEST（1）
2、查询测试任务表iot_test_task更新测试任务表中的time_long_total_test、tm_begin字段；
3、查询设备表iot_device、测试任务表iot_test_task和测试台测试装置表iot_test_task_device来更新设备状态test_state = TEST_DEV_STATE_TESTING（1）
3、查询设备表iot_testapp、测试任务表iot_test_task和测试台测试装置表iot_test_tase_testapp来更新设备状态test_state = TEST_DEV_STATE_TESTING（1）
4、解析GuideBook，创建被测装置测试项目实时结果表iot_device_item_rslt，
并更新相关字段；包括index_test_task; index_bench; index_device; index_item; 
name_item_path; id_item_path; rsltjdg; state; select_state;
******************************/
//多个设备同时测试时，每个被测设备返回一次TestCreated事件
BOOL CMosquittoServerBase::Process_TestCreated(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestCreated"));
	BOOL bRet = FALSE;

	//预估总时间
	long nTotalTime = 0;
	long nTotalItems = 0;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_TestTotalTimeLong, nTotalTime);
	oSysState.GetParasDataValueByID(STT_CMD_PARA_TotalItems, nTotalItems);

	//查询测试台表
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
	

	//查询测试任务表
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

	//从数据库获取device对象
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

	//从数据库获取testapp对象
	CIot_TestApps oIotTestApps;
	bRet = oIotTestApps.QueryTestAppsByIndexTask(g_pTheMySqlApp, oTestTask.m_nIndex_Test_Task);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oIotTestApps.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	//查询测试台关联装置表
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

	//更新测试任务关联装置的总测试项目数量
	oTestTaskDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	g_pTheMySqlApp->Commit();

	CIot_DeviceItemRslts oIotDeviceItemRslts;
	CSttParas* pParas =  oSysState.GetSttParas();
	CSttGuideBook* pGuideBook = pParas->GetGuideBook();

	if (pGuideBook == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("创建测试错误！***没有返回作业指导书  GuideBook = NULL***"));
		return FALSE;
	}

	CSttDevice* pDevice = (CSttDevice*)pGuideBook->FindByClassID(STTGBXMLCLASSID_CSTTDEVICE);

	if (pDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("创建测试错误！***作业指导书没有返回设备信息  Device = NULL***"));
		return FALSE;
	}

	CExBaseList oListItem;
	pDevice->SelectAllRootItem(oListItem);
	pDevice->RemoveAll();
	
	CreateIotItemRslts(oIotDeviceItemRslts, oBench.m_nIndex_Test_Task,oBench.m_nIndex_Bench, &oIotDevice, &oListItem);
	g_pTheMySqlApp->StartTransaction();

	//更新测试台状态
	oBench.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	//更新测试任务时长，开始时间
	oTestTask.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	//更新装置表的关联装置(不是关联装置表)iot_device
	//oIotDevices.UpdateDeviceState(g_pTheMySqlApp,DEVICE_TEST_STATE_SvrTesting);
	oIotDevice.m_nTest_State = DEVICE_TEST_STATE_SvrTesting;
	oIotDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	//更新装置表的关联测试仪(不是关联装置表)iot_testapp
	oIotTestApps.UpdateTestAppState(g_pTheMySqlApp,TEST_DEV_STATE_TESTING);

	g_pTheMySqlApp->Commit();

	//更新iot_device_test
		CXDb_PKeyValue oPKeyValue;
		oIotDeviceItemRslts.DB_InsertEx(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys, oPKeyValue);
	
	return TRUE;
}

/*******************************
主题：测试台SN/ AtsState/EVENT/TestStarted
命令数据格式：
<sys-state name="" id="TestStarted" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id=" DeviceSN " data-type="long" value="0" unit=""/>
	</paras>
</sys-state>

物联服务器收到TestStarted事件处理逻辑：
更新测试台iot_bench表中state=2【测试中】；
********************************/
BOOL CMosquittoServerBase::Process_TestStarted(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestStarted"));
	//更新测试台状态
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
主题：测试台SN/ AtsState/EVENT/TestStoped
命令数据格式：
<sys-state name="" id="TestStoped" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id=" DeviceSN" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>

网站服务器收到TestStoped事件处理逻辑：
更新测试台iot_bench表中state=3【停止测试】；
*******************************/
BOOL CMosquittoServerBase::Process_TestStoped(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestStoped"));
	//更新测试台状态
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
主题：测试台SN/AtsState/EVENT/ExportFinish
命令数据格式：
<sys-state name="" id="ExportReported" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name=" " id="EventID" data-type="string" value=" ExportFinish "/>
		<data name="" id="TotalDevices" data-type="" value="4"/>
		<data name="" id="CurrDevice" data-type="" value="1"/>
		<data name="" id=" DeviceSN " data-type="" value="装置SN"/>
		<data name="测试台标识" id="TestID" value="测试台SN"/>
		<data name="报告记录文件" id="gbrpt-file" value=" SZNR-TTU202012131427"/>
		<data name="服务器报告记录文件" id="gbrpt-file_s" value=" http文件传输返回的fileName"/>
		<data name="报告文件" id="doc-file" value="SZNR-TTU202012131427.doc"/>
		<data name="服务器报告文件" id="doc-file_s" value=" http文件传输返回的fileName "/>
	</paras>
</sys-state>

1、根据deviceID、tm_begin查询测试记录表iot_device_test记录，是否存在，若存在则更新，不存在则创建；
2、更新测试台记录iot_bench中state=5【测试完成，且已导出报告】
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

	//查询测试台关联装置表
	CIot_TestTaskDevice oTestTaskDevice;
	bRet = oTestTaskDevice.QueryDeviceByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTaskDevice.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	//查询装置
	CIot_Device oDevice;
	bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	//查询测试任务表
	CIotTestTask oTestTask;
	bRet = oTestTask.QueryByBenchSN(g_pTheMySqlApp, strBenchSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTask.QueryByBenchSN failed![%s]"),strBenchSN);
		return FALSE;
	}

	//从数据库获取testapp对象
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

	//根据装置和开始时间查询，不存在则插入，存在则更新
	bRet = oDeviceHisTest.UpdateDeviceHisTest(g_pTheMySqlApp);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDeviceHisTest.UpdateDeviceHisTest failed![%s]"),strBenchSN);
		return FALSE;
	}

	//更新扩展报告表，该表仅记录业务性能测试的原始记录文件
	CIot_DeviceReportEx oReportEx;
	oReportEx.m_nIndex_Device_Histest = oDeviceHisTest.m_nIndex_Device_Histest;
	oSysState.GetParasDataValueByID(XPARA_ID_DOCRPTFILE_EX,oReportEx.m_strDoc_File);
	oSysState.GetParasDataValueByID(XPARA_ID_DOCRPTFILE_EX_S,oReportEx.m_strDoc_File_S);
	//有就更新，没有就插入
	bRet = oReportEx.UpdateDeviceReportEx(g_pTheMySqlApp);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oReportEx.UpdateDeviceReportEx failed![%s]"),strBenchSN);
		//此处不能返回FALSE，因为不是所有的测试都有扩展报告
		//return FALSE;
	}

	//更新测试台状态
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

	//更新被测设备的状态
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
		//更新装置表的关联测试仪(不是关联装置表)iot_testapp
		oIotTestApps.UpdateTestAppState(g_pTheMySqlApp,TEST_DEV_STATE_STANDBY);
	}

	return bRet;
}

/********************************
主题：测试台SN/AtsState/CloseTest/REPLY
命令数据格式：
<sys-state name="" id=" CloseTest " mater-host="" ret-type="REPLY" id-cmd="ats-cmd">
	<paras name="" id="">
		<data id="ExecStatus" data-type=" " value="1|2|3|4" unit=""/>
	</paras>
</sys-state>

物联服务器收到CloseTest/REPLY命令处理逻辑：
执行关闭测试后续逻辑：
1、	更新测试台iot_bench表中state=0【空闲】；
2、	更新装置表iot_device、iot_testapp中test_state=0【空闲】；
3、	删除测试台关联的实时表记录，iot_bench_device、iot_device_item_rslt
4、	删除当前测试装置临时实时数据文件夹
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

	//查询测试台表
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

	//查询测试任务表
	CIotTestTask oTestTask;
	oTestTask.m_nIndex_Test_Task = nIndex_TestTask;
	bRet = oTestTask.DB_Select_OwnEx(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTask.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	//从数据库获取device对象
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

	//删除实时表
	strDeleteBenchDeviceSql.Format(_T("delete from %s where %s=%d")
		,strBenchDeviceTable,strIndex_TestTaskKey,oTestTask.m_nIndex_Test_Task);
	strDeleteItemRsltsSql.Format(_T("delete from %s where %s=%d")
		,strItemRsltsTable,strIndex_TestTaskKey,oTestTask.m_nIndex_Test_Task);

	//从数据库获取testapp对象
	CIot_TestApps oIotTestApps;
	bRet = oIotTestApps.QueryTestAppsByIndexTask(g_pTheMySqlApp, oTestTask.m_nIndex_Test_Task);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oIotTestApps.DB_Select_OwnEx failed![%s]"),strBenchSN);
		return FALSE;
	}

	g_pTheMySqlApp->StartTransaction();

	//更新测试台状态
	oBench.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	//更新装置表的关联装置(不是关联装置表)iot_device
	oIotDevices.UpdateDeviceState(g_pTheMySqlApp,DEVICE_TEST_STATE_IDLE);

	//更新装置表的关联测试仪(不是关联装置表)iot_testapp
	oIotTestApps.UpdateTestAppState(g_pTheMySqlApp,TEST_DEV_STATE_NORMAL);

	//删除实时表
	g_pTheMySqlApp->ExecuteCmd(strDeleteBenchDeviceSql);
	g_pTheMySqlApp->ExecuteCmd(strDeleteItemRsltsSql);

	g_pTheMySqlApp->Commit();

	//删除当前测试装置临时实时数据文件夹
	oIotDevices.DeleteRTDeviceRpt(g_strRTDeviceRptPath);

	return TRUE;
}

//查询指定测试项实时数据记录
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

	//查询装置
	CIot_Device oDevice;
	bRet = oDevice.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oDevice.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	//查询测试任务表
	CIotTestTask oTestTask;
	bRet = oTestTask.QueryByBenchSN(g_pTheMySqlApp, strBenchSN);
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("oTestTask.QueryByBenchSN failed![%s]"),strBenchSN);
		return FALSE;
	}

	//查询指定测试项实时数据记录
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
主题：测试台SN/ AtsState/EVENT/ItemStateChanged
命令数据格式：
<sys-state name="" id="ItemStateChanged" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id=" DeviceSN " data-type="" value="装置SN"/>
		<data id="DeviceIndex" data-type="long" value="0" unit=""/>
		<data id="TestID" data-type="string" value="" unit=""/>
		<data id="ReportIndex" data-type="long" value="0" unit=""/>
		<data id="ItemIndex" data-type="long" value="2" unit=""/>
		<data id=" ItemPath " data-type="string" value="***$MacroTest1" unit=""/>
		<data id="State" data-type="string" value="TESTING" unit=""/>
	</paras>
</sys-state>

物联服务器收到ItemStateChanged事件处理逻辑：
根据测试台SN、被测装置SN、ItemPath信息定位iot_device_item_rslt记录，根据State信息更新state字段，rsltjdg、rsltdsc；
测试状态说明详见数据库表说明；
************************************/
BOOL CMosquittoServerBase::Process_ItemStateChanged(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_ItemStateChanged"));
	//查询指定测试项实时数据记录
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
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("++++++Process_ItemStateChanged++++++%s++++++%ld++++返回值 = %d"), strItemPath, nState, bRet);

	return bRet;
}

/*********************************
主题：测试台SN/AtsState/EVENT/REPORT
命令数据格式：
<sys-state name="" id="" mater-host="" ret-type="REPORT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id=" DeviceSN " data-type="" value="装置SN"/>
		<data id="ItemIndex" data-type="long" value="2" unit=""/>
		<data id="ItemPath" data-type="string" value="MacroTest1" unit=""/>
		<data id="State" data-type="string" value="ELIGIBLE" unit=""/>
		<reports>
			<report name="1970-1-1 1:28:48" id="Rpt00_1_0" begintime="1970-1-1 1:28:48" endtime="">
				<values name="" id="">
					<value id="RsltJdg" value="1"/>
					<value id="RsltDsc" value="合格"/>
				</values>
				<dataset name="Dataset" id="dataset" data-type="" write-mode="0" index="0">
					数据对象
				</dataset>
			</report>
			……………………….
		</reports>
		<rpt-map-datas>报告映射数据</rpt-map-datas>
	<paras>
</sys-state>

物联服务器收到REPORT事件处理逻辑：
1、	根据测试台SN、被测装置SN、ItemPath信息定位iot_device_item_rslt记录；
2、	提取reports节点保存到 对应装置SN\主键.xml;
3、	更新file_report【文件内容为reports节点xml字符串】、file_report_s、file_pkgs、file_pkgs_s字段；
**********************************/
BOOL CMosquittoServerBase::Process_Report(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_Report"));
	//查询指定测试项实时数据记录
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
主题：测试台SN/AtsState/EVENT/TestFinished
命令数据格式：
<sys-state name="" id="TestFinished" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id=" DeviceSN " data-type="" value="装置SN"/>
		<data id="DeviceIndex" data-type="long" value="0" unit=""/>
	</paras>
</sys-state>

物联服务器收到TestFinished事件处理逻辑：
更新测试台iot_bench中state=4【测试完成，未导出报告】、tm_end;
*******************************/
BOOL CMosquittoServerBase::Process_TestFinished(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestFinished"));
	//查询测试台表
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

	//查询测试任务表
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

	//更新测试台状态
	oBench.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	//更新测试任务结束时间
	oTestTask.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);

	g_pTheMySqlApp->Commit();

	return TRUE;
}
/*******************************
<sys-state name="" id="TestProcess" mater-host="" ret-type="EVENT" id-cmd="ats-cmd">
	<paras name="" id="">
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
		<data name="" id="BenchSN" data-type="" value="测试台SN/"/>
		<data id="TotalItems" data-type="long" value="100" unit=""/>
		<data id="CurrItem" data-type="long" value="30" unit=""/>
		<data id="TotalTime" data-type="long" value="6000" unit="s"/>
		<data id="RemainTime" data-type="long" value="3000" unit="s"/>
		<data name="" id="DeviceState" data-type="" value="合格|不合格"/>
	</paras>
</sys-state>
主题：测试台SN/AtsState/EVENT/ TestProcess
收到TestProcess事件，更新测试台关联数据库表iot_test_task_device
更新其中的测试进度相关的字段
*******************************/
BOOL CMosquittoServerBase::Process_TestProcess(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_TestProcess"));
	CString strDeviceSN;
	oSysState.GetParasDataValueByID(STT_CMD_PARA_DeviceSN, strDeviceSN);

	//查询测试台关联装置表
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

	if (strDeviceState == _T("未测试"))
	{
		strDeviceState = _T("待检");
	}

	oTestTaskDevice.m_nRemainTime = nRemainTime;
	oTestTaskDevice.m_nTotalTime = nTotalTime;
	//oTestTaskDevice.m_nTotalItems = nTotalItems;  项目总数不刷新，在创建测试时已经刷新
	oTestTaskDevice.m_nCurrItem = nCurrItem;
	oTestTaskDevice.m_strDeviceState = strDeviceState;

	//更新测试任务结束时间
	oTestTaskDevice.DB_Update(g_pTheMySqlApp, CIot_AtsMngrXmlRWKeys::g_pXmlKeys);
	g_pTheMySqlApp->Commit();
	return TRUE;
}

BOOL CMosquittoServerBase::Process_UploadReportFinished(const CString &strBenchSN,CSttSysState &oSysState)
{
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("CMosquittoServerBase::Process_UploadReportFinished"));
	CString strDocFile, strDocFile_s, strDocFileEx, strDocFileEx_s, strDeviceSN, strPcapFile, strPcapFile_s;
	//跟英锐祺确定的参数的ID 与我们系统中不一致 后面统一
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

	//外部系统报告表插入
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


	//外部系统扩展报告表
	//CIot_DeviceOutReportExs oOutReportExs;
	CIot_DeviceOutReportEx oOutReportEx;
	oOutReportEx.m_nIndexRpt = oOutReport.m_nIndex_Rpt;   //插入后，自身的主键会更新吗？
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
//测试仪送上来的实时数据，只有需要画曲线的数据，才送上来，并填写数据库
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

	//先根据SN，查询对应的测试仪
	CIot_TestApp oTestApp;
	bRet = oTestApp.QueryByDeviceSN(g_pTheMySqlApp, strDeviceSN);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CMosquittoServerBase::Process_RtData++++++oTestApp.QueryByDeviceSN failed![%s]"),strDeviceSN);
		return FALSE;
	}

	//从曲线定义表中，查询该设备类型的曲线的数据定义
	CIot_RTDeviceHisDataTitles oDataTitles;
	bRet = oDataTitles.QueryRTDeviceHisDataTitlesByDeviceType(g_pTheMySqlApp, oTestApp.m_nIndex_Device_Type);
	
	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CMosquittoServerBase::Process_RtData++++++oDataTitles.QueryRTDeviceHisDataTitlesByDeviceType failed![%d]")
			,oTestApp.m_nIndex_Device_Type);
		return FALSE;
	}

	CDataGroup *pParas = (CDataGroup *)oGroup.FindByID(_T("RTDATA"));
	//插入实时数据到实时数据历史表中
	bRet = oDataTitles.InsertRtDeviceHisData(g_pTheMySqlApp, strDeviceSN, pParas);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("++++++CMosquittoServerBase::Process_RtData++++++oDataTitles.InsertRtDeviceHisData failed![%s]"), strDeviceSN);
		return FALSE;
	}

	return TRUE;
}

//topic：DeviceSN/HeartBeat
/*
<group id="">
	<data id="DeviceSN" name="" value="PAL-E-ZH.0016"/>
</group>
*/
/*
根据设备sn，查询iot_testapp表，判断isupdate字段是否为1。
若为1，则不处理；
若不为1，则进行当年使用天数和总使用天数的累加。并将isupdate字段置1。
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

	//先根据SN，查询对应的测试仪
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
//根据设备SN，查询iot_testapp表，将使用次数+1。
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

	//先根据SN，查询对应的测试仪
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
	//创建测试实时表
	CIot_DeviceItemRslt* oIotDeviceItemRslt = new CIot_DeviceItemRslt();
	oIotDeviceItemRslt->m_nIndex_Test_Task = nIndex_TestTask;
	oIotDeviceItemRslt->m_nIndex_Bench = nIndex_Bench;
	oIotDeviceItemRslt->m_nIndex_Device = pIotDevice->m_nIndex_Device;
	oIotDeviceItemRslt->m_nIndex_Item = 0;//默认为0
	CString strTemp = pItem->GetNamePathEx(STTGBXMLCLASSID_CSTTDEVICE, TRUE);
	strTemp = pIotDevice->m_strName + strTemp.Mid(strTemp.Find(_T("$")));
	oIotDeviceItemRslt->m_strName_Item_Path = strTemp;
	strTemp = pItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, TRUE);
	strTemp = pIotDevice->m_strID + strTemp.Mid(strTemp.Find(_T("$")));
	oIotDeviceItemRslt->m_strId_Item_Path = strTemp;
	oIotDeviceItemRslt->m_nRsltjdg = 1;//默认为1
	oIotDeviceItemRslt->m_nState = pItem->m_nState;
	oIotDeviceItemRslt->m_nSelect_State = pItem->m_nSelect;
	oIotDeviceItemRslts.AddNewChild(oIotDeviceItemRslt);
}