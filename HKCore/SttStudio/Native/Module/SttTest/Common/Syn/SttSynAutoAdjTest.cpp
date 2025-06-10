#include "stdafx.h"
#include"SttSynAutoAdjTest.h"
#include "../SttSystemConfig.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttSynAutoAdjTest::m_strMacroName = "同期自调整试验";
CString CSttSynAutoAdjTest::m_strMacroID = STT_MACRO_ID_SynAutoAdjTest;
CString CSttSynAutoAdjTest::m_strFilePostFix = "saft";
CString CSttSynAutoAdjTest::m_strMacroVer ="1.0";


CSttSynAutoAdjTest::CSttSynAutoAdjTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
}

void CSttSynAutoAdjTest::Init()
{
	CSttSynActVolTest::Init();
}

CSttSynAutoAdjTest::~CSttSynAutoAdjTest(void)
{
}

void CSttSynAutoAdjTest::ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA)
{
#ifdef _PSX_QT_LINUX_
    int nCommfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	int nSize = 0;
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nSize = read(nCommfd,(char*)&m_oSyncStepRst,0x250);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

    if(nSize != sizeof(Drv_SyncStepRst))
        return;

    float fAmp,fFre;
    for(int i = 0;i < 6;i++)
    {
        tmt_channel &oChannel = m_pTmtSynParas->m_uiVOL[i];

        fAmp = oChannel.Harm[1].fAmp;
        if(oChannel.Ramp[0].nIndex == 1)
        {
            fAmp = m_oSyncStepRst.nVolt*0.000001;
        }
		oRTDATA.m_oVolCh[i].m_fMag = fAmp;

        fFre = oChannel.Harm[1].fFreq;
        if(oChannel.Ramp[2].nIndex == 1)
        {
            fFre = m_oSyncStepRst.nFre*0.000001;
        }
		oRTDATA.m_oVolCh[i].m_fFreq = fFre;

        unsigned int nPhase = GetPhase(m_oSyncStepRst,i);
        m_fCalAng[i] += nPhase*0.001;

		oRTDATA.m_oVolCh[i].m_fAng = m_fCalAng[i];
    }

    SetVoltAng(oRTDATA);
#endif
}

long CSttSynAutoAdjTest::CalReport(UINT nState)
{
  	m_oSynResults.m_fFreqBordValue = 0.0f;
 	m_oSynResults.m_nAct = 0;
  
#ifdef _PSX_QT_LINUX_
    SynResult &oSynResult=CSttDeviceBase::g_pSttDeviceBase->m_oSynResult;
    if(oSynResult.m_nAct == 1)
    {
        m_oSynResults.m_nAct = 1;
        m_oSynResults.m_fVolBordValue = oSynResult.m_fTripValueV;
        m_oSynResults.m_fFreqBordValue = oSynResult.m_fTripValueF;
        m_oSynResults.m_fVolDelt = fabs(m_pTmtSynParas->m_fVs_Mag - m_oSynResults.m_fVolBordValue);
        m_oSynResults.m_fFreqDelt = fabs(m_pTmtSynParas->m_fVs_Fre - m_oSynResults.m_fFreqBordValue);
    }
#endif

	return 0;
}


void CSttSynAutoAdjTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_AutoAdj(m_pTmtSynParas,pXmlSerialize);
    m_pTmtSynParas->m_nTestType = Stt_Syn_Test_Type_AutoAdj;

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		AfterSetParameter();
		TranslateToStateParas();//参数设置完进行故障转换
	}
}


void CSttSynAutoAdjTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_AutoAdj(&m_oSynResults,  pXmlSerialize);
}

void CSttSynAutoAdjTest::TranslateToStateParas()
{
	TranslateToStateParasBase();
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
    tmt_channel *pVolChannel = m_pTmtSynParas->m_uiVOL;

    m_pTmtSynParas->m_fVoltMax = m_pTmtSynParas->m_fVg_Std*1.2;//上边界
    m_pTmtSynParas->m_fVoltMin = m_pTmtSynParas->m_fVg_Std*0.8;//下边界
    m_pTmtSynParas->m_fFreMax = m_pTmtSynParas->m_fVs_Fre*1.2;
    m_pTmtSynParas->m_fFreMin = m_pTmtSynParas->m_fVs_Fre*0.8;
    m_pTmtSynParas->m_fDrvStepV = m_pTmtSynParas->m_fdVg_dt/1000;
    m_pTmtSynParas->m_fDrvStepF = m_pTmtSynParas->m_fdFg_dt/1000;

    if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ub)
	{
        pVolChannel[1].Ramp[0].nIndex = 1;
        pVolChannel[1].Ramp[2].nIndex = 1;
	}
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ubc)
	{
        pVolChannel[1].Ramp[0].nIndex = 1;
        pVolChannel[2].Ramp[0].nIndex = 1;

        pVolChannel[1].Ramp[2].nIndex = 1;
        pVolChannel[2].Ramp[2].nIndex = 1;
	}
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uz_Uabc)
	{
		pVolChannel[0].Ramp[0].nIndex = 1;
		pVolChannel[1].Ramp[0].nIndex = 1;
		pVolChannel[2].Ramp[0].nIndex = 1;

		pVolChannel[0].Ramp[2].nIndex = 1;
		pVolChannel[1].Ramp[2].nIndex = 1;
		pVolChannel[2].Ramp[2].nIndex = 1;
	}
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uabc1_Uabc2)
	{
		pVolChannel[3].Ramp[0].nIndex = 1;
		pVolChannel[4].Ramp[0].nIndex = 1;
		pVolChannel[5].Ramp[0].nIndex = 1;

		pVolChannel[3].Ramp[2].nIndex = 1;
		pVolChannel[4].Ramp[2].nIndex = 1;
		pVolChannel[5].Ramp[2].nIndex = 1;
	}
}
