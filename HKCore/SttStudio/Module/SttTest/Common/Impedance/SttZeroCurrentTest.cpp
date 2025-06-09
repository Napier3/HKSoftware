#include "stdafx.h"
#include "SttZeroCurrentTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttZeroCurrentTest::m_strMacroName = "零序保护试验";
CString CSttZeroCurrentTest::m_strMacroID = STT_MACRO_ID_ZeroCurrent;
CString CSttZeroCurrentTest::m_strFilePostFix = "ozsc";
CString CSttZeroCurrentTest::m_strMacroVer ="1.0";

CSttZeroCurrentTest::CSttZeroCurrentTest() : CSttImpBaseTest()
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

void CSttZeroCurrentTest::Init()
{ 
	CSttImpBaseTest::Init();
//	m_oStateParas.m_nStateNumbers = 2;
	tmt_ZeroCurrentParas::init();
	m_oResults.init();
	m_fUnom = g_theSystemConfig->m_fVNom/SQRT3;//初始化时将额定电压初始化为系统参数中值,如果串行化生效,使用传入的额定电压值
}

CSttZeroCurrentTest::~CSttZeroCurrentTest(void)
{

}

void CSttZeroCurrentTest::AfterSetParameter()
{
	CSttImpBaseTest::AfterSetParameter();
	m_pImpBaseParas->m_bSearchNext = FALSE;
	m_pImpBaseParas->m_pStateParas->m_paraState[0].m_tGps = m_tGps;
	m_fSCCurrent[0] = m_fSetting[0]*m_fRate[0];//通过定值和系数计算过流值]
	m_nCalMode = 0;

	Complex p1;
	p1 = p1.polar(m_fK0Amp,m_fK0Angle);
	p1 = (p1+1)*m_fSCCurrent[0];
	p1 = p1*m_fImpedance[0];
	m_fSCVoltage[0] = (float)p1.norm();
}

long CSttZeroCurrentTest::CalReport(UINT nState)
{
	CalReport_ImpBase(this,&m_oResults);
	return 0;
}

void CSttZeroCurrentTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_ZeroCurrent((tmt_ZeroCurrentParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttZeroCurrentTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oResults, pXmlSerialize);
}

long CSttZeroCurrentTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttZeroCurrentTest::TranslateToStateParas()
{
	m_fMaxFaultTime = m_fTSetting+m_fMarginTime;
	TranslateToStateParas_ImpBase(this,m_fVolAmp,m_fVolAng);
	m_oResults.m_fFaultVol = m_fSCVoltage[0];
	m_oResults.m_fFaultCurrent = m_fSCCurrent[0];
}
