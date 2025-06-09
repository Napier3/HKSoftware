#include "stdafx.h"
#include "SttFailureDidtActTime.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttFailureDidtActTime::m_strMacroName = "失灵保护2段动作时间";
CString CSttFailureDidtActTime::m_strMacroID = STT_MACRO_ID_FailureProtDidtActTime;
CString CSttFailureDidtActTime::m_strFilePostFix = "stttst";
CString CSttFailureDidtActTime::m_strMacroVer = "1.0";

CSttFailureDidtActTime::CSttFailureDidtActTime() : CSttFailureProtTest()
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

void CSttFailureDidtActTime::Init()
{
    CSttFailureProtTest::Init();
}

CSttFailureDidtActTime::~CSttFailureDidtActTime(void)
{
}

void CSttFailureDidtActTime::AfterSetParameter()
{
    CSttFailureProtTest::AfterSetParameter();
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Harm[1].fAmp = m_oFailureProtTestParas.m_fIstart;
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].fEnd = m_oFailureProtTestParas.m_fIend;
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].fStep = m_oFailureProtTestParas.m_fDidt * 0.001;
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].fStepTime = 0.001f;
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].nIndex = 1;
    paraState1->m_nRampTimeGrad = 1;
    paraState1->m_fTimeState = m_oFailureProtTestParas.m_fMarginTime + m_oFailureProtTestParas.m_fHoldTime
            +  fabs(m_oFailureProtTestParas.m_fIend - m_oFailureProtTestParas.m_fIstart)/m_oFailureProtTestParas.m_fDidt;
}

long CSttFailureDidtActTime::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct)
    {
        m_oFailureProtTestResults.m_fResSATime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;

    }
    return 0;
}

void CSttFailureDidtActTime::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    //CSttDeviceBase::g_pSttDeviceBase->SetSyncSecond();
#endif
    stt_xml_serialize_FailureProtDidtActTime(&m_oFailureProtTestParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttFailureDidtActTime::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_FailureProtDidtActTime(&m_oFailureProtTestResults, pXmlSerialize);
}
