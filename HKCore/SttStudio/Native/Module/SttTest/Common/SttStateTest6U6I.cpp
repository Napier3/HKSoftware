#include "stdafx.h"
#include"SttStateTest.h"
#include "SttSystemConfig.h"

CString CSttStateTest::m_strMacroName = "状态序列测试";
CString CSttStateTest::m_strMacroID = STT_MACRO_ID_StateTest;
CString CSttStateTest::m_strFilePostFix = "stttst";
CString CSttStateTest::m_strMacroVer ="1.0";

CSttStateTest::CSttStateTest() : CSttTestBase()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;

    m_pStateTest = stt_test_get_base_statetest_buff();
}

void CSttStateTest::Init()
{ 
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.init(g_nStateCount);
    m_pStateTest->m_oStateResults.init(g_nStateCount);
    CSttTestBase::Init();
    m_nCurStateIndex = 0;
}

long CSttStateTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    //qDebug()<<("CommReadResult(CSttStateTest)");
    //lijq 2020-3-28
    //	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(CSttStateTest)") );

    //#ifdef _PSX_QT_LINUX_
    //	int nRet =CSttDeviceBase::g_pSttDeviceBase->GetTestResult(StateResult,(char*)&m_oDrvResults);
    //	if(nRet == -1)
    //		return false;
    //#endif

    //	if(m_oDrvResults.nCount<=0)//结果数量为空时，直接返回
    //	{
    //		//qDebug()<<("CommReadResult(m_oDrvResults.cnt<=0)");
    //		//lijq 2020-3-28
    //		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(m_oDrvResults.cnt<=0)") );
    //		return 0;
    //	}

    //	UINT nBinOrg=0xFF;

    //	for (int n=0; n<m_oDrvResults.nCount; n++)
    //	{
    //		int nSec=m_oDrvResults.stResult[n].nSec;
    //		int nNanoSec=m_oDrvResults.stResult[n].nNanoSec;

    //		if(m_oDrvResults.stResult[n].currentIndex >= m_oStateParas.m_nStateNumbers)//当前状态号大于设置的总状态数时，返回
    //		{
    //			//qDebug()<<("CommReadResult(m_oDrvResults.result[n].from >= m_nStateNumbers)");
    //			//lijq 2020-3-28
    //			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(m_oDrvResults.result[n].from >= m_nStateNumbers)") );
    //			Stop();
    //			break;
    //		}

    //		switch(m_oDrvResults.stResult[n].nType)
    //		{
    //		case STATE_RESULT_START:
    //		{//开始测试时，初始化开始测试时间，状态号，开入量
    //			m_uStartTimeS = nSec;
    //			m_uStartTimeNS = nNanoSec;
    //			m_oStateResults.m_resultState[0].m_frTimeStateBegin  = 0;
    //			m_nCurStateIndex = 0;
    //			nBinOrg = m_oDrvResults.stResult[n].nInput;
    //		}
    //			break;
    //		case STATE_RESULT_CHANGE:
    //		{//状态改变时记录状态号，相对第一个状态的相对时间
    //			m_nCurStateIndex = m_oDrvResults.stResult[n].nObjective;
    //			m_oStateResults.m_resultState[m_nCurStateIndex].m_frTimeStateBegin = GetTimeFromLong(m_oDrvResults.stResult[n].nSec-m_uStartTimeS,m_oDrvResults.stResult[n].nNanoSec-m_uStartTimeNS);
    //			nBinOrg = m_oDrvResults.stResult[n].nInput;
    //			//qDebug()<<("CommReadResult(type == STATE_TYPE_CHANGE)");
    //			//lijq 2020-3-28
    //			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("") );

    //		}
    //			break;
    //		case STATE_RESULT_DI_CHANGE:
    //		{//开入变位时，记录所有的产生变位的结果记录
    //			int nBin = nBinOrg^m_oDrvResults.stResult[n].nInput;//取异或
    //			//qDebug()<<("CommReadResult(type == STATE_TYPE_DI_CHANGE)");
    //			//lijq 2020-3-28
    //			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(type == STATE_TYPE_DI_CHANGE)") );

    //			for (int i=0;i<MAX_BINARYIN_COUNT;i++)
    //			{
    //				if (((nBin>>i)&0x01) > 0)
    //				{
    //					m_oStateResults.m_resultState[m_nCurStateIndex].m_frTimeBinAct[i][m_oStateResults.m_resultState[m_nCurStateIndex].m_nrBinSwitchCount[i]] =
    //							GetTimeFromLong((nSec-m_uStartTimeS),(nNanoSec-m_uStartTimeNS))-m_oStateResults.m_resultState[m_nCurStateIndex].m_frTimeStateBegin;//xupf 20190717 修改纳秒级的计算
    //					m_oStateResults.m_resultState[m_nCurStateIndex].m_nrBinSwitchCount[i]++;
    //				}
    //			}

    //			nBinOrg = m_oDrvResults.stResult[n].nInput;
    //		}
    //			break;
    //		case STATE_RESULT_STOP:
    //		{
    //			//StopTest();
    //			//qDebug()<<("CommReadResult(type == STATE_TYPE_STOP)");
    //			//lijq 2020-3-28
    //			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommReadResult(type == STATE_TYPE_STOP)") );

    //			bFinish = true;
    //		}
    //			break;
    //		}
    //	}

    return true;
}

