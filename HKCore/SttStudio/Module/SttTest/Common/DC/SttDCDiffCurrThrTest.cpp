#include "stdafx.h"
#include "SttDCDiffCurrThrTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDCDiffCurrThrTest::m_strMacroName = "纵差保护";
CString CSttDCDiffCurrThrTest::m_strMacroID = STT_MACRO_ID_DCDifferCurrTest;
CString CSttDCDiffCurrThrTest::m_strFilePostFix = "pdffctst";
CString CSttDCDiffCurrThrTest::m_strMacroVer = "1.0";

CSttDCDiffCurrThrTest::CSttDCDiffCurrThrTest() : CSttStateTest()
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

void CSttDCDiffCurrThrTest::Init()
{
    CSttStateTest::Init();
	m_pStateTest->m_oStateParas.m_nStateNumbers = 3;//最后一态复制第一态的值
	m_pStateTest->m_oStateParas.m_bSearchNext = TRUE;
	m_pStateTest->m_oStateParas.init(3);
    tmt_DcDifferCurParas::init();
    m_oResults.init();
}

CSttDCDiffCurrThrTest::~CSttDCDiffCurrThrTest(void)
{
}

void CSttDCDiffCurrThrTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
    m_oDiffCalTool.Init();
    float fStdLN_Vol = g_theSystemConfig->m_fVNom / SQRT3; //计算标准相电压,一般57.735V

    m_oDiffCalTool.InitSysParas(100,0);//20231120 zhoulei 由硬件资源去判断

    m_oDiffCalTool.InitParas6I(DCDIFF_INSEL, m_fIStart, m_nSearchMode, DCDIFF_MINAXIS, DCDIFF_ANGLEMODE, m_nIbiasCal, DCDIFF_WINDH, DCDIFF_WINDM, DCDIFF_WINDL, DCDIFF_WINDSIDE,
                               m_fFactor1, m_fFactor2, DCDIFF_CONNECTMODE, DCDIFF_PHASE, DCDIFF_CTSTARPOINT, DCDIFF_JXFACTOR);

    m_oDiffCalTool.InitParas_SetBalanceFactors(m_fK1, 1, m_fK2);

    InitSearch();
}

long CSttDCDiffCurrThrTest::CalReport(UINT nState)
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

void CSttDCDiffCurrThrTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_thr(this, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
		m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fBeforeTime;
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttDCDiffCurrThrTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_thr(&m_oResults, pXmlSerialize);
}

long CSttDCDiffCurrThrTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttDCDiffCurrThrTest::SetResultValues_I1IeI2Ie()
{
    ChannelUI_Diff *pDiffChs = m_oDiffCalTool.GetChannelCurrents();
    float fIe = 1.0f;
    m_oDiffCalTool.GetIet(fIe);

    m_oResults.m_fI1Ie = pDiffChs[0].famptitude / fIe;
    m_oResults.m_fI1 = pDiffChs[0].famptitude;
    m_oResults.m_fI2Ie = pDiffChs[3].famptitude / fIe;
    m_oResults.m_fI2 = pDiffChs[3].famptitude;
}

void CSttDCDiffCurrThrTest::SetStatePreFault_6U6I()
{
    float fAngle[DIFF_CURR_CAL_CHANNEL_MAX] = {0, -120.0, 120.0, 0, -120.0, 120.0};

    for(int nIndex = 0; nIndex < 6; nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAmp = 0;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fFreq = 0;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[nIndex].Harm[1].fAngle = 0;
    }

    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
    m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
    SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut, m_binOut);
    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
    m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = TRUE;
}

void CSttDCDiffCurrThrTest::TranslateToStateParas()
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

    m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[m_nCurChannel1].Harm[1].fAmp = pChCurrents[0].famptitude;
    m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[m_nCurChannel2].Harm[1].fAmp = pChCurrents[3].famptitude;

    Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1], m_binIn, m_nBinLogic);
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fActTime + m_fMarginTime;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = TRUE;
//	m_pStateTest->m_oStateParas.m_paraState[1].m_nTriggerCondition = 2;
    SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut, m_binOut);

    for(int nBoutIndex = 0; nBoutIndex < MAX_BINARYOUT_COUNT; nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

	memcpy(&m_pStateTest->m_oStateParas.m_paraState[2],
			&m_pStateTest->m_oStateParas.m_paraState[0],sizeof(tmt_StatePara));
	m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = 0.01;
    //////////////////////////////////////////////////////////////////////////
}

void CSttDCDiffCurrThrTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
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

void CSttDCDiffCurrThrTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_diff_search_results(this, &m_oResults, pXmlSerialize);
}

void CSttDCDiffCurrThrTest::ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent)
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

// BOOL CSttDCDiffCurrThrTest::ActProcess()
// {
// 	return TRUE;
// }



