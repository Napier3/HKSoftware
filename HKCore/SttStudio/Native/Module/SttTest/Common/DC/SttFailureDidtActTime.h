#pragma once

#include "SttFailureProtTest.h"


class CSttFailureDidtActTime : public CSttFailureProtTest
{
public:
    CSttFailureDidtActTime();
    virtual ~CSttFailureDidtActTime(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttFailureDidtActTime();
    }
public:

    virtual void Init();
    virtual void AfterSetParameter();
    virtual long CalReport(UINT nState=0);

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
