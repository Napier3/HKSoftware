#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include"tmt_adjust_test.h"

class CSttAdjust_Three : public CSttTestBase, public TMT_ADJUST_THREE
{
public:
    CSttAdjust_Three();
    virtual ~CSttAdjust_Three(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
	static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttAdjust_Three();
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
};
