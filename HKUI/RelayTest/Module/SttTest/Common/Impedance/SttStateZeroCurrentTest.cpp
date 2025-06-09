#include "stdafx.h"
#include "SttStateZeroCurrentTest.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttStateZeroCurrentTest::m_strMacroName = "零序保护试验(单机)";
CString CSttStateZeroCurrentTest::m_strMacroID = STT_MACRO_ID_StateI0Current;
CString CSttStateZeroCurrentTest::m_strFilePostFix = "sti0c";
CString CSttStateZeroCurrentTest::m_strMacroVer ="1.0";

CSttStateZeroCurrentTest::CSttStateZeroCurrentTest() : CSttZeroCurrentTest()
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

void CSttStateZeroCurrentTest::Init()
{ 
	CSttZeroCurrentTest::Init();
}

CSttStateZeroCurrentTest::~CSttStateZeroCurrentTest(void)
{

}

void CSttStateZeroCurrentTest::AfterSetParameter()
{
	CSttZeroCurrentTest::AfterSetParameter();

	if (m_nIsAutoTest)
	{
		int nSttTrigMode = TMT_MDSTATE_TIMETRIGGER;

		switch (m_nFaultTrigMode)
		{
		case 0:		// 按键触发
			nSttTrigMode = TMT_MDSTATE_MEARSURETRIGGER; 
			break;
		case 1:		// 时间触发
			nSttTrigMode = TMT_MDSTATE_TIMETRIGGER; 
			break;
		case 2:		// GPS触发
			nSttTrigMode = TMT_MDSTATE_GPSBTRIGGER; 
			break;
		case 3:		// 开入接点翻转触发
			nSttTrigMode = TMT_MDSTATE_BINTRIGGER; 
			break;
		default:
			break;
		}

		m_nFaultTrigMode = nSttTrigMode;
	}
}

void CSttStateZeroCurrentTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_StateZeroCurrent((tmt_ZeroCurrentParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttStateZeroCurrentTest::TranslateToStateParas()
{
	m_fMaxFaultTime = m_fTSetting+m_fMarginTime;
	TranslateToStateParas_ImpBase(this,m_fUnom);
	m_oResults.m_fFaultVol = m_fSCVoltage[0];
	m_oResults.m_fFaultCurrent = m_fSCCurrent[0];
//	CSttZeroCurrentTest::TranslateToStateParas();
}