CSttStateTest::~CSttStateTest(void)
{

}

void CSttStateTest::AfterSetParameter()
{
    float fOutputHoldTime;
    for(int nIndex = 0;nIndex<m_pStateTest->m_oStateParas.m_nStateNumbers;nIndex++)
    {
        m_pStateTest->m_oStateResults.m_resultState[nIndex].init();
        fOutputHoldTime = m_pStateTest->m_oStateParas.m_paraState[nIndex].m_fOutputHoldTime;
        if(fOutputHoldTime > 0)
            m_pStateTest->m_oStateParas.m_paraState[nIndex].m_binOut[0].fHoldTime = fOutputHoldTime;
    }

    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

BOOL CSttStateTest::EventProcess()
{
    if(!GetTestStarting())
        return FALSE;

    BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->ProStateDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
    return bTestFinished;
}

double CSttStateTest::GetTestTimeLong()
{
    float	fTime = 0.000;
    for (int i=0;i<m_pStateTest->m_oStateParas.m_nStateNumbers;i++)
    {
        tmt_state_para *pSt = &m_pStateTest->m_oStateParas.m_paraState[i];
        if (pSt->m_nTriggerCondition==TMT_MDSTATE_TIMETRIGGER || pSt->m_nTriggerCondition==TMT_MDSTATE_TIMEBINTRIGGER)
            fTime += pSt->m_fTimeState+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
        else
            fTime += TIME_MAX_WAITING+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
    }

    fTime *= (m_pStateTest->m_oStateParas.m_nRepeatNumbers+1);

    fTime += TIME_ONLINE_DELAY;		//等待时间过长，给10s缓冲

    return fTime;
}

long CSttStateTest::CalReport(UINT nState)
{
    return 0;
}

void CSttStateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_pStateTest->m_oStateParas,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttStateTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_pStateTest->m_oStateResults, m_pStateTest->m_oStateParas.m_nStateNumbers,
                      pXmlSerialize,m_pStateTest->m_oStateParas.m_nBinTripRef);
}


//2020-10-26  lijunqing
void CSttStateTest::Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_pStateTest->m_oStateParas,pXmlSerialize);
}

//2020-10-26  lijunqing
void CSttStateTest::Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_pStateTest->m_oStateResults, m_pStateTest->m_oStateParas.m_nStateNumbers,
                      pXmlSerialize,m_pStateTest->m_oStateParas.m_nBinTripRef);
}


long CSttStateTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttStateTest::Triger()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
#endif
}

void CSttStateTest::StartTest()
{	
    if(GetTestStarting())
    {
        //仅状态序列实验有可能会多次StartTest
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        SetRecvStopCmd(TRUE);
        CSttTestBase::Stop();
        CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttStateTest is  Running,do CSttTestBase::Stop()");
    }

    CSttTestBase::StartTest();
    TtmToDrv();
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
    SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(StateTest);
#endif
    CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttStateTest::StartTest >>>>>>");
}

void CSttStateTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StatePara(&m_pStateTest->m_oStateParas);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(&m_pStateTest->m_oStateParas);
#endif
}

