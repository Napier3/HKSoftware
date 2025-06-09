#include "stdafx.h"
#include "SttSequenceManuTest.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

CString CSttSequenceManuTest::m_strMacroName = "通用试验(序分量)";
CString CSttSequenceManuTest::m_strMacroID = STT_MACRO_ID_SequenceManuTest;
CString CSttSequenceManuTest::m_strFilePostFix = "semtst";
CString CSttSequenceManuTest::m_strMacroVer = "1.0";

CSttSequenceManuTest::CSttSequenceManuTest()// : CSttManuTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
    m_pManualTest = stt_test_get_base_manualtest_buff();
}

void CSttSequenceManuTest::Init()
{
    CSttManuTest::Init();
    m_pManualTest->m_oManuParas.SetFundFreq(g_theSystemConfig->m_fFNom);//使用系统频率
    m_pManualTest->m_oManuParas.init();

    for(int nIndex = 0; nIndex < 18; nIndex++)
    {
        m_uiVOL[nIndex].init();
        m_uiCUR[nIndex].init();
    }

    m_oResults.init();
    m_oGradientParas.init();
    m_oGradientParas.SetAllFreq(g_theSystemConfig->m_fFNom);//初始化系统频率
    m_oGradientParas.m_nSttTestMode = GradientTest_Base;
}

CSttSequenceManuTest::~CSttSequenceManuTest(void)
{
}

void CSttSequenceManuTest::AfterSetParameter()
{
    CSttManuTest::AfterSetParameter();
}

long CSttSequenceManuTest::CalReport(UINT nState)
{
    return CSttManuTest::CalReport(nState);
}

void CSttSequenceManuTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_Sequence(&m_pManualTest->m_oManuParas, pXmlSerialize, m_uiVOL, m_uiCUR);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
		TranslateToStateParas();//参数设置完进行故障转换
        AfterSetParameter();

        Gouts_XmlSerialize(pXmlSerialize);       
    }
}

void CSttSequenceManuTest::SyncGradientResult(int nStep, double dTime, int nTripType)
{
#ifdef _PSX_QT_LINUX_
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
#endif
}

void CSttSequenceManuTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
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

        for(int j = 0; j < nrBinSwitchCount; j++)
        {
            m_pManualTest->m_oManuResult.m_frTimeBinAct[i][j] = oRampRestCom.m_frTimeBinAct[i][j];
        }
    }

    SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

    for(int i = 0; i < oSwitchModules.m_nModulesBiCount; i++)
    {
        nrBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[i];
        m_pManualTest->m_oManuResult.m_nrBinExSwitchCount[i] = nrBinExSwitchCount;

        for(int j = 0; j < nrBinExSwitchCount; j++)
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
    m_pManualTest->m_oManuResult.CopyOwn(&m_oResults);
    stt_xml_serialize(&m_oResults, pXmlSerialize);
}

long CSttSequenceManuTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttSequenceManuTest::TtmToDrv()
{
    if(m_pManualTest->m_oManuParas.m_bAuto)
    {
        m_nCurStepIndex = 0;
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_Gradient_NeedStepsValue(&m_oGradientParas);
#endif
    }
    else
    {
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_manu(m_pManualTest, TRUE);
#endif
    }
}

