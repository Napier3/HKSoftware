#pragma once
#include "SttMqttClientTool.h"
#include "../../Module/TestMacro/TestMacros.h"
#include "../../Module/BaseClass/StringSerializeBuffer.h"
#include "../../SttStudio/Module/SttCmd/SttSysState.h"
#include "../../SttStudio/Module/SttCmd/SttTestCmd.h"
#include "../../Module/MemBuffer/EquationBuffer.h"
#include "../../Module/BaseClass/XTimer.h"
#include "CommErrorDef.h"

#define IOT_TEST_STATE_IDLE			0
#define IOT_TEST_STATE_TESTING		1
#define IOT_TEST_STATE_WAITRESULT	2

#define  IOTVM_MACRO_MSG_TYPE_MACRO   0
#define  IOTVM_MACRO_MSG_TYPE_MACROS  1

#define WM_FLUSH_MACRO	(WM_USER+1111)


#define TIMER_ID_CreateDevice  1001
#define TIMER_LONG_CreateDevice 30000

enum TmtMessageID
{
	MTMSG_ConnectSuccess=0,
	MTMSG_ConnectFaild=1,
	MTMSG_ConnectConfig=2,
	MTMSG_TestBegin=3,
	MTMSG_TestFinished=4, 
	MTMSG_SearchPointFinished=5, 
	MTMSG_CommError=6,
	MTMSG_Not_Surport=7,
	MTMSG_ManualTestBegin=8,
	MTMSG_ManualTestReturn=9,
	MTMSG_ManualTestStop=10,
	MTMSG_ShowCurItem=11,
	MTMSG_TestOverTime=12,
	MTMSG_AppWarning=13,
	MTMSG_AppError=14
};

class CIotTestCtrlBase : public CExBaseList, public CMqttMsgInterface,public CXTimer
{
public:
	CIotTestCtrlBase();
	virtual ~CIotTestCtrlBase();
	void FreeTestMacros();

	//mqtt接口
public:
	virtual void OnMqttMsgRecieve(CSttMqttTopicParser &oSttMqttTopicParser);
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	virtual void OnMqttDisconnected(char *pszErr);
public:
	virtual void OnXTimer(DWORD dwTimerID);
	virtual void OnProcessOverTime();

public:
	//m_strID:测试仪SN
	BOOL m_bIsConnect;   //此处表示跟测试仪是否连接成功，而非与MQTT服务端是否连接成功
	CString m_strRemoteIP;
	CString m_strEngineProgID;
	long m_nRemotePort;
	CString m_strProtocolID;
	CString m_strMacroFile;
	CString m_strDeviceSN;
	long m_nDeviceType;
	CTestMacros *m_pTestMacros;
	CTestMacro *m_pTestMacro;
	CMqttClient m_oMqttClient;
	CString m_strClientSN;   //测试服务端SN

	long m_nTestState;//测试状态：0空闲，1：正在测试；2：等待结果
	CString m_strFormat;//XML | JSON
	CString m_strCurrCmd;	//当前命令

	CEquationBuffer m_oEquation;	//等式解析器

	HWND m_hTestMsgRcvWnd;	//消息发送的窗口句柄	
	UINT m_nMessage;	//消息

	CWnd *m_pMacroUpdateMsgRcvWnd;//界面刷新消息

	void SetMacroUpdateMsgRcvWnd(CWnd *pWnd){m_pMacroUpdateMsgRcvWnd = pWnd;}
	BOOL IsTesting(){return (m_nTestState != IOT_TEST_STATE_IDLE);}
	BOOL ConnectMqttServer();
	virtual BOOL IsIotTestCtrl(){return FALSE;}
	virtual BOOL SubcribeMqttTopic(int nQos);
	virtual long PublicCmdEx(CSttCmdBase *pSttCmd,long nTimeOut=30000);
	virtual long PublicCmd(const CString &strTopic,CSttCmdBase *pSttCmd);
	BOOL CreateDevice();
	
