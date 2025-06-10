#include "stdafx.h"
#include"SttSynActFreqTest.h"
#include "../SttSystemConfig.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttSynActFreqTest::m_strMacroName = "同期频率边界值测试";
CString CSttSynActFreqTest::m_strMacroID = STT_MACRO_ID_SynActFreqTest;
CString CSttSynActFreqTest::m_strFilePostFix = "saft";
CString CSttSynActFreqTest::m_strMacroVer ="1.0";


CSttSynActFreqTest::CSttSynActFreqTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;
}

void CSttSynActFreqTest::Init()
{
    CSttSynActVolTest::Init();
}

CSttSynActFreqTest::~CSttSynActFreqTest(void)
{
}

void CSttSynActFreqTest::ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA)
{
    if(m_nCurStepIndex <= 0)
        return;

#ifdef _PSX_QT_LINUX_
    int nCommfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	int nSize = 0;
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nSize = read(nCommfd,(char*)&m_oSyncStepRst,0x250);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

    if(nSize != sizeof(Drv_SyncStepRst))
        return;

    float fFre;
    for(int i = 0;i < 6;i++)
    {
        tmt_channel &oChannel = m_pTmtSynParas->m_uiVOL[i];

        fFre = oChannel.Harm[1].fFreq;
        if(oChannel.Ramp[2].nIndex == 1)
        {
            if (m_pTmtSynParas->m_fVs_Fre > m_pTmtSynParas->m_fVg_Fre)
            {
                //增频
                fFre += m_nCurStepIndex*m_pTmtSynParas->m_fDfStep;
            }
            else
            {
                //减频
                fFre -= m_nCurStepIndex*m_pTmtSynParas->m_fDfStep;
            }
			oRTDATA.m_oVolCh[i].m_fFreq = fFre;
        }

        unsigned int nPhase = GetPhase(m_oSyncStepRst,i);
        m_fCalAng[i] += nPhase*0.001;

		oRTDATA.m_oVolCh[i].m_fAng = m_fCalAng[i];
    }

    SetVoltAng(oRTDATA);
#endif
}

long CSttSynActFreqTest::CalReport(UINT nState)
{
    m_oSynResults.m_fFreqBordValue = 0.0f;
    m_oSynResults.m_nAct = 0;

#ifdef _PSX_QT_LINUX_
    SynResult &oSynResult=CSttDeviceBase::g_pSttDeviceBase->m_oSynResult;
    if(oSynResult.m_nAct == 1)
    {
        m_oSynResults.m_nAct = 1;
        m_oSynResults.m_fFreqBordValue = oSynResult.m_fTripValueF;
        m_oSynResults.m_fFreqDelt = fabs(m_pTmtSynParas->m_fVs_Fre - m_oSynResults.m_fFreqBordValue);
    }
#endif
    return 0;
}

void CSttSynActFreqTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_ActFreq(m_pTmtSynParas,pXmlSerialize);
    m_pTmtSynParas->m_nTestType = Stt_Syn_Test_Type_FreqBoder;

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
    }
}

void CSttSynActFreqTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_ActFreq(&m_oSynResults,  pXmlSerialize);
}

void CSttSynActFreqTest::TranslateToStateParas()
{
    TranslateToStateParasBase();
    float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
    tmt_channel *pVolChannel = m_pTmtSynParas->m_uiVOL;

    m_pTmtSynParas->m_fFreMax = m_pTmtSynParas->m_fVs_Fre*1.2;
    m_pTmtSynParas->m_fFreMin = m_pTmtSynParas->m_fVs_Fre*0.8;
    m_pTmtSynParas->m_fDrvStepF = m_pTmtSynParas->m_fDfStep;

    if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ub)
    {
        pVolChannel[1].Ramp[2].nIndex = 1;
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ubc)
    {
        pVolChannel[1].Ramp[2].nIndex = 1;
        pVolChannel[2].Ramp[2].nIndex = 1;
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uz_Uabc)
    {
        pVolChannel[0].Ramp[2].nIndex = 1;
        pVolChannel[1].Ramp[2].nIndex = 1;
        pVolChannel[2].Ramp[2].nIndex = 1;
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uabc1_Uabc2)
    {
        pVolChannel[3].Ramp[2].nIndex = 1;
        pVolChannel[4].Ramp[2].nIndex = 1;
        pVolChannel[5].Ramp[2].nIndex = 1;
    }
}
