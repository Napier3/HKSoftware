#include "stdafx.h"
#include"SttManuTest.h"
#ifdef _PSX_QT_LINUX_
    #include "../../SttDevice/SttDeviceBase.h"
#else
    #include "SttSystemConfig.h"
#endif

CString CSttManuTest::m_strMacroName = "电压电流试验";
CString CSttManuTest::m_strMacroID = STT_MACRO_ID_ManualTest;
CString CSttManuTest::m_strFilePostFix = "sttuit";

CString CSttMUAccuracyTest::m_strMacroName = "合并单元精确度试验";
CString CSttMUAccuracyTest::m_strMacroID = _T("MUAccuracyTest");
CString CSttMUAccuracyTest::m_strFilePostFix = "sttuit";

CSttManuTest::CSttManuTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
    m_pManualTest = stt_test_get_base_manualtest_buff();
}

void CSttManuTest::Init()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->m_oManuRtList.clear();
#endif
    m_pManualTest->init();
    CSttTestBase::Init();
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

long CSttManuTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    m_dwCurTickCount++;

    if(GetTestStarting())
    {
        if(m_pManualTest->m_oManuParas.m_fOutPutTime >= 0.001 && IsTestTimeFinished(m_pManualTest->m_oManuParas.m_fOutPutTime))
        {
            if(!m_pManualTest->m_oManuParas.m_bAging)
            {
                Stop();

#ifdef _PSX_QT_LINUX_
				if(g_nLogPrintIsZN)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[warning] 输出限时[%d]"),
											   m_pManualTest->m_oManuParas.m_fOutPutTime);
				}
				else
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[warning] OutPutTime[%d]"),
										 m_pManualTest->m_oManuParas.m_fOutPutTime);
				}
#endif

				if(m_pManualTest->m_oManuParas.m_bResultAddBin)
				{
					GetBinStatus();
				}

				ReturnTestStateEvent_TestFinish(0, 0, FALSE);
			}
        }

#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->AutoControl_PTU();
#endif
    }

    return 0;
}

void CSttManuTest::GetBinStatus()
{
	long nret = 0;
#ifdef _PSX_QT_LINUX_
	Drv_BIStatus oBiStatus;
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nret = read(nFd, &oBiStatus, 0x202);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(nret != sizeof(Drv_BIStatus))
	{
		return;
	}

	BI_STATUS *pBIStatus = &CSttDeviceBase::g_pSttDeviceBase->m_oBIStatus;
	int nBiValue = 0;
	for(int nChanIndex = 0; nChanIndex < MAX_BINARYIN_COUNT && nChanIndex < g_nBinCount; nChanIndex++)
	{
		nBiValue = oBiStatus.item[0].nVal1 >> nChanIndex;
		nBiValue = nBiValue & 0x1;
		nBiValue = (nBiValue == 0 ? 1 : 0);
		pBIStatus->m_nBin[nChanIndex] = nBiValue;
	}

	SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

	if(oSwitchModules.m_nModulesCount > 0)
	{
		int nOffSet = 0;

		for(int j = 0; j < oSwitchModules.m_nModulesCount; j++)
		{
			if(j > 0)
			{
				nOffSet += oSwitchModules.oSWITCHINFO[j - 1].m_nBiCount;
			}

			long nBiIndex = 0;
			for(int k = 0; k < 64; k++)
			{
				if(oSwitchModules.oSWITCHINFO[j].m_bBiPos[k] == FALSE)
				{
					continue;
				}

				if(k < 32)
				{
					nBiValue = (oBiStatus.item[j + 1].nVal1 >> k) & 1;
				}
				else
				{
					nBiValue = (oBiStatus.item[j + 1].nVal2 >> (k - 32)) & 1;
				}

				pBIStatus->m_nBinEx[nOffSet + nBiIndex] = nBiValue > 0 ? 0 : 1;
				nBiIndex++;
			}
		}
	}
#endif
}

CSttManuTest::~CSttManuTest(void)
{
}

void CSttManuTest::AfterSetParameter()
{
    m_pManualTest->m_oManuResult.m_fTripTime = 0;
    m_pManualTest->m_oManuResult.m_fActValue = 0;
    m_pManualTest->m_oManuResult.m_fReturnValue = 0;
    m_pManualTest->m_oManuResult.m_fReturnTime = 0;
    m_bBinStopTest = m_pManualTest->m_oManuParas.m_bBinStop;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetOutputTime(m_pManualTest, NULL); //大电流限时
#endif

	float fOutPutTime = m_pManualTest->m_oManuParas.m_fOutPutTime;
	if(fOutPutTime > 1.0)
	{
#ifdef _PSX_QT_LINUX_
		if(g_nLogPrintIsZN)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("输出限时%d秒"),fOutPutTime);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("OutPutTime[%ds]"),fOutPutTime);
		}
