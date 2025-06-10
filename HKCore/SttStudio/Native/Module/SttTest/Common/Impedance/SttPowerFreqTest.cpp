#include "stdafx.h"
#include "SttPowerFreqTest.h"
#include "../SttSystemConfig.h"
#include "../SttStateTest.h"

CString CSttPowerFreqTest::m_strMacroName = "��Ƶ�仯���������";
CString CSttPowerFreqTest::m_strMacroID = STT_MACRO_ID_PsuPowerFreqDist;
CString CSttPowerFreqTest::m_strFilePostFix = "ppfd";
CString CSttPowerFreqTest::m_strMacroVer ="1.0";

CSttPowerFreqTest::CSttPowerFreqTest() : CSttImpBaseTest()
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

void CSttPowerFreqTest::Init()
{ 
	CSttImpBaseTest::Init();
	tmt_PowerFreqParas::init();
}

CSttPowerFreqTest::~CSttPowerFreqTest(void)
{

}

void CSttPowerFreqTest::AfterSetParameter()
{
	CSttImpBaseTest::AfterSetParameter();
	m_pImpBaseParas->m_bSearchNext = FALSE;
	m_pImpBaseParas->m_pStateParas->m_paraState[0].m_tGps = m_tGps;
	m_oPowerFreqResults.init();//zhouhj 20210804  �����ò��������,�������迹�߽��ģ��,��Ҫ��ͬһ���������ε��ÿ�ʼ����ʱ,��Ҫ�Խ�����г�ʼ��
	m_oPowerFreqResults.m_fImp = m_fImpedance[0] = m_fSetting[0]/**m_fRate[0]*/;
	m_oPowerFreqResults.m_fImpAngle = m_fImpAngle[0];
}

long CSttPowerFreqTest::CalReport(UINT nState)
{
	CalReport_ImpBase(this,&m_oPowerFreqResults);
	return 0;
}

void CSttPowerFreqTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_PowerFreqParas*)this,pXmlSerialize);


	//2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//������������й���ת��

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttPowerFreqTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPowerFreqResults, pXmlSerialize);
}

long CSttPowerFreqTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttPowerFreqTest::TranslateToStateParas()
{
	m_fMaxFaultTime = m_fTSetting+m_fMarginTime;

	if (m_nFaultDir[0] == 0)
	{
		m_nCalMode = 5;
	} 
	else
	{
		m_nCalMode = 4;
	}

	TranslateToStateParas_ImpBase(this);

	Complex	oComplexUI[2][4],Comp1;
	static int   nPhaseRef[11] = {1,2,0,2,0,1,2,0,1,0,0};
	static float nAngle[11]    = {0,-120,120,30,-90,150,30,-90,150,0,120};
	double fVOutmax = 300.0f,fVFactor = 1.0f, fIOutmax   = 32.0f,fIFactor  = 1.0f,fVt = 50.0,fValueFactor = 1.0f;
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//�����׼���ѹ,һ��57.735V
	double  fK0AmpCal;       //!��������ֵ
	double  fK0AngleCal;     //!�������Ƕ�

	Comp1 = m_oFaultCalculatTool.GroundFactor(m_nK0CalMode,	m_fK0Amp, m_fK0Angle, m_fImpAngle[0]);
	fK0AmpCal   = (float)Comp1.norm();
	fK0AngleCal = (float)Comp1.arg();

	BOOL bHasCalFinished = FALSE;
	float fTmpVolValue = 0.0f;
	long nCurrCount = 0;

	while((!bHasCalFinished) && (nCurrCount<5))
	{
		bHasCalFinished = m_oFaultCalculatTool.Calculat(m_fCalCoef,\
			m_nFaultDir[0],\
			m_nCTPoint,\
			m_nCalMode,\
			m_nFaultType[0],\
			nPhaseRef[m_nFaultType[0]],
			nAngle[nPhaseRef[m_nFaultType[0]]],
			fVOutmax/fVFactor,\
			fStdLN_Vol/fVFactor,\
			fIOutmax/fIFactor,\
			&m_fSCCurrent[0],\
			&fVt,\
			Comp1.polar(0, 0),\
			Comp1.polar(m_fImpedance[0]/fVFactor/fValueFactor*fIFactor, m_fImpAngle[0]),\
			Comp1.polar(fK0AmpCal, fK0AngleCal),\
			Comp1.polar(m_fImpedance[0]/fVFactor/fValueFactor*fIFactor, m_fImpAngle[0]),\
			Comp1.polar(m_fK0Amp,m_fK0Angle),\
			&oComplexUI[0][0],&oComplexUI[0][1],&oComplexUI[0][2],&oComplexUI[1][0],&oComplexUI[1][1],&oComplexUI[1][2]);
		nCurrCount++;

		if (!bHasCalFinished)
		{
			m_fSCCurrent[0] *=1.1;
		}
	}

	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(m_nVzDefine, oComplexUI[0],m_nVzPhDefine,m_fUxInput_Ang);
	Global_SetStateUIFromCpl(&m_pImpBaseParas->m_pStateParas->m_paraState[1],oComplexUI[0],oComplexUI[1]);

	m_oPowerFreqResults.m_fFaultVol = m_fSCVoltage[0];
	m_oPowerFreqResults.m_fFaultCurrent = m_fSCCurrent[0];
}
