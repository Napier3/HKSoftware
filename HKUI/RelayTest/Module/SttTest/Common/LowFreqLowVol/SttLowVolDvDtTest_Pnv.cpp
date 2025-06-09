#include "stdafx.h"
#include "SttLowVolDvDtTest_Pnv.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttLowVolDvDtPnvTest::m_strMacroName = "Pnv低压滑差动作值测试";
CString CSttLowVolDvDtPnvTest::m_strMacroID = STT_MACRO_ID_PnvLowVolDvdt;
CString CSttLowVolDvDtPnvTest::m_strFilePostFix = "lvld";
CString CSttLowVolDvDtPnvTest::m_strMacroVer ="1.0";

CSttLowVolDvDtPnvTest::CSttLowVolDvDtPnvTest() : CSttLowVolDvDtTest()
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

void CSttLowVolDvDtPnvTest::Init()
{ 
    CSttLowVolActTest::Init();
}

CSttLowVolDvDtPnvTest::~CSttLowVolDvDtPnvTest(void)
{

}

void CSttLowVolDvDtPnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PnvLowVolDvDt(this,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换

        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttLowVolDvDtPnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_PnvLowVolDvDt(&m_oResults, pXmlSerialize);
}

void CSttLowVolDvDtPnvTest::TranslateToStateParas()
{
  	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
    m_pStateTest->m_oStateParas.m_fTao = 0;
	float fGradientTime = 0.0f,fLnDvDt = m_fDvdt ,fLnEndVol = m_fVend;
  
    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    for (int i=0;i<3;i++)
    {
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[i].Harm[1].fAmp = m_uiVOL[0][i].Harm[1].fAmp;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL[i].Harm[1].fAngle = m_uiVOL[0][i].Harm[1].fAngle;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[i].Harm[1].fAmp = m_uiCUR[0][i].Harm[1].fAmp;
        m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR[i].Harm[1].fAngle = m_uiVOL[0][i].Harm[1].fAngle;
    }
   
    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreFaultTime;
    m_pStateTest->m_oStateParas.m_paraState[0].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    Global_SetStateBinPreFault(&m_pStateTest->m_oStateParas.m_paraState[0]);
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[0].m_binOut,m_binOut);
    m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeAfterTrigger = 0.0f;
    m_pStateTest->m_oStateParas.m_paraState[0].m_bDC = FALSE;
    //////////////////////////////////////////////////////////////////////////
    //故障状态
    m_pStateTest->m_oStateParas.m_paraState[1].m_nRampTimeGrad =  1;
    m_pStateTest->m_oStateParas.m_paraState[2].m_nRampTimeGrad =  1;

	if (m_nRunSearchCount > m_nGradientCount)
    {
        fLnDvDt = m_fDvdtEnd;
    }
	else if (m_fDvdtStart>m_fDvdtEnd)
    {
		fLnDvDt = m_fDvdtStart - (m_nRunSearchCount-1)*m_fDvdtStep;
	} 
    else
    {
		fLnDvDt = m_fDvdtStart + (m_nRunSearchCount-1)*m_fDvdtStep;
    }

	if (m_nUSetMode == 1)
    {
        fLnDvDt  /= SQRT3;
		fLnEndVol = m_fVend/SQRT3;
    }

    m_fCurrSearchDvdt = fLnDvDt;
    for (int i = 0;i<3;i++)
    {
        fGradientTime = max(fabs(m_uiVOL[0][i].Harm[1].fAmp-fLnEndVol)/fLnDvDt,fGradientTime);
    }
	for (int nIndex = 0;nIndex<3;nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAmp = m_uiVOL[0][nIndex].Harm[1].fAmp;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Harm[1].fAngle = m_uiVOL[0][nIndex].Harm[1].fAngle;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAmp = m_uiCUR[1][nIndex].Harm[1].fAmp;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAngle = m_uiVOL[1][nIndex].Harm[1].fAngle;

        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiVOL[nIndex].Ramp[0].fEnd = fLnEndVol;
    }

	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = fGradientTime + m_fHoldTime;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut,m_binOut);
 
 	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
    }
 
    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
    //频率递边回稳态值

	for (int nIndex = 0;nIndex<3;nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Harm[1].fAngle = m_uiVOL[0][nIndex].Harm[1].fAngle;
        m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Harm[1].fAmp = m_uiCUR[1][nIndex].Harm[1].fAmp;
        m_pStateTest->m_oStateParas.m_paraState[2].m_uiCUR[nIndex].Harm[1].fAngle = m_uiVOL[1][nIndex].Harm[1].fAngle;

        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].nIndex = 1;
		m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fStep = fLnDvDt/1000;
        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fStepTime = 0.001f;

        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Harm[1].fAmp = fLnEndVol;
        m_pStateTest->m_oStateParas.m_paraState[2].m_uiVOL[nIndex].Ramp[0].fEnd = m_uiVOL[0][nIndex].Harm[1].fAmp;
    }

    m_pStateTest->m_oStateParas.m_paraState[2].m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
    m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeState = fGradientTime + 0.5;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[2].m_binOut,m_binOut);

	for (int nBoutIndex=0;nBoutIndex<MAX_BINARYOUT_COUNT;nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[2].m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    m_pStateTest->m_oStateParas.m_paraState[2].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[2].m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
}
