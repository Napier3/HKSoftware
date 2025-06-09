#include "stdafx.h"
#include "SttStateOverCurrentTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttStateOverCurrentTest::m_strMacroName = "过流保护试验(单机)";
CString CSttStateOverCurrentTest::m_strMacroID = STT_MACRO_ID_StateOverCurrent;
CString CSttStateOverCurrentTest::m_strFilePostFix = "stoc";
CString CSttStateOverCurrentTest::m_strMacroVer ="1.0";

CSttStateOverCurrentTest::CSttStateOverCurrentTest() : CSttOverCurrentTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttStateOverCurrentTest::Init()
{ 
	CSttOverCurrentTest::Init();
    m_fUNom = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
}

CSttStateOverCurrentTest::~CSttStateOverCurrentTest(void)
{

}

void CSttStateOverCurrentTest::AfterSetParameter()
{
	CSttImpBaseTest::AfterSetParameter();
	m_pImpBaseParas->m_bSearchNext = FALSE;
	m_pImpBaseParas->m_pStateParas->m_paraState[0].m_tGps = m_tGps;
	m_fSCCurrent[0] = m_fSetting[0]*m_fRate[0];//通过定值和系数计算过流值

	if (m_nFaultType[0] == 6)
	{
		m_nFaultType[0] = 9;
	}

	m_nCalMode = 3;//固定电压、电流值时,计算模式为3
}

void CSttStateOverCurrentTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_StateOverCurrent((tmt_OverCurrentParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttStateOverCurrentTest::TranslateToStateParas()
{
	m_fMaxFaultTime = m_fTSetting+m_fMarginTime;
    TranslateToStateParas_ImpBase(this, m_fUNom);
	m_oResults.m_fFaultVol = m_fSCVoltage[0];
	m_oResults.m_fFaultCurrent = m_fSCCurrent[0];
	m_oResults.m_fOverCurrent = m_fSCCurrent[0];

	if (m_bImitatePT)
	{
		for (int nStateIndex = 0;nStateIndex<8;nStateIndex++)
		{
			tmt_StatePara *paraState = &m_pImpBaseParas->m_pStateParas->m_paraState[nStateIndex];
			if (m_nImitPTPhase < STT_PT_IMIT_PHASE_AB)
			{
				paraState->m_uiVOL[m_nImitPTPhase].Harm[1].fAmp = 0.0f;
			}
			else
			{
				switch (m_nImitPTPhase)
				{
				case STT_PT_IMIT_PHASE_AB:
					paraState->m_uiVOL[0].Harm[1].fAmp = 0.0f;
					paraState->m_uiVOL[1].Harm[1].fAmp = 0.0f;
					break;
				case STT_PT_IMIT_PHASE_BC:
					paraState->m_uiVOL[1].Harm[1].fAmp = 0.0f;
					paraState->m_uiVOL[2].Harm[1].fAmp = 0.0f;
					break;
				case STT_PT_IMIT_PHASE_CA:
					paraState->m_uiVOL[0].Harm[1].fAmp = 0.0f;
					paraState->m_uiVOL[2].Harm[1].fAmp = 0.0f;
					break;
				case STT_PT_IMIT_PHASE_ABC:
					paraState->m_uiVOL[0].Harm[1].fAmp = 0.0f;
					paraState->m_uiVOL[1].Harm[1].fAmp = 0.0f;
					paraState->m_uiVOL[2].Harm[1].fAmp = 0.0f;
					break;
				default:
					break;
				}
			}
		}
	}
}
