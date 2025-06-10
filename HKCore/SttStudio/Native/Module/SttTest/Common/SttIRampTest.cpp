#include "stdafx.h"
#include"SttIRampTest.h"
#include "SttSystemConfig.h"

CString CSttIRampTest::m_strMacroName = "电流递变测试";
CString CSttIRampTest::m_strMacroID = STT_MACRO_ID_GradientI;
CString CSttIRampTest::m_strFilePostFix = "sttGDT";
CString CSttIRampTest::m_strMacroVer ="1.0";

CSttIRampTest::CSttIRampTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

void CSttIRampTest::Init()
{ 
	CSttGradientTest::Init();
	m_oGradientParas.m_nType = 0;
    m_oGradientParas.m_nSttTestMode = GradientTest_IRamp;
}

// long CSttIRampTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
// {
// 	return true;
// }

CSttIRampTest::~CSttIRampTest(void)
{
}

void CSttIRampTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	m_oGradientParas.m_fEDU = g_theSystemConfig->m_fVNom/SQRT3;
	m_oGradientParas.m_fEDFreq = g_theSystemConfig->m_fFNom;

	m_oGradientParas.m_fG1Volt=m_oGradientParas.m_fEDU;
	m_oGradientParas.m_fG2Volt=m_oGradientParas.m_fEDU;

	stt_xml_serialize_AtsRamp(&m_oGradientParas, pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttIRampTest::AfterSetParameter()
{
	InitBeforeFaultParas_BySequenceSet(&m_oGradientParas);

	switch(m_oGradientParas.m_nChannel)
{
	case IRampCh_Ia:   
        m_oGradientParas.m_nChannel = a1;
		break;
	case IRampCh_Ib:     
        m_oGradientParas.m_nChannel =b1;
		break;
	case IRampCh_Ic:     
        m_oGradientParas.m_nChannel = c1;
		break;
	case IRampCh_Iabc:     
        m_oGradientParas.m_nChannel = abc1;
		break;
	case IRampCh_Ia2:     
        m_oGradientParas.m_nChannel =a2;
		break;
	case IRampCh_Ib2:     
        m_oGradientParas.m_nChannel = b2;
		break;
	case IRampCh_Ic2:     
        m_oGradientParas.m_nChannel = c2;
		break;
	case IRampCh_Iabc2:     
        m_oGradientParas.m_nChannel = abc2;
		break;
	case IRampCh_Iab:     
        m_oGradientParas.m_nChannel = ab1;
		break;
	case IRampCh_Ibc:     
        m_oGradientParas.m_nChannel = bc1;
		break;
	case IRampCh_Ica:     
        m_oGradientParas.m_nChannel = ca1;
		break;
	case IRampCh_Iab2:     
        m_oGradientParas.m_nChannel = ab2;
		break;
	case IRampCh_Ibc2:     
        m_oGradientParas.m_nChannel = bc2;
		break;
	case IRampCh_Ica2:     
        m_oGradientParas.m_nChannel = ca2;
		break;
    case IRampCh_Iabc12:
        m_oGradientParas.m_nChannel = abc12;
		break;

	default:
        m_oGradientParas.m_nChannel = a1;
		break;
	}

    m_oGradientParas.m_fStepTime += m_oGradientParas.m_fMarginTime;

	CSttGradientTest::AfterSetParameter();
}

// double CSttIRampTest::GetTestTimeLong()
// {
// 	float	fTime = 0.000;
// 
// 	return fTime;
// }

// long CSttIRampTest::CalReport(UINT nState)
// {
// 	return 0;
// }

// long CSttIRampTest::SetParameter(DWORD dwState)
// {
// 	return 0;
// }



