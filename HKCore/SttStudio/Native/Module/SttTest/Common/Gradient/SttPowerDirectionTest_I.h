#pragma once

#include "../SttGradientMaxAngleTest.h"
#include "tmt_power_direction_test.h"


class CSttPowerDirectionTest_I : public CSttGradientMaxAngleTest
{
public:
    CSttPowerDirectionTest_I();
    virtual ~CSttPowerDirectionTest_I(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttPowerDirectionTest_I();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

	virtual void InitParaBeforeGradient(long nGradientChCount = 3);
	virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas,float fCurValue,int nHarmIndex);
	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);
	virtual void SyncGradientResult(int nStep,double dTime,int nTripType);//nTripType: 0-¶¯×÷¶Î 1-·µ»Ø¶Î
	virtual void TtmToDrv();

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);

protected:
	 virtual void TranslateToStateParas();//

    tmt_PowerDirectionParas_I m_oPowerDirectionParas_I;
};
