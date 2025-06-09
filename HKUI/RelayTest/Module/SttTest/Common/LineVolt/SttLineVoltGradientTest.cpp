#include "stdafx.h"
#include "SttLineVoltGradientTest.h"
#include "../SttSystemConfig.h"

CString CSttLineVoltGradientTest::m_strMacroName = "递变试验(线电压项电流)";
CString CSttLineVoltGradientTest::m_strMacroID = STT_MACRO_ID_LineVolGradientTest;
CString CSttLineVoltGradientTest::m_strFilePostFix = "sttGDT";
CString CSttLineVoltGradientTest::m_strMacroVer = "1.0";

CSttLineVoltGradientTest::CSttLineVoltGradientTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
}

void CSttLineVoltGradientTest::Init()
{
    CSttTestBase::Init();

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            m_uiVOL[i][j].init();
        }

        for(int j = 0; j < 6; j++)
        {
            m_uiCUR[i][j].init();
        }
    }

    m_oGradientParas.init();
    m_oGradientParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
    m_oGradientResult.init();
}

CSttLineVoltGradientTest::~CSttLineVoltGradientTest(void)
{
}


void CSttLineVoltGradientTest::AfterSetParameter()
{
}

double CSttLineVoltGradientTest::GetTestTimeLong()
{
    float	fTime = 0.000;
    return fTime;
}

long CSttLineVoltGradientTest::CalReport(UINT nState)
{
    return 0;
}

long CSttLineVoltGradientTest::SetParameter(DWORD dwState)
{
    return 0;
}

BOOL CSttLineVoltGradientTest::EventProcess()
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

void CSttLineVoltGradientTest::StartTest()
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

    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttLineVoltGradientTest::StartTest >>>>>>");
}

void CSttLineVoltGradientTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_

    if(m_oGradientParas.m_fPrepareTime < EPSINON)
    {
        m_nCurStepIndex = 0;
    }

    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_Gradient_NeedStepsValue(&m_oGradientParas);
#endif
}

void CSttLineVoltGradientTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_linevolt(&m_oGradientParas, pXmlSerialize, m_uiVOL[0], m_uiVOL[1], m_uiVOL[2], m_uiCUR[0], m_uiCUR[1], m_uiCUR[2]);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttLineVoltGradientTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
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

void CSttLineVoltGradientTest::SyncGradientResult(int nStep, double dTime, int nTripType)
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

void CSttLineVoltGradientTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
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
    stt_xml_serialize_LineVol(&m_oGradientResult,  pXmlSerialize);
}

void CSttLineVoltGradientTest::Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if(g_theSystemConfig->m_nHasDigital)
    {
        stt_xml_serialize(m_oGradientParas.m_oGoosePub, pXmlSerialize); //获取Gout信息
    }
}

