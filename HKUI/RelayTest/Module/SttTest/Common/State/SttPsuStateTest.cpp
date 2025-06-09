#include "stdafx.h"
#include"SttPsuStateTest.h"
#include "../SttSystemConfig.h"

CString CSttPsuStateTest::m_strMacroName = "Psu状态序列测试";
CString CSttPsuStateTest::m_strMacroID = STT_MACRO_ID_PsuStateTest;
CString CSttPsuStateTest::m_strFilePostFix = "psust";
CString CSttPsuStateTest::m_strMacroVer ="1.0";

CSttPsuStateTest::CSttPsuStateTest() : CSttStateTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;

    m_pStateTest = stt_test_get_base_statetest_buff();
}

CSttPsuStateTest::~CSttPsuStateTest(void)
{

}

void CSttPsuStateTest::SetPsuGradientCh(tmt_StatePara *paraState,tmt_channel *uiGradientch)
{
    if(paraState->m_nRampType == 1)
    {
        uiGradientch->Harm[1].fFreq = paraState->m_sttGradient.fStart;
        uiGradientch->Ramp[2].nIndex = 1;
        uiGradientch->Ramp[2].fStep = paraState->m_sttGradient.fdfdt/1000;
        uiGradientch->Ramp[2].fEnd = paraState->m_sttGradient.fEnd;
        paraState->m_nRampTimeGrad =  0.001f;
    }
    else if(paraState->m_nRampType == 2)
    {
        uiGradientch->Harm[1].fAmp = paraState->m_sttGradient.fStart;
        uiGradientch->Ramp[0].nIndex = 1;
        uiGradientch->Ramp[0].fStep = paraState->m_sttGradient.fdvdt/1000;
        uiGradientch->Ramp[0].fEnd = paraState->m_sttGradient.fEnd;
        paraState->m_nRampTimeGrad =  0.001f;
    }
    else if(paraState->m_nRampType == 3)
    {
        uiGradientch->Harm[1].fAmp = paraState->m_sttGradient.fStart;
        uiGradientch->Ramp[0].nIndex = 1;
        uiGradientch->Ramp[0].fStep = paraState->m_sttGradient.fStep/1000;
        uiGradientch->Ramp[0].fEnd = paraState->m_sttGradient.fEnd;
        paraState->m_nRampTimeGrad = paraState->m_sttGradient.fStepTime * 0.001f;
    }
}

void CSttPsuStateTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(&m_pStateTest->m_oStateParas,pXmlSerialize);

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
	}
}

void CSttPsuStateTest::AfterSetParameter()
{
    CSttStateTest::AfterSetParameter();
    for(int i=1; i<m_pStateTest->m_oStateParas.m_nStateNumbers; i++)
    {
        tmt_StatePara  *paraState = &m_pStateTest->m_oStateParas.m_paraState[i];
        switch(paraState->m_sttGradient.iVar)
        {
        case         PsuGradientUa1:
        case         PsuGradientVdc:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[0]);
            break;
        case         PsuGradientUb1:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[1]);
            break;
        case         PsuGradientUc1:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[2]);
            break;
        case         PsuGradientUab1:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[1]);
            break;
        case         PsuGradientUbc1:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[1]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[2]);
            break;
        case         PsuGradientUca1:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[2]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[0]);
            break;
        case         PsuGradientUabc1:
        case         PsuGradientUa1Ub1Uc1:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[1]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[2]);
            break;
        case         PsuGradientUa2:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[3]);
            break;
        case         PsuGradientUb2:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[4]);
            break;
        case         PsuGradientUc2:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[5]);
            break;
        case         PsuGradientUab2:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[4]);
            break;
        case         PsuGradientUbc2:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[4]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[5]);
            break;
        case         PsuGradientUca2:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[5]);
            break;
        case         PsuGradientUabc2:
        case         PsuGradientUa2Ub2Uc2:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[4]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[5]);
            break;
        case         PsuGradientIa1:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[0]);
            break;
        case         PsuGradientIb1:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[1]);
            break;
        case         PsuGradientIc1:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[2]);
            break;
        case         PsuGradientIab1:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[1]);
            break;
        case         PsuGradientIbc1:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[1]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[2]);
            break;
        case         PsuGradientIca1:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[2]);
            break;
        case         PsuGradientIabc1:
        case         PsuGradientIa1Ib1Ic1:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[1]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[2]);
            break;
        case         PsuGradientIa2:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[3]);
            break;
        case         PsuGradientIb2:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[4]);
            break;
        case         PsuGradientIc2:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[5]);
            break;
        case         PsuGradientIab2:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[4]);
            break;
        case         PsuGradientIbc2:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[4]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[5]);
            break;
        case         PsuGradientIca2:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[5]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[3]);
            break;
        case         PsuGradientIabc2:
        case         PsuGradientIa2Ib2Ic2:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[4]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[5]);
            break;
        case         PsuGradientVoltageAll:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[1]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[2]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[4]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[5]);
            break;
        case         PsuGradientCurrentAll:
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[1]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[2]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[4]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[5]);
            break;
        case         PsuGradientVz:
            break;
        case         PsuGradientAll:
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[1]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[2]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[4]);
            SetPsuGradientCh(paraState, &paraState->m_uiVOL[5]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[0]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[1]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[2]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[3]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[4]);
            SetPsuGradientCh(paraState, &paraState->m_uiCUR[5]);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
