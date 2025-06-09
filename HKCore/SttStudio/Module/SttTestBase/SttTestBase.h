#pragma once

#include "SttMacroXmlKeys.h"
#include "SttTestBaseSearch.h"
#include "SttTestBaseComlexSearch.h"
#include "../../../Module/BaseClass/ComplexNumber.h"
#include "../SttCmd/SttParas.h"
#include "SttTestEventArray.h"
#include "../SttTest/Common/tmt_gradient_test.h"
#include "../SttTest/Common/tmt_state_test.h"
#include "../SttTest/Common/tmt_manu_test.h"
#include "../SttTest/Common/tmt_harm_test.h"
#include "../SttTest/Common/Impedance/tmt_imp_base_test.h"
#include "../SttTest/Common/Syn/tmt_syn_test.h"
#include "../SttTest/Common/Async/tmt_async_manu_test.h"
#include "../SttTest/Common/Async/tmt_async_state_test.h"

//参数类型
#define PARATYPE_FAULT    0
#define PARATYPE_SYSTEM 1
#define PARATYPE_RESULT  2

#define TIME_MAX_WAITING		300			//最长触发等待时间
#define TIME_ONLINE_DELAY		  1			//联机延时

//TestType
#define ManualTest      0
#define GradientTest    1
#define HarmTest        2
#define StateTest       3
#define ShakeTest       4
#define IECDataCfg      5
#define SvCtrlCfg       6
#define GseCtrlCfg      7
#define FiberCtrlCfg    8
#define AbnoramlTest    9
#define LtReplayTest    10
#define ReplayTestCfg   11
#define ReplayTestData  12
#define Record          13
#define SystemDefaultOutput 14
#define SOE             15
#define Ft3CtrlCfg      16
#define CboperTest      17
#define ClearSvCfg      18
#define IECDataCfg_Stable2M   19
#define MUTest          20
#define ComDataPkg      21
#define BinaryStateTest 22
#define SynTest         23
#define BinaryManuTest  24
#define Ft3DataCfg      25
#define BinaryStateExTest 26

//////////////////////////////////////////////////////////////////////////
//CSttTestBase
class CSttTestBase : public CExBaseList
{
public:
    CSttTestBase();
    virtual ~CSttTestBase(void);

    CString m_strPxAppName;  //测试仪器的种类

	void SetSearchMode()	{	m_bIsSearchMode = TRUE;	}
	BOOL IsSearchMode()	{	return m_bIsSearchMode;		}
	void SetTestChanged(BOOL bChanged=TRUE)	{	m_bIsTestChanged = bChanged;	}
	BOOL IsTestChanged()										{	return m_bIsTestChanged;			}

    char *m_pDrvResults;
	double m_dTestStartTime;	
    long   m_nCurStateLoopIndex;	//当前状态循环序号
    long   m_nCurStateIndex;		//当前状态序号
    long   m_nCurStepIndex;			//当前递变序号
    BOOL   m_bBinStopTest;
    STT_TIME m_oTestFinishedTime;
    long   m_nStateNum[100];
    long   GetStateNum(long nStateIndex);
protected:
    CString m_strFileType;
    CString  m_strTestID; //测试底层功能ID
    CString  m_strTestVer; //测试底层功能version

    long    m_nRsltJdg;    //结果判断
    long    m_nRsltDsc;    //结果描述
    BOOL  m_bIsSearchMode;  //测试功能是搜索线模式
    BOOL  m_bIsTestChanged;	//测试是否改变
    float	m_fAbsError;	//绝对误差
    float	m_fRelError;	//相对误差

    DWORD m_dwHasPostFinishMsg;
    BOOL m_bTestStarting;//实验是否进行中
    BOOL m_bTestParaCheckOk;//实验参数检查无误
public:
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize_WithPara(CSttXmlSerializeBase *pXmlSerialize);

    //2020-04-9  扩展测试功能对应的底层测试功能
    virtual void Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize_WithPara_Basic(CSttXmlSerializeBase *pXmlSerialize);

