#include "stdafx.h"
#include "SttImpBaseTest.h"
#include "../SttSystemConfig.h"
#include "../SttStateTest.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttImpBaseTest::m_strMacroName = "SttImpBaseTest";
CString CSttImpBaseTest::m_strMacroID = "SttImpBaseTest";
CString CSttImpBaseTest::m_strFilePostFix = "impb";
CString CSttImpBaseTest::m_strMacroVer ="1.0";
CSttImpBaseTest::CSttImpBaseTest() : CSttTestBase()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;

	m_pImpBaseParas = stt_test_get_ex_ImpBase_buff();
}
void CSttImpBaseTest::Init()
{
	tmt_StateTest *pStateTest = stt_test_get_base_statetest_buff();
	m_pImpBaseParas->init(&pStateTest->m_oStateParas);
	pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统参数里面的频率
    CSttTestBase::Init();
    m_nCurStateIndex = 0;
	m_oImpBaseResults.init(8);
}

long CSttImpBaseTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    return true;
}

CSttImpBaseTest::~CSttImpBaseTest(void)
{

}

void CSttImpBaseTest::AfterSetParameter()
{
	m_oImpBaseResults.init(8);
    m_nCurStateIndex = 0;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

BOOL CSttImpBaseTest::EventProcess()
{
	if(!GetTestStarting())
		return FALSE;

	BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->ProStateDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
	return bTestFinished;
}

double CSttImpBaseTest::GetTestTimeLong()
{
    float	fTime = 0.000;
	for (int i=0;i<m_pImpBaseParas->m_pStateParas->m_nStateNumbers;i++)
    {
		tmt_state_para *pSt = &m_pImpBaseParas->m_pStateParas->m_paraState[i];
        if (pSt->m_nTriggerCondition==TMT_MDSTATE_TIMETRIGGER || pSt->m_nTriggerCondition==TMT_MDSTATE_TIMEBINTRIGGER)
            fTime += pSt->m_fTimeState+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
        else
            fTime += TIME_MAX_WAITING+pSt->m_fTimeAfterTrigger+pSt->m_binOut[0].fTimeTrig;
    }

	fTime *= (m_pImpBaseParas->m_pStateParas->m_nRepeatNumbers+1);

    fTime += TIME_ONLINE_DELAY;		//

    return fTime;
}

long CSttImpBaseTest::CalReport(UINT nState)
{
    return 0;
}

long CSttImpBaseTest::CalReport_ImpBase(tmt_ImpedanceParas *pImpParas,tmt_ImpedanceResults *pResult)
{
	long nBeginIndex,nEndIndex;

	if (pImpParas->m_nBinSelect == 1)
	{
		nBeginIndex = 4;
	} 
	else
	{
		nBeginIndex = 0;
	}

	nEndIndex = (nBeginIndex+4);
	long nTripIndex = 0;
	bool bHasMapReclose = false;
	float fTimeBin = 0;

	for (int nIndex = nBeginIndex;nIndex<nEndIndex;nIndex++)
	{
		if (pImpParas->m_nDInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_RECLOCE)
		{
			fTimeBin = m_oImpBaseResults.m_resultState[2].m_frTimeBinAct[nIndex][0];
			if(g_theSystemConfig->m_nBinBoutMode)
			{
				if(m_oImpBaseResults.m_resultState[2].m_frTimeBinExAct[nIndex][0] > fTimeBin)
				{
					fTimeBin = m_oImpBaseResults.m_resultState[2].m_frTimeBinExAct[nIndex][0];
				}
			}
			pResult->SetRecloseTime(fTimeBin);
			bHasMapReclose = true;
		} 
		else
		{
			fTimeBin = m_oImpBaseResults.m_resultState[1].m_frTimeBinAct[nIndex][0];
			if(g_theSystemConfig->m_nBinBoutMode)
			{
				if(m_oImpBaseResults.m_resultState[1].m_frTimeBinExAct[nIndex][0] > fTimeBin)
				{
					fTimeBin = m_oImpBaseResults.m_resultState[1].m_frTimeBinExAct[nIndex][0];
				}
			}
			pResult->SetFault1TripTime(nTripIndex,pImpParas->m_nDInputState[nIndex],fTimeBin,bHasMapReclose);

			if (pImpParas->m_nFaultProperty == 0)//瞬时性故障
			{
				fTimeBin = m_oImpBaseResults.m_resultState[3].m_frTimeBinAct[nIndex][0];
				if(g_theSystemConfig->m_nBinBoutMode)
				{
					if(m_oImpBaseResults.m_resultState[3].m_frTimeBinExAct[nIndex][0] > fTimeBin)
					{
						fTimeBin = m_oImpBaseResults.m_resultState[3].m_frTimeBinExAct[nIndex][0];
					}
				}
				pResult->SetFault2TripTime(nTripIndex,pImpParas->m_nDInputState[nIndex],fTimeBin);
			} 
			else
			{
				fTimeBin = m_oImpBaseResults.m_resultState[4].m_frTimeBinAct[nIndex][0];
				if(g_theSystemConfig->m_nBinBoutMode)
				{
					if(m_oImpBaseResults.m_resultState[4].m_frTimeBinExAct[nIndex][0] > fTimeBin)
					{
						fTimeBin = m_oImpBaseResults.m_resultState[4].m_frTimeBinExAct[nIndex][0];
					}
				}
				pResult->SetFault2TripTime(nTripIndex,pImpParas->m_nDInputState[nIndex],fTimeBin);
			}

			nTripIndex++;
		}
	}

	pResult->m_nActA = (pResult->m_fFirstTripTime[0]-0.0001) > 0 ? 1 : 0;
	pResult->m_nActB = (pResult->m_fFirstTripTime[1]-0.0001) > 0 ? 1 : 0;
	pResult->m_nActC = (pResult->m_fFirstTripTime[2]-0.0001) > 0 ? 1 : 0;
	pResult->m_nActD = (pResult->m_fRecloseTime - 0.0001) > 0 ? 1 : 0;
	pResult->m_fTripTime = 0;

	for (int i=0;i<8;i++)
	{
        pResult->m_nActID[i] = (pResult->m_fFirstTripTime[i]-0.0001) > 0 ? 1 : 0;
		pResult->m_fTripTime = GetMaxValue(pResult->m_fTripTime,pResult->m_fFirstTripTime[i]);
	}

	pResult->m_fImp = pImpParas->m_fImpedance[0];
	pResult->m_fImpAngle = pImpParas->m_fImpAngle[0];
//	Global_AddSimulateBreakTimeToResults(pImpParas,pResult); 20220615 zhouhj北京要求实际动作时间中去除模断时间的添加与老版PowerTest一致
	return 0;
}

void CSttImpBaseTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_ImpBaseParas*)this,pXmlSerialize);

    //2020-4-6  
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
    }
}

