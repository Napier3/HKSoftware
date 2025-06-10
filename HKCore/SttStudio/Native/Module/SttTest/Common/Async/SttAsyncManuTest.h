#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"../../../SttTestBase/SttComplexp.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

class CSttAsyncManuTest : public CSttTestBase
{
public:
	CSttAsyncManuTest();
	virtual ~CSttAsyncManuTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
		return new CSttAsyncManuTest();
    }
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeMS;
    UINT m_uChangeTime;
    UINT m_uChangeTimeMS;
    UINT m_uStartTimeNS;
    bool m_bIsReturn;
    UINT m_uReturnTimeMS;
    UINT m_uReturnTime;

public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
    virtual void AfterSetParameter();
    virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual long OnTimer(BOOL &bFinish, long nTimerLongMs=500);
    virtual void StartTest();
    virtual BOOL EventProcess();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Stop();
    BOOL CheckBeforeUpdatePara();//zhouhj 20211201 在更新参数前检查

public:
    virtual void TtmToDrv();
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
