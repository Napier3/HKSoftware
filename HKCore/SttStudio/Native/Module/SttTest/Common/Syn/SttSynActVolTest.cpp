#include "stdafx.h"
#include"SttSynActVolTest.h"
#include "../SttSystemConfig.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttSynActVolTest::m_strMacroName = "同期电压边界值测试";
CString CSttSynActVolTest::m_strMacroID = STT_MACRO_ID_SynActVoltageTest;
CString CSttSynActVolTest::m_strFilePostFix = "savt";
CString CSttSynActVolTest::m_strMacroVer ="1.0";

CSttSynActVolTest::CSttSynActVolTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;
#ifdef _PSX_QT_LINUX_
    m_pTmtSynParas = stt_test_get_synparas_buff();
#endif
}

void CSttSynActVolTest::Init()
{
    CSttTestBase::Init();
    m_pTmtSynParas->init();
    m_oSynResults.init();
    m_nCurStepIndex = -1;
	m_bCalRTDATA = FALSE;
}

CSttSynActVolTest::~CSttSynActVolTest(void)
{
}

void CSttSynActVolTest::AfterSetParameter()
{

}

unsigned int CSttSynActVolTest::GetPhase(Drv_SyncStepRst oSyncStepRst,int nChanIdx)
{
    if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ub)
    {
        if(nChanIdx == 0)
        {
            return oSyncStepRst.nNormalPhase;
        }
        else if(nChanIdx == 1)
        {
            return oSyncStepRst.nPhase;
        }
        else
        {
            return 0;
        }
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ubc)
    {
        if(nChanIdx == 0)
        {
            return oSyncStepRst.nNormalPhase;
        }
        else if(nChanIdx == 1 || nChanIdx == 2)
        {
            return oSyncStepRst.nPhase;
        }
        else
        {
            return 0;
        }
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uz_Uabc)
    {
        if(nChanIdx == 3)
        {
            return oSyncStepRst.nNormalPhase;
        }
        else if(nChanIdx == 0 || nChanIdx == 1 || nChanIdx == 2)
        {
            return oSyncStepRst.nPhase;
        }
        else
        {
            return 0;
        }
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uabc1_Uabc2)
    {
        if(nChanIdx == 0 || nChanIdx == 1 || nChanIdx == 2)
        {
            return oSyncStepRst.nNormalPhase;
        }
        else if(nChanIdx == 3 || nChanIdx == 4 || nChanIdx == 5)
        {
            return oSyncStepRst.nPhase;
        }
        else
        {
            return 0;
        }
    }

}

float CSttSynActVolTest::TransAng(float fPh)
{
    while((fPh >= 360)||(fPh < 0))
    {
        if(fPh >= 360)
        {
            fPh -= 360;
        }
        else
        {
            fPh += 360;
        }
    }

    return fPh;
}

void CSttSynActVolTest::SetVoltAng(STT_RTDATA_EVENT &oRTDATA)
{
	float fRefAng = oRTDATA.m_oVolCh[0].m_fAng;
    float fRstAng;
    for(int i = 0;i < 6;i++)
    {
		fRstAng = oRTDATA.m_oVolCh[i].m_fAng;
        fRstAng -= fRefAng;
        fRstAng = TransAng(fRstAng);

		oRTDATA.m_oVolCh[i].m_fAng = fRstAng;
    }
}

void CSttSynActVolTest::ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA)
{
    if(m_nCurStepIndex <= 0)
        return;

    float fAmp;
    for(int i = 0;i < 6;i++)
    {
        tmt_channel &oChannel = m_pTmtSynParas->m_uiVOL[i];

        if(oChannel.Ramp[0].nIndex == 1)
        {
            fAmp = oChannel.Harm[1].fAmp;
            if (m_pTmtSynParas->m_fVs_Mag > m_pTmtSynParas->m_fVg_Mag)
            {
                //增压
                fAmp += m_nCurStepIndex*m_pTmtSynParas->m_fDvStep;
            }
            else
            {
                //减压
                fAmp -= m_nCurStepIndex*m_pTmtSynParas->m_fDvStep;
            }
			oRTDATA.m_oVolCh[i].m_fMag = fAmp;
        }
    }

    SetVoltAng(oRTDATA);
}

long CSttSynActVolTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    m_dwCurTickCount++;
	if(m_bCalRTDATA)
    {
        if(m_pTmtSynParas->m_fMaxSynTime >= 0.001 && IsTestTimeFinished(m_pTmtSynParas->m_fMaxSynTime))
        {
            Stop();
			ReturnTestStateEvent_TestFinish(0, 0, FALSE);
			return 0;
        }

#ifdef _PSX_QT_LINUX_
        STT_RTDATA_EVENT oRtdata;
        oRtdata.oTime.dTime = m_dTestStartTime + m_dwCurTickCount;
        oRtdata.oTime.dRealTime = m_dwCurTickCount;
        oRtdata.m_nVolChCount = 0;
        oRtdata.m_nCurChCount = 0;
		oRtdata.m_nHasFaultVolCur=0;
        //电压电流
        for(int i = 0;i < 6;i++)
        {
            tmt_channel &oChannel = m_pTmtSynParas->m_uiVOL[i];
            oRtdata.m_oVolCh[i].m_nIndex = i;
			oRtdata.m_oVolCh[i].m_fMag = oChannel.Harm[1].fAmp;
			oRtdata.m_oVolCh[i].m_fAng = oChannel.Harm[1].fAngle;
			oRtdata.m_oVolCh[i].m_fFreq = oChannel.Harm[1].fFreq;
            oRtdata.m_nVolChCount++;
        }

        ReCalVoltCurr(oRtdata);

        stt_add_rtdatas(oRtdata);
#endif
    }

    return 0;
}

BOOL CSttSynActVolTest::EventProcess()
{
    if(!GetTestStarting())
        return FALSE;

    BOOL bTestFinished=FALSE;
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->ProSynDrvResult(bTestFinished,m_oTestFinishedTime);
#endif
    return bTestFinished;
}

long CSttSynActVolTest::CalReport(UINT nState)
{
    m_oSynResults.m_fVolBordValue = 0.0f;
    m_oSynResults.m_nAct = 0;

#ifdef _PSX_QT_LINUX_
    SynResult &oSynResult=CSttDeviceBase::g_pSttDeviceBase->m_oSynResult;
    if(oSynResult.m_nAct == 1)
    {
        m_oSynResults.m_nAct = 1;
        m_oSynResults.m_fVolBordValue = oSynResult.m_fTripValueV;
        m_oSynResults.m_fVolDelt = fabs(m_pTmtSynParas->m_fVs_Mag - m_oSynResults.m_fVolBordValue);
    }
#endif

    return 0;
}


long CSttSynActVolTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttSynActVolTest::StartTest()
{
    CSttTestBase::StartTest();
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->tmt_to_drv_SynPara(m_pTmtSynParas);

    if(!GetTestStarting())
    {
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
#endif
        SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
        CSttDeviceBase::g_pSttDeviceBase->SetTestStart(SynTest);
#endif
    }
#endif
    CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttSynTest::StartTest >>>>>>");
}

void CSttSynActVolTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_ActVol(m_pTmtSynParas,pXmlSerialize);
    m_pTmtSynParas->m_nTestType = Stt_Syn_Test_Type_VoltageBoder;

    //2020-4-6  lijq  读取参数模式下，需要进行初始化
    if (stt_xml_serialize_is_read(pXmlSerialize))
    {
        AfterSetParameter();
        TranslateToStateParas();//参数设置完进行故障转换
    }
}

void CSttSynActVolTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_ActVol(&m_oSynResults,  pXmlSerialize);
}

