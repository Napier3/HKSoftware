#include "stdafx.h"
#include "SttLowFreqActTest_Pnv.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowFreqActPnvTest::m_strMacroName = "���ܼ��ض���ֵ����";
CString CSttLowFreqActPnvTest::m_strMacroID = STT_MACRO_ID_PnvLowFreqAct;
CString CSttLowFreqActPnvTest::m_strFilePostFix = "pnvlfa";
CString CSttLowFreqActPnvTest::m_strMacroVer ="1.0";

CSttLowFreqActPnvTest::CSttLowFreqActPnvTest() : CSttLowFreqActTest()
{
	m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
	m_dTestStartTime=0;
    Init();
}

CSttLowFreqActPnvTest::~CSttLowFreqActPnvTest(void)
{
}

void CSttLowFreqActPnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PnvLowFreqAct(this,pXmlSerialize);


    //2020-4-6  lijq  ��ȡ����ģʽ�£���Ҫ���г�ʼ��
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//������������й���ת��

        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttLowFreqActPnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PnvLowFreqAct(&m_oResults, pXmlSerialize);
}

void CSttLowFreqActPnvTest::TranslateToStateParas()
{
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    tmt_StatePara  *paraState2 = &m_pStateTest->m_oStateParas.m_paraState[2];
    m_pStateTest->m_oStateParas.m_fTao = 0;

	m_fCurrSearchDfdt = m_fDfdt;
    //////////////////////////////////////////////////////////////////////////
    //����ǰ״̬
    for (int i=0;i<3;i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_fUabc[i];
        paraState0->m_uiVOL[i].Harm[1].fAngle = m_fUabcPh[i];
        paraState0->m_uiVOL[i].Harm[1].fFreq = m_fFnom;
    }
    paraState0->m_fTimeState = m_fPreFaultTime;
    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(paraState0);
    SetStateBout(paraState0->m_binOut,m_binOut);
    paraState0->m_fTimeAfterTrigger = 0.0f;
    paraState0->m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
	paraState1->m_nRampTimeGrad =  m_fDrvStepTime * 1000;
	paraState2->m_nRampTimeGrad =  m_fDrvStepTime * 1000;
    //����״̬
    float fEndFreq = m_fFnom;

	if (m_fFstart>m_fFend)
    {
		fEndFreq = m_fFstart-(m_nRunSearchCount-1)*m_fFstep;
	} 
    else
    {
		fEndFreq = m_fFstart+(m_nRunSearchCount-1)*m_fFstep;
    }

	if (m_nRunSearchCount > m_nGradientCount)
    {
        fEndFreq = m_fFend;
    }

    for (int i=0;i<3;i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_fUabc[i+3];
        paraState1->m_uiVOL[i].Harm[1].fAngle = m_fUabcPh[i+3];
    }

	for (int nIndex = 0;nIndex<3;nIndex++)
    {
        paraState1->m_uiCUR[nIndex].Ramp[2].nIndex = 1;
        paraState1->m_uiVOL[nIndex].Ramp[2].nIndex = 1;
		paraState1->m_uiCUR[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		paraState1->m_uiVOL[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		paraState1->m_uiCUR[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
		paraState1->m_uiVOL[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;

        paraState1->m_uiCUR[nIndex].Ramp[2].fEnd = fEndFreq;
        paraState1->m_uiVOL[nIndex].Ramp[2].fEnd = fEndFreq;
    }

    Global_SetStateBinFault(paraState1,m_binIn,m_nBinLogic);
	paraState1->m_fTimeState = fabs(m_fFnom-fEndFreq)/m_fDfdt + m_fHoldTime;
    SetStateBout(paraState1->m_binOut,m_binOut);
 
 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
    {
        paraState1->m_binOut[nBoutIndex].fTimeTrig = 0;
    }
 
    paraState1->m_fTimeAfterTrigger = 0;
    paraState1->m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
    //Ƶ�ʵݱ߻���ֵ̬

    for (int i=0;i<3;i++)
    {
        paraState2->m_uiVOL[i].Harm[1].fAmp = m_fUabc[i+3];
        paraState2->m_uiVOL[i].Harm[1].fAngle = m_fUabcPh[i+3];
        paraState2->m_uiVOL[i].Harm[1].fFreq = m_fFnom;
    }

	for (int nIndex = 0;nIndex<3;nIndex++)
    {
        paraState2->m_uiCUR[nIndex].Ramp[2].nIndex = 1;
        paraState2->m_uiVOL[nIndex].Ramp[2].nIndex = 1;
		paraState2->m_uiCUR[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		paraState2->m_uiVOL[nIndex].Ramp[2].fStep = m_fDrvDfDt/1000;
		paraState2->m_uiCUR[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;
		paraState2->m_uiVOL[nIndex].Ramp[2].fStepTime = m_fDrvStepTime;

        paraState2->m_uiCUR[nIndex].Harm[1].fFreq = fEndFreq;
        paraState2->m_uiVOL[nIndex].Harm[1].fFreq = fEndFreq;
        paraState2->m_uiCUR[nIndex].Ramp[2].fEnd = m_fFnom;
        paraState2->m_uiVOL[nIndex].Ramp[2].fEnd = m_fFnom;
    }

    paraState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
	paraState2->m_fTimeState = fabs(m_fFnom-fEndFreq)/m_fDfdt + 0.5;
    SetStateBout(paraState2->m_binOut,m_binOut);

	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
    {
        paraState2->m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    paraState2->m_fTimeAfterTrigger = 0;
    paraState2->m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
}
