#pragma once

#include "SttImpBaseTest.h"
#include "tmt_power_freq_test.h"

class CSttPowerFreqTest : public CSttImpBaseTest ,public tmt_PowerFreqParas
{
public:
    CSttPowerFreqTest();
    virtual ~CSttPowerFreqTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttPowerFreqTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
    {
		CSttImpBaseTest::ReturnTestStateEvent_TestStart(dTime,dRealTime,bWithEvent);
    }

	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
	{
		CSttImpBaseTest::ReturnTestStateEvent_TestFinish(dTime,dRealTime,bWithEvent);
	}

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数

	tmt_PowerFreqResults m_oPowerFreqResults;
};
