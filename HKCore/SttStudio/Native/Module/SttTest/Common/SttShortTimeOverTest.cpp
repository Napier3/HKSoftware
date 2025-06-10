#include "stdafx.h"
#include "SttShortTimeOverTest.h"
#include "SttSystemConfig.h"
#include "../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttShortTimeOverTest::m_strMacroName = "短时过量输入";
CString CSttShortTimeOverTest::m_strMacroID = STT_MACRO_ID_ShortTimeOverTest;
CString CSttShortTimeOverTest::m_strFilePostFix = "state";
CString CSttShortTimeOverTest::m_strMacroVer = "1.0";

CSttShortTimeOverTest::CSttShortTimeOverTest() : CSttStateTest()
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

void CSttShortTimeOverTest::Init()
{
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    CSttTestBase::Init();
}

CSttShortTimeOverTest::~CSttShortTimeOverTest(void)
{
}

void CSttShortTimeOverTest::AfterSetParameter()
{
    m_pStateTest->m_oStateParas.m_nRepeatNumbers = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_nInflictCount - 1;
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_uiVOL[i].Harm[1].fAmp;
        paraState0->m_uiVOL[i].Harm[1].fAngle = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_uiVOL[i].Harm[1].fAngle;
        paraState0->m_uiVOL[i].Harm[1].fFreq = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_uiVOL[i].Harm[1].fFreq;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState0->m_uiCUR[i].Harm[1].fAmp = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_uiCUR[i].Harm[1].fAmp;
        paraState0->m_uiCUR[i].Harm[1].fAngle = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_uiCUR[i].Harm[1].fAngle;
        paraState0->m_uiCUR[i].Harm[1].fFreq = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_uiCUR[i].Harm[1].fFreq;
    }

    paraState0->m_fTimeState = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_fOnceInflictTime;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState1->m_uiCUR[i].Harm[1].fAmp = 0;
    }
    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    paraState1->m_fTimeState = m_oShortTimeOverParas.m_pParaShortTimeOver[0].m_fIntervalTime;
}

long CSttShortTimeOverTest::CalReport(UINT nState)
{
    return 0;
}

void CSttShortTimeOverTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    //CSttDeviceBase::g_pSttDeviceBase->SetSyncSecond();
#endif
    stt_xml_serialize_ex2(&m_oShortTimeOverParas, pXmlSerialize, 18, 18);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttShortTimeOverTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{

}
