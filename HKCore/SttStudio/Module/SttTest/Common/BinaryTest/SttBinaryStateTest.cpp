#include "stdafx.h"
#include"SttBinaryStateTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

CString CSttBinaryStateTest::m_strMacroName = "开关量状态序列";
CString CSttBinaryStateTest::m_strMacroID = STT_MACRO_ID_BinaryStateTest;
CString CSttBinaryStateTest::m_strFilePostFix = "bsttst";
CString CSttBinaryStateTest::m_strMacroVer = "1.0";

CSttBinaryStateTest::CSttBinaryStateTest() : CSttTestBase()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
	m_pStateTest = stt_test_get_base_statetest_buff();
#ifdef _PSX_QT_LINUX_
    m_nDrvResItemLen = sizeof(Drv_ResultItem);
#endif
}

void CSttBinaryStateTest::Init()
{
	g_nBinaryStateTestMode = 0;
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.init(g_nStateCount);
	m_pStateTest->m_oStateResults.init(g_nStateCount);
	m_oResults.init();

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
		m_oResults.m_nrBinSwitchTotalCount[i] = 0;
    }

    CSttTestBase::Init();
    m_nCurStateIndex = 0;
}

long CSttBinaryStateTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    if(!GetTestStarting())
    {
        return 0;
    }

	if(g_nBinaryStateTestMode == 0)
	{
		return 0;
	}

    CSttTestServerBase *pSttTestServerBase = CSttTestServerBase::GetServerEngine();

	if(m_oResults.m_nresultCount > 10)
    {
        pSttTestServerBase->Process_Cmd_Test_GetReport(FALSE);
    }

	double dStateBeginTime = 0;
	BOOL bTestFinished = FALSE;
#ifdef _PSX_QT_LINUX_
    m_nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
    char *pDrvResults = stt_test_get_drvresult_buff();
	int nret = 0;
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nret = read(m_nfd, pDrvResults, 0x203);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

    if(nret <= 0)
    {
        return 0;
    }

    for(int i = 0; i < nret / m_nDrvResItemLen; i++)
    {
        memcpy(&m_oDrvResItem, pDrvResults + i * m_nDrvResItemLen, m_nDrvResItemLen);
        double dTime = m_oDrvResItem.nSec + m_oDrvResItem.nNanoSec * 0.000000001;

        switch(m_oDrvResItem.nType)
        {
            case 1:
            {
                ReturnTestStateEvent_TestStart(0, 0, FALSE);
            }
            break;

            case 2:
            {
                SetTestStarting(FALSE);
                bTestFinished = TRUE;
            }
            break;

            case 0x102:
            {
				long nResultIdx = m_oResults.m_nresultCount;
				tmt_BinaryStateResult  &oResultState = m_oResults.m_resultState[nResultIdx];
                oResultState.m_nCurLoopIndx = m_oDrvResItem.nDegressStep;
                oResultState.m_nCurStateIndx = m_oDrvResItem.nStep;
                oResultState.m_nBinAct = 1;
                BOOL bSrcIsGoose = FALSE;
                Drv_BIStatus oBiStatus;
                DrvBIChange  oBiChg = m_oDrvResItem.oBiChg;
                long nBiSize = g_nBinCount;

                if(g_nBinCount > MAX_BINARYIN_COUNT)
                {
                    nBiSize = MAX_BINARYIN_COUNT;
                }

                if(m_oDrvResItem.nGooseFlag & 0x10000)
                {
                    nBiSize = 8;
                    bSrcIsGoose = TRUE;
                    memcpy(&oBiStatus, &m_oDrvResItem.nDi, sizeof(Drv_BIStatus));
                }
                else
                {
                    memcpy(&oBiStatus, &m_oDrvResItem.nBi, sizeof(Drv_BIStatus));
                }

                int nBiChang = 0;
                int nBiValue = 0;

                for(int nChanIndex = 0; nChanIndex < nBiSize; nChanIndex++)
                {
                    nBiValue = oBiStatus.item[0].nVal1 >> nChanIndex;
                    nBiValue = nBiValue & 0x1;
                    nBiChang = oBiChg.item[0].nVal1 >> nChanIndex;
                    nBiChang = nBiChang & 0x1;

                    if(nBiChang == 0)
                    {
                        continue;
                    }

                    nBiValue = (nBiValue == 0 ? 1 : 0);
                    int &nBinSwitchCount = oResultState.m_nrBinSwitchCount[nChanIndex];

                    if(nBinSwitchCount < BIBO_ACTCOUNT)
                    {
                        if(nBinSwitchCount == 0)
                        {
                            oResultState.m_nBinFirstChgState[nChanIndex] = nBiValue;
                        }

						oResultState.m_frTimeBinAct[nChanIndex][nBinSwitchCount] = dTime - dStateBeginTime;
                        nBinSwitchCount++;
						m_oResults.m_nrBinSwitchTotalCount[nChanIndex]++;
                    }
                }

                if(bSrcIsGoose)
                {
                    //无开关量板时 BinEx:0-63 考虑GOOSE虚端子
                    for(int k = 0; k < 64; k++)
                    {
                        if(k < 32)
                        {
                            nBiValue = (oBiStatus.item[1].nVal1 >> k) & 1;
                            nBiChang = (oBiChg.item[1].nVal1 >> k) & 1;
                        }
                        else
                        {
                            nBiValue = (oBiStatus.item[1].nVal2 >> (k - 32)) & 1;
                            nBiChang = (oBiChg.item[1].nVal2 >> (k - 32)) & 1;
                        }

                        if(nBiChang == 0)
                        {
                            continue;
                        }

                        int &nBinExSwitchCount = oResultState.m_nrBinExSwitchCount[k];

                        if(nBinExSwitchCount == 0)
                        {
                            oResultState.m_nBinExFirstChgState[k] = nBiValue;
                        }

						oResultState.m_frTimeBinExAct[k][nBinExSwitchCount] = dTime - dStateBeginTime;
                        nBinExSwitchCount++;
                    }
                }
                else
                {
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
									nBiChang = (oBiChg.item[j + 1].nVal1 >> k) & 1;
								}
								else
								{
									nBiValue = (oBiStatus.item[j + 1].nVal2 >> (k - 32)) & 1;
									nBiChang = (oBiChg.item[j + 1].nVal2 >> (k - 32)) & 1;
								}

								if(nBiChang == 0)
								{
									nBiIndex++;
									continue;
								}

								int &nBinExSwitchCount = oResultState.m_nrBinExSwitchCount[nOffSet + nBiIndex];

								if(nBinExSwitchCount < BIBO_ACTCOUNT)
								{
									if(nBinExSwitchCount == 0)
									{
										oResultState.m_nBinExFirstChgState[nOffSet + nBiIndex] = nBiValue;
									}

									oResultState.m_frTimeBinExAct[nOffSet + nBiIndex][nBinExSwitchCount] = dTime - dStateBeginTime;
									nBinExSwitchCount++;
								}

								nBiIndex++;
							}
						}
                    }
                }
            }
            break;

            case 0x201:
            {
				if(m_oDrvResItem.nStep < CSttDeviceBase::g_pSttDeviceBase->m_nCurStateCount)
				{
					long &nresultCount = m_oResults.m_nresultCount;
					tmt_BinaryStateResult  oResultState = m_oResults.m_resultState[nresultCount];

					if(oResultState.m_nBinAct)
					{
						nresultCount++;
					}
				}
            }
            break;

			case 0x206:
			{
				dStateBeginTime = m_oDrvResItem.nSec + m_oDrvResItem.nNanoSec * 0.000000001;
			}
			break;
        }
    }

