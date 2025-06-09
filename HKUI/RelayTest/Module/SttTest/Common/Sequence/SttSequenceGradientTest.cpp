#include "stdafx.h"
#include "SttSequenceGradientTest.h"
#include "../SttSystemConfig.h"

CString CSttSequenceGradientTest::m_strMacroName = "递变试验(序分量)";
CString CSttSequenceGradientTest::m_strMacroID = STT_MACRO_ID_SequenceGradientTest;
CString CSttSequenceGradientTest::m_strFilePostFix = "sttGDT";
CString CSttSequenceGradientTest::m_strMacroVer = "1.0";

CSttSequenceGradientTest::CSttSequenceGradientTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
}

void CSttSequenceGradientTest::Init()
{
    CSttTestBase::Init();

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            m_uiVOL[i][j].init();
            m_uiCUR[i][j].init();
        }
    }

    m_oGradientParas.init();
    m_oGradientParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
    m_oGradientResult.init();
}

CSttSequenceGradientTest::~CSttSequenceGradientTest(void)
{
}


void CSttSequenceGradientTest::AfterSetParameter()
{
    m_oGradientParas.m_fStepTime += m_oGradientParas.m_fMarginTime;
    switch(m_oGradientParas.m_nChannel)
    {
        case STT_Sequence_Gradient_Ch_U1_1:
        case STT_Sequence_Gradient_Ch_U1_2:
        case STT_Sequence_Gradient_Ch_U1_0:
        case STT_Sequence_Gradient_Ch_I1_1:
        case STT_Sequence_Gradient_Ch_I1_2:
        case STT_Sequence_Gradient_Ch_I1_0:
            break;

        default:
            m_oGradientParas.m_nChannel = STT_Sequence_Gradient_Ch_U1_1;
    }
}

double CSttSequenceGradientTest::GetTestTimeLong()
{
    float	fTime = 0.000;
    return fTime;
}

long CSttSequenceGradientTest::CalReport(UINT nState)
{
    return 0;
}

long CSttSequenceGradientTest::SetParameter(DWORD dwState)
{
    return 0;
}

BOOL CSttSequenceGradientTest::EventProcess()
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

void CSttSequenceGradientTest::StartTest()
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
        CSttDeviceBase::g_pSttDeviceBase->SetTestStart(GradientTest);
#endif
    }

    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttSequenceGradientTest::StartTest >>>>>>");
}

void CSttSequenceGradientTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_

    if(m_oGradientParas.m_fPrepareTime < EPSINON)
    {
        m_nCurStepIndex = 0;
    }

    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_Gradient_NeedStepsValue(&m_oGradientParas);
#endif
}

void CSttSequenceGradientTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_Sequence(&m_oGradientParas, pXmlSerialize, m_uiVOL[0], m_uiVOL[1], m_uiVOL[2],
                               m_uiCUR[0], m_uiCUR[1], m_uiCUR[2]);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttSequenceGradientTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
{
#ifdef _PSX_QT_LINUX_
    STT_RTDATA_EVENT oRtdata;
    oRtdata.oTime.dTime = dTime1;
    oRtdata.oTime.dRealTime = dTime2;
    oRtdata.m_nVolChCount = 0;
    oRtdata.m_nCurChCount = 0;
	oRtdata.m_nHasFaultVolCur=0;
    int nRtIndex = 0;
    float fVal;
	tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

    if(nType == 0)
    {
		if(m_oGradientParas.m_fPrepareTime > 0.0001)
		{
			//变化前
			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				nRtIndex = oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiVOL[0][nIndex].Harm[1].fFreq;
				oRtdata.m_nVolChCount++;
			}

			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				nRtIndex = oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiCUR[0][nIndex].Harm[1].fFreq;
				oRtdata.m_nCurChCount++;
			}
		}
		else if(m_oGradientParas.m_fPreFaultTime > 0.0001)
		{
			//变化前
			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				nRtIndex = oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp;
				oRtdata.m_oVolCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oVolCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq;
				oRtdata.m_nVolChCount++;
			}

			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				nRtIndex = oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag =
					m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp;
				oRtdata.m_oCurCh[nRtIndex].m_fAng =
					m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle;
				oRtdata.m_oCurCh[nRtIndex].m_fFreq =
					m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq;
				oRtdata.m_nCurChCount++;
			}
		}
		else
		{
			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				fVal = fabs(pTmtGradientProcess->m_uiStepData[0].fU[nIndex][0]);
				nRtIndex = oRtdata.m_nVolChCount;
				oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oVolCh[nRtIndex].m_fMag = fVal;
				oRtdata.m_oVolCh[nRtIndex].m_fAng =
					pTmtGradientProcess->m_uiStepData[0].fU[nIndex][1];
				oRtdata.m_oVolCh[nRtIndex].m_fFreq =
					pTmtGradientProcess->m_uiStepData[0].fU[nIndex][2];
				oRtdata.m_nVolChCount++;
			}

			for(int nIndex = 0; nIndex < 3; nIndex++)
			{
				fVal = fabs(pTmtGradientProcess->m_uiStepData[0].fI[nIndex][0]);
				nRtIndex = oRtdata.m_nCurChCount;
				oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
				oRtdata.m_oCurCh[nRtIndex].m_fMag = fVal;
				oRtdata.m_oCurCh[nRtIndex].m_fAng =
					pTmtGradientProcess->m_uiStepData[0].fI[nIndex][1];
				oRtdata.m_oCurCh[nRtIndex].m_fFreq =
					pTmtGradientProcess->m_uiStepData[0].fI[nIndex][2];
				oRtdata.m_nCurChCount++;
			}
		}
    }
    else
    {
		if((nStep <= pTmtGradientProcess->m_nStepCount) && (nStep < GRADIENT_MAX_COUNT))
        {
            if(nType == 2)
            {
                for(int nIndex = 0; nIndex < 3; nIndex++)
                {
                    fVal = fabs(pTmtGradientProcess->m_uiStepData[nStep].fU[nIndex][0]);
                    nRtIndex = oRtdata.m_nVolChCount;
                    oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
					oRtdata.m_oVolCh[nRtIndex].m_fMag = fVal;
					oRtdata.m_oVolCh[nRtIndex].m_fAng =
						pTmtGradientProcess->m_uiStepData[nStep].fU[nIndex][1];
					oRtdata.m_oVolCh[nRtIndex].m_fFreq =
						pTmtGradientProcess->m_uiStepData[nStep].fU[nIndex][2];
                    oRtdata.m_nVolChCount++;
                }

                for(int nIndex = 0; nIndex < 3; nIndex++)
                {
                    fVal = fabs(pTmtGradientProcess->m_uiStepData[nStep].fI[nIndex][0]);
                    nRtIndex = oRtdata.m_nCurChCount;
                    oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
					oRtdata.m_oCurCh[nRtIndex].m_fMag = fVal;
					oRtdata.m_oCurCh[nRtIndex].m_fAng =
						pTmtGradientProcess->m_uiStepData[nStep].fI[nIndex][1];
					oRtdata.m_oCurCh[nRtIndex].m_fFreq =
						pTmtGradientProcess->m_uiStepData[nStep].fI[nIndex][2];
					oRtdata.m_nCurChCount++;
                }
            }
            else
            {
                //故障前
                for(int nIndex = 0; nIndex < 3; nIndex++)
                {
                    nRtIndex = oRtdata.m_nVolChCount;
                    oRtdata.m_oVolCh[nRtIndex].m_nIndex = nIndex;
					oRtdata.m_oVolCh[nRtIndex].m_fMag =
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp;
					oRtdata.m_oVolCh[nRtIndex].m_fAng =
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle;
					oRtdata.m_oVolCh[nRtIndex].m_fFreq =
						m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq;
                    oRtdata.m_nVolChCount++;
                }

                for(int nIndex = 0; nIndex < 3; nIndex++)
                {
                    nRtIndex = oRtdata.m_nCurChCount;
                    oRtdata.m_oCurCh[nRtIndex].m_nIndex = nIndex;
					oRtdata.m_oCurCh[nRtIndex].m_fMag =
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp;
					oRtdata.m_oCurCh[nRtIndex].m_fAng =
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle;
					oRtdata.m_oCurCh[nRtIndex].m_fFreq =
						m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq;
					oRtdata.m_nCurChCount++;
                }
            }
        }
    }

	UpdateMonitorCur(oRtdata);

    if(oRtdata.m_nCurChCount > 0 || oRtdata.m_nVolChCount > 0)
    {
        stt_add_rtdatas(oRtdata);
    }