void CSttSequenceManuTest::TranslateToStateParas()
{
    //////////////////////////////////////////////////////////////////////////
    int nIndex = 0;
    tmt_channel *pCh_Vol = m_pManualTest->m_oManuParas.m_uiVOL;
    tmt_channel *pCh_Cur = m_pManualTest->m_oManuParas.m_uiCUR;

    //18U18I
    for(nIndex = 0; nIndex < 6; nIndex++)
    {
        CalABCValues_BySequenceValues_Float(pCh_Vol[nIndex * 3].Harm[1].fAmp, pCh_Vol[nIndex * 3].Harm[1].fAngle,
                                            pCh_Vol[nIndex * 3 + 1].Harm[1].fAmp, pCh_Vol[nIndex * 3 + 1].Harm[1].fAngle,
                                            pCh_Vol[nIndex * 3 + 2].Harm[1].fAmp, pCh_Vol[nIndex * 3 + 2].Harm[1].fAngle,
                                            m_uiVOL[nIndex * 3].Harm[1].fAmp, m_uiVOL[nIndex * 3].Harm[1].fAngle,
                                            m_uiVOL[nIndex * 3 + 1].Harm[1].fAmp, m_uiVOL[nIndex * 3 + 1].Harm[1].fAngle,
                                            m_uiVOL[nIndex * 3 + 2].Harm[1].fAmp, m_uiVOL[nIndex * 3 + 2].Harm[1].fAngle);
        pCh_Vol[nIndex * 3].Harm[1].fFreq = m_uiVOL[nIndex * 3].Harm[1].fFreq;
        pCh_Vol[nIndex * 3 + 1].Harm[1].fFreq = m_uiVOL[nIndex * 3 + 1].Harm[1].fFreq;
        pCh_Vol[nIndex * 3 + 2].Harm[1].fFreq = m_uiVOL[nIndex * 3 + 2].Harm[1].fFreq;
        CalABCValues_BySequenceValues_Float(pCh_Cur[nIndex * 3].Harm[1].fAmp, pCh_Cur[nIndex * 3].Harm[1].fAngle,
                                            pCh_Cur[nIndex * 3 + 1].Harm[1].fAmp, pCh_Cur[nIndex * 3 + 1].Harm[1].fAngle,
                                            pCh_Cur[nIndex * 3 + 2].Harm[1].fAmp, pCh_Cur[nIndex * 3 + 2].Harm[1].fAngle,
                                            m_uiCUR[nIndex * 3].Harm[1].fAmp, m_uiCUR[nIndex * 3].Harm[1].fAngle,
                                            m_uiCUR[nIndex * 3 + 1].Harm[1].fAmp, m_uiCUR[nIndex * 3 + 1].Harm[1].fAngle,
                                            m_uiCUR[nIndex * 3 + 2].Harm[1].fAmp, m_uiCUR[nIndex * 3 + 2].Harm[1].fAngle);
        pCh_Cur[nIndex * 3].Harm[1].fFreq = m_uiCUR[nIndex * 3].Harm[1].fFreq;
        pCh_Cur[nIndex * 3 + 1].Harm[1].fFreq = m_uiCUR[nIndex * 3 + 1].Harm[1].fFreq;
        pCh_Cur[nIndex * 3 + 2].Harm[1].fFreq = m_uiCUR[nIndex * 3 + 2].Harm[1].fFreq;
    }

    if(m_pManualTest->m_oManuParas.m_bAuto)
    {
        switch(m_pManualTest->m_oManuParas.m_nGradientChSelect)
        {
            case STT_Sequence_Gradient_Ch_U1_1:
            case STT_Sequence_Gradient_Ch_U1_2:
            case STT_Sequence_Gradient_Ch_U1_0:
            case STT_Sequence_Gradient_Ch_I1_1:
            case STT_Sequence_Gradient_Ch_I1_2:
            case STT_Sequence_Gradient_Ch_I1_0:
                break;

            default:
                m_pManualTest->m_oManuParas.m_nGradientChSelect = STT_Sequence_Gradient_Ch_U1_1;
        }

        m_oGradientParas.m_nBinLogic = m_pManualTest->m_oManuParas.m_nBinLogic;

        for(int j = 0; j < MAX_BINARYIN_COUNT; j++)
        {
            m_oGradientParas.m_binIn[j].nSelect =
                m_pManualTest->m_oManuParas.m_binIn[j].nSelect;
        }

        for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_oGradientParas.m_binInEx[j].nSelect =
                m_pManualTest->m_oManuParas.m_binInEx[j].nSelect;
        }

        for(int j = 0; j < MAX_BINARYOUT_COUNT; j++)
        {
            m_oGradientParas.m_binOut[1][j].nState =
                m_pManualTest->m_oManuParas.m_binOut[j].nState;
            m_oGradientParas.m_binOut[1][j].nMode =
                m_pManualTest->m_oManuParas.m_binOut[j].nMode;
            m_oGradientParas.m_binOut[1][j].fTimeTrig =
                m_pManualTest->m_oManuParas.m_binOut[j].fTimeTrig;
            m_oGradientParas.m_binOut[1][j].fHoldTime =
                m_pManualTest->m_oManuParas.m_binOut[j].fHoldTime;
        }

        for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_oGradientParas.m_binOutEx[1][j].nState =
                m_pManualTest->m_oManuParas.m_binOutEx[j].nState;
            m_oGradientParas.m_binOutEx[1][j].nMode =
                m_pManualTest->m_oManuParas.m_binOutEx[j].nMode;
            m_oGradientParas.m_binOutEx[1][j].fTimeTrig =
                m_pManualTest->m_oManuParas.m_binOutEx[j].fTimeTrig;
            m_oGradientParas.m_binOutEx[1][j].fHoldTime =
                m_pManualTest->m_oManuParas.m_binOutEx[j].fHoldTime;
        }

        for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
        {
            m_oGradientParas.m_oGoosePub[nIndex].m_bUseFlag =
                m_pManualTest->m_oManuParas.m_oGoosePub[nIndex].m_bUseFlag;
            m_oGradientParas.m_oGoosePub[nIndex].m_bHasTest =
                m_pManualTest->m_oManuParas.m_oGoosePub[nIndex].m_bHasTest;
            m_oGradientParas.m_oGoosePub[nIndex].m_nTest =
                m_pManualTest->m_oManuParas.m_oGoosePub[nIndex].m_nTest;

            for(int nCh = 0; nCh < MAX_GOOSE_CHANNEL_COUNT; nCh++)
            {
                m_oGradientParas.m_oGoosePub[nIndex].m_strChannel[nCh] =
                    m_pManualTest->m_oManuParas.m_oGoosePub[nIndex].m_strChannel[nCh];
            }
        }

        m_oGradientParas.m_nTestMode = m_pManualTest->m_oManuParas.m_manuGradient.nMode;
        m_oGradientParas.m_fStart = m_pManualTest->m_oManuParas.m_manuGradient.fStart;
        m_oGradientParas.m_fStop = m_pManualTest->m_oManuParas.m_manuGradient.fEnd;
        m_oGradientParas.m_fStep = m_pManualTest->m_oManuParas.m_manuGradient.fStep;
        m_oGradientParas.m_fStepTime = m_pManualTest->m_oManuParas.m_manuGradient.fStepTime;
        CalStepValue_SequenceChs(pCh_Vol, pCh_Cur, m_pManualTest->m_oManuParas.m_manuGradient.fStart);

        //设置故障前所有通道始值
        for(nIndex = 0; nIndex < 18; nIndex++)
        {
            m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAmp = pCh_Vol[nIndex].Harm[1].fAmp;
            m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fAngle = pCh_Vol[nIndex].Harm[1].fAngle;
            m_oGradientParas.m_uiVOL[1][nIndex].Harm[1].fFreq = pCh_Vol[nIndex].Harm[1].fFreq;
            m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAmp = pCh_Cur[nIndex].Harm[1].fAmp;
            m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fAngle = pCh_Cur[nIndex].Harm[1].fAngle;
            m_oGradientParas.m_uiCUR[1][nIndex].Harm[1].fFreq = pCh_Cur[nIndex].Harm[1].fFreq;
        }

