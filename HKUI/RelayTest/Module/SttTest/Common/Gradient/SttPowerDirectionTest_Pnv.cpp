#include "stdafx.h"
#include "SttPowerDirectionTest_Pnv.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

CString CSttPowerDirectionPnvTest::m_strMacroName = "动作边界测试";
CString CSttPowerDirectionPnvTest::m_strMacroID = STT_MACRO_ID_PnvPowerDirection;
CString CSttPowerDirectionPnvTest::m_strFilePostFix = "pnvppd";
CString CSttPowerDirectionPnvTest::m_strMacroVer ="1.0";

CSttPowerDirectionPnvTest::CSttPowerDirectionPnvTest() : CSttPowerDirectionTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
	Init();
}

void CSttPowerDirectionPnvTest::Init()
{ 
	CSttGradientMaxAngleTest::Init();
    m_oPowerDirectionParas.init();
    m_oPowerDirectionParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
	m_oResultParas.init();
#ifdef _PSX_QT_LINUX_
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	pTmtGradientProcess->m_nDiretionMode = 0;
#endif
}

CSttPowerDirectionPnvTest::~CSttPowerDirectionPnvTest(void)
{

}

void CSttPowerDirectionPnvTest::AfterSetParameter()
{
    m_oPowerDirectionParas.CopyOwn(&m_oGradientParas,4,3);
	m_oGradientParas.m_fEDU = m_oGradientParas.m_fG1Volt;
	m_oGradientParas.m_fEDI = m_oGradientParas.m_fG1Current;
	m_oGradientParas.m_fG2Volt = 0;
	m_oGradientParas.m_fG2Current = 0;

    m_oGradientParas.m_fStepTime += m_oGradientParas.m_fMarginTime;
//	CSttGradientMaxAngleTest::AfterSetParameter();//zhouhj 20210710 在故障计算里进行基类中的操作

    switch (m_oPowerDirectionParas.m_nVarIndex)
    {
    case Pha_a:
        m_oPowerDirectionParas.m_nTestPhase = POWER_DIR_TEST_PHASE_A;
        m_oPowerDirectionParas.m_nFaultPhase = POWER_DIR_FAULT_PHASE_A;
        m_oPowerDirectionParas.m_nConnectMode = 0;
        break;
    case Phb_b:
        m_oPowerDirectionParas.m_nTestPhase = POWER_DIR_TEST_PHASE_B;
        m_oPowerDirectionParas.m_nFaultPhase = POWER_DIR_FAULT_PHASE_B;
        m_oPowerDirectionParas.m_nConnectMode = 0;
        break;
    case Phc_c:
        m_oPowerDirectionParas.m_nTestPhase = POWER_DIR_TEST_PHASE_C;
        m_oPowerDirectionParas.m_nFaultPhase = POWER_DIR_FAULT_PHASE_C;
        m_oPowerDirectionParas.m_nConnectMode = 0;
        break;
    case Phab_c:
        m_oPowerDirectionParas.m_nTestPhase = POWER_DIR_TEST_PHASE_C;
        m_oPowerDirectionParas.m_nFaultPhase = POWER_DIR_FAULT_PHASE_AB;
        m_oPowerDirectionParas.m_nConnectMode = 1;
        break;
    case Phbc_a:
        m_oPowerDirectionParas.m_nTestPhase = POWER_DIR_TEST_PHASE_A;
        m_oPowerDirectionParas.m_nFaultPhase = POWER_DIR_FAULT_PHASE_BC;
        m_oPowerDirectionParas.m_nConnectMode = 1;
        break;
    case Phca_b:
        m_oPowerDirectionParas.m_nTestPhase = POWER_DIR_TEST_PHASE_B;
        m_oPowerDirectionParas.m_nFaultPhase = POWER_DIR_FAULT_PHASE_CA;
        m_oPowerDirectionParas.m_nConnectMode = 1;
        break;
    default:
        m_oPowerDirectionParas.m_nTestPhase = POWER_DIR_TEST_PHASE_A;
        m_oPowerDirectionParas.m_nFaultPhase = POWER_DIR_FAULT_PHASE_A;
        m_oPowerDirectionParas.m_nConnectMode = 0;
        break;
    }
    if(m_oPowerDirectionParas.m_fStart > m_oPowerDirectionParas.m_fStop)
    {
        m_oPowerDirectionParas.m_fStart += m_oPowerDirectionParas.m_fAngleOffset;
        m_oPowerDirectionParas.m_fStop -= m_oPowerDirectionParas.m_fAngleOffset;
    }
    else
    {
        m_oPowerDirectionParas.m_fStart -= m_oPowerDirectionParas.m_fAngleOffset;
        m_oPowerDirectionParas.m_fStop += m_oPowerDirectionParas.m_fAngleOffset;
    }

    for(int i = 0;i<3;i++)
    {
        m_oPowerDirectionParas.m_uiVOL[1][i].Harm[1].fAmp = m_oPowerDirectionParas.m_uiVOL[0][i].Harm[1].fAmp;
        m_oPowerDirectionParas.m_uiCUR[1][i].Harm[1].fAmp = m_oPowerDirectionParas.m_uiCUR[0][i].Harm[1].fAmp;
        m_oPowerDirectionParas.m_binOut[1][i+1].fHoldTime = m_oPowerDirectionParas.m_binOut[1][0].fHoldTime;
    }

     switch (m_oPowerDirectionParas.m_nVarIndex)
     {
     case Pha_a:
     case Phbc_a:
         m_oPowerDirectionParas.m_fSCVoltage = m_oPowerDirectionParas.m_uiVOL[2][0].Harm[1].fAmp;
         m_oPowerDirectionParas.m_fSCCurrent = m_oPowerDirectionParas.m_uiCUR[2][0].Harm[1].fAmp;
         break;
     case Phb_b:
     case Phca_b:
         m_oPowerDirectionParas.m_fSCVoltage = m_oPowerDirectionParas.m_uiVOL[2][1].Harm[1].fAmp;
         m_oPowerDirectionParas.m_fSCCurrent = m_oPowerDirectionParas.m_uiCUR[2][1].Harm[1].fAmp;
         break;
     case Phc_c:
     case Phab_c:
         m_oPowerDirectionParas.m_fSCVoltage = m_oPowerDirectionParas.m_uiVOL[2][2].Harm[1].fAmp;
         m_oPowerDirectionParas.m_fSCCurrent = m_oPowerDirectionParas.m_uiCUR[2][2].Harm[1].fAmp;
         break;
     default:
         m_oPowerDirectionParas.m_fSCVoltage = m_oPowerDirectionParas.m_uiVOL[2][0].Harm[1].fAmp;
         m_oPowerDirectionParas.m_fSCCurrent = m_oPowerDirectionParas.m_uiCUR[2][0].Harm[1].fAmp;
         break;
     }
}

void CSttPowerDirectionPnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_pnv((tmt_PowerDirectionParas*)&m_oPowerDirectionParas,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttPowerDirectionPnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_pnv_power_dir(&m_oResultParas, pXmlSerialize);
}
