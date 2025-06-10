#include "stdafx.h"
#include"SttAsyncManuTest.h"
#ifdef _PSX_QT_LINUX_
	#include "../../../SttDevice/SttDeviceBase.h"
#else
    #include "SttSystemConfig.h"
#endif

CString CSttAsyncManuTest::m_strMacroName = "异步通用试验";
CString CSttAsyncManuTest::m_strMacroID = STT_MACRO_ID_AnsyncManualTest;
CString CSttAsyncManuTest::m_strFilePostFix = "sttuit";

CSttAsyncManuTest::CSttAsyncManuTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    SetTestStarting(FALSE);
	m_dTestStartTime = 0;
}

void CSttAsyncManuTest::Init()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->m_oManuRtList.clear();
	CSttDeviceBase::g_pSttDeviceBase->InitAsyncManu();
#endif
    CSttTestBase::Init();
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

long CSttAsyncManuTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    m_dwCurTickCount++;

	if(GetTestStarting() && g_pAsyncManualTest != NULL)
    {
		if(g_pAsyncManualTest->m_oParas.m_fOutPutTime >= 0.001 && IsTestTimeFinished(g_pAsyncManualTest->m_oParas.m_fOutPutTime))
        {
			if(!g_pAsyncManualTest->m_oParas.m_bAging)
            {
                Stop();
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 大电流输出限时或用户主动限时"));
				ReturnTestStateEvent_TestFinish(0, 0, FALSE);
			}
        }

#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->AutoControl_PTU();
#endif
    }

    return 0;
}

CSttAsyncManuTest::~CSttAsyncManuTest(void)
{

}

void CSttAsyncManuTest::AfterSetParameter()
{
	if(g_pAsyncManualTest != NULL)
	{
		g_pAsyncManualTest->m_oResult.m_fTripTime = 0;
		g_pAsyncManualTest->m_oResult.m_fActValue = 0;
		g_pAsyncManualTest->m_oResult.m_fReturnValue = 0;
		g_pAsyncManualTest->m_oResult.m_fReturnTime = 0;
		m_bBinStopTest = g_pAsyncManualTest->m_oParas.m_bBinStop;
#ifdef _PSX_QT_LINUX_
		// CSttDeviceBase::g_pSttDeviceBase->SetOutputTime(m_pManualTest, NULL); //大电流限时
#endif
	}
}

double CSttAsyncManuTest::GetTestTimeLong()
{
    float fTime;
	if(g_pAsyncManualTest != NULL)
		fTime = g_pAsyncManualTest->m_oParas.m_fOutPutTime;
    fTime += TIME_ONLINE_DELAY;
    return fTime;
}

long CSttAsyncManuTest::CalReport(UINT nState)
{
    return 0;
}

BOOL CSttAsyncManuTest::EventProcess()
{
    if(!GetTestStarting())
    {
        return FALSE;
    }

    BOOL bTestFinished = FALSE;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->ProCommDrvResult(bTestFinished, m_oTestFinishedTime);
#endif
    return bTestFinished;
}

void CSttAsyncManuTest::Stop()
{
	if(g_pAsyncManualTest != NULL && g_pAsyncManualTest->m_oParas.m_bAging == FALSE)
    {
	   CSttTestBase::Stop();    //老化模式不停输出
    }
}

long CSttAsyncManuTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttAsyncManuTest::StartTest()
{
    CSttTestBase::StartTest();
    TtmToDrv();

    if(!GetTestStarting())
	{
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
		if(g_pAsyncManualTest != NULL)
		{
			if(g_pAsyncManualTest->m_oParas.m_bAuto)
			{
				CSttDeviceBase::g_pSttDeviceBase->SetTestStart(GradientTest);
			}
			else
			{
				CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ManualTest);
			}
		}
#endif
    }

	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttAsyncManuTest::StartTest >>>>>>");
}

