#include "stdafx.h"
#include "SttDiff6IHarmTest_Pnv.h"
#include "../SttSystemConfig.h"
#include "../../../Engine/SttTestServerBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDiff6IHarmPnvTest::m_strMacroName = "差动(6I)-谐波制动搜索";
CString CSttDiff6IHarmPnvTest::m_strMacroID = STT_MACRO_ID_Diff6IHarmRestrainSearchTest;
CString CSttDiff6IHarmPnvTest::m_strFilePostFix = "pdffhtst";
CString CSttDiff6IHarmPnvTest::m_strMacroVer ="1.0";

CSttDiff6IHarmPnvTest::CSttDiff6IHarmPnvTest() : CSttDiffCurrHarmTest()
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

CSttDiff6IHarmPnvTest::~CSttDiff6IHarmPnvTest(void)
{

}

void CSttDiff6IHarmPnvTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_6i_harm_pnv((tmt_DiffCurrParas*)this,pXmlSerialize);

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换

        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttDiff6IHarmPnvTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_6i_harm_pnv(&m_oResults, pXmlSerialize);
}

void CSttDiff6IHarmPnvTest::AfterSetParameter()
{
    switch (m_nWindSide)
    {
    case 1://高中侧
        m_fKpm = m_fKpl;
        break;
    case 2://中低侧
        m_fKpm = m_fKph;
        break;
    }
    CSttDiffCurrHarmTest::AfterSetParameter();
}
void CSttDiff6IHarmPnvTest::TranslateToStateParas()
{
    m_pStateTest->m_oStateParas.m_fTao = 0;

    //////////////////////////////////////////////////////////////////////////
    //故障前状态
    //Xuzhantao Pnv待处理
    //谐波施加侧  m_nHarmPos
    //Id动作方程  m_nIbiasCal
    //Ir制动方程  m_nIdiffCal
    //保护内部零序修正方式   m_nY0CorrectMode
    SetStatePreFault_6U6I();//在此函数中设置故障前电压电流、开入开出等,并设置故障态电压值
    //////////////////////////////////////////////////////////////////////////
    //故障状态
    m_oDiffCalTool.CurrentCal(&m_fIdiff,m_fIbias);
    SetResultValues_I1IeI2Ie();
    m_oResults.m_fIdiffSettingValue = m_fIdiff;
    ChannelUI_Diff *pChCurrents = m_oDiffCalTool.GetChannelCurrents();

    for (int nIndex = 0;nIndex<DIFF_CURR_CAL_CHANNEL_MAX;nIndex++)
    {
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAmp = pChCurrents[nIndex].famptitude;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fAngle = pChCurrents[nIndex].fphase;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[1].fFreq = g_theSystemConfig->m_fFNom;

        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[m_nHarmIndex].m_bSelect = TRUE;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[m_nHarmIndex].fAmp = pChCurrents[nIndex].famptitude*m_fCurrScanVal/100;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[m_nHarmIndex].fAngle = pChCurrents[nIndex].fphase;
        m_pStateTest->m_oStateParas.m_paraState[1].m_uiCUR[nIndex].Harm[m_nHarmIndex].fFreq = g_theSystemConfig->m_fFNom*m_nHarmIndex;
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
