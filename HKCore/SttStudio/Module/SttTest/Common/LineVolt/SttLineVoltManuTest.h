#pragma once

#include "../SttManuTest.h"
#include "tmt_linevolt_manu_test.h"
#include "../tmt_gradient_test.h"


class CSttLineVoltManuTest : public CSttManuTest//, public tmt_SequenceManuParas
{
public:
    CSttLineVoltManuTest();
    virtual ~CSttLineVoltManuTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase *CreateTest()
    {
        return new CSttLineVoltManuTest();
    }
public:

    virtual void AfterSetParameter();
    virtual long CalReport(UINT nState = 0);

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType);
    virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex);
    virtual void SyncGradientResult(int nStep, double dTime, int nTripType);

public:
    virtual void Init();
    virtual long SetParameter(DWORD dwState = 0);
    virtual void TtmToDrv();

protected:
    void CalStepValue_Chs(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue);
    virtual void TranslateToStateParas();
    tmt_GradientParas m_oGradientParas;
    tmt_channel m_uiVOL[12];
    tmt_channel m_uiCUR[18];
};