void CSttAsyncManuTest::TtmToDrv()
{
	if(g_pAsyncManualTest != NULL)
	{
		if(g_pAsyncManualTest->m_oParas.m_bAuto)
		{
			m_nCurStepIndex = 0;
		}

#ifdef _PSX_QT_LINUX_
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_AsyncManu(g_pAsyncManualTest, TRUE);
#endif
	}
}

void CSttAsyncManuTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_pAsyncManualTest != NULL)
		stt_xml_serialize(&g_pAsyncManualTest->m_oParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttAsyncManuTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if(!CheckBeforeUpdatePara())
    {
        return;
    }

    Para_XmlSerialize(pXmlSerialize);
    CSttTestBase::StartTest();//实验开始时间重新赋值
	if(g_pAsyncManualTest != NULL)
	{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_AsyncManu_UpdateParameter();
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_AsyncManu(g_pAsyncManualTest);
#endif
	}

	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttAsyncManuTest::UpdatePara Finished");
}

#ifdef _PSX_QT_LINUX_
	#include "../../../SttDevice/Module/PowerCtrl/SttPowerCtrlCom.h"
#endif

BOOL CSttAsyncManuTest::CheckBeforeUpdatePara()
{
    if(!GetTestStarting())//实验未开始
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttAsyncManuTest not StartTest, undo UpdatePara_XmlSerialize");
        return FALSE;
    }

	if(g_pAsyncManualTest != NULL && g_pAsyncManualTest->m_oParas.m_bAuto)//自动递变
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttAsyncManuTest m_bAuto==TRUE, undo UpdatePara_XmlSerialize");
        return FALSE;
    }

	if(g_pAsyncManualTest != NULL && g_pAsyncManualTest->m_oParas.m_bAging)//老化
    {
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttAsyncManuTest m_bAging==TRUE, undo UpdatePara_XmlSerialize");
        return FALSE;
    }

    if(g_theSystemConfig->m_nHasWeek)//使能小信号输出
    {
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitWeekOutputDAData();
#endif
    }

    return TRUE;
}

void CSttAsyncManuTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
{

}

void CSttAsyncManuTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_pAsyncManualTest == NULL)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
	g_pAsyncManualTest->m_oResult.m_frTestTime = oRampRestCom.m_fTripTime;
	g_pAsyncManualTest->m_oResult.m_fTripTime = g_pAsyncManualTest->m_oResult.m_frTestTime;
    int nrBinSwitchCount, nrBinExSwitchCount;

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        nrBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[i];
		g_pAsyncManualTest->m_oResult.m_nrBinSwitchCount[i] = nrBinSwitchCount;

        for(int j = 0; j < nrBinSwitchCount && j <= 64; j++)
        {
			g_pAsyncManualTest->m_oResult.m_frTimeBinAct[i][j] = oRampRestCom.m_frTimeBinAct[i][j];
        }
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
        nrBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[i];
		g_pAsyncManualTest->m_oResult.m_nrBinExSwitchCount[i] = nrBinExSwitchCount;

        for(int j = 0; j < nrBinExSwitchCount && j <= 64; j++)
        {
			g_pAsyncManualTest->m_oResult.m_frTimeBinExAct[i][j] = oRampRestCom.m_frTimeBinExAct[i][j];
        }
    }

	g_pAsyncManualTest->m_oResult.m_nTripFlag = oRampRestCom.m_nAct;
	g_pAsyncManualTest->m_oResult.m_fActValue = oRampRestCom.m_fTripValue;
	g_pAsyncManualTest->m_oResult.m_fReturnValue = oRampRestCom.m_fReturnValue;
	g_pAsyncManualTest->m_oResult.m_fReturnCoef = oRampRestCom.m_fReturnCoef;
	g_pAsyncManualTest->m_oResult.m_fReturnTime = oRampRestCom.m_fReturnTime;
#endif
	stt_xml_serialize(&g_pAsyncManualTest->m_oResult, pXmlSerialize);
}
