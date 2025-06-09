#pragma once

#define USE_SttImpBaseTest

#include "../SttManuTest.h"
#include "tmt_power_manu_test.h"

class CSttManualPowerTest : public CSttManuTest

{
public:
    CSttManualPowerTest();
    virtual ~CSttManualPowerTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttManualPowerTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType);
	virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex);
	virtual void SyncGradientResult(int nStep, double dTime, int nTripType);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual void TtmToDrv();

protected:

	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
	tmt_PowerManuResult m_oManualPowerResults;
	tmt_GradientParas m_oGradientParas;
	tmt_channel m_uiVOL[4];
	tmt_ChannelPower m_uiPOW[3];
};
