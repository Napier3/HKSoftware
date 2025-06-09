#include "stdafx.h"
#include"SttPIK100Test.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttPik100Test::m_strMacroName = "PIK100测试";
CString CSttPik100Test::m_strMacroID = ("SttPik100ExTest");
CString CSttPik100Test::m_strFilePostFix = "sttptt";
CString CSttPik100Test::m_strMacroVer ="1.0";

CSttPik100Test::CSttPik100Test()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPik100Test::Init()
{
	tmt_Pik100Test::init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttPik100Test::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttPik100Test::~CSttPik100Test(void)
{

}

void CSttPik100Test::AfterSetParameter()
{	

}

long CSttPik100Test::CalReport(UINT nState)
{

	return 0;
}



long CSttPik100Test::SetParameter(DWORD dwState)
{
	return 0;
}

BOOL CSttPik100Test::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProPik100DrvResult();
#endif
	return FALSE;
}

void CSttPik100Test::StartTest()
{
	CSttTestBase::StartTest();
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPik100Test::DataDownload Finished");
	TtmToDrv();
}

void CSttPik100Test::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	tmt_Pik100Test *p=this;
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_pik100(p);
#endif
}

void CSttPik100Test::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPik100Para,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttPik100Test::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	Para_XmlSerialize(pXmlSerialize);
}