void CSttStateTest::ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType)
{
#ifdef _PSX_QT_LINUX_
    if(nState>=0&&nState<m_pStateTest->m_oStateParas.m_nStateNumbers)
    {
        STT_RTDATA_EVENT oRtdata;
        oRtdata.oTime.dTime=dTime1;
        oRtdata.oTime.dRealTime=dTime2;
        oRtdata.m_nVolChCount=0;
        oRtdata.m_nCurChCount=0;
        float fVal,fPreVal;
        int nRtIndex=0;
        float fStart,fEnd,fStep;
        BOOL bNeedUpdate;

        tmt_StatePara   oparaState=m_pStateTest->m_oStateParas.m_paraState[nState];
        for(int nIndex=0;nIndex<g_nRtDataVoltCnt;nIndex++)
        {
            bNeedUpdate = FALSE;
            tmt_channel &uiVOL=oparaState.m_uiVOL[nIndex];
            nRtIndex=oRtdata.m_nVolChCount;
            oRtdata.m_oVolCh[nRtIndex].m_nIndex=nIndex;            

            if(nType == 0)
            {
                //实验开始态
                fVal=fabs(uiVOL.Harm[1].fAmp);
                oRtdata.m_oVolCh[nRtIndex].m_nMag=fVal*Ratio_float_long;
                oRtdata.m_oVolCh[nRtIndex].m_nAng=
                        oparaState.m_uiVOL[nIndex].Harm[1].fAngle*Ratio_float_long;
                oRtdata.m_oVolCh[nRtIndex].m_nFreq=
                        oparaState.m_uiVOL[nIndex].Harm[1].fFreq*Ratio_float_long;
                oRtdata.m_nVolChCount++;
            }
            else if(nType == 1)
            {
                if(nState == 0)
                {
                    //循环后第一态
                    fVal=fabs(uiVOL.Harm[1].fAmp);
                    oRtdata.m_oVolCh[nRtIndex].m_nMag=fVal*Ratio_float_long;
                    oRtdata.m_oVolCh[nRtIndex].m_nAng=
                            oparaState.m_uiVOL[nIndex].Harm[1].fAngle*Ratio_float_long;
                    oRtdata.m_oVolCh[nRtIndex].m_nFreq=
                            oparaState.m_uiVOL[nIndex].Harm[1].fFreq*Ratio_float_long;
                    oRtdata.m_nVolChCount++;
                }
                else
                {
                    tmt_StatePara   oparaPreState = m_pStateTest->m_oStateParas.m_paraState[nState-1];
                    tmt_channel &PreuiVOL = oparaPreState.m_uiVOL[nIndex];

                    //状态切换
                    if(PreuiVOL.Ramp[0].nIndex > -1 || PreuiVOL.Ramp[1].nIndex > -1 || PreuiVOL.Ramp[2].nIndex == 1)
                    {
                        fVal=fabs(uiVOL.Harm[1].fAmp);
                        oRtdata.m_oVolCh[nRtIndex].m_nMag=fVal*Ratio_float_long;
                        oRtdata.m_oVolCh[nRtIndex].m_nAng=
                                oparaState.m_uiVOL[nIndex].Harm[1].fAngle*Ratio_float_long;
                        oRtdata.m_oVolCh[nRtIndex].m_nFreq=
                                oparaState.m_uiVOL[nIndex].Harm[1].fFreq*Ratio_float_long;
                        oRtdata.m_nVolChCount++;
                    }
                    else
                    {
                        fVal=fabs(uiVOL.Harm[1].fAmp);
                        fPreVal = fabs(PreuiVOL.Harm[1].fAmp);
                        if(fabs(fPreVal - fVal) > EPSINON)
                        {
                            bNeedUpdate = TRUE;
                        }

                        if(!bNeedUpdate)
                        {
                            fVal=uiVOL.Harm[1].fAngle;
                            fPreVal = PreuiVOL.Harm[1].fAngle;
                            if(fabs(fPreVal - fVal) > EPSINON)
                            {
                                bNeedUpdate = TRUE;
                            }
                        }

                        if(!bNeedUpdate)
                        {
                            fVal=uiVOL.Harm[1].fFreq;
                            fPreVal = PreuiVOL.Harm[1].fFreq;
                            if(fabs(fPreVal - fVal) > EPSINON)
                            {
                                bNeedUpdate = TRUE;
                            }
                        }

                        if(bNeedUpdate)
                        {
                            fVal=fabs(uiVOL.Harm[1].fAmp);
                            oRtdata.m_oVolCh[nRtIndex].m_nMag=fVal*Ratio_float_long;
                            oRtdata.m_oVolCh[nRtIndex].m_nAng=
                                    oparaState.m_uiVOL[nIndex].Harm[1].fAngle*Ratio_float_long;
                            oRtdata.m_oVolCh[nRtIndex].m_nFreq=
                                    oparaState.m_uiVOL[nIndex].Harm[1].fFreq*Ratio_float_long;
                            oRtdata.m_nVolChCount++;
                        }
                    }
                }
            }
            else
            {
                oRtdata.m_oVolCh[nRtIndex].m_nMag=fabs(uiVOL.Harm[1].fAmp)*Ratio_float_long;
                oRtdata.m_oVolCh[nRtIndex].m_nAng=uiVOL.Harm[1].fAngle*Ratio_float_long;
                oRtdata.m_oVolCh[nRtIndex].m_nFreq=fabs(uiVOL.Harm[1].fFreq)*Ratio_float_long;

                //递变
                if(uiVOL.Ramp[0].nIndex > -1)
                {
                    fStart=fabs(uiVOL.Harm[1].fAmp);
                    fEnd=fabs(uiVOL.Ramp[0].fEnd);
                    fStep=fabs(uiVOL.Ramp[0].fStep);

                    if(fStart > fEnd)
                    {
                        fStep = fStep*(-1);
                        fVal=fStart + fStep*nStep;
                        if(fVal < fEnd)
                            fVal = fEnd;
                    }
                    else
                    {
                        fVal=fStart + fStep*nStep;

                        if(fVal > fEnd)
                            fVal = fEnd;
                    }

                    oRtdata.m_oVolCh[nRtIndex].m_nMag=fVal*Ratio_float_long;

                    bNeedUpdate = TRUE;
                }

                if(uiVOL.Ramp[1].nIndex > -1)
                {
                    fStart=uiVOL.Harm[1].fAngle;
                    fEnd=uiVOL.Ramp[1].fEnd;
                    fStep=fabs(uiVOL.Ramp[1].fStep);

                    if(fStart > fEnd)
                    {
                        fStep = fStep*(-1);
                        fVal=fStart + fStep*nStep;

                        if(fVal < fEnd)
                            fVal = fEnd;
                    }
                    else
                    {
                        fVal=fStart + fStep*nStep;

                        if(fVal > fEnd)
                            fVal = fEnd;
                    }

                    oRtdata.m_oVolCh[nRtIndex].m_nAng=fVal*Ratio_float_long;

                    bNeedUpdate = TRUE;
                }

                if(uiVOL.Ramp[2].nIndex == 1)
                {
                    fStart=fabs(uiVOL.Harm[1].fFreq);
                    fEnd=fabs(uiVOL.Ramp[2].fEnd);
                    fStep=fabs(uiVOL.Ramp[2].fStep);

                    if(fStart > fEnd)
                    {
                        fStep = fStep*(-1);
                        fVal=fStart + fStep*nStep;

                        if(fVal < fEnd)
                            fVal = fEnd;
                    }
                    else
                    {
                        fVal=fStart + fStep*nStep;

                        if(fVal > fEnd)
                            fVal = fEnd;
                    }

                    oRtdata.m_oVolCh[nRtIndex].m_nFreq=fVal*Ratio_float_long;

                    bNeedUpdate = TRUE;
                }

                if(bNeedUpdate && nStep > -1)
                    oRtdata.m_nVolChCount++;
            }
        }

        for(int nIndex=0;nIndex<g_nRtDataCurrCnt;nIndex++)
        {
            bNeedUpdate = FALSE;
            tmt_channel &uiCUR=oparaState.m_uiCUR[nIndex];
            nRtIndex=oRtdata.m_nCurChCount;
            oRtdata.m_oCurCh[nRtIndex].m_nIndex=nIndex;            

            if(nType == 0)
            {
                //实验开始态
                fVal=fabs(uiCUR.Harm[1].fAmp);
                oRtdata.m_oCurCh[nRtIndex].m_nMag=fVal*Ratio_float_long;
                oRtdata.m_oCurCh[nRtIndex].m_nAng=
                        oparaState.m_uiCUR[nIndex].Harm[1].fAngle*Ratio_float_long;
                oRtdata.m_oCurCh[nRtIndex].m_nFreq=
                        oparaState.m_uiCUR[nIndex].Harm[1].fFreq*Ratio_float_long;
                oRtdata.m_nCurChCount++;
            }
            else if(nType == 1)
            {
                if(nState == 0)
                {
                    //循环后第一态
                    fVal=fabs(uiCUR.Harm[1].fAmp);
                    oRtdata.m_oCurCh[nRtIndex].m_nMag=fVal*Ratio_float_long;
                    oRtdata.m_oCurCh[nRtIndex].m_nAng=
                            oparaState.m_uiCUR[nIndex].Harm[1].fAngle*Ratio_float_long;
                    oRtdata.m_oCurCh[nRtIndex].m_nFreq=
                            oparaState.m_uiCUR[nIndex].Harm[1].fFreq*Ratio_float_long;
                    oRtdata.m_nCurChCount++;
                }
                else
                {
                    tmt_StatePara   oparaPreState = m_pStateTest->m_oStateParas.m_paraState[nState-1];
                    tmt_channel &PreuiCUR = oparaPreState.m_uiCUR[nIndex];

                    //状态切换
                    if(PreuiCUR.Ramp[0].nIndex > -1 || PreuiCUR.Ramp[1].nIndex > -1 || PreuiCUR.Ramp[2].nIndex == 1)
                    {
                        fVal=fabs(uiCUR.Harm[1].fAmp);
                        oRtdata.m_oCurCh[nRtIndex].m_nMag=fVal*Ratio_float_long;
                        oRtdata.m_oCurCh[nRtIndex].m_nAng=
                                oparaState.m_uiCUR[nIndex].Harm[1].fAngle*Ratio_float_long;
                        oRtdata.m_oCurCh[nRtIndex].m_nFreq=
                                oparaState.m_uiCUR[nIndex].Harm[1].fFreq*Ratio_float_long;
                        oRtdata.m_nCurChCount++;
                    }
                    else
                    {
                        fVal=fabs(uiCUR.Harm[1].fAmp);
                        fPreVal = fabs(PreuiCUR.Harm[1].fAmp);
                        if(fabs(fPreVal - fVal) > EPSINON)
                        {
                            bNeedUpdate = TRUE;
                        }

                        if(!bNeedUpdate)
                        {
                            fVal=uiCUR.Harm[1].fAngle;
                            fPreVal = PreuiCUR.Harm[1].fAngle;
                            if(fabs(fPreVal - fVal) > EPSINON)
                            {
                                bNeedUpdate = TRUE;
                            }
                        }

                        if(!bNeedUpdate)
                        {
                            fVal=uiCUR.Harm[1].fFreq;
                            fPreVal = PreuiCUR.Harm[1].fFreq;
                            if(fabs(fPreVal - fVal) > EPSINON)
                            {
                                bNeedUpdate = TRUE;
                            }
                        }

                        if(bNeedUpdate)
                        {
                            fVal=fabs(uiCUR.Harm[1].fAmp);
                            oRtdata.m_oCurCh[nRtIndex].m_nMag=fVal*Ratio_float_long;
                            oRtdata.m_oCurCh[nRtIndex].m_nAng=
                                    oparaState.m_uiCUR[nIndex].Harm[1].fAngle*Ratio_float_long;
                            oRtdata.m_oCurCh[nRtIndex].m_nFreq=
                                    oparaState.m_uiCUR[nIndex].Harm[1].fFreq*Ratio_float_long;
                            oRtdata.m_nCurChCount++;
                        }
                    }
                }
            }
            else
            {
                oRtdata.m_oCurCh[nRtIndex].m_nMag=fabs(uiCUR.Harm[1].fAmp)*Ratio_float_long;
                oRtdata.m_oCurCh[nRtIndex].m_nAng=uiCUR.Harm[1].fAngle*Ratio_float_long;
                oRtdata.m_oCurCh[nRtIndex].m_nFreq=fabs(uiCUR.Harm[1].fFreq)*Ratio_float_long;

                //递变
                if(uiCUR.Ramp[0].nIndex > -1)
                {
                    fStart=fabs(uiCUR.Harm[1].fAmp);
                    fEnd=fabs(uiCUR.Ramp[0].fEnd);
                    fStep=fabs(uiCUR.Ramp[0].fStep);

                    if(fStart > fEnd)
                    {
                        fStep = fStep*(-1);
                        fVal=fStart + fStep*nStep;

                        if(fVal < fEnd)
                            fVal = fEnd;
                    }
                    else
                    {
                        fVal=fStart + fStep*nStep;

                        if(fVal > fEnd)
                            fVal = fEnd;
                    }

                    oRtdata.m_oCurCh[nRtIndex].m_nMag=fVal*Ratio_float_long;

                    bNeedUpdate = TRUE;
                    CSttDeviceBase::g_pSttDeviceBase->SetCurrAmp_Monitor(nIndex,oRtdata.m_oCurCh[nRtIndex].m_nMag*Ratio_long_float);
                }

                if(uiCUR.Ramp[1].nIndex > -1)
                {
                    fStart=uiCUR.Harm[1].fAngle;
                    fEnd=uiCUR.Ramp[1].fEnd;
                    fStep=fabs(uiCUR.Ramp[1].fStep);

                    if(fStart > fEnd)
                    {
                        fStep = fStep*(-1);
                        fVal=fStart + fStep*nStep;

                        if(fVal < fEnd)
                            fVal = fEnd;
                    }
                    else
                    {
                        fVal=fStart + fStep*nStep;

                        if(fVal > fEnd)
                            fVal = fEnd;
                    }

                    oRtdata.m_oCurCh[nRtIndex].m_nAng=fVal*Ratio_float_long;

                    bNeedUpdate = TRUE;
                }

                if(uiCUR.Ramp[2].nIndex == 1)
                {
                    fStart=fabs(uiCUR.Harm[1].fFreq);
                    fEnd=fabs(uiCUR.Ramp[2].fEnd);
                    fStep=fabs(uiCUR.Ramp[2].fStep);

                    if(fStart > fEnd)
                    {
                        fStep = fStep*(-1);
                        fVal=fStart + fStep*nStep;

                        if(fVal < fEnd)
                            fVal = fEnd;
                    }
                    else
                    {
                        fVal=fStart + fStep*nStep;

                        if(fVal > fEnd)
                            fVal = fEnd;
                    }

                    oRtdata.m_oCurCh[nRtIndex].m_nFreq=fVal*Ratio_float_long;

                    bNeedUpdate = TRUE;
                }

                if(bNeedUpdate && nStep > -1)
                    oRtdata.m_nCurChCount++;
            }
        }

        if(oRtdata.m_nCurChCount>0||oRtdata.m_nVolChCount>0)
            stt_add_rtdatas(oRtdata);
    }
#endif	
}

