#pragma once

#include "../../../SttTestBase/SttTestBase.h"
#include "../../../SttTestBase/SttComplexp.h"
#include "tmt_fault_gradient_test.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

class CSttFaultGradientTest : public CSttTestBase, public tmt_faultGradientTest
{
public:
	CSttFaultGradientTest();
	virtual ~CSttFaultGradientTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;
	tmt_GradientParas m_oGradientParas;

    static CSttTestBase *CreateTest()
    {
		return new CSttFaultGradientTest();
    }

public:
    virtual void Init();
    virtual long SetParameter(DWORD dwState = 0);
    virtual void TtmToDrv();
    virtual void AfterSetParameter();
    virtual double GetTestTimeLong();
    virtual long CalReport(UINT nState = 0);
    virtual BOOL EventProcess();
    virtual void StartTest();

public:
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType);
    virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex);
	virtual void GetFaultValue(tmt_StepUI *pUIStepData, float fCurValue);
    virtual void SyncGradientResult(int nStep, double dTime, int nTripType);

protected:
	void CalStepValue_Fault(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue);
    virtual void TranslateToStateParas();
    void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
