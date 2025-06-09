#pragma once

#include "SttFailureProtTest.h"


class CSttFailureProtActTime : public CSttFailureProtTest
{
public:
    CSttFailureProtActTime();
    virtual ~CSttFailureProtActTime(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttFailureProtActTime();
    }
public:

    virtual void Init();
    virtual void AfterSetParameter();
    virtual long CalReport(UINT nState=0);

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
