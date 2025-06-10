#include "stdafx.h"
#include "SttDCDiffCurrRateTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDCDiffCurrRateTest::m_strMacroName = "比率制动系数";
CString CSttDCDiffCurrRateTest::m_strMacroID = STT_MACRO_ID_DCDifferRateTest;
CString CSttDCDiffCurrRateTest::m_strFilePostFix = "pdffrtst";
CString CSttDCDiffCurrRateTest::m_strMacroVer ="1.0";

CSttDCDiffCurrRateTest::CSttDCDiffCurrRateTest() : CSttDCDiffCurrThrTest()
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

CSttDCDiffCurrRateTest::~CSttDCDiffCurrRateTest(void)
{

}

long CSttDCDiffCurrRateTest::CalReport(UINT nState)
{
    CSttDCDiffCurrThrTest::CalReport(nState);
	m_oResults.m_fIbiasValue = m_fIbias;

	if (m_oResults.m_nActFlag)
	{
		float fValue = m_oResults.m_fIdiffActValue;
		m_oDiffCalTool.CurrentCal(&fValue,m_fIbias);
		SetResultValues_I1IeI2Ie();
		
	}

	return 0;
}

void CSttDCDiffCurrRateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_rate(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDCDiffCurrRateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_rate(&m_oResults, pXmlSerialize);
}




