#include "stdafx.h"
#include"SttSynLeadAngleTest.h"
#include "../SttSystemConfig.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
#endif

CString CSttSynLeadAngleTest::m_strMacroName = "��ǰ�Ǽ���ǰʱ�����";
CString CSttSynLeadAngleTest::m_strMacroID = STT_MACRO_ID_SynLeadAngTest;
CString CSttSynLeadAngleTest::m_strFilePostFix = "saft";
CString CSttSynLeadAngleTest::m_strMacroVer ="1.0";


CSttSynLeadAngleTest::CSttSynLeadAngleTest()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    m_strTestVer = m_strMacroVer;
    SetTestStarting(FALSE);
    m_dTestStartTime=0;
}

CSttSynLeadAngleTest::~CSttSynLeadAngleTest(void)
{
}

void CSttSynLeadAngleTest::ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA)
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

long CSttSynLeadAngleTest::CalReport(UINT nState)
{
    m_oSynResults.m_fFreqBordValue = 0.0f;
    m_oSynResults.m_nAct = 0;

    SynResult &oSynResult=CSttDeviceBase::g_pSttDeviceBase->m_oSynResult;
    if(oSynResult.m_nAct == 1)
    {
        m_oSynResults.m_nAct = 1;
        double fSyncActTime = oSynResult.m_dActTime;

        float fActTime = fSyncActTime - m_dTestStartTime;
        float fDiffFre = fabs(m_pTmtSynParas->m_fVs_Fre - m_pTmtSynParas->m_fVg_Fre);
        float fAngDiff = fActTime*360.0*fDiffFre;

        while(fAngDiff > 360)
        {
            fAngDiff -= 360;
        }
        if(fAngDiff > 180)
        {
            fAngDiff = 360 - fAngDiff;
        }
        m_oSynResults.m_fLeaderAngle = fAngDiff;
        m_oSynResults.m_fLeaderTime = 1/fDiffFre - fActTime;//>0 �������ں������䣬<0������ʱ�����ڵ�һ����λͬ����
    }

    return 0;
}

void CSttSynLeadAngleTest::Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_LeadAng(&m_oSynResults,  pXmlSerialize);
}

void CSttSynLeadAngleTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    CSttSynActFreqTest::Para_XmlSerialize(pXmlSerialize);
    m_pTmtSynParas->m_nTestType = Stt_Syn_Test_Type_LeadAngle;
}
