#include "stdafx.h"
#include "SttGseAbnormalTest.h"
#include "../SttSystemConfig.h"
#include "../SttStateTest.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttGseAbnTest::m_strMacroName = "GseÒì³£Ä£Äâ";
CString CSttGseAbnTest::m_strMacroID = STT_MACRO_ID_GseAbnTest;
CString CSttGseAbnTest::m_strFilePostFix = "abn";
CString CSttGseAbnTest::m_strMacroVer ="1.0";
CSttGseAbnTest::CSttGseAbnTest()
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

CSttGseAbnTest::~CSttGseAbnTest(void)
{

}

void CSttGseAbnTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_AbnPara(&m_pStateTest->m_oStateParas,ABN_TYPE_GOOSE);
#endif
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttGseAbnormalTest::StartTest >>>>>>");
}