#endif

    if(bTestFinished)
    {
        ReturnTestStateEvent_TestFinish(0, 0, false);
    }

    return 0;
}

BOOL CSttBinaryStateTest::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

	if(g_nBinaryStateTestMode == 1)
	{
		return FALSE;
	}

	BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProStateDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
	return bTestFinished;
}

void CSttBinaryStateTest:: InitStateLoopResults()
{
	m_pStateTest->m_oStateResults.init(g_nStateCount);
}

void CSttBinaryStateTest::SyncSingleStateTmtResult()
{
	if(m_nCurStateIndex >= 0 && m_nCurStateIndex < m_pStateTest->m_oStateParas.m_nStateNumbers)
	{

	}
	else
	{
#ifdef _PSX_QT_LINUX_
		for(int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			m_pStateTest->m_oStateResults.m_nBinRefState[i] =
				CSttDeviceBase::g_pSttDeviceBase->m_nBinRefState[i];
		}

		for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_pStateTest->m_oStateResults.m_nBinExRefState[i] =
				CSttDeviceBase::g_pSttDeviceBase->m_nBinExRefState[i];
		}
#endif

		return;
	}

#ifdef _PSX_QT_LINUX_
	long nStateNum = GetStateNum(m_nCurStateIndex);

	if(nStateNum < 0 || nStateNum >= g_nStateCount)
	{
		return;
	}

	tmt_StateResult  &oResultState = m_pStateTest->m_oStateResults.m_resultState[nStateNum];
	GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;

	oResultState.m_nAct = oRampRestCom.m_nAct;//开入量触发翻转,则该标记置为1;有开入变位,但是实际为时间触发进入下一个状态时,该标记仍为0,
	oResultState.m_frTestTime = oRampRestCom.m_fTripTime;
	oResultState.m_nCurStepIndex = oRampRestCom.m_nTripStep;

	int nrBinSwitchCount,nrBinExSwitchCount;
	for(int i=0; i<MAX_BINARYIN_COUNT; i++)
	{
		nrBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[i];
		oResultState.m_nrBinSwitchCount[i] = nrBinSwitchCount;

		if(nrBinSwitchCount >= 0 && nrBinSwitchCount <= 64)
		{
			for(int j = 0; j < nrBinSwitchCount; j++)
			{
				oResultState.m_frTimeBinAct[i][j] = oRampRestCom.m_frTimeBinAct[i][j];
			}
		}

		oResultState.m_nBinFirstChgState[i] = oRampRestCom.m_nBinFirstChgState[i];
		oResultState.m_nRampIndex[i] = oRampRestCom.m_nRampIndex[i];
	}

	for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
	{
		nrBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[i];
		oResultState.m_nrBinExSwitchCount[i] = nrBinExSwitchCount;

		if(nrBinExSwitchCount >= 0 && nrBinExSwitchCount <= 64)
		{
			for(int j = 0; j < nrBinExSwitchCount; j++)
			{
				oResultState.m_frTimeBinExAct[i][j] = oRampRestCom.m_frTimeBinExAct[i][j];
			}
		}

		oResultState.m_nBinExFirstChgState[i] = oRampRestCom.m_nBinExFirstChgState[i];
		oResultState.m_nRampIndexEx[i] = oRampRestCom.m_nRampIndexEx[i];
	}

	oResultState.m_frInTime = oRampRestCom.m_frInTime;
	oResultState.m_frTimeStateBegin = oRampRestCom.m_frTimeStateBegin;
