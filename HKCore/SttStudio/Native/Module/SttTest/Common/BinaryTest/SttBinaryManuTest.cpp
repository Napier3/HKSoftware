#include "stdafx.h"
#include"SttBinaryManuTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

CString CSttBinaryManuTest::m_strMacroName = "开关量手动测试";
CString CSttBinaryManuTest::m_strMacroID = STT_MACRO_ID_BinaryManuTest;
CString CSttBinaryManuTest::m_strFilePostFix = "bsttst";
CString CSttBinaryManuTest::m_strMacroVer = "1.0";

CSttBinaryManuTest::CSttBinaryManuTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
	m_pManualTest = stt_test_get_base_manualtest_buff();
}

void CSttBinaryManuTest::Init()
{
	m_pManualTest->init();
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

CSttBinaryManuTest::~CSttBinaryManuTest(void)
{
}

BOOL CSttBinaryManuTest::EventProcess()
{
	if(!GetTestStarting())
	{
		return FALSE;
	}

	BOOL bTestFinished = FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProCommDrvResult(bTestFinished, m_oTestFinishedTime);
#endif
	return bTestFinished;
}

long CSttBinaryManuTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttBinaryManuTest::StartTest()
{
	CSttTestBase::StartTest();
	TtmToDrv();

	if(!GetTestStarting())
	{
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
		SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->SetTestStart(BinaryManuTest);
#endif
	}

	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttBinaryManuTest::StartTest >>>>>>");
}

void CSttBinaryManuTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_BinaryManu(m_pManualTest, TRUE);
#endif
}

void CSttBinaryManuTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_BinaryManual(&m_pManualTest->m_oManuParas, pXmlSerialize);
}

void CSttBinaryManuTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	Para_XmlSerialize(pXmlSerialize);
	CSttTestBase::StartTest();//实验开始时间重新赋值
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_BinaryManu(m_pManualTest);
#endif
	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttBinaryManuTest::UpdatePara Finished");
}
