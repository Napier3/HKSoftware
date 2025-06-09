#include "stdafx.h"
#include "SttVolActValueTest_Pnv.h"
#include "../SttSystemConfig.h"
#include "../../../SttTestBase/SttFaultCalculatTool.h"
#include "../SttStateTest.h"

CString CSttVolActValuePnvTest::m_strMacroName = "Pnv电压动作值试验";
CString CSttVolActValuePnvTest::m_strMacroID = STT_MACRO_ID_PnvVoltageActValue;
CString CSttVolActValuePnvTest::m_strFilePostFix = "pnvvav";
CString CSttVolActValuePnvTest::m_strMacroVer ="1.0";

CSttVolActValuePnvTest::CSttVolActValuePnvTest() : CSttGradientTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttVolActValuePnvTest::Init()
{ 
	CSttGradientTest::Init();
    m_oVolActValuePnvParas.init();
    m_oVolActValuePnvParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
#ifdef _PSX_QT_LINUX_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	pTmtGradientProcess->m_nDiretionMode = 0;
#endif
}

CSttVolActValuePnvTest::~CSttVolActValuePnvTest(void)
{

}

void CSttVolActValuePnvTest::AfterSetParameter()
{
    m_oVolActValuePnvParas.CopyOwn(&m_oGradientParas,3,3);

#ifdef _PSX_QT_LINUX_
	m_oGradientParas.m_fEDFreq = g_theSystemConfig->m_fFNom;
#endif

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

void CSttVolActValuePnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize((tmt_VolActValuePnvParas*)&m_oVolActValuePnvParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		TranslateToGradientParas();
        AngleTestTransPara();

		AfterSetParameter();
		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttVolActValuePnvTest::InitParaBeforeGradient()
{
	InitParaBeforeGradient_Chs(&m_oGradientParas,3,3);

    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            m_oGradientParas.m_uiCUR[i][j].Harm[1].fAngle = m_oVolActValuePnvParas.m_uiCUR[0][j].Harm[1].fAngle;
        }
        for(int j = 0;j<4;j++)
        {
            m_oGradientParas.m_uiVOL[i][j].Harm[1].fAngle = m_oVolActValuePnvParas.m_uiVOL[0][j].Harm[1].fAngle;
        }
    }
    m_oGradientParas.m_uiCUR[2][0].Harm[1].fAmp = m_oVolActValuePnvParas.m_uiCUR[2][0].Harm[1].fAmp;
    m_oGradientParas.m_uiCUR[2][1].Harm[1].fAmp = m_oVolActValuePnvParas.m_uiCUR[2][1].Harm[1].fAmp;
    m_oGradientParas.m_uiCUR[2][2].Harm[1].fAmp = m_oVolActValuePnvParas.m_uiCUR[2][2].Harm[1].fAmp;

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

    for(int i = 0;i<3;i++)
    {
        oGradientParas.m_binOut[1][i].fHoldTime = m_oVolActValuePnvParas.m_binOut[1][0].fHoldTime;
    }
#endif
}

