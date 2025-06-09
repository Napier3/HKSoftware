#pragma once

#include"MacroTestInterface.h"
#include "../Engine/SttClientTestEngine.h"
#include "SttMacroTestMsgRcvInterface.h"
#include "../TestClient/SttTestClientBase.h"

//2020-11-6  lijunqing
#include "../../../Module/BaseClass/StringSerializeBufferAscii.h"

#ifdef _PSX_IDE_QT_

#else
#include "VC/VmSttMacroTestSpyDlg.h"
#endif

#include "../../../IotAtsMngr/Module/MqttCmmInterface.h"
//2020-10-17  lijunqing

class CVmMqttMacroTest : public CMacroTestInterface
	, public CMacroTestEventInterface
	, public CSttCmdOverTimeMsgRcv
	, public CMqttMsgProcessInterface
{
public:
	CVmMqttMacroTest();
	virtual ~CVmMqttMacroTest(void);

//MQTT事件处理接口，共CMqttMsgInterface对象调用
//class CMqttMsgProcessInterface
public:
	//根据收到的MQTT主题进行匹配，如果匹配成功，则返回TRUE，否则返回FALSE
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser);
	//MQTT消息处理
	virtual void MqttMsgProcess(CSttMqttTopicParser &oSttMqttTopicParser);

	//MQTT主题订阅接口函数：MQTT Client连接成功后，遍历各CMqttMsgProcessInterface
	//订阅相关的主题
	virtual BOOL MqttSubscribeTopic();

	//MQTT取消主题订阅接口函数：MQTT Client断开连接后，遍历各CMqttMsgProcessInterface
	//T取消订阅相关的主题
	virtual BOOL MqttUnSubscribeTopic();

	void MqttAddToClient();
	void MqttRemoveFromClient();

public:
    virtual void Release();

    //CVmMqttMacroTestMsgRcvInterface *m_pTestMsgRcv;
	unsigned long m_hMsgWnd;
	unsigned long m_nMsgID;

	//CString m_strTestAppSN;   CMacroTestInterface中定义
	CString m_strBenchSN; //
	CString m_strTestMacroID;  //资源申请的测试功能没有m_pTestMacro，因此定义此变量保存
	//为了防止系统参数测试未结束，又下发下一条StartTest指令，故增加此变量
	BOOL m_bTestStarted;

	//2020-11-6  lijunqing
    CStringSerializeBufferAscii m_oReportBuffer;
	
	//用于保存ReadDeviceParameter指令返回的数据，以便Native客户端登录后，返回给它
	//CSttParas m_oReadDeviceParameter;   //shaolei 2023-12-19改为全局
	CDataGroup m_oSearchRslts;  //曲线搜索结果

	//2023-4-22  lijunqing
	CVmSttMacroTestSpyDlg *m_pVmMqttMacroTestSpyDlg;

public:
	virtual void OnSendCmdOverTime(LPVOID pSocketRef, DWORD nCmdType, char *pszCmdID);

