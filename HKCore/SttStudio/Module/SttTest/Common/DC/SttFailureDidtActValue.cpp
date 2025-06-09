#include "stdafx.h"
#include "SttFailureDidtActValue.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttFailureDidtActValue::m_strMacroName = "失灵保护2段动作值";
CString CSttFailureDidtActValue::m_strMacroID = STT_MACRO_ID_FailureProtDidtActValue;
CString CSttFailureDidtActValue::m_strFilePostFix = "stttst";
CString CSttFailureDidtActValue::m_strMacroVer = "1.0";

CSttFailureDidtActValue::CSttFailureDidtActValue() : CSttFailureProtTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
    Init();
}

void CSttFailureDidtActValue::Init()
{
    CSttStateTest::Init();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 3;
    m_pStateTest->m_oStateParas.init(3);
    m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    m_oFailureProtTestParas.init();
    m_oFailureProtTestResults.init();
	g_theSystemConfig->m_nHasAnalog = 0;
	g_theSystemConfig->m_nHasWeek = 0;
    m_bIsTest = TRUE;
}

CSttFailureDidtActValue::~CSttFailureDidtActValue(void)
{
}

void CSttFailureDidtActValue::AfterSetParameter()
{
    CSttFailureProtTest::AfterSetParameter();
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    tmt_StatePara  *paraState2 = &m_pStateTest->m_oStateParas.m_paraState[2];
    paraState2->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState2->m_nBinLogic = m_oFailureProtTestParas.m_nBinLogic;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState2->m_uiVOL[i].Harm[1].fAmp = m_oFailureProtTestParas.m_fPreFaultVol;
        paraState2->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState2->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState2->m_uiCUR[i].Harm[1].fAmp = m_oFailureProtTestParas.m_fPreFaultCur;
        paraState2->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState2->m_uiCUR[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState2->m_binOut[i].nState = m_oFailureProtTestParas.m_nStateBOut[i];
    }

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        paraState2->m_binIn[i].nSelect = m_oFailureProtTestParas.m_binIn[i].nSelect;
    }

    int oIChanSelect = m_oFailureProtTestParas.m_nIChanSelect;
    paraState1->m_uiCUR[oIChanSelect].Harm[1].fAmp = m_oFailureProtTestParas.m_fIstart;
    paraState1->m_uiCUR[oIChanSelect].Ramp[0].fEnd = m_oFailureProtTestParas.m_fIend;
    paraState1->m_uiCUR[oIChanSelect].Ramp[0].fStep = m_fDidNow * 0.001;
    paraState1->m_uiCUR[oIChanSelect].Ramp[0].fStepTime = 0.001f;
    paraState1->m_uiCUR[oIChanSelect].Ramp[0].nIndex = 1;
    paraState1->m_nRampTimeGrad = 1;
    paraState1->m_fTimeState = m_oFailureProtTestParas.m_fMarginTime + m_oFailureProtTestParas.m_fHoldTime
            +  fabs(m_oFailureProtTestParas.m_fIend - m_oFailureProtTestParas.m_fIstart)/m_fDidNow;

    paraState2->m_uiCUR[oIChanSelect].Harm[1].fAmp = m_oFailureProtTestParas.m_fIend;
    paraState2->m_uiCUR[oIChanSelect].Ramp[0].fEnd = m_oFailureProtTestParas.m_fIstart;
    paraState2->m_uiCUR[oIChanSelect].Ramp[0].fStep = m_fDidNow * 0.001;
    paraState2->m_uiCUR[oIChanSelect].Ramp[0].fStepTime = 0.001f;
    paraState2->m_uiCUR[oIChanSelect].Ramp[0].nIndex = 1;
    paraState2->m_nRampTimeGrad = 1;
    paraState2->m_fTimeState = m_oFailureProtTestParas.m_fMarginTime + m_oFailureProtTestParas.m_fHoldTime
            +  fabs(m_oFailureProtTestParas.m_fIend - m_oFailureProtTestParas.m_fIstart)/m_fDidNow;
}

long CSttFailureDidtActValue::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct || m_pStateTest->m_oStateResults.m_resultState[2].m_nAct)
    {
        m_oFailureProtTestResults.m_fResSACValue = m_fDidNow;
    }
    return 0;
}

void CSttFailureDidtActValue::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    //CSttDeviceBase::g_pSttDeviceBase->SetSyncSecond();
#endif
    stt_xml_serialize_FailureProtDidtActValue(&m_oFailureProtTestParas, pXmlSerialize);

    m_fDidNow = m_oFailureProtTestParas.m_fDidtStart;

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttFailureDidtActValue::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_FailureProtDidtActValue(&m_oFailureProtTestResults, pXmlSerialize);
}

void CSttFailureDidtActValue::UpdatePara()
{
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    tmt_StatePara  *paraState2 = &m_pStateTest->m_oStateParas.m_paraState[2];

    paraState0->m_fTimeState = m_oFailureProtTestParas.m_fHoldTime;

    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].fStep = m_fDidNow * 0.001;
    paraState1->m_fTimeState = m_oFailureProtTestParas.m_fMarginTime + m_oFailureProtTestParas.m_fHoldTime
            +  fabs(m_oFailureProtTestParas.m_fIend - m_oFailureProtTestParas.m_fIstart)/m_fDidNow;

    paraState2->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].fStep = m_fDidNow * 0.001;
    paraState2->m_fTimeState = paraState1->m_fTimeState;
}

BOOL CSttFailureDidtActValue::CalNext()
{
    if(m_oFailureProtTestParas.m_fDidtStart < m_oFailureProtTestParas.m_fDidtEnd)
    {
    m_fDidNow += m_oFailureProtTestParas.m_fDidtStep;
    if(m_fDidNow > m_oFailureProtTestParas.m_fDidtEnd)
    {
        m_fDidNow = m_oFailureProtTestParas.m_fDidtEnd;
    }
    }
    else
    {
        m_fDidNow -= m_oFailureProtTestParas.m_fDidtStep;
        if(m_fDidNow < m_oFailureProtTestParas.m_fDidtEnd)
        {
            m_fDidNow = m_oFailureProtTestParas.m_fDidtEnd;
        }
    }
    UpdatePara();
    return TRUE;
}

BOOL CSttFailureDidtActValue::IsGradientFinished()
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct || m_pStateTest->m_oStateResults.m_resultState[2].m_nAct)
    {
        m_oFailureProtTestResults.m_fResSACValue = m_fDidNow;
        return TRUE;
    }

    if(m_oFailureProtTestParas.m_fDidtStart < m_oFailureProtTestParas.m_fDidtEnd && m_fDidNow < m_oFailureProtTestParas.m_fDidtEnd)
    {
        return FALSE;
    }
    else if (m_oFailureProtTestParas.m_fDidtStart > m_oFailureProtTestParas.m_fDidtEnd && m_fDidNow > m_oFailureProtTestParas.m_fDidtEnd)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

void CSttFailureDidtActValue::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
    if(!IsGradientFinished())
    {
        CalNext();
        StartTest();//后续开始测试操作
        return;
    }

    CSttFailureProtTest::ReturnTestStateEvent_TestFinish(dTime, dRealTime, bWithEvent);
}

void CSttFailureDidtActValue::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;
    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

    if(m_bIsTest) //只有第一个测试点,需要下发开始测试命令,后续测试点不需要
    {
        m_bIsTest = FALSE;
        pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
    }

    pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}
