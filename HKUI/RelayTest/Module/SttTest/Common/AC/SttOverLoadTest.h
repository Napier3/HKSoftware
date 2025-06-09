#pragma once

#include"../SttStateTest.h"
#include "tmt_overload_test.h"

class CSttOverLoadTest : public CSttStateTest, public tmt_overload_test
{
public:
    CSttOverLoadTest();
    virtual ~CSttOverLoadTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase *CreateTest()
    {
        return new CSttOverLoadTest;
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

