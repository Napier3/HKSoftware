#include "stdafx.h"
#include "SttOverCurrentTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttOverCurrentTest::m_strMacroName = "������������";
CString CSttOverCurrentTest::m_strMacroID = STT_MACRO_ID_OverCurrent;
CString CSttOverCurrentTest::m_strFilePostFix = "oovc";
CString CSttOverCurrentTest::m_strMacroVer ="1.0";

CSttOverCurrentTest::CSttOverCurrentTest() : CSttImpBaseTest()
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

void CSttOverCurrentTest::Init()
{ 
	CSttImpBaseTest::Init();
//	m_pStateParas.m_nStateNumbers = 2;
	tmt_OverCurrentParas::init();
	m_oResults.init();
}

CSttOverCurrentTest::~CSttOverCurrentTest(void)
{

}

void CSttOverCurrentTest::AfterSetParameter()
{
	CSttImpBaseTest::AfterSetParameter();

	//Pnv��������,���Ƿ�ģ��PT���ߺ�PT��������Ϊ�ϲ�Ϊ1������,Ϊ0ʱ�̶���ģ��PT����,����Ϊ1ʱģ��A�����;
	//���ù̶���·�迹�ķ�ʽ,δ�õ���·��ѹ

	if(m_nImitPTPhase>0)//����0ʱ�̶�ģ��PT����,��ӦPT��������ڶ�Ӧֵ�����ϼ�1
	{	
		m_bImitatePT = TRUE;
		m_nImitPTPhase--;
	}
	else
	{
		m_bImitatePT = FALSE;
	}

	m_pImpBaseParas->m_bSearchNext = FALSE;
	m_pImpBaseParas->m_pStateParas->m_paraState[0].m_tGps = m_tGps;
	m_fSCCurrent[0] = m_fSetting[0]*m_fRate[0];//ͨ����ֵ��ϵ���������ֵ

	Complex p1;
	p1 = p1.polar(m_fK0Amp,m_fK0Angle);
	p1 = (p1+1)*m_fSCCurrent[0];
	p1 = p1*m_fImpedance[0];
	m_fSCVoltage[0] = (float)p1.norm();

	if (m_nFaultType[0] == 6)
	{
		m_nFaultType[0] = 9;
	}
}

long CSttOverCurrentTest::CalReport(UINT nState)
{
	CalReport_ImpBase(this,&m_oResults);
	return 0;
}

void CSttOverCurrentTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_OverCurrent((tmt_OverCurrentParas*)this,pXmlSerialize);


	//2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttOverCurrentTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oResults, pXmlSerialize);
}

long CSttOverCurrentTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttOverCurrentTest::TranslateToStateParas()
{
	m_fMaxFaultTime = m_fTSetting+m_fMarginTime;
	TranslateToStateParas_ImpBase(this,m_fVolAmp,m_fVolAng);
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
