#include "stdafx.h"
#include"SttDCBreakTest.h"

//2023-11-16-xuzhantao

CString CSttDCBreakTest::m_strMacroName = "开关保护测试";
CString CSttDCBreakTest::m_strMacroID = STT_MACRO_ID_DCBreakTest;
CString CSttDCBreakTest::m_strFilePostFix = "stttst";
CString CSttDCBreakTest::m_strMacroVer = "1.0";

CSttDCBreakTest::CSttDCBreakTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
}

void CSttDCBreakTest::Init()
{
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_oDcBreakParas.init();
    m_oDcBreakResults.init();
    CSttTestBase::Init();
    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    g_theSystemConfig->m_nHasAnalog = 0;
    g_theSystemConfig->m_nHasWeek = 0;
}

CSttDCBreakTest::~CSttDCBreakTest(void)
{
}

void CSttDCBreakTest::AfterSetParameter()
{
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
    paraState0->m_uiVOL[i].Harm[1].fAmp = 0;
    paraState0->m_uiVOL[i].Harm[1].fAngle = 0;
    paraState0->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState0->m_uiCUR[i].Harm[1].fAmp = 0;
        paraState0->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState0->m_uiCUR[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState0->m_binOut[i].nState = m_oDcBreakParas.m_nStateBOut[i];
    }

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        paraState0->m_binIn[i].nSelect = m_oDcBreakParas.m_binIn[i].nSelect;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState0->m_binInEx[i].nSelect = m_oDcBreakParas.m_binInEx[i].nSelect;
    }

    switch(m_oDcBreakParas.m_nFaultTrigMode)
    {
        case 1:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_MEARSURETRIGGER;
        }
        break;

        case 2:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_BINTRIGGER;
            paraState0->m_fTimeAfterTrigger =  m_oDcBreakParas.m_fPostFaultTime;
        }
        break;

        case 3:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_GPSBTRIGGER;
            paraState0->m_tGps.nHour = m_oDcBreakParas.m_tGps.nHour;
            paraState0->m_tGps.nMinutes = m_oDcBreakParas.m_tGps.nMinutes;
            paraState0->m_tGps.nSeconds = m_oDcBreakParas.m_tGps.nSeconds;
        }
        break;

        default:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
            paraState0->m_fTimeState = m_oDcBreakParas.m_fPreFaultTime;
            //paraState0->m_fTimeState = m_oDcBreakParas.m_fMaxFaultTime + m_oDcBreakParas.m_fMarginTime;
        }
    }

    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState1->m_fTimeState = m_oDcBreakParas.m_fMarginTime + m_oDcBreakParas.m_fTSetting;
    paraState1->m_fTimeAfterTrigger =  m_oDcBreakParas.m_fPostFaultTime;
    paraState1->m_nBinLogic = m_oDcBreakParas.m_nBinLogic;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = 0;
        paraState1->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState1->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState1->m_uiCUR[i].Harm[1].fAmp = 0;
        paraState1->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState1->m_uiCUR[i].Harm[1].fFreq = 0;
    }
    paraState1->m_uiCUR[m_oDcBreakParas.m_nFaultChannel].Harm[1].fAmp = m_oDcBreakParas.m_fISetting * m_oDcBreakParas.m_fRate;

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binOut[i].nState = m_oDcBreakParas.m_nStateBOut[i];
    }

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        paraState1->m_binIn[i].nSelect = m_oDcBreakParas.m_binIn[i].nSelect;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState1->m_binInEx[i].nSelect = m_oDcBreakParas.m_binInEx[i].nSelect;
    }

    Global_SetStateBoutPreFault(m_pStateTest->m_oStateParas.m_paraState, m_oDcBreakParas.m_nStateBOut,
                                m_oDcBreakParas.m_nOutputSwitchMode, m_oDcBreakParas.m_nBinLogic, m_oDcBreakParas.m_fBoutTimeTrig, m_oDcBreakParas.m_fBoutHoldTime);
}

long CSttDCBreakTest::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct)
    {
        m_oDcBreakResults.m_fTripTime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;
    }
    return  0;
}

void CSttDCBreakTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_DcBreak(&m_oDcBreakParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttDCBreakTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oDcBreakResults, pXmlSerialize);
}

void CSttDCBreakTest::StartTest()
{
    if(GetTestStarting())
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttDCBreakTest is  Running,Can't StartTest()");
        return;
    }

    CSttTestBase::StartTest();
    TtmToDrv();
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
    SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(StateTest);
#endif
    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttDCBreakTest::StartTest >>>>>>");
}

void CSttDCBreakTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StatePara(&m_pStateTest->m_oStateParas);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);
#endif
}
