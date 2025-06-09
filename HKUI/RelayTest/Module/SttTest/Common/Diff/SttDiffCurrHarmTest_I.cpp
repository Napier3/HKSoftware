#include "stdafx.h"
#include "SttDiffCurrHarmTest_I.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiffCurrHarmTest_I::m_strMacroName = "差动谐波制动搜索(国际版)";
CString CSttDiffCurrHarmTest_I::m_strMacroID = STT_MACRO_ID_PsuDiffHarmTest_I;
CString CSttDiffCurrHarmTest_I::m_strFilePostFix = "pdffhtst";
CString CSttDiffCurrHarmTest_I::m_strMacroVer ="1.0";

CSttDiffCurrHarmTest_I::CSttDiffCurrHarmTest_I() : CSttDiffCurrHarmTest()
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

CSttDiffCurrHarmTest_I::~CSttDiffCurrHarmTest_I(void)
{

}

void CSttDiffCurrHarmTest_I::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize_harm(this,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
		m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_fPreTime + m_fPreFaultTime;

        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttDiffCurrHarmTest_I::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_harm(&m_oResults, pXmlSerialize);
}

void CSttDiffCurrHarmTest_I::TranslateToStateParas()
{
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
    m_pStateTest->m_oStateParas.m_fTao = 0;

    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    SetStatePreFault_6U6I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
    //////////////////////////////////////////////////////////////////////////
    //故障状态
	m_oDiffCalTool.CurrentCal(&m_fIdiff,m_fIbias);
    SetResultValues_I1IeI2Ie();
    m_oResults.m_fIdiffSettingValue = m_fIdiff;
    ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

    //国际版谐波次数为2345
    long nHarmIndex = m_nHarmIndex;
    nHarmIndex += 2;

	for (int nIndex = 0;nIndex<DIFF_CURR_CAL_CHANNEL_MAX;nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAmp = pChCurrents[nIndex].famptitude;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAngle = pChCurrents[nIndex].fphase;
        //m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;

		m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[nHarmIndex].fAmp = pChCurrents[nIndex].famptitude*m_fCurrScanVal/100;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[nHarmIndex].fAngle = pChCurrents[nIndex].fphase;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[nHarmIndex].fFreq = m_fFnom*nHarmIndex;
    }
    //国际版新增谐波输出侧
    switch(m_nHarmOutSide)
    {
    case 0://IA
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    case 1://IB
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    case 2://IC
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    case 3://IABC
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    case 4://IA2
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[3].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    case 5://IB2
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[4].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    case 6://IC2
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[5].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    case 7://IABC2
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[3].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[4].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[5].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    case -1://IALL
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[0].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[1].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[2].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[3].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[4].Harm[nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[5].Harm[nHarmIndex].m_bSelect = TRUE;
        break;
    }

	Global_SetStateBinFault(&m_pStateTest->m_oStateParas.m_paraState[1],m_binIn,m_nBinLogic);
    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeState = m_fFaultTime;
	SetStateBout(m_pStateTest->m_oStateParas.m_paraState[1].m_binOut,m_binOut);

    for(int nBoutIndex = 0; nBoutIndex < MAX_BINARYOUT_COUNT; nBoutIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_binOut[nBoutIndex].fTimeTrig = 0;
    }

    m_pStateTest->m_oStateParas.m_paraState[1].m_fTimeAfterTrigger = 0;
    m_pStateTest->m_oStateParas.m_paraState[1].m_bDC = FALSE;

    //////////////////////////////////////////////////////////////////////////
}



