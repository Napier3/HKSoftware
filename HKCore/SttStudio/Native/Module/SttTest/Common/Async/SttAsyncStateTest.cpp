#include "stdafx.h"
#include "SttAsyncStateTest.h"
#include "../SttSystemConfig.h"
#ifdef _PSX_QT_LINUX_
#include "QStringList"
#endif

CString CSttAsyncStateTest::m_strMacroName = "异步状态序列";
CString CSttAsyncStateTest::m_strMacroID = STT_MACRO_ID_AnsyncStateTest;
CString CSttAsyncStateTest::m_strFilePostFix = "stttst";
CString CSttAsyncStateTest::m_strMacroVer ="1.0";

CSttAsyncStateTest::CSttAsyncStateTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;
}

void CSttAsyncStateTest::Init()
{ 
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->InitAsyncState();
#endif
    CSttTestBase::Init();
    for(int i = 0;i < 10;i++)
    {
        m_oRstEval[i].m_bSelect = FALSE;
    }
    m_nCurStateIndex = 0;
}

CSttAsyncStateTest::~CSttAsyncStateTest(void)
{

}

void CSttAsyncStateTest::AfterSetParameter()
{
	if(g_pAsyncStateTest == NULL)
		return;

    float fOutputHoldTime;
    for(int nIndex = 0;nIndex<g_nStateCount;nIndex++)
    {
		if(!g_pAsyncStateTest->m_oStateAsyncParas.m_paraState[nIndex].m_bSelected)
            continue;

		g_pAsyncStateTest->m_oStateAsyncResults.m_resultState[nIndex].init();
		fOutputHoldTime = g_pAsyncStateTest->m_oStateAsyncParas.m_paraState[nIndex].m_fOutputHoldTime;
        if(fOutputHoldTime > 0)
			g_pAsyncStateTest->m_oStateAsyncParas.m_paraState[nIndex].m_binOut[0].fHoldTime = fOutputHoldTime;
	}

    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;

// #ifdef _PSX_QT_LINUX_
//     for(int i = 0;i < 10;i++)
//     {
// 		if(g_pAsyncStateTest->m_oStateAsyncParas.m_paraEstimates[i].m_bUseError)
//         {
//             m_oRstEval[i].m_bSelect = TRUE;
//         }
//         else
//         {
//             m_oRstEval[i].m_bSelect = FALSE;
//             continue;
//         }

//         QString strState,strBin,strVal;

// 		strState = g_pAsyncStateTest->m_oStateAsyncParas.m_paraEstimates[i].m_strTtripBegin_State;
//         if(strState == "BinTrig")
//         {
//             m_oRstEval[i].m_nBeginType = 0;
//         }
//         else if(strState.contains("_"))
//         {
//             strVal = strState.split("_")[1];
//             m_oRstEval[i].m_nBeginState = strVal.toInt();

// 			strBin = g_pAsyncStateTest->m_oStateAsyncParas.m_paraEstimates[i].m_strTtripBegin_Bin;
//             if(strBin.contains("$"))
//             {
//                 m_oRstEval[i].m_nBeginType = 2;
//                 strVal = strBin.split("$")[1];
//                 m_oRstEval[i].m_nBeginValue = strVal.toInt();
//                 strVal = strBin.split("$")[0];
//                 if(strVal.contains("_"))
//                 {
//                     strVal = strVal.split("_")[1];
//                     m_oRstEval[i].m_nBeginBin = strVal.toInt();
//                 }
//                 else
//                 {
//                     m_oRstEval[i].m_bSelect = FALSE;
//                 }
//             }
//             else
//             {
//                 m_oRstEval[i].m_nBeginType = 1;
//             }
//         }
//         else
//         {
//             m_oRstEval[i].m_bSelect = FALSE;
//         }

// 		strState = g_pAsyncStateTest->m_oStateAsyncParas.m_paraEstimates[i].m_strTtripEnd_State;
//         if(strState == "BinTrig")
//         {
//             m_oRstEval[i].m_nEndType = 0;
//         }
//         else if(strState.contains("_"))
//         {
//             strVal = strState.split("_")[1];
//             m_oRstEval[i].m_nEndState = strVal.toInt();

// 			strBin = g_pAsyncStateTest->m_oStateAsyncParas.m_paraEstimates[i].m_strTtripEnd_Bin;
//             if(strBin.contains("$"))
//             {
//                 m_oRstEval[i].m_nEndType = 2;
//                 strVal = strBin.split("$")[1];
//                 m_oRstEval[i].m_nEndValue = strVal.toInt();
//                 strVal = strBin.split("$")[0];
//                 if(strVal.contains("_"))
//                 {
//                     strVal = strVal.split("_")[1];
//                     m_oRstEval[i].m_nEndBin = strVal.toInt();
//                 }
//                 else
//                 {
//                     m_oRstEval[i].m_bSelect = FALSE;
//                 }
//             }
//             else
//             {
//                 m_oRstEval[i].m_nEndType = 1;
//             }
//         }
//         else
//         {
//             m_oRstEval[i].m_bSelect = FALSE;
//         }
//     }

//     State_EventRsts &oStateEvents = CSttDeviceBase::g_pSttDeviceBase->m_oStateEvents;
//     oStateEvents.m_nRstCnt = 0;

//     for (int i = 0;i < 10;i++)
//     {
//         tmt_StateRstEval &oRstEval = m_oRstEval[i];
//         if(oRstEval.m_bSelect)
//         {
//             BOOL bFind = FALSE;

//             for(int j = 0; j < oStateEvents.m_nRstCnt && j <= 20; j++)
//             {
//                 if(oRstEval.m_nBeginType == oStateEvents.m_oRst[j].m_nEventType)
//                 {
//                     switch(oRstEval.m_nBeginType)
//                     {
//                         case 1:
//                             if(oRstEval.m_nBeginState == oStateEvents.m_oRst[j].m_nStateIdx)
//                                 bFind = TRUE;
//                             break;
//                         case 2:
//                             if(oRstEval.m_nBeginState == oStateEvents.m_oRst[j].m_nStateIdx
//                                     && oRstEval.m_nBeginBin == oStateEvents.m_oRst[j].m_nBinIndex
//                                     && oRstEval.m_nBeginValue == oStateEvents.m_oRst[j].m_nBinValue)
//                                 bFind = TRUE;
//                             break;
//                     }
//                 }
//             }

//             if(!bFind)
//             {
//                 //添加
//                 long nIdx = oStateEvents.m_nRstCnt;

//                 if(nIdx >= 0 && nIdx < 20)
//                 {
//                     oStateEvents.m_oRst[nIdx].m_nEventType = oRstEval.m_nBeginType;
//                     oStateEvents.m_oRst[nIdx].m_nStateIdx = oRstEval.m_nBeginState;
//                     oStateEvents.m_oRst[nIdx].m_nBinIndex = oRstEval.m_nBeginBin;
//                     oStateEvents.m_oRst[nIdx].m_nBinValue = oRstEval.m_nBeginValue;
//                     oStateEvents.m_nRstCnt++;
//                 }
//             }

//             bFind = FALSE;

//             for(int j = 0; j < oStateEvents.m_nRstCnt && j <= 20; j++)
//             {
//                 if(oRstEval.m_nEndType == oStateEvents.m_oRst[j].m_nEventType)
//                 {
//                     switch(oRstEval.m_nEndType)
//                     {
//                         case 1:
//                             if(oRstEval.m_nEndState == oStateEvents.m_oRst[j].m_nStateIdx)
//                                 bFind = TRUE;
//                             break;
//                         case 2:
//                             if(oRstEval.m_nEndState == oStateEvents.m_oRst[j].m_nStateIdx
//                                     && oRstEval.m_nEndBin == oStateEvents.m_oRst[j].m_nBinIndex
//                                     && oRstEval.m_nEndValue == oStateEvents.m_oRst[j].m_nBinValue)
//                                 bFind = TRUE;
//                             break;
//                     }
//                 }
//             }

//             if(!bFind)
//             {
//                 //添加
//                 long nIdx = oStateEvents.m_nRstCnt;

//                 if(nIdx >= 0 && nIdx < 20)
//                 {
//                     oStateEvents.m_oRst[nIdx].m_nEventType = oRstEval.m_nEndType;
//                     oStateEvents.m_oRst[nIdx].m_nStateIdx = oRstEval.m_nEndState;
//                     oStateEvents.m_oRst[nIdx].m_nBinIndex = oRstEval.m_nEndBin;
//                     oStateEvents.m_oRst[nIdx].m_nBinValue = oRstEval.m_nEndValue;
//                     oStateEvents.m_nRstCnt++;
//                 }
//             }
//         }
//     }

// #endif
}

