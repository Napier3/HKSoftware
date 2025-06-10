#pragma once

#include "../../../SttTestBase/SttTestBase.h"
#include "../../../SttTestBase/SttComplexp.h"
#include "tmt_sequence_gradient_test.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

class CSttSequenceGradientTest : public CSttTestBase
{
public:
    CSttSequenceGradientTest();
    virtual ~CSttSequenceGradientTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;
    tmt_GradientParas m_oGradientParas;
    tmt_GradientResult m_oGradientResult;
    tmt_channel m_uiVOL[3][3];//Õý³£Ì¬+¹ÊÕÏÌ¬ 3U3I
    tmt_channel m_uiCUR[3][3];

    static CSttTestBase *CreateTest()
    {
        return new CSttSequenceGradientTest();
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
    virtual void SyncGradientResult(int nStep, double dTime, int nTripType);

protected:
    virtual void CalStepValue_SequenceChs(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue);
    virtual void TranslateToStateParas();
    void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
};