void CSttLineVoltGradientTest::TranslateToStateParas()
{
    switch(m_oGradientParas.m_nChannel)
    {
        case STT_LINEVOLT_Gradient_Ch_Uab1:
        case STT_LINEVOLT_Gradient_Ch_3U0_1:
        case STT_LINEVOLT_Gradient_Ch_Uab2:
        case STT_LINEVOLT_Gradient_Ch_3U0_2:
        case STT_LINEVOLT_Gradient_Ch_Ia1:
        case STT_LINEVOLT_Gradient_Ch_Ib1:
        case STT_LINEVOLT_Gradient_Ch_Ic1:
        case STT_LINEVOLT_Gradient_Ch_Ia2:
        case STT_LINEVOLT_Gradient_Ch_Ib2:
        case STT_LINEVOLT_Gradient_Ch_Ic2:
            break;

        default:
            m_oGradientParas.m_nChannel = STT_LINEVOLT_Gradient_Ch_Uab1;
    }

    //////////////////////////////////////////////////////////////////////////
    tmt_channel *pCh_Vol;
    //Prepare
    pCh_Vol = m_oGradientParas.m_uiVOL[0];
    CalABCValues_Bylinevolt_Float(pCh_Vol[0].Harm[1].fAmp, pCh_Vol[0].Harm[1].fAngle,
                                  pCh_Vol[1].Harm[1].fAmp, pCh_Vol[1].Harm[1].fAngle,
                                  pCh_Vol[2].Harm[1].fAmp, pCh_Vol[2].Harm[1].fAngle,
                                  m_uiVOL[0][0].Harm[1].fAmp, m_uiVOL[0][0].Harm[1].fAngle,
                                  m_uiVOL[0][1].Harm[1].fAmp, m_uiVOL[0][1].Harm[1].fAngle);
    CalABCValues_Bylinevolt_Float(pCh_Vol[3].Harm[1].fAmp, pCh_Vol[3].Harm[1].fAngle,
                                  pCh_Vol[4].Harm[1].fAmp, pCh_Vol[4].Harm[1].fAngle,
                                  pCh_Vol[5].Harm[1].fAmp, pCh_Vol[5].Harm[1].fAngle,
                                  m_uiVOL[0][2].Harm[1].fAmp, m_uiVOL[0][2].Harm[1].fAngle,
                                  m_uiVOL[0][3].Harm[1].fAmp, m_uiVOL[0][3].Harm[1].fAngle);

    for(int i = 0; i < 6; i++)
    {
        pCh_Vol[i].Harm[1].fFreq = m_uiVOL[0][i].Harm[1].fFreq;
        m_oGradientParas.m_uiCUR[0][i].Harm[1].fAmp = m_uiCUR[0][i].Harm[1].fAmp;
        m_oGradientParas.m_uiCUR[0][i].Harm[1].fAngle = m_uiCUR[0][i].Harm[1].fAngle;
        m_oGradientParas.m_uiCUR[0][i].Harm[1].fFreq = m_uiCUR[0][i].Harm[1].fFreq;
    }

    //Prefault
    pCh_Vol = m_oGradientParas.m_uiVOL[1];
    //3U3I
    CalABCValues_Bylinevolt_Float(pCh_Vol[0].Harm[1].fAmp, pCh_Vol[0].Harm[1].fAngle,
                                  pCh_Vol[1].Harm[1].fAmp, pCh_Vol[1].Harm[1].fAngle,
                                  pCh_Vol[2].Harm[1].fAmp, pCh_Vol[2].Harm[1].fAngle,
                                  m_uiVOL[1][0].Harm[1].fAmp, m_uiVOL[1][0].Harm[1].fAngle,
                                  m_uiVOL[1][1].Harm[1].fAmp, m_uiVOL[1][1].Harm[1].fAngle);
    CalABCValues_Bylinevolt_Float(pCh_Vol[3].Harm[1].fAmp, pCh_Vol[3].Harm[1].fAngle,
                                  pCh_Vol[4].Harm[1].fAmp, pCh_Vol[4].Harm[1].fAngle,
                                  pCh_Vol[5].Harm[1].fAmp, pCh_Vol[5].Harm[1].fAngle,
                                  m_uiVOL[1][2].Harm[1].fAmp, m_uiVOL[1][2].Harm[1].fAngle,
                                  m_uiVOL[1][3].Harm[1].fAmp, m_uiVOL[1][3].Harm[1].fAngle);

    for(int i = 0; i < 6; i++)
    {
        pCh_Vol[i].Harm[1].fFreq = m_uiVOL[1][i].Harm[1].fFreq;
        m_oGradientParas.m_uiCUR[1][i].Harm[1].fAmp = m_uiCUR[1][i].Harm[1].fAmp;
        m_oGradientParas.m_uiCUR[1][i].Harm[1].fAngle = m_uiCUR[1][i].Harm[1].fAngle;
        m_oGradientParas.m_uiCUR[1][i].Harm[1].fFreq = m_uiCUR[1][i].Harm[1].fFreq;
    }

    //Fault
    pCh_Vol = m_oGradientParas.m_uiVOL[2];
    //3U3I
    CalABCValues_Bylinevolt_Float(pCh_Vol[0].Harm[1].fAmp, pCh_Vol[0].Harm[1].fAngle,
                                  pCh_Vol[1].Harm[1].fAmp, pCh_Vol[1].Harm[1].fAngle,
                                  pCh_Vol[2].Harm[1].fAmp, pCh_Vol[2].Harm[1].fAngle,
                                  m_uiVOL[2][0].Harm[1].fAmp, m_uiVOL[2][0].Harm[1].fAngle,
                                  m_uiVOL[2][1].Harm[1].fAmp, m_uiVOL[2][1].Harm[1].fAngle);
    CalABCValues_Bylinevolt_Float(pCh_Vol[3].Harm[1].fAmp, pCh_Vol[3].Harm[1].fAngle,
                                  pCh_Vol[4].Harm[1].fAmp, pCh_Vol[4].Harm[1].fAngle,
                                  pCh_Vol[5].Harm[1].fAmp, pCh_Vol[5].Harm[1].fAngle,
                                  m_uiVOL[2][2].Harm[1].fAmp, m_uiVOL[2][2].Harm[1].fAngle,
                                  m_uiVOL[2][3].Harm[1].fAmp, m_uiVOL[2][3].Harm[1].fAngle);

    for(int i = 0; i < 6; i++)
    {
        pCh_Vol[i].Harm[1].fFreq = m_uiVOL[2][i].Harm[1].fFreq;
        m_oGradientParas.m_uiCUR[2][i].Harm[1].fAmp = m_uiCUR[2][i].Harm[1].fAmp;
        m_oGradientParas.m_uiCUR[2][i].Harm[1].fAngle = m_uiCUR[2][i].Harm[1].fAngle;
        m_oGradientParas.m_uiCUR[2][i].Harm[1].fFreq = m_uiCUR[2][i].Harm[1].fFreq;
    }

    CalStepValue_Chs(pCh_Vol, m_oGradientParas.m_uiCUR[2], m_oGradientParas.m_fStart);
#ifdef _PSX_QT_LINUX_
    memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bUChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
    memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bIChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
#endif
    tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

    for(int i = 0; i < 6; i++)
    {
        //保证故障所有通道刷新一遍
        pTmtGradientProcess->m_bUChange[i][0] = 1;
        pTmtGradientProcess->m_bUChange[i][1] = 1;
        pTmtGradientProcess->m_bIChange[i][0] = 1;
    }

    CalStepValue_Gradient(&m_oGradientParas, 1, 3);
    //////////////////////////////////////////////////////////////////////////
}