//2020-10-26  lijunqing
void CSttImpBaseTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oImpBaseResults, m_pImpBaseParas->m_pStateParas, m_pImpBaseParas->m_pStateParas->m_nRepeatNumbers,
					  pXmlSerialize,m_pImpBaseParas->m_pStateParas->m_nBinTripRef);
}


//2020-10-26  lijunqing
void CSttImpBaseTest::Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize((tmt_ImpBaseParas*)this,pXmlSerialize);
}

//2020-10-26  lijunqing
void CSttImpBaseTest::Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oImpBaseResults, m_pImpBaseParas->m_pStateParas, m_pImpBaseParas->m_pStateParas->m_nRepeatNumbers,
					  pXmlSerialize,m_pImpBaseParas->m_pStateParas->m_nBinTripRef);
}


long CSttImpBaseTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttImpBaseTest::Triger()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetStateTriger();
#endif
}

void CSttImpBaseTest::StartTest()
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
		if(m_pImpBaseParas->m_pStateParas->m_bSequence)
			CSttDeviceBase::g_pSttDeviceBase->SetTestStart(StateTest);
		else
			CSttDeviceBase::g_pSttDeviceBase->SetTestStart(CboperTest);
#endif
		CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttImpBaseTest::StartTest >>>>>>");
	}
	else
	{
        CLogPrint::LogString(XLOGLEVEL_DEBUG, "[error] CSttImpBaseTest is  Running,Can't StartTest()");
	}

}

void CSttImpBaseTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
	if(m_pImpBaseParas->m_pStateParas->m_bSequence)
	{
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StatePara(m_pImpBaseParas->m_pStateParas);
		int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
		
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(nfd, 0x149, 1);//按故障态开出设置来，时间或开入量启动
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}
	else
	{
		CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_CboperPara(m_pImpBaseParas);
	}

	CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_StateItem(m_pImpBaseParas->m_pStateParas);
#endif
}

void CSttImpBaseTest::SyncSingleStateTmtResult()
{
	if(m_nCurStateIndex>=0&&m_nCurStateIndex<m_pImpBaseParas->m_pStateParas->m_nStateNumbers)
	{

	}
	else
		return;

#ifdef _PSX_QT_LINUX_
    long nStateNum = GetStateNum(m_nCurStateIndex);
    if(nStateNum < 0)
    {
        return;
    }
    tmt_StateResult  &oResultState=m_oImpBaseResults.m_resultState[nStateNum];
#ifdef _PSX_QT_LINUX_
	GradientResult_Com &oRampRestCom=CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;

	oResultState.m_nAct = oRampRestCom.m_nAct;
    oResultState.m_frTestTime=oRampRestCom.m_fTripTime;

	int nrBinSwitchCount;
	for(int i=0; i<MAX_BINARYIN_COUNT; i++)
	{
		nrBinSwitchCount=oRampRestCom.m_nrBinSwitchCount[i];
		oResultState.m_nrBinSwitchCount[i]=nrBinSwitchCount;
		for(int j=0; j<nrBinSwitchCount; j++)
		{
			oResultState.m_frTimeBinAct[i][j]=oRampRestCom.m_frTimeBinAct[i][j];
		}
        oResultState.m_nBinFirstChgState[i]=oRampRestCom.m_nBinFirstChgState[i];
	}

	oResultState.m_frInTime=oRampRestCom.m_frInTime;
	oResultState.m_frTimeStateBegin=oRampRestCom.m_frTimeStateBegin;
#endif
#endif
}