#endif
}

CSttBinaryStateTest::~CSttBinaryStateTest(void)
{
}

void CSttBinaryStateTest::AfterSetParameter()
{
    float fOutputHoldTime;

    for(int nIndex = 0; nIndex < m_pStateTest->m_oStateParas.m_nStateNumbers; nIndex++)
    {
        m_pStateTest->m_oStateResults.m_resultState[nIndex].init();
        fOutputHoldTime = m_pStateTest->m_oStateParas.m_paraState[nIndex].m_fOutputHoldTime;

        if(fOutputHoldTime > 0)
        {
            m_pStateTest->m_oStateParas.m_paraState[nIndex].m_binOut[0].fHoldTime = fOutputHoldTime;
        }
    }

    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

double CSttBinaryStateTest::GetTestTimeLong()
{
    float	fTime = 0.000;

    for(int i = 0; i < m_pStateTest->m_oStateParas.m_nStateNumbers; i++)
    {
		tmt_StatePara *pSt = &m_pStateTest->m_oStateParas.m_paraState[i];

        if(pSt->m_nTriggerCondition == TMT_MDSTATE_TIMETRIGGER || pSt->m_nTriggerCondition == TMT_MDSTATE_TIMEBINTRIGGER)
        {
            fTime += pSt->m_fTimeState + pSt->m_fTimeAfterTrigger + pSt->m_binOut[0].fTimeTrig;
        }
        else
        {
            fTime += TIME_MAX_WAITING + pSt->m_fTimeAfterTrigger + pSt->m_binOut[0].fTimeTrig;
        }
    }

    fTime *= (m_pStateTest->m_oStateParas.m_nRepeatNumbers + 1);
    fTime += TIME_ONLINE_DELAY;		//等待时间过长，给10s缓冲
    return fTime;
}

long CSttBinaryStateTest::CalReport(UINT nState)
{
    return 0;
}

void CSttBinaryStateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_BinaryStates(&m_pStateTest->m_oStateParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttBinaryStateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_nBinaryStateTestMode == 0)
	{
		m_pStateTest->m_oStateResults.m_nLoopIndex = m_nCurStateLoopIndex;
		stt_xml_serialize(&m_pStateTest->m_oStateResults, &m_pStateTest->m_oStateParas, m_pStateTest->m_oStateParas.m_nStateNumbers,
						  pXmlSerialize,m_pStateTest->m_oStateParas.m_nBinTripRef);
	}
	else
	{
		stt_xml_serialize(&m_oResults, pXmlSerialize);
	}
}

//2020-10-26  lijunqing
void CSttBinaryStateTest::Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_pStateTest->m_oStateParas, pXmlSerialize);
}

//2020-10-26  lijunqing
void CSttBinaryStateTest::Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_nBinaryStateTestMode == 0)
	{
		m_pStateTest->m_oStateResults.m_nLoopIndex = m_nCurStateLoopIndex;
		stt_xml_serialize(&m_pStateTest->m_oStateResults, &m_pStateTest->m_oStateParas, m_pStateTest->m_oStateParas.m_nStateNumbers,
						  pXmlSerialize,m_pStateTest->m_oStateParas.m_nBinTripRef);
	}
	else
	{
		stt_xml_serialize(&m_oResults, pXmlSerialize);
	}
}

long CSttBinaryStateTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttBinaryStateTest::Triger()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
#endif
}

void CSttBinaryStateTest::StartTest()
{
    CSttTestBase::StartTest();

    if(!GetTestStarting())
    {
        TtmToDrv();
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
		if(g_nBinaryStateTestMode == 0)
		{
        CSttDeviceBase::g_pSttDeviceBase->SetTestStart(BinaryStateTest);
		}
		else
		{
			CSttDeviceBase::g_pSttDeviceBase->SetTestStart(BinaryStateExTest);
		}
#endif
    }

    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttBinaryStateTest::StartTest >>>>>>");
}

void CSttBinaryStateTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StatePara(&m_pStateTest->m_oStateParas);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_BinaryStateItem(&m_pStateTest->m_oStateParas);
#endif
}
