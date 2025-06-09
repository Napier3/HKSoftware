#include "stdafx.h"
#include"SttOverLoadTest.h"

CString CSttOverLoadTest::m_strMacroName = "过负荷测试";
CString CSttOverLoadTest::m_strMacroID = STT_MACRO_ID_OverLoadTest;
CString CSttOverLoadTest::m_strFilePostFix = "sttovl";
CString CSttOverLoadTest::m_strMacroVer = "1.0";

CSttOverLoadTest::CSttOverLoadTest()
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

void CSttOverLoadTest::Init()
{
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_oOverLoadParas.init();
    m_oOverLoadTestResults.init();
    CSttTestBase::Init();
    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    g_theSystemConfig->m_nHasAnalog = 0;
    g_theSystemConfig->m_nHasWeek = 0;
}

CSttOverLoadTest::~CSttOverLoadTest(void)
{
}

void CSttOverLoadTest::AfterSetParameter()
{
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    paraState0->m_fTimeState = m_oOverLoadParas.m_fNormaltime;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_oOverLoadParas.m_fPreFaultVol;
        paraState0->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState0->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState0->m_uiCUR[i].Harm[1].fAmp = m_oOverLoadParas.m_fPreFaultCur;
        paraState0->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState0->m_uiCUR[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState0->m_binOut[i].nState = m_oOverLoadParas.m_binOut[0][i].nState;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState0->m_binOutEx[i].nState = m_oOverLoadParas.m_binOutEx[0][i].nState;
    }

    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState1->m_fTimeState = m_oOverLoadParas.m_fFaultSettingTime + m_oOverLoadParas.m_fFaultMarginTime;
    paraState1->m_nBinLogic = m_oOverLoadParas.m_nBinLogic;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_oOverLoadParas.m_fPreFaultVol;
        paraState1->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState1->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState1->m_uiCUR[i].Harm[1].fAmp = m_oOverLoadParas.m_fPreFaultCur;
        paraState1->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState1->m_uiCUR[i].Harm[1].fFreq = 0;
    }
    paraState1->m_uiCUR[m_oOverLoadParas.m_nFaultCurChannel].Harm[1].fAmp = m_oOverLoadParas.m_fFaultCur;

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binOut[i].nState = m_oOverLoadParas.m_binOut[1][i].nState;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState1->m_binOutEx[i].nState = m_oOverLoadParas.m_binOutEx[1][i].nState;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binIn[i].nSelect = m_oOverLoadParas.m_binIn[i].nSelect;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState1->m_binInEx[i].nSelect = m_oOverLoadParas.m_binInEx[i].nSelect;
    }
}

long CSttOverLoadTest::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct)
    {
        m_oOverLoadTestResults.m_nAct = m_pStateTest->m_oStateResults.m_resultState[1].m_nAct;
        m_oOverLoadTestResults.m_fTripTime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;
    }
}

void CSttOverLoadTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oOverLoadParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttOverLoadTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oOverLoadTestResults, pXmlSerialize);
}

void CSttOverLoadTest::StartTest()
{
    if(GetTestStarting())
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttOverCurrentTest is  Running,Can't StartTest()");
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

void CSttOverLoadTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StatePara(&m_pStateTest->m_oStateParas);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);
#endif
}
