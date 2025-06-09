#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"../../../SttTestBase/SttComplexp.h"
#include "tmt_async_state_test.h"

#include "../../../SttTestBase/SttFaultCalculatTool.h"

#ifdef _PSX_IDE_QT_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

typedef struct tmt_state_rsteval
{
    BOOL        m_bSelect;
    int         m_nBeginType;//0-开入量触发 1-状态进入 2-状态内开入变位
    int         m_nBeginState;
    int         m_nBeginBin;
    int         m_nBeginValue;//状态
    int         m_nEndType;
    int         m_nEndState;
    int         m_nEndBin;
    int         m_nEndValue;
}tmt_StateRstEval;

class CSttAsyncStateTest : public CSttTestBase
{
public:
	CSttAsyncStateTest();
	virtual ~CSttAsyncStateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
		return new CSttAsyncStateTest();
	}
public:

// 	//过程参数
// 	Complex m_CmpUI[2][MAX_VOLTAGE_COUNT];    

    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

    tmt_StateRstEval m_oRstEval[10];
public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
	{
		CSttTestBase::ReturnTestStateEvent_TestStart(dTime,dRealTime,bWithEvent);
	}

	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
	{
		CSttTestBase::ReturnTestStateEvent_TestFinish(dTime,dRealTime,bWithEvent);
	}

public:
	virtual void Init();

	virtual long SetParameter(DWORD dwState=0);
    virtual void StartTest();
	virtual void Stop();
	virtual BOOL EventProcess();
	virtual void Triger();
    virtual void InitStateLoopResults();

    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
	virtual void SyncSingleStateTmtResult();
};


