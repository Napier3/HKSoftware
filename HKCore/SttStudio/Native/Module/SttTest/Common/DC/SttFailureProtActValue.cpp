#include "stdafx.h"
#include "SttFailureProtActValue.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttFailureProtActValue::m_strMacroName = "失灵保护1段动作值";
CString CSttFailureProtActValue::m_strMacroID = STT_MACRO_ID_FailureProtActValue;
CString CSttFailureProtActValue::m_strFilePostFix = "stttst";
CString CSttFailureProtActValue::m_strMacroVer = "1.0";

CSttFailureProtActValue::CSttFailureProtActValue() : CSttFailureProtTest()
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

void CSttFailureProtActValue::Init()
{
    CSttFailureProtTest::Init();
}

CSttFailureProtActValue::~CSttFailureProtActValue(void)
{
}

void CSttFailureProtActValue::AfterSetParameter()
{
    CSttFailureProtTest::AfterSetParameter();
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Harm[1].fAmp = m_oFailureProtTestParas.m_fFIstart;
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].fEnd = m_oFailureProtTestParas.m_fFIend;
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].fStep = m_oFailureProtTestParas.m_fFIstep;
    paraState1->m_uiCUR[m_oFailureProtTestParas.m_nIChanSelect].Ramp[0].nIndex = 1;
    paraState1->m_nRampTimeGrad = (m_oFailureProtTestParas.m_fFActionTime + m_oFailureProtTestParas.m_fMarginTime)* 1000;
    paraState1->m_fTimeState = m_oFailureProtTestParas.m_fMarginTime + m_oFailureProtTestParas.m_fFActionTime + 0.5//比递变时间多0.5s
            +fabs(m_oFailureProtTestParas.m_fFIend - m_oFailureProtTestParas.m_fFIstart)/m_oFailureProtTestParas.m_fFIstep *m_oFailureProtTestParas.m_fFActionTime ;
}

long CSttFailureProtActValue::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct)
    {
        if(m_oFailureProtTestParas.m_fFIstart < m_oFailureProtTestParas.m_fFIend)
       {
            m_oFailureProtTestResults.m_fResFACurValue =  m_oFailureProtTestParas.m_fFIstart + CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nTripStep * m_oFailureProtTestParas.m_fFIstep;
        }
        else
        {
            m_oFailureProtTestResults.m_fResFACurValue =  m_oFailureProtTestParas.m_fFIstart - CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nTripStep * m_oFailureProtTestParas.m_fFIstep;

        }
    }
    return 0;
}

void CSttFailureProtActValue::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    //CSttDeviceBase::g_pSttDeviceBase->SetSyncSecond();
#endif
    stt_xml_serialize_FailureProtActValue(&m_oFailureProtTestParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttFailureProtActValue::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_FailureProtActValue(&m_oFailureProtTestResults, pXmlSerialize);
}
