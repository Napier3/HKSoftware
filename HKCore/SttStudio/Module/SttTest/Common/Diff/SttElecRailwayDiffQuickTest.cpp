#include "stdafx.h"
#include "SttElecRailwayDiffQuickTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttElecRailwayDiffQuickTest::m_strMacroName = "差动速断电流测试(牵引变)";
CString CSttElecRailwayDiffQuickTest::m_strMacroID = STT_MACRO_ID_ElecRailwayDiffQuickTest;
CString CSttElecRailwayDiffQuickTest::m_strFilePostFix = "pdffqtst";
CString CSttElecRailwayDiffQuickTest::m_strMacroVer ="1.0";

CSttElecRailwayDiffQuickTest::CSttElecRailwayDiffQuickTest() : CSttElecRailwayDiffThrTest()
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

CSttElecRailwayDiffQuickTest::~CSttElecRailwayDiffQuickTest(void)
{

}

long CSttElecRailwayDiffQuickTest::CalReport(UINT nState)
{
	CSttElecRailwayDiffThrTest::CalReport(nState);
	return 0;
}

void CSttElecRailwayDiffQuickTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_quick(this,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();//在读取完参数后进行参数设置,在此步骤后进行参数转换
		TranslateToStateParas();//参数设置完进行故障转换

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttElecRailwayDiffQuickTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_quick(&m_oResults, pXmlSerialize);
}




