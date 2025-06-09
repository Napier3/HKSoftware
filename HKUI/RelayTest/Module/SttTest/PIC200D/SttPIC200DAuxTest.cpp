#include "stdafx.h"
#include"SttPIC200DAuxTest.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttPic200dAuxTest::m_strMacroName = "PIC200D测试";
CString CSttPic200dAuxTest::m_strMacroID = ("SttPic200dAuxTest");
CString CSttPic200dAuxTest::m_strFilePostFix = "sttptt";
CString CSttPic200dAuxTest::m_strMacroVer ="1.0";

CSttPic200dAuxTest::CSttPic200dAuxTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPic200dAuxTest::Init()
{
	tmt_pic200dAux_para::init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttPic200dAuxTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttPic200dAuxTest::~CSttPic200dAuxTest(void)
{

}

void CSttPic200dAuxTest::AfterSetParameter()
{	

}

long CSttPic200dAuxTest::CalReport(UINT nState)
{

	return 0;
}

void CSttPic200dAuxTest::Stop()
{
   CSttDeviceBase::g_pSttDeviceBase->close_pic200d();
}

long CSttPic200dAuxTest::SetParameter(DWORD dwState)
{
	return 0;
}

void CSttPic200dAuxTest::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProPic200dDrvResult();
#endif
}

void CSttPic200dAuxTest::StartTest()
{
	CSttTestBase::StartTest();
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPic200dAuxTest::DataDownload Finished");
	TtmToDrv();
}

void CSttPic200dAuxTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->EventProcessAUDCOUT(this);
#endif
}

void CSttPic200dAuxTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serializeAux(&m_oAuxDA,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttPic200dAuxTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	Para_XmlSerialize(pXmlSerialize);
}
