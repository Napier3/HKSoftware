#include "stdafx.h"
#include"SttHarmTest.h"
#ifdef _PSX_QT_LINUX_
    #include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttHarmTest::m_strMacroName = "谐波测试";
CString CSttHarmTest::m_strMacroID = ("HarmTest");
CString CSttHarmTest::m_strFilePostFix = "stthrt";
CString CSttHarmTest::m_strMacroVer = "1.0";

CString CSttMUHarmTest::m_strMacroName = "合并单元谐波试验";
CString CSttMUHarmTest::m_strMacroID = _T("MUHarmTest");
CString CSttMUHarmTest::m_strFilePostFix = "sttuit";

CSttHarmTest::CSttHarmTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
    m_pHarmTest = stt_test_get_base_harmtest_buff();
}

void CSttHarmTest::Init()
{
    m_pHarmTest->init();
    CSttTestBase::Init();
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

long CSttHarmTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    m_dwCurTickCount++;

    if(GetTestStarting())
    {
        if(m_pHarmTest->m_oHarmParas.m_fOutPutTime >= 0.001 &&
                IsTestTimeFinished(m_pHarmTest->m_oHarmParas.m_fOutPutTime))
        {
            Stop();
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 大电流输出限时"));
			ReturnTestStateEvent_TestFinish(0, 0, FALSE);
        }
    }

    return 0;
}

CSttHarmTest::~CSttHarmTest(void)
{
}

void CSttHarmTest::AfterSetParameter()
{
    m_pHarmTest->m_oHarmResult.m_fTripTime = 0;
    m_pHarmTest->m_oHarmResult.m_fActValue = 0;
    m_pHarmTest->m_oHarmResult.m_fReturnValue = 0;
    m_pHarmTest->m_oHarmResult.m_fReturnTime = 0;
    m_bBinStopTest = m_pHarmTest->m_oHarmParas.m_bBinStop;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetOutputTime(NULL, m_pHarmTest); //大电流限时
#endif

	float fOutPutTime = m_pHarmTest->m_oHarmParas.m_fOutPutTime;
	if(fOutPutTime > 1.0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("电流限时输出%f秒"),fOutPutTime);
	}
}

void CSttMUHarmTest::AfterSetParameter()
{
	m_pHarmTest->m_oHarmResult.m_fTripTime = 0;
	m_pHarmTest->m_oHarmResult.m_fActValue = 0;
	m_pHarmTest->m_oHarmResult.m_fReturnValue = 0;
	m_pHarmTest->m_oHarmResult.m_fReturnTime = 0;
	m_bBinStopTest = m_pHarmTest->m_oHarmParas.m_bBinStop;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetOutputTime(NULL, m_pHarmTest); //大电流限时
#endif

	float fOutPutTime = m_pHarmTest->m_oHarmParas.m_fOutPutTime;
	if(fOutPutTime > 1.0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("电流限时输出%f秒"),fOutPutTime);
	}
	m_pHarmTest->m_oHarmParas.m_nFuncType = 1;
}

double CSttHarmTest::GetTestTimeLong()
{
    float fTime;
    fTime = m_pHarmTest->m_oHarmParas.m_fOutPutTime;
    fTime += TIME_ONLINE_DELAY;
    return fTime;
}

long CSttHarmTest::CalReport(UINT nState)
{
    return 0;
}


long CSttHarmTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttHarmTest::StartTest()
{
#ifdef _PSX_QT_LINUX_

    if(g_theSystemConfig->m_nHasAnalog != 0)
    {
        int nRet = CSttDeviceBase::g_pSttDeviceBase->CheckHarmTestPara(m_pHarmTest);

        if(nRet == 0)
        {
            m_bTestParaCheckOk = TRUE;
        }
        else if(nRet == 1)
        {
            m_bTestParaCheckOk = FALSE;
        }
        else if(nRet == 2)
        {
            m_bTestParaCheckOk = FALSE;
        }
        else
        {
            m_bTestParaCheckOk = TRUE;
            m_pHarmTest->m_oHarmParas.m_fOutPutTime = 10;//谐波含量过大，限制输出时间
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 谐波含量过大，限制输出10秒"));
        }
    }
    else
    {
        m_bTestParaCheckOk = TRUE;    //小信号及数字输出不需要检测谐波含量
    }

    if(!m_bTestParaCheckOk)
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttHarmTest TestParaCheckFail");
        return;
    }

