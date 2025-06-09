#include "stdafx.h"
#include"SttDCOverCurrentTest.h"
#include"../Impedance/SttImpBaseTest.h"

CString CSttDCOverCurrentTest::m_strMacroName = "柔直过流测试";
CString CSttDCOverCurrentTest::m_strMacroID = STT_MACRO_ID_DCOverCurrentTest;
CString CSttDCOverCurrentTest::m_strFilePostFix = "stttst";
CString CSttDCOverCurrentTest::m_strMacroVer = "1.0";

CSttDCOverCurrentTest::CSttDCOverCurrentTest()
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

void CSttDCOverCurrentTest::Init()
{
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_oDCOverCurrentParas.init();
    m_oDCOverCurrentResults.init();
    CSttTestBase::Init();
    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    g_theSystemConfig->m_nHasAnalog = 0;
    g_theSystemConfig->m_nHasWeek = 0;
}

CSttDCOverCurrentTest::~CSttDCOverCurrentTest(void)
{
}

void CSttDCOverCurrentTest::AfterSetParameter()
{
    tmt_ImpedanceParas *pImpedanceParas = (tmt_ImpedanceParas *)&m_oDCOverCurrentParas;
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    //paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    //paraState0->m_fTimeState = pImpedanceParas->m_fPreFaultTime;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_oDCOverCurrentParas.m_fPreFaultVol * 1000;
        paraState0->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState0->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState0->m_uiCUR[i].Harm[1].fAmp = m_oDCOverCurrentParas.m_fPreFaultCur;
        paraState0->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState0->m_uiCUR[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState0->m_binOut[i].nState = m_oDCOverCurrentParas.m_binOut[0][i].nState;
    }

    paraState0->m_nBinLogic = m_oDCOverCurrentParas.m_nBinSelect;

    switch(m_oDCOverCurrentParas.m_nFaultTrigMode)
    {
        case 1:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_MEARSURETRIGGER;
        }
        break;

        case 2:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_BINTRIGGER;
            paraState0->m_fTimeAfterTrigger =  m_oDCOverCurrentParas.m_fAfterTriggerFaultTime;
        }
        break;

        case 3:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_GPSBTRIGGER;
            paraState0->m_tGps.nHour = m_oDCOverCurrentParas.m_tGps.nHour;
            paraState0->m_tGps.nMinutes = m_oDCOverCurrentParas.m_tGps.nMinutes;
            paraState0->m_tGps.nSeconds = m_oDCOverCurrentParas.m_tGps.nSeconds;
        }
        break;

        default:
        {
            paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
            paraState0->m_fTimeState = pImpedanceParas->m_fPreFaultTime;
            //paraState0->m_fTimeState = m_oDCOverCurrentParas.m_fMaxFaultTime + m_oDCOverCurrentParas.m_fMarginTime;
        }
    }
    
    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState1->m_fTimeState = m_oDCOverCurrentParas.m_fMarginTime + m_oDCOverCurrentParas.m_fTSetting;
    paraState1->m_fTimeAfterTrigger =  m_oDCOverCurrentParas.m_fAfterTriggerFaultTime;
    paraState1->m_nBinLogic = m_oDCOverCurrentParas.m_nBinSelect;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_oDCOverCurrentParas.m_fVoltage * 1000;
        paraState1->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState1->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState1->m_uiCUR[i].Harm[1].fAmp = m_oDCOverCurrentParas.m_fPreFaultCur;
        paraState1->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState1->m_uiCUR[i].Harm[1].fFreq = 0;
    }
    paraState1->m_uiCUR[m_oDCOverCurrentParas.m_nFaultChannel].Harm[1].fAmp = m_oDCOverCurrentParas.m_fSetting[0] * m_oDCOverCurrentParas.m_fRate[0];

    if(m_oDCOverCurrentParas.m_nSettingMethod == 0)
    {
        paraState1->m_uiCUR[m_oDCOverCurrentParas.m_nFaultChannel].Harm[1].fAmp *= m_oDCOverCurrentParas.m_fRatePrimaryCurr;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binOut[i].nState = m_oDCOverCurrentParas.m_binOut[1][i].nState;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState1->m_binOutEx[i].nState = m_oDCOverCurrentParas.m_binOutEx[1][i].nState;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binIn[i].nSelect = m_oDCOverCurrentParas.m_binIn[i].nSelect;
    }

    for(int i = 0; i < MAX_ExBINARY_COUNT; i++)
    {
        paraState1->m_binInEx[i].nSelect = m_oDCOverCurrentParas.m_binInEx[i].nSelect;
    }
}

void CSttDCOverCurrentTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_DCOverCurrent(&m_oDCOverCurrentParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttDCOverCurrentTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oDCOverCurrentResults, pXmlSerialize);
}

long CSttDCOverCurrentTest::CalReport(UINT nState)
{
    GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    for(int i = 0; i < 8; i++)
        {
        m_oDCOverCurrentResults.m_fFirstTripTime[i] = oRampRestCom.m_frTimeBinAct[i][0];
    }

//    long nTripIndex = 0;
//    bool bHasMapReclose = false;

//    for (int nIndex = 0;nIndex<8;nIndex++)
//    {
//        if (m_oDCOverCurrentParas.m_nDInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_RECLOCE)
//        {
//            m_oDCOverCurrentResults.SetRecloseTime(m_pStateTest->m_oStateResults.m_resultState[2].m_frTimeBinAct[nIndex][0]);
//            bHasMapReclose = true;
//        }
//        else
//        {
//            m_oDCOverCurrentResults.SetFault1TripTime(nTripIndex,m_oDCOverCurrentParas.m_nDInputState[nIndex],m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[nIndex][0],bHasMapReclose);
//            nTripIndex++;
//        }
//    }

    m_oDCOverCurrentResults.m_nActA = (m_oDCOverCurrentResults.m_fFirstTripTime[0]-0.0001) > 0 ? 1 : 0;
    m_oDCOverCurrentResults.m_nActB = (m_oDCOverCurrentResults.m_fFirstTripTime[1]-0.0001) > 0 ? 1 : 0;
    m_oDCOverCurrentResults.m_nActC = (m_oDCOverCurrentResults.m_fFirstTripTime[2]-0.0001) > 0 ? 1 : 0;
    //m_oDCOverCurrentResults.m_nActD = (m_oDCOverCurrentResults.m_fRecloseTime - 0.0001) > 0 ? 1 : 0;

    m_oDCOverCurrentResults.m_fTripTime = 0;

    for (int i=0;i<8;i++)
    {
        m_oDCOverCurrentResults.m_fTripTime = GetMaxValue(m_oDCOverCurrentResults.m_fTripTime,m_oDCOverCurrentResults.m_fFirstTripTime[i]);
    }

    m_oDCOverCurrentResults.m_fImp = m_oDCOverCurrentParas.m_fImpedance[0];
    m_oDCOverCurrentResults.m_fImpAngle = m_oDCOverCurrentParas.m_fImpAngle[0];
    return  0;
}

void CSttDCOverCurrentTest::StartTest()
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

void CSttDCOverCurrentTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StatePara(&m_pStateTest->m_oStateParas);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);
#endif
}
