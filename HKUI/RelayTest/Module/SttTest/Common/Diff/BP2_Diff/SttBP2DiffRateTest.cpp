#include "stdafx.h"
#include "SttBP2DiffRateTest.h"
#include "../../SttSystemConfig.h"
#include "../../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttBP2DiffRateTest::m_strMacroName = "BP2差动比率制动搜索";
CString CSttBP2DiffRateTest::m_strMacroID = STT_MACRO_ID_BP2DiffRateTest;
CString CSttBP2DiffRateTest::m_strFilePostFix = "bprdct";
CString CSttBP2DiffRateTest::m_strMacroVer ="1.0";

CSttBP2DiffRateTest::CSttBP2DiffRateTest() : CSttBP2DiffThrTest()
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

CSttBP2DiffRateTest::~CSttBP2DiffRateTest(void)
{

}

long CSttBP2DiffRateTest::CalReport(UINT nState)
{
	CSttBP2DiffThrTest::CalReport(nState);
	m_oResults.m_fIbiasValue = m_fIr_Id;

	if (m_oResults.m_nActFlag)
	{
		float fValue = m_oResults.m_fIdiffActValue;
		m_oDiffCalTool.CurrentCal3I_BP2(&fValue,m_fIr_Id);
		SetResultValues_I1I2();
	}

	return 0;
}

void CSttBP2DiffRateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
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

void CSttBP2DiffRateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_rate(&m_oResults, pXmlSerialize);
}