#endif
    CSttTestBase::StartTest();
    TtmToDrv();

    if(!GetTestStarting())
    {
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_

        if(m_pHarmTest->m_oHarmParas.m_bAuto)
        {
            CSttDeviceBase::g_pSttDeviceBase->SetTestStart(GradientTest);
        }
        else
        {
			if(m_pHarmTest->m_oHarmParas.m_nFuncType == 0)
			{
            CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ManualTest);
        }
			else
			{
				if(m_pHarmTest->m_oHarmParas.m_nFuncType == 1)
				{
					CSttDeviceBase::g_pSttDeviceBase->SetADMUChannel(m_pHarmTest);
				}
				int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
				
				g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
				ioctl(nfd, 0x110, 1);//合并单元角差，开启秒同步
				g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

				CSttDeviceBase::g_pSttDeviceBase->SetTestStart(MUTest);
			}
		}

#endif
    }

    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttHarmTest::StartTest >>>>>>");
}

void CSttHarmTest::TtmToDrv()
{
    if(m_pHarmTest->m_oHarmParas.m_bAuto)
    {
        m_nCurStepIndex = 0;
    }

#ifdef _PSX_QT_LINUX_
	if(m_pHarmTest->m_oHarmParas.m_nFuncType == 0)
	{
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_harm(m_pHarmTest, TRUE);
	}
	else
	{
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_MUHarmTest(m_pHarmTest, TRUE);
	}
#endif
}

void CSttHarmTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_pHarmTest->m_oHarmParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttHarmTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if(!GetTestStarting())
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttHarmTest not StartTest, undo UpdatePara_XmlSerialize");
        return;
    }

    if(m_pHarmTest->m_oHarmParas.m_bAuto)
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttHarmTest m_bAuto==TRUE, undo UpdatePara_XmlSerialize");
        return;
    }

    Para_XmlSerialize(pXmlSerialize);
#ifdef _PSX_QT_LINUX_

    if(g_theSystemConfig->m_nHasAnalog != 0)
    {
        int nRet = CSttDeviceBase::g_pSttDeviceBase->CheckHarmTestPara(m_pHarmTest);

        if(nRet == 0)
        {
            m_bTestParaCheckOk = TRUE;
        }
        else if(nRet == 1)
        {
            m_bTestParaCheckOk = FALSE;
        }
        else if(nRet == 2)
        {
            m_bTestParaCheckOk = FALSE;
        }
        else
        {
            m_bTestParaCheckOk = TRUE;
            m_pHarmTest->m_oHarmParas.m_fOutPutTime = 10;//谐波含量过大，限制输出时间
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 谐波含量过大，限制输出10秒"));
        }
    }
    else
    {
        m_bTestParaCheckOk = TRUE;    //小信号及数字输出不需要检测谐波含量
    }

    if(!m_bTestParaCheckOk)
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] CSttHarmTest TestParaCheckFail"));
        return;
    }

    if(g_theSystemConfig->m_nHasWeek != 0)
    {
        CSttDeviceBase::g_pSttDeviceBase->InitWeekOutputDAData();
    }

    CSttTestBase::StartTest();//实验开始时间重新赋值

	if(m_pHarmTest->m_oHarmParas.m_nFuncType == 0)
	{
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_harm(m_pHarmTest);
	}
	else
	{
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_MUHarmTest(m_pHarmTest);
	}
#endif
    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttHarmTest::UpdatePara Finished");
}

BOOL CSttHarmTest::EventProcess()
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

void CSttHarmTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
{
    STT_RTDATA_EVENT oRtdata;
    oRtdata.oTime.dTime = dTime1;
    oRtdata.oTime.dRealTime = dTime2;
    oRtdata.m_nVolChCount = 0;
    oRtdata.m_nCurChCount = 0;
	oRtdata.m_nHasFaultVolCur=0;
    int nRtIndex = 0;
    float fVal;
    float fTotal = 0;
    //后期完善
    return;

    if(m_pHarmTest->m_oHarmParas.m_bAuto)
    {
#ifdef _PSX_QT_LINUX_
        tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;

        if(m_nCurStepIndex <= oGradientParas.m_nStepCnt && m_nCurStepIndex > -1)
        {
            ProGradientRtDatasEvent(oRtdata, nStep, nType);
        }

#endif
    }
    else
    {
        for(int nIndex = 0; nIndex < g_nRtDataVoltCnt; nIndex++)
        {
            fTotal = 0;

            for(int i = 1; i < MAX_HARM_COUNT; i++)
            {
                fVal = fabs(m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[1].fAmp);
                fTotal += fVal * fVal;
            }

            fTotal = sqrt(fTotal);
            fTotal += m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[0].fAmp;
            nRtIndex = oRtdata.m_nVolChCount;
            oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
			oRtdata.m_oVolCh[nRtIndex].m_fMag = fTotal;
			oRtdata.m_oVolCh[nRtIndex].m_fAng =
				m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[1].fAngle;
			oRtdata.m_oVolCh[nRtIndex].m_fFreq =
				m_pHarmTest->m_oHarmParas.m_uiVOL[nIndex].Harm[1].fFreq;
            oRtdata.m_nVolChCount++;
        }

        for(int nIndex = 0; nIndex < g_nRtDataCurrCnt; nIndex++)
        {
            fTotal = 0;

            for(int i = 1; i < MAX_HARM_COUNT; i++)
            {
                fVal = fabs(m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[1].fAmp);
                fTotal += fVal * fVal;
            }

            fTotal = sqrt(fTotal);
            fTotal += m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[0].fAmp;
            nRtIndex = oRtdata.m_nCurChCount;
            oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
			oRtdata.m_oCurCh[nRtIndex].m_fMag = fTotal;
			oRtdata.m_oCurCh[nRtIndex].m_fAng =
				m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[1].fAngle;
			oRtdata.m_oCurCh[nRtIndex].m_fFreq =
				m_pHarmTest->m_oHarmParas.m_uiCUR[nIndex].Harm[1].fFreq;
            oRtdata.m_nCurChCount++;
#ifdef _PSX_QT_LINUX_
            CSttDeviceBase::g_pSttDeviceBase->SetCurrAmp_Monitor(nIndex, fTotal);
#endif
        }
    }

    if(oRtdata.m_nCurChCount > 0 || oRtdata.m_nVolChCount > 0)
    {
        stt_add_rtdatas(oRtdata);
    }
}

void CSttHarmTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_pHarmTest->m_oHarmResult.m_frTestTime = oRampRestCom.m_fTripTime;
    m_pHarmTest->m_oHarmResult.m_fTripTime = m_pHarmTest->m_oHarmResult.m_frTestTime;
    int nrBinSwitchCount, nrBinExSwitchCount;

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        nrBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[i];
        m_pHarmTest->m_oHarmResult.m_nrBinSwitchCount[i] = nrBinSwitchCount;

        for(int j = 0; j < nrBinSwitchCount; j++)
        {
            m_pHarmTest->m_oHarmResult.m_frTimeBinAct[i][j] = oRampRestCom.m_frTimeBinAct[i][j];
        }
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
        nrBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[i];
        m_pHarmTest->m_oHarmResult.m_nrBinExSwitchCount[i] = nrBinExSwitchCount;

        for(int j = 0; j < nrBinExSwitchCount; j++)
        {
            m_pHarmTest->m_oHarmResult.m_frTimeBinExAct[i][j] = oRampRestCom.m_frTimeBinExAct[i][j];
        }
    }

    m_pHarmTest->m_oHarmResult.m_nTripFlag = oRampRestCom.m_nAct;
    m_pHarmTest->m_oHarmResult.m_fActValue = oRampRestCom.m_fTripValue;
    m_pHarmTest->m_oHarmResult.m_fReturnValue = oRampRestCom.m_fReturnValue;
    m_pHarmTest->m_oHarmResult.m_fReturnCoef = oRampRestCom.m_fReturnCoef;
    m_pHarmTest->m_oHarmResult.m_fReturnTime = oRampRestCom.m_fReturnTime;
#endif
    stt_xml_serialize(&m_pHarmTest->m_oHarmResult, pXmlSerialize);
}