void CSttImpBaseTest::ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType)
{
#ifdef _PSX_QT_LINUX_
	if(m_nCurStateIndex>=0&&m_nCurStateIndex<m_pImpBaseParas->m_pStateParas->m_nStateNumbers)
    {
        STT_RTDATA_EVENT oRtdata;
        oRtdata.oTime.dTime=dTime1;
        oRtdata.oTime.dRealTime=dTime2;
        oRtdata.m_nVolChCount=0;
        oRtdata.m_nCurChCount=0;
		oRtdata.m_nHasFaultVolCur=0;
        float fVal;
        int nRtIndex=0;

        long nStateNum = GetStateNum(m_nCurStateIndex);
        if(nStateNum < 0)
            return;

        tmt_StatePara   oparaState=m_pImpBaseParas->m_pStateParas->m_paraState[nStateNum];
        for(int nIndex=0;nIndex<g_nRtDataVoltCnt;nIndex++)
        {
            fVal=fabs(oparaState.m_uiVOL[nIndex].Harm[1].fAmp);
            nRtIndex=oRtdata.m_nVolChCount;
            oRtdata.m_oVolCh[nRtIndex].m_nIndex=nIndex;
			oRtdata.m_oVolCh[nRtIndex].m_fMag=fVal;
			oRtdata.m_oVolCh[nRtIndex].m_fAng=
					oparaState.m_uiVOL[nIndex].Harm[1].fAngle;
			oRtdata.m_oVolCh[nRtIndex].m_fFreq=
					oparaState.m_uiVOL[nIndex].Harm[1].fFreq;
            oRtdata.m_nVolChCount++;
        }

        for(int nIndex=0;nIndex<g_nRtDataCurrCnt;nIndex++)
        {
            fVal=fabs(oparaState.m_uiCUR[nIndex].Harm[1].fAmp);
            nRtIndex=oRtdata.m_nCurChCount;
            oRtdata.m_oCurCh[nRtIndex].m_nIndex=nIndex;
			oRtdata.m_oCurCh[nRtIndex].m_fMag=fVal;
			oRtdata.m_oCurCh[nRtIndex].m_fAng=
					oparaState.m_uiCUR[nIndex].Harm[1].fAngle;
			oRtdata.m_oCurCh[nRtIndex].m_fFreq=
					oparaState.m_uiCUR[nIndex].Harm[1].fFreq;
            oRtdata.m_nCurChCount++;
        }
        if(oRtdata.m_nCurChCount>0||oRtdata.m_nVolChCount>0)
            stt_add_rtdatas(oRtdata);
    }
#endif
}

void CSttImpBaseTest::TranslateToStateParas_ImpBase(tmt_ImpedanceParas *pImpParas)
{
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	TranslateToStateParas_ImpBase(pImpParas,fStdLN_Vol);
}

void CSttImpBaseTest::TranslateToStateParas_ImpBase(tmt_ImpedanceParas *pImpParas,float fUnom)
{
	m_pImpBaseParas->m_fImpBaseFaultTime = pImpParas->m_fMaxFaultTime;
	m_pImpBaseParas->m_fImpBaseTripTime = pImpParas->m_fPostFaultTime;
	m_pImpBaseParas->m_bImpBaseIsPermanent = pImpParas->m_nFaultProperty;
	m_pImpBaseParas->m_bImpBaseTransFault = FALSE;
	m_pImpBaseParas->m_fImpBaseReclosingTime = pImpParas->m_fRecloseTime;
	m_pImpBaseParas->m_fImpBaseStopTime = 1.0f;
	m_pImpBaseParas->m_pStateParas->m_bSequence = FALSE;

	m_pImpBaseParas->m_pStateParas->m_nPlusDC = pImpParas->m_bIPlusDC;
	m_pImpBaseParas->m_pStateParas->m_fTao =
			m_oFaultCalculatTool.CalImpPlusDC_Tao(pImpParas->m_fImpedance[0],pImpParas->m_fImpAngle[0]);

	tmt_StatePara *pState0 = &m_pImpBaseParas->m_pStateParas->m_paraState[0];
	tmt_StatePara *pState1 = &m_pImpBaseParas->m_pStateParas->m_paraState[1];
	tmt_StatePara *pState2 = &m_pImpBaseParas->m_pStateParas->m_paraState[2];
	tmt_StatePara *pState3 = &m_pImpBaseParas->m_pStateParas->m_paraState[3];
	tmt_StatePara *pState4 = &m_pImpBaseParas->m_pStateParas->m_paraState[4];
	tmt_StatePara *pState5 = &m_pImpBaseParas->m_pStateParas->m_paraState[5];
	tmt_StatePara *pState6 = &m_pImpBaseParas->m_pStateParas->m_paraState[6];
	tmt_StatePara *pState7 = &m_pImpBaseParas->m_pStateParas->m_paraState[7];
	//////////////////////////////////////////////////////////////////////////
	//状态1：故障前状态
	Complex p1;
	Complex	oComplexUI[2][4];
	SetStateParas_PreFault(pState0,pImpParas,oComplexUI[0],oComplexUI[1],fUnom);
	Global_SetStateBoutPreFault(m_pImpBaseParas->m_pStateParas->m_paraState,pImpParas->m_nStateBOut,
                                pImpParas->m_nOutputSwitchMode,pImpParas->m_nBinSelect,pImpParas->m_fBoutTimeTrig,pImpParas->m_fBoutHoldTime);
	//////////////////////////////////////////////////////////////////////////
	//状态2：故障状态
	SetStateParas_FirstFault(pState1,pImpParas,oComplexUI[0],oComplexUI[1],fUnom);
	//////////////////////////////////////////////////////////////////////////
	//状态3：跳闸后,等待重合闸状态
	SetStateParas_AfterFirstTrip(pState2,pImpParas,oComplexUI[0],oComplexUI[1],fUnom);
	//////////////////////////////////////////////////////////////////////////
	//状态4：重合后(瞬时)
	SetStateParas_AfterRecoseTransient(pState3,pImpParas,oComplexUI[0],oComplexUI[1],fUnom);
	//////////////////////////////////////////////////////////////////////////
	//状态5：重合后(永久)
	SetStateParas_AfterRecosePermanent(pState4,pImpParas,oComplexUI[0],oComplexUI[1],fUnom);
	//////////////////////////////////////////////////////////////////////////
	//状态6：转换故障
	SetStateParas_TransFault(pState5,pImpParas,oComplexUI[0],oComplexUI[1],fUnom);
	//////////////////////////////////////////////////////////////////////////
	//状态7：加速后
	SetStateParas_AccTrip(pState6,pImpParas,oComplexUI[0],oComplexUI[1],fUnom);
	//////////////////////////////////////////////////////////////////////////
	//状态8：停止态
	SetStateParas_StopTest(pState7,pImpParas,oComplexUI[0],oComplexUI[1],fUnom);
	//////////////////////////////////////////////////////////////////////////
	TranslateToStateParas_FaultIncMode(pImpParas);
}

