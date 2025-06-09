#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"../../../SttTestBase/SttComplexp.h"

#include "SttSynActFreqTest.h"

class CSttSynLeadAngleTest : public CSttSynActFreqTest
{
public:
    CSttSynLeadAngleTest();
    virtual ~CSttSynLeadAngleTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttSynLeadAngleTest();
    }

public:
    virtual long CalReport(UINT nState=0);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
    virtual void ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA);
};
