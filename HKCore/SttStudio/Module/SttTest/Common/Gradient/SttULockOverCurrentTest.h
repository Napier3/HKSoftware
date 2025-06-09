#pragma once

#include "../SttGradientTest.h"
#include "tmt_ulock_overcurrent_test.h"


class CSttULockOverCurrentTest : public CSttGradientTest
{
public:
    CSttULockOverCurrentTest();
    virtual ~CSttULockOverCurrentTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttULockOverCurrentTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

	virtual void InitParaBeforeGradient(long nGradientChCount = 3);
	virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas,float fCurValue,int nHarmIndex);
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
	virtual void TtmToDrv();

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

protected:
	virtual void TranslateToStateParas();//
	virtual void SyncGradientResult(int nStep,double dTime,int nTripType);//nTripType: 0-¶¯×÷¶Î 1-·µ»Ø¶Î

	tmt_ULockOverCurrentParas m_oULockOverCurrentParas;
//	tmt_ULockOverCurrentResults m_oULockOverCurrentResults;
};
