#include "stdafx.h"
#include "SttLowVolActTest_Pnv.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowVolActPnvTest::m_strMacroName = "Pnv低压减载动作值测试";
CString CSttLowVolActPnvTest::m_strMacroID = STT_MACRO_ID_PnvLowVolAct;
CString CSttLowVolActPnvTest::m_strFilePostFix = "pnvlva";
CString CSttLowVolActPnvTest::m_strMacroVer ="1.0";

CSttLowVolActPnvTest::CSttLowVolActPnvTest() : CSttLowVolActTest()
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

CSttLowVolActPnvTest::~CSttLowVolActPnvTest(void)
{
}

void CSttLowVolActPnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PnvLowVolAct(this,pXmlSerialize);


    //2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换

        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttLowVolActPnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PnvLowVolAct(&m_oResults, pXmlSerialize);
}

void CSttLowVolActPnvTest::TranslateToStateParas()
{

    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    tmt_StatePara  *paraState2 = &m_pStateTest->m_oStateParas.m_paraState[2];

    m_pStateTest->m_oStateParas.m_fTao = 0;
	float fGradientTime = 0.0f,fLnDvDt = m_fDvdt;
  
    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    for (int i=0;i<3;i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_uiVOL[0][i].Harm[1].fAmp;
        paraState0->m_uiVOL[i].Harm[1].fAngle = m_uiVOL[0][i].Harm[1].fAngle;
        paraState0->m_uiCUR[i].Harm[1].fAmp = m_uiCUR[0][i].Harm[1].fAmp;
        paraState0->m_uiCUR[i].Harm[1].fAngle = m_uiVOL[0][i].Harm[1].fAngle;
    }
    paraState0->m_fTimeState = m_fPreFaultTime;
    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(paraState0);
    SetStateBout(paraState0->m_binOut,m_binOut);
    paraState0->m_fTimeAfterTrigger = 0.0f;
    paraState0->m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
    //故障状态

    for (int i=0;i<3;i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_uiVOL[0][i].Harm[1].fAmp;
        paraState1->m_uiVOL[i].Harm[1].fAngle = m_uiVOL[1][i].Harm[1].fAngle;
        paraState1->m_uiCUR[i].Harm[1].fAmp = m_uiCUR[1][i].Harm[1].fAmp;
        paraState1->m_uiCUR[i].Harm[1].fAngle = m_uiVOL[1][i].Harm[1].fAngle;
    }

    float fEndVol = g_theSystemConfig->m_fFNom;
	paraState1->m_nRampTimeGrad =  1;
	paraState2->m_nRampTimeGrad =  1;

	if (m_fVstart>m_fVend)
    {
		fEndVol = m_fVstart-(m_nRunSearchCount-1)*m_fVstep;
	} 
    else
    {
		fEndVol = m_fVstart+(m_nRunSearchCount-1)*m_fVstep;
    }

	if (m_nRunSearchCount > m_nGradientCount)
    {
        fEndVol = m_fVend;
    }

	if (m_nUSetMode == 1)
    {
        fEndVol /= SQRT3;
		fLnDvDt = m_fDvdt/SQRT3;
    }

    m_fCurrSearchDvdt = fLnDvDt;

    switch(m_nFaultType)
    {
        case 0://A相接地
        case 3://AB短路
            paraState1->m_uiVOL[0].Ramp[0].nIndex = 1;
        paraState1->m_uiVOL[0].Ramp[0].fStep = fLnDvDt/1000;
            paraState1->m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
            paraState1->m_uiVOL[0].Harm[1].fAmp = m_uiVOL[0][0].Harm[1].fAmp;
            paraState1->m_uiVOL[0].Ramp[0].fEnd = fEndVol;

		if (m_nUSetMode)
            {
                paraState1->m_uiVOL[1].Ramp[0].nIndex = 1;
            paraState1->m_uiVOL[1].Ramp[0].fStep = fLnDvDt/1000;
                paraState1->m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
                paraState1->m_uiVOL[1].Harm[1].fAmp = m_uiVOL[0][1].Harm[1].fAmp;
                paraState1->m_uiVOL[1].Ramp[0].fEnd = fEndVol;
            }

            fGradientTime = fabs(m_uiVOL[0][0].Harm[1].fAmp-fEndVol)/fLnDvDt;
            break;

        case 1://B相接地
        case 4://BC短路
            paraState1->m_uiVOL[1].Ramp[0].nIndex = 1;
            paraState1->m_uiVOL[1].Ramp[0].fStep = fLnDvDt/1000;
            paraState1->m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
            paraState1->m_uiVOL[1].Harm[1].fAmp = m_uiVOL[0][1].Harm[1].fAmp;
            paraState1->m_uiVOL[1].Ramp[0].fEnd = fEndVol;

		if (m_nUSetMode)
            {
                paraState1->m_uiVOL[2].Ramp[0].nIndex = 1;
            paraState1->m_uiVOL[2].Ramp[0].fStep = fLnDvDt/1000;
                paraState1->m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
                paraState1->m_uiVOL[2].Harm[1].fAmp = m_uiVOL[0][2].Harm[1].fAmp;
                paraState1->m_uiVOL[2].Ramp[0].fEnd = fEndVol;
            }

             fGradientTime = fabs(m_uiVOL[0][1].Harm[1].fAmp-fEndVol)/fLnDvDt;
            break;

        case 2://C相接地
        case 5://CA短路
            paraState1->m_uiVOL[2].Ramp[0].nIndex = 1;
        paraState1->m_uiVOL[2].Ramp[0].fStep = fLnDvDt/1000;
            paraState1->m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
            paraState1->m_uiVOL[2].Harm[1].fAmp = m_uiVOL[0][2].Harm[1].fAmp;
            paraState1->m_uiVOL[2].Ramp[0].fEnd = fEndVol;

		if (m_nUSetMode)
            {
                paraState1->m_uiVOL[0].Ramp[0].nIndex = 1;
            paraState1->m_uiVOL[0].Ramp[0].fStep = fLnDvDt/1000;
                paraState1->m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
                paraState1->m_uiVOL[0].Harm[1].fAmp = m_uiVOL[0][0].Harm[1].fAmp;
                paraState1->m_uiVOL[0].Ramp[0].fEnd = fEndVol;
            }

            fGradientTime = fabs(m_uiVOL[0][2].Harm[1].fAmp-fEndVol)/fLnDvDt;
            break;

        default:

		for (int nIndex = 0;nIndex<3;nIndex++)
            {
                paraState1->m_uiVOL[nIndex].Ramp[0].nIndex = 1;
                 paraState1->m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
                paraState1->m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;
                paraState1->m_uiVOL[nIndex].Harm[1].fAmp = m_uiVOL[0][0].Harm[1].fAmp;
                paraState1->m_uiVOL[nIndex].Ramp[0].fEnd = fEndVol;
            }
           fGradientTime = fabs(m_uiVOL[0][0].Harm[1].fAmp-fEndVol)/fLnDvDt;

            break;
    }

    Global_SetStateBinFault(paraState1,m_binIn,m_nBinLogic);
    paraState1->m_fTimeState = fGradientTime + m_fHoldTime;
    SetStateBout(paraState1->m_binOut,m_binOut);
 
 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
    {
        paraState1->m_binOut[nBoutIndex].fTimeTrig = 0;
    }
 
    paraState1->m_fTimeAfterTrigger = 0;
    paraState1->m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
    //电压递边回稳态值

    for (int i=0;i<3;i++)
    {
        paraState2->m_uiVOL[i].Harm[1].fAmp = m_uiVOL[0][i].Harm[1].fAmp;
        paraState2->m_uiVOL[i].Harm[1].fAngle = m_uiVOL[1][i].Harm[1].fAngle;
        paraState2->m_uiCUR[i].Harm[1].fAmp = m_uiCUR[1][i].Harm[1].fAmp;
        paraState2->m_uiCUR[i].Harm[1].fAngle = m_uiVOL[1][i].Harm[1].fAngle;
    }

    switch(m_nFaultType)
    {
        case 0:
        case 3://AB短路
            paraState2->m_uiVOL[0].Ramp[0].nIndex = 1;
        paraState2->m_uiVOL[0].Ramp[0].fStep = fLnDvDt/1000;
            paraState2->m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
            paraState2->m_uiVOL[0].Harm[1].fAmp = fEndVol;
            paraState2->m_uiVOL[0].Ramp[0].fEnd = m_uiVOL[0][0].Harm[1].fAmp;

		if (m_nUSetMode)
            {
                paraState2->m_uiVOL[1].Ramp[0].nIndex = 1;
            paraState2->m_uiVOL[1].Ramp[0].fStep = fLnDvDt/1000;
                paraState2->m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
                paraState2->m_uiVOL[1].Harm[1].fAmp = fEndVol;
                paraState2->m_uiVOL[1].Ramp[0].fEnd = m_uiVOL[0][1].Harm[1].fAmp;
            }
              fGradientTime = fabs(m_uiVOL[0][0].Harm[1].fAmp-fEndVol)/fLnDvDt;

            break;

        case 1:
        case 4://BC短路
            paraState2->m_uiVOL[1].Ramp[0].nIndex = 1;
        paraState2->m_uiVOL[1].Ramp[0].fStep = fLnDvDt/1000;
            paraState2->m_uiVOL[1].Ramp[0].fStepTime = 0.001f;
            paraState2->m_uiVOL[1].Harm[1].fAmp = fEndVol;
            paraState2->m_uiVOL[1].Ramp[0].fEnd = m_uiVOL[0][1].Harm[1].fAmp;

		if (m_nUSetMode)
            {
                paraState2->m_uiVOL[2].Ramp[0].nIndex = 1;
            paraState2->m_uiVOL[2].Ramp[0].fStep = fLnDvDt/1000;
                paraState2->m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
                paraState2->m_uiVOL[2].Harm[1].fAmp = fEndVol;
                paraState2->m_uiVOL[2].Ramp[0].fEnd = m_uiVOL[0][2].Harm[1].fAmp;
            }
        fGradientTime = fabs(m_uiVOL[0][1].Harm[1].fAmp-fEndVol)/fLnDvDt;

            break;

        case 2:
        case 5://CA短路
            paraState2->m_uiVOL[2].Ramp[0].nIndex = 1;
        paraState2->m_uiVOL[2].Ramp[0].fStep = fLnDvDt/1000;
            paraState2->m_uiVOL[2].Ramp[0].fStepTime = 0.001f;
            paraState2->m_uiVOL[2].Harm[1].fAmp = fEndVol;
            paraState2->m_uiVOL[2].Ramp[0].fEnd = m_uiVOL[0][2].Harm[1].fAmp;

		if (m_nUSetMode)
            {
                paraState2->m_uiVOL[0].Ramp[0].nIndex = 1;
            paraState2->m_uiVOL[0].Ramp[0].fStep = fLnDvDt/1000;
                paraState2->m_uiVOL[0].Ramp[0].fStepTime = 0.001f;
                paraState2->m_uiVOL[0].Harm[1].fAmp = fEndVol;
                paraState2->m_uiVOL[0].Ramp[0].fEnd = m_uiVOL[0][2].Harm[1].fAmp;
            }
        fGradientTime = fabs(m_uiVOL[0][2].Harm[1].fAmp-fEndVol)/fLnDvDt;

            break;

        default:

		for (int nIndex = 0;nIndex<3;nIndex++)
            {
                paraState2->m_uiVOL[nIndex].Ramp[0].nIndex = 1;
            paraState2->m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
                paraState2->m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;
                paraState2->m_uiVOL[nIndex].Harm[1].fAmp = fEndVol;
                paraState2->m_uiVOL[nIndex].Ramp[0].fEnd = m_uiVOL[0][nIndex].Harm[1].fAmp;
            }
        fGradientTime = fabs(m_uiVOL[0][0].Harm[1].fAmp-fEndVol)/fLnDvDt;

            break;
    }

    paraState2->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    paraState2->m_fTimeState = fGradientTime + 0.5;
    SetStateBout(paraState2->m_binOut,m_binOut);

	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
    {
        paraState2->m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    paraState2->m_fTimeAfterTrigger = 0;
    paraState2->m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
}