float GetPhaseDiff(float fPhaseDiff,int nWindAngs)
{
    float oPhaseDiff = fPhaseDiff;
    if(nWindAngs < WingAng_6)
    {
        oPhaseDiff -= 30*nWindAngs;
    }
    else
    {
        oPhaseDiff += 360-30*nWindAngs;
    }
    return oPhaseDiff;
}

void CSttSynActVolTest::TranslateToStateParasBase()
{
    float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
    float oPhaseDiff = GetPhaseDiff(m_pTmtSynParas->m_fPhaseDiff,m_pTmtSynParas->m_nWindAngs);

    //////////////////////////////////////////////////////////////////////////
    //	m_pStateTest->m_oStateParas.m_paraState[0].m_fTimeState = m_pTmtSynParas->m_fMaxSynTime;

    //////////////////////////////////////////////////////////////////////////
    tmt_channel *pVolChannel = m_pTmtSynParas->m_uiVOL;

    for (int nIndex=0;nIndex<6;nIndex++)//先将所有通道电压电流置为0
    {
        pVolChannel[nIndex].Harm[1].fAmp = 0.0f;
    }

    if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ub)
    {
        pVolChannel[0].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag;
        pVolChannel[1].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag;

        pVolChannel[0].Harm[1].fAngle = 0.0f;
        pVolChannel[1].Harm[1].fAngle = 0.0f + oPhaseDiff;

        pVolChannel[0].Harm[1].fFreq = m_pTmtSynParas->m_fVs_Fre;
        pVolChannel[1].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;

    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ubc)
    {
        pVolChannel[0].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag;
        pVolChannel[1].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag/1.7320508;
        pVolChannel[2].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag/1.7320508;

        pVolChannel[0].Harm[1].fAngle = 0.0f;
        pVolChannel[1].Harm[1].fAngle = 150.0f + oPhaseDiff;
        pVolChannel[2].Harm[1].fAngle = 30.0f + oPhaseDiff;

        pVolChannel[0].Harm[1].fFreq = m_pTmtSynParas->m_fVs_Fre;
        pVolChannel[1].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;
        pVolChannel[2].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;

    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uz_Uabc)
    {
        float fRefAngle = 0.0f;

        if (m_pTmtSynParas->m_nRefVolType == Stt_Syn_Test_Ref_Vol_Def_Ua)
        {
            pVolChannel[3].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag;//*1.7320508;
        }
        else if (m_pTmtSynParas->m_nRefVolType == Stt_Syn_Test_Ref_Vol_Def_Ub)
        {
            fRefAngle = -120.0f;
            pVolChannel[3].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag;//*1.7320508;
        }
        else if (m_pTmtSynParas->m_nRefVolType == Stt_Syn_Test_Ref_Vol_Def_Uc)
        {
            fRefAngle = 120.0f;
            pVolChannel[3].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag;//*1.7320508;
        }
        else if (m_pTmtSynParas->m_nRefVolType == Stt_Syn_Test_Ref_Vol_Def_Uab)
        {
            fRefAngle = -150.0f;
            pVolChannel[3].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag;
        }
        else if (m_pTmtSynParas->m_nRefVolType == Stt_Syn_Test_Ref_Vol_Def_Ubc)
        {
            fRefAngle = 90.0f;
            pVolChannel[3].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag;
        }
        else if (m_pTmtSynParas->m_nRefVolType == Stt_Syn_Test_Ref_Vol_Def_Uca)
        {
            fRefAngle = -30.0f;
            pVolChannel[3].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag;
        }

        pVolChannel[0].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag/1.7320508;
        pVolChannel[1].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag/1.7320508;
        pVolChannel[2].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag/1.7320508;

        pVolChannel[0].Harm[1].fAngle = 0.0f - fRefAngle + oPhaseDiff;
        pVolChannel[1].Harm[1].fAngle = -120.0f - fRefAngle + oPhaseDiff;
        pVolChannel[2].Harm[1].fAngle = 120.0f - fRefAngle + oPhaseDiff;
        pVolChannel[3].Harm[1].fAngle = 0.0f;

        pVolChannel[3].Harm[1].fFreq = m_pTmtSynParas->m_fVs_Fre;
        pVolChannel[0].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;
        pVolChannel[1].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;
        pVolChannel[2].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uabc1_Uabc2)
    {
        pVolChannel[0].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag/1.7320508;
        pVolChannel[1].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag/1.7320508;
        pVolChannel[2].Harm[1].fAmp = m_pTmtSynParas->m_fVs_Mag/1.7320508;
        pVolChannel[3].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag/1.7320508;
        pVolChannel[4].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag/1.7320508;
        pVolChannel[5].Harm[1].fAmp = m_pTmtSynParas->m_fVg_Mag/1.7320508;

        pVolChannel[0].Harm[1].fAngle = 0.0f;
        pVolChannel[1].Harm[1].fAngle = -120.0f;
        pVolChannel[2].Harm[1].fAngle = 120.0f;
        pVolChannel[3].Harm[1].fAngle = 0.0f + oPhaseDiff;
        pVolChannel[4].Harm[1].fAngle = -120.0f + oPhaseDiff;
        pVolChannel[5].Harm[1].fAngle = 120.0f + oPhaseDiff;

        pVolChannel[0].Harm[1].fFreq = m_pTmtSynParas->m_fVs_Fre;
        pVolChannel[1].Harm[1].fFreq = m_pTmtSynParas->m_fVs_Fre;
        pVolChannel[2].Harm[1].fFreq = m_pTmtSynParas->m_fVs_Fre;
        pVolChannel[3].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;
        pVolChannel[4].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;
        pVolChannel[5].Harm[1].fFreq = m_pTmtSynParas->m_fVg_Fre;
    }

    for (int nIndex=0;nIndex<6;nIndex++)//先将所有通道电压电流置为0
    {
        m_fCalAng[nIndex] = pVolChannel[nIndex].Harm[1].fAngle;
    }
}