void CSttLineVoltGradientTest::CalStepValue_Chs(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue)
{
    switch(m_oGradientParas.m_nChannel)
    {
        case STT_LINEVOLT_Gradient_Ch_Uab1:
        {
            CalABCValues_Bylinevolt_Float(pCh_Vol[0].Harm[1].fAmp, pCh_Vol[0].Harm[1].fAngle,
                                          pCh_Vol[1].Harm[1].fAmp, pCh_Vol[1].Harm[1].fAngle,
                                          pCh_Vol[2].Harm[1].fAmp, pCh_Vol[2].Harm[1].fAngle,
                                          fCurValue, m_uiVOL[2][0].Harm[1].fAngle,
                                          m_uiVOL[2][1].Harm[1].fAmp, m_uiVOL[2][1].Harm[1].fAngle);
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_3U0_1:
        {
            CalABCValues_Bylinevolt_Float(pCh_Vol[0].Harm[1].fAmp, pCh_Vol[0].Harm[1].fAngle,
                                          pCh_Vol[1].Harm[1].fAmp, pCh_Vol[1].Harm[1].fAngle,
                                          pCh_Vol[2].Harm[1].fAmp, pCh_Vol[2].Harm[1].fAngle,
                                          m_uiVOL[2][0].Harm[1].fAmp, m_uiVOL[2][0].Harm[1].fAngle,
                                          fCurValue, m_uiVOL[2][1].Harm[1].fAngle);
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_Uab2:
        {
            CalABCValues_Bylinevolt_Float(pCh_Vol[3].Harm[1].fAmp, pCh_Vol[3].Harm[1].fAngle,
                                          pCh_Vol[4].Harm[1].fAmp, pCh_Vol[4].Harm[1].fAngle,
                                          pCh_Vol[5].Harm[1].fAmp, pCh_Vol[5].Harm[1].fAngle,
                                          fCurValue, m_uiVOL[2][2].Harm[1].fAngle,
                                          m_uiVOL[2][3].Harm[1].fAmp, m_uiVOL[2][3].Harm[1].fAngle);
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_3U0_2:
        {
            CalABCValues_Bylinevolt_Float(pCh_Vol[3].Harm[1].fAmp, pCh_Vol[3].Harm[1].fAngle,
                                          pCh_Vol[4].Harm[1].fAmp, pCh_Vol[4].Harm[1].fAngle,
                                          pCh_Vol[5].Harm[1].fAmp, pCh_Vol[5].Harm[1].fAngle,
                                          m_uiVOL[2][2].Harm[1].fAmp, m_uiVOL[2][2].Harm[1].fAngle,
                                          fCurValue, m_uiVOL[2][3].Harm[1].fAngle);
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_Ia1:
        {
            pCh_Cur[0].Harm[1].fAmp = fCurValue;
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_Ib1:
        {
            pCh_Cur[1].Harm[1].fAmp = fCurValue;
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_Ic1:
        {
            pCh_Cur[2].Harm[1].fAmp = fCurValue;
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_Ia2:
        {
            pCh_Cur[3].Harm[1].fAmp = fCurValue;
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_Ib2:
        {
            pCh_Cur[4].Harm[1].fAmp = fCurValue;
        }
        break;

        case STT_LINEVOLT_Gradient_Ch_Ic2:
        {
            pCh_Cur[5].Harm[1].fAmp = fCurValue;
        }
        break;
    }
}

void CSttLineVoltGradientTest::CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex)
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
    CalStepValue_Chs(pTmt_GradientParas->m_uiVOL[2], pTmt_GradientParas->m_uiCUR[2], fCurValue);
}