void CSttImpBaseTest::TranslateToStateParas_ImpBase(tmt_ImpedanceParas *pImpParas,float *pfVolAmp,float *pfVolAng)
{
	m_pImpBaseParas->m_fImpBaseFaultTime = pImpParas->m_fMaxFaultTime;
	m_pImpBaseParas->m_fImpBaseTripTime = pImpParas->m_fPostFaultTime;
	m_pImpBaseParas->m_bImpBaseIsPermanent = pImpParas->m_nFaultProperty;
	m_pImpBaseParas->m_bImpBaseTransFault = FALSE;
	m_pImpBaseParas->m_fImpBaseReclosingTime = pImpParas->m_fRecloseTime;
	m_pImpBaseParas->m_fImpBaseStopTime = 1.0f;
	m_pImpBaseParas->m_pStateParas->m_bSequence = FALSE;

	m_pImpBaseParas->m_pStateParas->m_nPlusDC = pImpParas->m_bIPlusDC;
	m_pImpBaseParas->m_pStateParas->m_fTao =
		m_oFaultCalculatTool.CalImpPlusDC_Tao(pImpParas->m_fImpedance[0],pImpParas->m_fImpAngle[0]);

	tmt_StatePara *pState0 = &m_pImpBaseParas->m_pStateParas->m_paraState[0];
	tmt_StatePara *pState1 = &m_pImpBaseParas->m_pStateParas->m_paraState[1];
	tmt_StatePara *pState2 = &m_pImpBaseParas->m_pStateParas->m_paraState[2];
	tmt_StatePara *pState3 = &m_pImpBaseParas->m_pStateParas->m_paraState[3];
	tmt_StatePara *pState4 = &m_pImpBaseParas->m_pStateParas->m_paraState[4];
	tmt_StatePara *pState5 = &m_pImpBaseParas->m_pStateParas->m_paraState[5];
	tmt_StatePara *pState6 = &m_pImpBaseParas->m_pStateParas->m_paraState[6];
	tmt_StatePara *pState7 = &m_pImpBaseParas->m_pStateParas->m_paraState[7];
	//////////////////////////////////////////////////////////////////////////
	//状态1：故障前状态
	Complex p1;
	Complex	oComplexUI[2][4];
	SetStateParas_PreFault(pState0,pImpParas,oComplexUI[0],oComplexUI[1],pfVolAmp,pfVolAng);
	Global_SetStateBoutPreFault(m_pImpBaseParas->m_pStateParas->m_paraState,pImpParas->m_nStateBOut,
        pImpParas->m_nOutputSwitchMode,pImpParas->m_nBinSelect,pImpParas->m_fBoutTimeTrig,pImpParas->m_fBoutHoldTime);
	//////////////////////////////////////////////////////////////////////////
	//状态2：故障状态
	SetStateParas_FirstFault(pState1,pImpParas,oComplexUI[0],oComplexUI[1],pfVolAmp,pfVolAng);
	//////////////////////////////////////////////////////////////////////////
	//状态3：跳闸后,等待重合闸状态
	SetStateParas_AfterFirstTrip(pState2,pImpParas,oComplexUI[0],oComplexUI[1],pfVolAmp,pfVolAng);
	//////////////////////////////////////////////////////////////////////////
	//状态4：重合后(瞬时)
	SetStateParas_AfterRecoseTransient(pState3,pImpParas,oComplexUI[0],oComplexUI[1],pfVolAmp,pfVolAng);
	//////////////////////////////////////////////////////////////////////////
	//状态5：重合后(永久)
	SetStateParas_AfterRecosePermanent(pState4,pImpParas,oComplexUI[0],oComplexUI[1],pfVolAmp,pfVolAng);
	//////////////////////////////////////////////////////////////////////////
	//状态6：转换故障
	SetStateParas_TransFault(pState5,pImpParas,oComplexUI[0],oComplexUI[1],pfVolAmp,pfVolAng);
	//////////////////////////////////////////////////////////////////////////
	//状态7：加速后
	SetStateParas_AccTrip(pState6,pImpParas,oComplexUI[0],oComplexUI[1],pfVolAmp,pfVolAng);
	//////////////////////////////////////////////////////////////////////////
	//状态8：停止态
	SetStateParas_StopTest(pState7,pImpParas,oComplexUI[0],oComplexUI[1],0);
	//////////////////////////////////////////////////////////////////////////
	TranslateToStateParas_FaultIncMode(pImpParas);
}

