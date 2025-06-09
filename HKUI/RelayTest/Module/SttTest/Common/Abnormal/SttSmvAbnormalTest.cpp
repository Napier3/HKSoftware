#include "stdafx.h"
#include "SttSmvAbnormalTest.h"
#include "../SttSystemConfig.h"
#include "../SttStateTest.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttSmvAbnTest::m_strMacroName = "Smv异常模拟";
CString CSttSmvAbnTest::m_strMacroID = STT_MACRO_ID_SmvAbnTest;
CString CSttSmvAbnTest::m_strFilePostFix = "abn";
CString CSttSmvAbnTest::m_strMacroVer ="1.0";
CSttSmvAbnTest::CSttSmvAbnTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;
	m_pStateTest = stt_test_get_base_statetest_buff();
}

CSttSmvAbnTest::~CSttSmvAbnTest(void)
{

}

void CSttSmvAbnTest::StartTest()
{
	CSttTestBase::StartTest();

	if(!GetTestStarting())
	{
		TtmToDrv();
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
		SetTestStarting(TRUE);

#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->SetTestStart(AbnSvTest);
#endif		
	}
	else
	{
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttAbnormalTest is  Running,Can't StartTest()");
	}

}

void CSttSmvAbnTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	g_nTmtParaMode = g_theSystemConfig->m_nParaMode;
	stt_xml_serialize(&m_pStateTest->m_oStateParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttSmvAbnTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_AbnPara(&m_pStateTest->m_oStateParas,ABN_TYPE_SMV);
#endif
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttSmvAbnormalTest::StartTest >>>>>>");
}