#endif
	}
}

double CSttManuTest::GetTestTimeLong()
{
    float fTime;
    fTime = m_pManualTest->m_oManuParas.m_fOutPutTime;
    fTime += TIME_ONLINE_DELAY;
    return fTime;
}

long CSttManuTest::CalReport(UINT nState)
{
    return 0;
}

BOOL CSttManuTest::EventProcess()
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

void CSttManuTest::Stop()
{
    if(!m_pManualTest->m_oManuParas.m_bAging)
    {
        if(m_pManualTest->m_oManuParas.m_nFuncType < 3)
        {
            CSttTestBase::Stop();    //老化模式不停输出
        }
        else
        {
#ifdef _PSX_QT_LINUX_
            CSttDeviceBase::g_pSttDeviceBase->SetPPSTestStop();
#endif
			SetTestStarting(FALSE);
        }
    }
}

long CSttManuTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttManuTest::StartTest()
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

        if(m_pManualTest->m_oManuParas.m_bAuto)
        {
            CSttDeviceBase::g_pSttDeviceBase->SetTestStart(GradientTest);
        }
        else
        {
            if(m_pManualTest->m_oManuParas.m_nFuncType == 0)
            {
                CSttDeviceBase::g_pSttDeviceBase->SetTestStart(ManualTest);
            }
            else if(m_pManualTest->m_oManuParas.m_nFuncType < 3)
            {
				if(m_pManualTest->m_oManuParas.m_nFuncType == 1)
				{
					CSttDeviceBase::g_pSttDeviceBase->SetADMUChannel(m_pManualTest);
				}
				int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
				
				g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
				ioctl(nfd, 0x110, 1);//合并单元角差，开启秒同步
				g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

                CSttDeviceBase::g_pSttDeviceBase->SetTestStart(MUTest);
            }
            else
            {
                int nPPS_SetType = m_pManualTest->m_oManuParas.m_oMuParas.nPPS_SetType;

                if(nPPS_SetType < 2)
                {
                    CSttDeviceBase::g_pSttDeviceBase->SetPPSTestStart();
                }
                else
                {
                    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(MUTest);
                }
            }
        }

#endif
    }

    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttManuTest::StartTest >>>>>>");
}

void CSttManuTest::TtmToDrv()
{
    if(m_pManualTest->m_oManuParas.m_bAuto)
    {
        m_nCurStepIndex = 0;
    }

#ifdef _PSX_QT_LINUX_

    if(m_pManualTest->m_oManuParas.m_nFuncType == 0)
    {
        CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_manu(m_pManualTest, TRUE);
    }
    else
    {
        CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_MUTest(m_pManualTest, TRUE);
        int nPPS_SetType = m_pManualTest->m_oManuParas.m_oMuParas.nPPS_SetType;

        if(nPPS_SetType < 2)
        {
            CSttDeviceBase::g_pSttDeviceBase->SetRising(nPPS_SetType);
        }
    }

#endif
}

void CSttManuTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_pManualTest->m_oManuParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

void CSttManuTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if(!CheckBeforeUpdatePara())
    {
        return;
    }

    Para_XmlSerialize(pXmlSerialize);
    CSttTestBase::StartTest();//实验开始时间重新赋值
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Manu_UpdateParameter(m_pManualTest->m_oManuParas.m_bDC);

    if(m_pManualTest->m_oManuParas.m_nFuncType == 0)
    {
        CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_manu(m_pManualTest);
    }
    else
    {
        CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_MUTest(m_pManualTest);
    }

#endif
    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttManuTest::UpdatePara Finished");
}

#ifdef _PSX_QT_LINUX_
    #include "../../SttDevice/Module/PowerCtrl/SttPowerCtrlCom.h"
#endif

BOOL CSttManuTest::CheckBeforeUpdatePara()
{
    if(!GetTestStarting())//实验未开始
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttManuTest not StartTest, undo UpdatePara_XmlSerialize");
        return FALSE;
    }

    if(m_pManualTest->m_oManuParas.m_bAuto)//自动递变
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttManuTest m_bAuto==TRUE, undo UpdatePara_XmlSerialize");
        return FALSE;
    }

    if(m_pManualTest->m_oManuParas.m_bAging)//老化
    {
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttManuTest m_bAging==TRUE, undo UpdatePara_XmlSerialize");
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

void CSttManuTest::Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if(g_theSystemConfig->m_nHasDigital)
    {
        stt_xml_serialize(m_pManualTest->m_oManuParas.m_oGoosePub, pXmlSerialize); //获取Gout信息,放入第一个状态的Gout中
    }
}

void CSttManuTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
{
    STT_RTDATA_EVENT oRtdata;
    oRtdata.oTime.dTime = dTime1;
    oRtdata.oTime.dRealTime = dTime2;
    oRtdata.m_nVolChCount = 0;
    oRtdata.m_nCurChCount = 0;
	oRtdata.m_nHasFaultVolCur=0;
    int nRtIndex = 0;
    float fVal;

    if(m_pManualTest->m_oManuParas.m_bAuto)
    {
#ifdef _PSX_QT_LINUX_
        tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;

        if(nStep <= oGradientParas.m_nStepCnt)
        {
            ProGradientRtDatasEvent(oRtdata, nStep, nType);
        }

#endif
    }
    else
    {
#ifdef _PSX_QT_LINUX_

        if(CSttDeviceBase::g_pSttDeviceBase->m_oManuRtList.isEmpty())
        {
            return;
        }

        ManuRtData oManuRtData = CSttDeviceBase::g_pSttDeviceBase->m_oManuRtList.takeFirst();

        for(int nIndex = 0; nIndex < g_nRtDataVoltCnt; nIndex++)
        {
            fVal = fabs(oManuRtData.uiVOL[nIndex].Harm[1].fAmp);
            nRtIndex = oRtdata.m_nVolChCount;
            oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
			oRtdata.m_oVolCh[nRtIndex].m_fMag = fVal;
			oRtdata.m_oVolCh[nRtIndex].m_fAng =
				oManuRtData.uiVOL[nIndex].Harm[1].fAngle;
			oRtdata.m_oVolCh[nRtIndex].m_fFreq =
				oManuRtData.uiVOL[nIndex].Harm[1].fFreq;
            oRtdata.m_nVolChCount++;
        }

        for(int nIndex = 0; nIndex < g_nRtDataCurrCnt; nIndex++)
        {
            fVal = fabs(oManuRtData.uiCUR[nIndex].Harm[1].fAmp);
            nRtIndex = oRtdata.m_nCurChCount;
            oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
			oRtdata.m_oCurCh[nRtIndex].m_fMag = fVal;
			oRtdata.m_oCurCh[nRtIndex].m_fAng =
				oManuRtData.uiCUR[nIndex].Harm[1].fAngle;
			oRtdata.m_oCurCh[nRtIndex].m_fFreq =
				oManuRtData.uiCUR[nIndex].Harm[1].fFreq;
            oRtdata.m_nCurChCount++;
            CSttDeviceBase::g_pSttDeviceBase->SetCurrAmp_Monitor(nIndex, fVal);
        }

#endif
    }

    if(oRtdata.m_nCurChCount > 0 || oRtdata.m_nVolChCount > 0)
    {
        stt_add_rtdatas(oRtdata);
    }
}

void CSttManuTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_pManualTest->m_oManuResult.m_frTestTime = oRampRestCom.m_fTripTime;
    m_pManualTest->m_oManuResult.m_fTripTime = m_pManualTest->m_oManuResult.m_frTestTime;
    int nrBinSwitchCount, nrBinExSwitchCount;

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        nrBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[i];
        m_pManualTest->m_oManuResult.m_nrBinSwitchCount[i] = nrBinSwitchCount;

        for(int j = 0; j < nrBinSwitchCount && j <= 64; j++)
        {
            m_pManualTest->m_oManuResult.m_frTimeBinAct[i][j] = oRampRestCom.m_frTimeBinAct[i][j];
        }
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
        nrBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[i];
        m_pManualTest->m_oManuResult.m_nrBinExSwitchCount[i] = nrBinExSwitchCount;

        for(int j = 0; j < nrBinExSwitchCount && j <= 64; j++)
        {
            m_pManualTest->m_oManuResult.m_frTimeBinExAct[i][j] = oRampRestCom.m_frTimeBinExAct[i][j];
        }
    }

    m_pManualTest->m_oManuResult.m_nTripFlag = oRampRestCom.m_nAct;
    m_pManualTest->m_oManuResult.m_fActValue = oRampRestCom.m_fTripValue;
    m_pManualTest->m_oManuResult.m_fReturnValue = oRampRestCom.m_fReturnValue;
    m_pManualTest->m_oManuResult.m_fReturnCoef = oRampRestCom.m_fReturnCoef;
    m_pManualTest->m_oManuResult.m_fReturnTime = oRampRestCom.m_fReturnTime;
#endif
	stt_xml_serialize(&m_pManualTest->m_oManuResult, pXmlSerialize, m_pManualTest->m_oManuParas.m_bResultAddBin);
}
