#include "stdafx.h"
#include "SttDisTanceTest_I.h"
#include "../SttSystemConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDisTanceTest_I::m_strMacroName = "距离保护测试(国际版)";
CString CSttDisTanceTest_I::m_strMacroID = STT_MACRO_ID_Distance_I;
CString CSttDisTanceTest_I::m_strFilePostFix = "odis";
CString CSttDisTanceTest_I::m_strMacroVer ="1.0";

CSttDisTanceTest_I::CSttDisTanceTest_I() : CSttDisTanceTest()
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

void CSttDisTanceTest_I::Init()
{
    CSttImpBaseTest::Init();
    tmt_DistanceParas_I::init();
    m_fUNom = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
}

CSttDisTanceTest_I::~CSttDisTanceTest_I(void)
{

}

long CSttDisTanceTest_I::CalReport(UINT nState)
{
    if(m_oImpBaseResults.m_resultState[2].m_nAct)
    {
        for (int nIndex = 0;nIndex<8;nIndex++)
        {
            m_oDistanceResults.m_fFirstTripTime[nIndex] = m_oImpBaseResults.m_resultState[2].m_frTimeBinAct[nIndex][0];
        }

        m_oDistanceResults.m_nActA = (m_oDistanceResults.m_fFirstTripTime[0]-0.0001) > 0 ? 1 : 0;
        m_oDistanceResults.m_nActB = (m_oDistanceResults.m_fFirstTripTime[1]-0.0001) > 0 ? 1 : 0;
        m_oDistanceResults.m_nActC = (m_oDistanceResults.m_fFirstTripTime[2]-0.0001) > 0 ? 1 : 0;
        m_oDistanceResults.m_nActD = (m_oDistanceResults.m_fFirstTripTime[3]-0.0001) > 0 ? 1 : 0;

        m_oDistanceResults.m_fTripTime = 0;

        for (int i=0;i<8;i++)
        {
            m_oDistanceResults.m_fTripTime = GetMaxValue(m_oDistanceResults.m_fTripTime,m_oDistanceResults.m_fFirstTripTime[i]);
        }

        m_oDistanceResults.m_fImp = m_fImpedance[0];
        m_oDistanceResults.m_fImpAngle = m_fImpAngle[0];
    }
    return 0;
}

void CSttDisTanceTest_I::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_I((tmt_DistanceParas_I*)this,pXmlSerialize);


    //2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
        Gouts_XmlSerialize(pXmlSerialize);
    }
}

void CSttDisTanceTest_I::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(&m_oDistanceResults, pXmlSerialize);
}

long CSttDisTanceTest_I::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttDisTanceTest_I::TranslateToStateParas()
{
	m_fMaxFaultTime = m_fTSetting+m_fMarginTime;
    TranslateToStateParas_ImpBase(this,m_fUNom);

    //状态3：跳闸后,等待重合闸状态
    tmt_StatePara *pState2 = &m_pImpBaseParas->m_pStateParas->m_paraState[2];
    pState2->m_nTriggerCondition = TMT_MDSTATE_TIMEBINTRIGGER;
    for (int i = 0;i<8;i++)
    {
        pState2->m_binIn[i].nSelect = m_nBinState[i];
    }
    pState2->m_nBinLogic = m_nBinLogic;

    m_oDistanceResults.m_fFaultVol = m_fSCVoltage[0];
    m_oDistanceResults.m_fFaultCurrent = m_fSCCurrent[0];
}
