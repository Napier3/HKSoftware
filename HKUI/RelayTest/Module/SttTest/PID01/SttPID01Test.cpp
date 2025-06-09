#include "stdafx.h"
#include "SttPID01Test.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttPid01Test::m_strMacroName = "PID01测试";
CString CSttPid01Test::m_strMacroID = STT_MACRO_ID_Pid01Test;
CString CSttPid01Test::m_strFilePostFix = "sttptt";
CString CSttPid01Test::m_strMacroVer ="1.0";

CSttPid01Test::CSttPid01Test()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttPid01Test::Init()
{
	tmt_Pid01Test::init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

CSttPid01Test::~CSttPid01Test(void)
{

}

void CSttPid01Test::AfterSetParameter()
{	

}

BOOL CSttPid01Test::EventProcess()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProPid01DrvResult();
#endif
	return FALSE;
}

void CSttPid01Test::StartTest()
{
	CSttTestBase::StartTest();
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttPid01Test::DataDownload Finished");
	TtmToDrv();
}

void CSttPid01Test::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	tmt_Pid01Test *p=this;
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_pid01(p);
#endif
}

void CSttPid01Test::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oPid01Para,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}
