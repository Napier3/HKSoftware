#pragma once

#include"../SttStateTest.h"
#include "tmt_dc_overcurrent_test.h"

class CSttDCOverCurrentTest : public CSttStateTest, public tmt_dc_overcurrent_test
{
public:
    CSttDCOverCurrentTest();
    virtual ~CSttDCOverCurrentTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase *CreateTest()
    {
        return new CSttDCOverCurrentTest;
    }

public:
    virtual void AfterSetParameter();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

    virtual long CalReport(UINT nState=0);
public:
    virtual void Init();
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs)
    {
        return true;
    }
	virtual void StartTest();

    //将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();
};

