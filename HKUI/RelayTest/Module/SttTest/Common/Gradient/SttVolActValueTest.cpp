#include "stdafx.h"
#include "SttVolActValueTest.h"
#include "../SttSystemConfig.h"
#include "../../../SttTestBase/SttFaultCalculatTool.h"
#include "../SttStateTest.h"

CString CSttVolActValueTest::m_strMacroName = "电压动作值试验";
CString CSttVolActValueTest::m_strMacroID = STT_MACRO_ID_VoltageActValue;
CString CSttVolActValueTest::m_strFilePostFix = "vav";
CString CSttVolActValueTest::m_strMacroVer ="1.0";

CSttVolActValueTest::CSttVolActValueTest() : CSttGradientTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttVolActValueTest::Init()
{ 
	CSttGradientTest::Init();
	m_oVolActValueParas.init();
	m_oVolActValueParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
#ifdef _PSX_QT_LINUX_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	pTmtGradientProcess->m_nDiretionMode = 0;
#endif
}

CSttVolActValueTest::~CSttVolActValueTest(void)
{

}

void CSttVolActValueTest::AfterSetParameter()
{
	m_oVolActValueParas.CopyOwn(&m_oGradientParas,3,3);

#ifdef _PSX_QT_LINUX_
//	m_oGradientParas.m_fEDU = g_theSystemConfig->m_fVNom/SQRT3;
	m_oGradientParas.m_fEDFreq = g_theSystemConfig->m_fFNom;
#endif

// 	m_oGradientParas.m_fG1Volt=m_oGradientParas.m_fEDU;
// 	m_oGradientParas.m_fG2Volt=m_oGradientParas.m_fEDU;

	m_oGradientParas.m_fEDU = m_oGradientParas.m_fG1Volt;
	m_oGradientParas.m_fEDI = m_oGradientParas.m_fG1Current;
	m_oGradientParas.m_fG2Volt = 0;
	m_oGradientParas.m_fG2Current = 0;

	m_oGradientParas.m_nChannel2 = Null;

 	m_oResultParas.init();

#ifdef _PSX_QT_LINUX_
	InitParaBeforeGradient();    
	CSttDeviceBase::g_pSttDeviceBase->SetChannelSelect(m_oGradientParas);
	CSttDeviceBase::g_pSttDeviceBase->CalStepValue_Gradient(m_oGradientParas);
#endif
}

void CSttVolActValueTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_VolActValueParas*)&m_oVolActValueParas,pXmlSerialize);

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

