#include "stdafx.h"
#include "SttLowVolTimeTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowVolTimeTest::m_strMacroName = "低压动作时间测试";
CString CSttLowVolTimeTest::m_strMacroID = STT_MACRO_ID_PsuLowVolTime;
CString CSttLowVolTimeTest::m_strFilePostFix = "plvt";
CString CSttLowVolTimeTest::m_strMacroVer = "1.0";

CSttLowVolTimeTest::CSttLowVolTimeTest() : CSttStateTest()
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

void CSttLowVolTimeTest::Init()
{
    CSttStateTest::Init();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    tmt_LowVolParas::init();
    m_oResults.init();
}

CSttLowVolTimeTest::~CSttLowVolTimeTest(void)
{
}

void CSttLowVolTimeTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
}

long CSttLowVolTimeTest::CalReport(UINT nState)
{
    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct > 0)
    {
        float fActValue = 0, fBeginTime = 0.0f;
        m_oResults.m_nAct = 1;

        if(m_fUAct > m_fVend)
        {
            fActValue = m_fUAct;
        }
        else
        {
            fActValue = m_fVend;
        }

        if(m_nUSetMode)
        {
            fBeginTime = (g_theSystemConfig->m_fVNom - fActValue) / m_fDvdt;
        }
        else
        {
            fBeginTime = (g_theSystemConfig->m_fVNom / SQRT3 - fActValue) / m_fDvdt;
        }

       m_oResults.m_fLowUActTime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime + m_pStateTest->m_oStateResults.m_resultState[1].m_nCurStepIndex * 0.001f;
       if(m_nDvdtTiming ==0)
       {
           m_oResults.m_fLowUActTime -= fBeginTime;
       }

        if(m_oResults.m_fLowUActTime < 0)
        {
            m_oResults.m_nAct = 0;
            m_oResults.m_fLowUActTime = 0;
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("当前动作时间小于理论动作时间,请重新设置低压动作值定值."));
        }

// 		if (m_oResults.m_fLowUActTime < 0 )
// 		{
// 			m_oResults.m_fLowUActTime = m_oStateResults.m_resultState[1].m_frTestTime;
// 		}
    }
    else
    {
        m_oResults.m_nAct = 0;
        m_oResults.m_fLowUActTime = 0.0f;
    }

    return 0;
}

void CSttLowVolTimeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PsuLowVolTime(this, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttLowVolTimeTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PsuLowVolTime(&m_oResults, pXmlSerialize);
}

void CSttLowVolTimeTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_LowVol_search_results(this, &m_oResults, pXmlSerialize);
}

void CSttLowVolTimeTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;
    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
    pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}


long CSttLowVolTimeTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttLowVolTimeTest::TranslateToStateParas()
{
    float fStdLN_Vol = g_theSystemConfig->m_fVNom / SQRT3; //计算标准相电压,一般57.735V
    float fGradientTime = 0.0f, fLnDvDt = m_fDvdt, fLnEndVol = m_fVend;
    m_pStateTest->m_oStateParas.m_fTao = 0;
    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    Complex p1;
    Complex	oComplexUI[2][4];
    m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0], fStdLN_Vol, 0.0f); //计算故障前三相电压
    m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1], 1.2 * m_fIAct, -78); //计算故障前三相电流
    m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3], oComplexUI[0], 0);
    Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[0], oComplexUI[0], oComplexUI[1]);
    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
    m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
    SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut, m_binOut);
    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
    m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
    //故障状态
    m_pStateTest->m_oStateParas.m_paraState[1].m_nRampTimeGrad =  1;

    if(m_nUSetMode == 1)
    {
        fLnDvDt = m_fDvdt / SQRT3;
        fLnEndVol = m_fVend / SQRT3;
    }

    m_fCurrSearchDvdt = fLnDvDt;
    fGradientTime = fabs(fStdLN_Vol - fLnEndVol) / fLnDvDt;
    Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1], oComplexUI[0], oComplexUI[1]);

    for(int nIndex = 0; nIndex < 3; nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt / 1000;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fEnd = fLnEndVol;
    }

    Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1], m_binIn, m_nBinLogic);
    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = fGradientTime + m_fHoldTime;
    SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut, m_binOut);

    for(int nBoutIndex = 0; nBoutIndex < MAX_BINARYOUT_COUNT; nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
}

