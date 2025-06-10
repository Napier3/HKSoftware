#pragma once
#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "tmt_abnsimulation_test.h"

#ifdef _PSX_IDE_QT_
#include "drv_abnormal_test.h"
#include "../../SttDevice/RelayTest/SttDevice.h"
#endif

#define TIME_MAX_WAITING		300			//最长触发等待时间
#define TIME_ONLINE_DELAY		1			//联机延时

class CSttAbnormalTest : public CSttTestBase, public tmt_AbnSimulationTest
{
public:
    CSttAbnormalTest();
    virtual ~CSttAbnormalTest(void);

#ifdef _PSX_IDE_QT_
	drv_abnstate_test       m_oDrvStateAbnormalData;
#endif
    structResultItem  m_oDrvResults;

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttAbnormalTest();
    }
public:

    int		m_nCurStateIndex;			//当前状态序号

    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
    virtual void AfterSetParameter();
    virtual double GetTestTimeLong();
    virtual long CalReport(UINT nState=0);

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    bool m_Start;
public:
    virtual void Init(long nStateNums);
    virtual void EventProcess();
    virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
    virtual void Stop();

    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();
};
