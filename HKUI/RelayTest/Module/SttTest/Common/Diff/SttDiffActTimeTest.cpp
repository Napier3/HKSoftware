#include "stdafx.h"
#include "SttDiffActTimeTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiffActTimeTest::m_strMacroName = "差动动作时间测试";
CString CSttDiffActTimeTest::m_strMacroID = STT_MACRO_ID_PsuDiffTimeTest;
CString CSttDiffActTimeTest::m_strFilePostFix = "pdffttst";
CString CSttDiffActTimeTest::m_strMacroVer ="1.0";

CSttDiffActTimeTest::CSttDiffActTimeTest() : CSttDiffCurrThrTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
}

CSttDiffActTimeTest::~CSttDiffActTimeTest(void)
{

}

long CSttDiffActTimeTest::CalReport(UINT nState)
{
	m_oResults.m_fTripTime = m_pStateTest->m_oStateResults.m_resultState[1].m_frTestTime;
	m_oResults.m_nActFlag = m_pStateTest->m_oStateResults.m_resultState[1].m_nAct;
    SetResultValues_I1IeI2Ie();
	return 0;
}

void CSttDiffActTimeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_acttime(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		m_fScanFrom = m_fIdiff;
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换
		m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreTime + m_fPreFaultTime;

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDiffActTimeTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_acttime(&m_oResults, pXmlSerialize);
}

void CSttDiffActTimeTest::ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;

	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestStart, &oTime, bWithEvent);
	m_fCurrScanVal = m_fIdiff;
	pTestServer->ReturnTestStateEvent(SttResult_Type_SearchPointReport, &oTime, bWithEvent);
}


void CSttDiffActTimeTest::ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
{
	STT_TIME oTime;
	oTime.dRealTime = dRealTime;
	oTime.dTime = dTime;
	oTime.dBinActTime = -1;
	CalReport();
	CSttTestServerBase *pTestServer = CSttTestServerBase::GetServerEngine();
	pTestServer->ReturnTestStateEvent(SttResult_Type_TestFinish, &oTime, bWithEvent);
	SetTestStarting(FALSE);
}





