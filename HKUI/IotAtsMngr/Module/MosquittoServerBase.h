#pragma  once

#include "..\..\Module\mosquitto-1.4.8\src\Mosquitto_Process.h"
#include "..\..\Module\MySqlApp\MySqlBaseApp.h"
#include "..\..\SttStudio\Module\SttCmd\SttSysState.h"
#include "..\..\SttStudio\Module\SttCmd\SttAtsCmd.h"

#include "Iot_AtsMngrDB\Iot_DeviceItemRslts.h"
#include "Iot_AtsMngrDB\IotTestTask.h"
#include "Iot_AtsMngrDB\Iot_Devices.h"
#include "Iot_AtsMngrDB\Iot_TestApps.h"
#include "Iot_AtsMngrDB\Iot_Bench.h"
#include "Iot_AtsMngrDB\Iot_DeviceHisTest.h"
#include "Iot_AtsMngrDB\Sys_User.h"
#include "..\..\SttStudio\Module\SttCmd\GuideBook\SttCommCmd.h"

//包含协议一致性测试，测试台状态定义
#define TEST_BENCH_STATE_NORMAL 0			//空闲
#define TEST_BENCH_STATE_OCCUPY 1			//占用
#define TEST_BENCH_STATE_TESTCREATED 2		//已创建测试，但未开始测试
#define TEST_BENCH_STATE_TESTING_FUNCTION 3		//正在性能测试
#define TEST_BENCH_STATE_TESTING_PROTOCOL 4		//正在协议一致性测试
#define TEST_BENCH_STATE_TESTSTOPED_FUNCTION 5		//性能测试暂停
#define TEST_BENCH_STATE_TESTSTOPED_PROTOCOL 6		//协议一致性测试暂停
#define TEST_BENCH_STATE_FINISHED 7		//测试完成，但未导出报告
#define TEST_BENCH_STATE_EXPORTED 8		//测试完成，且导出报告

// 不包含协议一致性测试，测试台状态定义
#define TEST_BENCH_STATE_Funtion_NORMAL 0			//空闲
#define TEST_BENCH_STATE_Funtion_TESTCREATED 1		//已创建测试，但未开始测试
#define TEST_BENCH_STATE_Funtion_TESTING 2		//已开始测试
#define TEST_BENCH_STATE_Funtion_STOPED 3		//已停止测试
#define TEST_BENCH_STATE_Funtion_FINISHED 4		//测试完成，但未导出报告
#define TEST_BENCH_STATE_Funtion_EXPORTED 5		//测试完成，且导出报告


//测试仪的状态
#define TEST_DEV_STATE_NORMAL	0		//空闲
#define TEST_DEV_STATE_TESTING	1		//正在业务测试
#define TEST_DEV_STATE_STANDBY  2       //待机：所有被测设备均已导出报告，但未关闭测试

class CMosquittoServerBase : public CMySqlBaseApp
{
public:
	CMosquittoServerBase();
	virtual ~CMosquittoServerBase();

	static long GenerateIndexTest();
	static long GenerateIndexItem();

private:
	CExBaseObject* NewMosquittoClient(const char* strName, const char* strID);
	void PraseCmdBuf(CSttCmdBase* pSttCmd, const char* pBuf, int nLen, const CString& strFormat);
	void SetXmlBufferLen(long nLen);
	void CreateIotItemRslts(CIot_DeviceItemRslts& oIotDeviceItemRslts, long nIndex_TestTask,long nIndex_Bench, 
		CIot_Device *pIotDevice, CExBaseList* pList);
	void NewIotItemRslt(CIot_DeviceItemRslts& oIotDeviceItemRslts, long nIndex_TestTask,long nIndex_Bench, 
		CIot_Device *pIotDevice, CSttItemBase* pItem);
	BOOL HasValidChild(CExBaseList* pList);

public:
	void InitMosquittoServerBase();
	void ExitMosquittoServerBase();

	static BOOL SendTopicData(const CString& strTopic, char *pBuf, long nLen);
	void SetMsgWnd(const HWND hWnd);
	void Process_UpdateLog(int nPriority, const char* strMsg);
	void Process_Disconnect(const char* strID);
	void Process_Connect(const char* strIP, const char* strID);
	void Process_Subscribe(const char* strTopic, const char* strID);
	void Process_Unsubscribe(const char* strTopic, const char* strID);

	//Ats 事件
	BOOL Process_Ats_Event(const char* strTopic, const char* strMsg);

	//shaolei 20210807
	BOOL Process_Ats_Report(const char* strTopic, const char* strMsg);
	BOOL Process_TestCreated(const CString &strBenchSN,CSttSysState &oSysState);
	BOOL Process_TestStarted(const CString &strBenchSN,CSttSysState &oSysState);
	BOOL Process_TestStoped(const CString &strBenchSN,CSttSysState &oSysState);
	BOOL Process_ExportReport(const CString &strBenchSN,CSttSysState &oSysState);
	BOOL Process_CloseTestReply(const CString &strBenchSN,CSttSysState &oSysState);
	BOOL Process_ItemStateChanged(const CString &strBenchSN,CSttSysState &oSysState);
	BOOL Process_Report(const CString &strBenchSN,CSttSysState &oSysState);
	BOOL Process_TestFinished(const CString &strBenchSN,CSttSysState &oSysState);
	BOOL Process_TestProcess(const CString &strBenchSN,CSttSysState &oSysState);
	//shaolei 20210927
	BOOL Process_UploadReportFinished(const CString &strBenchSN,CSttSysState &oSysState);
	//2021-10-10  lijunqing
	BOOL Process_RtData(const char* strTopic, const char* strMsg);
	//2021-12-2  shaolei
	BOOL Process_TestApp_HeartBeat(const char* strTopic, const char* strMsg);
	BOOL Process_TestApp_CreateDeviceReply(const char* strTopic, const char* strMsg);

	//IOT|MQTT Ats事件
	BOOL Process_IotAts_Event(const char* strTopic, const char* strMsg);
	BOOL Process_Iot_TestCreated(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_TestStarted(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_TestStoped(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_TestFinished(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_ExternTestFinished(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_TestProcess(const CString &strTestType,CJSON *pJson);

	
	//查询指定测试项实时数据记录
	BOOL QueryDeviceItemRslt(const CString &strBenchSN,CSttSysState &oSysState,CIot_DeviceItemRslt &oDeviceItemRslt);

	//判断一个CLASSID是否属于ITEMBASE
	BOOL IsItemBaseClassID(UINT nClassID);

public:
	CExBaseList m_oClientList;
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;

	HWND m_hWnd;
};

extern CString g_strRTDeviceRptPath;

