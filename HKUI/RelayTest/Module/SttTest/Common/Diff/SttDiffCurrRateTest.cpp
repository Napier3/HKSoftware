#include "stdafx.h"
#include "SttDiffCurrRateTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiffCurrRateTest::m_strMacroName = "差动比率制动搜索";
CString CSttDiffCurrRateTest::m_strMacroID = STT_MACRO_ID_PsuDiffRateTest;
CString CSttDiffCurrRateTest::m_strFilePostFix = "pdffrtst";
CString CSttDiffCurrRateTest::m_strMacroVer ="1.0";

CSttDiffCurrRateTest::CSttDiffCurrRateTest() : CSttDiffCurrThrTest()
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

CSttDiffCurrRateTest::~CSttDiffCurrRateTest(void)
{

}

long CSttDiffCurrRateTest::CalReport(UINT nState)
{
	CSttDiffCurrThrTest::CalReport(nState);
	m_oResults.m_fIbiasValue = m_fIbias;

	if (m_oResults.m_nActFlag)
	{
		float fValue = m_oResults.m_fIdiffActValue;
		m_oDiffCalTool.CurrentCal(&fValue,m_fIbias,m_nEarthing);
		SetResultValues_I1IeI2Ie();
		
	}

	return 0;
}

void CSttDiffCurrRateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_rate(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换
		m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreTime + m_fPreFaultTime;

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDiffCurrRateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_rate(&m_oResults, pXmlSerialize);
}




