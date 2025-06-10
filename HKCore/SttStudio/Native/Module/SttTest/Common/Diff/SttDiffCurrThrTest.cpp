#include "stdafx.h"
#include "SttDiffCurrThrTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiffCurrThrTest::m_strMacroName = "差动启动电流测试";
CString CSttDiffCurrThrTest::m_strMacroID = STT_MACRO_ID_PsuDiffTCurrTest;
CString CSttDiffCurrThrTest::m_strFilePostFix = "pdffctst";
CString CSttDiffCurrThrTest::m_strMacroVer = "1.0";

CSttDiffCurrThrTest::CSttDiffCurrThrTest() : CSttStateTest()
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

void CSttDiffCurrThrTest::Init()
{
    CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 3;//最后一态复制第一态的值
	m_pStateTest->m_oStateParas.m_bSearchNext = TRUE;
	m_pStateTest->m_oStateParas.init(3);
    m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    tmt_DiffCurrParas::init();
    m_oResults.init();
    float fStdLN_Vol = g_theSystemConfig->m_fVNom / SQRT3; //计算标准相电压,一般57.735V
    m_fVg1 = fStdLN_Vol;
    m_fVg2 = fStdLN_Vol;
    m_fVg1_fault = fStdLN_Vol;
    m_fVg2_fault = fStdLN_Vol;
}

CSttDiffCurrThrTest::~CSttDiffCurrThrTest(void)
{
}

void CSttDiffCurrThrTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
    m_oDiffCalTool.Init();
    float fStdLN_Vol = g_theSystemConfig->m_fVNom / SQRT3; //计算标准相电压,一般57.735V

    if(m_fVg1 < -0.001f)
    {
        m_fVg1 = fStdLN_Vol;
    }

    if(m_fVg2 < -0.001f)
    {
        m_fVg2 = fStdLN_Vol;
    }

    if(m_fVg1_fault < -0.001f)
    {
        m_fVg1_fault = fStdLN_Vol;
    }

    if(m_fVg2_fault < -0.001f)
    {
        m_fVg2_fault = fStdLN_Vol;
    }

	m_oDiffCalTool.InitSysParas(100,g_theSystemConfig->m_fFNom);//20231120 zhoulei 由硬件资源去判断

    m_oDiffCalTool.InitParas6I(m_nInSel, m_fIbase, m_nSearchMode, m_bMinAxis, m_nAngleMode, m_nIbiasCal, m_nWindH, m_nWindM, m_nWindL, m_nWindSide,
                               m_fFactor1, m_fFactor2, m_nConnectMode, m_nPhase, m_bCTStarPoint, m_nJXFactor);

    if(m_nKcal == 0)
    {
        m_oDiffCalTool.InitParas_AutoCalBalanceFactors(m_fSN, m_fUh, m_fUm, m_fUl, m_fCTh, 1.0f, m_fCTm, 1.0f, m_fCTl, 1.0f);
    }
    else
    {
        m_oDiffCalTool.InitParas_SetBalanceFactors(m_fKph, m_fKpm, m_fKpl);
    }

    InitSearch();
}