#endif
}

void CSttSequenceGradientTest::SyncGradientResult(int nStep, double dTime, int nTripType)
{
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    long nDirection = 1;

    if(m_oGradientParas.m_fStart > m_oGradientParas.m_fStop)
    {
        nDirection = -1;
    }

    tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
    float fUIStepValue;

    if(nStep == pTmtGradientProcess->m_nStepCount)
    {
        fUIStepValue = m_oGradientParas.m_fStop;
    }
    else
    {
        fUIStepValue = m_oGradientParas.m_fStart + m_oGradientParas.m_fStep * nDirection * nStep;
    }

    if(nTripType == 0)
    {
        oRampRestCom.m_fTripValue = fUIStepValue;
        oRampRestCom.m_fTripTime = dTime;
    }
    else
    {
        oRampRestCom.m_fReturnValue = fUIStepValue;
        oRampRestCom.m_fReturnTime = dTime;

        if(fabs(oRampRestCom.m_fTripValue) < EPSINON)
        {
            oRampRestCom.m_fReturnCoef = 0;
        }
        else
        {
            oRampRestCom.m_fReturnCoef = oRampRestCom.m_fReturnValue / oRampRestCom.m_fTripValue; //返回值/动作值
        }
    }
}

void CSttSequenceGradientTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_oGradientResult.m_fTripValue = oRampRestCom.m_fTripValue;
    m_oGradientResult.m_nAct = oRampRestCom.m_nAct;
    m_oGradientResult.m_fReturnValue = oRampRestCom.m_fReturnValue;
    m_oGradientResult.m_fReturnCoef = oRampRestCom.m_fReturnCoef;
    m_oGradientResult.m_fTripTime = oRampRestCom.m_fTripTime; //zhouhj 20211125 记录动作时间

    for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
    {
        m_oGradientResult.m_fTripValueChl[i] = oRampRestCom.m_fTripValueChl[i];
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
        m_oGradientResult.m_fTripValueExChl[i] = oRampRestCom.m_fTripValueChlEx[i];
    }

#endif
	stt_xml_sequence_serialize(&m_oGradientResult,  pXmlSerialize);
}

void CSttSequenceGradientTest::Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if(g_theSystemConfig->m_nHasDigital)
    {
        stt_xml_serialize(m_oGradientParas.m_oGoosePub, pXmlSerialize); //获取Gout信息
    }
}