void CSttStateTest::SyncSingleStateTmtResult()
{
    if(m_nCurStateIndex>=0&&m_nCurStateIndex<m_pStateTest->m_oStateParas.m_nStateNumbers)
    {

    }
    else
        return;

    tmt_StateResult  &oResultState=m_pStateTest->m_oStateResults.m_resultState[m_nCurStateIndex];
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;

    oResultState.m_nAct = oRampRestCom.m_nAct;//开入量触发翻转,则该标记置为1;有开入变位,但是实际为时间触发进入下一个状态时,该标记仍为0,
    oResultState.m_frTestTime=oRampRestCom.m_fTripTime;
    oResultState.m_nCurStepIndex = oRampRestCom.m_nTripStep;

    int nrBinSwitchCount,nrBinExSwitchCount;
    for(int i=0; i<MAX_BINARYIN_COUNT; i++)
    {
        nrBinSwitchCount=oRampRestCom.m_nrBinSwitchCount[i];
        oResultState.m_nrBinSwitchCount[i]=nrBinSwitchCount;
        for(int j=0; j<nrBinSwitchCount; j++)
        {
            oResultState.m_frTimeBinAct[i][j]=oRampRestCom.m_frTimeBinAct[i][j];
        }
        oResultState.m_nBinInitState[i]=oRampRestCom.m_nBinInitState[i];
        oResultState.m_nRampIndex[i]=oRampRestCom.m_nRampIndex[i];
    }

    SwitchModules oSwitchModules=CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
    for(int i=0; i<oSwitchModules.m_nModulesBiCount; i++)
    {
        nrBinExSwitchCount=oRampRestCom.m_nrBinExSwitchCount[i];
        oResultState.m_nrBinExSwitchCount[i]=nrBinExSwitchCount;
        for(int j=0; j<nrBinExSwitchCount; j++)
        {
            oResultState.m_frTimeBinExAct[i][j]=oRampRestCom.m_frTimeBinExAct[i][j];
        }
        oResultState.m_nBinExInitState[i]=oRampRestCom.m_nBinExInitState[i];
        oResultState.m_nRampIndexEx[i]=oRampRestCom.m_nRampIndexEx[i];
    }

    oResultState.m_frInTime=oRampRestCom.m_frInTime;
    oResultState.m_frTimeStateBegin=oRampRestCom.m_frTimeStateBegin;
#endif
}