void CSttVolActValueTest::InitParaBeforeGradient()
{
	InitParaBeforeGradient_Chs(&m_oGradientParas,3,3);

	m_oGradientParas.m_uiVOL[2][0].Harm[1].fAmp = m_oVolActValueParas.m_uiVOL[2][0].Harm[1].fAmp;
	m_oGradientParas.m_uiVOL[2][0].Harm[1].fAngle = m_oVolActValueParas.m_uiVOL[2][0].Harm[1].fAngle;
	m_oGradientParas.m_uiVOL[2][1].Harm[1].fAmp = m_oVolActValueParas.m_uiVOL[2][1].Harm[1].fAmp;
	m_oGradientParas.m_uiVOL[2][1].Harm[1].fAngle = m_oVolActValueParas.m_uiVOL[2][1].Harm[1].fAngle;
	m_oGradientParas.m_uiVOL[2][2].Harm[1].fAmp = m_oVolActValueParas.m_uiVOL[2][2].Harm[1].fAmp;
	m_oGradientParas.m_uiVOL[2][2].Harm[1].fAngle = m_oVolActValueParas.m_uiVOL[2][2].Harm[1].fAngle;

	m_oGradientParas.m_uiCUR[2][0].Harm[1].fAmp = m_oVolActValueParas.m_uiCUR[2][0].Harm[1].fAmp;
	m_oGradientParas.m_uiCUR[2][0].Harm[1].fAngle = m_oVolActValueParas.m_uiCUR[2][0].Harm[1].fAngle;
	m_oGradientParas.m_uiCUR[2][1].Harm[1].fAmp = m_oVolActValueParas.m_uiCUR[2][1].Harm[1].fAmp;
	m_oGradientParas.m_uiCUR[2][1].Harm[1].fAngle = m_oVolActValueParas.m_uiCUR[2][1].Harm[1].fAngle;
	m_oGradientParas.m_uiCUR[2][2].Harm[1].fAmp = m_oVolActValueParas.m_uiCUR[2][2].Harm[1].fAmp;
	m_oGradientParas.m_uiCUR[2][2].Harm[1].fAngle = m_oVolActValueParas.m_uiCUR[2][2].Harm[1].fAngle;

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

void CSttVolActValueTest::TranslateToGradientParas()
{
	m_oVolActValueParas.m_nType = GRADIENT_AMP;
	m_oVolActValueParas.m_nTestMode = Gradient_TestMode_ActValue;
	m_oVolActValueParas.m_fG2Current = 0.0f;
	m_oVolActValueParas.m_fG2Volt = 0.0f;

	Complex	oComplexUI[2][4],oCompTmp;
	tmt_ImpedanceParas oImpedanceParas;
	oImpedanceParas.init();
	oImpedanceParas.m_fSCVoltage[0] = fabs(m_oVolActValueParas.m_fStart + m_oVolActValueParas.m_fStop)/2;
	oImpedanceParas.m_fSCCurrent[0] = m_oVolActValueParas.m_fFaultCurrent;
	oImpedanceParas.m_fImpAngle[0] = m_oVolActValueParas.m_fImpAngle;
	oImpedanceParas.m_nFaultType[0] = m_oVolActValueParas.m_nFaultType;
	oImpedanceParas.m_fIfh = m_oVolActValueParas.m_fG1Current;
	oImpedanceParas.m_fPowerAngle = m_oVolActValueParas.m_fEDUaIaAngle;
	oImpedanceParas.m_nCalMode = 3;////过流计算时,计算模式为3
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	oComplexUI[0][0] = oCompTmp.polar(fStdLN_Vol,0);
	oComplexUI[0][1] = oCompTmp.polar(fStdLN_Vol,-120);
	oComplexUI[0][2] = oCompTmp.polar(fStdLN_Vol,120);
	oComplexUI[1][0] = oCompTmp.polar(m_oVolActValueParas.m_fG1Current,0-m_oVolActValueParas.m_fEDUaIaAngle);
	oComplexUI[1][1] = oCompTmp.polar(m_oVolActValueParas.m_fG1Current,-120-m_oVolActValueParas.m_fEDUaIaAngle);
	oComplexUI[1][2] = oCompTmp.polar(m_oVolActValueParas.m_fG1Current,120-m_oVolActValueParas.m_fEDUaIaAngle);
	Global_FaultCalculatUI(&oImpedanceParas,0,oComplexUI[0],oComplexUI[1]);
	m_oVolActValueParas.m_uiVOL[2][0].Harm[1].fAmp = oComplexUI[0][0].norm();
	m_oVolActValueParas.m_uiVOL[2][0].Harm[1].fAngle = oComplexUI[0][0].arg();
	m_oVolActValueParas.m_uiVOL[2][1].Harm[1].fAmp = oComplexUI[0][1].norm();
	m_oVolActValueParas.m_uiVOL[2][1].Harm[1].fAngle = oComplexUI[0][1].arg();
	m_oVolActValueParas.m_uiVOL[2][2].Harm[1].fAmp = oComplexUI[0][2].norm();
	m_oVolActValueParas.m_uiVOL[2][2].Harm[1].fAngle = oComplexUI[0][2].arg();

	m_oVolActValueParas.m_uiCUR[2][0].Harm[1].fAmp = oComplexUI[1][0].norm();
	m_oVolActValueParas.m_uiCUR[2][0].Harm[1].fAngle = oComplexUI[1][0].arg();
	m_oVolActValueParas.m_uiCUR[2][1].Harm[1].fAmp = oComplexUI[1][1].norm();
	m_oVolActValueParas.m_uiCUR[2][1].Harm[1].fAngle = oComplexUI[1][1].arg();
	m_oVolActValueParas.m_uiCUR[2][2].Harm[1].fAmp = oComplexUI[1][2].norm();
	m_oVolActValueParas.m_uiCUR[2][2].Harm[1].fAngle = oComplexUI[1][2].arg();

	switch(m_oVolActValueParas.m_nFaultType)
	{
	case IMPEDANCE_FAULT_TYPE_AN:
		{
			m_oVolActValueParas.m_nChannel = U1a;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_BN:
		{
			m_oVolActValueParas.m_nChannel = U1b;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_CN:
		{
			m_oVolActValueParas.m_nChannel = U1c;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_AB:
	case IMPEDANCE_FAULT_TYPE_ABN:
		{
			m_oVolActValueParas.m_nChannel = U1ab;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_BC:
	case IMPEDANCE_FAULT_TYPE_BCN:
		{
			m_oVolActValueParas.m_nChannel = U1bc;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_CA:
	case IMPEDANCE_FAULT_TYPE_CAN:
		{
			m_oVolActValueParas.m_nChannel = U1ca;
		}

		break;
	case IMPEDANCE_FAULT_TYPE_ABC:
		{
			m_oVolActValueParas.m_nChannel = U1abc;
		}

		break;

	default:
		{
		}

		break;
	}
}