void CSttSequenceGradientTest::TranslateToStateParas()
{
    //////////////////////////////////////////////////////////////////////////
    tmt_channel *pCh_Vol, *pCh_Cur;
    //Prepare
    pCh_Vol = m_oGradientParas.m_uiVOL[0];
    pCh_Cur = m_oGradientParas.m_uiCUR[0];
    //3U3I
    CalABCValues_BySequenceValues_Float(pCh_Vol[0].Harm[1].fAmp, pCh_Vol[0].Harm[1].fAngle,
                                        pCh_Vol[1].Harm[1].fAmp, pCh_Vol[1].Harm[1].fAngle,
                                        pCh_Vol[2].Harm[1].fAmp, pCh_Vol[2].Harm[1].fAngle,
                                        m_uiVOL[0][0].Harm[1].fAmp, m_uiVOL[0][0].Harm[1].fAngle,
                                        m_uiVOL[0][1].Harm[1].fAmp, m_uiVOL[0][1].Harm[1].fAngle,
                                        m_uiVOL[0][2].Harm[1].fAmp, m_uiVOL[0][2].Harm[1].fAngle);
    pCh_Vol[0].Harm[1].fFreq = m_uiVOL[0][0].Harm[1].fFreq;
    pCh_Vol[1].Harm[1].fFreq = m_uiVOL[0][1].Harm[1].fFreq;
    pCh_Vol[2].Harm[1].fFreq = m_uiVOL[0][2].Harm[1].fFreq;
    CalABCValues_BySequenceValues_Float(pCh_Cur[0].Harm[1].fAmp, pCh_Cur[0].Harm[1].fAngle,
                                        pCh_Cur[1].Harm[1].fAmp, pCh_Cur[1].Harm[1].fAngle,
                                        pCh_Cur[2].Harm[1].fAmp, pCh_Cur[2].Harm[1].fAngle,
                                        m_uiCUR[0][0].Harm[1].fAmp, m_uiCUR[0][0].Harm[1].fAngle,
                                        m_uiCUR[0][1].Harm[1].fAmp, m_uiCUR[0][1].Harm[1].fAngle,
                                        m_uiCUR[0][2].Harm[1].fAmp, m_uiCUR[0][2].Harm[1].fAngle);
    pCh_Cur[0].Harm[1].fFreq = m_uiCUR[0][0].Harm[1].fFreq;
    pCh_Cur[1].Harm[1].fFreq = m_uiCUR[0][1].Harm[1].fFreq;
    pCh_Cur[2].Harm[1].fFreq = m_uiCUR[0][2].Harm[1].fFreq;
    //Prefault
    pCh_Vol = m_oGradientParas.m_uiVOL[1];
    pCh_Cur = m_oGradientParas.m_uiCUR[1];
    //3U3I
    CalABCValues_BySequenceValues_Float(pCh_Vol[0].Harm[1].fAmp, pCh_Vol[0].Harm[1].fAngle,
                                        pCh_Vol[1].Harm[1].fAmp, pCh_Vol[1].Harm[1].fAngle,
                                        pCh_Vol[2].Harm[1].fAmp, pCh_Vol[2].Harm[1].fAngle,
                                        m_uiVOL[1][0].Harm[1].fAmp, m_uiVOL[1][0].Harm[1].fAngle,
                                        m_uiVOL[1][1].Harm[1].fAmp, m_uiVOL[1][1].Harm[1].fAngle,
                                        m_uiVOL[1][2].Harm[1].fAmp, m_uiVOL[1][2].Harm[1].fAngle);
    pCh_Vol[0].Harm[1].fFreq = m_uiVOL[1][0].Harm[1].fFreq;
    pCh_Vol[1].Harm[1].fFreq = m_uiVOL[1][1].Harm[1].fFreq;
    pCh_Vol[2].Harm[1].fFreq = m_uiVOL[1][2].Harm[1].fFreq;
    CalABCValues_BySequenceValues_Float(pCh_Cur[0].Harm[1].fAmp, pCh_Cur[0].Harm[1].fAngle,
                                        pCh_Cur[1].Harm[1].fAmp, pCh_Cur[1].Harm[1].fAngle,
                                        pCh_Cur[2].Harm[1].fAmp, pCh_Cur[2].Harm[1].fAngle,
                                        m_uiCUR[1][0].Harm[1].fAmp, m_uiCUR[1][0].Harm[1].fAngle,
                                        m_uiCUR[1][1].Harm[1].fAmp, m_uiCUR[1][1].Harm[1].fAngle,
                                        m_uiCUR[1][2].Harm[1].fAmp, m_uiCUR[1][2].Harm[1].fAngle);
    pCh_Cur[0].Harm[1].fFreq = m_uiCUR[1][0].Harm[1].fFreq;
    pCh_Cur[1].Harm[1].fFreq = m_uiCUR[1][1].Harm[1].fFreq;
    pCh_Cur[2].Harm[1].fFreq = m_uiCUR[1][2].Harm[1].fFreq;
    //Fault
    pCh_Vol = m_oGradientParas.m_uiVOL[2];
    pCh_Cur = m_oGradientParas.m_uiCUR[2];
    //3U3I
    CalABCValues_BySequenceValues_Float(pCh_Vol[0].Harm[1].fAmp, pCh_Vol[0].Harm[1].fAngle,
                                        pCh_Vol[1].Harm[1].fAmp, pCh_Vol[1].Harm[1].fAngle,
                                        pCh_Vol[2].Harm[1].fAmp, pCh_Vol[2].Harm[1].fAngle,
                                        m_uiVOL[2][0].Harm[1].fAmp, m_uiVOL[2][0].Harm[1].fAngle,
                                        m_uiVOL[2][1].Harm[1].fAmp, m_uiVOL[2][1].Harm[1].fAngle,
                                        m_uiVOL[2][2].Harm[1].fAmp, m_uiVOL[2][2].Harm[1].fAngle);
    pCh_Vol[0].Harm[1].fFreq = m_uiVOL[2][0].Harm[1].fFreq;
    pCh_Vol[1].Harm[1].fFreq = m_uiVOL[2][1].Harm[1].fFreq;
    pCh_Vol[2].Harm[1].fFreq = m_uiVOL[2][2].Harm[1].fFreq;
    CalABCValues_BySequenceValues_Float(pCh_Cur[0].Harm[1].fAmp, pCh_Cur[0].Harm[1].fAngle,
                                        pCh_Cur[1].Harm[1].fAmp, pCh_Cur[1].Harm[1].fAngle,
                                        pCh_Cur[2].Harm[1].fAmp, pCh_Cur[2].Harm[1].fAngle,
                                        m_uiCUR[2][0].Harm[1].fAmp, m_uiCUR[2][0].Harm[1].fAngle,
                                        m_uiCUR[2][1].Harm[1].fAmp, m_uiCUR[2][1].Harm[1].fAngle,
                                        m_uiCUR[2][2].Harm[1].fAmp, m_uiCUR[2][2].Harm[1].fAngle);
    pCh_Cur[0].Harm[1].fFreq = m_uiCUR[2][0].Harm[1].fFreq;
    pCh_Cur[1].Harm[1].fFreq = m_uiCUR[2][1].Harm[1].fFreq;
    pCh_Cur[2].Harm[1].fFreq = m_uiCUR[2][2].Harm[1].fFreq;
    CalStepValue_SequenceChs(pCh_Vol, pCh_Cur, m_oGradientParas.m_fStart);
#ifdef _PSX_QT_LINUX_
    memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bUChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
    memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bIChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
#endif
    tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

    //保证故障所有通道刷新一遍
    for(int i = 0; i < 3; i++)
    {
        pTmtGradientProcess->m_bUChange[i][0] = 1;
        pTmtGradientProcess->m_bIChange[i][0] = 1;
        pTmtGradientProcess->m_bUChange[i][1] = 1;
        pTmtGradientProcess->m_bIChange[i][1] = 1;
    }

    CalStepValue_Gradient(&m_oGradientParas, 1, 3);
    //////////////////////////////////////////////////////////////////////////
}