void CSttStateTest::SetStateBout(tmt_BinaryOut *pStateBinaryOut,tmt_BinaryOut *pBinaryOut,long nBoutCount)
{
    for (int nIndex = 0;nIndex<nBoutCount;nIndex++)
    {
        pStateBinaryOut[nIndex] = pBinaryOut[nIndex];
    }
}

void CSttStateTest::Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if (g_theSystemConfig->m_nHasDigital)
    {
        stt_xml_serialize(m_pStateTest->m_oStateParas.m_paraState[0].m_oGoosePub,pXmlSerialize);//获取Gout信息,放入第一个状态的Gout中

        for (int nStateIndex = 1;nStateIndex<m_pStateTest->m_oStateParas.m_nStateNumbers;nStateIndex++)
        {
            for(int nIndexCB = 0;nIndexCB<MAX_MODULES_GOOSEPUB_COUNT;nIndexCB++)
                m_pStateTest->m_oStateParas.m_paraState[0].m_oGoosePub[nIndexCB].CopyOwn(
                            &m_pStateTest->m_oStateParas.m_paraState[nStateIndex].m_oGoosePub[nIndexCB]);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Global_SetStateUIFromCpl(tmt_StatePara *pStatePara,Complex *pVol_Complex,Complex *pCur_Complex)
{
    for (int j=0;j<3;j++)
    {
        pStatePara->m_uiVOL[j].Harm[1].fAmp = (float)pVol_Complex[j].norm();
        pStatePara->m_uiVOL[j].Harm[1].fAngle = (float)pVol_Complex[j].arg();
        pStatePara->m_uiCUR[j].Harm[1].fAmp = (float)pCur_Complex[j].norm();
        pStatePara->m_uiCUR[j].Harm[1].fAngle = (float)pCur_Complex[j].arg();
    }

    pStatePara->m_uiVOL[3].Harm[1].fAmp = (float)pVol_Complex[3].norm();
    pStatePara->m_uiVOL[3].Harm[1].fAngle = (float)pVol_Complex[3].arg();
}

void Global_SetStateBinPreFault(tmt_StatePara *pStatePara)
{
    pStatePara->m_nBinLogic = TMT_BINLOGIC_OR;//缺省为或逻辑

    for (int nIndex = 0;nIndex<8;nIndex++)
    {
        pStatePara->m_binIn[nIndex].nSelect = 1;
    }
}

void Global_SetStateBoutPreFault(tmt_StatePara *pStatePara,long *pnStateBOut,long nOutputSwitchMode,float fBoutTimeTrig,float fBoutHoldTime)
{
    for (int nIndex = 0;nIndex<8;nIndex++)
    {
        pStatePara[0].m_binOut[nIndex].nState = pnStateBOut[nIndex];
        pStatePara[0].m_binOut[nIndex].nMode = STT_BOUT_REVERSAL_TRIG_MODE_NOT;
        pStatePara[0].m_binOut[nIndex].fTimeTrig = 0;
        pStatePara[0].m_binOut[nIndex].fHoldTime = 0;

        pStatePara[1].m_binOut[nIndex].nState = 0;
        pStatePara[1].m_binOut[nIndex].nMode = nOutputSwitchMode;
        pStatePara[1].m_binOut[nIndex].fTimeTrig = fBoutTimeTrig;
        pStatePara[1].m_binOut[nIndex].fHoldTime = fBoutHoldTime;
    }

    for (int nStateIndex = 2;nStateIndex<8;nStateIndex++)
    {
        for (int nBinOutIndex = 0;nBinOutIndex<8;nBinOutIndex++)
        {
            pStatePara[nStateIndex].m_binOut[nBinOutIndex].nState = 0;
            pStatePara[nStateIndex].m_binOut[nBinOutIndex].nMode = STT_BOUT_REVERSAL_TRIG_MODE_LAST_STATE;
            pStatePara[nStateIndex].m_binOut[nBinOutIndex].fTimeTrig = 0;
            pStatePara[nStateIndex].m_binOut[nBinOutIndex].fHoldTime = 0;
        }
    }
}

void Global_FaultCalculatUI(tmt_ImpedanceParas *pImpParas,int nFaultIndex,Complex *pVol_Complex,Complex *pCur_Complex)
{
    CSttFaultCalculatTool oFaultCalculatTool;
    float fVOutmax = 120.0f;//暂时默认最大输出电压120V
    float fIOutmax = 30.0f;//暂时默认最大输出电压30A
    float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
    int nPhaseRef[11]={1,2,0,2,0,1,2,0,1,0,0};
    float nAngle[11] = {(float)pVol_Complex[0].arg(),(float)pVol_Complex[1].arg(),(float)pVol_Complex[2].arg(),(float)pVol_Complex[0].arg()+30.0f
                        ,(float)pVol_Complex[1].arg()+30.0f,(float)pVol_Complex[2].arg()+30.0f,(float)pVol_Complex[0].arg()+30.0f,(float)pVol_Complex[1].arg()+30.0f
                        ,(float)pVol_Complex[2].arg()+30.0f,(float)pVol_Complex[0].arg(),(float)pVol_Complex[2].arg()};
    float fVFactor=1.0f,fIFactor=1.0f,fValueFactor = 1.0f;
    Complex fUI[7];
    Complex Comp1;
    float	fK0AmpCal;		//计算后的 m_fK0Amp
    float	fK0AngleCal;		//计算后的 m_fK0Angle
    Comp1 = oFaultCalculatTool.GroundFactor(pImpParas->m_nK0CalMode,pImpParas->m_fK0Amp,pImpParas->m_fK0Angle,pImpParas->m_fImpAngle[nFaultIndex]);
    fK0AmpCal=(float)Comp1.norm();
    fK0AngleCal=(float)Comp1.arg();

    if(g_theSystemConfig->m_nParaMode == 0)//如果参数设置为一次值
    {
        fValueFactor=1000.0;
        fVFactor = g_theSystemConfig->m_fVPrimary[0]/g_theSystemConfig->m_fVSecondary[0];
        fIFactor = g_theSystemConfig->m_fIPrimary[0]/g_theSystemConfig->m_fISecondary[0];
    }

    if (pImpParas->m_fSCCurrent[nFaultIndex] > fIOutmax)	//CCCC 距离、过流加此判断
        pImpParas->m_fSCCurrent[nFaultIndex] = fIOutmax;

    double fIt = pImpParas->m_fSCCurrent[nFaultIndex]/fIFactor;
    double fVt = pImpParas->m_fSCVoltage[nFaultIndex]/fVFactor;
    oFaultCalculatTool.Calculat(1.0f,pImpParas->m_nFaultDir[nFaultIndex],pImpParas->m_nCTPoint,pImpParas->m_nCalMode,pImpParas->m_nFaultType[nFaultIndex],
                                nPhaseRef[pImpParas->m_nFaultType[nFaultIndex]],nAngle[nPhaseRef[pImpParas->m_nFaultType[nFaultIndex]]],
            fVOutmax/fVFactor,fStdLN_Vol/fVFactor,fIOutmax/fIFactor,
            &fIt,&fVt,
            Comp1.polar(pImpParas->m_fIfh/fIFactor,-pImpParas->m_fPowerAngle),	//不再检测负荷电流是否允许有值，交给平台决定
            Comp1.polar(pImpParas->m_fImpedance[nFaultIndex]/fVFactor/fValueFactor*fIFactor,pImpParas->m_fImpAngle[nFaultIndex]),
            Comp1.polar(fK0AmpCal,fK0AngleCal),
            Comp1.polar(pImpParas->m_fZs/fVFactor/fValueFactor*fIFactor,pImpParas->m_fPhis),
            Comp1.polar(pImpParas->m_fK0s,pImpParas->m_fK0sPh),
            &fUI[0],&fUI[1],&fUI[2],&fUI[4],&fUI[5],&fUI[6]);

    for (int i=0;i<3;i++)
    {
        pVol_Complex[i] = fUI[i]*fVFactor;
        pCur_Complex[i] = fUI[i+4]*fIFactor;
    }

	pImpParas->m_fSCCurrent[nFaultIndex] = (float)fIt*fIFactor;
    pImpParas->m_fSCVoltage[nFaultIndex] = (float)fVt*fVFactor;
}

void Global_SetStateBinFault(tmt_StatePara *pStatePara,long *pnStateBInput,long nBinSelect)
{
    pStatePara->m_nBinLogic = TMT_BINLOGIC_OR;
    pStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    BOOL bHasThreeTrip = FALSE;

    if (nBinSelect == 1)
    {
        pStatePara->m_binIn[0].nSelect = 0;
        pStatePara->m_binIn[1].nSelect = 0;
        pStatePara->m_binIn[2].nSelect = 0;
        pStatePara->m_binIn[3].nSelect = 0;
        pStatePara->m_binIn[4].nSelect = 1;
        pStatePara->m_binIn[5].nSelect = 1;
        pStatePara->m_binIn[6].nSelect = 1;
        pStatePara->m_binIn[7].nSelect = 1;
    }
    else
    {
        pStatePara->m_binIn[0].nSelect = 1;
        pStatePara->m_binIn[1].nSelect = 1;
        pStatePara->m_binIn[2].nSelect = 1;
        pStatePara->m_binIn[3].nSelect = 1;
        pStatePara->m_binIn[4].nSelect = 0;
        pStatePara->m_binIn[5].nSelect = 0;
        pStatePara->m_binIn[6].nSelect = 0;
        pStatePara->m_binIn[7].nSelect = 0;
    }

    for (int nIndex = 0;nIndex<8;nIndex++)
    {
        if (pnStateBInput[nIndex] == STT_IMPEDANCE_BIN_STATE_RECLOCE)
        {
            pStatePara->m_binIn[nIndex].nSelect = 0;
        }
        // 		else if ((pStatePara->m_binIn[nIndex].nSelect)&&(pnStateBInput[nIndex] == STT_IMPEDANCE_BIN_STATE_THREE))
        // 		{
        // 			bHasThreeTrip = TRUE;
        // 		}
    }

    // 	if (!bHasThreeTrip)
    // 	{
    // 		pStatePara->m_nBinLogic = TMT_BINLOGIC_AND;
    // 	}
}

void Global_SetStateBinFault(tmt_StatePara *pStatePara,tmt_BinaryIn *pBinaryIn,int nBinLogic)
{
    pStatePara->m_nBinLogic = nBinLogic;
    pStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;

    for (int nIndex = 0;nIndex<8;nIndex++)
    {
        pStatePara->m_binIn[nIndex] = pBinaryIn[nIndex];
    }
}

void Global_SetStateBinReclose(tmt_StatePara *pStatePara,long *pnDInputState,long nBinSelect)
{
    pStatePara->m_nBinLogic = TMT_BINLOGIC_OR;
    pStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;

    if (nBinSelect == 1)
    {
        pStatePara->m_binIn[0].nSelect = 0;
        pStatePara->m_binIn[1].nSelect = 0;
        pStatePara->m_binIn[2].nSelect = 0;
        pStatePara->m_binIn[3].nSelect = 0;
        pStatePara->m_binIn[4].nSelect = 1;
        pStatePara->m_binIn[5].nSelect = 1;
        pStatePara->m_binIn[6].nSelect = 1;
        pStatePara->m_binIn[7].nSelect = 1;
    }
    else
    {
        pStatePara->m_binIn[0].nSelect = 1;
        pStatePara->m_binIn[1].nSelect = 1;
        pStatePara->m_binIn[2].nSelect = 1;
        pStatePara->m_binIn[3].nSelect = 1;
        pStatePara->m_binIn[4].nSelect = 0;
        pStatePara->m_binIn[5].nSelect = 0;
        pStatePara->m_binIn[6].nSelect = 0;
        pStatePara->m_binIn[7].nSelect = 0;
    }

    for (int nIndex = 0;nIndex<8;nIndex++)
    {
        if (pnDInputState[nIndex] != STT_IMPEDANCE_BIN_STATE_RECLOCE)
        {
            pStatePara->m_binIn[nIndex].nSelect = 0;
        }
    }
}

void Global_SetStateI_AfterTripFromFaultType(tmt_StatePara *pStatePara,long nFaultType,long *pnDInputState,int nBinSelect)
{
    BOOL bHasTripThree = FALSE;

    if (nBinSelect == 1)
    {
        for (int nIndex = 0;nIndex<4;nIndex++)
        {
            if (pnDInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_THREE)
            {
                bHasTripThree = TRUE;
            }
        }
    }
    else
    {
        for (int nIndex = 4;nIndex<8;nIndex++)
        {
            if (pnDInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_THREE)
            {
                bHasTripThree = TRUE;
            }
        }
    }

    if (bHasTripThree)
    {
        pStatePara->m_uiCUR[0].Harm[1].fAmp = 0.0f;
        pStatePara->m_uiCUR[1].Harm[1].fAmp = 0.0f;
        pStatePara->m_uiCUR[2].Harm[1].fAmp = 0.0f;
        return;
    }

    if (nFaultType == IMPEDANCE_FAULT_TYPE_AN)
    {
        pStatePara->m_uiCUR[0].Harm[1].fAmp = 0.0f;
    }
    else if (nFaultType == IMPEDANCE_FAULT_TYPE_BN)
    {
        pStatePara->m_uiCUR[1].Harm[1].fAmp = 0.0f;
    }
    else if (nFaultType == IMPEDANCE_FAULT_TYPE_CN)
    {
        pStatePara->m_uiCUR[2].Harm[1].fAmp = 0.0f;
    }
    else if ((nFaultType == IMPEDANCE_FAULT_TYPE_AB)||(nFaultType == IMPEDANCE_FAULT_TYPE_ABN))
    {
        pStatePara->m_uiCUR[0].Harm[1].fAmp = 0.0f;
        pStatePara->m_uiCUR[1].Harm[1].fAmp = 0.0f;
    }
    else if ((nFaultType == IMPEDANCE_FAULT_TYPE_BC)||(nFaultType == IMPEDANCE_FAULT_TYPE_BCN))
    {
        pStatePara->m_uiCUR[1].Harm[1].fAmp = 0.0f;
        pStatePara->m_uiCUR[2].Harm[1].fAmp = 0.0f;
    }
    else if ((nFaultType == IMPEDANCE_FAULT_TYPE_CA)||(nFaultType == IMPEDANCE_FAULT_TYPE_CAN))
    {
        pStatePara->m_uiCUR[0].Harm[1].fAmp = 0.0f;
        pStatePara->m_uiCUR[2].Harm[1].fAmp = 0.0f;
    }
    else if (nFaultType == IMPEDANCE_FAULT_TYPE_ABC)
    {
        pStatePara->m_uiCUR[0].Harm[1].fAmp = 0.0f;
        pStatePara->m_uiCUR[1].Harm[1].fAmp = 0.0f;
        pStatePara->m_uiCUR[2].Harm[1].fAmp = 0.0f;
    }
    else if (nFaultType == IMPEDANCE_FAULT_TYPE_ONE)
    {
        pStatePara->m_uiCUR[0].Harm[1].fAmp = 0.0f;
    }
}

void Global_AddSimulateBreakTimeToResults(tmt_ImpedanceParas *pImpParas,tmt_ImpedanceResults *pResult)
{
    if (pImpParas->m_bCBSimulation)
    {
        for (int nIndex = 0;nIndex<8;nIndex++)
        {
            if (pResult->m_fFirstTripTime[nIndex]>0.0001)
            {
                pResult->m_fFirstTripTime[nIndex] += pImpParas->m_fCBTripTime;
            }
        }

        if (pResult->m_fRecloseTime>0.0001)
        {
            pResult->m_fRecloseTime += pImpParas->m_fCBCloseTime;
        }

        if (pResult->m_fTripTime>0.0001)
        {
            pResult->m_fTripTime += pImpParas->m_fCBTripTime;
        }

        if (pResult->m_fSecondTripTime>0.0001)
        {
            pResult->m_fSecondTripTime += pImpParas->m_fCBTripTime;
        }
    }
}