	CTestMacro *SetCurrTestMacro(CTestMacro *pTestMacro);
	CTestMacro *SetCurrTestMacro(const CString &strMacroID);
	void ClearTestState();

	void PostTestWndMsg(WPARAM wParam, LPARAM lParam);
	void PostUpdateMacroMsg(long nMsgType);

public:
	//com接口调用
	virtual LONG SetWndMsg(ULONG hMainWnd, ULONG nMsgID);
	virtual LONG Test(const CString &strMacroID, const CString &strParameter);
	virtual LONG StopTest();
	virtual BSTR GetConfig(void);
	virtual LONG SetConfig(const CString & bstrConfig);
	virtual LONG CloseDevice(void);
	virtual BSTR GetReport(void);
	virtual BSTR GetSearchReport(void);
	virtual DWORD FinishTest(DWORD dwState);

public:
	virtual long Test_StartTest();
	virtual long Test_StopTest();

	//应答或事件处理
	virtual long Process_SysState_Reply(CSttSysState &oSysState,const CString &strCmd);
	virtual long Process_SysState_Event(CSttSysState &oSysState,const CString &strEvent);
	virtual long Process_SysState_Report(CSttSysState &oSysState);
	virtual long Process_SysState_Exception(CSttSysState &oSysState);

	virtual long Process_SysState_Reply_QueryDeviceState(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_SendSensorModel(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_GetTestMacros(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_GetTopo(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_StartTest(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_StopTest(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_SetParameter(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_UpdateParameter(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_GetReport(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_CloseDevice(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_GetSystemState(CSttSysState &oSysState);
	virtual long Process_SysState_TriggerTest(CSttSysState &oSysState);
	virtual long Process_SysState_Reply_CreateDevice(CSttSysState &oSysState);

	virtual long Process_SysState_Event_OnTestStarted(CSttSysState &oSysState);
	virtual long Process_SysState_Event_OnTestStoped(CSttSysState &oSysState);
	virtual long Process_SysState_Event_OnTestFinished(CSttSysState &oSysState);
	virtual long Process_SysState_Event_OnSearchPointReport(CSttSysState &oSysState);

protected:
	//GetReport生成报告等式用到
	CStringSerializeBuffer m_oBinaryBuffer;

	//避免xml解析的时候，频繁分配内存，缺省为1M
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;
	void SetXmlBufferLen(long nLen);

	void PraseBufToCmd(CSttCmdBase *pCmdBase,char *pBuf,long nLen,const CString &strFormat=MQTT_DATA_FORMAT_XML);
};

//////////////////////
CString GetParaIDPath(CShortData *pData);
//获取报告
void GetDatasReportEx(CStringSerializeBuffer &oBinaryBuffer,CShortDatas *pDatas);
void GetGroupReportEx(CStringSerializeBuffer &oBinaryBuffer,CDataGroup *pGroup);
//解析更新参数
void UpdateDatasByParas(CEquationBuffer *pEquation,CShortDatas *pDatas);
void UpdateGroupByParas(CEquationBuffer *pEquation,CDataGroup *pGroup);
//根据macro节点生成SttMacro节点
void Stt_AppendDatasParas(CDataGroup *pDstParas,CShortDatas *pSrcDatas);
void Stt_AppendGroupParas(CDataGroup *pDstParas,CDataGroup *pSrcGroup);
void Stt_UpdateDatasParas(CDataGroup *pDstParas,CDataGroup *pSrcGroup);
CSttMacro *GenerateSttMacroParas(CTestMacro *pTestMacro);
void UpdateMacroResultBySttMacroResult(CTestMacro *pDstTestMacro,CSttMacro *pSrcSttMacro);

//根据SttMacro节点生成macro节点
CTestMacro *GenerateMacroParas(CSttMacro *pSttMacro);
void Stt_AppendDatasParas2(CShortDatas *pDstDatas,CDataGroup *pSrcGroup);
