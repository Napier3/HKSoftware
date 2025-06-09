#include "stdafx.h"
#include "SttManuDiffCurrThrTest.h"
#include "../../SttSystemConfig.h"
#include "../../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttManuDiffCurrThrTest::m_strMacroName = "差动启动电流测试(手动递变)";
CString CSttManuDiffCurrThrTest::m_strMacroID = STT_MACRO_ID_PsuManuDiffTCurrTest;
CString CSttManuDiffCurrThrTest::m_strFilePostFix = "pdffctst";
CString CSttManuDiffCurrThrTest::m_strMacroVer ="1.0";

CSttManuDiffCurrThrTest::CSttManuDiffCurrThrTest() : CSttManuTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;
}

void CSttManuDiffCurrThrTest::Init()
{
    CSttManuTest::Init();
    m_pManualTest->m_oManuParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统频率
    tmt_DiffCurrParas::init();
    m_oResults.init();
}

CSttManuDiffCurrThrTest::~CSttManuDiffCurrThrTest(void)
{

}

void CSttManuDiffCurrThrTest::AfterSetParameter()
{
    CSttManuTest::AfterSetParameter();
    m_oDiffCalTool.Init();

	m_oDiffCalTool.InitSysParas(100,g_theSystemConfig->m_fFNom);//20231120 zhoulei 由硬件资源去判断

    m_oDiffCalTool.InitParas6I(m_nInSel,m_fIbase,m_nSearchMode,m_bMinAxis,m_nAngleMode,m_nIbiasCal,m_nWindH,m_nWindM,m_nWindL,m_nWindSide,
                               m_fFactor1,m_fFactor2,m_nConnectMode,m_nPhase,m_bCTStarPoint,m_nJXFactor);

    if (m_nKcal == 0)
    {
        m_oDiffCalTool.InitParas_AutoCalBalanceFactors(m_fSN,m_fUh,m_fUm,m_fUl,m_fCTh,1.0f,m_fCTm,1.0f,m_fCTl,1.0f);
    }
    else
    {
        m_oDiffCalTool.InitParas_SetBalanceFactors(m_fKph,m_fKpm,m_fKpl);
    }

    m_fCurrScanVal = m_fIdSetting;
}

long CSttManuDiffCurrThrTest::CalReport(UINT nState)
{
    if (IsAct())
    {
        m_oResults.m_fIdiffActValue = GetActValue();
        m_oResults.m_nActFlag = 1;
    }
    else
    {
        m_oResults.m_fIdiffActValue = 0.0f;
        m_oResults.m_nActFlag = 0;
    }

    return 0;
}

void CSttManuDiffCurrThrTest::StartTest()
{
    CSttTestBase::StartTest();
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_manu(m_pManualTest,TRUE);
#endif

    if(!GetTestStarting())
    {
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ManualTest);
#endif
    }
    CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttManuDiffCurrThrTest::StartTest >>>>>>");
}

void CSttManuDiffCurrThrTest::Stop()
{
#ifdef _PSX_QT_LINUX_
    CSttTestBase::Stop();
#endif
}

void CSttManuDiffCurrThrTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_thr(this,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换

        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttManuDiffCurrThrTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_thr(&m_oResults, pXmlSerialize);
}

long CSttManuDiffCurrThrTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttManuDiffCurrThrTest::SetResultValues_I1IeI2Ie()
{
    ChannelUI_Diff *pDiffChs = m_oDiffCalTool.GetChannelCurrents();
    float fIe = 1.0f;
    m_oDiffCalTool.GetIet(fIe);

    if (CSttDiffCurrCalculatTool::IsPhaseA(m_nPhase)||CSttDiffCurrCalculatTool::IsPhaseAB(m_nPhase))
    {
        m_oResults.m_fI1Ie = pDiffChs[0].famptitude/fIe;
        m_oResults.m_fI1 = pDiffChs[0].famptitude;
        m_oResults.m_fI2Ie = pDiffChs[3].famptitude/fIe;
        m_oResults.m_fI2 = pDiffChs[3].famptitude;
    }
    else if (CSttDiffCurrCalculatTool::IsPhaseB(m_nPhase)||CSttDiffCurrCalculatTool::IsPhaseBC(m_nPhase))
    {
        m_oResults.m_fI1Ie = pDiffChs[1].famptitude/fIe;
        m_oResults.m_fI1 = pDiffChs[1].famptitude;
        m_oResults.m_fI2Ie = pDiffChs[4].famptitude/fIe;
        m_oResults.m_fI2 = pDiffChs[4].famptitude;
    }
    else if (CSttDiffCurrCalculatTool::IsPhaseC(m_nPhase)||CSttDiffCurrCalculatTool::IsPhaseCA(m_nPhase))
    {
        m_oResults.m_fI1Ie = pDiffChs[2].famptitude/fIe;
        m_oResults.m_fI1 = pDiffChs[2].famptitude;
        m_oResults.m_fI2Ie = pDiffChs[5].famptitude/fIe;
        m_oResults.m_fI2 = pDiffChs[5].famptitude;
    }
    else
    {
        m_oResults.m_fI1Ie = pDiffChs[0].famptitude/fIe;
        m_oResults.m_fI1 = pDiffChs[0].famptitude;
        m_oResults.m_fI2Ie = pDiffChs[3].famptitude/fIe;
        m_oResults.m_fI2 = pDiffChs[3].famptitude;
    }
}

void CSttManuDiffCurrThrTest::InitManuDiffParas_6U6I()
{
    float fAngle[DIFF_CURR_CAL_CHANNEL_MAX] = {0, -120.0, 120.0, 0, -120.0, 120.0};

    for (int nIndex=0;nIndex<6;nIndex++)
    {
        if (nIndex<3)
        {
            m_pManualTest->m_oManuParas.m_uiVOL[nIndex].Harm[1].fAmp = m_fVg1;
        }
        else
        {
            m_pManualTest->m_oManuParas.m_uiVOL[nIndex].Harm[1].fAmp = m_fVg2;
        }

        m_pManualTest->m_oManuParas.m_uiVOL[nIndex].Harm[1].fAngle = fAngle[nIndex];
        m_pManualTest->m_oManuParas.m_uiVOL[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;

        m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fAmp = 0;
        m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fAngle = fAngle[nIndex];
        m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
    }

    m_nBinLogic = m_nBinLogic;

    for(int nIndex = 0; nIndex < MAX_BINARYIN_COUNT; nIndex++)
    {
        m_pManualTest->m_oManuParas.m_binIn[nIndex] = m_binIn[nIndex];
    }

    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT; nIndex++)
    {
        m_pManualTest->m_oManuParas.m_binOut[nIndex] = m_binOut[nIndex];
    }
}

void CSttManuDiffCurrThrTest::TranslateToStateParas()
{
    float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V

    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    InitManuDiffParas_6U6I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
    //////////////////////////////////////////////////////////////////////////
    //故障状态
    m_oDiffCalTool.CurrentCal(&m_fIdSetting,m_fIbias);
    SetResultValues_I1IeI2Ie();
    m_oResults.m_fIdiffSettingValue = m_fIdSetting;
    ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

    for (int nIndex = 0;nIndex<DIFF_CURR_CAL_CHANNEL_MAX;nIndex++)
    {
        m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fAmp = pChCurrents[nIndex].famptitude;
        m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fAngle = pChCurrents[nIndex].fphase;
        m_pManualTest->m_oManuParas.m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
    }

    //////////////////////////////////////////////////////////////////////////
}

void CSttManuDiffCurrThrTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_diff_search_results(this,&m_oResults, pXmlSerialize);
}

void CSttManuDiffCurrThrTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if (!CheckBeforeUpdatePara())
    {
        return;
    }

    Para_XmlSerialize(pXmlSerialize);

    CSttTestBase::StartTest();//实验开始时间重新赋值
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Manu_UpdateParameter(m_pManualTest->m_oManuParas.m_bDC);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_manu(m_pManualTest);
#endif

    CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttManuDiffCurrThrTest::UpdatePara Finished");
}

void CSttManuDiffCurrThrTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;

    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

    if (m_nStepIndex == 0)//只有第一个测试点,需要下发开始测试命令,后续测试点不需要
    {
        pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
    }

    pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}