void CSttVolActValuePnvTest::TranslateToGradientParas()
{
    m_oVolActValuePnvParas.m_nType = GRADIENT_AMP;
    m_oVolActValuePnvParas.m_nTestMode = Gradient_TestMode_ActValue;
    m_oVolActValuePnvParas.m_fG2Current = 0.0f;
    m_oVolActValuePnvParas.m_fG2Volt = 0.0f;
    m_oVolActValuePnvParas.m_fStepTime += m_oVolActValuePnvParas.m_fMarginTime;

	Complex	oComplexUI[2][4],oCompTmp;
	tmt_ImpedanceParas oImpedanceParas;
	oImpedanceParas.init();
    oImpedanceParas.m_fSCVoltage[0] = fabs(m_oVolActValuePnvParas.m_fStart + m_oVolActValuePnvParas.m_fStop)/2;
    oImpedanceParas.m_fIfh = m_oVolActValuePnvParas.m_fG1Current;
    oImpedanceParas.m_fPowerAngle = 0;
	oImpedanceParas.m_nCalMode = 3;////过流计算时,计算模式为3
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	oComplexUI[0][0] = oCompTmp.polar(fStdLN_Vol,0);
	oComplexUI[0][1] = oCompTmp.polar(fStdLN_Vol,-120);
	oComplexUI[0][2] = oCompTmp.polar(fStdLN_Vol,120);
    oComplexUI[1][0] = oCompTmp.polar(m_oVolActValuePnvParas.m_fG1Current,0);
    oComplexUI[1][1] = oCompTmp.polar(m_oVolActValuePnvParas.m_fG1Current,-120);
    oComplexUI[1][2] = oCompTmp.polar(m_oVolActValuePnvParas.m_fG1Current,120);
	Global_FaultCalculatUI(&oImpedanceParas,0,oComplexUI[0],oComplexUI[1]);
    m_oVolActValuePnvParas.m_uiVOL[2][0].Harm[1].fAmp = oComplexUI[0][0].norm();
    m_oVolActValuePnvParas.m_uiVOL[2][0].Harm[1].fAngle = oComplexUI[0][0].arg();
    m_oVolActValuePnvParas.m_uiVOL[2][1].Harm[1].fAmp = oComplexUI[0][1].norm();
    m_oVolActValuePnvParas.m_uiVOL[2][1].Harm[1].fAngle = oComplexUI[0][1].arg();
    m_oVolActValuePnvParas.m_uiVOL[2][2].Harm[1].fAmp = oComplexUI[0][2].norm();
    m_oVolActValuePnvParas.m_uiVOL[2][2].Harm[1].fAngle = oComplexUI[0][2].arg();

    m_oVolActValuePnvParas.m_uiCUR[2][0].Harm[1].fAmp = oComplexUI[1][0].norm();
    m_oVolActValuePnvParas.m_uiCUR[2][0].Harm[1].fAngle = oComplexUI[1][0].arg();
    m_oVolActValuePnvParas.m_uiCUR[2][1].Harm[1].fAmp = oComplexUI[1][1].norm();
    m_oVolActValuePnvParas.m_uiCUR[2][1].Harm[1].fAngle = oComplexUI[1][1].arg();
    m_oVolActValuePnvParas.m_uiCUR[2][2].Harm[1].fAmp = oComplexUI[1][2].norm();
    m_oVolActValuePnvParas.m_uiCUR[2][2].Harm[1].fAngle = oComplexUI[1][2].arg();

    switch(m_oVolActValuePnvParas.m_nFaultType)
	{
    case URampCh_Ua:
		{
            m_oVolActValuePnvParas.m_nChannel = U1a;
		}

		break;

    case URampCh_Ub:
		{
            m_oVolActValuePnvParas.m_nChannel = U1b;
		}

		break;

    case URampCh_Uc:
		{
            m_oVolActValuePnvParas.m_nChannel = U1c;
		}

		break;

    case URampCh_Uab:
		{
            m_oVolActValuePnvParas.m_nChannel = U1ab;
		}

		break;

    case URampCh_Ubc:
		{
            m_oVolActValuePnvParas.m_nChannel = U1bc;
		}

		break;

    case URampCh_Uca:
		{
            m_oVolActValuePnvParas.m_nChannel = U1ca;
		}

		break;
    case URampCh_Uabc:
		{
            m_oVolActValuePnvParas.m_nChannel = U1abc;
		}

		break;

	default:
		{
		}

		break;
	}
}

void CSttVolActValuePnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_oResultParas.m_fTripValue=oRampRestCom.m_fTripValue;
    m_oResultParas.m_nAct=oRampRestCom.m_nAct;
    m_oResultParas.m_fReturnValue=oRampRestCom.m_fReturnValue;
#endif

    stt_xml_serialize_vol_actvalue_pnv(&m_oResultParas,  pXmlSerialize);
}
