#pragma once

#include"../SttStateTest.h"
#include "tmt_dc_break_test.h"

class CSttDCBreakTest : public CSttStateTest, public tmt_dc_break_test
{
public:
    CSttDCBreakTest();
    virtual ~CSttDCBreakTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase *CreateTest()
    {
        return new CSttDCBreakTest;
    }

public:
    virtual void AfterSetParameter();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs)
    {
        return true;
    }
    virtual void StartTest();
    virtual long CalReport(UINT nState=0);

    //将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();
};

