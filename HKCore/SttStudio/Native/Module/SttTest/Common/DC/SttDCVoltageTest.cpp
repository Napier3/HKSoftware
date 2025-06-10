#include "stdafx.h"
#include"SttDCVoltageTest.h"

CString CSttDCVoltageTest::m_strMacroName = "柔直过压测试";
CString CSttDCVoltageTest::m_strMacroID = STT_MACRO_ID_DCVoltageTest;
CString CSttDCVoltageTest::m_strFilePostFix = "stttst";
CString CSttDCVoltageTest::m_strMacroVer = "1.0";

CSttDCVoltageTest::CSttDCVoltageTest()
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

void CSttDCVoltageTest::Init()
{
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_oDcVoltageParas.init();
    m_oDcVoltageResults.init();
    CSttTestBase::Init();
    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    g_theSystemConfig->m_nHasAnalog = 0;
    g_theSystemConfig->m_nHasWeek = 0;
}

CSttDCVoltageTest::~CSttDCVoltageTest(void)
{
}

void CSttDCVoltageTest::AfterSetParameter()
{
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    //paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    //paraState0->m_fTimeState = m_oDcVoltageParas.m_fPreFaultTime;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_oDcVoltageParas.m_fPreFaultVol;
        paraState0->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState0->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState0->m_uiCUR[i].Harm[1].fAmp = m_oDcVoltageParas.m_fPreFaultCur;
        paraState0->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState0->m_uiCUR[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState0->m_binOut[i].nState = m_oDcVoltageParas.m_binOut[i].nState;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState0->m_binOutEx[i].nState = m_oDcVoltageParas.m_binOutEx[i].nState;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState0->m_binIn[i].nSelect = m_oDcVoltageParas.m_binIn[i].nSelect;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState0->m_binInEx[i].nSelect = m_oDcVoltageParas.m_binInEx[i].nSelect;
    }

    switch(m_oDcVoltageParas.m_nFaultTrigMode)
    {
        case 1:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_MEARSURETRIGGER;
        }
        break;

        case 2:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_BINTRIGGER;
            paraState0->m_fTimeAfterTrigger = m_oDcVoltageParas.m_fPostFaultTime;
        }
        break;

        case 3:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_GPSBTRIGGER;
            paraState0->m_tGps.nHour = m_oDcVoltageParas.m_tGps.nHour;
            paraState0->m_tGps.nMinutes = m_oDcVoltageParas.m_tGps.nMinutes;
            paraState0->m_tGps.nSeconds = m_oDcVoltageParas.m_tGps.nSeconds;
        }
        break;

        default:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
            paraState0->m_fTimeState = m_oDcVoltageParas.m_fPreFaultTime;
        }
    }

    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState1->m_fTimeState = m_oDcVoltageParas.m_fMaxFaultTime + m_oDcVoltageParas.m_fMarginTime;
    paraState1->m_fTimeAfterTrigger = m_oDcVoltageParas.m_fPostFaultTime;
    paraState1->m_nBinLogic = m_oDcVoltageParas.m_nBinLogic;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_oDcVoltageParas.m_fPreFaultVol;
        paraState1->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState1->m_uiVOL[i].Harm[1].fFreq = 0;
    }
    paraState1->m_uiVOL[m_oDcVoltageParas.m_nFaultChannel].Harm[1].fAmp = m_oDcVoltageParas.m_fUSetting*m_oDcVoltageParas.m_fRate;

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState1->m_uiCUR[i].Harm[1].fAmp = m_oDcVoltageParas.m_fPreFaultCur;
        paraState1->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState1->m_uiCUR[i].Harm[1].fFreq = 0;
    }
    paraState1->m_uiCUR[m_oDcVoltageParas.m_nCurrentChannel].Harm[1].fAmp = m_oDcVoltageParas.m_fCurrent;

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binOut[i].nState = m_oDcVoltageParas.m_binOut[i].nState;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState1->m_binOutEx[i].nState = m_oDcVoltageParas.m_binOutEx[i].nState;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binIn[i].nSelect = m_oDcVoltageParas.m_binIn[i].nSelect;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState1->m_binInEx[i].nSelect = m_oDcVoltageParas.m_binInEx[i].nSelect;
    }
}

void CSttDCVoltageTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_DcVoltage(&m_oDcVoltageParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttDCVoltageTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oDcVoltageResults, pXmlSerialize);
}

long CSttDCVoltageTest::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct)
    {
        m_oDcVoltageResults.m_fTripTime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;
    }
    return  0;
}

void CSttDCVoltageTest::StartTest()
{
    if(GetTestStarting())
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttDCOverCurrentTest is  Running,Can't StartTest()");
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
    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttDCOverCurrentTest::StartTest >>>>>>");
}

void CSttDCVoltageTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StatePara(&m_pStateTest->m_oStateParas);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);
#endif
}
