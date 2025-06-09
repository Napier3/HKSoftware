#include "stdafx.h"
#include "SttStateDiffCoefTest_Pnv.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiffCoefPnvTest::m_strMacroName = "Pnv状态序列比率差动制动系数校验";
CString CSttDiffCoefPnvTest::m_strMacroID = STT_MACRO_ID_StateDiffCoef;
CString CSttDiffCoefPnvTest::m_strFilePostFix = "pnvsdct";
CString CSttDiffCoefPnvTest::m_strMacroVer ="1.0";

CSttDiffCoefPnvTest::CSttDiffCoefPnvTest() : CSttStateTest()
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

    m_oDiffCoefPnvResults.init();
}

void CSttDiffCoefPnvTest::Init()
{ 
    m_pStateTest->m_oStateParas.initCommon();
    m_pStateTest->m_oStateParas.m_nStateNumbers = 2;
    m_pStateTest->m_oStateParas.init(2);
    m_pStateTest->m_oStateResults.init(2);
    CSttTestBase::Init();
    for(int i = 0;i < 10;i++)
    {
        m_oRstEval[i].m_bSelect = FALSE;
    }
    m_nCurStateIndex = 0;
    m_pStateTest->m_oStateParas.SetFundFreq(g_theSystemConfig->m_fFNom);
}

CSttDiffCoefPnvTest::~CSttDiffCoefPnvTest(void)
{

}
long CSttDiffCoefPnvTest::CalReport(UINT nState)
{
    CSttStateTest::CalReport(nState);

    for(int i = 0; i < 3; i++)
    { 
        m_oDiffCoefPnvResults.m_nBinSwitchCount[i] = m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[i];
        m_oDiffCoefPnvResults.m_fTimeBinAct[i] = m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[i][0];
    }
}
void CSttDiffCoefPnvTest::uiRampCh(tmt_channel *m_uiRamp)
{
    m_uiRamp->Harm[1].fAmp = m_fBeginVal;
    m_uiRamp->Ramp[0].nIndex = 1;
    m_uiRamp->Ramp[0].fEnd = m_fEndVal;
    m_uiRamp->Ramp[0].fStep = m_fStepVal / 1000;

}
void CSttDiffCoefPnvTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
    m_pStateTest->m_oStateParas.SetFundFreq(m_fFreq);
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    paraState0->m_fTimeState = m_fPreFaultTime;

    for(int i = 0; i < 9; i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_fVolAmp[0][i];
        paraState0->m_uiVOL[i].Harm[1].fAngle = m_fVolAng[0][i];
        paraState0->m_uiCUR[i].Harm[1].fAmp = m_fCurAmp[0][i];
        paraState0->m_uiCUR[i].Harm[1].fAngle = m_fCurAng[0][i];

    }for(int i = 0; i < 8; i++)
    {
        paraState0->m_binOut[i].nState = m_nBout[0][i];
        paraState0->m_binOut[i].fTimeTrig = 0;
    }

    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState1->m_fTimeState = fabs(m_fBeginVal - m_fEndVal) / m_fStepVal * m_fStepTime + 1;

    for(int i = 0; i < 9; i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_fVolAmp[1][i];
        paraState1->m_uiVOL[i].Harm[1].fAngle = m_fVolAng[1][i];
        paraState1->m_uiCUR[i].Harm[1].fAmp = m_fCurAmp[1][i];
        paraState1->m_uiCUR[i].Harm[1].fAngle = m_fCurAng[1][i];
    }

    paraState1->m_nRampTimeGrad = m_fStepTime * 0.001f;

    switch (m_nRampIndex)
    {
    case StateRampPnvUa:
        uiRampCh(&paraState1->m_uiVOL[0]);
        break;
    case StateRampPnvUb:
        uiRampCh(&paraState1->m_uiVOL[1]);
        break;
    case StateRampPnvUc:
        uiRampCh(&paraState1->m_uiVOL[2]);
        break;
    case StateRampPnvUabc:
        uiRampCh(&paraState1->m_uiVOL[0]);
        uiRampCh(&paraState1->m_uiVOL[1]);
        uiRampCh(&paraState1->m_uiVOL[2]);
        break;
    case StateRampPnvUap:
        uiRampCh(&paraState1->m_uiVOL[3]);
        break;
    case StateRampPnvUbp:
        uiRampCh(&paraState1->m_uiVOL[4]);
        break;
    case StateRampPnvUcp:
        uiRampCh(&paraState1->m_uiVOL[5]);
        break;
    case StateRampPnvUabcp:
        uiRampCh(&paraState1->m_uiVOL[3]);
        uiRampCh(&paraState1->m_uiVOL[4]);
        uiRampCh(&paraState1->m_uiVOL[5]);
        break;
    case StateRampPnvIa:
        uiRampCh(&paraState1->m_uiCUR[0]);
        break;
    case StateRampPnvIb:
        uiRampCh(&paraState1->m_uiCUR[1]);
        break;
    case StateRampPnvIc:
        uiRampCh(&paraState1->m_uiCUR[2]);
        break;
    case StateRampPnvIabc:
        uiRampCh(&paraState1->m_uiCUR[0]);
        uiRampCh(&paraState1->m_uiCUR[1]);
        uiRampCh(&paraState1->m_uiCUR[2]);
        break;
    case StateRampPnvIap:
        uiRampCh(&paraState1->m_uiCUR[3]);
        break;
    case StateRampPnvIbp:
        uiRampCh(&paraState1->m_uiCUR[4]);
        break;
    case StateRampPnvIcp:
        uiRampCh(&paraState1->m_uiCUR[5]);
        break;
    case StateRampPnvIabcp:
        uiRampCh(&paraState1->m_uiCUR[3]);
        uiRampCh(&paraState1->m_uiCUR[4]);
        uiRampCh(&paraState1->m_uiCUR[5]);
        break;
    }

    for(int i = 0; i < 8; i++)
    {
        paraState1->m_binOut[i].nState = m_nBout[1][i];
        paraState1->m_binOut[i].nMode = 0;
        paraState1->m_binOut[i].fHoldTime = m_fHoldTime;
        if(m_nOutputSwitchMode)
        {
            paraState1->m_binOut[i].fTimeTrig = 0.01;
        }
        else
        {
            paraState1->m_binOut[i].fTimeTrig = 0;
        }

        paraState1->m_binIn[0].nSelect = m_nInputState[i];
    }
    paraState1->m_nBinLogic = m_nBinLogic;

}

void CSttDiffCoefPnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_DiffCoef_Pnv((tmt_DiffCoefPnvParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
        AfterSetParameter();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttDiffCoefPnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_DiffCoef_Pnv(&m_oDiffCoefPnvResults, pXmlSerialize);
}