long CSttDiffCurrThrTest::CalReport(UINT nState)
{
    if(IsAct())
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

void CSttDiffCurrThrTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_thr(this, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
		m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreTime;
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttDiffCurrThrTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_thr(&m_oResults, pXmlSerialize);
}

long CSttDiffCurrThrTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttDiffCurrThrTest::SetResultValues_I1IeI2Ie()
{
    ChannelUI_Diff *pDiffChs = m_oDiffCalTool.GetChannelCurrents();
    float fIe = 1.0f;
    m_oDiffCalTool.GetIet(fIe);

    if(CSttDiffCurrCalculatTool::IsPhaseA(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseAB(m_nPhase))
    {
        m_oResults.m_fI1Ie = pDiffChs[0].famptitude / fIe;
        m_oResults.m_fI1 = pDiffChs[0].famptitude;
        m_oResults.m_fI2Ie = pDiffChs[3].famptitude / fIe;
        m_oResults.m_fI2 = pDiffChs[3].famptitude;
    }
    else if(CSttDiffCurrCalculatTool::IsPhaseB(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseBC(m_nPhase))
    {
        m_oResults.m_fI1Ie = pDiffChs[1].famptitude / fIe;
        m_oResults.m_fI1 = pDiffChs[1].famptitude;
        m_oResults.m_fI2Ie = pDiffChs[4].famptitude / fIe;
        m_oResults.m_fI2 = pDiffChs[4].famptitude;
    }
    else if(CSttDiffCurrCalculatTool::IsPhaseC(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseCA(m_nPhase))
    {
        m_oResults.m_fI1Ie = pDiffChs[2].famptitude / fIe;
        m_oResults.m_fI1 = pDiffChs[2].famptitude;
        m_oResults.m_fI2Ie = pDiffChs[5].famptitude / fIe;
        m_oResults.m_fI2 = pDiffChs[5].famptitude;
    }
    else
    {
        m_oResults.m_fI1Ie = pDiffChs[0].famptitude / fIe;
        m_oResults.m_fI1 = pDiffChs[0].famptitude;
        m_oResults.m_fI2Ie = pDiffChs[3].famptitude / fIe;
        m_oResults.m_fI2 = pDiffChs[3].famptitude;
    }
}

void CSttDiffCurrThrTest::SetStatePreFault_6U6I()
{
    float fAngle[DIFF_CURR_CAL_CHANNEL_MAX] = {0, -120.0, 120.0, 0, -120.0, 120.0};

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
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAmp = 0;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAngle = fAngle[nIndex];
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
    }

    //增加故障态电压可设置,根据故障相别处理
    if(CSttDiffCurrCalculatTool::IsPhaseA(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseAB(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseABC(m_nPhase))
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[0].Harm[1].fAmp = m_fVg1_fault;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[3].Harm[1].fAmp = m_fVg2_fault;
    }

    if(CSttDiffCurrCalculatTool::IsPhaseB(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseBC(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseABC(m_nPhase))
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[1].Harm[1].fAmp = m_fVg1_fault;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[4].Harm[1].fAmp = m_fVg2_fault;
    }

    if(CSttDiffCurrCalculatTool::IsPhaseC(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseCA(m_nPhase) || CSttDiffCurrCalculatTool::IsPhaseABC(m_nPhase))
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[2].Harm[1].fAmp = m_fVg1_fault;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[5].Harm[1].fAmp = m_fVg2_fault;
    }

	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
    m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
    SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut, m_binOut);
	if(g_theSystemConfig->m_nBinBoutMode)
	{
		SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOutEx, m_binOut);
	}
    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
    m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
}

void CSttDiffCurrThrTest::TranslateToStateParas()
{
    float fStdLN_Vol = g_theSystemConfig->m_fVNom / SQRT3; //计算标准相电压,一般57.735V
    m_pStateTest->m_oStateParas.m_fTao = 0;
    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    SetStatePreFault_6U6I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
    //////////////////////////////////////////////////////////////////////////
    //故障状态
    m_oDiffCalTool.CurrentCal(&m_fCurrScanVal, m_fIbias);
    SetResultValues_I1IeI2Ie();
    m_oResults.m_fIdiffSettingValue = m_fCurrScanVal;
    ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

    for(int nIndex = 0; nIndex < DIFF_CURR_CAL_CHANNEL_MAX; nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAmp = pChCurrents[nIndex].famptitude;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAngle = pChCurrents[nIndex].fphase;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;
    }

    Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1], m_binIn, m_nBinLogic);
    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fFaultTime;
//	m_pStateTest->m_oStateParas.m_paraState[1].m_nTriggerCondition = 2;
    SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut, m_binOut);
	if(g_theSystemConfig->m_nBinBoutMode)
	{
		SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOutEx, m_binOut);
	}

    for(int nBoutIndex = 0; nBoutIndex < MAX_BINARYOUT_COUNT; nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;

		if(g_theSystemConfig->m_nBinBoutMode)
		{
			m_pStateTest->m_oStateParas.m_paraState[1].m_binOutEx[nBoutIndex].fTimeTrig = 0;
		}
    }

    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

	memcpy(&m_pStateTest->m_oStateParas.m_paraState[2],
			&m_pStateTest->m_oStateParas.m_paraState[0],sizeof(tmt_StatePara));
	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = 0.01;
    //////////////////////////////////////////////////////////////////////////
}

void CSttDiffCurrThrTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;
    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();

    if(m_nStepIndex == 0) //只有第一个测试点,需要下发开始测试命令,后续测试点不需要
    {
        pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
    }

    pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}

void CSttDiffCurrThrTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_diff_search_results(this, &m_oResults, pXmlSerialize);
}

void CSttDiffCurrThrTest::ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent)
{
// 	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("状态2动作结果(%d),开入A变位次数(%d),动作时间(%f)"),m_pStateTest->m_oStateResults.m_resultState[1].m_nAct,
// 		m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[0],m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[0]);
    if(dTime > -0.1f)
    {
        if(!IsSearchFinished(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct))
        {
            CSttStateTest::AfterSetParameter();
            SearchNext();
            TranslateToStateParas();
#ifdef _PSX_QT_LINUX_
			CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);//后续开始测试操作
			int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
			
			g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
			ioctl(nFd,0x14B,0);
			g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
            return;
        }
    }

    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;
    CalReport();

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
#endif
	SetTestStarting(FALSE);

    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
}

// BOOL CSttDiffCurrThrTest::ActProcess()
// {
// 	return TRUE;
// }



