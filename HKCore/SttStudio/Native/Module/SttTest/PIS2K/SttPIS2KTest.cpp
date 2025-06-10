#include "stdafx.h"
#include"SttPIS2KTest.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttPis2kTest::m_strMacroName = "PIS2K测试";
CString CSttPis2kTest::m_strMacroID = ("SttPis2kTest");
CString CSttPis2kTest::m_strFilePostFix = "sttptt";
CString CSttPis2kTest::m_strMacroVer ="1.0";

CSttPis2kTest::CSttPis2kTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPis2kTest::Init()
{
	tmt_Pis2kTest::init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttPis2kTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttPis2kTest::~CSttPis2kTest(void)
{

}

void CSttPis2kTest::AfterSetParameter()
{	

}

long CSttPis2kTest::CalReport(UINT nState)
{

	return 0;
}

long CSttPis2kTest::SetParameter(DWORD dwState)
{
	return 0;
}

BOOL CSttPis2kTest::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	tmt_Pis2kTest *p=this;
	CSttDeviceBase::g_pSttDeviceBase->ProPis2kDrvResult(p);
#endif
	return FALSE;
}

void CSttPis2kTest::StartTest()
{
	CSttTestBase::StartTest();
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPis2kTest::DataDownload Finished");
	TtmToDrv();
}

void CSttPis2kTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	tmt_Pis2kTest *p=this;
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_pis2k(p);
#endif
}

void CSttPis2kTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPis2kPara,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttPis2kTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	Para_XmlSerialize(pXmlSerialize);
}


void CSttPis2kTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPis2kResult, pXmlSerialize);
}
