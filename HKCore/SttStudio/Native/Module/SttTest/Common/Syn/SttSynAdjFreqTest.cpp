#include "stdafx.h"
#include "SttSynAdjFreqTest.h"
#include "../SttSystemConfig.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttSynAdjFreqTest::m_strMacroName = "调频周期测试";
CString CSttSynAdjFreqTest::m_strMacroID = STT_MACRO_ID_SynAdjFreqTest;
CString CSttSynAdjFreqTest::m_strFilePostFix = "saft";
CString CSttSynAdjFreqTest::m_strMacroVer ="1.0";


CSttSynAdjFreqTest::CSttSynAdjFreqTest()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	m_dTestStartTime=0;
}

void CSttSynAdjFreqTest::Init()
{
    CSttSynActVolTest::Init();
}

CSttSynAdjFreqTest::~CSttSynAdjFreqTest(void)
{

}

void CSttSynAdjFreqTest::ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA)
{
#ifdef _PSX_QT_LINUX_
    int nCommfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	int nSize = 0;
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nSize = read(nCommfd,(char*)&m_oSyncStepRst,0x250);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

    if(nSize != sizeof(Drv_SyncStepRst))
        return;

    for(int i = 0;i < 6;i++)
    {
        unsigned int nPhase = GetPhase(m_oSyncStepRst,i);
        m_fCalAng[i] += nPhase*0.001;

		oRTDATA.m_oVolCh[i].m_fAng = m_fCalAng[i];
    }

    SetVoltAng(oRTDATA);
#endif
}

long CSttSynAdjFreqTest::CalReport(UINT nState)
{
  	m_oSynResults.m_fFreqBordValue = 0.0f;
 	m_oSynResults.m_nAct = 0;
    m_oSynResults.m_fFAdjWidth = 0;
    m_oSynResults.m_fFAdjTime = 0;

    SynResult &oSynResult=CSttDeviceBase::g_pSttDeviceBase->m_oSynResult;
    for(int i = 0; i < 8;i++)
    {
        if(oSynResult.m_nBinSwitchCount[i] == 3)
        {
            m_oSynResults.m_fFAdjWidth = oSynResult.m_dTimeBinAct[i][1] -
                    oSynResult.m_dTimeBinAct[i][0];
             m_oSynResults.m_fFAdjTime = oSynResult.m_dTimeBinAct[i][2] -
                     oSynResult.m_dTimeBinAct[i][0];
             m_oSynResults.m_nAct = 1;
            break;
        }
    }

	return 0;
}

void CSttSynAdjFreqTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_AdjFreqCycle(m_pTmtSynParas,pXmlSerialize);
    m_pTmtSynParas->m_nTestType = Stt_Syn_Test_Type_AdjFreqCycle;

	//2020-4-6  lijq  读取参数模式下，需要进行初始化
	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		TranslateToStateParas();//参数设置完进行故障转换
	}
}

void CSttSynAdjFreqTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_AdjFreqCycle(&m_oSynResults,  pXmlSerialize);
}

