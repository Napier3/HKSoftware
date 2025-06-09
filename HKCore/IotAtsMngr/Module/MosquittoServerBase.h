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

//����Э��һ���Բ��ԣ�����̨״̬����
#define TEST_BENCH_STATE_NORMAL 0			//����
#define TEST_BENCH_STATE_OCCUPY 1			//ռ��
#define TEST_BENCH_STATE_TESTCREATED 2		//�Ѵ������ԣ���δ��ʼ����
#define TEST_BENCH_STATE_TESTING_FUNCTION 3		//�������ܲ���
#define TEST_BENCH_STATE_TESTING_PROTOCOL 4		//����Э��һ���Բ���
#define TEST_BENCH_STATE_TESTSTOPED_FUNCTION 5		//���ܲ�����ͣ
#define TEST_BENCH_STATE_TESTSTOPED_PROTOCOL 6		//Э��һ���Բ�����ͣ
#define TEST_BENCH_STATE_FINISHED 7		//������ɣ���δ��������
#define TEST_BENCH_STATE_EXPORTED 8		//������ɣ��ҵ�������

// ������Э��һ���Բ��ԣ�����̨״̬����
#define TEST_BENCH_STATE_Funtion_NORMAL 0			//����
#define TEST_BENCH_STATE_Funtion_TESTCREATED 1		//�Ѵ������ԣ���δ��ʼ����
#define TEST_BENCH_STATE_Funtion_TESTING 2		//�ѿ�ʼ����
#define TEST_BENCH_STATE_Funtion_STOPED 3		//��ֹͣ����
#define TEST_BENCH_STATE_Funtion_FINISHED 4		//������ɣ���δ��������
#define TEST_BENCH_STATE_Funtion_EXPORTED 5		//������ɣ��ҵ�������


//�����ǵ�״̬
#define TEST_DEV_STATE_NORMAL	0		//����
#define TEST_DEV_STATE_TESTING	1		//����ҵ�����
#define TEST_DEV_STATE_STANDBY  2       //���������б����豸���ѵ������棬��δ�رղ���

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

	//Ats �¼�
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

	//IOT|MQTT Ats�¼�
	BOOL Process_IotAts_Event(const char* strTopic, const char* strMsg);
	BOOL Process_Iot_TestCreated(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_TestStarted(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_TestStoped(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_TestFinished(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_ExternTestFinished(const CString &strTestType,CJSON *pJson);
	BOOL Process_Iot_TestProcess(const CString &strTestType,CJSON *pJson);

	
	//��ѯָ��������ʵʱ���ݼ�¼
	BOOL QueryDeviceItemRslt(const CString &strBenchSN,CSttSysState &oSysState,CIot_DeviceItemRslt &oDeviceItemRslt);

	//�ж�һ��CLASSID�Ƿ�����ITEMBASE
	BOOL IsItemBaseClassID(UINT nClassID);

public:
	CExBaseList m_oClientList;
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;

	HWND m_hWnd;
};

extern CString g_strRTDeviceRptPath;

