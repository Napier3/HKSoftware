#pragma once

#include"../SttStateTest.h"
#include "tmt_dc_voltage_test.h"

class CSttDCVoltageTest : public CSttStateTest, public tmt_dc_voltage_test
{
public:
    CSttDCVoltageTest();
    virtual ~CSttDCVoltageTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase *CreateTest()
    {
        return new CSttDCVoltageTest;
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

    //���ϲ�ṹ��תΪ�ײ�ṹ��
public:
    virtual void TtmToDrv();
};

