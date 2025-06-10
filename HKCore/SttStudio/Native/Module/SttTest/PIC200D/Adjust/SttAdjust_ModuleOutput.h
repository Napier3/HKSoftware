#pragma once

#include"../../../SttTestBase/SttTestBase.h"
#include"../../common/Adjust/tmt_adjust_test.h"
#include "../../common/Adjust/SttAdjustTool.h"
#include "../../common/tmt_common_def.h"

class CSttAdjust_ModuleOutput : public CSttTestBase, public TMT_ADJ_MODULE_OUTPUT
{
public:
    CSttAdjust_ModuleOutput();
    virtual ~CSttAdjust_ModuleOutput(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttAdjust_ModuleOutput();
    }
    
public:


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
    virtual void Stop();

public:
    virtual void TtmToDrv();
	virtual BOOL EventProcess();
};

extern PTMT_ADJ_MODULE_OUTPUT g_theModuleOutPut;