    //2020-10-26  lijunqing 底层驱动结构体的XML串行化
    virtual void Para_XmlSerialize_Drv(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize_Drv(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize_WithPara_Drv(CSttXmlSerializeBase *pXmlSerialize);

    virtual BOOL EventProcess();
	virtual BOOL EventProcessEx();
    virtual void Init();
    virtual void StartTest();
    virtual void UpdateParameter();
	virtual long SetParameter(DWORD dwState=0);
    virtual void Stop();
	virtual void Triger(){}
	virtual void OnSendDataFinish(int nIndex,int nSendNum){}
	virtual void OnSendDataStart(int nIndex,int nSendNum){}
	virtual void OnAfterMoveToComtradeBuf(int nIndex,int nDataLen){}
	virtual BOOL GetTestStarting() {return m_bTestStarting;}
	virtual void SetTestStarting(BOOL bTestStarting) {m_bTestStarting=bTestStarting;}
	virtual long StopDevice()		{	return 0;	}
	virtual long OnTimer(BOOL &bFinish, long nTimerLongMs=500)	{	return 0;	}
	virtual long CalReport(UINT nState=0)	{	return 0;	}
    virtual void InitStateLoopResults(){}

    //2020-10-26  lijunqing
	virtual bool NeedCheckHeartbeat()	{	return true;		}

    //2021-03-12 zhoulei
	virtual bool TestPara_CheckOK()	{	return true;		}
public:
	virtual double GetTestTimeLong()	{	return -1;	}
	virtual BOOL IsTestFinished(DWORD dwState)		{	return TRUE;	}
    virtual BOOL IsTestTimeFinished(long nMs);
	virtual long ValidateBeforeTest()		{		return 0;		} //测试前检查参数有效性

    //调试报告的处理部分
    DWORD CalTestUseTimeLong();			//获取测试从开始到现在的时间长度
    virtual BOOL IsTestOverTime(long nMsEx = 30000);

public://用于公共计算类
	float GetTimeFromLong(UINT nS,UINT nnS);
	DWORD m_dwBeginTickCount;	
    DWORD m_dwCurTickCount;
public:
    //2020-12-22  lijunqing 测试事件处理
    void ReturnTestStateEvent(long nEventType, double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent);
    virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
    virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent); // zhouhj 20210626 对于搜索阻抗边界,需要在子类中进行测试点的切换,将其改为虚函数
    void ReturnRealTimeEvent();  //返回实时事件

	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType){}//nType: 0:变化前,1:故障前,2:故障
	virtual void SyncSingleStateTmtResult(){}
	virtual void SyncGradientResult(int nStep,double dTime,int nTripType){}//nTripType: 0-动作段 1-返回段
	void ProGradientRtDatasEvent(STT_RTDATA_EVENT &oRtdata,int nStep,int nType);

public://zhouhj 20210703 高级试验重载函数
	virtual void InitParaBeforeGradient(tmt_GradientParas *pTmt_GradientParas,long nGradientChCount = 3);
	virtual void CalStepValue_Gradient(tmt_GradientParas *pTmt_GradientParas,int nHarmIndex = 1,long nGradientChCount = 3);
	virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas,float fCurValue,int nHarmIndex);
    virtual void SetUIParaToStepUI(tmt_channel *uData, tmt_channel *iData, tmt_StepUI *pUIStepData, int nHarmIndex);

	void InitParaBeforeGradient_Chs(tmt_GradientParas *pTmt_GradientParas,long nCurrentChCount,long nVoltageChCount);
	float GetMaxValue(float fValue1,float fValue2);//
    void GradientAllChAndAllType(int nChNum = 3);//zhouhj 20211008 递变全部通道的幅值、相位、频率
};

extern BOOL g_bLogTestParaAndReport;
extern BOOL g_bLogTestStateMsg;

extern BOOL g_bUpdateFPGA;
extern BOOL g_bNeedReadDeviceStatatus;

extern long g_nRtDataVoltCnt;
extern long g_nRtDataCurrCnt;

extern tmt_AsyncManualTest *g_pAsyncManualTest;
extern tmt_AsyncStateTest *g_pAsyncStateTest;

char* stt_test_new_drvparas_buff();
void stt_test_free_drvparas_buff();
char* stt_test_get_drvparas_buff();

char* stt_test_new_drvresult_buff();
void stt_test_free_drvresult_buff();
char* stt_test_get_drvresult_buff();

tmt_ManualTest *stt_test_new_base_manualtest_buff();
tmt_ManualTest* stt_test_get_base_manualtest_buff();
void stt_test_free_base_manualtest_buff();

tmt_StateTest *stt_test_new_base_statetest_buff();
tmt_StateTest* stt_test_get_base_statetest_buff();
void stt_test_free_base_statetest_buff();

tmt_ImpBaseParas *stt_test_new_ex_ImpBase_buff();
tmt_ImpBaseParas* stt_test_get_ex_ImpBase_buff();
void stt_test_free_ex_ImpBase_buff();

tmt_HarmTest *stt_test_new_base_harmtest_buff();
tmt_HarmTest* stt_test_get_base_harmtest_buff();
void stt_test_free_base_harmtest_buff();

tmt_SynParas *stt_test_new_synparas_buff();
tmt_SynParas *stt_test_get_synparas_buff();
void stt_test_free_synparas_buff();
