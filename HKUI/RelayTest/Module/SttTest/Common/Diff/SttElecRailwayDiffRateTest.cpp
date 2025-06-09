#include "stdafx.h"
#include "SttElecRailwayDiffRateTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttElecRailwayDiffRateTest::m_strMacroName = "差动比率制动搜索(牵引变)";
CString CSttElecRailwayDiffRateTest::m_strMacroID = STT_MACRO_ID_ElecRailwayDiffRateTest;
CString CSttElecRailwayDiffRateTest::m_strFilePostFix = "erdfrtst";
CString CSttElecRailwayDiffRateTest::m_strMacroVer ="1.0";

CSttElecRailwayDiffRateTest::CSttElecRailwayDiffRateTest() : CSttElecRailwayDiffThrTest()
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

CSttElecRailwayDiffRateTest::~CSttElecRailwayDiffRateTest(void)
{

}

long CSttElecRailwayDiffRateTest::CalReport(UINT nState)
{
	CSttElecRailwayDiffThrTest::CalReport(nState);
	m_oResults.m_fIbiasValue = m_fIbias;

	if (m_oResults.m_nActFlag)
	{
		float fValue = m_oResults.m_fIdiffActValue;
		float fIalpha = 0,fIbeta = 0;
		m_oDiffCalTool.CurrentCal_ElecRailway(&fValue,m_fIbias,fIalpha,fIbeta);
		SetResultValues_I1IeI2Ie_ElecRailway(fIalpha,fIbeta);
	}

	return 0;
}

void CSttElecRailwayDiffRateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
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

void CSttElecRailwayDiffRateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_rate_elec_railway(&m_oResults, pXmlSerialize);
}




