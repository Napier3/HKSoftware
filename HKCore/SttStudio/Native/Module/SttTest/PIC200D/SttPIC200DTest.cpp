#include "stdafx.h"
#include"SttPIC200DTest.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttPic200dTest::m_strMacroName = "PIC200D测试";
CString CSttPic200dTest::m_strMacroID = ("SttPic200dTest");
CString CSttPic200dTest::m_strFilePostFix = "sttptt";
CString CSttPic200dTest::m_strMacroVer ="1.0";

CSttPic200dTest::CSttPic200dTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPic200dTest::Init()
{
	tmt_Pic200dTest::init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttPic200dTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttPic200dTest::~CSttPic200dTest(void)
{

}

void CSttPic200dTest::AfterSetParameter()
{	

}

long CSttPic200dTest::CalReport(UINT nState)
{

	return 0;
}

long CSttPic200dTest::SetParameter(DWORD dwState)
{
	return 0;
}

BOOL CSttPic200dTest::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

#ifdef _PSX_QT_LINUX_
	tmt_Pic200dTest *p=this;
	CSttDeviceBase::g_pSttDeviceBase->ProPic200dDrvResult(p);
#endif
	return FALSE;
}

void CSttPic200dTest::StartTest()
{
	CSttTestBase::StartTest();
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPic200dTest::DataDownload Finished");
	TtmToDrv();
}

void CSttPic200dTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	tmt_Pic200dTest *p=this;
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_pic200d(p);
#endif
}

void CSttPic200dTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPic200dPara,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}


void CSttPic200dTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	Para_XmlSerialize(pXmlSerialize);
}

void CSttPic200dTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPic200dResult,pXmlSerialize);
}
