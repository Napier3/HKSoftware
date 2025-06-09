#include "stdafx.h"
#include "SttFailureProtTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttFailureProtTest::m_strMacroName = "失灵保护测试(直流)";
CString CSttFailureProtTest::m_strMacroID = STT_MACRO_ID_DCFailureProtTest;
CString CSttFailureProtTest::m_strFilePostFix = "stttst";
CString CSttFailureProtTest::m_strMacroVer = "1.0";

CSttFailureProtTest::CSttFailureProtTest() : CSttStateTest()
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

void CSttFailureProtTest::Init()
{
    CSttStateTest::Init();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    m_oFailureProtTestParas.init();
    m_oFailureProtTestResults.init();
	g_theSystemConfig->m_nHasAnalog = 0;
	g_theSystemConfig->m_nHasWeek = 0;
}

CSttFailureProtTest::~CSttFailureProtTest(void)
{
}

void CSttFailureProtTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_oFailureProtTestParas.m_fPreFaultVol;
        paraState0->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState0->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState0->m_uiCUR[i].Harm[1].fAmp = m_oFailureProtTestParas.m_fPreFaultCur;
        paraState0->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState0->m_uiCUR[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState0->m_binOut[i].nState = m_oFailureProtTestParas.m_nStateBOut[i];
    }

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        paraState0->m_binIn[i].nSelect = m_oFailureProtTestParas.m_binIn[i].nSelect;
    }

    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    paraState0->m_fTimeState = m_oFailureProtTestParas.m_fPreFaultTime;

    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState1->m_nBinLogic = m_oFailureProtTestParas.m_nBinLogic;

    for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_oFailureProtTestParas.m_fPreFaultVol;
        paraState1->m_uiVOL[i].Harm[1].fAngle = 0;
        paraState1->m_uiVOL[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_CURRENT_COUNT; i++)
    {
        paraState1->m_uiCUR[i].Harm[1].fAmp = m_oFailureProtTestParas.m_fPreFaultCur;
        paraState1->m_uiCUR[i].Harm[1].fAngle = 0;
        paraState1->m_uiCUR[i].Harm[1].fFreq = 0;
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
        paraState1->m_binOut[i].nState = m_oFailureProtTestParas.m_nStateBOut[i];
    }

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        paraState1->m_binIn[i].nSelect = m_oFailureProtTestParas.m_binIn[i].nSelect;
    }

    Global_SetStateBoutPreFault(m_pStateTest->m_oStateParas.m_paraState, m_oFailureProtTestParas.m_nStateBOut,
                                m_oFailureProtTestParas.m_nOutputSwitchMode, m_oFailureProtTestParas.m_nBinLogic, m_oFailureProtTestParas.m_fBoutTimeTrig, m_oFailureProtTestParas.m_fBoutHoldTime);

}

long CSttFailureProtTest::CalReport(UINT nState)
{
    return 0;
}

void CSttFailureProtTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    /*
#ifdef _PSX_QT_LINUX_
    //CSttDeviceBase::g_pSttDeviceBase->SetSyncSecond();
#endif
    //stt_xml_serialize_PsuLowFreqAct(this, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        Gouts_XmlSerialize(pXmlSerialize);
    }*/
}

void CSttFailureProtTest::Stop()
{
    CSttTestBase::Stop();
#ifdef _PSX_QT_LINUX_
    //CSttDeviceBase::g_pSttDeviceBase->SetSyncSecond(g_theSystemConfig->m_bSyncSecond);
#endif
}

void CSttFailureProtTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    //stt_xml_serialize_PsuLowFreqAct(&m_oResults, pXmlSerialize);
}

void CSttFailureProtTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    //stt_xml_serialize_LowFreq_search_results(this, &m_oResults, pXmlSerialize);
}

void CSttFailureProtTest::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;
    CalReport();//zhouhj 20210613在返回测试结束消息时,计算报告结果值
    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
#ifdef _PSX_QT_LINUX_
    //CSttDeviceBase::g_pSttDeviceBase->SetSyncSecond(g_theSystemConfig->m_bSyncSecond);
#endif
}

void CSttFailureProtTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;
    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
}