#ifdef _PSX_QT_LINUX_
        memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bUChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);
        memset(CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess.m_bIChange, 0, sizeof(bool) * 3 * GRADIENT_CHAN_COUNT);

        tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

        switch(m_pManualTest->m_oManuParas.m_nGradientChSelect)
        {
            case STT_Sequence_Gradient_Ch_U1_1:
            case STT_Sequence_Gradient_Ch_U1_2:
            case STT_Sequence_Gradient_Ch_U1_0:
                pTmtGradientProcess->m_bUChange[0][0] = 1;
                pTmtGradientProcess->m_bUChange[1][0] = 1;
                pTmtGradientProcess->m_bUChange[2][0] = 1;
                pTmtGradientProcess->m_bUChange[0][1] = 1;
                pTmtGradientProcess->m_bUChange[1][1] = 1;
                pTmtGradientProcess->m_bUChange[2][1] = 1;
                break;

            case STT_Sequence_Gradient_Ch_I1_1:
            case STT_Sequence_Gradient_Ch_I1_2:
            case STT_Sequence_Gradient_Ch_I1_0:
                pTmtGradientProcess->m_bIChange[0][0] = 1;
                pTmtGradientProcess->m_bIChange[1][0] = 1;
                pTmtGradientProcess->m_bIChange[2][0] = 1;
                pTmtGradientProcess->m_bIChange[0][1] = 1;
                pTmtGradientProcess->m_bIChange[1][1] = 1;
                pTmtGradientProcess->m_bIChange[2][1] = 1;
                break;
        }

        CalStepValue_Gradient(&m_oGradientParas, 1, 3);
#endif
    }

    //////////////////////////////////////////////////////////////////////////
}

void CSttSequenceManuTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    if(!CheckBeforeUpdatePara())
    {
        return;
    }

    Para_XmlSerialize(pXmlSerialize);
    CSttTestBase::StartTest();//实验开始时间重新赋值
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Manu_UpdateParameter(m_pManualTest->m_oManuParas.m_bDC);
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_manu(m_pManualTest);
#endif
    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttSequenceManuTest::UpdatePara Finished");
}

