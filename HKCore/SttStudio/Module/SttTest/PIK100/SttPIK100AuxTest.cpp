#include "stdafx.h"
//#include"SttPIK100AuxTest.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttPik100AuxTest::m_strMacroName = "PIK100测试";
CString CSttPik100AuxTest::m_strMacroID = ("SttPik100AuxTest");
CString CSttPik100AuxTest::m_strFilePostFix = "sttptt";
CString CSttPik100AuxTest::m_strMacroVer ="1.0";

CSttPik100AuxTest::CSttPik100AuxTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPik100AuxTest::Init()
{
	tmt_Pik100AuxTest::init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttPik100AuxTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttPik100AuxTest::~CSttPik100AuxTest(void)
{

}

void CSttPik100AuxTest::AfterSetParameter()
{	

}

long CSttPik100AuxTest::CalReport(UINT nState)
{

	return 0;
}

void CSttPik100AuxTest::Stop()
{
   CSttDeviceBase::g_pSttDeviceBase->EventProcessAUDCSTOP();
}

long CSttPik100AuxTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttPik100AuxTest::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProPik100DrvResult();
#endif
}

void CSttPik100AuxTest::StartTest()
{
	CSttTestBase::StartTest();
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPik100Test::DataDownload Finished");
	TtmToDrv();
}

void CSttPik100AuxTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->EventProcessAUDCOUT();
#endif
}

void CSttPik100AuxTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPik100AuxPara,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttPik100AuxTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	Para_XmlSerialize(pXmlSerialize);
}
