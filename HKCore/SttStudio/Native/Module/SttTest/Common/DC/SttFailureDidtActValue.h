#pragma once

#include "SttFailureProtTest.h"


class CSttFailureDidtActValue : public CSttFailureProtTest
{
public:
    CSttFailureDidtActValue();
    virtual ~CSttFailureDidtActValue(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttFailureDidtActValue();
    }
public:

    virtual void Init();
    virtual void AfterSetParameter();
    virtual long CalReport(UINT nState=0);

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual BOOL IsGradientFinished();
    virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
    virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);

protected:
    BOOL CalNext();
    void UpdatePara();
    float m_fDidNow;
    bool m_bIsTest;
};
