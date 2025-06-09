#pragma once

#include "../SttStateTest.h"
#include "tmt_low_freq_test.h"


class CSttLowFreqTimeTest : public CSttStateTest ,public tmt_LowFreqParas
{
public:
    CSttLowFreqTimeTest();
    virtual ~CSttLowFreqTimeTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttLowFreqTimeTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
    virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
	tmt_LowFreqResults m_oResults;
	float m_fDrvDfDt;
	float m_fDrvStepTime;
};
