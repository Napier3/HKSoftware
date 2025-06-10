#include "stdafx.h"
#include"SttLightGetAngle.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLightGetAngle::m_strMacroName = "¶ÁÈ¡»¡¹â½Ç¶È";
CString CSttLightGetAngle::m_strMacroID = ("LightGetAngle");
CString CSttLightGetAngle::m_strFilePostFix = "sttptt";
CString CSttLightGetAngle::m_strMacroVer ="1.0";

tmt_LightGetAngle g_oLightGetAngle;

CSttLightGetAngle::CSttLightGetAngle()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttLightGetAngle::Init()
{
	tmt_LightGetAngle::init();
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttLightGetAngle::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttLightGetAngle::~CSttLightGetAngle(void)
{

}

void CSttLightGetAngle::AfterSetParameter()
{	

}

long CSttLightGetAngle::CalReport(UINT nState)
{

	return 0;
}

long CSttLightGetAngle::SetParameter(DWORD dwState)
{
	return 0;
}

BOOL CSttLightGetAngle::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

	BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProLightDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
	return bTestFinished;
}

void CSttLightGetAngle::StartTest()
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

	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttLightGetAngle::StartTest >>>>>>>");
}

void CSttLightGetAngle::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{

}

void CSttLightGetAngle::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_lightangle(NULL,2);
#endif
}

void CSttLightGetAngle::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&g_oLightGetAngle.m_oLightGetAngleResult, pXmlSerialize);
}
