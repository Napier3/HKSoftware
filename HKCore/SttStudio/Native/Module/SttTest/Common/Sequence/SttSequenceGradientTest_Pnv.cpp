#include "stdafx.h"
#include "SttSequenceGradientTest_Pnv.h"
#include "../SttSystemConfig.h"

CString CSttSequenceGradientPnvTest::m_strMacroName = "序分量动作值测试(pnv)";
CString CSttSequenceGradientPnvTest::m_strMacroID = STT_MACRO_ID_PnvSCActValue;
CString CSttSequenceGradientPnvTest::m_strFilePostFix = "pnvGDT";
CString CSttSequenceGradientPnvTest::m_strMacroVer = "1.0";

CSttSequenceGradientPnvTest::CSttSequenceGradientPnvTest() : CSttSequenceGradientTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
}

CSttSequenceGradientPnvTest::~CSttSequenceGradientPnvTest(void)
{
}

void CSttSequenceGradientPnvTest::AfterSetParameter()
{
    m_oGradientParas.m_fStepTime += m_oGradientParas.m_fMarginTime;
    switch(m_oGradientParas.m_nChannel)
    {
        case VarPhaseV1:
        case VarPhaseV2:
        case VarPhaseV0:
        case VarPhaseI1:
        case VarPhaseI2:
        case VarPhaseI0:
            break;
        default:
            m_oGradientParas.m_nChannel = VarPhaseV1;
    }
    for(int i = 0;i<3;i++)
    {
        for(int j = 0;j<3;j++)
        {
            m_uiVOL[i][j].Harm[1].fFreq =g_theSystemConfig->m_fFNom;
            m_uiCUR[i][j].Harm[1].fFreq =g_theSystemConfig->m_fFNom;
            m_oGradientParas.m_uiVOL[i][j].Harm[1].fAmp = m_oGradientParas.m_uiVOL[0][j].Harm[1].fAmp;
            m_oGradientParas.m_uiVOL[i][j].Harm[1].fAngle = m_oGradientParas.m_uiVOL[0][j].Harm[1].fAngle;
            m_oGradientParas.m_uiCUR[i][j].Harm[1].fAmp = m_oGradientParas.m_uiCUR[0][j].Harm[1].fAmp;
            m_oGradientParas.m_uiCUR[i][j].Harm[1].fAngle = m_oGradientParas.m_uiCUR[0][j].Harm[1].fAngle;
        }
        m_oGradientParas.m_binOut[1][i+1].fHoldTime = m_oGradientParas.m_binOut[1][0].fHoldTime;
    }
}

void CSttSequenceGradientPnvTest::StartTest()
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

    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttSequenceGradientPnvTest::StartTest >>>>>>");
}

void CSttSequenceGradientPnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_sequence_pnv_serialize(&m_oGradientParas, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttSequenceGradientPnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
    GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
    m_oGradientResult.m_fTripValue = oRampRestCom.m_fTripValue;
    m_oGradientResult.m_nAct = oRampRestCom.m_nAct;
    m_oGradientResult.m_fReturnValue = oRampRestCom.m_fReturnValue;
    m_oGradientResult.m_fReturnCoef = oRampRestCom.m_fReturnCoef;

#endif
    stt_xml_sequence_pnv_serialize(&m_oGradientResult,  pXmlSerialize);
}

void CSttSequenceGradientPnvTest::CalStepValue_SequenceChs(tmt_channel *pCh_Vol, tmt_channel *pCh_Cur, float fCurValue)
{
    double dPos_mag = 0.0f, dPos_ang = 0.0f, dNeg_mag = 0.0f, dNeg_ang = 0.0f;
    double dZero_mag = 0.0f, dZero_ang = 0.0f;
    tmt_channel *pCh_Gradient = pCh_Vol;
    tmt_channel *pCh_Sequence = m_uiVOL[2];

    switch(m_oGradientParas.m_nChannel)
    {
        case VarPhaseV1:
        case VarPhaseV2:
        case VarPhaseV0:
            pCh_Gradient = pCh_Vol;
            pCh_Sequence = m_uiVOL[2];
            break;

        case VarPhaseI1:
        case VarPhaseI2:
        case VarPhaseI0:
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
        case VarPhaseV1:
        case VarPhaseI1:
            if(m_oGradientParas.m_nType == GRADIENT_AMP)
            {
                dPos_mag = fCurValue;
            }
            else
            {
                dPos_ang = fCurValue;
            }

            break;

        case VarPhaseV2:
        case VarPhaseI2:
            if(m_oGradientParas.m_nType == GRADIENT_AMP)
            {
                dNeg_mag = fCurValue;
            }
            else
            {
                dNeg_ang = fCurValue;
            }

            break;

        case VarPhaseV0:
        case VarPhaseI0:
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