void CSttSequenceGradientTest::CalStepValue_SequenceChs(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue)
{
    double dPos_mag = 0.0f, dPos_ang = 0.0f, dNeg_mag = 0.0f, dNeg_ang = 0.0f;
    double dZero_mag = 0.0f, dZero_ang = 0.0f;
    tmt_channel *pCh_Gradient = pCh_Vol;
    tmt_channel *pCh_Sequence = m_uiVOL[2];

    switch(m_oGradientParas.m_nChannel)
    {
        case STT_Sequence_Gradient_Ch_U1_1:
        case STT_Sequence_Gradient_Ch_U1_2:
        case STT_Sequence_Gradient_Ch_U1_0:
            pCh_Gradient = pCh_Vol;
            pCh_Sequence = m_uiVOL[2];
            break;

        case STT_Sequence_Gradient_Ch_I1_1:
        case STT_Sequence_Gradient_Ch_I1_2:
        case STT_Sequence_Gradient_Ch_I1_0:
            pCh_Gradient = pCh_Cur;
            pCh_Sequence = m_uiCUR[2];
            break;
    }

    dPos_mag = pCh_Sequence[0].Harm[1].fAmp;
    dPos_ang = pCh_Sequence[0].Harm[1].fAngle;
    dNeg_mag = pCh_Sequence[1].Harm[1].fAmp;
    dNeg_ang = pCh_Sequence[1].Harm[1].fAngle;
    dZero_mag = pCh_Sequence[2].Harm[1].fAmp;
    dZero_ang = pCh_Sequence[2].Harm[1].fAngle;

    switch(m_oGradientParas.m_nChannel)
    {
        case STT_Sequence_Gradient_Ch_U1_1:
        case STT_Sequence_Gradient_Ch_I1_1:
            if(m_oGradientParas.m_nType == GRADIENT_AMP)
            {
                dPos_mag = fCurValue;
            }
            else
            {
                dPos_ang = fCurValue;
            }

            break;

        case STT_Sequence_Gradient_Ch_U1_2:
        case STT_Sequence_Gradient_Ch_I1_2:
            if(m_oGradientParas.m_nType == GRADIENT_AMP)
            {
                dNeg_mag = fCurValue;
            }
            else
            {
                dNeg_ang = fCurValue;
            }

            break;

        case STT_Sequence_Gradient_Ch_U1_0:
        case STT_Sequence_Gradient_Ch_I1_0:
            if(m_oGradientParas.m_nType == GRADIENT_AMP)
            {
                dZero_mag = fCurValue;
            }
            else
            {
                dZero_ang = fCurValue;
            }

            break;
    }

    CalABCValues_BySequenceValues_Float(pCh_Gradient[0].Harm[1].fAmp, pCh_Gradient[0].Harm[1].fAngle,
                                        pCh_Gradient[1].Harm[1].fAmp, pCh_Gradient[1].Harm[1].fAngle,
                                        pCh_Gradient[2].Harm[1].fAmp, pCh_Gradient[2].Harm[1].fAngle,
                                        dPos_mag, dPos_ang, dNeg_mag, dNeg_ang, dZero_mag, dZero_ang);
}