void CSttImpBaseTest::TranslateToStateParas_FaultIncMode(tmt_ImpedanceParas *pImpParas)
{
	tmt_StatePara *pStatePara = m_pImpBaseParas->m_pStateParas->m_paraState;
	

	if (pImpParas->m_nFaultIncMode>0)
	{
		tmt_StateCloseAngle *pCloseAngle = NULL;
		pCloseAngle = &pStatePara[1].m_oCloseAngle;//第一次故障态
		pCloseAngle->m_nFaultIncMode = pImpParas->m_nFaultIncMode;
		pCloseAngle->m_fRefCloseAngle = pImpParas->m_fFaultAngle;
		m_oFaultCalculatTool.CalculateCloseAngle(pImpParas->m_fFaultAngle,pImpParas->m_nFaultType[0], 
			pStatePara[1].m_uiVOL[0].Harm[1].fAngle,pStatePara[1].m_uiVOL[1].Harm[1].fAngle,pStatePara[1].m_uiVOL[2].Harm[1].fAngle,
			pImpParas->m_fPowerAngle,
			pCloseAngle->m_fVolCloseAngle,pCloseAngle->m_fCurCloseAngle,pCloseAngle->m_nCloseChannel);

// 		pCloseAngle = &pStatePara[2].m_oCloseAngle;//第一次故障跳闸后
// 		pCloseAngle->m_nFaultIncMode = pImpParas->m_nFaultIncMode;
// 		m_oFaultCalculatTool.CalculateCloseAngle(pImpParas->m_fFaultAngle,pImpParas->m_nFaultType[0], 
// 			pStatePara[2].m_uiVOL[0].Harm[1].fAngle,pStatePara[2].m_uiVOL[1].Harm[1].fAngle,pStatePara[2].m_uiVOL[2].Harm[1].fAngle,
// 			pImpParas->m_fPowerAngle,
// 			pCloseAngle->m_fVolCloseAngle,pCloseAngle->m_fCurCloseAngle,pCloseAngle->m_nCloseChannel);

		pCloseAngle = &pStatePara[4].m_oCloseAngle;//第一次故障 永久故障
		pCloseAngle->m_nFaultIncMode = pImpParas->m_nFaultIncMode;
		pCloseAngle->m_fRefCloseAngle = pImpParas->m_fFaultAngle;
		m_oFaultCalculatTool.CalculateCloseAngle(pImpParas->m_fFaultAngle,pImpParas->m_nFaultType[0], 
			pStatePara[4].m_uiVOL[0].Harm[1].fAngle,pStatePara[4].m_uiVOL[1].Harm[1].fAngle,pStatePara[4].m_uiVOL[2].Harm[1].fAngle,
			pImpParas->m_fPowerAngle,
			pCloseAngle->m_fVolCloseAngle,pCloseAngle->m_fCurCloseAngle,pCloseAngle->m_nCloseChannel);

		pCloseAngle = &pStatePara[5].m_oCloseAngle;//转换后故障
		pCloseAngle->m_nFaultIncMode = pImpParas->m_nFaultIncMode;
		pCloseAngle->m_fRefCloseAngle = pImpParas->m_fFaultAngle;
		m_oFaultCalculatTool.CalculateCloseAngle(pImpParas->m_fFaultAngle,pImpParas->m_nFaultType[1], 
			pStatePara[5].m_uiVOL[0].Harm[1].fAngle,pStatePara[5].m_uiVOL[1].Harm[1].fAngle,pStatePara[5].m_uiVOL[2].Harm[1].fAngle,
			pImpParas->m_fPowerAngle,
			pCloseAngle->m_fVolCloseAngle,pCloseAngle->m_fCurCloseAngle,pCloseAngle->m_nCloseChannel);
	}
}

