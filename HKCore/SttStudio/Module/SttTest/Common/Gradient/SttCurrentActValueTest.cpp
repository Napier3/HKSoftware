#include "stdafx.h"
#include "SttCurrentActValueTest.h"
#include "../SttSystemConfig.h"
#include "../../../SttTestBase/SttFaultCalculatTool.h"
#include "../SttStateTest.h"

CString CSttCurrentActValueTest::m_strMacroName = "电流动作值试验";
CString CSttCurrentActValueTest::m_strMacroID = STT_MACRO_ID_CurrentActValue;
CString CSttCurrentActValueTest::m_strFilePostFix = "cav";
CString CSttCurrentActValueTest::m_strMacroVer ="1.0";

CSttCurrentActValueTest::CSttCurrentActValueTest() : CSttGradientTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttCurrentActValueTest::Init()
{ 
	CSttGradientTest::Init();
	m_oCurrentActValueParas.init();
	m_oCurrentActValueParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
#ifdef _PSX_QT_LINUX_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	pTmtGradientProcess->m_nDiretionMode = 0;
#endif
}

CSttCurrentActValueTest::~CSttCurrentActValueTest(void)
{

}

void CSttCurrentActValueTest::AfterSetParameter()
{
	m_oCurrentActValueParas.CopyOwn(&m_oGradientParas,3,3);

#ifdef _PSX_QT_LINUX_
	m_oGradientParas.m_fEDU = g_theSystemConfig->m_fVNom/SQRT3;
	m_oGradientParas.m_fEDFreq = g_theSystemConfig->m_fFNom;
#endif

	m_oGradientParas.m_fEDU = m_oGradientParas.m_fG1Volt;
	m_oGradientParas.m_fEDI = m_oGradientParas.m_fG1Current;
	m_oGradientParas.m_fG2Volt = 0;
	m_oGradientParas.m_fG2Current = 0;

	m_oGradientParas.m_nChannel2 = Null;

 	m_oResultParas.init();

#ifdef _PSX_QT_LINUX_
	InitParaBeforeGradient();//在该函数中进行重新初始化
	CSttDeviceBase::g_pSttDeviceBase->SetChannelSelect(m_oGradientParas);
	CSttDeviceBase::g_pSttDeviceBase->CalStepValue_Gradient(m_oGradientParas);
#endif
}