public:
	virtual long SetWndMsg(unsigned long hMainWnd, unsigned long nMsgID);
	virtual CString GetConfig();
	virtual long SetConfig(CSttTestAppCfg *pSttTestAppCfg);
	virtual long SetConfig(const CString & bstrConfig);
	virtual long Test(const CString & strMacroID, const CString & strParameter);
	virtual long Test(const CString & strMacroID, CDataGroup *pParas);	//2023-6-16  lijunqing 
	virtual CString GetReport();
	virtual long StopTest();
	virtual long CloseDevice();
	virtual CString GetSearchReport();
	virtual long FinishTest(long nState);
	virtual long ExcuteCmd(const CString & strCmdID, const CString & strCmdParameter);
	virtual unsigned long GetExternMsgRcvWnd();
	virtual unsigned long GetExternMsgID();
	virtual unsigned long StopDevice(void);
    virtual long UpdateParameter(const CString &strMacroID, CDataGroup *pParas);
    virtual long ManualTrigger();
	//2023-6-20  lijunqing
	virtual CDataGroup* GetResults();
	
	//2022-4-20 shaolei lijunq 
	virtual long SendCmd_Adjust(const CString &strMacroID, CDataGroup *pParas, const CString &strCmdID);
	virtual long SendCmd_Test(const CString &strMacroID, CDataGroup *pParas, const CString &strCmdID);

	//add by shaolei
	BOOL SetParameter(CTestMacro *pTestMacro, const CString & strParameter);
    BOOL SetParameter_ChMapsConfig(CDataGroup &oDataGroup, const CString &strParameter);
 
	//shaolei 20220215
    BOOL SetParameter_ChMapsConfig_UIParas(CDataGroup &oDataGroup, const CString &strParameter);
    BOOL SetParameter_IECConfig(CDataGroup &oDataGroup, const CString &strParameter);
	BOOL SetParameter_IECConfig_UIParas(CDataGroup &oDataGroup, const CString &strParameter);
	BOOL SetParameter_SystemConfig(CDataGroup &oDataGroup, const CString &strParameter);
	BOOL ConnectDevice();
	long System_Login();
	long Adjust_ReadDeviceParameter(CStringArray &astrTypes, BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	void PostTestWndMsg(WPARAM wParam, LPARAM lParam);
	long Test_StartTest(const CString &strMacroID, CDataGroup *pParas,BOOL bDoEvents=TRUE,CSttCmdData *pRetData = NULL,BOOL bSendCmdAsync=FALSE);
	long Test_UpdateParameter(const CString &strMacroID, CDataGroup *pParas);
	long Test_SendTrigger();

	//测试功能事件接口
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);

	virtual void OnReport(CDataGroup *pParas);
	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);
	virtual long OnAts_Stop(CDataGroup *pParas);

public:
	//add by shaolei 20210515
	void SetConfig_TestApp();
	//add by  shaolei  20210729
	void GetParaIDPath(CString &strPath, CDvmData *pData);
	void AppendReport_ResultEx(CDataGroup *pRsltGroup);
	void AppendReport_ResultEx(CDvmValues *pValues, CDataGroup *pRsltGroup);
	void GetResultFromTestMacro();

	//对于特定的测试功能，对测试功能ID，进行修正，例如递变测试的最大灵敏角试验
	void ResetParasByStateCount(long nStateCount);
	void ResetParasByStateCount(CDataGroup *pParas, long nStateCount);
	void ResetParas_RsltEvalute();

private:
	BOOL IsAdjust(const CString &strMacroID);

	void InitTopicCmbn(CSttMqttTopicCmbn &oTopicCmbn, const CString &strCmdType, const CString &strCmdID);

	long Adjust_Adjust(const CString &strMacroID, CDataGroup *pParas, BOOL bDoEvents
		,CSttCmdData *pRetData,BOOL bSendCmdAsync);
};


class CVmMqttMacroTestCreator : public CMacroTestCreatorInterface
{
public:
	CVmMqttMacroTestCreator();
	virtual ~CVmMqttMacroTestCreator();

public:
	virtual CMacroTestEngineInterface* CreateMacroTestEngine(const CString &strMacroFile);
	virtual CMacroTestEngineInterface* GetMacroTestEngine(const CString &strType, const CString &strProgID, const CString &strMacroFile);
	virtual CMacroTestInterface* GetMacroTest(const CString &strType, const CString &strProgID, const CString &strMacroFile, CDataGroup *pTestApps);
	virtual void ReleaseMacroTestEngine();
	virtual void ReleaseMacroTestEngine(const CString &strProgID);
	virtual void InitMacroTestEngineShowSpyWnd();
	virtual void ShowSpyWnd();
	virtual void ExecuteMtCmd(const CString &strCmdID, const CString &strCmdPara);
	virtual long ConfigEngine(const CString &strMacroFile, const CString &strIP);
	virtual long AttatchLogWnd(unsigned long hWnd);
};

//2023-8-22 李俊庆  自动测试端，全局唯一的BenchSN
extern CString *g_strSmartTest_BenchSN;
