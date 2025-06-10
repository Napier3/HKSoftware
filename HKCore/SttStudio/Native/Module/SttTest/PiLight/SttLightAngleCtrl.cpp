#include "stdafx.h"
#include"SttLightAngleCtrl.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLightAngleCtrl::m_strMacroName = "弧光角度控制";
CString CSttLightAngleCtrl::m_strMacroID = ("LightAngleCtrl");
CString CSttLightAngleCtrl::m_strFilePostFix = "sttptt";
CString CSttLightAngleCtrl::m_strMacroVer ="1.0";

CSttLightAngleCtrl::CSttLightAngleCtrl()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttLightAngleCtrl::Init()
{
	tmt_LightAngleTest::init();
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttLightAngleCtrl::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttLightAngleCtrl::~CSttLightAngleCtrl(void)
{

}

void CSttLightAngleCtrl::AfterSetParameter()
{	

}

long CSttLightAngleCtrl::CalReport(UINT nState)
{

	return 0;
}

long CSttLightAngleCtrl::SetParameter(DWORD dwState)
{
	return 0;
}

BOOL CSttLightAngleCtrl::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

	BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProLightDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
	return bTestFinished;
}

void CSttLightAngleCtrl::StartTest()
{
	CSttTestBase::StartTest();

	if(!GetTestStarting())
	{
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
		SetTestStarting(TRUE);
		TtmToDrv();
	}

	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttLightAngleCtrl::StartTest >>>>>>>");
}

void CSttLightAngleCtrl::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oLightAnglePara,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttLightAngleCtrl::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	tmt_LightAngleTest *p = this;
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_lightangle(p,m_oLightAnglePara.m_nMode);
#endif
}
