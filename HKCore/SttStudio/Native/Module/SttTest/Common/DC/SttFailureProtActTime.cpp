#include "stdafx.h"
#include "SttFailureProtActTime.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttFailureProtActTime::m_strMacroName = "失灵保护1段动作时间";
CString CSttFailureProtActTime::m_strMacroID = STT_MACRO_ID_FailureProtActTime;
CString CSttFailureProtActTime::m_strFilePostFix = "stttst";
CString CSttFailureProtActTime::m_strMacroVer = "1.0";

CSttFailureProtActTime::CSttFailureProtActTime() : CSttFailureProtTest()
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

void CSttFailureProtActTime::Init()
{
    CSttFailureProtTest::Init();
}

CSttFailureProtActTime::~CSttFailureProtActTime(void)
{
}

void CSttFailureProtActTime::AfterSetParameter()
{
    CSttFailureProtTest::AfterSetParameter();

    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    paraState1->m_fTimeState = m_oFailureProtTestParas.m_fMarginTime + m_oFailureProtTestParas.m_fFActionTime;
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Harm[1].fAmp = m_oFailureProtTestParas.m_fFI * m_oFailureProtTestParas.m_fMul;
}

long CSttFailureProtActTime::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct)
    {
    m_oFailureProtTestResults.m_fResFATime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;
    }
    return 0;
}

void CSttFailureProtActTime::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    //CSttDeviceBase::g_pSttDeviceBase->SetSyncSecond();
#endif
    stt_xml_serialize_FailureProtActTime(&m_oFailureProtTestParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttFailureProtActTime::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_FailureProtActTime(&m_oFailureProtTestResults, pXmlSerialize);
}
