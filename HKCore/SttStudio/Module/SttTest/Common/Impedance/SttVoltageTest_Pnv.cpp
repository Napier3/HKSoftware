#include "stdafx.h"
#include "SttVoltageTest_Pnv.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttVoltagePnvTest::m_strMacroName = "电压保护试验";
CString CSttVoltagePnvTest::m_strMacroID = STT_MACRO_ID_VoltageTest;
CString CSttVoltagePnvTest::m_strFilePostFix = "pnvvt";
CString CSttVoltagePnvTest::m_strMacroVer ="1.0";

CSttVoltagePnvTest::CSttVoltagePnvTest() : CSttStateTest()
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

    m_oVoltagePnvResults.init();
}

void CSttVoltagePnvTest::Init()
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

CSttVoltagePnvTest::~CSttVoltagePnvTest(void)
{

}
long CSttVoltagePnvTest::CalReport(UINT nState)
{
    CSttStateTest::CalReport(nState);

    for(int i = 0; i < 3; i++)
    {
        if(m_nBinSelect == 1)
        {
           m_oVoltagePnvResults.m_nBinSwitchCount[i] = m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[i+4];
           m_oVoltagePnvResults.m_fTimeBinAct[i] = m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[i+4][0];
        }
        else
        {
            m_oVoltagePnvResults.m_nBinSwitchCount[i] = m_pStateTest->m_oStateResults.m_resultState[1].m_nrBinSwitchCount[i];
            m_oVoltagePnvResults.m_fTimeBinAct[i] = m_pStateTest->m_oStateResults.m_resultState[1].m_frTimeBinAct[i][0];
        }
    }
}

void CSttVoltagePnvTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
    tmt_StatePara  *paraState0 = &m_pStateTest->m_oStateParas.m_paraState[0];
    tmt_StatePara  *paraState1 = &m_pStateTest->m_oStateParas.m_paraState[1];
    paraState0->m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    paraState0->m_fTimeState = m_fPreFaultTime;

    for(int i = 0; i < 4; i++)
    {
        paraState0->m_uiVOL[i].Harm[1].fAmp = m_fVolAmp[i];
        paraState0->m_uiVOL[i].Harm[1].fAngle = m_fVolAng[i];
    }

    for(int i = 0; i < 3; i++)
    {
        paraState0->m_uiCUR[i].Harm[1].fAmp = m_fCurAmp[i];
        paraState0->m_uiCUR[i].Harm[1].fAngle = m_fCurAng[i];
    }

    paraState1->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    paraState1->m_fTimeState = m_fFaultTime + m_fTSetting;

    for(int i = 0; i < 4; i++)
    {
        paraState1->m_uiVOL[i].Harm[1].fAmp = m_fVolAmp[i+4];
        paraState1->m_uiVOL[i].Harm[1].fAngle = m_fVolAng[i+4];
    }

    for(int i = 0; i < 3; i++)
    {
        paraState1->m_uiCUR[i].Harm[1].fAmp = m_fCurAmp[i+3];
        paraState1->m_uiCUR[i].Harm[1].fAngle = m_fCurAng[i+3];
    }
    for(int i = 0; i < 4; i++)
    {
        paraState1->m_binOut[i].nState = m_nBout[i];
        paraState1->m_binOut[i].nMode = m_nOutputSwitchMode;
        paraState1->m_binOut[i].fHoldTime = m_fOutputHoldTime;
        paraState1->m_binOut[i].fTimeTrig = m_fTimeTrig;
    }

    if (m_nBinSelect == 1)
    {
        paraState1->m_binIn[0].nSelect = 0;
        paraState1->m_binIn[1].nSelect = 0;
        paraState1->m_binIn[2].nSelect = 0;
        paraState1->m_binIn[3].nSelect = 0;
        paraState1->m_binIn[4].nSelect = 1;
        paraState1->m_binIn[5].nSelect = 1;
        paraState1->m_binIn[6].nSelect = 1;
        paraState1->m_binIn[7].nSelect = 1;
    }
    else
    {
        paraState1->m_binIn[0].nSelect = 1;
        paraState1->m_binIn[1].nSelect = 1;
        paraState1->m_binIn[2].nSelect = 1;
        paraState1->m_binIn[3].nSelect = 1;
        paraState1->m_binIn[4].nSelect = 0;
        paraState1->m_binIn[5].nSelect = 0;
        paraState1->m_binIn[6].nSelect = 0;
        paraState1->m_binIn[7].nSelect = 0;
    }

    BOOL bHasThreeTrip = FALSE;
    for (int nIndex = 0;nIndex<8;nIndex++)
    {
        if (m_nInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_RECLOCE)
        {
            paraState1->m_binIn[nIndex].nSelect = 0;
        }
        else if ((paraState1->m_binIn[nIndex].nSelect)&&(m_nInputState[nIndex] == STT_IMPEDANCE_BIN_STATE_THREE))
        {
            bHasThreeTrip = TRUE;
        }
    }

    if (!bHasThreeTrip)
    {
        paraState1->m_nBinLogic = TMT_BINLOGIC_AND;
    }
}

void CSttVoltagePnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_Voltage_Pnv((tmt_VoltagePnvParas*)this,pXmlSerialize);


	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
        AfterSetParameter();

		Gouts_XmlSerialize(pXmlSerialize);
	}
}

void CSttVoltagePnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_Voltage_Pnv(&m_oVoltagePnvResults, pXmlSerialize);
}