void CSttImpBaseTest::SetStateParas_PreFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,fStdLN_Vol,0.0f);//计算故障前三相电压
	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,pImpParas->m_fIfh,-pImpParas->m_fPowerAngle);//计算故障前三相电流
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	//	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],m_nVzDefine);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);

	pStatePara->m_fTimeState = pImpParas->m_fPreFaultTime;
	pStatePara->m_nTriggerCondition = pImpParas->GetSttTrigMode();
	Global_SetStateBinPreFault(pStatePara);
	pStatePara->m_fTimeAfterTrigger = 0.0f;
	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_PreFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng)
{
//	m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,pfVolAmp[0],pfVolAng[0]);//计算故障前三相电压
	Complex p1;
	pVol_Complex[0] = p1.polar(pfVolAmp[0],pfVolAng[0]);
	pVol_Complex[1] = p1.polar(pfVolAmp[1],pfVolAng[1]);
	pVol_Complex[2] = p1.polar(pfVolAmp[2],pfVolAng[2]);
	pVol_Complex[3] = p1.polar(pfVolAmp[3],pfVolAng[3]);
	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,pImpParas->m_fIfh,pfVolAng[0]-pImpParas->m_fPowerAngle);//计算故障前三相电流

	
	//以直接设置的电压幅值相位为准
//	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	//	m_oFaultCalculatTool.CalVzComplex(&oComplexUI[0][3],oComplexUI[0],m_nVzDefine);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);

	pStatePara->m_fTimeState = pImpParas->m_fPreFaultTime;
	pStatePara->m_nTriggerCondition = pImpParas->GetSttTrigMode();
	Global_SetStateBinPreFault(pStatePara);
	pStatePara->m_fTimeAfterTrigger = 0.0f;
	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_FirstFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	Global_FaultCalculatUI(pImpParas,0,pVol_Complex,pCur_Complex);
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fMaxFaultTime;
	Global_SetStateBinFault(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect,Global_IsLNFaultType(pImpParas->m_nFaultType[0]));
	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBTripTime,pImpParas->m_bCBSimulation);

// 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYIN_COUNT;nBoutIndex++)
// 	{
// 		pStatePara->m_binOut[nBoutIndex].fTimeTrig = 0;
// 	}

	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_FirstFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng)
{
	Global_FaultCalculatUI(pImpParas,0,pVol_Complex,pCur_Complex);
	Complex p1;

	switch(pImpParas->m_nFaultType[0])
	{
	case IMPEDANCE_FAULT_TYPE_AN:
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_BN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_CN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		break;
	case IMPEDANCE_FAULT_TYPE_AB:
	case IMPEDANCE_FAULT_TYPE_ABN:
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_BC:
	case IMPEDANCE_FAULT_TYPE_BCN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		break;
	case IMPEDANCE_FAULT_TYPE_CA:
	case IMPEDANCE_FAULT_TYPE_CAN:
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		break;

	default:
		break;
	}

	pVol_Complex[3] = p1.polar(pfVolAmp[7],pfVolAng[7]);
//	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fMaxFaultTime;
	Global_SetStateBinFault(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect,Global_IsLNFaultType(pImpParas->m_nFaultType[0]));
	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBTripTime,pImpParas->m_bCBSimulation);

	// 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYIN_COUNT;nBoutIndex++)
	// 	{
	// 		pStatePara->m_binOut[nBoutIndex].fTimeTrig = 0;
	// 	}

	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_AfterFirstTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	if (pImpParas->m_nPTPoint == 0)//PT安装在母线侧,跳闸后电压恢复57.74
	{
		m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,fStdLN_Vol,0.0f);//计算故障前三相电压
	} 
	else//PT安装在线路侧,跳闸后电压0
	{
		m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,0,0.0f);//计算故障前三相电压
	}

	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,pImpParas->m_fIfh,-pImpParas->m_fPowerAngle);//计算故障前三相电流
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);

	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	Global_SetStateI_AfterTripFromFaultType(pStatePara,pImpParas->m_nFaultType[0],pImpParas->m_nDInputState,pImpParas->m_nBinSelect);
	pStatePara->m_fTimeState = pImpParas->m_fPostFaultTime;
	Global_SetStateBinReclose(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect);

// 	for (int i=1;i<MAX_BINARYIN_COUNT;i++)
// 	{
// 		pStatePara->m_binOut[i].fTimeTrig = 0;
// 	}

	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBCloseTime,pImpParas->m_bCBSimulation);;
	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_AfterFirstTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,
												   Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng)
{
	Complex p1;

	if (pImpParas->m_nPTPoint == 0)//PT安装在母线侧,跳闸后电压恢复57.74
	{
		pVol_Complex[0] = p1.polar(pfVolAmp[0],pfVolAng[0]);
		pVol_Complex[1] = p1.polar(pfVolAmp[1],pfVolAng[1]);
		pVol_Complex[2] = p1.polar(pfVolAmp[2],pfVolAng[2]);
//		m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,fStdLN_Vol,0.0f);//计算故障前三相电压
	} 
	else//PT安装在线路侧,跳闸后电压0
	{
		m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,0,0.0f);//计算故障前三相电压
	}

	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,pImpParas->m_fIfh,pfVolAng[0] - pImpParas->m_fPowerAngle);//计算故障前三相电流
	pVol_Complex[3] = p1.polar(pfVolAmp[3],pfVolAng[3]);
