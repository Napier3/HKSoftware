#include "stdafx.h"
#include "SttCurrentActValueTest_Pnv.h"
#include "../SttSystemConfig.h"
#include "../../../SttTestBase/SttFaultCalculatTool.h"
#include "../SttStateTest.h"

CString CSttCurrentActValuePnvTest::m_strMacroName = "Pnv电流动作值试验";
CString CSttCurrentActValuePnvTest::m_strMacroID = STT_MACRO_ID_PnvCurrentActValue;
CString CSttCurrentActValuePnvTest::m_strFilePostFix = "pnvcav";
CString CSttCurrentActValuePnvTest::m_strMacroVer ="1.0";

CSttCurrentActValuePnvTest::CSttCurrentActValuePnvTest() : CSttGradientTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttCurrentActValuePnvTest::Init()
{ 
	CSttGradientTest::Init();
    m_oCurActValuePnvParas.init();
    m_oCurActValuePnvParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
#ifdef _PSX_QT_LINUX_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	pTmtGradientProcess->m_nDiretionMode = 0;
#endif
}

CSttCurrentActValuePnvTest::~CSttCurrentActValuePnvTest(void)
{

}

void CSttCurrentActValuePnvTest::AfterSetParameter()
{
    m_oCurActValuePnvParas.CopyOwn(&m_oGradientParas,3,3);

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
	InitParaBeforeGradient();//在该函数中进行重新初始化
	CSttDeviceBase::g_pSttDeviceBase->SetChannelSelect(m_oGradientParas);
	CSttDeviceBase::g_pSttDeviceBase->CalStepValue_Gradient(m_oGradientParas);
#endif
}

void CSttCurrentActValuePnvTest::InitParaBeforeGradient()
{
	InitParaBeforeGradient_Chs(&m_oGradientParas,3,3);

    for(int i = 0;i<3;i++)
    {
        m_oCurActValuePnvParas.m_uiVOL[1][i].Harm[1].fAmp = m_oCurActValuePnvParas.m_uiVOL[0][i].Harm[1].fAmp;
        m_oCurActValuePnvParas.m_uiVOL[1][i].Harm[1].fAngle = m_oCurActValuePnvParas.m_uiVOL[0][i].Harm[1].fAngle;
        m_oCurActValuePnvParas.m_uiCUR[1][i].Harm[1].fAmp = m_oCurActValuePnvParas.m_uiCUR[0][i].Harm[1].fAmp;
        m_oCurActValuePnvParas.m_uiCUR[1][i].Harm[1].fAngle = m_oCurActValuePnvParas.m_uiCUR[0][i].Harm[1].fAngle;

    }

#ifdef _PSX_QT_LINUX_
    tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;
    oGradientParas.m_fPrepareTime = m_oGradientParas.m_fPrepareTime;//用于RTDADA第一包数据判断
    oGradientParas.m_fPreFaultTime = m_oGradientParas.m_fPreFaultTime;
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            oGradientParas.m_uiVOL[i][j].Harm[0].fAmp = m_oCurActValuePnvParas.m_uiVOL[i][j].Harm[0].fAmp;
            oGradientParas.m_uiCUR[i][j].Harm[0].fAmp = m_oCurActValuePnvParas.m_uiCUR[i][j].Harm[0].fAmp;

            oGradientParas.m_uiVOL[i][j].Harm[1].fAmp = m_oCurActValuePnvParas.m_uiVOL[i][j].Harm[1].fAmp;
            oGradientParas.m_uiVOL[i][j].Harm[1].fAngle = m_oCurActValuePnvParas.m_uiVOL[i][j].Harm[1].fAngle;
            oGradientParas.m_uiVOL[i][j].Harm[1].fFreq = m_oCurActValuePnvParas.m_uiVOL[i][j].Harm[1].fFreq;

            oGradientParas.m_uiCUR[i][j].Harm[1].fAmp = m_oCurActValuePnvParas.m_uiCUR[i][j].Harm[1].fAmp;
            oGradientParas.m_uiCUR[i][j].Harm[1].fAngle = m_oCurActValuePnvParas.m_uiCUR[i][j].Harm[1].fAngle;
            oGradientParas.m_uiCUR[i][j].Harm[1].fFreq = m_oCurActValuePnvParas.m_uiCUR[i][j].Harm[1].fFreq;
        }
    }
    for(int i = 0;i<3;i++)
    {
        oGradientParas.m_binOut[1][i].fHoldTime = m_oCurActValuePnvParas.m_binOut[1][0].fHoldTime;
    }
#endif
}

void CSttCurrentActValuePnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize((tmt_CurActValuePnvParas*)&m_oCurActValuePnvParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		TranslateToGradientParas();

        AngleTestTransPara();

		AfterSetParameter();
		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttCurrentActValuePnvTest::TranslateToGradientParas()
{
    m_oCurActValuePnvParas.m_nType = GRADIENT_AMP;
    m_oCurActValuePnvParas.m_nTestMode = Gradient_TestMode_ActValue;
    m_oCurActValuePnvParas.m_fG2Current = 0.0f;
    m_oCurActValuePnvParas.m_fG2Volt = 0.0f;
    m_oCurActValuePnvParas.m_fStepTime += m_oCurActValuePnvParas.m_fMarginTime;

	Complex	oComplexUI[2][4],oCompTmp;
	tmt_ImpedanceParas oImpedanceParas;
	oImpedanceParas.init();
    oImpedanceParas.m_fSCCurrent[0] = fabs(m_oCurActValuePnvParas.m_fStart + m_oCurActValuePnvParas.m_fStop)/2;
    oImpedanceParas.m_fIfh = m_oCurActValuePnvParas.m_fG1Current;
    oImpedanceParas.m_fPowerAngle = 0;
	oImpedanceParas.m_nCalMode = 3;//过流计算时,计算模式为3

	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	oComplexUI[0][0] = oCompTmp.polar(fStdLN_Vol,0);
	oComplexUI[0][1] = oCompTmp.polar(fStdLN_Vol,-120);
	oComplexUI[0][2] = oCompTmp.polar(fStdLN_Vol,120);
    oComplexUI[1][0] = oCompTmp.polar(m_oCurActValuePnvParas.m_fG1Current,0);
    oComplexUI[1][1] = oCompTmp.polar(m_oCurActValuePnvParas.m_fG1Current,-120);
    oComplexUI[1][2] = oCompTmp.polar(m_oCurActValuePnvParas.m_fG1Current,120);

	Global_FaultCalculatUI(&oImpedanceParas,0,oComplexUI[0],oComplexUI[1]);
    m_oCurActValuePnvParas.m_uiVOL[2][0].Harm[1].fAmp = oComplexUI[0][0].norm();
    m_oCurActValuePnvParas.m_uiVOL[2][0].Harm[1].fAngle = oComplexUI[0][0].arg();
    m_oCurActValuePnvParas.m_uiVOL[2][1].Harm[1].fAmp = oComplexUI[0][1].norm();
    m_oCurActValuePnvParas.m_uiVOL[2][1].Harm[1].fAngle = oComplexUI[0][1].arg();
    m_oCurActValuePnvParas.m_uiVOL[2][2].Harm[1].fAmp = oComplexUI[0][2].norm();
    m_oCurActValuePnvParas.m_uiVOL[2][2].Harm[1].fAngle = oComplexUI[0][2].arg();

    m_oCurActValuePnvParas.m_uiCUR[2][0].Harm[1].fAmp = oComplexUI[1][0].norm();
    m_oCurActValuePnvParas.m_uiCUR[2][0].Harm[1].fAngle = oComplexUI[1][0].arg();
    m_oCurActValuePnvParas.m_uiCUR[2][1].Harm[1].fAmp = oComplexUI[1][1].norm();
    m_oCurActValuePnvParas.m_uiCUR[2][1].Harm[1].fAngle = oComplexUI[1][1].arg();
    m_oCurActValuePnvParas.m_uiCUR[2][2].Harm[1].fAmp = oComplexUI[1][2].norm();
    m_oCurActValuePnvParas.m_uiCUR[2][2].Harm[1].fAngle = oComplexUI[1][2].arg();

    switch(m_oCurActValuePnvParas.m_nFaultType)
	{
    case IRampCh_Ia:
		{
            m_oCurActValuePnvParas.m_nChannel = I1a;
		}

		break;

    case IRampCh_Ib:
		{
            m_oCurActValuePnvParas.m_nChannel = I1b;
		}

		break;

    case IRampCh_Ic:
		{
            m_oCurActValuePnvParas.m_nChannel = I1c;
		}

		break;

    case IRampCh_Iab:
		{
            m_oCurActValuePnvParas.m_nChannel = I1ab;
		}

		break;

    case IRampCh_Ibc:
		{
            m_oCurActValuePnvParas.m_nChannel = I1bc;
		}

		break;

    case IRampCh_Ica:
		{
            m_oCurActValuePnvParas.m_nChannel = I1ca;
		}

		break;
    case IRampCh_Iabc:
		{
            m_oCurActValuePnvParas.m_nChannel = I1abc;
		}

		break;

	default:
		{
		}

		break;
	}
}

void CSttCurrentActValuePnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_oResultParas.m_fTripValue=oRampRestCom.m_fTripValue;
    m_oResultParas.m_nAct=oRampRestCom.m_nAct;
    m_oResultParas.m_fReturnValue=oRampRestCom.m_fReturnValue;
#endif

    stt_xml_serialize_cur_actvalue_pnv(&m_oResultParas,  pXmlSerialize);
}
