#include "stdafx.h"
#include "SttOverVoltageTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttOverVoltageTest::m_strMacroName = "过压保护试验";
CString CSttOverVoltageTest::m_strMacroID = STT_MACRO_ID_OverVoltageTest;
CString CSttOverVoltageTest::m_strFilePostFix = "oovv";
CString CSttOverVoltageTest::m_strMacroVer ="1.0";

CSttOverVoltageTest::CSttOverVoltageTest() : CSttImpBaseTest()
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

void CSttOverVoltageTest::Init()
{ 
	CSttImpBaseTest::Init();
//	m_pStateParas.m_nStateNumbers = 2;
    tmt_OverVoltageParas::init();
	m_oResults.init();
}

CSttOverVoltageTest::~CSttOverVoltageTest(void)
{

}

void CSttOverVoltageTest::AfterSetParameter()
{
	CSttImpBaseTest::AfterSetParameter();

	m_pImpBaseParas->m_bSearchNext = FALSE;
	m_pImpBaseParas->m_pStateParas->m_paraState[0].m_tGps = m_tGps;
    m_fSCVoltage[0] = m_fUSetting * m_fRate[0];//通过定值和系数计算过压值

    /*Complex p1;
	p1 = p1.polar(m_fK0Amp,m_fK0Angle);
	p1 = (p1+1)*m_fSCCurrent[0];
	p1 = p1*m_fImpedance[0];
    m_fSCVoltage[0] = (float)p1.norm();*/

	if (m_nFaultType[0] == 6)
	{
		m_nFaultType[0] = 9;
	}
    m_nCalMode = 3;//固定电压、电流值时,计算模式为3
}

long CSttOverVoltageTest::CalReport(UINT nState)
{
	CalReport_ImpBase(this,&m_oResults);
	return 0;
}

void CSttOverVoltageTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_OverVoltage((tmt_OverVoltageParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttOverVoltageTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oResults, pXmlSerialize);
}

long CSttOverVoltageTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttOverVoltageTest::TranslateToStateParas()
{
	m_fMaxFaultTime = m_fTSetting+m_fMarginTime;
    TranslateToStateParas_ImpBase(this);
    switch(m_nFaultType[0])
    {
    case  0:
        m_pImpBaseParas->m_pStateParas->m_paraState[1].m_uiVOL[0].Harm[1].fAmp = m_fSCVoltage[0];
        break;
    case  1:
        m_pImpBaseParas->m_pStateParas->m_paraState[1].m_uiVOL[1].Harm[1].fAmp = m_fSCVoltage[0];
        break;
    case  2:
        m_pImpBaseParas->m_pStateParas->m_paraState[1].m_uiVOL[2].Harm[1].fAmp = m_fSCVoltage[0];
        break;
    }
	m_oResults.m_fFaultVol = m_fSCVoltage[0];
	m_oResults.m_fFaultCurrent = m_fSCCurrent[0];
	m_oResults.m_fOverCurrent = m_fSCCurrent[0];
    m_oResults.m_fDcVoltage = m_fSCVoltage[0];
}
