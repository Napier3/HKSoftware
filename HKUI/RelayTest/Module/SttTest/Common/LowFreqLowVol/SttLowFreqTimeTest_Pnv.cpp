#include "SttLowFreqTimeTest_Pnv.h"
#include "stdafx.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
    #include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowFreqTimePnvTest::m_strMacroName = "低周动作时间测试(Pnv)";
CString CSttLowFreqTimePnvTest::m_strMacroID = STT_MACRO_ID_PnvLowFreqTime;
CString CSttLowFreqTimePnvTest::m_strFilePostFix = "pnvlft";
CString CSttLowFreqTimePnvTest::m_strMacroVer = "1.0";

CSttLowFreqTimePnvTest::CSttLowFreqTimePnvTest() : CSttLowFreqTimeTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
}

CSttLowFreqTimePnvTest::~CSttLowFreqTimePnvTest(void)
{
}

void CSttLowFreqTimePnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PnvLowFreqTime(this, pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if(stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttLowFreqTimePnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PnvLowFreqTime(&m_oResults, pXmlSerialize);
}

void CSttLowFreqTimePnvTest::TranslateToStateParas()
{
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    m_pStateTest->m_oStateParas.m_fTao = 0;
	m_fCurrSearchDfdt = m_fDfdt;
    //////////////////////////////////////////////////////////////////////////
    //故障前状态

    for (int i=0;i<3;i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_fUabc[i];
        paraState0->m_uiVOL[i].Harm[1].fAngle = m_fUabcPh[i];
        paraState0->m_uiVOL[i].Harm[1].fFreq = m_fFnom;
    }

    paraState0->m_fTimeState = m_fPreFaultTime;
    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(paraState0);
    SetStateBout(paraState0->m_binOut, m_binOut);
    paraState0->m_fTimeAfterTrigger = 0.0f;
    paraState0->m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
    //故障状态
	paraState1->m_nRampTimeGrad =  m_fDrvStepTime * 1000;

    for (int i=0;i<3;i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_fUabc[i];
        paraState1->m_uiVOL[i].Harm[1].fAngle = m_fUabcPh[i];
    }

    for(int nIndex = 0; nIndex < 3; nIndex++)
    {
        paraState1->m_uiCUR[nIndex].Ramp[2].nIndex = 1;
        paraState1->m_uiVOL[nIndex].Ramp[2].nIndex = 1;
		paraState1->m_uiCUR[nIndex].Ramp[2].fStep = m_fDrvDfDt / 1000;
		paraState1->m_uiVOL[nIndex].Ramp[2].fStep = m_fDrvDfDt / 1000;
		paraState1->m_uiCUR[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
		paraState1->m_uiVOL[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
        paraState1->m_uiCUR[nIndex].Ramp[2].fEnd = m_fFend;
        paraState1->m_uiVOL[nIndex].Ramp[2].fEnd = m_fFend;
    }

    Global_SetStateBinFault(paraState1, m_binIn, m_nBinLogic);
	paraState1->m_fTimeState = fabs(m_fFAct - m_fFend) / m_fDfdt + m_fHoldTime;
    SetStateBout(paraState1->m_binOut, m_binOut);

    for(int nBoutIndex = 0; nBoutIndex < MAX_BINARYOUT_COUNT; nBoutIndex++)
    {
        paraState1->m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    paraState1->m_fTimeAfterTrigger = 0;
    paraState1->m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
}

