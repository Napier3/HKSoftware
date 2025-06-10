#pragma once
#include "SttSequenceGradientTest.h"



class CSttSequenceGradientPnvTest : public CSttSequenceGradientTest
{
public:
    CSttSequenceGradientPnvTest();
    virtual ~CSttSequenceGradientPnvTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;
    static CSttTestBase *CreateTest()
    {
        return new CSttSequenceGradientPnvTest();
    }

public:
    virtual void AfterSetParameter();
    virtual void StartTest();

public:
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
    virtual void CalStepValue_SequenceChs(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue);
};