void CSttSynAdjFreqTest::TranslateToStateParas()
{
	TranslateToStateParasBase();
        /***
	float fStdLN_Vol = g_theSystemConfig->m_fVNom/SQRT3;//计算标准相电压,一般57.735V
	tmt_channel *pVolChannel = m_pStateTest->m_oStateParas.m_paraState[0].m_uiVOL;
	tmt_channel *pCurChannel = m_pStateTest->m_oStateParas.m_paraState[0].m_uiCUR;
	m_pStateTest->m_oStateParas.m_paraState[0].m_nRampTimeGrad = 1;//设置为滑差递变  递变分度为1ms

	if (m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ub)
	{
		pVolChannel[1].Ramp[0].nIndex = 1;
		pVolChannel[1].Ramp[0].fEnd = m_fVg_Std;
		pVolChannel[1].Ramp[0].fStep = m_fdVg_dt/1000;

		pVolChannel[1].Ramp[2].nIndex = 1;
		pVolChannel[1].Ramp[2].fEnd = m_fVs_Fre;
		pVolChannel[1].Ramp[2].fStep = m_fdFg_dt/1000;
	}
	else if (m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Ua_Ubc)
	{
		pVolChannel[1].Ramp[0].nIndex = 1;
		pVolChannel[1].Ramp[0].fEnd = m_fVg_Std;
		pVolChannel[1].Ramp[0].fStep = m_fdVg_dt/1000;

		pVolChannel[2].Ramp[0].nIndex = 1;
		pVolChannel[2].Ramp[0].fEnd = m_fVg_Std;
		pVolChannel[2].Ramp[0].fStep = m_fdVg_dt/1000;


		pVolChannel[1].Ramp[2].nIndex = 1;
		pVolChannel[1].Ramp[2].fEnd = m_fVs_Fre;
		pVolChannel[1].Ramp[2].fStep = m_fdFg_dt/1000;

		pVolChannel[2].Ramp[2].nIndex = 1;
		pVolChannel[2].Ramp[2].fEnd = m_fVs_Fre;
		pVolChannel[2].Ramp[2].fStep = m_fdFg_dt/1000;
	}
	else if (m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uz_Uabc)
	{
		pVolChannel[0].Ramp[0].nIndex = 1;
		pVolChannel[1].Ramp[0].nIndex = 1;
		pVolChannel[2].Ramp[0].nIndex = 1;

		pVolChannel[0].Ramp[0].fEnd = m_fVg_Std;
		pVolChannel[1].Ramp[0].fEnd = m_fVg_Std;
		pVolChannel[2].Ramp[0].fEnd = m_fVg_Std;

		pVolChannel[0].Ramp[0].fStep = m_fdVg_dt/1000;
		pVolChannel[1].Ramp[0].fStep = m_fdVg_dt/1000;
		pVolChannel[2].Ramp[0].fStep = m_fdVg_dt/1000;


		pVolChannel[0].Ramp[2].nIndex = 1;
		pVolChannel[1].Ramp[2].nIndex = 1;
		pVolChannel[2].Ramp[2].nIndex = 1;

		pVolChannel[0].Ramp[2].fEnd = m_fVs_Fre;
		pVolChannel[1].Ramp[2].fEnd = m_fVs_Fre;
		pVolChannel[2].Ramp[2].fEnd = m_fVs_Fre;

		pVolChannel[0].Ramp[2].fStep = m_fdFg_dt/1000;
		pVolChannel[1].Ramp[2].fStep = m_fdFg_dt/1000;
		pVolChannel[2].Ramp[2].fStep = m_fdFg_dt/1000;
	}
	else if (m_nVolDefType == Stt_Syn_Test_Vol_Def_Type_Uabc1_Uabc2)
	{
		pVolChannel[3].Ramp[0].nIndex = 1;
		pVolChannel[4].Ramp[0].nIndex = 1;
		pVolChannel[5].Ramp[0].nIndex = 1;

		pVolChannel[3].Ramp[0].fEnd = m_fVg_Std;
		pVolChannel[4].Ramp[0].fEnd = m_fVg_Std;
		pVolChannel[5].Ramp[0].fEnd = m_fVg_Std;

		pVolChannel[3].Ramp[0].fStep = m_fdVg_dt/1000;
		pVolChannel[4].Ramp[0].fStep = m_fdVg_dt/1000;
		pVolChannel[5].Ramp[0].fStep = m_fdVg_dt/1000;


		pVolChannel[3].Ramp[2].nIndex = 1;
		pVolChannel[4].Ramp[2].nIndex = 1;
		pVolChannel[5].Ramp[2].nIndex = 1;

		pVolChannel[3].Ramp[2].fEnd = m_fVs_Fre;
		pVolChannel[4].Ramp[2].fEnd = m_fVs_Fre;
		pVolChannel[5].Ramp[2].fEnd = m_fVs_Fre;

		pVolChannel[3].Ramp[2].fStep = m_fdFg_dt/1000;
		pVolChannel[4].Ramp[2].fStep = m_fdFg_dt/1000;
		pVolChannel[5].Ramp[2].fStep = m_fdFg_dt/1000;
	}
    ***/
}