void CSttSequenceManuTest::CalStepValue(tmt_GradientParas *pTmt_GradientParas, float fCurValue, int nHarmIndex)
{
    tmt_channel *pCh_Vol = m_pManualTest->m_oManuParas.m_uiVOL;
    tmt_channel *pCh_Cur = m_pManualTest->m_oManuParas.m_uiCUR;
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

void CSttSequenceManuTest::CalStepValue_SequenceChs(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue)
{
    double dPos_mag = 0.0f, dPos_ang = 0.0f, dNeg_mag = 0.0f, dNeg_ang = 0.0f;
    double dZero_mag = 0.0f, dZero_ang = 0.0f;
    tmt_channel *pCh_Gradient = pCh_Vol;
    tmt_channel *pCh_Sequence = m_uiVOL;

    switch(m_pManualTest->m_oManuParas.m_nGradientChSelect)
    {
        case STT_Sequence_Gradient_Ch_U1_1:
        case STT_Sequence_Gradient_Ch_U1_2:
        case STT_Sequence_Gradient_Ch_U1_0:
            pCh_Gradient = pCh_Vol;
            pCh_Sequence = m_uiVOL;
            break;

        case STT_Sequence_Gradient_Ch_I1_1:
        case STT_Sequence_Gradient_Ch_I1_2:
        case STT_Sequence_Gradient_Ch_I1_0:
            pCh_Gradient = pCh_Cur;
            pCh_Sequence = m_uiCUR;
            break;
    }

    dPos_mag = pCh_Sequence[0].Harm[1].fAmp;
    dPos_ang = pCh_Sequence[0].Harm[1].fAngle;
    dNeg_mag = pCh_Sequence[1].Harm[1].fAmp;
    dNeg_ang = pCh_Sequence[1].Harm[1].fAngle;
    dZero_mag = pCh_Sequence[2].Harm[1].fAmp;
    dZero_ang = pCh_Sequence[2].Harm[1].fAngle;

    switch(m_pManualTest->m_oManuParas.m_nGradientChSelect)
    {
        case STT_Sequence_Gradient_Ch_U1_1:
        case STT_Sequence_Gradient_Ch_I1_1:
        {
            if(m_pManualTest->m_oManuParas.m_nGradientTpSelect == GRADIENT_AMP)
            {
                dPos_mag = fCurValue;
            }
            else
            {
                dPos_ang = fCurValue;
            }
        }
        break;

        case STT_Sequence_Gradient_Ch_U1_2:
        case STT_Sequence_Gradient_Ch_I1_2:
        {
            if(m_pManualTest->m_oManuParas.m_nGradientTpSelect == GRADIENT_AMP)
            {
                dNeg_mag = fCurValue;
            }
            else
            {
                dNeg_ang = fCurValue;
            }
        }
        break;

        case STT_Sequence_Gradient_Ch_U1_0:
        case STT_Sequence_Gradient_Ch_I1_0:
        {
            if(m_pManualTest->m_oManuParas.m_nGradientTpSelect == GRADIENT_AMP)
            {
                dZero_mag = fCurValue;
            }
            else
            {
                dZero_ang = fCurValue;
            }
        }
        break;
    }

    CalABCValues_BySequenceValues_Float(pCh_Gradient[0].Harm[1].fAmp, pCh_Gradient[0].Harm[1].fAngle,
                                        pCh_Gradient[1].Harm[1].fAmp, pCh_Gradient[1].Harm[1].fAngle,
                                        pCh_Gradient[2].Harm[1].fAmp, pCh_Gradient[2].Harm[1].fAngle,
                                        dPos_mag, dPos_ang, dNeg_mag, dNeg_ang, dZero_mag, dZero_ang);
}

void CSttSequenceManuTest::ProRtDatasEvent(double dTime1, double dTime2, int nStep, int nState, int nType)
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

        if(nType == 0)
        {
            //变化前
            for(int nIndex = 0; nIndex < g_nRtDataVoltCnt; nIndex++)
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

            for(int nIndex = 0; nIndex < g_nRtDataCurrCnt; nIndex++)
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
            tmt_GradientProcess *pTmtGradientProcess = &CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;

			if((nStep <= pTmtGradientProcess->m_nStepCount) && (nStep < GRADIENT_MAX_COUNT))
            {
				for(int nIndex = 0; nIndex < 3; nIndex++)
                {
                    if(pTmtGradientProcess->m_bUChange[nIndex][0] == 0
                            && pTmtGradientProcess->m_bUChange[nIndex][1] == 0)
                    {
                        continue;
                    }

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
                    if(pTmtGradientProcess->m_bIChange[nIndex][0] == 0
                            && pTmtGradientProcess->m_bIChange[nIndex][1] == 0)
                    {
                        continue;
                    }

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
        }

#endif
    }

	UpdateMonitorCur(oRtdata);

    if(oRtdata.m_nCurChCount > 0 || oRtdata.m_nVolChCount > 0)
    {
        stt_add_rtdatas(oRtdata);
    }
}