void CSttCurrentActValueTest::InitParaBeforeGradient()
{
	InitParaBeforeGradient_Chs(&m_oGradientParas,3,3);

	m_oGradientParas.m_uiVOL[2][0].Harm[1].fAmp = m_oCurrentActValueParas.m_uiVOL[2][0].Harm[1].fAmp;
	m_oGradientParas.m_uiVOL[2][0].Harm[1].fAngle = m_oCurrentActValueParas.m_uiVOL[2][0].Harm[1].fAngle;
	m_oGradientParas.m_uiVOL[2][1].Harm[1].fAmp = m_oCurrentActValueParas.m_uiVOL[2][1].Harm[1].fAmp;
	m_oGradientParas.m_uiVOL[2][1].Harm[1].fAngle = m_oCurrentActValueParas.m_uiVOL[2][1].Harm[1].fAngle;
	m_oGradientParas.m_uiVOL[2][2].Harm[1].fAmp = m_oCurrentActValueParas.m_uiVOL[2][2].Harm[1].fAmp;
	m_oGradientParas.m_uiVOL[2][2].Harm[1].fAngle = m_oCurrentActValueParas.m_uiVOL[2][2].Harm[1].fAngle;

	m_oGradientParas.m_uiCUR[2][0].Harm[1].fAmp = m_oCurrentActValueParas.m_uiCUR[2][0].Harm[1].fAmp;
	m_oGradientParas.m_uiCUR[2][0].Harm[1].fAngle = m_oCurrentActValueParas.m_uiCUR[2][0].Harm[1].fAngle;
	m_oGradientParas.m_uiCUR[2][1].Harm[1].fAmp = m_oCurrentActValueParas.m_uiCUR[2][1].Harm[1].fAmp;
	m_oGradientParas.m_uiCUR[2][1].Harm[1].fAngle = m_oCurrentActValueParas.m_uiCUR[2][1].Harm[1].fAngle;
	m_oGradientParas.m_uiCUR[2][2].Harm[1].fAmp = m_oCurrentActValueParas.m_uiCUR[2][2].Harm[1].fAmp;
	m_oGradientParas.m_uiCUR[2][2].Harm[1].fAngle = m_oCurrentActValueParas.m_uiCUR[2][2].Harm[1].fAngle;

	if (m_oCurrentActValueParas.m_bImitatePT)
	{
		for (int nStateIndex = 0;nStateIndex<3;nStateIndex++)
		{
			if (m_oCurrentActValueParas.m_nImitPTPhase < STT_PT_IMIT_PHASE_AB)
			{
				m_oGradientParas.m_uiVOL[nStateIndex][m_oCurrentActValueParas.m_nImitPTPhase].Harm[1].fAmp = 0.0f;
			}
			else
			{
				switch (m_oCurrentActValueParas.m_nImitPTPhase)
				{
				case STT_PT_IMIT_PHASE_AB:
					m_oGradientParas.m_uiVOL[nStateIndex][0].Harm[1].fAmp = 0.0f;
					m_oGradientParas.m_uiVOL[nStateIndex][1].Harm[1].fAmp = 0.0f;
					break;
				case STT_PT_IMIT_PHASE_BC:
					m_oGradientParas.m_uiVOL[nStateIndex][1].Harm[1].fAmp = 0.0f;
					m_oGradientParas.m_uiVOL[nStateIndex][2].Harm[1].fAmp = 0.0f;
					break;
				case STT_PT_IMIT_PHASE_CA:
					m_oGradientParas.m_uiVOL[nStateIndex][0].Harm[1].fAmp = 0.0f;
					m_oGradientParas.m_uiVOL[nStateIndex][2].Harm[1].fAmp = 0.0f;
					break;
				case STT_PT_IMIT_PHASE_ABC:
					m_oGradientParas.m_uiVOL[nStateIndex][0].Harm[1].fAmp = 0.0f;
					m_oGradientParas.m_uiVOL[nStateIndex][1].Harm[1].fAmp = 0.0f;
					m_oGradientParas.m_uiVOL[nStateIndex][2].Harm[1].fAmp = 0.0f;
					break;
				default:
					break;
				}
			}
		}
	}

#ifdef _PSX_QT_LINUX_
    tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;
    oGradientParas.m_fPrepareTime = m_oGradientParas.m_fPrepareTime;//用于RTDADA第一包数据判断
    oGradientParas.m_fPreFaultTime = m_oGradientParas.m_fPreFaultTime;
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            oGradientParas.m_uiVOL[i][j].Harm[0].fAmp = m_oGradientParas.m_uiVOL[i][j].Harm[0].fAmp;
            oGradientParas.m_uiCUR[i][j].Harm[0].fAmp = m_oGradientParas.m_uiCUR[i][j].Harm[0].fAmp;

            oGradientParas.m_uiVOL[i][j].Harm[1].fAmp = m_oGradientParas.m_uiVOL[i][j].Harm[1].fAmp;
            oGradientParas.m_uiVOL[i][j].Harm[1].fAngle = m_oGradientParas.m_uiVOL[i][j].Harm[1].fAngle;
            oGradientParas.m_uiVOL[i][j].Harm[1].fFreq = m_oGradientParas.m_uiVOL[i][j].Harm[1].fFreq;

            oGradientParas.m_uiCUR[i][j].Harm[1].fAmp = m_oGradientParas.m_uiCUR[i][j].Harm[1].fAmp;
            oGradientParas.m_uiCUR[i][j].Harm[1].fAngle = m_oGradientParas.m_uiCUR[i][j].Harm[1].fAngle;
            oGradientParas.m_uiCUR[i][j].Harm[1].fFreq = m_oGradientParas.m_uiCUR[i][j].Harm[1].fFreq;
        }
    }
#endif
}

void CSttCurrentActValueTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_CurrentActValueParas*)&m_oCurrentActValueParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		TranslateToGradientParas();

		if(m_oGradientParas.m_nPhaseGradDir == 0)
			AngleTestTransPara();
		else
			AngleTestTransPara(FALSE);

		AfterSetParameter();
		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttCurrentActValueTest::TranslateToGradientParas()
{
	m_oCurrentActValueParas.m_nType = GRADIENT_AMP;
	m_oCurrentActValueParas.m_nTestMode = Gradient_TestMode_ActValue;
	m_oCurrentActValueParas.m_fG2Current = 0.0f;
	m_oCurrentActValueParas.m_fG2Volt = 0.0f;
	m_oCurrentActValueParas.m_fStepTime = m_oCurrentActValueParas.m_fSettingActTime + m_oCurrentActValueParas.m_fMarginTime;

	Complex	oComplexUI[2][4],oCompTmp;
	tmt_ImpedanceParas oImpedanceParas;
	oImpedanceParas.init();
	oImpedanceParas.m_fSCCurrent[0] = fabs(m_oCurrentActValueParas.m_fStart + m_oCurrentActValueParas.m_fStop)/2;
	oImpedanceParas.m_fSCVoltage[0] = m_oCurrentActValueParas.m_fFaultVol;
	oImpedanceParas.m_fImpAngle[0] = m_oCurrentActValueParas.m_fImpAngle;
	oImpedanceParas.m_nFaultType[0] = m_oCurrentActValueParas.m_nFaultType;
	oImpedanceParas.m_nFaultDir[0] = m_oCurrentActValueParas.m_nFaultDir;
	oImpedanceParas.m_fIfh = m_oCurrentActValueParas.m_fG1Current;
	oImpedanceParas.m_fPowerAngle = m_oCurrentActValueParas.m_fEDUaIaAngle;
	oImpedanceParas.m_nCalMode = 3;//过流计算时,计算模式为3

	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	oComplexUI[0][0] = oCompTmp.polar(fStdLN_Vol,0);
	oComplexUI[0][1] = oCompTmp.polar(fStdLN_Vol,-120);
	oComplexUI[0][2] = oCompTmp.polar(fStdLN_Vol,120);
	oComplexUI[1][0] = oCompTmp.polar(m_oCurrentActValueParas.m_fG1Current,0-m_oCurrentActValueParas.m_fEDUaIaAngle);
	oComplexUI[1][1] = oCompTmp.polar(m_oCurrentActValueParas.m_fG1Current,-120-m_oCurrentActValueParas.m_fEDUaIaAngle);
	oComplexUI[1][2] = oCompTmp.polar(m_oCurrentActValueParas.m_fG1Current,120-m_oCurrentActValueParas.m_fEDUaIaAngle);

	Global_FaultCalculatUI(&oImpedanceParas,0,oComplexUI[0],oComplexUI[1]);
	m_oCurrentActValueParas.m_uiVOL[2][0].Harm[1].fAmp = oComplexUI[0][0].norm();
	m_oCurrentActValueParas.m_uiVOL[2][0].Harm[1].fAngle = oComplexUI[0][0].arg();
	m_oCurrentActValueParas.m_uiVOL[2][1].Harm[1].fAmp = oComplexUI[0][1].norm();
	m_oCurrentActValueParas.m_uiVOL[2][1].Harm[1].fAngle = oComplexUI[0][1].arg();
	m_oCurrentActValueParas.m_uiVOL[2][2].Harm[1].fAmp = oComplexUI[0][2].norm();
	m_oCurrentActValueParas.m_uiVOL[2][2].Harm[1].fAngle = oComplexUI[0][2].arg();

	m_oCurrentActValueParas.m_uiCUR[2][0].Harm[1].fAmp = oComplexUI[1][0].norm();
	m_oCurrentActValueParas.m_uiCUR[2][0].Harm[1].fAngle = oComplexUI[1][0].arg();
	m_oCurrentActValueParas.m_uiCUR[2][1].Harm[1].fAmp = oComplexUI[1][1].norm();
	m_oCurrentActValueParas.m_uiCUR[2][1].Harm[1].fAngle = oComplexUI[1][1].arg();
	m_oCurrentActValueParas.m_uiCUR[2][2].Harm[1].fAmp = oComplexUI[1][2].norm();
	m_oCurrentActValueParas.m_uiCUR[2][2].Harm[1].fAngle = oComplexUI[1][2].arg();

	switch(m_oCurrentActValueParas.m_nFaultType)
	{
	case IMPEDANCE_FAULT_TYPE_AN:
		{
			m_oCurrentActValueParas.m_nChannel = I1a;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_BN:
		{
			m_oCurrentActValueParas.m_nChannel = I1b;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_CN:
		{
			m_oCurrentActValueParas.m_nChannel = I1c;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_AB:
	case IMPEDANCE_FAULT_TYPE_ABN:
		{
			m_oCurrentActValueParas.m_nChannel = I1ab;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_BC:
	case IMPEDANCE_FAULT_TYPE_BCN:
		{
			m_oCurrentActValueParas.m_nChannel = I1bc;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_CA:
	case IMPEDANCE_FAULT_TYPE_CAN:
		{
			m_oCurrentActValueParas.m_nChannel = I1ca;
		}

		break;
	case IMPEDANCE_FAULT_TYPE_ABC:
		{
			m_oCurrentActValueParas.m_nChannel = I1abc;
		}

		break;

	default:
		{
		}

		break;
	}
}
