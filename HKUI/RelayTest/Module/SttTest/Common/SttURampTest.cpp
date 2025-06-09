#include "stdafx.h"
#include"SttURampTest.h"
#include "SttSystemConfig.h"

CString CSttURampTest::m_strMacroName = "电压递变测试";
CString CSttURampTest::m_strMacroID = STT_MACRO_ID_GradientU;
CString CSttURampTest::m_strFilePostFix = "sttGDT";
CString CSttURampTest::m_strMacroVer ="1.0";

CSttURampTest::CSttURampTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
}

void CSttURampTest::Init()
{ 
	CSttGradientTest::Init();
	m_oGradientParas.m_nType = 0;
    m_oGradientParas.m_nSttTestMode = GradientTest_URamp;
}

// long CSttURampTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
// {
// 	return true;
// }

CSttURampTest::~CSttURampTest(void)
{
}

void CSttURampTest::AfterSetParameter()
{
	for(int i=0;i<GRADIENT_CHAN_COUNT;i++)
	{
		m_oGradientParas.m_uiVOL[2][i].Harm[1].fFreq = m_oGradientParas.m_fHz;
		m_oGradientParas.m_uiCUR[2][i].Harm[1].fFreq = m_oGradientParas.m_fHz;
	}

	InitBeforeFaultParas_BySequenceSet(&m_oGradientParas);

	switch(m_oGradientParas.m_nChannel)
	{
	case URampCh_Ua:   
        m_oGradientParas.m_nChannel = a1;
		break;
	case URampCh_Ub:     
        m_oGradientParas.m_nChannel = b1;
		break;
	case URampCh_Uc:     
        m_oGradientParas.m_nChannel =  c1;
		break;
	case URampCh_Uab:     
        m_oGradientParas.m_nChannel = ab1;
		break;
	case URampCh_Ubc:     
        m_oGradientParas.m_nChannel = bc1;
		break;
	case URampCh_Uca:     
        m_oGradientParas.m_nChannel = ca1;
		break;
	case URampCh_Uabc:     
        m_oGradientParas.m_nChannel = abc1;
		break;
    case URampCh_Ua2:
        m_oGradientParas.m_nChannel = a2;
        break;
    case URampCh_Ub2:
        m_oGradientParas.m_nChannel = b2;
        break;
    case URampCh_Uc2:
        m_oGradientParas.m_nChannel =  c2;
        break;
    case URampCh_Uab2:
        m_oGradientParas.m_nChannel = ab2;
        break;
    case URampCh_Ubc2:
        m_oGradientParas.m_nChannel = bc2;
        break;
    case URampCh_Uca2:
        m_oGradientParas.m_nChannel = ca2;
        break;
    case URampCh_Uabc2:
        m_oGradientParas.m_nChannel = abc2;
        break;
    case URampCh_Uabc12:
        m_oGradientParas.m_nChannel = abc12;
		break;

	default:
		m_oGradientParas.m_nChannel = U1a;
		break;
	}
    m_oGradientParas.m_fStepTime += m_oGradientParas.m_fMarginTime;

	CSttGradientTest::AfterSetParameter();
}

void CSttURampTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
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


// double CSttURampTest::GetTestTimeLong()
// {
// 	float	fTime = 0.000;
// 
// 	return fTime;
// }

// long CSttURampTest::CalReport(UINT nState)
// {
// 
// 	return 0;
// }
// 
// long CSttURampTest::SetParameter(DWORD dwState)
// {
// 	return 0;
// }



