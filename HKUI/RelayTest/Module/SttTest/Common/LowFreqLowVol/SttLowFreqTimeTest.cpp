#include "stdafx.h"
#include "SttLowFreqTimeTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowFreqTimeTest::m_strMacroName = "低周动作时间测试";
CString CSttLowFreqTimeTest::m_strMacroID = STT_MACRO_ID_PsuLowFreqTime;
CString CSttLowFreqTimeTest::m_strFilePostFix = "plft";
CString CSttLowFreqTimeTest::m_strMacroVer = "1.0";

CSttLowFreqTimeTest::CSttLowFreqTimeTest() : CSttStateTest()
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

void CSttLowFreqTimeTest::Init()
{
    CSttStateTest::Init();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    tmt_LowFreqParas::init();
    m_oResults.init();
}

CSttLowFreqTimeTest::~CSttLowFreqTimeTest(void)
{
}

void CSttLowFreqTimeTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
	m_fDrvDfDt = m_fDfdt;
	m_fDrvStepTime = 0.001;
	double fDrvStep = m_fDrvDfDt / 1000;//1ms对应的步长
	if(fDrvStep < 0.0001)
	{
		BOOL bValid = FALSE;
		for(int i = 2;i <= 100;i++)
		{
			if(fDrvStep*i > 0.0001)
			{
				m_fDrvDfDt = fDrvStep*i*1000;
				m_fDrvStepTime = m_fDrvStepTime*i;
				bValid = TRUE;
				break;
			}
		}

		if(!bValid)
		{
			m_fDrvDfDt = 0.1;
			m_fDrvStepTime = 0.1;
		}
	}
}

long CSttLowFreqTimeTest::CalReport(UINT nState)
{
    float fActValue = 0;

    if(m_pStateTest->m_oStateResults.m_resultState[1].m_nAct > 0)
    {
        m_oResults.m_nAct = 1;

        if(m_fFAct > m_fFend)
        {
            fActValue = m_fFAct;
        }
        else
        {
            fActValue = m_fFend;
        }

        m_oResults.m_fLowFActTime =m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime + m_pStateTest->m_oStateResults.m_resultState[1].m_nCurStepIndex * 0.001f;
        if(m_nDfdtTiming ==0)
        {
            m_oResults.m_fLowFActTime -= (g_theSystemConfig->m_fFNom - fActValue) / m_fDfdt;
        }

        if(m_oResults.m_fLowFActTime < 0)
        {
            m_oResults.m_nAct = 0;
            m_oResults.m_fLowFActTime = 0;
            CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("当前动作时间小于理论动作时间,请重新设置频率动作值定值."));
        }

// 		if (m_oResults.m_fLowFActTime < 0 )
// 		{
// 			m_oResults.m_fLowFActTime = m_oStateResults.m_resultState[1].m_frTestTime;
// 		}
    }
    else
    {
        m_oResults.m_nAct = 0;
        m_oResults.m_fLowFActTime = 0.0f;
    }

    return 0;
}

void CSttLowFreqTimeTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;
    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
    pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}

void CSttLowFreqTimeTest::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
    STT_TIME oTime;
    oTime.dRealTime = dRealTime;
    oTime.dTime = dTime;
    oTime.dBinActTime = -1;

    CalReport();//zhouhj 20210613在返回测试结束消息时,计算报告结果值

    CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
    pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
    SetTestStarting(FALSE);
}

void CSttLowFreqTimeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PsuLowFreqTime(this, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttLowFreqTimeTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PsuLowFreqTime(&m_oResults, pXmlSerialize);
}

void CSttLowFreqTimeTest::SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_LowFreq_search_results(this, &m_oResults, pXmlSerialize);
}

long CSttLowFreqTimeTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttLowFreqTimeTest::TranslateToStateParas()
{
    float fStdLN_Vol = g_theSystemConfig->m_fVNom / SQRT3; //计算标准相电压,一般57.735V
    m_pStateTest->m_oStateParas.m_fTao = 0;
	m_fCurrSearchDfdt = m_fDfdt;
    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    Complex p1;
    Complex	oComplexUI[2][4];
    m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[0], fStdLN_Vol, 0.0f); //计算故障前三相电压
    m_oFaultCalculatTool.CalPreFaultComplex(oComplexUI[1], 1.2 * m_fILow, -78); //计算故障前三相电流
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
	m_pStateTest->m_oStateParas.m_paraState[1].m_nRampTimeGrad =  m_fDrvStepTime * 1000;
	m_pStateTest->m_oStateParas.m_paraState[2].m_nRampTimeGrad =  m_fDrvStepTime * 1000;
    Global_SetStateUIFromCpl(&m_pStateTest->m_oStateParas.m_paraState[1], oComplexUI[0], oComplexUI[1]);

    for(int nIndex = 0; nIndex < 3; nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].nIndex = 1;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fStep = m_fDrvDfDt / 1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fStep = m_fDrvDfDt / 1000;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Ramp[2].fEnd = m_fFend;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[2].fEnd = m_fFend;
    }

    Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1], m_binIn, m_nBinLogic);
	m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = fabs(g_theSystemConfig->m_fFNom - m_fFend) / m_fDfdt + m_fHoldTime;
    SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut, m_binOut);

    for(int nBoutIndex = 0; nBoutIndex < MAX_BINARYOUT_COUNT; nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
}

