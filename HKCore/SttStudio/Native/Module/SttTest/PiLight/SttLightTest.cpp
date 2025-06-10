#include "stdafx.h"
#include"SttLightTest.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLightTest::m_strMacroName = "弧光测试";
CString CSttLightTest::m_strMacroID = ("LightTest");
CString CSttLightTest::m_strFilePostFix = "sttptt";
CString CSttLightTest::m_strMacroVer ="1.0";

CSttLightTest::CSttLightTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttLightTest::Init()
{
	tmt_LightTest::init();
	CSttTestBase::Init();
	m_uStartTimeS = 0;
	m_uStartTimeNS = 0;
}

long CSttLightTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttLightTest::~CSttLightTest(void)
{

}

void CSttLightTest::AfterSetParameter()
{	

}

long CSttLightTest::CalReport(UINT nState)
{

	return 0;
}

long CSttLightTest::SetParameter(DWORD dwState)
{
	return 0;
}

BOOL CSttLightTest::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

	BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProLightDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
	return bTestFinished;
}

void CSttLightTest::StartTest()
{
	CSttTestBase::StartTest();

	if(!GetTestStarting())
	{
#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif		
		TtmToDrv();
	}

	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttLightTest::StartTest >>>>>>>");
}

void CSttLightTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oLightPara,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttLightTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	tmt_LightTest *p=this;
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_lightpara(p);
#endif
}

void CSttLightTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	Para_XmlSerialize(pXmlSerialize);

	CSttTestBase::StartTest();//实验开始时间重新赋值
#ifdef _PSX_QT_LINUX_
	tmt_LightTest *p=this;
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_lightpara(p);
#endif

	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttLightTest::UpdatePara Finished");
}

void CSttLightTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
	GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;

	m_oLightResult.m_frTestTime=oRampRestCom.m_fTripTime;
	m_oLightResult.m_fTripTime=m_oLightResult.m_frTestTime;

	int nrBinSwitchCount;
	for(int i=0; i<MAX_BINARYIN_COUNT; i++)
	{
		nrBinSwitchCount=oRampRestCom.m_nrBinSwitchCount[i];
		m_oLightResult.m_nrBinSwitchCount[i]=nrBinSwitchCount;
		for(int j=0; j<nrBinSwitchCount; j++)
		{
			m_oLightResult.m_frTimeBinAct[i][j]=oRampRestCom.m_frTimeBinAct[i][j];
		}
	}

	m_oLightResult.m_nTripFlag=oRampRestCom.m_nAct;
	m_oLightResult.m_fActValue=oRampRestCom.m_fTripValue;
#endif

	stt_xml_serialize(&m_oLightResult, pXmlSerialize);
}
