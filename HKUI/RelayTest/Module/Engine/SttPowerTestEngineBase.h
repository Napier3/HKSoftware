#pragma once

#include "../SttCmd/SttCmdDefineGlobal.h"
#include "../SttCmd/SttTestCmd.h"
#include "../SttTestBase/SttXmlSerialize.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"

#include "SttTestEngineClientData.h"
#include "SttTestEngineBase.h"
#include "../SttTestAppConfig/SttTestAppConfigTool.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../SttTest/Common/tmt_result_def.h"
#include "../SttTest/Common/tmt_system_config.h"
#include "../SttTest/Common/tmt_pt_test.h"

#define MACROID_SttSystemDefaultOutput	"SystemDefaultOutput"
#define MACROID_SttSystemPara			"SystemConfig"
#define MACROID_PTTestPara				"SttPtTest"

extern TMT_SYSTEM_DEFAULT_OUTPUT_PARAS g_oDefaultOutputPara;
extern STT_SystemParas g_oSystemParas;
extern tmt_PtPara g_oPTTestPara;
extern bool g_bPrintLog;
extern bool g_bSaveFile;

typedef struct stt_event_info
{
	CString m_strEventID;
	double m_fTime;
}SttEventInfo;

class CSttPowerTestEngineBase : public CSttTestMsgViewInterface, public CMacroTestEventInterface
{
public:
	CSttPowerTestEngineBase();
	virtual ~CSttPowerTestEngineBase();

public:
	CSttTestEngineClientData *m_pXClientEngine;//联机成功后该对象从Tool中获取
	void FreeXClientEngine();

	virtual BOOL connectTestApp(const CString &strIP,long nPort,const CString &strSoftID = STT_SOFT_ID_TEST);
	virtual long SendStartCmd();
	virtual long SendStopCmd();
	virtual long SendDefaultOutputCmd();
	virtual long SendUpdateParameter();
	virtual long SendTrigger();
	virtual long SendSystemParaCmd();
	virtual long SendAuxDCOutputCmd();//zhouhj 20211016 发送辅助直流输出命令
	virtual long SendModulesGearSwitchCmd();//zhouhj 20211016 发送辅助直流输出命令
	virtual long SendChMapsConfig();
	virtual long SendIECParaCmd();
	virtual long SendPTTestParaCmd();
	virtual long SendReadDeviceParameter();//第一次联机成功后，从装置读取Device信息
	virtual long SendDebugLogCmd(long nValue);//yyj add 控制底层发送调试信息

	virtual long Process_SysState_Log(CSttSysState &oSysState); //yyj 20210809	

        virtual void GenerateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel=true);
	virtual void GenerateTestCmdFromDefaultOutput(CSttTestCmd &oSttTestCmd);//zhouhj 20211016 设置测试仪停止后保持输出的数据值,即默认输出值
	virtual void GenerateTestCmdFromAuxDCOutput(CSttTestCmd &oSttTestCmd);//设置辅助直流输出
	virtual void GenerateTestCmdFromModulesGearSwitch(CSttTestCmd &oSttTestCmd);//设置模块档位

        virtual void UpdateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel=true);
	virtual void GenerateTestCmdFromSystemParas(CSttTestCmd &oSttTestCmd);
        virtual void GenerateTestCmdFromIEC(CSttParas &oSttParas);
	virtual void GenerateTestCmdFromChMaps(CSttParas &oSttParas);
	virtual void GenerateTestCmdFromPTTestParas(CSttTestCmd &oSttTestCmd);

	/////////CSttTestMsgViewInterface//////////
	virtual void OnTestMsgEx(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, long nCmdType, char *pszCmdID, char *pszTestor, char *pszRetCmdType);
        virtual void On_Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState);

	////////CMacroTestEventInterface/////////
	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestStoped(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestFinished(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnSearchPointFinish(const CString &strMacroID, CDataGroup *pParas, CDataGroup *pResults);
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);
	virtual void OnException(CDataGroup *pParas);
	virtual void OnReport(const CString &strTestID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString & strItemID, long nState, CSttParas *pParas);
	virtual void OnReport(CDataGroup *pParas);
	virtual long OnUpdate(CSttParas *pParas);
	virtual long OnDisConnect();
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnReport_ReadDevice(const CString &strMacroID, CDataGroup *pParas);//读取Device的Report解析函数
	virtual long OnRtData(CSttParas *pParas);
        virtual void OnTestResults(CDataGroup *pResults);
        virtual void OnTestInitialize(CEventResult *pEventInfo,CDataGroup *pParas);
	//virtual void OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend){};//zhouhj 20210827更新Gps时间  OnUpdateSyncTime
        virtual long OnUpdateSyncTime(CDataGroup *pSyncTime);//zhouhj 2022-6-9  lijunqing
	void UpdateIBreakUShortOverHeat(long nIBreak,long nUShort,long nOverHeat);

	//通知应用界面刷新
	CEventResult m_oCurrEventResult;	//界面刷新
	CEventResult *m_pLastEventResult;	//事件最后一个
	CExBaseList m_oLastEventList;//存放获取并处理完的最后一个Event事件,该事件暂时不能删除 需要定期 删除
//	CExBaseList m_oEventResultList;		//测试过程中总的事件链表  zhouhj 20210930 没有用到,长时间运行时,该链表会导致内存占用上升

	CEventResult *InitEvent(const CString &strEventID,double fTime,double fRealTime,const CString &strTimeStr); //yyj modify 20210902

	BOOL m_bLockFlag; //1:通用试验、谐波；0:其它
	void SetLockFlag(){ m_bLockFlag = 1; }

public:
	virtual void InitXmlKeys();
	virtual void ReleaseXmlKeys();

	CAutoCriticSection m_oCriticSection;
	CExBaseList m_oFlushEventList;
	void AppenEventInfo(CEventResult *pEventInfo);
	void GetEventInfo(CExBaseList &oEventInfoList);

	BOOL OpenSysOutputParaFile();
//	BOOL OpenSystemParasFile();

public:
	//suyang 20230710 发送探测命令
	virtual void SendIecDetect(long bEnable);
	virtual void SendIecRecord(CDataGroup *pIecRecordParas);


	//2022-4-13  lijunqing
        virtual void On_IecDetect(CDataGroup *pIecCb);

	bool m_bStarted;//2023-11-30 suyang 使用于两台电脑控制一台仪器的情况下，一台电脑开始测试另外一台不响应测试
	bool m_bUpdateRtData; //20240328 suyang 是否更新实时数据


};

extern CSttTestAppConfigTool g_oSttTestAppConfigTool;
extern CSttTestAppCfg g_oSttTestAppCfg;   

double CalcSpanTime(SYSTEMTIME &tmStart,SYSTEMTIME &tmEnd);
void InitDefaultSystemParas();
void InitDefualtSysOutputPara();
void InitDefaultPtTestPara();
void stt_xml_serialize_write_SysOutput();
