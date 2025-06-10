#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"../../../SttTestBase/SttComplexp.h"
#include"tmt_swing_test.h"
#include "../../../SttTestBase/SttFaultCalculatTool.h"

typedef struct{
    unsigned int nStep;//状态内步数
    unsigned int nType;//实验状态
}Drv_SwingRst;

class CSttSwingTest : public CSttTestBase,public tmt_SwingParas
{
public:
    CSttSwingTest();
    virtual ~CSttSwingTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttSwingTest();
    }
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeMS;
    UINT m_uChangeTime;
    UINT m_uChangeTimeMS;
    UINT m_uStartTimeNS;
    bool m_bIsReturn;
    UINT m_uReturnTimeMS;
    UINT m_uReturnTime;

public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
    virtual void AfterSetParameter();
    virtual double GetTestTimeLong();
    virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
    virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual BOOL EventProcess();

public:
    virtual void TtmToDrv();
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SyncSingleStateTmtResult();

protected:
    void ReCalVoltCurr(STT_RTDATA_EVENT &oRTDATA);
	CSttFaultCalculatTool m_oFaultCalculatTool;
	tmt_SwingResults m_oSwingResults;
    Drv_SwingRst m_oSwingRst;

    tmt_StepUI m_oUI0;
    tmt_GradientProcess m_oUI1;
    tmt_GradientProcess m_oUI2;
	char *m_pszDrvPara;
};