void CSttSequenceGradientTest::CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex)
{
    tmt_channel *pCh_Vol = m_oGradientParas.m_uiVOL[2];
    tmt_channel *pCh_Cur = m_oGradientParas.m_uiCUR[2];
    pTmt_GradientParas->m_uiVOL[2][0].Harm[1].fAmp = pCh_Vol[0].Harm[1].fAmp;
    pTmt_GradientParas->m_uiVOL[2][1].Harm[1].fAmp = pCh_Vol[1].Harm[1].fAmp;
    pTmt_GradientParas->m_uiVOL[2][2].Harm[1].fAmp = pCh_Vol[2].Harm[1].fAmp;
    pTmt_GradientParas->m_uiVOL[2][0].Harm[1].fAngle = pCh_Vol[0].Harm[1].fAngle;
    pTmt_GradientParas->m_uiVOL[2][1].Harm[1].fAngle = pCh_Vol[1].Harm[1].fAngle;
    pTmt_GradientParas->m_uiVOL[2][2].Harm[1].fAngle = pCh_Vol[2].Harm[1].fAngle;
    pTmt_GradientParas->m_uiCUR[2][0].Harm[1].fAmp = pCh_Cur[0].Harm[1].fAmp;
    pTmt_GradientParas->m_uiCUR[2][1].Harm[1].fAmp = pCh_Cur[1].Harm[1].fAmp;
    pTmt_GradientParas->m_uiCUR[2][2].Harm[1].fAmp = pCh_Cur[2].Harm[1].fAmp;
    pTmt_GradientParas->m_uiCUR[2][0].Harm[1].fAngle = pCh_Cur[0].Harm[1].fAngle;
    pTmt_GradientParas->m_uiCUR[2][1].Harm[1].fAngle = pCh_Cur[1].Harm[1].fAngle;
    pTmt_GradientParas->m_uiCUR[2][2].Harm[1].fAngle = pCh_Cur[2].Harm[1].fAngle;
    CalStepValue_SequenceChs(pTmt_GradientParas->m_uiVOL[2], pTmt_GradientParas->m_uiCUR[2], fCurValue);
}