//	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);

	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	Global_SetStateI_AfterTripFromFaultType(pStatePara,pImpParas->m_nFaultType[0],pImpParas->m_nDInputState,pImpParas->m_nBinSelect);
	pStatePara->m_fTimeState = pImpParas->m_fPostFaultTime;
	Global_SetStateBinReclose(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect);

	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBCloseTime,pImpParas->m_bCBSimulation);;
	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_AfterRecoseTransient(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,fStdLN_Vol,0.0f);//计算故障前三相电压
	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,pImpParas->m_fIfh,-pImpParas->m_fPowerAngle);//计算故障前三相电流
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fPostFaultTime;
	Global_SetStateBinFault(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect,Global_IsLNFaultType(pImpParas->m_nFaultType[1]));
	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBTripTime,pImpParas->m_bCBSimulation);//跳合闸信号控制模式下,两次故障共用一个跳闸后持续时间

// 	for (int i=1;i<MAX_BINARYIN_COUNT;i++)
// 	{
// 		pStatePara->m_binOut[i].fTimeTrig = 0;
// 	}

	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_AfterRecoseTransient(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,
														 Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng)
{
	Complex p1;
	pVol_Complex[0] = p1.polar(pfVolAmp[0],pfVolAng[0]);
	pVol_Complex[1] = p1.polar(pfVolAmp[1],pfVolAng[1]);
	pVol_Complex[2] = p1.polar(pfVolAmp[2],pfVolAng[2]);
//	m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,fStdLN_Vol,0.0f);//计算故障前三相电压
	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,pImpParas->m_fIfh,pfVolAng[0]-pImpParas->m_fPowerAngle);//计算故障前三相电流
	pVol_Complex[3] = p1.polar(pfVolAmp[3],pfVolAng[3]);
//	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fPostFaultTime;
	Global_SetStateBinFault(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect,Global_IsLNFaultType(pImpParas->m_nFaultType[1]));
	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBTripTime,pImpParas->m_bCBSimulation);//跳合闸信号控制模式下,两次故障共用一个跳闸后持续时间

	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_AfterRecosePermanent(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	Global_FaultCalculatUI(pImpParas,0,pVol_Complex,pCur_Complex);
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fPostFaultTime;
	Global_SetStateBinFault(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect,Global_IsLNFaultType(pImpParas->m_nFaultType[1]));
	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBTripTime,pImpParas->m_bCBSimulation);//跳合闸信号控制模式下,两次故障共用一个跳闸后持续时间

// 	for (int i=1;i<MAX_BINARYIN_COUNT;i++)
// 	{
// 		pStatePara->m_binOut[i].fTimeTrig = 0;
// 	}

	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_AfterRecosePermanent(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,
														 Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng)
{
	Global_FaultCalculatUI(pImpParas,0,pVol_Complex,pCur_Complex);

	Complex p1;

	switch(pImpParas->m_nFaultType[0])
	{
	case IMPEDANCE_FAULT_TYPE_AN:
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_BN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_CN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		break;
	case IMPEDANCE_FAULT_TYPE_AB:
	case IMPEDANCE_FAULT_TYPE_ABN:
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_BC:
	case IMPEDANCE_FAULT_TYPE_BCN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		break;
	case IMPEDANCE_FAULT_TYPE_CA:
	case IMPEDANCE_FAULT_TYPE_CAN:
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		break;

	default:
		break;
	}

	pVol_Complex[3] = p1.polar(pfVolAmp[7],pfVolAng[7]);

//	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fPostFaultTime;
	Global_SetStateBinFault(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect,Global_IsLNFaultType(pImpParas->m_nFaultType[1]));
	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBTripTime,pImpParas->m_bCBSimulation);//跳合闸信号控制模式下,两次故障共用一个跳闸后持续时间

	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_TransFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	Global_FaultCalculatUI(pImpParas,1,pVol_Complex,pCur_Complex);
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fPostFaultTime;
	Global_SetStateBinFault(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect,Global_IsLNFaultType(pImpParas->m_nFaultType[1]));
	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBTripTime,pImpParas->m_bCBSimulation);//跳合闸信号控制模式下,两次故障共用一个跳闸后持续时间

