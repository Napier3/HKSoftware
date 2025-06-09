#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"../../../SttTestBase/SttComplexp.h"

//#include "../SttStateTest.h"

#include"tmt_syn_test.h"

typedef struct{
    unsigned int nVolt;//uV
    unsigned int nFre;//uHz
    unsigned int nPhase;//0.001¶È
    unsigned int nNormalPhase;//0.001¶È
}Drv_SyncStepRst;

class CSttSynActVolTest : public CSttTestBase
{
public:
    CSttSynActVolTest();
    virtual ~CSttSynActVolTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttSynActVolTest();
    }

    tmt_SynParas *m_pTmtSynParas;
    tmt_SynResults m_oSynResults;
public:
    virtual void AfterSetParameter();
    virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
    virtual long SetParameter(DWORD dwState=0);
    virtual void StartTest();
	virtual void Stop()
	{
		m_bCalRTDATA = FALSE;
		CSttTestBase::Stop();
	}
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs=500);
    virtual BOOL EventProcess();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
	{
		m_bCalRTDATA = TRUE;
		CSttTestBase::ReturnTestStateEvent_TestStart(dTime, dRealTime, bWithEvent);
	}
	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
	{
		m_bCalRTDATA = FALSE;
		CSttTestBase::ReturnTestStateEvent_TestFinish(dTime, dRealTime, bWithEvent);
	}

protected:
	void TranslateToStateParasBase();
	virtual void TranslateToStateParas();
    virtual void ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA);
    float m_fCalAng[6];
    Drv_SyncStepRst m_oSyncStepRst;
    unsigned int GetPhase(Drv_SyncStepRst oSyncStepRst,int nChanIdx);
    float TransAng(float fPh);
    void SetVoltAng(STT_RTDATA_EVENT &oRTDATA);
	BOOL m_bCalRTDATA;
};
