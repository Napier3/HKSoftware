#pragma once

#include "../../../SttTestBase/SttTestBase.h"
#include "../../../SttTestBase/SttComplexp.h"
#include "tmt_linevolt_gradient_test.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

class CSttLineVoltGradientTest : public CSttTestBase
{
public:
    CSttLineVoltGradientTest();
    virtual ~CSttLineVoltGradientTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;
    tmt_GradientParas m_oGradientParas;
    tmt_LineVolGradientResult m_oGradientResult;
    tmt_channel m_uiVOL[3][4];//Uab1 3U1-0 Uab2 3U2-0
    tmt_channel m_uiCUR[3][6];//Ia1 Ib1 Ic1 Ia2 Ib2 Ic2

    static CSttTestBase *CreateTest()
    {
        return new CSttLineVoltGradientTest();
    }

public:
    virtual void Init();
    virtual long SetParameter(DWORD dwState = 0);
    virtual void TtmToDrv();
    virtual void AfterSetParameter();
    virtual double GetTestTimeLong();
    virtual long CalReport(UINT nState = 0);
    virtual void StartTest();
    virtual BOOL EventProcess();

public:
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType);
    virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex);
    virtual void SyncGradientResult(int nStep, double dTime, int nTripType);

protected:
    void CalStepValue_Chs(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue);
    virtual void TranslateToStateParas();
    void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