BOOL CSttAsyncStateTest::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

    BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->ProStateDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
    return bTestFinished;
}

double CSttAsyncStateTest::GetTestTimeLong()
{
    float	fTime = 0.000;
	if(g_pAsyncStateTest != NULL)
	{
		for (int i=0;i < g_nStateCount;i++)
		{
			tmt_AsyncStatePara *pSt = &g_pAsyncStateTest->m_oStateAsyncParas.m_paraState[i];
			if(!pSt->m_bSelected)
				continue;

			if (pSt->m_nTriggerCondition==TMT_MDSTATE_TIMETRIGGER || pSt->m_nTriggerCondition==TMT_MDSTATE_TIMEBINTRIGGER)
				fTime += pSt->m_fTimeState+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
			else
				fTime += TIME_MAX_WAITING+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
		}
	}

	// fTime *= (g_pAsyncStateTest->m_oStateAsyncParas.m_nRepeatNumbers+1);

    fTime += TIME_ONLINE_DELAY;		//等待时间过长，给10s缓冲

    return fTime;
}

long CSttAsyncStateTest::CalReport(UINT nState)
{
	if(g_pAsyncStateTest == NULL)
	{
		return 0;
	}

#ifdef _PSX_QT_LINUX_
    State_EventRsts &oStateEvents = CSttDeviceBase::g_pSttDeviceBase->m_oStateEvents;
    double fBegin, fEnd;
    BOOL bFind = FALSE;

    for(int i = 0; i < 10; i++)
    {
		g_pAsyncStateTest->m_oStateAsyncResults.m_resultEstimates[i].m_fTtrip = 0;
        tmt_StateRstEval &oRstEval = m_oRstEval[i];
        if(oRstEval.m_bSelect)
        {
            int nBinTrigState = -1;
            fBegin = fEnd = -1;
            bFind = FALSE;

            for(int j = 0; j < oStateEvents.m_nRstCnt && j <= 20; j++)
            {
                if(!oStateEvents.m_oRst[j].m_bUsed)
                {
                    continue;
                }

                if(oRstEval.m_nBeginType == oStateEvents.m_oRst[j].m_nEventType)
                {
                    switch(oRstEval.m_nBeginType)
                    {
                        case 0://开入量触发
                        {
                            if(oStateEvents.m_nBinTripCnt > 0)
                            {
                                bFind = TRUE;
                                fBegin = oStateEvents.m_oBinTripRst[0].m_dEventTime;
                                nBinTrigState = oStateEvents.m_oRst[j].m_nStateIdx;

                                if(nBinTrigState > -1 && nBinTrigState < g_nStateCount)
                                {
									fBegin -= g_pAsyncStateTest->m_oStateAsyncParas.m_paraState[nBinTrigState].m_fTimeAfterTrigger;
                                }
                            }
                        }
                        break;
                        case 1://状态进入
                            if(oRstEval.m_nBeginState == oStateEvents.m_oRst[j].m_nStateIdx)
                            {
                                bFind = TRUE;
                                fBegin = oStateEvents.m_oRst[j].m_dEventTime;
                            }

                            break;
                        case 2://状态内开入变位
                            if(oRstEval.m_nBeginState == oStateEvents.m_oRst[j].m_nStateIdx
                                    && oRstEval.m_nBeginBin == oStateEvents.m_oRst[j].m_nBinIndex
                                    && oRstEval.m_nBeginValue == oStateEvents.m_oRst[j].m_nBinValue)
                            {
                                bFind = TRUE;
                                fBegin = oStateEvents.m_oRst[j].m_dEventTime;
                            }

                            break;
                    }
				}

                if(bFind)
                {
                    break;
                }
            }

            if(fBegin < 0)
            {
                continue;
            }

            bFind = FALSE;

            for(int j = 0; j < oStateEvents.m_nRstCnt && j <= 20; j++)
            {
                if(!oStateEvents.m_oRst[j].m_bUsed)
                {
                    continue;
                }

                if(oRstEval.m_nEndType == oStateEvents.m_oRst[j].m_nEventType)
                {
                    switch(oRstEval.m_nEndType)
                    {
                        case 0:
                        {
                            for(int k = 0; k < oStateEvents.m_nBinTripCnt && k <= 20; k++)
                            {
                                if(oStateEvents.m_oBinTripRst[k].m_dEventTime > fBegin)
                                {
                                    bFind = TRUE;
                                    fEnd = oStateEvents.m_oBinTripRst[k].m_dEventTime;
                                    nBinTrigState = oStateEvents.m_oBinTripRst[k].m_nStateIdx;

                                    if(nBinTrigState > -1 && nBinTrigState < g_nStateCount)
                                    {
										fEnd -= g_pAsyncStateTest->m_oStateAsyncParas.m_paraState[nBinTrigState].m_fTimeAfterTrigger;
                                    }

                                    break;
                                }
                            }
                        }
                        break;
                        case 1:
                            if(oRstEval.m_nEndState == oStateEvents.m_oRst[j].m_nStateIdx)
                            {
                                bFind = TRUE;
                                fEnd = oStateEvents.m_oRst[j].m_dEventTime;
                            }

                            break;
                        case 2:
                            if(oRstEval.m_nEndState == oStateEvents.m_oRst[j].m_nStateIdx
                                    && oRstEval.m_nEndBin == oStateEvents.m_oRst[j].m_nBinIndex
                                    && oRstEval.m_nEndValue == oStateEvents.m_oRst[j].m_nBinValue)
                            {
                                bFind = TRUE;
                                fEnd = oStateEvents.m_oRst[j].m_dEventTime;
                            }

                            break;
                    }
                }

                if(bFind)
                {
                    break;
                }
            }

            double fDiff = fEnd - fBegin;

            if(fDiff > 0.0009)
            {
				g_pAsyncStateTest->m_oStateAsyncResults.m_resultEstimates[i].m_fTtrip = fDiff;
            }
        }
    }

#endif
    return 0;
}

void CSttAsyncStateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_pAsyncStateTest != NULL)
	{
		stt_xml_serialize(&g_pAsyncStateTest->m_oStateAsyncParas,pXmlSerialize);

		//2020-4-6  lijq  读取参数模式下，需要进行初始化
		if (stt_xml_serialize_is_read(pXmlSerialize))
		{
			AfterSetParameter();
		}
	}
}

//2020-10-26  lijunqing
void CSttAsyncStateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_pAsyncStateTest != NULL)
	{
		g_pAsyncStateTest->m_oStateAsyncResults.m_nLoopIndex = m_nCurStateLoopIndex;
		stt_xml_serialize(&g_pAsyncStateTest->m_oStateAsyncResults, &g_pAsyncStateTest->m_oStateAsyncParas,g_pAsyncStateTest->m_oStateAsyncParas.m_nStateNumbers,
						  pXmlSerialize,g_pAsyncStateTest->m_oStateAsyncParas.m_nBinTripRef);
	}
}


//2020-10-26  lijunqing
void CSttAsyncStateTest::Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_pAsyncStateTest != NULL)
	{
		stt_xml_serialize(&g_pAsyncStateTest->m_oStateAsyncParas,pXmlSerialize);
	}
}

//2020-10-26  lijunqing
void CSttAsyncStateTest::Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_pAsyncStateTest != NULL)
	{
		g_pAsyncStateTest->m_oStateAsyncResults.m_nLoopIndex = m_nCurStateLoopIndex;
		stt_xml_serialize(&g_pAsyncStateTest->m_oStateAsyncResults, &g_pAsyncStateTest->m_oStateAsyncParas, g_pAsyncStateTest->m_oStateAsyncParas.m_nStateNumbers,
						  pXmlSerialize,g_pAsyncStateTest->m_oStateAsyncParas.m_nBinTripRef);
	}
}