void CSttSynActVolTest::TranslateToStateParas()
{
    TranslateToStateParasBase();
    float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
    tmt_channel *pVolChannel = m_pTmtSynParas->m_uiVOL;

    m_pTmtSynParas->m_fVoltMax = m_pTmtSynParas->m_fVg_Std*1.2;//上边界
    m_pTmtSynParas->m_fVoltMin = m_pTmtSynParas->m_fVg_Std*0.8;//下边界

    if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ub)
    {
        pVolChannel[1].Ramp[0].nIndex = 1;
        m_pTmtSynParas->m_fDrvStepV = m_pTmtSynParas->m_fDvStep;
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ubc)
    {
        pVolChannel[1].Ramp[0].nIndex = 1;
        pVolChannel[2].Ramp[0].nIndex = 1;

        m_pTmtSynParas->m_fDrvStepV = m_pTmtSynParas->m_fDvStep/1.7320508;
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uz_Uabc)
    {
        pVolChannel[0].Ramp[0].nIndex = 1;
        pVolChannel[1].Ramp[0].nIndex = 1;
        pVolChannel[2].Ramp[0].nIndex = 1;

        if (m_pTmtSynParas->m_nRefVolType<Stt_Syn_Test_Ref_Vol_Def_Uab)
        {
            m_pTmtSynParas->m_fDrvStepV = m_pTmtSynParas->m_fDvStep;
        }
        else
        {
            m_pTmtSynParas->m_fDrvStepV = m_pTmtSynParas->m_fDvStep/1.7320508;
        }
    }
    else if (m_pTmtSynParas->m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uabc1_Uabc2)
    {
        pVolChannel[3].Ramp[0].nIndex = 1;
        pVolChannel[4].Ramp[0].nIndex = 1;
        pVolChannel[5].Ramp[0].nIndex = 1;

        m_pTmtSynParas->m_fDrvStepV = m_pTmtSynParas->m_fDvStep;
    }
}
