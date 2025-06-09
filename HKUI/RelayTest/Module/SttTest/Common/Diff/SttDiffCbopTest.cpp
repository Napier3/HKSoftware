#include "stdafx.h"
#include "SttDiffCbopTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiffCbopTest::m_strMacroName = "整组差动测试";
CString CSttDiffCbopTest::m_strMacroID = STT_MACRO_ID_DiffCBOp;
CString CSttDiffCbopTest::m_strFilePostFix = "pdfcbopst";
CString CSttDiffCbopTest::m_strMacroVer = "1.0";

CSttDiffCbopTest::CSttDiffCbopTest() : CSttStateTest()
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

void CSttDiffCbopTest::Init()
{
    CSttStateTest::Init();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.m_bSearchNext = FALSE;
    m_pStateTest->m_oStateParas.init(2);
    m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    tmt_DiffCBOpParas::init();
    m_oResults.init();
}

CSttDiffCbopTest::~CSttDiffCbopTest(void)
{
}

void CSttDiffCbopTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
    m_oDiffCalTool.Init();
    int oConnectMode;//测试绕组角差
    switch (m_nWindSide)
    {
    case 0://0-高-低
        oConnectMode = m_nAroundClockNumHL;
        break;
    case 1://1-高-中
        oConnectMode = m_nAroundClockNumHM;
        break;
    case 2://2-中-低
        oConnectMode = m_nAroundClockNumHM - m_nAroundClockNumHL;
        if(oConnectMode <= 0)
        {
            oConnectMode += 12;
        }
        break;
    }
    m_oDiffCalTool.InitSysParas(100,m_fFreq);//20231120 zhoulei 由硬件资源去判断

    m_oDiffCalTool.InitParas6I(m_nInSel, m_fIbase, 0, m_nCoordinate, m_nAngleMode, m_nIbiasCal, m_nWindH, m_nWindM, m_nWindL, m_nWindSide,
                               m_fFactor1, m_fFactor2, oConnectMode, m_nFaultType, m_bCTStarPoint, m_nBalanceTerms);

    if(m_nKcal == 0)
    {
        m_oDiffCalTool.InitParas_AutoCalBalanceFactors(m_fSN, m_fUh, m_fUm, m_fUl, m_fCTh, 1.0f, m_fCTm, 1.0f, m_fCTl, 1.0f);
    }
    else
    {
        m_oDiffCalTool.InitParas_SetBalanceFactors(m_fKph, m_fKpm, m_fKpl);
    }

}

long CSttDiffCbopTest::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct)
    {
        m_oResults.m_fTripTime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;
        if(m_bCBSimulation)
        {
            m_oResults.m_fTripTime += m_fCBTripTime;
        }
        m_oResults.m_nActFlag = 1;
    }
    return 0;
}

void CSttDiffCbopTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(this, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
		m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPrepareTime + m_fPreFaultTime;

        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttDiffCbopTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oResults, pXmlSerialize);
}

long CSttDiffCbopTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttDiffCbopTest::SetStatePreFault_6U6I()
{
    float fAngle[DIFF_CURR_CAL_CHANNEL_MAX] = {0, -120.0, 120.0, 0, -120.0, 120.0};

    float fStdLN_Vol = g_theSystemConfig->m_fVNom / SQRT3; //计算标准相电压,一般57.735V
    for(int nIndex = 0; nIndex < 6; nIndex++)
    {
        if(nIndex < 3)
        {
            m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fAmp = m_fVg1;
            m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAmp = m_fVg1;
        }
        else
        {
            m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fAmp = m_fVg2;
            m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAmp = m_fVg2;
        }
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fAngle = fAngle[nIndex];
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAngle = fAngle[nIndex];
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fFreq = m_fFreq;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAmp = 0;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAngle = fAngle[nIndex];
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
    }

    //增加故障态电压可设置,根据故障相别处理
    if(CSttDiffCurrCalculatTool::IsPhaseA(m_nFaultType) || CSttDiffCurrCalculatTool::IsPhaseAB(m_nFaultType) || CSttDiffCurrCalculatTool::IsPhaseABC(m_nFaultType))
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAmp = fStdLN_Vol;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[3].Harm[1].fAmp = fStdLN_Vol;
    }

    if(CSttDiffCurrCalculatTool::IsPhaseB(m_nFaultType) || CSttDiffCurrCalculatTool::IsPhaseBC(m_nFaultType) || CSttDiffCurrCalculatTool::IsPhaseABC(m_nFaultType))
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAmp = fStdLN_Vol;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[4].Harm[1].fAmp = fStdLN_Vol;
    }

    if(CSttDiffCurrCalculatTool::IsPhaseC(m_nFaultType) || CSttDiffCurrCalculatTool::IsPhaseCA(m_nFaultType) || CSttDiffCurrCalculatTool::IsPhaseABC(m_nFaultType))
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAmp = fStdLN_Vol;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[5].Harm[1].fAmp = fStdLN_Vol;
    }

    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPrepareTime + m_fPreFaultTime;
    m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT; nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[0].m_binOut[nIndex].nState = m_binOut[0][nIndex];
    }

    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
    m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
}

void CSttDiffCbopTest::TranslateToStateParas()
{
    float fI1,fI2,fAmp[6],fAngle[6];
    m_pStateTest->m_oStateParas.m_fTao = 0;
    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    SetStatePreFault_6U6I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
    //////////////////////////////////////////////////////////////////////////
    //故障状态

    m_oDiffCalTool.CurrentCal_CbopDiff(m_fFaultCurrent, m_nFaultLocation,m_nEarthing);
    ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

    for(int nIndex = 0; nIndex < DIFF_CURR_CAL_CHANNEL_MAX; nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAmp = pChCurrents[nIndex].famptitude;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAngle = pChCurrents[nIndex].fphase;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fFreq = m_fFreq;
    }

    m_pStateTest->m_oStateParas.m_paraState[1].m_nBinLogic = m_nBinLogic;
    m_pStateTest->m_oStateParas.m_paraState[1].m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    for(int nIndex = 0; nIndex < MAX_BINARYOUT_COUNT; nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_binIn[nIndex].nSelect = m_binIn[nIndex];
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nIndex].nState = m_binOut[1][nIndex];
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nIndex].fTimeTrig = 0;
    }
    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fFaultTime + m_fFaultTimeMargin;

    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = m_fActionHoldTime;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
}


