#pragma once

#include "tmt_short_time_over_test.h"
#include "SttStateTest.h"

class CSttShortTimeOverTest : public CSttStateTest ,public tmt_ShortTimeOver_Test
{
public:
    CSttShortTimeOverTest();
    virtual ~CSttShortTimeOverTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttShortTimeOverTest();
    }
public:

    virtual void Init();
    virtual void AfterSetParameter();
    virtual long CalReport(UINT nState=0);

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
    {
        CSttTestBase::ReturnTestStateEvent_TestStart(dTime,dRealTime,bWithEvent);
    }
    virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
    {
        CSttTestBase::ReturnTestStateEvent_TestFinish(dTime,dRealTime,bWithEvent);
    }
};
