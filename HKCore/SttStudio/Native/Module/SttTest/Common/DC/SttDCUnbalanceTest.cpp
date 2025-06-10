#include "stdafx.h"
#include"SttDCUnbalanceTest.h"

//2023-11-28-xuzhantao

CString CSttDCUnbalanceTest::m_strMacroName = "不平衡保护";
CString CSttDCUnbalanceTest::m_strMacroID = STT_MACRO_ID_DCUnbalanceTest;
CString CSttDCUnbalanceTest::m_strFilePostFix = "stttst";
CString CSttDCUnbalanceTest::m_strMacroVer = "1.0";

CSttDCUnbalanceTest::CSttDCUnbalanceTest()
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

void CSttDCUnbalanceTest::Init()
{
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_oDcUnbalanceParas.init();
    m_oDcUnbalanceResults.init();
    CSttTestBase::Init();
    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    g_theSystemConfig->m_nHasAnalog = 0;
    g_theSystemConfig->m_nHasWeek = 0;
}

CSttDCUnbalanceTest::~CSttDCUnbalanceTest(void)
{
}

void CSttDCUnbalanceTest::AfterSetParameter()
{
    long oStateBOut[MAX_BINARYOUT_COUNT];
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
        paraState0->m_binOut[i].nState = m_oDcUnbalanceParas.m_binOut[i].nState;
    }

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        paraState0->m_binIn[i].nSelect = m_oDcUnbalanceParas.m_binIn[i].nSelect;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState0->m_binInEx[i].nSelect = m_oDcUnbalanceParas.m_binInEx[i].nSelect;
    }

    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    paraState0->m_fTimeState = m_oDcUnbalanceParas.m_fPreFaultTime;


    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState1->m_fTimeState = m_oDcUnbalanceParas.m_fMarginTime + m_oDcUnbalanceParas.m_fSettingTime;
    //paraState1->m_fTimeAfterTrigger =  m_oDcUnbalanceParas.m_fSettingTime;
    paraState1->m_nBinLogic = m_oDcUnbalanceParas.m_nBinLogic;

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
    paraState1->m_uiCUR[m_oDcUnbalanceParas.m_nCurrent1Select].Harm[1].fAmp = m_oDcUnbalanceParas.m_fSettingValue * m_oDcUnbalanceParas.m_fRate;

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binOut[i].nState = m_oDcUnbalanceParas.m_binOut[i].nState;
        oStateBOut[i] = m_oDcUnbalanceParas.m_binOut[i].nState;
    }

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        paraState1->m_binIn[i].nSelect = m_oDcUnbalanceParas.m_binIn[i].nSelect;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState1->m_binInEx[i].nSelect = m_oDcUnbalanceParas.m_binInEx[i].nSelect;
    }

    Global_SetStateBoutPreFault(m_pStateTest->m_oStateParas.m_paraState, oStateBOut,
                                m_oDcUnbalanceParas.m_nOutputSwitchMode, m_oDcUnbalanceParas.m_nBinLogic, m_oDcUnbalanceParas.m_fBoutTimeTrig, m_oDcUnbalanceParas.m_fBoutHoldTime);
}

long CSttDCUnbalanceTest::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct)
    {
        m_oDcUnbalanceResults.m_fTripTime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;
    }
}

void CSttDCUnbalanceTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_DcUnbalance_ex(&m_oDcUnbalanceParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttDCUnbalanceTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oDcUnbalanceResults, pXmlSerialize);
}

void CSttDCUnbalanceTest::StartTest()
{
    if(GetTestStarting())
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttDCUnbalanceTest is  Running,Can't StartTest()");
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
    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttDCUnbalanceTest::StartTest >>>>>>");
}

void CSttDCUnbalanceTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StatePara(&m_pStateTest->m_oStateParas);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);
#endif
}