void CSttAsyncStateTest:: InitStateLoopResults()
{
	if(g_pAsyncStateTest != NULL)
	{
		g_pAsyncStateTest->m_oStateAsyncResults.init(g_nStateCount);
	}
}

long CSttAsyncStateTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttAsyncStateTest::Triger()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
#endif
}

void CSttAsyncStateTest::StartTest()
{
    if(GetTestStarting())
    {
        //仅状态序列实验有可能会多次StartTest
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        CSttTestBase::Stop();
		CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttAsyncStateTest is  Running,do CSttTestBase::Stop()");
    }

    CSttTestBase::StartTest();
    TtmToDrv();
	if(g_pAsyncStateTest != NULL && g_pAsyncStateTest->m_oStateAsyncParas.m_nStateNumbers == 0)
	{
		return;
	}
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
    SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(StateTest);
#endif
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttAsyncStateTest::StartTest >>>>>>");
}

void CSttAsyncStateTest::Stop()
{
	CSttTestBase::Stop();
}

void CSttAsyncStateTest::TtmToDrv()
{
	if(g_pAsyncStateTest != NULL)
	{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_AsyncStatePara(&g_pAsyncStateTest->m_oStateAsyncParas);
	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_AsyncStateItem(&g_pAsyncStateTest->m_oStateAsyncParas);
#endif
	}
}

void CSttAsyncStateTest::ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType)
{

}

void CSttAsyncStateTest::SyncSingleStateTmtResult()
{
	if(g_pAsyncStateTest == NULL)
	{
		return;
	}

	if(m_nCurStateIndex >= 0 && m_nCurStateIndex < g_pAsyncStateTest->m_oStateAsyncParas.m_nStateNumbers)
    {

    }
    else
    {
#ifdef _PSX_QT_LINUX_
        for(int i=0; i<MAX_BINARYIN_COUNT; i++)
        {
			g_pAsyncStateTest->m_oStateAsyncResults.m_nBinRefState[i] =
                CSttDeviceBase::g_pSttDeviceBase->m_nBinRefState[i];
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
			g_pAsyncStateTest->m_oStateAsyncResults.m_nBinExRefState[i] =
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

	tmt_AsyncStateResult  &oResultState = g_pAsyncStateTest->m_oStateAsyncResults.m_resultState[nStateNum];
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
