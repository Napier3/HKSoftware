#include "stdafx.h"
#include"SttSoeTest.h"
// #include<QtDebug>

CString CSttSoeTest::m_strMacroName = "开出测试";
CString CSttSoeTest::m_strMacroID = STT_MACRO_ID_SoeTest;
CString CSttSoeTest::m_strFilePostFix = "sttsoet";
CString CSttSoeTest::m_strMacroVer ="1.0";

CSttSoeTest::CSttSoeTest()
{
	m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    SetTestStarting(FALSE);
    Init();
}

void CSttSoeTest::Init()
{
    tmt_SoeTest::init();
    CSttTestBase::Init();
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

long CSttSoeTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    return 0;
}

CSttSoeTest::~CSttSoeTest(void)
{
}

void CSttSoeTest::AfterSetParameter()
{
    if(!GetTestStarting())
    {
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_soe(this);
#endif
    }
}

long CSttSoeTest::CalReport(UINT nState)
{

    return 0;
}

void CSttSoeTest::Stop()
{
    CSttTestBase::Stop();
}

long CSttSoeTest::SetParameter(DWORD dwState)
{
    return 0;
}

BOOL CSttSoeTest::EventProcess()
{
    if(!GetTestStarting())
        return FALSE;

	BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProSoeDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
    return bTestFinished;
}

void CSttSoeTest::StartTest()
{
    CSttTestBase::StartTest();
    if(!GetTestStarting())
    {
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->SetTestStart(SOE);
#endif
    }
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttSoeTest::StartTest >>>>>>");
}


void CSttSoeTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_oSoeParas,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttSoeTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
	GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;

	int nrBinSwitchCount,nrBinExSwitchCount,nrBoutSwitchCount,nrBoutExSwitchCount;
	for(int i=0; i<MAX_BINARYIN_COUNT; i++)
    {
		nrBinSwitchCount=oRampRestCom.m_nrBinSwitchCount[i];
		m_oSoeResult.m_nrBinSwitchCount[i]=nrBinSwitchCount;
		for(int j=0; j<nrBinSwitchCount; j++)
        {
			m_oSoeResult.m_frTimeBinAct[i][j]=oRampRestCom.m_frTimeBinAct[i][j];
        }
    }

    for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
    {
		nrBoutSwitchCount=oRampRestCom.m_nrBoutSwitchCount[i];
		m_oSoeResult.m_nrBoutSwitchCount[i]=nrBoutSwitchCount;
		for(int j=0; j<nrBoutSwitchCount; j++)
        {
			m_oSoeResult.m_frTimeBoutAct[i][j]=oRampRestCom.m_frTimeBoutAct[i][j];
        }
    }

	SwitchModules oSwitchModules=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

	for(int i=0; i<oSwitchModules.m_nModulesBiCount; i++)
    {
		nrBinExSwitchCount=oRampRestCom.m_nrBinExSwitchCount[i];
		m_oSoeResult.m_nrBinExSwitchCount[i]=nrBinExSwitchCount;
		for(int j=0; j<nrBinExSwitchCount; j++)
        {
			m_oSoeResult.m_frTimeBinExAct[i][j]=oRampRestCom.m_frTimeBinExAct[i][j];
        }
    }

	for(int i=0; i<oSwitchModules.m_nModulesBoCount; i++)
    {
		nrBoutExSwitchCount=oRampRestCom.m_nrBoutExSwitchCount[i];
		m_oSoeResult.m_nrBoutExSwitchCount[i]=nrBoutExSwitchCount;
		for(int j=0; j<nrBoutExSwitchCount; j++)
        {
			m_oSoeResult.m_frTimeBoutExAct[i][j]=oRampRestCom.m_frTimeBoutExAct[i][j];
        }
    }
#endif

    stt_xml_serialize(&m_oSoeResult, pXmlSerialize);
}

void CSttSoeTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
{
	STT_RTDATA_EVENT oRtdata;
	oRtdata.oTime.dTime = dTime1;
	oRtdata.oTime.dRealTime = dTime2;
	oRtdata.m_nVolChCount = 0;
	oRtdata.m_nCurChCount = 0;
	oRtdata.m_nHasFaultVolCur=0;

	oRtdata.m_oVolCh[0].m_nIndex = 0;
	oRtdata.m_oVolCh[0].m_fMag = 0;
	oRtdata.m_oVolCh[0].m_fAng = 0;
	oRtdata.m_oVolCh[0].m_fFreq = 0;
	oRtdata.m_nVolChCount++;

	stt_add_rtdatas(oRtdata);
}
