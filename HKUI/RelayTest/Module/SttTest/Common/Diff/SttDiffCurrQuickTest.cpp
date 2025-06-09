#include "stdafx.h"
#include "SttDiffCurrQuickTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiffCurrQuickTest::m_strMacroName = "差动速断电流测试";
CString CSttDiffCurrQuickTest::m_strMacroID = STT_MACRO_ID_PsuDiffQuickTest;
CString CSttDiffCurrQuickTest::m_strFilePostFix = "pdffqtst";
CString CSttDiffCurrQuickTest::m_strMacroVer ="1.0";

CSttDiffCurrQuickTest::CSttDiffCurrQuickTest() : CSttDiffCurrThrTest()
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

CSttDiffCurrQuickTest::~CSttDiffCurrQuickTest(void)
{

}

long CSttDiffCurrQuickTest::CalReport(UINT nState)
{
	CSttDiffCurrThrTest::CalReport(nState);
	return 0;
}

void CSttDiffCurrQuickTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_quick(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换
		m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreTime + m_fPreFaultTime;

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDiffCurrQuickTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_quick(&m_oResults, pXmlSerialize);
}