// 	for (int i=1;i<MAX_BINARYIN_COUNT;i++)
// 	{
// 		pStatePara->m_binOut[i].fTimeTrig = 0;
// 	}

	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_TransFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,
											   Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng)
{
	Global_FaultCalculatUI(pImpParas,1,pVol_Complex,pCur_Complex);

	Complex p1;

	switch(pImpParas->m_nFaultType[1])
	{
	case IMPEDANCE_FAULT_TYPE_AN:
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_BN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_CN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		break;
	case IMPEDANCE_FAULT_TYPE_AB:
	case IMPEDANCE_FAULT_TYPE_ABN:
		pVol_Complex[2] = p1.polar(pfVolAmp[6],pfVolAng[6]);
		break;
	case IMPEDANCE_FAULT_TYPE_BC:
	case IMPEDANCE_FAULT_TYPE_BCN:
		pVol_Complex[0] = p1.polar(pfVolAmp[4],pfVolAng[4]);
		break;
	case IMPEDANCE_FAULT_TYPE_CA:
	case IMPEDANCE_FAULT_TYPE_CAN:
		pVol_Complex[1] = p1.polar(pfVolAmp[5],pfVolAng[5]);
		break;

	default:
		break;
	}

	pVol_Complex[3] = p1.polar(pfVolAmp[7],pfVolAng[7]);
//	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fPostFaultTime;
	Global_SetStateBinFault(pStatePara,pImpParas->m_nDInputState,pImpParas->m_nBinSelect,Global_IsLNFaultType(pImpParas->m_nFaultType[1]));
	pStatePara->m_fTimeAfterTrigger = m_oFaultCalculatTool.GetTimeAfterTrigger(pImpParas->m_fCBTripTime,pImpParas->m_bCBSimulation);//跳合闸信号控制模式下,两次故障共用一个跳闸后持续时间

	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_AccTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	if (pImpParas->m_nPTPoint == 0)//PT安装在母线侧,跳闸后电压恢复57.74
	{
		m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,fStdLN_Vol,0.0f);//计算故障前三相电压
	} 
	else//PT安装在线路侧,跳闸后电压0
	{
		m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,0,0.0f);//计算故障前三相电压
	}

//	m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,fStdLN_Vol,0.0f);//计算故障前三相电压
	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,0,-pImpParas->m_fPowerAngle);//计算故障前三相电流
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fRecloseTime;
	pStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

// 	for (int i=1;i<MAX_BINARYIN_COUNT;i++)
// 	{
// 		pStatePara->m_binOut[i].fTimeTrig = 0;
// 	}

	pStatePara->m_fTimeAfterTrigger = 0.0f;
	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_AccTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,
											Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng)
{
	Complex p1;

	if (pImpParas->m_nPTPoint == 0)//PT安装在母线侧,跳闸后电压恢复57.74
	{
		pVol_Complex[0] = p1.polar(pfVolAmp[0],pfVolAng[0]);
		pVol_Complex[1] = p1.polar(pfVolAmp[1],pfVolAng[1]);
		pVol_Complex[2] = p1.polar(pfVolAmp[2],pfVolAng[2]);
//		m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,fStdLN_Vol,0.0f);//计算故障前三相电压
	} 
	else//PT安装在线路侧,跳闸后电压0
	{
		m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,0,0.0f);//计算故障前三相电压
	}

	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,0,pfVolAng[0]-pImpParas->m_fPowerAngle);//计算故障前三相电流
	pVol_Complex[3] = p1.polar(pfVolAmp[3],pfVolAng[3]);
//	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = pImpParas->m_fRecloseTime;
	pStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

	pStatePara->m_fTimeAfterTrigger = 0.0f;
	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::SetStateParas_StopTest(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol)
{
	m_oFaultCalculatTool.CalPreFaultComplex(pVol_Complex,0,0.0f);//计算故障前三相电压
	m_oFaultCalculatTool.CalPreFaultComplex(pCur_Complex,0,-pImpParas->m_fPowerAngle);//计算故障前三相电流
	m_oFaultCalculatTool.Cal_VzAccordDefine_ImpBase(pImpParas->m_nVzDefine, pVol_Complex,pImpParas->m_nVzPhDefine,pImpParas->m_fUxInput_Ang);
	Global_SetStateUIFromCpl(pStatePara,pVol_Complex,pCur_Complex);
	pStatePara->m_fTimeState = m_pImpBaseParas->m_fImpBaseStopTime;
	pStatePara->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;

// 	for (int i=1;i<MAX_BINARYIN_COUNT;i++)
// 	{
// 		pStatePara->m_binOut[i].fTimeTrig = 0;
// 	}

	pStatePara->m_fTimeAfterTrigger = 0.0f;
	pStatePara->m_bDC = FALSE;
}

void CSttImpBaseTest::Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if (g_theSystemConfig->m_nHasDigital)
	{
		stt_xml_serialize(m_pImpBaseParas->m_pStateParas->m_paraState[0].m_oGoosePub,pXmlSerialize);//获取Gout信息,放入第一个状态的Gout中

		for (int nStateIndex = 1;nStateIndex<m_pImpBaseParas->m_pStateParas->m_nStateNumbers;nStateIndex++)
		{
			for(int nIndexCB = 0;nIndexCB<MAX_MODULES_GOOSEPUB_COUNT;nIndexCB++)
				m_pImpBaseParas->m_pStateParas->m_paraState[0].m_oGoosePub[nIndexCB].CopyOwn(
							&m_pImpBaseParas->m_pStateParas->m_paraState[nStateIndex].m_oGoosePub[nIndexCB]);
		}
	}
}

