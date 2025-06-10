#include "stdafx.h"
#include "SttManuDiffCurrQuickTest.h"
#include "../../SttSystemConfig.h"
#include "../../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttManuDiffCurrQuickTest::m_strMacroName = "差动速断电流测试(手动递变)";
CString CSttManuDiffCurrQuickTest::m_strMacroID = STT_MACRO_ID_PsuManuDiffQuickTest;
CString CSttManuDiffCurrQuickTest::m_strFilePostFix = "pdffqtst";
CString CSttManuDiffCurrQuickTest::m_strMacroVer ="1.0";

CSttManuDiffCurrQuickTest::CSttManuDiffCurrQuickTest() : CSttManuDiffCurrThrTest()
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

CSttManuDiffCurrQuickTest::~CSttManuDiffCurrQuickTest(void)
{

}

long CSttManuDiffCurrQuickTest::CalReport(UINT nState)
{
	CSttManuDiffCurrThrTest::CalReport(nState);
	return 0;
}

void CSttManuDiffCurrQuickTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_quick(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttManuDiffCurrQuickTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_quick(&m_oResults, pXmlSerialize);
}




